#include "StdAfx.h"
#include "RectangleContainer.h"
#include "ExtentedPolygon.h"
#include <algorithm>
#include <functional>
#include "cad_helper.h"
#include "Windows.h" 


// 比较方法
struct CPolygonCompar:public binary_function<CExentedPolygon*,CExentedPolygon*,bool>
{
	bool operator()(CExentedPolygon*p1,CExentedPolygon*p2)const
	{
		if(p1!=NULL && p1!= NULL)
		{
			return p1->equal(p2);
		}
		return false;
	}
};



CRectangleContainer::CRectangleContainer(int x,int y,int width, int height)
:m_container(NULL)
,m_blankArea(width*height)
,m_area(width*height)
,m_listSize(0)
,m_x(x)
,m_y(y)
,m_width(width)
,m_height(height)
{
	vector<POINT> points;
	POINT p1 = {x,y},p2 = {x,y+height},p3 = {x+width,y+height},p4 = {x+width,y};
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	m_container = new CExentedPolygon(points);
	for(int i = 0; i < 5;++i)
	{
		m_polygons_inside[i] = vector<CExentedPolygon*>();
	}  
}

CRectangleContainer::~CRectangleContainer(void)
{
	delete m_container;
	m_container = NULL;
}

vector<CExentedPolygon*> CRectangleContainer::getAllPolygons()
{

	vector<CExentedPolygon*> resultList;

	for(int i =0;i < 5;++i)
	{
		vector<CExentedPolygon*> tmpList = m_polygons_inside[i];
		std::copy(tmpList.begin(), tmpList.end(), std::back_inserter(resultList));
	}
	return resultList;
}
int CRectangleContainer::getQuadrant(CExentedPolygon* polygon)
{
	return calculateQuadrant(polygon,m_x,m_y,m_width,m_height);
}
int CRectangleContainer::calculateQuadrant(CExentedPolygon* polygon, int x, int y, int width, int height)
{

	POINT center;
	center.x = x+width/2;
	center.y = y+height/2;

	CRectangleContainer* section1 = new CRectangleContainer(x,y,width/2,height/2);
	CRectangleContainer* section2 = new CRectangleContainer(center.x,y,width/2,height/2);
	CRectangleContainer* section3 = new CRectangleContainer(x,center.y,width/2,height/2);
	CRectangleContainer* section4 = new CRectangleContainer(center.x,center.y,width/2,height/2);

	int result = 0;
	if(section1->contains(polygon)) 
	{
		result = 1;
	} 
	else if(section2->contains(polygon)) 
	{
		result = 2;
	} 
	else if(section3->contains(polygon)) 
	{
		result = 3;
	} 
	else if(section4->contains(polygon)) 
	{
		result = 4;
	} 

	delete section1;section1 = NULL;
	delete section2;section2 = NULL;
	delete section3;section3 = NULL;
	delete section4;section4 = NULL;
 
	return result;

}
bool CRectangleContainer::contains(CExentedPolygon*polygon)
{
	vector<POINT>& POINTs = polygon->getVerts();
	int size = POINTs.size();
	for(int i = 0; i < size; ++i)
	{
		if(!contains(POINTs.at(i).x,POINTs.at(i).y))
		{
			return false;
		}
	}

	return true;
}
bool  CRectangleContainer::contains(double x,double y)
{
	if((x >= m_x) && (x <= m_x+m_width) && (y >= m_y) && (y <= m_y+m_height))
	{
		return true;
	}
	return false;
}

bool CRectangleContainer::remove(CExentedPolygon* polygon)
{
	vector<CExentedPolygon*>& polyList = this->m_polygons_inside[polygon->getQuadrant()];
	
	vector<CExentedPolygon*>::iterator iter = find_if(polyList.begin(),polyList.end(),bind2nd(CPolygonCompar(),polygon));
	
	bool res = polyList.erase(iter) != polyList.end();
	if(res)
	{
		double area= 0;
		polygon->getArea(area);
		this->m_blankArea += area;
		this->m_listSize--;
	}
	return res;
}

void CRectangleContainer::put(CExentedPolygon* polygon)
{
	(this->m_polygons_inside[polygon->getQuadrant()]).push_back(polygon);
	double area = 0.0;
	polygon->getArea(area);
	this->m_blankArea-=area;
	if(this->m_blankArea < 0)
	{
		this->m_blankArea = 0;
		return ;
	}
	m_listSize = 0;
	for(int i = 0; i < 5; ++i)
	{
		m_listSize+=(this->m_polygons_inside[i]).size();
	}

	
	vector<POINT>& arrayList = polygon->getVerts();
	int size = (int)arrayList.size();

	
	  
	OutputDebugStringA("<Polygon>\n\r");	
	char buffer[128] = {0};
	for(int i = 0 ;i < size; ++i)
	{
		memset(buffer,0x0,128); 
		POINT pt = arrayList[i];
		long x = pt.x;
		long y = pt.y;
		sprintf(buffer, "<Point><X>%d</X><Y>%d</Y></Point>\n\r",x,y); 

		OutputDebugStringA(buffer);		
	}
	OutputDebugStringA("</Polygon>\n\r");
	

	//
	//acutPrintf(_T("%d: %d-edges  %.2f%%-coverage  %.2f-area\n\r"),m_listSize,size,getCoverageRatio()*100,this->m_blankArea);
	//printfw(_T("%d: %d-edges  %.2f%%-coverage  %.2f-area\n\r"),m_listSize,size,getCoverageRatio()*100,this->m_blankArea);
	// 添加到模型空间
	//Cad_Helper::PostToModelSpace(polygon->getEnty());

}

bool CRectangleContainer::canSafePut(CExentedPolygon* polygon)
{
	if(!this->contains(polygon))
	{
		return false;
	}

	int section = getQuadrant(polygon);
	polygon->setQuadrant(section);

	{	
		vector<CExentedPolygon*>&  polyList = this->m_polygons_inside[0];
		for(int i = 0;i < (int)polyList.size();++i)
		{
			if(polygon->intersects(polyList[i]))
			{
				return false;
			}
		}
	}

	if(section == 0)
	{
		for(int i = 1; i < 5;++i)
		{
			vector<CExentedPolygon*>& polyList = this->m_polygons_inside[i];
			for(int j = 0;j < polyList.size();++j)
			{
				if(polygon->intersects(polyList[j]))
				{
					return false;
				}
			}
		}
	}
	else
	{
		vector<CExentedPolygon*>& polyList = this->m_polygons_inside[section];
		for(int j = 0;j < polyList.size();++j)
		{
			if(polygon->intersects(polyList[j]))
			{
				return false;
			}
		}
	} 
	 
	return true; 
}
#include "StdAfx.h"
#include "ExtentedPolygon.h"
#include "guid_helper.h"
#include "cad_helper.h"



CExentedPolygon::CExentedPolygon(const vector<POINT>& points)
:m_points(points)
,m_quadrant(-1)
,m_area(-1)
,m_radius(0)
,m_circleCenter(POINT())
// ,m_entity(NULL)
{ 
	//m_entity = new AcDb2dPolyline(AcDb::k2dSimplePoly,m_points,0,Adesk::kTrue);
	m_key = guid::createGuid();
}
bool CExentedPolygon::equal(CExentedPolygon* polygon)
{
	if(NULL != polygon)
	{
		return polygon->getKey() == m_key;
	}
	return false;
}

CExentedPolygon::~CExentedPolygon(void)
{
	 
	
}
//AcDb2dPolyline* CExentedPolygon::getEnty()
//{
//	if(NULL == m_entity)
//	{
//		m_entity = new AcDb2dPolyline(AcDb::k2dSimplePoly,m_points,0,Adesk::kTrue);
//	}
//	return m_entity;	
//}
 

void CExentedPolygon::getArea(double& area)
{  
	if(m_area  > 0)
	{
		area = m_area;
	}

	area = Cad_Helper::getArea(this->m_points);

	m_area = area;
}
vector<POINT> CExentedPolygon::getVerts()
{
	return m_points;
}
void CExentedPolygon::GetMinMaxProjs(POINT arix,int & minProj, int & maxProj)
{
	int size = m_points.size();  

	minProj = m_points[0].x* arix.x + m_points[0].y*arix.y;
	maxProj = minProj;

	for(int i = 1; i < size; ++i)
	{
		int proj = m_points[i].x* arix.x + m_points[i].y*arix.y;
		if(minProj > proj)
		{
			minProj = proj;
		}

		if(maxProj < proj)
		{
			maxProj = proj;
		}
	} 
}
// 外接圆是否相交
// true 表示相交
// false 表示相交
bool  CExentedPolygon::OutBoxIntersects(CExentedPolygon* polygon)
{
	// 半径之间和
	double radiusDistance =  polygon->getRadius() + this->m_radius ;
	int centerDistance =  abs(pow(this->m_circleCenter.x - polygon->getCircleCenter().x,2.0)+pow(this->m_circleCenter.y - polygon->getCircleCenter().y,2.0));

	return centerDistance < radiusDistance;
	 
}
bool CExentedPolygon::intersects(CExentedPolygon* polygon)
{


	 /*if(!OutBoxIntersects(polygon))
	 {
		 return false;
	 }*/

	 
	int size = m_points.size();
	// Check each of this polygon's norms
	for(int i = 0; i < size; ++i)
	{
		int minProj1,maxProj1,minProj2,maxProj2;
		this->GetMinMaxProjs(this->getNorms()[i],minProj1,maxProj1);
		polygon->GetMinMaxProjs(this->getNorms()[i],minProj2,maxProj2);

		if(maxProj1<minProj2 || maxProj2 <  minProj1)
		{
			return false;
		}
	}

 
	vector<POINT>& points = polygon->getVerts();
	size = points.size();
	// Check each of other polygon's norms
	for (int i = 0; i < size; i++) 
	{

		int minProj1,maxProj1,minProj2,maxProj2;
		this->GetMinMaxProjs(polygon->getNorms()[i],minProj1,maxProj1);
		polygon->GetMinMaxProjs(polygon->getNorms()[i],minProj2,maxProj2);

		if(maxProj1<minProj2 || maxProj2 <  minProj1)
		{
			return false;
		}
	}


	return true;
}
vector<POINT> CExentedPolygon::getNorms()
{
	if(!m_norms.empty())
	{
		return m_norms;
	}
	 
 
	int size = m_points.size();
	int i= 0;
	for( ; i < size -1; ++i)
	{
		POINT& pt1 =m_points[i];
		POINT& pt2 =m_points[i+1];
		POINT normPt={pt1.y - pt2.y,pt2.x-pt1.x};
		m_norms.push_back(normPt);
	}
	POINT &pt2 =m_points.at(0);
	POINT &pt1 =m_points.at(i);
	POINT ptTemp = {pt1.y - pt2.y,pt2.x-pt1.x};
	m_norms.push_back(ptTemp); 

	return m_norms;

}

void CExentedPolygon::treanslate(int deltX,int deltY)
{  
	this->m_circleCenter.x += deltX;
	this->m_circleCenter.y += deltY;
	int size = m_points.size();
	int i= 0;
	for( ; i < size; ++i)
	{
		POINT& pt = m_points[i]; 
		pt.x+=deltX;
		pt.y+= deltY;
		 
		
	}
 
}

#include "StdAfx.h"
#include "ExtentedPolygon.h"
#include "guid_helper.h"
#include "cad_helper.h"



CExentedPolygon::CExentedPolygon(const AcGePoint3dArray& points)
:m_points(points)
,m_quadrant(-1)
,m_area(-1)
,m_radius(0)
,m_circleCenter(AcGePoint3d())
,m_entity(NULL)
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
AcDb2dPolyline* CExentedPolygon::getEnty()
{
	if(NULL == m_entity)
	{
		m_entity = new AcDb2dPolyline(AcDb::k2dSimplePoly,m_points,0,Adesk::kTrue);
	}
	return m_entity;	
}
 

void CExentedPolygon::getArea(double& area)
{  
	if(m_area  > 0)
	{
		area = m_area;
	}

	area = Cad_Helper::getArea(this->m_points);

	m_area = area;
}
AcGePoint3dArray CExentedPolygon::getVerts()
{
	return m_points;
}
void CExentedPolygon::GetMinMaxProjs(AcGePoint3d arix,int & minProj, int & maxProj)
{
	int size = m_points.length();  

	minProj = m_points.at(0).x* arix.x + m_points[0].y*arix.y;
	maxProj = minProj;

	for(int i = 1; i < size; ++i)
	{
		int proj = m_points.at(i).x* arix.x + m_points[i].y*arix.y;
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
	double radiusDistance =  polygon->getRadius() + this->m_radius;
	 
	// 圆点之间的距离
	int centerDistance =  sqrt(pow(this->m_circleCenter.x - polygon->getCircleCenter().x,2.0)+pow(this->m_circleCenter.y - polygon->getCircleCenter().y,2.0));
 
	return centerDistance < radiusDistance; 
}


bool CExentedPolygon::intersects(CExentedPolygon* polygon)
{ 
	if(!OutBoxIntersects(polygon))
	{
		return false;
	} 

	int size = m_points.length();
	// Check each of this polygon's norms
	for(int i = 0; i < size; ++i)
	{
		int minProj1,maxProj1,minProj2,maxProj2;
		this->GetMinMaxProjs(this->getNorms().at(i),minProj1,maxProj1);
		polygon->GetMinMaxProjs(this->getNorms().at(i),minProj2,maxProj2);

		if(maxProj1<minProj2 || maxProj2 <  minProj1)
		{
			return false;
		}
	}

 
	AcGePoint3dArray& points = polygon->getVerts();
	size = points.length();
	// Check each of other polygon's norms
	for (int i = 0; i < size; i++) 
	{

		int minProj1,maxProj1,minProj2,maxProj2;
		this->GetMinMaxProjs(polygon->getNorms().at(i),minProj1,maxProj1);
		polygon->GetMinMaxProjs(polygon->getNorms().at(i),minProj2,maxProj2);

		if(maxProj1<minProj2 || maxProj2 <  minProj1)
		{
			return false;
		}
	}


	return true;
}
AcGePoint3dArray CExentedPolygon::getNorms()
{
	if(!m_norms.isEmpty())
	{
		return m_norms;
	}
	 
 
	int size = m_points.length();
	int i= 0;
	for( ; i < size -1; ++i)
	{
		AcGePoint3d& pt1 =m_points.at(i);
		AcGePoint3d& pt2 =m_points.at(i+1);
		AcGePoint3d normPt(pt1.y - pt2.y,pt2.x-pt1.x,0);
		m_norms.append(normPt);
	}
	AcGePoint3d &pt2 =m_points.at(0);
	AcGePoint3d &pt1 =m_points.at(i);
	m_norms.append(AcGePoint3d(pt1.y - pt2.y,pt2.x-pt1.x,0)); 

	return m_norms;

}

void CExentedPolygon::treanslate(int deltX,int deltY)
{ 
	AcGeMatrix3d matrix = AcGePoint3d(deltX,deltY,0) - AcGePoint3d(0,0,0); 
	 
	this->m_circleCenter.x+= deltX;
	this->m_circleCenter.y+= deltY;
	int size = m_points.length();
	int i= 0;
	for( ; i < size; ++i)
	{
		AcGePoint3d& pt = m_points.at(i); 
		//pt.transformBy(matrix);
		pt.x+= deltX;
		pt.y+= deltY;
		 
		
	}
 
}

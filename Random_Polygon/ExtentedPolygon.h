#pragma once
#include <string>
using namespace std;


class CExentedPolygon
{
public:
	CExentedPolygon(const AcGePoint3dArray& points); 
	virtual ~CExentedPolygon(void);
	AcDb2dPolyline* getEnty();
	void getArea(double& area);
    AcGePoint3dArray getNorms();
	// 获得顶点坐标集合
	AcGePoint3dArray getVerts();
	// 获得投影
	void GetMinMaxProjs(AcGePoint3d arix,int & minProj, int & maxProj);
	// 是否相交
    bool intersects(CExentedPolygon* polygon);
	
	AcGePoint3d getCircleCenter(){return m_circleCenter;};
	void   setCircleCenter(AcGePoint3d center){this->m_circleCenter = center;};

	double getRadius(){return m_radius;};
	void   setRadius(double radius){this->m_radius = radius;};

	int getQuadrant(){return m_quadrant;};
	void setQuadrant(int quadrant){this->m_quadrant = quadrant;};
	
	void treanslate(int deltX,int deltY);
	bool equal(CExentedPolygon* polygon);
	string getKey(){return m_key;};
 
	
private:
	AcDb2dPolyline* m_entity;
	int m_quadrant;
	double m_area;
	double m_radius;// radius of the polygons' circum circle if it exists
	AcGePoint3d m_circleCenter;
	// 法向量
	AcGePoint3dArray m_norms;
	// 坐标点
	AcGePoint3dArray m_points; 
	string m_key;
};

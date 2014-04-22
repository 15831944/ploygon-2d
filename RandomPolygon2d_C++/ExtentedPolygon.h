#pragma once
#include <string>
#include <vector>
using namespace std; 
#include <WinDef.h>
#include <Windows.h>

class CExentedPolygon 
{
public:
	CExentedPolygon(const vector<POINT>& points); 
	virtual ~CExentedPolygon(void);
	/*AcDb2dPolyline* getEnty();*/
	void getArea(double& area);
    vector<POINT> getNorms();
	// 获得顶点坐标集合
	vector<POINT> getVerts();
	// 获得投影
	void GetMinMaxProjs(POINT arix,int & minProj, int & maxProj);
	// 是否相交
    bool intersects(CExentedPolygon* polygon);
	
	// 外接圆是否相交
	bool OutBoxIntersects(CExentedPolygon* polygon);

	POINT getCircleCenter(){return m_circleCenter;};
	void   setCircleCenter(POINT center){this->m_circleCenter = center;};

	double getRadius(){return m_radius;};
	void   setRadius(double radius){this->m_radius = radius;};

	int getQuadrant(){return m_quadrant;};
	void setQuadrant(int quadrant){this->m_quadrant = quadrant;};
	
	void treanslate(int deltX,int deltY);
	bool equal(CExentedPolygon* polygon);
	string getKey(){return m_key;};
 
	
private:
	//AcDb2dPolyline* m_entity;
	int m_quadrant;
	double m_area;
	double m_radius;// radius of the polygons' circum circle if it exists
	POINT m_circleCenter;
	// 法向量
	vector<POINT> m_norms;
	// 坐标点
	vector<POINT> m_points; 
	string m_key;

};

#pragma once
#include "ExtentedPolygon.h"
#include <vector>
using namespace std;
class CRectangleContainer  
{
public:
	CRectangleContainer(int x,int y,int width, int height);
	~CRectangleContainer(void);
	vector<CExentedPolygon*> getAllPolygons();
	bool contains(CExentedPolygon*polygon);
	bool remove(CExentedPolygon* polygon);
	void put(CExentedPolygon* polygon);
	bool safePut(CExentedPolygon* polygon);
	vector<CExentedPolygon*>* getPolygonInsize(){return this->m_polygons_inside;};

	double getBlankArea(){return this->m_blankArea;};
	double getArea(){return this->m_area;};

	int getListSize(){return m_listSize;};

	double getCoverageRatio(){return 1 - this->getBlankArea()/this->getArea();};


private:
	int getQuadrant(CExentedPolygon* polygon);
	int calculateQuadrant(CExentedPolygon* polygon, int x, int y, int width, int height);
	bool contains(double x,double y);
private:
	double m_blankArea;
	double m_area;
	int    m_listSize;
	vector<CExentedPolygon*> m_polygons_inside[5];
	CExentedPolygon* m_container;
public:
	double m_x;
	double m_y;
	double m_height;
	double m_width;
};

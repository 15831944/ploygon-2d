#include "StdAfx.h"
#include "ExtendedPolygonBuilder.h"
#include "ExtentedPolygon.h"
#include "RectangleContainer.h"
#include "cad_helper.h"
#include <time.h>
#include <math.h>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;
 


const double PI = 3.1415927;
 
bool Contain(const vector<POINT>& list, POINT p)
{
	for(int i = 0; i < (int) list.size();++i)
	{
		if(p.x == list[i].x && p.y == list[i].y)
		{
			return true;
		}
	}

	return false;
}


CExtendedPolygonBuilder::CExtendedPolygonBuilder(CRectangleContainer* container)
:m_pContainer(container)
{
}

CExtendedPolygonBuilder::~CExtendedPolygonBuilder(void)
{
}
 

 
CExentedPolygon* CExtendedPolygonBuilder::builderPolygon(int edgeNum, int minRadius, int maxRadius)
{
	return this->randAnyPolygonWithinBox(m_pContainer,edgeNum,minRadius,maxRadius);
}

CExentedPolygon* CExtendedPolygonBuilder::builderPolygon(int edgeNum)
{
	return this->randAnyPolygonWithinBox(m_pContainer,edgeNum);
}




CExentedPolygon* CExtendedPolygonBuilder::randAnyPolygonWithinBox(CRectangleContainer* box,int edgeNum)
{
	srand((unsigned)time(NULL));
	POINT center = {box->m_x + box->m_width/2,box->m_y+box->m_height/2};
	double  minLength = box->m_width;
	if(minLength > box->m_height)
	{
		minLength = box->m_height;
	}

	double radius = minLength/2;

	double minTriangleArea = 0.3*radius*radius*PI;

	vector<POINT> generatedPoints;
	int totalCount = 0;
	//CExentedPolygon* polygon = new CExentedPolygon()
	for(int i = 0;i < edgeNum; ++i)
	{
		int pCount = 10000;
		do 
		{
			double param_t =  (double)rand() / RAND_MAX; 
			param_t = param_t*2*PI;
			POINT p = {radius*cos(param_t)+center.x,radius*sin(param_t)+center.y};
		 
			if(!Contain(generatedPoints,p))
			{
				generatedPoints.push_back(p);
				break;
			}

			//if(pCount-- < 0)
			//{
			//	break;
			//}

		} while (true);
		
		if((int)generatedPoints.size() == 3)
		{
			double area = Cad_Helper::getArea(generatedPoints);
			if(area < minTriangleArea)
			{
				i = 0;
				generatedPoints.clear();
				totalCount++;
				/*if(totalCount > 1000)
				{

					return NULL;
				}*/
			}
		}

	}
	// 如果有三个点
	if((int)generatedPoints.size() > 2)
	{
		vector<POINT> clockWisePOINTArray = Cad_Helper::getClockWiseArray(center,generatedPoints);

		CExentedPolygon* pResultPolygon = new CExentedPolygon(clockWisePOINTArray);
		pResultPolygon->setCircleCenter(center);  
		return pResultPolygon;
	}


	return NULL;
}

CExentedPolygon* CExtendedPolygonBuilder::randAnyPolygonWithinBox(CRectangleContainer* box,int edgeNum, int minRadius, int maxRadius)
{
	srand((unsigned)time(NULL));
	POINT center;
	center.x = box->m_x + rand()%((int)(box->m_width-0.5));
	center.y = box->m_y + rand()%((int)(box->m_height-0.5));
	 
	int radius = minRadius + rand()%(maxRadius-minRadius+1);

	double minTriangleArea = 0.05*radius*radius*PI;
	int totalCount = 0;
	vector<POINT> generatedPoints;
	for(int i = 0;i < edgeNum; ++i)
	{
		int pCount = 10000;
		do 
		{
			double param_t =  (double)rand() / RAND_MAX;  
			param_t = param_t*2*PI; // 0-360角度
			POINT p = {(long)radius*cos(param_t)+center.x,(long)radius*sin(param_t)+center.y};
		
			if(!Contain(generatedPoints,p))
			{
				generatedPoints.push_back(p);
				break;
			}
		   /*if(pCount-- < 0)
			{
				break;
			}*/


		} while (true);

		if((int)generatedPoints.size() == 3)
		{
			double area = Cad_Helper::getArea(generatedPoints);
			if(area < minTriangleArea)
			{
				i = 0;
				generatedPoints.clear();
				totalCount++;
				/*if(totalCount > 1000)
				{

					return NULL;
				}*/
			}
		}

	}

	// 如果有三个点
	if((int)generatedPoints.size()>2)
	{
		vector<POINT> clockWisePOINTArray = Cad_Helper::getClockWiseArray(center,generatedPoints);

		CExentedPolygon* pResultPolygon = new CExentedPolygon(clockWisePOINTArray);
		pResultPolygon->setCircleCenter(center); 
		return pResultPolygon;
	}

	return NULL;

}

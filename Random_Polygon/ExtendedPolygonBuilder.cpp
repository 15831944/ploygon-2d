#include "StdAfx.h"
#include "ExtendedPolygonBuilder.h"
#include "ExtentedPolygon.h"
#include "RectangleContainer.h"
#include "cad_helper.h"
#include <time.h>
#include <math.h>



const double PI = 3.1415927;

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
	AcGePoint3d center = AcGePoint3d(box->m_x + box->m_width/2,box->m_y+box->m_height/2,0);
	double  minLength = box->m_width;
	if(minLength > box->m_height)
	{
		minLength = box->m_height;
	}

	double radius = minLength/2;

	double minTriangleArea = 0.3*radius*radius*PI;

	AcGePoint3dArray generatedPoints;
	//CExentedPolygon* polygon = new CExentedPolygon()
	for(int i = 0;i < edgeNum; ++i)
	{
		do 
		{
			double param_t =  (double)rand() / RAND_MAX; 
			param_t = param_t*2*PI;
			AcGePoint3d p(radius*cos(param_t)+center.x,radius*sin(param_t)+center.y,0);
			if(!generatedPoints.contains(p))
			{
				generatedPoints.append(p);
				break;
			}

		} while (true);
		
		if(generatedPoints.length() == 3)
		{
			double area = Cad_Helper::getArea(generatedPoints);
			if(area < minTriangleArea)
			{
				i = 0;
				generatedPoints.removeAll();
			}
		}

	}
	

	AcGePoint3dArray clockWisePointArray = Cad_Helper::getClockWiseArray(center,generatedPoints);

	CExentedPolygon* pResultPolygon = new CExentedPolygon(clockWisePointArray);
	pResultPolygon->setCircleCenter(center); 
    
	return pResultPolygon;
}

CExentedPolygon* CExtendedPolygonBuilder::randAnyPolygonWithinBox(CRectangleContainer* box,int edgeNum, int minRadius, int maxRadius)
{
	srand((unsigned)time(NULL));
	AcGePoint3d center;
	center.x = box->m_x + rand()%((int)(box->m_width-0.5));
	center.y = box->m_y + rand()%((int)(box->m_height-0.5));
	 
	int radius = minRadius + rand()%(maxRadius-minRadius+1);

	double minTriangleArea = 0.05*radius*radius*PI;

	AcGePoint3dArray generatedPoints;
	for(int i = 0;i < edgeNum; ++i)
	{
		do 
		{
			double param_t =  (double)rand() / RAND_MAX; 
			param_t = param_t*2*PI;
			AcGePoint3d p(radius*cos(param_t)+center.x,radius*sin(param_t)+center.y,0);
			if(!generatedPoints.contains(p))
			{
				generatedPoints.append(p);
				break;
			}

		} while (true);

		if(generatedPoints.length() == 3)
		{
			double area = Cad_Helper::getArea(generatedPoints);
			if(area < minTriangleArea)
			{
				i = 0;
				generatedPoints.removeAll();
			}
		}

	}

	AcGePoint3dArray clockWisePointArray = Cad_Helper::getClockWiseArray(center,generatedPoints);

	CExentedPolygon* pResultPolygon = new CExentedPolygon(clockWisePointArray);
	pResultPolygon->setCircleCenter(center); 

	return pResultPolygon;
}

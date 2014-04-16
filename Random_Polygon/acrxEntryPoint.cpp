// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
 
#include "ExtentedPolygon.h"
#include "cad_helper.h"
#include "vectorcomparator.h"
#include "RectangleContainer.h"
#include "RandomPolygonGen.h"
#include <vector>
#include <algorithm>
using namespace std;

//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CRandom_PolygonApp : public AcRxArxApp {

public:
	CRandom_PolygonApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}


	// - Random_Polygon.add command (do not rename)
	static void Random_Polygonadd(void)
	{
		// Add your code for command Random_Polygon.add here
		//ExtentedPolygon* rectangle = new ExtentedPolygon(4);
		//rectangle->setClosed(Adesk::kTrue);
	 //
		//rectangle->addVertexAt(0,AcGePoint2d(0,0));
		//rectangle->addVertexAt(2,AcGePoint2d(0,10));
		//rectangle->addVertexAt(1,AcGePoint2d(10,0));
		//rectangle->addVertexAt(2,AcGePoint2d(10,10));
		//
		//rectangle->setColorIndex(1);
		//rectangle->setThickness(2);
		//double area=1.0;
		////rectangle->getArea(area);
		//acutPrintf(_T("area = %f\n\r",area));

		//Cad_Helper::PostToModelSpace(rectangle);
		//rectangle->close(); 

		 
	}

	// - Random_Polygon.test command (do not rename)
	static void Random_Polygontest(void)
	{
		// Add your code for command Random_Polygon.test here
		//AcGePoint3dArray points;
		//points.append(AcGePoint3d(0,0,0));
		//points.append(AcGePoint3d(0,10,0));
		//points.append(AcGePoint3d(10,10,0));
		//points.append(AcGePoint3d(10,0,0));
		///*AcDb2dPolyline* rectangle = new AcDb2dPolyline(AcDb::k2dSimplePoly,points,0,Adesk::kTrue,2,2);  
		//
		//rectangle->setColorIndex(1);
		//rectangle->setThickness(2);
		//double area=1.0;
		//rectangle->getArea(area);
		//acutPrintf(_T("area = %f\n\r",area));
		//Cad_Helper::PostToModelSpace(rectangle);
		//rectangle->close(); */

		//CExentedPolygon* rectangle = new CExentedPolygon(points);
		//double area=0.0;
		//rectangle->getArea(area); 
		//acutPrintf(_T("area1 = %f\n\r"),area); 
		//AcDbEntity *pEntiy = rectangle->getEnty();
		//if(pEntiy!=NULL)
		//Cad_Helper::PostToModelSpace(pEntiy);
		//

		int maxEdge = 5;
		int minRadius = 20;
		int maxRadius = 50;
		double minCoverageRadio = 0.45;
		int width = 500;
		int height = 500;
		int loopCount = 250000; 
		int stepX = -1;
		int stepY = 1;
		int expandStep = 1;
		 

		long start = 0, finish = 0;
		double  duration = 0;
		start = clock();
		CRectangleContainer* container = new CRectangleContainer(0,0,width,height);
		Cad_Helper::PostToModelSpace(container->getEntity());

		while(true)
		{
			 bool result = false;
			 CExentedPolygon* polygon = CRandonPolygonGen::randWithinBox(container,maxEdge,minRadius,maxRadius);
			 result = container->canSafePut(polygon);
			 if(result)
			 {
				container->put(polygon);
			 }
			 else// 失败投放后，进行20次更正投放
			 {
				 
				for(int i = 0; i < 20; ++i)
				{
					srand((unsigned)time(NULL));
					int deltX = stepX + (rand()%3);
					int deltY = stepY;
					polygon->treanslate(deltX,deltY);
					result = container->canSafePut(polygon);
					if(result)
					{
						container->put(polygon);
						break;
					} 
				}
			 }  


			 // 填充
			 {

				 srand((unsigned)time(NULL));
				 for (int i = 0; i < loopCount; ++i)
				 {
					int x = rand()/(container->m_width-1)+1;
					int y = rand()/(container->m_height-1)+1;
					int iWidth = minRadius/2;
					int iHeight = container->m_width;

					 

					CExentedPolygon* pPolygon = NULL;
					bool bOK = false;
					for(int j = 0; j < maxRadius*2; j+=expandStep)
					{
						iWidth+=j;
						iHeight+=j;

						CExentedPolygon* temPoly = CRandonPolygonGen::randWithinBox(new CRectangleContainer(x,y,iWidth,iHeight),5);
						bOK = container->canSafePut(temPoly);
						if(bOK)
						{
							pPolygon = temPoly; 
						}
						else
						{
							break;
						}
					}

					if(pPolygon!=NULL)
					{
						container->put(pPolygon);
					}

					if(container->getCoverageRatio() > minCoverageRadio)
					{
						break;
					}


				 }

			 }

			 if(container->getCoverageRatio() > minCoverageRadio)
			 {
				 break;
			 }
			 
		}

		finish = clock();
		duration = (finish - start)/1000;
		acutPrintf( _T("Total cost: %f seconds\n"), duration );




		
	}
} ;

//---------------------------------------------rr--------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CRandom_PolygonApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CRandom_PolygonApp, Random_Polygon, add, add, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CRandom_PolygonApp, Random_Polygon, test, test, ACRX_CMD_TRANSPARENT, NULL)

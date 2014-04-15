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
		AcGePoint3dArray points;
		points.append(AcGePoint3d(0,0,0));
		points.append(AcGePoint3d(0,10,0));
		points.append(AcGePoint3d(10,10,0));
		points.append(AcGePoint3d(10,0,0));
		/*AcDb2dPolyline* rectangle = new AcDb2dPolyline(AcDb::k2dSimplePoly,points,0,Adesk::kTrue,2,2);  
		
		rectangle->setColorIndex(1);
		rectangle->setThickness(2);
		double area=1.0;
		rectangle->getArea(area);
		acutPrintf(_T("area = %f\n\r",area));
		Cad_Helper::PostToModelSpace(rectangle);
		rectangle->close(); */

		CExentedPolygon* rectangle = new CExentedPolygon(points);
		double area=0.0;
		rectangle->getArea(area); 
		acutPrintf(_T("area1 = %f\n\r"),area); 
		AcDbEntity *pEntiy = rectangle->getEnty();
		if(pEntiy!=NULL)
		Cad_Helper::PostToModelSpace(pEntiy);
		
	 
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CRandom_PolygonApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CRandom_PolygonApp, Random_Polygon, add, add, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CRandom_PolygonApp, Random_Polygon, test, test, ACRX_CMD_TRANSPARENT, NULL)

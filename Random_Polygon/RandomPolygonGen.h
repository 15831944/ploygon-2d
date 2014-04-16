#ifndef RANDONPOLGONGENH
#define RANDONPOLGONGENH
#include "ExtendedPolygonBuilder.h"
#include "RectangleContainer.h"
#include "ExtentedPolygon.h"
#include <time.h>
class CRandonPolygonGen
{
public:
	static CExentedPolygon* randWithinBox(CRectangleContainer* pBox, int maxEdgeNum)
	{
		srand((unsigned)time(NULL));

		int edgeNum = 3 + rand()%(maxEdgeNum-2);
		CExtendedPolygonBuilder* pBuilder = new CExtendedPolygonBuilder(pBox);
		return pBuilder->builderPolygon(edgeNum); 
	}
	static CExentedPolygon* randWithinBox(CRectangleContainer* pBox, int maxEdgeNum,int minRadius,int maxRadius)
	{
		srand((unsigned)time(NULL));

		int edgeNum = 3 + rand()%(maxEdgeNum-2);
		CExtendedPolygonBuilder* pBuilder = new CExtendedPolygonBuilder(pBox);
		return pBuilder->builderPolygon(edgeNum,minRadius,maxRadius); 
	}

};


#endif
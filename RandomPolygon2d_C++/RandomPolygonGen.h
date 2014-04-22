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
		 
		CExentedPolygon* pResult = pBuilder->builderPolygon(edgeNum); 
		delete pBuilder;
		pBuilder = NULL;
		return pResult;
	}
	static CExentedPolygon* randWithinBox(CRectangleContainer* pBox, int maxEdgeNum,int minRadius,int maxRadius)
	{
		srand((unsigned)time(NULL));

		int edgeNum = 3 + rand()%(maxEdgeNum-2);
		CExtendedPolygonBuilder* pBuilder = new CExtendedPolygonBuilder(pBox);
		CExentedPolygon* pResult = pBuilder->builderPolygon(edgeNum,minRadius,maxRadius);
		delete pBuilder;
	    pBuilder = NULL;
		return pResult;
	}


	static bool Fill(CRectangleContainer* container,int loopCount,int minRadius,int maxRadius,int expandStep,int maxEdge,double minCoverageRadio)	 
	// Моід
	{

		try
		{
			srand((unsigned)time(NULL));
			for (int i = 0; i < loopCount; ++i)
			{
				int x = rand()%((int)container->m_width-1)+1;
				int y = rand()%((int)container->m_height-1)+1;
				int iWidth = minRadius*2;
				int iHeight = minRadius + rand()%minRadius; 

				CExentedPolygon* pPolygon = NULL;
				bool bOK = false;
				for(int j = 0; j < maxRadius*2; j+=expandStep)
				{
					iWidth+=j;
					iHeight+=j;
					CRectangleContainer* pBox = new CRectangleContainer(x,y,iWidth,iHeight);

					CExentedPolygon* temPoly = CRandonPolygonGen::randWithinBox(pBox,maxEdge,minRadius,maxRadius);
					if(temPoly == NULL)
					{
						continue;
					}
					bOK = container->canSafePut(temPoly);
					if(bOK)
					{
						delete pPolygon;
						pPolygon = NULL;
						pPolygon = temPoly; 
					}
					else
					{
						 
						break;
					}

					delete pBox;
					pBox = NULL;
				}

				if(pPolygon!=NULL)
				{
					printf("_3_");
					container->put(pPolygon);
				}

				if(container->getCoverageRatio() > minCoverageRadio)
				{
					return true;
				} 
			}// end for
		}
		catch(...)
		{
			printf("Fill accure errors!\n\r");
		}

		return false;

		 
	}

};


#endif
#ifndef CAD_HELPER_H
#define CAD_HELPER_H
#include "Windows.h" 
#include <vector>
#include <algorithm>
using namespace std;

#include "vectorcomparator.h"

class Cad_Helper
{
// avoid to create instance 
protected:
	Cad_Helper();
	~Cad_Helper();
public:
	//// 添加实体到当前的表记录中
	//static AcDbObjectId PostToModelSpace(AcDbEntity* pEntiy)
	//{
	//	AcDbBlockTable *pBlk;
	//	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlk,AcDb::kForRead);
	//	AcDbBlockTableRecord *pBLKrcd;
	//	pBlk->getAt(ACDB_MODEL_SPACE,pBLKrcd,AcDb::kForWrite);
	//	pBlk->close();
	//	AcDbObjectId id;
	//	pBLKrcd->appendAcDbEntity(id,pEntiy);
	//	pEntiy->close();
	//	pBLKrcd->close(); 
	//	return id;
	//}

	static double getArea(POINT pt0,POINT pt1,POINT pt2)
	{
		return (pt1.x-pt0.x)*(pt2.y-pt0.y) - (pt1.y-pt0.y) *(pt2.x-pt0.x);
	}

	static double getArea(vector<POINT> points)
	{
		double area = 0.0;
		for(int i = 0; i < (int)points.size() -1; ++i)
		{
			area = area+ Cad_Helper::getArea(points.at(0),points.at(i),points.at(i+1)); 
		} 

		area = abs(area)/2;  
		return area;
	}

	static vector<POINT> getClockWiseArray(POINT center,vector<POINT> points)
	{  

		vector<POINT>  resultArray;
		vector<POINT>  tmpPoints;

		for(int i = 0; i < (int)points.size(); ++i)
		{
			tmpPoints.push_back(points.at(i));
		} 

		std::sort(tmpPoints.begin(),tmpPoints.end(),CollectionComparator(center));



		for(int i = 0; i < (int)tmpPoints.size(); ++i)
		{
			POINT p = tmpPoints[i];
			//acutPrintf(_T("(%.2f,%.2f,%.3f)\n\r"),p.x,p.y,p.z);
			resultArray.push_back(p);

		}

		return resultArray;


	}

};

#endif
#ifndef CAD_HELPER_H
#define CAD_HELPER_H

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
	// 添加实体到当前的表记录中
	static AcDbObjectId PostToModelSpace(AcDbEntity* pEntiy)
	{
		AcDbBlockTable *pBlk;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlk,AcDb::kForRead);
		AcDbBlockTableRecord *pBLKrcd;
		pBlk->getAt(ACDB_MODEL_SPACE,pBLKrcd,AcDb::kForWrite);
		pBlk->close();
		AcDbObjectId id;
		pBLKrcd->appendAcDbEntity(id,pEntiy);
		pEntiy->close();
		pBLKrcd->close(); 
		return id;
	}

	static double getArea(AcGePoint3d pt0,AcGePoint3d pt1,AcGePoint3d pt2)
	{
		return (pt1.x-pt0.x)*(pt2.y-pt0.y) - (pt1.y-pt0.y) *(pt2.x-pt0.x);
	}

	static double getArea(AcGePoint3dArray points)
	{
		double area = 0.0;
		for(int i = 0; i < points.length() -1; ++i)
		{
			area = area+ Cad_Helper::getArea(points.at(0),points.at(i),points.at(i+1)); 
		} 

		area = abs(area)/2;
		acutPrintf(_T("area = %f\n\r"),area);
		return area;
	}

	static AcGePoint3dArray getClockWiseArray(AcGePoint3d center,AcGePoint3dArray points)
	{  

		AcGePoint3dArray resultArray;
		vector<AcGePoint3d> tmpPoints;

		for(int i = 0; i < points.length(); ++i)
		{
			tmpPoints.push_back(points.at(i));
		} 

		std::sort(tmpPoints.begin(),tmpPoints.end(),CollectionComparator(center));



		for(int i = 0; i < tmpPoints.size(); ++i)
		{
			AcGePoint3d p = tmpPoints[i];
			//acutPrintf(_T("(%.2f,%.2f,%.3f)\n\r"),p.x,p.y,p.z);
			resultArray.append(p);

		}

		return resultArray;


	}

};

#endif
#pragma once
class CExentedPolygon;
class CRectangleContainer;


class CExtendedPolygonBuilder
{
public:
	CExtendedPolygonBuilder(CRectangleContainer* container);
	~CExtendedPolygonBuilder(void);

public:
	CExentedPolygon* builderPolygon(int edgeNum, int minRadius, int maxRadius);
	CExentedPolygon* builderPolygon(CRectangleContainer* box,int edgeNum);

private:
	CExentedPolygon* randAnyPolygonWithinBox(CRectangleContainer* box,int edgeNum);
	CExentedPolygon* randAnyPolygonWithinBox(CRectangleContainer* box,int edgeNum, int minRadius, int maxRadius);

private:
	CRectangleContainer* m_pContainer;
};

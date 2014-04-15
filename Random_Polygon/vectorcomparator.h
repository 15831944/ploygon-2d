#ifndef VECTOR_COMPARATOR_H
#define VECTOR_COMPARATOR_H

class CollectionComparator
{
public:
	CollectionComparator(const AcGePoint3d & center)
	:m_center(center)
	{

	}

	bool operator()(const AcGePoint3d & p1, const AcGePoint3d & p2)
	{
		return true;
	}


private:
	AcGePoint3d & m_center;
};



#endif
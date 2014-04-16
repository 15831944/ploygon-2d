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

		AcGePoint3d vector1,vector2;

		AcGePoint3d axis,axisVertex;


		axis.x = -m_center.x;
		axis.y = 0;
		axis.z =0;

		axisVertex.x = 0;
		axisVertex.y = m_center.y;
		axisVertex.z = 0;

		vector1.x =p1.x -m_center.x;
		vector1.y =p1.y - m_center.y;
		vector1.z =0;

		vector2.x = p2.x-m_center.x;
		vector2.y = p2.y - m_center.y;;
		vector2.z =0;

		double cos1 = getAngleCos(axis,vector1);
		double cos2 = getAngleCos(axis,vector2);

		bool on_right_av1    = onTheRightSide(axis,vector1);
		bool on_right_av2    = onTheRightSide(axis,vector2);
		bool on_left_av1      = onTheLeftSide(axis,vector1);
		bool on_left_av2      = onTheLeftSide(axis,vector2);
		bool on_same_av1   = onTheSameLine(axis,vector1);
		bool on_same_av2   = onTheSameLine(axis,vector2);

		bool on_right_v1v2    = onTheRightSide(vector1,vector2);
		bool on_same_v1v2    = onTheSameLine(vector1,vector2);

		double dotpro_av1 = doProduct(axis,vector1);
		double dotpro_av2 = doProduct(axis,vector2);

		double magpro_av1 = getMagnitude(axis)*getMagnitude(vector1);
		double magpro_av2 = getMagnitude(axis)*getMagnitude(vector2);

		if(on_right_av1 && on_right_av2)
		{
			if(on_right_v1v2)
			{
				return -1;
			} 
			else
			{
				return 1;
			}
		} 
		else if(on_left_av1 && on_left_av2)
		{
			if(on_right_v1v2)
			{
				return -1;
			} 
			else 
			{
				return 1;
			}
		} 
		else if(on_right_av1 && on_left_av2)
		{
			return -1;
		} 
		else if(on_left_av1 && on_right_av2)
		{
			return 1;
		} 
		else if(on_same_v1v2)
		{
			// on_same_av1 && on_same_av2
			if(dotpro_av1 == magpro_av1)
			{
				return -1;
			} 
			else
			{
				return 1;
			}
		} 
		else if(on_same_av1 && on_left_av2)
		{
			return -1;
		}
		else if(on_same_av1 && on_right_av2)
		{
			if(dotpro_av1 == magpro_av1)
			{
				return -1;
			} else 
			{
				return 1;
			}
		} 
		else if(on_same_av2 && on_left_av1) 
		{
			return 1;
		}
		else
		{
			//                } else if(on_same_av2 && on_right_av1) {
			if(dotpro_av2 == magpro_av2)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		} 
		return true;
	}

private:
	// 获得该平面向量的值
	double getMagnitude(AcGePoint3d point)
	{
		return sqrt(pow(point.x,2)+pow(point.y,2));
	}

	double doProduct(AcGePoint3d p1, AcGePoint3d p2)
	{
		return p1.x*p2.x + p1.y*p2.y;
	}

	//获得叉积
	double getAngleCos(AcGePoint3d p1, AcGePoint3d p2)
	{
		return doProduct(p1,p2)/(getMagnitude(p1)*getMagnitude(p2));
	}

	// the clock wise circle	
	bool onTheRightSide(AcGePoint3d p1, AcGePoint3d p2)
	{
		return p2.y*p1.x - p2.x*p1.y < 0;
	}

	bool onTheLeftSide(AcGePoint3d p1, AcGePoint3d p2)
	{
		return p2.y*p1.x - p2.x*p1.y > 0;
	}

	bool onTheSameLine(AcGePoint3d p1, AcGePoint3d p2)
	{
		return p2.y*p1.x - p2.x*p1.y == 0;
	}


private:
	AcGePoint3d & m_center;
};



#endif
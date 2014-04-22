#ifndef VECTOR_COMPARATOR_H
#define VECTOR_COMPARATOR_H
#include <math.h>

class CollectionComparator
{
public:
	CollectionComparator(const POINT  center)
	:m_center(center)
	{
	}

	bool operator()(const POINT & p1, const POINT & p2)
	{

		POINT vector1,vector2;

		POINT axis,axisVertex;


		axis.x = -m_center.x;
		axis.y = 0;
	 

		axisVertex.x = 0;
		axisVertex.y = m_center.y;
	 

		vector1.x =p1.x -m_center.x;
		vector1.y =p1.y - m_center.y;
		 

		vector2.x = p2.x- m_center.x;
		vector2.y = p2.y - m_center.y;;
	 
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
				return false;
			} 
			else
			{
				return true;
			}
		} 
		else if(on_left_av1 && on_left_av2)
		{
			if(on_right_v1v2)
			{
				return false;
			} 
			else 
			{
				return true;
			}
		} 
		else if(on_right_av1 && on_left_av2)
		{
			return false;
		} 
		else if(on_left_av1 && on_right_av2)
		{
			return true;
		} 
		else if(on_same_v1v2)
		{
			// on_same_av1 && on_same_av2
			if(dotpro_av1 == magpro_av1)
			{
				return false;
			} 
			else
			{
				return true;
			}
		} 
		else if(on_same_av1 && on_left_av2)
		{
			return false;
		}
		else if(on_same_av1 && on_right_av2)
		{
			if(dotpro_av1 == magpro_av1)
			{
				return false;
			} else 
			{
				return true;
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
				return true;
			}
			else
			{
				return false;
			}
		} 
		return true;
	}

private:
	// 获得该平面向量的值
	double getMagnitude(POINT point)
	{
		return sqrt(pow(point.x,2.0)+pow(point.y,2.0));
	}

	double doProduct(POINT p1, POINT p2)
	{
		return p1.x*p2.x + p1.y*p2.y;
	}

	//获得叉积
	double getAngleCos(POINT p1, POINT p2)
	{
		return doProduct(p1,p2)/(getMagnitude(p1)*getMagnitude(p2));
	}

	// the clock wise circle	
	bool onTheRightSide(POINT p1, POINT p2)
	{
		return p2.y*p1.x - p2.x*p1.y < 0;
	}

	bool onTheLeftSide(POINT p1, POINT p2)
	{
		return p2.y*p1.x - p2.x*p1.y > 0;
	}

	bool onTheSameLine(POINT p1, POINT p2)
	{
		return p2.y*p1.x - p2.x*p1.y == 0;
	}


private:
	POINT m_center;
};



#endif
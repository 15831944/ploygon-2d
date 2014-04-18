using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConfigProject
{

    public class Point
    {
        public double X;
        public double Y;
     }

    public  class Polygon
    {
        public int Edges;
        public List<Point> Points = new List<Point>();
    }

    public class TPolygons
    {
        public List<Polygon> Polygons = new List<Polygon>();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//http://www.bimcad.org 数字建筑
//深入浅出AutoCAD二次开发(李冠亿)
/////////////////////////////////////////////////////////////////////////////////////////////////

using System;

using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.Runtime;
using System.Collections.Generic;
 
using System.Xml.Serialization;
using System.IO;
using System.Reflection;
using System.Xml;
using ConfigProject;
using Autodesk.AutoCAD;

[assembly: CommandClass(typeof(Sample.CreateGraphic))]
namespace Sample
{
    class CreateGraphic
    {
        /// <summary>
        /// 将块表记录加入到块表中
        /// </summary>
        /// <returns>块表记录ObjectId</returns>
        public  ObjectId AddBlockTableRecord(BlockTableRecord btr, Database db)
        {
            ObjectId id = new ObjectId();
            using (Transaction transaction = db.TransactionManager.StartTransaction())
            {
                BlockTable bt = transaction.GetObject(db.BlockTableId, OpenMode.ForWrite) as BlockTable;
                id = bt.Add(btr);
                transaction.AddNewlyCreatedDBObject(btr, true);
                transaction.Commit();
            }
            return id;
        }


        public Polyline getPolyline(List<Point2d> pointList)
        {
            Polyline poly = new Polyline();

            foreach (Point2d pt in pointList)
            {
                poly.AddVertexAt(0, pt, 0, 0, 0);
            }

            poly.Closed = true;
            return poly;
        }

        public TPolygons getConfig()
        {
            XmlSerializer ser = new XmlSerializer(typeof(TPolygons));
            TPolygons config = new TPolygons();
            using (XmlTextReader reader = new XmlTextReader(@"D:\config.xml"))
            //using (TextReader tr = new StringReader())
            {
                config = (TPolygons)ser.Deserialize(reader);
            }
            return config;
        }

        [CommandMethod("Create")]
        public void CreateBlock()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            BlockTableRecord btr = new BlockTableRecord();
            btr.Name = "Random";// +DateTime.Now.ToString();

            TPolygons config = getConfig();
            foreach (Polygon node in config.Polygons)
            {
                List<Point2d> pts = new List<Point2d>();
                foreach (Point pt in node.Points)
                {
                    pts.Add(new Point2d(pt.X, pt.Y));
                }
                Polyline poly = getPolyline(pts);
                btr.AppendEntity(poly);
               
            }
            AddBlockTableRecord(btr, db);
        }

        [CommandMethod("CreateBox")]
        public void Create3DBox()
        {  
             Solid3d bbb = new Solid3d();
             bbb.CreatePyramid(50, 3, 50,0);
             bbb.Color = Autodesk.AutoCAD.Colors.Color.FromRgb(0, 250, 0);
             ToModelSpace(bbb);

             Solid3d bbbb = new Solid3d();
             bbbb.CreateSphere(50);
            // Move(bbbb, new Point3d(-50, -50, -50));
             ToModelSpace(bbbb);
        }



        /// <summary>
        /// 添加实体到模型空间
        /// </summary>
        /// <param name="ent">要添加的实体</param>
        /// <returns>实体ObjectId</returns>
        public static ObjectId ToModelSpace(Entity ent)
        {
            Database db = HostApplicationServices.WorkingDatabase;
            ObjectId entId;
            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                BlockTable bt = (BlockTable)trans.GetObject(db.BlockTableId, OpenMode.ForRead);
                BlockTableRecord modelSpace = (BlockTableRecord)trans.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite);
                entId = modelSpace.AppendEntity(ent);
                trans.AddNewlyCreatedDBObject(ent, true);
                trans.Commit();
            }
            return entId;
        }

        /// <summary>
        /// 以原点为基点，指定目标点移动实体
        /// </summary>
        /// <param name="ent">实体对象</param>
        /// <param name="pt">目标点</param>
        public static void Move(Entity ent, Point3d pt)
        {
            Matrix3d mt = Matrix3d.Displacement(pt - new Point3d());
            ent.TransformBy(mt);
        }
    
    
    }
}

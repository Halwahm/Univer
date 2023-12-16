use [mshoad]

SELECT SCHEMA_NAME
FROM INFORMATION_SCHEMA.SCHEMATA

-- 6 TASK datatype
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'dbo'


-- 7 TASK SRID
SELECT COLUMN_NAME
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_NAME = 'gmtg20-master' AND DATA_TYPE = 'geometry'

select distinct geom.STSrid as SRID from [gmtg20-master] 


-- 8 TASK аттрибутивные столбцы
SELECT COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'dbo' AND DATA_TYPE <> 'geometry'

-- 9 TASK WRT
SELECT geom.STAsText() AS WKT_Description
FROM [gmtg20-master]

-- 10 TASKS
select * from [gmtg20-master]

-- 10.1 Intersaction

SELECT obj1.geom.STIntersection(obj2.geom) AS Intersection
FROM [gmtg20-master] obj1, [gmtg20-master] obj2
WHERE obj1.qgs_fid = 1 AND obj2.qgs_fid = 2

-- 10.2 Union

SELECT obj1.geom.STUnion(obj2.geom) AS [Union]
FROM [gmtg20-master] obj1, [gmtg20-master] obj2
WHERE obj1.qgs_fid = 3 AND obj2.qgs_fid = 2

-- 10.3 WithIn

SELECT obj1.geom.STWithin(obj2.geom) AS [IsWithin]
FROM [gmtg20-master] obj1, [gmtg20-master] obj2
WHERE obj1.qgs_fid = 4 AND obj2.qgs_fid = 5

-- 10.4 Simplified (не поддерживается, использовал Reduce)

SELECT geom.Reduce(50) AS Simplified --насколько сильно должен быть упрощен геометрический объект
FROM [gmtg20-master]
WHERE qgs_fid = 2

-- 10.5 VertexCoordinates

SELECT geom.STPointN(1).ToString() AS VertexCoordinates
FROM [gmtg20-master]
WHERE qgs_fid = 6

-- 10.6 ObjectDimension

SELECT geom.STDimension() AS ObjectDimension
FROM [gmtg20-master]
WHERE qgs_fid = 3

-- 10.7 ObjectLength, ObjectArea

SELECT geom.STLength() AS ObjectLength, geom.STArea() AS ObjectArea
FROM [gmtg20-master]
WHERE qgs_fid = 5


-- 10.8 Distance

SELECT obj1.geom.STDistance(obj2.geom) AS Distance
FROM [gmtg20-master] obj1, [gmtg20-master] obj2
WHERE obj1.qgs_fid = 6 AND obj2.qgs_fid = 4


-- 11 point, line, polygon

DECLARE @pointGeometry GEOMETRY;
SET @pointGeometry = GEOMETRY::STGeomFromText('POINT(30 10)', 0);

SELECT @pointGeometry AS PointGeometry;


DECLARE @lineGeometry GEOMETRY;
SET @lineGeometry = GEOMETRY::STGeomFromText('LINESTRING(30 10, 10 30, 40 40)', 0);

SELECT @lineGeometry AS LineGeometry;



DECLARE @polygonGeometry GEOMETRY;
SET @polygonGeometry = GEOMETRY::STGeomFromText('POLYGON((35 10, 45 45, 15 40, 10 20, 35 10))', 0);

SELECT @polygonGeometry AS PolygonGeometry;


-- 12 

-- точка и полигон
DECLARE @point GEOMETRY = GEOMETRY::STGeomFromText('POINT(30 30)', 0);
DECLARE @polygon GEOMETRY = GEOMETRY::STGeomFromText('POLYGON((20 20, 20 40, 40 40, 40 20, 20 20))', 0);

SELECT @point.STWithin(@polygon) AS PointWithinPolygon;

-- прямая и полигон
DECLARE @line GEOMETRY = GEOMETRY::STGeomFromText('LINESTRING(30 10, 10 30, 40 40)', 0);
DECLARE @polygonn GEOMETRY = GEOMETRY::STGeomFromText('POLYGON((20 20, 20 40, 40 40, 40 20, 20 20))', 0);
SELECT @polygonn.STLength() AS Length, @polygonn.STArea() AS Area;

SELECT @line.STIntersects(@polygonn) AS LineIntersectsPolygon;
void setup()
{
  testCase1();  
  testCase2();  
  testCase3();  
}// void setup()

void testCase1()
{
  Sphere sph = new Sphere(new PVector(0,0,5), 1);
  Ray ray = new Ray();
  ray.start.set(0,0,-5);
  ray.direction = PVector.sub(new PVector(-1,1,0), ray.start);
  IntersectionPoint res = sph.testIntersection(ray);
  if ( res == null )
    println("testCase1 is succeeded!");
  else
    println("testCase1 is failed...");
}

void testCase2()
{
  Sphere sph = new Sphere(new PVector(0,0,5), 1);
  Ray ray = new Ray();
  ray.start.set(0,0,-5);
  ray.direction = PVector.sub(new PVector(0,0,0), ray.start);
  IntersectionPoint expect = new IntersectionPoint();
  expect.distance = 9.0f;
  expect.position = new PVector(0,0,4);
  expect.normal = new PVector(0,0,-1);
  IntersectionPoint res = sph.testIntersection(ray);
  if ( res != null && equals(res, expect) )
    println("testCase2 is succeeded!");
  else
    println("testCase2 is failed...");
}

void testCase3()
{
  Sphere sph = new Sphere(new PVector(0,0,5), 1);
  Ray ray = new Ray();
  ray.start.set(0,0,-5);
  ray.direction = PVector.sub(new PVector(sqrt(25.0/99.0),0,0), ray.start);
  IntersectionPoint expect = new IntersectionPoint();
  expect.distance = (9900.0/5000.0) * ray.direction.mag();
  expect.position = ray.getPoint(9900.0/5000.0);
  expect.normal = PVector.sub(expect.position, sph.center);
  IntersectionPoint res = sph.testIntersection(ray);
  if ( res != null && equals(res, expect) )
    println("testCase3 is succeeded!");
  else
    println("testCase3 is failed...");
}

boolean nearlyEquals(float f1, float f2)
{
  return abs(f1 - f2) < EPSILON;
}
boolean equals(PVector v1, PVector v2)
{
  return nearlyEquals(v1.x, v2.x) 
      && nearlyEquals(v1.y, v2.y)
      && nearlyEquals(v1.z, v2.z);
}
boolean equals(IntersectionPoint p1, IntersectionPoint p2)
{
  return nearlyEquals(p1.distance, p2.distance)
      && equals(p1.position, p2.position)
      && equals(p1.normal, p2.normal);
}

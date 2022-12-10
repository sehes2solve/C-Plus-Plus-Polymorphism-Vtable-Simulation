#include <iostream>
#define PI 3.142857

using namespace std;

struct Shape;

struct ShapeVtable
{
    double(*GetArea)(Shape*);
    void  (*Destroy)(Shape*);
};

struct Shape
{
    ShapeVtable* vtable;
};

double GetArea(Shape* shape){ return shape->vtable->GetArea(shape); }
void Destroy(Shape* shape){ shape->vtable->Destroy(shape); }

struct Circle
{
    Shape parent;
    double radius;
};

double CircleGetArea(Circle* circle)
{
    return PI * circle->radius * circle->radius;
}

void CircleDestroy(Circle* circle)
{
    //Deallocate Heap Memory of Class Instance
}

ShapeVtable circle_vtable =
{
    (double (*)(Shape*))CircleGetArea,
    (void   (*)(Shape*))CircleDestroy
};

void CircleInitialize(Circle* circle,double radius)
{
    circle->radius = radius;
    circle->parent.vtable = &circle_vtable;
}

struct Rectangle
{
    Shape parent;
    double height, width;
};

double RectangleGetArea(Rectangle* rectangle)
{
    return rectangle->height * rectangle->width;
}

void RectangleDestroy(Rectangle* rectangle)
{
    //Deallocate Heap Memory of Class Instance
}

ShapeVtable rectangle_vtable =
{
    (double (*)(Shape*))RectangleGetArea,
    (void   (*)(Shape*))RectangleDestroy
};

void RectangleInitialize(Rectangle* rectangle,double width,double height)
{
    rectangle->width  = width;
    rectangle->height = height;
    rectangle->parent.vtable = &rectangle_vtable;
}

struct Square
{
    Shape parent;
    double length;
};

double SquareGetArea(Square* square)
{
    return square->length * square->length;
}

void SquareDestroy(Square* square)
{
    //Deallocate Heap Memory of Class Instance
}

ShapeVtable square_vtable =
{
  (double(*)(Shape*))SquareGetArea,
  (void  (*)(Shape*))SquareDestroy
};

void SquareInitialize(Square* square,double length)
{
    square->length = length;
    square->parent.vtable = &square_vtable;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Square square;
    SquareInitialize(&square, 7); // square with side length 7

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle;
    shapes[1]=(Shape*)&rectangle;
    shapes[2]=(Shape*)&square;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
    }

    cout<<total_area<<endl; // check if the value is correct

    return 0;
}


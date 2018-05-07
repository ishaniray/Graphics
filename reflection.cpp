#include <stdio.h>
#include <graphics.h>

/* Macro to calibrate origin to the centre of the viewport */
#define fx(x) ((getmaxx() / 2) + x)
#define fy(y) ((getmaxy() / 2) - y)


/* Structure definition */
typedef struct point
{
        int x;    /* x co-ordinate of a point */
        int y;    /* y co-ordinate of a point */
} Point;

/* Function prototypes */
void reflect_triangle(Point, Point, Point);
void reflect_point(Point);

int main(void)
{
    Point A, B, C;    
    int choice, b;
    float m;
    
    printf("1. Reflect a triangle in all quadrants\n2. Reflect a point in all octants");
    printf("\n\nPick one: ");
    scanf("%d", &choice);
    
    if(choice == 1)
    {   
        initwindow(600, 600, "Reflection");
         
        /* Hardcode values (A, B, C are the three vertices of the triangle) */
        A.x = 100;
        A.y = 100;
        B.x = 100;
        B.y = 200;
        C.x = 200;
        C.y = 100;
        
        /* Draw quadrants */
        line(300, 0, 300, 600);
        line(0, 300, 600, 300);
    
        /* Draw triangle in first quadrant */
        line(fx(A.x), fy(A.y), fx(B.x), fy(B.y));
        line(fx(B.x), fy(B.y), fx(C.x), fy(C.y));
        line(fx(C.x), fy(C.y), fx(A.x), fy(A.y));
        
        reflect_triangle(A, B, C);   /* reflect triangle in all quadrants */
    }
    
    else if(choice == 2)
    {
        initwindow(600, 600, "Reflection");
        
        /* Hardcode values */
        A.x = 200;
        A.y = 100;
        
        /* Draw octants */
        line(300, 0, 300, 600);
        line(0, 300, 600, 300);
        line(600, 0, 0, 600);
        line(0, 0, 600, 600);
        
        /* Plot point in first octant */
        circle(fx(A.x), fy(A.y), 2);
        
        reflect_point(A);    /* reflect point in all octants */
    }        
          
    while(!kbhit());    /* hold the window open until a key is pressed */
    closegraph();
    return 0;
} 

void reflect_triangle(Point A, Point B, Point C)
{
     /* Second quadrant */
     line(fx(-A.x), fy(A.y), fx(-B.x), fy(B.y));
     line(fx(-B.x), fy(B.y), fx(-C.x), fy(C.y));
     line(fx(-C.x), fy(C.y), fx(-A.x), fy(A.y));
     
     /* Third quadrant */
     line(fx(-A.x), fy(-A.y), fx(-B.x), fy(-B.y));
     line(fx(-B.x), fy(-B.y), fx(-C.x), fy(-C.y));
     line(fx(-C.x), fy(-C.y), fx(-A.x), fy(-A.y));
     
     /* Fourth quadrant */
     line(fx(A.x), fy(-A.y), fx(B.x), fy(-B.y));
     line(fx(B.x), fy(-B.y), fx(C.x), fy(-C.y));
     line(fx(C.x), fy(-C.y), fx(A.x), fy(-A.y));
}

void reflect_point(Point A)
{
     /* Second octant */
     circle(fx(A.y), fy(A.x), 2);
     
     /* Third octant */
     circle(fx(-A.y), fy(A.x), 2);   
     
     /* Fourth octant */
     circle(fx(-A.x), fy(A.y), 2);   
     
     /* Fifth octant */
     circle(fx(-A.x), fy(-A.y), 2);   
     
     /* Sixth octant */
     circle(fx(-A.y), fy(-A.x), 2);   
     
     /* Seventh octant */
     circle(fx(A.y), fy(-A.x), 2); 
     
     /* Eighth octant */
     circle(fx(A.x), fy(-A.y), 2);
}

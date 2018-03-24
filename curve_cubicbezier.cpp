/* This program draws a cubic Bezier curve.
   (All inputs are hardcoded.) 
   [Refer to curve_cubicbezier_cont.cpp for a much-refined, properly documented implementation of cubic Bezier curves.] */

#include <stdio.h>
#include <graphics.h>
#include <math.h>

#define fy(y) (getmaxy() - y)       /* calibrate origin to bottom-left corner of the window */

/* Structure definition */
typedef struct point
{
       int x;         /* x co-ordinate of a point */
       int y;         /* y co-ordinate of a point */
} Point;

int main(void)
{
    Point P0, P1, P2, P3, A, B;
    int i, n;
    float t, increment, J0, J1, J2, J3;
    
    n = 50;  /* no. of divisions / line segments making up the curve */
    increment = 1 / float(n);
    t = increment;
    
    P0.x = 200;
    P0.y = 250;
    
    P1.x = 300;
    P1.y = 500;
    
    P2.x = 600;
    P2.y = 575;
    
    P3.x = 900;
    P3.y = 200;
    
    initwindow(1280, 720, "Cubic Bezier Curve");
    
    setcolor(RED);
    circle(P0.x, fy(P0.y), 5);
    setcolor(WHITE);
    outtextxy(P0.x - 20, fy(P0.y + 10), "0");
    
    setcolor(RED);
    circle(P1.x, fy(P1.y), 5);
    setcolor(WHITE);
    outtextxy(P1.x - 20, fy(P1.y + 10), "1");
    
    setcolor(RED);
    circle(P2.x, fy(P2.y), 5);
    setcolor(WHITE);
    outtextxy(P2.x - 20, fy(P2.y + 10), "2");
    
    setcolor(RED);
    circle(P3.x, fy(P3.y), 5);
    setcolor(WHITE);
    outtextxy(P3.x - 20, fy(P3.y + 10), "3");
    
    setcolor(YELLOW);
    
    line(P0.x, fy(P0.y), P1.x, fy(P1.y));
    line(P1.x, fy(P1.y), P2.x, fy(P2.y));
    line(P2.x, fy(P2.y), P3.x, fy(P3.y));
    
    setcolor(GREEN);
    
    B = P0;
    
    for(i = 0; i < (n - 1); ++i)
    {
          A = B;
          
          J0 = pow((1 - t), 3);
          J1 = 3 * t * pow((1 - t), 2);
          J2 = 3 * pow(t, 2) * (1 - t);
          J3 = pow(t, 3);
          
          B.x =  (P0.x * J0) + (P1.x * J1) + (P2.x * J2) + (P3.x * J3);
          B.y =  (P0.y * J0) + (P1.y * J1) + (P2.y * J2) + (P3.y * J3);
          
          line(A.x, fy(A.y), B.x, fy(B.y));
          
          t += increment;
          
          delay(50);
    }
    
    line(B.x, fy(B.y), P3.x, fy(P3.y));
          
    while(!kbhit());                              /* hold the window open until a key is pressed */
    closegraph();
    return 0;     
}

/* This program draws a cubic Bezier curve where the user can change the order of the control points.
   (Inputs are hardcoded.) */

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

/* Function prototype */
void drawCurve(Point, Point, Point, Point);

int main(void)
{
    Point bezierPoints[4];
    int first, second, third, fourth;
    
    bezierPoints[0].x = 200;
    bezierPoints[0].y = 250;
    
    bezierPoints[1].x = 300;
    bezierPoints[1].y = 500;
    
    bezierPoints[2].x = 600;
    bezierPoints[2].y = 575;
    
    bezierPoints[3].x = 900;
    bezierPoints[3].y = 200;
    
    initwindow(1280, 720, "Cubic Bezier Curve");
    
    drawCurve(bezierPoints[0], bezierPoints[1], bezierPoints[2], bezierPoints[3]);   /* draw initial curve */
    
    printf("Change order of control points (enter control point numbers [0-3]):");
    printf("\n\n1st point: ");
    scanf("%d", &first);
    printf("\n2nd point: ");
    scanf("%d", &second);
    printf("\n3rd point: ");
    scanf("%d", &third);
    printf("\n4th point: ");
    scanf("%d", &fourth);
    
    initwindow(1280, 720, "Cubic Bezier Curve - Modified");
    
    drawCurve(bezierPoints[first], bezierPoints[second], bezierPoints[third], bezierPoints[fourth]);    /* draw modified curve */
          
    while(!kbhit());    /* hold the window open until a key is pressed */
    closegraph();
    return 0;     
}

/* Function to draw the cubic-Bezier curve */
void drawCurve(Point P0, Point P1, Point P2, Point P3)
{
    Point A, B;
    int i, n;
    float t, increment, J0, J1, J2, J3;
    
    n = 50;  /* no. of divisions / line segments making up the curve */
    increment = 1 / float(n);
    t = increment;
     
    /* Circling and numbering the control points */ 
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
    
    /* Drawing the control polygon */
    setcolor(YELLOW);
    line(P0.x, fy(P0.y), P1.x, fy(P1.y));
    line(P1.x, fy(P1.y), P2.x, fy(P2.y));
    line(P2.x, fy(P2.y), P3.x, fy(P3.y));
    
    /* Drawing the curve */
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
}

/* This program draws continuous cubic Bezier curves. 
   (All inputs are hardcoded.) */

#include <stdio.h>
#include <graphics.h>
#include <math.h>

/* Structure definition */
typedef struct point
{
       int x;         /* x co-ordinate of a point */
       int y;         /* y co-ordinate of a point */
} Point;

/* Function prototypes */
void drawControlPoly(Point*, int);
void drawContCurves(Point*, int, float, int*, bool);
void firstOrderCont(Point*, int, float, int*, bool);


int main(void)
{
    Point *bezierPoints;
    int numofcurves, numofbpoints, numofsegments, *colours;
    
    numofcurves = 3;
    numofsegments = 50;                   /* no. of divisions, i.e., no. of line segments making up each curve */
    numofbpoints = 3 * numofcurves + 1;   /* 'n' continuous cubic Bezier curves will have 3n + 1 control-polygon points */
     
     /* control-polygons */
    bezierPoints = (Point*)malloc(numofbpoints * sizeof(Point));
     
    bezierPoints[0].x = 40;
    bezierPoints[0].y = 100;
    
    bezierPoints[1].x = 100;
    bezierPoints[1].y = 360;
    
    bezierPoints[2].x = 250;
    bezierPoints[2].y = 400;

    bezierPoints[3].x = 300;
    bezierPoints[3].y = 280;
    
    bezierPoints[4].x = 200;
    bezierPoints[4].y = 170; 
    
    bezierPoints[5].x = 350;
    bezierPoints[5].y = 125;
    
    bezierPoints[6].x = 460;
    bezierPoints[6].y = 250;
    
    bezierPoints[7].x = 400;
    bezierPoints[7].y = 400;
    
    bezierPoints[8].x = 520;
    bezierPoints[8].y = 450;
    
    bezierPoints[9].x = 570;
    bezierPoints[9].y = 275;
     
    colours = (int*)malloc(numofcurves * sizeof(int));   /* array indicating the colours in which each curve is to be drawn */
    
    initwindow(900, 600, "Continuous Cubic Bezier Curves");
    
    drawControlPoly(bezierPoints, numofbpoints);   /* drawing control-polygons */
      
    colours[0] = RED;
    colours[1] = MAGENTA;
    colours[2] = YELLOW;
    
    drawContCurves(bezierPoints, numofbpoints, numofsegments, colours, false);    /* drawing zero-order continuous curves */
    
    colours[0] = LIGHTMAGENTA;
    colours[1] = YELLOW;
    colours[2] = WHITE;
    
    firstOrderCont(bezierPoints, numofbpoints, numofsegments, colours, true);    /* drawing first-order continuous curves */
    
    setcolor(WHITE);
    outtextxy(600, 50, "Thin Curves:  Zero-Order Continuity");
    outtextxy(600, 75, "Thick Curves: First-Order Continuity");
    
    while(!kbhit());    /* hold the window open until a key is pressed */
    closegraph();
    return 0;     
}


/* Function to draw control-polygons */
void drawControlPoly(Point *bezierPoints, int numofbpoints)
{
     int i;
     char pointNum[2];
     
     for(i = 0; i < numofbpoints; ++i)
     {   
          setcolor(WHITE);
          circle(bezierPoints[i].x, bezierPoints[i].y, 2);  /* circle the point */
          
          pointNum[0] = 48 + i;
          pointNum[1] = '\0';
          outtextxy(bezierPoints[i].x - 20, bezierPoints[i].y + 10, pointNum);  /* number the point */
          
          setcolor(GREEN);
          if(i > 0)
               line(bezierPoints[i - 1].x, bezierPoints[i - 1].y, bezierPoints[i].x, bezierPoints[i].y);  /* draw lines between successive points */
    }
}


/* Function implementing zero-order continuity of curves (for two successive curves, the point where one curve ends is the point where the other curve begins) */    
void drawContCurves(Point *bezierPoints, int numofbpoints, float numofsegments, int *colours, bool thick)
{
     float t, increment, J0, J1, J2, J3;
     int i, j;
     Point A, B;    
     
     increment = 1 / float(numofsegments);
     
     if(thick)
              setlinestyle(0, 0, 3);    /* curves to be drawn with thicker lines */
     
     for(i = 0; i < numofbpoints - 1; i = i + 3)
     {
          setcolor(colours[i / 3]);
               
          t = increment;    /* first point on the curve, i.e., when t = 0, is already known (bezierPoints[i]) - therefore, t is initialised to the next incremental value */
          B = bezierPoints[i];
          
          for(j = 0; j < (numofsegments - 1); ++j)
          {
                A = B;   /* A is now the point generated in the previous iteration while B is the point to be generated in the current iteration */
                          
                J0 = pow((1 - t), 3);
                J1 = 3 * t * pow((1 - t), 2);
                J2 = 3 * pow(t, 2) * (1 - t);
                J3 = pow(t, 3);
          
                B.x =  (bezierPoints[i].x * J0) + (bezierPoints[i + 1].x * J1) + (bezierPoints[i + 2].x * J2) + (bezierPoints[i + 3].x * J3);
                B.y =  (bezierPoints[i].y * J0) + (bezierPoints[i + 1].y * J1) + (bezierPoints[i + 2].y * J2) + (bezierPoints[i + 3].y * J3);
          
                line(A.x, A.y, B.x, B.y);
          
                t += increment;
          
                delay(35);
          }
          line(B.x, B.y, bezierPoints[i + 3].x, bezierPoints[i + 3].y);  /* drawing the last segment - i.e., from the last generated point, to the point where t = 1 (bezierPoints[i + 3]) */
    }
}


/* Function implementing tangential continuity of curves, ensuring smoother joining.
   (i.e., at the point of joining of two successive curves, their gradients are equal.) */
void firstOrderCont(Point *bezierPoints, int numofbpoints, float numofsegments, int *colours, bool thick)
{
     int i;
     
     for(i = 3; i < numofbpoints - 1; i = i + 3)
     {
           bezierPoints[i].x = (bezierPoints[i - 1].x + bezierPoints[i + 1].x) / 2;
           bezierPoints[i].y = (bezierPoints[i - 1].y + bezierPoints[i + 1].y) / 2;
     }
     
     drawContCurves(bezierPoints, numofbpoints, numofsegments, colours, thick);
}

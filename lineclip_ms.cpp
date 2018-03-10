/* Midpoint-Subdivision Line-Clipping Algorithm */

#include <stdio.h>
#include <graphics.h>
#include <math.h>

#define fy(y) (getmaxy() - y)       /* calibrate origin to bottom-left corner of the window */

/* Structure definition */
typedef struct point
{
       int x;         /* x co-ordinate of a point */
       int y;         /* y co-ordinate of a point */
       int outcode;   /* region code (left-right-bottom-top) of the point with respect to the clipping window */
} Point;

/* Function prototypes */
void clip(Point, Point);
void midpointClip(Point, Point);
int generateOutcode(Point);
bool accept(Point, Point);
bool reject(Point, Point);

/* Global variables */
int Xmin, Xmax, Ymin, Ymax;     /* viewport boundaries */
Point IP1, IP2;                 /* structure variables to hold the two possible intersection points */

/* main() */
int main(void)
{
    Point A, B;
    
    printf("[WINDOW SIZE: 1280 by 720 pixels]");
    printf("\n\nPlease enter the (x, y) co-ordinates of the bottom-left and top-right corners of the viewport (in that order):\n\n");
    scanf("%d%d%d%d", &Xmin, &Ymin, &Xmax, &Ymax);   /* sample values: 420, 240, 860, 480, respectively */
    
    printf("\n\nPlease enter the (x, y) co-ordinates of the two endpoints of the line (in that order):\n\n");
    scanf("%d%d%d%d", &A.x, &A.y, &B.x, &B.y);       /* sample values: 320, 340, 720, 580, respectively */
    
    initwindow(1280, 720, "Line Clipping");
    
    outtextxy(500, fy(650), "Original line with respect to viewport");
    
    rectangle(Xmin, fy(Ymax), Xmax, fy(Ymin));    /* clipping window */
    
    line(A.x, fy(A.y), B.x, fy(B.y));             /* unclipped line */
    circle(A.x, fy(A.y), 4);
    circle(B.x, fy(B.y), 4);
    
    clip(A, B);                                   /* call to clip() */
    
    while(!kbhit());                              /* hold the window open until a key is pressed */
    closegraph();
    return 0;
}

/* Function implementing Midpoint-Subdivision Line-Clipping Algorithm */
void clip(Point A, Point B)
{
    bool liesOnBoundary = false;
    
    A.outcode = generateOutcode(A);
    B.outcode = generateOutcode(B);  
    
    /* intersection points initialized to inadmissible values */
    IP1.x = -1;
    IP1.y = -1;    
    IP2.x = -1;
    IP2.y = -1; 
    
    if(accept(A, B))       /* trivially accepted */
    {
         printf("\n\nLine is already within clipping window.\n");
         return;
    }
    else if(reject(A, B)) /* trivially rejected */
    {
         printf("\n\nLine cannot be clipped. Terminating program...\n");
         return;
    }
    
    
    /* Dealing with lines that run along a boundary: 
       (Such a line would have hundreds of intersection points and hence won't work with our subdivision algorithm.) */
    if((A.x == B.x) && (A.x == Xmin || A.x == Xmax))  /* line runs along left or right boundary */
    {
           liesOnBoundary = true;
           IP1 = A;
           IP2 = B;
           
           if(A.outcode)  /*if A lies outside clipping window */
           {
               IP1.x = A.x;
               if(A.y < Ymin)
                   IP1.y = Ymin;
               else
                   IP1.y = Ymax;
           }
           
           if(B.outcode) /*if B lies outside clipping window */
           {
               IP2.x = B.x;
               if(B.y < Ymin)
                   IP2.y = Ymin;
               else
                   IP2.y = Ymax;
           }               
    }
    if((A.y == B.y) && (A.y == Ymin || A.y == Ymax))  /* line runs along bottom or top boundary */
    {
           liesOnBoundary = true;
           IP1 = A;
           IP2 = B;
           
           if(A.outcode)  /*if A lies outside clipping window */
           {
               IP1.y = A.y;
               if(A.x < Xmin)
                   IP1.x = Xmin;
               else
                   IP1.x = Xmax;
           }
           
           if(B.outcode) /*if B lies outside clipping window */
           {
               IP2.y = B.y;
               if(B.x < Xmin)
                   IP2.x = Xmin;
               else
                   IP2.x = Xmax;
           }            
    }

    if(!liesOnBoundary)
            midpointClip(A, B);   /* call to recursive function midpointClip() */
    
    if(IP1.x == -1)       /* if no intersection point with the viewport boundaries is found */
    {
             printf("\n\nLine cannot be clipped. Terminating program...\n");
             return;
    }

    else if(IP2.x == -1)   /* if only one intersection point is found; one of the two endpoints of the original line segment lies within clipping window */
    {
         if(!A.outcode)   /* if A lies within clipping window */
             IP2 = A;
         else             
             IP2 = B;
    }
    
    printf("\n\nLine has been clipped.\n");
         
    delay(3000);
         
    initwindow(1280, 720, "Line Clipping 2", 0, 0, true);   /* new window created with dual-buffering enabled */
         
    rectangle(Xmin, fy(Ymax), Xmax, fy(Ymin));              /* drawing viewport in current buffer of current window */
    outtextxy(580, fy(650), "Internal Clipping");
    setcolor(12);                                           /* colour set to pink */
    line(IP1.x, fy(IP1.y), IP2.x, fy(IP2.y));               /* drawing internally-clipped line */
         
    delay(2000);
         
    swapbuffers();
    setcolor(15);                                           /* colour set to white */
    rectangle(Xmin, fy(Ymax), Xmax, fy(Ymin));              /* drawing viewport in other buffer of current window */
    outtextxy(580, fy(650), "External Clipping");
    setcolor(12);                                           /* colour set to pink */
    /* drawing externally clipped line(s) */
    line(A.x, fy(A.y), IP1.x, fy(IP1.y));     
    line(IP2.x, fy(IP2.y), B.x, fy(B.y));
         
    while(!kbhit())
    {
                        delay(2000);
                        swapbuffers();                           /* switching between buffers every 2 seconds */
    }
}

/* Recursive definition of the midpoint-subdivision line-clipping algorithm */
void midpointClip(Point A, Point B)
{
     Point midpoint;
     
     if(abs(A.x - B.x) <= 1 && abs(A.y - B.y) <= 1)        /* base case 1: A and B are adjacent pixels */
     /* Since we are doing integer calculations, no new midpoint can be found for a line segment whose endpoints are adjacent.
        Hence, if such a line segment is encountered, the corresponding function call is terminated immediately.
        (Otherwise, it results in infinite recursive calls leading nowhere and ultimately exhausting system-stack.) */   
         return;
     
     midpoint.x = (A.x + B.x) / 2;
     midpoint.y = (A.y + B.y) / 2;
     midpoint.outcode = generateOutcode(midpoint);
     
     if(midpoint.x == Xmin || midpoint.x == Xmax || midpoint.y == Ymin || midpoint.y == Ymax)    /* base case 2: midpoint is an intersection point */
     {
              if(IP1.x == -1)  /* if no intersection point has been found till now, update IP1 */
                      IP1 = midpoint;
              else  /* else, update IP2 */
                      IP2 = midpoint;
     }
     
     else  /* recursive calls: a subdivison is to be divided further only if one of the endpoints lies within the viewport and the other, outside */
     {
              if((!A.outcode && midpoint.outcode) || (A.outcode && !midpoint.outcode))
                      midpointClip(A, midpoint);
                      
              if((!B.outcode && midpoint.outcode) || (B.outcode && !midpoint.outcode))
                      midpointClip(midpoint, B);
     }
}

/* Function to generate region-code of a point w.r.t. viewport boundaries */
int generateOutcode(Point A)
{
    
    int outcode = 1000 * (A.x < Xmin) + 100 * (A.x > Xmax) + 10 * (A.y < Ymin) + 1 * (A.y > Ymax);
    return outcode;
}

/* Function to check whether a line-segment lies within the viewport */
bool accept(Point A, Point B)
{
    if((!A.outcode) && (!B.outcode))  /* accept if: Both A and B lie within clipping window (i.e., A.outcode and B.outcode both evaluate to 0000) */
            return true;
    else
            return false;
}

/* Function to trivially reject a line for clipping  */
bool reject(Point A, Point B)
{
    /* Reject if: Bitwise AND of outcodes evaluates to any value other than 0000. 
       (Cannot employ the '&' operator since outcodes are in binary already. Besides, the result is sought in binary as well.)*/
       
    if((A.outcode % 10) == 1 && (B.outcode % 10) == 1)                                /* if both LSBs are 1 */
            return true; 
    else if(((A.outcode / 10) % 10) == 1 && ((B.outcode / 10) % 10) == 1)             /* if the bit to the left of the LSB in both cases is 1 */
            return true; 
    else if(((A.outcode / 100) % 10) == 1 && ((B.outcode / 100) % 10) == 1)           /* if the bit to the right of the MSB in both cases is 1 */
            return true; 
    else if(((A.outcode / 1000) % 10) == 1 && ((B.outcode / 1000) % 10) == 1)          /* if both MSBs are 1 */
            return true; 
    else    /* cannot trivially reject */
            return false;
} 

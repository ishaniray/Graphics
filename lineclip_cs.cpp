/* Cohen-Sutherland's Line-Clipping Algorithm */

#include <stdio.h>
#include <graphics.h>

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
int generateOutcode(Point);
bool accept(Point, Point);
bool reject(Point, Point);

/* Global variables */
int Xmin, Xmax, Ymin, Ymax;     /* viewport boundaries */

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

/* Function implementing Cohen-Sutherland's Line-Clipping Algorithm */
void clip(Point A, Point B)
{
    bool clipped;
    Point IP1, IP2, oldIP1, oldIP2;   /* IP: Intersection Point */
    
    A.outcode = generateOutcode(A);
    B.outcode = generateOutcode(B);
    
    /* intersection points initialized to A and B respectively */
    IP1 = A;    
    IP2 = B;   
    
    if(accept(A, B))    /* trivially accepted */
    {
         printf("\n\nLine is already within clipping window.\n");
         return;
    }
    else if(reject(A, B))    /* trivially rejected */
    {
         printf("\n\nLine cannot be clipped. Terminating program...\n");
         return ;
    }
    
    /* Dealing with vertical (or horizontal) lines: 
       Since IP co-ordinates will be computed by equating slopes, if delta-x (or delta-y) is zero, 
       increment an x-value (or y-value), so as to bypass the division-by-zero error. */
    if(B.x - A.x == 0)
           ++A.x;
    else if(B.y - A.y == 0)
           ++A.y;
    
    do
    {  
               clipped = false;
               oldIP1 = IP1;
               oldIP2 = IP2;
                       
               if(IP1.outcode > 999)               /* an intersection point with the left boundary can be found */
               {
                            IP1.x = Xmin;
                            IP1.y = B.y - (((B.x - IP1.x) * (B.y - A.y)) / (B.x - A.x));     
                            IP1.outcode = generateOutcode(IP1);
                            clipped = true;
               }
               else if(IP1.outcode > 99)           /* an intersection point with the right boundary can be found */
               {
                            IP1.x = Xmax;
                            IP1.y = B.y - (((B.x - IP1.x) * (B.y - A.y)) / (B.x - A.x));
                            IP1.outcode = generateOutcode(IP1);
                            clipped = true;
               }
            
               else if(IP1.outcode % 10)          /* an intersection point with the top boundary can be found */
               {
                            IP1.y = Ymax;
                            IP1.x = B.x - (((B.y - IP1.y) * (B.x - A.x)) / (B.y - A.y));
                            IP1.outcode = generateOutcode(IP1);
                            clipped = true;
               }
               else if((IP1.outcode / 10) % 10)    /* an intersection point with the bottom boundary can be found */
               {
                            IP1.y = Ymin;
                            IP1.x = B.x - (((B.y - IP1.y) * (B.x - A.x)) / (B.y - A.y));
                            IP1.outcode = generateOutcode(IP1);
                            clipped = true;
               }
               
    
               if(IP2.outcode > 999)               /* an intersection point with the left boundary can be found */
               {
                            IP2.x = Xmin;
                            IP2.y = B.y - (((B.x - IP2.x) * (B.y - A.y)) / (B.x - A.x));
                            IP2.outcode = generateOutcode(IP2);
                            clipped = true;
               }
               else if(IP2.outcode > 99)           /* an intersection point with the right boundary can be found */
               {
                            IP2.x = Xmax;
                            IP2.y = B.y - (((B.x - IP2.x) * (B.y - A.y)) / (B.x - A.x));
                            IP2.outcode = generateOutcode(IP2);
                            clipped = true;
               }
            
               else if(IP2.outcode % 10)           /* an intersection point with the top boundary can be found */
               {
                            IP2.y = Ymax;
                            IP2.x = B.x - (((B.y - IP2.y) * (B.x - A.x)) / (B.y - A.y));
                            IP2.outcode = generateOutcode(IP2);
                            clipped = true;
               }            
               else if((IP2.outcode / 10) % 10)    /* an intersection point with the bottom boundary can be found */
               {
                            IP2.y = Ymin;
                            IP2.x = B.x - (((B.y - IP2.y) * (B.x - A.x)) / (B.y - A.y));
                            IP2.outcode = generateOutcode(IP2);
                            clipped = true;
               }
               
               if((IP1.x == oldIP2.x && IP1.y == oldIP2.y) || (IP2.x == oldIP1.x && IP2.y == oldIP1.y))  
                            clipped = false;  /* intersection points simply exchanging places in successive iterations does not amount to clipping */
                            
    } while(clipped);  /* if no clipping takes place in a particular iteration, the line can be clipped no further, and hence we break out of the loop */
    
    if(accept(IP1, IP2))    /* if the final clipped portion lies entirely within viewport */
    {
         printf("\n\nLine has been clipped.\n");
         
         delay(5000);
         
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
   
    else  /* rejected after evaluating clipping candidates */
         printf("\n\nLine cannot be clipped. Terminating program...\n");
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

/* Implementation of Cyrus-Beck Algorithm where the clipping polygon is a standard rectangle (i.e., aligned with the x and y axes).
   (This implementation is not extensible - i.e., the program will not work for other kinds of polygon.)  
   [Inputs are hardcoded.] */

#include <graphics.h>
#include <math.h>

/* Structure definition */
typedef struct point
{
        int x;
        int y;
        int outcode;
} Point;

/* Function prototypes */
int generateOutcode(Point);
bool reject(Point, Point);
void cyrusBeck(Point, Point B);

int Xmin = 300, Xmax = 900, Ymin = 175, Ymax = 575;    /* Global variables: viewport dimensions */

int main(void)
{
    Point A, B;
    
    A.x = 100;
    A.y = 400;
    A.outcode = generateOutcode(A);
    
    B.x = 700;
    B.y = 100;
    B.outcode = generateOutcode(B);
    
    initwindow(1280, 720, "Cyrus-Beck Line-Clipping Algorithm");
    rectangle(Xmin, Ymin, Xmax, Ymax);
    line(A.x, A.y, B.x, B.y);
    
    if(!A.outcode && !B.outcode)    /* trivial acceptance */
        printf("Line is already within clipping window.");
    else
        cyrusBeck(A, B);        /* call to cyrusBeck() */
    
    while(!kbhit());    /* hold the window open until a key is pressed */
    closegraph();
    return 0;
}

/* Function to generate region codes.
   Flag order: Left, Right, Bottom, Top */
int generateOutcode(Point A)
{
    int outcode = 1000 * (A.x < Xmin) + 100 * (A.x > Xmax) + 10 * (A.y > Ymax) + 1 * (A.y < Ymin);
    return outcode;
}

/* Function implementing the Cyrus-Beck Line-Clipping Algorithm.
   Direction of the line is assumed to be from Point A to Point B. */
void cyrusBeck(Point A, Point B)
{
     Point IP, IP1 = A, IP2 = B;     /* 'IP' stands for intersection point. IP1 and IP2 are the points between which the resultant line will be drawn. IP is used for temporary calculations. */
     float pet = 0.0, plt = 1.0, abd, d, t;
     abd = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));    /* distance between A and B */
     
     if(reject(A, B))    /* trivial rejection */
     {
         printf("Line cannot be clipped.");
         return;
     }
     
     if((A.outcode >= 1000 && B.outcode < 1000) || (A.outcode < 1000 && B.outcode >= 1000))    /* an intersection point with the left boundary can be found */
     {
         IP.x = Xmin;
         IP.y = B.y - (((B.x - IP.x) * (B.y - A.y)) / (B.x - A.x));
         
         d = sqrt(pow(IP.x - A.x, 2) + pow(IP.y - A.y, 2));    /* distance between A and IP */
         t = d / abd;
         
         if(B.x >= Xmin)    /* potentially entering situation */
         {
             if(t > pet)
             {
                 pet = t;
                 IP1 = IP;
             }
         }
         else               /* potentially leaving situation */
         {
             if(t < plt)
             {
                 plt = t;
                 IP2 = IP;
             }
         }
     }
     
     if((A.outcode / 100) % 10 != (B.outcode / 100) % 10)    /* an intersection point with the right boundary can be found */
     {
         IP.x = Xmax;
         IP.y = B.y - (((B.x - IP.x) * (B.y - A.y)) / (B.x - A.x));
         
         d = sqrt(pow(IP.x - A.x, 2) + pow(IP.y - A.y, 2));    /* distance between A and IP */
         t = d / abd;
         
         if(B.x <= Xmax)    /* potentially entering situation */
         {
             if(t > pet)
             {
                 pet = t;
                 IP1 = IP;
             }
         }
         else               /* potentially leaving situation */
         {
             if(t < plt)
             {
                 plt = t;
                 IP2 = IP;
             }
         }
     }
     
     if((A.outcode / 10) % 10 != (B.outcode / 10) % 10)    /* an intersection point with the bottom boundary can be found */
     {
         IP.y = Ymax;
         IP.x = B.x - (((B.y - IP.y) * (B.x - A.x)) / (B.y - A.y));
         
         d = sqrt(pow(IP.x - A.x, 2) + pow(IP.y - A.y, 2));    /* distance between A and IP */
         t = d / abd;
         
         if(B.y <= Ymax)    /* potentially entering situation */
         {
             if(t > pet)
             {
                 pet = t;
                 IP1 = IP;
             }
         }
         else               /* potentially leaving situation */
         {
             if(t < plt)
             {
                 plt = t;
                 IP2 = IP;
             }
         }
     }
     
     if(A.outcode % 10 != B.outcode % 10)    /* an intersection point with the top boundary can be found */
     {
         IP.y = Ymin;
         IP.x = B.x - (((B.y - IP.y) * (B.x - A.x)) / (B.y - A.y));
         
         d = sqrt(pow(IP.x - A.x, 2) + pow(IP.y - A.y, 2));    /* distance between A and IP */
         t = d / abd;
         
         if(B.y >= Ymin)    /* potentially entering situation */
         {
             if(t > pet)
             {
                 pet = t;
                 IP1 = IP;
             }
         }
         else               /* potentially leaving situation */
         {
             if(t < plt)
             {
                 plt = t;
                 IP2 = IP;
             }
         }
     }
     
     if(pet <= plt)    /* we have a clipping candidate */
     {
         setcolor(LIGHTRED);
         line(IP1.x, IP1.y, IP2.x, IP2.y);
         printf("Line has been clipped.");
     }
     
     else
         printf("Line cannot be clipped."); 
}

/* Function to trivially reject a line for clipping  */
bool reject(Point A, Point B)
{
       
    if((A.outcode % 10) == 1 && (B.outcode % 10) == 1)                                /* if line lies totally above the clipping window */
            return true; 
    else if(((A.outcode / 10) % 10) == 1 && ((B.outcode / 10) % 10) == 1)             /* if line lies totally beneath the clipping window */
            return true; 
    else if(((A.outcode / 100) % 10) == 1 && ((B.outcode / 100) % 10) == 1)           /* if line lies entirely to the right of the clipping window */
            return true; 
    else if(((A.outcode / 1000) % 10) == 1 && ((B.outcode / 1000) % 10) == 1)          /* if line lies entirely to the left of the clipping window */
            return true; 
    else    /* cannot trivially reject */
            return false;
} 

/* Bresenham's Line-Drawing Algorithm */

#include <stdio.h>
#include <graphics.h>
#include <math.h>

/* Macros */
#define TRUE 1
#define FALSE 0
#define WHITE 15   /* colour code */

/* Structure definition */
struct point
{
       int x;    /* x co-ordinate of a point */
       int y;    /* y co-ordinate of a point */
};

typedef struct point Point;

/* Function prototype */
void bresenham(Point, Point);

int main(void)
{
    Point initial, final;    /* a line is to be drawn from the initial point to the final point */
    
    printf("Please enter x, y co-ordinates of an endpoint:\n");
    scanf("%d", &initial.x);
    scanf("%d", &initial.y);
    
    printf("\n\nPlease enter x, y co-ordinates of the other endpoint:\n");
    scanf("%d", &final.x);
    scanf("%d", &final.y);
    
    initwindow(640, 480, "Bresenham's Line-Drawing Algorithm");    /* window size: 640 by 480 pixels */
    
    bresenham(initial, final);  /*call to function */
    
    while(!kbhit())
            ;          /* keep window open until a key is pressed */
    closegraph();
    return 0;
}

/* Function implementing Bresenham's line-drawing algorithm */
void bresenham(Point initial, Point final)
{
     int delX, delY, xInc, yInc, steepSlope = FALSE, decParam;
     
     delX = abs(final.x - initial.x);     /* delta-x */
     delY = abs(final.y - initial.y);     /* delta-y */
     
     if(delY > delX)
             steepSlope = TRUE;
     
     /* Checking if initial x, y values are to be gradually incremented or decremented to reach the final point */
     if(final.x > initial.x)
                xInc = 1;
     else
                xInc = -1;
                
     if(final.y > initial.y)
                yInc = 1;
     else
                yInc = -1;
                
     putpixel(initial.x, initial.y, WHITE);        /* the initial point is plotted */
                
     if(steepSlope)
     {
                   decParam = 2 * delX - delY;     /* initial decision parameter */
                   
                   while((initial.x != final.x) || (initial.y != final.y))      /* while the final point is yet to be reached */
                   {
                                    if(decParam > 0)
                                    {
                                                decParam += (2 * delX) - (2 * delY);
                                                initial.x += xInc;
                                                initial.y += yInc;
                                    }
                                    else
                                    {
                                                decParam += 2 * delX;
                                                initial.y += yInc;
                                    }
                                    putpixel(initial.x, initial.y, WHITE);
                   }
     }
     else     /* gentle slope */
     {
                 decParam = 2 * delY - delX;        /* initial decision parameter */
     
                 while((initial.x != final.x) || (initial.y != final.y))      /* while the final point is yet to be reached */
                 {
                                  if(decParam > 0)
                                  {
                                              decParam += (2 * delY) - (2 * delX);
                                              initial.x += xInc;
                                              initial.y += yInc;
                                  }
                                  else
                                  {
                                              decParam += 2 * delY;
                                              initial.x += xInc;
                                  }
                                  putpixel(initial.x, initial.y, WHITE);
                 }
     }
}

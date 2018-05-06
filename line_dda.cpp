/* This program draws a straight line using the Digital Differential Analyzer (DDA) algorithm */

#include <graphics.h>
#include <math.h>

/* Structure definition */
typedef struct point
{
        float x;    /* x co-ordinate of a point */
        float y;    /* y co-ordinate of a point */
} Point;

/* Function prototype */
void line_dda(int, int, int, int);

int main(void)
{
    int a, b, c, d;
    
    initwindow(1280, 720, "Line-Drawing - DDA Algorithm");
    outtextxy(425, 50, "Click and drag your mouse over the screen to draw a line!");
    
    while(true)    /* wait for a mouseclick */
    {
        if(ismouseclick(WM_LBUTTONDOWN))    /* once a left-click of the mouse occurs... */
        {
            getmouseclick(WM_LBUTTONDOWN, a, b);    /* ...capture the co-ordinates of the mouseclick... */
            while(!ismouseclick(WM_LBUTTONUP));    /* ...wait for the mouse to be released... */
            getmouseclick(WM_LBUTTONUP, c, d);    /* ...capture co-ordinates of the release point. */
            break;    /* break out of the loop */
        }
    }
    
    line_dda(a, b, c, d);    /* draw a line from (a, b) to (c, d) */
    
    while(!kbhit());    /* hold the window open until a key is pressed */
    closegraph();
    return 0;
}

/* Function to draw a line, applying the DDA algorithm */
void line_dda(int a, int b, int c, int d)
{    
     Point initial;
     float absSlope;
     int xInc, yInc;
     
     initial.x = a;    /* (a, b) is the first point to be plotted */
     initial.y = b;     
     
     if(c > a)
         xInc = 1;    /* x-increment is positive */
     else
         xInc = -1;    /* x-increment is negative (i.e., x is to be decremented) */
         
     if(d > b)
         yInc = 1;    /* y-increment is positive */
     else
         yInc = - 1;     /* y-increment is negative (i.e., y is to be decremented) */
     
     if((c - a) != 0)    /* if the line to be drawn is not a vertical line */    
         absSlope = fabs(float(d - b) / float(c - a));    /* calculate absolute slope */
     else    /* line to be drawn is a vertical line (or, is a single point); deal with it separately since we cannot calculate its slope and proceed the normal way */
     {
         while((yInc == 1 && initial.y < d) || (yInc == -1 && initial.y > d))    /* while the final y-value is yet to be reached */
         {
             putpixel(initial.x, initial.y, WHITE);    /* plot pixel previously calculated */
             initial.y = initial.y + yInc;    /* change y (no change in x) */
         }
         putpixel(c, d, WHITE);    /* plot final pixel */
         return;
     }
     
     if(absSlope <= 1)    /* gentle slope */
     {
         while((xInc == 1 && initial.x < c) || (xInc == -1 && initial.x > c))    /* while the final x-value is yet to be reached */
         {
             putpixel(int(initial.x), int(initial.y), WHITE);    /* plot pixel calculated previously */
             
             /* Calculate next pixel */
             initial.x = initial.x + xInc;    /* x is always incremented (or decremented) */
             initial.y = initial.y + (absSlope * yInc);    /* calculate y */
         }
     }
     else    /* absSlope) > 1; sharp slope */
     {
         while((yInc == 1 && initial.y < d) || (yInc == -1 && initial.y > d))    /* while the final y-value is yet to be reached */
         {
             putpixel(int(initial.x), int(initial.y), WHITE);    /* plot pixel calculated previously */
             
             /* Calculate next pixel */                         
             initial.x = initial.x + (1 / absSlope * xInc);    /* calculate x */
             initial.y = initial.y + yInc;    /* y is always incremented (or decremented) */
         }
     }

     putpixel(c, d, WHITE);    /* plot final pixel */
 }

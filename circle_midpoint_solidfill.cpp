/* This program draws a circle implementing the Mid-point Algorithm, and colours it via Boundary Fill, followed by Flood Fill */

#include <graphics.h>

/* Macros */
#define TRUE 1
#define FALSE 0
#define WHITE 15   
#define PINK 12
#define GREEN 10
#define fx(x) (getmaxx() / 2 + x)        /* puts origin at the... */
#define fy(y) (getmaxy() / 2 - y)        /* ...centre of the window. */

/* Structure definition */
typedef struct point
{
       int x;       /* x co-ordinate of a point */
       int y;       /* y co-ordinate of a point */
} Point;

/* Function prototypes */
void midpointcircle(int);
void boundFill4(int, int, int, int);
void floodFill4(int, int, int, int);

int main(void)
{
    int radius, a, b;

    radius = 180;
    
    initwindow(1280, 720);    /* window size: 1280 by 720 pixels */
    
    midpointcircle(radius);    /* circle is drawn */
    
    outtextxy(525, 100, "Click on the circle to colour it!");
    
    while(TRUE)
    {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                    getmouseclick(WM_LBUTTONDOWN, a, b);  /* in the event of a mouseclick, the co-ordinates (a, b) are captured... */
                    boundFill4(a, b, WHITE, PINK);         /* ...and Boundary Fill is applied. */
                    break;
            }
    }
    
    floodFill4(a, b, PINK, GREEN);    /* Flood Fill applied */
    
    while(!kbhit())
            ;
    closegraph();
    return 0;
}

/* Mid-point algorithm for drawing a circle:
   Only the second actant will be generated.
   Points in other octants will be plotted by applying the concepts of symmetry and reflection. 
   The centre of the circle is at (0, 0). */
void midpointcircle(int radius)
{
     Point initial;
     int decParam;
     
     initial.x = 0;
     initial.y = radius;       /* initial pixel: (0, radius) */
     
     decParam = 1 - radius;       /* initial decision parameter */
     
     while(initial.x <= initial.y)
     {
                     /* Plotting pixels in the eight octants */
                     putpixel(fx(initial.x), fy(initial.y), WHITE);
                     putpixel(fx(initial.y), fy(initial.x), WHITE);
                     putpixel(fx(initial.x), fy(-initial.y), WHITE);
                     putpixel(fx(initial.y), fy(-initial.x), WHITE);
                     putpixel(fx(-initial.y), fy(-initial.x), WHITE);
                     putpixel(fx(-initial.x), fy(-initial.y), WHITE);
                     putpixel(fx(-initial.x), fy(initial.y), WHITE);
                     putpixel(fx(-initial.y), fy(initial.x), WHITE);
                     
                     /* Computing which pixel to plot next */
                     if(decParam < 0)
                     {
                     
                                 initial.x += 1;
                                 decParam += 2 * (initial.x + 1) + 1;
                     }
                                 
                     else
                     {
                                 initial.x += 1;
                                 initial.y -= 1;
                                 decParam += 2 * (initial.x + 1) + 1 - 2 * (initial.y - 1);
                     }
                     
     }
}

/* Colouring the circle: Applying Boundary Fill */     
void boundFill4(int a, int b, int boundCol, int fillCol)
{
     int col = getpixel(a, b);              /* (a, b) - initial values captured by the mouseclick - is the inner pixel, and its colour is extracted */
     if(col != boundCol && col != fillCol)  /* if the inner pixel does not lie on the boundary and is yet to be coloured in the desired hue... */
     {
            putpixel(a, b, fillCol);        /* ...colour the pixel... */
                                            /* ...move right, left, up, down - recursively. */
            boundFill4(a + 1, b, boundCol, fillCol);
            boundFill4(a - 1, b, boundCol, fillCol);
            boundFill4(a, b + 1, boundCol, fillCol);
            boundFill4(a, b - 1, boundCol, fillCol);
     }
}

/* Applying Flood Fill:
   Works the same way as Boundary Fill, except, colouring continues as long as the original colour is encountered */
void floodFill4(int a, int b, int origCol, int fillCol)
{
     int col = getpixel(a, b);
     if(col == origCol)
     {
            putpixel(a, b, fillCol);
            floodFill4(a + 1, b, origCol, fillCol);
            floodFill4(a - 1, b, origCol, fillCol);
            floodFill4(a, b + 1, origCol, fillCol);
            floodFill4(a, b - 1, origCol, fillCol);
     }
}

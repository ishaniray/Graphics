/* This program applies simultaneous shearing on a square.
   All inputs except x-shear and y-shear values are hardcoded. */

#include <stdio.h>
#include <graphics.h>

/* Structure definition */
typedef struct point
{
        int x;    /* x co-ordinate of a point */
        int y;    /* y co-ordinate of a point */
} Point;

/* Function prototype */
void simultaneous_shearing(Point, Point, Point, Point, float, float);


int main(void)
{
    Point A, B, C, D;    /* A, B, C, D are the four vertices of the square */
    float xshear, yshear;
    
    A.x = 640;
    A.y = 360;
    B.x = 640;
    B.y = 260;
    C.x = 740;
    C.y = 260;
    D.x = 740;
    D.y = 360;
    
    printf("[Please note that origin lies at the top-left corner of the viewport.]");
    printf("\n\nEnter value of x-shear: ");
    scanf("%f", &xshear);
    printf("\nEnter value of y-shear: ");
    scanf("%f", &yshear);
    
    initwindow(1280, 720, "Shearing", 0, 0, true);    /* double buffering enabled */
    outtextxy(600, 50, "Pre-Shearing");
    
    rectangle(B.x, B.y, D.x, D.y);    /* draw original square */
    simultaneous_shearing(A, B, C, D, xshear, yshear);    /* apply shearing */
    
    closegraph();
    return 0;
}

/* Function to apply simultaneous shearing on ABCD */
void simultaneous_shearing(Point A, Point B, Point C, Point D, float xshear, float yshear)
{
    int tx, ty;    /* Translation factors */
     
    tx = A.x;
    ty = A.y;
    
    /* Translate points so that A is at (0, 0) */
    A.x -= tx;
    A.y -= ty;
    B.x -= tx;
    B.y -= ty;
    C.x -= tx;
    C.y -= ty;
    D.x -= tx;
    D.y -= ty;
    
    /* Apply x-shear */
    A.x += xshear * A.y;
    B.x += xshear * B.y;
    C.x += xshear * C.y;
    D.x += xshear * D.y;
    
    /* Apply y-shear */
    A.y += yshear * A.x;
    B.y += yshear * B.x;
    C.y += yshear * C.x;
    D.y += yshear * D.x;
    
    /* Translate back the points to their original co-ordinates */
    A.x += tx;
    A.y += ty;
    B.x += tx;
    B.y += ty;
    C.x += tx;
    C.y += ty;
    D.x += tx;
    D.y += ty;
    
    swapbuffers();    /* Swap buffers */
    outtextxy(600, 50, "Post-Shearing");
    
    /* Redraw sheared 'square' in other buffer */
    line(A.x, A.y, B.x, B.y);
    line(B.x, B.y, C.x, C.y);
    line(C.x, C.y, D.x, D.y);
    line(D.x, D.y, A.x, A.y);
    
    while(!kbhit())    /* until a key is pressed */
    {
        delay(2000);
        swapbuffers();    /* keep swapping buffers every two seconds */
    }
}

/* Program to rotate a straight line w.r.t. its midpoint */

#include <stdio.h>
#include <graphics.h>
#include <math.h>

/* Structure definition */
typedef struct point
{
       int x;    /* x co-ordinate of a point */
       int y;    /* y co-ordinate of a point */
} Point;

/* Function prototype */
void rotate_line(Point, Point, Point, float);

int main(void)
{
    Point A, B, midpoint;
    float r;    /* angle of rotation */
    
    printf("Enter (x, y) co-ordinates of the two enndpoints of the line.\n[Please note that origin lies at the top-left corner of the viewport.]");
    printf("\n\nEnter x: ");
    scanf("%d", &A.x);
    printf("\nEnter y: ");
    scanf("%d", &A.y);
    printf("\n\nEnter x: ");
    scanf("%d", &B.x);
    printf("\nEnter y: ");
    scanf("%d", &B.y);
    printf("\n\nEnter the angle of rotation (in degrees): ");
    scanf("%f", &r);
    
    r = r * M_PI / 180;    /* conversion of degrees to radians */
    
    midpoint.x = (A.x + B.x) / 2;    /* midpoint is the middle-point between A and B */
    midpoint.y = (A.y + B.y) / 2;
    
    initwindow(1280, 720, "Rotation");
    
    outtextxy(1050, 50, "Original Line");
    line(A.x, A.y, B.x, B.y);    /* draw the line */
    
    setcolor(LIGHTRED);
    outtextxy(1050, 70, "Counter-clockwise Rotation");
    rotate_line(A, B, midpoint, r);    /* rotate the line counter-clockwise w.r.t. its midpoint */
    
    setcolor(CYAN);
    outtextxy(1050, 90, "Clockwise Rotation");
    rotate_line(A, B, midpoint, -r);    /* rotate the line clockwise w.r.t. its midpoint */
    
    while(!kbhit());    /* hold the window open until a key is pressed */
    closegraph();
    return 0;
}

/* Function to rotate a line w.r.t. its midpoint (in both directions) */
void rotate_line(Point A, Point B, Point midpoint, float r)
{
     int tx, ty;
     Point temp;
     
     /* Translate pivot to origin (figuratively); translate the endpoints of the line accordingly (literally) */
     tx = midpoint.x;
     ty = midpoint.y;
     
     A.x -= tx;
     A.y -= ty;
     
     B.x -= tx;
     B.y -= ty;
     
     /* Apply rotation */
     A.x = (A.x * cos(r)) - (A.y * sin(r));
     A.y = (A.x * sin(r)) + (A.y * cos(r));
     
     B.x = (B.x * cos(r)) - (B.y * sin(r));
     B.y = (B.x * sin(r)) + (B.y * cos(r));
     
     /* Translate points back to their original co-ordinates */
     A.x += tx;
     A.y += ty;
     
     B.x += tx;
     B.y += ty;
     
     line(A.x, A.y, B.x, B.y);    /* draw rotated line */
}

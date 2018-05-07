/* This program draws an ellipse whose axes are aligned with the X and Y axes, implementing the Midpoint Algorithm */

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
void midpoint_ellipse(int, int, Point);

int main(void)
{
    int a, b;
    Point centre;
    
    printf("Provide values.\n[Please note that origin lies at the top-left corner of the viewport.]\n");
    printf("\nSemi-major axis: ");
    scanf("%d", &a);
    printf("\nSemi-minor axis: ");
    scanf("%d", &b);
    printf("\nx-value of centre: ");
    scanf("%d", &centre.x);
    printf("\ny-value of centre: ");
    scanf("%d", &centre.y);
    
    initwindow(1280, 720, "Ellipse - Midpoint Algorithm");
    
    midpoint_ellipse(a, b, centre);
    
    while(!kbhit());    /* hold the window open until a key is pressed */
    closegraph();
    return 0;
}

/* Function implementing the Midpoint Algorithm for drawing ellipses */
void  midpoint_ellipse(int a, int b, Point centre)
{
      Point initial;
      int decParam, slope;
      
      initial.x = 0;   /* (0, b) is the first point to be plotted in Region 1 */
      initial.y = b;
      
      slope = -((pow(b, 2) * initial.x) / (pow(a, 2) * initial.y));    /* slope of the ellipse at point (0, b) */
      decParam = (pow(a, 2) / 4) - (pow(a, 2) * b) + pow(b, 2);    /* initial decision parameter for Region 1 */
      
      while(slope > -1)   /* Region 1 */
      {
          putpixel(initial.x + centre.x, initial.y + centre.y, LIGHTRED);    /* plot the pixel calculated previously */
          putpixel(-initial.x + centre.x, initial.y + centre.y, YELLOW);    /* reflect point in second quadrant */
          putpixel(-initial.x + centre.x, -initial.y + centre.y, LIGHTGREEN);    /* reflect point in third quadrant */
          putpixel(initial.x + centre.x, -initial.y + centre.y, CYAN);    /* reflect point in fourth qudrant */
          
          if(decParam < 0)
          {
              initial.x = initial.x + 1;   /* only increment x */
              decParam = decParam + (2 * pow(b, 2) * initial.x) + pow(b, 2);    /* update decision parameter */
          }
          else    /* decParam >= 0 */
          {
              initial.x = initial.x + 1;    /* increment x */
              initial.y = initial.y - 1;    /* decrement y */
              decParam = decParam + (2 * pow(b, 2) * initial.x) + pow(b, 2) - (2 * pow(a, 2) * initial.y);    /* update decision parameter */
          }
          
          slope = -((pow(b, 2) * initial.x) / (pow(a, 2) * initial.y));    /* re-calculate slope */
          
          delay(10);
      }
      
      decParam = (pow(b, 2) * pow(initial.x + 0.5, 2)) + (pow(a, 2) * pow(initial.y - 1, 2)) - (pow(a, 2) * pow(b, 2));    /* initial decision parameter for Region 2 */
      
      while(!(initial.x == a && initial.y == 0))    /* Region 2 */
      {
          putpixel(initial.x + centre.x, initial.y + centre.y, LIGHTRED);    /* plot the pixel calculated previously */
          putpixel(-initial.x + centre.x, initial.y + centre.y, YELLOW);    /* reflect point in second quadrant */
          putpixel(-initial.x + centre.x, -initial.y + centre.y, LIGHTGREEN);    /* reflect point in third quadrant */
          putpixel(initial.x + centre.x, -initial.y + centre.y, CYAN);    /* reflect point in fourth qudrant */
          
          if(decParam < 0)
          {
              initial.x = initial.x + 1;    /* increment x */
              initial.y = initial.y - 1;    /* increment y */
              decParam = decParam + (2 * pow(b, 2) * initial.x) - (2 * pow(a, 2) * initial.y) + pow(a, 2);    /* update decision parameter */
          }
          else    /* decision parameter >= 0 */
          {
              initial.y = initial.y - 1;    /* only decrement y */
              decParam = decParam - (2 * pow(a, 2) * initial.y) + pow(a, 2);    /* update decision parameter */
          }
          
          delay(10);
      }      
}

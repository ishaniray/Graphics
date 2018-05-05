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
void bresenham(Point, Point, bool*);

int main(void)
{
    Point initial, final;    /* a line is to be drawn from the initial point to the final point */
    int choice;
    bool styles[4] = {false};    /* indices correspond to dashed, dotted, dash-dot, and thick styles respectively */
    
    printf("Please enter x, y co-ordinates of an endpoint:\n");
    scanf("%d", &initial.x);
    scanf("%d", &initial.y);
    
    printf("\n\nPlease enter x, y co-ordinates of the other endpoint:\n");
    scanf("%d", &final.x);
    scanf("%d", &final.y);
    
    printf("\n\nLINE STYLES:\nDASHED = 0; DOTTED = 1; DASH-DOT = 2; THICK = 3");
    printf("\n\nPick a line style: ");
    scanf("%d", &choice);
    styles[choice] = true; 
    
    initwindow(1280, 720, "Bresenham's Line-Drawing Algorithm");    /* window size: 1280 by 720 pixels */
    
    bresenham(initial, final, styles);  /*call to function */
    
    while(!kbhit())
            ;          /* keep window open until a key is pressed */
    closegraph();
    return 0;
}

/* Function implementing Bresenham's line-drawing algorithm */
void bresenham(Point initial, Point final, bool *styles)
{
     int delX, delY, xInc, yInc, steepSlope = FALSE, decParam, count[3] = {1};
     
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
                                    
                                    if(styles[0])    /* dashed line chosen */
                                    {
                                        if(count[0] % 9 != 0)    /* if true, plot current pixel (a dash is a sequence of eight pixels; every ninth pixel is to be skipped) */
                                            putpixel(initial.x, initial.y, WHITE);
                                        ++count[0];
                                    }
                                    else if(styles[1])    /* dotted line chosen */
                                    {
                                        if(count[1] % 2 != 0)    /* if true, plot current pixel (every second pixel is to be skipped) */
                                            putpixel(initial.x, initial.y, WHITE);
                                        ++count[1];
                                    }
                                    else if(styles[2])    /* dash-dot line chosen */
                                    {
                                         if((count[2] % 9 != 0) && (count[2] % 11 != 0))    /* if true, plot current pixel (the tenth and twelfth pixels are to be left blank to create a dash-dot effect) */
                                             putpixel(initial.x, initial.y, WHITE);
                                         else if(count[2] % 11 == 0)    /* if a cycle is complete... */
                                             count[2] = 0;    /* ...reset cycle. */
                                         ++count[2];
                                    }
                                    else    /* thick line chosen */
                                    {
                                        /* plot adjacent pixels along with the target pixel */
                                        putpixel(initial.x - 1, initial.y, WHITE);
                                        putpixel(initial.x, initial.y, WHITE);
                                        putpixel(initial.x + 1, initial.y, WHITE);
                                    }
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
                                  
                                  if(styles[0])    /* dashed line chosen */
                                  {
                                      if(count[0] % 9 != 0)    /* if true, plot current pixel (a dash is a sequence of eight pixels; every ninth pixel is to be skipped) */
                                          putpixel(initial.x, initial.y, WHITE);
                                      ++count[0];
                                  }
                                  else if(styles[1])    /* dotted line chosen */
                                  {
                                      if(count[1] % 2 != 0)    /* if true, plot current pixel (every second pixel is to be skipped) */
                                          putpixel(initial.x, initial.y, WHITE);
                                      ++count[1];
                                  }
                                  else if(styles[2])    /* dash-dot line chosen */
                                  {
                                      if((count[2] % 9 != 0) && (count[2] % 11 != 0))    /* if true, plot current pixel (the tenth and twelfth pixels are to be left blank to create a dash-dot effect) */
                                          putpixel(initial.x, initial.y, WHITE);
                                      else if(count[2] % 11 == 0)    /* if a cycle is complete... */
                                          count[2] = 0;    /* ...reset cycle. */
                                      ++count[2];
                                  }
                                  else    /* thick line chosen */
                                  {
                                      /* plot adjacent pixels along with the target pixel */
                                      putpixel(initial.x, initial.y - 1, WHITE);
                                      putpixel(initial.x, initial.y, WHITE);
                                      putpixel(initial.x, initial.y + 1, WHITE);
                                  }
                 }
     }
}

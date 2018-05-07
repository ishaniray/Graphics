/* This is a simple program demonstrating a lunar eclipse.

   Since no filling algorithm has been applied to colour the circles - one smaller circle 
   has been drawn within another in a loop to create the desired effect - aliasing is observed. */

#include <graphics.h>

int main(void)
{
    int x1 = 320, y1 = 240, x2 = 560, y2 = 240, radius, a, b;
    
    initwindow(640, 480, "Lunar Eclipse", 0, 0, true);  /* sixth parameter indicates the use of two buffers */
    
    while(x2 != 0)
    {
             setcolor(15);
             for(radius = 120; radius > 0; --radius)
                        circle(x1, y1, radius);     /* draw the moon */
                        
             setcolor(0);
             for(radius = 120; radius > 0; --radius)
                        circle(x2, y2, radius);     /* draw the shadow */
                        
             delay(500);
                               
             x2 = x2 - 5;      /* decrement x2 by 5, so that in the next iteration, the shadow moves to the left by 5 pixels */
       
             setcolor(12);
             if(ismouseclick(WM_LBUTTONDOWN))  /* check for a mouseclick */
             {
                        getmouseclick(WM_LBUTTONDOWN, a, b);
                        outtextxy(a, b, "Lo and behold! It's an eclipse!");         /* display a message at the point where the mouseclick occurs */
             }
             
             swapbuffers();          /* switch to the other buffer */
    }
    
    while(!kbhit());        /* hold window open until a key is pressed */
    return 0;
}

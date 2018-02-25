/* This program draws lines on the screen by making use of WinBGIm library's mouse-event handlers. */

#include <graphics.h>

int main(void)
{
    int x, y, a, b;
    
    initwindow(1280, 720, "Lines and Lines of Code");
    
    outtextxy(425, 50, "Draw lines by clicking and dragging your mouse over the screen!");
    
    while(true)
    {
               while(!ismouseclick(WM_LBUTTONDOWN))
                       ;                                    /* wait for a mouseclick */
               getmouseclick(WM_LBUTTONDOWN, x, y);         /* capture co-ordinates of the mouseclick (x, y) once it happens */
    
               while(!ismouseclick(WM_LBUTTONUP))
                       ;                                    /* wait until mouse-button is released */
               getmouseclick(WM_LBUTTONUP, a, b);           /* capture release-point (a, b) */
    
               line(x, y, a, b);                            /* draw a line from (x, y) to (a, b) */
               
               clearmouseclick(WM_LBUTTONDOWN);
               clearmouseclick(WM_LBUTTONUP);
    }
    
    return 0;
}

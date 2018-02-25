/* This program emulates freehand drawing by making use of WinBGIm library's mouse-event handlers.
   Since the handlers are a tad slow, if the mouse moves too fast, lesser number of pixels get traced along the path, giving the drawings a dotted appearance. */ 

#include <graphics.h>

int main(void)
{
    int x, y, a, b;
    
    initwindow(1280, 720, "Let's Draw!");
    
    outtextxy(450, 50, "Draw by clicking and dragging your mouse over the screen!");
    
    while(true)
    {
               while(!ismouseclick(WM_LBUTTONDOWN))
                       ;                                         /* wait for a mouseclick */
               getmouseclick(WM_LBUTTONDOWN, x, y);              /* once a mouseclick happens, capture co-ordinates... */
               putpixel(x, y, 15);                               /* ...plot that pixel... */
               
               while(!ismouseclick(WM_LBUTTONUP))                /* ...while mouse-button is not released... */
               {
                       getmouseclick(WM_MOUSEMOVE, x, y);         /* ...trace mouse movements... */
                       putpixel(x, y, 15);                        /* ...plot pixels along the path in which the mouse moves. */
               }                                                  
               
               clearmouseclick(WM_LBUTTONDOWN);
               clearmouseclick(WM_LBUTTONUP);
    }
    
    return 0;
}

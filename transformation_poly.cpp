/* 2D Transformation of an Assymmetric Polygon: Translation + Rotation (about any point) + Scaling */

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

#define fy(y) (getmaxy() - y)       /* calibrate origin to bottom-left corner of the window */

/* Structure definitions */
typedef struct point
{
       int x;         /* x co-ordinate of a point */
       int y;         /* y co-ordinate of a point */
} Point;

typedef struct edge
{
       Point A;       /* A and B are the two endpoints of an edge */
       Point B;
} Edge;

int main(void)
{
    Edge *edgeTable, *newEdgeTable;
    int numofedges, i, tx, ty, Xshift, Yshift, oldVal; 
    float r, sx, sy;
    Point pivotr, pivots;
    
    printf("TRANSFORMATION of a POLYGON:\n");
    printf("(All drawings take place in the first quadrant. Window size is 1280 by 720 pixels. Please provide inputs accordingly.)\n\n");
    
    /* Sample inputs:
       - Triangle with vertices at (400, 200), (800, 200), (400, 500);
       - tx = 50; ty = 50;
       - r = 45;
       - Pivot at (400, 200);
       - sx = 0.75; sy = 0.75; */
    
    printf("How many edges does the polygon have?\n");
    scanf("%u", &numofedges);
    
    edgeTable = (Edge*)malloc(numofedges * sizeof(Edge));      /* edge-list for original polygon */
    newEdgeTable = (Edge*)malloc(numofedges * sizeof(Edge));   /* edge-list for transformed polygon */
    
    printf("\nFor each edge, enter the (x, y) co-ordinates of the two endpoints:\n");
    
    for(i = 0; i < numofedges; ++i)
    {
          printf("\nEdge %d -", i + 1);
          printf("\nx1: ");
          scanf("%u", &edgeTable[i].A.x);
          printf("\ny1: ");
          scanf("%u", &edgeTable[i].A.y);
          printf("\nx2: ");
          scanf("%u", &edgeTable[i].B.x);
          printf("\ny2: ");
          scanf("%u", &edgeTable[i].B.y);
    }
    
    printf("\nProvide translation factors (tx and ty, respectively):\n");
    scanf("%d%d", &tx, &ty);
    
    printf("\nProvide the angle of rotation (in degrees):\n");
    scanf("%f", &r);
    r *= M_PI / 180;  /* conversion from degrees to radians */
    printf("Enter (x, y) co-ordinates of the pivot (for rotation):\n");
    scanf("%d%d", &pivotr.x, &pivotr.y);
    
    printf("\nProvide scaling factors (sx and sy, respectively):\n");
    scanf("%f%f", &sx, &sy);
    printf("Enter (x, y) co-ordinates of the pivot (for scaling):\n");
    scanf("%d%d", &pivots.x, &pivots.y);
          
    for(i = 0; i < numofedges; ++i)
    {
          /* Translation */
          newEdgeTable[i].A.x = edgeTable[i].A.x + tx;
          newEdgeTable[i].A.y = edgeTable[i].A.y + ty;
          
          Xshift = -pivotr.x;
          Yshift = -pivotr.y;
          
          /* Pivot point is lined up with origin; calibrating points accordingly */
          newEdgeTable[i].A.x = newEdgeTable[i].A.x + Xshift;
          newEdgeTable[i].A.y = newEdgeTable[i].A.y + Yshift;
          
          /* Rotation */
          oldVal = newEdgeTable[i].A.x;
          newEdgeTable[i].A.x = newEdgeTable[i].A.x * cos(r) - newEdgeTable[i].A.y * sin(r);
          newEdgeTable[i].A.y = oldVal * sin(r) + newEdgeTable[i].A.y * cos(r);
          
          /* Re-calibrating points w.r.t. original co-ordinate system */
          newEdgeTable[i].A.x = newEdgeTable[i].A.x - Xshift;
          newEdgeTable[i].A.y = newEdgeTable[i].A.y - Yshift;
          
          Xshift = -pivots.x;
          Yshift = -pivots.y;
          
          /* Pivot point is lined up with origin; calibrating points accordingly */
          newEdgeTable[i].A.x = newEdgeTable[i].A.x + Xshift;
          newEdgeTable[i].A.y = newEdgeTable[i].A.y + Yshift;
          
          /* Scaling */
          newEdgeTable[i].A.x = newEdgeTable[i].A.x * sx;
          newEdgeTable[i].A.y = newEdgeTable[i].A.y * sy;
          
          /* Re-calibrating points w.r.t. original co-ordinate system */
          newEdgeTable[i].A.x = newEdgeTable[i].A.x - Xshift;
          newEdgeTable[i].A.y = newEdgeTable[i].A.y - Yshift;
          
          /* Repeating process for Point B */
          newEdgeTable[i].B.x = edgeTable[i].B.x + tx;
          newEdgeTable[i].B.y = edgeTable[i].B.y + ty;
          
          Xshift = -pivotr.x;
          Yshift = -pivotr.y;
            
          newEdgeTable[i].B.x = newEdgeTable[i].B.x + Xshift;
          newEdgeTable[i].B.y = newEdgeTable[i].B.y + Yshift;
          
          oldVal = newEdgeTable[i].B.x;
          newEdgeTable[i].B.x = newEdgeTable[i].B.x * cos(r) - newEdgeTable[i].B.y * sin(r);
          newEdgeTable[i].B.y = oldVal * sin(r) + newEdgeTable[i].B.y * cos(r);
          
          newEdgeTable[i].B.x = newEdgeTable[i].B.x - Xshift;
          newEdgeTable[i].B.y = newEdgeTable[i].B.y - Yshift;
          
          Xshift = -pivots.x;
          Yshift = -pivots.y;
          
          newEdgeTable[i].B.x = newEdgeTable[i].B.x + Xshift;
          newEdgeTable[i].B.y = newEdgeTable[i].B.y + Yshift; 
          
          newEdgeTable[i].B.x = newEdgeTable[i].B.x * sx;
          newEdgeTable[i].B.y = newEdgeTable[i].B.y * sy;
          
          newEdgeTable[i].B.x = newEdgeTable[i].B.x - Xshift;
          newEdgeTable[i].B.y = newEdgeTable[i].B.y - Yshift;          
    }    
    
    initwindow(1280, 720, "Polygon Transformation");
    
    /* Drawing original figure */
    outtextxy(1100, fy(680), "Original figure");
    for(i = 0; i < numofedges; ++i)
          line(edgeTable[i].A.x, fy(edgeTable[i].A.y), edgeTable[i].B.x, fy(edgeTable[i].B.y));
                          
    setcolor(LIGHTRED);
    /* Drawing transformed figure */
    outtextxy(1100, fy(650), "Transformed figure");
    for(i = 0; i < numofedges; ++i) 
          line(newEdgeTable[i].A.x, fy(newEdgeTable[i].A.y), newEdgeTable[i].B.x, fy(newEdgeTable[i].B.y));
    
    while(!kbhit());   /* hold the window open until a key is pressed */
    closegraph();
    return 0;
}

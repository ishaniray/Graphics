/* This program is an implementation of the Scan-Line Polygon Filling Algorithm. */

#include <stdio.h>
#include <graphics.h>

/* Structure definitions */
typedef struct point
{
        int x;              /* x-coordinate of a point */
        int y;              /* y-coordinate of the point */
} Point;

typedef struct edge
{
        Point A;            /* A and B are the two endpoints of an edge */
        Point B;
        float slope;        /* slope of the edge (line) */
        bool isVertical;    /* flag indicating whether or not the edge is a vertical line */
        int ymin;           /* minimum y-value of the edge */
        int ymax;           /* maximum y-value of the edge */
} Edge;

/* Function prototypes */
void fillPoly(Edge*, int, int, int, int);
void qsort(Point*, int, int);
int partition(Point *intersectionPoints, int, int);
 
int main(void)
{
    int n, i, fillCol, borderCol, minY = 720, maxY = 0;    /* minimum and maximum y-values of viewport are 0px and 720px respectively; minY and maxY initialised accordingly */
    Point *vertices;
    Edge *edges;
    
    printf("How many vertices does the polygon have?\n");
    scanf("%d", &n);    /* n = number of vertices / number of edges */
    while(n < 3)
    {
            printf("\n\nA polygon must have at least 3 vertices. Please try again:\n");
            scanf("%d", &n);
    }
    vertices = (Point*)malloc(n * sizeof(Point));    /* creating an array of vertices */
    edges = (Edge*)malloc(n * sizeof(Edge));         /* creating an array of edges */
    
    printf("\n\nEnter the co-ordinates of the vertices (x, y pairs) sequentially:\n[Please note that origin lies at the top-left corner of the viewport.]");
    for(i = 0; i < n; ++i)
    {
          printf("\n\nEnter x: ");
          scanf("%d", &vertices[i].x);
          printf("\nEnter y: ");
          scanf("%d", &vertices[i].y);
          
          /* Update minY / maxY so that eventually, we end up with the minimum and maximum y-values of the subject polygon. We'll work with scan-lines only within that range. */
          if(vertices[i].y < minY)
              minY = vertices[i].y;
          if(vertices[i].y > maxY)
              maxY = vertices[i].y;
    }
    
    printf("\n\nCOLOUR CODES:\nBLACK = 0; BLUE = 1; GREEN = 2; CYAN = 3; RED = 4; MAGENTA = 5; BROWN = 6; LIGHTGRAY = 7; DARKGRAY = 8;\nLIGHTBLUE = 9; LIGHTGREEN = 10; LIGHTCYAN = 11; LIGHTRED = 12; LIGHTMAGENTA = 13; YELLOW = 14; WHITE = 15");
    
    printf("\n\nPick a fill-colour: ");
    scanf("%d", &fillCol);
    while(fillCol < 1 || fillCol > 15)
    {
        printf("\nWrong input! Try again: ");
        scanf("%d", &fillCol);
    }
    printf("\n\nPick a border-colour: ");
    scanf("%d", &borderCol);
    while(fillCol < 1 || fillCol > 15)
    {
        printf("\nWrong input! Try again: ");
        scanf("%d", &borderCol);
    }
    
    for(i = 0; i < n; ++i)
    {
          /* Populating the 'edges' array: an edge is a link between two subsequent vertices */
          edges[i].A = vertices[i];
          edges[i].B = vertices[(i + 1) % n];
          
          if((edges[i].B.x - edges[i].A.x) != 0)    /* the edge is not a vertical line */
          {
              edges[i].slope = (edges[i].B.y - edges[i].A.y) / ((edges[i].B.x - edges[i].A.x) * 1.0);    /* calculate slope */
              edges[i].isVertical = false;
          }
          else    /* the edge is a vertical line */
              edges[i].isVertical = true;
          
          /* Noting minimum and maximum y-values of each edge */    
          if(edges[i].A.y <= edges[i].B.y)
          {
              edges[i].ymin = edges[i].A.y;
              edges[i].ymax = edges[i].B.y;
          }
          else
          {
              edges[i].ymin = edges[i].B.y;
              edges[i].ymax = edges[i].A.y;
          }
    }
    
    initwindow(1280, 720, "Scan-Line Polygon Fill");    /* Viewport dimensions: 1280px x 720px */
    outtextxy(525, 50, "SCAN-LINE POLYGON FILL");
          
    fillPoly(edges, n, minY, maxY, fillCol);    /* render the polygon in specified fill-colour */
    
    /* Draw the boundaries of the polygon in border-colour */
    setcolor(borderCol);
    for(i = 0; i < n; ++i)
          line(edges[i].A.x, edges[i].A.y, edges[i].B.x, edges[i].B.y);
    
    while(!kbhit());    /* hold the window open until a key is pressed */
    closegraph();
    return 0;
}

/* Function implementing scan-line polygon-filling algorithm */
void fillPoly(Edge *edges, int n, int minY, int maxY, int fillCol)
{
     Point *intersectionPoints;
     int i, j, Y;
     
     intersectionPoints = (Point*)malloc(n * sizeof(Point));    /* creating an array of intersection points of size 'n' */
     
     for(Y = minY; Y <= maxY; ++Y)    /* for each scan-line */
     {
           j = 0;
           
           for(i = 0; i < n; ++i)    /* for each edge */
           {
                 if(edges[i].ymin > Y || edges[i].ymax < Y || (!edges[i].isVertical && edges[i].slope == 0))   /* if an edge lies totally below the scan-line / above the scan-line, or, is a horizontal line */
                     continue;    /* ignore current edge and move on to the next iteration */
                     
                 else if(edges[i].isVertical)   /* if the edge is a vertical line */
                 {
                     intersectionPoints[j].x = edges[i].A.x;    /* x-value of intersection point is same as the constant x-value of the vertical line */
                     intersectionPoints[j].y = Y;               /* y-value of intersection point = y-value of scan-line */
                 }
                 else   /* for all other edges */
                 {
                     intersectionPoints[j].y = Y;    /* y-value of intersection point = y-value of scan-line */
                     intersectionPoints[j].x = (int)(edges[i].A.x - ((edges[i].A.y - intersectionPoints[j].y) / edges[i].slope));   /* y-value derived from value of slope */
                 }
                 
                 /* Checking for local maxima/minima and providing for the same */
                 if((intersectionPoints[j].x == edges[i].A.x && intersectionPoints[j].y == edges[i].A.y) || (intersectionPoints[j].x == edges[i].B.x && intersectionPoints[j].y == edges[i].B.y))    /* if intersectionPoints[j] is a vertex */
                 {
                     if(intersectionPoints[j].y == edges[i].ymax)
                     {
                         if(intersectionPoints[j].y == edges[(i + 1) % n].ymin)    /* if the other edge incident on the vertex (i.e., the (i + 1)th edge, since input was taken sequentially) lies on the opposite side of the scan-line */
                         {
                             /* vertex is a local maxima/minima */
                             if(i == n - 1) /* if this is the last edge in the loop */
                                 --j;       /* ...the other edge has already been accounted for, therefore, skip this one. */
                             else    
                                 ++i;    /* skip next edge */
                         }
                     }
                     else    /* intersectionPoints[j].y == edges[i].ymin */
                     {
                         if(intersectionPoints[j].y == edges[(i + 1) % n].ymax)    /* if the other edge incident on the vertex (i.e., the (i + 1)th edge, since input was taken sequentially) lies on the opposite side of the scan-line */
                         {
                             /* vertex is a local maxima/minima */
                             if(i == n - 1) /* if this is the last edge in the loop */
                                 --j;       /* ...the other edge has already been accounted for, therefore, skip this one. */
                             else    
                                 ++i;    /* skip next edge */
                         }                         
                     }
                 }
                 
                 ++j;
           }
           
           qsort(intersectionPoints, 0, j - 1);    /* sort intersectionPoints according to x-values (in a non-decreasing order) */
           
           /* Plot the points between intersection points with fill-colour (intersection points will be plotted later as part of polygon-boundaries) */
           setcolor(fillCol);
           for(i = 0; (i + 1) < j; i = i + 2)
                 line(intersectionPoints[i].x + 1, intersectionPoints[i].y, intersectionPoints[i + 1].x - 1, intersectionPoints[i + 1].y);
     }
}

/* Functions implementing Quick Sort on the array of intersection points */
void qsort(Point *intersectionPoints, int low, int high)
{
     int pivotPos;
     
     if(low < high)
     {
            pivotPos = partition(intersectionPoints, low, high);
            qsort(intersectionPoints, low, pivotPos - 1);
            qsort(intersectionPoints, pivotPos + 1, high);
     }
}
int partition(Point *intersectionPoints, int low, int high)
{
     int lastSmall, i, mid;
     Point temp, pivot;
     
     mid = low + (high - low) / 2;
     temp = intersectionPoints[low];
     intersectionPoints[low] = intersectionPoints[mid];
     intersectionPoints[mid] = temp;
     pivot = intersectionPoints[low];
     lastSmall = low;
     
     for(i = low + 1; i <= high; ++i)
     {
           if(intersectionPoints[i].x < pivot.x)
           {
                   ++lastSmall;
                   temp = intersectionPoints[lastSmall];
                   intersectionPoints[lastSmall] = intersectionPoints[i];
                   intersectionPoints[i] = temp;
           }
     }
     
     intersectionPoints[low] = intersectionPoints[lastSmall];
     intersectionPoints[lastSmall] = pivot;
     
     return lastSmall;
}

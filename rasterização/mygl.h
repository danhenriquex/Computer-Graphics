#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

struct Color {

    int r, g, b, a;

};

void DrawTriangle(int x0, int y0, Color c0, int x1, int y1, Color c1, int x2, int y2, Color c2);
void Putpixel(int x, int y, Color c);
void Drawline(int x0, int y0,Color c0, int x1, int y1, Color c1);
Color InterpolaCor(float delta, Color c0, Color c1);


void Putpixel(int x, int y, Color c) {

    int pixel = x * 4 + y *IMAGE_WIDTH * 4;
    FBptr[pixel] = c.r;
    FBptr[pixel + 1] = c.g;
    FBptr[pixel + 2] = c.b;
    FBptr[pixel + 3] = c.a;

}

Color InterpolaCor(float delta, Color c0, Color c1) {

    Color c;

    c.r = c0.r - delta*(c1.r - c0.r);
    c.g = c0.g - delta*(c1.g - c0.g);
    c.b = c0.b - delta*(c1.b - c0.b);

    return c;

}

void Drawline(int x0, int y0,Color c0, int x1, int y1, Color c1) {

    int dx = x1 - x0;
    int dy = y1 - y0;
    int i = 0;
    float delta;
    Color c;
    c.r = 255;

    if(dx >= dy && dy >= 0 && dx > 0) { //Para o octante 0

        int d =2*dy - dx;
        int incr_e = 2*dy;
        int incr_ne = 2*(dy - dx);
        int x = x0;
        int y = y0;

        Putpixel(x, y, c);

        while(x < x1) {

            if(d <= 0) {

                d += incr_e;
                x++;

            }else {

                d += incr_ne;
                x++;
                y++;
            }
            i++;
            delta = ((float)i)/((float)dx);
            InterpolaCor(delta, c0, c1);
            Putpixel(x, y, c);

        }
    }else if(dy > dx && dy > 0 && dx > 0) { //Para o octante 1

        int d = 2 * dx-dy;
        int incr_e = 2*dx;
        int incr_ne = 2*(dx - dy);
        int x = x0;
        int y = y0;

        Putpixel(x, y, c);

        while(y < y1) {

            if(d <= 0) {

                d += incr_e;
                y++;

            }else {

                d += incr_ne;
                y++;
                x++;

            }
            i++;
            delta = ((float)i)/((float)dy);
            InterpolaCor(delta, c0, c1);
            Putpixel(x, y, c);

        }
    }else if(dy > -dx && dy > 0 && dx <= 0) { //Para o octante 2

        dx = -dx;
        int d = 2 * dx-dy;
        int incr_e = 2*dx;
        int incr_ne = 2*(dx-dy);
        int x = x0;
        int y = y0;

        Putpixel(x, y, c);

        while(y < y1) {

            if(d <= 0) {

                d += incr_e;
                y++;

            }else {

                d+= incr_ne;
                y++;
                x--;
            }
            i++;
            delta = ((float)i)/((float)dy);
            InterpolaCor(delta, c0, c1);
            Putpixel(x, y, c);
            
        }
    }else if(-dx >= dy && dx < 0 && dy > 0) { //Para o octante 3

        dx = -dx;
        int d = 2*dy-dx;
        int incr_e = 2*dy;
        int incr_ne = 2*(dy-dx);
        int x = x0;
        int y = y0;

        Putpixel(x, y, c);

        while(x > x1) {

            if(d <= 0) {

                d += incr_e;
                x--;

            }else {

                d+= incr_ne;
                x--;
                y++;
            }
            i++;
            delta = ((float)i)/((float)dx);
            InterpolaCor(delta, c0, c1);
            Putpixel(x, y, c);

        }
        
    }else if(-dx >= -dy && dx < 0 && dy < 0) { //Para o octante 4

        dx = -dx;
        dy = -dy;
        int d = 2 * dy-dx;
        int incr_e = 2*dy;
        int incr_ne = 2*(dy - dx);
        int x = x0;
        int y = y0;

        Putpixel(x, y, c);

        while(x > x1) {

            if(d <= 0) {

                d += incr_e;
                x--;

            }else {

                d += incr_ne;
                x--;
                y--;
            }
            i++;
            delta = ((float)i)/((float)dx);
            InterpolaCor(delta, c0, c1);
            Putpixel(x, y, c);

        }
        
    }else if(-dy > -dx && dy < 0 && dx < 0) { //Para o octante 5

        dy = -dy;
        dx = -dx;
        int d =2* dx-dy;
        int incr_e = 2*dx;
        int incr_ne = 2*(dx - dy);
        int x = x0;
        int y = y0;

        Putpixel(x, y, c);

        while(y > y1) {

            if(d <= 0) {

                d += incr_e;
                y--;

            }else {

                d += incr_ne;
                y--;
                x++;
            }
            i++;
            delta = ((float)i)/((float)dy);
            InterpolaCor(delta, c0, c1);
            Putpixel(x, y, c);

        }

    }else if(-dy > dx && dy < 0 && dx > 0) { //Para o octante 6

        dy = -dy;
        int d = 2*dx-dy;
        int incr_e = 2*dx;
        int incr_ne = 2*(dx-dy);
        int x = x0;
        int y = y0;

        Putpixel(x, y, c);

        while(y > y1) {

            if(d <= 0) {

                d += incr_e;
                y--;

            }else {

                d+= incr_ne;
                y--;
                x++;
            }
            i++;
            delta = ((float)i)/((float)dy);
            InterpolaCor(delta, c0, c1);
            Putpixel(x, y, c);

        }

    }else if(dx >= -dy && dx > 0 && dy < 0) { //Para o octante 7

        dy = -dy;
        int d = 2 * dy-dx;
        int incr_e = 2*dy;
        int incr_ne = 2*(dy-dx);
        int x = x0;
        int y = y0;

        Putpixel(x, y, c);

        while(x < x1) {

            if(d <= 0) {

                d += incr_e;
                x++;

            }else {

                d+= incr_ne;
                x++;
                y--;
            }
            i++;
            delta = ((float)i)/((float)dx);
            InterpolaCor(delta, c0, c1);
            Putpixel(x, y, c);
            
        }

    }
    
}

void DrawTriangle(int x0, int y0, Color c0, int x1, int y1, Color c1, int x2, int y2, Color c2) {

    Drawline(x0,y0,c0,x1,y1,c1);
    Drawline(x0,y0,c1,x2,y2,c2);
    Drawline(x1,y1,c1,x2,y2,c2);
}



#endif // _MYGL_H_

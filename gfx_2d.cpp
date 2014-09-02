#include "gfx_2d.h"

const font_5x7 font_default = {
50,5,
{
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
{0b00100001,0b00001000,0b01000000,0b00000000,0b10000000},
{0b01010010,0b10010100,0b00000000,0b00000000,0b00000000},
{0b01010010,0b10111110,0b10101111,0b10101001,0b01000000},
{0b00100011,0b11101000,0b11100010,0b11111000,0b10000000},
{0b11000110,0b01000100,0b01000100,0b01001100,0b01100000},
{0b01100100,0b10101000,0b10001010,0b01001001,0b10100000},
{0b01100001,0b00010000,0b00000000,0b00000000,0b00000000},
{0b00010001,0b00010000,0b10000100,0b00010000,0b01000000},
{0b01000001,0b00000100,0b00100001,0b00010001,0b00000000},
{0b00000001,0b00101010,0b11101010,0b10010000,0b00000000},
{0b00000001,0b00001001,0b11110010,0b00010000,0b00000000},
{0b00000000,0b00000000,0b00000110,0b00010001,0b00000000},
{0b00000000,0b00000001,0b11110000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00110001,0b10000000},
{0b00000000,0b01000100,0b01000100,0b01000000,0b00000000},
{0b01110100,0b01100111,0b01011100,0b11000101,0b11000000},
{0b00100011,0b00001000,0b01000010,0b00010001,0b11000000},
{0b01110100,0b01000010,0b00100010,0b00100011,0b11100000},
{0b11111000,0b10001000,0b00100000,0b11000101,0b11000000},
{0b00010001,0b10010101,0b00101111,0b10001000,0b01000000},
{0b11111100,0b00111100,0b00010000,0b11000101,0b11000000},
{0b00110010,0b00100001,0b11101000,0b11000101,0b11000000},
{0b11111000,0b01000100,0b01000100,0b00100000,0b00000000},
{0b01110100,0b01100010,0b11101000,0b11000101,0b11000000},
{0b01110100,0b01100010,0b11110000,0b10001001,0b10000000},
{0b00000011,0b00011000,0b00000110,0b00110000,0b00000000},
{0b00000011,0b00011000,0b00000110,0b00010001,0b00000000},
{0b00010001,0b00010001,0b00000100,0b00010000,0b01000000},
{0b00000000,0b00111110,0b00001111,0b10000000,0b00000000},
{0b01000001,0b00000100,0b00010001,0b00010001,0b00000000},
{0b01110100,0b01000010,0b00100010,0b00000000,0b10000000},
{0b01110100,0b01000010,0b11011010,0b11010101,0b11000000},
{0b01110100,0b01100011,0b00011111,0b11000110,0b00100000},
{0b11110100,0b01100011,0b11101000,0b11000111,0b11000000},
{0b01110100,0b01100001,0b00001000,0b01000101,0b11000000},
{0b11100100,0b10100011,0b00011000,0b11001011,0b10000000},
{0b11111100,0b00100001,0b11101000,0b01000011,0b11100000},
{0b11111100,0b00100001,0b11101000,0b01000010,0b00000000},
{0b01110100,0b01100001,0b01111000,0b11000101,0b11100000},
{0b10001100,0b01100011,0b11111000,0b11000110,0b00100000},
{0b01110001,0b00001000,0b01000010,0b00010001,0b11000000},
{0b00111000,0b10000100,0b00100001,0b01001001,0b10000000},
{0b10001100,0b10101001,0b10001010,0b01001010,0b00100000},
{0b10000100,0b00100001,0b00001000,0b01000011,0b11100000},
{0b10001110,0b11101011,0b01011000,0b11000110,0b00100000},
{0b10001100,0b01110011,0b01011001,0b11000110,0b00100000},
{0b01110100,0b01100011,0b00011000,0b11000101,0b11000000},
{0b11110100,0b01100011,0b11101000,0b01000010,0b00000000},
{0b01110100,0b01100011,0b00011010,0b11001001,0b10100000},
{0b11110100,0b01100011,0b11101010,0b01001010,0b00100000},
{0b01111100,0b00100000,0b11100000,0b10000111,0b11000000},
{0b11111001,0b00001000,0b01000010,0b00010000,0b10000000},
{0b10001100,0b01100011,0b00011000,0b11000101,0b11000000},
{0b10001100,0b01100011,0b00011000,0b10101000,0b10000000},
{0b10001100,0b01100011,0b01011010,0b11010101,0b01000000},
{0b10001100,0b01010100,0b01000101,0b01000110,0b00100000},
{0b10001100,0b01100010,0b10100010,0b00010000,0b10000000},
{0b11111000,0b01000100,0b01000100,0b01000011,0b11100000},
{0b01110010,0b00010000,0b10000100,0b00100001,0b11000000},
{0b10001010,0b10111110,0b01001111,0b10010000,0b10000000},
{0b01110000,0b10000100,0b00100001,0b00001001,0b11000000},
{0b00100010,0b10100010,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00000000,0b00000000,0b00000011,0b11100000},
{0b01000001,0b00000100,0b00000000,0b00000000,0b00000000},
{0b00000000,0b00011100,0b00010111,0b11000101,0b11100000},
{0b10000100,0b00100001,0b01101100,0b11000111,0b11000000},
{0b00000000,0b00011101,0b00001000,0b01000101,0b11000000},
{0b00001000,0b01000010,0b11011001,0b11000101,0b11100000},
{0b00000000,0b00011101,0b00011111,0b11000001,0b11000000},
{0b00110010,0b01010001,0b10000100,0b00100001,0b00000000},
{0b00000011,0b11100011,0b00010111,0b10000101,0b11000000},
{0b10000100,0b00101101,0b10011000,0b11000110,0b00100000},
{0b00000001,0b00000000,0b01000010,0b00010000,0b10000000},
{0b00000000,0b10000000,0b01100001,0b00001010,0b01001100},
{0b10000100,0b00100101,0b01001100,0b01010010,0b01000000},
{0b01100001,0b00001000,0b01000010,0b00010001,0b11000000},
{0b00000000,0b00000001,0b10101010,0b11010110,0b00110001},
{0b00000000,0b00101101,0b10011000,0b11000110,0b00100000},
{0b00000000,0b00011101,0b00011000,0b11000101,0b11000000},
{0b00000000,0b00111101,0b00011111,0b01000010,0b00000000},
{0b00000000,0b00011011,0b00110111,0b10000100,0b00100000},
{0b00000000,0b00101101,0b10011000,0b01000010,0b00000000},
{0b00000000,0b00011101,0b00000111,0b00000111,0b11000000},
{0b01000010,0b00111000,0b10000100,0b00100100,0b11000000},
{0b00000000,0b00100011,0b00011000,0b11001101,0b10100000},
{0b00000000,0b00100011,0b00011000,0b10101000,0b10000000},
{0b00000000,0b00100011,0b00011010,0b11010101,0b01000000},
{0b00000000,0b00100010,0b10100010,0b00101010,0b00100000},
{0b00000000,0b00100011,0b00010111,0b10000101,0b11000000},
{0b00000000,0b00111110,0b00100010,0b00100011,0b11100000},
{0b00010001,0b00001000,0b10000010,0b00010000,0b01000000},
{0b00100001,0b00001000,0b01000010,0b00010000,0b10000000},
{0b01000001,0b00001000,0b00100010,0b00010001,0b00000000},
{0b00000001,0b00000101,0b11110001,0b00010000,0b00000000},
}
};

void gfx_2d_clear(void)
{
    for(int x = 0; x < 96; x++)
    {
        for(int y = 0; y < 64; y++)
        {
            framebuffer[x][y] = 0xff;
        }
    }
}

void gfx_2d_pixel(int x, int y, int color)
{
    if(x >= 0 && y >= 0 && x < 96 && y < 64)
    {
        if(color >= 0)
        {
            framebuffer[x][y] = color;
        }
        else if(color != -1)
        {
            if(color == -2)
            {
                framebuffer[x][y] = 255 - framebuffer[x][y];
            }
        }
        //color = -1 : transparent
    }
}



void gfx_2d_character(int character, int x, int y, int textcolor, int backgroundcolor)
{
    int cnt = 0;
    for(int ycnt = y; ycnt < y + 7; ycnt ++)
    {
        for(int xcnt = x; xcnt < x + 5; xcnt ++)
        {   
            if((font_default.chardata[character][cnt / 8] >> 7 - (cnt % 8)) & 1)
            {
                gfx_2d_pixel(xcnt, ycnt, textcolor);
            }
            else
            {
                gfx_2d_pixel(xcnt, ycnt, backgroundcolor);
            }
            cnt ++;
        }
    }
}

void gfx_2d_string(const char string[], int length, int x, int y, int textcolor, int backgroundcolor)
{
    for(int i = 0; i < length; i++)
    {
        gfx_2d_character(string[i], x + 6 * i, y, textcolor, backgroundcolor);
    }
}

void gfx_2d_line(int x0, int y0, int x1, int y1, int color) 
{
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2;
 
    while(1)
    {
        gfx_2d_pixel(x0,y0,color);
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) 
        {
            err += dy; x0 += sx;
        } 
        if (e2 < dx)
        { 
            err += dx; y0 += sy; 
        } 
    }
}


void gfx_2d_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color)
{
    gfx_2d_line(x0,y0,x1,y1,color);
    gfx_2d_line(x1,y1,x2,y2,color);
    gfx_2d_line(x2,y2,x0,y0,color);
}


void gfx_2d_fill_BottomFlatTriangle(point point1, point point2, point point3, int color)
{
    float invslope1 = (point2.x - point1.x) / (point2.y - point1.y);
    float invslope2 = (point3.x - point1.x) / (point3.y - point1.y);

    if(invslope1 > invslope2)
    {
        float temp = invslope1;
        invslope1 = invslope2;
        invslope2 = temp;
    }

    float curx1 = point1.x;
    float curx2 = point1.x;

    for (int scanlineY = point1.y; scanlineY <= point2.y; scanlineY++)
    {
        for(int i = curx1; i <= curx2; i++)
        {
            gfx_2d_pixel(i, scanlineY, color);
        }
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void gfx_2d_fill_TopFlatTriangle(point point1, point point2, point point3, int color)
{
    float invslope1 = (point3.x - point1.x) / (point3.y - point1.y);
    float invslope2 = (point3.x - point2.x) / (point3.y - point2.y);
    
    if(invslope1 < invslope2)
    {
        float temp = invslope1;
        invslope1 = invslope2;
        invslope2 = temp;
    }

    float curx1 = point3.x;
    float curx2 = point3.x;

    for (int scanlineY = point3.y; scanlineY > point1.y; scanlineY--)
    {
        curx1 -= invslope1;
        curx2 -= invslope2;
        for(int i = curx1; i <= curx2; i++)
        {
            gfx_2d_pixel(i, scanlineY, color);
        }
    }
}

void gfx_2d_fill_triangle(point point1, point point2, point point3, int color)
{
    if (point1.y < point2.y) 
    {
        if (point3.y < point1.y) 
        {
            int tempx = point1.x;
            int tempy = point1.y;
            point1.x = point3.x;
            point1.y = point3.y;
            point3.x = tempx;
            point3.y = tempy;
        }
    } 
    else 
    {
        if (point2.y < point3.y) 
        {
            int tempx = point1.x;
            int tempy = point1.y;
            point1.x = point2.x;
            point1.y = point2.y;
            point2.x = tempx;
            point2.y = tempy;
        }
        else 
        {
            int tempx = point1.x;
            int tempy = point1.y;
            point1.x = point3.x;
            point1.y = point3.y;
            point3.x = tempx;
            point3.y = tempy;
        }
    }
    if(point3.y<point2.y) 
    {
        int tempx = point2.x;
        int tempy = point2.y;
        point2.x = point3.x;
        point2.y = point3.y;
        point3.x = tempx;
        point3.y = tempy;
    }

  if (point2.y == point3.y)
  {
    gfx_2d_fill_BottomFlatTriangle(point1, point2, point3, color);
  }
 

  else if (point1.y == point2.y)
  {
    gfx_2d_fill_TopFlatTriangle(point1, point2, point3, color);
  } 
  else
  {
    
    point point4 = {(int)(point1.x + ((float)(point2.y - point1.y) / (float)(point3.y - point1.y)) * (point3.x - point1.x)), point2.y};

    gfx_2d_fill_BottomFlatTriangle(point1, point2, point4, color);
    gfx_2d_fill_TopFlatTriangle(point2, point4, point3, color);
  }
}

void gfx_2d_rectangle(int x0, int y0, int x1, int y1, int color)
{
    gfx_2d_line(x0,y0,x0,y1,color);
    gfx_2d_line(x0,y0,x1,y0,color);
    gfx_2d_line(x1,y1,x0,y1,color);
    gfx_2d_line(x1,y1,x1,y0,color);
}

void gfx_2d_fill_rectangle(int x0, int y0, int x1, int y1, int color)
{
    if(x0 > x1)
    {
        int temp = x0;
        x0 = x1;
        x1 = temp;
    }
    if(y0 > y1)
    {
        int temp = y0;
        y0 = y1;
        y1 = temp;
    }

    for(int j = y0; j <= y1; j++)
    {
        for(int i = x0; i <= x1; i++)
        {
            gfx_2d_pixel(i,j,color);
        }
    }
}

void gfx_2d_circle(point centre, float radius, int color)
{
    for(float i = 0; i < radius * 0.707106; i ++)
    {
        int root = sqrtf(radius*radius - i*i);
        if(i == 0 && radius > 5)
        {
            root --;
        }
        gfx_2d_pixel(centre.x + i, centre.y + root, color);
        gfx_2d_pixel(centre.x + i, centre.y - root, color);
        gfx_2d_pixel(centre.x - i, centre.y + root, color);
        gfx_2d_pixel(centre.x - i, centre.y - root, color);
        gfx_2d_pixel(centre.x + root, centre.y + i, color);
        gfx_2d_pixel(centre.x - root, centre.y + i, color);
        gfx_2d_pixel(centre.x + root, centre.y - i, color);
        gfx_2d_pixel(centre.x - root, centre.y  - i, color);
    }
}

void gfx_2d_fill_circle(point centre, float radius, int bordercolor, int fillcolor)
{
    for(float i = 0; i < radius * 0.707106; i ++)
    {
        int root = sqrtf(radius*radius - i*i);
        if(i == 0 && radius > 5)
        {
            root --;
        }       
        for(int curx = centre.x - i; curx <= centre.x + i; curx ++)
        {
            gfx_2d_pixel(curx, centre.y + root, fillcolor);
            gfx_2d_pixel(curx, centre.y - root, fillcolor);
        }
        for(int curx = centre.x - root; curx <= centre.x + root; curx ++)
        {
            gfx_2d_pixel(curx, centre.y - i, fillcolor);
            gfx_2d_pixel(curx, centre.y + i, fillcolor);
        }
    }
    if(bordercolor != fillcolor)
    {
        gfx_2d_circle(centre, radius, bordercolor);
    }
}

int gfx_2d_menu_simple(const char *entries, int number_of_entries)
{
    int selected = 1;
    int begin = 0;
    int setbefore = 0;

    while(1)
    {
        int index = 0;
        int y = 1;
        int charcnt = 0;

        float scrollbar_length = 230 / number_of_entries;
        float scrollbar_beginning = (46 - scrollbar_length) / (number_of_entries - 5) * (begin);
        if(number_of_entries <= 5)
        {
            scrollbar_beginning = 0;
            scrollbar_length = 46;
        }

        gfx_2d_clear();

        gfx_2d_fill_rectangle(0,0,95,8,0);
        gfx_2d_rectangle(90,14,95,62,0);
        gfx_2d_fill_rectangle(91,15 + scrollbar_beginning,94,15 + scrollbar_beginning + scrollbar_length,60);
        
        
        while(entries[index] != 0)
        {
            gfx_2d_character(entries[index], 1 + 6 * charcnt, y, 255, -1);
            index ++;
            charcnt ++;
        }
        index ++;
        y += 14;
        for(int i = 0; i < begin; i ++)
        {
            while(entries[index] != 0)
            {
                index ++;
            }
            index ++;
        }
        for(int i = begin; i < number_of_entries && i < begin + 5; i ++)
        {
            index ++;
            charcnt = 0;
            if(i + 1 == selected)
            {
                gfx_2d_fill_rectangle(0,y-1,88,y+7,120);
            }
            while(entries[index] != 0)
            {
                gfx_2d_character(entries[index], 1 + 6 * charcnt, y, 0, -1);
                index ++;
                charcnt ++;
            }
            index ++;
            y += 10;
        }
        LINK_transfer_framedata();
        if(keys == key_up && selected > 1 && setbefore == 0)
        { 
            selected --;
            if(selected <= begin)
            {
                begin = selected - 1;
            }
            setbefore = 1;
        }
        if(keys == key_down && selected < number_of_entries && setbefore == 0)
        {
            selected ++;
            if(selected > begin + 5)
            {
                begin = selected - 5;
            }
            setbefore = 1;
        }
        if(keys == 0)
        {
            setbefore = 0;
        }
        if(keys == key_enter)
        {
            while(keys == key_enter)
            {
                LINK_transfer_framedata();
            }
            gfx_2d_clear();
            return selected;
        }
    }
}


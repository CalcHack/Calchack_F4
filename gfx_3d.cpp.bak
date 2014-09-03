#include "gfx_3d.h"
#include "gfx_2d.h"
#include "stm32f4xx_conf.h"
#include "math.h"

float zbuffer[96][64];

const int cubecount = 6;

int brightness_3d = 200;

uint32_t polygon_buffer_next_ID = 1;
uint16_t polygon_buffer_next_entry = 0;
uint16_t vertice_buffer_next_entry = 0;
uint16_t texture_buffer_next_entry = 0;

int cnt = 0;

vector rotation[cubecount] = {{1,2,3}};



polygon_bfr polygon_buffer[500];
vertice_bfr vertice_buffer[500];
texture_bfr texture_buffer[5];

vertice activevertice;

obj3D_Box cube[cubecount];
Camera cam1;


void gfx_3d_pixel(int x, int y, float z, int color)
{
    if(x >= 0 && y >= 0 && x < 96 && y < 64)
    {
        if(zbuffer[x][y] < z && zbuffer[x][y] < 0)
        {
            zbuffer[x][y] = z;
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
}

void gfx_3d_fill_BottomFlatTriangle(vertice point1, vertice point2, vertice point3, int color)
{
    float invslope1 = (point2.x - point1.x) / (point2.y - point1.y);
    float invslope2 = (point3.x - point1.x) / (point3.y - point1.y);
    float invslope1_z = (point2.z - point1.z) / (point2.y - point1.y);
    float invslope2_z = (point3.z - point1.z) / (point3.y - point1.y);

    if(invslope1 > invslope2)
    {
        float temp = invslope1;
        invslope1 = invslope2;
        invslope2 = temp;
    }
    if(invslope1_z > invslope2_z)
    {
        float temp = invslope1_z;
        invslope1_z = invslope2_z;
        invslope2_z = temp;
    }


    float curx1 = point1.x;
    float curx2 = point1.x;
    float curz1 = point1.z;
    float curz2 = point1.z;

    for (int scanlineY = point1.y; scanlineY <= point2.y; scanlineY++)
    {
        for(int x = curx1; x <= curx2; x++)
        {
            float curxdiff = curx2 - x;
            float curzdiff = curz2 - curz1;
            float z;
            if(curxdiff == 0)
            {
                z = curz1;
            }
            else
            {
                z = curz1 + (curzdiff) * (x - curx1) / (curxdiff);
            }           
            gfx_3d_pixel(x, scanlineY, z, color);
        }
        curx1 += invslope1;
        curx2 += invslope2;
        curz1 += invslope1_z;
        curz2 += invslope2_z;
    }
}

void gfx_3d_fill_TopFlatTriangle(vertice point1, vertice point2, vertice point3, int color)
{
    float invslope1 = (point3.x - point1.x) / (point3.y - point1.y);
    float invslope2 = (point3.x - point2.x) / (point3.y - point2.y);
    float invslope1_z = (point3.z - point1.z) / (point3.y - point1.y);
    float invslope2_z = (point3.z - point2.z) / (point3.y - point2.y);

    if(invslope1 < invslope2)
    {
        float temp = invslope1;
        invslope1 = invslope2;
        invslope2 = temp;
    }
    if(invslope1_z < invslope2_z)
    {
        float temp = invslope1_z;
        invslope1_z = invslope2_z;
        invslope2_z = temp;
    }
    
    float curx1 = point3.x;
    float curx2 = point3.x;
    float curz1 = point3.z;
    float curz2 = point3.z;

    if((point3.y - point1.y) == 0)
    {
        curx1 = curx2;
    }
    

    for (int scanlineY = point3.y; scanlineY > point1.y; scanlineY--)
    {
        curx1 -= invslope1;
        curx2 -= invslope2;
        curz1 -= invslope1_z;
        curz2 -= invslope2_z;
        for(int x = curx1; x <= curx2; x++)
        {
            float curxdiff = curx2 - x;
            float curzdiff = curz2 - curz1;
            float z;
            if(curxdiff == 0)
            {
                z = curz1;
            }
            else
            {
                z = curz1 + (curzdiff) * (x - curx1) / (curxdiff);
            }           
            gfx_3d_pixel(x, scanlineY, z, color);
        }
    }
}

void gfx_3d_fill_triangle(vertice point1, vertice point2, vertice point3, int color)
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
        gfx_3d_fill_BottomFlatTriangle(point1, point2, point3, color);
    }


    else if (point1.y == point2.y)
    {
        gfx_3d_fill_TopFlatTriangle(point1, point2, point3, color);
    } 
    else
    { 
        vertice point4 = {(point1.x + ((point3.x - point1.x) / (point3.y - point1.y) * (point2.y - point1.y))), point2.y, (point1.z + ((point3.z - point1.z) / (point3.y - point1.y) * (point2.y - point1.y)))};

        gfx_3d_fill_BottomFlatTriangle(point1, point2, point4, color);
        gfx_3d_fill_TopFlatTriangle(point2, point4, point3, color);
    }
}

void gfx_3d_texture_triangle(vertice point1, vertice point2, vertice point3, texture_bfr texture)
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

//    if (point2.y == point3.y)
//    {
//        gfx_3d_fill_BottomFlatTriangle(point1, point2, point3, color);
//    }
//
//
//    else if (point1.y == point2.y)
//    {
//        gfx_3d_fill_TopFlatTriangle(point1, point2, point3, color);
//    } 
//    else
//    { 
//        vertice point4 = {(point1.x + ((point3.x - point1.x) / (point3.y - point1.y) * (point2.y - point1.y))), point2.y, (point1.z + ((point3.z - point1.z) / (point3.y - point1.y) * (point2.y - point1.y)))};
//
//        gfx_3d_fill_BottomFlatTriangle(point1, point2, point4, color);
//        gfx_3d_fill_TopFlatTriangle(point2, point4, point3, color);
//    }
}

// Clamping values to keep them between 0 and 1
//float Clamp(float value, float min = 0, float max = 1)
//{
//    if(value <= max && value >= min)
//    {
//        return value;
//    }
//    if(value > max)
//    {
//        return max;
//    }
//    return min;
//}
//
// Interpolating the value between 2 vertices 
// min is the starting point, max the ending point
// and gradient the % between the 2 points
//float Interpolate(float min, float max, float gradient)
//{
//    return min + (max - min) * Clamp(gradient);
//}
//
//void ProcessScanLine(int y, vertice pa, vertice pb, vertice pc, vertice pd, int color)
//{
//    // Thanks to current y, we can compute the gradient to compute others values like
//    // the starting x (sx) and ending x (ex) to draw between
//    // if pa.y == pb.y or pc.y == pd.y, gradient is forced to 1
//    float gradient1 = pa.y != pb.y ? (y - pa.y) / (pb.y - pa.y) : 1;
//    float gradient2 = pc.y != pd.y ? (y - pc.y) / (pd.y - pc.y) : 1;
//
//    int sx = (int)Interpolate(pa.x, pb.x, gradient1);
//    int ex = (int)Interpolate(pc.x, pd.x, gradient2);
//
//    // starting z & ending z
//    float z1 = Interpolate(pa.z, pb.z, gradient1);
//    float z2 = Interpolate(pc.z, pd.z, gradient2);
//
//    // drawing a line from left (sx) to right (ex) 
//    for (float x = sx; x < ex; x++)
//    {
//        float gradient = (x - sx) / (float)(ex - sx);
//
//        float z = Interpolate(z1, z2, gradient);
//
//        gfx_3d_pixel(x,y,z, color);
//    }
//}
//
//void gfx_3d_fill_triangle(vertice p1, vertice p2, vertice p3, int color)
//{
//    // Sorting the points in order to always have this order on screen p1, p2 & p3
//    // with p1 always up (thus having the y the lowest possible to be near the top screen)
//    // then p2 between p1 & p3
//    if (p1.y > p2.y)
//    {
//        vertice temp = p2;
//        p2 = p1;
//        p1 = temp;
//    }
//
//    if (p2.y > p3.y)
//    {
//        vertice temp = p2;
//        p2 = p3;
//        p3 = temp;
//    }
//
//    if (p1.y > p2.y)
//    {
//        vertice temp = p2;
//        p2 = p1;
//        p1 = temp;
//    }
//
//    // inverse slopes
//    float dP1P2, dP1P3;
//
//    // http://en.wikipedia.org/wiki/Slope
//    // Computing inverse slopes
//    if (p2.y - p1.y > 0)
//        dP1P2 = (p2.x - p1.x) / (p2.y - p1.y);
//    else
//        dP1P2 = 0;
//
//    if (p3.y - p1.y > 0)
//        dP1P3 = (p3.x - p1.x) / (p3.y - p1.y);
//    else
//        dP1P3 = 0;
//
//    // First case where triangles are like that:
//    // P1
//    // -
//    // -- 
//    // - -
//    // -  -
//    // -   - P2
//    // -  -
//    // - -
//    // -
//    // P3
//    if (dP1P2 > dP1P3)
//    {
//        for (int y = (int)p1.y; y <= (int)p3.y; y++)
//        {
//            if (y < p2.y)
//            {
//                ProcessScanLine(y, p1, p3, p1, p2, color);
//            }
//            else
//            {
//                ProcessScanLine(y, p1, p3, p2, p3, color);
//            }
//        }
//    }
//    // First case where triangles are like that:
//    //       P1
//    //        -
//    //       -- 
//    //      - -
//    //     -  -
//    // P2 -   - 
//    //     -  -
//    //      - -
//    //        -
//    //       P3
//    else
//    {
//        for (int y = (int)p1.y; y <= (int)p3.y; y++)
//        {
//            if (y < p2.y)
//            {
//                ProcessScanLine(y, p1, p2, p1, p3, color);
//            }
//            else
//            {
//                ProcessScanLine(y, p2, p3, p1, p3, color);
//            }
//        }
//    }
//}

vertice vertice_to_point(vertice vertice[0])
{
  vertice[0].x = vertice[0].x * 10000 / vertice[0].z;  
  vertice[0].y = vertice[0].y * 10000 / vertice[0].z;
  return vertice[0];
}

void BubbleSort(float a[], int b[], int array_size)
{
    int i, j, temp;
    for (i = 0; i < (array_size - 1); ++i)
    {
        for (j = 0; j < array_size - 1 - i; ++j )
        {
             if (a[j] > a[j+1])
             {
                  temp = a[j+1];
                  a[j+1] = a[j];
                  a[j] = temp;
                  temp = b[j+1];
                  b[j+1] = b[j];
                  b[j] = temp;
             }
        }
    }
}   

void drawpolygon(polygon_bfr polygon, float zoomlevel, int width, int height)
{
    uint16_t vertice_index = 0;
    while(vertice_buffer[vertice_index].unique_ID != polygon.unique_ID)
    {
        vertice_index ++;
    }
    
    
    vertice point1 = vertice_to_point(vertice_buffer[vertice_index + polygon.vertices[0]].vt);
    vertice point2 = vertice_to_point(vertice_buffer[vertice_index + polygon.vertices[1]].vt);
    vertice point3 = vertice_to_point(vertice_buffer[vertice_index + polygon.vertices[2]].vt);

    point1.x = floorf(point1.x / zoomlevel + width / 2);
    point2.x = floorf(point2.x / zoomlevel + width / 2);
    point3.x = floorf(point3.x / zoomlevel + width / 2);

    point1.y = floorf(point1.y / zoomlevel + height / 2);
    point2.y = floorf(point2.y / zoomlevel + height / 2);
    point3.y = floorf(point3.y / zoomlevel + height / 2);
    
    if(polygon.texels[0].u==0 && polygon.texels[0].v==0 && polygon.texels[1].u==0 && polygon.texels[1].v==0 && polygon.texels[2].u==0)
    {
        gfx_3d_fill_triangle(point1, point2, point3, polygon.texels[2].v);
    }
    else
    {
        int texture_index = 0;
        while(texture_buffer[texture_index].unique_ID != polygon.unique_ID)
        {
            texture_index ++;
        }
        gfx_3d_texture_triangle(point1, point2, point3, texture_buffer[texture_index]);
    }
}

    
      
//      polygon polygon_arr[24] = {
//    {{-10,20,20},{-50,20,20},{-10,20,-20},0},
//    {{-50,20,20},{-10,20,-20},{-50,20,-20},63},
//    {{-10,-20,20},{-50,-20,20},{-10,-20,-20},0},
//    {{-50,-20,20},{-10,-20,-20},{-50,-20,-20},63},
//    {{-10,20,20},{-10,20,-20},{-10,-20,20},63},
//    {{-10,-20,20},{-10,20,-20},{-10,-20,-20},126},
//    {{-50,20,20},{-50,20,-20},{-50,-20,20},63},
//    {{-50,-20,20},{-50,20,-20},{-50,-20,-20},126},
//    {{-10,20,20},{-50,20,20},{-10,-20,20},126},
//    {{-50,20,20},{-10,-20,20},{-50,-20,20},189},
//    {{-50,20,-20},{-10,20,-20},{-50,-20,-20},126},
//    {{-10,20,-20},{-40,-20,-20},{-10,-20,-20},189},
//    {{50,20,20},{10,20,20},{50,20,-20},0},
//    {{10,20,20},{50,20,-20},{10,20,-20},63},
//    {{50,-20,20},{10,-20,20},{50,-20,-20},0},
//    {{10,-20,20},{50,-20,-20},{10,-20,-20},63},
//    {{50,20,20},{50,20,-20},{50,-20,20},63},
//    {{50,-20,20},{50,20,-20},{50,-20,-20},126},
//    {{10,20,20},{10,20,-20},{10,-20,20},63},
//    {{10,-20,20},{10,20,-20},{10,-20,-20},126},
//    {{50,20,20},{10,20,20},{50,-20,20},126},
//    {{10,20,20},{50,-20,20},{10,-20,20},189},
//    {{10,20,-20},{50,20,-20},{10,-20,-20},126},
//    {{50,20,-20},{10,-20,-20},{50,-20,-20},189}};
      
#define polyCount 12
#define vtCount 8
obj3D_Box::obj3D_Box()
{
    ID = 0;
    reset();
}
void obj3D_Box::reset()
{
    hide();
    center.x = 0;
    center.y = 0;
    center.z = 0;
    dimension.x = 1;
    dimension.y = 1;
    dimension.z = 1;
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;
    for(int i = 0; i < 6; i++)
    {
        color_arr[i] = 0;
    }
}
obj3D_Box::~obj3D_Box()
{
    this -> hide();
}
void obj3D_Box::hide()
{
    if(ID != 0)
    {
        int i = 0;
        while(polygon_buffer[i].unique_ID != ID)
        {
            i ++;
        }
        while(i + polyCount < polygon_buffer_next_entry)
        {
            polygon_buffer[i] = polygon_buffer[i + polyCount];
            i++;
        }
        polygon_buffer_next_entry -= polyCount;
        ID = 0;
    }
}
void obj3D_Box::show()
{
    if(ID == 0)
    {
        ID = polygon_buffer_next_ID;
        polygon_buffer_next_ID ++;
        for(int i = polygon_buffer_next_entry; i < polygon_buffer_next_entry + polyCount; i++)
        {
            polygon_buffer[i].unique_ID = ID;
        }
        polygon_buffer_next_entry += polyCount;
        update();
    }
}
void obj3D_Box::rotate(vector rotate)
{
    rotation.x += rotate.x;
    rotation.y += rotate.y;
    rotation.z += rotate.z;
}
void obj3D_Box::move(vector move)
{
    center.x += move.x;
    center.y += move.y;
    center.z += move.z;
}
void obj3D_Box::scale(vector factor)
{
    dimension.x *= factor.x;
    dimension.y *= factor.y;
    dimension.z *= factor.z;
}
void obj3D_Box::resize(vector newsize)
{
    dimension.x = newsize.x;
    dimension.y = newsize.y;
    dimension.z = newsize.z;
}
void obj3D_Box::color(uint8_t newcolor)
{
    for(int i = 0; i < 6; i++)
    {
        color_arr[i] = newcolor;
    }
}
void obj3D_Box::color(uint8_t newcolor[6])
{
    for(int i = 0; i < 6; i++)
    {
        color_arr[i] = newcolor[i];
    }
}
void obj3D_Box::update()
{
    if(ID != 0)
    {
        int polygon_index = 0;
        int vertice_index = 0;
        int texture_index = 0;
        while(polygon_buffer[polygon_index].unique_ID != ID)
        {
            polygon_index ++;
        }
        while(polygon_buffer[vertice_index].unique_ID != ID)
        {
            vertice_index ++;
        }
        while(polygon_buffer[texture_index].unique_ID != ID)
        {
            texture_index ++;
        }

        vertice vertices[vtCount] = {
        {0.5, -0.5, 0.5},
        {0.5, 0.5, 0.5},
        {-0.5, 0.5, 0.5},
        {-0.5, -0.5, 0.5},
        {0.5, -0.5, -0.5},
        {0.5, 0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, -0.5, -0.5}};
        
        //rotate & move to center pos

        float sinangle_x = sin(rotation.x * 0.0174532925);
        float cosangle_x = cos(rotation.x * 0.0174532925);
        float sinangle_y = sin(rotation.y * 0.0174532925);
        float cosangle_y = cos(rotation.y * 0.0174532925);
        float sinangle_z = sin(rotation.z * 0.0174532925);
        float cosangle_z = cos(rotation.z * 0.0174532925);
        
        float op1 = (cosangle_y * cosangle_z);
        float op2 = (cosangle_z * sinangle_x * sinangle_y - cosangle_x * sinangle_z);
        float op3 = (cosangle_x * cosangle_z * sinangle_y + sinangle_x * sinangle_z);
        float op4 = (cosangle_y * sinangle_z);
        float op5 = (cosangle_x * cosangle_z + sinangle_x * sinangle_y * sinangle_z);
        float op6 = (-cosangle_z * sinangle_x + cosangle_x * sinangle_y * sinangle_z);
        float op7 = (-sinangle_y);
        float op8 = (cosangle_y * sinangle_x);
        float op9 = (cosangle_x * cosangle_y);

        for(int i = 0; i < vtCount; i++)
        {   
            vertices[i].x *= dimension.x;
            vertices[i].y *= dimension.y;
            vertices[i].z *= dimension.z;
            float x = vertices[i].x * op1 + vertices[i].y * op2 + vertices[i].z * op3;
            float y = vertices[i].x * op4 + vertices[i].y * op5 + vertices[i].z * op6;
            float z = vertices[i].x * op7 + vertices[i].y * op8 + vertices[i].z * op9;
            vertice_buffer[vertice_index + i].vt.x = x + center.x;
            vertice_buffer[vertice_index + i].vt.y = y + center.y;
            vertice_buffer[vertice_index + i].vt.z = z + center.z;
        }


        polygon_buffer[polygon_index].vertices[0] = 0;
        polygon_buffer[polygon_index].vertices[1] = 2;
        polygon_buffer[polygon_index].vertices[2] = 1;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 0;
        polygon_buffer[polygon_index].vertices[1] = 2;
        polygon_buffer[polygon_index].vertices[2] = 3;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 4;
        polygon_buffer[polygon_index].vertices[1] = 6;
        polygon_buffer[polygon_index].vertices[2] = 5;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 4;
        polygon_buffer[polygon_index].vertices[1] = 6;
        polygon_buffer[polygon_index].vertices[2] = 7;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 3;
        polygon_buffer[polygon_index].vertices[1] = 6;
        polygon_buffer[polygon_index].vertices[2] = 2;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 3;
        polygon_buffer[polygon_index].vertices[1] = 6;
        polygon_buffer[polygon_index].vertices[2] = 7;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 2;
        polygon_buffer[polygon_index].vertices[1] = 5;
        polygon_buffer[polygon_index].vertices[2] = 6;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 2;
        polygon_buffer[polygon_index].vertices[1] = 5;
        polygon_buffer[polygon_index].vertices[2] = 1;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 1;
        polygon_buffer[polygon_index].vertices[1] = 0;
        polygon_buffer[polygon_index].vertices[2] = 4;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 1;
        polygon_buffer[polygon_index].vertices[1] = 4;
        polygon_buffer[polygon_index].vertices[2] = 5;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 0;
        polygon_buffer[polygon_index].vertices[1] = 7;
        polygon_buffer[polygon_index].vertices[2] = 3;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
        polygon_buffer[polygon_index].vertices[0] = 0;
        polygon_buffer[polygon_index].vertices[1] = 7;
        polygon_buffer[polygon_index].vertices[2] = 4;
        polygon_buffer[polygon_index].texels[0].u = 0;
        polygon_buffer[polygon_index].texels[0].v = 0;
        polygon_buffer[polygon_index].texels[1].u = 0;
        polygon_buffer[polygon_index].texels[1].v = 0;
        polygon_buffer[polygon_index].texels[2].u = 0;
        polygon_buffer[polygon_index].texels[2].v = 0;
        polygon_index ++;
    }
}



Camera::Camera()
{
    reset();
}
Camera::~Camera()
{
    
}
void Camera::reset()
{
    frameheight = 64;
    framewidth = 96;
    zoomlevel = 60;
    center.x = 0;
    center.y = 0;
    center.z = 0;
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;
}
void Camera::resolution(int width, int height)
{
    framewidth = width;
    frameheight = height;
}
void Camera::zoom(float zoom)
{
    zoomlevel = zoom;
}
void Camera::rotate(vector rotate)
{
    rotation.x += rotate.x;
    rotation.y += rotate.y;
    rotation.z += rotate.z;
}
void Camera::move(vector move)
{
    center.x += move.x;
    center.y += move.y;
    center.z += move.z;
}
void Camera::render(uint8_t *output)
{
    gfx_2d_clear();

    for(int x = 0; x < 96; x++)
    {
        for(int y = 0; y < 64; y++)
        {
            zbuffer[x][y] = -3.4E+38;
        }
    }


    float sinangle_x = sin(rotation.x * 0.0174532925);
    float cosangle_x = cos(rotation.x * 0.0174532925);
    float sinangle_y = sin(rotation.y * 0.0174532925);
    float cosangle_y = cos(rotation.y * 0.0174532925);
    float sinangle_z = sin(rotation.z * 0.0174532925);
    float cosangle_z = cos(rotation.z * 0.0174532925);

    float op1 = (cosangle_y * cosangle_z);
    float op2 = (cosangle_z * sinangle_x * sinangle_y - cosangle_x * sinangle_z);
    float op3 = (cosangle_x * cosangle_z * sinangle_y + sinangle_x * sinangle_z);
    float op4 = (cosangle_y * sinangle_z);
    float op5 = (cosangle_x * cosangle_z + sinangle_x * sinangle_y * sinangle_z);
    float op6 = (-cosangle_z * sinangle_x + cosangle_x * sinangle_y * sinangle_z);
    float op7 = (-sinangle_y);
    float op8 = (cosangle_y * sinangle_x);
    float op9 = (cosangle_x * cosangle_y);

    polygon_bfr activepolygon;
    
    for(int i = 0; i < polygon_buffer_next_entry; i++)
    {   
        activepolygon = polygon_buffer[i];

        float x = activepolygon.verticess[0].x * op1 + activepolygon.vertices[0].y * op2 + activepolygon.vertices[0].z * op3;
        float y = activepolygon.vertices[0].x * op4 + activepolygon.vertices[0].y * op5 + activepolygon.vertices[0].z * op6;
        float z = activepolygon.vertices[0].x * op7 + activepolygon.vertices[0].y * op8 + activepolygon.vertices[0].z * op9;
        activepolygon.vertices[0].x = x - center.x;
        activepolygon.vertices[0].y = y - center.y;
        activepolygon.vertices[0].z = z - center.z;

        x = activepolygon.vertices[1].x * op1 + activepolygon.vertices[1].y * op2 + activepolygon.vertices[1].z * op3;
        y = activepolygon.vertices[1].x * op4 + activepolygon.vertices[1].y * op5 + activepolygon.vertices[1].z * op6;
        z = activepolygon.vertices[1].x * op7 + activepolygon.vertices[1].y * op8 + activepolygon.vertices[1].z * op9;
        activepolygon.vertices[1].x = x - center.x;
        activepolygon.vertices[1].y = y - center.y;
        activepolygon.vertices[1].z = z - center.z;

        x = activepolygon.vertices[2].x * op1 + activepolygon.vertices[2].y * op2 + activepolygon.vertices[2].z * op3;
        y = activepolygon.vertices[2].x * op4 + activepolygon.vertices[2].y * op5 + activepolygon.vertices[2].z * op6;
        z = activepolygon.vertices[2].x * op7 + activepolygon.vertices[2].y * op8 + activepolygon.vertices[2].z * op9;
        activepolygon.vertices[2].x = x - center.x;
        activepolygon.vertices[2].y = y - center.y;
        activepolygon.vertices[2].z = z - center.z;
        
     
        drawpolygon(activepolygon, zoomlevel, framewidth, frameheight);
    }

}



void gfx3dsetup()
{
    
    vector vector1 = {0,0,-500};
    vector vector2 = {100,100,100};
    for(int i = 0; i < cubecount; i++)
    {
        cube[i].move(vector1);
        cube[i].resize(vector2);
        cube[i].show();
    }
}
void gfx3dperiodic()
{
    //clear zbuffer

    if(keys == key_enter)
    {
        
        for(int i = 0; i < cubecount; i++)
        {
             rotation[i].x = rand() % 10;
             rotation[i].y = rand() % 10;
             rotation[i].z = rand() % 10;
             cube[i].dimension.x = rand() % 50 + 50;
             cube[i].dimension.y = rand() % 50 + 50;
             cube[i].dimension.z = rand() % 50 + 50;
             cube[i].center.z = rand() % 500 - 1000;
             cube[i].center.x = rand() % 300 - 150;
             cube[i].center.y = rand() % 300 - 150;

             uint8_t temp = rand() % 200;
             cube[i].color(temp);
             //cube[i].color_edge(1);

        }
    }
    

    for(int i = 0; i < cubecount; i++)
    {
        cube[i].rotate(rotation[i]);
        cube[i].update();
    }
    uint8_t x;

    cam1.render(&x);
    cnt --;
}



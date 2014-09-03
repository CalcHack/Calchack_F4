#ifndef GFX_3D_H
#define GFX_3D_H

#include "stm32f4xx_conf.h"




typedef struct 
{
    float x;
    float y;
    float z;
}vertice;

typedef struct
{
    uint16_t u;
    uint16_t v;
}texel;

typedef struct 
{
    float x;
    float y;
    float z;
}vector;

typedef struct 
{
    uint32_t unique_ID;    
    uint8_t vertices[3];
    texel texels[3];
}polygon_bfr;

typedef struct 
{
    uint32_t unique_ID; 
    vertice vt;
}vertice_bfr;

typedef struct 
{
    uint32_t unique_ID; 
    uint16_t height;
    uint16_t width;
    uint8_t *texture;
}texture_bfr;


class obj3D_Box
{
    public:
    obj3D_Box();
    ~obj3D_Box();
    void reset();
    void hide();
    void show();
    void rotate(vector rotate);
    void move(vector move);
    void scale(vector factor);
    void resize(vector newsize);
    void color(uint8_t newcolor);
    void color(uint8_t newcolor[6]);
    void update();

    vertice center;
    vector dimension;
    vector rotation;
    uint8_t color_arr[6];
    private:
    uint32_t ID;
};

class obj3D_Box_colored_edge
{
    public:
    obj3D_Box_colored_edge();
    ~obj3D_Box_colored_edge();
    void reset();
    void hide();
    void show();
    void rotate(vector rotate);
    void move(vector move);
    void scale(vector factor);
    void resize(vector newsize);
    void color(uint8_t newcolor);
    void color(uint8_t newcolor[6]);
    void color_edge(uint8_t newcolor);
    void color_edge(uint8_t newcolor[6]);
    void update();

    vertice center;
    vector dimension;
    vector rotation;
    uint8_t color_arr[6];
    uint8_t edge_color_arr[6];
    private:
    uint32_t ID;
};

class Camera
{
    public:
    Camera();
    ~Camera();
    void reset();
    void resolution(int width, int height);
    void zoom(float zoom);
    void rotate(vector rotate);
    void move(vector move);
    void render(uint8_t *output);
    vertice center;
    vector rotation;
    float zoomlevel;
    private:
    int framewidth, frameheight;
};

void gfx3dsetup();
void gfx3dperiodic();

#endif
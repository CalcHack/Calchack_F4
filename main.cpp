#include <stdio.h>

#include "system_stm32f4xx.h"

#include "linkport.h"
#include "stm32f4xx_conf.h"
#include "img.h"
#include "gfx_2d.h"
#include "gfx_3d.h"


#define Breset BSRRH
#define Bset BSRRL



int x;






void boot()
{
  LINK_send_key(0x9b00);
  
  LINK_send_key(0xa800);

  LINK_send_key(0xa800);

  LINK_send_key(0xad00);

  LINK_send_key(0xa200);

  LINK_send_key(0xa700);

  LINK_send_key(0xa000);

  LINK_send_key(0xfe68);

  LINK_send_key(0xfe68);

  LINK_send_key(0xfe68);

}


int main(void)
{

  LINK_init();


  

  //boot();
  
  //while(!LINK_check_password());
  LINK_send_os();


  
//  uint64_t bin = 0;
//  for(int i = 512; i < 768; i++)
//      {
//          framebuffer[i] = 0xff;
//
//      }
//
//  for(int i = 2048; i < 4096; i++)
//  {
//     framebuffer[i % 96][i / 96] = 150;
//  }
//  for(int i = 4096; i < 6144; i++)
//  {
//     framebuffer[i % 96][i / 96] = 190;
//  }
//    


gfx3dsetup();

int framecnt = 0;
  
  


int framecount = 0;

  const char str1[] = "Welcome to";
  gfx_2d_string(str1,sizeof(str1),1,5,-2,-1);
  const char str2[] = "CalcHack";
  gfx_2d_string(str2,sizeof(str2),1,13,-2,-1);
  for(int i = 0; i < 30; i++)
  LINK_transfer_framedata();

  while(1)
  {
  const char strng1[] = "CalcHack\0 Demos\0 Apps\0 Settings\0 TEST\0 AndrinPRGM\0 AndrinPRGM2";
  int menu = gfx_2d_menu_simple(strng1,6);
  
  if(menu == 6)
  {
      int X[3] = {10,50,30};
      int Y[3] = {10,40,10};
      int A[3] = {1,2,2};
      int B[3] = {1,1,2};
      int step = 1;
      
      while(1)
      {
          if(keys == key_enter)
          {
              while(keys == key_enter)
              {
                  LINK_transfer_framedata();
              }
              break;
          }
          gfx_2d_clear();
          
          for(int ct = 0; ct < step; ct ++)
          {
              for(int i = 0; i < 3; i++)
              {
                  gfx_2d_fill_circle({X[i],Y[i]},8,0,0);
     
          
          
          
                  if (A[i] == 1)
                  {
                      X[i]+=step;
                  }

                  if (A[i]  == 2)
                  {
                      X[i]-=step;
                  }

                  if (B[i] == 1)
                  {
                      Y[i]+=step;
                  }

                  if (B[i] == 2)
                  {
                      Y[i]-=step;
                  }



          

                  if (Y[i] >= 58)
                  {
                      B[i] = 2;
                  }
                  if (Y[i] <= 5)
                  {
                      B[i] = 1;
                  }

                  if (X[i] >= 90)
                  {
                      A[i] = 2;
                  }

                  if (X[i] <= 5)
                  {
                      A[i] = 1;
                  }

              }
          }

          gfx_2d_fill_triangle({X[0],Y[0]},{X[1],Y[1]},{X[2],Y[2]},120);
          LINK_transfer_framedata();
          if(keys == key_up)
          {
              step ++;
          }
          if(keys == key_down && step > 0)
          {
              step --;
          }
          
      }
  }

  if(menu == 5)
  {
      int X = 10;
      int Y = 10;
      int A = 1;
      int B = 1;
      int C = 1;
      int D = 1;
      
      
      while(1)
      {
          if(keys == key_enter)
          {
              while(keys == key_enter)
              {
                  LINK_transfer_framedata();
              }
              break;
          }
          gfx_2d_clear();
          gfx_2d_fill_circle({X,Y},C,0,0);
     
          
          if (D == 1)
          {
          C++;
          }
          
          if (D == 2)
          {
          C--;
          }
         
          if (A == 1)
          {
          
          X++;
          }

          if (A  == 2)
          {
          
          X--;
          }

          if (B == 1)
          {
          Y++;
          
          }

          if (B == 2)
          {
          Y--;
          
          }



          LINK_transfer_framedata();

          if (Y == 58)
            {
      
                 B = 2;
      
            }
          if (Y == 5)
          {
          B = 1;
          }

          if (X == 90)
          {
          A = 2;
          }

          if (X == 5)
          {
          A = 1;
          }

          if (C == 10)
          {
          D = 2;
          }

          if (C == 1)
          {
          D = 1;
          }

          
      }
  }

  if(menu == 4)
  {
      
      point pt = {45,30};
      
      for(int i = 0; i < 35; i++)
   {
      gfx_2d_clear();
      gfx_2d_fill_circle(pt,i,0,200);
      LINK_transfer_framedata();
      LINK_transfer_framedata();
      LINK_transfer_framedata();
      LINK_transfer_framedata();
      LINK_transfer_framedata();
      LINK_transfer_framedata();
      LINK_transfer_framedata();
      LINK_transfer_framedata();
   }
  }
    
  if(menu == 1)
  {
      const char strng1[] = "CalcHack Demos\0 2D-GFX Demos\0 3D-Engine Demo\0 Greyscale Horse";
      menu = gfx_2d_menu_simple(strng1,3);
      if(menu == 1)
      {
          gfx_2d_clear();
  const char str7[] = "-Pixels";
  gfx_2d_string(str7,sizeof(str7),1,5,-2,-1);
  for(int i = 0; i < 100; i++)
   {
      gfx_2d_pixel(rand() % 96, rand() % 64, rand() % 256);
      gfx_2d_pixel(rand() % 96, rand() % 64, rand() % 256);
      gfx_2d_pixel(rand() % 96, rand() % 64, rand() % 256);
      gfx_2d_pixel(rand() % 96, rand() % 64, rand() % 256);
      gfx_2d_pixel(rand() % 96, rand() % 64, rand() % 256);
      LINK_transfer_framedata();
   }

  gfx_2d_clear();
  const char str8[] = "-Lines";
  gfx_2d_string(str8,sizeof(str8),1,5,-2,-1);
  for(int i = 0; i < 100; i++)
   {
      gfx_2d_line(rand() % 96, rand() % 64, rand() % 96, rand() % 64, rand() % 256);
      LINK_transfer_framedata();
   }
   gfx_2d_clear();
  const char str88[] = "-Triangles";
  gfx_2d_string(str88,sizeof(str88),1,5,-2,-1);
  for(int i = 0; i < 100; i++)
   {
      gfx_2d_triangle(rand() % 96, rand() % 64, rand() % 96, rand() % 64, rand() % 96, rand() % 64, rand() % 256);
      LINK_transfer_framedata();
   }
   gfx_2d_clear();
  const char str9[] = "-Rectangles";
  gfx_2d_string(str9,sizeof(str9),1,5,-2,-1);
  for(int i = 0; i < 100; i++)
   {
      gfx_2d_rectangle(rand() % 96, rand() % 64, rand() % 96, rand() % 64, rand() % 256);
      LINK_transfer_framedata();
   }
   gfx_2d_clear();
   const char str13[] = "-Circles";
  gfx_2d_string(str13,sizeof(str13),1,5,-2,-1);
  for(int i = 0; i < 100; i++)
   {
      point pt1 = {rand() % 96, rand() % 64};
      gfx_2d_circle(pt1, rand() % 50, rand() % 256);
      LINK_transfer_framedata();
   }
   gfx_2d_clear();
  const char str10[] = "-Filled Triangles";
  gfx_2d_string(str10,sizeof(str10),1,5,-2,-1);
  for(int i = 0; i < 100; i++)
   {
      point pt1 = {rand()%96,rand()%64};
      point pt2 = {rand()%96,rand()%64};
      point pt3 = {rand()%96,rand()%64};
      gfx_2d_fill_triangle(pt1,pt2, pt3, rand()%256);
      LINK_transfer_framedata();
   }
   gfx_2d_clear();
  const char str11[] = "-Filled Rectangles";
  gfx_2d_string(str11,sizeof(str11),1,5,-2,-1);
  for(int i = 0; i < 100; i++)
   {
      gfx_2d_fill_rectangle(rand() % 96, rand() % 64, rand() % 96, rand() % 64, rand() % 256);
      LINK_transfer_framedata();
   }
   gfx_2d_clear();
  const char str12[] = "-Filled Circles";
  gfx_2d_string(str12,sizeof(str12),1,5,-2,-1);
  for(int i = 0; i < 100; i++)
   {
      point pt1 = {rand() % 96, rand() % 64};
      gfx_2d_fill_circle(pt1, rand() % 50, rand() % 256, rand() % 256);
      LINK_transfer_framedata();
   }
      }
      if(menu == 2)
      {
          gfx3dsetup();
          int i = 0;
  while(i < 500)
  {   
      framecount ++;
      i++;
      LINK_transfer_framedata();

      if(framecount % 2 == 0)
      {
      framecount = 0;
      gfx3dperiodic();
      char c[] = "3D-Engine";
      gfx_2d_string(c,sizeof(c),10,5,-2,-1);
      }

  }
      }
      if(menu == 3)
      {
          for(int x = 0; x < 96; x++)
          {
              for(int y = 0; y < 64; y++)
              {
                  framebuffer[x][y]=img1[y*96+x];
              }
          }
          for(int i = 0; i < 300; i++)
          LINK_transfer_framedata();
      }
  }
  if (menu == 3)
  {
  const char strng1[] = "Settings\0 Network Config\0 Show CPUID\0 Change PW\0 FW Upgrade\0 CPU Overclock\0 FACTORY RESET";
      menu = gfx_2d_menu_simple(strng1,6);

      }
 } 

//const char str3[] = "Here are some";
//gfx_2d_string(str3,sizeof(str3),1,25,-2,-1);
//const char str4[] = "of its features!";
//gfx_2d_string(str4,sizeof(str4),1,33,-2,-1);
//for(int i = 0; i < 50; i++)
//LINK_transfer_framedata();
//
//gfx_2d_clear();
//
//
//const char str5[] = "Greyscale Pics";
//gfx_2d_string(str5,sizeof(str5),1,5,-2,-1);
//for(int i = 0; i < 30; i++)
//LINK_transfer_framedata();
//  for(int x = 0; x < 96; x++)
//  {
//  for(int y = 0; y < 64; y++)
//  {
//    framebuffer[x][y]=img1[y*96+x];
//  }
//  }
//for(int i = 0; i < 40; i++)
//LINK_transfer_framedata();
//gfx_2d_clear();
//
//const char str6[] = "2D-Graphic Lib:";
//gfx_2d_string(str6,sizeof(str6),1,5,-2,-1);
//for(int i = 0; i < 25; i++)
//LINK_transfer_framedata();
//

  
//gfx3dsetup();
//  while(1)
//  {   
//      framecount ++;
//      LINK_transfer_framedata();
//
//      if(framecount % 2 == 0)
//      {
//      framecount = 0;
//      gfx3dperiodic();
//      char c[] = "3D-Engine";
//      gfx_2d_string(c,sizeof(c),10,5,-2,-1);
//      }
//      
//      if(return_to_tios == 1)
//      {
//         // break;
//      }
//  }
      

//  while         (1)
//  {   
//  framecnt ++;
//      if(framecnt % 2 == 0)
//      {
//      framecnt = 0;
//      gfx3dperiodic();
//      char c[] = "3D-Engine Test";
//      gfx_2d_string(c,sizeof(c),10,5,-2,-1);
//      }
//      LINK_transfer_framedata();
//  }
//      while (1)
//      {
//     for(int i = 256; i < 512; i++)
//      {
//          framebuffer[i] = 0b10101010;
//          i++;
//          framebuffer[i] = 0b01010101;
//      }
//      LINK_transfer_framedata();
//
//       for(int i = 256; i < 512; i++)
//      {
//          framebuffer[i] = 0b01010101;
//          i++;
//          framebuffer[i] = 0b10101010;
//      }
//      LINK_transfer_framedata();


//      for(int i = 0; i < 768; i++)
//      {
//          framebuffer[i] = rand();
//          if(i % 32 == 0)
//          {
//              LINK_transfer_framedata();
//          }
//      }
//      for(int i = 0; i < 768; i++)
//      {
//          framebuffer[i] = screen[(i%64)*12+i/64];
//          if(i % 32 == 0)
//          {
//              LINK_transfer_framedata();
//          }
//      }
    
//    for(int i = 0; i < 64; i++)
//    {
//        framebuffer[i] = bin >> 24;
//        bin ++;
//    }
//    bin -= 64;
//
//    for(int i = 0; i < 64; i++)
//    {
//        framebuffer[i + 64] = bin >> 16;
//        bin ++;
//    }
//    bin -= 64;
//
//    for(int i = 0; i < 64; i++)
//    {
//        framebuffer[i + 128] = bin >> 8;
//        bin ++;
//    }
//    bin -= 64;
//
//    for(int i = 0; i < 64; i++)
//    {
//        framebuffer[i + 192] = bin;
//        bin ++;
//    }
//    bin -= 64;
//    LINK_transfer_framedata();
//    
//    if(x % 4 == 0)
//    bin+=40;
   
//  
//    for(int x = 0; x < 96; x++)
//    {
//    LINK_transfer_framedata();
//    for(int y = 0; y < 64; y++)
//    {
//      framebuffer[x][y]=img1[y*96+x];
//    }
//    }
//    gfx_2d_fill_rectangle(0,0,95,63,-1);
//
//    for(int i = 0; i < 60; i++)
//    LINK_transfer_framedata();
//
//    for(int x = 0; x < 96; x++)
//    {
//    LINK_transfer_framedata();
//    for(int y = 0; y < 64; y++)
//    {
//      framebuffer[x][y]=img2[y*96+x];
//    }
//    }
//    
//    for(int i = 0; i < 380; i++)
//    LINK_transfer_framedata();
//
//    gfx_2d_fill_rectangle(0,0,95,63,-1);
//
//    for(int i = 0; i < 60; i++)
//    LINK_transfer_framedata();
//
//    for(int x = 0; x < 96; x++)
//    {
//    LINK_transfer_framedata();
//    for(int y = 0; y < 64; y++)
//    {
//      framebuffer[x][y]=img3[y*96+x];
//    }
//    }
//
//    gfx_2d_fill_rectangle(0,0,95,63,-1);
//
//    for(int i = 0; i < 60; i++)
//    LINK_transfer_framedata();
//
//
//  
//
//
////    if (bDeviceState == CONFIGURED)
////    {
////        while(Receive_length == 0)
////        {
////          CDC_Receive_DATA();
////        }
////        Receive_length = 0;
////      LINK_get_screenshot();
////      send_lcd_data();
////
////    }
//  }
} 




/**




  * @brief  SHA256 HASH digest compute example.
  * @param  InputMessage: pointer to input message to be hashed.
  * @param  InputMessageLength: input data message length in byte.
  * @param  MessageDigest: pointer to output parameter that will handle message digest
  * @param  MessageDigestLength: pointer to output digest length.
  * @retval error status: can be HASH_SUCCESS if success or one of
  *         HASH_ERR_BAD_PARAMETER, HASH_ERR_BAD_CONTEXT,
  *         HASH_ERR_BAD_OPERATION if error occured.
  */

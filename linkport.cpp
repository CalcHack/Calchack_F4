#include "linkport.h"
#include "os.h"

uint32_t frame = 0;
uint8_t framebuffer[96][64];
uint8_t framebuffer_now[768];
uint8_t brightness_level[6] = {0,51,102,153,205,255};
int return_to_tios = 0;
uint8_t prgm_header[11] = {(OS_SIZE + 2) & 0xFF, ((OS_SIZE + 2) >> 8) & 0xff, 0x05,0,0,0,0,0,0,0,0};
uint8_t password_buffer[9]; //what user entered: byte 0: length, byte 1-8: password
uint8_t password[9] = {8,'C','A','L','C','H','A','C','K'}; //password to which entered password is compared

uint8_t keydelay_1 = 80;
uint8_t keydelay_2 = 80;




uint64_t keys;



const uint8_t framemask_1[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
};

const uint8_t framemask_1_3[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
};

const uint8_t framemask_1_2[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
};

const uint8_t framemask_1_5[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
};





const uint8_t framemask_2[5][6][8][8] = {    
        {
            {
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1}
            },
            {
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1}
            },
            {
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1}
            },
            {
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1}
            },
            {
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1}
            },
            {
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1}
            }
        },
        {
            {
                {1,0,1,0,1,1,1,0},
                {0,1,0,1,1,1,1,1},
                {1,1,1,0,0,0,1,1},
                {1,1,1,0,1,0,1,1},
                {1,1,1,0,1,1,1,0},
                {1,0,1,0,1,0,1,1},
                {0,1,1,0,1,1,1,0},
                {0,1,1,0,1,1,1,0}
            },
            {
                {0,1,0,1,1,0,1,1},
                {1,1,1,0,0,1,0,1},
                {0,1,0,1,1,1,1,1},
                {1,0,0,1,1,1,0,0},
                {1,0,1,1,0,0,1,1},
                {1,1,1,1,1,1,0,0},
                {1,1,0,1,1,0,1,1},
                {1,0,1,1,0,1,0,1}
            },
            {
                {1,1,1,1,0,1,0,1},
                {1,0,1,1,1,0,1,0},
                {1,0,1,1,1,1,0,0},
                {0,1,1,1,0,1,1,1},
                {0,1,0,1,1,1,0,1},
                {0,1,0,1,0,1,1,1},
                {1,0,1,1,0,1,0,1},
                {1,1,0,1,1,0,1,1}
            },
            {
                {1,0,1,0,1,1,1,0},
                {0,1,0,1,1,1,1,1},
                {1,1,1,0,0,0,1,1},
                {1,1,1,0,1,0,1,1},
                {1,1,1,0,1,1,1,0},
                {1,0,1,0,1,0,1,1},
                {0,1,1,0,1,1,1,0},
                {0,1,1,0,1,1,1,0}
            },
            {
                {0,1,0,1,1,0,1,1},
                {1,1,1,0,0,1,0,1},
                {0,1,0,1,1,1,1,1},
                {1,0,0,1,1,1,0,0},
                {1,0,1,1,0,0,1,1},
                {1,1,1,1,1,1,0,0},
                {1,1,0,1,1,0,1,1},
                {1,0,1,1,0,1,0,1}
            },
            {
                {1,1,1,1,0,1,0,1},
                {1,0,1,1,1,0,1,0},
                {1,0,1,1,1,1,0,0},
                {0,1,1,1,0,1,1,1},
                {0,1,0,1,1,1,0,1},
                {0,1,0,1,0,1,1,1},
                {1,0,1,1,0,1,0,1},
                {1,1,0,1,1,0,1,1}
            },
        },
        {
            {
                {1,1,1,0,0,1,0,1},
                {0,0,0,1,1,0,1,0},
                {1,0,1,1,1,1,0,0},
                {0,1,1,1,0,0,1,1},
                {0,1,0,0,1,1,0,0},
                {0,0,0,0,0,1,1,1},
                {1,0,1,0,0,1,0,1},
                {0,1,0,1,1,0,1,1}
            },
            {
                {0,0,0,1,1,0,1,0},
                {1,1,1,0,0,1,0,1},
                {0,1,0,0,0,0,1,1},
                {1,0,0,0,1,1,0,0},
                {1,0,1,1,0,0,1,1},
                {1,1,1,1,1,0,0,0},
                {0,1,0,1,1,0,1,0},
                {1,0,1,0,0,1,0,0}
            },
            {
                {1,1,1,0,0,1,0,1},
                {0,0,0,1,1,0,1,0},
                {1,0,1,1,1,1,0,0},
                {0,1,1,1,0,0,1,1},
                {0,1,0,0,1,1,0,0},
                {0,0,0,0,0,1,1,1},
                {1,0,1,0,0,1,0,1},
                {0,1,0,1,1,0,1,1}
            },
            {
                {0,0,0,1,1,0,1,0},
                {1,1,1,0,0,1,0,1},
                {0,1,0,0,0,0,1,1},
                {1,0,0,0,1,1,0,0},
                {1,0,1,1,0,0,1,1},
                {1,1,1,1,1,0,0,0},
                {0,1,0,1,1,0,1,0},
                {1,0,1,0,0,1,0,0}
            },
            {
                {1,1,1,0,0,1,0,1},
                {0,0,0,1,1,0,1,0},
                {1,0,1,1,1,1,0,0},
                {0,1,1,1,0,0,1,1},
                {0,1,0,0,1,1,0,0},
                {0,0,0,0,0,1,1,1},
                {1,0,1,0,0,1,0,1},
                {0,1,0,1,1,0,1,1}
            },
            {
                {0,0,0,1,1,0,1,0},
                {1,1,1,0,0,1,0,1},
                {0,1,0,0,0,0,1,1},
                {1,0,0,0,1,1,0,0},
                {1,0,1,1,0,0,1,1},
                {1,1,1,1,1,0,0,0},
                {0,1,0,1,1,0,1,0},
                {1,0,1,0,0,1,0,0}
            },
        },
        {
            {
                {0,1,0,1,0,0,0,1},
                {1,0,1,0,0,0,0,0},
                {0,0,0,1,1,1,0,0},
                {0,0,0,1,0,1,0,0},
                {0,0,0,1,0,0,0,1},
                {0,1,0,1,0,1,0,0},
                {1,0,0,1,0,0,0,1},
                {1,0,0,1,0,0,0,1}
            },
            {
                {1,0,1,0,0,1,0,0},
                {0,0,0,1,1,0,1,0},
                {1,0,1,0,0,0,0,0},
                {0,1,1,0,0,0,1,1},
                {0,1,0,0,1,1,0,0},
                {0,0,0,0,0,0,1,1},
                {0,0,1,0,0,1,0,0},
                {0,1,0,0,1,0,1,0}
            },
            {
                {0,0,0,0,1,0,1,0},
                {0,1,0,0,0,1,0,1},
                {0,1,0,0,0,0,1,1},
                {1,0,0,0,1,0,0,0},
                {1,0,1,0,0,0,1,0},
                {1,0,1,0,1,0,0,0},
                {0,1,0,0,1,0,1,0},
                {0,0,1,0,0,1,0,0}
            },
            {
                {0,1,0,1,0,0,0,1},
                {1,0,1,0,0,0,0,0},
                {0,0,0,1,1,1,0,0},
                {0,0,0,1,0,1,0,0},
                {0,0,0,1,0,0,0,1},
                {0,1,0,1,0,1,0,0},
                {1,0,0,1,0,0,0,1},
                {1,0,0,1,0,0,0,1}
            },
            {
                {1,0,1,0,0,1,0,0},
                {0,0,0,1,1,0,1,0},
                {1,0,1,0,0,0,0,0},
                {0,1,1,0,0,0,1,1},
                {0,1,0,0,1,1,0,0},
                {0,0,0,0,0,0,1,1},
                {0,0,1,0,0,1,0,0},
                {0,1,0,0,1,0,1,0}
            },
            {
                {0,0,0,0,1,0,1,0},
                {0,1,0,0,0,1,0,1},
                {0,1,0,0,0,0,1,1},
                {1,0,0,0,1,0,0,0},
                {1,0,1,0,0,0,1,0},
                {1,0,1,0,1,0,0,0},
                {0,1,0,0,1,0,1,0},
                {0,0,1,0,0,1,0,0}
            },
        },
        {
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            }
        }
    

};
void LINK_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    LINK_INIT_GPIO_CLOCK
     
    GPIO_InitStructure.GPIO_Pin = LINK_WHITE_bit;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = LINK_GPIO_Speed;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LINK_WHITE_port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LINK_RED_bit;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = LINK_GPIO_Speed;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LINK_RED_port, &GPIO_InitStructure);
    
    LINK_RED_high
    LINK_WHITE_high
}

int16_t LINK_get_byte()
{
    uint8_t bit=0;
    uint8_t byte=0;
    int timeout=0;

    while(bit<8)
    {

        if (!GPIO_ReadInputDataBit(LINK_WHITE_port, LINK_WHITE_bit))
        { 
            timeout=0;
            bit++;
            byte = (byte >> 1) | 128;	
            LINK_RED_low;						
            LINK_WHITE_wait_until_high;					
            LINK_RED_high;						
            for(volatile uint32_t delaycount = LINK_BIT_DELAY; delaycount > 0; delaycount --);
        }
        else if (!GPIO_ReadInputDataBit(LINK_RED_port, LINK_RED_bit))
        {
            timeout=0;
            bit++;
            byte = byte >> 1;													
            LINK_WHITE_low;			
            LINK_RED_wait_until_high;		
            LINK_WHITE_high;			
            for(volatile uint32_t delaycount = LINK_BIT_DELAY; delaycount > 0; delaycount --);
        }
        else
        {
            timeout ++;
            if(timeout > 1000)
            {
                return -1;
            }
        }
    }
    for(volatile uint32_t delaycount = LINK_BYTE_DELAY; delaycount > 0; delaycount --);
    return byte;
}

uint8_t LINK_wait_for_byte()
{
    int16_t temp = -1;
    while(temp == -1)
    {
        temp = LINK_get_byte();
    }
    return temp;
}



void LINK_transfer_framedata() //timing: rising edge/begin -> 7 DATA -> 27 -> DATA -> 31 -> DATA -> 31 -> DATA -> 43 -> repeat
{
    frame++;
    uint32_t static transferstate;
    uint16_t pattern0;
    uint16_t pattern1;
    uint16_t pattern2;
    uint16_t pattern3;
    frame = frame % 6;

    
    
    for(int i = 0; i < 768; i++)
    {
        pattern3 = 0;
        int x = i / 64 * 8;
        int y = i % 64;
        int line = y % 8;


//        for(int brightness_step = 0; brightness_step < 5; brightness_step ++)
//        {
//
//            uint8_t temp = 0;
//            
//            for(int bit = 0; bit < 8; bit ++)
//            {
//                temp = temp << 1 + framemask_2[frame][framemask_1[framebuffer[x+bit][y]]][bit];
//            }
//            pattern3 = pattern3 | temp;
//      
//        }
        
        

        for(volatile uint32_t delaycount = 10; delaycount > 0; delaycount --); 
    
        
        //for(volatile uint32_t delaycount = 2; delaycount > 0; delaycount --);
        
        uint16_t pattern;

        pattern = framemask_2[framemask_1[framebuffer[x][y]]][frame][0][line];
        pattern = pattern << 1;
        pattern += framemask_2[framemask_1[framebuffer[x+1][y]]][frame][1][line];
        pattern = pattern << 8;

        LINK_RED_wait_until_low
        LINK_RED_wait_until_high

        LINK_RED_port -> Breset = 0b11 << 8;
        LINK_RED_port -> Bset = pattern;
        for(volatile uint32_t delaycount = 40; delaycount > 0; delaycount --); 
        framebuffer_now[i] = pattern;
        pattern = framemask_2[framemask_1[framebuffer[x+2][y]]][frame][2][line];
        pattern = pattern << 1;
        pattern += framemask_2[framemask_1[framebuffer[x+3][y]]][frame][3][line];
        pattern = pattern << 8;
        LINK_RED_port -> Breset = 0b11 << 8;
        LINK_RED_port -> Bset = pattern;
        framebuffer_now[i] += pattern >> 2;
        for(volatile uint32_t delaycount = 40; delaycount > 0; delaycount --); 
        pattern = framemask_2[framemask_1[framebuffer[x+6][y]]][frame][6][line];
        pattern = pattern << 1;
        pattern += framemask_2[framemask_1[framebuffer[x+7][y]]][frame][7][line];
        pattern = pattern << 8;
        LINK_RED_port -> Breset = 0b11 << 8;
        LINK_RED_port -> Bset = pattern;
        framebuffer_now[i] += pattern >> 4;
        for(volatile uint32_t delaycount = 40; delaycount > 0; delaycount --); 
        pattern = framemask_2[framemask_1[framebuffer[x+4][y]]][frame][4][line];
        pattern = pattern << 1;
        pattern += framemask_2[framemask_1[framebuffer[x+5][y]]][frame][5][line];
        pattern = pattern << 8;
        LINK_RED_port -> Breset = 0b11 << 8;
        LINK_RED_port -> Bset = pattern;
        framebuffer_now[i] += pattern >> 6;
        for(volatile uint32_t delaycount = 40; delaycount > 0; delaycount --); 
        LINK_RED_port -> Bset = 0b11 << 8;

    }
    
    if(keys == key_del)
    {
        return_to_tios = 1;
    }
    keys = 0;
    for(int i = 0; i < 8; i++)
    {
        uint8_t temp = 0;
    
        for(volatile uint32_t delaycount = keydelay_1; delaycount > 0; delaycount --);
        LINK_WHITE_wait_until_low
        
        
        for(int j = 0; j < 4; j++)
        {
            for(volatile uint32_t delaycount = keydelay_2; delaycount > 0; delaycount --);
            temp = temp << 2;
            if(!GPIO_ReadInputDataBit(LINK_WHITE_port, LINK_WHITE_bit))
            {
                temp += 1; 
            }
            if(!GPIO_ReadInputDataBit(LINK_RED_port, LINK_RED_bit))
            {
                temp += 2;
            }
            
        }
        keys = keys << 8;
        keys += temp;
    }
    if(return_to_tios == 1)
    {
        LINK_RED_low
    }
}


void LINK_send_command(uint8_t command_ID, uint16_t length, uint8_t data[])
{
    uint16_t checksum = 0;
    LINK_send_byte(MACHINE_ID);
    LINK_send_byte(command_ID);
    uint8_t cmd1 = length & 0xff;
    uint8_t cmd2 = (length >> 8) & 0xff;
    LINK_send_byte(cmd1);
    LINK_send_byte(cmd2);
    for(uint16_t i = 0; i < length; i ++)
    {
        LINK_send_byte(data[i]);
        checksum += data[i];
    }
    uint8_t chksm1 = checksum & 0xff;
    uint8_t chksm2 = (checksum >> 8) & 0xff;
    LINK_send_byte(chksm1);
    LINK_send_byte(chksm2);
}

void LINK_send_byte (uint8_t byte)
{

    uint8_t bit;

    for (bit = 0; bit < 8; bit++)
    {
        if (byte & 1)
        {
            LINK_WHITE_low;	
            LINK_RED_wait_until_low;
            LINK_WHITE_high;
            LINK_RED_wait_until_high;
        } 
        else 
        {
            LINK_RED_low;	
            LINK_WHITE_wait_until_low;
            LINK_RED_high;		
            LINK_WHITE_wait_until_high;
        }
        byte >>= 1;
    }
    for(volatile uint32_t delaycount = LINK_BYTE_DELAY; delaycount > 0; delaycount --);
}
void LINK_send_array(uint8_t array[], int length)
{
    int i = 0;
    while(i < length)
    {
        LINK_send_byte(array[i]);
        i++;
    }
}

void LINK_send_key(uint16_t key)
{
    uint8_t cmd1 = key & 0xff;
    uint8_t cmd2 = (key >> 8) & 0xff;
  
    LINK_send_byte(0x02);
    LINK_send_byte(0x87);
    LINK_send_byte(cmd1);  
    LINK_send_byte(cmd2);  
    LINK_wait_for_byte();
    LINK_wait_for_byte();
    LINK_wait_for_byte();
    LINK_wait_for_byte();
}

void LINK_send_key_sequence(uint16_t key_sequence[], uint16_t length)
{
    for(uint16_t i = 0; i < length; i ++)
    {
        LINK_send_key(key_sequence[i]);
    }
}



void LINK_send_array_with_checksum(const uint8_t data[], uint16_t length)
{
    uint16_t checksum = 0;
    for(uint16_t i = 0; i < length; i ++)
    {
      LINK_send_byte(data[i]);
      checksum += data[i];
    }
    uint8_t chksm1 = checksum & 0xff;
    uint8_t chksm2 = (checksum >> 8) & 0xff;
    LINK_send_byte(chksm1);
    LINK_send_byte(chksm2);
}


void LINK_get_screenshot(void)
{
    LINK_send_byte(MACHINE_ID);
    LINK_send_byte(0x6D);
    LINK_send_byte(0);
    LINK_send_byte(0);
    LINK_get_byte();
    LINK_get_byte();
    LINK_get_byte();
    LINK_get_byte();
    LINK_get_byte();
    LINK_get_byte();
    LINK_get_byte();
    LINK_get_byte();
    int i = 0;
    while (i < 768)
    {
        screenshot[i] = LINK_get_byte();
        i ++;
    }
    LINK_get_byte();
    LINK_get_byte();
    LINK_send_byte(MACHINE_ID);
    LINK_send_byte(0x56);
    LINK_send_byte(0x00);
    LINK_send_byte(0x00);
}


void LINK_send_os(void)
{

    for(int i = 1; i < 9; i++)
    {
        prgm_header[i+2] = password[i];
    }


    uint8_t character_lookup_1[26] = {0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35};
    uint8_t character_lookup_2[26] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41};
    /*
    os_image[11] = password_buffer[0] + 0x30; //length of os name -> os, so os can delete itself...

    for(int i = 1; i <= 8; i++)
    {
    if(password_buffer[i] == 0)
    {
      os_image[8*i + 10] = 0;
      os_image[8*i + 11] = 0;
    }
    else
    {
      os_image[8*i + 10] = character_lookup_1[password_buffer[i] - 0x41];
      os_image[8*i + 11] = character_lookup_2[password_buffer[i] - 0x41];  
    }
    }

    */




    LINK_send_command(0xC9, 0x0B, prgm_header);
    for(int i = 0; i < 8; i ++)
    {
        LINK_wait_for_byte();
    }

    LINK_send_byte(MACHINE_ID);
    LINK_send_byte(0x56);
    LINK_send_byte(0);
    LINK_send_byte(0);
    //LINK_send_command(0x56,0,empty_array);
    //LINK_send_command(0x15,OS_SIZE,empty_array);

    uint16_t temp = OS_SIZE+2;
    LINK_send_byte(MACHINE_ID);
    LINK_send_byte(0x15);
    LINK_send_byte(temp & 0xff);
    LINK_send_byte((temp >> 8) & 0xff);


    LINK_send_array_with_checksum(os_image, OS_SIZE+2);


    for(int i = 0; i < 4; i ++)
    {
        LINK_wait_for_byte();
    }

    LINK_send_byte(MACHINE_ID);
    LINK_send_byte(0x92);
    LINK_send_byte(0);
    LINK_send_byte(0);

    LINK_send_key(0x09);            //clear input line
    LINK_send_key(0xfe63);          //"send("
    LINK_send_key(0x97);            //9
    LINK_send_key(0x3E);            //catalog
    LINK_send_key(0xA9);            //"p" in catalog
    for(int i = 0; i < 14; i ++)    //14 down -> prgm
    {
        LINK_send_key(0x04);
    }
    LINK_send_key(0x05);            //enter -> looks like this now: Send(9prgm

    for(int i = 1; i <= password[0]; i++) 
    {
        LINK_send_key(password[i] + 89);    //program name
    }
    LINK_send_key(0x05);    //enter

}

int LINK_check_password(void)
{
    uint8_t y[50];
    password_buffer[0] = 0;
    for(int i = 0; i < 7; i++)
    {
        y[i] = LINK_wait_for_byte();
    }
    for(int i = 1; i < 9; i++)
    {
        password_buffer[i] = LINK_wait_for_byte();
        if(password_buffer[i] != 0)
        {
            password_buffer[0] ++;
        }
    }
    LINK_wait_for_byte();
    LINK_wait_for_byte();

    int i = 0;
    while(password_buffer[i] == password[i])
    {
        i ++;
        if(i == 9)
        { 
            LINK_send_byte(MACHINE_ID2);
            LINK_send_byte(0x56);
            LINK_send_byte(0x0B);
            LINK_send_byte(0);
            LINK_send_byte(MACHINE_ID2);
            LINK_send_byte(0x09);
            LINK_send_byte(0x0B);
            LINK_send_byte(0);

            for(int i = 0; i < 12; i ++)
            {
                LINK_wait_for_byte();
            }

            LINK_send_byte(MACHINE_ID);
            LINK_send_byte(0x56);
            LINK_send_byte(0);
            LINK_send_byte(0);

            for(int i = 0; i < 4; i ++)
            {
                LINK_wait_for_byte();
            }

            LINK_send_byte(MACHINE_ID);
            LINK_send_byte(0x56);
            LINK_send_byte(0);
            LINK_send_byte(0);
            return 1;
        }
    }
    return 0;
}
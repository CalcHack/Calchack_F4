#ifndef LINKPORT_H
#define LINKPORT_H

#include "stm32f4xx_conf.h"

#define MACHINE_ID 0x03
#define MACHINE_ID2 0x83

#define LINK_TIMEOUT 7200000
#define LINK_BIT_DELAY 50
#define LINK_BYTE_DELAY 500

#define LINK_INIT_GPIO_CLOCK RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
#define LINK_GPIO_Speed GPIO_Speed_50MHz

//	RED = Tip
#define	LINK_RED_port		GPIOD
#define	LINK_RED_bit		GPIO_Pin_8

//	WHITE = Middle
#define	LINK_WHITE_port	        GPIOD
#define	LINK_WHITE_bit		GPIO_Pin_9

#define Breset BSRRH
#define Bset BSRRL

#define LINK_RED_high LINK_RED_port->Bset = LINK_RED_bit;
#define LINK_RED_low LINK_RED_port->Breset = LINK_RED_bit;
#define LINK_WHITE_high LINK_WHITE_port->Bset = LINK_WHITE_bit;
#define LINK_WHITE_low LINK_WHITE_port->Breset = LINK_WHITE_bit;

#define	LINK_RED_wait_until_high		while(!GPIO_ReadInputDataBit(LINK_RED_port, LINK_RED_bit));                                                
#define	LINK_RED_wait_until_low		while(GPIO_ReadInputDataBit(LINK_RED_port, LINK_RED_bit));

#define	LINK_WHITE_wait_until_high		  while(!GPIO_ReadInputDataBit(LINK_WHITE_port, LINK_WHITE_bit));
#define	LINK_WHITE_wait_until_low   while(GPIO_ReadInputDataBit(LINK_WHITE_port, LINK_WHITE_bit));


enum key
{
key_up = 0x1000000000000000,
key_down  = 0x8000000000000000,
key_left  = 0x4000000000000000,
key_right  = 0x2000000000000000,
key_0  = 0x0000000080000000,
key_1  = 0x0000000040000000,
key_2  = 0x0000004000000000,
key_3  = 0x0000400000000000,
key_4  = 0x0000000020000000,
key_5  = 0x0000002000000000,
key_6  = 0x0000200000000000,
key_7  = 0x0000000010000000,
key_8  = 0x0000001000000000,
key_9  = 0x0000100000000000,
key_enter = 0x0080000000000000,
key_del = 0x0000000000000100
};

extern uint8_t screenshot[768];
extern uint8_t framebuffer[96][64];
extern uint64_t keys;
extern int return_to_tios;
extern uint8_t password[9];


void LINK_init();
int16_t LINK_get_byte();
void LINK_transfer_framedata();
void LINK_send_command(uint8_t command_ID, uint16_t length, uint8_t data[]);
void LINK_send_byte (uint8_t byte);
void LINK_send_array(uint8_t array[], int length);
void LINK_send_key(uint16_t key);
void LINK_send_key_sequence(uint16_t key_sequence[], uint16_t length);
void LINK_send_array_with_checksum(const uint8_t data[], uint16_t length);
void LINK_get_screenshot(void);
void LINK_send_os(void);
int LINK_check_password(void);

#endif
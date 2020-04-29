/*
 * header_0.h
 *
 * Created: 4/20/2020 5:21:55 PM
 *  Author: tungh
 */ 

// https://github.com/Matiasus/ST7735
// file:///X:/X/X/X/X/X/AvrTFT.pdf

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/common.h>
#include <util/twi.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <string.h>

// TH: forces 16MHz CPU frequency to be considered by delay function.
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

#ifndef HEADER_0_H_
#define HEADER_0_H_

/////////////////////////////////////////////////////

#define BUADRATE 9600UL

// TH: div 8, 2x speed mode.
#define MYUBRR (F_CPU/8/BUADRATE-1)

// TH: initializes UART.
void uart_init_(void);

// TH: sends UART data.
void uart_send_(uint8_t);

// TH: represents user input via USART.
volatile uint8_t val=0;

#define H_CHAR_ 0x48
#define F_CHAR_ 0x46
#define C_CHAR_ 0x43
#define I_CHAR_ 0x49
#define T_CHAR_ 0x54
#define L_CHAR_ 0x4C

#define V_CHAR_ 0x56 // TH: raw V.
#define A_CHAR_ 0x41 // TH: calibrated V.

#define B_CHAR_ 0x42 // TH: raw B.
#define D_CHAR_ 0x44 // TH: calibrated B.

#define G_CHAR_ 0x47 // TH: raw G.
#define E_CHAR_ 0x45 // TH: calibrated G.

#define Y_CHAR_ 0x59 // TH: raw Y.
#define J_CHAR_ 0x4A // TH: calibrated Y.

#define O_CHAR_ 0x4F // TH: raw O.
#define K_CHAR_ 0x4B // TH: calibrated O.

#define R_CHAR_ 0x52 // TH: raw R.
#define M_CHAR_ 0x4D // TH: calibrated R.

/////////////////////////////////////////////////////

// TH: prints serial.
void PCprint(char strbuf[200]);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// TH: initializes TWI interface.
void TWIinit(void);

// TH: issues START condition transmission and waits for completion.
void TWIstart(void);

// TH: issues slave address and access request command byte.
void TWIwrite(uint8_t, uint8_t);

// TH: issues STOP  condition transmission and waits for completion.
void TWIstop(void);

// TH: reads data with NACK response.
uint8_t TWIread_nack(uint8_t);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// TH: initializes pin change interrupt.
void PCinit(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define I2C_AS72XX_SLAVE_ADDR_WRITE_          0x92 // TH: master write.
#define I2C_AS72XX_SLAVE_ADDR_READ_           0x93 // TH: master read.

#define I2C_AS72XX_SLAVE_ADDR_REG_STATUS_     0x00 // TH: status register addr.
#define I2C_AS72XX_SLAVE_STATUS_TX_VALID_     0x01 // TH: bit position.
#define I2C_AS72XX_SLAVE_STATUS_RX_VALID_     0x00 // TH: bit position.

#define I2C_AS72XX_SLAVE_ADDR_REG_WRITE_      0x01
#define I2C_AS72XX_SLAVE_ADDR_REG_READ_       0x02

#define I2C_AS72XX_VIRTUAL_HW_VERSION_LOW_    0x00
#define I2C_AS72XX_VIRTUAL_HW_VERSION_HIGH_   0x01

#define I2C_AS72XX_VIRTUAL_FW_VERSION_LOW_    0x02
#define I2C_AS72XX_VIRTUAL_FW_VERSION_HIGH_   0x03

#define I2C_AS72XX_VIRTUAL_CONTROL_           0x04
#define I2C_AS72XX_VIRTUAL_INT_T_             0x05
#define I2C_AS72XX_VIRTUAL_DEVICE_TEMP_       0x06
#define I2C_AS72XX_VIRTUAL_LED_CONTROL_       0x07

#define I2C_AS72XX_VIRTUAL_V_RAW_LOW_         0x08
#define I2C_AS72XX_VIRTUAL_V_RAW_HIGH_        0x09

#define I2C_AS72XX_VIRTUAL_V_CAL_ADDR_0_      0x14
#define I2C_AS72XX_VIRTUAL_V_CAL_ADDR_1_      0x15
#define I2C_AS72XX_VIRTUAL_V_CAL_ADDR_2_      0x16
#define I2C_AS72XX_VIRTUAL_V_CAL_ADDR_3_      0x17

#define I2C_AS72XX_VIRTUAL_B_RAW_LOW_         0x0A
#define I2C_AS72XX_VIRTUAL_B_RAW_HIGH_        0x0B

#define I2C_AS72XX_VIRTUAL_B_CAL_ADDR_0_      0x18
#define I2C_AS72XX_VIRTUAL_B_CAL_ADDR_1_      0x19
#define I2C_AS72XX_VIRTUAL_B_CAL_ADDR_2_      0x1A
#define I2C_AS72XX_VIRTUAL_B_CAL_ADDR_3_      0x1B

#define I2C_AS72XX_VIRTUAL_G_RAW_LOW_         0x0C
#define I2C_AS72XX_VIRTUAL_G_RAW_HIGH_        0x0D

#define I2C_AS72XX_VIRTUAL_G_CAL_ADDR_0_      0x1C
#define I2C_AS72XX_VIRTUAL_G_CAL_ADDR_1_      0x1D
#define I2C_AS72XX_VIRTUAL_G_CAL_ADDR_2_      0x1E
#define I2C_AS72XX_VIRTUAL_G_CAL_ADDR_3_      0x1F

#define I2C_AS72XX_VIRTUAL_Y_RAW_LOW_         0x0E
#define I2C_AS72XX_VIRTUAL_Y_RAW_HIGH_        0x0F

#define I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_0_      0x20
#define I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_1_      0x21
#define I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_2_      0x22
#define I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_3_      0x23

#define I2C_AS72XX_VIRTUAL_O_RAW_LOW_         0x10
#define I2C_AS72XX_VIRTUAL_O_RAW_HIGH_        0x11

#define I2C_AS72XX_VIRTUAL_O_CAL_ADDR_0_      0x24
#define I2C_AS72XX_VIRTUAL_O_CAL_ADDR_1_      0x25
#define I2C_AS72XX_VIRTUAL_O_CAL_ADDR_2_      0x26
#define I2C_AS72XX_VIRTUAL_O_CAL_ADDR_3_      0x27

#define I2C_AS72XX_VIRTUAL_R_RAW_LOW_         0x12
#define I2C_AS72XX_VIRTUAL_R_RAW_HIGH_        0x13

#define I2C_AS72XX_VIRTUAL_R_CAL_ADDR_0_      0x28
#define I2C_AS72XX_VIRTUAL_R_CAL_ADDR_1_      0x29
#define I2C_AS72XX_VIRTUAL_R_CAL_ADDR_2_      0x2A
#define I2C_AS72XX_VIRTUAL_R_CAL_ADDR_3_      0x2B

// TH: initializes AS7262.
void as7262_init_(void);

// TH: reads virtual register.
uint8_t as7262_read_virtual_(uint8_t);

// TH: implements I2C master receive.
uint8_t i2cm_read(uint8_t);

// TH: implements I2C master transmit.
void i2cm_write(uint8_t, uint8_t);

// TH: converts hex to float.
float convert_hex_to_float_(uint32_t);

// TH: computes floating point.
float hw_all__ = 0;

// TH: prints calibrated value from float.
void print_calibrated_(float);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
#define DEBUG_         0x01
#else
#define DEBUG_         0x00
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
#define DEBUG_TFT_CTC_ 1
#else
#define DEBUG_TFT_CTC_ 0
#endif

// TH: TIMER 1 COUNTER MAX.
#define TIMER1_MAX 65535UL

// TH: TIMER 1 OV RESOLUTION, in sec (i.e.  4.0960msec @ 16MHz).
// TH: TIMER 1 OV RESOLUTION, in sec (i.e. 32.7675msec @  2MHz).
#define TIMER1_OV_RESOLUTION  ((float)((float)1UL)/((float)F_CPU))*TIMER1_MAX

// TH: defines resolution for Timer 1 CTC mode, @ 16MHz.
#define TIMER1_TARGET_CTC_1SEC (float)(((float)1UL)/((float)TIMER1_OV_RESOLUTION))

// TH: counts interrupts.
volatile float timer1_resolution;

// TH: initializes TIMER 1.
void TC1init(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/Adafruit_ST77xx.h

#define ST77XX_SLPOUT     0x11

#define ST77XX_COLMOD     0x3A
#define ST77XX_COLMOD_12_ 0x03
#define ST77XX_COLMOD_16_ 0x05
#define ST77XX_COLMOD_18_ 0x06

#define ST77XX_DISPOFF    0x28
#define ST77XX_DISPON     0x29

#define ST77XX_CASET              0x2A
#define ST77XX_COL_S_HIGH_        0x00
#define ST77XX_COL_S_LOW_         0x00
#define ST77XX_COL_E_HIGH_        0x00

#define ST77XX_COL_S_LOW_MIN_                0x19 // TH: minimum active column boundary is NOT 0x00 !!

#define ST77XX_COL_E_LOW_MAX_THEORECTICAL_   0x7F // TH: 5 pixels per char (width), one pixel space.
#define ST77XX_COL_E_LOW_MAX_PORTRAIT_       0x66 // TH: in reality, only 13 columns available (7x5 resolution).

#define ST77XX_CHAR_WIDTH_        0x05 // TH: 5 pixels per char (width).

#define ST77XX_RASET              0x2B
#define ST77XX_ROW_S_HIGH_        0x00
#define ST77XX_ROW_S_LOW_         0x00
#define ST77XX_ROW_E_HIGH_        0x00

#define ST77XX_ROW_S_LOW_MIN_                0x01 // TH: minimum active row boundary (i.e. OR could be 0x00 as well).

#define ST77XX_ROW_E_LOW_MAX_THEORECTICAL_   0x9F // TH: 7 pixels per char, one pixel space.
#define ST77XX_ROW_E_LOW_MAX_PORTRAIT_       0x96 // TH: in reality, only at most 20 rows available (7x5 resolution).

#define ST77XX_CHAR_HEIGHT_       0x07 // TH: 7 pixels per char (height).

#define ROW_MAX_7_BY_5_           0x14 // TH: 20 rows    available (7x5 resolution).
#define COL_MAX_7_BY_5_           0x0D // TH: 13 columns available (7x5 resolution).

#define ST77XX_RAMWR              0x2C

#define ST77XX_MADCTL             0x36
#define ST77XX_MADCTL_MY          0x80
#define ST77XX_MADCTL_MX          0x40
#define ST77XX_MADCTL_MV          0x20
#define ST77XX_MADCTL_ML          0x10
#define ST77XX_MADCTL_RGB         0x00 // TH: RGB color filter panel.

#define ST77XX_COLOR_0_           0x07507 
#define ST77XX_COLOR_1_           0x00000 // 0xFFFFF 


#define ST77XX_CHAR_SIZE_ROW_     0x07
#define ST77XX_CHAR_SIZE_COL_     0x05

// TH: FONT_CHAR ...
const uint8_t FONT_CHAR[][ST77XX_CHAR_SIZE_ROW_] PROGMEM = {
{0x04, 0x0A, 0x11, 0x11, 0x1F, 0x11, 0x11}, // A
{0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E}, // B
{0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E}, // C
{0x1C, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1C}, // D
{0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F}, // E
{0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10}, // F
{0x0E, 0x10, 0x10, 0x17, 0x12, 0x12, 0x0E}, // G
{0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11}, // H
{0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1F}, // I
{0x1F, 0x01, 0x01, 0x01, 0x01, 0x09, 0x07}, // J
{0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11}, // K
{0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F}, // L
{0x11, 0x11, 0x1B, 0x15, 0x11, 0x11, 0x11}, // M
{0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x11}, // N
{0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // O
{0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10}, // P
{0x0F, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01}, // Q
{0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11}, // R
{0x0E, 0x11, 0x08, 0x04, 0x02, 0x11, 0x0E}, // S
{0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, // T
{0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // U
{0x11, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x04}, // V
{0x11, 0x11, 0x15, 0x15, 0x15, 0x1F, 0x0A}, // W
{0x11, 0x0A, 0x04, 0x04, 0x04, 0x0A, 0x11}, // X
{0x11, 0x0A, 0x04, 0x04, 0x04, 0x04, 0x04}, // Y
{0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F}, // Z
{0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E}, // 0
{0x04, 0x0C, 0x14, 0x04, 0x04, 0x04, 0x1F}, // 1
{0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F}, // 2
{0x1F, 0x01, 0x02, 0x04, 0x02, 0x01, 0x1F}, // 3
{0x01, 0x03, 0x05, 0x09, 0x1F, 0x01, 0x01}, // 4
{0x1F, 0x10, 0x1C, 0x02, 0x01, 0x02, 0x1C}, // 5
{0x0E, 0x11, 0x10, 0x10, 0x1E, 0x11, 0x0E}, // 6
{0x1F, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10}, // 7
{0x0E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x0E}, // 8
{0x0E, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x0E}, // 9
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // dummy.
};

// TH: specifies volatile data for debug ...
volatile uint8_t data;

#define NCHARS (sizeof tab_char_ / sizeof tab_char_[0])
const struct char_{char c_; uint8_t i_;} tab_char_[]  = {
{
'A',0
},
{
'B',1
},
{
'C',2
},
{
'D',3
},
{
'E',4
},
{
'F',5
},
{
'G',6
},
{
'H',7
},
{
'I',8
},
{
'J',9
},
{
'K',10
},
{
'L',11
},
{
'M',12
},
{
'N',13
},
{
'O',14
},
{
'P',15
},
{
'Q',16
},
{
'R',17
},
{
'S',18
},
{
'T',19
},
{
'U',20
},
{
'V',21
},
{
'W',22
},
{
'X',23
},
{
'Y',24
},
{
'Z',25
}
};

#define NNUMS (sizeof tab_num_ / sizeof tab_num_[0])
const struct num_{uint8_t n_; uint8_t i_;} tab_num_[]  = {
{0x0,26},
{0x1,27},
{0x2,28},
{0x3,29},
{0x4,30},
{0x5,31},
{0x6,32},
{0x7,33},
{0x8,34},
{0x9,35},
{0xA,0},
{0xB,1},
{0xC,2},
{0xD,3},
{0xE,4},
{0xF,5}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// TH: initializes SPI module.
void spi_init_(void);

// TH: initializes ST7735S.
void ST7735S_init_(void);

// TH: initializes display.
void display_init_(void);

// TH: sets window for memory write.
void spi_write_seq_window_(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);

// TH: sends SPI command to ST7735S, without params.
void spi_write_seq_cmd_(uint8_t);

// TH: sends SPI param to ST7735S.
void spi_write_seq_param_(uint32_t,uint8_t,uint8_t,uint8_t);

// TH: sends SPI command to ST7735S, with 1 param.
void spi_write_seq_cmd_param_(uint8_t, uint8_t);

// TH: sends SPI data to ST7735S.
void spi_write_seq_data_(uint8_t);

// TH: writes particular pattern to display.
void write_pattern_0_(void);

// TH: helps clear given window.
void write_pattern_1_(void);

// TH: writes particular character to display (i.e. 7x5), pixel-wise.
void write_char_(
uint8_t , 
uint8_t , uint8_t , uint8_t , uint8_t ,
uint8_t , uint8_t , uint8_t , uint8_t 
);

// TH: writes particular row of characters to display (i.e. 7x5), pixel-wise in portrait mode.
void write_row_portrait_(
uint8_t ,
uint8_t , uint8_t , uint8_t , uint8_t ,
uint8_t , uint8_t , uint8_t , uint8_t
);

// TH: writes particular text to one row (~ ended with newline character) to display (i.e. 7x5), pixel-wise in portrait mode.
void write_row_text_(
char * ptr_,
uint8_t , uint8_t , uint8_t , uint8_t ,
uint8_t , uint8_t , uint8_t , uint8_t
);

// TH: writes particular number to one row (~ ended with newline character) to display (i.e. 7x5), pixel-wise in portrait mode.
void write_row_number_(
uint32_t number_,
uint8_t , uint8_t , uint8_t , uint8_t ,
uint8_t , uint8_t , uint8_t , uint8_t
);

// TH: tracks what gets sent to display.
char * ptr_str_;
uint32_t number_;

// TH: caches coordinate boundaries.
uint8_t col_s_high_=0;
uint8_t col_s_low_ =0;
uint8_t col_e_high_=0;
uint8_t col_e_low_ =0;
uint8_t row_s_high_=0;
uint8_t row_s_low_ =0;
uint8_t row_e_high_=0;
uint8_t row_e_low_ =0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* HEADER_0_H_ */
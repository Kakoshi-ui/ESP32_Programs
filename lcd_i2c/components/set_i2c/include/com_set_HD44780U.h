#ifndef COM_SET_HD44780U_H_
#define COM_SET_HD44780U_H_

#define LCD_RS      0x01
#define LCD_RW      0x02
#define LCD_EN      0x04
#define FONT_LIGTH  0x08

#define PCF8574_SLV_ADDR_W 0x27 //Slave Address: 0x27 displaced 1 bit to left
#define PCF8574_SLV_ADDR_R 0x28 //Read Slave Address

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02

//Entry Mode Set
#define WR_MODE_BKW_LFT 0x04
#define WR_MODE_BKW_RGT 0x05
#define WR_MODE_FWD_LFT 0x06
#define WR_MODE_FWD_RGT 0x07

//Display On/Off Control
#define ENT_DISP_OFF 0x08
#define ENT_DISP_ON 0x0C
#define ENT_DISP_CUR_ON 0x0E
#define ENT_DISP_CUR_BNK_ON 0x0F

//Cursor or Display Shift

#endif/*COM_SET_HD44780U_H_*/
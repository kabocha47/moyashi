#include "iodefine.h"

#define LCD_RS	IO.PDR1.BIT.B0
#define LCD_RS_CMD		0
#define LCD_RS_DATA		1

#define LCD_RW	IO.PDR1.BIT.B1
#define LCD_RW_WRITE	0
#define LCD_RW_READ		1

#define LCD_E	IO.PDR1.BIT.B2
#define LCD_E_DISABLE	0
#define LCD_E_ENABLE	1

#define LCD_INPUT		{IO.PCR5=0x00; }
#define LCD_OUTPUT		{IO.PCR5=0xff; }
#define LCD_BUS	IO.PDR5.BYTE

#define START_LCD_ACC	{LCD_E= LCD_E_ENABLE; }
#define END_LCD_ACC		{LCD_E = LCD_E_DISABLE; }

#define LCD_WAIT_LOOP_FOR_1mSec	3500

#define LCD_CTRL_BIT	0x08
#define LCD_ON_BIT		0x04
#define LCD_CUR_BIT		0x02
#define LCD_BLINK_BIT	0x01

unsigned char lcd_disp_mode;


void lcd_wait(unsigned int mSec)
{
	unsigned int loop1, loop2;
	for (loop1 = 0; loop1 < mSec; loop1++) {
		for (loop2 = 0; loop2 < LCD_WAIT_LOOP_FOR_1mSec; loop2++);
	}
}


unsigned char LcdRead(unsigned char rs)
{
	unsigned char read_data; // 読み出したデータの格納変数。

	LCD_INPUT;
	LCD_RS = rs;
	LCD_RW = LCD_RW_READ;

	START_LCD_ACC
	{
		read_data = LCD_BUS;
	}
	END_LCD_ACC

	return read_data;
}

void LcdWrite(unsigned char data, unsigned char rs)
{
	while ((LcdRead(LCD_RS_CMD) & 0x80) != 0) ; // Busy flag Check

	LCD_OUTPUT;

	LCD_RS = rs;
	LCD_RW = LCD_RW_WRITE;

	START_LCD_ACC
	{
		LCD_BUS = data;
	}
	END_LCD_ACC
}


void InitLcd(void)
{
	{ // ポートの初期化

		IO.PCR1 = 0x07;
		//IO.PCR1.BIT.B0 = 1;
		//IO.PCR1.BIT.B1 = 1;
		//IO.PCR1.BIT.B2 = 1;

		LCD_RS = LCD_RS_CMD;
		LCD_RW = LCD_RW_WRITE;
		LCD_E  = LCD_E_DISABLE;

		LCD_BUS = 0x00;
		LCD_OUTPUT;
	}
	

	{ // LCD仕様書に記されていた初期化手順に従って、初期化をします。

		lcd_wait(15); // 45mSec
		START_LCD_ACC
		{
			LCD_BUS = 0x30; // 8bitで使用
		}
		END_LCD_ACC

		lcd_wait(5); // 5mSec
		START_LCD_ACC
		{
			LCD_BUS = 0x30; // 8bitで使用
		}
		END_LCD_ACC

		lcd_wait(1); // 1mSec
		START_LCD_ACC
		{
			LCD_BUS = 0x30; // 8bitで使用
		}
		END_LCD_ACC
 
		LcdWrite(0x38, LCD_RS_CMD); // 8bit. duty=1/16, 5x7

		LcdWrite(0x00, LCD_RS_CMD); // LCD OFF

		LcdWrite(0x01, LCD_RS_CMD); // 表示クリア

		LcdWrite(0x06, LCD_RS_CMD); // エントリモード, I/D=Increment, shiftなし
	}
	
	// 仕様書の初期化手順にはありませんが、表示をONしておきます。
	lcd_disp_mode = LCD_CTRL_BIT;
	lcd_disp_mode |= LCD_ON_BIT;
	LcdWrite(lcd_disp_mode, LCD_RS_CMD); // LCD ON (カーソル、ブリンク無し)
}

// 画面のクリアをします	
void LcdClear(void)
{
	LcdWrite(0x01, LCD_RS_CMD);
}

void LcdOn(void)
{
	lcd_disp_mode |= LCD_ON_BIT;
	LcdWrite(lcd_disp_mode, LCD_RS_CMD);
}

void LcdOff(void)
{
	lcd_disp_mode &= ~LCD_ON_BIT;
	LcdWrite(lcd_disp_mode, LCD_RS_CMD);
}

void LcdCurOn(void)
{
	lcd_disp_mode |= LCD_CUR_BIT;
	LcdWrite(lcd_disp_mode, LCD_RS_CMD);
}

void LcdCurOff(void)
{
	lcd_disp_mode &= ~LCD_CUR_BIT;
	LcdWrite(lcd_disp_mode, LCD_RS_CMD);
}

void LcdXY(unsigned char x, unsigned char y)
{
	unsigned char addr;
	addr = ((x-1) + (y-1) * 0x40) | 0x80;
	LcdWrite(addr, LCD_RS_CMD);
}

void LcdPuts(char *str)
{
	while (*str) {
		LcdWrite(*str, LCD_RS_DATA);
		str++;
	}
}


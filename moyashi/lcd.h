#ifndef _LCD_H_
#define _LCD_H_

// Lcdアクセス時に時間待ちをします
void lcd_wait(unsigned int mSec);

// Lcdからデータ読み込み
unsigned char LcdRead(unsigned char rs);

// Lcdへデータ書き込み
void LcdWrite(unsigned char data, unsigned char rs);

// Lcdの初期化をします
void InitLcd(void);

// 画面のクリアをします	
void LcdClear(void);

// LCD表示をオンします
void LcdOn(void);

// LCD表示をオフします
void LcdOff(void);

// LCDのカーソルを表示します
void LcdCurOn(void);

// LCDのカーソルを表示しません
void LcdCurOff(void);

// カーソル位置を移動します
void LcdXY(unsigned char x, unsigned char y);

// 文字列を表示します
void LcdPuts(char *str);

#endif /* _LCD_H_ */

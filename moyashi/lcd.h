#ifndef _LCD_H_
#define _LCD_H_

// Lcd�A�N�Z�X���Ɏ��ԑ҂������܂�
void lcd_wait(unsigned int mSec);

// Lcd����f�[�^�ǂݍ���
unsigned char LcdRead(unsigned char rs);

// Lcd�փf�[�^��������
void LcdWrite(unsigned char data, unsigned char rs);

// Lcd�̏����������܂�
void InitLcd(void);

// ��ʂ̃N���A�����܂�	
void LcdClear(void);

// LCD�\�����I�����܂�
void LcdOn(void);

// LCD�\�����I�t���܂�
void LcdOff(void);

// LCD�̃J�[�\����\�����܂�
void LcdCurOn(void);

// LCD�̃J�[�\����\�����܂���
void LcdCurOff(void);

// �J�[�\���ʒu���ړ����܂�
void LcdXY(unsigned char x, unsigned char y);

// �������\�����܂�
void LcdPuts(char *str);

#endif /* _LCD_H_ */

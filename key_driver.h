#ifndef _KEY_DRIVER_H
#define _KEY_DRIVER_H

//°´¼üÒý½Å
#define KEY1IN		P0CR &= ~BIT7
#define KEY2IN		P0CR &= ~BIT6
#define KEY3IN		P7CR &= ~BIT0
#define KEY4IN		P3CR &= ~BIT7

#define	KEY11OUT	P10CR |= BIT2
#define KEY12OUT	P10CR |= BIT3
#define KEY13OUT	P0CR |= BIT0

#define KEY11_H		P10 |= BIT2
#define KEY12_H		P10 |= BIT3
#define KEY13_H		P0 |= BIT0

#define KEY11_L		P10 &= ~BIT2
#define KEY12_L		P10 &= ~BIT3
#define KEY13_L		P0 &= ~BIT0

#define KEY1_Is_L	(P0 & BIT7) ? 0x00:0x01
#define KEY2_Is_L	(P0 & BIT6) ? 0x00:0x02
#define KEY3_Is_L	(P7 & BIT0) ? 0x00:0x03
#define KEY4_Is_L	(P3 & BIT7) ? 0x00:0x04

#define KEY_NUM_1     0x00010000
#define KEY_NUM_2     0x00000100
#define KEY_NUM_3     0x00000001
#define KEY_NUM_4     0x00020000
#define KEY_NUM_5     0x00000200
#define KEY_NUM_6     0x00000002
#define KEY_NUM_7     0x00030000
#define KEY_NUM_8     0x00000300
#define KEY_NUM_9     0x00000003
#define KEY_ESC       0x00040000
#define KEY_NUM_0     0x00000400
#define KEY_ENTER     0x00000004

void KeyIOInit(void);
void KeyCodeProcess(void);

#endif //_KEY_DRIVER_H
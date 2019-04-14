#include "config.h"

void Delay_us(uint16 cnt)
{
	uint16 i;
	for(i = cnt; i > 0; i--)
		_nop_();
}

//---------------------------------------------------------------------------------------------------------------//
//函数名称：Delay_ms
//函数功能: 延时cnt毫秒
//入口参数: cnt:延时毫秒数
//出口参数: 
//说    明：
//---------------------------------------------------------------------------------------------------------------//
void Delay_ms(uint16 cnt)
{
   uint16 i;
   uint16 j;
	 
   for(i=cnt;i>0;i--)
   {
      for(j=0;j<600;j++);	
   }   	
}

//---------------------------------------------------------------------------------------------------------------//
//函数名称：KeyIoInit				
//函数功能: 按键扫描IO口初始化
//入口参数: 
//出口参数: 
//说    明：
//---------------------------------------------------------------------------------------------------------------//
void KeyIOInit(void)
{
	KEY1IN;
	KEY2IN;
	KEY3IN;
	KEY4IN;

	KEY11OUT;
	KEY12OUT;
	KEY13OUT;

	KEY11_L;
	KEY12_L;
	KEY13_L;
}

//---------------------------------------------------------------------------------------------------------------//
//函数名称：Read_Key_Value				
//函数功能: 读取按键值
//入口参数: 
//出口参数: Temp1-Temp2：按键值代码
//说    明：为兼容上个版本的算法，将KEY1和KEY2两个标志位合成一个字节归入Temp1
//			根据行列发送数据不一样读取返回的按键值代码
//---------------------------------------------------------------------------------------------------------------//
uint32 Read_Key_Value(void)
{
	uint32 Temp1 = 0;
	uint32 Temp2 = 0;
	uint32 Temp3 = 0;
	uint32 Temp4 = 0;

	KEY11_L;
	KEY12_H;
	KEY13_H;
	Delay_us(500);
	Temp1 |= (uint32)(KEY1_Is_L) << 16;
	Temp2 |= (uint32)(KEY2_Is_L) << 16;
	Temp3 |= (uint32)(KEY3_Is_L) << 16;
	Temp4 |= (uint32)(KEY4_Is_L) << 16;

	KEY11_H;
	KEY12_L;
	KEY13_H;
	Delay_us(500);
	Temp1 |= (uint32)(KEY1_Is_L) << 8;
	Temp2 |= (uint32)(KEY2_Is_L) << 8;
	Temp3 |= (uint32)(KEY3_Is_L) << 8;
	Temp4 |= (uint32)(KEY4_Is_L) << 8;

	KEY11_H;
	KEY12_H;
	KEY13_L;
	Delay_us(500);
	Temp1 |= (uint32)(KEY1_Is_L);
	Temp2 |= (uint32)(KEY2_Is_L);
	Temp3 |= (uint32)(KEY3_Is_L);
	Temp4 |= (uint32)(KEY4_Is_L);

	KEY11_L;
	KEY12_L;
	KEY13_L;
	Delay_us(500);

	return (Temp1 + Temp2 + Temp3 + Temp4);
}

//---------------------------------------------------------------------------------------------------------------//
//函数名称：ScanKey				
//函数功能: 按键检测扫描
//入口参数: 
//出口参数: 
//说    明：连续两次读取按键值，相等就处理，消抖10mS
//---------------------------------------------------------------------------------------------------------------//
uint32 ScanKey(void)
{
	uint32 ReadKey1,ReadKey2;
	if(((P0 & 0xC0) != 0xC0) || ((P3 & 0x80) != 0x80) || ((P7 & 0x01) != 0x01))  //有按键按下
	{
		ReadKey1 = Read_Key_Value();
		Delay_ms(10);
		ReadKey2 = Read_Key_Value();
		if(ReadKey1 == ReadKey2)
		{
			return ReadKey1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}	
}

//---------------------------------------------------------------------------------------------------------------//
//函数名称：KeyCodeProcess
//函数功能: 对于检测到的按键值进行处理
//入口参数: 
//出口参数: 
//说    明：
//---------------------------------------------------------------------------------------------------------------//
void KeyCodeProcess(void)
{
	uint32 KeyNum;
	KeyNum = ScanKey();

	switch(KeyNum)
	{
		case KEY_NUM_0:
	    case KEY_NUM_1:
	    case KEY_NUM_2:
	    case KEY_NUM_3:
	    case KEY_NUM_4:
	    case KEY_NUM_5:
	    case KEY_NUM_6:
	    case KEY_NUM_7:
	    case KEY_NUM_8:
	    case KEY_NUM_9:
			BELL_ON;
			break;
		case KEY_ENTER:

			break;
		case KEY_ESC: 

			break;

		default:
			BELL_OFF;
			break;
	}
}
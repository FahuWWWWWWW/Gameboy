#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sram.h"
#include "malloc.h" 
#include "sdio_sdcard.h"
#include "w25qxx.h"
#include "ff.h"
#include "exfuns.h"
#include "string.h"
#include "nes_main.h" 

int main(void)
{
 	u32 total,free;
	u8 t=0;	
	u8 res=0;
	
	HAL_Init();                   	//��ʼ��HAL��    
	Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	LED_Init();						//��ʼ��LED	
	KEY_Init();						//��ʼ��KEY
	LCD_Init();                     //��ʼ��LCD
#ifndef NO_SRAMEX
	SRAM_Init();					//��ʼ���ⲿSRAM  
#endif
	W25QXX_Init();				    //��ʼ��W25Q256
	
	my_mem_init(SRAMIN);			//��ʼ���ڲ��ڴ��
#ifndef NO_SRAMEX
	my_mem_init(SRAMEX);			//��ʼ���ⲿ�ڴ��
#endif	

   	POINT_COLOR=RED;
    
 	while(SD_Init())//��ⲻ��SD��
	{
		LCD_ShowString(30,150,200,16,16,"SD Card Error!");
		delay_ms(500);					
		LCD_ShowString(30,150,200,16,16,"Please Check! ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
 	exfuns_init();							//Ϊfatfs��ر��������ڴ�				 
  f_mount(fs[0],"0:",1); 					//����SD�� 

	LCD_Fill(30,150,240,150+16,WHITE);		//�����ʾ			  
	while(exf_getfree("0:",&total,&free))	//�õ�SD������������ʣ������
	{
		LCD_ShowString(30,150,200,16,16,"SD Card Fatfs Error!");
		delay_ms(200);
		LCD_Fill(30,150,240,150+16,WHITE);	//�����ʾ			  
		delay_ms(200);
		LED0=!LED0;//DS0��˸
	}
	LCD_Clear(BLACK);	
	nes_load("0:/game.nes");
	while(1)
	{
		t++; 
		delay_ms(200);		 			   
		LED0=!LED0;
	}	
}


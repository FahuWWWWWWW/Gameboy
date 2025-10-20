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
	
	HAL_Init();                   	//初始化HAL库    
	Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	LED_Init();						//初始化LED	
	KEY_Init();						//初始化KEY
	LCD_Init();                     //初始化LCD
#ifndef NO_SRAMEX
	SRAM_Init();					//初始化外部SRAM  
#endif
	W25QXX_Init();				    //初始化W25Q256
	
	my_mem_init(SRAMIN);			//初始化内部内存池
#ifndef NO_SRAMEX
	my_mem_init(SRAMEX);			//初始化外部内存池
#endif	

   	POINT_COLOR=RED;
    
 	while(SD_Init())//检测不到SD卡
	{
		LCD_ShowString(30,150,200,16,16,"SD Card Error!");
		delay_ms(500);					
		LCD_ShowString(30,150,200,16,16,"Please Check! ");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
 	exfuns_init();							//为fatfs相关变量申请内存				 
  f_mount(fs[0],"0:",1); 					//挂载SD卡 

	LCD_Fill(30,150,240,150+16,WHITE);		//清除显示			  
	while(exf_getfree("0:",&total,&free))	//得到SD卡的总容量和剩余容量
	{
		LCD_ShowString(30,150,200,16,16,"SD Card Fatfs Error!");
		delay_ms(200);
		LCD_Fill(30,150,240,150+16,WHITE);	//清除显示			  
		delay_ms(200);
		LED0=!LED0;//DS0闪烁
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


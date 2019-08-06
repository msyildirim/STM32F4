/*GPIO_InitTypeDef has 5 options:

GPIO_Pin: Choose pins you will use for set settings
GPIO_Mode: Choose mode of operation. Look down for options
GPIO_OType: Choose output type
GPIO_PuPd: Choose pull resistor
GPIO_Speed: Choose pin speed
*/
#include "stm32f4xx.h"

#include "stm32f4xx_rcc.h"

#include "stm32f4xx_gpio.h"

 

void Delay(__IO uint32_t nCount)

{

    while (nCount--);

}

 

int main(void)

{
	//RCC(reset and clock control) ile AHB1 bus'indaki(butun GPIO'lar bu bus a bagli) A ve D portlarinda clock enable edilir
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //button pin_A0 da
 
		////kart uzerindaki internal ledler D portunda 12-13-14 uncu pinlerde
	
    GPIO_InitTypeDef GPIO_InitDef;

    GPIO_InitDef.GPIO_Pin = GPIO_Pin_13;

    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;

    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;

    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;//pin output oldugu icin gerek yok

    GPIO_InitDef.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOD, &GPIO_InitDef);
	
	/////////////button/////////////////

     GPIO_InitDef.GPIO_Pin = GPIO_Pin_0;

    GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;

    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;//Output type push-pull

    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;//With pull down resistor yani buttona bastigimizda 1 olacak basili degilken 0

    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitDef);
		while(1){

    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)

    {
				Delay(8000000);//1 sn bekletiyorum yoksa elimi butondan cekene kadar tekrar toggle oluyor
        GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
        

    }
	}

}

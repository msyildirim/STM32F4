#include "stm32f4xx.h"

#include "stm32f4xx_rcc.h"

#include "stm32f4xx_gpio.h"

#include "stm32f4xx_usart.h"

void USART_Config(void){
 // Enable clock for GPIOB
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
 // Enable clock for USART1
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
 // Connect PB6 to USART1_Tx
 GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
 // Connect PB7 to USART1_Rx
 GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
 // Initialization of GPIOB
 GPIO_InitTypeDef GPIO_InitStruct;
 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
 GPIO_Init(GPIOB, &GPIO_InitStruct);
 // Initialization of USART1
 USART_InitTypeDef USART_InitStruct;
 USART_InitStruct.USART_BaudRate = 9600;
 USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 USART_InitStruct.USART_Parity = USART_Parity_No;
 USART_InitStruct.USART_StopBits = USART_StopBits_1;
 USART_InitStruct.USART_WordLength = USART_WordLength_8b;
 USART_Init(USART1, &USART_InitStruct);
 // Enable USART1
 USART_Cmd(USART1, ENABLE);
}

void USART_PutChar(char c)
{
  // Wait until transmit data register is empty
  while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
  // Send a char using USART1
  USART_SendData(USART1, c);
}

void USART_PutString(char *s)
{
    // Send a string
    while (*s)
    {
        USART_PutChar(*s++);
    }
}


uint16_t USART_GetChar()
{
    // Wait until data is received
    while (!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
    // Read received char
    return USART_ReceiveData(USART1);
} 

int main(void)
{
    // Enable clock for GPIOD (for orange LED)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    // Initialization of GPIOD (for orange LED)
    GPIO_InitTypeDef GPIO_InitDef;
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitDef);
    // Call USART1 configuration
    USART_Config();
    // Send "Hello, World!" to PC
    USART_PutString("Hello, World!\n");
    while (1)
    {
      // Get a char from PC
      uint16_t data = USART_GetChar();
      if (data == 'H')
      {
          // If received char is 'H' then turn on orange LED
          GPIO_SetBits(GPIOD, GPIO_Pin_13);
      }
      else if (data == 'L')
      {
          // If received char is 'L' then turn off orange LED
          GPIO_ResetBits(GPIOD, GPIO_Pin_13);
      }

  }

}

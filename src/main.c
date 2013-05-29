/**
 ******************************************************************************
 * @file    Examples/GPIOToggle/main.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    09/13/2010
 * @brief   Main program body.
 ******************************************************************************
 * @copy
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "STM32vldiscovery.h"
#include <stdio.h>
/** @addtogroup Examples
 * @{
 */

/* Private typedef --------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured,
	 this is done through SystemInit() function which is called from startup
	 file (startup_stm32f10x_xxb.s) before to branch to application main.
	 To reconfigure the default setting of SystemInit() function, refer to
	 system_stm32f10x.c file
	 */

	/* Configure all unused GPIO port pins in Analog Input mode (floating input
	 trigger OFF), this will reduce the power consumption and increase the device
	 immunity against EMI/EMC *************************************************/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	// Initialize USART1_Tx
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// Initialize USART1_RX
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	USART_InitTypeDef USART_InitStructure;
	// Initialize USART structure
	USART_StructInit(&USART_InitStructure);
	// Modify USART_InitStructure for non - default values , e.g.
	// USART_InitStructure . USART_BaudRate = 38400;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, DISABLE);
	STM32vldiscovery_LEDInit(LED3);
//	STM32vldiscovery_LEDInit(LED4);
	while (1)
	{
//		/* Turn on LD2 and LD3 */
//		STM32vldiscovery_LEDOn(LED3);
//		STM32vldiscovery_LEDOn(LED4);
//		/* Insert delay */
//		Delay(0x6FFFF);
//
//		/* Turn off LD3 and LD4 */
//		STM32vldiscovery_LEDOff(LED3);
//		STM32vldiscovery_LEDOff(LED4);
//		/* Insert delay */
//		Delay(0x6FFFF);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE ) == RESET)
			;
		USART1 ->DR = 'a';

		printf("ok! I am fine!\n");

		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE ) == RESET)
			;
		USART1 ->DR = 'b';

		GPIO_SetBits(GPIOC, GPIO_Pin_9 );
		Delay(0x6FFFF);
		GPIO_ResetBits(GPIOC, GPIO_Pin_9 );
		Delay(0x6FFFF);

		GPIOC ->BSRR = GPIO_Pin_9;
		Delay(0x6FFFF);
		GPIOC ->BRR = GPIO_Pin_9;
		Delay(0x6FFFF);

		GPIO_SetBits(GPIOC, GPIO_Pin_8 );
		Delay(0x6FFFF);
		GPIO_ResetBits(GPIOC, GPIO_Pin_8 );
		Delay(0x6FFFF);
	}
}

/**
 * @brief  Inserts a delay time.
 * @param  nCount: specifies the delay time length.
 * @retval None
 */
void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount--)
		;
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

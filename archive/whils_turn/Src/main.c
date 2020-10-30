/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t byte;
UART_HandleTypeDef huart2;
uint8_t byte_2;
volatile HAL_StatusTypeDef r;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  TIM3->CCR2 = 0;
  TIM3->CCR1 = 0;

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_UART_Receive_IT(&huart2, &byte, 1); // start the interrupt for data receiving
  while (1)
  {
//	 TIM3->CCR1 =
//	 printf("Success!\n");
	 HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
//	 us_delay(1000);
	 HAL_Delay(300);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if(GPIO_Pin == GPIO_PIN_0) { // button hendler
		static uint32_t last_change_tick;
		if( HAL_GetTick() - last_change_tick < 50 ) {
	       return;
		}
		// do
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
		last_change_tick = HAL_GetTick();

	}
}

void reset_10_11_pins() {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 0);
}

unsigned char left[100] = "LEFT\n";
unsigned char stop[100] = "STOP\n";
unsigned char right[100] = "RIGHT\n";
//unsigned char pow_frame[100] = "POWER %d\n";
unsigned char pow_res[100];
unsigned char pow_inc[100] = "POWER UP + 15%\n";
unsigned char pow_dec[100] = "POWER UP - 15%\n";
unsigned char pow_min[100] = "POWER DOWN\n";
unsigned char pow_max[100] = "POWER MAX\n";


// receive and send data through bluetooth
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
	  switch(byte) {
	  case '1': {
		  reset_10_11_pins();
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, 1);
		  HAL_UART_Transmit(&huart2, left, strlen((char*)left), 100);
//		  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
//		  str2[99] = '\0';
		  break;
	  }
	  case '2':{
		  reset_10_11_pins();
		  HAL_UART_Transmit(&huart2, stop, strlen((char*)stop), 100);
		  break;
	  }
	  case '3':{
		  reset_10_11_pins();
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 1);
		  HAL_UART_Transmit(&huart2, right, strlen((char*)right), 100);
		  break;
	  }
	  case '4': {
		  if (TIM3->CCR1 + 10000 < TIM3->ARR) {
			  TIM3->CCR1 += 10000;
			  sprintf(pow_res, "POWER %d\n", (int)((double)TIM3->CCR1 / TIM3->ARR * 100.0));
			  HAL_UART_Transmit(&huart2, pow_res, strlen((char*)pow_res), 100);
		  } else {
			  HAL_UART_Transmit(&huart2, pow_max, strlen((char*)pow_max), 100);
		  }
		  break;
	  }
	  case '5': {
		  if (TIM3->CCR1 - 10000 < TIM3->CCR1) {
			  TIM3->CCR1 -= 10000;
//			  HAL_UART_Transmit(&huart2, pow_dec, strlen((char*)pow_dec), 100);
			  sprintf(pow_res, "POWER %d\n", (int)((double) TIM3->CCR1 / TIM3->ARR * 100.0));
			  HAL_UART_Transmit(&huart2, pow_res, strlen((char*)pow_res), 100);
		  } else {
			  HAL_UART_Transmit(&huart2, pow_min, strlen((char*)pow_min), 100);
		  }
		  break;
	  }
	  }
	  HAL_UART_Receive_IT(&huart2, &byte, 1);
	}

}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     text: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

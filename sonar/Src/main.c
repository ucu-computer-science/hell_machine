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

uint8_t byte;
UART_HandleTypeDef huart2;
uint8_t byte_2;
volatile HAL_StatusTypeDef r;
unsigned char str1[100] = "NOT STR\n";
unsigned char str2[100] = "STR\n";
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// for sonar
typedef enum state_t {
 IDLE_S,
 TRIGGERING_S,
 WAITING_FOR_ECHO_START_S,
 WAITING_FOR_ECHO_STOP_S,
 TRIG_NOT_WENT_LOW_S,
 ECHO_TIMEOUT_S,
 ECHO_NOT_WENT_LOW_S,
 READING_DATA_S,
 ERROR_S
} state_t;

volatile state_t state = IDLE_S;


volatile uint32_t echo_start;
volatile uint32_t echo_finish;
volatile uint32_t measured_time;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//char* print_n(uint32_t n, char* str) {
//	for (int i = 0; i < 32; ++i) {
//	    if (n & 1)
//	    	str[i] = "1";
//	    else
//	    	str[i] = "0";
//	    n >>= 1;
//	}
//	str[33] = "\0";
//	return str;
//}

#define LOOP_FREQ (SystemCoreClock/4000000)
// LOOP_FREQ == 6 для 24МГц
// LOOP_FREQ == 16 для 64МГц
// LOOP_FREQ == 18 для 72МГц

//! Затримка в мікросекундах.
//! Увага! Не працюватиме за частот, менших за 4МГц, через значення LOOP_FREQ
//! ЗАтримка буде трішки більшою за задану, але на лічені такти.
// additional source for timers: https://indrekis2.blogspot.com/2016/02/stm32.html
// source: http://indrekis2.blogspot.com/2016/10/stm32_20.html
inline void udelay (uint32_t useconds) {
 useconds *= LOOP_FREQ;

    asm volatile("   mov r0, %[useconds]    \n\t"
                 "1: subs r0, #1            \n\t"
                 "   bhi 1b                 \n\t"
                 :
                 : [useconds] "r" (useconds)
                 : "r0");
}
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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)) {
   // Помилка -- імпульсу не було, а на Echo вже одиниця
     HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET); // Синім позначатимемо помилку
     printf("Error -- Echo line is high, though no impuls was given\n");
     while(1); // Зависаємо
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_UART_Receive_IT(&huart2, &byte, 1); // start the interrupt for data receiving
  while (1)
  {
//	 printf("Success!\n");
//	 HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
//	 us_delay(1000);
//	 HAL_Delay(300);
     /* USER CODE END WHILE */

     /* USER CODE BEGIN 3 */
	 HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
	 udelay(16);
	 HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);

	 state = WAITING_FOR_ECHO_START_S;

	 while( state == WAITING_FOR_ECHO_START_S && state != ERROR_S )
	 {}
	 if ( state == ERROR_S )
	 {
	    printf("Unexpected error while waiting for ECHO to start.\n");
	    continue;
	 }
	 while( state == WAITING_FOR_ECHO_STOP_S && state != ERROR_S ) {}
	 if ( state == ERROR_S ) {
	    printf("Unexpected error while waiting for ECHO to finish.\n");
	    continue;
	 }

	 uint32_t distance = measured_time / 58;
	 //! Увага, не забудьте додати:
	 // monitor arm semihosting enable
	 // До  Debug Configurations -> Startup Tab:
	 char str[10];
	 sprintf( str, "%ld", measured_time );
	 HAL_UART_Transmit(&huart2, str, strlen((char*)str), 100);
	 sprintf( str, "%ld", distance );
	 HAL_UART_Transmit(&huart2, str, strlen((char*)str), 100);
//	 printf("Time: %lu us, distance: %lu cm\n", measured_time, distance);
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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

uint32_t get_us(void) {

    uint32_t usTicks = HAL_RCC_GetSysClockFreq() / 1000000;
    register uint32_t ms, cycle_cnt;
    do {
        ms = HAL_GetTick();
        cycle_cnt = SysTick->VAL;
    } while (ms != HAL_GetTick());
    return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

void us_delay(uint32_t usec) { // bug; o not make a dillay
	if (usec < 2) {
		usec = 2;
	}
	us_TIM->ARR = usec - 1;	// set period
	us_TIM->EGR = 1;			// re-initialise the timer
	us_TIM->SR &= ~1;			// reset the update event flag flag
	us_TIM->CR1 |= 1;			// enable the counter
	while((us_TIM->SR&0x0001) != 1) {} // do not make a loop
	us_TIM->SR &= ~(0x0001);		// reset update event flag
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if(GPIO_Pin == GPIO_PIN_0) { // button hendler
		static uint32_t last_change_tick;
		if( HAL_GetTick() - last_change_tick < 50 ) {
	       return;
		}
		// do
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
		last_change_tick = HAL_GetTick();

	} else if (GPIO_Pin == ECHOI_Pin) { // sonar handler
	   // source: https://indrekis2.blogspot.com/2016/10/hc-sr04-gpiohal.html
	   switch (state) {
		  case WAITING_FOR_ECHO_START_S: {
			 echo_start =  get_us();
			 state = WAITING_FOR_ECHO_STOP_S;
			 break;
		  }
		  case WAITING_FOR_ECHO_STOP_S: {
			 echo_finish = get_us();
			 measured_time = echo_finish - echo_start;
			 state = READING_DATA_S;
			 break;
		  }
	  default:
		  state = ERROR_S;
	  }
   }
}

// receive and send data through bluetooth
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
	  if (byte == '1'){
		  HAL_UART_Transmit(&huart2, str2, strlen((char*)str2), 100);
		  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
		  str2[99] = '\0';
	  }
	  if (byte == '2') {
		  HAL_UART_Transmit(&huart2, str1, strlen((char*)str1), 100);
		  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
		  str1[99] = '\0';
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

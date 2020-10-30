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
#define and &&
#define or ||
#define not !
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

static void MX_GPIO_Init(void);

static void MX_TIM1_Init(void);

static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
UART_HandleTypeDef huart2;
uint8_t byte[];
volatile char result;
volatile int previous_car_speed = 0;
volatile int car_speed = 0;
unsigned char enabled[100] = "ENABLED\n";
unsigned char disabled[100] = "DISABLED\n";
unsigned char error[100] = "ERROR\n";
unsigned char left[100] = "LEFT\n";
unsigned char up[100] = "UP\n";
unsigned char down[100] = "DOWN\n";
unsigned char right[100] = "RIGHT\n";
unsigned char forward[100] = "FORWARD\n";
unsigned char backward[100] = "BACKWARD\n";
unsigned char message[100];
uint8_t direction = 1;
uint8_t car_enabled = 1;
uint8_t rotating = 0;
uint8_t rotating_direction = 0;
char speed[100];

void send_message(unsigned char message[]) {
    __disable_irq();
    HAL_UART_Transmit(&huart2, message, strlen((char *) message), 100);
    __enable_irq();
}

inline void stop_car() {
    car_enabled = 0;
    HAL_GPIO_WritePin(BREAK_GPIO_Port, BREAK_Pin, GPIO_PIN_RESET);
}

inline void unbreak_car() {
    car_enabled = 1;
    HAL_GPIO_WritePin(BREAK_GPIO_Port, BREAK_Pin, GPIO_PIN_SET);
}

inline void set_direction(uint8_t dir) {
    if (dir == 0) {
        HAL_GPIO_WritePin(BACK_RIGHT_GPIO_Port, BACK_RIGHT_Pin, 1);
        HAL_GPIO_WritePin(BACK_LEFT_GPIO_Port, BACK_LEFT_Pin, 0);
    } else {
        HAL_GPIO_WritePin(BACK_RIGHT_GPIO_Port, BACK_RIGHT_Pin, 0);
        HAL_GPIO_WritePin(BACK_LEFT_GPIO_Port, BACK_LEFT_Pin, 1);
    }
}

inline void set_car_speed(uint8_t speed) {
    if (car_enabled == 0) return;
    TIM1->CCR1 = speed;
}

//inline void start_car() {
//    for (int i = 0; i < 10000; i++) {
//    	TIM1->CCR1 = 9;
//    }
//    TIM1->CCR1 = 0;
//}

inline void start_compressor() {
    HAL_GPIO_WritePin(COMPRESSOR_GPIO_Port, COMPRESSOR_Pin, GPIO_PIN_RESET);
}

inline void stop_compressor() {
    HAL_GPIO_WritePin(COMPRESSOR_GPIO_Port, COMPRESSOR_Pin, GPIO_PIN_SET);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        switch (byte[0]) {
            case 'D': {
                __disable_irq();
                unbreak_car();
                send_message(enabled);
                __enable_irq();
                break;
            }
            case 'd': {
                __disable_irq();
                stop_car();
                send_message(disabled);
                __enable_irq();
                break;
            }
            case 'X': {
                __disable_irq();
                start_compressor();
                send_message(up);
                __enable_irq();
                break;
            }
            case 'x': {
                __disable_irq();
                stop_compressor();
                send_message(down);
                __enable_irq();
                break;
            }
            case 'F': {
                __disable_irq();
                direction = 1;
                send_message(forward);
                __enable_irq();
                break;
                case 'B': {
                    __disable_irq();
                    direction = 0;
                    send_message(backward);
                    __enable_irq();
                    break;
                }
                case 'L': {
                    __disable_irq();
//				rotating = 1;
//				rotating_direction = 0;
                    HAL_GPIO_WritePin(TURNR_GPIO_Port, TURNR_Pin, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(TURNL_GPIO_Port, TURNL_Pin, GPIO_PIN_RESET);
                    for (int i = 0; i < 800000; i++) {}
                    HAL_GPIO_WritePin(TURNR_GPIO_Port, TURNR_Pin, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(TURNL_GPIO_Port, TURNL_Pin, GPIO_PIN_SET);
                    send_message(left);
                    __enable_irq();
                    break;
                }
                case 'R': {
                    __disable_irq();
//				rotating = 1 ;
//				rotating_direction = 1;
                    HAL_GPIO_WritePin(TURNR_GPIO_Port, TURNR_Pin, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(TURNL_GPIO_Port, TURNL_Pin, GPIO_PIN_SET);
                    for (int i = 0; i < 800000; i++) {}
                    HAL_GPIO_WritePin(TURNR_GPIO_Port, TURNR_Pin, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(TURNL_GPIO_Port, TURNL_Pin, GPIO_PIN_SET);
                    send_message(right);
                    __enable_irq();
                    break;
                }
                case '0': {
                    __disable_irq();
                    car_speed = 0;
                    __enable_irq();
                    break;
                }
                case '1': {
                    __disable_irq();
                    car_speed = 1;
                    __enable_irq();
                    break;
                }
                case '2': {
                    __disable_irq();
                    car_speed = 2;
                    __enable_irq();
                    break;
                }
                case '3': {
                    __disable_irq();
                    car_speed = 3;
                    __enable_irq();
                    break;
                }
                case '4': {
                    __disable_irq();
                    car_speed = 4;
                    __enable_irq();
                    break;
                }
                case '5': {
                    __disable_irq();
                    car_speed = 5;
                    __enable_irq();
                    break;
                }
                case '6': {
                    __disable_irq();
                    car_speed = 6;
                    __enable_irq();
                    break;
                }
                case '7': {
                    __disable_irq();
                    car_speed = 7;
                    __enable_irq();
                    break;

                }
                case '8': {
                    __disable_irq();
                    car_speed = 8;
                    __enable_irq();
                    break;
                }
                case '9': {
                    __disable_irq();
                    car_speed = 9;
                    __enable_irq();
                    break;
                }
                default: {
                    send_message(error);
                }

            }

        }
        __disable_irq();
        set_direction(direction);
        set_car_speed(car_speed);
//	if (rotating == 1 and car_enabled == 1) {
//		rotating = 0;
//		if (rotating_direction == 1) {
//			HAL_GPIO_WritePin(TURNR_GPIO_Port, TURNR_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(TURNL_GPIO_Port, TURNL_Pin, GPIO_PIN_RESET);
//		} else {
//			HAL_GPIO_WritePin(TURNR_GPIO_Port, TURNR_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(TURNL_GPIO_Port, TURNL_Pin, GPIO_PIN_RESET);
//		}
//
//	} else {
//		HAL_GPIO_WritePin(TURNR_GPIO_Port, TURNR_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(TURNL_GPIO_Port, TURNL_Pin, GPIO_PIN_SET);
//	}
        sprintf(speed, "SPEED: %d\n", car_speed);
        send_message(speed);
        __enable_irq();
        HAL_UART_Receive_IT(&huart2, byte, 1);
    }
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
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
    MX_TIM1_Init();
    MX_USART2_UART_Init();
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    /*PreSet all pins*/
    HAL_GPIO_WritePin(COMPRESSOR_GPIO_Port, COMPRESSOR_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BACK_RIGHT_GPIO_Port, BACK_RIGHT_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BACK_LEFT_GPIO_Port, BACK_LEFT_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BREAK_GPIO_Port, BREAK_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TURNL_GPIO_Port, TURNL_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TURNR_GPIO_Port, TURNR_Pin, GPIO_PIN_SET);
    HAL_UART_Receive_IT(&huart2, byte, 1);
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
        HAL_Delay(500);
//        HAL_UART_Transmit(&huart2, result, strlen((char *) result), 100);
        /*MY MAIN CODE BEGIN*/

        /*MY MAIN CODE END*/
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 192;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
        Error_Handler();
    }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void) {

    /* USER CODE BEGIN TIM1_Init 0 */

    /* USER CODE END TIM1_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    /* USER CODE BEGIN TIM1_Init 1 */

    /* USER CODE END TIM1_Init 1 */
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 959;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 10;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM1_Init 2 */

    /* USER CODE END TIM1_Init 2 */
    HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void) {

    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART2_Init 2 */

    /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOE, COMPRESSOR_Pin | BREAK_Pin | BACK_LEFT_Pin | BACK_RIGHT_Pin
                             | TURNL_Pin | TURNR_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);

    /*Configure GPIO pin : PA0 */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : COMPRESSOR_Pin BREAK_Pin BACK_LEFT_Pin BACK_RIGHT_Pin
                             TURNL_Pin TURNR_Pin */
    GPIO_InitStruct.Pin = COMPRESSOR_Pin | BREAK_Pin | BACK_LEFT_Pin | BACK_RIGHT_Pin
                          | TURNL_Pin | TURNR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /*Configure GPIO pins : PD13 PD14 PD15 */
    GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>

#include "mb.h" //MODBUS RTU SLAVE
#include "GlobalVar.h"
#include "FbTs.h"
#include "FbBlink.h"
#include "FbFilterA.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SetBit(Var,Bit)   ( Var = Var |  (1 << (Bit)) )
#define ResetBit(Var,Bit) ( Var = Var & ~(1 << (Bit)) )

#define USER_LED_ON() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)
#define USER_LED_OFF() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)
//#define USER_BUTTON_STATE() (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != GPIO_PIN_SET)

#define millis() HAL_GetTick() //Arduino function.
#define Reboot_CPU() HAL_NVIC_SystemReset()

#define MODBUS_RTU_SLAVE_ADDRESS 1
#define MW usSRegHoldBuf //MODBUS HOLDING REGISTERS
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
static struct GlobalVar GV = { 0 };
static struct DbTs DbTs1 = { 0 };
extern USHORT usSRegHoldBuf[]; //MODBUS RTU SLAVE HOLDING REGISTERS
static struct DbBlink DbBlink1 = { 0 };
static struct DbFilterA DbFilterA1 = { 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void setup(void);
void loop(void);
void FcTaskCyclic(bool Reset, uint32_t Ts_ms);
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
	MX_TIM3_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	setup();
	while (1) {
		loop();
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void) {

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 71;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 49;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

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
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(RS485_RTS_GPIO_Port, RS485_RTS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : LED_Pin */
	GPIO_InitStruct.Pin = LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : RS485_RTS_Pin */
	GPIO_InitStruct.Pin = RS485_RTS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RS485_RTS_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void setup(void) //Arduino function.
{

	eMBInit(MB_RTU, MODBUS_RTU_SLAVE_ADDRESS, &huart2,
			(ULONG) huart2.Init.BaudRate, &htim3); //MODBUS RTU SLAVE
	eMBEnable(); //MODBUS RTU SLAVE

	GV.Reset = true;
	//Расчет времени скана.
	//             DbTs
	//    +---------------------+
	//    |        FbTs         |
	//   -|millis          Ts_ms|->-
	//   -|Reset              Ts|->-
	//    |            Ts_ms_max|->-
	//    |             Uptime_s|->-
	//    +---------------------+
	DbTs1.millis = millis(); //millis() Arduino.
	DbTs1.Reset = GV.Reset; //Сброс при перезагрузке.
	FbTs(&DbTs1); //Расчет времени скана.
	GV.Ts_ms = DbTs1.Ts_ms; //Шаг дискретизации по времени [мс].
	GV.Ts = DbTs1.Ts; //Шаг дискретизации по времени [с].
	GV.Ts_ms_max = DbTs1.Ts_ms_max; //Максимальное время скана [мс].
	GV.Uptime_s = DbTs1.Uptime_s; //Время в работе [мс].

	FcTaskCyclic(GV.Reset, GV.Ts_ms); //PLC Task 1
	return;
}

void loop(void) //Arduino function.
{

	eMBErrorCode retu;
	retu = eMBPoll(); //MODBUS RTU SLAVE
	if (retu == MB_ENOERR) {
		;
	} // IF OK

	GV.Reset = false;
	//Расчет времени скана.
	//             DbTs
	//    +---------------------+
	//    |        FbTs         |
	//   -|millis          Ts_ms|->-
	//   -|Reset              Ts|->-
	//    |            Ts_ms_max|->-
	//    |             Uptime_s|->-
	//    +---------------------+
	DbTs1.millis = millis();	//millis() Arduino.
	DbTs1.Reset = GV.Reset;	//Сброс при перезагрузке.
	FbTs(&DbTs1);	//Расчет времени скана.
	GV.Ts_ms = DbTs1.Ts_ms;	//Шаг дискретизации по времени [мс].
	GV.Ts = DbTs1.Ts;	//Шаг дискретизации по времени [с].
	GV.Ts_ms_max = DbTs1.Ts_ms_max;	//Максимальное время скана [мс].
	GV.Uptime_s = DbTs1.Uptime_s;	//Время в работе [мс].

	//PLC Cyclic Task1
	FcTaskCyclic(GV.Reset, GV.Ts_ms);	//PLC Task 1

	//PLC digital output
	if (GV.Do1) {
		USER_LED_ON();
	} else {
		USER_LED_OFF();
	}

	return;
}

void FcTaskCyclic(bool Reset, uint32_t Ts_ms) //PLC ST style logic.
{

	//Время работы мс.
	MW[0] = 0x7fff bitand millis(); //0x7fff ограничение до 2**15-1

	//Время скана мс.
	MW[1] = 0x7fff bitand GV.Ts_ms; //0x7fff ограничение до 2**15-1

	//Максимальное время скана мс.
	MW[2] = 0x7fff bitand GV.Ts_ms_max; //0x7fff ограничение до 2**15-1

	//Blink
	MW[3] = GV.Do1;

	//Тест на сложение.
	if (Reset) {
		MW[4] = -2;
		MW[5] = 6;
	}
	MW[6] = MW[4] + MW[5];

	//Пример работы с дискретными алгоритмами.
	//Мигалка.
	//            DbBlink
	//    +---------------------+
	//    |       FbBlink       |
	//   -|Time_on_ms        Out|->-
	//   -|Time_off_ms          |
	//   -|Ts_ms                |
	//   -|Reset                |
	//    +---------------------+
	DbBlink1.Time_on_ms = 500;	//Время импульса [мс].
	DbBlink1.Time_off_ms = 500;	//Время паузы [мс].
	DbBlink1.Ts_ms = Ts_ms;	//Шаг дискретизации по времени [мс].
	DbBlink1.Reset = Reset;	//Сброс при перезагрузке.
	FbBlink(&DbBlink1);	//Мигалка.
	GV.Do1 = DbBlink1.Out;	//Мигающая лампочка.

	//Пример работы с аналоговыми алгоритмами.
	//Фильтр апериодический.
	//      DbFilterA
	//    +-----------+
	//    | FbFilterA |
	// ->-|In      Out|->-
	//   -|Tf         |
	//   -|Ts         |
	//    +-----------+
	DbFilterA1.In = (float) DbBlink1.Out;	//Входной сигнал до фильтрации.
	DbFilterA1.Tf = 0.15;	//Постоянная времени фильтра [с].
	DbFilterA1.Ts = GV.Ts;	//Шаг дискретизации по времени [с].
	FbFilterA(&DbFilterA1);	//Фильтр апериодический.
	//            = DbFilterA1.Out; //Выходной сигнал после фильтрации.

	return;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

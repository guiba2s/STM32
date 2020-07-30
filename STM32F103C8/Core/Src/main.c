/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum //criar um tipo para variaveis booleanas
{
	Bit_RESET = 0,
	Bit_Set
}bitAction;

typedef enum
{
	estadoOFF = 0,
	estadoON,
	estadoCres,
	estadoDecres
}estadoMaquina;

typedef enum
{
	LedsOff = 0,
	LedsOn,
	LedsCrescente,
	LedsDeCrescente
}Leds;
Leds ledsMode;

typedef uint8_t uint8;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
bitAction dinBtnOnVal, dinBtnOffVal, dinBtnCres, dinBtnDecres; //variaveis para controle da funcao de modo de acionamento dos leds
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void check_Din_Values();
void modoLeds(Leds output);
bitAction Din_btn_LoEdge(bitAction din_input);
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
	estadoMaquina machineEstate;

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		Delayms(100);

		switch(machineEstate)
		{
			case estadoOFF:
			{
				if(Din_btn_LoEdge(dinBtnOnVal)==Bit_Set)//EVENTO - SE BOTÃO b1 FOR PRESSIONADO
				{
					machineEstate = estadoON;
					modoLeds(LedsOn);
				}
			}
			break;

			case estadoON:
			{
				if(Din_btn_LoEdge(dinBtnOffVal) == Bit_Set)
				{

					machineEstate = estadoOFF;
					modoLeds(LedsOff);
				}
			}
			break;

			case estadoCres:
			{
				if(Din_btn_LoEdge(dinBtnCres) == Bit_Set)
				{
					machineEstate = estadoON;
					modoLeds(LedsCrescente);
				}
			}
			break;

			case estadoDecres:
					{
						if(Din_btn_LoEdge(dinBtnDecres) == Bit_Set)
						{
							machineEstate = estadoOFF;
							modoLeds(LedsDeCrescente);
						}
					}

			/*
			 *
			 * incluir caso sequencial e decrescente
			 *
			 *
			 *
			 */

		}


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
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DOUT_LED1_Pin|DOUT_LED2_Pin|DOUT_LED3_Pin|DOUT_LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DOUT_LED5_Pin|DOUT_LED6_Pin|DOUT_LED7_Pin|DOUT_LED8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : DIN_BTN_DECRES_Pin */
  GPIO_InitStruct.Pin = DIN_BTN_DECRES_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DIN_BTN_DECRES_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DOUT_LED1_Pin DOUT_LED2_Pin DOUT_LED3_Pin DOUT_LED4_Pin */
  GPIO_InitStruct.Pin = DOUT_LED1_Pin|DOUT_LED2_Pin|DOUT_LED3_Pin|DOUT_LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DIN_BTN_ALLON_Pin DIN_BTN_OFF_Pin DIN_BTN_SEQC_Pin */
  GPIO_InitStruct.Pin = DIN_BTN_ALLON_Pin|DIN_BTN_OFF_Pin|DIN_BTN_SEQC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DOUT_LED5_Pin DOUT_LED6_Pin DOUT_LED7_Pin DOUT_LED8_Pin */
  GPIO_InitStruct.Pin = DOUT_LED5_Pin|DOUT_LED6_Pin|DOUT_LED7_Pin|DOUT_LED8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//interrupção gerada a cada 1ms
void HAL_SYSTICK_Callback()
{

	DelayIncCnt(); //incrementa base de tempo para a geração de tempo
	check_Din_Values();

}

//função para leitura das entradas digitais
void check_Din_Values(){
	static uint8 cntTick;
	cntTick++;
	if(cntTick >= 20)//a cada 20ms faz uma
	{
		cntTick = 0;
		dinBtnOnVal = HAL_GPIO_ReadPin(DIN_BTN_ALLON_GPIO_Port, DIN_BTN_ALLON_Pin); // BOTAO ON RECEBE VALOR LIDO
		dinBtnOffVal = HAL_GPIO_ReadPin(DIN_BTN_OFF_GPIO_Port, DIN_BTN_OFF_Pin);	//BOTAO OFF RECEBE VALOR LIDO
		dinBtnOffVal = HAL_GPIO_ReadPin(DIN_BTN_SEQC_GPIO_Port, DIN_BTN_SEQC_Pin);	//BOTAO SEQUENCIA_CRESCENTE RECEBE VALOR LIDO
		dinBtnOffVal = HAL_GPIO_ReadPin(DIN_BTN_DECRES_GPIO_Port, DIN_BTN_DECRES_Pin);	//BOTAO DECRESCENTE RECEBE VALOR LIDO

	}

}

//Verifica a borda de descida na entrada DIN_BUTTON
bitAction Din_btn_LoEdge(bitAction din_input)//recebe o botão que será lido e comparado
{
	  bitAction pin_value, old;
	  static bitAction old_pin_value;

	 pin_value = din_input;
	 old = old_pin_value;
	 old_pin_value = pin_value;

	  if(pin_value != Bit_RESET)
	  {
	    return(Bit_RESET);
	  }
	  else if(old == Bit_RESET)
	  {
	    return(Bit_RESET);
	  }
	  else
	  {
	    return(Bit_Set);
	  }
}

void modoLeds(Leds leds_output)	//função que controla a sequencia de acionamento do leds
{
	uint8_t varredura;

	uint16_t pinos[8] = { DOUT_LED1_Pin, DOUT_LED2_Pin, DOUT_LED3_Pin,
			DOUT_LED4_Pin, DOUT_LED5_Pin, DOUT_LED6_Pin, DOUT_LED7_Pin,
			DOUT_LED8_Pin};

	switch (leds_output)
	{
		case LedsOn:
		{
			for (varredura = 0; varredura <= 5; varredura++)
			{
				HAL_GPIO_WritePin(DOUT_LED1_GPIO_Port, pinos[varredura], Bit_Set);

			}

			for (varredura = 4 ; varredura <=8; varredura++)
			{
				HAL_GPIO_WritePin(DOUT_LED5_GPIO_Port, pinos[varredura], Bit_Set);

			}
		}
		break;

		case LedsOff:
		{
			for(varredura = 0; varredura <= 5; varredura++)
			{
				HAL_GPIO_WritePin(DOUT_LED1_GPIO_Port, pinos[varredura], Bit_RESET);
			}

			for(varredura = 4; varredura <= 8; varredura++)
			{
				HAL_GPIO_WritePin(DOUT_LED5_GPIO_Port, pinos[varredura], Bit_RESET);
			}
		}
		break;

		case LedsCrescente:
		{
			for(varredura = 0; varredura <= 5; varredura++)
			{
				HAL_GPIO_WritePin(DOUT_LED1_GPIO_Port, pinos[varredura], Bit_Set);
				Delayms(300);
			}
			for(varredura = 4; varredura <= 8; varredura++)
			{
				HAL_GPIO_WritePin(DOUT_LED5_GPIO_Port, pinos[varredura], Bit_Set);
				Delayms(300);
			}
		}
		break;

		case LedsDeCrescente:
			{
				for(varredura = 8; varredura >= 4; varredura--)
				{
					HAL_GPIO_WritePin(DOUT_LED1_GPIO_Port, pinos[varredura], Bit_RESET);
					Delayms(300);
				}
				for(varredura = 4; varredura >= 0; varredura--)
				{
					HAL_GPIO_WritePin(DOUT_LED5_GPIO_Port, pinos[varredura], Bit_Set);
					Delayms(300);
				}
			}
			break;


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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

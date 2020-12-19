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

uint8_t temp = 0;
float mag[3], acc[3];
volatile uint8_t interrupt;
volatile int menu = 3;

void SystemClock_Config(void);

extern uint64_t disp_time;

uint64_t saved_time;
double num_to_display = 10;
int vypis[5];
int poc = 0;
int smer = 0;
char text[50];

int main(void)
{

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  SystemClock_Config();

  MX_GPIO_Init();

  setSegments();
  setDigits();
  LL_mDelay(2000);
  resetDigits();
  resetSegments();

  MX_TIM3_Init();
  MX_I2C1_Init();

  lis3mdl_init();
  lbs_init();

  char tmp_arr[50];

  int i = 0;
  int c = 0;

  float tlak = 0;
  float nad_vysk = 0;
  float azimut = 0;
  float teplota = 0;

  while (1)
  {

	  //CITANIE SENZOROV

	  azimut = ziskajAzimut();
	  tlak = lbsZiskajTlak();
	  nad_vysk = ziskajNadVysku(tlak);
	  teplota = ziskajTeplotu();

	  //MENU
	  if(menu==0) {
		snprintf(tmp_arr, sizeof(tmp_arr), "%.2fQ", tlak);
	  	text[0]='B';
	  	text[1]='A';
	  	text[2]='R';
	  	text[3]='_';

	  	i=0;
	  	c=0;
	  	while(1){
	  		if(tmp_arr[i] == 'Q')break;

	  		if(tmp_arr[i+1]=='.'){
	  			text[c+4]=tmp_arr[i]+100;
	  			i++;
	  		}else{
	  			text[c+4]=tmp_arr[i];
	  		}
	  		i++;
	  		c++;
	  	}
	  	text[c+4]='Q';
	  }

	  if(menu==1) {
	 		snprintf(tmp_arr, sizeof(tmp_arr), "%.1fQ", nad_vysk);
	 	  	text[0]='A';
	 	  	text[1]='L';
	 	  	text[2]='T';
	 	  	text[3]='_';

	 	  	i=0;
	 	  	c=0;
	 	  	while(1){
	 	  		if(tmp_arr[i] == 'Q')break;

	 	  		if(tmp_arr[i+1]=='.'){
	 	  			text[c+4]=tmp_arr[i]+100;
	 	  			i++;
	 	  		}else{
	 	  			text[c+4]=tmp_arr[i];
	 	  		}
	 	  		i++;
	 	  		c++;
	 	  	}
	 	  	text[c+4]='Q';
	 	  }

	  if(menu==2) {
	  	 		snprintf(tmp_arr, sizeof(tmp_arr), "%.1fQ", azimut);
	  	 	  	text[0]='M';
	  	 	  	text[1]='A';
	  	 	  	text[2]='G';
	  	 	  	text[3]='_';

	  	 	  	i=0;
	  	 	  	c=0;
	  	 	  	while(1){
	  	 	  		if(tmp_arr[i] == 'Q')break;

	  	 	  		if(tmp_arr[i+1]=='.'){
	  	 	  			text[c+4]=tmp_arr[i]+100;
	  	 	  			i++;
	  	 	  		}else{
	  	 	  			text[c+4]=tmp_arr[i];
	  	 	  		}
	  	 	  		i++;
	  	 	  		c++;
	  	 	  	}
	  	 	  	text[c+4]='Q';
	  	 	  }

	  if(menu==3) {
	  	  	 		snprintf(tmp_arr, sizeof(tmp_arr), "%.1fQ", teplota);
	  	  	 	  	text[0]='T';
	  	  	 	  	text[1]='E';
	  	  	 	  	text[2]='M';
	  	  	 	  	text[3]='P';
	  	  	 	  	text[4]='_';

	  	  	 	  	i=0;
	  	  	 	  	c=0;
	  	  	 	  	while(1){
	  	  	 	  		if(tmp_arr[i] == 'Q')break;

	  	  	 	  		if(tmp_arr[i+1]=='.'){
	  	  	 	  			text[c+5]=tmp_arr[i]+100;
	  	  	 	  			i++;
	  	  	 	  		}else{
	  	  	 	  			text[c+5]=tmp_arr[i];
	  	  	 	  		}
	  	  	 	  		i++;
	  	  	 	  		c++;
	  	  	 }
	  	  	 text[c+5]='Q';
	  }

	  //VYPIS
	  vypis[0]=text[poc];
	  vypis[1]=text[poc+1];
	  vypis[2]=text[poc+2];
	  vypis[3]=text[poc+3];
	  vypis[4]=text[poc+4];

	  if(vypis[4]==81){smer=1;}
	  if(poc==0)smer=0;
	  if(smer==0){poc++;}else{poc--;}

	  LL_mDelay(500);

  }



}


/**
  * @brief System Clock Configuration
  * @retval None
  */




void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SYSTICK_EnableIT();
  LL_SetSystemCoreClock(8000000);
}

/* USER CODE BEGIN 4 */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

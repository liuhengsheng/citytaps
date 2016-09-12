#include "variables.h"
#include <string.h>

extern ADC_HandleTypeDef hadc;
uint16_t  ADC_raw_value;
float Voltage,Tem;
uint8_t temp[50];

#ifdef DEBUG_MODE
void print_temp(void){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);	// turn on thermometer 
	HAL_ADC_Start(&hadc);																// begin ADC
	HAL_Delay(1);
	ADC_raw_value = HAL_ADC_GetValue(&hadc);
	Voltage = (float)ADC_raw_value * 3.6 / 4096 ; 	// base on 3.6V battery power
	Tem = Voltage *100 ; 
	sprintf((char *)temp, "ADC_Voltage: %.3f  Temperature: %.0f \n", Voltage , Tem);
	HAL_UART_Transmit(&huart2, temp, strlen((char *)temp), 50);
	HAL_ADC_Stop(&hadc);																// stop ADC
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);	// turn off thermometer
}
#endif
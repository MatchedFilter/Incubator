#include <cinttypes>
#include "stm32f1xx_hal.h"
#include <cstring>
#include "main.h"
#include <stdbool.h>


extern TIM_HandleTypeDef htim4;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c1;
extern volatile int64_t g_TimestampInMilliseconds;

#ifdef _cplusplus
extern "C"
{
#endif // _cplusplus

void _start_dht11_timer()
{
	TIM_HandleTypeDef *dht11_htim = &htim4;
	__HAL_TIM_SET_COUNTER(dht11_htim, 0);
	HAL_TIM_Base_Start(dht11_htim);
}

void _reset_dht11_timer()
{
	TIM_HandleTypeDef *dht11_htim = &htim4;
	__HAL_TIM_SET_COUNTER(dht11_htim, 0);
}

void _stop_dht11_timer()
{
	HAL_TIM_Base_Stop(&htim4);
}

uint32_t _get_timestamp_in_microseconds_from_dht11_timer()
{
	TIM_HandleTypeDef *dht11_htim = &htim4;
	return __HAL_TIM_GET_COUNTER(dht11_htim);
}

void _delay_in_microseconds(int32_t duration_in_microseconds)
{
	TIM_HandleTypeDef *dht11_htim = &htim4;
	_start_dht11_timer();
	while (__HAL_TIM_GET_COUNTER(dht11_htim) < (uint32_t)duration_in_microseconds) {}
	_stop_dht11_timer();
}

void _delay_in_milliseconds(int32_t duration_in_miliseconds)
{
	HAL_Delay(duration_in_miliseconds);
}

void _set_dht11_data_pin_as_output()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void _set_dht11_data_pin_as_input()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void _set_dht11_data_pin_as_low()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}

int _read_dht11_data_pin()
{
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
}

void _transmit_log_buffer(uint8_t *buffer, int32_t size)
{
	HAL_UART_Transmit(&huart1, buffer, size, 100);
}

int64_t _get_timestamp_in_milliseconds()
{
    return g_TimestampInMilliseconds;
}

void _set_timestamp_in_milliseconds(int64_t timestampInMilliseconds)
{
	g_TimestampInMilliseconds = timestampInMilliseconds;
}

void _set_d4_pin_output(uint8_t outputValue)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (GPIO_PinState)outputValue);
}

void _set_d5_pin_output(uint8_t outputValue)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (GPIO_PinState)outputValue);
}

void _set_d6_pin_output(uint8_t outputValue)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (GPIO_PinState)outputValue);
}

void _set_d7_pin_output(uint8_t outputValue)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (GPIO_PinState)outputValue);
}

void _set_en_pin_output(uint8_t outputValue)
{
	HAL_GPIO_WritePin(TC1602_EN_GPIO_Port, TC1602_EN_Pin, (GPIO_PinState)outputValue);
}

void _set_reset_pin_output(uint8_t outputValue)
{
	HAL_GPIO_WritePin(TC1602_RS_GPIO_Port, TC1602_RS_Pin, (GPIO_PinState)outputValue);
}

void _set_rw_pin_output(uint8_t outputValue)
{
	HAL_GPIO_WritePin(TC1602_RW_GPIO_Port, TC1602_RW_Pin, (GPIO_PinState)outputValue);
}

void _start_adc_for_ntc(uint8_t ntc_id)
{
	HAL_ADC_Start(&hadc1);
}

uint32_t _get_adc_value_for_ntc(uint8_t ntc_id)
{
	return HAL_ADC_GetValue(&hadc1);
}

void _start_adc_for_joystick_with_id_for_right_position(uint8_t joystickId)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
	HAL_ADC_ConfigChannel(&hadc2, &sConfig);
	HAL_ADC_Start(&hadc2);
}

void _start_adc_for_joystick_with_id_for_up_position(uint8_t joystickId)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_8;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
	HAL_ADC_ConfigChannel(&hadc2, &sConfig);
	HAL_ADC_Start(&hadc2);
}

uint32_t _get_adc_value_for_joystick_with_id(uint8_t joystickId)
{
	return HAL_ADC_GetValue(&hadc2);
}

uint8_t _get_pressed_state_for_joystick_with_id(uint8_t joystickId)
{
	uint8_t result = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET;
	return result;
}

bool _write_to_i2c_memory(uint16_t deviceAddres, uint16_t memoryAddress, uint8_t *buffer, uint16_t bufferSize)
{
	bool b_result = false;
	if (HAL_I2C_Mem_Write(&hi2c1, deviceAddres, memoryAddress, sizeof(uint16_t), buffer, bufferSize, 100) == HAL_OK)
	{
		b_result = true;
	}
	return b_result;
}

bool _read_from_i2c_memory(uint16_t deviceAddres, uint16_t memoryAddress, uint8_t *buffer, uint16_t bufferSize)
{
	bool b_result = false;
	if (HAL_I2C_Mem_Read(&hi2c1, deviceAddres, memoryAddress, sizeof(uint16_t), buffer, bufferSize, 1000) == HAL_OK)
	{
		b_result = true;
	}
	return b_result;
}

#ifdef _cplusplus
}
#endif // _cplusplus

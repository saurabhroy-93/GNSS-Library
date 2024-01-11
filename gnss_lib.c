/*
 * gnss_lib.c
 *
 *  Created on: Jan 11, 2024
 *      Author: ppmes
 */
#include "stm32h7xx_hal.h"
#include "string.h"
#include "gnss_lib.h"

extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart3;

char response_buffer[700]={0};

void GPS_SendATCommand(const char *command) {
    // Function to send AT command to GPS module
    HAL_UART_Transmit(&huart7, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);
    HAL_UART_Receive(&huart7,(uint8_t *)response_buffer,sizeof(response_buffer)-1,2000);
    HAL_UART_Transmit(&huart3,(uint8_t *)response_buffer, sizeof(response_buffer), HAL_MAX_DELAY);
    memset(response_buffer, 0, sizeof(response_buffer));
}

/*--------------------------------------------GET-FUNCTIONS------------------------------------------------*/

void read_operator(void) {
    GPS_SendATCommand("AT+COPS?\r\n");
}

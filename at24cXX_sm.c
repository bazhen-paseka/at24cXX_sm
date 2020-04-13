/**
* \file
* \version 1.0
* \author bazhen.levkovets
** \date 2020
*
*************************************************************************************
* \copyright	Bazhen Levkovets
* \copyright	Brovary, Kyiv region
* \copyright	Ukraine
*
*************************************************************************************
*
* \brief
*
*/

/*
**************************************************************************
*							INCLUDE FILES
**************************************************************************
*/
	#include "at24cXX_sm.h"
/*
**************************************************************************
*							LOCAL DEFINES
**************************************************************************
*/

/*
**************************************************************************
*							LOCAL CONSTANTS
**************************************************************************
*/
/*
**************************************************************************
*						    LOCAL DATA TYPES
**************************************************************************
*/
/*
**************************************************************************
*							  LOCAL TABLES
**************************************************************************
*/
/*
**************************************************************************
*								 MACRO'S
**************************************************************************
*/

/*
**************************************************************************
*						    GLOBAL VARIABLES
**************************************************************************
*/


/*
**************************************************************************
*                        LOCAL FUNCTION PROTOTYPES
**************************************************************************
*/
	
/*
**************************************************************************
*                           GLOBAL FUNCTIONS
**************************************************************************
*/

//************************************************************************

//************************************************************************
//************************************************************************
void At24cXX_Init (void) {
	/* Arrays for operating with strings */
	uint8_t str[32] = {0};
	uint8_t buf[32] = {0};

	uint16_t EEPROM_Memory_Address_u16 = 0x40 ;
	char DataChar[100];

	sprintf((char *) str, "Hello, BoryViter!");
	HAL_UART_Transmit(&huart1, (uint8_t *)str, sizeof(str) / sizeof(str[0]), 100);
	/* EEPROM write */
	if (HAL_I2C_Mem_Write(&hi2c1, EEPROM_DEVICE_ADDRESS, EEPROM_Memory_Address_u16, I2C_MEMADD_SIZE_16BIT, str, sizeof(str) / sizeof(str[0]), 100) == HAL_OK) {
		sprintf(DataChar,"EEPROM write: OK.\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
	} else {
		sprintf(DataChar,"EEPROM write - error.\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
	}

	while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_DEVICE_ADDRESS, 100, 100) != HAL_OK);				/* Wait till device ready */

	/* EEPROM read */
	if (HAL_I2C_Mem_Read(&hi2c1, EEPROM_DEVICE_ADDRESS, EEPROM_Memory_Address_u16, I2C_MEMADD_SIZE_16BIT, (uint8_t *)buf, sizeof(buf) / sizeof(buf[0]), 100) == HAL_OK) {
		sprintf(DataChar,"Reading text: OK.\r\n");
	} else {
		sprintf(DataChar,"Reading text: error.\r\n\r\n");
	}
	/* Now buf[] has "Hello, TechMaker! #xxx\0" text */
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, sizeof(buf) / sizeof(buf[0]), 100);
	HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);

}
//************************************************************************

void  Write_to_EEPROM(uint8_t * _str, uint8_t _size_of_str_u8, uint16_t _eeprom_packet_u16) {
	uint16_t eeprom_memory_address_u16 = 32 * _eeprom_packet_u16;
	HAL_I2C_Mem_Write(&hi2c1, EEPROM_DEVICE_ADDRESS, eeprom_memory_address_u16, I2C_MEMADD_SIZE_16BIT, _str, _size_of_str_u8, 100);
}
//************************************************************************

void Read_from_EEPROM(uint8_t * _str, uint8_t _size_of_str_u8, uint16_t _eeprom_packet_u16) {
	while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_DEVICE_ADDRESS, 100, 100) != HAL_OK);				/* Wait till device ready */
	uint16_t eeprom_memory_address_u16 = 32 * _eeprom_packet_u16;
	HAL_I2C_Mem_Read(&hi2c1, EEPROM_DEVICE_ADDRESS, eeprom_memory_address_u16, I2C_MEMADD_SIZE_16BIT, (uint8_t *)_str, 32, 100);		/* EEPROM read */
}
//************************************************************************
/*
**************************************************************************
*                           LOCAL FUNCTIONS
**************************************************************************
*/

//************************************************************************

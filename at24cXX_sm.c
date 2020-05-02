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
void AT24cXX_init (void) {

}
//************************************************************************

HAL_StatusTypeDef  AT24cXX_write_to_EEPROM(uint8_t * _str, uint8_t _size_of_str_u8, uint16_t _eeprom_packet_u16) {
	uint16_t eeprom_memory_address_u16 = EEPROM_PACKET_SIZE * _eeprom_packet_u16;
	HAL_StatusTypeDef operation_result_td = HAL_ERROR;
	operation_result_td = HAL_I2C_Mem_Write(&hi2c1, EEPROM_DEVICE_ADDRESS, eeprom_memory_address_u16, I2C_MEMADD_SIZE_16BIT, _str, _size_of_str_u8, 100);
	return operation_result_td;
}
//************************************************************************

HAL_StatusTypeDef AT24cXX_read_from_EEPROM(uint8_t * _str, uint8_t _size_of_str_u8, uint16_t _eeprom_packet_u16) {
	while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_DEVICE_ADDRESS, 100, 100) != HAL_OK);				/* Wait till device ready */
	uint16_t eeprom_memory_address_u16 = EEPROM_PACKET_SIZE * _eeprom_packet_u16;
	HAL_StatusTypeDef operation_result_td = HAL_ERROR;

	operation_result_td = HAL_I2C_Mem_Read(&hi2c1, EEPROM_DEVICE_ADDRESS, eeprom_memory_address_u16, I2C_MEMADD_SIZE_16BIT, (uint8_t *)_str, 32, 100);		/* EEPROM read */
	return operation_result_td;
}
//************************************************************************

//======================================================================
void AT24cXX_scan_I2C_bus(I2C_HandleTypeDef * _hi2c, UART_HandleTypeDef * _huart)
{
	char DataChar[32];
	int device_serial_numb = 0;

	sprintf(DataChar,"Start scan I2C\r\n");
	HAL_UART_Transmit(_huart, (uint8_t *)DataChar, strlen(DataChar), 100);
	HAL_Delay(100);

	for ( int i2c_addr_int = 0x07; i2c_addr_int < 0x78; i2c_addr_int++) {
		if (HAL_I2C_IsDeviceReady(_hi2c, i2c_addr_int << 1, 10, 100) == HAL_OK) {
			device_serial_numb++;
			switch (i2c_addr_int) {
				case 0x23: sprintf(DataChar,"%d) bh-1750", device_serial_numb ); break;
				case 0x27: sprintf(DataChar,"%d) fc-113 ", device_serial_numb ); break;
				case 0x38: sprintf(DataChar,"%d) pcf-8574", device_serial_numb ); break;
				case 0x57: sprintf(DataChar,"%d) at24c32", device_serial_numb ); break;
				case 0x50: sprintf(DataChar,"%d) at24c256", device_serial_numb ); break;
				case 0x68: sprintf(DataChar,"%d) ds-3231", device_serial_numb ); break;
				//case 0x68: sprintf(DataChar_I2C,"%d) MPU9250", device_serial_numb ); break;
				case 0x76: sprintf(DataChar,"%d) BMP280", device_serial_numb ); break;
				case 0x77: sprintf(DataChar,"%d) BMP180", device_serial_numb ); break;
				default:   sprintf(DataChar,"%d) Unknown", device_serial_numb ); break;
			}// end switch
			sprintf(DataChar,"%s\tAdr: 0x%x\r\n", DataChar, i2c_addr_int);
			HAL_UART_Transmit(_huart, (uint8_t *)DataChar, strlen(DataChar), 100);
			HAL_Delay(10);
		} //end if HAL I2C1
	} // end for i2c_addr_int i2c1
	sprintf(DataChar,"End scan I2C\r\n");
	HAL_UART_Transmit(_huart, (uint8_t *)DataChar, strlen(DataChar), 100);
	HAL_Delay(100);
}// end void I2C_ScanBus

/*
**************************************************************************
*                           LOCAL FUNCTIONS
**************************************************************************
*/

//************************************************************************

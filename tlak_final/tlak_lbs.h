

///TLAK LIB


#include "main.h"
#include "i2c.h"

#define 	LBS_DEVICE_ADDRESS_0					0xBA
#define 	LBS_DEVICE_ADDRESS_1					0xB8
#define 	LBS_WHO_AM_I_VALUE						0xBD
#define 	LBS_WHO_AM_I_ADDRES						0x0F

#define 	LBS_ADDRESS_CTRL1						0x20

uint8_t lbs_init(void);
uint8_t lbs_read_byte(uint8_t reg_addr);
void lbs_write_byte(uint8_t reg_addr, uint8_t value);
float lbsZiskajTlak();






///TLAK LIB


#include "tlak_lbs.h"

uint8_t lbs_addres = LBS_DEVICE_ADDRESS_0;


uint8_t lbs_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, lbs_addres, 0));
}


void lbs_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, lbs_addres, 0);
}


void lbs_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, lbs_addres, 1);
}

float lbsZiskajTlak(){

	float tlak_out;
	uint8_t tlak_data[3];

	lbs_readArray(tlak_data, 0x28, 3);
	tlak_out = ((uint32_t)tlak_data[2])<<16|((uint16_t)tlak_data[1])<<8|tlak_data[0];
	return tlak_out/4096;
}


uint8_t lbs_init(void)
{

	uint8_t status = 1;
	LL_mDelay(100);
	uint8_t val = lbs_read_byte(LBS_WHO_AM_I_ADDRES);

	if(val == LBS_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else
	{
		lbs_addres = LBS_DEVICE_ADDRESS_1;
		val = lbs_read_byte(LBS_WHO_AM_I_ADDRES);
		if(val == LBS_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
		}
	}

	lbs_write_byte(LBS_ADDRESS_CTRL1, 0xC0);

	return status;
}



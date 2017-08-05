/*
 * CCS811sensor.cpp
 *
 *  Created on: Aug 4, 2017
 *      Author: pete
 */

#include <CCS811sensor.h>

namespace sensor {

	CCS811_sensor::CCS811_sensor(uint16_t addr, std::string name) : i2c_sensor(addr, name)
	{
	}

	CCS811_sensor::~CCS811_sensor()
	{
	}

	void CCS811_sensor::prepare()
	{
		uint8_t hwid = 0;
		uint8_t status = 0;

		sensors::sleep(0, 70);

	}

	void CCS811_sensor::compensate(float t, float r)    // compensate for temperature and relative humidity
	{
		int temp, rh;
		uint8_t envdata[4];

		m_gpio->low();
		localSleep(0, 50000);

		if (t > 0) {
			temp = (int)t + 0.5;
		}
		else if (t < 0) {
			temp = (int)t - 0.5;
		}
		temp = temp + 25;
		rh = (int)r + 0.5;

		envdata[0] = rh << 1;
		envdata[1] = 0;
		envdata[2] = temp << 1;
		envdata[3] = 0;

		i2c_writeBuffer(0, m_addr, ENV_DATA, envdata, 4);
		m_gpio->high();
	}

	void CCS811_sensor::getData(void)
	{
		uint8_t buffer[8];

		//CCS811::compensate(t, rh);
		m_gpio->low();
		localSleep(0, 50000);
		i2c_writeBytes(0, m_addr, ALG_RESULT_DATA, 0, 0);
		i2c_readBytes(0, m_addr, ALG_RESULT_DATA, &buffer, 8);
		CO2 = ((uint16_t)buffer[0] << 8) | buffer[1];
		TVOC = ((uint16_t)buffer[2] << 8) | buffer[3];
		m_gpio->high();
	}


} /* namespace sensor */

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
		m_gpio = NULL;
	}

	CCS811_sensor::~CCS811_sensor()
	{
	}

	void CCS811_sensor::setGpio(int pin)
	{
		m_gpio = new gpio(pin);
	}

	void CCS811_sensor::prepare()
	{
		uint8_t hwid = 0;
		uint8_t status = 0;

		m_gpio->low();
		sleep(0, 70);
		i2c_sensor::writeRegister(HW_ID, 1);
		hwid = readRegister(HW_ID);
		m_gpio->high();
	}

	void CCS811_sensor::compensate(float t, float r)    // compensate for temperature and relative humidity
	{
		int temp, rh;
		uint8_t envdata[4];

		m_gpio->low();
		sleep(0, 50);

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

		writeRegisterArray(ENV_DATA, envdata, 4);
		m_gpio->high();
	}

	void CCS811_sensor::getData(void)
	{
		uint8_t buffer[8];

		//CCS811::compensate(t, rh);
		m_gpio->low();
		sleep(0, 50);
		writeRegister(ALG_RESULT_DATA, 0);
		readRegisterArray(ALG_RESULT_DATA, &buffer, 8);
		m_co2 = ((uint16_t)buffer[0] << 8) | buffer[1];
		m_tvoc = ((uint16_t)buffer[2] << 8) | buffer[3];
		m_gpio->high();
	}

	uint8_t CCS811_sensor::readHW_ID(void)
	{
		uint8_t hwid = 0;

		m_gpio->low();
		sleep(0, 70);
		try {
			writeRegister(HW_ID, 1);
			hwid = readRegister(HW_ID);
		}
		catch (sensorException e) {
			std::cerr << "Caught ioctl exception";
		}
		m_gpio->high();
		return hwid;
	}

	uint8_t CCS811_sensor::readStatus(void)
	{
		uint8_t status;

		m_gpio->low();
		sleep(0, 50);
		writeRegister(STATUS, 1);

		status = readRegister(STATUS);
		m_gpio->high();
		return status;
	}

	uint8_t CCS811_sensor::readErrorID(uint8_t _status)
	{
		uint8_t error_id = 0;

		m_gpio->low();
		sleep(0, 50);
		writeRegister(ERROR_ID, 1);
		error_id = readRegister(ERROR_ID);
		uint8_t bit = (_status & (1 << 1 - 1)) != 0;
		if (bit == 1) {
			std::cerr << __PRETTY_FUNCTION__ << ":" << __LINE__ << ": Error ID: " << error_id;
		}
		return error_id;
	}

	void CCS811_sensor::getData(void)
	{
		uint8_t buffer[8];

		//CCS811::compensate(t, rh);
		m_gpio->low();
		sleep(0, 50);
		writeRegister(ALG_RESULT_DATA, 0);
		readRegister(ALG_RESULT_DATA, &buffer, 8);
		m_co2 = ((uint16_t)buffer[0] << 8) | buffer[1];
		m_tvoc = ((uint16_t)buffer[2] << 8) | buffer[3];
		m_gpio->high();
	}


} /* namespace sensor */

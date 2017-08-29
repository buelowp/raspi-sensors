/*
 * CCS811sensor.h
 *
 *  Created on: Aug 4, 2017
 *      Author: pete
 */

#ifndef INCLUDE_CCS811SENSOR_H_
#define INCLUDE_CCS811SENSOR_H_

#include <cstdint>
#include <string>
#include "include/i2c_sensor.h"
#include "include/helpers.h"
#include "include/gpio.h"

#define ADDR            0x5B   // when I2C_ADDR pin is HIGH

// Registers for CCS811
#define STATUS          0x00
#define MEAS_MODE       0x01
#define ALG_RESULT_DATA 0x02
#define ENV_DATA        0x05
#define APP_START       0xF4
#define HW_ID           0x20
#define ERROR_ID        0xE0
#define SW_RESET        0xFF

namespace sensor {

class CCS811_sensor : public i2c_sensor {
public:
	CCS811_sensor(uint16_t, std::string);
	virtual ~CCS811_sensor();

	void setGpio(int);
    /**
     *  @brief Return the type of the sensor (BMP180)
     */
	const std::string getType() { return std::string("CCS811"); }

	/**
     *  @brief Prepare a result fetching. May throw an exception if any error occures
     */
    void prepare();

    /**
     *  @brief Fetch a result. May throw an exception if any error occures
     *
     * @return The list of results fetched from the sensor.
     */
    std::list<result> getResults();

    /**
     * @brief Static creator for the sensor
     *
     * @return A pointer to the created sensor
     */
    static sensor* create(int, const std::string&);

    /**
     * @brief Get HW id from CCS811
     *
     * @return Returns the HW id as an unsigned 8 bit value
     */
    uint8_t readHW_ID();
    uint8_t readStatus();
    uint8_t readErrorID(uint8_t);
    void getData();

private:
    void compensate(float, float);

    gpio *m_gpio;
    int m_tvoc;
    int m_co2;
};

} /* namespace sensor */

#endif /* INCLUDE_CCS811SENSOR_H_ */

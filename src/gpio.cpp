/*
 * gpio.cpp
 *
 *  Created on: Aug 4, 2017
 *      Author: pete
 */

#include <gpio.h>

namespace sensor {

	gpio::gpio(int pin)
	{
		m_pin = pin;
		std::string ex_str = "/sys/class/gpio/export";
		std::ofstream ex_file(ex_str);
		if (ex_file) {
			ex_file << pin;
		}

		std::string gpio_str = "/sys/class/gpio/gpio" + m_pin + "/direction";
		std::ofstream gpio_file(gpio_str);
		if (gpio_file) {
			gpio_file << "out";
		}

		std::string value_str = "/sys/class/gpio/gpio" + m_pin + "/value";
		m_gpio.open(value_str.c_str());
	}

	gpio::~gpio()
	{
		m_gpio.close();
	}

	void gpio::high()
	{
		if (m_gpio.is_open())
			m_gpio << "1";
	}

	void gpio::low()
	{
		if (m_gpio.is_open())
			m_gpio << "0";
	}

	void gpio::set(int val)
	{
		if (m_gpio.is_open())
			m_gpio << val;
	}

} /* namespace sensor */

/*
 * gpio.h
 *
 *  Created on: Aug 4, 2017
 *      Author: pete
 */

#ifndef INCLUDE_GPIO_H_
#define INCLUDE_GPIO_H_

#include <ofstream>
#include <string>

namespace sensor {

	class gpio {
	public:
		gpio(int);
		virtual ~gpio();

		void low();
		void high();
		void set(int);

	private:
		std::ofstream m_gpio;
		std::string m_gpioPath;
		int m_pin;
	};

} /* namespace sensor */

#endif /* INCLUDE_GPIO_H_ */

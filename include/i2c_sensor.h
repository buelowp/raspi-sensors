/**
 * @file i2c_sensor.h
 * @brief Class for TSL2561 sensors. A TSL2561 use the I2C bus on the raspberry
 * @author Vuzi
 * @version 0.2
 */

#ifndef H_I2C_SENSOR
#define H_I2C_SENSOR

#include <string>
#include <cstdint>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

#include "sensor.h"

/**
 * @namespace sensor
 *
 * Name space used to store every class and functions related to the sensors
 */
namespace sensor {

    /**
     * I2C sensor. I2C sensor needs a special intialization, and a special way of retreiving data
     * from the sensor (reading a special file)
     */
    class i2c_sensor : public sensor {

        public:
            /**
             *  @brief Constructor
             *  @param address Address of the sensor
             *  @param name    Name of the sensor
             */
            i2c_sensor(uint16_t, std::string);

            /**
             * @brief Destructor
             */
            ~i2c_sensor();

        protected:
            /**
             * Return the address of the device
             * @return The address of the device
             */
            uint16_t getDeviceAddress();

            /**
             * Read and return data on the specified register
             * @param  uint16_t The instruction where to read
             * @return          The value read
             */
            uint16_t readRegister(uint16_t);

            /**
              * Read and return an array of uint8_t values
              * @param uint16_6 Register to read from
              * @param uint8_t* Pointer to buffer to store results
              * @param int Number of array elements to read
              * @
              */
            void readRegisterArray(uint16_t address, uint8_t*, uint8_t);
            uint16_t readRegisterInt(uint16_t);
            
             /**
             * Write a value in the specified register
             * @param  uint16_t The instruction where to write at
             * @param  uint16_t The value to write
             */
            void writeRegister(uint16_t, uint16_t);

            /**
             * Write a value in the specified register
             * @param  uint8_t The instruction where to write at
             * @param  uint8_t The value to write
             */
            void writeRegisterArray(uint8_t, uint8_t*, uint8_t);

            /**
             * Open the bus to read data from. If the opening failed, the filed
             * descriptor is set to -1
             * @return          The bus descriptor, or -1 on error 
             */
            void openBus();

            /**
             * Return the file descriptor of the bus, or -1
             * @return The bus file descriptor
             */
            int getBus();

            /**
             * Close the bus
             */
            void closeBus();

        private:
            int i2c_fd;              // File descriptor of the bus
            uint16_t deviceAddress;  // Adress of the device
    };
}

#endif // H_I2C_SENSOR

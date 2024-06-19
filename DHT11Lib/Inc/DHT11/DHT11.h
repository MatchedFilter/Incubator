#ifndef _SENSORS_DHT11_H_
#define _SENSORS_DHT11_H_
#include "DHT11Data.h"

/**
 * @brief Sensors
*/
namespace Sensors
{
	/**
	 * @brief DHT11 Temperature and Humidity Sensor
	 * 
	*/
	class DHT11
	{
	public:
		DHT11() = default;
		~DHT11() = default;

		/**
		 * @brief Retrieves temperature and humidity data
		 * @returns true if it successfully retrieves data, false otherwise
		*/
		bool RetreiveData(DHT11Data &dht11Data);


	};
} // namespace Sensors

#endif // _SENSORS_DHT11_H_

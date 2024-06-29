#include "Incubator/Utils/IncubatorUtils.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include "Incubator/Storage/Storage.h"

void IncubatorUtils::ReadStorageData(IncubatorData &incubatorData)
{
    HumidityData humidityData;
    TemperatureData temperatureData;
    TimeInfoData timeInfoData;
    incubatorData.m_MemoryDeviceErrorState = ERROR_STATE_ERROR;
    if (Storage::Query(humidityData))
    {
        TimeUtils::SleepInMilliseconds(Storage::STORAGE_READ_TIME_IN_MILLISECOND);
    	if (Storage::Query(temperatureData))
    	{
        	TimeUtils::SleepInMilliseconds(Storage::STORAGE_READ_TIME_IN_MILLISECOND);
    		if (Storage::Query(timeInfoData))
    		{
        		TimeUtils::SleepInMilliseconds(Storage::STORAGE_READ_TIME_IN_MILLISECOND);
    			incubatorData.m_MemoryDeviceErrorState    	= ERROR_STATE_NO_ERROR;
    		    incubatorData.m_HumidityStart             	= humidityData.m_HumidityStartPercentage;
    		    incubatorData.m_HumidityEnd               	= humidityData.m_HumidityEndPercentage;
    		    incubatorData.m_HumidityDesired           	= (incubatorData.m_HumidityStart + incubatorData.m_HumidityEnd) / 2;

				incubatorData.m_MotorsOffHumidityStart    	= humidityData.m_MotorsOffHumidityStartPercentage;
				incubatorData.m_MotorsOffHumidityEnd      	= humidityData.m_MotorsOffHumidityEndPercentage;
    		    incubatorData.m_MotorsOffHumidityDesired  	= (incubatorData.m_MotorsOffHumidityStart + incubatorData.m_MotorsOffHumidityEnd) / 2;

    		    incubatorData.m_TemperatureStart          	= temperatureData.m_TemperatureStartInDeciDegrees;
    		    incubatorData.m_TemperatureEnd            	= temperatureData.m_TemperatureEndInDeciDegrees;
    		    incubatorData.m_TemperatureDesired        	= (incubatorData.m_TemperatureStart + incubatorData.m_TemperatureEnd) / 2;

				incubatorData.m_MotorsOffTemperatureStart 	= temperatureData.m_MotorsOffTemperatureStartInDeciDegrees;
				incubatorData.m_MotorsOffTemperatureEnd   	= temperatureData.m_MotorsOffTemperatureEndInDeciDegrees;
				incubatorData.m_MotorsOffTemperatureDesired	= (incubatorData.m_MotorsOffTemperatureStart + incubatorData.m_MotorsOffTemperatureEnd) / 2;

    		    incubatorData.m_CurrentTimestampInSeconds 	= timeInfoData.m_IncubatorCurrentTimestampInSeconds;
    		    incubatorData.m_TotalIncubationDayCount   	= timeInfoData.m_TotalDayCount;
    		    incubatorData.m_MotorOffDayCount          	= timeInfoData.m_MotorOffDayCount;
    		}
    	}
    }
}


bool IncubatorUtils::IsInMotorsOffTime(const IncubatorData &incubatorData)
{
	constexpr const uint32_t SECOND_OVER_DAY = 24 * 3600;
	bool bResult = false;
	if (incubatorData.m_CurrentTimestampInSeconds > (incubatorData.m_TotalIncubationDayCount - incubatorData.m_MotorOffDayCount) * SECOND_OVER_DAY)
	{
		bResult = true;
	}
	return bResult;
}

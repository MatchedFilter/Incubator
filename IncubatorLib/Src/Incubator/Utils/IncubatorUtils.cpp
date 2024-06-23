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
        TimeUtils::SleepInMilliseconds(20);
    	if (Storage::Query(temperatureData))
    	{
        	TimeUtils::SleepInMilliseconds(20);
    		if (Storage::Query(timeInfoData))
    		{
        		TimeUtils::SleepInMilliseconds(20);
    			incubatorData.m_MemoryDeviceErrorState    = ERROR_STATE_NO_ERROR;
    		    incubatorData.m_HumidityStart             = humidityData.m_HumidityStartPercentage;
    		    incubatorData.m_HumidityEnd               = humidityData.m_HumidityEndPercentage;
    		    incubatorData.m_HumidityDesired           = (incubatorData.m_HumidityStart + incubatorData.m_HumidityEnd) / 2;

    		    incubatorData.m_TemperatureStart          = temperatureData.m_TemperatureStartInDeciDegrees;
    		    incubatorData.m_TemperatureEnd            = temperatureData.m_TemperatureEndInDeciDegrees;
    		    incubatorData.m_TemperatureDesired        = (incubatorData.m_TemperatureStart + incubatorData.m_TemperatureEnd) / 2;

    		    incubatorData.m_StartTimestampInSeconds   = timeInfoData.m_IncbutorStartTimestampInSeconds;
    		    incubatorData.m_CurrentTimestampInSeconds = timeInfoData.m_IncubatorCurrentTimestampInSeconds;
    		    incubatorData.m_TotalIncubationDayCount   = timeInfoData.m_TotalDayCount;
    		    incubatorData.m_MotorOffDayCount          = timeInfoData.m_MotorOffDayCount;
    		}
    	}
    }
}

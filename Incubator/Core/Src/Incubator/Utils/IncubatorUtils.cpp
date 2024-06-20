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
        TimeUtils::SleepInMilliseconds(1);
    	if (Storage::Query(temperatureData))
    	{
        	TimeUtils::SleepInMilliseconds(1);
    		if (Storage::Query(timeInfoData))
    		{
        		TimeUtils::SleepInMilliseconds(1);
    			incubatorData.m_MemoryDeviceErrorState    = ERROR_STATE_NO_ERROR;
    		    incubatorData.m_HumidityDesired           = humidityData.m_HumidityDesiredInMilliDegrees;
    		    incubatorData.m_HumidityStart             = humidityData.m_HumidityStartPercentage;
    		    incubatorData.m_HumidityEnd               = humidityData.m_HumidityEndPercentage;

    		    incubatorData.m_TemperatureDesired        = temperatureData.m_TemperatureDesiredInMilliDegrees;
    		    incubatorData.m_TemperatureStart          = temperatureData.m_TemperatureStartInMilliDegrees;
    		    incubatorData.m_TemperatureEnd            = temperatureData.m_TemperatureEndInMilliDegrees;

    		    incubatorData.m_StartTimestampInSeconds   = timeInfoData.m_IncbutorStartTimestampInSeconds;
    		    incubatorData.m_CurrentTimestampInSeconds = timeInfoData.m_IncubatorCurrentTimestampInSeconds;
    		    incubatorData.m_TotalIncubationDayCount   = timeInfoData.m_TotalDayCount;
    		    incubatorData.m_MotorOffDayCount          = timeInfoData.m_MotorOffDayCount;
    		}
    	}
    }
}

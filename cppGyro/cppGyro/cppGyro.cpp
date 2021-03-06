// cppGyro.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <InitGuid.h>
#include <SensorsApi.h>
#include <Sensors.h>

#include "cppGyro.h"
#pragma comment(lib, "Sensorsapi.lib")

__declspec (dllexport) PluginVector3 GetGyrometer()
{
	ISensorManager *pSensorManager;
	ISensorCollection *pMotionSensorCollection;
	ISensor *pMotionSensor;

	if (!SUCCEEDED(::CoCreateInstance(CLSID_SensorManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pSensorManager))))
	{
		return PluginVector3();
	}
	if (!SUCCEEDED(pSensorManager->GetSensorsByCategory(SENSOR_TYPE_GYROMETER_3D, &pMotionSensorCollection)))
	{
		pSensorManager->Release();
		return PluginVector3();
	}
	if (!SUCCEEDED(pMotionSensorCollection->GetAt(0, &pMotionSensor)))
	{
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}

	ISensorDataReport *pData;
	if (!SUCCEEDED(pMotionSensor->GetData(&pData)))
	{
		pMotionSensor->Release();
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}

	PROPVARIANT x = {};
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_ANGULAR_VELOCITY_X_DEGREES_PER_SECOND, &x)))
	{
		pData->Release();
		pMotionSensor->Release();
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}
	PROPVARIANT y = {};
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_ANGULAR_VELOCITY_Y_DEGREES_PER_SECOND, &y)))
	{
		pData->Release();
		pMotionSensor->Release();
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}
	PROPVARIANT z = {};
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_ANGULAR_VELOCITY_Z_DEGREES_PER_SECOND, &z)))
	{
		pData->Release();
		pMotionSensor->Release();
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}

	pData->Release();
	pMotionSensor->Release();
	pMotionSensorCollection->Release();
	pSensorManager->Release();

	PluginVector3 v;
	v.x = x.dblVal;
	v.y = y.dblVal;
	v.z = z.dblVal;
	return v;
}

__declspec (dllexport) float GetGyrometerX()
{
	PluginVector3 v = GetGyrometer();

	return v.x;
}

__declspec (dllexport) float GetGyrometerY()
{
	PluginVector3 v = GetGyrometer();

	return v.y;
}

__declspec (dllexport) float GetGyrometerZ()
{
	PluginVector3 v = GetGyrometer();

	return v.z;
}





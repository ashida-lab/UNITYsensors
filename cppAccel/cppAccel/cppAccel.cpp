// cppAccel.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <InitGuid.h>
#include <SensorsApi.h>
#include <Sensors.h>

#include "cppAccel.h"
#pragma comment(lib, "Sensorsapi.lib")

__declspec (dllexport) PluginVector3 GetAccelerometer()
{
	ISensorManager *pSensorManager;
	ISensorCollection *pMotionSensorCollection;
	ISensor *pMotionSensor;

	if (!SUCCEEDED(::CoCreateInstance(CLSID_SensorManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pSensorManager))))
	{
		return PluginVector3();
	}
	if (!SUCCEEDED(pSensorManager->GetSensorsByCategory(SENSOR_TYPE_ACCELEROMETER_3D, &pMotionSensorCollection)))
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
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_ACCELERATION_X_G, &x)))
	{
		pData->Release();
		pMotionSensor->Release();
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}
	PROPVARIANT y = {};
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_ACCELERATION_Y_G, &y)))
	{
		pData->Release();
		pMotionSensor->Release();
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}
	PROPVARIANT z = {};
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_ACCELERATION_Z_G, &z)))
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

__declspec (dllexport) float GetAccelerometerX()
{
	PluginVector3 v = GetAccelerometer();

	return v.x;
}

__declspec (dllexport) float GetAccelerometerY()
{
	PluginVector3 v = GetAccelerometer();

	return v.y;
}

__declspec (dllexport) float GetAccelerometerZ()
{
	PluginVector3 v = GetAccelerometer();

	return v.z;
}


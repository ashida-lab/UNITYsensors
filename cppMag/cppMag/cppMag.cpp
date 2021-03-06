// cppMag.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <InitGuid.h>
#include <SensorsApi.h>
#include <Sensors.h>

#include "cppMag.h"
#pragma comment(lib, "Sensorsapi.lib")

__declspec (dllexport) PluginVector3 GetMagnetometer()
{
	ISensorManager *pSensorManager;
	ISensorCollection *pMotionSensorCollection;
	ISensor *pMotionSensor;

	if (!SUCCEEDED(::CoCreateInstance(CLSID_SensorManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pSensorManager))))
	{
		return PluginVector3();
	}
	if (!SUCCEEDED(pSensorManager->GetSensorsByCategory(SENSOR_TYPE_COMPASS_3D, &pMotionSensorCollection)))
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
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_MAGNETIC_FIELD_STRENGTH_X_MILLIGAUSS, &x)))
	{
		pData->Release();
		pMotionSensor->Release();
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}
	PROPVARIANT y = {};
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_MAGNETIC_FIELD_STRENGTH_Y_MILLIGAUSS, &y)))
	{
		pData->Release();
		pMotionSensor->Release();
		pMotionSensorCollection->Release();
		pSensorManager->Release();
		return PluginVector3();
	}
	PROPVARIANT z = {};
	if (!SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_MAGNETIC_FIELD_STRENGTH_Z_MILLIGAUSS, &z)))
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

__declspec (dllexport) float GetMagnetometerX()
{
	PluginVector3 v = GetMagnetometer();

	return v.x;
}

__declspec (dllexport) float GetMagnetometerY()
{
	PluginVector3 v = GetMagnetometer();

	return v.y;
}

__declspec (dllexport) float GetMagnetometerZ()
{
	PluginVector3 v = GetMagnetometer();

	return v.z;
}





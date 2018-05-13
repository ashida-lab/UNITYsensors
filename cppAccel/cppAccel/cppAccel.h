#pragma once

extern "C"
{
	struct PluginVector3
	{
		double x;
		double y;
		double z;
	};

	__declspec (dllexport) PluginVector3 GetAccelerometer();
	__declspec (dllexport) float GetAccelerometerX();
	__declspec (dllexport) float GetAccelerometerY();
	__declspec (dllexport) float GetAccelerometerZ();
}
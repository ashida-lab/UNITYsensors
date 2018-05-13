#pragma once

extern "C"
{
	struct PluginVector3
	{
		double x;
		double y;
		double z;
	};

	__declspec (dllexport) PluginVector3 GetGyrometer();
	__declspec (dllexport) float GetGyrometerX();
	__declspec (dllexport) float GetGyrometerY();
	__declspec (dllexport) float GetGyrometerZ();
}
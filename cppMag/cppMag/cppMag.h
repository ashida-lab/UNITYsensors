#pragma once

extern "C"
{
	struct PluginVector3
	{
		double x;
		double y;
		double z;
	};

	__declspec (dllexport) PluginVector3 GetMagnetometer();
	__declspec (dllexport) float GetMagnetometerX();
	__declspec (dllexport) float GetMagnetometerY();
	__declspec (dllexport) float GetMagnetometerZ();
}
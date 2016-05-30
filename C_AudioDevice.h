//@file:C_Device.h
//@brief: 定义设备的接口方法。
//@author: wangzhongping@oristartech.com
//date: 2012-05-23

#ifndef _H_AUDIODEVICE_
#define _H_AUDIODEVICE_

#include "device/C_Device.h"
#include <vector>

class C_AudioDevice : public C_Device
{
public:
	C_AudioDevice() : C_Device(){};
	virtual ~C_AudioDevice(){}

	enum
	{
		GAMECHANNEL = 100
	};

    virtual int GetAudioStatus(int &iValue, int &iMute, int &iChanel,
		std::vector<std::string> &vecChanelList) = 0;
    virtual int SetValue(int iValue) = 0;
    virtual int SetMute(int iMute) = 0;
    virtual int SetChanel(int iChanel) = 0;
    virtual int SetValueAndMute(int iValue,int iMute) = 0;
	virtual int SetChanel(const std::string &chanel) = 0;
};

#endif//_H_AUDIODEVICE_

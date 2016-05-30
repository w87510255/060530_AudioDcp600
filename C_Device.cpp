//@file:C_Device.cpp
//@brief: 实现少数设备通用的接口方法。
//@author: wangzhongping@oristartech.com
//date: 2012-05-23

#include "device/C_Device.h"

using namespace std;

//duheqing 2012-6-6
int C_Device::SetError(int iErrorNum, const string &strErrorInfo)
{
	m_strErrorInfo = strErrorInfo;
	m_iErrorNum = iErrorNum;
	return 0;
}

int C_Device::GetError(string &strErrorInfo) const
{
    //printf("Call method C_Device GetError!\n");
    strErrorInfo =  m_strErrorInfo;
    return m_iErrorNum;
}

/*void C_Device::GetConncetState(int &iConnectState)
{
    printf("Call method C_Device GetConncetState!\n");   
    iConnectState = m_bConnect;
}*/

C_Device::~C_Device()
{
    //printf("Call method C_Device ~C_Device!\n");
}

C_Device::C_Device()
{
    //printf("Call method C_Device C_Device!\n");
    m_iReadInterval = 1;
}

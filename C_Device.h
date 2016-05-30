//@file:C_Device.h
//@brief: 定义设备通用的接口方法。
//@author: wangzhongping@oristartech.com;duheqingoristartech.com
//date: 2012-05-23

#ifndef _H_DEVICE_
#define _H_DEVICE_
#include <stdlib.h>
#include <algorithm>
#include <string>

class C_Device
{
private:
	//错误码；
   int m_iErrorNum;
   //错误信息。  
   std::string m_strErrorInfo;
   //int m_bConnect; //0: Connected; 1:UnConnected;
   
protected:
   //读操作间隔时间，单位：秒,不同的设备分别设置。默认为1
   int m_iReadInterval; 
   //写操作间隔时间，单位：秒,不同的设备分别设置。默认为1
   int m_iWriteIterval;
   // 读操作的等待时间。
   int m_iReadWait;
public:
   C_Device();
   virtual ~C_Device();
   //初始化设备。，支持更换设备后的重新初始化。
   virtual int Init(const std::string &strIp, unsigned short usPort,
	   const std::string &strUserName, const std::string &strPassword) = 0;

   //duheqing 2012-6-5
   int SetError(int iErrorNum, const std::string &strErrorInfo);
   int GetError(std::string &strErrorInfo) const;//return m_iErrorNum;
	 int GetReadInterval()
	 {
	 		return m_iReadInterval;
	 }
	 int GetWriteInterval()
	 {
	 	 return m_iWriteIterval;
	 }
	 int GetReadWait()	 
	 {
	 		return m_iReadWait;
	 }
	 
	 void SetReadInterval(int iReadInterval)
	 {
	 	 m_iReadInterval = iReadInterval;
	 }
	 
	 void SetReadWait(int iReadWait)
	 {
	 		m_iReadWait = iReadWait;	
	 }
	 
	 void SetWriteInterval(int iWriteInterval) 
	 {
	 	 m_iWriteIterval = iWriteInterval;
	 }
   virtual int GetConncetState() = 0;
   virtual int Close() = 0; 
   virtual int GetVersion(std::string &strVersion) = 0;
};

#endif//_H_DEVICE_

//@file:  C_AudioDcp600.h
//@brief: 实现音频设备Dcp 600 接口定义。
//@author:zhangmiao@oristartech.com
//date:   2015-06-24 

#ifndef _H_AUDIO_DCP600_
#define _H_AUDIO_DCP600_

#include "constDef/C_ErrorDef.h"
#include "device/audio/C_AudioDevice.h"
#include "common/C_TcpSocket.h"
#ifndef _UDPTRANSPORT_H_
#include "UdpTransport.h"
#endif

#include <vector>
#include <string>
#include <cstring>
#include <cstdio>

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

const int nDcp600_Offset_MuteState    = 0x369;   //0x369 = 873  
const int nDcp600_Offset_ChannelState = 0x35a;   //0x35a = 858 

//通道与面板的对应关系
//通道0=Digital8，通道1=Analog8，通道2=NonSync，通道3=Aux，
const int nDcp600_Offset_Vol_Ch00 = 0x35d;  //0x35d = 861 通道0，音量值的偏移地址
const int nDcp600_Offset_Vol_Ch01 = 0x35e;  //0x35e = 862 通道1，音量值的偏移地址
const int nDcp600_Offset_Vol_Ch02 = 0x35f;  //0x35f = 863 通道2，音量值的偏移地址
const int nDcp600_Offset_Vol_Ch03 = 0x360;  //0x360 = 864 通道3，音量值的偏移地址

#define _DEBUG_

class C_AudioDCP600 : public C_AudioDevice
{
	std::vector<std::string> m_chanelList;	//通道列表
	
	std::string m_ip;			//IP地址
	unsigned short m_port;		//端口号:2305
	std::string m_userName;
	std::string m_passwd;

	//连接状态  0----无法连接；	1----可以连接
	int m_bConnected; 

	//保存每个通道对应的音量值，共8个，dcp600只用了4个，index = 0 , 1 , 2 , 3  
	char m_Channel_VolList[8];

	//当前通道号，从0--3
	int m_CurChannelNum;

	//表示：之前是否执行过获取状态函数GetAudioStatus().
	int m_IsLoadFunc_GetAudioStatus;

public:
	C_AudioDCP600();
	virtual ~C_AudioDCP600();

	virtual int Init(const std::string &strIp, unsigned short usPort, const std::string &strUserName, const std::string &strPassword);

	virtual int Close();

	//设置静音状态,1表示静音状态，0表示非静音状态
	virtual int SetMute(int iMute);

	//获取音频处理器当前状态
	//静音状态iMute=1；非静音状态iMute=0
	virtual int GetAudioStatus(int &iValue, int &iMute, int &iChanel,std::vector<std::string> &vecChanelList);

	//设置音量 0-100，内部使用0-100，对应面板上的0 - 10.0,每个通道是独立控制的。
	virtual int SetValue(int iValue);
	//设置通道号 0-3,
	virtual int SetChanel(int iChanel);

	//目前没使用
	virtual int SetChanel(const std::string &chanel);
	//目前没使用
	virtual int SetValueAndMute(int iValue,int iMute);

	virtual int GetVersion(std::string &strVersion);
	virtual int GetConncetState();

#if 0
	int GetChanelData();
	int GetVolumeData();
	int GetMuteData();
#endif


 private:

	//GetChanel()、GetVolume()函数，内部用于测试，不对外调用
	int GetChanel( int &chanel );
	int GetVolume( int &volume );

	
	//被SetValue函数调用  SetValue()--->SetVolume()，
	int SetVolume( int volume );

	//该函数被SetChanel(int iChanel)调用  SetChanel()--->SetChanel_type()
	int SetChanel_type(int type);

	//被GetAudioStatus函数调用  GetAudioStatus()--->GetAll()
	int GetAll(int &volume, int &mute, int &channel);

	//UDP发送、接收命令数据
	int SendAndRecv( const char *sendBuffer, int size, char *recvBuffer, int& rRecvDataLength );

	
	int GetMuteRet( const char *info , int &mute , int Length );
	int GetChanelType( char *info , int &type , int Length );
	
	int GetVolumeRet( const char *info , int Length );
	
};

#define TMS2_AUDIO_ERRCODE
#ifdef TMS2_AUDIO_ERRCODE
#define AD600TT(error) Dcp600ErrorCodeToTmsErrorCode(error);
#define AD600TT2(error) Dcp600ErrorCodeToTmsErrorCode(error)
int Dcp600ErrorCodeToTmsErrorCode(int error);
#else
#define AD600TT(error) (error);
#define AD600TT2(error) (error)
#endif // TMS2_AUDIO_ERRCODE

#define WRITE_DCP600ELOG 
#ifdef WRITE_DCP600ELOG
#define WDCP600LOG(str) Dcp600_WriteErrorLog(str);
int Dcp600_WriteErrorLog( const std::string& strError );
#else
#define WDCP600LOG(str) 
#endif // WRITE_DCP600ELOG

const int ERROR_AUDIO_DCP_600_CANNOTCONNECT      = -101;		//can not connect the audio server
const int ERROR_AUDIO_DCP_600_UDPTRANSPORTFAILED = -102;	    //udp transport failed
const int ERROR_AUDIO_DCP_600_PARAMETERERROR     = -103;		//function get a bad parameter
const int ERROR_AUDIO_DCP_600_OPERATORFAILED     = -104;		//audio error, operator failed
const int ERROR_AUDIO_DCP_600_PARSER_FAILED      = -105;		//message error, operator failed

#endif//_H_AUDIO_DCP600_


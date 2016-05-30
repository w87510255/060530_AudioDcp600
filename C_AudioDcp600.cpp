//@file:  C_AudioDcp600.cpp
//@brief: 实现音频设备Dcp 600 接口定义。
//@author:zhangmiao@oristartech.com
//date:   2015-06-24 
#ifndef _H_AUDIO_DCP600_
#include "device/audio/dcp600/C_AudioDcp600.h"
#endif

using namespace std;


//采用UDP通讯模式，本地端口固定为2305。
const unsigned short udp_port = 2305 ;
const int BUFFERLENGTH = 1024*1;
const int MINDELYTIME = 30;

C_AudioDCP600::C_AudioDCP600()
  : C_AudioDevice()
{
	//目前通道只用了4个
    m_chanelList.clear();
	m_chanelList.push_back("Digital8");
	m_chanelList.push_back("Analog8");
	m_chanelList.push_back("NonSync");
	m_chanelList.push_back("Aux");
    //m_chanelList.push_back("Mic");
	m_chanelList.push_back("unknow");

	m_bConnected = 0;
}

C_AudioDCP600::~C_AudioDCP600()
{
	m_bConnected = 0;
}

//初始化连接
int C_AudioDCP600::Init(const string &strIp, unsigned short usPort,
					   const string &strUserName, const string &strPassword)
{
	m_ip = strIp;
	m_port = usPort;
	m_userName = strUserName;
	m_passwd = strPassword;

	m_IsLoadFunc_GetAudioStatus = 0;

	for ( int i = 0; i < 8; i++ )
	{
		m_Channel_VolList[i] = 70;	//0x46
	}

	m_bConnected = 1;

	WDCP600LOG( m_ip + "*DCP-600_Init" );
	
	return 0;
}

//释放连接
int C_AudioDCP600::Close()
{
	//WDCP600LOG(m_ip+"*DCP-600_Close");
	return 0;
}

//获得连接状态； 连接，返回1；未连接，返回0
int C_AudioDCP600::GetConncetState()
{
	return m_bConnected;
}

int C_AudioDCP600::GetVersion(string &strVersion)
{
	strVersion = "ENPAR DCP-600";
	return 0;
}

//获取音频处理器当前状态
//静音状态iMute=1；非静音状态iMute=0
int C_AudioDCP600::GetAudioStatus( int &iValue, int &iMute, int &iChanel, vector<string> &vecChanelList )
{
    int result = 0;
    int currentVolume(0) , currentChanel = 0;
    int currentMute = 0;
	
	WDCP600LOG( m_ip + "*DCP-600_GetAudioStatus" );
    
	result = GetAll( currentVolume , currentMute , currentChanel );
    if(result == 0)
	{
		WDCP600LOG( m_ip + "*DCP-600_GetAudioStatus_Success!" );
		
		iValue  = currentVolume;
		iMute   = currentMute;
		iChanel = currentChanel;
        
		vecChanelList = m_chanelList;

		m_bConnected = 1;
		m_IsLoadFunc_GetAudioStatus = 1;
		m_CurChannelNum = currentChanel;

		return 0;
	}
	else
	{
		WDCP600LOG( m_ip + "*DCP-600_GetAudioStatus_Fail!" );
		m_bConnected = 0;
		Close();
		return AD600TT(ERROR_AUDIO_DCP_600_OPERATORFAILED);
	}
}

//被GetAudioStatus函数调用  GetAudioStatus()--->GetAll()
int C_AudioDCP600::GetAll(int &volume, int &mute, int &channel)
{
	int result = 0;
	int rRecvDataLength = 0;
	char sendBuffer[BUFFERLENGTH];
	char recvBuffer[BUFFERLENGTH];
	memset(sendBuffer, 0, BUFFERLENGTH);
	memset(recvBuffer, 0, BUFFERLENGTH);

	sendBuffer[0] = 0x53;	//DCP600 控制命令以 “SetPara”  +  “DCP600ConfigData” 为前导识别验证字 
	sendBuffer[1] = 0x65;
	sendBuffer[2] = 0x74;
	sendBuffer[3] = 0x50;
	sendBuffer[4] = 0x61;
	sendBuffer[5] = 0x72;
	sendBuffer[6] = 0x61;
	sendBuffer[7] = 0x00;
	sendBuffer[8] = 0x00;
	sendBuffer[9] = 0x00;
	sendBuffer[10] = 0x44;	//DCP600
	sendBuffer[11] = 0x43;
	sendBuffer[12] = 0x50;
	sendBuffer[13] = 0x36;  //0x36 => '6'
	sendBuffer[14] = 0x30;	//0x30 => '0'
	sendBuffer[15] = 0x30;  //0x30 => '0'
	sendBuffer[16] = 0x43;
	sendBuffer[17] = 0x6f;
	sendBuffer[18] = 0x6e;
	sendBuffer[19] = 0x66;
	sendBuffer[20] = 0x69;
	sendBuffer[21] = 0x67;
	sendBuffer[22] = 0x44;
	sendBuffer[23] = 0x61;
	sendBuffer[24] = 0x74;
	sendBuffer[25] = 0x61;
	sendBuffer[26] = 0x00;
	sendBuffer[27] = 0x00;
	sendBuffer[28] = 0x00;
	sendBuffer[29] = 0x00;
	sendBuffer[30] = 0xca;	//StartByte = 0xca;
	sendBuffer[31] = 0x03;	//CmdType = 0x03;
	sendBuffer[32] = 0x00;	//ParaStaAdd =0x00 00
	sendBuffer[33] = 0x00;
	sendBuffer[34] = 0x58;	//ParaNum = 0x58 03
	sendBuffer[35] = 0x03;
	sendBuffer[36] = 0x00;
	sendBuffer[37] = 0x00;	

	int requestSize = 38;	  //发送command命令的总长度
	//int resultLengthS = 894;  //成功response,数据的总字节数

	int iCmd_GetStatusLen = requestSize;

#ifdef _DEBUG_
	printf("\nSend Cmd_GetStatusLen Data:%d\n\n" , iCmd_GetStatusLen );
#endif

	result = SendAndRecv( sendBuffer , iCmd_GetStatusLen , recvBuffer , rRecvDataLength );
	if(result != 0)
		return result;

#ifdef _DEBUG_
	printf( "\nRecv GetAll Data Length:%d\n\n" , rRecvDataLength );
#endif

	//获取GetMuteState
	result = GetMuteRet( recvBuffer, mute , rRecvDataLength  );
	if ( result != 0 )
	{
		return result;
	}

	//获取GetChanelState
	result = GetChanelType(recvBuffer, channel , rRecvDataLength );
	if ( result != 0 )
	{
		return result;
	}

	//获取GetVolume
	result = GetVolumeRet( recvBuffer, rRecvDataLength );
	if ( result == 0 )
	{
		if ( channel == 0 )
		{
			volume = m_Channel_VolList[0];
		} 
		else if( channel == 1 )
		{
			volume = m_Channel_VolList[1];
		}
		else if( channel == 2 )
		{
			volume = m_Channel_VolList[2];
		}
		else if( channel == 3 )
		{
			volume = m_Channel_VolList[3];
		}
		else
		{
			volume = 70;
		}
	}
	else
	{
		return result;
	}

	return 0;
}

#if 0
int C_AudioDCP600::GetChanelData()
{
	int result = 0;
	int rRecvDataLength = 0;
	char sendBuffer[BUFFERLENGTH];
	char recvBuffer[BUFFERLENGTH];
	memset(sendBuffer, 0, BUFFERLENGTH);
	memset(recvBuffer, 0, BUFFERLENGTH);

	sendBuffer[0] = 0x53;	//DCP1000 控制命令以 “SetPara”  +  “DCP1002ConfigData” 为前导识别验证字
	sendBuffer[1] = 0x65;
	sendBuffer[2] = 0x74;
	sendBuffer[3] = 0x50;
	sendBuffer[4] = 0x61;
	sendBuffer[5] = 0x72;
	sendBuffer[6] = 0x61;
	sendBuffer[7] = 0x00;
	sendBuffer[8] = 0x00;
	sendBuffer[9] = 0x00;
	sendBuffer[10] = 0x44;	//DCP1002
	sendBuffer[11] = 0x43;
	sendBuffer[12] = 0x50;
	sendBuffer[13] = 0x31;
	sendBuffer[14] = 0x30;	//0x30 => '0'
	sendBuffer[15] = 0x30;
	sendBuffer[16] = 0x32;	//0x32 => '2'
	sendBuffer[17] = 0x43;
	sendBuffer[18] = 0x6f;
	sendBuffer[19] = 0x6e;
	sendBuffer[20] = 0x66;
	sendBuffer[21] = 0x69;
	sendBuffer[22] = 0x67;
	sendBuffer[23] = 0x44;
	sendBuffer[24] = 0x61;
	sendBuffer[25] = 0x74;
	sendBuffer[26] = 0x61;
	sendBuffer[27] = 0x00;
	sendBuffer[28] = 0x00;
	sendBuffer[29] = 0x00;
	sendBuffer[30] = 0xca;	//StartByte = 0xca;
	sendBuffer[31] = 0x03;	//CmdType = 0x03;
	sendBuffer[32] = 0x36;	//ParaStaAdd =0x36 03
	sendBuffer[33] = 0x03;
	sendBuffer[34] = 0x03;	//ParaNum = 0x03 00 
	sendBuffer[35] = 0x00;
	sendBuffer[36] = 0x00;
	sendBuffer[37] = 0x00;	

	int requestSize = 38;	  //发送command命令的总长度
	//int resultLengthS = 894;  //成功response,数据的总字节数

	int iCmd_GetStatusLen = requestSize;

#ifdef _DEBUG_
	printf("\nSend Cmd_GetStatusLen Data:%d\n\n" , iCmd_GetStatusLen );
#endif

	result = SendAndRecv( sendBuffer , iCmd_GetStatusLen , recvBuffer , rRecvDataLength );
	if(result != 0)
		return result;

#ifdef _DEBUG_
	printf( "\nRecv GetChanelData Data Length:%d\n\n" , rRecvDataLength );
#endif

	return 0;
}

int C_AudioDCP600::GetMuteData()
{
	int result = 0;
	int rRecvDataLength = 0;
	char sendBuffer[BUFFERLENGTH];
	char recvBuffer[BUFFERLENGTH];
	memset(sendBuffer, 0, BUFFERLENGTH);
	memset(recvBuffer, 0, BUFFERLENGTH);

	sendBuffer[0] = 0x53;	//DCP1000 控制命令以 “SetPara”  +  “DCP1002ConfigData” 为前导识别验证字
	sendBuffer[1] = 0x65;
	sendBuffer[2] = 0x74;
	sendBuffer[3] = 0x50;
	sendBuffer[4] = 0x61;
	sendBuffer[5] = 0x72;
	sendBuffer[6] = 0x61;
	sendBuffer[7] = 0x00;
	sendBuffer[8] = 0x00;
	sendBuffer[9] = 0x00;
	sendBuffer[10] = 0x44;	//DCP1002
	sendBuffer[11] = 0x43;
	sendBuffer[12] = 0x50;
	sendBuffer[13] = 0x31;
	sendBuffer[14] = 0x30;	//0x30 => '0'
	sendBuffer[15] = 0x30;
	sendBuffer[16] = 0x32;	//0x32 => '2'
	sendBuffer[17] = 0x43;
	sendBuffer[18] = 0x6f;
	sendBuffer[19] = 0x6e;
	sendBuffer[20] = 0x66;
	sendBuffer[21] = 0x69;
	sendBuffer[22] = 0x67;
	sendBuffer[23] = 0x44;
	sendBuffer[24] = 0x61;
	sendBuffer[25] = 0x74;
	sendBuffer[26] = 0x61;
	sendBuffer[27] = 0x00;
	sendBuffer[28] = 0x00;
	sendBuffer[29] = 0x00;
	sendBuffer[30] = 0xca;	//StartByte = 0xca;
	sendBuffer[31] = 0x03;	//CmdType = 0x03;
	sendBuffer[32] = 0x45;	//ParaStaAdd =0x45 03
	sendBuffer[33] = 0x03;
	sendBuffer[34] = 0x01;	//ParaNum = 0x01 00 
	sendBuffer[35] = 0x00;
	sendBuffer[36] = 0x00;
	sendBuffer[37] = 0x00;	

	int requestSize = 38;	  //发送command命令的总长度
	//int resultLengthS = 894;  //成功response,数据的总字节数

	int iCmd_GetStatusLen = requestSize;

#ifdef _DEBUG_
	printf("\nSend Cmd_GetStatusLen Data:%d\n\n" , iCmd_GetStatusLen );
#endif

	result = SendAndRecv( sendBuffer , iCmd_GetStatusLen , recvBuffer , rRecvDataLength );
	if(result != 0)
		return result;

#ifdef _DEBUG_
	printf( "\nRecv GetMuteData Data Length:%d\n\n" , rRecvDataLength );
#endif

	return 0;
}


int C_AudioDCP600::GetVolumeData()
{
	int result = 0;
	int rRecvDataLength = 0;
	char sendBuffer[BUFFERLENGTH];
	char recvBuffer[BUFFERLENGTH];
	memset(sendBuffer, 0, BUFFERLENGTH);
	memset(recvBuffer, 0, BUFFERLENGTH);

	sendBuffer[0] = 0x53;	//DCP1000 控制命令以 “SetPara”  +  “DCP1002ConfigData” 为前导识别验证字
	sendBuffer[1] = 0x65;
	sendBuffer[2] = 0x74;
	sendBuffer[3] = 0x50;
	sendBuffer[4] = 0x61;
	sendBuffer[5] = 0x72;
	sendBuffer[6] = 0x61;
	sendBuffer[7] = 0x00;
	sendBuffer[8] = 0x00;
	sendBuffer[9] = 0x00;
	sendBuffer[10] = 0x44;	//DCP1002
	sendBuffer[11] = 0x43;
	sendBuffer[12] = 0x50;
	sendBuffer[13] = 0x31;
	sendBuffer[14] = 0x30;	//0x30 => '0'
	sendBuffer[15] = 0x30;
	sendBuffer[16] = 0x32;	//0x32 => '2'
	sendBuffer[17] = 0x43;
	sendBuffer[18] = 0x6f;
	sendBuffer[19] = 0x6e;
	sendBuffer[20] = 0x66;
	sendBuffer[21] = 0x69;
	sendBuffer[22] = 0x67;
	sendBuffer[23] = 0x44;
	sendBuffer[24] = 0x61;
	sendBuffer[25] = 0x74;
	sendBuffer[26] = 0x61;
	sendBuffer[27] = 0x00;
	sendBuffer[28] = 0x00;
	sendBuffer[29] = 0x00;
	sendBuffer[30] = 0xca;	//StartByte = 0xca;
	sendBuffer[31] = 0x03;	//CmdType = 0x03;
	sendBuffer[32] = 0x39;	//ParaStaAdd =0x39 03
	sendBuffer[33] = 0x03;
	sendBuffer[34] = 0x08;	//ParaNum = 0x08 00 
	sendBuffer[35] = 0x00;
	sendBuffer[36] = 0x00;
	sendBuffer[37] = 0x00;	

	int requestSize = 38;	  //发送command命令的总长度
	//int resultLengthS = 894;  //成功response,数据的总字节数

	int iCmd_GetStatusLen = requestSize;

#ifdef _DEBUG_
	printf("\nSend Cmd_GetStatusLen Data:%d\n\n" , iCmd_GetStatusLen );
#endif

	result = SendAndRecv( sendBuffer , iCmd_GetStatusLen , recvBuffer , rRecvDataLength );
	if(result != 0)
		return result;

#ifdef _DEBUG_
	printf( "\nRecv GetVolumeData Data Length:%d\n\n" , rRecvDataLength );
#endif

	return 0;
}
#endif

//设置静音状态,1表示静音状态，0表示非静音状态
int C_AudioDCP600::SetMute(int iMute)
{
	int result = 0;
	int rRecvDataLength = 0;
	char sendBuffer[BUFFERLENGTH];
	char recvBuffer[BUFFERLENGTH];
	memset(sendBuffer, 0, BUFFERLENGTH);
	memset(recvBuffer, 0, BUFFERLENGTH);

	sendBuffer[0] = 0x53;	//DCP600 控制命令以 “SetPara”  +  “DCP600ConfigData” 为前导识别验证字 
	sendBuffer[1] = 0x65;
	sendBuffer[2] = 0x74;
	sendBuffer[3] = 0x50;
	sendBuffer[4] = 0x61;
	sendBuffer[5] = 0x72;
	sendBuffer[6] = 0x61;
	sendBuffer[7] = 0x00;
	sendBuffer[8] = 0x00;
	sendBuffer[9] = 0x00;
	sendBuffer[10] = 0x44;	//DCP600
	sendBuffer[11] = 0x43;
	sendBuffer[12] = 0x50;
	sendBuffer[13] = 0x36;  //0x36 => '6'
	sendBuffer[14] = 0x30;	//0x30 => '0'
	sendBuffer[15] = 0x30;  //0x30 => '0'
	sendBuffer[16] = 0x43;
	sendBuffer[17] = 0x6f;
	sendBuffer[18] = 0x6e;
	sendBuffer[19] = 0x66;
	sendBuffer[20] = 0x69;
	sendBuffer[21] = 0x67;
	sendBuffer[22] = 0x44;
	sendBuffer[23] = 0x61;
	sendBuffer[24] = 0x74;
	sendBuffer[25] = 0x61;
	sendBuffer[26] = 0x00;
	sendBuffer[27] = 0x00;
	sendBuffer[28] = 0x00;
	sendBuffer[29] = 0x00;
	sendBuffer[30] = 0xca;	//StartByte = 0xca;
	sendBuffer[31] = 0x06;	//CmdType = 0x06;
	sendBuffer[32] = 0x45;	//ParaStaAdd =0x45 03
	sendBuffer[33] = 0x03;
	sendBuffer[34] = 0x01;	//ParaNum = 1;0x01 00
	sendBuffer[35] = 0x00;

	sendBuffer[36] = ((iMute == 1) ? 0x01 : 0x00);		//0x01 mute=on ，0x00 mute=off 

	sendBuffer[37] = 0x00;	//u16 ChkSum;校验和
	sendBuffer[38] = 0x00;	
	
	int requestSize = 39;	//发送command命令的总长度
	//int resultLengthS = 38;  //成功response,数据的总字节数
	//int resultLengthF = 8;  //失败response,数据的总字节数

	WDCP600LOG( m_ip + "*DCP600_SetMute" );

	//Set Mute State
	int nCmd_SetMuteLen = requestSize;

#ifdef _DEBUG_
	printf("\nSend SetMute Data Length:%d\n\n" , nCmd_SetMuteLen );
#endif

	result = SendAndRecv( sendBuffer , nCmd_SetMuteLen , recvBuffer , rRecvDataLength );
	if ( result != 0 )
	{
		Close();
		m_bConnected = 0;

		WDCP600LOG(m_ip+"*DCP600_SetMute_Fail!");

		return AD600TT(ERROR_AUDIO_DCP_600_UDPTRANSPORTFAILED);
	}

#ifdef _DEBUG_
	printf( "\nRecv SetMute Data Length:%d\n\n" , rRecvDataLength );
#endif

	int iSuccess(0);
	char buffer[BUFFERLENGTH]="";
	strcpy( buffer , "CtlOK!" );
	if( strncmp( recvBuffer , buffer , strlen( buffer ) ) != 0 )
	{
		iSuccess = 0;
	}
	else
	{
		iSuccess = 1;
	}

	if ( iSuccess == 1 )
	{
		m_bConnected = 1;
		printf("SetMute() Successed!\n");

		WDCP600LOG(m_ip+"*DCP600_SetMute_Success!");

		return 0;
	}
	else
	{
		Close();
		m_bConnected = 0;

		WDCP600LOG(m_ip+"*DCP600_SetMute_Fail!");

		printf("\n SetMuteState Failed!\n\n");

		return AD600TT(ERROR_AUDIO_DCP_600_OPERATORFAILED);
	}

	return 0;
}

int C_AudioDCP600::SetChanel( const string &chanel )
{
	WDCP600LOG(m_ip+"*DCP600_SetChanel");
	for(size_t i=0; i<m_chanelList.size(); i++)
	{
		if(m_chanelList[i] == chanel)
		{
			int result = SetChanel(i);
			if ( result != 0 )
			{
				WDCP600LOG(m_ip+"*DCP600_SetChanel_Fail!");
				return result;
			}

			WDCP600LOG(m_ip+"*DCP600_SetChanel_Success!");
			return 0;
		}
	}

	WDCP600LOG(m_ip+"*DCP600_SetChanel_Fail!");

	return AD600TT(ERROR_AUDIO_DCP_600_OPERATORFAILED);
}

//设置通道号 0-3,共4个
int C_AudioDCP600::SetChanel(int chanel)  
{
	if(chanel == GAMECHANNEL) chanel = 3;//duheqing 2016-03-25

	if( chanel < 0 || chanel > (int)(m_chanelList.size()-1) )
		return AD600TT(ERROR_AUDIO_DCP_600_PARAMETERERROR);

	int result = 0;

	WDCP600LOG(m_ip+"*DCP600_SetChanel");

	result = SetChanel_type( chanel );
	if ( result != 0 )
	{
		m_bConnected = 0;
		Close();

		WDCP600LOG(m_ip+"*DCP600_SetChanel_Fail!");
		return AD600TT(ERROR_AUDIO_DCP_600_OPERATORFAILED);
	}
	else
	{
		m_bConnected = 1;

		m_CurChannelNum = chanel;

		WDCP600LOG(m_ip+"*DCP600_SetChanel_Success!");
		return 0;
	}
}
//被SetChanel函数调用  SetChanel()--->SetChanel_type()
int C_AudioDCP600::SetChanel_type(int type)
{
	int result = 0;
	int rRecvDataLength = 0;
	char sendBuffer[BUFFERLENGTH];
	char recvBuffer[BUFFERLENGTH];
	memset(sendBuffer, 0, BUFFERLENGTH);
	memset(recvBuffer, 0, BUFFERLENGTH);

	sendBuffer[0] = 0x53;	//DCP600 控制命令以 “SetPara”  +  “DCP600ConfigData” 为前导识别验证字 
	sendBuffer[1] = 0x65;
	sendBuffer[2] = 0x74;
	sendBuffer[3] = 0x50;
	sendBuffer[4] = 0x61;
	sendBuffer[5] = 0x72;
	sendBuffer[6] = 0x61;
	sendBuffer[7] = 0x00;
	sendBuffer[8] = 0x00;
	sendBuffer[9] = 0x00;
	sendBuffer[10] = 0x44;	//DCP600
	sendBuffer[11] = 0x43;
	sendBuffer[12] = 0x50;
	sendBuffer[13] = 0x36;  //0x36 => '6'
	sendBuffer[14] = 0x30;	//0x30 => '0'
	sendBuffer[15] = 0x30;  //0x30 => '0'
	sendBuffer[16] = 0x43;
	sendBuffer[17] = 0x6f;
	sendBuffer[18] = 0x6e;
	sendBuffer[19] = 0x66;
	sendBuffer[20] = 0x69;
	sendBuffer[21] = 0x67;
	sendBuffer[22] = 0x44;
	sendBuffer[23] = 0x61;
	sendBuffer[24] = 0x74;
	sendBuffer[25] = 0x61;
	sendBuffer[26] = 0x00;
	sendBuffer[27] = 0x00;
	sendBuffer[28] = 0x00;
	sendBuffer[29] = 0x00;

	sendBuffer[30] = 0xca;	//StartByte = 0xca;
	sendBuffer[31] = 0x06;	//CmdType = 0x06;
	sendBuffer[32] = 0x36;	//ParaStaAdd =0x36 03 
	sendBuffer[33] = 0x03;
	sendBuffer[34] = 0x03;	//ParaNum = 1;0x03 00
	sendBuffer[35] = 0x00;
	//3个参数
	sendBuffer[36] = (char)type;		//索引从0开始，0--3，共4个
	sendBuffer[37] = 0x00;
	sendBuffer[38] = 0x00;	

	sendBuffer[39] = 0x00;	//u16 ChkSum;校验和
	sendBuffer[40] = 0x00;	

	int requestSize = 41;	//发送command命令的总长度
	//int resultLengthS = 38;  //成功response,数据的总字节数

	//SetChanelState
	int nCmd_SetChanelLen = requestSize;

#ifdef _DEBUG_
	printf("\nSend SetChanelState Data Length:%d\n\n" , nCmd_SetChanelLen );
#endif

	result = SendAndRecv( sendBuffer , nCmd_SetChanelLen , recvBuffer , rRecvDataLength );
	if(result != 0)
		return result;

#ifdef _DEBUG_
	printf( "\nRecv SetChanelState Data Length:%d\n\n" , rRecvDataLength );
#endif
	
	int iSuccess(0);
	char buffer[BUFFERLENGTH]="";
	strcpy( buffer , "CtlOK!" );
	if( strncmp( recvBuffer , buffer , strlen( buffer ) ) != 0 )
	{
		iSuccess = 0;
	}
	else
	{
		iSuccess = 1;
	}

	if ( iSuccess == 1 )
	{

#ifdef _DEBUG_
		printf("SetChanel() Successed!\n");
#endif

		return 0;
	}
	else
	{

#ifdef _DEBUG_
		printf("\n SetChanelType Failed!\n" );
#endif

		return -1;
	}

	return 0;
}

//GetChanel()、GetVolume()函数，内部用于测试，不对外调用
//取出通道号
int C_AudioDCP600::GetChanel(int &chanel)
{
    int mute = 0;
    int volume = 0;
	int result = 0;
    result = GetAll( volume , mute , chanel );
    return result;
}

//设置音量 0-100，内部使用0-100，对应面板上的0 - 10.0,每个通道是独立控制的。
int C_AudioDCP600::SetValue(int iValue)
{
    if( iValue > 100 || iValue < 0 )
		return AD600TT(ERROR_AUDIO_DCP_600_PARAMETERERROR);

    int result = 0;

    WDCP600LOG(m_ip+"*DCP600_SetValue");

	if( m_IsLoadFunc_GetAudioStatus == 0 )
	{
		//调用GetAudioStatus
		int iValue = 0 , iMute = 0 , iChannel = 0;
		vector<string> vChannelList;
		result = GetAudioStatus( iValue , iMute , iChannel , vChannelList );
	}

    if( result == 0 )
	{
        result = SetVolume( iValue );
		if( result == 0 )
		{
			m_bConnected = 1;
			m_IsLoadFunc_GetAudioStatus = 0;
			//更新数组 m_Channel_VolList
			if ( m_CurChannelNum == 0 )
			{
				m_Channel_VolList[0] = (char)iValue;
			} 
			else if( m_CurChannelNum == 1 )
			{
				m_Channel_VolList[1] = (char)iValue;
			}
			else if( m_CurChannelNum == 2 )
			{
				m_Channel_VolList[2] = (char)iValue;
			}
			else if( m_CurChannelNum == 3 )
			{
				m_Channel_VolList[3] = (char)iValue;
			}

			WDCP600LOG(m_ip+"*DCP600_SetValue_Success!");
			return 0;
		}
		else
		{
	        m_bConnected = 0;
            Close();
	        WDCP600LOG(m_ip+"*DCP600_SetValue_Fail!");
			return AD600TT(ERROR_AUDIO_DCP_600_OPERATORFAILED)
		}
	}
	else
	{
	    WDCP600LOG(m_ip+"*DCP600_SetValue_Fail!");
		return AD600TT(ERROR_AUDIO_DCP_600_OPERATORFAILED);
	}
}
//被SetValue函数调用  SetValue()--->SetVolume()
int C_AudioDCP600::SetVolume( int volume )
{
	int result = 0;
	int rRecvDataLength = 0;
	char sendBuffer[BUFFERLENGTH];
	char recvBuffer[BUFFERLENGTH];
	memset(sendBuffer, 0, BUFFERLENGTH);
	memset(recvBuffer, 0, BUFFERLENGTH);

	sendBuffer[0] = 0x53;	//DCP600 控制命令以 “SetPara”  +  “DCP600ConfigData” 为前导识别验证字 
	sendBuffer[1] = 0x65;
	sendBuffer[2] = 0x74;
	sendBuffer[3] = 0x50;
	sendBuffer[4] = 0x61;
	sendBuffer[5] = 0x72;
	sendBuffer[6] = 0x61;
	sendBuffer[7] = 0x00;
	sendBuffer[8] = 0x00;
	sendBuffer[9] = 0x00;
	sendBuffer[10] = 0x44;	//DCP600
	sendBuffer[11] = 0x43;
	sendBuffer[12] = 0x50;
	sendBuffer[13] = 0x36;  //0x36 => '6'
	sendBuffer[14] = 0x30;	//0x30 => '0'
	sendBuffer[15] = 0x30;  //0x30 => '0'
	sendBuffer[16] = 0x43;
	sendBuffer[17] = 0x6f;
	sendBuffer[18] = 0x6e;
	sendBuffer[19] = 0x66;
	sendBuffer[20] = 0x69;
	sendBuffer[21] = 0x67;
	sendBuffer[22] = 0x44;
	sendBuffer[23] = 0x61;
	sendBuffer[24] = 0x74;
	sendBuffer[25] = 0x61;
	sendBuffer[26] = 0x00;
	sendBuffer[27] = 0x00;
	sendBuffer[28] = 0x00;
	sendBuffer[29] = 0x00;

	sendBuffer[30] = 0xca;	//StartByte = 0xca;
	sendBuffer[31] = 0x06;	//CmdType = 0x06;
	sendBuffer[32] = 0x39;	//ParaStaAdd =0x39 03 
	sendBuffer[33] = 0x03;
	sendBuffer[34] = 0x08;	//ParaNum = 1;0x08 00
	sendBuffer[35] = 0x00;
	//8个参数
	sendBuffer[36] = 0x46;	//ch=00(通道0)的vol值
	sendBuffer[37] = 0x46;	//ch=01(通道1)的vol值
	sendBuffer[38] = 0x46;	//ch=02(通道2)的vol值	
	sendBuffer[39] = 0x46;	//ch=03(通道3)的vol值
	sendBuffer[40] = 0x46;
	sendBuffer[41] = 0x46;
	sendBuffer[42] = 0x46;
	sendBuffer[43] = 0x46;
	if( m_CurChannelNum == 0 )
	{
		sendBuffer[36] = (char)volume;			//ch=00(通道0)的vol值
		sendBuffer[37] = m_Channel_VolList[1];	//ch=01(通道1)的vol值
		sendBuffer[38] = m_Channel_VolList[2];	//ch=02(通道2)的vol值	
		sendBuffer[39] = m_Channel_VolList[3];	//ch=03(通道3)的vol值
		sendBuffer[40] = m_Channel_VolList[4];
		sendBuffer[41] = m_Channel_VolList[5];
		sendBuffer[42] = m_Channel_VolList[6];	
		sendBuffer[43] = m_Channel_VolList[7];
	}
	else if ( m_CurChannelNum == 1 )
	{
		sendBuffer[36] = m_Channel_VolList[0];	//ch=00(通道0)的vol值
		sendBuffer[37] = (char)volume;			//ch=01(通道1)的vol值
		sendBuffer[38] = m_Channel_VolList[2];	//ch=02(通道2)的vol值	
		sendBuffer[39] = m_Channel_VolList[3];	//ch=03(通道3)的vol值
		sendBuffer[40] = m_Channel_VolList[4];
		sendBuffer[41] = m_Channel_VolList[5];
		sendBuffer[42] = m_Channel_VolList[6];
		sendBuffer[43] = m_Channel_VolList[7];		
	}
	else if ( m_CurChannelNum == 2 )
	{
		sendBuffer[36] = m_Channel_VolList[0];	//ch=00(通道0)的vol值
		sendBuffer[37] = m_Channel_VolList[1];	//ch=01(通道1)的vol值
		sendBuffer[38] = (char)volume;			//ch=02(通道2)的vol值	
		sendBuffer[39] = m_Channel_VolList[3];	//ch=03(通道3)的vol值
		sendBuffer[40] = m_Channel_VolList[4];
		sendBuffer[41] = m_Channel_VolList[5];
		sendBuffer[42] = m_Channel_VolList[6];
		sendBuffer[43] = m_Channel_VolList[7];	
	}
	else if ( m_CurChannelNum == 3 )
	{
		sendBuffer[36] = m_Channel_VolList[0];	//ch=00(通道0)的vol值
		sendBuffer[37] = m_Channel_VolList[1];	//ch=01(通道1)的vol值
		sendBuffer[38] = m_Channel_VolList[2];	//ch=02(通道2)的vol值
		sendBuffer[39] = (char)volume;			//ch=03(通道3)的vol值
		sendBuffer[40] = m_Channel_VolList[4];
		sendBuffer[41] = m_Channel_VolList[5];
		sendBuffer[42] = m_Channel_VolList[6];
		sendBuffer[43] = m_Channel_VolList[7];	
	}
	

	sendBuffer[44] = 0x00;	//u16 ChkSum;校验和
	sendBuffer[45] = 0x00;	

	int requestSize = 46;	//发送command命令的总长度
	//int resultLengthS = 38;  //成功response,数据的总字节数

	//SetVolumeState
	int nCmd_SetVolumeLen = 0;

	nCmd_SetVolumeLen = requestSize;

#ifdef _DEBUG_
	printf("\nSend SetVolumeState Data Length:%d\n\n" , nCmd_SetVolumeLen );
#endif

	result = SendAndRecv( sendBuffer , nCmd_SetVolumeLen , recvBuffer , rRecvDataLength );
	if(result != 0)
		return result;

#ifdef _DEBUG_
	printf( "\nRecv SetVolumeState Data Length:%d\n\n" , rRecvDataLength );
#endif

	int iSuccess(0);
	char buffer[BUFFERLENGTH]="";
	strcpy( buffer , "CtlOK!" );
	if( strncmp( recvBuffer , buffer , strlen( buffer ) ) != 0 )
	{
		iSuccess = 0;
	}
	else
	{
		iSuccess = 1;
	}

	if ( iSuccess == 1 )
	{
#ifdef _DEBUG_
		printf("SetVolume() Successed!\n");
#endif
		return 0;
	}
	else
	{
#ifdef _DEBUG_
		printf("\n SetVolume Failed!\n" );
#endif
		return -1;
	}

	return 0;
}

//GetChanel()、GetVolume()函数，内部用于测试，不对外调用
//取出音量
int C_AudioDCP600::GetVolume(int &volume)
{
    int mute = 0;
    int channel = 0;
	int result = 0;
    result = GetAll( volume , mute , channel );
    return result;
}

int C_AudioDCP600::SendAndRecv( const  char *sendBuffer, int size,  char *recvBuffer, 
								    int& rRecvDataLength )
{
	int result = -1;
	int recvlen = 0;
	int iSendedLen = 0;

	udp::UdpTransport udp;

	result = udp.Create( m_ip.c_str() , m_port );
	if ( result != 0 )
	{
		return result;
	}

	result = udp.UdpSend( sendBuffer , size );
	if( result > 0 )
	{
		iSendedLen = result;
	}

	if( ( result <= 0 ) || ( size != iSendedLen ))
	{
		printf( "C_AudioDCP600 [ERROR] \" SendAndRecv \" send failed(%d):Len=%d,sendlen=%d\n" , result , size , iSendedLen );

		m_bConnected = 0;
		Close();

		udp.Close();

		if( result <= 0  )
			return result;
	}

#ifdef _DEBUG_
	printf( "AudioDCP600---Send Data length :%d---\n" , iSendedLen );
#endif

#ifdef _DEBUG_
	printf("[---C_AudioDCP600 Send cmd---] :\n");	
	int i = 0;
	for(i = 0; i < iSendedLen; i++)
		printf("%02X ", sendBuffer[i]);
	printf("\n");
#endif

#ifdef _DEBUG_
	printf("AudioDCP600 [INFO]  \" SendAndRecv \" send succeed(%d)!\n", result);
#endif


	//接收Command 的响应消息
	result = -1;
	recvlen = 0;
	result = udp.UdpRecv( recvBuffer,  BUFFERLENGTH );
	if( result > 0 )
	{
		recvlen = result;
	}

	if( result > 0 )  //SOCKET_SUCCEES			
	{
		rRecvDataLength += recvlen;

#ifdef _DEBUG_
		printf("[---AudioDCP600 Recv Data---] :\n");
		for(i = 0; i < recvlen; i++)
			printf("%02X ", recvBuffer[i]);
		printf("\n");
		
		printf("AudioDCP600 [INFO]  \" SendAndRecv \" recv data succeed(%d)!\n", result);
#endif

		WDCP600LOG( m_ip + "*AudioDCP600_Recv Data succeed!" );
	}
	else
	{
		udp.Close();

		Close();
		m_bConnected = 0;

#ifdef _DEBUG_
		printf( "AudioDCP600 [Error] Udp Recv Data [Return Code]:%d!\n\n" , result );
#endif

		WDCP600LOG( m_ip + "*AudioDCP600_Recv Failed:Payload Data error!" );
		
		if( result <= 0 )
			return result;
	}
	
#ifdef _DEBUG_
	printf( "AudioDCP600---Recv Data length :%d---\n" , recvlen );
#endif

	udp.Close();
	m_bConnected = 1;

	return 0;
}


int C_AudioDCP600::SetValueAndMute(int iValue,int iMute)
{
	return -1;
}

int C_AudioDCP600::GetMuteRet( const char *info , int &mute , int Length )
{
	if ( nDcp600_Offset_MuteState > Length )
	{
		return ERROR_AUDIO_DCP_600_OPERATORFAILED;
	}
	
	mute = info[nDcp600_Offset_MuteState] == 0x01 ? 1 : 0;
	return 0;
}

int C_AudioDCP600::GetVolumeRet( const char *info , int Length )
{
	if ( nDcp600_Offset_Vol_Ch00 > Length )
	{
		return ERROR_AUDIO_DCP_600_OPERATORFAILED;
	}

	memcpy( m_Channel_VolList , &info[nDcp600_Offset_Vol_Ch00] , 8 );
	return 0;
}

int C_AudioDCP600::GetChanelType( char *info , int &type , int Length )
{
	if ( nDcp600_Offset_ChannelState > Length )
	{
		return ERROR_AUDIO_DCP_600_OPERATORFAILED;
	}

	type = 0;
	type = info[nDcp600_Offset_ChannelState];
	return 0;
}


#if defined(TMS2_AUDIO_ERRCODE) || defined(WRITE_DCP600ELOG) 
#ifndef TMS20_LOG
#include "C_LogManage.h"
#endif
#endif

#ifdef WRITE_DCP600ELOG
int Dcp600_WriteErrorLog( const string& strError )
{
	int ret = 0;
	int iLevel=1, iModule=22, iSubModule=2;
	int errorCode = 0;
	ret = C_LogManage::GetInstance()->WriteLog( iLevel,  iModule, iSubModule, errorCode, strError);
	return ret;
}
#endif // WRITE_DCP600ELOG

#ifdef TMS2_AUDIO_ERRCODE
//错误码区分：DCP600 使用 2301- 2400
int Dcp600ErrorCodeToTmsErrorCode(int error)
{
	const int nDcp600_ErrorLevel = 3;
	const int nDcp600_Module = 22;
	const int nDcp600_SubModule = 2;
	const int nDcp600_ERROR_Code_Base_Value = 2000;
	if(error == 0)
		return 0;
	else if(error < 0xFFFF)
		return C_LogManage::GetInstance()->CreateLogNumber(nDcp600_ErrorLevel, nDcp600_Module, nDcp600_SubModule, nDcp600_ERROR_Code_Base_Value + abs(error));
	else
		return error;
}
#endif // TMS2_AUDIO_ERRCODE

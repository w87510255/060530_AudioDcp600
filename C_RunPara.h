//@file:C_RunPara.h
//@brief: ������C_RunPara��
//C_RunPara:����ϵͳ����ʱ����Ҫ������ ��ȡ/���á�
//Ŀǰ����ϵͳʱ�ӵķ�װ����ȡ���������ڵ�·�����ܡ������������ݺ����Ŀ�����Ҫ��ӡ�
//@author:wangzhongping@oristartech.com
//dade:2012-07-12



#ifndef TMS20_RUN_PARA
#define TMS20_RUN_PARA
#include <sys/time.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "C_constDef.h"
class C_RunPara
{
public:
				~C_RunPara();
				static C_RunPara* GetInstance();
				//��ʼ��ʱ�䣬����ʼ����ʱ�����̵߳��á�
				void Init();
        //���߳�ͨ�����ô˷�������ȡϵͳʱ�䣬ͬʱ��ϵͳʱ���ݴ���m_CurTV��
        //���̶߳�ʱ���ô˷�������ϵͳʱ�䡣
        //ͬʱ�����Ե���0��Ϊ��׼�ĺ�������
        //bDateStartָʾ��ǰʱ���Ƿ���0�㡣1����ǰʱ��Ϊ0�㣬0����0�㡣
        int GetCurMillisecond(int &bDateStart);
        //���ܣ���ȡϵͳ��ʱ�䡣
        //���أ�һ��Ϊ��λ��ϵͳʱ�䡣
        int GetCurTime()
        {
             return (int) m_CurTV.tv_sec;
        }
        //���ܣ���ȡϵͳ�ĵ�ǰʱ�䡣
        //���أ�0:�ɹ�������Ϊ�����롣
        //������strCurTime  [out] ���ص�ǰ��ϵͳʱ���ַ�����ʽ �磺2012-07-15 14:54:30
        int GetCurTime(std::string &strCurTime);
        //���ܣ���ȡϵͳ�ĵ�ǰ���ڡ�
        //���أ�0:�ɹ�������Ϊ�����롣
        //������strDate  [out] ���ص�ǰ��ϵͳ�����ַ�����ʽ �磺2012-07-15
        int GetCurDate(std::string &strDate);
        int GetZeroTime();
        //��ȡ ���������ڵ�·����
        int GetExePath(std::string &strExePath);
        //��ȡ�洢���ڵ�·����
        int GetSavePath(std::string &strPath);
        //��ȡ����·����
        int GetMountPath(std::string &strPath);
        int GetFtpUrL(std::string &strFtpUrl);
        int GetFtpKdmUrl(std::string &strFtpUrl);
        int GetKdmPath(std::string &strKdmPath);
        int GetDispatchCount(int &iDispatchCount);
		
		int GetLocalKdmPath(std::string &strLocal_kdm_path);

        int GetDcsPlayOffset(std::string &strDeviceModel, int &iMillisecond);
        int GetTMSDiskSizeAlarm(int &iDiskSizeAlarm);
        int GetDCSDiskSizeAlarm(int &iDiskSizeAlarm);
        int GetFinishDeleteMinute(int &iMinute);
				int SumAllFileSize(const char *pathname, unsigned long long& rSize);
				//wzp add 2014-2-13
				//ת�������ַ�����ʽ��
				int ZhGbkToUtf(std::string &info);
				//wzp add end;


		//@author zhangmiao@oristartech.com
		//@date 2012-09-13 
		//@brief ��ȡ���̿ռ�Ȳ����������ܿռ䡢���пռ䡢���пռ���ռ�İٷֱȡ�
		//@new
		int DH_GetDiskSpace(const char *pDisk, unsigned int& rFreespace , unsigned int & rTotalspace , float& rFreeSpacePercent );
		//@modify end;
                
		//duheqing 2012-11-2
    //���� -2 ��ʾ������Ʊ�����ڡ�����0 Ϊ����Ʊ��ϵͳ���ڡ�����Ϊ�����롣
		int GetCinemaIpPort(std::string &ip, unsigned short &port, std::string &cinemaId);//tickets
    //���� -2 ��ʾ�����ܹ��ƻ�������0 Ϊ���ܹ��ƻ�������Ϊ�����롣
		int GetShopIpPort(std::string &ip, unsigned short &port, std::string &cinemaId);//advertise a
		int GetPeerIpPort(std::string &ip, unsigned short &port);//advertise dcp

//@author zhangmiao@oristartech.com
//@date [2012-12-03]
//@brief ��� C++ ���ò�����ȡ��
//@new
		int GetDebugLevel( int& nDebugLevel );
		int GetHall_disk_alarm( int& nHall_disk_alarm );

		int GetAdver_ip( std::string& strAdver_ip );
		int GetAdver_port( unsigned short& nAdver_port );
		int GetAdver_update_period( int& nAdver_update_period );
		int GetDcp_alarm( int& nDcp_alarm );
		int GetDcp_fault_alarm( int& nDcp_fault_alarm );
		int GetKdm_alarm( int& nKdm_alarm );
		int GetKdm_fault_alarm( int& nKdm_fault_alarm );
		int GetKdm_end_alarm( int& nKdm_end_alarm );
		int GetShow_alarm( int& nShow_alarm );
		int GetShow_fault_alarm( int& nShow_fault_alarm );
		int GetCent_adver( int& nCent_adver );
		int GetTicket_show( int& nTicket_show );
		int GetShow_sync_way( int& nShow_sync_way );
		int GetTicket_show_ip( std::string& strTicket_show_ip );
		int GetTicket_show_port( unsigned short& nTicket_show_port );
		int TranslateGbkToUtf8(std::string &strGbk, std::string &strUtf8);
//@modify end;

		//wzp add on 2014-1-6
		int GetCuePlayCheckDelay(int &iCuePlayCheckDelay);
		//wzp add
		//wzp add on 2014-4-8
		int GetOpenLampFlag(int &bOpenLampFlag);
		int GetDefaultAudioLevel(int &iAudioLevel);
		int GetSwichtAudioChannel(int &bSwitchAudioChannel);
		int GetCloseLampFlag(int &bCloseLamp);
		int GetColorSpace(int &iColorSpace);
		void CreateUuid(std::string &strUuid);
		//wzp end

//@author zhangmiao@oristartech.com
//@date [2013-09-02]
//@brief ��� C++ ���ò�����ȡ��
//@new
		int GetTms_version( std::string& strTms_version );
		int GetDB_version( std::string& strDB_version );
		int GetPhp_version( std::string& strPhp_version );
//@modify end;

//@author zhangmiao@oristartech.com
//@date [2013-11-13]
//@brief ��� C++ ���ò�����ȡ��
//@new
//���Satellite�����豸�� IP and Port
		int GetSateDeviceIpPort(std::string &ip, unsigned short &port);
//@modify end;

//20140220 by xiaozhengxiu add
	int GetTmsCenterUrl(std::string &strTmsCenterUrl);

private:
				//����ʵ��ָ�롣
				static C_RunPara *m_pInstance;
				//ÿ��0���Ӧ��ʱ�䣬����ơ�
				int m_iZeroTime;
				//��ǰʱ��ṹ
        struct timeval m_CurTV; 
        //��ǰ����  �磺2012-07-15
        std::string m_strCurDate;
        // �Ƿ���������0��ʱ��ֵ��
        int m_bSettingTime;
        //C++ ���������ڵ�·����
        std::string m_strExePath;
        	
        	
        //Ƭ��·����
        std::string m_strSavePath;		//*
        //�ƶ�Ӳ�̵Ĺ���·����
        std::string m_strMountPath;		//*
         // ��Կ·�� kdm��Ƭ��·����
        std::string m_strKdmPath;		//*
		//kdmϵͳ�ϴ�·��local_kdm_path
		std::string m_local_kdm_path;	//*

        //���̿ռ䱨������ 
        int m_iTMSDiskSizeAlarm;
        int m_iDCSDiskSizeAlarm;
        //int m_iDiskPercent; 
        //���롢�ַ�������ɺ�ɾ��ʱ�䣨�֣� 
        int m_iFinishDeleteMinute;		//*
        //dcp ��tms��ftp����dcpʱ�õ���ftp url��        
        std::string m_strFtpUrl; 
        //dcp ��tms��ftp����kdmʱ�õ���ftp url��
        std::string m_strFTpKdmUrl; 
        // TMS ͬʱ�ַ�DCP�ĸ�����
				int m_iDispatchCount;
        
        int m_iFieldLampChannel;
        int m_iSkirtingLampChannel;
        int m_iCleanLampChannel;
        int m_iAq10PlayOffset;
        int m_iGdc3dPlayOffset;
        int m_iDolbyPlayOffset; 

//@author zhangmiao@oristartech.com
//@date [2012-12-03]
//@brief ��� C++ ���ò�����ȡ��
//@new
		//debug ����(0:����1:��ʾ2:����3:����)  ����ʱ��һ�� 
		int m_nDebugLevel;
		//hall_disk_alarm	190	Ӱ�����̿ռ䱨��  ����ʱ��һ�� 
		int m_nHall_disk_alarm;
		//���Ĺ��ip��ַÿ�ε���ʱ��ȡ 
		std::string m_strAdver_ip;
		//adver_port	809	���Ĺ���ַ�˿ں�ÿ�ε���ʱ��ȡ unsigned short
		unsigned short m_nAdver_port;
		//adver_update_period	49	���Ĺ���������ÿ�ε���ʱ��ȡ 
		int m_nAdver_update_period;
		//dcp_alarm	 dcpδ׼����Ԥ��ʱ��   ÿ�ε���ʱ��ȡ int
		int m_nDcp_alarm;
		//dcp_fault_alarm	dcpδ׼���ù���ʱ��  ÿ�ε���ʱ��ȡ int
		int m_nDcp_fault_alarm;
		//kdm_alarm	1	kdmδ׼����Ԥ��ʱ��  ÿ�ε���ʱ��ȡ int
		int m_nKdm_alarm;
		//kdm_fault_alarm	1	dcpδ׼���ù���ʱ�� ÿ�ε���ʱ��ȡ int
		int m_nKdm_fault_alarm;
		//kdm_end_alarm	1	KDM��������Ԥ��ʱ��ÿ�ε���ʱ��ȡ int
		int m_nKdm_end_alarm;
		//show_alarm	2	����δ׼����Ԥ��ʱ�� ÿ�ε���ʱ��ȡ int
		int m_nShow_alarm;
		//show_fault_alarm	1	dcpδ׼���ù���ʱ�� ÿ�ε���ʱ��ȡ int
		int m_nShow_fault_alarm;
		//cent_adver	1	�Ƿ�������Ĺ�棨0��������1�����ܣ�ÿ�ε���ʱ��ȡ int
		int m_nCent_adver;
		//ticket_show	0	�Ƿ����Ʊ�����ڣ�0��������1�����ܣ�ÿ�ε���ʱ��ȡ int
		int m_nTicket_show;
		//show_sync_way	2	����ͬ����ʽ   ÿ�ε���ʱ��ȡ int
		int m_nShow_sync_way;
		//ticket_show_ip		Ʊ��ϵͳ����ipÿ�ε���ʱ��ȡ string
		std::string m_strTicket_show_ip;
		//ticket_show_port		Ʊ��ϵͳ���ڵ�ַ�˿�ÿ�ε���ʱ��ȡ unsigned short
		unsigned short m_nTicket_show_port;
		//wzp add on 2014-1-6
		//������Ԥ�ƿ�ʼ��ʱ�����m_iCuePlayCheckDelay ��Է�ӳ�������Ƿ񲥷�
		//���м�⡣
		int m_iCuePlayCheckDelay;
		//wzp add
//@modify end;

        //tmsCenter���Ķ�url��        
		std::string m_strTmsCenterUrl; //20140220 by xiaozhengxiu add

protected:
				C_RunPara();
};

//@author zhangmiao@oristartech.com
//@date [2012-12-03]
//@brief ��� C++ ���ò�����ȡ��
//@new
int ReadTmsDBData4Str( const std::string& sFieldName , std::string& retValue );
int ReadTmsDBData4Int( const std::string& sFieldName , int& retValue );
//@modify end;

#endif //TMS20_RUN_PARA

//@file:C_constDef.h
//@brief: ��������״̬��Ϣ���塣
//@author:wangzhongping@oristartech.com
//dade:2012-07-12

#ifndef TMS20_CONST_DEFINE
#define TMS20_CONST_DEFINE
#include "C_CS.h"
#include <vector>
#include <string>
//�߳�״̬��
enum Thread_State
{
	INIT_STATE = 0, //��ʼ
	RUN_STATE = 1,  //����
	SUSPEND_IDL_STATE = 2, //����
	SUSPEND_FINISH_STATE = 3,//����ִ����ɶ���ͣ��
	RUN_LOCKED_STATE = 4,  // ����ʱ������
	SUSPEND_LOCKED_STATE = 5 // ��ͣʱ������
};
//�߳��������ͣ����������߳�ִ�в��������͡�
enum Thread_Run_Type
{
	RUN_WEBSERVICE_TYPE = 0, //�߳�����ִ��Webservice���á�
	RUN_TIMETASK_TYPE = 1, // �߳�����ִ�ж�ʱ����
	RUN_UNKNOWN_TYPE = 2 // �߳�δִ�в�����
};
 //����״̬��
enum TASK_STATE
{
	//����
	TASK_IDLE_STATE = 0,
	// ����δ��ʼִ��
	TASK_NO_STATE =1,
	// ��������ִ�С�
	TASK_RUNNING_STATE = 2,
	// ����ִ����ɡ�
	TASK_FINISH_STATE  = 3,
	// ������Ҫ��ɾ��
	TASK_DELETE_STATE  = 4,
	//����ʱ������
	TASK_LOCKED_STATE  = 5
};
//�豸����״̬
enum DEVICE_OPERATE_STATE
{
	//����
	DEVICE_OPERATE_STATE_IDLE = 0,
	//�������豸����ͨ��,���ò�����
	DEVICE_OPERATE_STATE_RUN = 1,
	//�������豸����ͨ�ţ���ȡ������
	DEVICE_OPERATE_STATE_READ = 2,	
	//CUEִ��ǰ�����豸
	DEVICE_OPERATE_STATE_PRE_CUE = 3,
};

enum DEVICE_TYPE
{
	DEVICE_TYPE_UNKNOWN = 0,
	DEVICE_TYPE_PROJECTOR = 1,
	DEVICE_TYPE_AUDIO = 2,
	DEVICE_TYPE_DCS = 3,
	DEVICE_TYPE_POWER = 4,
	DEVICE_TYPE_PROJECTOR2 = 5,	
	//Ӱ����ȫ���豸��
	DEVICE_TYPE_HALL = 6
//	DEVICE_TYPE_HALL = 5
};
//Ӱ��״̬��
enum HALL_STATE
{
	//Ӱ���ڽ���״̬���������á�ɾ���������豸��
	HALL_STATE_UNENABLE = 0x0,
	//Ӱ��������״̬��������ֲ�����
	HALL_STATE_ENABLE = 0x1,
	//Ӱ�����ڱ�ɾ����˲��״̬���������κβ�����
	HALL_STATE_DELETING = 0x4,
	//Ӱ���������ڳ�ʼ����˲��״̬���������κβ�����
	HALL_STATE_INITING = 0x8
};
//�豸״̬,
enum DEVICE_STATE
{
	//Ӱ���ڽ���״̬���������á�ɾ���������豸��
	DEVICE_STATE_UNENABLE = 0x0,
	//Ӱ��������״̬��������ֲ�����
	DEVICE_STATE_ENABLE = 0x1,
	//Ӱ�����ڱ�ɾ����˲��״̬���������κβ�����
	DEVICE_STATE_DELETING = 0x4,
	//Ӱ���������ڳ�ʼ����˲��״̬���������κβ�����
	DEVICE_STATE_INITING = 0x8
};

enum CONTENT_STATE
{
	CONTENT_STATE_NO_START = 0,
	CONTENT_STATE_OPERATING = 1,
	CONTENT_STATE_ERROR = 2,
	CONTENT_STATE_FINISH = 3,
	CONTENT_STATE_CANCEL = 4,
	CONTENT_STATE_PAUSE = 5
};

//���ƶ�Ӳ��dcp����ȡ״̬
enum GET_DCP_STATE
{
	GET_DCP_NO_START = 0,
	GET_DCP_GETTING =1,
	GET_DCP_FINISH = 2,
	GET_DCP_FINISH_ERROR = 3
};

enum DCP_DISPATCH_STATE
{
	DCP_DISPATCH_NO_READY = 0,
	DCP_DISPATCH_NO_START = 1,
	DCP_DISPATCH_OPERATING = 2,
	DCP_DISPATCH_PAUSE= 3,
	DCP_DISPATCH_FINISH = 4,
	DCP_DISPATCH_ERROR= 5,
	DCP_DISPATCH_DB_FINISH = 6
};




enum KDM_STATE
{
	//����
	KDM_STATE_NORMAL = 0,
	//��Ч,��ӰԺ���޶�Ӧ��dcs
	KDM_STATE_INVALID = 1,
	//����
	KDM_STATE_TIMEOUT = 2,
	//�Ѿ����ڣ�
	KDM_STATE_EXIST = 3,
	//kdm������ɣ�ֻ������KDM��Ч
	KDM_STATE_IMPORT_FINISH = 4,
	//KDM�������
	KDM_STATE_IMPORT_ERROR = 5,
	//kdm�ַ���� ֻ�� �����Ѿ������kdm��Ч��
	KDM_STATE_DISPATCH_FINISH = 12,
	//KDM �ַ�����
	KDM_STATE_DISPATCH_ERROR = 13
};

enum KDM_IMPORT_TYPE
{
	KDM_IMPORT_TYPE_OUT_DEVICE = 0,
	KDM_IMPORT_TYPE_LOCAL_PATH = 1,
	KDM_IMPORT_TYPE_UNKOWN = 2
};

enum PLAYER_CURRENT_WORK
{
	PLAYER_IS_DOING_NOTHING = 0,
	PLAYER_IS_TRANSFERING_DCP = 1,
	PLAYER_IS_TRANSFERING_KDM = 2,

	PLAYER_IS_CANNOTCONNECT = 10,//duheqing
};

enum PLAYER_PLAY_STATE
{
	PLAYER_IS_IDLE = 0,
	PLAYER_IS_PLAYING,
	PLAYER_IS_PAUSING,
	PLAYER_WAS_STOPPED,
	PLAYER_OTHER_TYPE,
	PLAYER_IS_ERROR,
};

enum POWER_CHANNEL_DEFINE
{
	POWER_CHANNEL_FIELD_LAMP = 0,
	POWER_CHANNEL_SKIRTING_LAMP = 1,
	POWER_CHANNEL_CLEAN_LAMP = 2
};

enum FILM_COLOR_SPACE
{
COLOR_SPACE_UNKNOW = 0, //δ֪
DCDM_XYZ_SCOPE_A_B = 1, //JPEG 20000 ����Ļ
DCDM_XYZ_FLAT_A_B = 2,//JPEG 20000 �ڷ� 
MXFI_SCOPE_A = 3, //���� MPEG2 ����Ļ
MXFI_FLAT_A = 4, //���� MPEG2 �ڷ�
SCOPE_3D = 5, //3D ����Ļ
FLAT_3D = 6 //3d �ڷ�
};

enum CPL_TEMPLATE_TYPE
{
	FILM_PRE = 1, //Ƭǰ����;
	FREE_DEF_AD = 2, //�Զ����档
	CENTER_AD = 3, //���Ĺ�淽����
	TYPE_VI = 4, //����VI
	TYPE_FILM = 5, //��Ƭ
	FILM_AFTER = 6 //Ƭ�������
};
//ӰƬ����(1:��Ƭ2:Ԥ��Ƭ3�����4����ʶ  9������ 10:Ƭǰ���� 11��Ƭ�����)
enum CPL_KIND_TYPE
{
	CPL_KIND_FILM = 1, //��Ƭ
	CPL_KIND_TEASER = 2, //Ԥ��Ƭ
	CPL_KIND_AD = 3,   //���
	CPL_KIND_TRANS = 4,  //��ʶ
	CPK_KIND_CENTER_AD = 8, //���Ĺ��
	CPL_KIND_OTHER = 9,  //����
	CPL_KIND_PRE = 10,  //Ƭǰ����
	CPL_KIND_AFTER = 11 //Ƭ�����
};

enum DCP_EXTEND_IMPORT_TYPE
{
	DCP_EXTEND_TYPE_DEFAULT = 0, // Ĭ�� ��Ƭ�̵���
	//M002
	DCP_EXTEND_TYPE_AD_SYS =1,    // �ӹ��ϵͳ����
	DCP_EXTENT_TYPE_SAT_SYS = 2   // ������ƽ̨����
	//M002
};

//CUE_Define

enum CUE_SCHEDULE_STATE
{
	CUE_SCHEDULE_NO_PLAY = 0,
	CUE_SCHEDULE_PLAYING = 1,
	CUE_SCHEDULE_DELETING = 2,
	CUE_SCHEDULE_DELETED = 3
//	CUE_SCHEDULE_DELETING = 2
};

enum CUE_ITEM_STATE
{
	CUE_ITEM_NO_START = 0,
	CUE_ITM_PAUSE = 1, //��ʱ����
	CUE_ITEM_LOCK_DEVICE = 2,
	CUE_ITEM_OPERATING = 3,
	CUE_ITEM_SUCCESS = 4,
	//�����豸״̬������״̬һ�£�CUEδִ�С�
	CUE_ITEM_NO_RUN = 5,
	//���ڲ��Ź����г������� ����CUEδִ�С�
	CUE_ITEM_NO_RUN_OFFSET = 6, //��ʱ���á�
	CUE_ITEM_ERROR = 7,
	//��Ӧ��CUE�����Ѿ���ɾ����
	CUE_ITEM_DELETED = 8,
	//add on 2013-8-20 wzp �����ֹ���������CUE δִ�С�
	CUE_ITEM_NO_RUN_MANUAL = 9
};

enum DEVICE_CONNECTION_ALAM_STATE
{
	DEVICE_CONNECTION_ALAM_STATE_INIT = 0,
	DEVICE_CONNECTION_ALAM_STATE_NO = 1,
	DEVICE_CONNECTION_ALAM_STATE_YES = 2
};

enum TMS_WORK_STATE
{
	TMS_WORK_STATE_NO_WORKING = 0,
	//���ڵ���KDM
	TMS_WORK_STATE_IMPORTING_KDM = 1,
	//���ڵ���DCP
	TMS_WORK_STATE_IMPORTING_DCP = 2,
	//���ڷַ�DCP
	TMS_WORK_STATE_DISPATCHING_DCP = 3,
	//����ӰƬcue����ִ�У����߼���ִ�С�
	TMS_WORK_STATE_RUN_CUE = 4
};

// DCP ɾ��״̬���塣
enum DCP_DELETE_STATE
{
	//ɾ��dcp��������δ��ʼ��
	DCP_DELETE_NO_START = 0,
	//ɾ�����ڽ����С�
	DCP_DELETE_RUNNING = 1,
	DCP_DELETE_FINISH = 2,
	DCP_DELETE_ERROR = 3
};

enum  CUE_INTERFACE_ITEM_STATE
{
	//cueδ��ʼִ�С�
	CUE_INTERFACE_ITEM_STATE_NO_START = 0,
	//cue����ִ���С�
	CUE_INTERFACE_ITEM_STATE_OPERATING = 1,
	//�����豸״̬������״̬һ�£�CUEδִ�С�
	//CUE_INTERFACE_ITEM_STATE_NO_RUN = 2,
	//cueִ�гɹ�
	CUE_INTERFACE_ITEM_STATE_SUCCESS = 2,
	//cueִ�д���
	CUE_INTERFACE_ITEM_STATE_ERROR = 3
};

// define struct 



//const define
//Ĭ�ϵ���־����
const int DEFAULT_LOG_LEVEL = 0;
//CUE ��ǰ�����豸��ʱ�䡣
const int CUE_PRE_TIME = 5;
 // ��ӳ������ʱ��ͬ���������λ���롣
const int DCS_TIME_SYNC_INTERVAL = 1800;
//const int DCS_TIME_SYNC_INTERVAL = 3600*6;
//��ȡdcs��ǰ����״̬ʱ��������λ���롣
const int DCS_GET_PLAY_STATE_INTERVAL = 90; //60
 //��ȡ��һ������״̬ʱ���� �롣
 const int DCS_GET_SCHEDULES_INTERVAL = 200;
 //��ȡ��ӳ������ ����״̬������ ʱ���� �롣
 const int DCS_GET_STATUS_INTERVAL = 90; //30
 //Ϊ���ƽ̨����������Ĵ��̿ռ��С
 const int DISK_SIZE_FOR_AD_RESERVE = 500*1024;
 //Ƭ�Ᵽ���ռ��С
 const int DISK_RESERVE_SIZE = 20*1024;
 // �̳߳����̵߳ĸ�����
 const int THREAD_COUNT_IN_POOL = 128;


//struct define;
typedef struct DevicePara
{
	std::string brand;
	std::string model;
	int type;
	//����ƫ��ֵ��
	int audioOffset;
	std::string ip;
	unsigned short port;
	std::string userName;
	std::string passwd;
	std::string version;
	int isUse;
	//�豸��ţ�
	std::string DeviceNum;
}DEVICE_PARA, *PDEVICE_PARA;

typedef struct HallPara
{
	std::string hallId;
	std::string name;
	int isUse;
	int iScreenState;
	std::vector<DEVICE_PARA> vecDevice;
}HALL_PARA, *PHALL_PARA;

typedef struct DcpImPortProgress
{
	std::string strPklUuid;
  int         iProgress;
  CONTENT_STATE state;
  std::string  strError;
}DCP_IMPORT_PROGRESS, *PDCP_IMPORT_PROGRESS;

typedef struct DcpDispatchProgress
{
	std::string strHallId;
	std::string strPklUuid;
  int         iProgress;
  DCP_DISPATCH_STATE state;
  std::string  strError;
}DCP_DISPATCH_PROGRESS, *PDCP_DISPATCH_PROGRESS;


/*typedef struct ImportKdm
{
	std::string path;//�����Ǵ����ļ�·����ftp url
	std::string filename;
	std::string kdmUuid;
	std::string hallid;
	std::string cplUuid;
	std::string playerSn;
	std::string startTime;
	std::string endTime;
	KDM_STATE  status;
	int iERROR;
	std::string strError;
}IMPORT_KDM;*/

typedef struct PowerChannel
{
	int iFieldLampChannel; //����ͨ���ţ�
	int iSkirtingLampChannel; //�߽ŵ�ͨ���ţ�
	int iCleanLampChannel; //����ͨ���ţ�
	int iWidthScreenChannel;//����Ļͨ���ţ�
	int iMaskedScreenChannel; //�ڷ�ͨ���ţ�	
}PowerChannel;

//��Ʊ��ϵͳ��ȡ����������м�ṹ��
typedef struct CenterSchedule
{
	FILM_COLOR_SPACE ColorSpace; //ӰƬ��Ӧ��ɫ�ʿռ䣬��films��ȡ��
	std::string strCplUuid;
	int iStartTime;
	std::string strHallId;
	float fDuring; //ӰƬ��cplʱ�� ��cpl_list��ȡ��
	std::string strTitle; //ӰƬ����������; �ɴ�Ʊ��ϵͳ��ȡ��
	std::string strName;  //ӰƬ��Ӣ������;�ɴ����ݿ�õ� dcp_list.title;
}CenterSchedule;

//�ӹ��ϵͳ��ȡ���ƻ���������м�ṹ�еĵ������ṹ��
typedef struct SliceCpl
{
	//����ɫ�ʿռ䣬�����films���л�ȡʧ�ܣ������ΪDCDM_XYZ_SCOPE_A_B
	FILM_COLOR_SPACE ColorSpace;  
	std::string strCplUuid;
	float fDuring; //ӰƬ��cplʱ�� ��cpl_list��ȡ��
	std::vector<std::string> featureUuid;
}SliceCpl;

/*//�ӹ��ϵͳ��ȡ���ƻ���������м�ṹ��
typedef struct SliceList
{
	std::string strSliceUuid;
	std::vector<SliceCpl> sliceCpl;
}SliceList;*/
//CUE �ṹ���塣
typedef struct Cue
{
	int iCueCode; //cue ���� ��Ӧ�����CUE�������͡�
	int iOffset;  //cue �����cpl��ʼ����ƫ��ʱ��ֵ��
	int iValue;  //cue ������ֵ ֻ��������������������Ƶƫ��ֵʱ��Ч��
}Cue;

//�����м�ṹ����Ӧ��Ԫ�ء�
typedef struct ScheduleElement
{
	FILM_COLOR_SPACE ColorSpace;  //ɫ�ʿռ䡣
	CPL_TEMPLATE_TYPE type;     //��cpl ��Ӧsplģ���ģ��Ԫ�ء�
	std::vector<Cue> vecCue;         //��cpl��Ӧ��cue�б�
	std::vector<std::string> featureUuid;//��Ƭ��UUID�б�ָ����Ƭ��������Щ��Ӱ֮ǰ
	std::string cpluuid;
	float fDuring;
 
}ScheduleElement;

//���ڵ��м�ṹ
typedef struct ScheduleSrt
{
	int iStartTime; //���ڵĿ�ʼʱ��
	float fDuring; //���ڵ���ʱ����
	std::string strHallId;
	int iFilmStartTime; //��Ƭ�Ŀ�ʼʱ�䡣
	//ӰƬ����������; �ɴ�Ʊ��ϵͳ��ȡ�� 
	std::string strTitle;
	//ӰƬ��Ӣ������;�ɴ����ݿ�õ� dcp_list.title; 
	std::string strName; 
	std::vector< ScheduleElement> element;
}ScheduleSrt;

//���DCP ���ؽṹ
typedef struct AdDcp
{
	std::string strTitle;
	std::string strPklUuid;
	std::string strFtpUrl;
}AdDcp;

//CUE �ṹ���塣

typedef struct CUE_Device
{
	int iCueCode;
	std::string strDeviceModel;
	int iOperateType;
	int iOffsetValue;
}CUE_Device;
typedef struct CUE_Item
{


	//��Ӧ��CUE_Schedule.strDBUuid
	std::string strScheduleUuid;
	//cue ��ϵͳ�ڵ�ͳһ��š�
	unsigned int uiNumber;
	//cue �豸������Ŷ�Ӧdb ��cue_code;
	int iCueCode;
	// cue ��Ӧ���豸�������� ��ɫ�ʿռ�ͨ���ţ�������Ƶ��������ͨ���š�
	int iOperateType;
	// cue ��ֵ������ֵ��
	int iCueValue;
	//unix ʱ���
	int  iTimeSencode;
	int  iTimeMillisecond;
	CUE_ITEM_STATE  state;
	int iError;
	//cue ��spl�ڵ�ƫ��ʱ��ֵ��
	int iCplOffsetTime;
	int iLockTime;
	int iCplTime;
	int iCplIndex;
private:
	 std::string strError;
	 	std::string strCplUuid;
	 	C_CS m_CS;
	 	C_CS m_CSCpl;
public:		
	void SetError(const char * str)
	{
		m_CS.EnterCS();
		strError = str;
		m_CS.LeaveCS();
	}

//	void SetError(const char * str)
	void SetError(std::string &str)
	{
		m_CS.EnterCS();
		strError = str;
		m_CS.LeaveCS();
	}
	void GetError(std::string &str)
	{
		m_CS.EnterCS();
		str = strError;
		m_CS.LeaveCS();
	}
	
void SetCplId(const char * strCplId)
{
	m_CSCpl.EnterCS();
	strCplUuid = strCplId;
	m_CSCpl.LeaveCS();
}	

void SetCplId(std::string &strCplId)
{
	m_CSCpl.EnterCS();
	strCplUuid = strCplId;
	m_CSCpl.LeaveCS();
}

void GetCplId(std::string &strCplId)
{
	m_CSCpl.EnterCS();
	strCplId = strCplUuid;
	m_CSCpl.LeaveCS();
}
	
	
	CUE_ITEM_STATE SetState(CUE_ITEM_STATE newState)
	{
		CUE_ITEM_STATE oldState;
		m_CS.EnterCS();
		oldState = state;
		if(state == CUE_ITEM_NO_START)
		{
			state = newState;
		}
		m_CS.LeaveCS();
		return oldState;	
	}
	
	CUE_ITEM_STATE SetNoStartState()
	{
		CUE_ITEM_STATE oldState;
		m_CS.EnterCS();
		oldState = state;
		if(state != CUE_ITEM_LOCK_DEVICE && state != CUE_ITEM_OPERATING)
		{
			state = CUE_ITEM_NO_START;
		}
		m_CS.LeaveCS();
		return oldState;	
	}
	
}CUE_Item;

typedef struct CUE_Schedule
{
	//std::string strScheduleUuid;
	//���ݿ������ڵ�Uuid; ��ʶ������ʱʹ�á�
	std::string strDBUuid; 
	std::string strSqlUUid;
	std::string strHallId;
	//wzp in 2013-07-24 add;
  //std::string strScheduleId;
  int iSqlUUidInTms;
  //add end;
  //wzp add A0042
  std::string strFilmName;
  //A0042 end;
	CUE_SCHEDULE_STATE state;
	int iStartTime;
	int iEndTime;
	int iCueStartTime;
	int iCueEndTime;
	std::vector<CUE_Item*> vecCueItem;
}CUE_Schedule;

typedef struct CUE_Schedule_Index
{
	std::string strSplId; //hall spl id.
}CUE_Schedule_Index;

// cue interface data
typedef struct CUE_Interface_Item
{
	//cue �豸������Ŷ�Ӧdb ��cue_code;
	int iCueCode;
	// cue ��ֵ������ֵ����ֵĬ��Ϊ0.
	int iCueValue;
	//CUEʱ��
	int  iCueTime;
	// cue��ǰ״̬��0��δ��ʼ��1��ִ�гɹ� 2��ִ�д���
	CUE_INTERFACE_ITEM_STATE  state;
	// cue	��cpl�ڵ�ƫ��ʱ�䡣
	int iCplOffsetTime;
	// ״̬����
	std::string  strInfo;
} CUE_Interface_Item;

typedef struct CUE__Interface_Cpl
{
	//cpl uuid
	std::string strCplId;
	//cpl ��spl�ڲ�����ţ�0��ʼ��
	int iCplIndex;
	//cpl�ڵ� cue �б�
	std::vector<CUE_Interface_Item> vecCueItem;
}CUE__Interface_Cpl;

typedef struct CUE_Interface_Schedule
{
	//Ӱ��ID
	std::string strHallId;
	//��ӳ�����������ڵ�uuid
	//std::string strScheduleId;
	//TMS��Spl��uuid
	//���ڿ�ʼʱ��
	int iStartPlayTime;	
	//��ӳ�������ϵ�spl uuid
	std::string strSplId;
	//TMS�϶�Ӧ��spl uuid
	int iSqlIdInTms;
	//spl �б�
	std::vector<CUE__Interface_Cpl> vecCpl;
}CUE_Interface_Schedule;


typedef struct DeviceTimePara
{
	std::string strModel;
	int iReadInterval;
	int iReadWait;
	int iWriteInterval;
}DeviceTimePara;

//duheqing 2013-5-14
struct KdmInfoFromXml
{
	std::string fileName;
	std::string path;
	std::string errorMsg; //must ascii status != 0;
	std::string size;
	std::string hash;
	int status; //success:0 error:errornum;
};
struct KdmInfoFromFilmCenter
{
	std::string ip; 
	std::string uid;
	std::string pwd;
	std::string taskCode;
	int kdmNumber;
	std::string filmName;
	std::string filmVersion;
	std::string tmsSN;
	std::string fileName;
	std::vector<KdmInfoFromXml> kdmName;
};
struct KdmInfoFromWebservice
{
	std::string uid;
	std::string pwd;
	std::string theatrecode;
	std::string tmsSN;
	std::string file;
	std::string fileName;
};

//add 2013-07-5
struct pKdmsInfo
{
	std::string name;
	std::string path;
	//std::string status;//add 07-25
	int status;
	std::string descript;//
};

/* del 07-09
struct pKdmsInfo
{
	int kdmNum;
	std::vector<pKdmInfo> kdm;
};
*/

struct pFilmInfo
{
	std::string filmname;
	std::string publiccode;
	std::string filmlasttime;
	std::string filmtype;
	std::string filmstyle;
	std::string filmversion;
};

struct pKdmInfoFromJMZX
{
	std::string taskcode;
	std::string issuer;
	std::string tasktime;
	std::string releasetime;
	std::string maketime;
	std::string makeovertime;
	std::string beforetime;
	std::string aftertime;
	std::vector<pFilmInfo> filminfo;
	std::vector<pKdmsInfo> kdmsinfo;
	std::string ip;//add
	std::string time;//add
};
//end

//add 9-27 cy
struct sDeviceInfo
{
	std::string deviceIp;
	unsigned int devicePort;
	std::string deviceVersion;
	std::string model;
	std::string brands;
	std::string serialNum;
	std::string deviceStatus;
	std::string deviceType;
	std::string connectState;
};

struct sHallInfo
{
	std::string hallCode;
	std::string hallName;
	int hallStatus;
	int totalSpace;
	int useSpace;
	int surplusSpace;
	std::string audioOffset;
	std::vector<struct sDeviceInfo> A_deviceinfo;
};

struct sCinemaAllInfo
{
	std::string cinemaCode;
	std::string cinemaName;
	int hallNum;
	std::string isAdver;
	std::string isTicket;
	std::string tmsVersion;
	std::string phpVersion;
	std::string cVersion;
	std::string mysqlVersion;
	//vector<ns1__sDeviceInfo> A_deviceinfo;
	std::vector<struct sHallInfo> A_hallinfo;
};
//end

//add projector_color_space by wzp on 2013-12-13
typedef struct ProjectorColorSpace
{
	std::string strProjectorIp;
	//ɫ�ʿռ��б�ÿһ��ĸ�ʽ���磺1:JK 235
	std::vector<std::string> macroList;
} ProjectorColorSpace;
//end;

//add cy 20151020 for gameset
struct sHallFilmDeviceStatus
{
	std::string hallid;
	int projectmarco;
	int audiochannel;
};
//end cy

//add cy 20151117 for adlistremove
struct sHallSpluuidplay
{
	std::string hallid;
	std::vector<std::string> spl_uuid_play;
};
//end cy

//20140507 by xiaozhengxiu add
//#define PRINTF_INFO_OF_AUTO_SPL//�Ƿ���ʾ �Զ�������Ϣ ����(�������沿��)
//#define PRINTF_INFO_OF_WARNING//�Ƿ���ʾ ������Ϣ ����
//#define PRINTF_INFO_OF_TLS_CHANNAL//�Ƿ���ʾ TLS��Ϣ ����

#endif //TMS20_CONST_DEFINE

//@file:C_constDef.h
//@brief: 包含各种状态信息定义。
//@author:wangzhongping@oristartech.com
//dade:2012-07-12

#ifndef TMS20_CONST_DEFINE
#define TMS20_CONST_DEFINE
#include "C_CS.h"
#include <vector>
#include <string>
//线程状态。
enum Thread_State
{
	INIT_STATE = 0, //初始
	RUN_STATE = 1,  //运行
	SUSPEND_IDL_STATE = 2, //空闲
	SUSPEND_FINISH_STATE = 3,//操作执行完成而暂停。
	RUN_LOCKED_STATE = 4,  // 运行时锁定。
	SUSPEND_LOCKED_STATE = 5 // 暂停时锁定。
};
//线程运行类型，用于区分线程执行操作的类型。
enum Thread_Run_Type
{
	RUN_WEBSERVICE_TYPE = 0, //线程正在执行Webservice调用。
	RUN_TIMETASK_TYPE = 1, // 线程正在执行定时任务。
	RUN_UNKNOWN_TYPE = 2 // 线程未执行操作。
};
 //任务状态；
enum TASK_STATE
{
	//空闲
	TASK_IDLE_STATE = 0,
	// 任务未开始执行
	TASK_NO_STATE =1,
	// 任务正在执行。
	TASK_RUNNING_STATE = 2,
	// 任务执行完成。
	TASK_FINISH_STATE  = 3,
	// 任务需要被删除
	TASK_DELETE_STATE  = 4,
	//空闲时被锁定
	TASK_LOCKED_STATE  = 5
};
//设备操作状态
enum DEVICE_OPERATE_STATE
{
	//空闲
	DEVICE_OPERATE_STATE_IDLE = 0,
	//正在与设备进行通信,设置参数。
	DEVICE_OPERATE_STATE_RUN = 1,
	//正在与设备进行通信，读取参数。
	DEVICE_OPERATE_STATE_READ = 2,	
	//CUE执行前锁定设备
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
	//影厅的全部设备。
	DEVICE_TYPE_HALL = 6
//	DEVICE_TYPE_HALL = 5
};
//影厅状态；
enum HALL_STATE
{
	//影厅在禁用状态，允许启用、删除、更换设备。
	HALL_STATE_UNENABLE = 0x0,
	//影厅在启用状态，允许各种操作。
	HALL_STATE_ENABLE = 0x1,
	//影厅正在被删除，瞬间状态，不允许任何操作。
	HALL_STATE_DELETING = 0x4,
	//影厅正在正在初始化，瞬间状态，不允许任何操作。
	HALL_STATE_INITING = 0x8
};
//设备状态,
enum DEVICE_STATE
{
	//影厅在禁用状态，允许启用、删除、更换设备。
	DEVICE_STATE_UNENABLE = 0x0,
	//影厅在启用状态，允许各种操作。
	DEVICE_STATE_ENABLE = 0x1,
	//影厅正在被删除，瞬间状态，不允许任何操作。
	DEVICE_STATE_DELETING = 0x4,
	//影厅正在正在初始化，瞬间状态，不允许任何操作。
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

//从移动硬盘dcp包获取状态
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
	//正常
	KDM_STATE_NORMAL = 0,
	//无效,与影院内无对应的dcs
	KDM_STATE_INVALID = 1,
	//过期
	KDM_STATE_TIMEOUT = 2,
	//已经存在；
	KDM_STATE_EXIST = 3,
	//kdm导入完成，只对正常KDM有效
	KDM_STATE_IMPORT_FINISH = 4,
	//KDM导入错误
	KDM_STATE_IMPORT_ERROR = 5,
	//kdm分发完成 只对 正常已经导入的kdm有效；
	KDM_STATE_DISPATCH_FINISH = 12,
	//KDM 分发错误
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
COLOR_SPACE_UNKNOW = 0, //未知
DCDM_XYZ_SCOPE_A_B = 1, //JPEG 20000 宽银幕
DCDM_XYZ_FLAT_A_B = 2,//JPEG 20000 遮幅 
MXFI_SCOPE_A = 3, //国产 MPEG2 宽银幕
MXFI_FLAT_A = 4, //国产 MPEG2 遮幅
SCOPE_3D = 5, //3D 宽银幕
FLAT_3D = 6 //3d 遮幅
};

enum CPL_TEMPLATE_TYPE
{
	FILM_PRE = 1, //片前过场;
	FREE_DEF_AD = 2, //自定义广告。
	CENTER_AD = 3, //中心广告方案。
	TYPE_VI = 4, //厂商VI
	TYPE_FILM = 5, //正片
	FILM_AFTER = 6 //片后过场。
};
//影片类型(1:正片2:预告片3：广告4：标识  9：其它 10:片前过长 11：片后过长)
enum CPL_KIND_TYPE
{
	CPL_KIND_FILM = 1, //正片
	CPL_KIND_TEASER = 2, //预告片
	CPL_KIND_AD = 3,   //广告
	CPL_KIND_TRANS = 4,  //标识
	CPK_KIND_CENTER_AD = 8, //中心广告
	CPL_KIND_OTHER = 9,  //其他
	CPL_KIND_PRE = 10,  //片前过长
	CPL_KIND_AFTER = 11 //片后过长
};

enum DCP_EXTEND_IMPORT_TYPE
{
	DCP_EXTEND_TYPE_DEFAULT = 0, // 默认 从片盘导入
	//M002
	DCP_EXTEND_TYPE_AD_SYS =1,    // 从广告系统导入
	DCP_EXTENT_TYPE_SAT_SYS = 2   // 从卫星平台导入
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
	CUE_ITM_PAUSE = 1, //暂时不用
	CUE_ITEM_LOCK_DEVICE = 2,
	CUE_ITEM_OPERATING = 3,
	CUE_ITEM_SUCCESS = 4,
	//由于设备状态与设置状态一致，CUE未执行。
	CUE_ITEM_NO_RUN = 5,
	//由于播放过程中出现跳播 导致CUE未执行。
	CUE_ITEM_NO_RUN_OFFSET = 6, //暂时不用。
	CUE_ITEM_ERROR = 7,
	//对应的CUE操作已经被删除。
	CUE_ITEM_DELETED = 8,
	//add on 2013-8-20 wzp 由于手工播放排期CUE 未执行。
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
	//正在导入KDM
	TMS_WORK_STATE_IMPORTING_KDM = 1,
	//正在导入DCP
	TMS_WORK_STATE_IMPORTING_DCP = 2,
	//正在分发DCP
	TMS_WORK_STATE_DISPATCHING_DCP = 3,
	//播放影片cue正在执行，或者即将执行。
	TMS_WORK_STATE_RUN_CUE = 4
};

// DCP 删除状态定义。
enum DCP_DELETE_STATE
{
	//删除dcp包操作还未开始。
	DCP_DELETE_NO_START = 0,
	//删除正在进行中。
	DCP_DELETE_RUNNING = 1,
	DCP_DELETE_FINISH = 2,
	DCP_DELETE_ERROR = 3
};

enum  CUE_INTERFACE_ITEM_STATE
{
	//cue未开始执行。
	CUE_INTERFACE_ITEM_STATE_NO_START = 0,
	//cue正在执行中。
	CUE_INTERFACE_ITEM_STATE_OPERATING = 1,
	//由于设备状态与设置状态一致，CUE未执行。
	//CUE_INTERFACE_ITEM_STATE_NO_RUN = 2,
	//cue执行成功
	CUE_INTERFACE_ITEM_STATE_SUCCESS = 2,
	//cue执行错误
	CUE_INTERFACE_ITEM_STATE_ERROR = 3
};

// define struct 



//const define
//默认的日志级别。
const int DEFAULT_LOG_LEVEL = 0;
//CUE 提前锁定设备的时间。
const int CUE_PRE_TIME = 5;
 // 放映服务器时间同步间隔。单位：秒。
const int DCS_TIME_SYNC_INTERVAL = 1800;
//const int DCS_TIME_SYNC_INTERVAL = 3600*6;
//获取dcs当前播放状态时间间隔。单位：秒。
const int DCS_GET_PLAY_STATE_INTERVAL = 90; //60
 //获取下一场播放状态时间间隔 秒。
 const int DCS_GET_SCHEDULES_INTERVAL = 200;
 //获取放映服务器 连接状态及参数 时间间隔 秒。
 const int DCS_GET_STATUS_INTERVAL = 90; //30
 //为广告平台虚拟机保留的磁盘空间大小
 const int DISK_SIZE_FOR_AD_RESERVE = 500*1024;
 //片库保留空间大小
 const int DISK_RESERVE_SIZE = 20*1024;
 // 线程池中线程的个数。
 const int THREAD_COUNT_IN_POOL = 128;


//struct define;
typedef struct DevicePara
{
	std::string brand;
	std::string model;
	int type;
	//音量偏移值。
	int audioOffset;
	std::string ip;
	unsigned short port;
	std::string userName;
	std::string passwd;
	std::string version;
	int isUse;
	//设备编号；
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
	std::string path;//可能是磁盘文件路径或ftp url
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
	int iFieldLampChannel; //场灯通道号；
	int iSkirtingLampChannel; //踢脚灯通道号；
	int iCleanLampChannel; //清洁灯通道号；
	int iWidthScreenChannel;//宽银幕通道号；
	int iMaskedScreenChannel; //遮幅通道号；	
}PowerChannel;

//从票务系统获取排期输出的中间结构。
typedef struct CenterSchedule
{
	FILM_COLOR_SPACE ColorSpace; //影片对应的色彩空间，从films中取。
	std::string strCplUuid;
	int iStartTime;
	std::string strHallId;
	float fDuring; //影片的cpl时长 从cpl_list中取。
	std::string strTitle; //影片的中文名称; 可从票务系统获取。
	std::string strName;  //影片的英文名称;可从数据库得到 dcp_list.title;
}CenterSchedule;

//从广告系统获取广告计划，输出的中间结构中的单个广告结构。
typedef struct SliceCpl
{
	//广告的色彩空间，如果在films表中获取失败，则输出为DCDM_XYZ_SCOPE_A_B
	FILM_COLOR_SPACE ColorSpace;  
	std::string strCplUuid;
	float fDuring; //影片的cpl时长 从cpl_list中取。
	std::vector<std::string> featureUuid;
}SliceCpl;

/*//从广告系统获取广告计划，输出的中间结构。
typedef struct SliceList
{
	std::string strSliceUuid;
	std::vector<SliceCpl> sliceCpl;
}SliceList;*/
//CUE 结构定义。
typedef struct Cue
{
	int iCueCode; //cue 编码 对应具体的CUE操作类型。
	int iOffset;  //cue 相对于cpl开始处的偏移时间值。
	int iValue;  //cue 具体数值 只对设置音量和设置音视频偏移值时有效。
}Cue;

//排期中间结构；对应的元素。
typedef struct ScheduleElement
{
	FILM_COLOR_SPACE ColorSpace;  //色彩空间。
	CPL_TEMPLATE_TYPE type;     //此cpl 对应spl模板的模板元素。
	std::vector<Cue> vecCue;         //此cpl对应的cue列表。
	std::vector<std::string> featureUuid;//正片的UUID列表，指出该片加载于哪些电影之前
	std::string cpluuid;
	float fDuring;
 
}ScheduleElement;

//排期的中间结构
typedef struct ScheduleSrt
{
	int iStartTime; //排期的开始时间
	float fDuring; //排期的总时长。
	std::string strHallId;
	int iFilmStartTime; //正片的开始时间。
	//影片的中文名称; 可从票务系统获取。 
	std::string strTitle;
	//影片的英文名称;可从数据库得到 dcp_list.title; 
	std::string strName; 
	std::vector< ScheduleElement> element;
}ScheduleSrt;

//广告DCP 下载结构
typedef struct AdDcp
{
	std::string strTitle;
	std::string strPklUuid;
	std::string strFtpUrl;
}AdDcp;

//CUE 结构定义。

typedef struct CUE_Device
{
	int iCueCode;
	std::string strDeviceModel;
	int iOperateType;
	int iOffsetValue;
}CUE_Device;
typedef struct CUE_Item
{


	//对应于CUE_Schedule.strDBUuid
	std::string strScheduleUuid;
	//cue 在系统内的统一编号。
	unsigned int uiNumber;
	//cue 设备操作编号对应db 中cue_code;
	int iCueCode;
	// cue 对应的设备操作类型 如色彩空间通道号，或者音频处理器的通道号。
	int iOperateType;
	// cue 的值如音量值。
	int iCueValue;
	//unix 时间戳
	int  iTimeSencode;
	int  iTimeMillisecond;
	CUE_ITEM_STATE  state;
	int iError;
	//cue 在spl内的偏移时间值。
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
	//数据库中排期的Uuid; 标识此排期时使用。
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
	//cue 设备操作编号对应db 中cue_code;
	int iCueCode;
	// cue 的值如音量值。此值默认为0.
	int iCueValue;
	//CUE时间
	int  iCueTime;
	// cue当前状态。0：未开始，1：执行成功 2：执行错误。
	CUE_INTERFACE_ITEM_STATE  state;
	// cue	在cpl内的偏移时间。
	int iCplOffsetTime;
	// 状态描述
	std::string  strInfo;
} CUE_Interface_Item;

typedef struct CUE__Interface_Cpl
{
	//cpl uuid
	std::string strCplId;
	//cpl 在spl内部的序号，0开始。
	int iCplIndex;
	//cpl内的 cue 列表。
	std::vector<CUE_Interface_Item> vecCueItem;
}CUE__Interface_Cpl;

typedef struct CUE_Interface_Schedule
{
	//影厅ID
	std::string strHallId;
	//放映服务器上排期的uuid
	//std::string strScheduleId;
	//TMS上Spl的uuid
	//排期开始时间
	int iStartPlayTime;	
	//放映服务器上的spl uuid
	std::string strSplId;
	//TMS上对应的spl uuid
	int iSqlIdInTms;
	//spl 列表。
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
	//色彩空间列表；每一项的格式，如：1:JK 235
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
//#define PRINTF_INFO_OF_AUTO_SPL//是否显示 自动排期信息 开关(含导入广告部分)
//#define PRINTF_INFO_OF_WARNING//是否显示 警告信息 开关
//#define PRINTF_INFO_OF_TLS_CHANNAL//是否显示 TLS信息 开关

#endif //TMS20_CONST_DEFINE

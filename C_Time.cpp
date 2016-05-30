#include "C_Time.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <C_LocalTime.h>
C_Time::C_Time()
{

}

C_Time::~C_Time()
{

}

int C_Time::getTimeInt()
{
    return (int)mktime(&m_time);
}

void C_Time::getTimeStr(string &strTime)
{
    char str[64];
    memset(str,0,64);
    sprintf(str,"%d-%02d-%02d %02d:%02d:%02d", 1900+m_time.tm_year,
		m_time.tm_mon+1, m_time.tm_mday, m_time.tm_hour,
		m_time.tm_min, m_time.tm_sec);
     strTime = str;
}
void C_Time::getDateStr(string &strDate)
{
    char str[64];
    memset(str,0,64);
    sprintf(str,"%d-%02d-%02d", 1900+m_time.tm_year,
		m_time.tm_mon+1, m_time.tm_mday);
     strDate = str;   
}
int C_Time::setCurTime()
{
    time_t tmpTime;
    tmpTime = time(NULL);

	DateTimeFromDb((int)tmpTime);//duheqing 2014-12-10
    
    //wangzhongping add  in 2012-7-15
    return C_LocalTime::GetInstance()->LocalTime(&tmpTime,m_time);
    // add end;
    
}
int C_Time::setTimeInt(int itime)
{
	DateTimeFromDb(itime);//duheqing 2014-12-10
    
     //wangzhongping add  in 2012-7-15
     time_t timetmp = (time_t)itime;
    return C_LocalTime::GetInstance()->LocalTime(&timetmp,m_time);
    // add end;
    
}
int C_Time::setTimeStr(string strTime)
{
    if(strTime.empty())
		return -1;

	DateTimeFromDb(IntTimeFromDb(strTime));//duheqing 2014-12-10
	
	//yyyy-mm-dd hh:mm:ss
	string::size_type beg = 0;
	string::size_type end = strTime.find('-', beg);
    if(end < beg)
    {
        return -1;
    }
	m_time.tm_year = atoi(strTime.substr(beg, end-beg).c_str()) - 1900;
    if(m_time.tm_year < 0)
    {
        return -1;
    }
	beg = end + 1;
	end = strTime.find('-', beg);
    if(end < beg)
    {
        return -1;
    }
	m_time.tm_mon = atoi(strTime.substr(beg, end-beg).c_str()) - 1;
    if(m_time.tm_mon < 0 || m_time.tm_mon>11)
    {
        return -1;
    }
	beg = end + 1;
	end = strTime.find(' ', beg);
    if(end < beg)
    {
        return -1;
    }
	m_time.tm_mday = atoi(strTime.substr(beg, end-beg).c_str());
    if(m_time.tm_mday<1 || m_time.tm_mday >31)
    {
        return -1;
    }
	beg = end + 1;
	end = strTime.find(':', beg);
    if(end < beg)
    {
        return -1;
    }
	m_time.tm_hour = atoi(strTime.substr(beg, end-beg).c_str());
    if(m_time.tm_hour<0 || m_time.tm_hour>23)
    {
        return -1;
    }
	beg = end + 1;
	end = strTime.find(':', beg);
    if(end < beg)
    {
        return -1;
    }
	m_time.tm_min = atoi(strTime.substr(beg, end-beg).c_str());
    if(m_time.tm_min<0 || m_time.tm_min>59)
    {
        return -1;
    }
	beg = end + 1;
	m_time.tm_sec = atoi(strTime.substr(beg).c_str());
    if(m_time.tm_sec<0 || m_time.tm_sec>59)
    {
        return -1;
    }
    
	m_time.tm_isdst = 0;

    return 0;
}



//@author liuhongjun@oristartech.com
//date 2012-07-19
//added begin
int  C_Time::setTimeTStr(string &strTime)
{
	if(strTime.empty())
		return -1;

	DateTimeFromDb(IntTimeFromDb(strTime));//2014-12-10

	//yyyy-mm-dd hh:mm:ss
	string::size_type beg = 0;
	string::size_type end = strTime.find('-', beg);
	if(end < beg)
	{
		return -1;
	}
	m_time.tm_year = atoi(strTime.substr(beg, end-beg).c_str()) - 1900;
	if(m_time.tm_year < 0)
	{
		return -1;
	}
	beg = end + 1;
	end = strTime.find('-', beg);
	if(end < beg)
	{
		return -1;
	}
	m_time.tm_mon = atoi(strTime.substr(beg, end-beg).c_str()) - 1;
	if(m_time.tm_mon < 0 || m_time.tm_mon>11)
	{
		return -1;
	}
	beg = end + 1;
	end = strTime.find('T', beg);
	if(end < beg)
	{
		return -1;
	}
	m_time.tm_mday = atoi(strTime.substr(beg, end-beg).c_str());
	if(m_time.tm_mday<1 || m_time.tm_mday >31)
	{
		return -1;
	}
	beg = end + 1;
	end = strTime.find(':', beg);
	if(end < beg)
	{
		return -1;
	}
	m_time.tm_hour = atoi(strTime.substr(beg, end-beg).c_str());
	if(m_time.tm_hour<0 || m_time.tm_hour>23)
	{
		return -1;
	}
	beg = end + 1;
	end = strTime.find(':', beg);
	if(end < beg)
	{
		return -1;
	}
	m_time.tm_min = atoi(strTime.substr(beg, end-beg).c_str());
	if(m_time.tm_min<0 || m_time.tm_min>59)
	{
		return -1;
	}
	beg = end + 1;
	m_time.tm_sec = atoi(strTime.substr(beg).c_str());
	if(m_time.tm_sec<0 || m_time.tm_sec>59)
	{
		return -1;
	}

	m_time.tm_isdst = 0;

	return 0;
}
void C_Time::getTimeTStr(string &strTime)
{
	char str[64] = {0};
	sprintf(str,"%d-%02d-%02dT%02d:%02d:%02d", 1900+m_time.tm_year,
		m_time.tm_mon+1, m_time.tm_mday, m_time.tm_hour,
		m_time.tm_min, m_time.tm_sec);
	strTime = str;
}

void C_Time::getHhMmSs(string &strTime)
{
	char str[64] = {0};
	sprintf(str,"%02d:%02d:%02d", m_time.tm_hour,
		m_time.tm_min, m_time.tm_sec);
	strTime = str;
}

int C_Time::IntTimeFromDb(const string &dateTime)
{
	int addEight = 8*60*60;
	int deltaTimeZone = 0;

	size_t pos = dateTime.find('+');
	if(pos == string::npos)
	{
		pos = dateTime.find(':');
		if(pos != string::npos)
			pos = dateTime.find("-", pos);
	}
	if(pos != string::npos)
	{
		int realTimeZone = atoi(dateTime.substr(pos+1, dateTime.find(':', pos+1) - (pos+1)).c_str()) * 60 * 60;
		deltaTimeZone = (dateTime[pos]=='+' ? addEight-realTimeZone : addEight+realTimeZone);
	}

	CppMySQL3DB mySql;
	int result = mySql.openTMS();
	if(result != 0)
		return result;

	string sql = "select unix_timestamp(\"" + dateTime.substr(0, pos) + "\") as uts;";
	CppMySQLQuery recordset = mySql.querySQL(sql.c_str(), result);
	if(result != 0)
		return result;

	recordset.seekRow(0);
	if(recordset.numRow() != 0)
		return recordset.getIntField("uts") + deltaTimeZone;
	else
		return -1;
}

int C_Time::DateTimeFromDb(int time)
{
	if(time < 0)
		return time;
	char tmp[32];
	sprintf(tmp, "%d", time);
	m_IntDateTime = tmp;

	CppMySQL3DB mySql;
	int result = mySql.openTMS();
	if(result != 0)
		return result;

	string sql = "select from_unixtime(" + m_IntDateTime + ") as fut;";
	CppMySQLQuery recordset = mySql.querySQL(sql.c_str(), result);
	if(result != 0)
		return result;

	recordset.seekRow(0);
	if(recordset.numRow() != 0)
		m_StrDateTime = recordset.getStringField("fut");

	m_DateTTime = m_StrDateTime;
	if(m_DateTTime.find(' ') != string::npos)
		m_DateTTime[m_DateTTime.find(' ')] = 'T';

	sql = "select date(\"" + m_StrDateTime + "\") as dt" 
		+ ",time(\"" + m_StrDateTime + "\") as tm"
		+ ",year(\"" + m_StrDateTime + "\") as yr"
		+ ",month(\"" + m_StrDateTime + "\") as mnth"
		+ ",day(\"" + m_StrDateTime + "\") as dy"
		+ ",hour(\"" + m_StrDateTime + "\") as hr"
		+ ",minute(\"" + m_StrDateTime + "\") as mnt"
		+ ",second(\"" + m_StrDateTime + "\") as sc;";
	recordset.close();//duheqing 2015-01-04 memory leak
	recordset = mySql.querySQL(sql.c_str(), result);
	if(result != 0)
		return result;

	recordset.seekRow(0);
	if(recordset.numRow() != 0)
	{
		m_onlyDate = recordset.getStringField("dt");
		m_onlyTime = recordset.getStringField("tm");
		m_year = recordset.getStringField("yr");
		m_month = recordset.getStringField("mnth");
		m_day = recordset.getStringField("dy");
		m_hour = recordset.getStringField("hr");
		m_minute = recordset.getStringField("mnt");
		m_second = recordset.getStringField("sc");
	}
	return 0;
}

//added end

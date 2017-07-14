#pragma once

#include "../mysql/include/mysql.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#define  MYSQL_POOL_SIZE 60



class DatabaseVariable
{
public:
	DatabaseVariable(){};
	~DatabaseVariable(){};

private:
	std::string val;
	
public:
	std::string  tosting()
	{
		return val;
	}
	int          tonumber()
	{
		if (val.size() == 0)
		{
			return 0;
		}
		return atoi(val.c_str());
	}
	bool         toTime(int& Y, int& m, int& D, int& h , int& mm, int& s);
	std::wstring towstring()
	{
		 std::wstring tmp;
		 StrtoWstr(val,tmp);
		 return tmp;
	}

	void Init(std::string tmp)
	{
	    val = tmp;
	}
	void Init(std::wstring tmp)
	{
		WstrtoStr(tmp,val);
	}
	void Init(int number)
	{
		NumberToStr(number,val);
	}
	void Init(int& Y, int& m, int& D, int& h , int& mm, int& s)
	{
		std::string strY,strm,strD,strh,strmm,strs;
		NumberToStr(Y,strY);
		NumberToStr(m,strm);
		NumberToStr(D,strD);
		NumberToStr(h,strh);
		NumberToStr(mm,strmm);
		NumberToStr(s,strs);

		val = strY + "-"+strm+"-"+strD+" "+strh+":"+strmm+":"+strs;
	}

	bool isDifferent(std::string tmp)
	{
		if (val.compare(tmp) != 0)
		{
			return true;
		}

		return false;
	}

	bool isDifferent(DatabaseVariable& tmp)
	{
		std::string tmp_val = tmp.tosting();
		if (val.compare(tmp_val) != 0)
		{
			return true;
		}

		return false;
	}

	void ClearVal()
	{
		val = "";
	}

	bool isValid()
	{
		return val.size() > 0;
	}

	bool isEmpty()
	{
		return val.size() == 0;
	}

public:

	static int WstrtoStr(std::wstring& src, std::string& des);
	static int StrtoWstr(std::string& src, std::wstring& des);
	static void StrToNumber(std::string& src, int& des);
	static void NumberToStr(int& src, std::string& des);
};

class DatabaseStruct
{
public:
	DatabaseStruct(){};
	~DatabaseStruct(){};

	DatabaseVariable id;        //记录ID

	DatabaseVariable ask_per;    //反馈人
	DatabaseVariable ask_perid;  //qq号 反馈人信息号
	DatabaseVariable ask_time;   //提问时间 反馈时间

	DatabaseVariable record_per; //客服 记录人
	DatabaseVariable record_time;   //录入时间 记录时间

	DatabaseVariable question_type;  //问题类别
	DatabaseVariable question_dis;  //问题描述
	DatabaseVariable question_result;    //解决方案
	DatabaseVariable question_comment;   //备注

	DatabaseVariable deliver_per;    //转交人
	DatabaseVariable deliver_time;  //转交时间
	DatabaseVariable deadline;  //希望完成时间

	DatabaseVariable accept_per; //接收人
	DatabaseVariable accept_time; //接收时间
	DatabaseVariable accept_done; //接收人完成时间
	DatabaseVariable accept_comment; //完成说明

	DatabaseVariable score_num;     //评分
	DatabaseVariable score_comment; //评价说明
	DatabaseVariable score_per;     //评价人

	bool isError()
	{
		if (id.tonumber() == -1)
		{
			return true;
		}

		return false;
	}
public:
	bool Compare_Change(DatabaseStruct& tmp, std::vector<DatabaseVariable>& allval);
};

class SqlConnect
{
public:
	SqlConnect()
	{
		m_bConnect = false;
		m_bsqlInit = false;
	}
	virtual ~SqlConnect()
	{

	}

	bool Connect_DB();
	bool DisConnect_DB();

	bool SqlSelect(const char* sqlstr);
	bool SqlRunSqlNoReturn(const char* sqlstr,char* errormsg);

	virtual void Fetch_row_item(MYSQL_ROW row) = 0;

private:
	bool GetServerSet(CStringA& csdb_path,CStringA& db_user,CStringA& db_psd,int& db_port,CStringA& db_name);


private:
	MYSQL mysql;
	bool m_bConnect;
	bool m_bsqlInit;
};

class MySqlConnect:public SqlConnect
{
public:
	MySqlConnect();
	~MySqlConnect();


	bool Mysql_Addto(DatabaseStruct& tmp);
	bool Mysql_Update(DatabaseStruct& tmp);
	bool Mysql_DelFrom(DatabaseStruct& tmp);
	bool Mysql_selectFrom(std::vector<DatabaseStruct>& allval, std::string condition);
	virtual void Fetch_row_item(MYSQL_ROW row);
	DatabaseStruct tmp_val;
	std::vector<DatabaseStruct> all_val;

	static int pos;

private:

	char* ReadFiletoChar(std::wstring filepath, size_t& len){
		std::fstream fs;
		char*  pdata = NULL;
		fs.open(filepath.c_str(),std::ios::in|std::ios::binary);
		if (fs)
		{
			fs.seekg(0,std::ios::end);
			std::ios::pos_type o = fs.tellg();
			len = (size_t)o;
			pdata = new char[len];
			fs.seekg(0,std::ios::beg);
			fs.read(pdata, len);
			fs.close();
		}
		return pdata;
	}



	bool WriteJPGFile(char* pdata, char* filepath , int length);

};

struct UserInfo
{
	std::string user;
	std::string pwd;
	std::string role;
};
class CUserManager:public SqlConnect
{
public:
	CUserManager()
	{

	}

	~CUserManager()
	{

	}

	std::vector<UserInfo> users;

	bool SelectUsers(std::vector<UserInfo>& _users,std::string condition);
    bool UpdataUser(UserInfo& user);
	bool DeleteUser(UserInfo& user);
	bool InsertUser(UserInfo& user);

	virtual void Fetch_row_item(MYSQL_ROW row);


};

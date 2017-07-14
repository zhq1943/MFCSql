#include "stdafx.h"
#include "MySqlConnect.h"
#include <iostream>
#include <regex>


int   MySqlConnect::pos          = 0;

#define _CompareValue(val,_struct,_vector) if(val.isDifferent(_struct.val)!=0){_vector.push_back(_struct.val);};
#define _CompareEmptyValue(val,_struct,_vector) if(val.isDifferent(_struct.val)==false){_struct.val.ClearVal();}else{_vector.push_back(_struct.val);};

MySqlConnect::MySqlConnect()
{

}

MySqlConnect::~MySqlConnect()
{

}


bool MySqlConnect::WriteJPGFile( char* pdata, char* filepath , int length )
{
	std::fstream fs;
	fs.open(filepath, std::ios::binary|std::ios::out);
	if (fs)
	{
		fs.write(pdata,length);
		fs.close();
	}
	return true;
}




bool MySqlConnect::Mysql_Addto( DatabaseStruct& tmp )
{
	std::stringstream sqlstr;
	MYSQL_ROW m_row;
	MYSQL_RES* m_res;
	size_t len = 0;
	sqlstr << "insert into bugreport_new \
			  ( ask_per, ask_perid, ask_time,\
			    record_per, record_time,\
			    question_type, question_dis, question_result, question_comment,\
				deliver_per, deliver_time, deadline,\
				accept_per, accept_time, accept_done, accept_comment,\
				score_num, score_comment, score_per) \
			  values \
			  (\""<<tmp.ask_per.tosting()<<"\",\""<<tmp.ask_perid.tosting()<<"\",\""<<tmp.ask_time.tosting()<<"\",\""
			      <<tmp.record_per.tosting()<<"\",\""<<tmp.record_time.tosting()<<"\",\""
				  <<tmp.question_type.tosting()<<"\",\""<<tmp.question_dis.tosting()<<"\",\""<<tmp.question_result.tosting()<<"\",\""<<tmp.question_comment.tosting()<<"\",\""
			      <<tmp.deliver_per.tosting()<<"\",\""<<tmp.deliver_time.tosting()<<"\",\""<<tmp.deadline.tosting()<<"\",\""
			      <<tmp.accept_per.tosting()<<"\",\""<<tmp.accept_time.tosting()<<"\",\""<<tmp.accept_done.tosting()<<"\",\""<<tmp.accept_comment.tosting()<<"\",\""
			      <<tmp.score_num.tonumber()<<"\",\""<<tmp.score_comment.tosting()<<"\",\""<<tmp.score_per.tosting()<<"\");";


	std::string tmp_sql_str = sqlstr.str();
// 	if (mysql_query(&mysql,tmp_sql_str.c_str()) != 0)
// 	{
// 		return false;
// 	}
	char* errormsg = "";
	SqlRunSqlNoReturn(tmp_sql_str.c_str(),errormsg);
	return true;

}

bool MySqlConnect::Mysql_Update( DatabaseStruct& tmp )
{
	std::stringstream sqlstr_title;
	std::stringstream sqlstr_val;

	if (tmp.isError())
	{
		return false;
	}

	if (tmp.ask_per.isValid())
	{
		sqlstr_title << "ask_per"
		             << "="
		             << "\""<<tmp.ask_per.tosting() <<"\""
		             <<",";
	}

	if (tmp.ask_perid.isValid())
	{
		sqlstr_title << "ask_perid"
					 << "="
					 << "\""<<tmp.ask_perid.tosting() <<"\""
					 <<",";
	}

	if (tmp.ask_time.isValid())
	{
		sqlstr_title << "ask_time"
					 << "="
					 << "\""<<tmp.ask_time.tosting() <<"\""
					 <<",";
	}

	//server persion
	if (tmp.record_per.isValid())
	{
		sqlstr_title << "record_per"
			<< "="
			<< "\""<<tmp.record_per.tosting() <<"\""
			<<",";
	}

	if (tmp.record_time.isValid())
	{
		sqlstr_title << "record_time"
			<< "="
			<< "\""<<tmp.record_time.tosting() <<"\""
			<<",";
	}

	//question 
	if (tmp.question_type.isValid())
	{
		sqlstr_title << "question_type"
			<< "="
			<< "\""<<tmp.question_type.tosting() <<"\""
			<<",";
	}

	if (tmp.question_dis.isValid())
	{
		sqlstr_title << "question_dis"
			<< "="
			<< "\""<<tmp.question_dis.tosting() <<"\""
			<<",";
	}

	if (tmp.question_result.isValid())
	{
		sqlstr_title << "question_result"
			<< "="
			<< "\""<<tmp.question_result.tosting() <<"\""
			<<",";
	}

	if (tmp.question_comment.isValid())
	{
		sqlstr_title << "question_comment"
			<< "="
			<< "\""<<tmp.question_comment.tosting() <<"\""
			<<",";
	}

	//deliver 
	if (tmp.deliver_per.isValid())
	{
		sqlstr_title << "deliver_per"
			<< "="
			<< "\""<<tmp.deliver_per.tosting() <<"\""
			<<",";
	}

	if (tmp.deliver_time.isValid())
	{
		sqlstr_title << "deliver_time"
			<< "="
			<< "\""<<tmp.deliver_time.tosting() <<"\""
			<<",";
	}

	if (tmp.deadline.isValid())
	{
		sqlstr_title << "deadline"
			<< "="
			<< "\""<<tmp.deadline.tosting() <<"\""
			<<",";
	}

	//accept
	if (tmp.accept_per.isValid())
	{
		sqlstr_title << "accept_per"
			<< "="
			<< "\""<<tmp.accept_per.tosting() <<"\""
			<<",";
	}

	if (tmp.accept_time.isValid())
	{
		sqlstr_title << "accept_time"
			<< "="
			<< "\""<<tmp.accept_time.tosting() <<"\""
			<<",";
	}

	if (tmp.accept_done.isValid())
	{
		sqlstr_title << "accept_done"
			<< "="
			<< "\""<<tmp.accept_done.tosting() <<"\""
			<<",";
	}

	if (tmp.accept_comment.isValid())
	{
		sqlstr_title << "accept_comment"
			<< "="
			<< "\""<<tmp.accept_comment.tosting() <<"\""
			<<",";
	}

	//score
	if (tmp.score_num.isValid())
	{
		sqlstr_title << "score_num"
			<< "="
			<<tmp.score_num.tosting()
			<<",";
	}

	if (tmp.score_comment.isValid())
	{
		sqlstr_title << "score_comment"
			<< "="
			<< "\""<<tmp.score_comment.tosting() <<"\""
			<<",";
	}

	if (tmp.score_per.isValid())
	{
		sqlstr_title << "score_per"
			<< "="
			<< "\""<<tmp.score_per.tosting() <<"\""
			<<",";
	}


	std::stringstream combin_sql_str;
	std::string tmp_sqlstr_title = sqlstr_title.str();
	int pos = tmp_sqlstr_title.find_last_of(',');
	(tmp_sqlstr_title.at(pos)) = ' ';
	combin_sql_str << "update bugreport_new set "
		           <<  tmp_sqlstr_title
				   <<  " where id = " << tmp.id.tonumber();

	std::string tmp_sql_str = combin_sql_str.str();

// 	if (mysql_query(&mysql, tmp_sql_str.c_str()) != 0)
// 	{
// 		return false;
// 	}
	char* errormsg = "";
	return SqlRunSqlNoReturn(tmp_sql_str.c_str(),errormsg);
}

bool MySqlConnect::Mysql_DelFrom( DatabaseStruct& tmp )
{
	if (tmp.isError())
	{
		return false;
	}

	std::stringstream m_del_str;
	m_del_str << "delete from bugreport_new where id = "
		      << tmp.id.tosting();

	std::string tmp_del_str = m_del_str.str();
// 	if (mysql_query(&mysql,tmp_del_str.c_str())!= 0)
// 	{
// 		return false;
// 	}

	char* errormsg = "";
	SqlRunSqlNoReturn(tmp_del_str.c_str(),errormsg);

	return true;
}

bool MySqlConnect::Mysql_selectFrom( std::vector<DatabaseStruct>& allval, std::string condition )
{
	allval.clear();
   
	unsigned int i,j = 0;    
	std::string sqlstr =  "select \
						  id,ask_per, ask_perid,ask_time, record_per, record_time,\
						  question_type, question_dis, question_result, question_comment,\
						  deliver_per, deliver_time, deadline,\
						  accept_per, accept_time, accept_done, accept_comment,\
						  score_num, score_comment, score_per\
						  from bugreport_new";

	if (condition.size() != 0)
	{
		std::string tmp = sqlstr;
		tmp += " where " + condition;
		sqlstr = tmp.c_str();
	}

	all_val.clear();
	if (SqlSelect(sqlstr.c_str()))
	{
		allval = all_val;
	}else
	{
		return false;
	}

	/*i = mysql_real_query(&mysql,sqlstr.c_str(),(unsigned int)strlen(sqlstr.c_str()));//    执行查询   
	if ( i < 0 )    
	{    
		return false;
	}   

	res = mysql_store_result(&mysql); 
	if (!res)
	{
		return false;
	}

	while(row = mysql_fetch_row(res))
	{
		DatabaseStruct tmp_val;

		tmp_val.id.Init(row[0]);
		tmp_val.ask_per.Init(row[1]);
		tmp_val.ask_perid.Init(row[2]);
		tmp_val.ask_time.Init(row[3]);

		tmp_val.record_per.Init(row[4]);
		tmp_val.record_time.Init(row[5]);

		tmp_val.question_type.Init(row[6]);
        tmp_val.question_dis.Init(row[7]);
		tmp_val.question_result.Init(row[8]);
		tmp_val.question_comment.Init(row[9]);

		tmp_val.deliver_per.Init(row[10]);
		tmp_val.deliver_time.Init(row[11]);
		tmp_val.deadline.Init(row[12]);

		tmp_val.accept_per.Init(row[13]);
		tmp_val.accept_time.Init(row[14]);
		tmp_val.accept_done.Init(row[15]);
		tmp_val.accept_comment.Init(row[16]);

		tmp_val.score_num.Init(row[14]);
		tmp_val.score_comment.Init(row[15]);
		tmp_val.score_per.Init(row[16]);

		allval.push_back(tmp_val);
	}*/

	return true;
}


void MySqlConnect::Fetch_row_item(MYSQL_ROW row)
{
	tmp_val.id.Init(row[0]);
	tmp_val.ask_per.Init(row[1]);
	tmp_val.ask_perid.Init(row[2]);
	tmp_val.ask_time.Init(row[3]);

	tmp_val.record_per.Init(row[4]);
	tmp_val.record_time.Init(row[5]);

	tmp_val.question_type.Init(row[6]);
	tmp_val.question_dis.Init(row[7]);
	tmp_val.question_result.Init(row[8]);
	tmp_val.question_comment.Init(row[9]);

	tmp_val.deliver_per.Init(row[10]);
	tmp_val.deliver_time.Init(row[11]);
	tmp_val.deadline.Init(row[12]);

	tmp_val.accept_per.Init(row[13]);
	tmp_val.accept_time.Init(row[14]);
	tmp_val.accept_done.Init(row[15]);
	tmp_val.accept_comment.Init(row[16]);

	tmp_val.score_num.Init(row[14]);
	tmp_val.score_comment.Init(row[15]);
	tmp_val.score_per.Init(row[16]);

	all_val.push_back(tmp_val);
}





bool DatabaseVariable::toTime( int& Y, int& m, int& D, int& h , int& mm, int& s )
{
	std::regex patt("([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})");

	std::sregex_iterator it(val.begin(),val.end(),patt),eos;
	if (it != eos)
	{
		std::string tmp_ss = (*it)[1];
		Y = atoi(tmp_ss.c_str());
		Y = Y<1900?2000:Y;
		tmp_ss = (*it)[2];
		m = atoi(tmp_ss.c_str());
		m = m<1?1:m;
		tmp_ss = (*it)[3];
		D = atoi(tmp_ss.c_str());
		D = D<1?1:D;
		D %= 32;
		tmp_ss = (*it)[4];
		h = atoi(tmp_ss.c_str());
		h %= 24;
		tmp_ss = (*it)[5];
		mm = atoi(tmp_ss.c_str());
		mm %= 60;
		tmp_ss = (*it)[6];
		s = atoi(tmp_ss.c_str());
		s %= 60;
	}else
	{
		return false;
	}

	return true;
}


int DatabaseVariable::WstrtoStr( std::wstring& src, std::string& des )
{
	DWORD dwMinSize; 
	dwMinSize = WideCharToMultiByte (CP_OEMCP,NULL,src.c_str(),-1,NULL,0,NULL,FALSE); 
    char* tmp = new char[dwMinSize];
	// Convert headers from ASCII to Unicode. 
	WideCharToMultiByte(CP_OEMCP,NULL,src.c_str(),-1,tmp,dwMinSize,NULL,FALSE);  
	des = tmp;
	delete []tmp;
	tmp = NULL;
	return dwMinSize;
}

int DatabaseVariable::StrtoWstr( std::string& src, std::wstring& des )
{

	DWORD dwMinSize; 
	dwMinSize = MultiByteToWideChar (CP_ACP, 0, src.c_str(), -1, NULL, 0); 
    wchar_t* tmp = new wchar_t[dwMinSize];
	// Convert headers from ASCII to Unicode. 
	MultiByteToWideChar (CP_ACP, 0, src.c_str(), -1, tmp, dwMinSize);
	des = tmp;
	delete []tmp;
	tmp = NULL;
	return dwMinSize; 
}

void DatabaseVariable::StrToNumber( std::string& src, int& des ) //做成模板
{
	std::stringstream tmp;
	tmp << src;
	tmp >> des;
}

void DatabaseVariable::NumberToStr( int& src, std::string& des )
{
	std::stringstream tmp;
	tmp << src;
	tmp >> des;
}

bool DatabaseStruct::Compare_Change(DatabaseStruct& tmp, std::vector<DatabaseVariable>& alldiff)
{
	 _CompareEmptyValue(ask_per,tmp,alldiff);
	 _CompareEmptyValue(ask_perid,tmp,alldiff);
	 _CompareEmptyValue(ask_time,tmp,alldiff);

	 _CompareEmptyValue(record_per,tmp,alldiff);
	 _CompareEmptyValue(record_time,tmp,alldiff);

	 _CompareEmptyValue(question_type,tmp,alldiff);
	 _CompareEmptyValue(question_dis,tmp,alldiff);
	 _CompareEmptyValue(question_result,tmp,alldiff);
	 _CompareEmptyValue(question_comment,tmp,alldiff);

	 _CompareEmptyValue(deliver_per,tmp,alldiff);
	 _CompareEmptyValue(deliver_time,tmp,alldiff);
	 _CompareEmptyValue(deadline,tmp,alldiff);

	 _CompareEmptyValue(accept_per,tmp,alldiff);
	 _CompareEmptyValue(accept_time,tmp,alldiff);
	 _CompareEmptyValue(accept_done,tmp,alldiff);
	 _CompareEmptyValue(accept_comment,tmp,alldiff);

	 _CompareEmptyValue(score_num,tmp,alldiff);
	 _CompareEmptyValue(score_comment,tmp,alldiff);
	 _CompareEmptyValue(score_per,tmp,alldiff);


	 return true;
}

bool SqlConnect::Connect_DB()
{
	if (m_bConnect)
	{
		return true;
	}

	if (!m_bsqlInit)
	{
		if (mysql_init(&mysql) == NULL)
		{
			TRACE("初始化失败！");
		}else
		{
			m_bsqlInit = true;
		}

	}

	CStringA db_path;
	CStringA db_user;
	CStringA db_psd;
	int db_port;
	CStringA db_name;
	GetServerSet(db_path,db_user,db_psd,db_port,db_name);
	mysql_options(&mysql,MYSQL_SET_CHARSET_NAME,"gb2312");
	if (!mysql_real_connect(&mysql,db_path,db_user,db_psd,db_name,db_port,NULL,0))
	{
		return false;
	}else
	{
		m_bConnect = true;
	}

	return m_bConnect;
}

bool SqlConnect::DisConnect_DB()
{
	mysql_close(&mysql);
	m_bConnect = false;
	return true;
}

bool SqlConnect::GetServerSet( CStringA& csdb_path,CStringA& db_user,CStringA& db_psd,int& db_port,CStringA& db_name )
{
	HMODULE module = GetModuleHandle(0);   
	char pFileName[MAX_PATH];   
	GetModuleFileNameA(module, pFileName, MAX_PATH);   

	CStringA csFullPath(pFileName);   
	int nPos = csFullPath.ReverseFind('\\');   

	if(nPos < 0)
		return false;

	CStringA ini_path = csFullPath.Left(nPos);
	ini_path += L"\\SERVER.ini";

	char tmpstr[128]={0};
	GetPrivateProfileStringA("SERVER","IPADDRESS","localhost",tmpstr,128,ini_path.GetBuffer());
	csdb_path = tmpstr;
	GetPrivateProfileStringA("SERVER","DBUSER","anyone",tmpstr,128,ini_path.GetBuffer());
	db_user = tmpstr;
	GetPrivateProfileStringA("SERVER","USERPWD","",tmpstr,128,ini_path.GetBuffer());
	db_psd = tmpstr;
	db_port =GetPrivateProfileIntA("SERVER","DBPORT",8000,ini_path.GetBuffer());
	GetPrivateProfileStringA("SERVER","DBNAME","TEST",tmpstr,128,ini_path.GetBuffer());
	db_name = tmpstr;

	return true;
}

bool SqlConnect::SqlSelect( const char* sqlstr )
{
	Connect_DB();
	if (m_bConnect&&m_bsqlInit == false)
	{
		return false;
	}

	MYSQL_RES *res;    
	MYSQL_ROW row;    

	int i = mysql_real_query(&mysql,sqlstr,(unsigned int)strlen(sqlstr));//    执行查询   
	if ( i < 0 )    
	{    
		return false;
	}   

	res = mysql_store_result(&mysql); 
	if (!res)
	{
		return false;
	}

	while(row = mysql_fetch_row(res))
	{
		Fetch_row_item(row);
	}

	return DisConnect_DB();
}

bool SqlConnect::SqlRunSqlNoReturn( const char* sqlstr,char* errormsg)
{
	Connect_DB();
	if (m_bConnect&&m_bsqlInit == false)
	{
		return false;
	}

	if (mysql_query(&mysql,sqlstr)!= 0)
	{
		errormsg = "error";
		return false;
	}

	return DisConnect_DB();
}

bool CUserManager::SelectUsers(std::vector<UserInfo>& _users,std::string condition)
{
	users.clear();
	std::string sqlstr =  "select username, password,role from bugreport_user ";
	if (condition.size() > 0)
	{
		sqlstr += " where ";
		sqlstr += condition;
	}

	SqlSelect(sqlstr.c_str());

	_users = users;

	return true;
}

bool CUserManager::UpdataUser( UserInfo& user )
{
	if (user.pwd.size() == 0&&user.role.size() == 0)
	{
		return false;
	}
	std::stringstream sqlstr;
	sqlstr << "update bugreport_user set ";
	if (user.pwd.size() != 0)
	{
		sqlstr << "password = "
			   << "\""<<user.pwd<<"\" ";
	}

	if (user.role.size() != 0)
	{
		sqlstr << "role = "
			   <<"\""<<user.role<<"\"";
	}

	sqlstr << " where username = "
		   << "\"" <<user.user<<"\"";

	char* msg = "";
	std::string tmp_str = sqlstr.str();
	return SqlRunSqlNoReturn(tmp_str.c_str(),msg);
}

bool CUserManager::DeleteUser( UserInfo& user )
{
	std::stringstream sqlstr;
	sqlstr << "delete from bugreport_user where username = "
		   << "\""<<user.user <<"\"";

	char* msg = "";
	std::string tmp_str = sqlstr.str();
	return SqlRunSqlNoReturn(tmp_str.c_str(),msg);
}

bool CUserManager::InsertUser( UserInfo& user )
{
	std::stringstream sqlstr;
	sqlstr <<"insert into bugreport_user (username, password, role) values ("
		   <<"\""<<user.user<<"\","
		   <<"\""<<user.pwd<<"\","
		   <<"\""<<user.role<<"\")";

	char* msg = "";
	std::string tmp_str = sqlstr.str();
	return SqlRunSqlNoReturn(tmp_str.c_str(),msg);
}

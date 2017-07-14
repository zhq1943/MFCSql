
// BugReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BugReport.h"
#include "BugReportDlg.h"
#include "afxdialogex.h"

#include "../mysql/include/mysql.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

#include "MySqlConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _M_X64
#pragma comment(lib,"../mysql/x64/libmysql.lib")
#else
#pragma comment(lib,"../mysql/win32/libmysql.lib")
#endif

MYSQL mysql;

// CAboutDlg dialog used for App About


using namespace std;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBugReportDlg dialog




CBugReportDlg::CBugReportDlg(DLG_TYPE type,CWnd* pParent /*=NULL*/)
	: CDialogEx(CBugReportDlg::IDD, pParent)
	,path_pic1(_T(""))
	,path_pic2(_T(""))
	,path_pic3(_T(""))
	, m_edit_answer(_T(""))
	, m_edit_question(_T(""))
	, m_qq_str(_T(""))
	, m_edit_common(_T(""))
	, m_edit_turnto(_T(""))
	, m_edit_answerp(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dlg_type = type;
}

void CBugReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_answer);
	DDX_Text(pDX, IDC_EDIT2, m_edit_question);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_data_time);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_turn_to_time);
	DDX_Control(pDX, IDC_COMBO1, m_var_turnto);
	DDX_Text(pDX, IDC_EDIT_QQ, m_qq_str);
	DDX_Text(pDX, IDC_EDIT3, m_edit_common);
	DDX_CBString(pDX, IDC_COMBO1, m_edit_turnto);
	DDX_Text(pDX, IDC_EDIT4, m_edit_answerp);
}

BEGIN_MESSAGE_MAP(CBugReportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CBugReportDlg::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CBugReportDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON4, &CBugReportDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CBugReportDlg message handlers

BOOL CBugReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_font.CreatePointFont(150,_T("宋体"));
	m_brush.CreateSolidBrush(RGB(255,255,255));

#ifdef _DEBUG
// 	path_pic1 = _T("d://test1.jpg");
// 	path_pic2 = _T("d://test2.jpg");
// 	path_pic3 = _T("d://test3.jpg");
 	m_edit_question = _T("测试问题1abc_ACB");
 	m_edit_answer = _T("测试解决方案123abc");
 	m_qq_str = _T("23023406306");
 	m_edit_common = _T("测试备注");
 	m_edit_answerp = _T("客服1");
#endif
	CString str;
	CTime tm; tm = CTime::GetCurrentTime();
	//str = tm.Format("现在时间是%Y年%m月%d日 %X");
	//MessageBox(str,NULL,MB_OK);
	m_data_time.SetTime(&tm);
	m_turn_to_time.SetTime(&tm);
	m_data_time.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_turn_to_time.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));



	m_listctrl.InsertColumn(0,_T("路径"),0,400);
// 	m_listctrl.InsertItem(0,_T("d://test1.jpg"));
// 	m_listctrl.InsertItem(1,_T("d://test2.jpg"));
// 	m_listctrl.InsertItem(2,_T("d://test3.jpg"));

	m_var_turnto.InsertString(0,_T("张志云"));
	m_var_turnto.InsertString(1,_T("赵汗青"));
	m_var_turnto.SetCurSel(0);

	if (m_dlg_type == INFO_MODIFY)
	{
	    InitData();
	}

	if (m_dlg_type == INFO_MODIFY)
	{
	    GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBugReportDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBugReportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBugReportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString CBugReportDlg::BootOpenDialog()
{
	CString strFile = _T("");

	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.jpg)|*.jpg|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
	}

	return strFile;
}



void CBugReportDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
// 	path_pic2 = BootOpenDialog();
// 	CString tmp = _T("附件2：");
// 	tmp += path_pic2;
// 	CString path = SelFilePath(); 
// 	m_listctrl.InsertItem(0,path.GetBuffer());
// 	return;

	std::vector<CString> files;
	SelectFiles(files);

	m_listctrl.DeleteAllItems();
	for (int i = 0; i< files.size(); i++)
	{
		CString filename = files.at(i);
		 m_listctrl.InsertItem(i,filename.GetBuffer());
	}
	//GetDlgItem(IDC_STATIC_PIC2)->SetWindowTextW(tmp);
}

HBRUSH CBugReportDlg::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC,pWnd,nCtlColor);
// 	if (GetDlgItem(IDC_STATIC_PIC1)->m_hWnd == pWnd->m_hWnd)
// 	{
// 		pDC->SelectObject(&m_font);
// 		return m_brush;
// 	}

	return hbr;
}


void CBugReportDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//上传到数据库

	UpdateData(TRUE);
	if (m_qq_str.IsEmpty()||m_edit_answer.IsEmpty()||m_edit_answerp.IsEmpty()||m_edit_common.IsEmpty()||m_edit_question.IsEmpty())
	{
		MessageBox(L"数据不完整，请检查数据");
		return;
	}

	if (m_dlg_type == INFO_MODIFY)
	{
		DatabaseStruct new_record;
		new_record.id.Init(old_record.id.tosting());
		UpdateGetData(new_record);
		std::vector<DatabaseVariable> allrecord;

		old_record.Compare_Change(new_record,allrecord);
			//res = databaseconnect.Mysql_Updata(_val,old_val);
        bool res = databaseconnect.Mysql_Update(new_record);

		if (!res)
		{
			int res = AfxMessageBox(L"修改失败！",MB_OKCANCEL);
			return;
		}

	}else
	{
		UpdateData();
		DatabaseStruct tmp_record;
		UpdateGetData(tmp_record);

		std::string errormsg;
		databaseconnect.Mysql_Addto(tmp_record);
	}

	

	CDialogEx::OnOK();
}

void CBugReportDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here

	UpdateData();

	if (m_qq_str.IsEmpty()||m_edit_answer.IsEmpty()||m_edit_answerp.IsEmpty()||m_edit_common.IsEmpty()||m_edit_question.IsEmpty())
	{
		MessageBox(L"数据不完整，请检查数据");
		return;
	}


	CString fpath1 = m_listctrl.GetItemText(0,0);
	CString fpath2 = m_listctrl.GetItemText(1,0);
	CString fpath3 = m_listctrl.GetItemText(2,0);

	DatabaseStruct tmp;
	UpdateGetData(tmp);

	std::string errormsg;
	databaseconnect.Mysql_Addto(tmp);


	return ;
}

bool CBugReportDlg::WriteJPGFile( char* pdata, char* filepath,int length)
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

bool CBugReportDlg::SelectFiles( vector<CString>& all_sel_files )
{
	CFileDialog dlg(TRUE, _T("*.jpg"), NULL, OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("Image Files(*.jpg)|*.jpg|"), NULL); 
	dlg.m_ofn.lpstrTitle = _T("选择图片"); 
	CString filename; 
	if(dlg.DoModal() == IDOK) 
	{ 
		POSITION fileNamesPosition = dlg.GetStartPosition(); 
		while(fileNamesPosition != NULL) 
		{ 
			filename = dlg.GetNextPathName(fileNamesPosition); 
			all_sel_files.push_back(filename);
		}   
	} 

	return true;
}

CString CBugReportDlg::SelFilePath()
{
	TCHAR           szFolderPath[MAX_PATH] = {0};  
	CString         strFolderPath = TEXT("");  

	BROWSEINFO      sInfo;  
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));  
	sInfo.pidlRoot   = 0;  
	sInfo.lpszTitle   = _T("请选择处理结果存储路径");  
	sInfo.ulFlags   = BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_DONTGOBELOWDOMAIN;  
	sInfo.lpfn     = NULL;  

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);   
	if (lpidlBrowse != NULL)  
	{  
		// 取得文件夹名  
		if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))    
		{  
			strFolderPath = szFolderPath;  
		}  
	}  
	if(lpidlBrowse != NULL)  
	{  
		::CoTaskMemFree(lpidlBrowse);  
	}  

	return strFolderPath;  
}
void PatternTimeWStr(std::wstring in_str, CTime& _time)
{
	std::wregex patt(L"([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})");
	try
	{
		int y,m,d,h,mm,s;
		std::wsregex_iterator it(in_str.begin(),in_str.end(),patt),eos;
		if (it != eos)
		{
			std::wstring tmp_ss = (*it)[1];
			y = _wtoi(tmp_ss.c_str());
			y = y<1900?2000:y;
			tmp_ss = (*it)[2];
			m = _wtoi(tmp_ss.c_str());
			m = m<1?1:m;
			tmp_ss = (*it)[3];
			d = _wtoi(tmp_ss.c_str());
			d = d<1?1:d;
			d %= 32;
			tmp_ss = (*it)[4];
			h = _wtoi(tmp_ss.c_str());
			h %= 24;
			tmp_ss = (*it)[5];
			mm = _wtoi(tmp_ss.c_str());
			mm %= 60;
			tmp_ss = (*it)[6];
			s = _wtoi(tmp_ss.c_str());
			s %= 60;

			_time = CTime(y,m,d,h,mm,s);
		}
	}
	catch (regex_error e)
	{

	}

}
void CBugReportDlg::InitData( )
{
	m_qq_str = old_record.ask_perid.towstring().c_str();
	CTime _time;
	PatternTimeWStr(old_record.ask_time.towstring(),_time);
	m_data_time.SetTime(&_time);

   //	CTime( atoi((*it)[0]),(*it)[1],(*it)[2],(*it)[3],(*it)[4],(*it)[5]);
	m_edit_question = old_record.question_dis.towstring().c_str();
	m_edit_answer = old_record.question_result.towstring().c_str();
	m_edit_common = old_record.question_comment.towstring().c_str();

	PatternTimeWStr(old_record.deliver_time.towstring(),_time);
	m_turn_to_time.SetTime(&_time);
	m_edit_answerp =old_record.ask_per.towstring().c_str();

	UpdateData(FALSE);

	if (old_record.accept_per.towstring().compare(L"张志云")==0)
	{
		m_var_turnto.SetCurSel(0);
	}else if (old_record.accept_per.towstring().compare(L"赵汗青")==0)
	{
		m_var_turnto.SetCurSel(1);
	}
}

void CBugReportDlg::UpdateGetData( DatabaseStruct& tmp_record )
{
	UpdateData();
	CTime tmp_time;
	m_turn_to_time.GetTime(tmp_time);
	CString time_str = tmp_time.FormatGmt(_T("%Y-%m-%d %H:%M:%S"));
	tmp_record.deliver_time.Init(time_str.GetBuffer());

	m_data_time.GetTime(tmp_time);
	CString time_str2 = tmp_time.FormatGmt(_T("%Y-%m-%d %H:%M:%S"));
	tmp_record.ask_time.Init(time_str2.GetBuffer());

	CTime system_time = CTime::GetCurrentTime();
	CString time_str3 = system_time.FormatGmt(_T("%Y-%m-%d %H:%M:%S"));
	tmp_record.record_time.Init(time_str3.GetBuffer());

	CString fpath1 = m_listctrl.GetItemText(0,0);
	CString fpath2 = m_listctrl.GetItemText(1,0);
	CString fpath3 = m_listctrl.GetItemText(2,0);

	tmp_record.ask_perid.Init(m_qq_str.GetBuffer());
	tmp_record.ask_per.Init(m_qq_str.GetBuffer());
	tmp_record.question_type.Init("new");
	tmp_record.question_dis.Init(m_edit_question.GetBuffer());
	tmp_record.question_result.Init(m_edit_answer.GetBuffer());
	tmp_record.question_comment.Init(m_edit_common.GetBuffer());
	tmp_record.accept_per.Init(m_edit_turnto.GetBuffer());
}


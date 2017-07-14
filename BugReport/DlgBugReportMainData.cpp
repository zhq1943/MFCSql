// DlgBugReportMainData.cpp : implementation file
//

#include "stdafx.h"
#include "BugReport.h"
#include "DlgBugReportMainData.h"
#include "afxdialogex.h"
#include "BugReportDlg.h"
#include "MySqlConnect.h"
#include "DialogCondition.h"
#include <ctime>


// CDlgBugReportMainData dialog
int page_count = 0;
IMPLEMENT_DYNAMIC(CDlgBugReportMainData, CDialogEx)

CDlgBugReportMainData::CDlgBugReportMainData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBugReportMainData::IDD, pParent)
	, m_edit_num_perpage(30)
	, m_page_string(_T(""))
{
	sel_line = -1;
	page_num = 0;
}

CDlgBugReportMainData::~CDlgBugReportMainData()
{
}

void CDlgBugReportMainData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALLDATA, m_listctrl_data);
	DDX_Text(pDX, IDC_EDIT1_NUM_PERPAGE, m_edit_num_perpage);
	DDX_Text(pDX, IDC_STATIC_NUM_PAGE, m_page_string);
}


BEGIN_MESSAGE_MAP(CDlgBugReportMainData, CDialogEx)
	ON_BN_CLICKED(IDOK_ADD, &CDlgBugReportMainData::OnBnClickedAdd)
	ON_BN_CLICKED(IDOK_MODIFY, &CDlgBugReportMainData::OnBnClickedModify)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ALLDATA, &CDlgBugReportMainData::OnNMClickListAlldata)
	ON_BN_CLICKED(IDOK_DEL, &CDlgBugReportMainData::OnBnClickedDel)
	ON_BN_CLICKED(IDOK_FIND, &CDlgBugReportMainData::OnBnClickedFind)
	ON_BN_CLICKED(IDOK_ALL, &CDlgBugReportMainData::OnBnClickedAll)
	ON_BN_CLICKED(IDCANCEL, &CDlgBugReportMainData::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK_EXP, &CDlgBugReportMainData::OnBnClickedExp)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CDlgBugReportMainData::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CDlgBugReportMainData::OnBnClickedButtonDown)
	ON_EN_CHANGE(IDC_EDIT1_NUM_PERPAGE, &CDlgBugReportMainData::OnEnChangeEdit1NumPerpage)
	ON_BN_CLICKED(IDOK_ON_ME, &CDlgBugReportMainData::OnBnClickedOnMe)
END_MESSAGE_MAP()


// CDlgBugReportMainData message handlers


void CDlgBugReportMainData::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	CBugReportDlg dlg(INFO_ADD);
	if (dlg.DoModal() == IDOK)
	{
		InitData();
	}

}


void CDlgBugReportMainData::OnBnClickedModify()
{
	// TODO: Add your control notification handler code here
	if (sel_line != -1)
	{
		CBugReportDlg dlg(INFO_MODIFY);
		dlg.old_record = (all_records.at(sel_line));
		dlg.DoModal();

	    InitData();

	}

}

void CDlgBugReportMainData::InitData()
{
	
    std::string errormsg;
	all_records.clear();
	//tmpdatabase.Mysql_Select_SqlStr(all_values,"",errormsg);
	database.Mysql_selectFrom(all_records,"");


	FillList();

}

BOOL CDlgBugReportMainData::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listctrl_data.SetExtendedStyle(m_listctrl_data.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);//选中整行 添加checkbox
	CRect rect;
	m_listctrl_data.GetClientRect(&rect);
	int _width = (rect.right - rect.left)/6;
	m_listctrl_data.InsertColumn(0,_T("QQ号"),0,_width);
	m_listctrl_data.InsertColumn(1,_T("问题"),0,_width);
	m_listctrl_data.InsertColumn(2,_T("备注"),0,_width);
	m_listctrl_data.InsertColumn(3,_T("客服"),0,_width);
	m_listctrl_data.InsertColumn(4,_T("提交时间"),0,_width);
	m_listctrl_data.InsertColumn(5,_T("转交人"),0,_width);

	InitData();

	InitPage();
	m_page_string.Format(L"第1页，共%d页",page_count);
	UpdateData(FALSE);
	return TRUE;
}


void CDlgBugReportMainData::OnNMClickListAlldata(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	sel_line = pNMItemActivate->iItem;
}


void CDlgBugReportMainData::OnBnClickedDel()
{
	// TODO: Add your control notification handler code here
	
	std::string erromsg;
	if (sel_line != -1)
	{
		int sel = AfxMessageBox(_T("确定删除该条记录？"),MB_OKCANCEL);
		if (sel == 2)
		{
			return;
		}

		bool res = database.Mysql_DelFrom(all_records.at(sel_line));
		if (res)
		{
			all_records.clear();
			database.Mysql_selectFrom(all_records,"");
			FillList();
			sel_line = -1;
		}
	}
}

void CDlgBugReportMainData::FillList(  )
{
	m_listctrl_data.DeleteAllItems();
// 	size_t si = all_values.size();
// 	int ind = 0;
// 	for (int i = page_num*m_edit_num_perpage; i < (page_num+1)*m_edit_num_perpage; ++i)
// 	{
// 		if (i >= si)
// 		{
// 			break;
// 		}
// 		DataBaseValue tmp = all_values.at(i);
// 		m_listctrl_data.InsertItem(ind,tmp.id.c_str());
// 		m_listctrl_data.SetItemText(ind,0,tmp.qqnum.c_str());
// 		m_listctrl_data.SetItemText(ind,1,tmp.question.c_str());
// 		m_listctrl_data.SetItemText(ind,2,tmp.comment.c_str());
// 		m_listctrl_data.SetItemText(ind,3,tmp.ansperson.c_str());
// 		m_listctrl_data.SetItemText(ind,4,tmp.addtime.c_str());
// 		m_listctrl_data.SetItemText(ind,5,tmp.turnto.c_str());
// 
// 		++ind;
// 	}

	size_t si = all_records.size();
	int ind = 0;
	for (int i = page_num*m_edit_num_perpage; i < (page_num+1)*m_edit_num_perpage; ++i)
	{
		if (i >= si)
		{
			break;
		}
		DatabaseStruct tmp = all_records.at(i);
		m_listctrl_data.InsertItem(ind,tmp.id.towstring().c_str());
		m_listctrl_data.SetItemText(ind,0,tmp.ask_perid.towstring().c_str());
		m_listctrl_data.SetItemText(ind,1,tmp.question_dis.towstring().c_str());
		m_listctrl_data.SetItemText(ind,2,tmp.question_comment.towstring().c_str());
		m_listctrl_data.SetItemText(ind,3,tmp.record_per.towstring().c_str());
		m_listctrl_data.SetItemText(ind,4,tmp.record_time.towstring().c_str());
		m_listctrl_data.SetItemText(ind,5,tmp.deliver_per.towstring().c_str());

		++ind;
	}
}


void CDlgBugReportMainData::OnBnClickedFind()
{
	// TODO: Add your control notification handler code here
	CDialogCondition dlg;
	if (dlg.DoModal() == IDOK)
	{
		all_records = dlg.all_val;
		FillList();
	}
}


void CDlgBugReportMainData::OnBnClickedAll()
{
	// TODO: Add your control notification handler code here
	MySqlConnect tmpdb;
	std::wstring errormsg;
	//tmpdb.Mysql_Select_SqlStr(all_values,L"",errormsg);
	all_records.clear();
	database.Mysql_selectFrom(all_records,"");
	FillList();
}


void CDlgBugReportMainData::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CDlgBugReportMainData::OnBnClickedExp()
{
	// TODO: Add your control notification handler code here
	CString str;
    CTime tm; tm = CTime::GetCurrentTime();
	str = tm.Format("现在时间是%Y年%m月%d日 %X");
	MessageBox(str,NULL,MB_OK);
//     SYSTEMTIME st;
// 	CString strDate,strTime;
// 	GetLocalTime(&st);
// 	strDate.Format(L"%4d-%2d-%2d %2d:%2d:%2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
// 	MessageBox(strDate,NULL,MB_OK);
}


void CDlgBugReportMainData::InitPage()
{
	page_count = all_records.size()/m_edit_num_perpage;
	if (all_records.size()%m_edit_num_perpage > 0)
	{
		page_count += 1;
	}

	page_num = 0;
}


void CDlgBugReportMainData::OnBnClickedButtonUp()
{
	// TODO: Add your control notification handler code here
	if (page_num > 0)
	{
		page_num -=1;
	}else
	{
		return;
	}

	m_page_string.Format(L"第%d页，共%d页", page_num+1,page_count);
	UpdateData(FALSE);
	FillList();
}


void CDlgBugReportMainData::OnBnClickedButtonDown()
{
	// TODO: Add your control notification handler code here
	if (page_num < page_count-1)
	{
		page_num += 1;
	}else
	{
		return;
	}


	m_page_string.Format(L"第%d页，共%d页", page_num+1,page_count);
	UpdateData(FALSE);
	FillList();
}


void CDlgBugReportMainData::OnEnChangeEdit1NumPerpage()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int old = m_edit_num_perpage;
	UpdateData();
    if (m_edit_num_perpage > 0)
    {
		InitPage();
		m_page_string.Format(L"第1页，共%d页",page_count);
		UpdateData(FALSE);
		page_num = 0;
		FillList();
    }else
	{
		m_edit_num_perpage = old;
	}
	
}


void CDlgBugReportMainData::OnBnClickedOnMe()
{
	// TODO: Add your control notification handler code here
	CMenu mymenu;
	CPoint pt;
	GetCursorPos(&pt);
	if (mymenu.CreatePopupMenu())
	{
		mymenu.AppendMenuW(MF_STRING,10001,L"登录");
		mymenu.AppendMenuW(MF_STRING,10002,L"分配给我");

		mymenu.TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);

		mymenu.Detach();
		mymenu.DestroyMenu();
	}

}

BOOL CDlgBugReportMainData::OnCommand( WPARAM wParam, LPARAM lParam )
{
	UINT uid = (UINT)wParam;
	switch(uid)
	{
	case 10001:
		//AfxMessageBox(L"登录");
		break;
	case 10002:
		//AfxMessageBox(L"分配给我");
		break;
	default:
		break;
	}

	return CDialogEx::OnCommand(wParam,lParam);
}

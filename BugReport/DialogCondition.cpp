// DialogCondition.cpp : implementation file
//

#include "stdafx.h"
#include "BugReport.h"
#include "DialogCondition.h"
#include "afxdialogex.h"
#include "DlgCreateCondition.h"


// CDialogCondition dialog

IMPLEMENT_DYNAMIC(CDialogCondition, CDialogEx)

CDialogCondition::CDialogCondition(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogCondition::IDD, pParent)
{

}

CDialogCondition::~CDialogCondition()
{
}

void CDialogCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_condition);
}


BEGIN_MESSAGE_MAP(CDialogCondition, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogCondition::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1_ADD, &CDialogCondition::OnBnClickedButton1Add)
END_MESSAGE_MAP()

BOOL CDialogCondition::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_list_condition.InsertColumn(0,L"并列条件",0,80);
	m_list_condition.InsertColumn(1,L"字段",0,80);
	m_list_condition.InsertColumn(2,L"条件",0,80);
	m_list_condition.InsertColumn(3,L"值"  ,0,80);

	return TRUE;
}


// CDialogCondition message handlers


void CDialogCondition::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	MySqlConnect tmp;
	std::wstring m_condition;
	std::wstring errormsg;

	int counts = m_list_condition.GetItemCount();
	for (int i = 0; i < counts; i++)
	{
		CString tmp_andor = m_list_condition.GetItemText(i,0);
		CString val_name  = m_list_condition.GetItemText(i,1);
		CString condi    = m_list_condition.GetItemText(i,2);
		CString value_   = m_list_condition.GetItemText(i,3);

		if (val_name.IsEmpty() || value_.IsEmpty() || condi.IsEmpty())
		{
			continue;
		}

		if (tmp_andor.CompareNoCase(_T("并且")) == 0)
		{
			m_condition += _T(" and ");
		}else if (tmp_andor.CompareNoCase(_T("或者")) == 0)
		{
			m_condition += _T(" or ");
		}


		if (val_name.CompareNoCase(_T("QQ")) == 0)
		{
			m_condition += _T("ask_perid");
		}else if (val_name.CompareNoCase(_T("客服")) == 0)
		{
			m_condition += _T("record_per");
		}else if (val_name.CompareNoCase(_T("转交人")) == 0)
		{
			m_condition += _T("deliver_per");
		}else if (val_name.CompareNoCase(_T("问题")) == 0)
		{
			m_condition += _T("question_dis");
		}else if (val_name.CompareNoCase(_T("解决方案")) == 0)
		{
			m_condition += _T("question_result");
		}else if (val_name.CompareNoCase(_T("备注")) == 0)
		{
			m_condition += _T("question_comment");
		}else if (val_name.CompareNoCase(_T("提交时间")) == 0)
		{
			m_condition += _T("record_time");
		}

		if (condi.CompareNoCase(_T("等于")) == 0)
		{
			m_condition += _T(" = ");
			m_condition += _T("\"") + value_+_T("\"");
		}else if (condi.CompareNoCase(_T("不等于")) == 0)
		{
			m_condition += _T(" != ");
			m_condition += _T("\"") + value_+_T("\"");
		}else if (condi.CompareNoCase(_T("包含")) == 0)
		{
			m_condition += _T(" like ");
			m_condition += _T("\"%") + value_+_T("%\"");
		}else if (condi.CompareNoCase(_T("不包含")) == 0)
		{
			m_condition += _T("not like ");
			m_condition += _T("\"%") + value_+_T("%\"");
		}else if (condi.CompareNoCase(_T("大于")) == 0)
		{
			m_condition += _T(" > ");
			m_condition += _T("\"") + value_+_T("\"");
		}else if (condi.CompareNoCase(_T("小于")) == 0)
		{
			m_condition += _T(" < ");
			m_condition += _T("\"") + value_+_T("\"");
		}
	}

	std::string tmp_sql;
	DatabaseVariable::WstrtoStr(m_condition,tmp_sql);
	tmp.Mysql_selectFrom(all_val,tmp_sql);
	CDialogEx::OnOK();
}


void CDialogCondition::OnBnClickedButton1Add()
{
	// TODO: Add your control notification handler code here
	CDlgCreateCondition dlg;
	dlg.condition_count = m_list_condition.GetItemCount();
	if (dlg.DoModal() == IDOK)
	{
		m_list_condition.InsertItem(dlg.condition_count,dlg.m_condi_andor);
		m_list_condition.SetItemText(dlg.condition_count,0,dlg.m_condi_andor);
		m_list_condition.SetItemText(dlg.condition_count,1,dlg.m_val_name);
		m_list_condition.SetItemText(dlg.condition_count,2,dlg.condi);
		m_list_condition.SetItemText(dlg.condition_count,3,dlg.m_val);

	}
}

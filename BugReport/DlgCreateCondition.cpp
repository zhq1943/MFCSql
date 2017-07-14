// DlgCreateCondition.cpp : implementation file
//

#include "stdafx.h"
#include "BugReport.h"
#include "DlgCreateCondition.h"
#include "afxdialogex.h"
#include <regex>

// CDlgCreateCondition dialog

IMPLEMENT_DYNAMIC(CDlgCreateCondition, CDialogEx)

CDlgCreateCondition::CDlgCreateCondition(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCreateCondition::IDD, pParent)
	, m_val(_T(""))
{

}

CDlgCreateCondition::~CDlgCreateCondition()
{
}

void CDlgCreateCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CONUM, m_combo_conum);
	DDX_Control(pDX, IDC_COMBO_CONDITON, m_combo_condition);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_val);
	DDX_Control(pDX, IDC_COMBO_ANDOR, m_combo_andor);
}


BEGIN_MESSAGE_MAP(CDlgCreateCondition, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCreateCondition::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDlgCreateCondition::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_combo_andor.AddString(_T("并且"));
	m_combo_andor.AddString(_T("或者"));

	m_combo_conum.AddString(_T("QQ"));
	m_combo_conum.AddString(_T("客服"));
	m_combo_conum.AddString(_T("转交人"));
	m_combo_conum.AddString(_T("问题"));
	m_combo_conum.AddString(_T("解决方案"));
	m_combo_conum.AddString(_T("备注"));
	m_combo_conum.AddString(_T("提交时间"));


    m_combo_condition.AddString(_T("等于"));
	m_combo_condition.AddString(_T("不等于"));
	m_combo_condition.AddString(_T("包含"));
	m_combo_condition.AddString(_T("不包含"));
	m_combo_condition.AddString(_T("大于"));
	m_combo_condition.AddString(_T("小于"));

	m_combo_condition.SetCurSel(0);
	m_combo_conum.SetCurSel(0);
	m_combo_andor.SetCurSel(0);

	

	return TRUE;
}


// CDlgCreateCondition message handlers


void CDlgCreateCondition::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData();
	m_combo_condition.GetWindowTextW(condi);
	m_combo_conum.GetWindowTextW(m_val_name);
	m_combo_andor.GetWindowTextW(m_condi_andor);

	if (condition_count != 0)
	{
		if (m_condi_andor.CompareNoCase(_T("而且")) == 0)
		{
			m_condition += _T(" and ");
		}else
		{
			m_condition += _T(" or ");
		}
	}else
	{
		m_condi_andor = L"";
	}
	

	if (m_val_name.CompareNoCase(_T("QQ")) == 0)
	{
		m_condition += _T("QQnum");
	}else if (m_val_name.CompareNoCase(_T("客服")) == 0)
	{
		m_condition += _T("Ansperson");
	}else if (m_val_name.CompareNoCase(_T("转交人")) == 0)
	{
		m_condition += _T("Turnto");
	}else if (m_val_name.CompareNoCase(_T("问题")) == 0)
	{
		m_condition += _T("Question");
	}else if (m_val_name.CompareNoCase(_T("解决方案")) == 0)
	{
		m_condition += _T("Result");
	}else if (m_val_name.CompareNoCase(_T("备注")) == 0)
	{
		m_condition += _T("Comment");
	}else if (m_val_name.CompareNoCase(_T("提交时间")) == 0)
	{
		m_condition += _T("Addtime");
		std::wstring in_str = m_val;
		std::wregex patt(L"([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})");
		std::wsregex_iterator it(in_str.begin(),in_str.end(),patt),eos;
		if (it == eos){
			AfxMessageBox(L"时间格式错误，格式为：2016-12-31 12:12:12");
			return ;
		}
		
	}

	
	

	if (condi.CompareNoCase(_T("等于")) == 0)
	{
		m_condition += _T(" = ");
		m_condition += _T("\"") + m_val+_T("\"");
	}else if (condi.CompareNoCase(_T("不等于")) == 0)
	{
		m_condition += _T(" != ");
		m_condition += _T("\"") + m_val+_T("\"");
	}else if (condi.CompareNoCase(_T("包含")) == 0)
	{
		m_condition += _T(" like ");
		m_condition += _T("\"%") + m_val+_T("%\"");
	}else if (condi.CompareNoCase(_T("不包含")) == 0)
	{
		m_condition += _T("not like ");
		m_condition += _T("\"%") + m_val+_T("%\"");
	}else if (condi.CompareNoCase(_T("大于")) == 0)
	{
		m_condition += _T(" > ");
		m_condition += _T("\"") + m_val+_T("\"");
	}else if (condi.CompareNoCase(_T("小于")) == 0)
	{
		m_condition += _T(" < ");
		m_condition += _T("\"") + m_val+_T("\"");
	}


	CDialogEx::OnOK();
}

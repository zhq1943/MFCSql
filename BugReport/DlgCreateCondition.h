#pragma once
#include "afxwin.h"


// CDlgCreateCondition dialog

class CDlgCreateCondition : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCreateCondition)

public:
	CDlgCreateCondition(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCreateCondition();

// Dialog Data
	enum { IDD = IDD_DIALOG1_MAKE_CONDITIONSSTR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CString m_condition;
public:
	CComboBox m_combo_conum;
	CComboBox m_combo_condition;
	CString m_val;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CComboBox m_combo_andor;

	int condition_count;
	CString m_condi_andor;
	CString m_val_name;
	CString condi;
};

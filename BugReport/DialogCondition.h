#pragma once
#include "afxcmn.h"
#include "MySqlConnect.h"
#include <vector>
// CDialogCondition dialog

class CDialogCondition : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCondition)

public:
	CDialogCondition(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogCondition();

// Dialog Data
	enum { IDD = IDD_DIALOG1_CONDITION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_condition;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	std::vector<DatabaseStruct> all_val;
	afx_msg void OnBnClickedButton1Add();
};

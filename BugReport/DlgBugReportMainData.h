#pragma once
#include "afxcmn.h"
#include "MySqlConnect.h"

// CDlgBugReportMainData dialog

class CDlgBugReportMainData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBugReportMainData)

public:
	CDlgBugReportMainData(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgBugReportMainData();

// Dialog Data
	enum { IDD = IDD_DIALOG_MAINDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	void InitData();
	CListCtrl m_listctrl_data;

	int sel_line;
	afx_msg void OnNMClickListAlldata(NMHDR *pNMHDR, LRESULT *pResult);

	std::vector<DatabaseStruct> all_records;
	afx_msg void OnBnClickedDel();

	void FillList();
	afx_msg void OnBnClickedFind();
	afx_msg void OnBnClickedAll();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedExp();
	int m_edit_num_perpage;

	void InitPage();
	int page_num;
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	CString m_page_string;
	afx_msg void OnEnChangeEdit1NumPerpage();

	MySqlConnect database;
	afx_msg void OnBnClickedOnMe();

	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

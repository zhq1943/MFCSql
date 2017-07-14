
// BugReportDlg.h : header file
//

#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include "MySqlConnect.h"
enum DLG_TYPE
{
	INFO_ADD,
	INFO_MODIFY,
};


// CBugReportDlg dialog
class CBugReportDlg : public CDialogEx
{
// Construction
public:
	CBugReportDlg(DLG_TYPE mtype,CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BUGREPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	

	CString BootOpenDialog();
	bool SelectFiles(std::vector<CString>& all_sel_files);
	CString SelFilePath();
	CString path_pic1;
	CString path_pic2;
	CString path_pic3;
	afx_msg void OnBnClickedButton2();

	CBrush m_brush;
	CFont  m_font;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();

	CString m_edit_question;
	CString m_edit_answer;
	afx_msg void OnBnClickedButton4();

	bool WriteJPGFile(char* pdata, char* filepath , int length);
	CDateTimeCtrl m_data_time;
	CListCtrl m_listctrl;
	CDateTimeCtrl m_turn_to_time;
	CComboBox m_var_turnto;
	CString m_qq_str;
	CString m_edit_common;
	CString m_edit_turnto;
	CString m_edit_answerp;
	DLG_TYPE m_dlg_type;

	void InitData();

	void UpdateGetData(DatabaseStruct& nv);
	DatabaseStruct old_record;

	MySqlConnect databaseconnect;
};

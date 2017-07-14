#pragma once


// CDialogLogin dialog

class CDialogLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLogin)

public:
	CDialogLogin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogLogin();

// Dialog Data
	enum { IDD = IDD_DIALOG1_LOGININ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

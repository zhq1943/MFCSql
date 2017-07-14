// DialogLogin.cpp : implementation file
//

#include "stdafx.h"
#include "BugReport.h"
#include "DialogLogin.h"
#include "afxdialogex.h"


// CDialogLogin dialog

IMPLEMENT_DYNAMIC(CDialogLogin, CDialogEx)

CDialogLogin::CDialogLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogLogin::IDD, pParent)
{

}

CDialogLogin::~CDialogLogin()
{
}

void CDialogLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogLogin, CDialogEx)
END_MESSAGE_MAP()


// CDialogLogin message handlers

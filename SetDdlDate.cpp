// SetDdlDate.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplicationGoodLuck.h"
#include "SetDdlDate.h"
#include "afxdialogex.h"


// SetDdlDate 对话框

IMPLEMENT_DYNAMIC(SetDdlDate, CDialogEx)

SetDdlDate::SetDdlDate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAL_DIALOG, pParent)
{

}

SetDdlDate::~SetDdlDate()
{
}

void SetDdlDate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER, calendar);
}


BEGIN_MESSAGE_MAP(SetDdlDate, CDialogEx)
	ON_BN_CLICKED(IDOK, &SetDdlDate::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SetDdlDate::OnBnClickedCancel)
END_MESSAGE_MAP()


// SetDdlDate 消息处理程序


void SetDdlDate::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime time;
	calendar.GetTime(time);
	date.year = time.GetYear();
	date.month = time.GetMonth();
	date.day = time.GetDay();
	CDialogEx::OnOK();
}


void SetDdlDate::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

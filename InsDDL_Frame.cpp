// InsDDL_Frame.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplicationGoodLuck.h"
#include "InsDDL_Frame.h"
#include "afxdialogex.h"


// InsDDL_Frame 对话框

IMPLEMENT_DYNAMIC(InsDDL_Frame, CDialogEx)

InsDDL_Frame::InsDDL_Frame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DDL, pParent)
	, text_about_DDL(_T(""))
	, text_DDL_type(_T(""))
	//, text_edit_end_hour(_T(""))
	, text_DDL_end_hour(_T(""))
	, text_DDL_end_min(_T(""))
	, text_DDL_start_hour(_T(""))
	, text_DDL_start_min(_T(""))
	, text_pre_alarm(_T(""))
{

}

InsDDL_Frame::~InsDDL_Frame()
{
}

void InsDDL_Frame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ABOUT_DDL, edit_about_DDL);
	DDX_Text(pDX, IDC_ABOUT_DDL, text_about_DDL);
	DDX_Control(pDX, IDC_DDL_TYPE, edit_DDL_type);
	DDX_Text(pDX, IDC_DDL_TYPE, text_DDL_type);
	DDX_Control(pDX, IDC_EDIT_END_HOUR, edit_DDL_end_hour);
	//  DDX_Text(pDX, IDC_EDIT_END_HOUR, text_edit_end_hour);
	DDX_Text(pDX, IDC_EDIT_END_HOUR, text_DDL_end_hour);
	DDX_Control(pDX, IDC_EDIT_END_MIN, edit_DDL_end_min);
	DDX_Text(pDX, IDC_EDIT_END_MIN, text_DDL_end_min);
	DDX_Control(pDX, IDC_EDIT_START_HOUR, edit_DDL_start_hour);
	DDX_Text(pDX, IDC_EDIT_START_HOUR, text_DDL_start_hour);
	DDX_Control(pDX, IDC_EDIT_START_MIN, edit_DDL_start_min);
	DDX_Text(pDX, IDC_EDIT_START_MIN, text_DDL_start_min);
	DDX_Control(pDX, IDC_PRE_ALARM, edit_pre_alarm);
	DDX_CBString(pDX, IDC_PRE_ALARM, text_pre_alarm);
	DDX_Control(pDX, IDC_SET_DATE, click_set_date);
}


BEGIN_MESSAGE_MAP(InsDDL_Frame, CDialogEx)
	ON_BN_CLICKED(IDOK, &InsDDL_Frame::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SET_DATE, &InsDDL_Frame::OnClickedSetDate)
END_MESSAGE_MAP()


// InsDDL_Frame 消息处理程序

#include"SetDdlDate.h"
void InsDDL_Frame::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void InsDDL_Frame::OnClickedSetDate()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDdlDate dlg;
	if (dlg.DoModal() == IDOK) {
		date.year = dlg.date.year;
		date.month = dlg.date.month;
		date.day = dlg.date.day;
		return;
	}
}

#pragma once


// InsDDL_Frame 对话框
struct Date
{
	int year;
	int month;
	int day;
};

class InsDDL_Frame : public CDialogEx
{
	DECLARE_DYNAMIC(InsDDL_Frame)

public:
	InsDDL_Frame(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~InsDDL_Frame();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DDL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_about_DDL;
	CString text_about_DDL;
	CEdit edit_DDL_type;
	CString text_DDL_type;
	CEdit edit_DDL_end_hour;
//	CString text_edit_end_hour;
	CString text_DDL_end_hour;
	CEdit edit_DDL_end_min;
	CString text_DDL_end_min;
	CEdit edit_DDL_start_hour;
	CString text_DDL_start_hour;
	CEdit edit_DDL_start_min;
	CString text_DDL_start_min;
	CComboBox edit_pre_alarm;
	CString text_pre_alarm;
	CButton click_set_date;
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedSetDate();
public:
	Date date;
};

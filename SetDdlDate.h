#pragma once


// SetDdlDate 对话框
struct setDate
{
	int year;
	int month;
	int day;
};
class SetDdlDate : public CDialogEx
{
	DECLARE_DYNAMIC(SetDdlDate)

public:
	SetDdlDate(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SetDdlDate();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	setDate date;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CDateTimeCtrl calendar;
};

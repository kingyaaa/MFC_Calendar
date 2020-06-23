
// MFCApplicationGoodLuckDlg.h: 头文件
//

#pragma once

#include "CMyListCtrl.h"

// CMFCApplicationGoodLuckDlg 对话框
class CMFCApplicationGoodLuckDlg : public CDialogEx
{
// 构造
public:
	CMFCApplicationGoodLuckDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONGOODLUCK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// afx_msg void OnLvnItemchangedCalList(NMHDR* pNMHDR, LRESULT* pResult);
	CMyListCtrl m_MyListCtrl;
	CString GetDate(int year,int month, int day, int i, int j,int k);
	//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

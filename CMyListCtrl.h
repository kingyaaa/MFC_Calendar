#pragma once
#include "InsDDL_Frame.h"
#include<string>
#include<vector>
using namespace std;
struct DDLTime
{
	int hour;
	int min;
};
struct Alarm
{
	int year;
	int month;
	int day;
	DDLTime time;
	CString text;
};
struct DDL
{
	CString type;
	CString text;
	int year;
	int month;
	int day;
	DDLTime start;
	DDLTime end;
	bool pre_alarm;
	Alarm alarm;
};
class CMyListCtrl :
    public CListCtrl
{
public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    void SetRowHeight(int nHeight);
public:
    int m_nRowHeight;
    DECLARE_MESSAGE_MAP()
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    afx_msg void OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
public:
	vector<DDL>myDDL;
	vector<Alarm>myAlarm;
	Alarm getAlarm(DDL& ddl, CString str);
	int lastDayOfLastMonth(const int month, const int day);
};


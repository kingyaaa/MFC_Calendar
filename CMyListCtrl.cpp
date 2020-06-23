#include "pch.h"
#include "CMyListCtrl.h"


void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	LVITEM lvi = { 0 };
	lvi.mask = LVIF_STATE;
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
	lvi.iItem = lpDrawItemStruct->itemID;
	BOOL bGet = GetItem(&lvi);
	//高亮显示
	BOOL bHighlight = ((lvi.state & LVIS_DROPHILITED) || ((lvi.state & LVIS_SELECTED) && ((GetFocus() == this) || (GetStyle() & LVS_SHOWSELALWAYS))));
	//画文本背景
	CRect rcBack = lpDrawItemStruct->rcItem;//将这里要绘制的文本背景设置为一个单元格
	pDC->SetBkMode(TRANSPARENT);
	if (bHighlight) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->FillRect(rcBack, &CBrush(RGB(90, 162, 0)));
	}
	else {
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->FillRect(rcBack, &CBrush(RGB(255, 255, 255)));
	}
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		//写文本
		CString szText;
		int nCollumn = GetHeaderCtrl()->GetItemCount();//列数
		for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++) {
			//循环得到文本
			CRect rcItem;
			if (!GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem))
				continue;
			szText = GetItemText(lpDrawItemStruct->itemID, i);
			rcItem.left += 5;
			rcItem.right -= 1;
			pDC->DrawText(szText, lstrlen(szText), &rcItem, DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
		}
	}
}

BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyListCtrl::OnNMCustomdraw)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyListCtrl::OnNMClick)
END_MESSAGE_MAP()

void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{ 
	lpMeasureItemStruct->itemHeight = m_nRowHeight; 
}

void CMyListCtrl::SetRowHeight(int nHeight) {
	m_nRowHeight = nHeight; //如果没有下面的代码，设置并不能奏效 
	CRect rcWin; 
	GetWindowRect(&rcWin);
	WINDOWPOS wp; 
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void CMyListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CMyListCtrl::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

}


void CMyListCtrl::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	if (nItem >= 0 && nItem < this->GetItemCount()) {
		int i = pNMListView->iItem;
		int j = pNMListView->iSubItem;
		CString str;
		str = this->GetItemText(i, j);
		//MessageBox(str);
		CString str_mon, str_day;
		str_mon = str.Left(str.Find("/") - 0);
		str_day = str.Right(str.GetLength() - str.Find("/") - 1);
		int month = _ttoi(str_mon);
		int day = _ttoi(str_day);				//获取该天的月和日
		InsDDL_Frame frameDlg;
		frameDlg.text_DDL_start_hour = _T("0");
		frameDlg.text_DDL_start_min = _T("00");
		frameDlg.text_DDL_end_hour = _T("0");
		frameDlg.text_DDL_end_min = _T("00");
		SYSTEMTIME current;
		GetLocalTime(&current);
		frameDlg.date.year = current.wYear;//年！
		frameDlg.date.month = month;
		frameDlg.date.day = day;
		if (frameDlg.DoModal() != IDOK) {
			return;
		}
		//MessageBox(str_mon);
		DDL ddl;
		ddl.text = frameDlg.text_about_DDL;
		ddl.type = frameDlg.text_DDL_type;
		ddl.year = frameDlg.date.year;
		ddl.month = frameDlg.date.month;
		ddl.day = frameDlg.date.day;
		ddl.alarm.year = ddl.year;
		ddl.alarm.month = ddl.month;
		ddl.alarm.day = ddl.day;
		ddl.pre_alarm = true;

		ddl.start.hour = _ttoi(frameDlg.text_DDL_start_hour);
		if (frameDlg.text_DDL_start_min == "00") {
			ddl.start.min = 0;
		}
		else
			ddl.start.min = _ttoi(frameDlg.text_DDL_start_min);
		ddl.end.hour = _ttoi(frameDlg.text_DDL_end_hour);
		if (frameDlg.text_DDL_end_min == "00") {
			ddl.end.min = 0;
		}
		else
			ddl.end.min = _ttoi(frameDlg.text_DDL_end_min);

		ddl.alarm = getAlarm(ddl, frameDlg.text_pre_alarm);

		myDDL.push_back(ddl);
		if (ddl.pre_alarm == true)
			myAlarm.push_back(ddl.alarm);

		//需要更新数据
		//读入文件 : ddl.text
		//同步数据到树状列表的对话框
	}
	*pResult = 0;
}

/*************
alarm:year, month, day, hour, min
**************/


Alarm CMyListCtrl::getAlarm(DDL& ddl,CString str)
{
	Alarm alarm;
	//初始化;
	alarm.time.hour = ddl.start.hour;
	alarm.time.min = ddl.start.min;
	alarm.month = ddl.month;
	alarm.year = ddl.year;
	alarm.day = ddl.day;
	alarm.text = ddl.text;
	//7天，年是否要往前推，月是否要往前推
	if (str == "7 days ago") {
		alarm.time.hour = ddl.start.hour;
		alarm.time.min = ddl.start.min;
		alarm.month = ddl.month;
		alarm.year = ddl.year;
		if (ddl.day <= 7) {
			if (ddl.month == 1) {
				alarm.year -= 1;
				alarm.month = 12;
				alarm.day = 31 - (7 - ddl.day);
			}
			if (ddl.month == 2 || ddl.month == 4 || ddl.month == 6 || ddl.month == 8 || ddl.month == 9 || ddl.month == 11) {
				alarm.month -= 1;
				alarm.day = 31 - (7 - ddl.day);
			}
//**********			//这是平年的专属版本
			if (ddl.month == 3) {
				alarm.month -= 1;
				alarm.day = 28 - (7 - ddl.day);
			}
			if (ddl.month == 5 || ddl.month == 7 || ddl.month == 10 || ddl.month == 12){
				alarm.month -= 1;
				alarm.day = 30 - (7 - ddl.day);
			}
		}
		else {
		//	alarm.month = ddl.month;
			alarm.day = ddl.day - 7;
		}
	}
	//一天
	if (str == "24 hours ago") {
		alarm.time.hour = ddl.start.hour;
		alarm.time.min = ddl.start.min;
		alarm.year = ddl.year;
		if (ddl.day == 1) {
			if (ddl.month == 1) {
				alarm.month = 12;
				alarm.day = 31;
				alarm.year -= 1;
			}
			else {
			alarm.month -= 1;
			alarm.day = lastDayOfLastMonth(ddl.month, ddl.day);
			}
		}
		else {
		alarm.month = ddl.month;
		alarm.day = ddl.day - 1;
		}
	}
	//12 hours
	if (str == "12 hours ago") {
		if (ddl.start.hour >= 12) {
			alarm.time.hour = ddl.start.hour - 12;
		}
		else {
			if (ddl.day > 1)
				alarm.day = ddl.day - 1;
			else
				alarm.day = lastDayOfLastMonth(ddl.month, ddl.day);
			alarm.time.hour = 24 - (12 - ddl.start.hour);
		}
	}
	//60 mins ago
	if (str == "60 mins ago") {
		alarm.time.hour = ddl.start.hour - 1;
	}
	if (str == "30 mins ago") {
		if (ddl.start.min >= 30) {
			alarm.time.min = ddl.start.min - 30;
		}
		else
		{
			alarm.time.hour = ddl.start.hour - 1;
			alarm.time.min = 60 - (30 - ddl.start.min);
		}
	}
	if (str == "15 mins ago") {
		if (ddl.start.min >= 15) {
			alarm.time.min = ddl.start.min - 15;
		}
		else
		{
			alarm.time.hour = ddl.start.hour - 1;
			alarm.time.min = 60 - (15 - ddl.start.min);
		}
	}
	if (str == "5 mins ago") {
		if (ddl.start.min >= 5) {
			alarm.time.min = ddl.start.min - 5;
		}
		else
		{
			alarm.time.hour = ddl.start.hour - 1;
			alarm.time.min = 60 - (5 - ddl.start.min);
		}
	}
	//if (str == "0 mins ago") {
	//
	//}
	if (str == "never") {
		ddl.pre_alarm = false;
	}
	return alarm;
}

int CMyListCtrl::lastDayOfLastMonth(const int month, const int day)
{
	// TODO: 在此处添加实现代码.
	if (month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11){
		return 31;
	}
	if (month == 5 || month == 7 || month == 10 || month == 12) {
		return 30;
	}
	if (month == 3)
		return 28;
}
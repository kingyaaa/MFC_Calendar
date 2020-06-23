#include "pch.h"
#include "CMyListCtrl.h"


void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  ������Ĵ����Ի���ָ����
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	LVITEM lvi = { 0 };
	lvi.mask = LVIF_STATE;
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
	lvi.iItem = lpDrawItemStruct->itemID;
	BOOL bGet = GetItem(&lvi);
	//������ʾ
	BOOL bHighlight = ((lvi.state & LVIS_DROPHILITED) || ((lvi.state & LVIS_SELECTED) && ((GetFocus() == this) || (GetStyle() & LVS_SHOWSELALWAYS))));
	//���ı�����
	CRect rcBack = lpDrawItemStruct->rcItem;//������Ҫ���Ƶ��ı���������Ϊһ����Ԫ��
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
		//д�ı�
		CString szText;
		int nCollumn = GetHeaderCtrl()->GetItemCount();//����
		for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++) {
			//ѭ���õ��ı�
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
	m_nRowHeight = nHeight; //���û������Ĵ��룬���ò�������Ч 
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CMyListCtrl::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

}


void CMyListCtrl::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		int day = _ttoi(str_day);				//��ȡ������º���
		InsDDL_Frame frameDlg;
		frameDlg.text_DDL_start_hour = _T("0");
		frameDlg.text_DDL_start_min = _T("00");
		frameDlg.text_DDL_end_hour = _T("0");
		frameDlg.text_DDL_end_min = _T("00");
		SYSTEMTIME current;
		GetLocalTime(&current);
		frameDlg.date.year = current.wYear;//�꣡
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

		//��Ҫ��������
		//�����ļ� : ddl.text
		//ͬ�����ݵ���״�б�ĶԻ���
	}
	*pResult = 0;
}

/*************
alarm:year, month, day, hour, min
**************/


Alarm CMyListCtrl::getAlarm(DDL& ddl,CString str)
{
	Alarm alarm;
	//��ʼ��;
	alarm.time.hour = ddl.start.hour;
	alarm.time.min = ddl.start.min;
	alarm.month = ddl.month;
	alarm.year = ddl.year;
	alarm.day = ddl.day;
	alarm.text = ddl.text;
	//7�죬���Ƿ�Ҫ��ǰ�ƣ����Ƿ�Ҫ��ǰ��
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
//**********			//����ƽ���ר���汾
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
	//һ��
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
	// TODO: �ڴ˴����ʵ�ִ���.
	if (month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11){
		return 31;
	}
	if (month == 5 || month == 7 || month == 10 || month == 12) {
		return 30;
	}
	if (month == 3)
		return 28;
}
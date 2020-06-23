
// MFCApplicationGoodLuckDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationGoodLuck.h"
#include "MFCApplicationGoodLuckDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationGoodLuckDlg 对话框



CMFCApplicationGoodLuckDlg::CMFCApplicationGoodLuckDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONGOODLUCK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationGoodLuckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_CAL_LIST, myListCtrl);
	//  DDX_Control(pDX, IDC_CAL_LIST, m_MyListCtrl);
	DDX_Control(pDX, IDC_CAL_LIST, m_MyListCtrl);
}

BEGIN_MESSAGE_MAP(CMFCApplicationGoodLuckDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_CAL_LIST, &CMFCApplicationGoodLuckDlg::OnLvnItemchangedCalList)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMFCApplicationGoodLuckDlg 消息处理程序

BOOL CMFCApplicationGoodLuckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//m_MyListCtrl.SetRowHeight(60);
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString strDate;
	strDate.Format("%d月%d日", st.wMonth, st.wDay);
	
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_MyListCtrl.GetClientRect(&rect);
	m_MyListCtrl.SetRowHeight(rect.Height() / 5);
	//m_MyListCtrl.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT,
	//	rect, this, IDC_CAL_LIST);
	// 为列表视图控件添加全行选中和栅格风格   
	m_MyListCtrl.SetExtendedStyle(m_MyListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列   
	m_MyListCtrl.InsertColumn(0, _T("1"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_MyListCtrl.InsertColumn(1, _T("2"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_MyListCtrl.InsertColumn(2, _T("3"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_MyListCtrl.InsertColumn(3, _T("4"), LVCFMT_CENTER, rect.Width() / 4, 3);
	//m_list
	// 在列表视图控件中插入列表项，并设置列表子项文本   
	
	for(int i = 0;i < 5; i++){
		for (int j = 0; j < 4; j++) {
			CString str;
			CString strTime = GetDate(st.wYear,st.wMonth, st.wDay, i, j, 4);
			CString strText;
			vector<DDL>::iterator it;
			//for (it = m_MyListCtrl.myDDL.begin(); it != m_MyListCtrl.myDDL.end(); it++) {
				//if()
			//}
			if (j == 0){//是首列
				m_MyListCtrl.InsertItem(i, strTime);
			}
			else {
				m_MyListCtrl.SetItemText(i, j, strTime);
			}
		}
	}
	m_MyListCtrl.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CMFCApplicationGoodLuckDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplicationGoodLuckDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplicationGoodLuckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CMFCApplicationGoodLuckDlg::OnLvnItemchangedCalList(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}


CString CMFCApplicationGoodLuckDlg::GetDate(int year, int month, int day, int i, int j,int k)
{
	CString str;
	int m = month;
	int d = day;
	int y = year;

	int dis = i * 4 + j;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10) {
		if (day + dis > 31) {
			m += 1;
			d = day + dis - 31;
		}
		else {
			d = day + dis;
		}
	}
	if (month == 2)
	{
		if (day + dis > 28) {
			m += 1;
			d = day + dis - 28;
		}
		else {
			d = day + dis;
		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day + dis > 30) {
			m += 1;
			d = day + dis - 30;
		}
		else {
			d = day + dis;
		}
	}
	if (month == 12) {
		if (day + dis > 31) {
			m = 1;
			d = day + dis - 31;
			y += 1;
		}
		else {
			d = day + dis;
		}
	}
	str.Format("%d/%d", m, d);
	return str;
}

//void CMFCApplicationGoodLuckDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonDblClk(nFlags, point);
//}


void CMFCApplicationGoodLuckDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME current;
	GetLocalTime(&current);
	vector<Alarm>::iterator it;
	for (it = m_MyListCtrl.myAlarm.begin(); it != m_MyListCtrl.myAlarm.end(); it++) {
		if ((*it).year == current.wYear && (*it).month == current.wMonth && (*it).day == current.wDay && (*it).time.hour == current.wHour && (*it).time.min == current.wMinute)
			MessageBox((*it).text, _T("你有DLL到期提醒，请注意查收"));
	}
	CDialogEx::OnTimer(nIDEvent);
}



int CMFCApplicationGoodLuckDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	SetTimer(1, 1000 * 60, NULL);
	return 0;
}

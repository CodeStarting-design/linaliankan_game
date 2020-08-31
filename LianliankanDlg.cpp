
// LianliankanDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Lianliankan.h"
#include "LianliankanDlg.h"
#include "afxdialogex.h"
#include"CGameDlg.h"
#include"CBasicGame.h"
#include"CEasyGame.h"

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


// CLianliankanDlg 对话框



CLianliankanDlg::CLianliankanDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIANLIANKAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLianliankanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLianliankanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON2, &CLianliankanDlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON5, &CLianliankanDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CLianliankanDlg::OnClickedButtonBasic)
	ON_BN_CLICKED(IDC_BUTTON_LESURE, &CLianliankanDlg::OnBnClickedButtonLesure)
END_MESSAGE_MAP()


// CLianliankanDlg 消息处理程序

BOOL CLianliankanDlg::OnInitDialog()
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
	InitBackground();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLianliankanDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLianliankanDlg::OnPaint()
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
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		/*
		//创建字体
		CFont font;
		font.CreatePointFont(200, _T("Courier Ner"));

		//将字体选进DC
		CFont* oldFont;
		oldFont = dc.SelectObject(&font);

		//设置字体颜色
		dc.SetTextColor(RGB(0, 0, 255));

		//设置欢迎语背景颜色
		dc.SetBkColor(RGB(255, 255, 255));

		CRect rect;
		GetClientRect(rect);

		//绘制欢迎语
		CString strText = _T("Welcome to LLK_Game");

		//获取字符串的宽度和高度
		CSize size;
		size = dc.GetTextExtent(strText, strText.GetLength());

		//欢迎语起点坐标
		int x = (rect.Width() - size.cx) / 2;
		int y = (rect.Height() - size.cy) / 2;
		dc.TextOut(x, y, strText);
		*/

		dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLianliankanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLianliankanDlg::InitBackground()
{
	//加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmap(IDB_MAIN_BG);
	//创建兼容DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);

	//将位图选进DC
	m_dcMem.SelectObject(&bmpMain);
}






void CLianliankanDlg::OnClickedButtonBasic()
{
	// TODO: 在此添加控件通知处理程序代码
	CBasicGame* basicgame = new CBasicGame;
	FLAG flag;
	flag.bTimer = true;
	flag.bProp = false;
	flag.bScore = false;
	flag.szTitle = _T("基本模式");
	basicgame->SetGameFlag(flag);
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.SetGameModel(basicgame);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLianliankanDlg::OnBnClickedButtonLesure()
{
	// TODO: 在此添加控件通知处理程序代码
	CEasyGame* easygame = new CEasyGame;
	FLAG flag;
	flag.bTimer = false;
	flag.bProp = true;
	flag.bScore = true;
	flag.szTitle = _T("休闲模式");
	easygame->SetGameFlag(flag);
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.SetGameModel(easygame);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}

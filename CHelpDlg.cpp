// CHelpDlg.cpp: 实现文件
//

#include "pch.h"
#include "Lianliankan.h"
#include "CHelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	iVscrollPos = 0;
}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_CREATE()
	ON_STN_CLICKED(IDC_STATIC_COPYRIGHT, &CHelpDlg::OnStnClickedStaticCopyright)
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序


void CHelpDlg::InitBackground()
{
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcBG.SelectObject(bmp);


	//创建与视频内存兼容的内存
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 508, 1024);

	//将位图资源选入DC
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.SetBkMode(TRANSPARENT);
	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 508, 1024, &m_dcBG, 0, 0, SRCCOPY);

	UpdateWindow();
}


BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitBackground();
	UpdateHelp(0);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CHelpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 508, 1024, &m_dcMem, 0, 0, SRCCOPY);
}


void CHelpDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int curpos = GetScrollPos(SB_VERT);
	switch (nSBCode)
	{
	case SB_LINEUP:

		curpos--;
		break;
	case SB_LINEDOWN:
		curpos++;
		break;
	case SB_PAGEUP:
		curpos -= 20;
		break;
	case SB_PAGEDOWN:
		SCROLLINFO   info;
		GetScrollInfo(SB_HORZ, &info, SIF_ALL);
		curpos += 20;
		break;
	case SB_TOP:
		curpos = 0;
		break;
	case SB_BOTTOM:
		curpos = 475;
		break;
	case SB_THUMBPOSITION:
		curpos = nPos;
		break;
	default:
		break;
	}
	SetScrollPos(SB_VERT, curpos, TRUE);
	UpdateHelp(curpos);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
void CHelpDlg::UpdateHelp(int nPos)
{
	m_dcMem.BitBlt(0, 0, 508, 1024, NULL, 0, 0, WHITENESS);
	m_dcMem.BitBlt(0, 0, 508, 1024, &m_dcBG, 0, nPos, SRCCOPY);
	Invalidate(FALSE);
}

int CHelpDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetScrollRange(SB_VERT, 0, 475, FALSE);
	SetScrollPos(SB_VERT, iVscrollPos, TRUE);
	return 0;
}


void CHelpDlg::OnStnClickedStaticCopyright()
{
	// TODO: 在此添加控件通知处理程序代码
}

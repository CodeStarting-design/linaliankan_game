// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "Lianliankan.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include"CGameControl.h"
#include"CHelpDlg.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG1, pParent)
{
	m_hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);

	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;
	//单个图片元素大小设置
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;
	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * COL_NUM;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * ROW_NUM;

	m_bFirstpoint = true;
	m_bPlaying = false;
	m_bPause = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIME_CONTROL, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_REMIND, &CGameDlg::OnClickedButtonRemind)
	ON_BN_CLICKED(IDC_BUTTON_REMAKE, &CGameDlg::OnClickedButtonRemake)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CGameDlg::OnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_ASS, &CGameDlg::OnBnClickedButtonAss)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CGameDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_PROPS, &CGameDlg::OnBnClickedButtonProps)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackground(void)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	//加载图片资源
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcBG.SelectObject(bmp);


	//创建与视频内存兼容的内存
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);

	//将位图资源选入DC
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.SetBkMode(TRANSPARENT);
	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	UpdateWindow();
	

}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon, TRUE);//设置大图标
	SetIcon(m_hIcon, FALSE);//设置小图标;
	//让窗口作为应用程序窗口显示
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);
	FLAG m_flag;
	m_flag = m_gameControl->GetGameFlag();
	if (m_flag.szTitle == "基本模式")
	{
		//窗口标题的设置
		this->SetWindowTextW(_T("欢乐连连看—基本模式"));
		this->GetDlgItem(IDC_BUTTON_PROPS)->ShowWindow(m_flag.bScore);
		this->GetDlgItem(IDC_STATIC_GRADE)->ShowWindow(m_flag.bProp);
	}
	if (m_flag.szTitle == "休闲模式")
	{
		//窗口标题的设置
		this->SetWindowTextW(_T("欢乐连连看—休闲模式"));
		this->GetDlgItem(IDC_BUTTON_PROPS)->EnableWindow(FALSE);//道具不可使用
		this->GetDlgItem(IDC_TIME_CONTROL)->ShowWindow(m_flag.bTimer);
	}
	
	//对背景初始化
	InitBackground();
	InitElment();
	this->GetDlgItem(IDC_BUTTON_REMIND)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BUTTON_REMAKE)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

}
void CGameDlg::InitElment(void)
{
	//获取当前对话框的视频内存
	CClientDC dc(this);
	//加载图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\an_elment1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存
	m_dcElement.CreateCompatibleDC(&dc);

	//将位图资源选入DC

	m_dcElement.SelectObject(hBmpBG);

	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\an_mask1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存
	m_dcMask.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);

	//加载暂停图片资源
	HANDLE hPuase = ::LoadImage(NULL, _T("theme\\picture\\an_puase.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存
	m_dcPause.CreateCompatibleDC(&dc);

	//将位图资源选入DC

	m_dcPause.SelectObject(hPuase);

}

void CGameDlg::UpdateMap(void) {//根据图中信息更新图片元素的显示
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i <ROW_NUM; i++) {
		for (int j = 0; j < COL_NUM; j++) {
			int nInfo = m_gameControl->GetElement(i, j);//根据行列取出元素
            //先进行与运算再进行或运算
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, m_gameControl->GetElement(i,j) * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_gameControl->GetElement(i, j) * nElemH, SRCAND);
		}
	}
}
void CGameDlg::OnClickedButtonStart()
{
	//初始化游戏地图
	m_gameControl->StartGame();
	m_gameControl->m_nGrade = 0;
	m_bPlaying = true;
	//将开始按钮设置为无法被按下
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	if (m_gameControl->GetGameFlag().szTitle == "基本模式") {
		this->GetDlgItem(IDC_BUTTON_REMIND)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_BUTTON_REMAKE)->EnableWindow(TRUE);
	}
	this->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	//更新游戏地图
	UpdateMap();
	Invalidate(FALSE);
    //初始化进度条
	m_GameProgress.SetRange(0, 60 * 5);//初始化范围
	m_GameProgress.SetStep(-1);   //初始步数值
	m_GameProgress.SetPos(60 * 5);//设置初始值
	//添加计时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
	if (m_gameControl->GetGameFlag().bTimer )
	{
		DrawGameTime();
	}
	else {
		DrawGameGrade();
	}
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > ROW_NUM-1|| nCol > COL_NUM-1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstpoint) {//第一个点
		//绘制提示框，保存坐标
		DrawTipFrame(nRow, nCol);
		m_gameControl->SetFirstPoint(nRow, nCol);
		//在控制层中保存了点击点的信息
	}
	else {       //第二个点
		DrawTipFrame(nRow, nCol);
		m_gameControl->SetSecPoint(nRow, nCol);

		//获得子路径
		Vertex avPath[MAX_VERTEX_NUM];
		int nVex;
		//判断是否是相同图片
		if (m_gameControl->Link(avPath,nVex)) {//判断是否可以相连
			if (m_gameControl->GetGameFlag().szTitle == "休闲模式") {
				m_gameControl->PlusGrade(10);
				if (m_gameControl->GetnProp() != 0) {
					this->GetDlgItem(IDC_BUTTON_PROPS)->EnableWindow(TRUE);
				}
				if (m_gameControl->GetGrade() > 20) {
					this->GetDlgItem(IDC_BUTTON_REMIND)->EnableWindow(TRUE);
				}
				if (m_gameControl->GetGrade() > 50) {
					this->GetDlgItem(IDC_BUTTON_REMAKE)->EnableWindow(TRUE);
				}
				if (m_gameControl->GetGrade() % 100 == 0) {
					m_gameControl->plusnProp();
				}
				DrawGameGrade();
			}
			//画提示线
			
			DrawTipLine(avPath,nVex);
			//将点设为-1，实现消去
		
			UpdateMap();

		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
		//进行胜负判断
		JudgeWin();

	}
	m_bFirstpoint = !m_bFirstpoint;

}
void CGameDlg::DrawTipFrame(int nRow, int nCol) {//绘制画框
	CClientDC dc(this);//获取到当前DC
	CBrush brush(RGB(233, 43, 43));//构造画刷
	CRect rtTipFrame;
	//确定区域
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;

	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::DrawTipLine(Vertex avPath[],int nVex)//绘制连接线
{
	//获取DC
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);
	//绘制连接线
	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	for (int i = 1; i < nVex; i++) {
		int y = 0;
		dc.LineTo(m_ptGameTop.x + avPath[ i].col * m_sizeElem.cx + m_sizeElem.cx / 2, 
			m_ptGameTop.y + avPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}


void CGameDlg::OnClickedButtonRemind()
{
	if (!m_bPlaying) {
		return;
	}
	Vertex avPath[MAX_VERTEX_NUM];
	int nVertex;
	m_gameControl->Help(avPath, nVertex);
	DrawTipFrame(avPath[0].row, avPath[0].col);
	DrawTipFrame(avPath[nVertex-1].row, avPath[nVertex-1].col);
	Sleep(500);
   //绘制连通线
	DrawTipLine(avPath, nVertex);
	if (m_gameControl->GetGameFlag().szTitle == "休闲模式") {
		m_gameControl->MinusGrade();
		m_gameControl->MinusGrade();
		if (m_gameControl->GetGrade() < 20) {
			this->GetDlgItem(IDC_BUTTON_REMIND)->EnableWindow(FALSE);
		}
		if (m_gameControl->GetGrade() < 50) {
			this->GetDlgItem(IDC_BUTTON_REMAKE)->EnableWindow(FALSE);
		}
		DrawGameGrade();
	}
	Sleep(500);
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::OnClickedButtonRemake() 
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bPlaying) {
		return;
	}
	//对图中的信息进行重排
	m_gameControl->ResetGame();
	//对游戏地图更新
	UpdateMap();
	if (m_gameControl->GetGameFlag().szTitle == "休闲模式") {
		for (int i = 0; i < 5; i++) {
			m_gameControl->MinusGrade();
		}
		if (m_gameControl->GetGrade() < 20) {
			this->GetDlgItem(IDC_BUTTON_REMIND)->EnableWindow(FALSE);
		}
		if (m_gameControl->GetGrade() < 50) {
			this->GetDlgItem(IDC_BUTTON_REMAKE)->EnableWindow(FALSE);
		}
		DrawGameGrade();
	}
	//生成游戏地图
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 首先进行胜负判断
	
	JudgeWin();

	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && !m_bPause) {
		//游戏时间减一秒
		m_GameProgress.StepIt();
		if (m_gameControl->GetGameFlag().bTimer == true)
		{
			DrawGameTime();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::DrawGameTime()
{
	CClientDC dc(this);
	CFont font;
	CFont* oldfont;
	font.CreatePointFont(130, _T("Arial"), &dc);
	dc.SelectObject(font);
	oldfont = dc.SelectObject(&font);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.SetBkColor(RGB(206, 190, 190));
	CString str;
	str.Format(_T("%.3d"), m_GameProgress.GetPos());
	dc.TextOut(637, 532, str);
	dc.SelectObject(oldfont);
}


void CGameDlg::JudgeWin()
{
	BOOL  GameStatus = m_gameControl->IsWin(m_GameProgress.GetPos());
	if (GameStatus == GAME_PLAY) {//游戏继续进行
		return;
	}
	else {
		//改变状态标识符
		m_bPlaying = false;
		//关闭计时器
		KillTimer(PLAY_TIMER_ID);
		//提示获胜
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (GameStatus == GAME_SUCCESS) {//游戏获胜时
			MessageBox(_T("恭喜你，获胜！"), strTitle);
		}
		else if ((GameStatus == GAME_LOSE)) {
			MessageBox(_T("很遗憾，时间到了"), strTitle);
			KillTimer(PLAY_TIMER_ID);//结束计时
		}
		//将开始游戏按钮设置为可以点击
		this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);

	}

}


void CGameDlg::OnClickedButtonStop()//暂停游戏响应函数
{
	if (m_bPlaying == false)
	{
		return;
	}
	if (m_bPause == false)
	{
		//使得提示重排功能不可用
		this->GetDlgItem(IDC_BUTTON_REMIND)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_REMAKE)->EnableWindow(FALSE);
		//加载遮罩图片
		m_dcMem.BitBlt(50, 50, 650, 415, &m_dcPause, 0, 0, SRCCOPY);
		InvalidateRect(m_rtGameRect, FALSE);
		//修改文字内容
		this->SetDlgItemText(IDC_BUTTON_STOP, _T("继续游戏"));

	}
	else if (m_bPause == true)
	{
		//恢复提示重排功能
		
		this->GetDlgItem(IDC_BUTTON_REMIND)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_BUTTON_REMAKE)->EnableWindow(TRUE);
		this->SetDlgItemText(IDC_BUTTON_STOP, _T("暂停游戏"));
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
	m_bPause = !m_bPause;
}


void CGameDlg::OnBnClickedButtonAss()
{
	//创建新的对话框显示信息
	CHelpDlg dlg;
	dlg.DoModal();
}


void CGameDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	
}
void CGameDlg::SetGameModel(CGameControl* gameControl)
{
	m_gameControl = gameControl;
}
void CGameDlg::DrawGameGrade()
{
	int nGrade = m_gameControl->GetGrade();
	CClientDC dc(this);
	CFont font;
	CFont* oldfont;
	font.CreatePointFont(200, _T("Arial"), &dc);
	dc.SelectObject(font);
	oldfont = dc.SelectObject(&font);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.SetBkColor(RGB(225, 224, 242));
	CString str;
	str.Format(_T("%.4d"), nGrade);
	dc.TextOut(701, 385, str);
	dc.SelectObject(oldfont);
}

void CGameDlg::OnBnClickedButtonProps()
{
	// TODO: 在此添加控件通知处理程序代码
	m_gameControl->PropLink();
	if (m_gameControl->GetnProp() == 0)
	{
		m_bProp = false;
	}
	
		DrawGameGrade();
	this->GetDlgItem(IDC_BUTTON_PROPS)->EnableWindow(m_bProp);
	UpdateMap();
	Sleep(200);
	InvalidateRect(m_rtGameRect, FALSE);

}

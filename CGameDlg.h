#pragma once
#include"global.h"
#include"CGameControl.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CDC m_dcMem;       //内存DC
	HICON m_hIcon;     //系统图标
	CDC m_dcElement;   //元素
	CDC m_dcMask;      //掩码DC
	CDC m_dcBG;        //背景DC  
	CDC m_dcPause;
	CPoint m_ptGameTop;   //游戏区起点
	CSize m_sizeElem;     //图片大小
	CRect m_rtGameRect;   //游戏区域大小
	bool m_bProp;//是否可使用道具
	bool m_bFirstpoint;
	bool m_bPlaying;     //是否正在游戏标识符
	bool m_bPause;      //游戏是否暂停
	CGameControl *m_gameControl;   //创建游戏控制对象
	


protected:
	void InitBackground(void);
	void InitElment();
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[], int nVex);
public:
	void DrawGameGrade();//显示积分
	void SetGameModel(CGameControl* gameControl);//设置游戏模式
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonRemind();
	afx_msg void OnClickedButtonRemake();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	void DrawGameTime();
public:
	void JudgeWin();
	afx_msg void OnClickedButtonStop();
	afx_msg void OnBnClickedButtonAss();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonProps();
};

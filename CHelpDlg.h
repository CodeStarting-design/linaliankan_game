#pragma once


// CHelpDlg 对话框

class CHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDlg)

public:
	CHelpDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHelpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HELP };
#endif

protected:
	CDC m_dcBG;
	CDC m_dcMem;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	void InitBackground();
public:
	int iVscrollPos;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void UpdateHelp(int nPos);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnStnClickedStaticCopyright();
};


// 上机作业Dlg.h : 头文件
//

#pragma once
#include "atltypes.h"
#include"Ball.h"
#include"Box.h"


// C上机作业Dlg 对话框
class C上机作业Dlg : public CDialogEx
{
// 构造
public:
	C上机作业Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
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
	CDC* canvasDC;
	bool m_StartDraw;
	bool m_StartGame;
	CPoint m_ShiftPoint;
	Box** boxes;
	int m_colNumOfBoxes;
	int m_rowNumOfBoxes;
	int m_scaleOfBox;
	Ball* ball;
	void InitCanvas();
	void UpdateBox(int rowIndex, int colIndex);
	void UpdateBall(int rowMove, int colMove);
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


// week10 L04Dlg.h : 头文件
//

#pragma once
#include "atltypes.h"


// Cweek10L04Dlg 对话框
class Cweek10L04Dlg : public CDialogEx
{
// 构造
public:
	Cweek10L04Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WEEK10L04_DIALOG };

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
	bool m_StartDraw;
	CPoint m_PrevPoint;
	CPoint m_ShiftPoint;
//	afx_msg void OnNcXButtonDown(short nFlags, UINT nButton, CPoint point);
//	afx_msg void OnNcXButtonUp(short nFlags, UINT nButton, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
};

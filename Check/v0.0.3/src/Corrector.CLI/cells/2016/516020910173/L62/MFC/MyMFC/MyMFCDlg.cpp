
// MyMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyMFC.h"
#include "MyMFCDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyMFCDlg 对话框




CMyMFCDlg::CMyMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyMFCDlg::IDD, pParent)
	, canvasDC(NULL)
	, m_StartDraw(false)
	, m_StartGame(false)
	, m_ShiftPoint(0)
	, boxes(NULL)
	, m_colNumOfBoxes(0)
	, m_rowNumOfBoxes(0)
	, m_scaleOfBoxes(0)
	, ball(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_LBUTTONDBLCLK()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_BN_CLICKED(IDC_BUTTON2, &CMyMFCDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON1, &CMyMFCDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyMFCDlg 消息处理程序

BOOL CMyMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//给成员变量赋初值
	CWnd*pCanvasWnd=GetDlgItem(IDC_CANVAS);
	canvasDC=pCanvasWnd->GetDC();
	pCanvasWnd->Detach();
	m_scaleOfBoxes=10;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyMFCDlg::OnPaint()
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
		//获取Canvas在对话框中的位置
		CWnd*pCanvasWnd=GetDlgItem(IDC_CANVAS);
		CRect rect;
	    pCanvasWnd->GetWindowRect(&rect);
	    ScreenToClient(rect);
	    m_ShiftPoint.x=rect.left;
		m_ShiftPoint.y=rect.top;
		//初始化小球
		ball=new Ball();
		ball->m_rowIndex=0;
		ball->m_colIndex=0;
		//获取绘制区域并计算方格数
		pCanvasWnd->GetClientRect(&rect);
		m_colNumOfBoxes=rect.Width()/m_scaleOfBoxes-1;
		m_rowNumOfBoxes=rect.Height()/m_scaleOfBoxes-1;
		//初始化方格
		boxes=new Box*[m_rowNumOfBoxes];
		for(int i=0;i<m_rowNumOfBoxes;i++)
		{
			boxes[i]=new Box[m_colNumOfBoxes];
			for(int j=0;j<m_colNumOfBoxes;j++)
			{
				boxes[i][j].top=i*m_scaleOfBoxes+1;
				boxes[i][j].bottom=(i+1)*m_scaleOfBoxes+2;
				boxes[i][j].left=j*m_scaleOfBoxes+1;
				boxes[i][j].right=(j+1)*m_scaleOfBoxes+2;
			}
		}
		//标记起始点和终止点
		boxes[0][0].m_isEnd=true;
		boxes[m_rowNumOfBoxes-1][m_colNumOfBoxes-1].m_isEnd=true;
		//调用InitCanvas函数初始化游戏
		InitCanvas();
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyMFCDlg::InitCanvas(void)
{
	//设置并更换画布
	CBrush brush(RGB(255,255,255));
	auto oldBrush=canvasDC->SelectObject(&brush);
	oldBrush->DeleteObject();
	//重新设置启动游戏开关
	m_StartGame=false;
	//重新绘制游戏界面
	for(int i=0;i<m_rowNumOfBoxes;i++)
	{
		for(int j=0;j<m_colNumOfBoxes;j++)
		{
			boxes[i][j].m_isSelected=false;
			canvasDC->Rectangle(boxes[i][j]);
		}
	}
	//标记起始位置和终止位置
	CBrush greenBrush(RGB(0,255,0));
	canvasDC->FillRect(boxes[0][0].GetContent(),&greenBrush);
	canvasDC->FillRect(boxes[m_rowNumOfBoxes-1][m_colNumOfBoxes-1].GetContent(),&greenBrush);
		
}


void CMyMFCDlg::UpdateBox(int rowIndex, int colIndex)
{
   //创建红绿两种画刷
	CBrush rBursh(RGB(255,0,0));
	CBrush gBrush(RGB(0,255,0));
	//判断方格是否有效
	//若有效，则设方格状态为选中并将其填充相应颜色
	if(rowIndex>=0&&rowIndex<m_rowNumOfBoxes&&colIndex>=0&&colIndex<m_colNumOfBoxes)
	{
		boxes[rowIndex][colIndex].m_isSelected=true;
		if(boxes[rowIndex][colIndex].m_isEnd)
			canvasDC->FillRect(boxes[rowIndex][colIndex].GetContent(),&gBrush);
		else
			canvasDC->FillRect(boxes[rowIndex][colIndex].GetContent(),&rBursh);
	}
}


void CMyMFCDlg::UpdateBall(int rowMove, int colMove)
{
	if(m_StartGame)
	{
	    //更新小球位置
		int rowIndex=ball->m_rowIndex+rowMove;
		int colIndex=ball->m_colIndex+colMove;
		// 判断新位置是否有效
		if(rowIndex>=0&&rowIndex<m_rowNumOfBoxes&&colIndex>=0&&colIndex<m_colNumOfBoxes)
		{
			//创建并更新画刷
			CBrush blackBrush(RGB(0,0,0,));
			auto oldBrush=canvasDC->SelectObject(&blackBrush);
			oldBrush->DeleteObject();
			//调用UpdateBox函数更新方格状态
			UpdateBox(ball->m_rowIndex,ball->m_colIndex);
			//更新小球状态
			ball->m_rowIndex=rowIndex;
			ball->m_colIndex=colIndex;
			canvasDC->Ellipse(boxes[ball->m_rowIndex][ball->m_colIndex]);
			int choice=-1;
			//达到终点，弹出对话框
			if(rowIndex==m_rowNumOfBoxes-1&&colIndex==m_colNumOfBoxes-1)
			{
				choice=MessageBox(TEXT("成功达到目的地，游戏结束！\r\n是否重新开始？"),TEXT("恭喜你"),MB_OKCANCEL);
			}
			//游戏失败，弹出对话框
			else if(!boxes[rowIndex][colIndex].m_isSelected)
				choice=MessageBox(TEXT("失败，游戏结束\r\n是否重新开始"),TEXT("好遗憾"),MB_OKCANCEL);
			//根据对话框的选择 重新启动游戏 或退出
			if(choice==IDOK)
			{
				InitCanvas();
				return;
			}
			else if(choice==IDCANCEL)
				exit(-1);
		}
	}
}

//void CMyMFCDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonDblClk(nFlags, point);
//}
//
//
//void CMyMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//}
//
//
//void CMyMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonUp(nFlags, point);
//}


void CMyMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//关闭开始绘制的开关
	m_StartDraw=true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMyMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//关闭开始打开的开关
	m_StartDraw=false;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMyMFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//计算当前鼠标所在方格并更新方格
	if(m_StartDraw&&!m_StartGame)
	{
		auto rowIndex=(point.y-m_ShiftPoint.y)/m_scaleOfBoxes;
		auto colIndex=(point.x-m_ShiftPoint.x)/m_scaleOfBoxes;
		UpdateBox(rowIndex,colIndex);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


	void CMyMFCDlg::OnBnClickedButton2()
	{
		// TODO: 在此添加控件通知处理程序代码
		InitCanvas();
	}


	void CMyMFCDlg::OnBnClickedButton1()
	{
		// TODO: 在此添加控件通知处理程序代码
		CBrush brush(RGB(0,0,0));
		auto oldBrush=canvasDC->SelectObject(&brush);
		oldBrush->DeleteObject();
		//重置并绘制小球
		ball->m_rowIndex=0;
		ball->m_colIndex=0;
		canvasDC->Ellipse(boxes[ball->m_rowIndex][ball->m_colIndex]);
		m_StartGame=true;
	}


	BOOL CMyMFCDlg::PreTranslateMessage(MSG* pMsg)
	{
		if(pMsg->message==WM_KEYDOWN)
		{
			switch(pMsg->wParam)
			{
			case VK_UP:UpdateBall(-1,0);break;
			case VK_DOWN:UpdateBall(1,0);break;
			case VK_LEFT:UpdateBall(0,-1);break;
			case VK_RIGHT:UpdateBall(0,1);break;
			}
		}

		return CDialog::PreTranslateMessage(pMsg);
	}

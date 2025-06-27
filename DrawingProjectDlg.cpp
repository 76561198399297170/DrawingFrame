
// DrawingProjectDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DrawingProject.h"
#include "DrawingProjectDlg.h"
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


// CDrawingProjectDlg 对话框



CDrawingProjectDlg::CDrawingProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAWINGPROJECT_DIALOG, pParent)
	, m_draw_type(0)
	, m_draw_width(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawingProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_draw_width);
	DDV_MinMaxInt(pDX, m_draw_width, 1, 99);
	DDX_Radio(pDX, IDC_RADIO1, m_draw_type);
	DDV_MinMaxInt(pDX, m_draw_type, -1, 5);
}

BEGIN_MESSAGE_MAP(CDrawingProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDrawingProjectDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CDrawingProjectDlg::OnEnChangeEdit1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDrawingProjectDlg::OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_RADIO1, &CDrawingProjectDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CDrawingProjectDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO2, &CDrawingProjectDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &CDrawingProjectDlg::OnBnClickedRadio4)
END_MESSAGE_MAP()


// CDrawingProjectDlg 消息处理程序

BOOL CDrawingProjectDlg::OnInitDialog()
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
	this->m_draw_color = RGB(0, 0, 0);

	this->m_draw_width = 1;
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDrawingProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDrawingProjectDlg::OnPaint()
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
HCURSOR CDrawingProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDrawingProjectDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colorDlg(this->m_draw_color);// 传入参数为窗口默认初始颜色

	if (colorDlg.DoModal() == IDOK)// 判断对话框结束结果是否为“确定”
	{
		this->m_draw_color = colorDlg.GetColor();// 接收对话框选择结果值
	}
}
void CDrawingProjectDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CDrawingProjectDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == 1)// 点击下箭头
	{
		this->m_draw_width = max(this->m_draw_width - 1, 1);
	}
	else if (pNMUpDown->iDelta == -1)// 点击上箭头
	{
		this->m_draw_width = min(this->m_draw_width + 1, 99);
	}
	UpdateData(FALSE);

	this->OnEnChangeEdit1();
	*pResult = 0;
}

void CDrawingProjectDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_draw_type = 0;
}

void CDrawingProjectDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_draw_type = 1;
}

void CDrawingProjectDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_draw_type = 2;
}

void CDrawingProjectDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_draw_type = 3;
}

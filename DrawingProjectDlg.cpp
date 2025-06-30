
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
	, m_insert_str(_T(""))
	, m_text_size(20)
	, m_picture_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawingProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_draw_width);
	DDV_MinMaxInt(pDX, m_draw_width, 1, 100);

	DDX_Radio(pDX, IDC_RADIO1, m_draw_type);
	DDV_MinMaxInt(pDX, m_draw_type, 0, 3);

	DDX_Control(pDX, IDC_COMBO1, m_width_box);

	DDX_Text(pDX, IDC_EDIT2, m_insert_str);

	DDX_Text(pDX, IDC_EDIT3, m_text_size);
	DDV_MinMaxInt(pDX, m_text_size, 1, 100);
	DDX_Text(pDX, IDC_EDIT6, m_picture_path);
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
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDrawingProjectDlg::OnCbnSelchangeCombo1)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON2, &CDrawingProjectDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT2, &CDrawingProjectDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CDrawingProjectDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT6, &CDrawingProjectDlg::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON3, &CDrawingProjectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDrawingProjectDlg::OnBnClickedButton4)
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

	this->m_width_box.AddString(TEXT("粗细: 1"));
	this->m_width_box.AddString(TEXT("粗细: 2"));
	this->m_width_box.AddString(TEXT("粗细: 3"));
	this->m_width_box.AddString(TEXT("粗细: 5"));
	this->m_width_box.AddString(TEXT("粗细: 10"));
	this->m_width_box.SetCurSel(0);

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

void CDrawingProjectDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (this->m_width_box.GetCurSel())
	{
	case 1:
		this->m_draw_width = 2;
		break;
	case 2:
		this->m_draw_width = 3;
		break;
	case 3:
		this->m_draw_width = 5;
		break;
	case 4:
		this->m_draw_width = 10;
		break;
	case 0:
	default:
		this->m_draw_width = 1;
		break;
	}
	UpdateData(FALSE);

	this->OnEnChangeEdit1();
}

void CDrawingProjectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (this->m_insert_str != "") 
	{
		CClientDC dc(this);

		CPen pen(PS_SOLID, this->m_draw_width, this->m_draw_color);

		CFont font;
		font.CreateFont(
			this->m_text_size,			// 字体高度
			0,							// 字体宽度，0表示使用默认值
			0,							// 字体倾斜角
			0,							// 字体倾斜角
			this->m_draw_width,			// 字体粗细，使用变量计算
			FALSE,						// 字体是否为斜体
			FALSE,						// 字体是否有下划线
			0,							// 字体是否有删除线
			ANSI_CHARSET,				// 字体使用的字符集
			OUT_DEFAULT_PRECIS,			// 指定如何选择合适的字体
			CLIP_DEFAULT_PRECIS,		// 确定裁剪的精度
			DEFAULT_QUALITY,			// 怎么样跟选择的字体相符合
			DEFAULT_PITCH | FF_SWISS,	// 间距标志和属性标志
			_T("Arial")					// 字体的名称
		);

		CFont* oldFont = dc.SelectObject(&font);
		CPen* old_pen = dc.SelectObject(&pen);
		int oldBkMode = dc.GetBkMode();
		dc.SetBkMode(TRANSPARENT);

		dc.TextOutW(point.x, point.y, this->m_insert_str);

		dc.SetBkMode(oldBkMode);
		dc.SelectObject(old_pen);
		dc.SelectObject(oldFont);

		this->m_insert_str = "";
		font.DeleteObject();
		UpdateData(FALSE);

		OnEnChangeEdit2();
	}
	else if (this->m_picture_path != "")
	{
		CClientDC dc(this);

		CRect rect;
		GetClientRect(&rect);

		CImage img;
		img.Load(this->m_picture_path);
		img.BitBlt(dc, point.x, point.y, rect.Width(), rect.Height(), 0, 0);
		img.Destroy();

		this->m_picture_path = "";
		UpdateData(FALSE);

		OnEnChangeEdit6();
	}
	else
	{
		this->is_drawing = true;
		this->_last_place = point;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDrawingProjectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!this->is_drawing) return;

	this->is_drawing = false;
	if (this->m_draw_type == 1)// 直线
	{
		CClientDC dc(this);

		CPen pen(PS_SOLID, this->m_draw_width, this->m_draw_color);

		CPen* old_pen = dc.SelectObject(&pen);

		dc.MoveTo(this->_last_place.x, this->_last_place.y);
		dc.LineTo(point.x, point.y);

		dc.SelectObject(old_pen);
	}
	else if (this->m_draw_type == 2)// 椭圆
	{
		CClientDC dc(this);

		CPen pen(PS_SOLID, this->m_draw_width, this->m_draw_color);
		CBrush* brush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

		CPen* old_pen = dc.SelectObject(&pen);
		CBrush* old_brush = dc.SelectObject(brush);

		dc.Ellipse(this->_last_place.x, this->_last_place.y, point.x, point.y);

		dc.SelectObject(old_pen);
		dc.SelectObject(old_brush);
	}
	else if (this->m_draw_type == 3)//矩形
	{
		CClientDC dc(this);

		CPen pen(PS_SOLID, this->m_draw_width, this->m_draw_color);
		CBrush* brush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

		CPen* old_pen = dc.SelectObject(&pen);
		CBrush* old_brush = dc.SelectObject(brush);

		dc.Rectangle(this->_last_place.x, this->_last_place.y, point.x, point.y);

		dc.SelectObject(old_pen);
		dc.SelectObject(old_brush);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CDrawingProjectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (this->m_draw_type)
	{
	case 0:
	{
		if (this->is_drawing)
		{
			CClientDC dc(this);

			CPen pen(PS_SOLID, this->m_draw_width, this->m_draw_color);

			CPen* old_pen = dc.SelectObject(&pen);

			dc.MoveTo(this->_last_place.x, this->_last_place.y);
			dc.LineTo(point.x, point.y);

			dc.SelectObject(old_pen);
		}
		this->_last_place = point;
	}
		break;
	default:
		break;
	}
	
	CDialogEx::OnMouseMove(nFlags, point);
}

void CDrawingProjectDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();//清空并触发重绘
}

void CDrawingProjectDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CDrawingProjectDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CDrawingProjectDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CDrawingProjectDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png|其他文件(*.*)|*.*||");
	CFileDialog file_dlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	
	if (file_dlg.DoModal() == IDOK)
	{
		this->m_picture_path = file_dlg.GetPathName();
	}
	UpdateData(FALSE);

	OnEnChangeEdit6();
}

void CDrawingProjectDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);

	CRect rect;
	BOOL  showMsgTag;
	GetClientRect(&rect);

	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);
	HDC hdc = CreateCompatibleDC(dc);
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);

	CImage image;
	image.Attach(hbitmap);

	CString  strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|	GIF图像文件 | *.gif | PNG图像文件 | *.png |	其他格式(*.*) | *.* || ");
	CFileDialog dlg(FALSE, _T("bmp"), _T("iPaint1.bmp"), NULL, strFilter);
	if (dlg.DoModal() != IDOK) return;

	CString strFile = dlg.m_ofn.lpstrFile;
	CString strExtension;

	if (dlg.m_ofn.nFileExtension = 0)
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			strExtension = "bmp"; break;
		case 2:
			strExtension = "jpg"; break;
		case 3:
			strExtension = "gif"; break;
		case 4:
			strExtension = "png"; break;
		default:
			break;
		}
		strFile = strFile + "." + strExtension;
	}

	HRESULT hResult = image.Save(strFile);

	if (FAILED(hResult)) MessageBox(_T("保存图像文件失败！"));
	else MessageBox(_T("文件保存成功！"));

	image.Detach();
	SelectObject(hdc, hOldMap);
}

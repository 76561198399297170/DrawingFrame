
// DrawingProjectDlg.h: 头文件
//

#pragma once


// CDrawingProjectDlg 对话框
class CDrawingProjectDlg : public CDialogEx
{
// 构造
public:
	CDrawingProjectDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWINGPROJECT_DIALOG };
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
	// 0：自由绘制 1：绘制直线 2：绘制椭圆 3：绘制矩形
	int m_draw_type;// 绘制类型
	int m_draw_width;// 绘制时边框粗细

	COLORREF m_draw_color;// 笔刷颜色

public:
	afx_msg void OnBnClickedButton1();// 修改笔刷颜色
	afx_msg void OnEnChangeEdit1();// 线条粗细框更改
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);// 线条粗细右侧上下按钮按下
	afx_msg void OnBnClickedRadio1();// 自由绘制单选框
	afx_msg void OnBnClickedRadio2();// 绘制直线单选框
	afx_msg void OnBnClickedRadio3();// 绘制椭圆单选框
	afx_msg void OnBnClickedRadio4();// 绘制矩形单选框
};

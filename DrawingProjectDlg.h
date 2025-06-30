
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
	CString m_insert_str;// 插入文字绑定文本
	CString m_picture_path;// 插入图片绑定路径
	int m_text_size;

	COLORREF m_draw_color;// 笔刷颜色

	CComboBox m_width_box; // 粗细下拉框

private:
	CPoint _last_place;
	bool is_drawing = false;

public:
	afx_msg void OnBnClickedButton1();// 修改笔刷颜色
	afx_msg void OnEnChangeEdit1();// 线条粗细框更改
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);// 线条粗细右侧上下按钮按下
	afx_msg void OnBnClickedRadio1();// 自由绘制单选框
	afx_msg void OnBnClickedRadio2();// 绘制直线单选框
	afx_msg void OnBnClickedRadio3();// 绘制椭圆单选框
	afx_msg void OnBnClickedRadio4();// 绘制矩形单选框
	afx_msg void OnCbnSelchangeCombo1();// 粗细下拉框处理
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);// 左键按下处理
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);// 鼠标移动处理
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);// 左键松开处理
	afx_msg void OnBnClickedButton2();// 清空绘制内容部分
	afx_msg void OnEnChangeEdit2();// 插入文本框更改
	afx_msg void OnEnChangeEdit3();// 插入文本大小框更改
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};

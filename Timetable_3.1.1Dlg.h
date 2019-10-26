
// Timetable_3.1.1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CTimetable_311Dlg 对话框
class CTimetable_311Dlg : public CDialogEx
{
// 构造
public:
	CTimetable_311Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMETABLE_311_DIALOG };
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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
//	CEdit m_edit1;
	afx_msg void OnEnChangeEdit1();
	// 用来向EDIT1框中输出值// 用来向EDIT1框中输出值
	CString m_edit1;
	// 学年选择框的变量
//	int m_year;
	int m_term;
	int m_year;
	int m_date;
	int m_weak;
};

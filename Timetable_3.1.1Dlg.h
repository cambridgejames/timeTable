
// Timetable_3.1.1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

// CTimetable_311Dlg �Ի���
class CTimetable_311Dlg : public CDialogEx
{
// ����
public:
	CTimetable_311Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMETABLE_311_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// ������EDIT1�������ֵ// ������EDIT1�������ֵ
	CString m_edit1;
	// ѧ��ѡ���ı���
//	int m_year;
	int m_term;
	int m_year;
	int m_date;
	int m_weak;
};

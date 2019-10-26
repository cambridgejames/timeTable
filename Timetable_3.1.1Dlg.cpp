
// Timetable_3.1.1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Timetable_3.1.1.h"
#include "Timetable_3.1.1Dlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define _TEST_

#include "UpdaterClass.cpp"
#include "ErrorCorrecter.cpp"

Course course[20];
string title, ocache, table[12];
unsigned short datas[15], i, j, k;
unsigned int combo[4];

bool judgesingle(unsigned int judged);
void caculater(unsigned int Xcombo[4]);


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTimetable_311Dlg �Ի���



CTimetable_311Dlg::CTimetable_311Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TIMETABLE_311_DIALOG, pParent)
	, m_edit1(_T(""))
	, m_year(0)
	, m_term(0)
	, m_date(0)
	, m_weak(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimetable_311Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_edit1);
	//  DDX_Text(pDX, IDC_EDIT1, m_edit1);
	//  DDV_MaxChars(pDX, m_edit1, 100);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDV_MaxChars(pDX, m_edit1, 500);
	//  DDX_CBIndex(pDX, IDC_COMBO4, m_year);
	//  DDV_MinMaxInt(pDX, m_year, 0, 50);
	DDX_CBIndex(pDX, IDC_COMBO4, m_term);
	DDV_MinMaxInt(pDX, m_term, 0, 50);
	DDX_CBIndex(pDX, IDC_COMBO3, m_year);
	DDV_MinMaxInt(pDX, m_year, 0, 50);
	DDX_CBIndex(pDX, IDC_COMBO2, m_date);
	DDV_MinMaxInt(pDX, m_date, 0, 50);
	DDX_CBIndex(pDX, IDC_COMBO1, m_weak);
	DDV_MinMaxInt(pDX, m_weak, 0, 50);
}

BEGIN_MESSAGE_MAP(CTimetable_311Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CTimetable_311Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CTimetable_311Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTimetable_311Dlg::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTimetable_311Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTimetable_311Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CTimetable_311Dlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT1, &CTimetable_311Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()




// CTimetable_311Dlg ��Ϣ�������

BOOL CTimetable_311Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	//�������Զ���ĳ�ʼ������;
	SetDlgItemText(IDC_EDIT1, TEXT("���ڼ��ؿγ̱��ļ�����"));
	
	for (i = 0; i < 12; table[i++] = "��");//��ʼ����ѯ���������

	ifstream read("courselist.syl", ios::in | ios::binary, _SH_DENYRW);	//��ֻ����ʽ�򿪲������γ̱��ļ�
	if (!read)
	{
		solve(1);	//������������
	}
	else
	{
		for (j = 0; j < 20; j++)	//���ζ�ȡ�γ̱��ļ�
		{
			title = "NULL";	//���ƻ�������λ��׼����һ�ζ�ȡ
			for (k = 0; k < 15; datas[k++] = 0);	//������������λ��׼����һ�ζ�ȡ

			read >> title;
			for (i = 0; i < 15; read >> datas[i++]);

			course[j].download(title, datas);	//����Ӧ�Ķ����Ա��ֵ
		}
		read.close();	//�رղ��ͷſγ̱��ļ�

		title = "NULL";	//���ƻ�������λ��׼����һ�ζ�ȡ
		for (k = 0; k < 15; datas[k++] = 0);	//������������λ��׼����һ�ζ�ȡ

		SetDlgItemText(IDC_EDIT1, TEXT("�γ̱��ļ��Ѽ������"));
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTimetable_311Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTimetable_311Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTimetable_311Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimetable_311Dlg::OnBnClickedCancel()
{
	if (MessageBox(TEXT("���Ҫ�˳���"), TEXT("��ʾ"), MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL ) == 6)
	{
		CDialogEx::OnCancel();
	}
}


void CTimetable_311Dlg::OnBnClickedButton2()
{
	if (MessageBox(TEXT("ȷ��Ҫ��ת���������"), TEXT("��ʾ"), MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL) == 6)
	{
		ShellExecute(NULL, TEXT("open"), TEXT("http://202.206.20.180/"), TEXT(" "), TEXT(" "), SW_SHOWNORMAL);
	}
}


void CTimetable_311Dlg::OnBnClickedButton3()
{
	MessageBox(TEXT("δ�ҵ����õĸ��£�"), TEXT("��ʾ"), MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
}


void CTimetable_311Dlg::OnCbnSelchangeCombo1()
{
	//TODO���ڴ�����Combo1ѡ��仯��Ĵ�����
}


void CTimetable_311Dlg::OnBnClickedButton1()//�������������ַ���
{
	SetDlgItemText(IDC_EDIT1, TEXT(""));

	UpdateData(TRUE);//���ռ���Ϣ��ֵ����Ա����

	combo[0] = m_year;
	combo[1] = m_term;
	combo[2] = m_weak;
	combo[3] = m_date;

	if ((combo[0] && combo[1] && combo[2] && combo[3]) == 0)
	{
		MessageBox(TEXT("��ѡ��ɸѡ������"), TEXT("��ʾ"), MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
	}
	else
	{
		ocache = "";//��������������׼����������

		title = "NULL";	//���ƻ�������λ��׼����һ�ζ�ȡ
		for (k = 0; k < 15; datas[k++] = 0);	//������������λ��׼����һ�ζ�ȡ

		caculater(combo);
		m_edit1 = ocache.c_str();

		ocache = "";//��������������������һ�ν�������
	}

	UpdateData(FALSE);//����Ա������ֵ���ؼ��������
}


void CTimetable_311Dlg::OnBnClickedButton4()//���������е�����
{
	SetDlgItemText(IDC_EDIT1, TEXT(""));
}


void CTimetable_311Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ������������ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void caculater(unsigned int Xcombo[4])
{
#ifdef _TEST_
	for (i = 0; i < 20; i++)
	{
		if (course[i].showcourse(title, datas))
		{
			ocache += title;
			for (j = 0; j < 15; j++)
			{
				ocache += '\t';
				ocache += to_string(datas[j]);
			}
			ocache += '\r';
			ocache += '\n';

			title = "NULL";	//���ƻ�������λ��׼����һ�ζ�ȡ
			for (k = 0; k < 15; datas[k++] = 0);	//������������λ��׼����һ�ζ�ȡ
		}
	}
#else
	ocache += "������";
	switch (combo[0])
	{
	case 1: ocache += "2016-2017"; break;
	case 2: ocache += "2017-2018"; break;
	default: break;
	}
	ocache += "ѧ���";
	ocache += to_string(combo[1]);
	ocache += "ѧ�ڵ�";
	ocache += to_string(combo[2]);
	ocache += "��";
	switch (combo[3])
	{
	case 1: ocache += "��һ"; break;
	case 2: ocache += "�ܶ�"; break;
	case 3: ocache += "����"; break;
	case 4: ocache += "����"; break;
	case 5: ocache += "����"; break;
	case 6: ocache += "����"; break;
	case 7: ocache += "����"; break;
	default: break;
	}
	ocache += "�γ̵Ĳ�ѯ�����";
	ocache += '\r';
	ocache += '\n';

	for (i = 0; i < 20; i++)//�������������ѯ������������ѯ���������
	{
		if (course[i].showcourse(title, datas))
		{
			if (combo[2] >= datas[0] && combo[2] <= datas[1])//ɸѡ����
			{
				if (datas[2] == 0 || (datas[2] == 1 && judgesingle(combo[2]) == true) || (datas[2] == 2 && judgesingle(combo[2]) == false))//ɸѡ��˫��
				{
					if (combo[3] == datas[3])//�Ա�������
					{
						for (j = datas[4]; j <= datas[5]; table[j++] = title);//����������ѯ���������
					}
					if (combo[3] == datas[6])
					{
						for (j = datas[7]; j <= datas[8]; table[j++] = title);
					}
					if (combo[3] == datas[9])
					{
						for (j = datas[10]; j <= datas[11]; table[j++] = title);
					}
					if (combo[3] == datas[12])
					{
						for (j = datas[13]; j <= datas[14]; table[j++] = title);
					}
				}
			}

			title = "NULL";	//���ƻ�������λ��׼����һ�ζ�ȡ
			for (k = 0; k < 15; datas[k++] = 0);	//������������λ��׼����һ�ζ�ȡ
		}
		
	}
	for (k = 0; k < 12; k++)
	{
		ocache += '\r';
		ocache += '\n';
		ocache += "��������������������������������������������������������������������������������������";
		ocache += '\r';
		ocache += '\n';
		ocache += "     ";
		switch (k)
		{
		case 0: ocache += "��һ��  ��08:00 - 08:50��"; break;
		case 1: ocache += "�ڶ���  ��09:00 - 09:50��"; break;
		case 2: ocache += "������  ��10:15 - 11:05��"; break;
		case 3: ocache += "���Ľ�  ��11:15 - 12:05��"; break;
		case 4: ocache += "�����  ��14:00 - 14:50��"; break;
		case 5: ocache += "������  ��15:00 - 15:50��"; break;
		case 6: ocache += "���߽�  ��16:15 - 17:05��"; break;
		case 7: ocache += "�ڰ˽�  ��17:15 - 18:05��"; break;
		case 8: ocache += "�ھŽ�  ��19:00 - 19:50��"; break;
		case 9: ocache += "��ʮ��  ��20:00 - 20:50��"; break;
		case 10: ocache += "��ʮһ�ڣ�21:00 - 21:50��"; break;
		case 11: ocache += "��ʮ���ڣ�22:00 - 22:50��"; break;
		default: break;
		}
		ocache += "   ";
		ocache += "�ص���";
		ocache += '\t';
		ocache += table[k];
	}

	ocache += '\r';
	ocache += '\n';
	ocache += "��������������������������������������������������������������������������������������";

	for (i = 0; i < 12; table[i++] = "��");//��ղ�ѯ���������
#endif
}

bool judgesingle(unsigned int judged)
{
	if (judged % 2 == 0)
	{
		return  false;
	}
	else { return true; }
}
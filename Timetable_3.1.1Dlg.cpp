
// Timetable_3.1.1Dlg.cpp : 实现文件
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


// CTimetable_311Dlg 对话框



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




// CTimetable_311Dlg 消息处理程序

BOOL CTimetable_311Dlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	//以下是自定义的初始化代码;
	SetDlgItemText(IDC_EDIT1, TEXT("正在加载课程表文件……"));
	
	for (i = 0; i < 12; table[i++] = "空");//初始化查询结果缓冲区

	ifstream read("courselist.syl", ios::in | ios::binary, _SH_DENYRW);	//以只读方式打开并锁定课程表文件
	if (!read)
	{
		solve(1);	//进入错误处理程序
	}
	else
	{
		for (j = 0; j < 20; j++)	//依次读取课程表文件
		{
			title = "NULL";	//名称缓存区复位，准备下一次读取
			for (k = 0; k < 15; datas[k++] = 0);	//参数缓冲区复位，准备下一次读取

			read >> title;
			for (i = 0; i < 15; read >> datas[i++]);

			course[j].download(title, datas);	//对相应的对象成员赋值
		}
		read.close();	//关闭并释放课程表文件

		title = "NULL";	//名称缓存区复位，准备下一次读取
		for (k = 0; k < 15; datas[k++] = 0);	//参数缓冲区复位，准备下一次读取

		SetDlgItemText(IDC_EDIT1, TEXT("课程表文件已加载完毕"));
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTimetable_311Dlg::OnPaint()
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
HCURSOR CTimetable_311Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimetable_311Dlg::OnBnClickedCancel()
{
	if (MessageBox(TEXT("真的要退出吗？"), TEXT("提示"), MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL ) == 6)
	{
		CDialogEx::OnCancel();
	}
}


void CTimetable_311Dlg::OnBnClickedButton2()
{
	if (MessageBox(TEXT("确定要跳转至浏览器吗？"), TEXT("提示"), MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL) == 6)
	{
		ShellExecute(NULL, TEXT("open"), TEXT("http://202.206.20.180/"), TEXT(" "), TEXT(" "), SW_SHOWNORMAL);
	}
}


void CTimetable_311Dlg::OnBnClickedButton3()
{
	MessageBox(TEXT("未找到可用的更新！"), TEXT("提示"), MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
}


void CTimetable_311Dlg::OnCbnSelchangeCombo1()
{
	//TODO：在此输入Combo1选项变化后的处理函数
}


void CTimetable_311Dlg::OnBnClickedButton1()//向输出框中输出字符串
{
	SetDlgItemText(IDC_EDIT1, TEXT(""));

	UpdateData(TRUE);//将空间信息赋值给成员变量

	combo[0] = m_year;
	combo[1] = m_term;
	combo[2] = m_weak;
	combo[3] = m_date;

	if ((combo[0] && combo[1] && combo[2] && combo[3]) == 0)
	{
		MessageBox(TEXT("请选择筛选条件！"), TEXT("提示"), MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
	}
	else
	{
		ocache = "";//清空输出缓冲区，准备接收数据

		title = "NULL";	//名称缓存区复位，准备下一次读取
		for (k = 0; k < 15; datas[k++] = 0);	//参数缓冲区复位，准备下一次读取

		caculater(combo);
		m_edit1 = ocache.c_str();

		ocache = "";//清空输出缓冲区，方便下一次接收数据
	}

	UpdateData(FALSE);//将成员变量赋值给控件进行输出
}


void CTimetable_311Dlg::OnBnClickedButton4()//清除输出框中的内容
{
	SetDlgItemText(IDC_EDIT1, TEXT(""));
}


void CTimetable_311Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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

			title = "NULL";	//名称缓存区复位，准备下一次读取
			for (k = 0; k < 15; datas[k++] = 0);	//参数缓冲区复位，准备下一次读取
		}
	}
#else
	ocache += "以下是";
	switch (combo[0])
	{
	case 1: ocache += "2016-2017"; break;
	case 2: ocache += "2017-2018"; break;
	default: break;
	}
	ocache += "学年第";
	ocache += to_string(combo[1]);
	ocache += "学期第";
	ocache += to_string(combo[2]);
	ocache += "周";
	switch (combo[3])
	{
	case 1: ocache += "周一"; break;
	case 2: ocache += "周二"; break;
	case 3: ocache += "周三"; break;
	case 4: ocache += "周四"; break;
	case 5: ocache += "周五"; break;
	case 6: ocache += "周六"; break;
	case 7: ocache += "周日"; break;
	default: break;
	}
	ocache += "课程的查询结果：";
	ocache += '\r';
	ocache += '\n';

	for (i = 0; i < 20; i++)//遍历对象数组查询并将结果送入查询结果缓冲区
	{
		if (course[i].showcourse(title, datas))
		{
			if (combo[2] >= datas[0] && combo[2] <= datas[1])//筛选周数
			{
				if (datas[2] == 0 || (datas[2] == 1 && judgesingle(combo[2]) == true) || (datas[2] == 2 && judgesingle(combo[2]) == false))//筛选单双周
				{
					if (combo[3] == datas[3])//对比星期数
					{
						for (j = datas[4]; j <= datas[5]; table[j++] = title);//将结果存入查询结果缓冲区
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

			title = "NULL";	//名称缓存区复位，准备下一次读取
			for (k = 0; k < 15; datas[k++] = 0);	//参数缓冲区复位，准备下一次读取
		}
		
	}
	for (k = 0; k < 12; k++)
	{
		ocache += '\r';
		ocache += '\n';
		ocache += "———————————————————————————————————————————";
		ocache += '\r';
		ocache += '\n';
		ocache += "     ";
		switch (k)
		{
		case 0: ocache += "第一节  （08:00 - 08:50）"; break;
		case 1: ocache += "第二节  （09:00 - 09:50）"; break;
		case 2: ocache += "第三节  （10:15 - 11:05）"; break;
		case 3: ocache += "第四节  （11:15 - 12:05）"; break;
		case 4: ocache += "第五节  （14:00 - 14:50）"; break;
		case 5: ocache += "第六节  （15:00 - 15:50）"; break;
		case 6: ocache += "第七节  （16:15 - 17:05）"; break;
		case 7: ocache += "第八节  （17:15 - 18:05）"; break;
		case 8: ocache += "第九节  （19:00 - 19:50）"; break;
		case 9: ocache += "第十节  （20:00 - 20:50）"; break;
		case 10: ocache += "第十一节（21:00 - 21:50）"; break;
		case 11: ocache += "第十二节（22:00 - 22:50）"; break;
		default: break;
		}
		ocache += "   ";
		ocache += "地点无";
		ocache += '\t';
		ocache += table[k];
	}

	ocache += '\r';
	ocache += '\n';
	ocache += "———————————————————————————————————————————";

	for (i = 0; i < 12; table[i++] = "空");//清空查询结果缓冲区
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
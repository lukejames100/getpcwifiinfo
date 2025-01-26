
// cplusGetWifiInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "cplusGetWifiInfo.h"
#include "cplusGetWifiInfoDlg.h"
#include "afxdialogex.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <utility>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

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


// CcplusGetWifiInfoDlg 对话框



CcplusGetWifiInfoDlg::CcplusGetWifiInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcplusGetWifiInfoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcplusGetWifiInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrl_ctrl);
}

BEGIN_MESSAGE_MAP(CcplusGetWifiInfoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CcplusGetWifiInfoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CcplusGetWifiInfoDlg 消息处理程序

BOOL CcplusGetWifiInfoDlg::OnInitDialog()
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
	UserInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//初始化控件
void CcplusGetWifiInfoDlg::UserInit()
{
	//设置list的样式
	m_ctrl_ctrl.SetExtendedStyle(LVS_EX_GRIDLINES||LVS_EX_FULLROWSELECT);//有网格线和能一行全选
	m_ctrl_ctrl.InsertColumn(0,"WiFi名称",LVCFMT_LEFT,150);
	m_ctrl_ctrl.InsertColumn(1,"WiFi密码",LVCFMT_LEFT,150);

	//获取list宽度
	CRect rect;
	m_ctrl_ctrl.GetClientRect(&rect);
	int totalWidth=rect.Width();

	//设置列宽度，按比例分配宽度
	m_ctrl_ctrl.SetColumnWidth(0,totalWidth/2);
	m_ctrl_ctrl.SetColumnWidth(1,totalWidth/2);
}
void CcplusGetWifiInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcplusGetWifiInfoDlg::OnPaint()
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
HCURSOR CcplusGetWifiInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcplusGetWifiInfoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	vector<pair<CString,CString>> wifiList=GetWifiData();
	for(size_t i=0;i<wifiList.size();++i)
	{
		//const CString wifiName, password;
		//const auto& [wifiName, password]=wifiList[i];
		CString wifiName=wifiList[i].first;
		CString password=wifiList[i].second;
		int index=m_ctrl_ctrl.InsertItem(static_cast<int>(i), wifiName);
		m_ctrl_ctrl.SetItemText(index,1,password);
	}

}

vector<pair<CString,CString>> CcplusGetWifiInfoDlg::GetWifiData()
{
	vector<pair<CString,CString>> wifiList;

	string commandOutput=execCommand("netsh wlan show profiles");
	istringstream iss(commandOutput);
	string line;

	while(getline(iss, line)){
		size_t pos=line.find("    所有用户配置文件 : ");
		if(pos!=string::npos){
			string profileName=line.substr(pos+23);
			string password=GetWifiPassword(profileName.c_str());
			wifiList.emplace_back(CString(profileName.c_str()),CString(password.c_str()));
		}
	}
	return wifiList;
}

CString CcplusGetWifiInfoDlg::GetWifiPassword(const CString& profileName){
	string command="netsh wlan show profile name=\""+ string(CT2A(profileName))+ "\" key=clear";
	string commandOutput=execCommand(command);
	istringstream iss(commandOutput);
	string line;
	while(getline(iss,line)){
		size_t pos=line.find("关键内容            : ");
		if(pos!=string::npos){
			return CString(line.substr(pos+22).c_str());
		}
	}
	return "无密码或无法读取";
}
string CcplusGetWifiInfoDlg::execCommand(const string& cmd)
{
	string result;
	FILE* pipe=_popen(cmd.c_str(),"r");
	if(!pipe){
		MessageBox("系统生成错误");
		return "Error";
	}
	char buff[128];
	while(fgets(buff,sizeof(buff),pipe)!=nullptr){
		result+=buff;
	}
	_pclose(pipe);
	return result;
}
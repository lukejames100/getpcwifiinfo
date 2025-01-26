
// cplusGetWifiInfoDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CcplusGetWifiInfoDlg �Ի���



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


// CcplusGetWifiInfoDlg ��Ϣ�������

BOOL CcplusGetWifiInfoDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UserInit();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//��ʼ���ؼ�
void CcplusGetWifiInfoDlg::UserInit()
{
	//����list����ʽ
	m_ctrl_ctrl.SetExtendedStyle(LVS_EX_GRIDLINES||LVS_EX_FULLROWSELECT);//�������ߺ���һ��ȫѡ
	m_ctrl_ctrl.InsertColumn(0,"WiFi����",LVCFMT_LEFT,150);
	m_ctrl_ctrl.InsertColumn(1,"WiFi����",LVCFMT_LEFT,150);

	//��ȡlist���
	CRect rect;
	m_ctrl_ctrl.GetClientRect(&rect);
	int totalWidth=rect.Width();

	//�����п�ȣ�������������
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcplusGetWifiInfoDlg::OnPaint()
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
HCURSOR CcplusGetWifiInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcplusGetWifiInfoDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
		size_t pos=line.find("    �����û������ļ� : ");
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
		size_t pos=line.find("�ؼ�����            : ");
		if(pos!=string::npos){
			return CString(line.substr(pos+22).c_str());
		}
	}
	return "��������޷���ȡ";
}
string CcplusGetWifiInfoDlg::execCommand(const string& cmd)
{
	string result;
	FILE* pipe=_popen(cmd.c_str(),"r");
	if(!pipe){
		MessageBox("ϵͳ���ɴ���");
		return "Error";
	}
	char buff[128];
	while(fgets(buff,sizeof(buff),pipe)!=nullptr){
		result+=buff;
	}
	_pclose(pipe);
	return result;
}

// cplusGetWifiInfoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include <vector>
#include <string>
#include <iostream>

#include <utility>
using namespace std;

// CcplusGetWifiInfoDlg �Ի���
class CcplusGetWifiInfoDlg : public CDialogEx
{
// ����
public:
	CcplusGetWifiInfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CPLUSGETWIFIINFO_DIALOG };

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
	CListCtrl m_ctrl_ctrl;
	afx_msg void OnBnClickedButton1();
	void UserInit();
	vector<pair<CString,CString>> GetWifiData();
	string execCommand(const string& cmd);
	CString GetWifiPassword(const CString& profileName);
};

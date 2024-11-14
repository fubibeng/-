
// MFCrlsbDlg.h: 头文件
//

#include"CFILEWIN.h"
#pragma once


// CMFCrlsbDlg 对话框
class CMFCrlsbDlg : public CDialogEx
{
// 构造
public:
	CMFCrlsbDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCRLSB_DIALOG };
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
private:
	CFILEWIN cf;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedliulan();
	CString m_str;
	afx_msg void OnBnClickedxz();
	afx_msg void OnBnClickedqr();
	afx_msg void OnBnClickedCxuanzhe();
	afx_msg void OnEnChangeEdit1();
};

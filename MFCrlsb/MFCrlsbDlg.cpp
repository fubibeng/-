
// MFCrlsbDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCrlsb.h"
#include "MFCrlsbDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <cstring>
#include<opencv2/opencv.hpp>
using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCrlsbDlg 对话框



CMFCrlsbDlg::CMFCrlsbDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCRLSB_DIALOG, pParent)
	, m_str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCrlsbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str);
}

BEGIN_MESSAGE_MAP(CMFCrlsbDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(liulan, &CMFCrlsbDlg::OnBnClickedliulan)

	ON_BN_CLICKED(qr, &CMFCrlsbDlg::OnBnClickedqr)
	ON_BN_CLICKED(IDCxuanzhe, &CMFCrlsbDlg::OnBnClickedCxuanzhe)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCrlsbDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CMFCrlsbDlg 消息处理程序

BOOL CMFCrlsbDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCrlsbDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCrlsbDlg::OnPaint()
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
HCURSOR CMFCrlsbDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//点击浏览按钮
void CMFCrlsbDlg::OnBnClickedliulan()
{
	// TODO: 在此添加控件通知处理程序代码
	cf.DoModal();
}


void MyImg(cv::VideoCapture cap);

void CMFCrlsbDlg::OnBnClickedqr()
{
	
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//cstring 转换为 string
	std::string st_img_path = (LPCSTR)(CStringA)(m_str);
	if (st_img_path.compare("0")==0)
	{
		cv::VideoCapture cap(0);
		MyImg(cap);
	}
	else
	{
		cv::VideoCapture cap(st_img_path);
		MyImg(cap);
	}
	
	
}
void MyImg(cv::VideoCapture cap){

	std::string pbtxt_file_path = "./mode/opencv_face_detector.pbtxt";
	std::string pd_filel_path = "./mode/opencv_face_detector_uint8.pb";//opencv_face_detector_uint8.pb
	//创建一个名为input的窗口 等比例缩放
	namedWindow("input", WINDOW_KEEPRATIO);
	//窗口大小为800 * 450 16：9
	resizeWindow("input", 800, 450);
	cv::dnn::Net net = cv::dnn::readNetFromTensorflow(pd_filel_path, pbtxt_file_path);

	Mat frame;
	while (true)
	{
		cap.read(frame);

		if (frame.empty())
		{
			break;
		}

		cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, Size(300, 300), cv::Scalar(104, 177, 123), false, false);
		net.setInput(blob);

		//对图片进行推理
		cv::Mat probs = net.forward();

		//推理结果 1*1*n*7  n:多少张人脸 7：7个维度 
		cv::Mat detectMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

		for (int row = 0; row < detectMat.rows; row++)
		{
			float conf = detectMat.at<float>(row, 2);
			if (conf > 0.5)
			{
				float x1 = detectMat.at<float>(row, 3) * frame.cols;
				float y1 = detectMat.at<float>(row, 4) * frame.rows;
				float x2 = detectMat.at<float>(row, 5) * frame.cols;
				float y2 = detectMat.at<float>(row, 6) * frame.rows;

				cv::Rect box(x1, y1, x2 - x1, y2 - y1);
				cv::rectangle(frame, box, cv::Scalar(0, 0, 255), 2, 8);
			}

		}

		cv::imshow("input", frame);
		char c = waitKey(1);
		//按esc推出
		if (c == 27)
		{
			break;
		}
	}
	cv::waitKey();
	cv::destroyAllWindows();

}


void CMFCrlsbDlg::OnBnClickedCxuanzhe()
{
	// TODO: 在此添加控件通知处理程序代码
	m_str = cf.m_filewin_str;
	UpdateData(FALSE);
}


void CMFCrlsbDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

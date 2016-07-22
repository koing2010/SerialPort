
// MFC_SerialPortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_SerialPort.h"
#include "MFC_SerialPortDlg.h"
#include "afxdialogex.h"

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


// CMFC_SerialPortDlg 对话框



CMFC_SerialPortDlg::CMFC_SerialPortDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_SERIALPORT_DIALOG, pParent)
	, Tx_string(_T(""))
	, Rx_string(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_SerialPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ComName, ComName);
	DDX_Control(pDX, IDC_COMBO_BaudRate, BaudRate);
	DDX_Control(pDX, IDC_MSCOMM1, my_com);
	DDX_Text(pDX, IDC_EDIT_Tx, Tx_string);
	DDX_Text(pDX, IDC_EDIT_Rx, Rx_string);

}

BEGIN_MESSAGE_MAP(CMFC_SerialPortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_OpenPort, &CMFC_SerialPortDlg::OnClickedButtonOpenport)
	ON_BN_CLICKED(IDC_BUTTON_Tx, &CMFC_SerialPortDlg::OnClickedButtonTx)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CMFC_SerialPortDlg::OnClickedButtonClear)

ON_BN_CLICKED(IDC_BUTTON_HexChose, &CMFC_SerialPortDlg::OnClickedButtonHexchose)
END_MESSAGE_MAP()


// CMFC_SerialPortDlg 消息处理程序

BOOL CMFC_SerialPortDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码

	//串口组合框 配置选择部分的代码添加在这里
	CString name_str;

	short int i = 0;
	for ( i = 0; i < 15 ; i ++)
	{
		name_str.Format(_T("com %d"), i + 1);
		ComName.InsertString(i,name_str);
	}

	//波特率选择组合
	CString baudRat_str[] = { _T("115200"), _T("19200") , _T("38400") , _T("56000") , _T("9600") };

		for (int i = 0; i < 5;i ++)
		{   
		 int judge_tf = BaudRate.AddString(baudRat_str[i]);
		 if (judge_tf == CB_ERR || judge_tf == CB_ERRSPACE)
		 {
			 MessageBox(_T("build baudrate error"));
		 }
		 BaudRate.SetCurSel(0);//默认9600

		}

   //
		hexMode = TRUE; //默认hex 模式

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_SerialPortDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_SerialPortDlg::OnPaint()
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
HCURSOR CMFC_SerialPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_SerialPortDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFC_SerialPortDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFC_SerialPortDlg::OnClickedButtonOpenport()
{
	// 打开串口按钮
	
	CString str, comFile, n;//定义字符串
	GetDlgItemText(IDC_BUTTON_OpenPort, str);//把打开按键的值付给str
	CWnd *pOpen;
	pOpen = GetDlgItem(IDC_BUTTON_OpenPort);//指向打开按键

	if (!my_com.get_PortOpen())
	{
		BaudRate.GetLBText(BaudRate.GetCurSel(), comFile);//获取所选串口波特率
		comFile = comFile + ',' + 'n' + ',' + '8' + ',' + '1';//配置串口格式
		my_com.put_CommPort((ComName.GetCurSel() + 1)); //选择串口
		my_com.put_InputMode(1);//二进制模式
		my_com.put_Settings(comFile);//配置串口
		my_com.put_InputLen(1024);//接收区1024字节缓存
		my_com.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取 
		my_com.put_RThreshold(1);//大于 1字节触发事件
		my_com.put_RTSEnable(1);//允许RT


		my_com.put_PortOpen(TRUE);//打开串口
		if (my_com.get_PortOpen())//打开成功
		{
			str = _T("ClosePort");
			UpdateData(true);
			pOpen->SetWindowText(str);//改变按钮显示 切换为关闭功能

		}

	}
	else
	{
		my_com.put_PortOpen(false);
		if (str != _T("OpenPort"))
		{
			str = _T("OpenPort");
			UpdateData(true);
			pOpen->SetWindowText(str);//改变按钮显示 切换为打开
		}

	}
}

//十六进制转字符串
char CMFC_SerialPortDlg::Hex2Char(char c)
{
	if ((c >= '0') && (c <= '9'))
		return c - 0x30;
	else if ((c >= 'A') && (c <= 'F'))
		return c - 'A' + 10;
	else if ((c >= 'a') && (c <= 'f'))
		return c - 'a' + 10;
	else
		return 0x10;
}


//将一个字符串作为十六进制串转化为一个字节数组，字节间可用空格分隔，
//返回转换后的字节数组长度，同时字节数组长度自动设置。
int CMFC_SerialPortDlg::Str2Hex(CString str, CByteArray &senddata)
{
/*	int t, t1;
	int rlen = 0, len = str.GetLength();
	//data.SetSize(len/2);
	for (int i = 0; i<len;)
	{
		char l, h = str[i];
		if (h == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		l = str[i];
		t = Hex2Char(h);
		t1 = Hex2Char(l);
		if ((t == 16) || (t1 == 16))
			break;
		else
			t = t * 16 + t1;
		i++;
		data[rlen] = (char)t;
		rlen++;
	}
	return rlen;*/
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();
	senddata.SetSize(len / 2);
	for (int i = 0; i<len;)
	{
		char lstr, hstr = str[i];
		if (hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i];
		hexdata = Hex2Char(hstr);
		lowhexdata = Hex2Char(lstr);
		if ((hexdata == 16) || (lowhexdata == 16))
			break;
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		senddata[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;

}

void CMFC_SerialPortDlg::OnClickedButtonTx()
{
	// 发送按钮
	UpdateData(true);//更新控件数据 Tx_string
	CString TxStr;
	CByteArray Txbuf;
	if (hexMode)//ASCII模式发送
	{
		CStringW str2(Tx_string);
		int lenth = str2.GetLength();//获取输入字符长度
		Str2Hex(Tx_string, Txbuf);
		my_com.put_Output(COleVariant(Txbuf));

	}
	else//hex模式
	{
		my_com.put_Output(COleVariant(Tx_string));
	}
	
}



void CMFC_SerialPortDlg::OnClickedButtonClear()
{
	// 清除接收数据
	Rx_string = _T("");
	UpdateData(false);

}
BEGIN_EVENTSINK_MAP(CMFC_SerialPortDlg, CDialogEx)
	ON_EVENT(CMFC_SerialPortDlg, IDC_MSCOMM1, 1, CMFC_SerialPortDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CMFC_SerialPortDlg::OnCommMscomm1()
{

	// 串口事件处理程序
	if (my_com.get_CommEvent() == 2)//接收到数据
	{
		char rxbuf[1024] = {0};
	    long length;
		long rxlength;
		VARIANT InputData;
		COleSafeArray fs;
		
		InputData  = my_com.get_Input();//读取缓冲区数据
		fs = InputData;//VARIANT型变量 转换成 ColeSafeArray 变量
		rxlength = fs.GetOneDimSize();
		for (length = 0; length < rxlength; length ++ )
		{
			fs.GetElement(&length,rxbuf + length );//转换成byte型数据
	
		}
	    
		Rx_string += rxbuf;//更新到显示区域
		Rx_string += _T("\r\n");

		UpdateData(false);

	}

}




void CMFC_SerialPortDlg::OnClickedButtonHexchose()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;//定义字符串
	CWnd *hexButton = GetDlgItem(IDC_BUTTON_HexChose);//指向

	GetDlgItemText(IDC_BUTTON_HexChose, str);//把打开按键的值付给str
	if (str == _T("HEX"))
	{
		hexMode = 0;
		str = _T("ASCII");
		hexButton->SetWindowText(str);//改变按钮显示

	}
	else
	{
		hexMode = 1;
		str = _T("HEX");
		hexButton->SetWindowText(str);//改变按钮显示
	}
	UpdateData(true);


}

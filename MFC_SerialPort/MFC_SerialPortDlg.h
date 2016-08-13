
// MFC_SerialPortDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CMFC_SerialPortDlg �Ի���
class CMFC_SerialPortDlg : public CDialogEx
{
// ����
public:
	CMFC_SerialPortDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_SERIALPORT_DIALOG };
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
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	CComboBox ComName;
	CComboBox BaudRate;
	CMscomm1 my_com;
	CString Tx_string;
	CString Rx_string;
	afx_msg void OnClickedButtonOpenport();
	afx_msg void OnClickedButtonTx();
	afx_msg void OnClickedButtonClear();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
//	CButton hexMode;
	afx_msg void OnClickedButtonHexchose();
	bool hexMode;
	//int Str2Hex(CString str,char* data);
	int Str2Hex(CString str, CByteArray &senddata);
	char Hex2Char(char );
	char Hex2Str(char C);
};

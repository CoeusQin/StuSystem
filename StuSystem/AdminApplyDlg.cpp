// AdminApplyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "AdminApplyDlg.h"
#include "FileIO.h"


// CAdminApplyDlg

IMPLEMENT_DYNCREATE(CAdminApplyDlg, CFormView)

CAdminApplyDlg::CAdminApplyDlg()
	: CFormView(DIALOG_ADM_APPLY)
	, m_message(_T(""))
{

}

CAdminApplyDlg::~CAdminApplyDlg()
{
}

void CAdminApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_message);
}

BEGIN_MESSAGE_MAP(CAdminApplyDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminApplyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdminApplyDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAdminApplyDlg ���

#ifdef _DEBUG
void CAdminApplyDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdminApplyDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdminApplyDlg ��Ϣ�������


void CAdminApplyDlg::UpdateCombo()
{	// �������µ���Ϣ�б�������
	FileIO file;
	file.ReadMessage();
	int count = 1;
	m_combo.ResetContent();
	for (vector<message>::iterator it = file.messagev.begin(); it != file.messagev.end(); it++)
	{
		CString str;
		str.Format(_T("��Ϣ%d"), count);
		m_combo.AddString(str);		// ͨ���γ̺��ڿγ��б����ҵ���Ӧ�Ŀγ�����
		count++;
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CAdminApplyDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ��ȡ��Ϣ�б���ӽ���������
	UpdateCombo();
}


void CAdminApplyDlg::OnBnClickedButton1()
{	// �鿴��Ϣ
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ��ȡ��������ѡ�����Ϣ
	int selectnum = m_combo.GetCurSel();
	FileIO file;
	file.ReadMessage();
	message tmp = file.messagev[selectnum];
	
	// ��message������Ҳ�m_message��
	m_message.Empty();	// ����տ���ԭ������Ϣ
	CString str;
	str = _T("�����ʦ��") + (CString)tmp.teaname.c_str();	// ��ʦ����
	str += (_T("\r\n��ʦ��ţ�") + (CString)tmp.teanum.c_str());	// ��ʦ���
	str += (_T("\r\n�¿γ�����") + (CString)tmp.coursename.c_str());	// �¿γ���
	CString planstr = (CString)tmp.courseplan.c_str();		// �����ڿμƻ��ַ���
	planstr.Replace(_T("&"), _T("\r\n"));
	str += (_T("\r\n�ڿμƻ���\r\n") + planstr);		// �ڿμƻ�
	m_message = str;
	UpdateData(FALSE);
}


void CAdminApplyDlg::OnBnClickedButton2()
{	// ����ǰ��Ϣ��Ϊ�Ѷ�������������ɾ��������Ϣ
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����տ�������
	UpdateData(TRUE);
	FileIO file;
	file.ReadMessage();
	// ��ȡ��������ѡ�����Ϣ
	int selectnum = m_combo.GetCurSel();
	vector<message>::iterator  it = file.messagev.begin() + selectnum;
	file.messagev.erase(it);
	CString str;
	str.Format(_T("�ɹ�ɾ����Ϣ%d"), selectnum + 1);
	MessageBox(str);
	file.WriteMessage();
	m_message.Empty();
	UpdateCombo();
}


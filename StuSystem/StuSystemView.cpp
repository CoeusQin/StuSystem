
// StuSystemView.cpp : CStuSystemView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "StuSystem.h"
#endif

#include "StuSystemDoc.h"
#include "StuSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStuSystemView

IMPLEMENT_DYNCREATE(CStuSystemView, CView)

BEGIN_MESSAGE_MAP(CStuSystemView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CStuSystemView ����/����

CStuSystemView::CStuSystemView()
{
	// TODO: �ڴ˴���ӹ������

}

CStuSystemView::~CStuSystemView()
{
}

BOOL CStuSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CStuSystemView ����

void CStuSystemView::OnDraw(CDC* /*pDC*/)
{
	CStuSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CStuSystemView ��ӡ

BOOL CStuSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CStuSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CStuSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CStuSystemView ���

#ifdef _DEBUG
void CStuSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CStuSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStuSystemDoc* CStuSystemView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStuSystemDoc)));
	return (CStuSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CStuSystemView ��Ϣ�������

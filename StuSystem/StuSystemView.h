
// StuSystemView.h : CStuSystemView ��Ľӿ�
//

#pragma once


class CStuSystemView : public CView
{
protected: // �������л�����
	CStuSystemView();
	DECLARE_DYNCREATE(CStuSystemView)

// ����
public:
	CStuSystemDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CStuSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // StuSystemView.cpp �еĵ��԰汾
inline CStuSystemDoc* CStuSystemView::GetDocument() const
   { return reinterpret_cast<CStuSystemDoc*>(m_pDocument); }
#endif


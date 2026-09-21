
// G26W03MFCView.h: CG26W03MFCView 클래스의 인터페이스
//

#pragma once


class CG26W03MFCView : public CView
{
protected: // serialization에서만 만들어집니다.
	CG26W03MFCView() noexcept;
	DECLARE_DYNCREATE(CG26W03MFCView)

// 특성입니다.
public:
	CG26W03MFCDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CG26W03MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // G26W03MFCView.cpp의 디버그 버전
inline CG26W03MFCDoc* CG26W03MFCView::GetDocument() const
   { return reinterpret_cast<CG26W03MFCDoc*>(m_pDocument); }
#endif


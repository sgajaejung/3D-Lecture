#pragma once



class C3DView : public CView
{
public:
	C3DView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~C3DView();           // 동적 만들기에 사용되는 protected 생성자입니다.

public:
	virtual void Render(HDC hdc) { }
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.

protected:
	DECLARE_MESSAGE_MAP()
};

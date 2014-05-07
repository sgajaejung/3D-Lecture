#pragma once

#include "3DView.h"


class CDotProductView : public C3DView
{
public:
	CDotProductView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CDotProductView();           // 동적 만들기에 사용되는 protected 생성자입니다.


public:
	virtual void Render(HDC hdc) override;


protected:
	DECLARE_MESSAGE_MAP()
};

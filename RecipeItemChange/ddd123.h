#pragma once


// Cddd123 대화 상자입니다.

class Cddd123 : public CDialog
{
	DECLARE_DYNAMIC(Cddd123)

public:
	Cddd123(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Cddd123();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RECIPEITEMCHANGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

#pragma once


// Cddd123 ��ȭ �����Դϴ�.

class Cddd123 : public CDialog
{
	DECLARE_DYNAMIC(Cddd123)

public:
	Cddd123(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Cddd123();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RECIPEITEMCHANGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

// ddd123.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RecipeItemChange.h"
#include "ddd123.h"


// Cddd123 대화 상자입니다.

IMPLEMENT_DYNAMIC(Cddd123, CDialog)

Cddd123::Cddd123(CWnd* pParent /*=NULL*/)
	: CDialog(Cddd123::IDD, pParent)
{

}

Cddd123::~Cddd123()
{
}

void Cddd123::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cddd123, CDialog)
END_MESSAGE_MAP()


// Cddd123 메시지 처리기입니다.

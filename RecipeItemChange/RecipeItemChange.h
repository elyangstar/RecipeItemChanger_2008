
// RecipeItemChange.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRecipeItemChangeApp:
// �� Ŭ������ ������ ���ؼ��� RecipeItemChange.cpp�� �����Ͻʽÿ�.
//

class CRecipeItemChangeApp : public CWinAppEx
{
public:
	CRecipeItemChangeApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CRecipeItemChangeApp theApp;
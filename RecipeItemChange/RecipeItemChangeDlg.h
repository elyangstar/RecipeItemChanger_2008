
// RecipeItemChangeDlg.h : 헤더 파일
//

#pragma once
#include "Include/GridControl/GridCtrl.h"
#include "Include/GridControl/NewCellTypes/GridCellCheck.h"
#include "Include/HMDataManager/HMConfigFile.h"
#include "RecipeChangeIPSettingDlg.h"
#include "Include/HMDataManager/MConfig.h"
#include "afxwin.h"

class CHMConfigFile;

struct _RecipeInfo
{
	int	m_nindex;
	CString	strRecipeName;
	CString	strRecipePath;

	BOOL bSelected;
	_RecipeInfo()
	{
		m_nindex = 0;
		strRecipeName = "";
		strRecipePath = "";

		bSelected = FALSE;
	}
};

struct _RecipeDataInfo
{
	int	nindex;

	CString	strItem;
	CString	strData;
	
	BOOL bCheck;

	_RecipeDataInfo()
	{
		nindex = 0;
		strItem = "";
		strData = "";

		bCheck = FALSE;
	}
};

// CRecipeItemChangeDlg 대화 상자
class CRecipeItemChangeDlg : public CDialog
{
// 생성입니다.
public:
	CRecipeItemChangeDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RECIPEITEMCHANGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedGirdCtrl();
	afx_msg void OnBnClickedRadioAoi();
	afx_msg void OnBnClickedRadioReview();
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonSelectedChange();
	afx_msg void OnBnClickedButtonIpSetting();

	std::vector<_RecipeInfo>		m_vectotalRecipe;
	std::vector<_RecipeInfo>		m_vecSelectedRecipe;
	std::vector<_RecipeDataInfo>	m_vecChangedRecipeData;

	CGridCtrl m_gridAllRecipe;
	CGridCtrl m_gridSelectedRecipe;
	CGridCtrl m_gridRecipeItem;

	void		SetInitGridAllRecipe();
	void		SetInitGridSelectedRecipe();
	void		SetInitGridRecipeItem();
	void		CopyToAllMachine();
	CString		CurrentPath();
	void		ClearFillData();

	CString		m_strFindItem;
	static UINT	CopyThreadFunc(LPVOID pParam);

	CRecipeChangeIPSettingDlg* m_DlgRecipeChangeIPSetting;

	CString m_strRecipeID;
	CButton m_btCopyToMachine;
	afx_msg void OnClose();

	BOOL PreTranslateMessage(MSG* pMsg);
};

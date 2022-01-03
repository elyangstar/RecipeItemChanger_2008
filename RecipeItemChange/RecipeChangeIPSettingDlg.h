#pragma once

#include "HMDataManager/HMConfigFile.h"
// CRecipeChangeIPSettingDlg 대화 상자입니다.

class CRecipeChangeIPSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecipeChangeIPSettingDlg)

public:
	CRecipeChangeIPSettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRecipeChangeIPSettingDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_IP_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	CHMConfigFile m_configFile;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void		LoadDataFile();
	CString		CurrentPath();
};

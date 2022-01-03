#pragma once

#include "HMDataManager/HMConfigFile.h"
// CRecipeChangeIPSettingDlg ��ȭ �����Դϴ�.

class CRecipeChangeIPSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecipeChangeIPSettingDlg)

public:
	CRecipeChangeIPSettingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRecipeChangeIPSettingDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_IP_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	CHMConfigFile m_configFile;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void		LoadDataFile();
	CString		CurrentPath();
};

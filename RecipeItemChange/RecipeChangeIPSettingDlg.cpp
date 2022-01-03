// RecipeChangeIPSettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RecipeItemChange.h"
#include "RecipeChangeIPSettingDlg.h"


// CRecipeChangeIPSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRecipeChangeIPSettingDlg, CDialog)

CRecipeChangeIPSettingDlg::CRecipeChangeIPSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecipeChangeIPSettingDlg::IDD, pParent)
{

}

CRecipeChangeIPSettingDlg::~CRecipeChangeIPSettingDlg()
{
}

void CRecipeChangeIPSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecipeChangeIPSettingDlg, CDialog)

	ON_BN_CLICKED(IDOK, &CRecipeChangeIPSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()



BOOL CRecipeChangeIPSettingDlg::OnInitDialog()
{
	LoadDataFile();

	return TRUE;
}


// CRecipeChangeIPSettingDlg 메시지 처리기입니다.

void CRecipeChangeIPSettingDlg::OnBnClickedOk()
{
	CString strTemp = "";
	CString strValue = "";
	BOOL bCheckUse = FALSE;

	CString strConfigPath = CurrentPath() + ".cfg";
	BOOL bFlag = m_configFile.SetFileName((LPSTR)(LPCSTR)strConfigPath);

	if (bFlag)
	{
		//AOIServer
		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("AOI_IP_Setting_%d",i);
			GetDlgItemText(IDC_EDIT_IP_1 + i, strValue);
			m_configFile.SetItemValue((LPSTR)(LPCSTR)strTemp,(LPSTR)(LPCSTR)strValue);
		}

		for (int i = 0 ;i<18 ; i++)
		{
			strTemp.Format("AOI_NAME_Setting_%d",i);
			GetDlgItemText(IDC_EDIT_IP_NAME_AOI_1+i, strValue);
			m_configFile.SetItemValue((LPSTR)(LPCSTR)strTemp,(LPSTR)(LPCSTR)strValue);
		}

		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("AOI_CHECK_Setting_%d",i);
			bCheckUse = ((CButton*)GetDlgItem(IDC_EDIT_IP_AOI_CHECK_1+i))->GetCheck();
			m_configFile.SetItemValue((LPSTR)(LPCSTR)strTemp,bCheckUse);
		}

		//Reveiw.
		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("Review_IP_Setting_%d",i);
			GetDlgItemText(IDC_EDIT_IP_19 + i, strValue);
			m_configFile.SetItemValue((LPSTR)(LPCSTR)strTemp,(LPSTR)(LPCSTR)strValue);
		}

		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("Review_NAME_Setting_%d",i);
			GetDlgItemText( IDC_EDIT_IP_NAME_REVIEW_1+i, strValue);
			m_configFile.SetItemValue((LPSTR)(LPCSTR)strTemp,(LPSTR)(LPCSTR)strValue);
		}

		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("Review_CHECK_Setting_%d",i);
			bCheckUse = ((CButton*)GetDlgItem(IDC_EDIT_IP_REVIEW_CHECK_1+i))->GetCheck();
			m_configFile.SetItemValue((LPSTR)(LPCSTR)strTemp,bCheckUse);
		}

		BOOL bUse = ((CButton*)GetDlgItem(IDC_CHECK_NETWORK))->GetCheck();
		m_configFile.SetItemValue("NETWROK_USE",bUse);
	}
}

void CRecipeChangeIPSettingDlg::LoadDataFile()
{
	CString strTemp = "";
	CString strValue = "";
	BOOL bCheckUse = FALSE;
	CString strConfigPath = CurrentPath() + ".cfg";
	BOOL bFlag = m_configFile.SetFileName((LPSTR)(LPCSTR)strConfigPath);

	if (bFlag)
	{
		//AOIServer
		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("AOI_IP_Setting_%d",i);
			m_configFile.GetItemValue((LPSTR)(LPCSTR)strTemp,strValue,"");

			SetDlgItemText(IDC_EDIT_IP_1 + i, strValue);
		}

		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("AOI_NAME_Setting_%d",i);
			m_configFile.GetItemValue((LPSTR)(LPCSTR)strTemp,strValue,"");

			SetDlgItemText(IDC_EDIT_IP_NAME_AOI_1 + i, strValue);
		}

		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("AOI_CHECK_Setting_%d",i);
			m_configFile.GetItemValue((LPSTR)(LPCSTR)strTemp,bCheckUse,FALSE);
			
			((CButton*)GetDlgItem(IDC_EDIT_IP_AOI_CHECK_1+i))->SetCheck(bCheckUse);
		}

		//Review
		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("Review_IP_Setting_%d",i);
			m_configFile.GetItemValue((LPSTR)(LPCSTR)strTemp,strValue,"");

			SetDlgItemText(IDC_EDIT_IP_19 + i, strValue);
		}

		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("Review_NAME_Setting_%d",i);
			m_configFile.GetItemValue((LPSTR)(LPCSTR)strTemp,strValue,"");

			SetDlgItemText(IDC_EDIT_IP_NAME_REVIEW_1 + i, strValue);
		}

		for (int i = 0; i<18 ; i++)
		{
			strTemp.Format("Review_CHECK_Setting_%d",i);
			m_configFile.GetItemValue((LPSTR)(LPCSTR)strTemp,bCheckUse,FALSE);

			((CButton*)GetDlgItem(IDC_EDIT_IP_REVIEW_CHECK_1+i))->SetCheck(bCheckUse);
		}

		BOOL bUse = FALSE;
		m_configFile.GetItemValue("NETWROK_USE",bUse);
		((CButton*)GetDlgItem(IDC_CHECK_NETWORK))->SetCheck(bUse);

	}

	UpdateData(FALSE);
}

CString CRecipeChangeIPSettingDlg::CurrentPath()
{
	CString strTempPath;
	TCHAR szpath[MAX_PATH+1];
	::GetModuleFileName(AfxGetInstanceHandle(),szpath,MAX_PATH);
	strTempPath = szpath;
	strTempPath = strTempPath.Mid(0,strTempPath.GetLength()-4);


	return strTempPath;
}
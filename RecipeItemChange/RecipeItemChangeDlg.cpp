
// RecipeItemChangeDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RecipeItemChange.h"
#include "RecipeItemChangeDlg.h"
#include <fstream>	

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define GRID_MAX_COUNT_ROW		4000
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRecipeItemChangeDlg 대화 상자




CRecipeItemChangeDlg::CRecipeItemChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecipeItemChangeDlg::IDD, pParent)
	, m_strFindItem(_T("")) 
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_COPY);

	m_vectotalRecipe.clear();
	m_vecSelectedRecipe.clear();
	
	m_DlgRecipeChangeIPSetting = NULL;
	m_strRecipeID = "";
}

void CRecipeItemChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GIRD_ALL_RECIPE, m_gridAllRecipe);
	DDX_Control(pDX, IDC_GIRD_SELECTED_RECIPE, m_gridSelectedRecipe);
	DDX_Control(pDX, IDC_GIRD_RECIPE_ITEM, m_gridRecipeItem);
	DDX_Text(pDX, IDC_FIND_ITEM, m_strFindItem);
	DDX_Text(pDX, IDC_STATIC_RCP_NAME, m_strRecipeID);
	DDX_Control(pDX, IDC_BUTTON_SELECTED_CHANGE, m_btCopyToMachine);
}

BEGIN_MESSAGE_MAP(CRecipeItemChangeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO_AOI, &CRecipeItemChangeDlg::OnBnClickedRadioAoi)
	ON_BN_CLICKED(IDC_BUTTON1, &CRecipeItemChangeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRecipeItemChangeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_GIRD_SELECTED_RECIPE, &CRecipeItemChangeDlg::OnBnClickedGirdCtrl)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CRecipeItemChangeDlg::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_SELECTED_CHANGE, &CRecipeItemChangeDlg::OnBnClickedButtonSelectedChange)
	ON_BN_CLICKED(IDC_BUTTON_IP_SETTING, &CRecipeItemChangeDlg::OnBnClickedButtonIpSetting)
	ON_BN_CLICKED(IDC_RADIO_REVIEW, &CRecipeItemChangeDlg::OnBnClickedRadioReview)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CRecipeItemChangeDlg 메시지 처리기

BOOL CRecipeItemChangeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetInitGridAllRecipe();
	SetInitGridSelectedRecipe();
	SetInitGridRecipeItem();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRecipeItemChangeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRecipeItemChangeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRecipeItemChangeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CRecipeItemChangeDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;

	GetClientRect(rect);

	pDC->FillSolidRect( rect, RGB(0, 0, 0) );

	return TRUE;

	//return CDialogEx::OnEraseBkgnd(pDC);

}

HBRUSH CRecipeItemChangeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC,pWnd,nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:
		{
			int nCtrlId = pWnd->GetDlgCtrlID();
				if( nCtrlId == IDC_STATIC_RECIPE || nCtrlId == IDC_RADIO_AOI || nCtrlId == IDC_RADIO_REVIEW 
					|| nCtrlId == IDC_STATIC_RECIPE2 || nCtrlId == IDC_STATIC_RCP_NAME ||nCtrlId == IDC_RADIO_ITEM || nCtrlId == IDC_RADIO_Value)
				{
					pDC->SetBkColor(RGB(0,0,0));
					pDC->SetTextColor(RGB(255, 255, 255));
					pDC->SetBkMode(TRANSPARENT);
					return (HBRUSH)GetStockObject(BLACK_BRUSH);;
				}
		} 
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CRecipeItemChangeDlg::SetInitGridAllRecipe()
{
	CGridCtrl* pGrid = &m_gridAllRecipe;
	const int nRowNum = GRID_MAX_COUNT_ROW;
	const int nColNum = 2;

	CString strTemp = "";
	pGrid->DeleteAllItems();
	pGrid->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(230,230,230));
	pGrid->SetFixedBkColor(RGB(100,100,100));
	pGrid->SetFixedTextColor(RGB(0,0,0));
	pGrid->SetGridLineColor(RGB(160,160,160));
	pGrid->SetGridLines(GVL_BOTH);

	pGrid->SetColumnCount(nColNum);
	pGrid->SetRowCount(nRowNum+1);
	pGrid->SetFixedRowCount(1);
	pGrid->SetFixedColumnCount(1);
	pGrid->SetColumnWidth(0,40);
	pGrid->ExpandColumnsToFit();

	pGrid->SetEditable(TRUE);
	pGrid->EnableSelection(TRUE);

	//header
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;

		Item.row = 0;
		Item.col = 0;
		Item.strText = "idx";
		pGrid->SetItem(&Item);
		Item.col = 1;
		Item.strText = "Recipe Name";
		pGrid->SetItem(&Item);
	}

	for (int i = 0 ; i<GRID_MAX_COUNT_ROW ; i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;
		Item.col = 0;
		Item.row = i+1;
		strTemp.Format("%d",i+1);
		Item.strText = strTemp;
		pGrid->SetItem(&Item);
	}

	pGrid->Invalidate(FALSE);
}

void CRecipeItemChangeDlg::SetInitGridSelectedRecipe()
{
	CGridCtrl* pGrid = &m_gridSelectedRecipe;
	const int nRowNum = GRID_MAX_COUNT_ROW;
	const int nColNum = 2;

	CString strTemp = "";
	pGrid->DeleteAllItems();
	pGrid->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(230,230,230));
	pGrid->SetFixedBkColor(RGB(100,100,100));
	pGrid->SetFixedTextColor(RGB(0,0,0));
	pGrid->SetGridLineColor(RGB(160,160,160));
	pGrid->SetGridLines(GVL_BOTH);

	pGrid->SetColumnCount(nColNum);
	pGrid->SetRowCount(nRowNum+1);
	pGrid->SetFixedRowCount(1);
	pGrid->SetFixedColumnCount(1);
	pGrid->SetColumnWidth(0,40);
	pGrid->ExpandColumnsToFit();

	pGrid->SetEditable(FALSE);
	pGrid->SetSingleRowSelection(TRUE);
	pGrid->SetSingleColSelection(TRUE);

	//header
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;

		Item.row = 0;
		Item.col = 0;
		Item.strText = "idx";
		pGrid->SetItem(&Item);
		Item.col = 1;
		Item.strText = "Recipe Name";
		pGrid->SetItem(&Item);
	}

	for (int i = 0 ; i<GRID_MAX_COUNT_ROW ; i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;
		Item.col = 0;
		Item.row = i+1;
		strTemp.Format("%d",i+1);
		Item.strText = strTemp;
		pGrid->SetItem(&Item);
	}

	pGrid->Invalidate(FALSE);
}

void CRecipeItemChangeDlg::SetInitGridRecipeItem()
{
	CGridCtrl* pGrid = &m_gridRecipeItem;
	const int nRowNum = GRID_MAX_COUNT_ROW;
	const int nColNum = 4;

	CString strTemp = "";
	pGrid->DeleteAllItems();
	pGrid->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(230,230,230));
	pGrid->SetFixedBkColor(RGB(100,100,100));
	pGrid->SetFixedTextColor(RGB(0,0,0));
	pGrid->SetGridLineColor(RGB(160,160,160));
	pGrid->SetGridLines(GVL_BOTH);

	pGrid->SetColumnCount(nColNum);
	pGrid->SetRowCount(nRowNum+1);
	pGrid->SetFixedRowCount(1);
	pGrid->SetFixedColumnCount(1);
	pGrid->SetColumnWidth(0,35);
	pGrid->SetColumnWidth(1,35);
	pGrid->SetColumnWidth(2,235);
	pGrid->ExpandLastColumn();

	pGrid->SetEditable(TRUE);
	pGrid->EnableSelection(TRUE);

	//header
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;

		Item.row = 0;
		Item.col = 0;
		Item.strText = "idx";
		pGrid->SetItem(&Item);
		
		Item.col = 1;
		Item.strText = "Use";
		pGrid->SetItem(&Item);
		
		Item.col = 2;
		Item.strText = "Recipe Item";
		pGrid->SetItem(&Item);

		Item.col = 3;
		Item.strText = "Recipe Value";
		pGrid->SetItem(&Item);
	}

	for (int i = 0 ; i<GRID_MAX_COUNT_ROW ; i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;
		Item.col = 0;
		Item.row = i+1;
		strTemp.Format("%d",i+1);
		Item.strText = strTemp;
		pGrid->SetItem(&Item);
		pGrid->SetCellType(i+1, 1, RUNTIME_CLASS(CGridCellCheck));

	}

	pGrid->Invalidate(FALSE);
}
void CRecipeItemChangeDlg::OnBnClickedRadioAoi()
{
	for (int i = 1 ;i<GRID_MAX_COUNT_ROW;i++)
	{
		m_gridRecipeItem.SetItemText(i,1,"");
		m_gridAllRecipe.SetItemText(i,1,"");
		m_gridSelectedRecipe.SetItemText(i,1,"");
	}

	m_vectotalRecipe.clear();
	m_vecSelectedRecipe.clear();
	m_vectotalRecipe.clear();

	CString strRecipePath = "";
	CString strDirectoryName = "" , strDirectoryPath = "";
	int		nCount = 0;
	CFileFind finder;

	_RecipeInfo RecipeData;
	strRecipePath.Format("\\\\126.100.100.1\\C\\AOIServer\\Recipes\\");
	//strRecipePath.Format("\\\\127.0.0.1\\C\\AOIServer\\Recipes\\");
	BOOL bWorking = finder.FindFile(strRecipePath + "*.*");
	
	m_vectotalRecipe.clear();
	m_vecSelectedRecipe.clear();

	while(bWorking)
	{
		bWorking = finder.FindNextFile();

		if(finder.IsDirectory())
		{
			strDirectoryName =  finder.GetFileName();
			strDirectoryPath.Format("%s\\%s\\AOIGlass.rcp",strRecipePath,strDirectoryName);
			

			RecipeData.m_nindex			= nCount;
			RecipeData.strRecipeName	= strDirectoryName;
			RecipeData.strRecipePath	= strDirectoryPath;
			RecipeData.bSelected		= FALSE;

			m_vectotalRecipe.push_back(RecipeData);
		}
		nCount++;
	}

	for (int i = 0 ; i<m_vectotalRecipe.size();i++)
	{
		RecipeData = m_vectotalRecipe.at(i);
		m_gridAllRecipe.SetItemText(i+1,1,RecipeData.strRecipeName);
	}
	m_gridAllRecipe.Invalidate(FALSE);
}
void CRecipeItemChangeDlg::OnBnClickedButton1()
{
	int nCount = 0;

	m_vecSelectedRecipe.clear();
	for (int i = 0 ;i< m_vectotalRecipe.size() ; i++)
	{
		for (int j = 0;j<m_vectotalRecipe.size() ;j++)
		{
			if (m_gridAllRecipe.IsCellSelected(i+1,1))
			{
				if (m_gridAllRecipe.GetItemText(i+1,1) == m_vectotalRecipe.at(j).strRecipeName && m_vectotalRecipe.at(j).bSelected == FALSE)
				{
					m_vectotalRecipe.at(j).bSelected = TRUE;
					break;
				}
			}
		}
	}
	for (int i = 0 ;i< m_vectotalRecipe.size() ; i++)
	{
		if (m_vectotalRecipe.at(i).bSelected == TRUE)
		{
			m_vecSelectedRecipe.push_back(m_vectotalRecipe.at(i));
			continue;
		}
	}
	
	//제일 왼쪽 GridCtrl
	for (int i = 0 ; i<m_vectotalRecipe.size();i++)
	{
		m_gridAllRecipe.SetItemText(i+1,1,"");
	}

	for (int i = 0 ; i<m_vectotalRecipe.size();i++)
	{
		if (m_vectotalRecipe.at(i).bSelected == FALSE)
		{
			m_gridAllRecipe.SetItemText(nCount+1,1,m_vectotalRecipe.at(i).strRecipeName);
			nCount++;
		}
	}

	//가운데 GridCtrl
	nCount = 0;
	for (int i = 0 ; i<m_vectotalRecipe.size();i++)
	{
		m_gridSelectedRecipe.SetItemText(i+1,1,"");
	}

	for (int i = 0 ; i<m_vecSelectedRecipe.size();i++)
	{
		if (m_vecSelectedRecipe.at(i).bSelected == TRUE)
		{
			m_gridSelectedRecipe.SetItemText(nCount+1,1,m_vecSelectedRecipe.at(i).strRecipeName);
			nCount++;
		}
	}

	m_gridAllRecipe.Invalidate(FALSE);
	m_gridSelectedRecipe.Invalidate(FALSE);

}

void CRecipeItemChangeDlg::OnBnClickedButton2()
{
	int nCount = 0;

	m_vecSelectedRecipe.clear();
	for (int i = 0 ;i< m_vectotalRecipe.size() ; i++)
	{
		for (int j = 0;j<m_vectotalRecipe.size() ;j++)
		{
			if (m_gridSelectedRecipe.IsCellSelected(i+1,1))
			{
				if (m_gridSelectedRecipe.GetItemText(i+1,1) == m_vectotalRecipe.at(j).strRecipeName && m_vectotalRecipe.at(j).bSelected == TRUE)
				{
					m_vectotalRecipe.at(j).bSelected = FALSE;
					break;
				}
			}
		}
	}
	for (int i = 0 ;i< m_vectotalRecipe.size() ; i++)
	{
		if (m_vectotalRecipe.at(i).bSelected == TRUE)
		{
			m_vecSelectedRecipe.push_back(m_vectotalRecipe.at(i));
			continue;
		}
	}

	//제일 왼쪽 GridCtrl
	for (int i = 0 ; i<m_vectotalRecipe.size();i++)
	{
		m_gridAllRecipe.SetItemText(i+1,1,"");
	}

	for (int i = 0 ; i<m_vectotalRecipe.size();i++)
	{
		if (m_vectotalRecipe.at(i).bSelected == FALSE)
		{
			m_gridAllRecipe.SetItemText(nCount+1,1,m_vectotalRecipe.at(i).strRecipeName);
			nCount++;
		}
	}

	//가운데 GridCtrl
	nCount = 0;
	for (int i = 0 ; i<m_vectotalRecipe.size();i++)
	{
		m_gridSelectedRecipe.SetItemText(i+1,1,"");
	}

	for (int i = 0 ; i<m_vecSelectedRecipe.size();i++)
	{
		if (m_vecSelectedRecipe.at(i).bSelected == TRUE)
		{
			m_gridSelectedRecipe.SetItemText(nCount+1,1,m_vecSelectedRecipe.at(i).strRecipeName);
			nCount++;
		}
	}

	m_gridAllRecipe.Invalidate(FALSE);
	m_gridSelectedRecipe.Invalidate(FALSE);
}

void CRecipeItemChangeDlg::OnBnClickedGirdCtrl()
{
	ClearFillData();
	CCellID nCellIndx = m_gridSelectedRecipe.GetFocusCell();
	int nID = GetCheckedRadioButton(IDC_RADIO_AOI,IDC_RADIO_REVIEW);

	if (nID == IDC_RADIO_AOI)
	{
		int nSelected = 0;
		std::ifstream	SelectedFile;
		char			sLine[1024] = {0,};
		CString			strValue = "" , strData = "";
		CHMConfigFile configFile;

		if (nCellIndx.row > m_vecSelectedRecipe.size())
			return;

		for (int i = 1 ;i< m_vecSelectedRecipe.size() ; i++)
		{
			nSelected++;
			if (m_gridSelectedRecipe.IsCellSelected(i+1,1))
				break;
			else if (m_vecSelectedRecipe.size()-1 == i)
			{			
				nSelected = 0;
				break;
			}
		}

		if (m_vecSelectedRecipe.size() == 0)
			return; 

		SetDlgItemText(IDC_STATIC_RCP_NAME,m_vecSelectedRecipe.at(nSelected).strRecipeName);

		CString strRecipePath = m_vecSelectedRecipe.at(nSelected).strRecipePath;
		BOOL bOpen = configFile.SetFileName((LPSTR)(LPCTSTR)strRecipePath);
		SelectedFile.open(strRecipePath, std::ios::in /*| std::ios::nocreate*/);

		if (SelectedFile.is_open() && bOpen == TRUE)
		{
			for (int i=0;i<GRID_MAX_COUNT_ROW;i++)
			{
				SelectedFile.getline(sLine, sizeof(sLine));
				AfxExtractSubString(strValue,sLine,0,'=');	
				configFile.GetItemValue((LPSTR)(LPCTSTR)strValue,strData,0);
				//Item Name & Data
				m_gridRecipeItem.SetItemText(i+1,2,(LPCTSTR)strValue);
				m_gridRecipeItem.SetItemText(i+1,3,(LPCTSTR)strData);
			}	
		}
		else
			AfxMessageBox("Recipe File is not exist");

		m_gridRecipeItem.Invalidate(FALSE);

	}

	if (nID == IDC_RADIO_REVIEW)
	{
		int nSelected = 0;
		std::ifstream	SelectedFile;
		char			sLine[1024] = {0,};
		CString			strValue = "" , strData = "";
		CMConfig		configFile;

		if (nCellIndx.row > m_vecSelectedRecipe.size())
			return;
		
		for (int i = 1 ;i< m_vecSelectedRecipe.size() ; i++)
		{
			nSelected++;
			if (m_gridSelectedRecipe.IsCellSelected(i+1,1))
				break;
			else if (m_vecSelectedRecipe.size()-1 == i)
			{			
				nSelected = 0;
				break;
			}
		}

		if (m_vecSelectedRecipe.size() == 0)
			return; 

		SetDlgItemText(IDC_STATIC_RCP_NAME,m_vecSelectedRecipe.at(nSelected).strRecipeName);

		CString strRecipePath = m_vecSelectedRecipe.at(nSelected).strRecipePath;
		BOOL bOpen = configFile.Read(strRecipePath);
		SelectedFile.open(strRecipePath, std::ios::in /*| std::ios::nocreate*/);

		if (SelectedFile.is_open() && bOpen == TRUE)
		{
			for (int i=0;i<GRID_MAX_COUNT_ROW;i++)
			{
				SelectedFile.getline(sLine, sizeof(sLine));
				AfxExtractSubString(strValue,sLine,0,'=');	
				configFile.GetItemValue((LPSTR)(LPCTSTR)strValue,strData,0);
				//Item Name & Data
				m_gridRecipeItem.SetItemText(i+1,2,(LPCTSTR)strValue);
				m_gridRecipeItem.SetItemText(i+1,3,(LPCTSTR)strData);
			}	
		}
		else
			AfxMessageBox("Recipe File is not exist");

		m_gridRecipeItem.Invalidate(FALSE);
	}

	//UpdateData(FALSE);

	return;
}

void CRecipeItemChangeDlg::ClearFillData()
{
	GV_ITEM Item;
	CString strValue;
	Item.mask = GVIF_TEXT;

	CGridCtrl* pGrid = &m_gridRecipeItem;

	int i = pGrid->GetFixedRowCount();
	for(i; i<pGrid->GetRowCount(); i++)
	{
		for(int j=pGrid->GetFixedColumnCount(); j<pGrid->GetColumnCount(); j++)
		{
			Item.row = i;
			Item.col = j;
			Item.strText = "";
			pGrid->SetItem(&Item);
		}
	}
	m_gridRecipeItem.SetRowCount(GRID_MAX_COUNT_ROW);
	pGrid->Invalidate(FALSE);
}


void CRecipeItemChangeDlg::OnBnClickedButtonFind()
{
	UpdateData(TRUE);
	CString strValue;
	CString strValueChar = "";
	int nMatchCount = 0;
	strValue = m_strFindItem;
	int i = 0;

	CCellID cellid = m_gridRecipeItem.GetFocusCell();
	int nID = GetCheckedRadioButton(IDC_RADIO_ITEM,IDC_RADIO_Value);

	if (nID == IDC_RADIO_ITEM)
	{
		for(i = cellid.row+1; i<m_gridRecipeItem.GetRowCount();i++)
		{
			strValueChar = m_gridRecipeItem.GetItemText(i,2);

			nMatchCount = strValueChar.Find(strValue.MakeUpper());

			if (nMatchCount > 0)
			{

				SCROLLINFO si;
				m_gridRecipeItem.GetScrollInfo(SB_VERT,&si);

				COLORREF CellColor = RGB(70,70,70);
				m_gridRecipeItem.SetFocusCell(i,2);
				m_gridRecipeItem.EnsureVisible(i,2);
				m_gridRecipeItem.SetSelectedRange(i, 2, i, 2, TRUE);

				m_gridRecipeItem.Refresh();

				return;
			}
		}
	}

	for(i = cellid.row+1; i<m_gridRecipeItem.GetRowCount();i++)
	{
		if (strValue == m_gridRecipeItem.GetItemText(i,2))
		{

			SCROLLINFO si;
			m_gridRecipeItem.GetScrollInfo(SB_VERT,&si);

			COLORREF CellColor = RGB(70,70,70);
			m_gridRecipeItem.SetFocusCell(i,2);
			m_gridRecipeItem.EnsureVisible(i,2);
			m_gridRecipeItem.SetSelectedRange(i, 2, i, 2, TRUE);

			m_gridRecipeItem.Refresh();

			return;
		}
	}

	for(i = cellid.row+1; i<m_gridRecipeItem.GetRowCount();i++)
	{
		if (strValue == m_gridRecipeItem.GetItemText(i,3))
		{

			SCROLLINFO si;
			m_gridRecipeItem.GetScrollInfo(SB_VERT,&si);

			COLORREF CellColor = RGB(70,70,70);
			m_gridRecipeItem.SetFocusCell(i,2);
			m_gridRecipeItem.EnsureVisible(i,2);
			m_gridRecipeItem.SetSelectedRange(i, 2, i, 2, TRUE);

			m_gridRecipeItem.Refresh();

			return;
		}
	}
	
	if (i == m_gridRecipeItem.GetRowCount())
	{
		m_gridRecipeItem.SetFocusCell(0,2);
		m_gridRecipeItem.EnsureVisible(0,2);
		m_gridRecipeItem.SetSelectedRange(0, 2, 0, 2, TRUE);
	}
}
void CRecipeItemChangeDlg::OnBnClickedButtonSelectedChange()
{
	AfxBeginThread(CopyThreadFunc, this);	
}

void CRecipeItemChangeDlg::OnBnClickedButtonIpSetting()
{
	m_DlgRecipeChangeIPSetting = new CRecipeChangeIPSettingDlg(this);
	m_DlgRecipeChangeIPSetting->Create(CRecipeChangeIPSettingDlg::IDD, this);
	m_DlgRecipeChangeIPSetting->ShowWindow(SW_SHOW);
}

void CRecipeItemChangeDlg::OnBnClickedRadioReview()
{
	for (int i = 1 ;i<GRID_MAX_COUNT_ROW;i++)
	{
		m_gridRecipeItem.SetItemText(i,1,"");
		m_gridAllRecipe.SetItemText(i,1,"");
		m_gridSelectedRecipe.SetItemText(i,1,"");
	}

	m_vectotalRecipe.clear();
	m_vecSelectedRecipe.clear();
	m_vectotalRecipe.clear();

	CString strRecipePath = "";
	CString strPathName = "" , strRecipePath2 = "";
	int		nCount = 0;
	CFileFind finder;

	_RecipeInfo RecipeData;
	strRecipePath.Format("\\\\126.100.100.210\\C\\DIT_Review\\Recipe\\");
	//strRecipePath.Format("\\\\127.0.0.1\\C\\DIT_Review\\Recipe\\");
	//strRecipePath.Format("C:\\AOIServer\\Recipes");
	BOOL bWorking = finder.FindFile(strRecipePath + "*.*");

	m_vectotalRecipe.clear();
	m_vecSelectedRecipe.clear();

	while(bWorking)
	{
		bWorking = finder.FindNextFile();

		strPathName =  finder.GetFileName();
		strRecipePath2.Format("%s%s",strRecipePath,strPathName);

		RecipeData.m_nindex			= nCount;
		RecipeData.strRecipeName	= strPathName;
		RecipeData.strRecipePath	= strRecipePath2;
		RecipeData.bSelected		= FALSE;

		m_vectotalRecipe.push_back(RecipeData);

		nCount++;
	}

	for (int i = 0 ; i<m_vectotalRecipe.size();i++)
	{
		RecipeData = m_vectotalRecipe.at(i);
		m_gridAllRecipe.SetItemText(i+1,1,RecipeData.strRecipeName);
	}
	m_gridAllRecipe.Invalidate(FALSE);
}

UINT CRecipeItemChangeDlg::CopyThreadFunc( LPVOID pParam )
{
	CRecipeItemChangeDlg *pMain = static_cast<CRecipeItemChangeDlg*>(pParam);
	if(pMain == NULL)	return 0;


	pMain->CopyToAllMachine();	
	

	return 0;
}

void CRecipeItemChangeDlg::CopyToAllMachine()
{

	GetDlgItem(IDC_BUTTON_SELECTED_CHANGE)->EnableWindow(FALSE);

	CProgressCtrl *barctrl = (CProgressCtrl*)AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_PROGRESS_COPY);

	barctrl->SetRange(0,m_vecSelectedRecipe.size()* 18);
	barctrl->SetPos(0);

	CString strValue;
	CString strTargetPath = "";
	CGridCellCheck *pCell;
	_RecipeDataInfo RecipeData;
	int nProgressCount = 0;

	int nID = GetCheckedRadioButton(IDC_RADIO_AOI,IDC_RADIO_REVIEW);

	if (nID == IDC_RADIO_AOI)
	{
		CHMConfigFile configFile;
		CHMConfigFile SettingFile;

		m_vecChangedRecipeData.clear();

		for(int i = 0; i<m_gridRecipeItem.GetRowCount()-1;i++)
		{
			pCell = (CGridCellCheck*)m_gridRecipeItem.GetCell(i+1,1);

			if (pCell->GetCheck() == TRUE)
			{
				RecipeData.bCheck		= TRUE;
				RecipeData.nindex		= i;
				RecipeData.strItem		= m_gridRecipeItem.GetItemText(i+1,2);
				RecipeData.strData		= m_gridRecipeItem.GetItemText(i+1,3);

				m_vecChangedRecipeData.push_back(RecipeData);
			}
		}

		BOOL bOpen = FALSE;
		CString stritem = "";
		CString strData = "";

		for (int i = 0;i<m_vecSelectedRecipe.size();i++)
		{
			BOOL bOpen = configFile.SetFileName((LPSTR)(LPCTSTR)m_vecSelectedRecipe.at(i).strRecipePath);

			if (bOpen)
			{
				for (int j =0 ; j<m_vecChangedRecipeData.size();j++)
				{
					stritem = m_vecChangedRecipeData.at(j).strItem;
					strData = m_vecChangedRecipeData.at(j).strData;

					configFile.SetItemValue((LPSTR)(LPCTSTR)stritem,(LPSTR)(LPCTSTR)strData);

					nProgressCount++;

					barctrl->SetPos(nProgressCount);
				}
			}

		}

		BOOL bUse = FALSE;
		CString strItem1;
		CString strData1;
		BOOL	bCheckPC = FALSE;
		CString strTargetPath = "";

		CString strConfigPath = CurrentPath() + ".cfg";

		SettingFile.SetFileName((LPSTR)(LPCTSTR)strConfigPath);
		SettingFile.GetItemValue("NETWROK_USE" , bUse);

		if (bUse == FALSE)
		{
			barctrl->SetPos(m_vecSelectedRecipe.size()* 18);
			GetDlgItem(IDC_BUTTON_SELECTED_CHANGE)->EnableWindow(TRUE);

			return;
		}

		if (bUse)
		{
			for (int nPc = 0 ; nPc<18;nPc++)
			{
				strItem1.Format("AOI_IP_Setting_%d",nPc);
				SettingFile.GetItemValue((LPSTR)(LPCTSTR)strItem1,strData1);

				strItem1.Format("AOI_CHECK_Setting_%d",nPc);
				SettingFile.GetItemValue((LPSTR)(LPCTSTR)strItem1,bCheckPC);

				barctrl->SetPos(m_vecSelectedRecipe.size() * nPc);

				if (strData1 == "")
					continue;

				if (bCheckPC == FALSE)
					continue;

				strData1 = "\\\\" + strData1;

				for (int i = 0;i<m_vecSelectedRecipe.size();i++)
				{
					strTargetPath.Format("%s\\c\\AOIServer\\Recipes\\%s\\AOIGlass.rcp",strData1,m_vecSelectedRecipe.at(i).strRecipeName);
					configFile.SetFileName((LPSTR)(LPCTSTR)strTargetPath);

					for (int j =0 ; j<m_vecChangedRecipeData.size();j++)
					{
						stritem = m_vecChangedRecipeData.at(j).strItem;
						strData = m_vecChangedRecipeData.at(j).strData;
						configFile.SetItemValue((LPSTR)(LPCTSTR)stritem,(LPSTR)(LPCTSTR)strData);

						nProgressCount++;

						barctrl->SetPos(nProgressCount);
					}
				}	
			}
		}
	}
	else
	{
		CMConfig configFile;
		CHMConfigFile SettingFile;

		m_vecChangedRecipeData.clear();

		for(int i = 0; i<m_gridRecipeItem.GetRowCount()-1;i++)
		{
			pCell = (CGridCellCheck*)m_gridRecipeItem.GetCell(i+1,1);

			if (pCell->GetCheck() == TRUE)
			{
				RecipeData.bCheck		= TRUE;
				RecipeData.nindex		= i;
				RecipeData.strItem		= m_gridRecipeItem.GetItemText(i+1,2);
				RecipeData.strData		= m_gridRecipeItem.GetItemText(i+1,3);

				m_vecChangedRecipeData.push_back(RecipeData);
			}
		}

		barctrl->SetRange(0,m_vecSelectedRecipe.size()* 18);

		BOOL bOpen = FALSE;
		CString stritem = "";
		CString strData = "";
		CString strTargetPath = "";
		for (int i = 0;i<m_vecSelectedRecipe.size();i++)
		{
			BOOL bOpen = configFile.Read(m_vecSelectedRecipe.at(i).strRecipePath);

			if (bOpen)
			{
				for (int j =0 ; j<m_vecChangedRecipeData.size();j++)
				{
					stritem = m_vecChangedRecipeData.at(j).strItem;
					strData = m_vecChangedRecipeData.at(j).strData;

					configFile.SetItemValue(stritem,strData);
				}
				configFile.Write(m_vecSelectedRecipe.at(i).strRecipePath);
			
				strTargetPath.Format("%s",m_vecSelectedRecipe.at(i).strRecipePath);
				strTargetPath.Replace("rcp","tmp");
				DeleteFile(strTargetPath);

			}	
		}

		BOOL bUse = FALSE;
		CString strItem1;
		CString strData1;
		BOOL	bCheckPC = FALSE;

		CString strConfigPath = CurrentPath() + ".cfg";

		SettingFile.SetFileName((LPSTR)(LPCTSTR)strConfigPath);
		SettingFile.GetItemValue("NETWROK_USE" , bUse);

		if (bUse == FALSE)
		{
			barctrl->SetPos(m_vecSelectedRecipe.size()* 18);
			GetDlgItem(IDC_BUTTON_SELECTED_CHANGE)->EnableWindow(TRUE);

			return;
		}

		if (bUse)
		{
			for (int nPc = 0 ; nPc<18;nPc++)
			{
				strItem1.Format("Review_IP_Setting_%d",nPc);
				SettingFile.GetItemValue((LPSTR)(LPCTSTR)strItem1,strData1);

				strItem1.Format("Review_CHECK_Setting_%d",nPc);
				SettingFile.GetItemValue((LPSTR)(LPCTSTR)strItem1,bCheckPC);

				barctrl->SetPos(m_vecSelectedRecipe.size() * nPc);

				if (strData1 == "")
					continue;

				if (bCheckPC == FALSE)
					continue;

				strData1 = "\\\\" + strData1;

				for (int i = 0;i<m_vecSelectedRecipe.size();i++)
				{
					strTargetPath.Format("%s\\c\\DIT_Review\\Recipe\\%s.rcp",strData1,m_vecSelectedRecipe.at(i).strRecipeName);
					//strTargetPath.Format("\\\\127.0.0.1\\c\\DIT_Review\\Recipe\\%s",m_vecSelectedRecipe.at(i).strRecipeName);

					configFile.Read(strTargetPath);

					for (int j =0 ; j<m_vecChangedRecipeData.size();j++)
					{
						stritem = m_vecChangedRecipeData.at(j).strItem;
						strData = m_vecChangedRecipeData.at(j).strData;
						configFile.SetItemValue((LPSTR)(LPCTSTR)stritem,(LPSTR)(LPCTSTR)strData);
					}

					configFile.Write(strTargetPath);
					strTargetPath.Replace("rcp","tmp");
					DeleteFile(strTargetPath);
				}	
			}
		}
	}

	barctrl->SetPos(m_vecSelectedRecipe.size()* 18);

	GetDlgItem(IDC_BUTTON_SELECTED_CHANGE)->EnableWindow(TRUE);

}

CString CRecipeItemChangeDlg::CurrentPath()
{
	CString strTempPath;
	TCHAR szpath[MAX_PATH+1];
	::GetModuleFileName(AfxGetInstanceHandle(),szpath,MAX_PATH);
	strTempPath = szpath;
	strTempPath = strTempPath.Mid(0,strTempPath.GetLength()-4);


	return strTempPath;
}
void CRecipeItemChangeDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnClose();
}

BOOL CRecipeItemChangeDlg::PreTranslateMessage( MSG* pMsg )
{
	// ESC 키
	if((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE))
	{
		// 여기에 원하는 동작의 코드를 삽입
		return true;
	}

	// 엔터키
	if((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
	}

	if((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == 115))
	{
		OnBnClickedButtonFind();
		return true;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

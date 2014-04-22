
// RP_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RP_MFC.h"
#include "RP_MFCDlg.h"
#include "RectangleContainer.h"
#include "ExtentedPolygon.h"
#include "cad_helper.h"
#include "RandomPolygonGen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRP_MFCDlg 对话框




CRP_MFCDlg::CRP_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRP_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRP_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRP_MFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CRP_MFCDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRP_MFCDlg 消息处理程序

BOOL CRP_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRP_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRP_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRP_MFCDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	int maxEdge = 4;
	int minRadius = 60;
	int maxRadius = 150;
	double minCoverageRadio = 0.20;
	int width = 500;
	int height = 500;
	int loopCount = width*height; 
	int stepX = -1;
	int stepY = 1;
	int expandStep = 3;
	int totalLoop = 10000;


	long start = 0, finish = 0;
	double  duration = 0;
	start = clock();
	CRectangleContainer* container = new CRectangleContainer(0,0,width,height);
	//Cad_Helper::PostToModelSpace(container->getEntity());

	int iTotalCount = 0;
	while(true)
	{
		iTotalCount++;
		if(iTotalCount > totalLoop)
		{
			break;
		}
		try
		{ 
			bool result = false;
			CExentedPolygon* polygon = CRandonPolygonGen::randWithinBox(container,maxEdge,minRadius,maxRadius);
			if(polygon == NULL)
			{
				continue;
			}
			result = container->canSafePut(polygon);
			if(result)
			{
				printf("_1_");
				container->put(polygon);
			}
			else// 失败投放后，进行20次更正投放
			{

				for(int i = 0; i < 20; ++i)
				{
					srand((unsigned)time(NULL));
					int deltX = stepX + (rand()%3);
					int deltY = stepY;

					polygon->treanslate(deltX,deltY);
					result = container->canSafePut(polygon);
					if(result)
					{
						printf("_2_");
						container->put(polygon);
						break;
					} 
				}//end for
			} //end else  

			// fill aswsome position
			if(CRandonPolygonGen::Fill(container,loopCount,minRadius,maxRadius,expandStep,maxEdge,minCoverageRadio))
			{

				break;
			}

		}//end try
		catch(...)
		{
			printf("an error ocurre");
		}



		if(container->getCoverageRatio() > minCoverageRadio)
		{
			break;
		}

	}//end while

	finish = clock();
	duration = (finish - start)/1000;
	char buffer[128] = {0};
	sprintf(buffer, "Total cost: %f seconds CoverageRatio%.2f%%\n", duration ,container->getCoverageRatio()*100);  
	OutputDebugStringA(buffer);		
}

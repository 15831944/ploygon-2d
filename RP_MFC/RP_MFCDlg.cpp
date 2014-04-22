
// RP_MFCDlg.cpp : ʵ���ļ�
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


// CRP_MFCDlg �Ի���




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


// CRP_MFCDlg ��Ϣ�������

BOOL CRP_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRP_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
			else// ʧ��Ͷ�ź󣬽���20�θ���Ͷ��
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

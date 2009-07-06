/*
 * cocoUpple.cpp : �u���������Ղ�v �A�v���P�[�V���� ���C��
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/cocoUpple.cpp $
 * 
 * 2     09/07/07 2:00 tsupo
 * 1.43��
 * 
 * 4     09/07/03 11:32 Tsujimura543
 * �f�o�b�O�p�̃��O�t�@�C�����o�͉\�ɂ���
 * 
 * 1     09/05/14 4:18 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/11/16 1:03 Tsujimura543
 * �\�[�X�R�[�h�𐮗� (�]���ȃR�����g���폜�A�Ȃ�)
 * 
 * 2     06/05/08 14:45 Tsujimura543
 * F1�L�[�������Ɂu�󋵈ˑ��w���v�v��\�����悤�Ƃ���̂�}������悤�ɂ�
 * ��
 * 
 * 1     04/12/16 19:22 Tsujimura543
 * �ŏ��̔�
 */

#include "cocoUpple.h"
#include "cocoUppleDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/uploadFile/cocoUpple/cocoUpple.cpp 2     09/07/07 2:00 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleApp

BEGIN_MESSAGE_MAP(CCocoUppleApp, CWinApp)
	//{{AFX_MSG_MAP(CCocoUppleApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleApp �N���X�̍\�z

CCocoUppleApp::CCocoUppleApp()
{
    m_verbose   = false;
    m_verboseFp = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CCocoUppleApp �I�u�W�F�N�g

CCocoUppleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleApp �N���X�̏�����

BOOL CCocoUppleApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	CCocoUppleDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
	}
	else if (nResponse == IDCANCEL) {
	}

	return FALSE;
}

void CCocoUppleApp::WinHelp(DWORD dwData, UINT nCmd) 
{
 // CWinApp::WinHelp(dwData, nCmd);
}

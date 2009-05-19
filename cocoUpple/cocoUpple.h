/*
 *  cocoUpple.h : �u���������Ղ�v  ���C�� �w�b�_�[ �t�@�C��
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/cocoUpple.h $
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

#if !defined(AFX_COCOUPPLE_H__5A2673C7_F87E_42BC_8AAC_1D598BBD2AF0__INCLUDED_)
#define AFX_COCOUPPLE_H__5A2673C7_F87E_42BC_8AAC_1D598BBD2AF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN

#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>         // MFC �̊g������
#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �R���� �R���g���[�� �T�|�[�g
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �R���� �R���g���[�� �T�|�[�g
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "resource.h"		// ���C�� �V���{��

extern  "C" {
#include "xmlRPC.h"
}
#define MAX_BLOGS       10  /* ����V�X�e�����ő�ݒu�\blog�� (�R�R���O) */

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleApp:

class CCocoUppleApp : public CWinApp
{
public:
	CCocoUppleApp();

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CCocoUppleApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CCocoUppleApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_COCOUPPLE_H__5A2673C7_F87E_42BC_8AAC_1D598BBD2AF0__INCLUDED_)

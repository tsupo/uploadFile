/*
 * AboutDlg.h  : �u���������Ղ�v �Ő�(�o�[�W�����ԍ�)�\���_�C�A���O
 *                                                      �w�b�_�[ �t�@�C��
 *          written by H.Tsujimura  16 Dec 2004
 *
 * $Log: /comm/uploadFile/cocoUpple/AboutDlg.h $
 * 
 * 1     09/05/14 4:18 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/11/16 1:08 Tsujimura543
 * cocoUppleDlg.cpp ���番���Ɨ�������
 */

#if !defined(AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_)
#define AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	~CAboutDlg();

    HCURSOR m_hCursor;
    CFont   m_cFont;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnUploadfileWebUrl();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif  /* AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_ */

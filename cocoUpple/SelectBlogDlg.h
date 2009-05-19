/*
 * SelectBlogDlg.h : �u���������Ղ�v blog�I���_�C�A���O �w�b�_�[ �t�@�C��
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/SelectBlogDlg.h $
 * 
 * 1     09/05/14 4:18 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/11/16 1:03 Tsujimura543
 * �\�[�X�R�[�h�𐮗� (�]���ȃR�����g���폜�A�Ȃ�)
 * 
 * 1     04/12/16 19:22 Tsujimura543
 * �ŏ��̔�
 */

#if !defined(AFX_SELECTBLOGDLG_H__7DE291CB_FC37_43DF_B245_0F7EA8EBE4D6__INCLUDED_)
#define AFX_SELECTBLOGDLG_H__7DE291CB_FC37_43DF_B245_0F7EA8EBE4D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSelectBlogDlg �_�C�A���O

class CSelectBlogDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CSelectBlogDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    BLOGINF m_blogInfo[MAX_BLOGS];
    int     m_numOfBlogs;
    CString m_blogName;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSelectBlogDlg)
	enum { IDD = IDD_BLOGSELECT_DIALOG };
	CListBox	m_blogList;
	CString	m_blogID;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CSelectBlogDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSelectBlogDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkListBlog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SELECTBLOGDLG_H__7DE291CB_FC37_43DF_B245_0F7EA8EBE4D6__INCLUDED_)

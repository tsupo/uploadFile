/*
 * SelectBlogDlg.cpp : �u���������Ղ�v blog�I���_�C�A���O
 *                          �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/SelectBlogDlg.cpp $
 * 
 * 1     09/05/14 4:18 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/11/16 1:03 Tsujimura543
 * �\�[�X�R�[�h�𐮗� (�]���ȃR�����g���폜�A�Ȃ�)
 * 
 * 2     07/07/03 11:09 Tsujimura543
 * Visual Studio 2005 �ł̃r���h���ʂ𔽉f
 * 
 * 1     04/12/16 19:22 Tsujimura543
 * �ŏ��̔�
 */

#include "cocoUpple.h"
#include "SelectBlogDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/uploadFile/cocoUpple/SelectBlogDlg.cpp 1     09/05/14 4:18 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectBlogDlg �_�C�A���O

CSelectBlogDlg::CSelectBlogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectBlogDlg::IDD, pParent)
{
    m_numOfBlogs = 0;
    m_blogName   = _T( "" );

	//{{AFX_DATA_INIT(CSelectBlogDlg)
	m_blogID = _T("");
	//}}AFX_DATA_INIT
}

void CSelectBlogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectBlogDlg)
	DDX_Control(pDX, IDC_LIST_BLOG, m_blogList);
	DDX_LBString(pDX, IDC_LIST_BLOG, m_blogID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelectBlogDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectBlogDlg)
	ON_WM_SHOWWINDOW()
	ON_LBN_DBLCLK(IDC_LIST_BLOG, OnDblclkListBlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectBlogDlg ���b�Z�[�W �n���h��

void CSelectBlogDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        char    buf[BUFSIZ];
        int     i;

        for ( i = 0; i < m_numOfBlogs; i++ ) {
            sprintf( buf, "(%d) %s [blogID: %s]",
                     i + 1,
                     utf2sjis( m_blogInfo[i].blogName ),
                     m_blogInfo[i].blogID );
            m_blogList.AddString( buf );
        }
    }
}

void CSelectBlogDlg::OnDblclkListBlog() 
{
    OnOK();
}

BOOL CSelectBlogDlg::DestroyWindow() 
{
    size_t  sz    = m_blogID.GetLength();
    char    *save = new char[sz + 1];
    char    *temp = new char[sz + 1];

    strcpy( save, m_blogID );
    strcpy( temp, m_blogID );

    char    *p = strstr( temp, "[blogID: " );
    if ( p ) {
        p += 9;
        p[strlen(p) - 1] = '\0';
        m_blogID = p;
    }

    p = strchr( save, ')' );
    if ( p ) {
        p += 2;
        char    *q = strrchr( p, '[' );
        if ( q ) {
            q--;
            *q = '\0';
            m_blogName = p;
        }
    }

    delete [] temp;
    delete [] save;

	return CDialog::DestroyWindow();
}

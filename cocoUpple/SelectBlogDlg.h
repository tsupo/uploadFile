/*
 * SelectBlogDlg.h : 「ここあっぷる」 blog選択ダイアログ ヘッダー ファイル
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/SelectBlogDlg.h $
 * 
 * 1     09/05/14 4:18 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/11/16 1:03 Tsujimura543
 * ソースコードを整理 (余分なコメントを削除、など)
 * 
 * 1     04/12/16 19:22 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_SELECTBLOGDLG_H__7DE291CB_FC37_43DF_B245_0F7EA8EBE4D6__INCLUDED_)
#define AFX_SELECTBLOGDLG_H__7DE291CB_FC37_43DF_B245_0F7EA8EBE4D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSelectBlogDlg ダイアログ

class CSelectBlogDlg : public CDialog
{
// コンストラクション
public:
	CSelectBlogDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

    BLOGINF m_blogInfo[MAX_BLOGS];
    int     m_numOfBlogs;
    CString m_blogName;

// ダイアログ データ
	//{{AFX_DATA(CSelectBlogDlg)
	enum { IDD = IDD_BLOGSELECT_DIALOG };
	CListBox	m_blogList;
	CString	m_blogID;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSelectBlogDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージ マップ関数
	//{{AFX_MSG(CSelectBlogDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkListBlog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SELECTBLOGDLG_H__7DE291CB_FC37_43DF_B245_0F7EA8EBE4D6__INCLUDED_)

/*
 * cocoUppleDlg.h : 「ここあっぷる」 メインダイアログ ヘッダー ファイル
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/cocoUppleDlg.h $
 * 
 * 1     09/05/14 4:18 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     07/11/30 23:01 Tsujimura543
 * 本ダイアログにファイルをドロップすることで、ファイル名を受け取れるよう
 * にした
 * 
 * 6     07/11/16 1:03 Tsujimura543
 * ソースコードを整理 (余分なコメントを削除、など)
 * 
 * 5     06/03/14 23:40 Tsujimura543
 * ココログフリーにも対応した
 * 
 * 4     06/03/14 21:56 Tsujimura543
 * ファイルの削除機能を追加
 * 
 * 3     05/04/28 13:33 Tsujimura543
 * enum uploadResult と uploadFileToBlog() を追加
 * 
 * 2     05/01/04 15:12 Tsujimura543
 * ファイルアップロード関連メソッドを修正
 * 
 * 1     04/12/16 19:22 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_COCOUPPLEDLG_H__CAE0F7BF_00C0_4C0F_81B0_C6DFB9D55FBC__INCLUDED_)
#define AFX_COCOUPPLEDLG_H__CAE0F7BF_00C0_4C0F_81B0_C6DFB9D55FBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleDlg ダイアログ

class CCocoUppleDlg : public CDialog
{
// 構築
public:
	CCocoUppleDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CCocoUppleDlg)
	enum { IDD = IDD_COCOUPPLE_DIALOG };
	BOOL	m_useProxy;
	CString	m_blogID;
	CString	m_blogName;
	CString	m_htmlSrc;
	CString	m_password;
	CString	m_targetDirectory;
	CString	m_targetFile;
	CString	m_userName;
	CString	m_targetURL;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CCocoUppleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
private:
    enum uploadResult {
        upload_success,         // アップロード成功
        upload_failure,         // アップロード失敗
        upload_fileNotFound     // アップロードしようとしているファイルが見つからない
    };

    void    setBlogID();
    void    loadSetting();
    void    saveSetting();
    void    updateUploadButton();
    void    updateSelectBlogButton();
    void    updateDeleteButton();
    void    updateRadioButtons();
    void    getImageSize( const char *filename, int& height, int& width );
    uploadResult    uploadFileToBlog();

    char    m_settingFilename[MAX_PATH];
    BLOGINF m_blogInfo[MAX_BLOGS];
    int     m_numOfBlogs;
    bool    m_needToSave;
    bool    m_cocologFree;

protected:
	HICON m_hIcon;

	// メッセージ マップ関数
	//{{AFX_MSG(CCocoUppleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckUseproxy();
	afx_msg void OnKillfocusEditUsername();
	afx_msg void OnKillfocusEditPassword();
	afx_msg void OnKillfocusEditTargetDirectory();
	afx_msg void OnKillfocusEditTargetFile();
	afx_msg void OnButtonSelectBlog();
	afx_msg void OnButtonSelectFile();
	afx_msg void OnButtonUpload();
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateEditTargetFile();
	afx_msg void OnChangeEditUsername();
	afx_msg void OnChangeEditPassword();
	afx_msg void OnKillfocusEditUrlDelete();
	afx_msg void OnUpdateEditUrlDelete();
	afx_msg void OnButtonDelete();
	afx_msg void OnRadioCocolog();
	afx_msg void OnRadioCocologfree();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_COCOUPPLEDLG_H__CAE0F7BF_00C0_4C0F_81B0_C6DFB9D55FBC__INCLUDED_)

/*
 * cocoUpple.cpp : 「ここあっぷる」 アプリケーション メイン
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/cocoUpple.cpp $
 * 
 * 2     09/07/07 2:00 tsupo
 * 1.43版
 * 
 * 4     09/07/03 11:32 Tsujimura543
 * デバッグ用のログファイルを出力可能にした
 * 
 * 1     09/05/14 4:18 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/11/16 1:03 Tsujimura543
 * ソースコードを整理 (余分なコメントを削除、など)
 * 
 * 2     06/05/08 14:45 Tsujimura543
 * F1キー押下時に「状況依存ヘルプ」を表示しようとするのを抑制するようにし
 * た
 * 
 * 1     04/12/16 19:22 Tsujimura543
 * 最初の版
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
// CCocoUppleApp クラスの構築

CCocoUppleApp::CCocoUppleApp()
{
    m_verbose   = false;
    m_verboseFp = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CCocoUppleApp オブジェクト

CCocoUppleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleApp クラスの初期化

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

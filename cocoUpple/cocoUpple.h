/*
 *  cocoUpple.h : 「ここあっぷる」  メイン ヘッダー ファイル
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/cocoUpple.h $
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

#if !defined(AFX_COCOUPPLE_H__5A2673C7_F87E_42BC_8AAC_1D598BBD2AF0__INCLUDED_)
#define AFX_COCOUPPLE_H__5A2673C7_F87E_42BC_8AAC_1D598BBD2AF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "resource.h"		// メイン シンボル

extern  "C" {
#include "xmlRPC.h"
}
#define MAX_BLOGS       10  /* 同一システム内最大設置可能blog数 (ココログ) */

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleApp:

class CCocoUppleApp : public CWinApp
{
public:
	CCocoUppleApp();

// オーバーライド
	//{{AFX_VIRTUAL(CCocoUppleApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CCocoUppleApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_COCOUPPLE_H__5A2673C7_F87E_42BC_8AAC_1D598BBD2AF0__INCLUDED_)

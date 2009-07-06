/*
 * cocoUppleDlg.cpp : 「ここあっぷる」 メインダイアログ
 *                          インプリメンテーション ファイル
 *          written by H.Tsujimura  16 Dec 2004
 *
 * History:
 * $Log: /comm/uploadFile/cocoUpple/cocoUppleDlg.cpp $
 * 
 * 2     09/07/07 2:00 tsupo
 * 1.43版
 * 
 * 26    09/07/03 18:14 Tsujimura543
 * ユーザ名、パスワード変更時、設定ファイルに保存しないままになる不具合
 * を修正 (アップロード対象ブログを変更したときだけ保存されていた)
 * 
 * 25    09/07/03 11:32 Tsujimura543
 * デバッグ用のログファイルを出力可能にした
 * 
 * 1     09/05/14 4:18 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 24    08/02/07 19:51 Tsujimura543
 * 初期設定ファイルがまだ存在しない場合のみ、isUsedProxy() を呼ぶ
 * ようにした
 * 
 * 23    07/12/05 23:18 Tsujimura543
 * unbase64() の引数追加に伴う修正を実施
 * 
 * 22    07/11/30 23:01 Tsujimura543
 * 本ダイアログにファイルをドロップすることで、ファイル名を受け取れるよう
 * にした
 * 
 * 21    07/11/16 1:29 Tsujimura543
 * リソースから拾ってきたバージョン番号、リリース年月日を表示するようにし
 * た
 * 
 * 20    07/11/16 1:15 Tsujimura543
 * CAboutDlg を分離独立させた
 * 
 * 19    07/11/16 1:03 Tsujimura543
 * ソースコードを整理 (余分なコメントを削除、など)
 * 
 * 18    07/09/28 21:13 Tsujimura543
 * proxy 情報がおかしい場合のリカバリ処理を実装
 * 
 * 17    07/07/03 11:09 Tsujimura543
 * Visual Studio 2005 でのビルド結果を反映
 * 
 * 16    07/01/04 21:09 Tsujimura543
 * バージョン情報表示ダイアログから、サポート用Webページに飛べる
 * ようにした
 * 
 * 15    06/12/12 11:56 Tsujimura543
 * 1.33版
 * 
 * 14    06/12/12 11:55 Tsujimura543
 * 「ここあっぷる」起動後、いきなり deleteFile() する場合に、proxy モード
 * が未設定のままココログの管理画面に login しようとして login に失敗する
 * (connect に失敗する)不具合に対処 (proxyサーバ経由でのアクセス時)
 * 
 * 13    06/03/15 18:37 Tsujimura543
 * 1.21 版
 * 
 * 12    06/03/15 18:33 Tsujimura543
 * トップディレクトリにアップロードする場合の指定ディレクトリを .. だけで
 * なく ../ でもいいようにした
 * 
 * 11    06/03/14 23:40 Tsujimura543
 * ココログフリーにも対応した
 * 
 * 10    06/03/14 21:56 Tsujimura543
 * ファイルの削除機能を追加
 * 
 * 9     05/11/17 21:32 Tsujimura543
 * xmlRPC.dll の送信電文サイズの上限撤廃に伴い、送信ファイルサイズの
 * チェック処理を変更した
 * 
 * 8     05/11/11 19:07 Tsujimura543
 * 送信しようとしているファイルのサイズを前もってチェックするようにした
 * 
 * 7     05/04/28 13:37 Tsujimura543
 * (1) リファクタリングを実施 (アップロード処理本体を uploadFileToBlog()
 *     として分離独立)
 * (2) アップロード実行中は、マウスカーソルを砂時計形状にするようにした
 * 
 * 6     05/01/07 16:11 Tsujimura543
 * Ver 1.11 正式リリース版
 * 
 * 5     05/01/07 16:09 Tsujimura543
 * アップロード処理実行中は、「アップロード」ボタンを disable にするよう
 * にした
 * 
 * 4     05/01/07 16:07 Tsujimura543
 * アップロード失敗時、ダイアログを出して、アップロードに失敗したことを
 * 知らせるようにした
 * 
 * 3     05/01/04 15:55 Tsujimura543
 * 画像ファイルのサイズ計算処理再修正(JPGファイルの縦横が逆になっていた)
 * 
 * 2     05/01/04 15:10 Tsujimura543
 * 画像ファイルのサイズ計算処理を修正
 * 
 * 1     04/12/16 19:22 Tsujimura543
 * 最初の版
 */

#include "cocoUpple.h"
#include "cocoUppleDlg.h"
#include "AboutDlg.h"
#include "SelectBlogDlg.h"

#include <sys/stat.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/uploadFile/cocoUpple/cocoUppleDlg.cpp 2     09/07/07 2:00 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleDlg ダイアログ

CCocoUppleDlg::CCocoUppleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCocoUppleDlg::IDD, pParent)
{
    m_numOfBlogs = 0;
    m_needToSave = false;

    char    baseDir[MAX_PATH], *p, *q;

    p = __argv[0];
    q = strrchr( p, '/' );
    if ( !q )
        q = strrchr( p, '\\' );
    else {
        p = "./";
        q = p + 1;
    }
    strncpy( baseDir, p, q - p );
    baseDir[q - p] = '\0';

    strcpy( m_path, baseDir );
    sprintf( m_settingFilename, "%s/setting.inf", baseDir );
    m_cocologFree = false;

	//{{AFX_DATA_INIT(CCocoUppleDlg)
	m_useProxy = FALSE;
	m_blogID = _T("");
	m_blogName = _T("");
	m_htmlSrc = _T("");
	m_password = _T("");
	m_targetDirectory = _T("");
	m_targetFile = _T("");
	m_userName = _T("");
	m_targetURL = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCocoUppleDlg::~CCocoUppleDlg()
{
    CCocoUppleApp   *bp = (CCocoUppleApp *)AfxGetApp();

    if ( bp->m_verboseFp ) {
        time_t      t   = time( NULL );
        struct tm   *tm = localtime( &t );
        fprintf( bp->m_verboseFp,
                 "\n*** logging end:   %d/%02d/%02d %02d:%02d:%02d ***\n",
                 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                 tm->tm_hour, tm->tm_min, tm->tm_sec );
        fclose( bp->m_verboseFp );
        bp->m_verboseFp = NULL;
    }
}

void CCocoUppleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCocoUppleDlg)
	DDX_Check(pDX, IDC_CHECK_USEPROXY, m_useProxy);
	DDX_Text(pDX, IDC_EDIT_BLOGID, m_blogID);
	DDV_MaxChars(pDX, m_blogID, 32);
	DDX_Text(pDX, IDC_EDIT_BLOGNAME, m_blogName);
	DDV_MaxChars(pDX, m_blogName, 80);
	DDX_Text(pDX, IDC_EDIT_HTML, m_htmlSrc);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 12);
	DDX_Text(pDX, IDC_EDIT_TARGETDIRECTORY, m_targetDirectory);
	DDV_MaxChars(pDX, m_targetDirectory, 256);
	DDX_Text(pDX, IDC_EDIT_TARGETFILENAME, m_targetFile);
	DDV_MaxChars(pDX, m_targetFile, 256);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_userName);
	DDV_MaxChars(pDX, m_userName, 32);
	DDX_Text(pDX, IDC_EDIT_URL_DELETE, m_targetURL);
	DDV_MaxChars(pDX, m_targetURL, 384);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCocoUppleDlg, CDialog)
	//{{AFX_MSG_MAP(CCocoUppleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_USEPROXY, OnCheckUseproxy)
	ON_EN_KILLFOCUS(IDC_EDIT_USERNAME, OnKillfocusEditUsername)
	ON_EN_KILLFOCUS(IDC_EDIT_PASSWORD, OnKillfocusEditPassword)
	ON_EN_KILLFOCUS(IDC_EDIT_TARGETDIRECTORY, OnKillfocusEditTargetDirectory)
	ON_EN_KILLFOCUS(IDC_EDIT_TARGETFILENAME, OnKillfocusEditTargetFile)
	ON_BN_CLICKED(IDC_BUTTON_SELECTBLOG, OnButtonSelectBlog)
	ON_BN_CLICKED(IDC_BUTTON_SELECTFILE, OnButtonSelectFile)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, OnButtonUpload)
	ON_WM_SHOWWINDOW()
	ON_EN_UPDATE(IDC_EDIT_TARGETFILENAME, OnUpdateEditTargetFile)
	ON_EN_CHANGE(IDC_EDIT_USERNAME, OnChangeEditUsername)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, OnChangeEditPassword)
	ON_EN_KILLFOCUS(IDC_EDIT_URL_DELETE, OnKillfocusEditUrlDelete)
	ON_EN_UPDATE(IDC_EDIT_URL_DELETE, OnUpdateEditUrlDelete)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_RADIO_COCOLOG, OnRadioCocolog)
	ON_BN_CLICKED(IDC_RADIO_COCOLOGFREE, OnRadioCocologfree)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleDlg ユーティリティ メソッド

void
CCocoUppleDlg::setBlogID()
{
    int     numOfBlogs = MAX_BLOGS;
    int     r;
    CString save;

    save = m_blogID;
    if ( m_numOfBlogs == 0 ) {
        bool        done = false;
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        do {
            done = true;
            SetLastError( ERROR_SUCCESS );
            r = getBlogIDs( m_userName, m_password, &numOfBlogs, m_blogInfo );
            if ( (r == 0) && m_useProxy ) {
                DWORD   err = GetLastError();
                if ( err == XMLRPC_ERROR_CHANGED_PROXYINFO ) {
                    numOfBlogs = MAX_BLOGS;
                    done = false;
                }
            }
        } while ( !done );
    }
    else
        r = m_numOfBlogs;
    if ( r == 1 ) {
        m_blogID   = m_blogInfo[0].blogID;
        m_blogName = utf2sjis( m_blogInfo[0].blogName );
    }
    else if ( r > 1 ) {
        if ( m_numOfBlogs == 0 ) {
            /* blog 情報を blog ID の昇順にソート */
            BLOGINF tempInfo;
            for ( int i = 0; i < numOfBlogs - 1; i++ ) {
                for ( int j = i + 1; j < numOfBlogs; j++ ) {
                    if ( atol(m_blogInfo[i].blogID) > atol(m_blogInfo[j].blogID) ) {
                        tempInfo = m_blogInfo[i];
                        m_blogInfo[i] = m_blogInfo[j];
                        m_blogInfo[j] = tempInfo;
                    }
                }
            }

            m_numOfBlogs   = r;
        }

        /* blog ID 選択ダイアログを表示 */
        CSelectBlogDlg  d;

        d.m_numOfBlogs = r;
        for ( int i = 0; i < r; i++ )
            d.m_blogInfo[i] = m_blogInfo[i];

        int ret = d.DoModal();
        if ( ret == IDOK ) {
            m_blogID   = d.m_blogID;
            m_blogName = d.m_blogName;
        }
        else {
            m_blogID   = _T( "" );
            m_blogName = _T( "" );
        }
    }
    else {
        MessageBox( "ユーザ名、またはパスワードが違います。    ",
                    "blog ID 取得失敗", MB_ICONEXCLAMATION | MB_OK );
    }

    if ( save != m_blogID )
        m_needToSave = true;
}

void
CCocoUppleDlg::loadSetting()
{
    FILE    *fp;

    if ( ( fp = fopen( m_settingFilename, "r" ) ) != NULL ) {
        char    buf[BUFSIZ];
        char    *pp;
        CEdit   *ep;

        while ( ( pp = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            while ( (pp[strlen(pp) - 1] == '\n') ||
                    (pp[strlen(pp) - 1] == '\r')    )
                 pp[strlen(pp) - 1] = '\0';

            if ( !strncmp( pp, "userName: ", 10 ) ) {
                m_userName = pp + 10;
                ep = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME );
                ep->SetWindowText( m_userName );
                continue;
            }
            if ( !strncmp( pp, "password: ", 10 ) ) {
                size_t  sz = 0;

                m_password = unbase64( (unsigned char *)(pp + 10),
                                       (unsigned char *)buf,
                                       &sz );
                ep = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD );
                ep->SetWindowText( m_password );
                continue;
            }
            if ( !strncmp( pp, "blogID:   ", 10 ) ) {
                m_blogID = pp + 10;
                ep = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
                ep->SetWindowText( m_blogID );
                continue;
            }
            if ( !strncmp( pp, "blogName: ", 10 ) ) {
                m_blogName = pp + 10;
                ep = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
                ep->SetWindowText( m_blogName );
                continue;
            }
            if ( !strncmp( pp, "useProxy: ", 10 ) ) {
                if ( !strcmp( pp + 10, "true" ) )
                    m_useProxy = TRUE;
                else
                    m_useProxy = FALSE;
                continue;
            }
            if ( !strncmp( pp, "cocologFree: ", 13 ) ) {
                if ( !strcmp( pp + 13, "true" ) )
                    m_cocologFree = true;
                else
                    m_cocologFree = false;
                continue;
            }
        }
        fclose( fp );
    }
    else
        m_useProxy = isUsedProxy() ? TRUE : FALSE;

    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_USEPROXY );
    bp->SetCheck( m_useProxy );

    updateSelectBlogButton();
    updateUploadButton();
    updateDeleteButton();
    updateRadioButtons();
    m_needToSave = false;
}

void
CCocoUppleDlg::saveSetting()
{
    FILE    *fp;

    if ( ( fp = fopen( m_settingFilename, "w" ) ) != NULL ) {
        fprintf( fp, "userName: %s\n", (const char *)m_userName );
        if ( m_password.GetLength() > 0 )
            fprintf( fp, "password: %s\n",
                     base64( (unsigned char *)((const char *)m_password),
                             m_password.GetLength() ) );
        fprintf( fp, "blogID:   %s\n", (const char *)m_blogID );
        fprintf( fp, "blogName: %s\n", (const char *)m_blogName );
        fprintf( fp, "useProxy: %s\n", m_useProxy == TRUE ? "true" : "false");
        fprintf( fp, "cocologFree: %s\n",
                 m_cocologFree == true ? "true" : "false" );
        fclose( fp );

        base64( NULL, 0 );
    }

    m_needToSave = false;
}

void
CCocoUppleDlg::updateUploadButton()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_UPLOAD );

    if ( (m_userName.GetLength()   > 0) &&
         (m_password.GetLength()   > 0) &&
         (m_blogID.GetLength()     > 0) &&
         (m_targetFile.GetLength() > 0)    )
        bp->EnableWindow( TRUE );
    else
        bp->EnableWindow( FALSE );
}

void
CCocoUppleDlg::updateSelectBlogButton()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_SELECTBLOG );

    if ( (m_userName.GetLength() > 0) &&
         (m_password.GetLength() > 0)    )
        bp->EnableWindow( TRUE );
    else
        bp->EnableWindow( FALSE );
}

void
CCocoUppleDlg::updateDeleteButton()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_DELETE );

    if ( (m_userName.GetLength()  > 0) &&
         (m_password.GetLength()  > 0) &&
         (m_targetURL.GetLength() > 0)    )
        bp->EnableWindow( TRUE );
    else
        bp->EnableWindow( FALSE );
}

void CCocoUppleDlg::updateRadioButtons()
{
    CButton *p;

    if ( m_cocologFree ) {
        p = (CButton *)GetDlgItem( IDC_RADIO_COCOLOG );
        p->SetCheck( 0 );
    
        p = (CButton *)GetDlgItem( IDC_RADIO_COCOLOGFREE );
        p->SetCheck( 1 );
    }
    else {
        p = (CButton *)GetDlgItem( IDC_RADIO_COCOLOG );
        p->SetCheck( 1 );
    
        p = (CButton *)GetDlgItem( IDC_RADIO_COCOLOGFREE );
        p->SetCheck( 0 );
    }
}

void
CCocoUppleDlg::getImageSize( const char *filename, int& height, int& width )
{
    FILE            *fp;
    const char      *p = strrchr( filename, '.' );
    unsigned char   buf[BUFSIZ];
    enum { FTYPE_JPG = 1,
           FTYPE_GIF,
           FTYPE_PNG }  ftype;

    height = width = 0;
    if ( !p )
        return;

    if ( !strcmpi( p + 1, "jpg"  ) ||
         !strcmpi( p + 1, "jpeg" )    )
        ftype = FTYPE_JPG;
    else if ( !strcmpi( p + 1, "gif" ) )
        ftype = FTYPE_GIF;
    else if ( !strcmpi( p + 1, "png" ) )
        ftype = FTYPE_PNG;
    else
        return;

    if ( ( fp = fopen( filename, "rb" ) ) == NULL )
        return;

    switch ( ftype ) {
    case FTYPE_JPG: {
        /* FF C0, FF C1, FF C2, FF C3 のいずれかの連続する2バイトの後 *
         * 3バイト読み飛ばした直後の                                  *
         *    2バイト               → height                         *
         *    さらにその次の2バイト → width                          */
        int ret, done = FALSE;

        do {
            unsigned char   *p;

            ret = fread( buf, sizeof ( char ), BUFSIZ, fp );
            p = buf;
            for ( int i = 0; i < BUFSIZ - 9; i++, p++ ) {
                if ( (*p == 0xFF) &&
                     (*(p + 1) >= 0xC0) && (*(p + 1) <= 0xC3) ) {
                    p += 5;
                    height = *p * 256 + *(p + 1);
                    width  = *(p + 2) * 256 + *(p + 3);
                    done = TRUE;
                    break;
                }
            }
        } while ( (ret > 0) && (done == FALSE) );
        }
        break;

    case FTYPE_GIF:
        /* width:  7バイト目からの2バイト (7バイト目:下位、 8バイト目:上位) *
         * height: 9バイト目からの2バイト (9バイト目:下位、10バイト目:上位) */
        fread( buf, sizeof ( char ), 16, fp );
        width  = buf[7] * 256 + buf[6];
        height = buf[9] * 256 + buf[8];
        break;

    case FTYPE_PNG:
        /*  width:  17バイト目からの4バイト                   *
         *         (17バイト目: 最上位 ～ 20バイト目: 最下位) *
         *  height: 21バイト目からの4バイト                   *
         *         (21バイト目: 最上位 ～ 24バイト目: 最下位) */
        fread( buf, sizeof ( char ), 32, fp );
        width  = ((((buf[16] * 256) + buf[17]) * 256) + buf[18]) * 256 + buf[19];
        height = ((((buf[20] * 256) + buf[21]) * 256) + buf[22]) * 256 + buf[23];
        break;
    }

    fclose( fp );
}

CCocoUppleDlg::uploadResult CCocoUppleDlg::uploadFileToBlog()
{
    uploadResult    ret = upload_success;

    struct stat s;

    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_UPLOAD );
    bp->EnableWindow( FALSE );

    if ( stat( m_targetFile, &s ) == 0 ) {
        char        url[MAX_URLLENGTH];
        char        targetDir[MAX_PATH];
        bool        isImageFile = false;
        int         size;
        CWaitCursor cur;    // マウスカーソルを砂時計表示

        const char  *p = strrchr( m_targetFile, '.' );
        if ( p &&
             (!strcmpi( p + 1, "jpg"  ) ||
              !strcmpi( p + 1, "jpeg" ) ||
              !strcmpi( p + 1, "gif"  ) ||
              !strcmpi( p + 1, "png"  )    ) )
            isImageFile = true;

        if ( m_targetDirectory.GetLength() > 0 ) {
            if ( m_targetDirectory.Compare( "../" ) == 0 )
                strcpy( targetDir, ".." );
            else
                strcpy( targetDir, m_targetDirectory );
        }
        else
            targetDir[0] = '\0';

        size = s.st_size;
#define MAX_UPLOAD_SIZE (40 * 1024 * 1024)  // ココログの上限は 40MB
        if ( (size * 3 / 2) >= MAX_UPLOAD_SIZE - MAX_CONTENT_SIZE ) {
            // 上記の計算式の根拠
            //   実際に送信するのは base64 エンコードしたもの。実際に送信する
            //   電文のサイズはファイルサイズの 3/2 倍程度の大きさになる
            //   また、電文のヘッダ部分など、余裕を考えて MAX_CONTENT_SIZE 分
            //   見込んでいる
            MessageBox( "アップロードしようとしているファイルのサイズが"
                        "大き過ぎます。    ",
                        "ファイルサイズ過大", MB_ICONEXCLAMATION | MB_OK );

            bp->EnableWindow( TRUE );
            ret = upload_failure;

            return ( ret );
        }
        url[0] = NULL;

        setUserInfo( m_userName, m_password );
        setUseProxy( m_useProxy );
        if ( m_cocologFree ) {
            setTargetURL( APIURL_COCOLOGFREE );
            setBlogKind( BLOGKIND_COCOLOGFREE );
        }
        else {
            setTargetURL( APIURL_COCOLOG );
            setBlogKind( BLOGKIND_COCOLOG );
        }

        bool    done = false;
        do {
            done = true;
            SetLastError( ERROR_SUCCESS );
            uploadFile( m_blogID,
                        m_userName,
                        m_password,
                        targetDir, /* NULL もしくは 空文字のときは、トップ */
                                   /* ディレクトリ直下にアップロードされる */
                        m_targetFile,
                        size,
                        "application/unknown",  /* dummy */
                        url );

            if ( !(url[0]) && m_useProxy ) {
                DWORD   err = GetLastError();
                if ( err == XMLRPC_ERROR_CHANGED_PROXYINFO )
                    done = false;
            }
        } while ( !done );

        if ( url[0] ) {
            char        filename[MAX_PATH];
            const char  *p;

            p = strrchr( url, '/' );
            if ( p ) {
                strcpy( filename, p + 1 );
            }
            else {
                p = strrchr( m_targetFile, '\\' );
                if ( !p )
                    p = strrchr( m_targetFile, '/' );
                if ( p )
                    strcpy( filename, p + 1 );
                else
                    strcpy( filename, m_targetFile );
            }

            if ( isImageFile ) {
                int     height, width;
                char    tmp[36];

                getImageSize( m_targetFile, height, width );

                m_htmlSrc += _T("<a href=\"");
                m_htmlSrc += url;
                m_htmlSrc += _T("\"><img src=\"");
                m_htmlSrc += url;
                m_htmlSrc += _T("\" width=\"");
                m_htmlSrc += itoa( width, tmp, 10 );
                m_htmlSrc += _T("\" height=\"");
                m_htmlSrc += itoa( height, tmp, 10 );
                m_htmlSrc += _T("\" border=\"0\" alt=\"");
                m_htmlSrc += filename;
                m_htmlSrc += _T("\" /></a>\r\n");
            }
            else {
                m_htmlSrc += _T("<a href=\"");
                m_htmlSrc += url;
                m_htmlSrc += _T("\">");
                m_htmlSrc += filename;
                m_htmlSrc += _T("</a>\r\n");
           }

            CEdit   *ep = (CEdit *)GetDlgItem( IDC_EDIT_HTML );
            ep->SetWindowText( m_htmlSrc );
        }
        else
            ret = upload_failure;
    }
    else
        ret = upload_fileNotFound;

    bp->EnableWindow( TRUE );

    return ( ret );
}

/////////////////////////////////////////////////////////////////////////////
// CCocoUppleDlg メッセージ ハンドラ

BOOL CCocoUppleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

    CCocoUppleApp   *bp = (CCocoUppleApp *)AfxGetApp();
#ifdef  _DEBUG
    bp->m_verbose = true;
#endif
    if ( bp->m_verbose ) {
        char            filename[MAX_PATH];
#ifdef  USE_STAT_64
        struct _stati64 s;
#else
        struct stat     s;
#endif  /* USE_STAT_64 */

        sprintf( filename, "%s/" COCOUPPLE_LOG_FILE, m_path );
#ifdef  USE_STAT_64
        if ( !_stati64( filename, &s ) ) {
            if ( s.st_size > (__int64)(1024 * 1024 * 64) ) {
#else   /* !USE_STAT_64 */
        if ( !stat( filename, &s ) ) {
            if ( (unsigned long)s.st_size > 1024 * 1024 * 64 ) {
#endif  /* !USE_STAT_64 */
                char        backup[MAX_PATH];
                time_t      t = time( NULL );
                struct tm   *tm = localtime( &t );

                sprintf( backup,
                         "%s/" COCOUPPLE_LOG_FILE ".%04d%02d%02d%02d%02d%02d",
                         m_path,
                         tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                         tm->tm_hour, tm->tm_min, tm->tm_sec );
                rename( filename, backup );
            }
        }

        bp->m_verboseFp = fopen( filename, "a" );
        if ( bp->m_verboseFp ) {
            time_t      t   = time( NULL );
            struct tm   *tm = localtime( &t );
            fprintf( bp->m_verboseFp,
                   "\n\n*** logging start: %d/%02d/%02d %02d:%02d:%02d ***\n",
                     tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                     tm->tm_hour, tm->tm_min, tm->tm_sec );
#ifdef  _DEBUG
            setDump( TRUE, bp->m_verboseFp );
#endif
        }
        setVerbose( bp->m_verbose, bp->m_verboseFp );
    }
		
	return TRUE;
}

void CCocoUppleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CCocoUppleDlg::OnPaint() 
{
	if (IsIconic()) {
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialog::OnPaint();
	}
}

HCURSOR CCocoUppleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCocoUppleDlg::OnCheckUseproxy() 
{
    switch ( m_useProxy ) {
    case TRUE:
        m_useProxy = FALSE;
        break;
    case FALSE:
    default:
        m_useProxy = TRUE;
        break;
    }

    m_needToSave = true;
}

void CCocoUppleDlg::OnKillfocusEditUsername() 
{
    CString save = m_userName;
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME );
    p->GetWindowText( m_userName );

    if ( save != m_userName ) {
        m_needToSave = true;
        m_numOfBlogs = 0;
        m_blogID     = _T( "" );
        m_blogName   =  _T( "" );

        CEdit   *ep = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
        ep->SetWindowText( m_blogID );

        ep = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
        ep->SetWindowText( m_blogName );
        updateUploadButton();
    }
}

void CCocoUppleDlg::OnKillfocusEditPassword() 
{
    CString save = m_password;
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD );
    p->GetWindowText( m_password );

    if ( save != m_password ) {
        m_needToSave = true;
        updateUploadButton();
    }
}

void CCocoUppleDlg::OnKillfocusEditTargetDirectory() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_TARGETDIRECTORY );
    p->GetWindowText( m_targetDirectory );
}

void CCocoUppleDlg::OnKillfocusEditTargetFile() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_TARGETFILENAME );
    p->GetWindowText( m_targetFile );
    updateUploadButton();
}

void CCocoUppleDlg::OnUpdateEditTargetFile() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_TARGETFILENAME );
    p->GetWindowText( m_targetFile );
	updateUploadButton();
}

void CCocoUppleDlg::OnButtonSelectBlog() 
{
	if ( (m_userName.GetLength() == 0) || (m_password.GetLength() == 0) )
        return;

    setUserInfo( m_userName, m_password );
    setUseProxy( m_useProxy );
    if ( m_cocologFree ) {
        setTargetURL( APIURL_COCOLOGFREE );
        setBlogKind( BLOGKIND_COCOLOGFREE );
    }
    else {
        setTargetURL( APIURL_COCOLOG );
        setBlogKind( BLOGKIND_COCOLOG );
    }
    setBlogID();

    CEdit   *ep = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
    ep->SetWindowText( m_blogID );

    ep = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
    ep->SetWindowText( m_blogName );
    updateUploadButton();
}

void CCocoUppleDlg::OnButtonSelectFile() 
{
    /* ファイル選択ダイアログを表示 */
    CFileDialog *fp;

    fp = new CFileDialog( TRUE, NULL, NULL,
                          OFN_FILEMUSTEXIST | OFN_READONLY,
                          _T("すべてのファイル (*.*)|*.*||") );
    if ( fp->DoModal() == IDOK )
        m_targetFile = fp->GetPathName();
    else
        m_targetFile = _T("");
    delete fp;

    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_TARGETFILENAME );
    p->SetWindowText( m_targetFile );
    updateUploadButton();
}

void CCocoUppleDlg::OnButtonUpload() 
{
	if ( (m_userName.GetLength()   == 0) ||
         (m_password.GetLength()   == 0) ||
         (m_blogID.GetLength()     == 0) ||
         (m_targetFile.GetLength() == 0)    )
        return;

    uploadResult    ret = uploadFileToBlog();
    if ( ret == upload_failure ) {
        MessageBox( "アップロードに失敗しました。    ",
                    "アップロード失敗", MB_ICONEXCLAMATION | MB_OK );
    }
    else if ( ret == upload_fileNotFound ) {
        MessageBox( "ファイルが見つかりません。    ",
                    "アップロード中止", MB_ICONEXCLAMATION | MB_OK );
    }
}

void CCocoUppleDlg::OnOK() 
{
    if ( m_needToSave )
        saveSetting();
	
	CDialog::OnOK();
}

void CCocoUppleDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CString str;
        CString version;
        CString releaseDate;

        version.LoadString( IDS_VERSION );
        releaseDate.LoadString( IDS_RELEASE_DATE );
        str = "by H.Tsujimura (tsupo)           Ver " + version +
                                        "                 " + releaseDate;

        CStatic *s = (CStatic *)GetDlgItem( IDC_VERSION_INFO );
        s->SetWindowText( str );

        loadSetting();
    }
}

void CCocoUppleDlg::OnChangeEditUsername() 
{
    CString save = m_userName;
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME );
    p->GetWindowText( m_userName );

    updateSelectBlogButton();

    p->GetWindowText( save );
    m_needToSave = true;
}

void CCocoUppleDlg::OnChangeEditPassword() 
{
    CString save = m_password;
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD );
    p->GetWindowText( m_password );

    updateSelectBlogButton();

    p->GetWindowText( save );
    m_needToSave = true;
}

void CCocoUppleDlg::OnKillfocusEditUrlDelete() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_URL_DELETE );
    p->GetWindowText( m_targetURL );
    updateDeleteButton();
}

void CCocoUppleDlg::OnUpdateEditUrlDelete() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_URL_DELETE );
    p->GetWindowText( m_targetURL );
    updateDeleteButton();
}

void CCocoUppleDlg::OnButtonDelete() 
{
	if ( (m_userName.GetLength()  == 0) ||
         (m_password.GetLength()  == 0) ||
         (m_targetURL.GetLength() == 0)    )
        return;

    CString messageText;
    messageText = m_targetURL + " を削除してもよろしいですか?    ";
    int res = MessageBox( messageText,
                          "削除確認", MB_YESNO|MB_ICONWARNING );
    if ( res == IDYES ) {
        CWaitCursor cur;    // マウスカーソルを砂時計表示

        if ( m_cocologFree ) {
            setTargetURL( APIURL_COCOLOGFREE );
            setBlogKind( BLOGKIND_COCOLOGFREE );
        }
        else {
            setTargetURL( APIURL_COCOLOG );
            setBlogKind( BLOGKIND_COCOLOG );
        }
        setUseProxy( m_useProxy );

        bool    done = false;
        do {
            done = true;
            SetLastError( ERROR_SUCCESS );
	        deleteFile( m_userName, m_password, m_targetURL );
            if ( m_useProxy ) {
                DWORD   err = GetLastError();
                if ( err == XMLRPC_ERROR_CHANGED_PROXYINFO )
                    done = false;
            }
        } while ( !done );
    }
}

void CCocoUppleDlg::OnRadioCocolog() 
{
	m_cocologFree = false;
    m_numOfBlogs  = 0;
    updateRadioButtons();
}

void CCocoUppleDlg::OnRadioCocologfree() 
{
	m_cocologFree = true;
    m_numOfBlogs  = 0;
    updateRadioButtons();
}

void CCocoUppleDlg::OnDropFiles(HDROP hDropInfo) 
{
    char        filename[MAX_PATH];
    int         num;
    size_t      sz = MAX_PATH;
    struct stat s;

    /* ドロップされたファイルの個数を得る */
    num = DragQueryFile( hDropInfo, (UINT)0xFFFFFFFF, NULL, 0 );
    /* ファイルを処理 */
    for ( int i = 0; i < num; i++ ) {
        filename[0] = NUL;
        DragQueryFile( hDropInfo, i, filename, sz );
        if ( filename[0] ) {
            if ( !stat( filename, &s ) ) {
                // ディレクトリは読み飛ばす
                if ( (s.st_mode & _S_IFDIR ) == _S_IFDIR )
                    continue;

                // ファイル名を設定、表示
                m_targetFile = filename;
                CEdit   *ep  = (CEdit *)GetDlgItem( IDC_EDIT_TARGETFILENAME );
                ep->SetWindowText( m_targetFile );
                updateUploadButton();
                break;
            }
        }
    }

	CDialog::OnDropFiles(hDropInfo);
}

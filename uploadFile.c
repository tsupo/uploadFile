/*
 * XML-RPC API 経由でファイルをアップロードする
 *   (ココログ専用版)
 *
 *    written by H.Tsujimura    2004.12.14
 *
 *    Usage:
 *      uploadFile [-p] -uユーザ名 -Pパスワード
 *                 [-dアップロード先ディレクトリ名]
 *                 -fアップロードしたいファイル [-bブログID]
 *                 -t[F]
 *
 *         -p:  proxy を使う
 *         -tF: 対象の blog はココログフリー
 *         -t:  対象の blog はココログベーシック、ココログプラス、ココログプロ
 *
 * History:
 * $Log: /comm/uploadFile/uploadFile.c $
 * 
 * 1     09/05/14 3:53 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/09/04 22:06 Tsujimura543
 * setVerbose() の第2引数追加に伴う変更
 * 
 * 3     06/03/14 23:55 Tsujimura543
 * ココログフリーにファイルをアップロードできることを確認
 * 
 * 2     06/03/14 23:40 Tsujimura543
 * ココログフリーにも対応した
 * 
 * 1     04/12/16 19:17 Tsujimura543
 */

#include "xmlRPC.h"
#include <sys/stat.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/uploadFile/uploadFile.c 1     09/05/14 3:53 tsupo $";
#endif

#define MAX_PROMPT_LEN  80
#define MAX_BLOGS       10  /* 同一システム内最大設置可能blog数 (ココログ) */


void
setBlogID( char *blogID )
{
    if ( !(blogID[0]) ) {
        BLOGINF blogInfo[MAX_BLOGS];
        char    prompt[MAX_PROMPT_LEN];
        char    buf[BUFSIZ];
        int     numOfBlogs = MAX_BLOGS;
        int     r, i;

        r = getBlogIDs( NULL, NULL, &numOfBlogs, blogInfo ); /* blogger API */
        if ( r == 1 )
            strcpy( (char *)blogID, blogInfo[0].blogID );/* 確定 */
        else if ( r > 1 ) {
            /* ---- 投稿先 blog の選択 */
            do {
                for ( i = 0; i < r; i++ ) {
                    printf( "(%d)\t%s (blogID: %s)\n",
                            i + 1,
                            utf2sjis( blogInfo[i].blogName ),
                            blogInfo[i].blogID );
                }
                sprintf( prompt,
                         "どの blog にアップロードしますか? (1 - %d): ", r );
                inputString( (char *)buf, prompt, FALSE );
                i = atoi( buf );
                if ( (i >= 1) && (i <= r) ) {
                    strcpy( blogID, blogInfo[i - 1].blogID );
                    break;
                }
            } while ( (i < 1) || (i > r) );
        }
    }
}


#define setValueFromArgv( str ) \
    if ( argv[i][j + 1] ) { \
        strcpy( (str), &argv[i][j + 1] ); \
        j = strlen( argv[i] ) - 1; \
    } \
    else if ( i + 1 < argc ) { \
        i++; \
        strcpy( (str), argv[i] ); \
        j = strlen( argv[i] ) - 1; \
    }

int
main( int argc, char *argv[] )
{
    char        targetURL[MAX_PATH];
    char        userName[MAX_USERIDLEN];
    char        password[MAX_PASSWDLEN];
    char        blogID[MAX_BLOGIDLENGTH];
    char        url[MAX_URLLENGTH];
    char        targetFile[MAX_PATH];
    char        targetDir[MAX_PATH];
    int         size        = 0;
    int         useProxy    = FALSE;
    int         cocologFree = FALSE;
    int         selected    = FALSE;
    struct stat s;

    memset( targetFile, 0x00, MAX_PATH );
    memset( targetDir,  0x00, MAX_PATH );
    memset( userName,   0x00, MAX_USERIDLEN );
    memset( password,   0x00, MAX_PASSWDLEN );
    memset( blogID,     0x00, MAX_BLOGIDLENGTH );
    memset( url,        0x00, MAX_URLLENGTH );

    if ( argc > 1 ) {
        int i, j;
        for ( i = 0; i < argc; i++ ) {
            if ( argv[i][0] == '-' ) {
                for ( j = 1; argv[i][j]; j++ ) {
                    switch ( argv[i][j] ) {
                    case 'p':
                        useProxy = !useProxy;
                        break;

                    case 'u':
                        setValueFromArgv( userName );
                        break;

                    case 'P':
                        setValueFromArgv( password );
                        break;

                    case 'f':
                        setValueFromArgv( targetFile );
                        break;

                    case 'd':
                        setValueFromArgv( targetDir );
                        break;

                    case 'b':
                        setValueFromArgv( blogID );
                        break;

                    case 't':
                        if ( argv[i][j + 1] == 'F' ) {
                            cocologFree = TRUE;
                            j++;
                        }
                        selected = TRUE;
                        break;
                    }
                }
            }
        }
    }

    if ( !userName[0] ) {
        fputs( "「login名」を指定してください!!\n", stderr );
        exit( 255 );
    }

    if ( !password[0] ) {
        fputs( "「パスワード」を指定してください!!\n", stderr );
        exit( 255 );
    }

    if ( !targetFile[0] ) {
        fputs( "「アップロードするファイルの名前」を指定してください!!\n",
               stderr );
        exit( 255 );
    }

    if ( !selected ) {
        fputs( "「従来のココログ/ココログフリー」のどちらなのか、"
               "指定してください!!\n",
               stderr );
        exit( 255 );
    }

    strcpy( targetURL, cocologFree ? APIURL_COCOLOGFREE : APIURL_COCOLOG );

    setUserInfo( userName, password );
    setUseProxy( useProxy );
    setTargetURL( targetURL );
    setBlogKind( cocologFree ? BLOGKIND_COCOLOGFREE : BLOGKIND_COCOLOG );
#ifdef  _DEBUG
    setVerbose( TRUE, stderr );
#endif

    setBlogID( blogID );

    if ( stat( targetFile, &s ) == 0 ) {
        size = s.st_size;

        uploadFile( blogID,
                    userName,
                    password,
                    targetDir, /* NULL もしくは 空文字のときは、トップディ */
                               /* レクトリ直下にアップロードされる         */
                    targetFile,
                    size,
                    "application/unknown",  /* dummy */
                    url );

        if ( url[0] )
            fprintf( stderr, "アップロードしたファイルの url = %s\n", url );
    }

    return ( 1 );
}

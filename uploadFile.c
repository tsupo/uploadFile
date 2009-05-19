/*
 * XML-RPC API �o�R�Ńt�@�C�����A�b�v���[�h����
 *   (�R�R���O��p��)
 *
 *    written by H.Tsujimura    2004.12.14
 *
 *    Usage:
 *      uploadFile [-p] -u���[�U�� -P�p�X���[�h
 *                 [-d�A�b�v���[�h��f�B���N�g����]
 *                 -f�A�b�v���[�h�������t�@�C�� [-b�u���OID]
 *                 -t[F]
 *
 *         -p:  proxy ���g��
 *         -tF: �Ώۂ� blog �̓R�R���O�t���[
 *         -t:  �Ώۂ� blog �̓R�R���O�x�[�V�b�N�A�R�R���O�v���X�A�R�R���O�v��
 *
 * History:
 * $Log: /comm/uploadFile/uploadFile.c $
 * 
 * 1     09/05/14 3:53 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/09/04 22:06 Tsujimura543
 * setVerbose() �̑�2�����ǉ��ɔ����ύX
 * 
 * 3     06/03/14 23:55 Tsujimura543
 * �R�R���O�t���[�Ƀt�@�C�����A�b�v���[�h�ł��邱�Ƃ��m�F
 * 
 * 2     06/03/14 23:40 Tsujimura543
 * �R�R���O�t���[�ɂ��Ή�����
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
#define MAX_BLOGS       10  /* ����V�X�e�����ő�ݒu�\blog�� (�R�R���O) */


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
            strcpy( (char *)blogID, blogInfo[0].blogID );/* �m�� */
        else if ( r > 1 ) {
            /* ---- ���e�� blog �̑I�� */
            do {
                for ( i = 0; i < r; i++ ) {
                    printf( "(%d)\t%s (blogID: %s)\n",
                            i + 1,
                            utf2sjis( blogInfo[i].blogName ),
                            blogInfo[i].blogID );
                }
                sprintf( prompt,
                         "�ǂ� blog �ɃA�b�v���[�h���܂���? (1 - %d): ", r );
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
        fputs( "�ulogin���v���w�肵�Ă�������!!\n", stderr );
        exit( 255 );
    }

    if ( !password[0] ) {
        fputs( "�u�p�X���[�h�v���w�肵�Ă�������!!\n", stderr );
        exit( 255 );
    }

    if ( !targetFile[0] ) {
        fputs( "�u�A�b�v���[�h����t�@�C���̖��O�v���w�肵�Ă�������!!\n",
               stderr );
        exit( 255 );
    }

    if ( !selected ) {
        fputs( "�u�]���̃R�R���O/�R�R���O�t���[�v�̂ǂ���Ȃ̂��A"
               "�w�肵�Ă�������!!\n",
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
                    targetDir, /* NULL �������� �󕶎��̂Ƃ��́A�g�b�v�f�B */
                               /* ���N�g�������ɃA�b�v���[�h�����         */
                    targetFile,
                    size,
                    "application/unknown",  /* dummy */
                    url );

        if ( url[0] )
            fprintf( stderr, "�A�b�v���[�h�����t�@�C���� url = %s\n", url );
    }

    return ( 1 );
}

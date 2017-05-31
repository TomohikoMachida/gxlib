// --------------------------------------------------------------------
//
// つじつまあわせ用共通ヘッダ
//
// --------------------------------------------------------------------
#ifndef _MACHINE_H_
#define _MACHINE_H_


#ifdef PLATFORM_WIN32_CONSOLE
	#include "win32console/machine.h"

#elif defined PLATFORM_WIN32_APP
	#include "win32app/machine.h"

#elif defined PLATFORM_WIN32_DIRECTX9
	#include "win32DirectX9/machine.h"

#elif defined PLATFORM_WIN32_OPENGL
	#include "win32OpenGL/machine.h"

#elif defined PLATFORM_WIN64_DIRECTX11

#elif defined PLATFORM_ANDROID

#elif defined PLATFORM_IOS

#elif defined PLATFORM_COCOS2DX
	#include "cocos2dx/machine.h"

#endif


//各プラットフォーム共通

gxBool GameMain();
gxBool GameSleep();
gxBool GameResume();
gxBool GameEnd();
gxBool GameReset();

//毎フレームの初期化処理
void   InitAction();

//毎フレームの描画処理
void   Render();

//毎フレームのディスプレイ同期待ち
gxBool vSync( gxBool bNoWait = gxFalse );

//毎フレームのディスプレイへの描画更新
void   Flip();

//毎フレームの動画更新処理
void   Movie();

//スリープからの復帰処理
void   Resume();

//テクスチャのVRAMへの転送
void   Upload(Sint32 sBank);

//毎フレームの音楽再生処理
void   Play();

//ネットワークにまつわる処理色々
gxBool NetWork();

// 通常のファイル入出力
// rootフォルダはexeファイル直下となります
Uint8* LoadFile( const gxChar* pFileName , Uint32* pLength );
gxBool SaveFile( const gxChar* pFileName , Uint8* pReadBuf , Uint32 uSize );

//ストレージへのファイルアクセス
//WindowsならStorageフォルダへ記録します
gxBool SaveStorageFile( const gxChar* pFileName , Uint8* pReadBuf , Uint32 uSize );
Uint8* LoadStorageFile( const gxChar* pFileName , Uint32* pLength );

//時計関連の処理
void   Clock();

//スレッドを作成する
void   MakeThread( void (*pFunc)(void*) , void * pArg );

//簡易コントローラー設定
gxBool PadConfig( Sint32 padNo , Uint32 button );

//ログ表示
void   LogDisp(char* pString);

#endif

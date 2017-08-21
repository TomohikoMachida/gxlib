//--------------------------------------------------
//
// gxUtil.h
// ライブラリでサポートされている関数、定義一覧
//
//--------------------------------------------------

#ifndef _GX_LIB_H_
#define _GX_LIB_H_

#define VERION_MAJOR   (2)
#define VERION_MINOR   (3)
#define VERION_RELEASE (1)

//---------------------------------------------------------------------------
//ユーザー定義
//---------------------------------------------------------------------------

#if \
	!defined(PLATFORM_WIN32_CONSOLE) && \
	!defined(PLATFORM_WIN32_APP) && \
	!defined(PLATFORM_WIN32_WINDOW) && \
	!defined(PLATFORM_WIN32_DIRECTX9) && \
	!defined(PLATFORM_WIN32_OPENGL) && \
	!defined(PLATFORM_WIN64_DIRECTX11) && \
	!defined(PLATFORM_ANDROID) && \
	!defined(PLATFORM_IOS) && \
	!defined(PLATFORM_COCOS2DX)

//#define PLATFORM_WIN32_CONSOLE
//#define PLATFORM_WIN32_APP
//#define PLATFORM_WIN32_WINDOW
#define PLATFORM_WIN32_DIRECTX9
//#define PLATFORM_WIN32_OPENGL
//#define PLATFORM_WIN64_DIRECTX11
//#define PLATFORM_ANDROID
//#define PLATFORM_IOS
//#define PLATFORM_COCOS2DX

#endif

//#define WINDOW_W (640)
//#define WINDOW_H (480)
#define WINDOW_W (480)
#define WINDOW_H (272)

#define MAX_ORDER_NUM (40000*2)		//グラフィックのオーダー（同時）限界数
#define MAX_TEXT_NUM  (256*2)			//gxLib::Printfでリクエスト可能な限界数
#define MAX_MASTERTEX_NUM (32)		//マスターテクスチャの最大枚数
#define MAX_SOUND_NUM (256)			//サウンドのバンク数（同時発音数はマシンのｃｈ数）
#define PRIORITY_MAX  (255)			//優先順位
#define FRAME_PER_SECOND  (60)		//FPS(vSync同期した場合はリフレッシュレートに依る)

#define APPLICATION_NAME "garurururu"
#define FILENAME_CONFIG  "config.dat"

//---------------------------------------------------------------------------
//型宣言
//---------------------------------------------------------------------------
typedef signed char 		Sint8;
typedef short				Sint16;
typedef int 				Sint32;
typedef unsigned			Uint;
typedef unsigned char		Uint8;
typedef unsigned short		Uint16;
typedef unsigned			Uint32;
typedef long long int		Sint64;
typedef unsigned long long 	Uint64;
typedef float				Float;
typedef float				Float32;
typedef double				Float64;
typedef long double			Float80;
typedef char				gxBool;
typedef char				gxChar;

#define gxTrue  (1)
#define gxFalse (0)

#define NULL_POINTER (0)

//---------------------------------------
//特殊な設定
//---------------------------------------

typedef struct gxPoint
{
	//よく使う座標管理用構造体
	Float32 x;
	Float32 y;

	void Set( Float px, Float py )
	{
		x = px;
		y = py;
	}

} gxPoint;

typedef struct gxPos
{
	void Set( Sint32 _x , Sint32 _y , Sint32 _z = 0)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	//よく使う座標管理用構造体
	Sint32 x,y,z;//,r;	//(x,y,z)＋回転

} gxPos;


typedef struct gxVec
{
	//よく使う座標管理用構造体（Float版）
	Float32 fx,fy,fz;

	void Set( Float32 x , Float32 y , Float32 z )
	{
		fx = x;
		fy = y;
		fz = z;
	}

} gxVec;


typedef struct gxVector2D
{
	Float32 x,y;
} gxVector2D;

typedef struct gxRect
{
	//簡単な当たり判定付き矩形

	Sint32 x1;
	Sint32 y1;
	Sint32 x2;
	Sint32 y2;

	gxRect()
	{
		x1 = y1 = x2 = y2 = 0;
	}

	void Set( Sint32 px, Sint32 py, Sint32 w, Sint32 h )
	{
		x1 = px;
		y1 = py;
		x2 = x1+w;
		y2 = y1+h;
	}

	gxBool IsHit( Sint32 const x , Sint32 const y ) const
	{
		if( x >= x1 && x < x2 && y >= y1 && y < y2 ) return gxTrue;

		return gxFalse;
	}

} gxRect;


typedef struct gxSprite
{
	//スプライト定義用構造体
	Sint32 page,u,v,w,h,cx,cy;

} gxSprite;

//============================================================================
//描画関連
//============================================================================
#define ARGB_DFLT (0xffffffff)
#define ARGB(a,r,g,b)	(((a)<<24)|((r)<<16)|((g)<<8)|(b))
#define SET_ALPHA( alp , rgb ) ( ( (rgb)&0x00ffffff) | (alp<<24) )

#define ATR_DFLT		(0x00000000)
#define ATR_ALPHA_NML	(0x00000000)
#define ATR_ALPHA_ADD	(0x00000001)		//加算
#define ATR_ALPHA_SUB	(0x00000002)		//減算
#define ATR_ALPHA_CRS   (0x00000003)		//乗算
#define ATR_ALPHA_RVS 	(0x00000004)		//反転
#define ATR_ALPHA_XOR 	(0x00000005)		//XOR
#define ATR_ALPHA_SCR 	(0x00000006)		//スクリーン乗算
//#define ATR_ALPHA_SCR 	(0x00000040)		//予約
//#define ATR_ALPHA_SCR 	(0x00000080)		//予約

#define ATR_FLIP_X 		(0x00000010)
#define ATR_FLIP_Y 		(0x00000020)

#define ATR_STR_LEFT	(0x00000000)
#define ATR_STR_CENTER	(0x00000100)
#define ATR_STR_RIGHT	(0x00000200)

#define ATR_DEFAULT  ATR_DFLT
#define ARGB_DEFAULT ARGB_DFLT
#define ATR_ALPHA_PLUS	  (0x01)		//加算半透明処理指定
#define ATR_ALPHA_MINUS	  (0x02)		//減算半透明処理指定
#define ATR_FLIP_XY 	(ATR_FLIP_X|ATR_FLIP_Y)



#define PLAYER_MAX (5)	//ユーザー定義できなくしてユーザーは１～５固定です

enum {
	//キーボードの状態
	enStatPush    = 0x01,
	enStatTrig    = 0x02,
	enStatRepeat  = 0x04,
	enStatRelease = 0x08,
	enStatDouble  = 0x10,
};

enum
{
	JOY_U =(0x00000001),
	JOY_R =(0x00000002),
	JOY_D =(0x00000004),
	JOY_L =(0x00000008),

	BTN_1 =(0x00000010),
	BTN_2 =(0x00000020),
	BTN_3 =(0x00000040),
	BTN_4 =(0x00000080),

	BTN_5 =(0x00000100),
	BTN_6 =(0x00000200),
	BTN_7 =(0x00000400),
	BTN_8 =(0x00000800),

	BTN_9 =(0x00001000),
	BTN_10=(0x00002000),
	BTN_11=(0x00004000),
	BTN_12=(0x00008000),	//ＰＡＤはココまで

	BTN_13=(0x00010000),
	BTN_14=(0x00020000),
	BTN_15=(0x00040000),
	BTN_16=(0x00080000),

	BTN_17=(0x00100000),
	BTN_18=(0x00200000),
	BTN_19=(0x00400000),
	BTN_20=(0x00800000),

	BTN_21=(0x01000000),
	BTN_22=(0x02000000),
	BTN_23=(0x04000000),	//マウスL
	BTN_24=(0x08000000),	//マウスR

	BTN_25=(0x10000000),	//アナログ１
	BTN_26=(0x20000000),	//アナログ２

	BTN_27=(0x40000000),	//マウスM
	BTN_28=(0x80000000),	//以下、未使用
	BTN_29=(0x80000000),	//
	BTN_30=(0x80000000),	//
	BTN_31=(0x80000000),	//

	BTN_MAX=32,
};

enum {
	//仮想キー

	//cmn

	BTN_SELECT =(BTN_11),
	BTN_START  =(BTN_12),

	//SS

	BTN_A=(BTN_1),
	BTN_B=(BTN_2),
	BTN_C=(BTN_3),
	BTN_X=(BTN_4),
	BTN_Y=(BTN_5),
	BTN_Z=(BTN_6),
	BTN_L =(BTN_7),
	BTN_R =(BTN_8),

	// PS1

	BTN_CROSS    = BTN_A,
	BTN_CIRCLE   = BTN_B,
	BTN_SQUARE   = BTN_X,
	BTN_TRIANGLE = BTN_Y,
	BTN_L1=(BTN_7),
	BTN_R1=(BTN_8),
	BTN_L2=(BTN_9),
	BTN_R2=(BTN_10),

	//PS2

	BTN_L3=(BTN_13),
	BTN_R3=(BTN_14),

	//mouse

	MOUSE_L = BTN_23,
	MOUSE_R = BTN_24,
	MOUSE_M = BTN_27,

	//Analogスティック

	BTN_ANALOG1 =(BTN_25),
	BTN_ANALOG2 =(BTN_26),

};


typedef struct StJoyStat
{
	Uint32  psh;	// 押しっぱなし
	Uint32  trg;	// 押した瞬間
	Uint32  rep;	// リピート
	Uint32  rls;	// 離した瞬間
	Uint32  dcl;	// ダブルクリック
	Sint32  mx;		// マウス座標Ｘ
	Sint32  my;		// マウス座標Ｙ
	Float32 ax;		// アナログＸ	左スティック
	Float32 ay;		// アナログＹ
	Float32 az;		// アナログＺ
	Float32 rx;		// アナログ（回転）Ｘ	右スティック
	Float32 ry;		// アナログ（回転）Ｙ
	Float32 rz;		// アナログ（回転）Ｚ
	Sint32  whl;	// ホイール回転

} StJoyStat;

typedef struct StTouch
{
	Sint32 stat;
	Sint32 x,y;
	Sint32 sx,sy;
	Sint32 ex,ey;

} StTouch;


class gxLib {

public:

	//グラフィック関連

	//画面消去時の背景色を設定します
	static void SetBgColor( Uint32 argb );

	//点を描画します

	static Uint32 DrawPoint( Sint32 x1,	Sint32 y1, Sint32 prio, Uint32 atr, Uint32 argb );

	//線を描画します(太さはDirectXでは指定できません)

	static Uint32 DrawLine( Sint32 x1,	Sint32 y1,	Sint32 x2 , Sint32 y2 , Sint32 prio, Uint32 atr, Uint32 col , Float32 width = 1.0f );

	//三角形を描画します

	static Uint32 DrawTriangle(
			Sint32 x1 , Sint32 y1,
			Sint32 x2 , Sint32 y2 ,
			Sint32 x3 , Sint32 y3 ,
			Sint32 prio,
			gxBool bFill,
			Uint32 atr=ATR_DFLT,	Uint32 col=ARGB_DFLT );

	//グラデーションの三角を描く

	static Uint32 DrawColorTriangle(
			Sint32 x1 ,	Sint32 y1 ,Uint32 argb1,
			Sint32 x2 , Sint32 y2 ,Uint32 argb2,
			Sint32 x3 , Sint32 y3 ,Uint32 argb3,
			Sint32 prio,
			Uint32 atr );

	//グラデーションの箱を描く
	static Uint32 DrawColorBox(
			Sint32 x1 ,	Sint32 y1 ,Uint32 argb1,
			Sint32 x2 , Sint32 y2 ,Uint32 argb2,
			Sint32 x3 , Sint32 y3 ,Uint32 argb3,
			Sint32 x4 , Sint32 y4 ,Uint32 argb4,
			Sint32 prio,
			Uint32 atr );


	//四角形を描画します
	static Uint32 DrawBox(
			Sint32 x1,		Sint32 y1,	Sint32 x2 , Sint32 y2 , Sint32 prio,
			gxBool bFill,
			Uint32 atr=ATR_DFLT,	Uint32 col=ARGB_DFLT,
			Sint32 cx=0 , Sint32 cy=0,
			Float32 r=0.f,	Float32 sx=1.f,	Float32 sy=1.f );

	//テクスチャ付き三角形を（UVデータ構造体を渡して）描画します
	static Uint32 PutTriangle(
			Sint32 x1 , Sint32 y1 ,Sint32 u1,Sint32 v1,
			Sint32 x2 , Sint32 y2 ,Sint32 u2,Sint32 v2,
			Sint32 x3 , Sint32 y3 ,Sint32 u3,Sint32 v3,
			Sint32 tpg,
			Sint32 prio,
			Uint32 atr=ATR_DFLT,	Uint32 col=ARGB_DFLT );

	//テクスチャ付き四角形を描画します
	static Uint32 PutSprite(
		Sint32 x,		Sint32 y,	Sint32 prio,
		Sint32 page,	Sint32 u, 	Sint32 v,	Sint32 w,	Sint32 h,

		Sint32 cx=0,
		Sint32 cy=0,
		Uint32 atr = ATR_DFLT,
		Uint32 col = ARGB_DFLT,
		Float32 r  = 0,
		Float32 sx = 1.0f,
		Float32 sy = 1.0f	);

	//（UVデータ構造体を渡して）テクスチャ付き四角形を描画します
	static Uint32 PutSprite(
		gxSprite* pSpr, Sint32 x,		Sint32 y,	Sint32 prio,	Uint32 atr = ATR_DFLT,	Uint32 col = ARGB_DFLT,
		Float32 r  = 0,	Float32 sx = 1.0f,	Float32 sy = 1.0f	);

	//テクスチャをファイルからマスターテクスチャへ読み込みます
	static gxBool LoadTexture ( Uint32 texPage , const gxChar* fileName , Uint32 colorKey=0xff00ff00 ,Uint32 ox = 0 , Uint32 oy = 0 , Sint32 *w=NULL_POINTER , Sint32 *h=NULL_POINTER  );

	//テクスチャをメモリからマスターテクスチャへ読み込みます
	static gxBool ReadTexture ( Uint32 texPage , const Uint8* pBuffer , Uint32 pSize , Uint32 colorKey=0xff00ff00 ,Uint32 ox = 0 , Uint32 oy = 0 , Sint32 *w=NULL_POINTER , Sint32 *h=NULL_POINTER );

	//マスターテクスチャをVRAMに転送します
	//※処理が重たいので、更新時にすべてのテクスチャを読み込んでから１回だけ行います
	static gxBool UploadTexture ( gxBool bForce = gxFalse );


	//動画処理

	static gxBool LoadMovie( Sint32 uIndex , gxChar *pFileName , Sint32 texPage , Sint32 uAudioIndex = -1 , gxChar *AudioFileName = NULL_POINTER );

	static gxBool PlayMovie( Sint32 uIndex , gxBool bLoop = gxFalse );
	static gxBool StillMovie( Sint32 uIndex , Sint32 uFrame );

	static gxBool StopMovie( Sint32 uIndex );


	//サウンド関連


	//サウンドファイルをメモリから指定バンクに読み込みます
	static gxBool ReadAudio( Uint32 uIndex , const Uint8* pMemory ,Uint32 uSize );

	//サウンドファイルをファイルから指定バンクに読み込みます
	static gxBool LoadAudio( Uint32 uIndex , const gxChar* pFileName );

	//指定バンクのサウンドを再生します
	static gxBool PlayAudio( Uint32 index , gxBool bLoop = gxFalse , gxBool bOverWrap = gxFalse , Uint32 uFrm = 0 );

	//指定バンクのサウンドを停止します
	static gxBool StopAudio( Uint32 index , Uint32 uFrm=0 );

	//特定バンクのサウンドボリュームを設定します
	static gxBool SetAudioVolume ( Uint32 index ,Float32 fVolume );

	//すべてのバンクのサウンドのボリュームを一括して調整します
	static gxBool SetAudioMasterVolume( Float32 fVolume );

	//特定バンクのサウンドの再生状況を返します
	static gxBool IsAudioPlay( Uint32 uIndex );

	//指定バンクのサウンドの音程を変更します
	static gxBool ChangeAudioPitch( Uint32 index , Float32 fRatio );

	//現在の時刻を取得します
	static Uint32 GetTime( Sint32 *pYear=NULL_POINTER , Sint32 *pMonth=NULL_POINTER , Sint32 *pDay=NULL_POINTER , Sint32 *pHour=NULL_POINTER , Sint32 *pMin=NULL_POINTER , Sint32 *pSec=NULL_POINTER , Sint32 *pMilliSec = NULL_POINTER);


	//コントローラーデバイス


	//入力デバイスの情報を返します
	static StJoyStat* Joy( Uint32 playerID = 0 );

	//キーボードデバイスからの入力を返します
	static Uint8 KeyBoard( Uint32 n );

	//タッチ状況を得る
	static StTouch* Touch( Sint32 n );

	//コントローラーを振動させる(止めるときは両方にゼロを設定する)
	static void SetRumble( Sint32 playerID , Sint32  bigMotorFrm = 30 , Sint32 smallMotorFrm = 30 );

	//その他

	//デバッグ文字を表示します
	static void Printf( Sint32 x , Sint32 y , Sint32 prio , Uint32 atr , Uint32 argb , gxChar* pFormat , ... );

	//デバッグコンソールにデバッグ文字を出力します
	static void DebugLog( gxChar* pFormat , ... );

	//高速なCos関数です
	static Float32 Cos( Float32 deg );

	//高速なSin関数です
	static Float32 Sin( Float32 deg );

	//高速なAtan2関数です
	static Float32 Atan( Float32 x ,Float32 y );

	//高速なsqrtです
	static Float32 Sqrt( Float32 n );

	//２点間の距離を返します
	static Float32 Distance( Float32 x ,Float32 y );

	static Float32 Distance( Float32 x1 ,Float32 y1 , Float32 x2 ,Float32 y2);

	//gxLibの設定ファイルを保存します
	static gxBool SaveConfig();

	//gxLibの設定ファイルをロードします
	static gxBool LoadConfig();

	//ローカルのファイルを取得する
	static Uint8* LoadFile( const gxChar* pFileName , Uint32* pLength );

	//ローカルにファイルを保存する
	static gxBool SaveFile( const gxChar* pFileName , Uint8* pData ,Uint32 uSize );

	//ローカルストレージからファイルを取得する
	static Uint8* LoadStorage( const gxChar* pFileName , Uint32* pLength );

	//ローカルストレージにファイルを保存する
	static gxBool SaveStorage( const gxChar* pFileName , Uint8* pData ,Uint32 uSize );

	//（xorShift法の）ランダム値を生成する
	static Uint32 Rand( Uint32 uSeed=0 );

	//毎フレームインクリメントされるカウンタを取得する
	static Uint32 GetGameCounter();

	//WEB上のファイルを取得する（未対応）
	static Uint8* LoadWebFile( gxChar* pURL , Uint32* pLength , gxChar* pUser , gxChar* pPassword);

	//スレッドを作成する
	static void CreateThread( void (*pFunc)(void*) , void * pArg );

	//デバッグ用のフラグを確認する

	static gxBool IsDebugSwitchOn(Sint32 n);

	//デバッグ用のスイッチを設定する

	static void   SetDebugSwitch( Sint32 n , gxBool bOn , gxBool bToggle = gxFalse );

	//IPアドレスを取得する
	Uint32 GetIPAddressV4( gxBool bLocalAddress = gxFalse );

	gxBool IsOnline();

	//gxLibの設定ファイルです

	enum {
		enSaveDataFreeArea = 30,
	};

	typedef struct StJoySign {
		Uint8 uDevice;
		Uint8 uButton;
	} StJoySign;

	typedef struct StSaveData {

		//設定ファイル構造体

		Sint32 m_sWindowType;
		Sint32 m_sVersion_no;
		Sint8  m_bWideScreen;
		Sint8  m_sFrameSkip;

		Sint8 sDummy[ 6 ];

		StJoySign Assign[ PLAYER_MAX ][ BTN_MAX ];

		Sint8  m_bUseJoyPad;
		Sint8  m_sUsePadIndex;
		Sint32 free[enSaveDataFreeArea];		//汎用

	} StSaveData;

	static StSaveData SaveData;

	static Sint32 m_DebugSwitch[8];				//PSPデバッガのDIPスイッチ相当
	static gxBool m_bMasterDebugSwitch;			//F8で切り替え

private:



};

//標準的なボタンのアサイン

enum {
	enBtnDecision = BTN_B,	//決定
	enBtnCancel   = BTN_A,	//キャンセル
};


//キャスト
#define s_cast static_cast
#define r_cast reinterpret_cast
#define c_cast const_cast
#define d_cast dynamic_cast

#define PI						(3.141592653589793238462643383279f)											///< π
#define RAD2DEG( r )	((r)*180.0f/PI)
#define DEG2RAD( r )	((r)/180.f*PI)
#define ABS( x )			( ( (x) < 0 ) ? -(x) : (x) )
#define	ARRAY_LENGTH( a )	( sizeof( a ) / sizeof( a[0] ) )
#define REV(v)					toF(1.0f/toF(v))															///< 逆数算出マクロ
#define SAFE_RELEASE(V)			if ( (V) != NULL ) { (V)->Release(); (V) = NULL; }							///< COM安全解放マクロ
#define SAFE_DELETE(V)			if ( (V) != NULL ) { delete (V); (V) = NULL; }								///< newメモリ安全解放
#define SAFE_DELETES(V)			if ( (V) != NULL ) { delete [] (V); (V) = NULL; }							///< new[]メモリ安全解放
#define SWAP(N1,N2)				{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										///< 値交換マクロ
#define CLAMP(x, low, high) ((x) > (high))? (high) : ((x) < (low))? (low) : (x)
#define POW(n) ((n)*(n))

//角度を３６０度以内に正規化する
#define NORMALIZE( n ){	while( (n)<0)  { (n)+=360; }	while( (n)>360){ (n)-=360; }	}
#define LIMIT_MIN(a,b) { (a) = ( (a) < (b) )? (b) : (a);	}
#define LIMIT_MAX(a,b) { (a) = ( (a) > (b) )? (b) : (a);	}
#define INIT_ARRAY( a , b , c )	for( Sint32 __ii__=0; __ii__< (b); __ii__ ++ ) { a[__ii__] = (c); }
#define DESTROY_ARRAY( a , b ) \
{\
	for( int nnn=0; nnn<(b); nnn++ )\
	{\
		if( ((a))[nnn] ) delete ((a)[nnn]);\
		((a)[nnn])=NULL;\
	}\
}\

#define ASSERT(n) assert(n)
#define	SINGLETON_DECLARE( T ) \
public: \
	static void CreateInstance() { s_pInstance = new T(); } \
	static void DeleteInstance() { if( s_pInstance ) delete( s_pInstance ); s_pInstance = NULL;	} \
	static T* GetInstance()      { if( s_pInstance == NULL ) CreateInstance(); return s_pInstance; } \
private: \
	static T* s_pInstance;

#define	SINGLETON_DECLARE_INSTANCE( T ) T* T::s_pInstance = NULL;



#include "gxLib/hard/machine.h"
#include "gxLib/util/gxUtil.h"

#define INLINE inline

namespace gxKey
{
	enum {
		DEL           = KEYBOARD_DELETE,
		INS           = KEYBOARD_INSERT,
		PAD0          = KEYBOARD_N0,
		PAD1          = KEYBOARD_N1,
		PAD2          = KEYBOARD_N2,
		PAD3          = KEYBOARD_N3,
		PAD4          = KEYBOARD_N4,
		PAD5          = KEYBOARD_N5,
		PAD6          = KEYBOARD_N6,
		PAD7          = KEYBOARD_N7,
		PAD8          = KEYBOARD_N8,
		PAD9          = KEYBOARD_N9,

		ESC           = KEYBOARD_ESCAPE,
		BS            = KEYBOARD_BACKSPACE,
		TAB           = KEYBOARD_TAB,
		RETURN        = KEYBOARD_RETURN,
		SHIFT         = KEYBOARD_SHIFT,
		RSHIFT        = KEYBOARD_RSHIFT,
		CTRL          = KEYBOARD_CTRL,
		RCTRL         = KEYBOARD_RCTRL,
		ALT           = KEYBOARD_ALT,
		RALT          = KEYBOARD_RALT,
		PAGEUP        = KEYBOARD_PAGEUP,
		PAGEDOWN      = KEYBOARD_PAGEDOWN,
		UP            = KEYBOARD_ARROW_UP,
		DOWN          = KEYBOARD_ARROW_DOWN,
		LEFT          = KEYBOARD_ARROW_LEFT,
		RIGHT         = KEYBOARD_ARROW_RIGHT,
		SPACE         = KEYBOARD_SPACE,
		ENTER         = KEYBOARD_ENTER,
		F1            = KEYBOARD_F1,
		F2            = KEYBOARD_F2,
		F3            = KEYBOARD_F3,
		F4            = KEYBOARD_F4,
		F5            = KEYBOARD_F5,
		F6            = KEYBOARD_F6,
		F7            = KEYBOARD_F7,
		F8            = KEYBOARD_F8,
		F9            = KEYBOARD_F9,
		F10           = KEYBOARD_F10,
		F11           = KEYBOARD_F11,
		F12           = KEYBOARD_F12,
		NUM0             = KEYBOARD_0,
		NUM1             = KEYBOARD_1,
		NUM2             = KEYBOARD_2,
		NUM3             = KEYBOARD_3,
		NUM4             = KEYBOARD_4,
		NUM5             = KEYBOARD_5,
		NUM6             = KEYBOARD_6,
		NUM7             = KEYBOARD_7,
		NUM8             = KEYBOARD_8,
		NUM9             = KEYBOARD_9,
		A             = KEYBOARD_A,
		B             = KEYBOARD_B,
		C             = KEYBOARD_C,
		D             = KEYBOARD_D,
		E             = KEYBOARD_E,
		F             = KEYBOARD_F,
		G             = KEYBOARD_G,
		H             = KEYBOARD_H,
		I             = KEYBOARD_I,
		J             = KEYBOARD_J,
		K             = KEYBOARD_K,
		L             = KEYBOARD_L,
		M             = KEYBOARD_M,
		N             = KEYBOARD_N,
		O             = KEYBOARD_O,
		P             = KEYBOARD_P,
		Q             = KEYBOARD_Q,
		R             = KEYBOARD_R,
		S             = KEYBOARD_S,
		T             = KEYBOARD_T,
		U             = KEYBOARD_U,
		V             = KEYBOARD_V,
		W             = KEYBOARD_W,
		X             = KEYBOARD_X,
		Y             = KEYBOARD_Y,
		Z             = KEYBOARD_Z,
	};
}


//以下のプリプロセッサをコンパイラに登録してください
//win32では、VC環境にて設定済み

//#define GX_DEBUG		//デバッグコンパイル時に使用（デバッグ情報を出力）、最適化なし
//#define GX_RELEASE	//マスターコンパイル環境と同等だが、デバッグ出力あり、最適化レベル最高
//#define GX_MASTER		//マスターコンパイル、デバッグ出力なし、最適化レベル最高

#endif

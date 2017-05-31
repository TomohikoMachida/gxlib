// --------------------------------------------------------------------
//
// つじつまあわせ用共通ヘッダ
//
// --------------------------------------------------------------------

#define PLATFORM_WINDOWS
#define GX_USE_OGGVORBIS

#ifdef _DEBUG
	#define GX_DEBUG
#else
	#define GX_RELEASE
#endif

#ifdef WIN32
	#define GX_BUILD_OPTIONx86
#else
	#define GX_BUILD_OPTIONx64
#endif

#pragma warning(disable : 4996)
#pragma warning(disable : 4819)

#include <d3d9.h>
#include <d3dx9.h>

//#define _WIN32_WINNT _WIN32_WINNT_WINXP
//#define _WIN32_WINNT _WIN32_WINNT_WIN2K
//#define _WIN32_WINNT _WIN32_WINNT_WINXP
//#define _WIN32_WINNT _WIN32_WINNT_VISTA
//#define _WIN32_WINNT _WIN32_WINNT_WIN7
//#define _WIN32_WINNT _WIN32_WINNT_WIN8

//#define _WIN32_WINNT _WIN32_WINNT_WIN8(d3dx9,hで定義済み)


#define DEBUG_FONT_SIZE (12)					//デバッグ用のフォントサイズ 12がデフォ
#define DEBUG_FONT_NAME "M+2VM+IPAG circle"		//デバッグ用のフォント種類
#define INDEXBUFFER_BIT (32)

#pragma warning(disable : 4996)
#pragma warning(disable : 4819)

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <assert.h>
#include <string.h>
#include <math.h>

//----------------------------------------------------
//プラットフォーム専用関数
//----------------------------------------------------
void Movie();
Uint32 GetDebugTime();
Uint32 GetVsyncRate();
void ExecuteApp( char *appname );
gxBool IsFullScreen();
void ChangeWindowMode( gxBool bWindow );
void ScreenCapture();


enum {
	eCmdChgTexture,
	eCmdNoneTexture,
	eCmdChgAttributeAlphaAdd,
	eCmdChgAttributeAlphaSub,
	eCmdChgAttributeAlphaCrs,
	eCmdChgAttributeAlphaRvs,
	eCmdChgAttributeAlphaNml,
	eCmdChgAttributeAlphaXor,
	eCmdChgAttributeAlphaScr,
	eCmdRenderSquare,
	eCmdRenderPoint,
	eCmdRenderLineStrip,
	eCmdRenderLineNormal,
	eCmdRenderTriangle,
	eCmdRenderFont,
};

typedef struct StCustomVertex
{
	Float32 x,y,z,rhw;
	Uint32  col;
	Float32 u,v;
} StCustomVertex;


class CCommandList
{
public:
	Uint32 eCommand;
	Uint32 arg[4];
	Sint32 x,y;
	void*  pString;
	Float32 opt;
private:

};



#define KEYBOARD_F1          (0x01)	//(VK_F1)
#define KEYBOARD_F2          (0x02)	//(VK_F2)
#define KEYBOARD_F3          (0x03)	//(VK_F3)
#define KEYBOARD_F4          (0x04)	//(VK_F4)
#define KEYBOARD_F5          (0x05)	//(VK_F5)
#define KEYBOARD_F6          (0x06)	//(VK_F6)
#define KEYBOARD_F7          (0x07)	//(VK_F7)
#define KEYBOARD_F8          (0x08)	//(VK_F8)
#define KEYBOARD_F9          (0x09)	//(VK_F9)
#define KEYBOARD_F10         (0x0A)	//(VK_F10)
#define KEYBOARD_F11         (0x0B)	//(VK_F11)
#define KEYBOARD_F12         (0x0C)	//(VK_F12)

#define KEYBOARD_ESCAPE      (0x10)	//(VK_ESCAPE)
#define KEYBOARD_BACKSPACE   (0x11)	//(VK_BACK)
#define KEYBOARD_TAB         (0x12)	//(VK_TAB)
#define KEYBOARD_RETURN      (0x13)	//(VK_RETURN)
#define KEYBOARD_ENTER       (0x13)	//(VK_RETURN)
#define KEYBOARD_SHIFT       (0x14)	//(VK_LSHIFT)
#define KEYBOARD_RSHIFT      (0x15)	//(VK_RSHIFT)
#define KEYBOARD_CTRL        (0x16)	//(VK_LCONTROL)
#define KEYBOARD_RCTRL       (0x17)	//(VK_RCONTROL)
#define KEYBOARD_ALT         (0x18)	//(VK_LMENU)
#define KEYBOARD_RALT        (0x19)	//(VK_RMENU)
#define KEYBOARD_ARROW_UP    (0x1A)	//(VK_UP)
#define KEYBOARD_ARROW_DOWN  (0x1B)	//(VK_DOWN)
#define KEYBOARD_ARROW_LEFT  (0x1C)	//(VK_LEFT)
#define KEYBOARD_ARROW_RIGHT (0x1D)	//(VK_RIGHT)
#define KEYBOARD_SPACE       (0x1E)	//(VK_SPACE)

#define KEYBOARD_N0          (0x20)	//(Numpad0)
#define KEYBOARD_N1          (0x21)	//(Numpad1)
#define KEYBOARD_N2          (0x22)	//(Numpad2)
#define KEYBOARD_N3          (0x23)	//(Numpad3)
#define KEYBOARD_N4          (0x24)	//(Numpad4)
#define KEYBOARD_N5          (0x25)	//(Numpad5)
#define KEYBOARD_N6          (0x26)	//(Numpad6)
#define KEYBOARD_N7          (0x27)	//(Numpad7)
#define KEYBOARD_N8          (0x28)	//(Numpad8)
#define KEYBOARD_N9          (0x29)	//(Numpad9)
#define KEYBOARD_PAGEUP      (0x2A)	//(PageUp)
#define KEYBOARD_PAGEDOWN    (0x2B)	//(PageDown)
#define KEYBOARD_DELETE		 (0x2C)	//(VK_DELETE)
#define KEYBOARD_INSERT		 (0x2D)	//(VK_INSERT)
#define KEYBOARD_HOME		 (0x2E)	//(VK_HOME)
#define KEYBOARD_END		 (0x2F)	//(VK_END)

#define KEYBOARD_0           ('0')	//0x30～
#define KEYBOARD_1           ('1')
#define KEYBOARD_2           ('2')
#define KEYBOARD_3           ('3')
#define KEYBOARD_4           ('4')
#define KEYBOARD_5           ('5')
#define KEYBOARD_6           ('6')
#define KEYBOARD_7           ('7')
#define KEYBOARD_8           ('8')
#define KEYBOARD_9           ('9')
#define KEYBOARD_A           ('A')
#define KEYBOARD_B           ('B')
#define KEYBOARD_C           ('C')
#define KEYBOARD_D           ('D')
#define KEYBOARD_E           ('E')
#define KEYBOARD_F           ('F')
#define KEYBOARD_G           ('G')
#define KEYBOARD_H           ('H')
#define KEYBOARD_I           ('I')
#define KEYBOARD_J           ('J')
#define KEYBOARD_K           ('K')
#define KEYBOARD_L           ('L')
#define KEYBOARD_M           ('M')
#define KEYBOARD_N           ('N')
#define KEYBOARD_O           ('O')
#define KEYBOARD_P           ('P')
#define KEYBOARD_Q           ('Q')
#define KEYBOARD_R           ('R')
#define KEYBOARD_S           ('S')
#define KEYBOARD_T           ('T')
#define KEYBOARD_U           ('U')
#define KEYBOARD_V           ('V')
#define KEYBOARD_W           ('W')
#define KEYBOARD_X           ('X')
#define KEYBOARD_Y           ('Y')
#define KEYBOARD_Z           ('Z')


#define KEYSIGN_U KEYBOARD_ARROW_UP
#define KEYSIGN_D KEYBOARD_ARROW_DOWN
#define KEYSIGN_L KEYBOARD_ARROW_LEFT
#define KEYSIGN_R KEYBOARD_ARROW_RIGHT

#define KEYSIGN01 KEYBOARD_Z		//ボタン１
#define KEYSIGN02 KEYBOARD_X		//ボタン２
#define KEYSIGN03 KEYBOARD_C		//ボタン３
#define KEYSIGN04 KEYBOARD_A		//ボタン４
#define KEYSIGN05 KEYBOARD_S		//ボタン５
#define KEYSIGN06 KEYBOARD_D		//ボタン６
#define KEYSIGN07 KEYBOARD_SHIFT	//ボタンＬ
#define KEYSIGN08 KEYBOARD_RSHIFT	//ボタンＲ
#define KEYSIGN09 KEYBOARD_CTRL		//ボタンL2
#define KEYSIGN10 KEYBOARD_RCTRL	//ボタンR2
#define KEYSIGN11 KEYBOARD_SPACE	//ＳＥＬＥＣＴ
#define KEYSIGN12 KEYBOARD_ENTER	//ＳＴＡＲＴ


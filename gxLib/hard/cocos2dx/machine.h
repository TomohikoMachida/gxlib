// --------------------------------------------------------------------
//
// ‚Â‚¶‚Â‚Ü‚ ‚í‚¹—p‹¤’Êƒwƒbƒ_
// Cocos—p
// --------------------------------------------------------------------
#ifndef _COCOS2d_MACHINE_H_
#define _COCOS2d_MACHINE_H_

#define USE_OPENGL

#include "cocos2d.h"
#include "AppDelegate.h"

USING_NS_CC;

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
	Uint16 eCommand;
	Uint16 arg[4];
	Sint16 x,y;
	void*  pString;
	Float32 opt;
private:

};

#define KEYBOARD_ESCAPE      (EventKeyboard::KeyCode::KEY_ESCAPE
#define KEYBOARD_BACKSPACE   (EventKeyboard::KeyCode::KEY_BACKSPACE
#define KEYBOARD_TAB         (EventKeyboard::KeyCode::KEY_TAB
#define KEYBOARD_RETURN      (EventKeyboard::KeyCode::KEY_RETURN
#define KEYBOARD_SHIFT       (EventKeyboard::KeyCode::KEY_SHIFT
#define KEYBOARD_RSHIFT      (EventKeyboard::KeyCode::KEY_RIGHT_SHIFT
#define KEYBOARD_CTRL        (EventKeyboard::KeyCode::KEY_CTRL
#define KEYBOARD_RCTRL       (EventKeyboard::KeyCode::KEY_RIGHT_CTRL
#define KEYBOARD_ALT         (EventKeyboard::KeyCode::KEY_ALT
#define KEYBOARD_RALT        (EventKeyboard::KeyCode::KEY_RIGHT_ALT
#define KEYBOARD_ARROW_UP    (EventKeyboard::KeyCode::KEY_UP_ARROW)
#define KEYBOARD_ARROW_DOWN  (EventKeyboard::KeyCode::KEY_DOWN_ARROW)
#define KEYBOARD_ARROW_LEFT  (EventKeyboard::KeyCode::KEY_LEFT_ARROW)
#define KEYBOARD_ARROW_RIGHT (EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
#define KEYBOARD_SPACE       (EventKeyboard::KeyCode::KEY_SPACE)
#define KEYBOARD_ENTER       (EventKeyboard::KeyCode::KEY_RETURN)
#define KEYBOARD_F1          (EventKeyboard::KeyCode::KEY_F1)
#define KEYBOARD_F2          (EventKeyboard::KeyCode::KEY_F2)
#define KEYBOARD_F3          (EventKeyboard::KeyCode::KEY_F3)
#define KEYBOARD_F4          (EventKeyboard::KeyCode::KEY_F4)
#define KEYBOARD_F5          (EventKeyboard::KeyCode::KEY_F5)
#define KEYBOARD_F6          (EventKeyboard::KeyCode::KEY_F6)
#define KEYBOARD_F7          (EventKeyboard::KeyCode::KEY_F7)
#define KEYBOARD_F8          (EventKeyboard::KeyCode::KEY_F8)
#define KEYBOARD_F9          (EventKeyboard::KeyCode::KEY_F9)
#define KEYBOARD_F10         (EventKeyboard::KeyCode::KEY_F10)
#define KEYBOARD_F11         (EventKeyboard::KeyCode::KEY_F11)
#define KEYBOARD_F12         (EventKeyboard::KeyCode::KEY_F12)
#define KEYBOARD_0           (EventKeyboard::KeyCode::KEY_0)
#define KEYBOARD_1           (EventKeyboard::KeyCode::KEY_1)
#define KEYBOARD_2           (EventKeyboard::KeyCode::KEY_2)
#define KEYBOARD_3           (EventKeyboard::KeyCode::KEY_3)
#define KEYBOARD_4           (EventKeyboard::KeyCode::KEY_4)
#define KEYBOARD_5           (EventKeyboard::KeyCode::KEY_5)
#define KEYBOARD_6           (EventKeyboard::KeyCode::KEY_6)
#define KEYBOARD_7           (EventKeyboard::KeyCode::KEY_7)
#define KEYBOARD_8           (EventKeyboard::KeyCode::KEY_8)
#define KEYBOARD_9           (EventKeyboard::KeyCode::KEY_9)
#define KEYBOARD_A           (EventKeyboard::KeyCode::KEY_A)
#define KEYBOARD_B           (EventKeyboard::KeyCode::KEY_B)
#define KEYBOARD_C           (EventKeyboard::KeyCode::KEY_C)
#define KEYBOARD_D           (EventKeyboard::KeyCode::KEY_D)
#define KEYBOARD_E           (EventKeyboard::KeyCode::KEY_E)
#define KEYBOARD_F           (EventKeyboard::KeyCode::KEY_F)
#define KEYBOARD_G           (EventKeyboard::KeyCode::KEY_G)
#define KEYBOARD_H           (EventKeyboard::KeyCode::KEY_H)
#define KEYBOARD_I           (EventKeyboard::KeyCode::KEY_I)
#define KEYBOARD_J           (EventKeyboard::KeyCode::KEY_J)
#define KEYBOARD_K           (EventKeyboard::KeyCode::KEY_K)
#define KEYBOARD_L           (EventKeyboard::KeyCode::KEY_L)
#define KEYBOARD_M           (EventKeyboard::KeyCode::KEY_M)
#define KEYBOARD_N           (EventKeyboard::KeyCode::KEY_N)
#define KEYBOARD_O           (EventKeyboard::KeyCode::KEY_0)
#define KEYBOARD_P           (EventKeyboard::KeyCode::KEY_P)
#define KEYBOARD_Q           (EventKeyboard::KeyCode::KEY_Q)
#define KEYBOARD_R           (EventKeyboard::KeyCode::KEY_R)
#define KEYBOARD_S           (EventKeyboard::KeyCode::KEY_S)
#define KEYBOARD_T           (EventKeyboard::KeyCode::KEY_T)
#define KEYBOARD_U           (EventKeyboard::KeyCode::KEY_U)
#define KEYBOARD_V           (EventKeyboard::KeyCode::KEY_V)
#define KEYBOARD_W           (EventKeyboard::KeyCode::KEY_W)
#define KEYBOARD_X           (EventKeyboard::KeyCode::KEY_X)
#define KEYBOARD_Y           (EventKeyboard::KeyCode::KEY_Y)
#define KEYBOARD_Z           (EventKeyboard::KeyCode::KEY_Z)

#define KEYSIGN_U ((Sint32)(KEYBOARD_ARROW_UP))
#define KEYSIGN_D ((Sint32)(KEYBOARD_ARROW_DOWN))
#define KEYSIGN_L ((Sint32)(KEYBOARD_ARROW_LEFT))
#define KEYSIGN_R ((Sint32)(KEYBOARD_ARROW_RIGHT))

#define KEYSIGN01 ((Sint32)(KEYBOARD_Z))		//ƒ{ƒ^ƒ“‚P
#define KEYSIGN02 ((Sint32)(KEYBOARD_X))		//ƒ{ƒ^ƒ“‚Q
#define KEYSIGN03 ((Sint32)(KEYBOARD_C))		//ƒ{ƒ^ƒ“‚R
#define KEYSIGN04 ((Sint32)(KEYBOARD_A))		//ƒ{ƒ^ƒ“‚S
#define KEYSIGN05 ((Sint32)(KEYBOARD_S))		//ƒ{ƒ^ƒ“‚T
#define KEYSIGN06 ((Sint32)(KEYBOARD_D))		//ƒ{ƒ^ƒ“‚U
#define KEYSIGN07 ((Sint32)(KEYBOARD_SHIFT))	//ƒ{ƒ^ƒ“‚k
#define KEYSIGN08 ((Sint32)(KEYBOARD_RSHIFT))	//ƒ{ƒ^ƒ“‚q
#define KEYSIGN09 ((Sint32)(KEYBOARD_CTRL))		//ƒ{ƒ^ƒ“L2
#define KEYSIGN10 ((Sint32)(KEYBOARD_RCTRL))	//ƒ{ƒ^ƒ“R2
#define KEYSIGN11 ((Sint32)(KEYBOARD_SPACE))	//‚r‚d‚k‚d‚b‚s
#define KEYSIGN12 ((Sint32)(KEYBOARD_ENTER))	//‚r‚s‚`‚q‚s


#endif	//_COCOS2d_MACHINE_H_



#include <gxLib.h>
#include <gxLib/gxTexManager.h>
#include "CLuaManager.h"

SINGLETON_DECLARE_INSTANCE( CLuaManager );

gxPos g_LuaOffsetPos = { 0 , 0 , 0 };

void CLuaManager::userMain()
{
	Sint32 err = 0;
	lua_getglobal( LuaState , "gameMain");
	err = lua_pcall(LuaState, 0, 0, 0 );

	
	for( Sint32 ii=0; ii<m_sDragAndDropCnt; ii++  )
	{
		m_sDragAndDropCnt --;
		lua_getglobal( LuaState , "DragAndDrop");
		lua_pushstring( LuaState , m_pDragAndDropFileName[ ii ] );
		err = lua_pcall(LuaState, 1, 0, 0 );
	}

	if (err)
	{
		errorFunc(LuaState);
		lua_close(LuaState);
		LuaState = NULL;
		luaSeq = enLuaStatErrorEnd;
	}
	else
	{	
/*
		Sint32 n = 0;
		Uint32 argb=0xffffffff;

		lua_getglobal( LuaState, "VideoRAM" );

		//errorFunc(LuaState);

		for (Sint32 y = 0; y < 160; y++)
		{
			for (Sint32 x = 0; x < 160; x++)
			{
				n = x + 1 +y * 160;
				lua_rawgeti(LuaState, -1 , n );

				argb = lua_tonumber(LuaState, -1);

				CTexManager::GetInstance()->GetAtlasTexture(0)->SetARGB( x, y, argb);

				lua_pop(LuaState , 1 );
			}
		}
//		CTexManager::GetInstance()->SetForceUpdate(0);
		gxLib::UploadTexture();

		//errorFunc(LuaState);
		lua_pop(LuaState, -1);
*/
	}
}

Sint32 CLuaManager::gxDraw( lua_State *L )
{
	const gxChar* name = lua_tostring( L , 1 );
	//strcmp(name, "str");

	//box

	if( lua_tonumber( L , 1 ) == 0 )
	{
		//box
		Sint32 x1,y1,x2,y2,pr,at;
		gxBool bFill;
		x1 = lua_tonumber( L , 2 ) + g_LuaOffsetPos.x;
		y1 = lua_tonumber( L , 3 ) + g_LuaOffsetPos.y;
		x2 = lua_tonumber( L , 4 ) + g_LuaOffsetPos.x;
		y2 = lua_tonumber( L , 5 ) + g_LuaOffsetPos.y;
		pr = lua_tonumber( L , 6 );
		at = lua_tointeger( L , 7 );
		Uint32 argb = lua_tointeger( L , 8 );
		bFill = (lua_tonumber( L , 9 ))? gxTrue : gxFalse;

		gxLib::DrawBox( x1 , y1 , x2 , y2 ,pr , bFill , at , argb );
	}

	if( lua_tonumber( L , 1 ) == 10 )
	{
		//point
		Sint32 x1,y1,pr,at;
		x1 = lua_tonumber( L , 2 ) + g_LuaOffsetPos.x;
		y1 = lua_tonumber( L , 3 ) + g_LuaOffsetPos.y;
		pr = lua_tonumber( L , 4 );
		at = lua_tointeger( L , 5 );
		Uint32 argb = lua_tointeger( L , 6 );

		gxLib::DrawPoint( x1 , y1 , pr , at , argb );
	}

	if( lua_tonumber( L , 1 ) == 20 )
	{
		//line
		Sint32 x1,y1,x2,y2,pr,at;
		x1 = lua_tonumber( L , 2 ) + g_LuaOffsetPos.x;
		y1 = lua_tonumber( L , 3 ) + g_LuaOffsetPos.y;
		x2 = lua_tonumber( L , 4 ) + g_LuaOffsetPos.x;
		y2 = lua_tonumber( L , 5 ) + g_LuaOffsetPos.y;
		pr = lua_tonumber( L , 6 );
		at = lua_tointeger( L , 7 );
		Uint32 argb = lua_tointeger( L , 8 );

		gxLib::DrawLine( x1 , y1 , x2 , y2 , pr , at , argb );
	}

	if( lua_tonumber( L , 1 ) == 30 )
	{
		//PutSprite
		Sint32 x1,y1,pr,at,pg,u,v,w,h,cx,cy;
		Float32 fRot, fx,fy;
		Uint32 argb;

		x1 = lua_tonumber( L , 2 ) + g_LuaOffsetPos.x;
		y1 = lua_tonumber( L , 3 ) + g_LuaOffsetPos.y;
		pr = lua_tonumber( L , 4 );

		pg = lua_tonumber( L , 5 );
		u  = lua_tonumber( L , 6 );
		v  = lua_tonumber( L , 7 );
		w  = lua_tonumber( L , 8 );
		h  = lua_tonumber( L , 9 );
		cx = lua_tonumber( L , 10 );
		cy = lua_tonumber( L , 11 );

		at   = lua_tointeger( L , 12 );
		argb = lua_tointeger( L , 13 );

		fRot = lua_tonumber( L , 14 );
		fx   = lua_tonumber( L , 15 );
		fy   = lua_tonumber( L , 16 );

		gxLib::PutSprite( x1 , y1 , pr , pg , u,v,w,h,cx,cy,at , argb ,fRot , fx,fy);
	}
	else if( lua_tonumber( L , 1 ) == 50 )
	{
		Sint32 x1 ; Sint32 y1;
		Sint32 x2 ; Sint32 y2;
		Sint32 x3 ; Sint32 y3;
		Uint32 argb1;
		Uint32 argb2;
		Uint32 argb3;
		Sint32 prio;
		Uint32 atr;

		//Triangle
		x1 = lua_tonumber( L , 2 ) + g_LuaOffsetPos.x;
		y1 = lua_tonumber( L , 3 ) + g_LuaOffsetPos.y;
		argb1 = lua_tointeger( L , 4 );

		x2 = lua_tonumber( L , 5 ) + g_LuaOffsetPos.x;
		y2 = lua_tonumber( L , 6 ) + g_LuaOffsetPos.y;
		argb2 = lua_tointeger( L , 7 );

		x3 = lua_tonumber( L , 8 ) + g_LuaOffsetPos.x;
		y3 = lua_tonumber( L , 9 ) + g_LuaOffsetPos.y;
		argb3 = lua_tointeger( L , 10 );

		prio = lua_tointeger( L , 11 );
		atr  = lua_tointeger( L , 12 );

		gxLib::DrawColorTriangle(
			x1 , y1 ,argb1,
			x2 , y2 ,argb2,
			x3 , y3 ,argb3,
			prio,
			atr );
	}
	else if( lua_tonumber( L , 1 ) == 60 )
	{
		Sint32 x1 ; Sint32 y1,u1,v1;
		Sint32 x2 ; Sint32 y2,u2,v2;
		Sint32 x3 ; Sint32 y3,u3,v3;
		Uint32 argb;
		Sint32 tpg;
		Sint32 prio;
		Uint32 atr;

		//Tex & Triangle
		x1 = lua_tonumber ( L , 2 ) + g_LuaOffsetPos.x;
		y1 = lua_tonumber ( L , 3 ) + g_LuaOffsetPos.y;
		u1 = lua_tointeger( L , 4 );
		v1 = lua_tointeger( L , 5 );

		x2 = lua_tonumber ( L , 6 ) + g_LuaOffsetPos.x;
		y2 = lua_tonumber ( L , 7 ) + g_LuaOffsetPos.y;
		u2 = lua_tointeger( L , 8 );
		v2 = lua_tointeger( L , 9 );

		x3 = lua_tonumber ( L ,10 ) + g_LuaOffsetPos.x;
		y3 = lua_tonumber ( L ,11 ) + g_LuaOffsetPos.y;
		u3 = lua_tointeger( L ,12 );
		v3 = lua_tointeger( L ,13 );

		tpg  = lua_tointeger( L , 14 );
		prio = lua_tointeger( L , 15 );
		atr  = lua_tointeger( L , 16 );
		argb = lua_tointeger( L , 17 );

		gxLib::PutTriangle(
			x1 , y1 ,u1, v1,
			x2 , y2 ,u2, v2,
			x3 , y3 ,u3, v3,
			tpg,
			prio,
			atr,
			argb );
	}
	else if (lua_tonumber(L, 1) == 100)
	{
		//Printf
		Sint32 x, y, prio,atr;
		x = lua_tonumber(L, 2) + g_LuaOffsetPos.x;
		y = lua_tonumber(L, 3) + g_LuaOffsetPos.y;
		prio = lua_tonumber(L, 4);
		atr  = lua_tonumber(L, 5);

		Uint32 argb = lua_tointeger(L, 6);

		gxChar *pStr = CLuaManager::GetLuaString( lua_tostring(L, 7) );

		gxLib::Printf(x, y, prio, atr, argb, pStr );
	}

	else if (lua_tonumber(L, 1) == 110 )
	{
		//SetBG
		Uint32 argb = lua_tointeger(L, 2);
		gxLib::SetBgColor( argb );
	}
	else if (lua_tonumber(L, 1) == 200)
	{
		//LoadAudio
		Uint32 id = lua_tointeger(L, 2);
		gxChar *pStr = GetLuaString( lua_tostring(L, 3) );
		gxLib::LoadAudio( id , pStr );
	}
	else if (lua_tonumber(L, 1) == 210)
	{
		//PlaySound
		Uint32 id = lua_tointeger(L, 2);
		gxBool  bLoop = (gxBool)lua_tointeger(L, 3);
		gxBool  bOverWrap = (gxBool)lua_tointeger(L, 4);
		gxLib::PlayAudio(id, bLoop, bOverWrap);
	}
	else if (lua_tonumber(L, 1) == 220)
	{
		//StopAudio
		Uint32 id = lua_tointeger(L, 2);
		Sint32  frm     = (Sint32)lua_tointeger(L, 3);
		gxLib::StopAudio( id, frm );
	}

	else if (lua_tonumber(L, 1) == 400 )
	{
		//loadTexture
		Sint32 page       = lua_tointeger(L, 2);
		gxChar *pFileName = GetLuaString( lua_tostring (L, 3) );
		Uint32 colorKey   = lua_tointeger(L, 4);

		Sint32 ox, oy;
		ox = lua_tonumber( L, 5 );
		oy = lua_tonumber( L, 6 );

		gxLib::LoadTexture( page , pFileName , colorKey , ox, oy );
	}
	else if (lua_tonumber(L, 1) == 410 )
	{
		//static gxBool LoadMovie( Sint32 uIndex , gxChar *pFileName , Sint32 texPage , Sint32 uAudioIndex = -1 , gxChar *AudioFileName = NULL_POINTER );
	}
	else if (lua_tonumber(L, 1) == 411 )
	{
		//static gxBool PlayMovie( Sint32 uIndex , gxBool bLoop = gxFalse );
	}
	else if (lua_tonumber(L, 1) == 412 )
	{
		//static gxBool StillMovie( Sint32 uIndex , Sint32 uFrame );
	}
	else if (lua_tonumber(L, 1) == 413 )
	{
		//static gxBool StopMovie( Sint32 uIndex );
	}

	else if (lua_tonumber(L, 1) == 500 )
	{
		//Rand:Luaに戻り値を返す
		Uint32 r = gxLib::Rand();
		lua_pushinteger(L, r);
		return 1;
	}
	else if (lua_tonumber(L, 1) == 600 )
	{
		//LoadFile
		gxChar *pFileName = CLuaManager::GetLuaString( lua_tostring(L, 2) );
		Uint32 uSize=0;

		Uint8 *pData = gxLib::LoadFile( pFileName , &uSize );

		lua_newtable( L );
	    for ( Sint32 ii = 0; ii < uSize; ii++ )
		{
	        lua_pushnumber( L , pData[ii]);
			lua_rawseti(L , 2, ii + 1);
		}

		SAFE_DELETE( pData );
		return 1;
	}
	else if (lua_tonumber(L, 1) == 900)
	{
		//break ポイント

//		errorFunc2(L);
	}
	else if (lua_tonumber(L, 1) == 910)
	{
		//DebugLog
		gxChar *pStr = CLuaManager::GetLuaString( lua_tostring(L, 2) );
		gxLib::DebugLog( pStr );

	}
/*
	static gxBool SetAudioVolume ( Uint32 index ,Float32 fVolume );
	static gxBool SetAudioMasterVolume( Float32 fVolume );
	static gxBool IsAudioPlay( Uint32 uIndex );
	static gxBool ChangeAudioPitch( Uint32 index , Float32 fRatio );

	static Uint32 DrawTriangle(
	static Uint32 DrawColorTriangle(

	static Uint32 DrawColorBox(
	static Uint32 GetTime( Sint32 *pYear=NULL_POINTER , Sint32 *pMonth=NULL_POINTER , Sint32 *pDay=NULL_POINTER , Sint32 *pHour=NULL_POINTER , Sint32 *pMin=NULL_POINTER , Sint32 *pSec=NULL_POINTER , Sint32 *pMilliSec = NULL_POINTER);
	static Uint8 KeyBoard( Uint32 n );
	static void SetRumble( Sint32 playerID , Sint32  bigMotorFrm = 30 , Sint32 smallMotorFrm = 30 );

	static Float32 Cos( Float32 deg );
	static Float32 Sin( Float32 deg );
	static Float32 Atan( Float32 x ,Float32 y );
	static Float32 Sqrt( Float32 n );
	static Float32 Distance( Float32 x ,Float32 y );
	static Float32 Distance( Float32 x1 ,Float32 y1 , Float32 x2 ,Float32 y2);
	static gxBool SaveConfig();
	static gxBool LoadConfig();

	static gxBool ReadTexture ( Uint32 texPage , const Uint8* pBuffer , Uint32 pSize , Uint32 colorKey=0xff00ff00 ,Uint32 ox = 0 , Uint32 oy = 0 , Sint32 *w=NULL_POINTER , Sint32 *h=NULL_POINTER );
	static Uint8* LoadFile( const gxChar* pFileName , Uint32* pLength );
	static gxBool SaveFile( const gxChar* pFileName , Uint8* pData ,Uint32 uSize );
	static Uint8* LoadStorage( const gxChar* pFileName , Uint32* pLength );
	static gxBool SaveStorage( const gxChar* pFileName , Uint8* pData ,Uint32 uSize );
	static Uint32 GetGameCounter();
	static Uint8* LoadWebFile( gxChar* pURL , Uint32* pLength , gxChar* pUser , gxChar* pPassword);
	static void CreateThread( void (*pFunc)(void*) , void * pArg );
	static gxBool IsDebugSwitchOn(Sint32 n);
	static void   SetDebugSwitch( Sint32 n , gxBool bOn , gxBool bToggle = gxFalse );
*/

	return 0;

}


void CLuaManager::errorFunc(lua_State *L)
{
	// スタックを見る関数
	{
		// スタック数を取得
		const int num = lua_gettop(L);
		if (num == 0) {
			gxLib::DebugLog("No stack.\n");
			return;
		}

		for (int i = num; i >= 1; i--) {
			gxLib::DebugLog("%03d(%04d): ", i, -num + i - 1);
			int type = lua_type(L, i);
			switch (type) {
			case LUA_TNIL:
				gxLib::DebugLog("NIL\n");
				break;
			case LUA_TBOOLEAN:
				gxLib::DebugLog("BOOLEAN %s\n", lua_toboolean(L, i) ? "true" : "false");
				break;
			case LUA_TLIGHTUSERDATA:
				gxLib::DebugLog("LIGHTUSERDATA\n");
				break;
			case LUA_TNUMBER:
				gxLib::DebugLog("NUMBER %f\n", lua_tonumber(L, i));
				break;
			case LUA_TSTRING:
				{
					gxChar *pString = GetLuaString( lua_tostring(L, i) );

					gxLib::DebugLog("STRING %s\n", pString );
					{
						Sint32 n = strlen( pString );
						if( n >= 1023 ) n = 1023;
						memcpy( errorString , pString , n );
						//sprintf( errorString , "%s",  );
						errorString[n] = 0x00;
					}
				}
				break;
			case LUA_TTABLE:
				gxLib::DebugLog("TABLE\n");
				break;
			case LUA_TFUNCTION:
				gxLib::DebugLog("FUNCTION\n");
				break;
			case LUA_TUSERDATA:
				gxLib::DebugLog("USERDATA\n");
				break;
			case LUA_TTHREAD:
				gxLib::DebugLog("THREAD\n");
				break;
			}
		}
		gxLib::DebugLog("-----------------------------\n\n");
	}


}

gxChar *CLuaManager::GetLuaString(const gxChar *pString)
{
	if( pString == NULL ) return "NULL";

	return (gxChar*)pString;
}

void CLuaManager::DragAndDrop( gxChar *pFileName )
{

	gxChar ext[128];
	gxUtil::GetExt( pFileName , ext );
	gxUtil::StrUpr( ext );

	if( strcmp(".LUA" , ext) == 0 )
	{
		if( m_pLuaControl )
		{
			Reset();
		}
		if( m_pLuaControl == NULL )
		{
			m_pLuaControl = this;
		}
		m_pLuaControl->Load( pFileName );
	}
	else
	{
		if( m_pLuaControl == NULL ) return;

		sprintf( m_pDragAndDropFileName[ m_sDragAndDropCnt ] , "%s" , pFileName );
		m_sDragAndDropCnt ++;
		

	}
}


void CLuaManager::Action()
{
	g_LuaOffsetPos.x = m_Offset.x;
	g_LuaOffsetPos.y = m_Offset.y;

	luaMain();

}


void errorFunc2(lua_State *L)
{
	// スタック数を取得
	const int num = lua_gettop(L);
	if (num == 0) {
		gxLib::DebugLog("No stack.\n");
		return;
	}

	for (int i = num; i >= 1; i--) {
		gxLib::DebugLog("%03d(%04d): ", i, -num + i - 1);
		int type = lua_type(L, i);
		switch (type) {
		case LUA_TNIL:
			gxLib::DebugLog("NIL\n");
			break;
		case LUA_TBOOLEAN:
			gxLib::DebugLog("BOOLEAN %s\n", lua_toboolean(L, i) ? "true" : "false");
			break;
		case LUA_TLIGHTUSERDATA:
			gxLib::DebugLog("LIGHTUSERDATA\n");
			break;
		case LUA_TNUMBER:
			gxLib::DebugLog("NUMBER %f\n", lua_tonumber(L, i));
			break;
		case LUA_TSTRING:
			gxLib::DebugLog("STRING %s\n", lua_tostring(L, i));
			break;
		case LUA_TTABLE:
			gxLib::DebugLog("TABLE\n");
			break;
		case LUA_TFUNCTION:
			gxLib::DebugLog("FUNCTION\n");
			break;
		case LUA_TUSERDATA:
			gxLib::DebugLog("USERDATA\n");
			break;
		case LUA_TTHREAD:
			gxLib::DebugLog("THREAD\n");
			break;
		}
	}

}


void luaTest()
{
	static CLuaManager *pLuaControl = NULL;

	if( pLuaControl == NULL )
	{
		pLuaControl = new CLuaManager();
		pLuaControl->Load("lua/gameMain.lua");
	}

	pLuaControl->Action();

	if( gxLib::Joy(0)->trg&BTN_START )
	{
		delete pLuaControl;
		pLuaControl = NULL;
	}

}


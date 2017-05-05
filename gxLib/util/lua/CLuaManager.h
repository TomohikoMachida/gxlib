#ifndef _CLUA_MANAGER_H_
#define _CLUA_MANAGER_H_

#include "lua.hpp"

class CLuaManager
{
public:

	enum {
		enLuaStatInit,
		enLuaStatLoad,
		enLuaStatMain,
		enLuaStatErrorEnd,
	};

	enum {
		enDragAndDropFileMax = 8,
	};

	CLuaManager()
	{
		m_FileName[0] = 0x00;
		m_pLuaScriptData  = NULL;
		m_uScriptFileSize = 0;

		init();
	}

	virtual ~CLuaManager()
	{
		dispose();

		m_pLuaControl = NULL;
	}

	void init()
	{
		LuaState = NULL;

		luaSeq = 0;

		errorString[0] = 0x00;

		m_pLuaControl = NULL;

		m_Offset.x = 0;
		m_Offset.y = 0;

		m_sDragAndDropCnt = 0;

		for( Sint32 ii=0;ii<enDragAndDropFileMax; ii++ )
		{
			m_pDragAndDropFileName[ii] = new gxChar[512];
		}
	}

	void dispose()
	{
		if(LuaState ) lua_remove( LuaState , 0 );
		if (LuaState) lua_close( LuaState );

		for( Sint32 ii=0;ii<enDragAndDropFileMax; ii++ )
		{
			SAFE_DELETES( m_pDragAndDropFileName[ii] );
		}

		LuaState = NULL;
	}

	void Reset()
	{
		if( m_pLuaControl )
		{
			dispose();
		}

		init();
	}

	void Action();

	void Load( gxChar *pFileName )
	{
		sprintf( m_FileName , "%s" , pFileName );
		
		Uint8 *pData;

		pData = gxLib::LoadFile( m_FileName , &m_uScriptFileSize );

		if( pData )
		{
			SAFE_DELETE( m_pLuaScriptData );
			m_pLuaScriptData = pData;
		}

		if (LuaState)
		{
			lua_close(LuaState);
			luaSeq = enLuaStatInit;
			LuaState = NULL;
		}
	}

	void Set( gxChar *pLuaGlobalName , Sint32 value )
	{
		//Luaのグローバル変数に値を入れる

		//スタックに値を乗せて
		lua_pushinteger( LuaState , value );

		//Lua側に持って行ってもらう
		lua_setglobal( LuaState , pLuaGlobalName );
	}

	Sint32 Get(  gxChar *pLuaGlobalName )
	{
		//スタックに値を乗せて
		lua_getglobal( LuaState , pLuaGlobalName );

		//intに変換して返す
		return lua_tonumber(LuaState, -1);
	}

	void DragAndDrop( gxChar *pFileName );

	void SetOffset( Sint32 x , Sint32 y )
	{
		m_Offset.x = x;
		m_Offset.y = y;
	}

	SINGLETON_DECLARE( CLuaManager );

private:

	gxPos m_Offset;

protected:

	void luaMain()
	{
		switch( luaSeq ){
		case enLuaStatInit:
			LuaState = luaL_newstate();
			luaL_openlibs( LuaState );
			luaSeq = enLuaStatLoad;
			break;

		case enLuaStatLoad:
			if( m_FileName[0] )
			{
				userInit();
				errorFunc(LuaState);
				Uint32 uSize;
				Uint8 *pData;

				if( m_pLuaScriptData )
				{
					pData = m_pLuaScriptData;
				}

				// Sint32 err = luaL_loadfile( LuaState, m_FileName );
				// lua_pcall(LuaState, 0, 0, 0);

				//Sint32 err = luaL_dofile(LuaState, m_FileName );

				Sint32 err = luaL_loadbuffer( LuaState, (const char*)m_pLuaScriptData , m_uScriptFileSize , (const char*)m_FileName );
				lua_pcall(LuaState, 0, 0, 0);

				switch ( err ) {
				case 0:
					{
						m_pLuaControl = this;
						lua_getglobal(LuaState, "InitLib");
						err = lua_pcall(LuaState, 0, 0, 0);
						errorFunc(LuaState);
						luaSeq = enLuaStatMain;
					}
					break;
				case LUA_ERRSYNTAX:
				case LUA_ERRMEM:
				default:
					errorFunc(LuaState);
					luaSeq = enLuaStatErrorEnd;
					break;
				}
			}
			break;

		case enLuaStatMain:
			if( m_pLuaControl == NULL ) break;
			initAction();
			userMain();
			break;

		case enLuaStatErrorEnd:
			if( errorString[0] )
			{
				gxLib::Printf( 0 , WINDOW_H-32 , PRIORITY_MAX , ATR_DFLT , ARGB_DFLT , errorString  );
			}
			break;

		}

//		gxLib::PutSprite(0, 0, 0, 0, 0, 0, 160, 160);

	}

	virtual void userInit()
	{
		lua_register( LuaState , "gxDraw" , &gxDraw );
	}

	void initAction()
	{
		Set( "PadPush"     , gxLib::Joy(0)->psh );
		Set( "PadTrig"     , gxLib::Joy(0)->trg );
		Set( "PadRepeat"   , gxLib::Joy(0)->rep );
		Set( "PadRelease"  , gxLib::Joy(0)->rls );
		Set( "MouseX"      , gxLib::Joy(0)->mx );
		Set( "MouseY"      , gxLib::Joy(0)->my );
//		Set( "KeyBoard"    , gxLib::Joy(0)->psh );
		Set( "GameCounter" , gxLib::GetGameCounter() );

		gxChar buf[256];

		for( Sint32 ii=0; ii<0xff; ii++ )
		{
			sprintf( buf , "KeyBoardPush[%d]" , ii );
			Set( buf , ( gxLib::KeyBoard( ii )&enStatPush )? 1 : 0 );

			sprintf( buf , "KeyBoardTrig[%d]" , ii );
			Set( buf , ( gxLib::KeyBoard( ii )&enStatTrig )? 1 : 0 );

			sprintf( buf , "KeyBoardRelease[%d]" , ii );
			Set( buf , ( gxLib::KeyBoard( ii )&enStatRelease )? 1 : 0 );

			sprintf( buf , "KeyBoardRepeat[%d]" , ii );
			Set( buf , ( gxLib::KeyBoard( ii )&enStatRepeat )? 1 : 0 );
		}


//		lua_setglobal( LuaState , "PadPush" );
//		lua_setglobal( LuaState , "PadTrig" );
//		lua_setglobal( LuaState , "PadRepeat" );
//		lua_setglobal( LuaState , "PadRelease" );
//		lua_setglobal( LuaState , "MouseX" );
//		lua_setglobal( LuaState , "MouseY" );
//		lua_setglobal( LuaState , "KeyBoard" );
//		lua_setglobal( LuaState , "GameCounter" );
	}

	void errorFunc(lua_State *L);
	virtual void userMain();
	static Sint32 gxDraw( lua_State *L );

	static gxChar *GetLuaString(const gxChar *pString);

	lua_State *LuaState;

	Sint32 luaSeq;

	gxChar m_FileName[256];
	gxChar errorString[1024];

	CLuaManager *m_pLuaControl;
	Uint8 *m_pLuaScriptData;
	Uint32 m_uScriptFileSize;

	Sint32 m_sDragAndDropCnt;
	gxChar *m_pDragAndDropFileName[enDragAndDropFileMax];
};


//テスト

void luaTest();

#endif


//--------------------------------------------------
//
// gxMain.h
// メインループ制御
//
//--------------------------------------------------

#include <gxLib.h>
#include "gx.h"
#include "gxOrderManager.h"
#include "gxTexManager.h"
#include "gxRender.h"
#include "gxPadManager.h"
#include "gxSoundManager.h"
#include "gxMovieManager.h"
#include "gxDebug.h"

SINGLETON_DECLARE_INSTANCE( CGameGirl );

CGameGirl::CGameGirl()
{
	m_bMainLoop = true;
	m_bResume   = gxFalse;

	m_bPause     = gxFalse;
	m_bSyoriochi = gxFalse;
	m_sStepFrm = 0;

	m_sTimer = 0;
	m_uGameCounter = 0;
	m_sFrameSkip = 0;

	m_uMemoryTotal   = 1;
	m_uMemoryMaximum = 1;
	m_uMemoryUse     = 1;

	m_TimeYear  = 0;
	m_TimeMonth = 0;
	m_TimeDay   = 0;
	m_TimeHour  = 0;
	m_TimeMin   = 0;
	m_TimeSec   = 0;
	m_TimeMSec  = 0;

	m_bResetButton   = gxFalse;
	m_bPadDeviceConfigMode = gxFalse;

	m_bInitializeCompleted = gxFalse;

	m_bWaitVSync = gxTrue;

	m_uGlobalIP = 0x00000000;
	m_uLocalIP  = 0x00000000;
	m_bOnLine   = gxFalse;

}


CGameGirl::~CGameGirl()
{


}


/*
void CGameGirl::Action()
{

	Init();

	while( IsExist() )
	{
	
		Main();
	}

	End();

}
*/


void CGameGirl::Init()
{
 	::Clock();

	m_uStartTime = m_TimeHour *60*60*1000 + m_TimeMin*60*1000 + m_TimeSec*1000 + m_TimeMSec;

	drawInit();
	soundInit();
	movieInit();
	inputInit();

	m_bInitializeCompleted = gxTrue;
}


void CGameGirl::Main()
{
	if( m_bResetButton )
	{
		//リセット
		m_bResetButton = gxFalse;
		::GameReset();
	}

	//while( m_bMainLoop )
	{
		gxBool bSkip = gxFalse;	

		gxDebug::GetInstance()->CheckPoint( 0 );

		::InitAction();

		inputMain();

		if( m_uGameCounter%(m_sFrameSkip +1 ) )
		{
			bSkip = gxTrue;
		}

		if( !m_bPause || m_sStepFrm == 0 )
		{
			gxDebug::GetInstance()->Draw();

			gameMain();

			movieMain();

			gxDebug::GetInstance()->CheckPoint( 1 );

			if( !bSkip ) drawMain();

			gxDebug::GetInstance()->CheckPoint( 2 );

			soundMain();
		}

		if( m_sStepFrm < StepRepeatFrm ) m_sStepFrm ++;

		vsyncWait();

		gxDebug::GetInstance()->CheckEnd();

		if( bSkip )
		{
			COrderManager::GetInstance()->Reset();
		}
		else
		{
			flip();
			COrderManager::GetInstance()->Reset();
		}

		if( m_bResume )
		{
			resume();
			m_bResume = gxFalse;
		}

	}

	m_bOnLine = network();

}


gxBool CGameGirl::network()
{
	//ネットワーク処理

	gxBool bOnlineReq = gxFalse;

	if( m_bConnenctNetwork )
	{
		m_bConnenctNetwork = gxFalse;
		bOnlineReq = gxTrue;
	}

	if(m_bOnLine || bOnlineReq )
	{
		if( ::NetWork() )
		{
			return gxTrue;
		}
	}

	return gxFalse;

}


void CGameGirl::End()
{
	gameEnd();

	drawEnd();
	soundEnd();
	movieEnd();
	inputEnd();

	gxDebug::DeleteInstance();
}


void CGameGirl::resume()
{

	::Resume();

}


gxBool CGameGirl::drawInit()
{
	CTexManager::GetInstance();
	COrderManager::GetInstance();
	CRender::GetInstance();

	return gxTrue;
}

gxBool CGameGirl::drawMain()
{

	CRender::GetInstance()->Action();

	::Render();

//	COrderManager::GetInstance()->Reset();

	return gxTrue;
}

gxBool CGameGirl::drawEnd()
{
	CTexManager::DeleteInstance();
	COrderManager::DeleteInstance();
	CRender::DeleteInstance();

	return gxTrue;
}


gxBool CGameGirl::soundInit()
{
	CSoundManager::GetInstance();
	return gxTrue;
}


gxBool CGameGirl::soundMain()
{
	if(m_bPause)
	{
		CSoundManager::GetInstance()->SetForceVolumeLevel( enMasterVolumeLow );
	}
	else
	{
		CSoundManager::GetInstance()->SetForceVolumeLevel( enMasterVolumeMiddle );
	}

	CSoundManager::GetInstance()->Action();
	CSoundManager::GetInstance()->Play();

	return gxTrue;
}

gxBool CGameGirl::soundEnd()
{
	CSoundManager::DeleteInstance();

	return gxTrue;
}


gxBool CGameGirl::movieInit()
{
	CMovieManager::GetInstance();
	return gxTrue;
}


gxBool CGameGirl::movieMain()
{
	CMovieManager::GetInstance()->Action();
	CMovieManager::GetInstance()->Draw();
	return gxTrue;
}

gxBool CGameGirl::movieEnd()
{
	CMovieManager::DeleteInstance();
	return gxTrue;
}


gxBool CGameGirl::inputInit()
{
	CPadManager::GetInstance();

	return gxTrue;
}

gxBool CGameGirl::inputMain()
{
	CPadManager::GetInstance()->Action();

	if( gxLib::Joy(0)->psh&BTN_SELECT && gxLib::Joy(0)->trg&BTN_START )
	{
		CGameGirl::GetInstance()->SetReset();
	}

	return gxTrue;
}

gxBool CGameGirl::inputEnd()
{
	CPadManager::DeleteInstance();

	return gxTrue;
}


gxBool CGameGirl::gameMain()
{
	if( CGameGirl::GetInstance()->IsPadConfigMode() )
	{
		return gxTrue;
	}


	gxBool bExist;

	bExist = ::GameMain();

	m_uGameCounter ++;

	if( !bExist ) m_bMainLoop = gxFalse;

	return bExist;
}


gxBool CGameGirl::gameEnd()
{

	::GameEnd();

	return gxTrue;
}


gxBool CGameGirl::vsyncWait()
{
	m_bSyoriochi = gxFalse;

	if( ::vSync( m_bWaitVSync ) )
	{
		m_bSyoriochi = gxTrue;
	}

	return gxTrue;
}


gxBool CGameGirl::flip()
{
	::Flip();
	return gxTrue;
}



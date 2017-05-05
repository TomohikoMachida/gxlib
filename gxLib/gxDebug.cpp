// -----------------------------------------------------------
//
// デバッグ用ルーチン色々
// （処理棒など）
// -----------------------------------------------------------

#include <gxLib.h>
#include "gx.h"
#include "gxOrderManager.h"
#include "gxTexManager.h"
#include "gxRender.h"
#include "gxPadManager.h"
#include "gxSoundManager.h"
#include "gxDebug.h"

SINGLETON_DECLARE_INSTANCE( gxDebug );

#ifdef GX_DEBUG
Sint32 gxDebug::m_DebugSwitch[8]={1,1,1,1,1,1,1,1};
#else
Sint32 gxDebug::m_DebugSwitch[8]={0,0,0,0,0,0,0,0};
#endif

gxBool gxDebug::m_bMasterDebugSwitch = gxFalse;

gxDebug::gxDebug()
{
	for(Sint32 ii=0;ii<8;ii++)
	{
		m_uTime[ii]  = 0;
		m_uOldTime[ii] = 0;
		m_fWorks[ii] = 0.f;
	}

	m_stInfo.drawCnt = 0;
	m_stInfo.start   = -1;

	m_sDebugNum = 0;
	m_sDebugCnt = 0;

	for( Sint32 ii=0; ii<enLogMax; ii++ )
	{
		m_pLineString[ii] = new gxChar[ enStringMaxSize ];
	}
}


gxDebug::~gxDebug()
{
	for( Sint32 ii=0; ii<enLogMax; ii++ )
	{
		SAFE_DELETES( m_pLineString[ii] );
	}

}


void gxDebug::SetDebugSwitch( gxBool bOn )
{
	m_bMasterDebugSwitch = bOn;
}


void gxDebug::CheckPoint(Sint32 n)
{

 	m_uTime[ n ] = gxLib::GetTime();
	if( m_stInfo.start == -1 )
	{
		m_stInfo.start = m_uTime[ n ];
	}

}


void gxDebug::CheckEnd()
{

/*
	m_fWorks[0] = 1.0f*(cl[1].LowPart - cl[0].LowPart) / (freq.LowPart / 60);	//Action
	m_fWorks[1] = 1.0f*(cl[2].LowPart - cl[0].LowPart) / (freq.LowPart / 60);	//Action
	m_fWorks[2] = 1.0f*(cl[3].LowPart - cl[0].LowPart) / (freq.LowPart / 60);	//Action
	m_fWorks[3] = 1.0f*(cl[4].LowPart - cl[0].LowPart) / (freq.LowPart / 60);	//Action
	m_fWorks[4] = 1.0f*(cl[5].LowPart - cl[0].LowPart) / (freq.LowPart / 60);	//Action
*/

	m_fWorks[0] = ( m_uTime[1] - m_uTime[0] );// / (freq / 60);	//Movie
	m_fWorks[1] = ( m_uTime[2] - m_uTime[0] );// / (freq / 60);	//Movie
	m_fWorks[2] = ( m_uTime[3] - m_uTime[0] );// / (freq/60);	//Draw
	m_fWorks[3] = ( m_uTime[4] - m_uTime[0] );// / (freq/60);	//Sound
	m_fWorks[4] = ( m_uTime[5] - m_uTime[0] );// / (freq/60);	//vSync

	m_stInfo.OrderNum    = COrderManager::GetInstance()->GetOrderNum();
	m_stInfo.SubOrderNum = COrderManager::GetInstance()->GetSubOrderNum();
	m_stInfo.vtx_max     = CRender::GetInstance()->GetVertexNum();
	m_stInfo.idx_max     = CRender::GetInstance()->GetIndexNum();


	Uint32 now = gxLib::GetTime();

	m_stInfo.drawCnt ++;

	if( now >= m_stInfo.start + 1000 )
	{
		m_stInfo.fps     = m_stInfo.drawCnt;
		m_stInfo.start   = now;
		m_stInfo.drawCnt = 0;
	}


}


#define KB(n) ((n)>>10)
#define MB(n) (((n)>>10)>>10)

void gxDebug::Draw()
{
#ifdef GX_MASTER
	return;
#endif

	if( !m_bMasterDebugSwitch ) return;

	drawCircleRader();

	drawConsole();

	Sint32 ax,ay,az;

	ax = 0;
	ay = 0;
	az = PRIORITY_MAX;

	gxLib::DrawBox( ax , ay , ax + 128 , ay + 100 , az , gxTrue , ATR_DFLT , 0x80000080 );

	gxLib::Printf( ax+8 , ay + 12*0+8 , az , ATR_DFLT , 0xffffffff , "fps %.2f" , m_stInfo.fps );
	gxLib::Printf( ax+8 , ay + 12*1+8 , az , ATR_DFLT , 0xffffffff , "Order %d" , m_stInfo.OrderNum + m_stInfo.SubOrderNum  );
	gxLib::Printf( ax+8 , ay + 12*2+8 , az , ATR_DFLT , 0xffffffff , "Sub   %d (%d%%)" , m_stInfo.SubOrderNum  , 100*(m_stInfo.SubOrderNum+1) / (m_stInfo.OrderNum + m_stInfo.SubOrderNum+1) );
	gxLib::Printf( ax+8 , ay + 12*3+8 , az , ATR_DFLT , 0xffffffff , "vtx   %d" , m_stInfo.vtx_max );
	gxLib::Printf( ax+8 , ay + 12*4+8 , az , ATR_DFLT , 0xffffffff , "idx   %d" , m_stInfo.idx_max );

	Uint32 uNow ,uTotal ,uMax;
	CGameGirl::GetInstance()->GetMemoryRemain( &uNow , &uTotal , &uMax );
	gxLib::Printf( ax+8 , ay + 12*5+8 , az , ATR_DFLT , 0xffffffff , "RAM   %dMB" , MB(uNow) );
	gxLib::Printf( ax+8 , ay + 12*6+8 , az , ATR_DFLT , 0xffffffff , "MAX   %d/%dMB" , MB(uMax) , MB(uTotal) );

	Sint32 num = 0;
	for( Sint32 ii=0; ii<MAX_SOUND_NUM; ii++ )
	{
		if( CSoundManager::GetInstance()->GetPlayInfo( ii )->bPlayNow )
		{
			gxLib::Printf( WINDOW_W , ay + 12*num , az , ATR_STR_RIGHT , 0xffffffff , "snd %04x/%d/%.2f (%03d)" ,
				CSoundManager::GetInstance()->GetPlayInfo( ii )->uStatus,
				CSoundManager::GetInstance()->GetPlayInfo( ii )->bPlayNow,
				CSoundManager::GetInstance()->GetPlayInfo( ii )->fVolume,
				ii
				);
				num ++;
		}
	}

}


void gxDebug::drawBar( Sint32 n , Float32 ratio )
{
	Sint32 ax,ay,max = 128;

	ax = 0;
	ay = 0;

	Sint32 w = 1;
	w = max * ratio;

	Uint32 argbTbl[]={
		0xff0000ff,
		0xff00ff00,
		0xff00ffff,
		0xffff0000,
		0xffff00ff,
		0xffffff00,
		0xffffffff,
	};

	gxLib::DrawBox( ax,ay, ax+w ,ay+8, PRIORITY_MAX, gxTrue , ATR_DFLT , argbTbl[n] );

//#ifdef DEBUG_ON
//	gxLib::DrawBox( 0,0, WINDOW_W*m_fWorks[3]/100.f ,8, PRIORITY_MAX, gxTrue , ATR_DFLT , 0xf000f0f0 );
//	gxLib::DrawBox( 0,0, WINDOW_W*m_fWorks[2]/100.f ,8, PRIORITY_MAX, gxTrue , ATR_DFLT , 0xf000f0c0 );
//	gxLib::DrawBox( 0,0,  WINDOW_W*m_fWorks[1]/100.f,8, PRIORITY_MAX, gxTrue , ATR_DFLT , 0xf0808000 );
//	gxLib::DrawBox( 0,0,  WINDOW_W*m_fWorks[0]/100.f,8, PRIORITY_MAX, gxTrue , ATR_DFLT , 0xf0f00000 );	//赤げーじ
//
//	Uint32 uUse , uMax , uTotal;
//
//	gxLib::GetMemoryRemain( &uUse , &uTotal, &uMax );
//
////	gxLib::DrawBox( 0,8 , 128,12, PRIORITY_MAX, gxTrue , ATR_DFLT , 0xA0010101 );
//	gxLib::Printf ( 0,0 , PRIORITY_MAX ,ATR_DFLT ,ARGB_DFLT , "%dMB / %dMB (%dMB) %.2f%%" , uUse/1024 , uTotal/1024 , uMax/1024 , 100.f*uUse/uTotal);
//
//#endif
}



void gxDebug::LogDisp( gxChar *pFormat , ... )
{
#if 0	//_GX_RELEASE_

#else
	gxChar _buf[ enStringMaxSize ];
	va_list app;

	if( pFormat == NULL ) return;

	va_start( app, pFormat );

	if( vsprintf( _buf , pFormat, app ) >= enStringMaxSize )
	{
		va_end( app );
		return;
	}

	va_end( app );

	sprintf( m_pLineString[ m_sDebugNum%enLogMax ] , _buf );
	m_sDebugNum ++;

#endif
}

void gxDebug::drawCircleRader()
{
	//ファイル読み込みで止まっていないときに動作

	static Float32 m_fRotArray[360];
	static Sint32  m_sRotationCnt = 0;
	static Float32 m_fRotation = 0.0f;

	m_fRotArray[ m_sRotationCnt%360 ] = m_fRotation;

	m_fRotation += 3.2f;
	m_sRotationCnt += 1;

	Sint32 ax,ay,ax1,ay1,ax2,ay2;
	ax = 32;
	ay = 32;

	Sint32 max = 64;

	for( Sint32 ii=0; ii<max;ii++ )
	{
		if( ii >= m_sRotationCnt ) continue;

		Sint32 n1 = ( m_sRotationCnt + 360 - 1 - ii )%360;
		Sint32 n2 = ( m_sRotationCnt + 360 - 2 - ii )%360;

		ax1 = ax+gxLib::Cos( m_fRotArray[n1] )*32;
		ay1 = ay+gxLib::Sin( m_fRotArray[n1] )*32;

		ax2 = ax+gxLib::Cos( m_fRotArray[n2] )*32;
		ay2 = ay+gxLib::Sin( m_fRotArray[n2] )*32;

		Sint32 alpha = 255 * (max-1-ii) / (max-1);
/*
		gxLib::DrawLine( ax  , ax  , ax1 , ay1 , 120 , ATR_DFLT , ARGB( alpha , 0x00 , 0xff , 0x00 ) );
		gxLib::DrawLine( ax  , ax  , ax2 , ay2 , 120 , ATR_DFLT , ARGB( alpha , 0x00 , 0xff , 0x00 ) );
		gxLib::DrawLine( ax1 , ay1 , ax2 , ay2 , 120 , ATR_DFLT , ARGB( alpha , 0x00 , 0xff , 0x00 ) );
*/
		gxLib::DrawTriangle( ax  , ax  , ax1 , ay1 , ax2 , ay2 , 120 , gxTrue , ATR_DFLT , ARGB( alpha , 0x00 , 0xff , 0x00 ) );
	}
}

void gxDebug::drawConsole()
{
	Sint32 ax,ay,az;

	ax = 16;
	ay = WINDOW_H - (enLogMax*16+16*3);
	az = PRIORITY_MAX;

	Sint32 max = enLogMax;

	Sint32 yy = m_sDebugNum;
	if( yy >= enLogMax ) yy = enLogMax;

	Sint32 y1 ,y2;
	y1 = 0;
	y2 = enLogMax*16+16*2;
	gxLib::DrawBox( 0,ay - 16  , WINDOW_W , ay-1   , PRIORITY_MAX, gxTrue , ATR_DFLT , 0x80008080 );
	gxLib::DrawBox( 0,ay + y1  , WINDOW_W , ay + y2, PRIORITY_MAX, gxTrue , ATR_DFLT , 0x80000080 );
	gxLib::DrawBox( 0,ay + y2, WINDOW_W , ay + y2 +16 , PRIORITY_MAX, gxTrue , ATR_DFLT , 0x80008080 );

	ay += yy*16;

	for( Sint32 ii=0; ii<max;ii++ )
	{
		if( ii >= m_sDebugNum ) continue;

		Sint32 n = ( m_sDebugNum + enLogMax - 1 - ii )%enLogMax;

		gxLib::Printf( ax , ay - 16*ii , PRIORITY_MAX , ATR_DFLT , ARGB_DFLT , "%s", m_pLineString[n] );
	}



}



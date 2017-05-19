#include <gxLib.h>
#include "CLogicAStar.h"

const static int MAP_X = 40;
const static int MAP_Y = 60;

Uint8 *_pMapData = NULL;

void makeMaze();

void AStarTest()
{
	//経路探索テスト

	static CAStarLogic *m_pLogic = NULL;
	static gxBool m_bMiniMapMode = gxTrue;
	static gxPoint m_Start= { 19 , 45 };
	static gxPoint m_Goal = { 30 , 19 };

	static gxPoint add    = { 0 , 0 };
	static gxPoint mouse  = { 0 , 0 };
	static gxPoint offset = { 0 , 0 };

	if( m_pLogic == NULL )
	{
		m_pLogic = new CAStarLogic();			//leak

		_pMapData = new Uint8[ MAP_X * MAP_Y ];	//leak
		makeMaze();

		m_pLogic->SetMap( MAP_X, MAP_Y, _pMapData );
	}

	if( gxLib::Joy(0)->trg&MOUSE_M )
	{
		m_bMiniMapMode = !m_bMiniMapMode;
	}

	Sint32 tipW = 8;

	if( m_bMiniMapMode )
	{
		Sint32 ox = ( WINDOW_W - (tipW*MAP_X) ) /2;
		Sint32 oy = ( WINDOW_H - (tipW*MAP_Y) ) /2;

		if( gxLib::Joy(0)->psh&MOUSE_L )
		{
			m_Start.x = gxLib::Joy(0)->mx-ox;
			m_Start.y = gxLib::Joy(0)->my-oy;

			m_Start.x /= 8;
			m_Start.y /= 8;

		}

		if( gxLib::Joy(0)->psh&MOUSE_R )
		{
			m_Goal.x = gxLib::Joy(0)->mx-ox;
			m_Goal.y = gxLib::Joy(0)->my-oy;
			m_Goal.x /= 8;
			m_Goal.y /= 8;
		}
	}
	else
	{
		if (gxLib::Joy(0)->trg&MOUSE_L)
		{
			mouse.x = gxLib::Joy(0)->mx;
			mouse.y = gxLib::Joy(0)->my;
		}
		else if (gxLib::Joy(0)->psh&MOUSE_L)
		{
			add.x = gxLib::Joy(0)->mx - mouse.x;
			add.y = gxLib::Joy(0)->my - mouse.y;

			mouse.x = gxLib::Joy(0)->mx;
			mouse.y = gxLib::Joy(0)->my;

			offset.x += add.x;
			offset.y += add.y;
		}
		else
		{
			add.x += ( 0 - add.x )/10.0f;
			add.y += ( 0 - add.y )/10.0f;

			offset.x += add.x;
			offset.y += add.y;
		}
	}

	if( ABS(gxLib::Joy(0)->whl) >= 0.5f )
	{
		//新規迷路作成
		makeMaze();
		m_pLogic->SetMap( MAP_X, MAP_Y, _pMapData );
	}

	m_pLogic->SetStart( m_Start.x , m_Start.y );
	m_pLogic->SetGoal ( m_Goal.x  , m_Goal.y  );
	m_pLogic->SearchRout();

//	gxLib::DrawBox(0, 0, WINDOW_W, WINDOW_H, 210, gxTrue, ATR_DFLT , 0xc0010101);

	if( m_bMiniMapMode )
	{
		m_pLogic->DrawMiniMap( 8 );
	}
	else
	{
		m_pLogic->DrawInfo( 64 , offset.x , offset.y );
	}
}


void makeMaze()
{
	// 準備
	Sint32 w = MAP_X;
	Sint32 h = MAP_Y;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (y == 0 || y == h -1 || x == 0 || x == w - 1)
			{
				_pMapData[y*MAP_X+x] = 0xff; // 外周
			}
			else if (y % 2 == 0 && x % 2 == 0)
			{
				_pMapData[y*MAP_X+x] = 0xff; // [偶数][偶数]
			}
			else
			{
				_pMapData[y*MAP_X+x] = 0; // その他
			}
		}
	}


	// 壁位置
	for (int y = 2; y < h - 2; y += 2)
	{
		for (int x = 2; x < w - 2; x += 2)
		{
			int n;
			if (y == 2)
			{
				// 一番上の段
				if (_pMapData[y*MAP_X+x-1] == 1)
				{
					n = gxLib::Rand()%2;//rand(0, 2);
				}
				else
				{
					n = gxLib::Rand()%3;//rand(0, 3);
				}

			}
			else
			{
				if (_pMapData[y*MAP_X + x-1] == 0xff)
				{
					n = 1 + gxLib::Rand()%2;//1, 2);
				}
				else
				{
					n = 1 + gxLib::Rand()%3;//rand(1, 3);
				}
			}

			switch (n) {
			case 0: // 上
				_pMapData[(y - 1)*MAP_X + x] = 0xff;
				break;
			case 1: // 右
				_pMapData[y*MAP_X + x + 1] = 0xff;
				break;
			case 2: // 下
				_pMapData[(y + 1)*MAP_X+x] = 0xff;
				break;
			default: // 左
				_pMapData[y*MAP_X + x - 1] = 0xff;
				break;
			}
		}
	}

}


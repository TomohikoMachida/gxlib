/**
-------------------------------------------------------------
 *
 *	CAStarLogic
 *
 *  written by ragi.
 *
 *  2016.06.28
-------------------------------------------------------------
**/

class CAStarLogic
{
public:

	enum {
		//�T����������
		enSearchType4Way,
		enSearchType8Way,	//<-- default
	};

	typedef struct StCell
	{
		//�e�Z���̏�ԊǗ�
		Sint32 id;
		Sint32 x,y,type;
		Sint8 stat;
		float j_cost;
		float h_cost;
		float score;
		StCell *parent;

		StCell()
		{
			id = 0;
			type = 0;
			x = y = 0;

			stat   = enStatNone;
			h_cost = 0;
			j_cost = 0;
			score  = 0;
			parent = NULL;
		}

		void Set( Sint32 _id , Sint32 _x , Sint32 _y , Sint32 _type )
		{
			id    = _id;
			x     = _x;
			y     = _y;
			type  = _type;
		}

		void clearStatus()
		{
			stat   = enStatNone;
			h_cost = 0;
			j_cost = 0;
			score  = 0;
			parent = NULL;
		}

	} StCell;

	CAStarLogic()
	{
		m_pMapData   = NULL;
		m_sMapWidth  = 1;
		m_sMapHeight = 1;

		m_TypeSearh = enSearchType8Way;

		m_Start.x = 0;
		m_Start.y = 0;

		m_Goal = m_Start;

		m_sBaseNodeCnt = 0;
		m_sAnswerNum = 0;
	}

	~CAStarLogic()
	{

	}

	void SetMap( Sint32 w , Sint32 h, Uint8 *pData )
	{
		//�O������MAP�f�[�^���Z�b�g����
		m_sMapWidth  = w;
		m_sMapHeight = h;

		resetMapData( w*h , pData );
	}

	void SetStart( Sint32 x , Sint32 y )
	{
		//�X�^�[�g�n�_��XY�Ŏw�肷��

		if( x < 0 ) x = 0;
		if( x >= m_sMapWidth )  x = m_sMapWidth-1;
		if( y < 0 ) y = 0;
		if( y >= m_sMapHeight ) y = m_sMapHeight-1;

		m_Start.x = x;
		m_Start.y = y;
	}

	void SetGoal( Sint32 x , Sint32 y )
	{
		//�S�[���n�_��XY�Ŏw�肷��

		if( x < 0 ) x = 0;
		if( x >= m_sMapWidth )  x = m_sMapWidth-1;
		if( y < 0 ) y = 0;
		if( y >= m_sMapHeight ) y = m_sMapHeight-1;

		m_Goal.x = x;
		m_Goal.y = y;
	}

	StCell* Get( Sint32 x , Sint32 y)
	{
		//XY����Z�����擾����

		Sint32 n = y*m_sMapWidth + x;

		if( x < 0 || x >= m_sMapWidth  ) return NULL;
		if( y < 0 || y >= m_sMapHeight ) return NULL;

		if( n < 0 || n >=m_sMapWidth*m_sMapHeight )
		{
			return NULL;
		}

		return &m_pMapData[n];
	}

	void DrawInfo( Sint32 width , Sint32 ox , Sint32 oy )
	{
		//�f�o�b�O�`��

		Sint32 w = m_sMapWidth;
		Sint32 h = m_sMapHeight;
		Sint32 z = 100;

		Sint32 tw, th;
		tw = width;
		th = width;

		Sint32 ax, ay;

		for( Sint32 y=0;y<h;y++)
		{
			for( Sint32 x=0;x<w;x++)
			{
				gxBool bFill = gxFalse;

				StCell* pData = Get(x,y);

				if( pData->type ) bFill = gxTrue;

				ax = x*tw;
				ay = y*th;

				ax += ox;
				ay += oy;

				if ( ax < -tw )			continue;
				if ( ay < -tw )			continue;
				if ( ax > WINDOW_W )	continue;
				if ( ay > WINDOW_H )	continue;

				gxLib::DrawBox( ax , ay , ax+tw , ay+th , z , bFill , ATR_DFLT , 0xffff0000 );
				gxLib::Printf( ax,ay+12*0,z + 1 , 0 , 0xffffffff , "c=%.2f"  , pData->j_cost );
				gxLib::Printf( ax,ay+12*1,z + 1 , 0 , 0xffffffff , "h=%.2f"  , pData->h_cost );
				gxLib::Printf( ax,ay+12*2,z + 1 , 0 , 0xffffffff , "s=%.2f"  , pData->score );
				gxLib::Printf( ax,ay+12*3,z + 1 , 0 , 0xffffffff , "stat=%d" , pData->stat );

				if (pData->stat == enStatClose)
				{
					gxLib::DrawBox( ax, ay, ax + tw, ay + th, z, gxTrue, ATR_DFLT, 0x80808080 );
				}
				else if (pData->stat == enStatOpen)
				{
					gxLib::DrawBox( ax, ay, ax + tw, ay + th, z, gxTrue, ATR_DFLT, 0x80f08080 );
				}

				for ( Sint32 ii = 0; ii < GetAnswerNum(); ii++ )
				{
					if ( GetAnswerCell(ii)->x == x && GetAnswerCell(ii)->y == y )
					{
						gxLib::DrawBox( ax+8, ay+8, ax + tw-16, ay + th-16, z, gxTrue, ATR_DFLT, 0x80808000);
					}
				}
			}
		}
	}

	void SearchRout()
	{
		search();
	}

	Sint32 GetAnswerNum()
	{
		return m_sAnswerNum;
	}

	StCell *GetAnswerCell( Sint32 n )
	{
		Sint32 m = m_sAnswerNum - n-1;

		if( m < 0 || m>=m_sAnswerNum ) m = 0;

		StCell* pData = Get( m_Goal.x , m_Goal.y );

		for(Sint32 ii=0;ii<m;ii++)
		{
			pData = Get( pData->parent->x , pData->parent->y );
		}

		return pData;
	}

	void DrawMiniMap( Sint32 cellWidth )
	{
		//�f�o�b�O�~�j�}�b�v�̕\��

		Sint32 ox,oy;

		Sint32 w = m_sMapWidth;
		Sint32 h = m_sMapHeight;
		Sint32 width = cellWidth;
		Sint32 alp = 0xff;
		Sint32 z = 110;

		Uint32 argbTbl[]={
			0x800000ff,
			0x8000ff00,
			0x8000ffff,
			0x80ff0000,
			0x80ff00ff,
			0x80ffff00,
			0x80ffffff,
		};

		ox = ( WINDOW_W - (width*w) ) / 2;
		oy = ( WINDOW_H - (width*h) ) / 2;

		gxLib::Printf( 32,32+16*0,z+3,0,0xffffffff,"START = %d,%d", (Sint32)m_Start.x , (Sint32)m_Start.y );
		gxLib::Printf( 32,32+16*1,z+3,0,0xffffffff,"GOAL  = %d,%d", (Sint32)m_Goal .x , (Sint32)m_Goal.y  );

		for( Sint32 y=0; y<h; y++ )
		{
			for( Sint32 x=0; x<w; x++ )
			{
				gxBool bFill  = gxFalse;
				StCell* pData = Get(x,y);

				if( pData->type )
				{
					bFill = gxTrue;
				}
				else
				{
					continue;
				}

				gxLib::DrawBox( ox + x*width , oy + y*width, ox + x*width+width-1 , oy + y*width+width-1 , z , bFill , ATR_DFLT , argbTbl[ pData->type%7 ] );
			}
		}

		int num = GetAnswerNum();

		int ax, ay;

		static int timer = 0;
		timer++;

		for (int ii = 0; ii<num; ii++)
		{
			CAStarLogic::StCell *pCell = GetAnswerCell(ii);
			{
				if (pCell)
				{
					ax = pCell->x;
					ay = pCell->y;

					Sint32 alp = 32;

					alp = 64 + 192 * ((timer + (num-1-ii)) % 16+1) / 16 ;
					gxLib::DrawBox(ox + ax*width, oy + ay*width, ox + ax*width + width, oy + ay*width + width, z + 1, gxTrue, ATR_DFLT, SET_ALPHA(alp, 0xff0000));
					gxLib::DrawBox( ox + ax*width , oy+ay*width, ox+ax*width+width , oy+ay*width+width , z+1 , gxFalse , ATR_DFLT , SET_ALPHA( 0xff , 0xffff00 ) );
				}
			}
		}
	}

private:

	enum {
		enStatNone,
		enStatOpen,
		enStatClose
	};

	void resetMapData( Sint32 num , Uint8 *pData )
	{
		//�}�b�v�f�[�^�����Z�b�g����

		if( m_pMapData ) SAFE_DELETE( m_pMapData );

		m_pMapData = new StCell[ num ];

		for( Sint32 ii=0;ii<num; ii++ )
		{
			m_pMapData[ii].Set( ii , ii%m_sMapWidth,ii/m_sMapWidth, pData[ii] );
		}
	}

	void resetStatus()
	{
		//�Z���̏�Ԃ��N���A����

		Sint32 num = m_sMapWidth*m_sMapHeight;

		for( Sint32 ii=0;ii<num; ii++)
		{
			m_pMapData[ii].clearStatus();
		}
	}
	
	gxBool search()
	{
		//�o�H��T������

		m_sBaseNodeCnt = 0;
		m_sAnswerNum = 0;
		resetStatus();

		m_pMapTemp = new StCell*[ m_sMapWidth*m_sMapHeight ];

		StCell* pData = Get(m_Goal.x , m_Goal.y);

		if( searchRout( m_Start.x , m_Start.y , m_Goal.x , m_Goal.y ) )
		{
			while( gxTrue )
			{
				m_sAnswerNum ++;

				if( ( pData->parent == NULL ) )
				{
					//�X�^�[�g�܂Ŗ߂ꂽ
					break;
				}

				pData = Get( pData->parent->x , pData->parent->y );
			}
		}

		delete[] m_pMapTemp;

		if( m_sAnswerNum > 0 ) return gxTrue;

		return gxFalse;
	}

	gxBool searchRout( Sint32 x1 , Sint32 y1 , Sint32 x2 ,Sint32 y2 )
	{
		//�o�H�T��

		Sint32 cost = 0;

		open1( x1,y1,0 );

		baseNode( Get(x1,y1) ,0.0f );

		StCell *pMap;

		while( gxTrue )
		{
			pMap = getMinimumCostCell();

			if( pMap == NULL )
			{
				break;
			}

			if( baseNode( pMap , pMap->j_cost+1 ) )
			{
				return gxTrue;
			}
		}

		//������Ȃ�����

		return gxFalse;
	}

	const float addCost = 0.41421356237f;

	gxBool baseNode( StCell *pMap , Float32 cost )
	{
		//������I�[�v�����Ď��g���N���[�Y����

		Sint32 x,y;

		x = pMap->x;
		y = pMap->y;

		if( x == m_Goal.x && y == m_Goal.y ) return gxTrue;

		if (m_TypeSearh == enSearchType4Way)
		{
			//4�����T��
			addBaseNode(open1(x - 0, y - 1, cost, pMap));

			addBaseNode(open1(x - 1, y - 0, cost, pMap));
			addBaseNode(open1(x + 1, y - 0, cost, pMap));

			addBaseNode(open1(x - 0, y + 1, cost, pMap));
		}
		else
		{
			//8�����T��
			addBaseNode(open1(x - 1, y - 1, cost + addCost , pMap));
			addBaseNode(open1(x - 0, y - 1, cost           , pMap));
			addBaseNode(open1(x + 1, y - 1, cost + addCost , pMap));

			addBaseNode(open1(x - 1, y - 0, cost   , pMap));
			//addBaseNode(open1(x - 0, y - 0, cost , pMap));
			addBaseNode(open1(x + 1, y - 0, cost   , pMap));

			addBaseNode(open1(x - 1, y + 1, cost + addCost, pMap));
			addBaseNode(open1(x - 0, y + 1, cost          , pMap));
			addBaseNode(open1(x + 1, y + 1, cost + addCost, pMap));
		}

		Get(x,y)->stat= enStatClose;

		return gxFalse;
	}

	void addBaseNode( StCell *pBase )
	{
		//��{�m�[�h��ǉ�����

		if( pBase == NULL ) return;

		m_pMapTemp[ m_sBaseNodeCnt ] = pBase;
		m_sBaseNodeCnt ++;
	}

	StCell *getMinimumCostCell()
	{
		//���͂̃Z���ōł��R�X�g���Ⴂ�̂͂ǂꂩ�H
		float minScore = -1;
		Sint32 tgt = -1;

		for( Sint32 ii=0; ii<m_sBaseNodeCnt; ii++ )
		{
			if( m_pMapTemp[ ii ]->stat ==  enStatClose ) continue;
			if( m_pMapTemp[ ii ]->score <= minScore || tgt == -1 )
			{
				if( m_pMapTemp[ ii ]->score == minScore && tgt != -1 )
				{
					//�R�R�������d�v�F�F�X�R�A�������������ꍇ�Ɏ��R�X�g���Ŕ��f����Ƃ���
					if( m_pMapTemp[ ii ]->j_cost > m_pMapTemp[ tgt ]->j_cost ) continue;
				}

				minScore = m_pMapTemp[ ii ]->score;
				tgt = ii;
			}
		}

		if( tgt == -1 ) return NULL;

		return m_pMapTemp[ tgt ];
	}


	StCell *open1( Sint32 x , Sint32 y , Float32 cost , StCell *pParent = NULL)
	{
		//�V�����Z�����J��

		StCell *pMap = Get(x,y);

		if( pMap == NULL )				return NULL;	//�����W�O
		if( pMap->stat != enStatNone )	return NULL;	//���łɌv�Z�ς�
		if( pMap->type == 0xFF )		return NULL;	//��

		float fDist = sqrt( (m_Goal.x - x)*(m_Goal.x - x) + (m_Goal.y - y)*(m_Goal.y - y));

		pMap->j_cost = cost + pMap->type;
		pMap->h_cost = fDist;
		pMap->score  = pMap->h_cost + pMap->j_cost;
		pMap->stat   = enStatOpen;

		if( pParent != NULL )
		{
			pMap->parent = pParent;
		}
		return pMap;
	}

	//�T�������Ǘ��p
	Sint8 m_TypeSearh;

	//�T���p�̃}�b�v�f�[�^
	Sint32 m_sMapWidth;
	Sint32 m_sMapHeight;
	StCell *m_pMapData;

	//�X�^�[�g�A�S�[���n�_
	gxPoint m_Start;
	gxPoint m_Goal;

	//��{�m�[�h�Ǘ��p
	Sint32 m_sBaseNodeCnt;
	StCell **m_pMapTemp;

	//�񓚗p�o�R�|�C���g��
	Sint32 m_sAnswerNum;

};



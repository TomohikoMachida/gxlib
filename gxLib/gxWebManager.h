#ifndef _gxWebManager_H_
#define _gxWebManager_H_

class gxWebManager
{
public:
	enum {
		enErrorFileNotFound,
		enErrorAccessDenied,
		enErrorFileSizeOver,
	};
	
	enum {
		enDataBufferMax = 32,
	};

	gxWebManager()
	{
		m_sReqMinIndex = 0;
		m_sReqMaxIndex = 0;

		for(Sint32 ii=0; ii<enDataBufferMax; ii++ )
		{
			m_pWebData[ii]->pData = NULL;
		}
	}

	~gxWebManager()
	{
		for(Sint32 ii=0; ii<enDataBufferMax; ii++ )
		{
			if( m_pWebData[ii]->pData )
			{
				SAFE_DELETE( m_pWebData[ii]->pData );
			}
		}
	}

	Sint32 Open( gxChar* pURL , gxChar* pUser , gxChar* pPassword );
	void Read();
	gxBool IsReadEnd();
	gxBool IsError();
	Uint8* GetDataImage();

	typedef struct StWebData {

		StWebData()
		{
			pData = NULL;
			bComplete = gxFalse;
			uSize = 0;
			url[0] = 0x00;
			user[0] = 0x00;
			pass[0] = 0x00;
		}

		gxChar url[256];
		gxChar user[256];
		gxChar pass[256];
		Uint8  *pData;
		Sint32 bComplete;
		Uint32 uSize;

	} StWebData;


	StWebData *GetWebData( Sint32 index );

	gxBool IsLoadComplete( Sint32 index )
	{
		Sint32 n = index%enDataBufferMax;
		
		return m_pWebData[n]->bComplete;
	}

	void Action();

	Sint32 GetMinIndex()
	{
		return m_sReqMinIndex;
	}
	
	Sint32 GetMaxIndex()
	{
		return m_sReqMaxIndex;
	}

private:

	Sint32 m_sReqMinIndex;
	Sint32 m_sReqMaxIndex;

	StWebData *m_pWebData[ enDataBufferMax ];
	gxBool m_bReadComplete;
	gxBool m_bError;
	Uint8* m_pFileImage;
};


#endif

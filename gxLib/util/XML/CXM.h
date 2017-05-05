#ifndef _XMLLOADER_
#define _XMLLOADER_

#include "tinyxml2.h"


class CXML
{

public:

	class Node
	{
	public:

		Node()
		{
			m_pElement = NULL;

			m_sBrotherNum = 0;
			m_pReturnStaticNode = NULL;

			m_sChildNum = 0;
			m_pChildArray = NULL;
		}

		~Node()
		{
			SAFE_DELETES( m_pChildArray );
			SAFE_DELETES( m_pReturnStaticNode );
		}

		Node* makeTree( gxChar *pName = NULL );

		Node* Get( gxChar* pName );

		gxChar *Name()
		{
			gxChar *p;

			if(m_pElement)
			{
				p = (gxChar*)m_pElement->Name();
				if( p ) return p;
			}
			
			return "No Name";
		}

		gxChar *Attribute( gxChar *pName )
		{
			gxChar *p;

			if(m_pElement)
			{
				p = (gxChar*)m_pElement->Attribute(pName);
				if( p ) return p;
			}
			
			return "No Attribute";
		}

		gxChar *Data()
		{
			gxChar *p;

			if(m_pElement)
			{
				p = (gxChar*)m_pElement->GetText();
				if( p ) return p;
			}
			
			return "No Data";
		}

		void SetChildren( Node* pChildren , Sint32 num )
		{
			SAFE_DELETE( m_pChildArray );

			m_pChildArray = pChildren;
			m_sChildNum = num;
		}

		Sint32 GetChildNum()
		{
			return m_sChildNum;
		}

		Node* GetChild( Sint32 n)
		{
			return &m_pChildArray[n];
		}


		Sint32 GetBrotherNum()
		{
			return m_sBrotherNum;
		}

		void SetBrotherNum( Sint32 num )
		{
			m_sBrotherNum = num;
		}

		Node* GetBrother( Sint32 n )
		{
			return &m_pReturnStaticNode[n];
		}

		void SetElement( tinyxml2::XMLElement *pElement )
		{
			if( pElement != NULL )
			{
				m_pElement = pElement;
			}
		}

	private:

		tinyxml2::XMLElement* searchChild( tinyxml2::XMLElement *element , gxChar *pString );

		Node* analyseBrother( tinyxml2::XMLElement *element , Sint32 *pNum , Sint32 *pChiNum = NULL );
		Node* analyseChild( tinyxml2::XMLElement *element );

		tinyxml2::XMLElement *m_pElement;

		Node *m_pReturnStaticNode;
		Node *m_pChildArray;

		Sint32 m_sBrotherNum;
		Sint32 m_sChildNum;
	};


	CXML()
	{
		m_pXML = NULL;
		m_XMLFileSize = 0;

		m_pRoot = NULL;
	}
	
	~CXML()
	{
		SAFE_DELETE( m_pRoot );
	}

	gxBool LoadFile( gxChar *pFileName );
	gxBool ReadFile( gxChar *pString , Uint32 uSize = 0 );

	Node* AdjustRoot( gxChar *pString = NULL );

	static gxBool IsSame( gxChar *str1 , gxChar *str2 );
	static tinyxml2::XMLElement* searchChild( tinyxml2::XMLElement *element , gxChar *pString );

private:

	tinyxml2::XMLElement* searchRout( gxChar *pString );

	tinyxml2::XMLDocument *m_pXML;
	Uint32 m_XMLFileSize;

	Node *m_pRoot;
};

#endif


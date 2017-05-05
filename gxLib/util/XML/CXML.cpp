
#define WIN32_LEAN_AND_MEAN
#include <gxLib.h>
#include "CXMLLoader.h"

#define _DEBUG_LOG_DISP

gxBool CXML::LoadFile( gxChar *pFileName )
{
	Uint8 *pData;
	pData = gxLib::LoadFile( pFileName , &m_XMLFileSize );

	if( pData == NULL )
	{
		return gxFalse;
	}

	ReadFile( (gxChar*)pData ,m_XMLFileSize );

	delete[] pData;

	return gxTrue;
}

gxBool CXML::ReadFile( gxChar *pString , Uint32 uSize )
{
	SAFE_DELETE( m_pXML );

	m_pXML = new tinyxml2::XMLDocument();
	m_pXML->Parse( (const char*)pString , uSize );

	m_XMLFileSize = strlen( (const char*)pString );

	return gxTrue;
}


CXML::Node* CXML::AdjustRoot( gxChar *pString )
{
	tinyxml2::XMLElement *pElem;
	CXML::Node *ret;

	if( pString )
	{
		pElem = searchRout( pString );
	}
	else
	{
		pElem = m_pXML->FirstChildElement();
	}

	if( pElem )
	{
		const char *pName = pElem->Name();

		SAFE_DELETE( m_pRoot );
		m_pRoot = new CXML::Node();
		m_pRoot->SetElement( pElem );
		ret = m_pRoot->makeTree( (gxChar*)pName );
	}

#ifdef _DEBUG_LOG_DISP
	gxLib::DebugLog("ROOT[%s]",m_pRoot->Name() );
#endif
	return ret;
}


tinyxml2::XMLElement* CXML::searchRout( gxChar *pString )
{
	tinyxml2::XMLElement *element;
	element = m_pXML->FirstChildElement( pString );

	if( element == NULL )
	{
		//routを探してそこから検索する
		element = m_pXML->FirstChildElement();

		if( element == NULL )
		{
			//routすらない
			return NULL;
		}
	}

	tinyxml2::XMLElement *child;
	child = searchChild( element , pString );

	if( child )
	{
#ifdef _DEBUG_LOG_DISP
//		gxLib::DebugLog("-[%s]",element->Name() );
#endif
		return child;
	}

	return element;
}

tinyxml2::XMLElement* CXML::searchChild( tinyxml2::XMLElement *element , gxChar *pString )
{
	if( element )
	{
#ifdef _DEBUG_LOG_DISP
//		gxLib::DebugLog("[%s]",element->Name() );
#endif
	}

	if( IsSame( (gxChar*)element->Name() , pString ) ) return element;

	tinyxml2::XMLElement *child;

	child = element->FirstChildElement();

	if( child )
	{
		child = searchChild( child , pString );
		if( child != NULL ) return child;
	}

	element = element->NextSiblingElement();

	if( element )
	{
		element = CXML::searchChild( element , pString );
		if( element != NULL ) return element;
	}

	return NULL;
}

gxBool CXML::IsSame( gxChar *str1 , gxChar *str2 )
{

	if( str1 == NULL || str2 == NULL ) return gxFalse;

	if( strcmp( str1 , str2 ) == 0 ) return gxTrue;

	return gxFalse;
}

CXML::Node* CXML::Node::makeTree( gxChar *pName )
{
	Sint32 broNum = 0;
	tinyxml2::XMLElement *element;

	m_sChildNum   = 0;
	m_sBrotherNum = 0;
	SAFE_DELETES( m_pReturnStaticNode );
	SAFE_DELETES( m_pChildArray );

	element = CXML::searchChild( m_pElement , pName );

	if( element )
	{
		m_pReturnStaticNode = analyseBrother( element , &m_sBrotherNum ,&m_sChildNum );
	}

	return m_pReturnStaticNode;
}


CXML::Node* CXML::Node::analyseBrother( tinyxml2::XMLElement *element , Sint32 *pNum , Sint32 *pChildNum )
{
	Sint32 broNum = 0;

	broNum ++;
	tinyxml2::XMLElement *bro = element;

	while( gxTrue )
	{
		bro = bro->NextSiblingElement();
		if( bro )	broNum ++;
		else break;
	}

	if( broNum == 0 ) return NULL;

	CXML::Node *p;
	p = new CXML::Node[ broNum ];

	tinyxml2::XMLElement *chi;
	Sint32 childNum = 0;

	for( Sint32 ii=0; ii<broNum; ii++ )
	{
		p[ii].SetElement( element );
		p[ii].SetBrotherNum( broNum );

		chi = element->FirstChildElement();

		if( chi )
		{
			Node *p2;
			p2 = analyseBrother( chi , &childNum );
			p[ii].SetChildren( p2 , childNum );
		}
		else
		{
			p[ii].SetChildren( NULL , 0 );
		}

		element = element->NextSiblingElement();
	}

	*pNum = broNum;
	if( pChildNum ) *pChildNum = childNum;

	return p;
}


CXML::Node* CXML::Node::Get( gxChar* pName )
{
	Sint32 len = strlen( pName );
	gxChar *p[32];
	gxChar string[256];
	Sint32 cnt = 0;

	sprintf( string , "%s" , pName );

	p[0] = &string[0];
	cnt ++;

	for( Sint32 ii=0;ii<len;ii++)
	{
		if( pName[ii] == '/' )
		{
			string[ii] = 0x00;
			p[cnt] = &string[ii+1];
			cnt ++;
		}
	}

	if( cnt > 1 )
	{
		CXML::Node *pNode = this;
		for( Sint32 ii=0; ii<cnt; ii++ )
		{
			pNode = pNode->Get( p[ii] );
			if( pNode == NULL ) return NULL;
		}
		return pNode;
	}


	Sint32 num = GetChildNum();

	if( m_pChildArray == NULL ) return NULL;

	for( Sint32 ii=0; ii<num; ii++ )
	{
		if( CXML::IsSame(  GetChild( ii )->Name() , pName ) )
		{
			return &m_pChildArray[ii];
		}
	}

	return NULL;
}

#if 0
tinyxml2::XMLDocument doc;
doc.LoadFile( "test.xml" );
const char * pSource = "<html><head></head><body><p>hello, world!</p></body></html>";
tinyxml2::XMLDocument doc;
doc.Parse(pSource);
doc.Print();

//.xml ファイルの読み込み - tinyxml2::XMLDocument::LoadFile
tinyxml2::XMLDocument doc;
doc.LoadFile( "test.xml" );

//文字列から読み込み - tinyxml2::XMLDocument::Parse
const char * pSource = "<html><head></head><body><p>hello, world!</p></body></html>";
tinyxml2::XMLDocument doc;
doc.Parse(pSource);
doc.Print();

//ルート要素の取得と、要素内容の取得 - tinyxml2::XMLDocument::FirstChildElement
const char * pSource = "<title>The Marshmallow Times</title>";
tinyxml2::XMLDocument doc;
doc.Parse(pSource);

tinyxml2::XMLElement * elem = doc.FirstChildElement("title");
std::cout << elem->GetText() << std::endl; // "The Marshmallow Times"

//要素内の要素を取得、要素名の取得 - tinyxml2::XMLElement::FirstChildElement
const char * pSource = "<book><title>The Marshmallow Times</title></book>";
tinyxml2::XMLDocument doc;
doc.Parse(pSource);

tinyxml2::XMLElement * elem = doc.FirstChildElement("book")->FirstChildElement("title");
std::cout << elem->Name() << std::endl;    // "title"
std::cout << elem->GetText() << std::endl; // "The Marshmallow Times"

//要素の次の要素を取得 - tinyxml2::XMLElement::NextSiblingElement
const char * pSource = "<book><title>The Marshmallow Times</title><author>Lun Lun Yamamoto</author></book>";
tinyxml2::XMLDocument doc;
doc.Parse(pSource);

tinyxml2::XMLElement * elem = doc.FirstChildElement("book")->FirstChildElement();
std::cout << elem->Name() << std::endl;                       // "title"
std::cout << elem->NextSiblingElement()->Name() << std::endl; // "author"


//要素の追加 - tinyxml2::XMLElement::NewElement, tinyxml2::XMLElement::InsertEndChild
const char * pSource = "<book><title>The Marshmallow Times</title></book>";
tinyxml2::XMLDocument doc;
doc.Parse(pSource);

tinyxml2::XMLElement * root = doc.FirstChildElement();
tinyxml2::XMLElement * newElement = doc.NewElement( "author" );
root->InsertEndChild(newElement);
doc.Print();


//要素の属性（Attribute）を取得 - tinyxml2::XMLElement::Attribute
const char * pSource = "<book title=\"The Marshmallow Times\"/>";
tinyxml2::XMLDocument doc;
doc.Parse(pSource);

tinyxml2::XMLElement * bookElem = doc.FirstChildElement("book");
const char * bookTitle = bookElem->Attribute("title");
if ( nullptr != bookTitle )
  std::cout << bookTitle << std::endl; //The Marshmallow Times
#endif


void TestXML()
{
	CXML xml;
	CXML::Node *pSlot;
	const char *pStr;

	xml.LoadFile( "v4th_config.xml" );

	//ルートをデフォルト設定
	pSlot = xml.AdjustRoot();

	//URIで取得
	//	pStr = pSlot->Get("Config/Light/Slot/Diffuse")->Data();

	//URI+配列で取得
	//	pStr = pSlot->Get("Config/Light/Slot")[1].Get("Diffuse")->Data();

	//個別の要素で取得
	//	pStr = pSlot->Get("Config")->Get("Light")->Get("Slot")[0].Get("LightDir")->Data();
	//	pStr = pSlot->Get("Config")->Get("Light")->Get("Slot")[1].Get("Diffuse")->Data();

	//中腹の要素をルートに設定
	//	pSlot = xml.AdjustRoot("PostEffect");
	//	pStr = pSlot->Get("GlareBg/Threshold")->Data();

	//複数の要素があるものをルート設定して2番目の要素を取得
	pSlot = xml.AdjustRoot("Slot");
	pStr = pSlot[1].Get("Specular")->Data();

	gxLib::DebugLog( "--%s" , pStr );

	//兄弟の数を調べて、子供の詳細を得る

	Sint32 num = pSlot->GetBrotherNum();

	for( Sint32 ii=0;ii<num;ii++)
	{
		gxLib::DebugLog( "%s"   , pSlot[ii].Name() );
		gxLib::DebugLog( "--%s" , pSlot[ii].Attribute("ID") );
		gxLib::DebugLog( "--%s" , pSlot[ii].Data() );

		Sint32 childNum = pSlot[ii].GetChildNum();

		for( Sint32 jj=0; jj<childNum; jj++ )
		{
			gxLib::DebugLog( "%s[%s]" ,  pSlot[ii].GetChild( jj )->Name() ,  pSlot[ii].GetChild( jj )->Data() );
		}
	}
}


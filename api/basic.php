<?php
	//------------------------------------
	// garuru web api
	// 2017.05.30
	//------------------------------------

	$globalIP = $_SERVER["REMOTE_ADDR"];
	$operation = $_GET['ope'];

	switch( $operation ){
	case "GetIP":
		//新規ユーザー登録
		SetHeader();
		getIPAddress();
		SetFooter();
		break;

	case "Rand":
		//ランダム値を得る
		SetHeader();
		getRand();
		SetFooter();
		break;

	case "Regist":
		//ランダム値を得る
		SetHeader();
		getRand();
		getIPAddress();
		SetFooter();
		break;

	default:
		SetHeader(0);
		printf("[GARURU],0\n" );
		SetFooter();
		break;
	}



function SetHeader( $num )
{
	printf("GARURU");
}

function SetFooter()
{
	printf(",EOF,\n");
}

function getIPAddress()
{
	global $globalIP;

	$ip = explode("." , $globalIP );
	$iphex = sprintf( "%02X%02X%02X%02X"   ,$ip[0],$ip[1],$ip[2],$ip[3] );
	$ipdec = sprintf( "%02d,%02d,%02d,%02d",$ip[0],$ip[1],$ip[2],$ip[3] );

//	printf("[GET_IP],". "[DEC]," . $ipdec . "," );
//	printf("[GET_IP],". "[HEX]," . $iphex . "," );

	printf( "," . $ipdec . "," . $iphex );
}


function getRand()
{
	$rand = rand()%255;

	printf(",%d",$rand );

}

?>


--[[

  GameMain.lua

  written by ragi.

  2016.06.28

]]

require "gxLib/api"

ax = 0;

g_pFileName = "";

function gameMain()


	if( ax > 0 ) then
		gxLib:DrawLine( ax,0,100,100,1 , ATR_DFLT , 0xffffffff );
		ax = ax + 1;
	end

	gxLib:Printf(  0,0,0, ATR_DFLT , 0xffffffff , "None" );

	if( g_pFileName == "" )
		gxLib:Printf(  0,0,0, ATR_DFLT , 0xffffffff , "None" );
	else
		gxLib:Printf(  0,0,0, ATR_DFLT , 0xffffffff , "exist" );	--g_pFileName );
	end


end

function DragAndDrop( pFileName )

	g_pFileName = pFileName;

	ax = ax + 1;
end

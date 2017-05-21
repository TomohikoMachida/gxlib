--[[

  GameMain.lua

  written by ragi.

  2016.06.28

]]

require "gxLib/api"
require "gxLib/visorizer"

g_pFileName = "";

function gameMain()

	Visoriser();

end

function DragAndDrop( pFileName )

	g_pFileName = pFileName;

end

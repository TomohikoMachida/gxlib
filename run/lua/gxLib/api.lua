--[[
 ----------------------------------------------------------------------

	Lua����g�p�ł���gxLib�֐��Q

----------------------------------------------------------------------

--]]

--[[
----------------------------------------------------------------------
 define
----------------------------------------------------------------------
--]]

JOY_U = 0x01;
JOY_R = 0x02;
JOY_D = 0x04;
JOY_L = 0x08;

gxFalse         = false;
gxTrue          = 1;

ATR_DFLT		= (0x00000000)
ATR_ALPHA_NML	= (0x00000000)
ATR_ALPHA_ADD	= (0x00000001)		-- ���Z 
ATR_ALPHA_SUB	= (0x00000002)		-- ���Z 
ATR_ALPHA_CRS   = (0x00000003)		-- ��Z 
ATR_ALPHA_RVS 	= (0x00000004)		-- ���] 
ATR_ALPHA_XOR 	= (0x00000005)		-- XOR 
ATR_ALPHA_SCR 	= (0x00000006)		-- �X�N���[����Z 

ATR_ALPHA_SCR 	= (0x00000006)		-- �X�N���[����Z 

ATR_FLIP_X 		= (0x00000010)
ATR_FLIP_Y 		= (0x00000020)

ATR_STR_CENTER	= (0x00000000)
ATR_STR_LEFT	= (0x00000100)
ATR_STR_RIGHT	= (0x00000200)

ARGB_DFLT		= 0xffffffff;

ATR_DEFAULT     = ATR_DFLT
ARGB_DEFAULT    = ARGB_DFLT
ATR_ALPHA_PLUS	= ATR_ALPHA_ADD
ATR_ALPHA_MINUS	= ATR_ALPHA_SUB
ATR_FLIP_XY 	= (ATR_FLIP_X|ATR_FLIP_Y)

KEYBOARD_ESCAPE      = (0x10)
KEYBOARD_BACKSPACE   = (0x11)
KEYBOARD_TAB         = (0x12)
KEYBOARD_RETURN      = (0x13)
KEYBOARD_SHIFT       = (0x14)
KEYBOARD_RSHIFT      = (0x15)
KEYBOARD_CTRL        = (0x16)
KEYBOARD_RCTRL       = (0x17)
KEYBOARD_ALT         = (0x18)
KEYBOARD_RALT        = (0x19)
KEYBOARD_ARROW_UP    = (0x1A)
KEYBOARD_ARROW_DOWN  = (0x1B)
KEYBOARD_ARROW_LEFT  = (0x1C)
KEYBOARD_ARROW_RIGHT = (0x1D)
KEYBOARD_SPACE       = (0x1E)
KEYBOARD_ENTER       = (0x13)
KEYBOARD_F1          = (0x01)
KEYBOARD_F2          = (0x02)
KEYBOARD_F3          = (0x03)
KEYBOARD_F4          = (0x04)
KEYBOARD_F5          = (0x05)
KEYBOARD_F6          = (0x06)
KEYBOARD_F7          = (0x07)
KEYBOARD_F8          = (0x08)
KEYBOARD_F9          = (0x09)
KEYBOARD_F10         = (0x0A)
KEYBOARD_F11         = (0x0B)
KEYBOARD_F12         = (0x0C)
KEYBOARD_0           = ('0')
KEYBOARD_1           = ('1')
KEYBOARD_2           = ('2')
KEYBOARD_3           = ('3')
KEYBOARD_4           = ('4')
KEYBOARD_5           = ('5')
KEYBOARD_6           = ('6')
KEYBOARD_7           = ('7')
KEYBOARD_8           = ('8')
KEYBOARD_9           = ('9')
KEYBOARD_A           = ('A')
KEYBOARD_B           = ('B')
KEYBOARD_C           = ('C')
KEYBOARD_D           = ('D')
KEYBOARD_E           = ('E')
KEYBOARD_F           = ('F')
KEYBOARD_G           = ('G')
KEYBOARD_H           = ('H')
KEYBOARD_I           = ('I')
KEYBOARD_J           = ('J')
KEYBOARD_K           = ('K')
KEYBOARD_L           = ('L')
KEYBOARD_M           = ('M')
KEYBOARD_N           = ('N')
KEYBOARD_O           = ('O')
KEYBOARD_P           = ('P')
KEYBOARD_Q           = ('Q')
KEYBOARD_R           = ('R')
KEYBOARD_S           = ('S')
KEYBOARD_T           = ('T')
KEYBOARD_U           = ('U')
KEYBOARD_V           = ('V')
KEYBOARD_W           = ('W')
KEYBOARD_X           = ('X')
KEYBOARD_Y           = ('Y')
KEYBOARD_Z           = ('Z')

--[[
KEYSIGN01 KEYBOARD_Z		//�{�^���P
KEYSIGN02 KEYBOARD_X		//�{�^���Q
KEYSIGN03 KEYBOARD_C		//�{�^���R
KEYSIGN04 KEYBOARD_A		//�{�^���S
KEYSIGN05 KEYBOARD_S		//�{�^���T
KEYSIGN06 KEYBOARD_D		//�{�^���U
KEYSIGN07 KEYBOARD_SHIFT	//�{�^���k
KEYSIGN08 KEYBOARD_RSHIFT	//�{�^���q
KEYSIGN09 KEYBOARD_CTRL		//�{�^��L2
KEYSIGN10 KEYBOARD_RCTRL	//�{�^��R2
KEYSIGN11 KEYBOARD_SPACE	//�r�d�k�d�b�s
KEYSIGN12 KEYBOARD_ENTER	//�r�s�`�q�s
--]]

--[[
----------------------------------------------------------------------
 global value
----------------------------------------------------------------------
--]]

DisplayWidth  = 160;
DisplayHeight = 160;
PadPush = 0;
PadTrig = 0;
PadRepeat = 0;
PadRelease = 0;

KeyBoardPush    = {};
KeyBoardTrig    = {};
KeyBoardRepeat  = {};
KeyBoardRelease = {};

MouseX = 0;
MouseY = 0;
KeyBoard = 0;
GameCounter = 0;

--[[
----------------------------------------------------------------------
 function
----------------------------------------------------------------------
--]]

function InitLib()

--	for y=0,159,1 do
--		for x=0,159,1 do
--			SetVRAM	( x , y , 0xffff0000 );
--		end
--	end

end

function ARGB( a , r , g , b )

	if( 1 ) then return 0xffffffff;	end

	a = math.integer(a);
	r = math.integer(r);
	g = math.integer(g);
	b = math.integer(b);

	argb = (a<<24)|(r<<16)|(g<<8)|(b);

	return argb
end

sfcLibrary = {};

sfcLibrary.new = function()

   local instance = {};
   instance.str = "";
   setmetatable(instance, { __index = sfcLibrary} );

	return instance;
end

--[[ // ��ʏ������̔w�i�F��ݒ肵�܂�--]]
function sfcLibrary:SetBgColor( argb )
	gxDraw( 110 , argb );
end

function sfcLibrary:DrawPoint( x1,	y1, prio, atr, argb )
	-- [[ // �_��`�悵�܂� --]]
	gxDraw( 10 , x1 , y1 , prio , atr , argb );
end


--[[ 	//����`�悵�܂� --]]
function sfcLibrary:DrawLine( x1,	y1,	x2 , y2 , prio, atr, argb )
	gxDraw( 20 , x1 , y1 , x2 , y2 , prio , atr , argb );
end


--[[ 	//�O�p�`��`�悵�܂� --]]
function sfcLibrary:DrawTriangle(
			x1 , y1,
			x2 , y2 ,
			x3 , y3 ,
			prio,
			bFill,
			atr,	argb )

	--������

end


--[[ 	//�l�p�`��`�悵�܂� --]]
function sfcLibrary:DrawBox(
			x1,y1,	x2 , y2 , prio,
			bFill,
			atr,	argb,...)

	gxDraw( 0 , x1 , y1 , x2 , y2 , prio , atr , argb , bFill );

end


--[[ 	//�e�N�X�`���t���l�p�`��`�悵�܂� --]]
function sfcLibrary:PutSprite(	x,y,prio, page,u,v,w,h,cx,cy, atr,argb, r,sx,sy	)

	gxDraw( 30 , x , y , prio ,  page , u , v , w , h , cx , cy , atr , argb , r , sx ,sy );

end


--[[ 	//�e�N�X�`���t���l�p�`���iUV�f�[�^�\���̂�n���āj�`�悵�܂� --]]
function sfcLibrary:PutSpriteArray(	pSpr, x , y , prio, atr , argb, r , sx , sy )

	gxDraw( 30 , x , y , prio ,  pSpr.page , pSpr.u , pSpr.v , pSpr.w , pSpr.h , pSpr.cx , pSpr.cy , atr , argb , r , sx ,sy );

end


--[[ 	//�e�N�X�`���t���O�p�`���iUV�f�[�^�\���̂�n���āj�`�悵�܂� --]]

function sfcLibrary:PutTriangle(
			x1 , y1 ,u1,v1,
			x2 , y2 ,u2,v2,
			x3 , y3 ,u3,v3,
			tpg,
			prio,
			atr,	argb );
end

--[[ 	//�e�N�X�`�����t�@�C������Ǘ��������ɓǂݍ��݂܂� --]]
function sfcLibrary:LoadTexture ( texPage , fileName , colorKey , ox , oy )

	if( ox == nill ) then ox = 0;	end
	if( oy == nill ) then oy = 0;	end

	gxDraw( 400 , texPage , fileName , colorKey , y , ox , oy );

end


--[[ 	//�e�N�X�`��������������Ǘ��������ɓǂݍ��݂܂� --]]
function sfcLibrary:ReadTexture ( texPage , pBuffer , pSize , colorKey )

	--������
end

--[[
 	//�ǂݍ��񂾃e�N�X�`�����Ǘ�����������VRAM�Ɉꊇ���ē]�����܂�
	//���������d�����̂ŁA���ׂẴe�N�X�`����ǂݍ���ł���P��s���Ηǂ��ł�
--]]
function sfcLibrary:UploadTexture ( bForce )

	gxDraw( 410 , bForce );

end



--[[	//���揈�� --]]

function sfcLibrary:LoadMovie( uIndex , pFileName , texPage , uAudioIndex , AudioFileName )

	if( uAudioIndex == nil )   then uAudioIndex = -1;		end
	if( AudioFileName == nil ) then AudioFileName = nil;	end

	gxDraw( 410 , uIndex , pFileName ,  texPage , uAudioIndex , AudioFileName );

end

function sfcLibrary:PlayMovie( uIndex , bLoop )

	gxDraw( 411 , uIndex , bLoop );

end

function sfcLibrary:StillMovie( uIndex )

	gxDraw( 412 , uIndex , bLoop );

end

function sfcLibrary:StopMovie( uIndex )

	gxDraw( 413 , uIndex , bLoop );

end

function sfcLibrary:DrawTriangle( uIndex )


end

function sfcLibrary:DrawColorTriangle( uIndex )


end


--[[	//�T�E���h�֘A --]]


--[[	//�T�E���h�t�@�C��������������w��o���N�ɓǂݍ��݂܂� --]]
function sfcLibrary:ReadAudio( uIndex , pMemory ,uSize )

end


--[[	//�T�E���h�t�@�C�����t�@�C������w��o���N�ɓǂݍ��݂܂� --]]
function sfcLibrary:LoadAudio( uIndex , pFileName )

	gxDraw( 200 , uIndex , pFileName );

end


--[[	//�w��o���N�̃T�E���h���Đ����܂� --]]
function sfcLibrary:PlayAudio( index , bLoop , bOverWrap );

	if( bLoop     == nil ) then bLoop     = 0;	end
	if( bOverWrap == nil ) then bOverWrap = 0;	end

	gxDraw( 210 , index , bLoop , bOverWrap );
end



--[[	//�w��o���N�̃T�E���h���~���܂� --]]
function sfcLibrary:StopAudio( index , uFrm )

	if( uFrm == nil ) then uFrm = 0; end

	gxDraw( 220 , index , uFrm );

end



--[[	//����o���N�̃T�E���h�{�����[����ݒ肵�܂� --]]
function sfcLibrary:SetAudioVolume ( index , fVolume )

end



--[[	//����o���N�̃T�E���h���H�t���[���Ńt�F�[�h�C���Đ����܂� --]]
function sfcLibrary:SetAudioFadeIn ( uIndex , bLoop  , fTgtVolume ,uFrm )

end



--[[	//����o���N�̃T�E���h���H�t���[���Ńt�F�[�h�A�E�g���܂� --]]
function sfcLibrary:SetAudioFadeOut( uIndex , uFrm )

end



--[[	//���ׂẴo���N�̃T�E���h�̃{�����[�����ꊇ���Ē������܂� --]]
function sfcLibrary:SetAudioMasterVolume(  fVolume )

end



--[[	//����o���N�̃T�E���h�̍Đ��󋵂�Ԃ��܂� --]]
function sfcLibrary:IsAudioPlay( uIndex );

end


--[[	//�w��o���N�̃T�E���h�̉�����ύX���܂� --]]
function sfcLibrary:ChangeAudioPitch( index ,  fRatio )
end


--[[	//���݂̎������擾���܂� --]]
function sfcLibrary:GetTime( pYear , pMonth , pDay , pHour , pMin , pSec , pMilliSec )

	--������

end


--[[ //���[�J���̃t�@�C�����擾����--]]
function sfcLibrary:LoadFile( pFileName )

	--[[ //�o�C�i���̎�舵���͓��]]

--	ret = gxDraw( 600 , pFileName );

	return ret;
end

--[[ //���[�J���Ƀt�@�C����ۑ����� --]]
function sfcLibrary:SaveFile( pFileName , pData ,uSize )

	--������

end


--[[//�ixorShift�@�́j�����_���l�𐶐����� --]]
function sfcLibrary:Rand( ... )

	ret = gxDraw( 500 );

	--gxLib:Break( gxTrue , ret );

	if( ret < 0 ) then ret = ret *-1;	end

	rnd = math.tointeger(ret);

	return ret;
end

--[[ //���t���[���C���N�������g�����J�E���^���擾����--]]
function sfcLibrary:GetGameCounter()

	--������

end

--[[ //WEB��̃t�@�C�����擾���� --]]
function sfcLibrary:LoadWebFile( pURL , pLength , pUser , pPassword )

	--��Ή�

end


function sfcLibrary:Printf( x , y , prio , atr , argb , pStr , ... );

	gxDraw( 100 , x , y , prio , atr , argb , pStr );

end

function sfcLibrary:JoyPadPush( player )

	return PadPush;
end

function sfcLibrary:JoyPadTrig( dir )

	return PadTrig;
end

function sfcLibrary:JoyPadRelease( dir )

	return PadRelease;

end

function sfcLibrary:JoyPadRepeat( dir )

	return PadRepeat;

end

function sfcLibrary:KeyBoardPush( keyval )

	return KeyBoardPush[keyval];

end

function sfcLibrary:KeyBoardTrig( keyval )

	return KeyBoardTrig[keyval];

end

function sfcLibrary:KeyBoardRelease( keyval )

	return KeyBoardRelease[keyval];

end

function sfcLibrary:KeyBoardRepeat( keyval )

	return KeyBoardRepeat[keyval];
end


--[[	//�f�o�b�O�p	--]]

function sfcLibrary:Break( bool , val )

	if( bool ) then
		gxDraw( 900 ,val );
	end

end


function sfcLibrary:DebugLog( pString )

	gxDraw( 910 , pString );

end


--[[	//�e�X�g�p	--]]

function sfcLibrary:CaptureScreen( pFileName )

end


function sfcLibrary:TxtPrintf( pFileName , mode , pText )

end

function sfcLibrary:BinPrintf( pFileName , mode , pText )

end

gxLib = sfcLibrary.new();


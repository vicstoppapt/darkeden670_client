//----------------------------------------------------------------------
// UserOption.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "Client_PCH.h"
#include "UserOption.h"
#include "KeyAccelerator.h"
#include <DInput.h>
#include "ClientConfig.h"
#include "Packet/Properties.h"
#include "ClientConfig.h"


//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
UserOption*		g_pUserOption = NULL;

//----------------------------------------------------------------------
// define functions
//----------------------------------------------------------------------
#define READ_CHECK_EOF( value, temp, bytes )		\
		{											\
			file.read((char*)&temp, bytes);			\
			if (!file.eof())						\
			{										\
				value = temp;						\
			}										\
			else									\
			{										\
				file.close();						\
				return true;						\
			}										\
		}

//----------------------------------------------------------------------
// 
// constructor
//
//----------------------------------------------------------------------
UserOption::UserOption()
{	
	Use3DHAL			= FALSE;
	UseSmoothCursor		= FALSE;//TRUE;
	DrawMinimap			= TRUE;		// minimap을 그릴까?
	DrawZoneName		= TRUE;		// Zone이름 출력
	DrawGameTime		= TRUE;		// 게임 시간 출력
	DrawInterface		= FALSE;		// interface
	DrawFPS				= FALSE;		// FPS
	BlendingShadow		= FALSE;//TRUE;			// 그림자 반투명
	FilteringCurse		= TRUE;		// 나쁜 말 제거
	PlayMusic			= TRUE;		// 음악 출력
	PlaySound			= TRUE;		// 효과음 출력
	VolumeMusic			= 15;		// 음악 소리크기
	VolumeSound			= 15;		// 효과음 소리 크기
	UseHelpEvent		= TRUE;		// 도움말 사용
	PlayWaveMusic		= TRUE;		// Wav로 음악 출력하기(아니면 MID로)
	BloodDrop			= TRUE;		// HP 낮을 때 피 흘리기
	OpenQuickSlot		= FALSE;
	UseHalfFrame		= FALSE;
	DrawTransHPBar		= TRUE;
	UseForceFeel		= FALSE;
	UseGammaControl		= TRUE;
	GammaValue			= 100;
	DrawChatBoxOutline	= TRUE;

	//new interface
	BackupID[0]			= '\0';
	UseEnterChat		= TRUE;
	UseMouseSpeed		= FALSE;
	MouseSpeedValue		= 50;
	PlayYellSound		= TRUE;
	ShowChoboHelp		= TRUE;
	TribeChange			= FALSE;
	DenyPartyInvite		= FALSE;
	DenyPartyRequest	= FALSE;
	AutoHideSmoothScroll = TRUE;
	ChattingColor		= RGB(198, 195, 198);
	ALPHA_DEPTH			= 23;
	DefaultAlpha		= FALSE;
	IsPreLoadMonster	= TRUE;
	ChatWhite			= FALSE;
	UseTeenVersion		= FALSE;				// 틴버전으로 게임하기
	PopupChatByWhisper	= TRUE;			// 귓속말 왔을때 채팅창 잠깐 보이기
	NotSendMyInfo = FALSE;
	DoNotShowWarMsg = FALSE;
	DoNotShowLairMsg = FALSE;
	DoNotShowHolyLandMsg = FALSE;
	Chinese = FALSE;
	Korean = TRUE;
	Japanese = FALSE;
	English = FALSE;
	persnalShopupdatetime = 0;
	ShowGameMoneyWithHANGUL = FALSE;
	DoNotShowPersnalShopMsg = FALSE;
#if __CONTENTS(__AUTO_ATTACT)	
	DoNotOneClickAttackOff	= TRUE;
#endif //__JAPAN_UI
	Resolution1024			= FALSE;

#if __CONTENTS(__GAMEOPTION_ITEMBAY_MESSAGEBOX)
	DoNotShowItemBayMessageBox	= FALSE;
#endif
}

UserOption::~UserOption()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void	
UserOption::SaveToFile(const char* filename)
{
	std::ofstream file(filename, std::ios::binary);	

	DWORD flag = 0;
	file.write((const char*)&flag, 4);
	g_pKeyAccelerator->SaveToFile(file);

	file.write((const char*)&UseSmoothCursor, 4);
	file.write((const char*)&DrawMinimap, 4);
	file.write((const char*)&DrawZoneName, 4);
	file.write((const char*)&DrawGameTime, 4);
	file.write((const char*)&DrawInterface, 4);
	file.write((const char*)&DrawFPS, 4);
	file.write((const char*)&BlendingShadow, 4);
	file.write((const char*)&FilteringCurse, 4);
	file.write((const char*)&PlayMusic, 4);
	file.write((const char*)&PlaySound, 4);
	file.write((const char*)&VolumeMusic, 4);
	file.write((const char*)&VolumeSound, 4);
	file.write((const char*)&UseHelpEvent, 4);
	file.write((const char*)&PlayWaveMusic, 4);
	file.write((const char*)&BloodDrop, 4);
	file.write((const char*)&OpenQuickSlot, 4);	
	file.write((const char*)&UseHalfFrame, 4);	
	file.write((const char*)&Use3DHAL, 4);
	file.write((const char*)&DrawTransHPBar, 4);	
	file.write((const char*)&UseForceFeel, 4);
	file.write((const char*)&UseGammaControl, 4);	
	file.write((const char*)&GammaValue, 4);	
	file.write((const char*)&DrawChatBoxOutline, 4);
	
	// new interface
	file.write((const char*)BackupID, 13);
	file.write((const char*)&UseEnterChat, 4);
	file.write((const char*)&UseMouseSpeed, 4);
	file.write((const char*)&MouseSpeedValue, 4);
	file.write((const char*)&PlayYellSound, 4);
	file.write((const char*)&ShowChoboHelp, 4);
	file.write((const char*)&TribeChange, 4);
	file.write((const char*)&DenyPartyInvite, 4);
	file.write((const char*)&DenyPartyRequest, 4);
	file.write((const char*)&AutoHideSmoothScroll, 4);
	file.write((const char*)&ChattingColor, 4);
	file.write((const char*)&ALPHA_DEPTH, 1);
	file.write((const char*)&DefaultAlpha, 4);
	file.write((const char*)&IsPreLoadMonster, 4);
	file.write((const char*)&ChatWhite, 4);
	file.write((const char*)&UseTeenVersion, 4);
	file.write((const char*)&PopupChatByWhisper, 4);
	file.write((const char*)&NotSendMyInfo,4);
	file.write((const char*)&DoNotShowWarMsg,4);
	file.write((const char*)&DoNotShowLairMsg,4);
	file.write((const char*)&DoNotShowHolyLandMsg,4);
	file.write((const char*)&ShowGameMoneyWithHANGUL,4);
	file.write((const char*)&DoNotShowPersnalShopMsg,4);
#if __CONTENTS(__AUTO_ATTACT)
	file.write((const char*)&DoNotOneClickAttackOff,4);
#endif //__JAPAN_UI

	file.close();
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
bool	
UserOption::LoadFromFile(const char* filename)
{
	//if(access(filename,0)) return false;

	ivfstream file(filename, std::ios::binary);	

	if (/*!file ||*/ !file.is_open())
	{
		return false;
	}
	
	DWORD flag = 0;
	file.read((char*)&flag, 4);
	
	// 단축키를 로드 할 때 크기가 틀리다면
	// 유저 옵션 버전이 맞지 않다고 판단 설정을 초기화한다.
	if(!g_pKeyAccelerator->LoadFromFile(file))
	{
		ResetUserOption();
		return true;
	}
	
//	if(flag == 0)
//	{
//		g_pKeyAccelerator->SetAcceleratorKey(ACCEL_GRADE1INFO, DIK_R);
//		file.seekg(-2, ios::cur);
//	}

	DWORD temp;
	
	READ_CHECK_EOF( UseSmoothCursor, temp, 4 );
	READ_CHECK_EOF( DrawMinimap, temp, 4 );
	READ_CHECK_EOF( DrawZoneName, temp, 4 );
	READ_CHECK_EOF( DrawGameTime, temp, 4 );
	READ_CHECK_EOF( DrawInterface, temp, 4 );
	READ_CHECK_EOF( DrawFPS, temp, 4 );
	READ_CHECK_EOF( BlendingShadow, temp, 4 );
	READ_CHECK_EOF( FilteringCurse, temp, 4 );
	READ_CHECK_EOF( PlayMusic, temp, 4 );
	READ_CHECK_EOF( PlaySound, temp, 4 );
	READ_CHECK_EOF( VolumeMusic, temp, 4 );
	READ_CHECK_EOF( VolumeSound, temp, 4 );	
	READ_CHECK_EOF( UseHelpEvent, temp, 4 );
	READ_CHECK_EOF( PlayWaveMusic, temp, 4 );
	READ_CHECK_EOF( BloodDrop, temp, 4 );	
	READ_CHECK_EOF( OpenQuickSlot, temp, 4 );		
	READ_CHECK_EOF( UseHalfFrame, temp, 4 );	
	READ_CHECK_EOF( Use3DHAL, temp, 4);
	READ_CHECK_EOF( DrawTransHPBar, temp, 4);	
	READ_CHECK_EOF( UseForceFeel, temp, 4);	
	READ_CHECK_EOF( UseGammaControl, temp, 4);		
	READ_CHECK_EOF( GammaValue, temp, 4);	
	READ_CHECK_EOF( DrawChatBoxOutline, temp, 4);
	
	// new interface
//	READ_CHECK_EOF( *BackupID, temp, 11);
	file.read((char *)BackupID, 13);
	READ_CHECK_EOF( UseEnterChat, temp, 4);
	UseEnterChat = TRUE;
	READ_CHECK_EOF( UseMouseSpeed, temp, 4);
	READ_CHECK_EOF( MouseSpeedValue, temp, 4);
	READ_CHECK_EOF( PlayYellSound, temp, 4);
	READ_CHECK_EOF( ShowChoboHelp, temp, 4);
	READ_CHECK_EOF( TribeChange, temp, 4);
	READ_CHECK_EOF( DenyPartyInvite, temp, 4);
	READ_CHECK_EOF( DenyPartyRequest, temp, 4);
	READ_CHECK_EOF( AutoHideSmoothScroll, temp, 4);
	READ_CHECK_EOF( ChattingColor, temp, 4);
	READ_CHECK_EOF( ALPHA_DEPTH, temp, 1);
	READ_CHECK_EOF( DefaultAlpha, temp, 4);
	READ_CHECK_EOF( IsPreLoadMonster, temp, 4);
	READ_CHECK_EOF( ChatWhite, temp, 4);
	READ_CHECK_EOF( UseTeenVersion, temp, 4);
	READ_CHECK_EOF( PopupChatByWhisper, temp, 4);
	READ_CHECK_EOF( NotSendMyInfo, temp, 4);
	READ_CHECK_EOF( DoNotShowWarMsg, temp, 4);
	READ_CHECK_EOF( DoNotShowLairMsg, temp, 4);
	READ_CHECK_EOF( DoNotShowHolyLandMsg, temp, 4);
	READ_CHECK_EOF( ShowGameMoneyWithHANGUL, temp, 4);
	READ_CHECK_EOF( DoNotShowPersnalShopMsg, temp, 4);
#if __CONTENTS(__AUTO_ATTACT)
	READ_CHECK_EOF( DoNotOneClickAttackOff, temp, 4);
#endif //__JAPAN_UI
	
	

	file.close();

	return true;
}


void UserOption::ResetUserOption()
{
//	if (g_Mode!=MODE_MAINMENU)
//	{
//		DEBUG_ADD("Not Mode MODE_MAINMENU");
//		return;
//	}
	
	TCHAR currentFolder[_MAX_PATH];

	GetCurrentDirectory(_MAX_PATH,currentFolder);

	//std::

	TCHAR result[_MAX_PATH];
	strcpy(result,currentFolder);
	strcat(result,"\\UserSet\\*.set");

	struct _finddata_t c_file;
    long hFile;

	if( (hFile = _findfirst( result, &c_file )) != -1L )
	{
		TCHAR deleteFileName[_MAX_PATH];
		strcpy(deleteFileName,currentFolder);
		strcat(deleteFileName,"\\UserSet\\");
		strcat(deleteFileName,c_file.name);

		DeleteFile(deleteFileName);

        /* Find the rest of the .c files */
        while( _findnext( hFile, &c_file ) == 0 )
        {
			strcpy(deleteFileName,currentFolder);
			strcat(deleteFileName,"\\UserSet\\");
			strcat(deleteFileName,c_file.name);

			DeleteFile(deleteFileName);
        }
       _findclose( hFile );
	}

/*	TCHAR result[_MAX_PATH];
	strcpy(result,"del ");
	strcat(result,currentFolder);

	//FindFilelist
	strcat(result,"\\UserSet\\*.set");
	
	//DeleteFile(result);

	system(result);*/
	SetDefaultAccelerator();
	//gC_vs_ui.CloseOption();

	//---------------------------------------------------------------
	// 그냥 저장해버린다. - -;
	//---------------------------------------------------------------
	g_pClientConfig->SaveToFile( g_pFileDef->getProperty("FILE_INFO_CLIENTCONFIG").c_str());
	g_pUserOption->SaveToFile( g_pFileDef->getProperty("FILE_INFO_USEROPTION").c_str());

	/*if (g_Mode==MODE_MAINMENU)
	{
		if (CDirect3D::IsHAL())
		{
			// 3D가속 중인데.. 가속 끄는 경퓖E
			if (!g_pUserOption->Use3DHAL)
			{
				g_Mode = MODE_CHANGE_OPTION;
			}
		}
		else
		{
			// 3D가속 아닌데.. 가속 하는 경퓖E
			if (g_bEnable3DHAL && g_pUserOption->Use3DHAL)
			{
				g_Mode = MODE_CHANGE_OPTION;
			}
		}
	}*/
}

# Microsoft Developer Studio Project File - Name="ClientInfo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ClientInfo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientInfo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientInfo.mak" CFG="ClientInfo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientInfo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ClientInfo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientInfo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "\designed\project\client" /I "Packet" /I "DXLib" /I "SpriteLib" /I "FrameLib" /I "D3DLib" /I "VolumeLib" /I "WinLib" /I "lib" /I "Updater" /I "MZLib" /I "\designed\project\vs_ui\src\hangul" /I "\designed\project\vs_ui\src\header" /I "\designed\project\vs_ui\src\Imm" /I "\designed\project\vs_ui\src\widget" /I "\designed\lib\ui" /I "\designed\project\lib" /D "__INIT_INFO__" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ZLib.lib ZZip.lib Packing.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ClientInfo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "\Darkeden\Designed_Korea\project\Client\PackingLib" /I "\Darkeden\Designed_Korea\project\clientinfo" /I "\Darkeden\Designed_Korea\project\client" /I "\Darkeden\Designed_Korea\project\client\DXLib" /I "\Darkeden\Designed_Korea\project\client\SpriteLib" /I "\Darkeden\Designed_Korea\project\client\FrameLib" /I "\Darkeden\Designed_Korea\project\client\D3DLib" /I "\Darkeden\Designed_Korea\project\client\VolumeLib" /I "\Darkeden\Designed_Korea\project\client\Packet" /I "\Darkeden\Designed_Korea\project\client\WinLib" /I "\Darkeden\Designed_Korea\project\client\lib" /I "\Darkeden\Designed_Korea\project\client\Updater" /I "\Darkeden\Designed_Korea\project\client\MZLib" /I "\Darkeden\Designed_Korea\project\Client\VirtualFileSystem" /I "\Darkeden\Designed_Korea\project\NEW - vs_ui\src\hangul" /I "\Darkeden\Designed_Korea\project\NEW - vs_ui\src\header" /I "\Darkeden\Designed_Korea\project\NEW - vs_ui\src\Imm" /I "\Darkeden\Designed_Korea\project\NEW - vs_ui\src\widget" /I "\Darkeden\Designed_Korea\lib\ui" /D "__INIT_INFO__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "__WINDOWS__" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 VFS_debug.lib ZLib_Debug.lib MiniLZO_debug.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"Libcd.lib" /pdbtype:sept /libpath:"\Darkeden\Designed_Korea\LIB"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ClientInfo - Win32 Release"
# Name "ClientInfo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Init"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ActionInfoTable.cpp
# End Source File
# Begin Source File

SOURCE=.\ActionInfoTableFireCracker.cpp
# End Source File
# Begin Source File

SOURCE=.\ActionInfoTableOusters.cpp
# End Source File
# Begin Source File

SOURCE=.\ActionInfoTableVampire.cpp
# End Source File
# Begin Source File

SOURCE=.\AppendPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CreatureSpriteTable.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectStatusTable.CPP
# End Source File
# Begin Source File

SOURCE=.\InitCreatureTable.cpp
# End Source File
# Begin Source File

SOURCE=.\InitEffectLight.cpp
# End Source File
# Begin Source File

SOURCE=.\InitHelpManager.cpp
# End Source File
# Begin Source File

SOURCE=.\InitHelpString.cpp
# End Source File
# Begin Source File

SOURCE=.\InitInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\InitPortal.cpp
# End Source File
# Begin Source File

SOURCE=.\InitSound.CPP
# End Source File
# Begin Source File

SOURCE=.\InitZone.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MGameStringTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MNPCTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSoundTable.cpp
# End Source File
# End Group
# Begin Group "ETC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Client\AppendPatchInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CAnimationFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\CFileIndexTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\FrameLib\CFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\FrameLib\CFramePack.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\ClientConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientInfo.rc
# End Source File
# Begin Source File

SOURCE=..\Client\CMessageArray.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\ExpInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MActionInfoTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\client\MathTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MChatManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MCreatureSpriteTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MCreatureTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MEffectSpriteTypeTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MEffectStatusTable.cpp
# End Source File
# Begin Source File

SOURCE=..\client\MGridItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MHelpManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MHelpStringTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MInteractionObjectTable.cpp
# End Source File
# Begin Source File

SOURCE=..\client\MItem.cpp
# End Source File
# Begin Source File

SOURCE=..\client\MItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MItemOptionTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MItemTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MLevelNameTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MMinMaxInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MMusicTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MObject.cpp
# End Source File
# Begin Source File

SOURCE=.\MServerCreatureTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MServerItemTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MShopTemplate.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSkillInfoTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSkillManager.cpp
# End Source File
# Begin Source File

SOURCE=..\client\MSlotItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MString.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MStringArray.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MStringMap.cpp
# End Source File
# Begin Source File

SOURCE=..\client\MTimeItemManager.CPP
# End Source File
# Begin Source File

SOURCE=..\Client\MZoneTable.cpp
# End Source File
# Begin Source File

SOURCE=..\client\packet\Properties.cpp
# End Source File
# Begin Source File

SOURCE=..\client\packet\Properties.h
# End Source File
# Begin Source File

SOURCE=..\client\RankBonusTable.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerRankBonusTable.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\client\packet\StringStream.cpp
# End Source File
# Begin Source File

SOURCE=..\client\packet\StringStream.h
# End Source File
# Begin Source File

SOURCE=..\client\UserInformation.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\EventGiftInfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Client\AddonDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\AppendPatchInfo.h
# End Source File
# Begin Source File

SOURCE=.\CFileIndexTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\FrameLib\CFrame.h
# End Source File
# Begin Source File

SOURCE=..\Client\FrameLib\CFramePack.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=..\Client\ClientConfig.h
# End Source File
# Begin Source File

SOURCE=.\ClientInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\CMessageArray.h
# End Source File
# Begin Source File

SOURCE=..\Client\CTypeTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\EffectSpriteTypeDef.h
# End Source File
# Begin Source File

SOURCE=.\InitInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\ItemClassDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\MActionInfoTable.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\Client\MChatManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MCreatureSpriteTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MCreatureTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MEffectSpriteTypeTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MEffectStatusDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\MEffectStatusTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MFileDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\MGameStringTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MGridItemManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MHelpDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\MHelpManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MHelpStringTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MInteractionObjectTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MItem.h
# End Source File
# Begin Source File

SOURCE=..\Client\MItemManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MItemOptionTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MItemTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MLevelNameTable.h
# End Source File
# Begin Source File

SOURCE=.\MMinMaxInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\MMusicTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MNPCTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MObject.h
# End Source File
# Begin Source File

SOURCE=.\MServerCreatureTable.h
# End Source File
# Begin Source File

SOURCE=.\MServerItemTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MShopTemplateTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MSkillManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MSlotItemManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MSoundTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MString.h
# End Source File
# Begin Source File

SOURCE=..\Client\MStringArray.h
# End Source File
# Begin Source File

SOURCE=..\Client\MStringMap.h
# End Source File
# Begin Source File

SOURCE=..\Client\MTypeDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\MusicDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\MZoneTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\Packet\Types\PacketItemDef.h
# End Source File
# Begin Source File

SOURCE=..\client\RankBonusDef.h
# End Source File
# Begin Source File

SOURCE=..\client\RankBonusTable.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ServerRankBonusTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\SkillDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\SoundDef.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ClientInfo.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientInfo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# End Group
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Client\BitAttribute.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

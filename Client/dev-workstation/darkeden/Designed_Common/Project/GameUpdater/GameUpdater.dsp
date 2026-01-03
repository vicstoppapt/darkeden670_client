# Microsoft Developer Studio Project File - Name="GameUpdater" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GameUpdater - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameUpdater.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameUpdater.mak" CFG="GameUpdater - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameUpdater - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GameUpdater - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameUpdater - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\AutoPatchManager20" /I "..\client\Packet" /I "..\client\VirtualFileSystem" /I "..\client" /I "..\client\SpriteLib" /I "..\client\WinLib" /I "..\client\FileCheckLib" /I "..\client\MZLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__WINDOWS__" /D "__UPDATE_CLIENT__" /D "__WIN32__" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Jpeg.lib DXGUID.lib DDraw.lib SP.lib DX.lib ZLib.lib FileCheck.lib VFS.lib Shlwapi.lib wininet.lib msimg32.lib WinMM.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"libc.lib" /force /out:"d:\dklaile\Updater.exe" /libpath:"../../Lib"
# SUBTRACT LINK32 /incremental:yes /nodefaultlib

!ELSEIF  "$(CFG)" == "GameUpdater - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\AutoPatchManager20" /I "..\client\Packet" /I "..\client\VirtualFileSystem" /I "..\client" /I "..\client\SpriteLib" /I "..\client\WinLib" /I "..\client\FileCheckLib" /I "..\client\MZLib" /D "__DEBUG_OUTPUT__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "__WINDOWS__" /D "__UPDATE_CLIENT__" /D "__WIN32__" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Jpeg.lib DXGUID.lib DDraw.lib SP_Debug.lib DX_Debug.lib ZLib_Debug.lib FileCheck_Debug.lib VFS_Debug.lib ZLib_Debug.lib Shlwapi.lib wininet.lib msimg32.lib WinMM.lib /nologo /subsystem:windows /pdb:"Debug/darkeden.pdb" /debug /machine:I386 /nodefaultlib:"libc.lib" /force /out:"d:\dklegend/Updater_d.exe" /pdbtype:sept /libpath:"../../Lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GameUpdater - Win32 Release"
# Name "GameUpdater - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Resource\aa.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\account_off.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\account_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\back.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bran_off.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\bran_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\btn_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\chk_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\customer_off.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\customer_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\customers_on.bmp
# End Source File
# Begin Source File

SOURCE=.\darkeden8.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\exit_img_off.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\exit_img_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\exit_off.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\exit_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\new_exit_button_push.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\new_main.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NewUpdater2.ico
# End Source File
# Begin Source File

SOURCE=.\res\NewUpdater2.rc2
# End Source File
# Begin Source File

SOURCE=.\Resource\num_0.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_3.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_4.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_5.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_6.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_7.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_8.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_9.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_dot.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\num_ver.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\peles_img_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\peles_off.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\peles_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\progress.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\progress_back.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\progress_backtotal.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\start_img_off.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\start_img_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\start_off.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\start_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_00.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_01.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_02.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_03.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_04.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_05.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_06.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_07.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_08.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_09.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\ver_dot.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\version_.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\version_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\weblogin_bg.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\weblogin_exit_hilight.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\Window.bmp
# End Source File
# Begin Source File

SOURCE=".\업데이트.bmp"
# End Source File
# End Group
# Begin Group "Framework"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameUpdater.cpp
# End Source File
# Begin Source File

SOURCE=.\GameUpdater.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Utility"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\AutoPatchManager20\APM_Macro.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\Packet\Assert.cpp
# End Source File
# Begin Source File

SOURCE=..\client\SpriteLib\CFileIndexTable.cpp
# End Source File
# Begin Source File

SOURCE=..\client\SpriteLib\CFileIndexTable.h
# End Source File
# Begin Source File

SOURCE=..\client\CMessageArray.cpp
# End Source File
# Begin Source File

SOURCE=..\client\CMessageArray.h
# End Source File
# Begin Source File

SOURCE=.\DebugInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\MGuildInfoMapper.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MGuildMarkManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MInternetConnection.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MInternetConnection.h
# End Source File
# Begin Source File

SOURCE=..\client\MString.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MWorkNode.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MWorkNode.h
# End Source File
# Begin Source File

SOURCE=..\Client\MWorkThread.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MWorkThread.h
# End Source File
# Begin Source File

SOURCE=.\MyComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MyComboBox.h
# End Source File
# Begin Source File

SOURCE=..\Client\MZLib\MZLib.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MZLib\MZlib.h
# End Source File
# Begin Source File

SOURCE=.\NowCom_DownEngineSDK.cpp
# End Source File
# Begin Source File

SOURCE=.\NowCom_DownEngineSDK.h
# End Source File
# Begin Source File

SOURCE=.\ProgressST.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressST.h
# End Source File
# Begin Source File

SOURCE=..\Client\Packet\Properties.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\Packet\StringStream.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateManager.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateManager.h
# End Source File
# Begin Source File

SOURCE=.\UpdateManager2.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateManagerNowcom.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\UpdateManagerNowcom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\UpdateManagerThread.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateManagerThread.h
# End Source File
# Begin Source File

SOURCE=..\Client\UtilityFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.cpp
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.h
# End Source File
# End Group
# Begin Group "Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameUpdaterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GameUpdaterDlg.h
# End Source File
# Begin Source File

SOURCE=.\GameUpdaterStringInfo.h
# End Source File
# Begin Source File

SOURCE=.\GameUpdaterWebLoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GameUpdaterWebLoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScreenObjectInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenObjectInfo.h
# End Source File
# End Group
# Begin Group "Updater"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Updater.h
# End Source File
# Begin Source File

SOURCE=.\UpdaterVersionControl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GameUpdater.rc
# End Source File
# End Target
# End Project
# Section NewUpdater2 : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser2.h
# 	2:16:DefaultSinkClass:CWebBrowser2
# End Section
# Section NewUpdater2 : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser2
# 	2:10:HeaderFile:webbrowser2.h
# 	2:8:ImplFile:webbrowser2.cpp
# End Section

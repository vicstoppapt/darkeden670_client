# Microsoft Developer Studio Project File - Name="Client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Client - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak" CFG="Client - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Client - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Client - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Client - Win32 ReleaseLog" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Client - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /Zi /O1 /Ob2 /I "..\..\..\..\Darkeden\Designed_Common\project\client\OggLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\VirtualFileSystem" /I "..\..\..\..\Darkeden\Designed_Common\project\client\RarLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client" /I "..\..\..\..\Darkeden\Designed_Common\project\client\DXLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\SpriteLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\FrameLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\D3DLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\VolumeLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\Packet" /I "..\..\..\..\Darkeden\Designed_Common\project\client\WinLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\lib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\Updater" /I "..\..\..\..\Darkeden\Designed_Common\project\client\MZLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\sxml" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\hangul" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\header" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\Imm" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\widget" /I "..\..\..\..\Darkeden\Designed_Common\lib\ui" /I "..\..\..\..\Darkeden\Designed_Common\Project\xerces\include" /D "__DESIGNED_CHS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__WINDOWS__" /D "__GAME_CLIENT__" /D "__WIN32__" /FAcs /Fr /Yu"Client_PCH.h" /FD /Zm800 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 NMCrypt.lib OggStream.lib VFS.lib ZLib.lib oleaut32.lib NPGAMELIB.LIB jpeg.lib Rar.lib DEUtil.lib WinLib.lib Volume.lib DX3D.lib VS_UI_Release.lib DX.lib SP.lib FR.lib IFC22.lib ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib netapi32.lib WS2_32.LIB NMCrypt.lib OggStream.lib VFS.lib ZLib.lib oleaut32.lib NPGAMELIB.LIB jpeg.lib Rar.lib DEUtil.lib WinLib.lib Volume.lib DX3D.lib VS_UI_Release.lib DX.lib SP.lib FR.lib IFC22.lib ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib netapi32.lib WS2_32.LIB NMCrypt.lib OggStream.lib VFS.lib ZLib.lib oleaut32.lib NPGAMELIB.LIB jpeg.lib Rar.lib DEUtil.lib WinLib.lib Volume.lib DX3D.lib VS_UI_Release.lib DX.lib SP.lib FR.lib IFC22.lib ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib netapi32.lib WS2_32.LIB NMCrypt.lib OggStream.lib VFS.lib ZLib.lib oleaut32.lib NPGAMELIB.LIB jpeg.lib Rar.lib DEUtil.lib WinLib.lib Volume.lib DX3D.lib VS_UI_Release.lib DX.lib SP.lib FR.lib IFC22.lib ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib netapi32.lib WS2_32.LIB /nologo /subsystem:windows /map:"f:\DarkEden_Chs\darkeden_r.map" /debug /machine:I386 /nodefaultlib:"libct.lib" /nodefaultlib:"libctd.lib" /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /out:"F:\201\·è¿ñÁ¶Óü\dklegend_r.exe" /libpath:"..\..\..\..\Darkeden\Designed_Common\lib\ui" /libpath:"..\..\..\..\Darkeden\Designed_Common\lib" /libpath:"..\..\..\..\Darkeden\Designed_Common\Project\xerces\lib" /libpath:"..\..\..\..\Darkeden\Designed_Chs\lib\ui"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Client - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\..\Darkeden\Designed_Common\project\client\OggLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\VirtualFileSystem" /I "..\..\..\..\Darkeden\Designed_Common\project\client\RarLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client" /I "..\..\..\..\Darkeden\Designed_Common\project\client\DXLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\SpriteLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\FrameLib" /I "..\..\..\..\darkeden\Designed_Common\Project\Client\D3DLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\VolumeLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\Packet" /I "..\..\..\..\Darkeden\Designed_Common\project\client\WinLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\lib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\Updater" /I "..\..\..\..\Darkeden\Designed_Common\project\client\MZLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\sxml" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\hangul" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\header" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\Imm" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\widget" /I "..\..\..\..\Darkeden\Designed_Common\lib\ui" /I "..\..\..\..\Darkeden\Designed_Common\Project\xerces\include" /D "_DEBUG" /D "__DESIGNED_CHS" /D "__DEBUG_OUTPUT__" /D "OUTPUT_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__WINDOWS__" /D "__GAME_CLIENT__" /D "__WIN32__" /D "__MOVE_ZONE_UI__" /Fr /Yu"Client_PCH.h" /FD /GZ /Zm1000 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 NMCrypt.lib OggStream_Debug.lib VFS_debug.lib ZLib_debug.lib vld.lib Shlwapi.lib npgamelib.lib oleaut32.lib jpeg_debug.lib IFC22.lib WinLib_Debug.lib Volume_Debug.lib DX3D_Debug.lib VS_UI_Debug.lib DX_debug.lib SP_debug.lib FR_debug.lib Comctl32.lib Timer.lib imm32.lib WSock32.lib GL.lib PS.lib BasicS.lib rbt.lib Libcmtd.lib LibCimtd.lib Libcpmtd.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib kernel32.lib DEUtil.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib shell32.lib netapi32.lib NMCrypt.lib OggStream_Debug.lib VFS_debug.lib ZLib_debug.lib vld.lib Shlwapi.lib npgamelib.lib oleaut32.lib jpeg_debug.lib IFC22.lib WinLib_Debug.lib Volume_Debug.lib DX3D_Debug.lib VS_UI_Debug.lib DX_debug.lib SP_debug.lib FR_debug.lib Comctl32.lib Timer.lib imm32.lib WSock32.lib GL.lib PS.lib BasicS.lib rbt.lib Libcmtd.lib LibCimtd.lib Libcpmtd.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib kernel32.lib DEUtil.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib shell32.lib netapi32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"msvcprtd.lib" /out:"D:\Á¶Óü\·è¿ñÁ¶Óüv10\·è¿ñÁ¶Óüv9\dklegend_d.exe" /pdbtype:sept /libpath:"..\..\..\..\Darkeden\Designed_Common\lib" /libpath:"..\..\..\..\Darkeden\Designed_Common\lib\ui" /libpath:"..\..\..\..\Darkeden\Designed_Common\Project\xerces\lib" /libpath:"..\..\..\..\darkeden\Designed_Chs\lib\ui"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Client - Win32 ReleaseLog"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Client___Win32_ReleaseLog"
# PROP BASE Intermediate_Dir "Client___Win32_ReleaseLog"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseLog"
# PROP Intermediate_Dir "ReleaseLog"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O1 /Ob2 /I "\designed\project\client" /I "DXLib" /I "SpriteLib" /I "FrameLib" /I "D3DLib" /I "VolumeLib" /I "Packet" /I "WinLib" /I "lib" /I "Updater" /I "MZLib" /I "\designed\project\NEW - vs_ui\src\hangul" /I "\designed\project\NEW - vs_ui\src\header" /I "\designed\project\NEW - vs_ui\src\Imm" /I "\designed\project\NEW - vs_ui\src\widget" /I "\designed\lib\ui" /D "__DEBUG_OUTPUT__" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__WINDOWS__" /D "__GAME_CLIENT__" /D "__WIN32__" /YX /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GR /GX /ZI /Od /I "..\..\..\..\Darkeden\Designed_Common\project\client\OggLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\VirtualFileSystem" /I "..\..\..\..\Darkeden\Designed_Common\project\client\RarLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client" /I "..\..\..\..\Darkeden\Designed_Common\project\client\DXLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\SpriteLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\FrameLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\D3DLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\VolumeLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\Packet" /I "..\..\..\..\Darkeden\Designed_Common\project\client\WinLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\lib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\Updater" /I "..\..\..\..\Darkeden\Designed_Common\project\client\MZLib" /I "..\..\..\..\Darkeden\Designed_Common\project\client\sxml" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\hangul" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\header" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\Imm" /I "..\..\..\..\Darkeden\Designed_Common\project\NEW - vs_ui\src\widget" /I "..\..\..\..\Darkeden\Designed_Common\lib\ui" /I "..\..\..\..\Darkeden\Designed_Common\Project\xerces\include" /D "__DESIGNED_KOREA" /D "__DEBUG_OUTPUT__" /D "OUTPUT_DEBUG" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__WINDOWS__" /D "__GAME_CLIENT__" /D "__WIN32__" /D "_STLP_USE_STATIC_LIB" /D "__MOVE_ZONE_UI__" /Fr /Yu"Client_PCH.h" /FD /Zm1000 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 NPGAMELIB.LIB jpegLib\jpeg_release.lib Rar_release.lib DEUtil\release\DEUtil.lib WinLib\Release\WinLib.lib VolumeLib\Release\Volume.lib D3DLib\Release\DX3D.lib VS_UI_Release.lib DXLib\Release\DX.lib SpriteLib\Release\SP.lib FrameLib\Release\FR.lib IFC22.lib MZLib\Release\ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /out:"\darkedentest\darkeden.exe" /libpath:"\designed\lib\ui" /libpath:"\designed\lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 NMCrypt.lib OggStream.lib VFS.lib ZLib.lib oleaut32.lib NPGAMELIB.LIB jpeg.lib Rar.lib DEUtil.lib WinLib.lib Volume.lib DX3D.lib VS_UI_Release.lib DX.lib SP.lib FR.lib IFC22.lib ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib netapi32.lib WS2_32.LIB NMCrypt.lib OggStream.lib VFS.lib ZLib.lib oleaut32.lib NPGAMELIB.LIB jpeg.lib Rar.lib DEUtil.lib WinLib.lib Volume.lib DX3D.lib VS_UI_Release.lib DX.lib SP.lib FR.lib IFC22.lib ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib netapi32.lib WS2_32.LIB NMCrypt.lib OggStream.lib VFS.lib ZLib.lib oleaut32.lib NPGAMELIB.LIB jpeg.lib Rar.lib DEUtil.lib WinLib.lib Volume.lib DX3D.lib VS_UI_Release.lib DX.lib SP.lib FR.lib IFC22.lib ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib netapi32.lib WS2_32.LIB NMCrypt.lib OggStream.lib VFS.lib ZLib.lib oleaut32.lib NPGAMELIB.LIB jpeg.lib Rar.lib DEUtil.lib WinLib.lib Volume.lib DX3D.lib VS_UI_Release.lib DX.lib SP.lib FR.lib IFC22.lib ZLib.lib imm32.lib GL.lib Timer.lib PS.lib BasicS.lib rbt.lib Libcmt.lib Libcimt.lib Libcpmt.lib Oldnames.lib DSetup.lib DDraw.lib DInput.lib DSound.lib DXGUID.lib WinMM.lib WSock32.lib user32.lib gdi32.lib advapi32.lib uuid.lib shell32.lib kernel32.lib Comctl32.lib ole32.lib netapi32.lib WS2_32.LIB /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"libct.lib" /nodefaultlib:"libctd.lib" /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /out:"D:\DarkEden_Kor\dklegend_rlog.exe" /libpath:"..\..\..\..\Darkeden\Designed_Common\lib\ui" /libpath:"..\..\..\..\Darkeden\Designed_Common\lib" /libpath:"..\..\..\..\Darkeden\Designed_Common\Project\xerces\lib" /libpath:"..\..\..\..\Darkeden\Designed_Korea\lib\ui"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Client - Win32 Release"
# Name "Client - Win32 Debug"
# Name "Client - Win32 ReleaseLog"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "GameObject Source"

# PROP Default_Filter ""
# Begin Group "EffectGenerator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAroundZoneEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachCreatureEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachCreatureEffectGroundGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachCreatureOrbitEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachOrbitEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachZoneAroundEffectGenerator.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachZoneEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachZoneSelectableEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackCreatureAroundThrowEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackCreatureEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackCreatureHomingEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackCreatureParabolaEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackZoneBombEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackZoneEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackZoneParabolaEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackZoneRectEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MBloodyBreakerEffectGenerator.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MBloodyWallEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MBloodyWaveEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectGeneratorTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFallingEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFirePiecingEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFollowPathEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMeteorDropEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMultipleFallingEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPlayingWithFireEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRippleZoneEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRippleZonePixelEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRippleZoneWideEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRisingEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSkipEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSpreadOutEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopInventoryEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneCrossEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEmptyCrossEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEmptyHorizontalEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEmptyRectEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEmptyVerticalWallEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneMultipleEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneRandomEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneRectEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneRectRandomPixelEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneRhombusEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneSelectableEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneWallEffectGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneXEffectGenerator.cpp
# End Source File
# End Group
# Begin Group "Object class source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAnimationObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCreature.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCreatureWear.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFakeCreature.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MImageObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MInteractionObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MNPC.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPortal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShadowAnimationObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShadowObject.cpp
# End Source File
# End Group
# Begin Group "Effect class source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MChaseEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGuidanceEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHomingEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MLinearEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMovingEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MParabolaEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MScreenEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MScreenEffectManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSkipEffect.cpp
# End Source File
# End Group
# Begin Group "Information class No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\BloodBibleSignInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CUsingColorSetTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ExperienceTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ExpInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MActionInfoTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MActionResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCreatureSpriteTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCreatureTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectSpriteTypeTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectStatusTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGameStringTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MInteractionObjectTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItemOptionTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItemTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MLevelNameTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMusicTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MNPCScriptTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MNPCTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MonsterNameTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPremiumGiveItemInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSkillInfoTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSkillManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSoundTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZoneTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\NicknameInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\PCConfigTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\QuestStatusInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RankBonusTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ServerInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\TempInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UserInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UserOption.cpp
# End Source File
# End Group
# Begin Group "ItemManager source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGridItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MOustersGear.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPlayerGear.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MQuickSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSlayerGear.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSlotItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSortedItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MVampireGear.cpp
# End Source File
# End Group
# Begin Group "Shop Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMoneyManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPriceManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShopShelf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShopTemplate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTradeManager.cpp
# End Source File
# End Group
# Begin Group "World source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGameTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelicopterManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWeather.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZoneSound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZoneSoundManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SectorSoundInfo.cpp
# End Source File
# End Group
# Begin Group "Help source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCompareManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpDisplayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpMessageManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpStringTable.cpp
# End Source File
# End Group
# Begin Group "Party&Guild"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GuildInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GuildMemberInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGuildInfoMapper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGuildMarkManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MParty.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MChatManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MJusticeAttackManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MObjectSelector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ModifyStatusManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRequestMode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SoundNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\TalkBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UIDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UIMessageManager.cpp
# End Source File
# End Group
# Begin Group "Utility source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\AppendPatchInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\AtlTypes\atltypes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\AtlTypes\atltypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CAvi.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CMessageArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CShadowPartManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CSoundPartManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CSpriteTexturePartManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CTexturePartManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CToken.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\FameInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GetWinVer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MathTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MemoryPool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MemoryPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEventManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFunctionManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MLoadingSPKWorkNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMonsterKillQuestInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMusic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MQuestInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStringArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStringList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStringMap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTimeItemManager.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWarManager.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWorkNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWorkThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWorkThreadGlobal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Netmarble.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\NPGameLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\nProtect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\PackFileManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Profiler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ShowTimeChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SystemAvailabilities.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UtilityFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\WavePackFileManager.cpp
# End Source File
# End Group
# Begin Group "GameLoop source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CGameUpdate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Client.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\COpeningUpdate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CWaitPacketUpdate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CWaitUIUpdate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GameInit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GameInitInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GameMain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GameUI.cpp
# End Source File
# End Group
# Begin Group "Player/Zone/View source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DrawCreatureDivineGuidance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DrawCreatureEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DrawCreatureShadow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTopView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTopViewDraw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTopViewDraw.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTopviewExceptionProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ZoneFileHeader.cpp
# End Source File
# End Group
# Begin Group "Patch source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Updater\Update.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Updater\UpdateManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Updater\UpdateUtility.cpp
# End Source File
# End Group
# Begin Group "RequestPlayer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ClientCommunicationManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ProfileManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RequestClientPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RequestClientPlayerManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RequestFileManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RequestFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RequestServerPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RequestServerPlayerManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RequestUserManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\WhisperManager.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\APICheck.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\BGMManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\spritelib\CAlphaSprite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGChangeGearSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Client_PCH.cpp
# ADD CPP /Yc"Client_PCH.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ClientConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ClientFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CMP3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CNormalSpriteTexturePartManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CSystemInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DebugInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Defender.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeGearSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeGearSlotHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGpsTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTestDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\OperatorOption.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\OtherClass\RequestClientPacketFactoryManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\OtherClass\RequestServerPacketFactoryManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Resource.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ShrineInfoManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SkillDef.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Group "GameObject Header"

# PROP Default_Filter ""
# Begin Group "EffectGenerator No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAroundZoneEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachCreatureEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachCreatureEffectGroundGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachCreatureOrbitEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachZoneAroundEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachZoneEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachZoneSelectableEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackCreatureAroundThrowEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackCreatureEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackCreatureHomingEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackCreatureParabolaEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackZoneBombEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackZoneEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackZoneParabolaEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttackZoneRectEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MBloodyBreakerEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MBloodyWallEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MBloodyWaveEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectGeneratorTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectTarget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFallingEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFirePiecingEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFollowPathEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMeteorDropEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMultipleFallingEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPlayingWithFireEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRippleZoneEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRippleZonePixelEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRippleZoneWideEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRisingEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSkipEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSpreadOutEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopInventoryEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneCrossEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEmptyCrossEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEmptyHorizontalWallEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEmptyRectEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneEmptyVerticalEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneMultipleEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneRandomEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneRectEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneRectRandomPixelEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneRhombusEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneSelectableEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneWallEffectGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStopZoneXEffectGenerator.h
# End Source File
# End Group
# Begin Group "Effect class"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MActionResult.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MChaseEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGuidanceEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHomingEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MLinearEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMovingEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MParabolaEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MScreenEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MScreenEffectManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSkipEffect.h
# End Source File
# End Group
# Begin Group "Object class"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GameObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAnimationObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MAttachOrbitEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCreature.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCreatureWear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFakeCreature.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MImageObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MInteractionObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MInteractionObjectTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MNPC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPortal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShadowAnimationObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShadowObject.h
# End Source File
# End Group
# Begin Group "Information class"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\BloodBibleSignInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CTypeTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CUsingColorSetTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ExperienceTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ExpInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MActionInfoTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCreatureSpriteTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCreatureTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectSpriteTypeTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectStatusTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGameStringTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItemOptionTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItemTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MLevelNameTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMusicTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MNPCScriptTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MNPCTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MonsterNameTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPremiumGiveItemInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSkillManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSoundTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZoneTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\NicknameInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\QuestStatusInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RankBonusTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ServerInformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\TempInformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UserInformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UserOption.h
# End Source File
# End Group
# Begin Group "ItemManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGridItemManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItemFinder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MItemManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MOustersGear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPlayerGear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MQuickSlot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSlayerGear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSlotItemManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSortedItemManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MVampireGear.h
# End Source File
# End Group
# Begin Group "Shop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMoneyManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPriceManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShopShelf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MShopTemplateTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStorage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTradeManager.h
# End Source File
# End Group
# Begin Group "Help header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MCompareManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpDisplayer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpMessageManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpStringTable.h
# End Source File
# End Group
# Begin Group "World header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGameTime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelicopterManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MSectorInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWeather.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZoneSound.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZoneSoundManager.h
# End Source File
# End Group
# Begin Group "Party&Guild header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GuildInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\GuildMemberInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGuildInfoMapper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGuildMarkManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MParty.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MChatManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MJusticeAttackManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MObjectSelector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ModifyStatusManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MRequestMode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SectorSoundInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\TalkBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UIMessageManager.h
# End Source File
# End Group
# Begin Group "GameLoop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CGameUpdate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Client.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\COpeningUpdate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CWaitPacketUpdate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CWaitUIUpdate.h
# End Source File
# End Group
# Begin Group "Utility"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\AppendPatchInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CAvi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CDataTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CMessageArray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\COrderedList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CPartManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CPositionList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CShadowPartManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CSoundPartManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CSpriteTexturePartManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CTexturePartManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CToken.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CTypeMap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CTypeMap2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DllInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\FameInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MathTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFunctionManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MLoadingSPKWorkNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMonsterKillQuestInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MMusic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStringArray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStringList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStringMap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTimeItemManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWorkNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWorkThread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWorkThreadGlobal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\npfgmsdk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\nProtect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\PackFileManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\PCConfigTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Profiler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RaceType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ShowTimeChecker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UtilityFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ValueList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\WavePackFileManager.h
# End Source File
# End Group
# Begin Group "Player/Zone/View"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MPlayer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MViewDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZoneDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZoneInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ZoneFileHeader.h
# End Source File
# End Group
# Begin Group "Patch"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Updater\Update.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Updater\UpdateDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Updater\UpdateManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Updater\UpdateUtility.h
# End Source File
# End Group
# Begin Group "RequestPlayer header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ClientCommunicationManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ProfileManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RequestClientPlayer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RequestClientPlayerManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RequestFileManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RequestFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RequestServerPlayer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RequestServerPlayerManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\RequestTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RequestUserManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\WhisperManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\AddonDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\APICheck.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\AutoItemRooting.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Client_PCH.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ClientConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ClientDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ClientFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\CSystemInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DebugInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Defender.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DrawItemNameNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DrawTextNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\EffectSpriteTypeDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ItemClassDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MActionResultDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectGeneratorDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEffectStatusDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MEventManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MFileDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGameDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGpsTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MGuildType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MHelpDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MQuestInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTestDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTopView.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MTypeDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MusicDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\NMCrypt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\OperatorOption.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\PacketFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\PacketFunction2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\RankBonusDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\OtherClass\RequestClientPacketFactoryManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\OtherClass\RequestServerPacketFactoryManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ScreenEffectDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ServerInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ServerInfoFileParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ServerInfoFileParser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SkillDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SoundDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SoundSetting.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SpriteIDDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ThemidaSDK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UIDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\UIFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\XTrap4Client.h
# End Source File
# End Group
# Begin Group "Packet"

# PROP Default_Filter ""
# Begin Group "GPacket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\FriendDetailInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\FriendDetailInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\FriendSimpleInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\FriendSimpleInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\FriendWaitInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\FriendWaitInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCActiveGuildList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCActiveGuildList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCActiveGuildListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddBat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddBat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddBatHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddBurrowingCreature.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddBurrowingCreature.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddBurrowingCreatureHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffectToScreen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffectToScreen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffectToScreenHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffectToTile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffectToTile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddEffectToTileHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddGearToInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddGearToInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddGearToInventoryHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddGearToZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddGearToZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddGearToZoneHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddHelicopter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddHelicopter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddHelicopterHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddInjuriousCreature.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddInjuriousCreature.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddInjuriousCreatureHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddInstalledMineToZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddInstalledMineToZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddInstalledMineToZoneHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddItemToInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddItemToInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddItemToItemVerify.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddItemToItemVerify.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddItemToItemVerifyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddItemToZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddItemToZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonster.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonster.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterCorpse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterCorpse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterCorpseHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterFromBurrowing.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterFromBurrowing.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterFromBurrowingHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterFromTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterFromTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterFromTransformationHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddMonsterHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNewItemToZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNewItemToZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNewItemToZoneHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNickname.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNickname.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNicknameHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNPC.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNPC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddNPCHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddOusters.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddOusters.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddOustersCorpse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddOustersCorpse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddOustersCorpseHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddOustersHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddressListVerify.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddressListVerify.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddressListVerifyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSlayer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSlayerCorpse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSlayerCorpse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSlayerCorpseHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSlayerHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddStoreItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddStoreItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddStoreItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSylph.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSylph.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddSylphHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampire.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampire.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireCorpse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireCorpse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireCorpseHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireFromBurrowing.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireFromBurrowing.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireFromBurrowingHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireFromTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireFromTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireFromTransformationHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampireHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampirePortal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampirePortal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddVampirePortalHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddWolf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddWolf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAddWolfHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK4.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK4.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK4Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK5.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK5.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackArmsOK5Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAttackMeleeOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAuthKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAuthKey.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCAuthKeyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleSignInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleSignInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleSignInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodBibleStatusHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCBloodDrainOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCannotAdd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCannotAdd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCannotAddHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCannotUse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCannotUse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCannotUseHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCastingSkill.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCastingSkill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCastingSkillHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeDarkLight.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeDarkLight.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeDarkLightHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeInventoryItemNum.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeInventoryItemNum.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeShape.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeShape.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeShapeHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeWeather.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeWeather.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeWeatherHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCreateItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCreateItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCreateItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCreatureDied.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCreatureDied.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCreatureDiedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCCrossCounterOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteandPickUpOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteandPickUpOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteandPickUpOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteEffectFromTile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteEffectFromTile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteEffectFromTileHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteInventoryItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteInventoryItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteInventoryItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDeleteObjectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDisconnect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDisconnect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDisconnectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDownSkillFailed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDownSkillFailed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDownSkillFailedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDownSkillOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDownSkillOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDownSkillOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDropItemToZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDropItemToZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCDropItemToZoneHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCEnterVampirePortal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCEnterVampirePortal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCEnterVampirePortalHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCExecuteElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCExecuteElement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCExecuteElementHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFakeMove.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFakeMove.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFakeMoveHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFastMove.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFastMove.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFastMoveHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFlagWarStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFlagWarStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFlagWarStatusHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendAdd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendAdd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendAddHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendDel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendDel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendDelHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendReqToAdd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendReqToAdd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendReqToAddHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendReqToDel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendReqToDel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendReqToDelHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendResToAdd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendResToAdd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendResToAddHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendSuggestToAdd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendSuggestToAdd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendSuggestToAddHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendUpdateConnect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendUpdateConnect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendUpdateConnectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendUpdateZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendUpdateZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendUpdateZoneHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendViewInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendViewInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendViewInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendWaitList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendWaitList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCFriendWaitListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetDamage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetDamage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetDamageHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycleFailed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycleFailed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycleFailedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycleHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycleOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycleOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGetOffMotorCycleOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGlobalChat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGlobalChat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGlobalChatHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGoodsList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGoodsList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGoodsListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestInventoryHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestStatusInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestStatusInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestStatusInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestStatusModify.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestStatusModify.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGQuestStatusModifyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildChat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildChat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildChatHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildMemberList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildMemberList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildMemberListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCGuildResponseHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHolyLandBonusInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHolyLandBonusInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHolyLandBonusInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryEndToOthers.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryEndToOthers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryEndToOthersHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryEndToSelf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryEndToSelf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryEndToSelfHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryStartToOthers.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryStartToOthers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryStartToOthersHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryStartToSelf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryStartToSelf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCHPRecoveryStartToSelfHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCInstanceDoungeonLobby.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCInstanceDoungeonLobby.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCInstanceDoungeonLobbyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCInstanceDoungeonResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCInstanceDoungeonResult.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCInstanceDoungeonResultHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKickMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKickMessage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKickMessageHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnockBack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnockBack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnockBackHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK4.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK4.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK4Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK5.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK5.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCKnocksTargetBackOK5Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillFailed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillFailed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillFailedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillReady.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillReady.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLearnSkillReadyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLightning.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLightning.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCLightningHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMakeItemFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMakeItemFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMakeItemFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMakeItemOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMakeItemOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMakeItemOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMineExplosionOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMineExplosionOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMineExplosionOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMineExplosionOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMineExplosionOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMineExplosionOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMiniGameScores.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMiniGameScores.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMiniGameScoresHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyGuildMemberInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyGuildMemberInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyGuildMemberInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyInformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyInformationHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyNickname.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyNickname.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCModifyNicknameHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMonsterKillQuestInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMonsterKillQuestInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMonsterKillQuestInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorph1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorph1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorph1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorphSlayer2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorphSlayer2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorphSlayer2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorphVampire2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorphVampire2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMorphVampire2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMove.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMove.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMoveError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMoveError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMoveErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMoveHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMoveOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMoveOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMoveOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMPRecoveryEnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMPRecoveryEnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMPRecoveryEndHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMPRecoveryStart.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMPRecoveryStart.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMPRecoveryStartHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMyStoreInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMyStoreInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCMyStoreInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNicknameList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNicknameList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNicknameListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNicknameVerify.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNicknameVerify.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNicknameVerifyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNoticeEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNoticeEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNoticeEventHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCNotifyWin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCNotifyWin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCNotifyWinHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAsk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAsk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAskDynamic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAskDynamic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAskDynamicHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAskHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAskVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAskVariable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCAskVariableHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCResponseHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCSay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCSay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCSayDynamic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCSayDynamic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCSayDynamicHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCNPCSayHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherGuildName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherGuildName.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherGuildNameHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherModifyInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherModifyInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherModifyInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherStoreInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherStoreInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCOtherStoreInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyInvite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyInvite.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyInviteHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyJoined.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyJoined.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyJoinedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyLeave.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyLeave.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyLeaveHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyPosition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyPosition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartyPositionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartySay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartySay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPartySayHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCPetInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCPetInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCPetInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPetStashList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPetStashList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPetStashListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPetStashVerify.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPetStashVerify.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPetStashVerifyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCPetUseSkill.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCPetUseSkill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\gpackets\GCPetUseSkillHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneConnected.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneConnected.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneConnectedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneConnectionFailed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneConnectionFailed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneConnectionFailedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneDisconnected.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneDisconnected.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneDisconnectedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneSay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneSay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCPhoneSayHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCQuestStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCQuestStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCQuestStatusHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRankBonusInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRankBonusInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRankBonusInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRealWearingInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRealWearingInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRealWearingInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReconnect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReconnect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReconnectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReconnectLogin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReconnectLogin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReconnectLoginHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRegenZoneStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRegenZoneStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRegenZoneStatusHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReloadOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReloadOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCReloadOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveCorpseHead.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveCorpseHead.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveCorpseHeadHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveEffectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveFromGear.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveFromGear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveFromGearHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveInjuriousCreature.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveInjuriousCreature.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveInjuriousCreatureHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveStoreItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveStoreItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRemoveStoreItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRepairInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRepairInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRepairInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestedIP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestedIP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestedIPHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestFailed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestFailed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestFailedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestPowerPointResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestPowerPointResult.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRequestPowerPointResultHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycleFailed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycleFailed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycleFailedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycleHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycleOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycleOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRideMotorCycleOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRing.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRing.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCRingHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSayHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSearchMotorcycleFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSearchMotorcycleFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSearchMotorcycleFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSearchMotorcycleOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSearchMotorcycleOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSearchMotorcycleOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectQuestID.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectQuestID.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectQuestIDHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectRankBonusFailed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectRankBonusFailed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectRankBonusFailedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectRankBonusOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectRankBonusOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSelectRankBonusOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSetPosition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSetPosition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSetPositionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBought.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBought.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBoughtHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBuyFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBuyFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBuyFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBuyOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBuyOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopBuyOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopListMysterious.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopListMysterious.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopListMysteriousHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopMarketCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopMarketCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopMarketConditionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSellFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSellFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSellFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSellOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSellOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSellOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSold.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSold.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopSoldHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopVersion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopVersion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShopVersionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildJoin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildJoin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildJoinHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildMemberInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildMemberInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowGuildMemberInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowMessageBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowMessageBoxHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowUnionInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowUnionInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowUnionInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowWaitGuildInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowWaitGuildInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowWaitGuildInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowWebMarket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowWebMarket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCShowWebMarketHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillFailed1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillFailed1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillFailed1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillFailed2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillFailed2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillFailed2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToInventoryOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToInventoryOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToInventoryOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToInventoryOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToInventoryOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToInventoryOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK4.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK4.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK4Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK5.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK5.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK5Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK6.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK6.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToObjectOK6Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToSelfOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK4.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK4.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK4Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK5.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK5.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK5Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK6.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK6.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSkillToTileOK6Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSMSAddressList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSMSAddressList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSMSAddressListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStashList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStashList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStashListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStashSell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStashSell.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStashSellHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStatusCurrentHP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStatusCurrentHP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCStatusCurrentHPHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSubInventoryInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSubInventoryInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSubInventoryInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSweeperBonusInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSweeperBonusInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSweeperBonusInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSystemAvailabilities.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSystemAvailabilities.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSystemAvailabilitiesHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSystemMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSystemMessage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCSystemMessageHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOff.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOff.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOffHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOutFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOutFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOutFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOutOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOutOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTakeOutOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTeachSkillInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTeachSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTeachSkillInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowBombOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK1Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCThrowItemOK3Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTimeLimitItemInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTimeLimitItemInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTimeLimitItemInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeAddItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeAddItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeAddItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeFinish.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeFinish.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeFinishHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeMoney.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeMoney.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeMoneyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradePrepare.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradePrepare.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradePrepareHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeRemoveItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeRemoveItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeRemoveItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeVerify.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeVerify.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCTradeVerifyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnburrowFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnburrowFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnburrowFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnburrowOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnburrowOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnburrowOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnionOfferList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnionOfferList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUnionOfferListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUntransformFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUntransformFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUntransformFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUntransformOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUntransformOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUntransformOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUpdateInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUpdateInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUpdateInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUpdateWeekItemList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUpdateWeekItemList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUpdateWeekItemListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseBonusPointFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseBonusPointFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseBonusPointFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseBonusPointOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseBonusPointOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseBonusPointOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUseOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUsePowerPointResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUsePowerPointResult.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCUsePowerPointResultHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCVisibleFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCVisibleFail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCVisibleFailHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCVisibleOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCVisibleOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCVisibleOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWaitGuildList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWaitGuildList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWaitGuildListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWarList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWarList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWarListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWarScheduleList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWarScheduleList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWarScheduleListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWhisper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWhisper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWhisperFailed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWhisperFailed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWhisperFailedHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCWhisperHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GLIncomingConnectionError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GLIncomingConnectionError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GLIncomingConnectionErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GLIncomingConnectionOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GLIncomingConnectionOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GLIncomingConnectionOKHandler.cpp
# End Source File
# End Group
# Begin Group "CPacket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGAbsorbSoul.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGAbsorbSoul.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAcceptUnion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAcceptUnion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAcceptUnionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddGearToMouse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddGearToMouse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddInventoryToMouse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddInventoryToMouse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddItemToCodeSheet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddItemToCodeSheet.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddItemToCodeSheetHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddItemToItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddItemToItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddMouseToGear.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddMouseToGear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddMouseToInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddMouseToInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddMouseToQuickSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddMouseToQuickSlot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddMouseToZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddMouseToZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddQuickSlotToMouse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddQuickSlotToMouse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddSMSAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddSMSAddress.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddZoneToInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddZoneToInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddZoneToMouse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAddZoneToMouse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAppointSubmaster.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAppointSubmaster.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAppointSubmasterHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAttack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAttack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAuthKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGAuthKey.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGBloodDrain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGBloodDrain.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGBuyStoreItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGBuyStoreItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGBuyStoreItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGCastingSkill.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGCastingSkill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGConnect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGConnect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGCrashReport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGCrashReport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDeleteSMSAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDeleteSMSAddress.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDenyUnion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDenyUnion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDenyUnionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDepositPet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDepositPet.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDepositPetHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDialUp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDialUp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDisplayItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDisplayItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDisplayItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDissectionCorpse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDissectionCorpse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDonationMoney.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDonationMoney.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDonationMoneyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDownSkill.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDownSkill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDownSkillHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDropMoney.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGDropMoney.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGExpelGuild.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGExpelGuild.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGExpelGuildHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFailQuest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFailQuest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFailQuestHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendReqToAdd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendReqToAdd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendReqToAddHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendReqToDel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendReqToDel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendReqToDelHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendResToAdd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendResToAdd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendResToAddHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendUpdateGlobalOption.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendUpdateGlobalOption.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendUpdateGlobalOptionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendUpdateIndividualOption.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendUpdateIndividualOption.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendUpdateIndividualOptionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendViewInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendViewInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGFriendViewInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGetEventItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGetEventItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGetOffMotorCycle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGetOffMotorCycle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGlobalChat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGlobalChat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGQuestAccept.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGQuestAccept.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGQuestCancel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGQuestCancel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGuildChat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGGuildChat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGInstanceDoungeonEnter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGInstanceDoungeonEnterHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGJoinGuild.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGJoinGuild.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGLearnSkill.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGLearnSkill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGLogout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGLogout.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGLotterySelect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGLotterySelect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGLotterySelectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMakeItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMakeItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMixItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMixItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMixItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyGuildIntro.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyGuildIntro.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyGuildMember.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyGuildMember.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyGuildMemberIntro.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyGuildMemberIntro.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyNickname.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyNickname.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyTaxRatio.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGModifyTaxRatio.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMouseToStash.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMouseToStash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMove.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGMove.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGNPCAskAnswer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGNPCAskAnswer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGNPCTalk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGNPCTalk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPartyInvite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPartyInvite.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPartyLeave.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPartyLeave.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPartyPosition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPartyPosition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPartySay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPartySay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGPetGamble.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGPetGamble.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPhoneDisconnect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPhoneDisconnect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPhoneSay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPhoneSay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPickupMoney.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPickupMoney.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPortCheck.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGPortCheck.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnionAccept.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnionAccept.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnionAcceptHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnionDeny.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnionDeny.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnionDenyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGQuitUnionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRangerSay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRangerSay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRangerSayHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGReady.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGReady.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRegistGuild.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRegistGuild.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRelicToObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRelicToObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGReloadFromInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGReloadFromInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGReloadFromQuickSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGReloadFromQuickSlot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestGuildList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestGuildList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestGuildListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestGuildMemberList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestGuildMemberList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestIP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestIP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestNewbieItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestNewbieItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestPowerPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestPowerPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestRepair.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestRepair.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestRepairInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestRepairInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestRepairInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestStoreInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestStoreInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestStoreInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestUnion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestUnion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestUnionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestUnionInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestUnionInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestUnionInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestWebMarket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestWebMarket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestWebMarket2.cpp

!IF  "$(CFG)" == "Client - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Client - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Client - Win32 ReleaseLog"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestWebMarket2.h

!IF  "$(CFG)" == "Client - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Client - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Client - Win32 ReleaseLog"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestWebMarket2Handler.cpp

!IF  "$(CFG)" == "Client - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Client - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Client - Win32 ReleaseLog"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRequestWebMarketHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGResurrect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGResurrect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRideMotorCycle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGRideMotorCycle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectAllWeekItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectAllWeekItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectAllWeekItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectBloodBible.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectBloodBible.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectBloodBibleHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectGuild.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectGuild.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectGuildMember.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectGuildMember.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectNickname.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectNickname.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectPortal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectPortal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectQuest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectQuest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectQuestHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectRankBonus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectRankBonus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectRegenZone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectRegenZone.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectRegenZoneHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectTileEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectTileEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectWayPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectWayPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectWeekItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectWeekItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSelectWeekItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSetSlayerHotKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSetSlayerHotKey.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSetVampireHotKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSetVampireHotKey.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGShopRequestBuy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGShopRequestBuy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGShopRequestList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGShopRequestList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGShopRequestSell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGShopRequestSell.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSilverCoating.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGSilverCoating.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToNamed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToNamed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToSelf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToSelf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToTile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSkillToTile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSMSAddressList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSMSAddressList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSMSSend.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSMSSend.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashDeposit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashDeposit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashRequestBuy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashRequestBuy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashToMouse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashToMouse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashWithdraw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStashWithdraw.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreClose.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreClose.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreCloseHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreOpen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreOpen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreOpenHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreSign.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreSign.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGStoreSignHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSubmitScore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGSubmitScore.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTakeOutGood.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTakeOutGood.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGTameMonster.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\cpackets\CGTameMonster.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGThrowBomb.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGThrowBomb.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGThrowItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGThrowItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradeAddItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradeAddItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradeFinish.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradeFinish.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradeMoney.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradeMoney.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradePrepare.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradePrepare.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradeRemoveItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTradeRemoveItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTryJoinGuild.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTryJoinGuild.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTypeStringList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGTypeStringList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUnburrow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUnburrow.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUndisplayItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUndisplayItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUndisplayItemHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUntransform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUntransform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseBonusPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseBonusPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseItemFromGear.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseItemFromGear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseItemFromGQuestInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseItemFromGQuestInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseItemFromGQuestInventoryHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseItemFromInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseItemFromInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseMessageItemFromInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUseMessageItemFromInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUsePotionFromInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUsePotionFromInventory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUsePotionFromQuickSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUsePotionFromQuickSlot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUsePowerPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGUsePowerPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGVerifyTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGVerifyTime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGVisible.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGVisible.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGWhisper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGWhisper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGWithdrawPet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGWithdrawPet.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGWithdrawPetHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGWithdrawTax.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGWithdrawTax.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGWithdrawTaxHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLAgreement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLAgreement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLChangeServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLChangeServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLCreatePC.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLCreatePC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLDeletePC.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLDeletePC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLGetPCList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLGetPCList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLGetServerList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLGetServerList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLGetWorldList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLGetWorldList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLLogin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLLogin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLLogout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLLogout.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLQueryCharacterName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLQueryCharacterName.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLQueryPlayerID.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLQueryPlayerID.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLReconnectLogin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLReconnectLogin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLRegisterPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLRegisterPlayer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLSelectPC.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLSelectPC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLSelectServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLSelectServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLSelectWorld.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLSelectWorld.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLVersionCheck.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CLVersionCheck.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRConnect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRConnect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRConnectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRDisconnect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRDisconnect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRDisconnectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRRequest2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRRequest2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRRequest2Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRRequestHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRWhisper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRWhisper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\CRWhisperHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Upackets\CURequestLoginMode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Upackets\CURequestLoginMode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Upackets\CURequestLoginModeHandler.cpp
# End Source File
# End Group
# Begin Group "LPacket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCCreatePCError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCCreatePCError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCCreatePCErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCCreatePCOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCCreatePCOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCCreatePCOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCDeletePCError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCDeletePCError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCDeletePCErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCDeletePCOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCDeletePCOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCDeletePCOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCLoginError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCLoginError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCLoginErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCLoginOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCLoginOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCLoginOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCPCList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCPCList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCPCListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCQueryResultCharacterName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCQueryResultCharacterName.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCQueryResultCharacterNameHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCQueryResultPlayerID.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCQueryResultPlayerID.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCQueryResultPlayerIDHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCReconnect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCReconnect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCReconnectHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCRegisterPlayerError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCRegisterPlayerError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCRegisterPlayerErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCRegisterPlayerOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCRegisterPlayerOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCRegisterPlayerOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCSelectPCError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCSelectPCError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCSelectPCErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCSelectWorldError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCSelectWorldError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCSelectWorldErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCServerList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCServerList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCServerListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCShowWebPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCShowWebPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCShowWebPageHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCVersionCheckError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCVersionCheckError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCVersionCheckErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCVersionCheckOK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCVersionCheckOK.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCVersionCheckOKHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCWorldList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCWorldList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LCWorldListHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LGIncomingConnection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LGIncomingConnection.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Lpackets\LGIncomingConnectionHandler.cpp
# End Source File
# End Group
# Begin Group "RPacket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCCharacterInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCCharacterInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCCharacterInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCConnectVerify.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCConnectVerify.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCConnectVerifyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCPositionInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCPositionInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCPositionInfoHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCRequestedFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCRequestedFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCRequestedFileHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCRequestVerify.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCRequestVerify.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCRequestVerifyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCSay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCSay.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCSayHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCStatusHP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCStatusHP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Rpackets\RCStatusHPHandler.cpp
# End Source File
# End Group
# Begin Group "UPacket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Upackets\UCRequestLoginMode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Upackets\UCRequestLoginMode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Upackets\UCRequestLoginModeHandler.cpp
# End Source File
# End Group
# Begin Group "PacketTypes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\CreatureTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\FriendType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\types\GuildTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\ItemTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\ObjectTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\types\PetTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\PlayerTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\QuestTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\types\ShopTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\SystemTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\types\WarTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\ZoneTypes.h
# End Source File
# End Group
# Begin Group "PacketInfo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\BloodBibleBonusInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\BloodBibleBonusInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\EffectInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\EffectInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ExtraInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ExtraInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ExtraSlotInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ExtraSlotInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\GameTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\GameTime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\GearInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\GearInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\GearSlotInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\GearSlotInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\GuildWarInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\GuildWarInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\InstanceDoungeonInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\InstanceDoungeonInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\InventoryInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\InventoryInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\InventorySlotInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\InventorySlotInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\LevelWarInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\LevelWarInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\ModifyDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ModifyInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ModifyInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MWarManager.H
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\NPCInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\NPCInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\OustersSkillInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\OustersSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCItemInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCItemInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCOustersInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCOustersInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCOustersInfo2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCOustersInfo2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCOustersInfo3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCOustersInfo3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCSlayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCSlayerInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCSlayerInfo2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCSlayerInfo2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCSlayerInfo3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCSlayerInfo3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCVampireInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCVampireInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCVampireInfo2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCVampireInfo2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCVampireInfo3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PCVampireInfo3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\PetInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\packet\PetInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RaceWarInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RaceWarInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RideMotorcycleInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RideMotorcycleInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RideMotorcycleSlotInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\RideMotorcycleSlotInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ScriptParameter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ScriptParameter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ServerGroupInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ServerGroupInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SlayerSkillInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SlayerSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\StoreInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\StoreInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubItemInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubItemInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubOustersSkillInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubOustersSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubServerInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubServerInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubSlayerSkillInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubSlayerSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubVampireSkillInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SubVampireSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\SweeperBonusInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\SweeperBonusInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\TextInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\TextInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\VampireSkillInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\VampireSkillInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\WarInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\WarInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\WorldInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\WorldInfo.h
# End Source File
# End Group
# Begin Group "PacketUtil"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Assert.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Assert.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Properties.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Properties.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Crypt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Crypt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\FriendGlobalOptionInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\FriendGlobalOptionInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\FriendIndividualOptionInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\FriendIndividualOptionInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\StringInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\StringInfo.h
# End Source File
# End Group
# Begin Group "Socket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ClientPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ClientPlayer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Datagram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Datagram.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\DatagramPacket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\DatagramSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\DatagramSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Encrypter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Encrypter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\EncryptUtility.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Exception.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\FileAPI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\FileAPI.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Packet.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\PacketDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PacketFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PacketFactoryManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PacketFactoryManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\PacketFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PacketIDSet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PacketIDSet.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Types\PacketItemDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PacketValidator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PacketValidator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Player.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Player.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PlayerInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\PlayerStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Socket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Socket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketAPI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketAPI.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketEncryptInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketEncryptInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketEncryptOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketEncryptOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\SocketOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\StringStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\StringStream.h
# End Source File
# End Group
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ACriticalSection.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\BitAttribute.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\PROJECT\Client\ContentsFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\DataCaching.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZLib\MZLib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\MZLib\MZlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\TickTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\TickTimer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\TSingleton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\WarningKiller.h
# End Source File
# End Group
# Begin Group "CrashReport"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Designed_Common\PROJECT\Client\CrashReport\BugTrapInclude.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\PROJECT\Client\CrashReport\CrashReport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\PROJECT\Client\CrashReport\CrashReport.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\AutoItemRooting.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\BGMManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGChangeGearSlot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Cpackets\CGInstanceDoungeonEnter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\cursor1.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\darkeden.exe.manifest
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\darkeden.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeGearSlot.asp
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\Packet\Gpackets\GCChangeGearSlot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\QuestDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\ShrineInfoManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SoundNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Designed_Common\Project\Client\SystemAvailabilities.h
# End Source File
# End Target
# End Project

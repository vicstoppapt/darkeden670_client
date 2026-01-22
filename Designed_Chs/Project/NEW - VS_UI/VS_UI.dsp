# Microsoft Developer Studio Project File - Name="VS_UI" - Package Owner=<4> 
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VS_UI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VS_UI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VS_UI.mak" CFG="VS_UI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VS_UI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VS_UI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VS_UI - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "\Darkeden\Designed_Korea\project\client\PackingLib" /I "\Darkeden\Designed_Korea\project\clientinfo" /I "\Darkeden\Designed_Korea\project\client" /I "\Darkeden\Designed_Korea\project\client\dxlib" /I "\Darkeden\Designed_Korea\project\client\d3dlib" /I "\Darkeden\Designed_Korea\project\client\spriteLib" /I "\Darkeden\Designed_Korea\project\client\frameLib" /I "src\widget" /I "src\hangul" /I "src\header" /I "src\imm" /I "\Darkeden\Designed_Korea\lib" /I "..\..\lib" /I "..\..\lib\ui" /I "..\client\sxml" /I "..\xerces\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "VS_UI - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "..\Client\VirtualFileSystem" /I "\Darkeden\Designed_Korea\project\client\RarLib" /I "\Darkeden\Designed_Korea\project\client\PackingLib" /I "\Darkeden\Designed_Korea\project\clientinfo" /I "\Darkeden\Designed_Korea\project\client" /I "\Darkeden\Designed_Korea\project\client\dxlib" /I "\Darkeden\Designed_Korea\project\client\d3dlib" /I "\Darkeden\Designed_Korea\project\client\spriteLib" /I "\Darkeden\Designed_Korea\project\client\frameLib" /I "src\widget" /I "src\hangul" /I "src\header" /I "src\imm" /I "\Darkeden\Designed_Korea\lib" /I "..\..\lib" /I "..\..\lib\ui" /I "..\client\sxml" /I "..\xerces\include" /I "..\client\ZZipLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ZLib_Debug.lib VFS_Debug.lib MiniLZO_debug.lib dsound.lib winmm.lib imm32.lib PS_debug.lib BasicS.lib Timer.lib dinput.lib ddraw.lib dxguid.lib sp_debug.lib fr_debug.lib dx_debug.lib gl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Rar_debug.lib src\\imm\\ifc22.lib jpeg_debug.lib xerces-c_2D.lib cwebpage.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libc.lib" /nodefaultlib:"libcmtd.lib" /out:"C:\Program Files\DarkEdenTest\VS_UI.exe" /pdbtype:sept /libpath:"..\..\lib" /libpath:"..\xerces\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "VS_UI - Win32 Release"
# Name "VS_UI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\AcceleratorDef.cpp
# End Source File
# Begin Source File

SOURCE=.\src\AcceleratorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\AtlTypes\atltypes.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\Client_PCH.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\Client_PCH.h
# End Source File
# Begin Source File

SOURCE=.\src\CWebPage.h
# End Source File
# Begin Source File

SOURCE=.\src\cwebpage_.h
# End Source File
# Begin Source File

SOURCE=.\src\KeyAccelerator.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MPortal.cpp
# End Source File
# Begin Source File

SOURCE=.\src\OperatorCategory.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\OperatorOption.cpp
# End Source File
# Begin Source File

SOURCE=.\src\SkinManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Vs_ui.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Base.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_BBS.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_DESC.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Description.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Descriptor.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_ELEVATOR.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Exception.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Exchange.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_ExtraDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Game.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_GameCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vs_ui_gamecommon2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_GameOusters.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_GameSlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_GameVampire.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_GlobalResource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Helper.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Item.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Message.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_mouse_pointer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Operator.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_PetStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_progress.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Shop.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_skill_tree.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_SKILL_VIEW.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Storage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_TaxRate.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Title.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_TITLE_SHOWCHAR.CPP
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_Tutorial.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_ui_result_receiver.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_util.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_WebBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_widget.cpp
# End Source File
# Begin Source File

SOURCE=.\src\VS_UI_WorldMap.cpp
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\header\AcceleratorDef.h
# End Source File
# Begin Source File

SOURCE=.\src\header\AcceleratorManager.h
# End Source File
# Begin Source File

SOURCE=.\src\header\KeyAccelerator.h
# End Source File
# Begin Source File

SOURCE=.\src\header\OperatorCategory.h
# End Source File
# Begin Source File

SOURCE=..\Client\OperatorOption.h
# End Source File
# Begin Source File

SOURCE=.\src\header\SkinManager.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Base.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_bbs.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_DESC.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Description.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_descriptor.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Dialog.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_ELEVATOR.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Exception.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Exchange.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_ExtraDialog.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_filepath.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Game.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_GameCommon.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_GameCommon2.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_GameOusters.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_GameSlayer.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_GameVampire.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_GlobalResource.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Helper.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_item.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Message.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_mouse_pointer.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Operator.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_PetStorage.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_progress.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Shop.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_skill_tree.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_SKILL_VIEW.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Storage.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_TaxRate.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_title.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_Tutorial.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_ui_result_receiver.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_UIMessage.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_util.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_WebBrowser.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_widget.h
# End Source File
# Begin Source File

SOURCE=.\src\header\VS_UI_WorldMap.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "CImm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Imm\CImm.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Imm\CImm.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\FeelitAPI.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\IFC.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\IFCErrors.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmBaseTypes.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmBox.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmCompoundEffect.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmCondition.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmConstant.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmDamper.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmDevice.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmDevices.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmDXDevice.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmEffect.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmEffectSuite.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmEllipse.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmEnclosure.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmFriction.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmGrid.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmIFR.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmInertia.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmMouse.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmPeriodic.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmProjects.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmRamp.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmSpring.h
# End Source File
# Begin Source File

SOURCE=.\src\Imm\ImmTexture.h
# End Source File
# End Group
# Begin Group "hangul"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\hangul\Ci.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hangul\Ci.h
# End Source File
# Begin Source File

SOURCE=.\src\hangul\FL2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hangul\Fl2.h
# End Source File
# End Group
# Begin Group "Widget"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\widget\mother.cpp
# End Source File
# Begin Source File

SOURCE=.\src\widget\mother.h
# End Source File
# Begin Source File

SOURCE=.\src\widget\PI.H
# End Source File
# Begin Source File

SOURCE=.\src\widget\pi_core.cpp
# End Source File
# Begin Source File

SOURCE=.\src\widget\pi_core.h
# End Source File
# Begin Source File

SOURCE=.\src\widget\SimpleDataList.h
# End Source File
# Begin Source File

SOURCE=.\src\widget\u_button.cpp
# End Source File
# Begin Source File

SOURCE=.\src\widget\u_button.h
# End Source File
# Begin Source File

SOURCE=.\src\widget\U_edit.cpp
# End Source File
# Begin Source File

SOURCE=.\src\widget\U_edit.h
# End Source File
# Begin Source File

SOURCE=.\src\widget\u_scrollbar.cpp
# End Source File
# Begin Source File

SOURCE=.\src\widget\u_scrollbar.h
# End Source File
# Begin Source File

SOURCE=.\src\widget\u_window.cpp
# End Source File
# Begin Source File

SOURCE=.\src\widget\u_window.h
# End Source File
# Begin Source File

SOURCE=.\src\widget\unicorn.h
# End Source File
# End Group
# Begin Group "Ex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Client\ClientConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\ClientConfig.h
# End Source File
# Begin Source File

SOURCE=..\Client\ClientFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\ClientFunction.h
# End Source File
# Begin Source File

SOURCE=..\Client\CMessageArray.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\CMessageArray.h
# End Source File
# Begin Source File

SOURCE=..\Client\CSoundPartManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\CSoundPartManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\CTypeTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\DebugInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\DebugInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\ExperienceTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\ExperienceTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\ExpInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\ExpInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\FameInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\FameInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\MCreatureTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MCreatureTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MEventManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MEventManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MFunctionManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MFunctionManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MGameStringTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MGameStringTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MGridItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MGridItemManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MGuildInfoMapper.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MGuildInfoMapper.h
# End Source File
# Begin Source File

SOURCE=..\Client\MGuildMarkManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MGuildMarkManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MHelpMessageManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MHelpMessageManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MInventory.h
# End Source File
# Begin Source File

SOURCE=..\Client\MItem.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MItem.h
# End Source File
# Begin Source File

SOURCE=..\Client\MItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MItemManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MItemOptionTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MItemOptionTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MItemTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MItemTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MMoneyManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MMoneyManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MMonsterKillQuestInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MMonsterKillQuestInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\MNPCTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MNPCTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MObject.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MObject.h
# End Source File
# Begin Source File

SOURCE=..\Client\MOustersGear.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MOustersGear.h
# End Source File
# Begin Source File

SOURCE=..\Client\MParty.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MParty.h
# End Source File
# Begin Source File

SOURCE=..\Client\MPlayerGear.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MPlayerGear.h
# End Source File
# Begin Source File

SOURCE=..\Client\MPriceManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MPriceManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MQuestInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MQuestInfo.h
# End Source File
# Begin Source File

SOURCE=..\Client\MQuickSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MQuickSlot.h
# End Source File
# Begin Source File

SOURCE=..\Client\MShop.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MShop.h
# End Source File
# Begin Source File

SOURCE=..\Client\MShopShelf.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MShopShelf.h
# End Source File
# Begin Source File

SOURCE=..\Client\MShopTemplate.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MShopTemplateTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MSkillInfoTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSkillManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSlayerGear.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSlayerGear.h
# End Source File
# Begin Source File

SOURCE=..\Client\MSlotItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSlotItemManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MSortedItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSortedItemManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MSoundTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MSoundTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\MStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MStorage.h
# End Source File
# Begin Source File

SOURCE=..\Client\MString.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MString.h
# End Source File
# Begin Source File

SOURCE=..\Client\MStringArray.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MStringArray.h
# End Source File
# Begin Source File

SOURCE=..\Client\MTimeItemManager.CPP
# End Source File
# Begin Source File

SOURCE=..\Client\MTimeItemManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MTradeManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MTradeManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\MVampireGear.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MVampireGear.h
# End Source File
# Begin Source File

SOURCE=..\Client\MZoneTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\MZoneTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\ProfileManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\ProfileManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\Profiler.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\Profiler.h
# End Source File
# Begin Source File

SOURCE=..\Client\Packet\Properties.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\Packet\Properties.h
# End Source File
# Begin Source File

SOURCE=..\Client\RankBonusDef.h
# End Source File
# Begin Source File

SOURCE=..\Client\RankBonusTable.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\RankBonusTable.h
# End Source File
# Begin Source File

SOURCE=..\Client\ShrineInfoManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\ShrineInfoManager.h
# End Source File
# Begin Source File

SOURCE=..\Client\Packet\StringStream.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\Packet\StringStream.h
# End Source File
# Begin Source File

SOURCE=..\client\SXml\SXml.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\SXml\SXml.h
# End Source File
# Begin Source File

SOURCE=..\Client\SystemAvailabilities.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\UserInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\UserInformation.h
# End Source File
# Begin Source File

SOURCE=..\Client\UserOption.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\UserOption.h
# End Source File
# Begin Source File

SOURCE=..\Client\UtilityFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\UtilityFunction.h
# End Source File
# End Group
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Client\TickTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\Client\TickTimer.h
# End Source File
# End Group
# End Target
# End Project

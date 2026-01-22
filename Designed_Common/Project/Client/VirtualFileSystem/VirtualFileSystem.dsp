# Microsoft Developer Studio Project File - Name="VirtualFileSystem" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=VirtualFileSystem - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VirtualFileSystem.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VirtualFileSystem.mak" CFG="VirtualFileSystem - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VirtualFileSystem - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "VirtualFileSystem - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "VirtualFileSystem - Win32 ReleaseLog" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VirtualFileSystem - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /Zi /O2 /I "." /I ".." /I "nFS" /I "..\MiniLZO" /I "..\SpriteLib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_MT" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\Lib\VFS.lib"

!ELSEIF  "$(CFG)" == "VirtualFileSystem - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "." /I ".." /I "nFS" /I "..\MiniLZO" /I "..\SpriteLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_MT" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\Lib\VFS_Debug.lib"

!ELSEIF  "$(CFG)" == "VirtualFileSystem - Win32 ReleaseLog"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VirtualFileSystem___Win32_ReleaseLog"
# PROP BASE Intermediate_Dir "VirtualFileSystem___Win32_ReleaseLog"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "VirtualFileSystem___Win32_ReleaseLog"
# PROP Intermediate_Dir "VirtualFileSystem___Win32_ReleaseLog"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /Zi /O2 /I "." /I ".." /I "nFS" /I "..\MiniLZO" /I "..\SpriteLib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_MT" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /Zi /O2 /I "." /I ".." /I "nFS" /I "..\MiniLZO" /I "..\SpriteLib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_MT" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\Lib\VFS.lib"
# ADD LIB32 /nologo /out:"..\..\..\Lib\VFS.lib"

!ENDIF 

# Begin Target

# Name "VirtualFileSystem - Win32 Release"
# Name "VirtualFileSystem - Win32 Debug"
# Name "VirtualFileSystem - Win32 ReleaseLog"
# Begin Group "nFS"

# PROP Default_Filter ""
# Begin Group "Class"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CNFS.cpp
# End Source File
# Begin Source File

SOURCE=.\CNFS.h
# End Source File
# Begin Source File

SOURCE=.\CNFS.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\nFS\nfs.cpp
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs.h
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_data.cpp
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_data.h
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_dt.cpp
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_dt.h
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_fat.cpp
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_fat.h
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_iio.cpp
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_iio.h
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_nt.cpp
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_nt.h
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_pmatch.cpp
# End Source File
# Begin Source File

SOURCE=.\nFS\nfs_pmatch.h
# End Source File
# End Group
# Begin Group "VFS"

# PROP Default_Filter ""
# Begin Group "FileIO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CompressVirtualFileAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\CompressVirtualFileAccess.h
# End Source File
# Begin Source File

SOURCE=.\IFileIO.h
# End Source File
# Begin Source File

SOURCE=.\NormalFileIO.cpp
# End Source File
# Begin Source File

SOURCE=.\NormalFileIO.h
# End Source File
# Begin Source File

SOURCE=.\NormalFileIO.inl
# End Source File
# Begin Source File

SOURCE=.\VFA_Base.h
# End Source File
# Begin Source File

SOURCE=.\VirtualFileAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtualFileAccess.h
# End Source File
# Begin Source File

SOURCE=.\VirtualFileAccess.inl
# End Source File
# Begin Source File

SOURCE=.\VirtualFileIO.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtualFileIO.h
# End Source File
# Begin Source File

SOURCE=.\VirtualFileIO.inl
# End Source File
# Begin Source File

SOURCE=.\VirtualTempFileIO.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtualTempFileIO.h
# End Source File
# Begin Source File

SOURCE=.\VirtualTempFileIO.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\VFS_Macro.h
# End Source File
# Begin Source File

SOURCE=.\VFS_Precompile.h
# End Source File
# Begin Source File

SOURCE=.\vfstream.cpp
# End Source File
# Begin Source File

SOURCE=.\vfstream.h
# End Source File
# Begin Source File

SOURCE=.\vfstream.inl
# End Source File
# Begin Source File

SOURCE=.\VirtualFileSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtualFileSystem.h
# End Source File
# End Group
# End Target
# End Project

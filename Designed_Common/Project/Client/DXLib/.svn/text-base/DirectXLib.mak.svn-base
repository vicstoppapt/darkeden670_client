# Microsoft Developer Studio Generated NMAKE File, Based on DirectXLib.dsp
!IF "$(CFG)" == ""
CFG=DirectXLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DirectXLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DirectXLib - Win32 Release" && "$(CFG)" != "DirectXLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DirectXLib.mak" CFG="DirectXLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DirectXLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "DirectXLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DirectXLib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\Lib\DX.lib"


CLEAN :
	-@erase "$(INTDIR)\BIT_RES.OBJ"
	-@erase "$(INTDIR)\CDirectDraw.obj"
	-@erase "$(INTDIR)\CDirectDrawSurface.obj"
	-@erase "$(INTDIR)\CDirectInput.obj"
	-@erase "$(INTDIR)\CDirectMusic.obj"
	-@erase "$(INTDIR)\CDirectSetupGetVersion.obj"
	-@erase "$(INTDIR)\CDirectSound.obj"
	-@erase "$(INTDIR)\CDirectSoundStream.obj"
	-@erase "$(INTDIR)\CMP3.obj"
	-@erase "$(INTDIR)\header.obj"
	-@erase "$(INTDIR)\huffman.obj"
	-@erase "$(INTDIR)\mp3.obj"
	-@erase "$(INTDIR)\reader.obj"
	-@erase "$(INTDIR)\soundbuf.obj"
	-@erase "$(INTDIR)\subdecoder.obj"
	-@erase "$(INTDIR)\synfilt.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\Lib\DX.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /Zi /O1 /I "..\\" /I "..\VirtualFileSystem" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\DirectXLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DirectXLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\Lib\DX.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BIT_RES.OBJ" \
	"$(INTDIR)\CDirectDraw.obj" \
	"$(INTDIR)\CDirectDrawSurface.obj" \
	"$(INTDIR)\CDirectInput.obj" \
	"$(INTDIR)\CDirectMusic.obj" \
	"$(INTDIR)\CDirectSetupGetVersion.obj" \
	"$(INTDIR)\CDirectSound.obj" \
	"$(INTDIR)\CDirectSoundStream.obj" \
	"$(INTDIR)\CMP3.obj" \
	"$(INTDIR)\header.obj" \
	"$(INTDIR)\huffman.obj" \
	"$(INTDIR)\mp3.obj" \
	"$(INTDIR)\reader.obj" \
	"$(INTDIR)\soundbuf.obj" \
	"$(INTDIR)\subdecoder.obj" \
	"$(INTDIR)\synfilt.obj"

"..\..\..\Lib\DX.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DirectXLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\Lib\DX_Debug.lib"


CLEAN :
	-@erase "$(INTDIR)\BIT_RES.OBJ"
	-@erase "$(INTDIR)\CDirectDraw.obj"
	-@erase "$(INTDIR)\CDirectDrawSurface.obj"
	-@erase "$(INTDIR)\CDirectInput.obj"
	-@erase "$(INTDIR)\CDirectMusic.obj"
	-@erase "$(INTDIR)\CDirectSetupGetVersion.obj"
	-@erase "$(INTDIR)\CDirectSound.obj"
	-@erase "$(INTDIR)\CDirectSoundStream.obj"
	-@erase "$(INTDIR)\CMP3.obj"
	-@erase "$(INTDIR)\header.obj"
	-@erase "$(INTDIR)\huffman.obj"
	-@erase "$(INTDIR)\mp3.obj"
	-@erase "$(INTDIR)\reader.obj"
	-@erase "$(INTDIR)\soundbuf.obj"
	-@erase "$(INTDIR)\subdecoder.obj"
	-@erase "$(INTDIR)\synfilt.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\Lib\DX_Debug.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /I "..\VirtualFileSystem" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\DirectXLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DirectXLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\Lib\DX_Debug.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BIT_RES.OBJ" \
	"$(INTDIR)\CDirectDraw.obj" \
	"$(INTDIR)\CDirectDrawSurface.obj" \
	"$(INTDIR)\CDirectInput.obj" \
	"$(INTDIR)\CDirectMusic.obj" \
	"$(INTDIR)\CDirectSetupGetVersion.obj" \
	"$(INTDIR)\CDirectSound.obj" \
	"$(INTDIR)\CDirectSoundStream.obj" \
	"$(INTDIR)\CMP3.obj" \
	"$(INTDIR)\header.obj" \
	"$(INTDIR)\huffman.obj" \
	"$(INTDIR)\mp3.obj" \
	"$(INTDIR)\reader.obj" \
	"$(INTDIR)\soundbuf.obj" \
	"$(INTDIR)\subdecoder.obj" \
	"$(INTDIR)\synfilt.obj"

"..\..\..\Lib\DX_Debug.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("DirectXLib.dep")
!INCLUDE "DirectXLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "DirectXLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DirectXLib - Win32 Release" || "$(CFG)" == "DirectXLib - Win32 Debug"
SOURCE=.\BIT_RES.CPP

"$(INTDIR)\BIT_RES.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CDirectDraw.cpp

"$(INTDIR)\CDirectDraw.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CDirectDrawSurface.cpp

"$(INTDIR)\CDirectDrawSurface.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CDirectInput.cpp

"$(INTDIR)\CDirectInput.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CDirectMusic.cpp

"$(INTDIR)\CDirectMusic.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CDirectSetupGetVersion.cpp

"$(INTDIR)\CDirectSetupGetVersion.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CDirectSound.cpp

"$(INTDIR)\CDirectSound.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CDirectSoundStream.cpp

"$(INTDIR)\CDirectSoundStream.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\CMP3.cpp

"$(INTDIR)\CMP3.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\header.cpp

"$(INTDIR)\header.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\huffman.cpp

"$(INTDIR)\huffman.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mp3.cpp

"$(INTDIR)\mp3.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\reader.cpp

"$(INTDIR)\reader.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\soundbuf.cpp

"$(INTDIR)\soundbuf.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\subdecoder.cpp

"$(INTDIR)\subdecoder.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\synfilt.cpp

"$(INTDIR)\synfilt.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 


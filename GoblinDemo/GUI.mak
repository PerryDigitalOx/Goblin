# Microsoft Developer Studio Generated NMAKE File, Based on GUI.dsp
!IF "$(CFG)" == ""
CFG=GUI - WIN32 DEBUG
!MESSAGE No configuration specified. Defaulting to GUI - WIN32 DEBUG.
!ENDIF 

!IF "$(CFG)" != "GUI - Win32 Release" && "$(CFG)" != "GUI - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GUI.mak" CFG="GUI - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GUI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GUI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GUI - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\GUI.exe"

!ELSE 

ALL : "Goblin - Win32 Release" ".\GUI.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Goblin - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\App.obj"
	-@erase "$(INTDIR)\GUI.res"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\MainMenu.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinMain.obj"
	-@erase ".\GUI.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /Fp"$(INTDIR)\GUI.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\GUI.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GUI.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ddraw.lib dsound.lib dxguid.lib dinput.lib winmm.lib cdx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\GUI.pdb" /machine:I386 /out:"./GUI.exe" /libpath:"\mssdk\lib" /libpath:"lib" 
LINK32_OBJS= \
	"$(INTDIR)\App.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MainMenu.obj" \
	"$(INTDIR)\WinMain.obj" \
	"$(INTDIR)\GUI.res" \
	"..\goblin\Release\Goblin.lib"

".\GUI.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GUI - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\GUI.exe" "$(OUTDIR)\GUI.bsc"

!ELSE 

ALL : "Goblin - Win32 Debug" ".\GUI.exe" "$(OUTDIR)\GUI.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Goblin - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\App.obj"
	-@erase "$(INTDIR)\App.sbr"
	-@erase "$(INTDIR)\GUI.res"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\MainMenu.obj"
	-@erase "$(INTDIR)\MainMenu.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WinMain.obj"
	-@erase "$(INTDIR)\WinMain.sbr"
	-@erase "$(OUTDIR)\GUI.bsc"
	-@erase "$(OUTDIR)\GUI.pdb"
	-@erase ".\GUI.exe"
	-@erase ".\GUI.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /Gi /GR /GX /Zi /Od /Gf /Gy /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\GUI.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\GUI.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GUI.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\App.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\MainMenu.sbr" \
	"$(INTDIR)\WinMain.sbr"

"$(OUTDIR)\GUI.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ddraw.lib dsound.lib dxguid.lib dinput.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\GUI.pdb" /debug /machine:I386 /out:"./GUI.exe" /pdbtype:sept /libpath:"\mssdk\lib" /libpath:".\lib" /opt:NOWIN98 
LINK32_OBJS= \
	"$(INTDIR)\App.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MainMenu.obj" \
	"$(INTDIR)\WinMain.obj" \
	"$(INTDIR)\GUI.res" \
	"..\lib\Goblin.lib"

".\GUI.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("GUI.dep")
!INCLUDE "GUI.dep"
!ELSE 
!MESSAGE Warning: cannot find "GUI.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "GUI - Win32 Release" || "$(CFG)" == "GUI - Win32 Debug"
SOURCE=.\App.cpp

!IF  "$(CFG)" == "GUI - Win32 Release"


"$(INTDIR)\App.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GUI - Win32 Debug"


"$(INTDIR)\App.obj"	"$(INTDIR)\App.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\GUI.rc

"$(INTDIR)\GUI.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\main.cpp

!IF  "$(CFG)" == "GUI - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GUI - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MainMenu.cpp

!IF  "$(CFG)" == "GUI - Win32 Release"


"$(INTDIR)\MainMenu.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GUI - Win32 Debug"


"$(INTDIR)\MainMenu.obj"	"$(INTDIR)\MainMenu.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\WinMain.cpp

!IF  "$(CFG)" == "GUI - Win32 Release"


"$(INTDIR)\WinMain.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GUI - Win32 Debug"


"$(INTDIR)\WinMain.obj"	"$(INTDIR)\WinMain.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

!IF  "$(CFG)" == "GUI - Win32 Release"

"Goblin - Win32 Release" : 
   cd "\Projects\Personal\goblin"
   $(MAKE) /$(MAKEFLAGS) /F .\Goblin.mak CFG="Goblin - Win32 Release" 
   cd "..\GoblinDemo"

"Goblin - Win32 ReleaseCLEAN" : 
   cd "\Projects\Personal\goblin"
   $(MAKE) /$(MAKEFLAGS) /F .\Goblin.mak CFG="Goblin - Win32 Release" RECURSE=1 CLEAN 
   cd "..\GoblinDemo"

!ELSEIF  "$(CFG)" == "GUI - Win32 Debug"

"Goblin - Win32 Debug" : 
   cd "\Projects\Personal\goblin"
   $(MAKE) /$(MAKEFLAGS) /F .\Goblin.mak CFG="Goblin - Win32 Debug" 
   cd "..\GoblinDemo"

"Goblin - Win32 DebugCLEAN" : 
   cd "\Projects\Personal\goblin"
   $(MAKE) /$(MAKEFLAGS) /F .\Goblin.mak CFG="Goblin - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\GoblinDemo"

!ENDIF 


!ENDIF 


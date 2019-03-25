# Microsoft Developer Studio Project File - Name="Goblin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Goblin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Goblin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Goblin.mak" CFG="Goblin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Goblin - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Goblin - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Goblin - Win32 Release"

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
# ADD CPP /nologo /G5 /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX"defs.h" /FD /opt:NOWIN98 /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Goblin - Win32 Debug"

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
# ADD CPP /nologo /G5 /W3 /Gm /GR /GX /Zi /Od /I "..\cdx" /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /D "STRICT" /YX"defs.h" /FD /GZ /opt:NOWIN98 /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\Goblin.lib"

!ENDIF 

# Begin Target

# Name "Goblin - Win32 Release"
# Name "Goblin - Win32 Debug"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AnimObj.cpp
# End Source File
# Begin Source File

SOURCE=.\avisurface.cpp
# End Source File
# Begin Source File

SOURCE=.\CDXFontBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CDXFontBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\CDXFontGDI.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBAvi.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBButtonMasked.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBCheckBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBColor.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBHProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBInput.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBManager.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBMsgBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBPopMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBRadioButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBStaticPic.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBStaticText.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBTextBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBToolTip.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\GOBWidgetParent.cpp
# End Source File
# Begin Source File

SOURCE=.\msglist.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemButtons.cpp
# End Source File
# End Group
# Begin Group "Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AnimObj.h
# End Source File
# Begin Source File

SOURCE=.\avisurface.h
# End Source File
# Begin Source File

SOURCE=.\CDXFontBase.h
# End Source File
# Begin Source File

SOURCE=.\CDXFontBitmap.h
# End Source File
# Begin Source File

SOURCE=.\CDXFontGDI.h
# End Source File
# Begin Source File

SOURCE=.\gobavi.h
# End Source File
# Begin Source File

SOURCE=.\GOBButton.h
# End Source File
# Begin Source File

SOURCE=.\GOBButtonMasked.h
# End Source File
# Begin Source File

SOURCE=.\GOBCheckBox.h
# End Source File
# Begin Source File

SOURCE=.\GOBColor.h
# End Source File
# Begin Source File

SOURCE=.\GOBComboBox.h
# End Source File
# Begin Source File

SOURCE=.\GOBDefs.h
# End Source File
# Begin Source File

SOURCE=.\GOBEditBox.h
# End Source File
# Begin Source File

SOURCE=.\GOBFrame.h
# End Source File
# Begin Source File

SOURCE=.\GOBHProgressBar.h
# End Source File
# Begin Source File

SOURCE=.\GOBHScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\GOBInput.h
# End Source File
# Begin Source File

SOURCE=.\GOBManager.h
# End Source File
# Begin Source File

SOURCE=.\GOBMenu.h
# End Source File
# Begin Source File

SOURCE=.\GOBMsgBox.h
# End Source File
# Begin Source File

SOURCE=.\GOBPanel.h
# End Source File
# Begin Source File

SOURCE=.\GOBPopMenu.h
# End Source File
# Begin Source File

SOURCE=.\GOBRadioButton.h
# End Source File
# Begin Source File

SOURCE=.\GOBScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\GOBSlider.h
# End Source File
# Begin Source File

SOURCE=.\GOBStaticPic.h
# End Source File
# Begin Source File

SOURCE=.\GOBStaticText.h
# End Source File
# Begin Source File

SOURCE=.\GOBTextBox.h
# End Source File
# Begin Source File

SOURCE=.\GOBToolTip.h
# End Source File
# Begin Source File

SOURCE=.\GOBVScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\GOBWidget.h
# End Source File
# Begin Source File

SOURCE=.\GOBWidgetParent.h
# End Source File
# Begin Source File

SOURCE=.\msglist.h
# End Source File
# Begin Source File

SOURCE=.\SystemButtons.h
# End Source File
# End Group
# End Target
# End Project

;chr2r

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  RequestExecutionLevel admin
 
  Name "chr2r"
  OutFile "setup.exe"
  InstallDir "$PROGRAMFILES\chr2r"
  
  !define MUI_PRODUCT "chr2r"
  !define MUI_NAME "Classic Heroes Redefined 2: Revengeance"
  !define MUI_FILE "Heros"
  !define MUI_FINISHPAGE_RUN "$INSTDIR\${MUI_FILE}.exe"
  !define MUI_FINISHPAGE_RUN_TEXT "Launch ${MUI_NAME}"
  
  InstallDirRegKey HKCU "Software\chr2r" "$INSTDIR\${MUI_FILE}.exe"

;--------------------------------
;Variables

  Var StartMenuFolder
  
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_LICENSE "dependencies\license.txt"
  
  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\${MUI_NAME}" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
  
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Game" SecGame
  ;SetShellVarContext all

  SetOutPath "$INSTDIR"

  File "Heros\Release\${MUI_FILE}.exe"
  File "Heros\Release\ikpFlac.dll"
  File "Heros\Release\ikpMP3.dll"
  File "Heros\Release\irrKlang.dll"
  File "Heros\Release\logo.ico"
  SetOutPath "$INSTDIR\lvl"
  File "Heros\Release\lvl\*.dat"
  SetOutPath "$INSTDIR\snd"
  File "Heros\Release\snd\*.*"
  SetOutPath "$INSTDIR\spr"
  File "Heros\Release\spr\*.bmp"
  
  SetOutPath "$INSTDIR"
  
  CreateShortCut "$DESKTOP\${MUI_NAME}.lnk" "$INSTDIR\${MUI_FILE}.exe" "" "$INSTDIR\logo.ico" 0
 
  CreateDirectory "$SMPROGRAMS\${MUI_NAME}"
  CreateShortCut "$SMPROGRAMS\${MUI_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\${MUI_FILE}.exe" 0
  CreateShortCut "$SMPROGRAMS\${MUI_NAME}\${MUI_NAME}.lnk" "$INSTDIR\${MUI_FILE}.exe" "" "$INSTDIR\logo.ico" 0
 
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" "DisplayName" "${MUI_NAME} (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKCU "Software\${MUI_PRODUCT}" "" $INSTDIR

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecGame ${LANG_ENGLISH} "The game."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecGame} $(DESC_SecGame)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  ;SetShellVarContext all
  
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
  
  Delete "$DESKTOP\${MUI_NAME}.lnk"
  
  Delete "$SMPROGRAMS\${MUI_NAME}\Uninstall.lnk"
  Delete "$SMPROGRAMS\${MUI_NAME}\${MUI_NAME}.lnk" 
  RMDir "$SMPROGRAMS\${MUI_NAME}"
 
  DeleteRegKey /ifempty HKCU "Software\${MUI_PRODUCT}"
  DeleteRegKey /ifempty HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" 
  
  Delete "$INSTDIR\${MUI_FILE}.exe"
  Delete "$INSTDIR\ikpFlac.dll"
  Delete "$INSTDIR\ikpMP3.dll"
  Delete "$INSTDIR\irrKlang.dll"
  
  Delete "$INSTDIR\Uninstall.exe"
  Delete "$INSTDIR\logo.ico"

  RMDir /r "$INSTDIR\lvl"
  RMDir /r "$INSTDIR\snd"
  RMDir /r "$INSTDIR\spr"
  
  RMDir "$INSTDIR"
 
SectionEnd

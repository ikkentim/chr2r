;chr2r
;
;

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  !define MUI_PRODUCT "Classic Heroes Redefined 2"
  !define MUI_NAME "Classic Heroes Redefined 2"
  !define MUI_FILE "Heros"
  !define MUI_FINISHPAGE_RUN "$INSTDIR\${MUI_FILE}.exe"
  !define MUI_FINISHPAGE_RUN_TEXT "Launch ${MUI_NAME}"
  
  ;Name and file
  Name "${MUI_NAME}"
  OutFile "setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${MUI_PRODUCT}"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\${MUI_PRODUCT}" "$INSTDIR\${MUI_FILE}.exe"
  
  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

;--------------------------------
;Variables

  Var StartMenuFolder
  
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "dependencies\license.txt"
  !insertmacro MUI_PAGE_DIRECTORY
  
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

  SetOutPath "$INSTDIR"

  File "README.txt"
  File "dependencies\license.txt"
  File "dependencies\logo.ico"
  
  File "Heros\Release\${MUI_FILE}.exe"
  File "Heros\Release\ikpFlac.dll"
  File "Heros\Release\ikpMP3.dll"
  File "Heros\Release\irrKlang.dll"
  
  SetOutPath "$INSTDIR\lvl"
  File "Heros\Release\lvl\*.dat"
  SetOutPath "$INSTDIR\snd"
  File "Heros\Release\snd\*.*"
  SetOutPath "$INSTDIR\spr"
  File "Heros\Release\spr\*.bmp"
  
  SetOutPath "$INSTDIR"
  
  ;Store installation folder
  WriteRegStr HKCU "Software\Modern UI Test" "" $INSTDIR
   
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
    CreateShortcut "$SMPROGRAMS\$StartMenuFolder\${MUI_NAME}.lnk" "$INSTDIR\${MUI_FILE}.exe" "" "$INSTDIR\logo.ico" 0
    CreateShortcut "$DESKTOP\${MUI_NAME}.lnk" "$INSTDIR\${MUI_FILE}.exe" "" "$INSTDIR\logo.ico" 0
 
  !insertmacro MUI_STARTMENU_WRITE_END

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

  Delete "README.txt"
  Delete "license.txt"
  Delete "logo.ico"
  
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
 
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
  Delete "$DESKTOP\${MUI_NAME}.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\${MUI_NAME}.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"
  
  DeleteRegKey /ifempty HKCU "Software\Modern UI Test"

SectionEnd

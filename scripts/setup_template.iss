; Template Inno Setup para Dark Eden Client
; Baseado na estrutura criada por prepare_setup.bat
; Uso: Compilar com Inno Setup Compiler

[Setup]
AppName=Dark Eden Client
AppVersion=1.0
DefaultDirName={pf}\DarkEden
DefaultGroupName=Dark Eden
OutputDir=dist
OutputBaseFilename=DarkEden_Setup
Compression=lzma
SolidCompression=yes
LicenseFile=
InfoBeforeFile=
InfoAfterFile=
SetupIconFile=
WizardImageFile=
WizardSmallImageFile=

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; Executavel e DLLs
Source: "dist\bin\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; Dados do jogo
Source: "dist\data\*"; DestDir: "{app}\data"; Flags: ignoreversion recursesubdirs createallsubdirs
; Arquivos de configuracao
Source: "dist\*.inf"; DestDir: "{app}"; Flags: ignoreversion
Source: "dist\*.ini"; DestDir: "{app}"; Flags: ignoreversion
Source: "dist\*.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Dark Eden"; Filename: "{app}\fk.exe"
Name: "{group}\{cm:UninstallProgram,Dark Eden}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Dark Eden"; Filename: "{app}\fk.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\fk.exe"; Description: "{cm:LaunchProgram,Dark Eden}"; Flags: nowait postinstall skipifsilent

[Code]
// Codigo personalizado pode ser adicionado aqui
// Exemplo: Verificar requisitos, criar arquivos adicionais, etc.

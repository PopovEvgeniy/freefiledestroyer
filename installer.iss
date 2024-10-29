[Setup]
AppId={{66BDC81D-C79A-4A38-BD0D-10B715BC78E2}
AppName=Free file destroyer
AppVersion=1.3.1.2
AppPublisher=Popov Evgeniy Alekseyevich
AppPublisherURL=https://github.com/PopovEvgeniy
AppSupportURL=https://github.com/PopovEvgeniy/freefiledestroyer
AppUpdatesURL=https://github.com/PopovEvgeniy/freefiledestroyer/releases/latest
DefaultDirName={pf}\Free file destroyer
DefaultGroupName=Free file destroyer
LicenseFile=.\copying.txt
InfoBeforeFile=.\readme.txt
OutputDir=.\
OutputBaseFilename=freefiledestroyer_setup
Compression=lzma
SolidCompression=true
InternalCompressLevel=max
MinVersion=5.0
RestartIfNeededByRun=false
PrivilegesRequired=none
UsePreviousUserInfo=false
UsePreviousAppDir=true
DisableStartupPrompt=true
DisableReadyPage=true
UsePreviousSetupType=false
UsePreviousTasks=false

[Files]
Source: .\copying.txt; DestDir: {app}; Flags: ignoreversion
Source: .\freefiledestroyer.exe; DestDir: {app}; Flags: ignoreversion
Source: .\readme.txt; DestDir: {app}; Flags: ignoreversion
Source: .\source.zip; DestDir: {app}; Flags: ignoreversion; Components: Source

[Types]
Name: Normal; Description: Normal installation; Flags: iscustom

[Components]
Name: Main; Description: Main components; Flags: fixed; Types: Normal
Name: Source; Description: Source code

[Icons]
Name: {group}\Documentation\Help; Filename: {app}\readme.txt; Flags: runmaximized
Name: {group}\Documentation\License; Filename: {app}\copying.txt; Flags: runmaximized
Name: {group}\Source code; Filename: {app}\source.zip; Components: Source
Name: {group}\Uninstall Free file destroyer; Filename: {app}\unins000.exe

[Registry]
Root: HKCR; Subkey: *\Shell\Destroy this file via Free file destroyer\command; ValueType: string; ValueData: {app}\freefiledestroyer.exe %1; Flags: uninsdeletekey
Root: HKCR; Subkey: *\Shell\Destroy this file via Free file destroyer; Flags: uninsdeletekey; ValueType: none
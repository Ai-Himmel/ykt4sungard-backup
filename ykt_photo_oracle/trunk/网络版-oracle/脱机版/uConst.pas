unit uConst;

interface

uses
  Dialogs, SysUtils, inifiles;
  
var
  SrcDir: string;
  DstDir: string;
  PreName: string;
  NumLen: Integer;

implementation

procedure GetInfo;
var
  FileName: string;
  IniFile: TIniFile;
begin
  FileName := GetCurrentDir + '\file.ini';
  if not FileExists(FileName) then
  begin
    ShowMessage('ϵͳ�����ļ������ڣ�����ϵͳ����Ա��ϵ��');
  end;
  IniFile := TIniFile.Create(FileName);
  
  SrcDir := IniFile.ReadString('FILEDIR', 'SrcDir', '');
  DstDir := IniFile.ReadString('FILEDIR', 'DstDir', '');
  PreName := IniFile.ReadString('FILEDIR', 'PreName', '');
  NumLen := IniFile.ReadInteger('FILEDIR', 'NumLen', 0);

  IniFile.Free;
end;

initialization
  GetInfo;
  
end.

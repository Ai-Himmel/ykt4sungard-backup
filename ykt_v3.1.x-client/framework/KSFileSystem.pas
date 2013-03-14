unit KSFileSystem;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSFileSystem
   <What>�ṩ��ȡǰ̨�����ļ�ϵͳ�ṹ�Ĺ�������
   <Written By> Huang YanLai (������)
   <History>
**********************************************}

{
���
    StartDir - ��������·��
    LocalBaseDir - ���򱾵ظ�·�������ظ�·���������Ŀ¼������Ա���������Ϣ
    BaseDir - �����·�������ԴӸ�·���������Ŀ¼�����ȡ����������Ҫ��������Ϣ
}
interface

uses SysUtils, Classes;

type
  TKSClientRunMode = (
    rmStandalone, // �������У���·���ͱ��ظ�·����ͬ�����ݳ�������·�����
    rmRemote,     // ���ļ��������������У���·�����ݳ�������·����ã����ظ�·����
    rmRemoteLocal // ִ�г����ڱ������棬�������ļ����������棺��·�����������ļ���ȡ�����ظ�·�����ݳ�������·�����
  );

{
  <Function>GetDirs
  <What>��ó������е�����·���ͱ��ظ�·����
  ���Ҹ��ݱ��ظ�·���Լ����ܴ��ڵ�start.ini�ļ�ȷ��ǰ̨�����ļ�ϵͳ�ĸ�·����
  �����Ƿ��������ģʽ
  <Params>
    StartDir - ��������·��
    LocalBaseDir - ���򱾵ظ�·�������ظ�·���������Ŀ¼������Ա���������Ϣ
    BaseDir - �����·�������ԴӸ�·���������Ŀ¼�����ȡ����������Ҫ��������Ϣ
  <Exception>
}
function  GetDirs(var StartDir, LocalBaseDir, BaseDir : string) : TKSClientRunMode;

procedure GetIniFileNames(const StartDir, BaseDir : string; var StartIni, MainIni : string);

{
  <Function>GetLocalBaseForRemoteMode
  <What>��ô��ļ��������������з�ʽ�£����ظ�·��
  <Params>
    -
  <Return>
  <Exception>
}
function  GetLocalBaseForRemoteMode : string;

{
  <Procedure>CreateOutputDirs
  <What>��֤�������·�����ڡ���������ڣ���������
  <Params>
    -
  <Exception>
}
function  CreateOutputDirs(const LocalBase : string):Boolean;

{
  <Procedure>BinToText
  <What>��ָ����Key���������ļ�ת��Ϊ�ı��ļ������ڲ˵��������ļ��Ľ��ܡ�
  <Params>
    -
  <Exception>
}
procedure BinToText(const BinFileName,TextFileName,Key : string);

{
  <Procedure>TextToBin
  <What>��ָ����Key���ı��ļ�ת��Ϊ�������ļ������ڲ˵��������ļ��ļ��ܡ�
  <Params>
    -
  <Exception>
}
procedure TextToBin(const TextFileName,BinFileName,Key : string);

implementation

uses KSClientConsts, Forms, IniFiles, KSStrUtils, Windows, {ShlObj,} FileCtrl, LogFile, FilterStreams;

function GetDirs(var StartDir, LocalBaseDir, BaseDir : string):TKSClientRunMode;
var
  StartIni : TIniFile;
  Mode : Integer;
  TempStartBase : string; // ���г���ĸ�·��
  TempBase : string;
begin
  // �������·��
  StartDir := ExpandPath(ExtractFilePath(Application.ExeName));
  // ���ִ��ģʽ
  try
    StartIni := TIniFile.Create(StartDir+StartIniFileName);
    try
      TempBase := ExpandPath(StartIni.ReadString(ccStart,ckBase,''));
      Mode := StartIni.ReadInteger(ccStart,ckMode,0);
      case Mode of
        0 : Result := rmStandalone;
        1 : Result := rmRemote;
        2 : Result := rmRemoteLocal;
      else
        Result := rmStandalone;
      end;
    finally
      StartIni.Free;
    end;
  except
    Result := rmStandalone;
  end;
  if SameText(Copy(StartDir,Length(StartDir)-Length(BinPath)+1,Length(BinPath)),BinPath) then
    TempStartBase := ExpandPath(Copy(StartDir,1,Length(StartDir)-Length(BinPath))) else
    TempStartBase := StartDir;
  case Result of
    rmStandalone  :
    begin
      // �������У���·���ͱ��ظ�·����ͬ�����ݳ�������·�����
      LocalBaseDir := TempStartBase;
      BaseDir := TempStartBase;
    end;
    rmRemote :
    begin
      // ���ļ��������������У���·�����ݳ�������·����ã����ظ�·����
      LocalBaseDir := ExpandPath(GetLocalBaseForRemoteMode);
      BaseDir := TempStartBase;
    end;
    rmRemoteLocal :
    begin
      // ִ�г����ڱ������棬�������ļ����������棺��·�����������ļ���ȡ�����ظ�·�����ݳ�������·�����
      LocalBaseDir := TempStartBase;
      BaseDir := TempBase; // ��������(ckBase)����ļ��������Ĺ���·��
    end;
  end;
  if not CreateOutputDirs(LocalBaseDir) then
    WriteLog('���ܴ����������Ŀ¼',lcKSClientStart);
end;

procedure GetIniFileNames(const StartDir, BaseDir : string; var StartIni, MainIni : string);
begin
  StartIni := StartDir + StartIniFileName;
  if System.ParamCount>=1 then
    MainIni:= BaseDir+ConfigPath+System.ParamStr(1) else
    MainIni:= BaseDir+ConfigPath+ConfigFileName;
end;

function  GetAppDataPath : string;
var
  PathBuffer : array[0..MAX_PATH] of Char;
begin
  FillChar(PathBuffer,MAX_PATH+1,0);
  {if SHGetSpecialFolderPath(0,@PathBuffer,CSIDL_APPDATA,True) then
  begin
    Result := PChar(@PathBuffer);
    Result := AddPathAndName(Result,AppFolder);
  end else}
  begin
    GetSystemDirectory(@PathBuffer,MAX_PATH);
    Result := PChar(@PathBuffer);
    Result := ExtractFileDrive(Result);
    Result := AddPathAndName(Result,'KSClient');
  end;
end;

function  GetLocalBaseForRemoteMode : string;
begin
  Result := GetAppDataPath;
end;

function  CreateOutputDirs(const LocalBase : string):Boolean;
var
  Temp : string;
begin
  try
    Temp := AddPathAndName(LocalBase,OutputPath);
    Result := ForceDirectories(Temp);
    Temp := AddPathAndName(LocalBase,UserPath);
    Result := ForceDirectories(Temp) and Result;
  except
    WriteException;
    Result := False;
  end;
end;

procedure BinToText(const BinFileName, TextFileName,
  Key: string);
var
  TextStream : TFileStream;
  FilterStream  : TFilterStream;
  BinStream    : TFileStream;
  Filter : IStreamFilter;
begin
  TextStream    := nil;
  FilterStream  := nil;
  BinStream    := nil;
  try
    Filter        := TXorFilter.Create(Key);
    TextStream    := TFileStream.Create(TextFileName,fmCreate);
    BinStream    := TFileStream.Create(BinFileName,fmOpenRead);
    FilterStream  := TFilterStream.Create(BinStream, Filter);

    TextStream.CopyFrom(FilterStream,0);
  finally
    TextStream.Free;
    FilterStream.Free;
    BinStream.Free;
  end;
end;

procedure TextToBin(const TextFileName, BinFileName,
  Key: string);
var
  TextStream : TFileStream;
  FilterStream  : TFilterStream;
  BinStream    : TFileStream;
  Filter : IStreamFilter;
begin
  TextStream    := nil;
  FilterStream  := nil;
  BinStream    := nil;
  try
    Filter        := TXorFilter.Create(Key);
    TextStream    := TFileStream.Create(TextFileName,fmOpenRead);
    BinStream    := TFileStream.Create(BinFileName,fmCreate);
    FilterStream  := TFilterStream.Create(BinStream, Filter);

    FilterStream.CopyFrom(TextStream,0);
  finally
    TextStream.Free;
    FilterStream.Free;
    BinStream.Free;
  end;
end;

end.

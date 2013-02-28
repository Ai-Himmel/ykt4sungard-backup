unit KSFileSystem;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSFileSystem
   <What>提供获取前台程序文件系统结构的公共函数
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

{
概念：
    StartDir - 程序启动路径
    LocalBaseDir - 程序本地根路径。本地根路径下面的子目录里面可以保存配置信息
    BaseDir - 程序根路径。可以从根路径下面的子目录里面读取程序运行需要的配置信息
}
interface

uses SysUtils, Classes;

type
  TKSClientRunMode = (
    rmStandalone, // 独立运行：根路径和本地根路径相同，根据程序启动路径获得
    rmRemote,     // 从文件服务器上面运行：根路径根据程序启动路径获得，本地根路径在
    rmRemoteLocal // 执行程序在本地上面，配置在文件服务器上面：根路径根据配置文件读取，本地根路径根据程序启动路径获得
  );

{
  <Function>GetDirs
  <What>获得程序运行的启动路径和本地根路径。
  并且根据本地根路径以及可能存在的start.ini文件确定前台程序文件系统的根路径。
  返回是否程序运行模式
  <Params>
    StartDir - 程序启动路径
    LocalBaseDir - 程序本地根路径。本地根路径下面的子目录里面可以保存配置信息
    BaseDir - 程序根路径。可以从根路径下面的子目录里面读取程序运行需要的配置信息
  <Exception>
}
function  GetDirs(var StartDir, LocalBaseDir, BaseDir : string) : TKSClientRunMode;

procedure GetIniFileNames(const StartDir, BaseDir : string; var StartIni, MainIni : string);

{
  <Function>GetLocalBaseForRemoteMode
  <What>获得从文件服务器上面运行方式下，本地根路径
  <Params>
    -
  <Return>
  <Exception>
}
function  GetLocalBaseForRemoteMode : string;

{
  <Procedure>CreateOutputDirs
  <What>保证各种输出路径存在。如果不存在，创建它们
  <Params>
    -
  <Exception>
}
function  CreateOutputDirs(const LocalBase : string):Boolean;

{
  <Procedure>BinToText
  <What>用指定的Key将二进制文件转换为文本文件。用于菜单和配置文件的解密。
  <Params>
    -
  <Exception>
}
procedure BinToText(const BinFileName,TextFileName,Key : string);

{
  <Procedure>TextToBin
  <What>用指定的Key将文本文件转换为二进制文件。用于菜单和配置文件的加密。
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
  TempStartBase : string; // 运行程序的根路径
  TempBase : string;
begin
  // 获得启动路径
  StartDir := ExpandPath(ExtractFilePath(Application.ExeName));
  // 获得执行模式
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
      // 独立运行：根路径和本地根路径相同，根据程序启动路径获得
      LocalBaseDir := TempStartBase;
      BaseDir := TempStartBase;
    end;
    rmRemote :
    begin
      // 从文件服务器上面运行：根路径根据程序启动路径获得，本地根路径在
      LocalBaseDir := ExpandPath(GetLocalBaseForRemoteMode);
      BaseDir := TempStartBase;
    end;
    rmRemoteLocal :
    begin
      // 执行程序在本地上面，配置在文件服务器上面：根路径根据配置文件读取，本地根路径根据程序启动路径获得
      LocalBaseDir := TempStartBase;
      BaseDir := TempBase; // 根据配置(ckBase)获得文件服务器的共享路径
    end;
  end;
  if not CreateOutputDirs(LocalBaseDir) then
    WriteLog('不能创建本地输出目录',lcKSClientStart);
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

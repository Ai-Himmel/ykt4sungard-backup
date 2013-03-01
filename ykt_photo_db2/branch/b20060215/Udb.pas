unit Udb;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB,IniFiles;

type
  Tdm = class(TDataModule)
    ADOConnection1: TADOConnection;
    procedure DataModuleCreate(Sender: TObject);
  private
    { Private declarations }
    sconnstring:string;  //连接数据库字符串
  public
    { Public declarations }
  end;

var
  dm: Tdm;

implementation

uses UtConfigs;

{$R *.DFM}

procedure Tdm.DataModuleCreate(Sender: TObject);
var
  inifile:TIniFile;
  sfilename:string;
begin
  sfilename:= ExtractFilePath(Paramstr(0)) + 'file.ini';
  inifile:= TIniFile.Create(sfilename);
  sconnstring:=inifile.ReadString('DataBase','conn',sconnstring);
  if ADOConnection1.Connected then
    ADOConnection1.Connected:=false;
  try
  ADOConnection1.ConnectionString:= sconnstring;
    ADOConnection1.Connected:=True;
  except
    ShowMessage('数据库连接失败，请检查！');
  end;
end;

end.


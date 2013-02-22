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
    sconnstring:string;
  public
    { Public declarations }
  end;

var
  dm: Tdm;

implementation

{$R *.DFM}

procedure Tdm.DataModuleCreate(Sender: TObject);
var
  inifile:TIniFile;
  sfilename:string;
begin
  sfilename:= ExtractFilePath(Paramstr(0)) + 'config.ini';
  inifile:= TIniFile.Create(sfilename);
  sconnstring:=inifile.ReadString('DataBase','conn',sconnstring);

  ADOConnection1.Connected:=False;
  try
    ADOConnection1.ConnectionString:=sconnstring;
    ADOConnection1.Connected:=true;
  except
    ShowMessage('连接失败，请检查配置文件是否正确！');
    exit;
  end;

end;

end.

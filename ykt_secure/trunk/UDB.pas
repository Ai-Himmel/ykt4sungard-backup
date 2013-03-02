unit UDB;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB, IniFiles;

type
  TFrmDB = class(TDataModule)
    SecureConnect: TADOConnection;
  private
    { Private declarations }
    procedure LoadADOConfig;
  public
    { Public declarations }
    constructor Create(AOwner : TComponent);override;


  end;

var
  FrmDB: TFrmDB;

implementation

{$R *.DFM}

{ TFrmDB }

constructor TFrmDB.Create(AOwner: TComponent);
begin
  inherited;
  LoadADOConfig;
end;

procedure TFrmDB.LoadADOConfig;
const
  //dbprovider = 'Provider=IBMDADB2.1;Password=%s;User ID=%s;Data Source=%s;Location=%s;Mode=ReadWrite;Persist Security Info=True';
  dbprovider = 'Provider=MSDASQL.1;Password=%s;Persist Security Info=True;User ID=%s;Data Source=%s';
var
  iniFile : TIniFile;
  providerstr,configFile: string;
  pswd,user,datasource,location : string;
begin
  configFile := ExtractFilePath(Application.ExeName) +  '\config.ini';
  iniFile := TIniFile.Create(configFile);
  pswd := iniFile.ReadString('DB','PSWD','');
  user := iniFile.ReadString('DB','USER','');
  datasource := iniFile.ReadString('DB','DATASOURCE','');
  location := iniFile.ReadString('DB','LOCATION','');
  providerstr := Format(dbprovider,[pswd,user,datasource,location]);
  if providerstr = '' then
  begin
    ShowMessage('没有指定数据库，请重试！');
    Application.Terminate;
  end
  else
  begin
    //ShowMessage(providerstr);
    SecureConnect.ConnectionString := providerstr;
    try
      SecureConnect.Open;
    except
      ShowMessage('连接数据库失败！');
      Application.Terminate;
    end;
    if not SecureConnect.Connected then
    begin
      ShowMessage('连接数据库失败！');
      Application.Terminate;
    end;
  end;
end;

end.


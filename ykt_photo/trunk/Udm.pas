unit Udm;

interface

uses
  SysUtils, Classes, DB, ADODB,Dialogs;

type
  Tfrmdm = class(TDataModule)
    conn: TADOConnection;
    procedure DataModuleCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmdm: Tfrmdm;

implementation

uses uCommon,TLoggerUnit;

{$R *.dfm}

procedure Tfrmdm.DataModuleCreate(Sender: TObject);
begin
  if conn.Connected then
    conn.Connected:=false;
  try
    //TLogger.GetInstance.Debug('连接数据库'+connstr);
    conn.ConnectionString:= connStr;
    conn.Connected:=True;
  except
    on e:Exception do
    begin
      TLogger.GetInstance.Debug('连接数据库失败--['+connstr+']Err--'+e.Message);
      ShowMessage('数据库连接失败--'+e.Message);
    end;
  end;

end;

end.

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
    //TLogger.GetInstance.Debug('�������ݿ�'+connstr);
    conn.ConnectionString:= connStr;
    conn.Connected:=True;
  except
    on e:Exception do
    begin
      TLogger.GetInstance.Debug('�������ݿ�ʧ��--['+connstr+']Err--'+e.Message);
      ShowMessage('���ݿ�����ʧ��--'+e.Message);
    end;
  end;

end;

end.

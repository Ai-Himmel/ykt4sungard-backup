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

uses uCommon;

{$R *.dfm}

procedure Tfrmdm.DataModuleCreate(Sender: TObject);
begin
  if conn.Connected then
    conn.Connected:=false;
  try
    conn.ConnectionString:= connStr;
    conn.Connected:=True;
  except
    on e:Exception do
    begin
      ShowMessage('���ݿ�����ʧ�ܣ��������ÿ��Ƿ���ȷ('+connstr+')--'+e.Message);
    end;
  end;

end;

end.

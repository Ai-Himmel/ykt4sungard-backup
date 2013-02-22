unit Udb;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB,IniFiles;

type
  Tdm = class(TDataModule)
    ADOConnection1: TADOConnection;
    qryprint: TADOQuery;
    procedure DataModuleCreate(Sender: TObject);
  private
    { Private declarations }
    sconnstring:string;
  public
    { Public declarations }
    procedure makecard(empNo:string);
  end;

var
  dm: Tdm;

implementation

uses UConfigs;

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
    ShowMessage('����ʧ�ܣ����������ļ��Ƿ���ȷ��');
    exit;
  end;

end;

{-------------------------------------------------------------------------------
  ������:    Tdm.makecard�ƿ�����
  ����:      ����ΰ
  ����:      2005.11.05
  ����:      empNo: string
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure Tdm.makecard(empNo: string);
var
  sqlstr:string;
begin
  sqlstr:='update '+ PhotoTableName +' set '+ifcard +'=1,'+makecarddate+'=';
  sqlstr:=sqlstr+#39+formatdatetime('yyyy-mm-dd',Date)+#39+' where '+PersonNo+'='+#39+empNo+#39;
  qryprint.Close;
  qryprint.SQL.Clear;
  qryprint.SQL.Add(sqlstr);
  qryprint.Prepared;
  qryprint.ExecSQL;
end;

end.

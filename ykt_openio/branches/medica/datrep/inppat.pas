unit inppat;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, db, Ora, MemDS, DBAccess, commu, jpeg, Grids,
  FR_DSet, FR_Class;

type
  Tinppatfrm = class(TForm)
    Panel1: TPanel;
    title: TPanel;
    labletaitle: TLabel;
    Panel2: TPanel;
    Panel3: TPanel;
    Panel4: TPanel;
    ucCardNoname: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    ucCardNo: TLabel;
    ucName: TLabel;
    ucSexNo: TLabel;
    ucIdentifyNo: TLabel;
    ucDepartmentNo: TLabel;
    STATUS: TLabel;
    DeadLineDate: TLabel;
    Panel5: TPanel;
    Panel6: TPanel;
    Image1: TImage;
    Memo1: TMemo;
    Panel7: TPanel;
    Label9: TLabel;
    Panel8: TPanel;
    Label10: TLabel;
    Panel9: TPanel;
    Label11: TLabel;
    changgemoney: TEdit;
    cancel: TButton;
    Memo2: TMemo;
    readMoney: TLabel;
    noname: TLabel;
    noid: TLabel;

    procedure procstdcardinf;
    procedure procIniForm;
    procedure cancelClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);


  private
    { Private declarations }
  public
    { Public declarations }
    studno, VOUCHERNO: string;
    Balance: integer;
  end;

var
  inppatfrm: Tinppatfrm;
  medicaldtl: Tmedicaldtl;
  imagestream: Tmemorystream;
  DBQuery: TOraQuery;
  tempDBQuery: TOraQuery;
  jpg: TJPEGImage;
  pic: TfrPictureView;
implementation

{$R *.dfm}


procedure Tinppatfrm.procstdcardinf;
var
  sSql: string;

begin
  ucCardNo.Caption := studno;
  sSql := 'select e.*,A.CUSTID,A.STATUS,b.STUEMPNO,A.CUSTID,A.CARDNO,a.EXPIREDATE,B.CUSTNAME,d.deptname,' +
    'B.SEX,C.CUSTTYPENAME  from T_CARD A,T_CUSTOMER B, T_custtype C ,t_dept d,T_medicaldtl e where ' +
    ' A.CUSTID=B.CUSTID and  b.CUSTTYPE=c.CUSTTYPE AND b.deptcode=d.deptcode  AND b.STUEMPNO=e.stuempno '+
    'and e.VOUCHERNO=' + ''''+VOUCHERNO+'''';
  procGetIniInfo;
  if funcConnectDB() then
  begin
    if debug = 'true' then
      writelog(sSql);
    funcSelectSql(sSql, DBQuery);
  end;
  if DBQuery.RecordCount < 1 then
  begin
    FuncShowMessage(handle, '数据库中没有找到此学工号信息！', 2);

  end
  else
  begin
    readmoney.Caption := floattostr(medicaldtl.money / 100);
    medicaldtl.STATUS := DBQuery.FieldByName('STATUS').AsString;
    if medicaldtl.STATUS = '1' then
      STATUS.Caption := '正常'
    else
      STATUS.Caption := '注销';
    ucName.Caption := DBQuery.FieldByName('CUSTNAME').AsString;
    ucIdentifyNo.Caption := DBQuery.FieldByName('CUSTTYPENAME').AsString;
    ucDepartmentNo.Caption := DBQuery.FieldByName('deptname').AsString;
    DeadLineDate.Caption := DBQuery.FieldByName('EXPIREDATE').AsString;
    noid.Caption := DBQuery.FieldByName('VOUCHERNO').AsString;
    if (DBQuery.FieldByName('SEX').AsString = '1') then
      ucSexNo.Caption := '男'
    else
      ucSexNo.Caption := '女';
    changgemoney.Text := floattostr(DBQuery.FieldByName('TRANSAMT').asinteger/100);
    memo1.Text := DBQuery.FieldByName('MEDICINES').AsString;
    memo2.Text := DBQuery.FieldByName('MEDICALINFO').AsString;
    SSQL := 'select photo from T_PHOTO where STUEMPNO=' + ''''+studno+'''';
    if funcConnectDB() then
    begin
      funcSelectSql(sSql, tempDBQuery);
    end;
    if tempDBQuery.RecordCount < 1 then
    begin
    end
    else
    begin
      try
        imagestream.Position := 0;
        TBlobField(tempDBQuery.FieldByName('PHOTO')).SaveToStream(imagestream);
        imagestream.Position := 0;
        jpg.LoadFromStream(imagestream);
        Image1.Picture.Assign(jpg);
        pic.Picture.Assign(jpg);
      except
      end;
    end;
  end;
end;

procedure Tinppatfrm.procIniForm;
var
  i: integer;
begin
  ucCardNo.Caption := '';
  ucName.Caption := '';
  ucSexNo.Caption := '';
  ucIdentifyNo.Caption := '';
  ucDepartmentNo.Caption := '';
  STATUS.Caption := '';
  readMoney.Caption := '';
  DeadLineDate.Caption := '';
  changgemoney.Text := '';
  Memo1.Clear;
  Memo2.Clear;
end;

procedure Tinppatfrm.cancelClick(Sender: TObject);
begin
  close;
end;

procedure Tinppatfrm.FormShow(Sender: TObject);
begin
  procIniForm;
  procstdcardinf;

end;



procedure Tinppatfrm.FormCreate(Sender: TObject);
begin
  procIniForm;
  DBQuery := TOraQuery.Create(nil);
  DBQuery.Connection := DBConn;
  tempDBQuery := TOraQuery.Create(nil);
  tempDBQuery.Connection := DBConn;
  jpg := TJPEGImage.Create;
  imagestream := Tmemorystream.Create;
end;

procedure Tinppatfrm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  DBQuery.Free;
  tempDBQuery.Free;
  imagestream.Free;
  pic.Free;
end;

end.


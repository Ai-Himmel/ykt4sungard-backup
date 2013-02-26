unit inppat;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, db, Ora, MemDS, DBAccess, commu, jpeg, Grids,
  FR_DSet, FR_Class, Mask, Buttons;

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
    readMoney: TLabel;
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
    print: TButton;
    cancel: TButton;
    redcard: TButton;
    frReport1: TfrReport;
    Memo2: TMemo;
    changemoney: TEdit;
    Label12: TLabel;
    noid: TLabel;
    Bpush: TButton;

    procedure procstdcardinf;
    procedure BpushClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure procIniForm;
    procedure procintinf;
    function funcSavemedic(var AID: string): boolean;
    procedure cancelClick(Sender: TObject);
    procedure redcardClick(Sender: TObject);
    procedure printClick(Sender: TObject);
    procedure getREFNO;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);

  private
    aid: string;
    { Private declarations }
  public
    { Public declarations }
    CardNo: string;
    Balance: integer;
  end;

var
  inppatfrm: Tinppatfrm;
  medicaldtl: Tmedicaldtl;
  imagestream: Tmemorystream;
  DBQuery: TOraQuery;
  jpg: TJPEGImage;
  pic: TfrPictureView;
implementation

{$R *.dfm}

procedure Tinppatfrm.getREFNO;
var
  ssql: string;
  sysdate: string;
  paraval: string;
  termseqno: string;
begin
  sSql := 'select sysdate,paraval from t_syspara where paraid=2';
  procGetIniInfo;
  if funcConnectDB() then
  begin
    DBQuery := TOraQuery.Create(nil);
    DBQuery.Connection := DBConn;
    funcSelectSql(sSql, DBQuery);
  end;
  sysdate := DBQuery.FieldByName('sysdate').asstring;
  paraval := DBQuery.FieldByName('paraval').asstring;
  ssql := 'select termseqno from T_SEQNOCTL where termid=''-20''';
  if funcConnectDB() then
  begin
    if DBQuery = nil then
      DBQuery := TOraQuery.Create(nil);
    DBQuery.Connection := DBConn;
    funcSelectSql(sSql, DBQuery);
  end;
  termseqno := trim(DBQuery.FieldByName('termseqno').asstring);
  if termseqno = '' then
  begin
    sSql := 'insert into t_seqnoctl(termid,termseqno,accdate)' +
      ' values(''-20'',''1'',to_char(sysdate,''yyyymmdd''))';
    procGetIniInfo;
    if funcConnectDB() then
    begin
      DBQueryTmp := TOraQuery.Create(nil);
      DBQueryTmp.Connection := DBConn;
      funcExcuteSql(sSql, DBQueryTmp);
    end;
    medicaldtl.REFNO := formatdatetime('yyyymmdd', strtodatetime(sysdate)) + funcGetNewID('0', 6);
  end
  else
  begin
    if paraval > formatdatetime('yyyymmdd', strtodatetime(sysdate)) then
    begin
      termseqno := funcGetNewID('0', 6);
      medicaldtl.REFNO := paraval + termseqno;
    end
    else
    begin
      termseqno := funcGetNewID(termseqno, 6);
      medicaldtl.REFNO := formatdatetime('yyyymmdd', strtodatetime(sysdate)) + termseqno;
    end;
  end;
  sSql := 'update t_seqnoctl set termseqno=' + termseqno + ' where termid=''-20''';
  if funcConnectDB() then
  begin

    funcExcuteSql(sSql, DBQueryTmp);
  end;
end;

function Tinppatfrm.funcSavemedic(var AID: string): boolean;
var
  i: integer;
  ssql: string;
  hand: integer;
  nFlowNo: integer;
  inpmoney: integer;

begin

  if trim(medicaldtl.STUEMPNO) = '' then
  begin
    FuncShowMessage(handle, '学工号不能为空！', 2);
    exit;
  end;
  medicaldtl.MEDICINES := memo2.Text;

  for i := 0 to Memo1.Lines.Count - 1 do
  begin
    medicaldtl.MEDICALINFO := medicaldtl.MEDICALINFO + Memo1.Lines[i];
  end;
  inpmoney := trunc(Fun_CurrGetValue(changemoney.Text) * 100);
  try
    SMT_ControlBuzzer();
    hand := SMT_PacketDelMomey(inpmoney, nFlowNo);
    if (hand = 0) or (hand = -7) then
    begin
      if hand = 0 then
      begin
        medicaldtl.STATUS := '3';
      end;
      if hand = -7 then
      begin
        medicaldtl.STATUS := '2';
      end;
    end
    else
      medicaldtl.STATUS := '0';
  except
  end;
  medicaldtl.DEVPHYID := DEVPHYID;
  medicaldtl.VOUCHERNO := aid;
  getREFNO;
  medicaldtl.REMARK := ' ';
  medicaldtl.OPERCODE := PtUser.GetUserName;
  sSql := 'insert into T_medicaldtl(REFNO,CUSTID,CUSTNAME,STUEMPNO,VOUCHERNO,MEDICINES,MEDICALINFO,CARDNO,TRANSDATE,TRANSTIME,TRANSTYPE,TRANSAMT,DEVPHYID,OPERCODE,STATUS,REMARK,DEVSEQNO)' +
    ' values(''' + medicaldtl.REFNO + ''',''' + inttostr(medicaldtl.CUSTID) + ''',' + ':f1' + ',''' + trim(medicaldtl.STUEMPNO) + ''',''' + medicaldtl.VOUCHERNO + ''',' + ':f2,:f3,' + inttostr(medicaldtl.CARDNO) + ',' +
    '' + FormatdateTime('yyyymmdd', now()) + ',''' + FormatdateTime('hhss', now) + ''',' + inttostr(medicaldtl.TRANSTYPE) + ',' + floattostr(inpmoney) + ',''' + medicaldtl.DEVPHYID + ''',''' + medicaldtl.OPERCODE + ''',' +
    '''' + medicaldtl.STATUS + ''',''' + medicaldtl.REMARK + ''',''' + inttostr(nFlowNo) + ''')';
  procGetIniInfo;
  writelog(sSql);
  if funcConnectDB() then
  begin
    DBQueryTmp := TOraQuery.Create(nil);
    DBQueryTmp.Connection := DBConn;
    try
      DBQueryTmp.SQL.Text := sSql;
      DBQueryTmp.Params[0].AsWideString := trim(medicaldtl.CUSTNAME);
      DBQueryTmp.Params[1].AsWideString := trim(memo2.Text);
      DBQueryTmp.Params[2].AsWideString := trim(medicaldtl.MEDICALINFO);
      if debug = 'true' then
        writelog(sSql);
      funcExcuteSqlForChinese(DBQueryTmp);
      FuncShowMessage(handle, '提交成功！', 0);
    except
      FuncShowMessage(handle, '提交失败！', 2);
    end;
  end;
end;

procedure Tinppatfrm.procstdcardinf;
var
  sSql: string;
begin
  sSql := 'select A.CUSTID,A.STATUS,b.STUEMPNO,A.CARDNO,a.EXPIREDATE,B.CUSTNAME,d.deptname,' +
    'B.SEX,C.CUSTTYPENAME  from T_CARD A,T_CUSTOMER B, T_custtype C ,t_dept d where ' +
    ' A.CUSTID=B.CUSTID and  b.CUSTTYPE=c.CUSTTYPE  AND b.deptcode=d.deptcode  AND ' +
    ' b.STUEMPNO= ' + '''' + trim(medicaldtl.STUEMPNO) + '''';
  procGetIniInfo;
  if funcConnectDB() then
  begin
    DBQuery := TOraQuery.Create(nil);
    DBQuery.Connection := DBConn;
    if debug = 'true' then
      writelog(sSql); ;
    funcSelectSql(sSql, DBQuery);

  end;
  if DBQuery.RecordCount < 1 then
  begin
    FuncShowMessage(handle, '数据库中没有找到此学工号信息！', 2);

  end
  else
  begin
    medicaldtl.CUSTID := DBQuery.FieldByName('CUSTID').asinteger;
    medicaldtl.STATUS := DBQuery.FieldByName('STATUS').AsString;
    if medicaldtl.STATUS = '1' then
    begin
      STATUS.Caption := '正常';
      Bpush.Enabled := true;
      Memo2.Enabled := true;
      Memo1.Enabled := true;
    end
    else
    begin
      Memo1.Enabled := false;
      Memo2.Enabled := false;
      Bpush.Enabled := false;
      STATUS.Caption := '注销';
    end;
    medicaldtl.CARDNO := DBQuery.FieldByName('CARDNO').asinteger;
    medicaldtl.CUSTNAME := DBQuery.FieldByName('CUSTNAME').AsString;
    medicaldtl.CUSTTYPENAME := DBQuery.FieldByName('CUSTTYPENAME').AsString;
    ucName.Caption := medicaldtl.CUSTTYPENAME;
    ucDepartmentNo.Caption := DBQuery.FieldByName('deptname').AsString;
    DeadLineDate.Caption := DBQuery.FieldByName('EXPIREDATE').AsString;
    if (DBQuery.FieldByName('SEX').AsString = '1') then
      medicaldtl.sex := '男'
    else
      medicaldtl.sex := '女';
    ucIdentifyNo.Caption := medicaldtl.CUSTNAME;
  end;
  SSQL := 'select photo from T_PHOTO where STUEMPNO=' + '''' + trim(medicaldtl.STUEMPNO) + '''';
  if debug = 'true' then
    writelog(sSql);
  funcSelectSql(sSql, DBQuery);
  if DBQuery.RecordCount < 1 then
  begin
  end
  else
  begin
    imagestream := Tmemorystream.Create;

    try
      jpg := TJPEGImage.Create;
      imagestream.Position := 0;
      TBlobField(DBQuery.FieldByName('PHOTO')).SaveToStream(imagestream);
      imagestream.Position := 0;
      jpg.LoadFromStream(imagestream);
      Image1.Picture.Assign(jpg);
      pic.Picture.Assign(jpg);
    except
    end;
  end;
  sSql := 'select max(to_number(VOUCHERNO))+1 as VOUCHERNOmax from T_MEDICALDTL';
  procGetIniInfo;
  if funcConnectDB() then
  begin

    DBQuery.Close;
    funcSelectSql(sSql, DBQuery);
  end;
  if DBQuery.FieldByName('VOUCHERNOmax').asstring = '' then
    aid := funcGetNewID('0', 5)
  else
    aid := DBQuery.FieldByName('VOUCHERNOmax').AsString;
  noid.Caption := aid;
  imagestream.Free;
  jpg.Free;
end;





procedure Tinppatfrm.BpushClick(Sender: TObject);
begin


  funcSavemedic(aid);

end;

procedure Tinppatfrm.FormCreate(Sender: TObject);
var
  hand: integer;
begin
  procIniForm;
  procintinf;
  DBQuery := TOraQuery.Create(nil);
  DBQuery.Connection := DBConn;
  DBQueryTmp := TOraQuery.Create(nil);
  DBQueryTmp.Connection := DBConn;

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
  changemoney.Text := '';
  Memo1.Clear;
  Memo2.Clear;
  medicaldtl.REFNO := ' ';
  medicaldtl.CUSTID := 0;
  medicaldtl.CUSTNAME := ' ';
  medicaldtl.STUEMPNO := ' ';
  medicaldtl.sex := ' ';
  medicaldtl.CUSTTYPENAME := ' ';
  medicaldtl.VOUCHERNO := ' ';
  medicaldtl.MEDICINES := ' ';
  medicaldtl.MEDICALINFO := ' ';
  medicaldtl.CARDNO := 0;
  medicaldtl.TRANSDATE := ' ';
  medicaldtl.TRANSTIME := ' ';
  medicaldtl.TRANSTYPE := 0;
  medicaldtl.money := 0;
  medicaldtl.DEVPHYID := '';
  medicaldtl.OPERCODE := ' ';
  medicaldtl.STATUS := ' ';
  medicaldtl.REMARK := ' ';
  noid.Caption := ' ';

end;

procedure Tinppatfrm.procintinf;
begin
  ucCardNo.Caption := medicaldtl.STUEMPNO;
  ucName.Caption := medicaldtl.CUSTNAME;
  ucSexNo.Caption := medicaldtl.sex;
  ucIdentifyNo.Caption := medicaldtl.CUSTTYPENAME;
  readmoney.Caption := floattostr(medicaldtl.money / 100);
end;

procedure Tinppatfrm.cancelClick(Sender: TObject);
begin
  close;
end;

procedure Tinppatfrm.redcardClick(Sender: TObject);
var
  hand: integer;
  inpmoney: integer;
begin
  try
    hand := -1;
    procIniForm;
    SMT_ControlBuzzer();
    setlength(cardno, 20);
    hand := SMT_ReadCardNo(pchar(cardno));
    if hand <> 0 then
    begin
      FuncShowMessage(handle, '读取学工号失败！', 2);
      exit;
    end
    else
    begin
      medicaldtl.STUEMPNO := copy(trim(cardno), 1, 12);
    end;
    hand := SMT_ReadBalance(Balance);
    if hand <> 0 then
    begin
      FuncShowMessage(handle, '读取金额失败！', 2);
      exit;
    end
    else
    begin
      medicaldtl.money := Balance;
    end;
  except
    FuncShowMessage(handle, '请确认是否打开串口！', 2);
    exit;
  end;
  procstdcardinf;
  procintinf;
end;




procedure Tinppatfrm.printClick(Sender: TObject);
var
  tempStream: TMemoryStream;

begin

  if frReport1.LoadFromFile(extractfilepath(application.ExeName) + 'medac.frf') then begin
    frReport1.FindObject('ucName').Memo.Text := ucName.Caption;
    frReport1.FindObject('ucCardNo').Memo.Text := ucCardNo.Caption;
    frReport1.FindObject('ucName').Memo.Text := ucName.Caption;
    frReport1.FindObject('ucSexNo').Memo.Text := ucSexNo.Caption;
    frReport1.FindObject('ucIdentifyNo').Memo.Text := ucIdentifyNo.Caption;
    frReport1.FindObject('ucDepartmentNo').Memo.Text := ucDepartmentNo.Caption;
    frReport1.FindObject('STATUS').Memo.Text := STATUS.Caption;
    frReport1.FindObject('Money').Memo.Text := floattostr(medicaldtl.money / 100);
    frReport1.FindObject('STATUS').Memo.Text := STATUS.Caption;
    frReport1.FindObject('DeadLineDate').Memo.Text := DeadLineDate.Caption;
    frReport1.FindObject('medmemo').Memo.Text := memo1.Text;
    frReport1.FindObject('medicine').Memo.Text := memo2.Text;
    frReport1.FindObject('totalmoney').Memo.Text := floattostr(Fun_CurrGetValue(changemoney.Text));
    frReport1.FindObject('noid').Memo.Text := aid + ' ';
    frReport1.ShowReport;
  end;


end;






procedure Tinppatfrm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  DBQueryTmp.Free;
  DBQuery.Free;
  pic.Free;
end;

end.


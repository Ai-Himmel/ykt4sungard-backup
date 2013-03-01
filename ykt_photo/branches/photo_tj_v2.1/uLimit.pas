unit uLimit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, GridsEh, DBGridEh, StdCtrls, Buttons, DB, ADODB;

type
  TfrmLimit = class(TForm)
    pnl1: TPanel;
    dbgrdhDb: TDBGridEh;
    lbl1: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    grpLimit: TGroupBox;
    edtCode: TEdit;
    edtName: TEdit;
    edtBegin: TEdit;
    edtEnd: TEdit;
    edtpwd: TEdit;
    edtRepwd: TEdit;
    chkStat: TCheckBox;
    chkQuery: TCheckBox;
    chkLimit: TCheckBox;
    chkImport: TCheckBox;
    chkExport: TCheckBox;
    chkAddCust: TCheckBox;
    chkEditCust: TCheckBox;
    chkStuPrint: TCheckBox;
    chkEmpPrint: TCheckBox;
    chkDelPhoto: TCheckBox;
    chkSavePhoto: TCheckBox;
    chkEnabled: TCheckBox;
    btnAdd: TBitBtn;
    btnSave: TBitBtn;
    btnExit: TBitBtn;
    qryQuery: TADOQuery;
    dsQuery: TDataSource;
    BitBtn1: TBitBtn;
    CheckBox1: TCheckBox;
    chkPhotoCopy: TCheckBox;
    procedure btnExitClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure qryQueryAfterScroll(DataSet: TDataSet);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
    operType:string;
    procedure queryOperList();
    procedure fillDataInfo();
    function getSelect(limitStr:string;iPos:Integer):Boolean;
    function selectForLimit():string;
    procedure addLimitInfo();
    procedure editLimitInfo();
    procedure clearSelect();
    function ifHaveOper(operCode:string):Boolean;
    procedure delLimitInfo();
    function FormatDate(str: string): boolean;
  public
    { Public declarations }
  end;

var
  frmLimit: TfrmLimit;

implementation

uses AES, ElAES, uCommon, Udm;

{$R *.dfm}

procedure TfrmLimit.btnExitClick(Sender: TObject);
begin
  close();
end;

procedure TfrmLimit.fillDataInfo;
var
  i:Integer;
  itag:Integer;
begin
  clearSelect();
  operType:='edit';
  edtCode.Enabled:=False;
  if qryQuery.Active=False then
    queryOperList();
  edtBegin.Text:=qryQuery.fieldbyname(lmtBeginDate).AsString;
  edtEnd.Text:=qryQuery.fieldbyname(lmtEndDate).AsString;
  edtCode.Text:=qryQuery.fieldbyname(lmtOperCode).AsString;
  edtName.Text:=qryQuery.fieldbyname(lmtOperName).AsString;
  edtpwd.Text:=DecryptString(qryQuery.fieldbyname(lmtpwd).AsString,'ksykt123');
  edtRepwd.Text:=edtpwd.Text;
  for i := 0 to grpLimit.ControlCount-1 do
  begin
    if grpLimit.Controls[i] is TCheckBox then
    begin
      itag:=TCheckBox(grpLimit.Controls[i]).Tag;
      TCheckBox(grpLimit.Controls[i]).Checked:=getSelect(qryQuery.fieldbyname(lmtLimit).AsString,itag);
    end;
  end;
end;

procedure TfrmLimit.FormShow(Sender: TObject);
begin
  dbgrdhDb.Columns[0].FieldName:=lmtOperCode;
  dbgrdhDb.Columns[1].FieldName:=lmtOperName;
  edtBegin.Text:=FormatDateTime('yyyymmddhhmmss',Now());
  edtEnd.Text:=FormatDateTime('yyyymmddhhmmss',Now());
  queryOperList();
end;

function TfrmLimit.getSelect(limitStr: string;iPos:Integer): Boolean;
var
  ss:string;
begin
  ss:=Copy(limitStr,iPos+1,1);
  if ss='0' then
    Result:=False
  else 
    Result:=True;
end;

procedure TfrmLimit.queryOperList;
var
  sqlStr:string;
begin
  sqlStr:=qryOperSql('','');
  qryQuery.Close;
  qryQuery.SQL.Clear;
  qryQuery.SQL.Add(sqlStr);
  qryQuery.Open;
  if not qryQuery.IsEmpty then
    fillDataInfo();
end;

procedure TfrmLimit.btnAddClick(Sender: TObject);
var
  i:Integer;
begin
  operType:='add';
  edtCode.Enabled:=True;
  clearSelect;
  for i := 0 to pnl1.ControlCount-1 do
    if pnl1.Controls[i] is TEdit then
      TEdit(pnl1.Controls[i]).Text:='';
  edtBegin.Text:=FormatDateTime('yyyymmddhhmmss',Now());
  edtEnd.Text:=FormatDateTime('yyyymmddhhmmss',Now());

end;

{-------------------------------------------------------------------------------
  ������:    TfrmLimit.selectForLimit��ѡ���Ȩ����Ϣ����ַ���
  ����:      hanjiwei
  ����:      2007.01.19
  ����:      ��
  ����ֵ:    string
-------------------------------------------------------------------------------}
function TfrmLimit.selectForLimit: string;
var
  i:Integer;
  itag:Integer;
  limitStr:string;
  sIfUse :string;       //�Ƿ����
  slimit :string ;      //Ȩ�޹���
  sphotoStat :string;   //����ͳ��
  sphotoQuery :string;  //���ղ�ѯ
  simport :string;      //������Ƭ
  sexport :string;      //������Ƭ
  saddCust :string;     //�����Ա��Ϣ
  sEditCust :string;    //�޸���Ա��Ϣ

  sstuPrint :string;    //ѧ������ӡ
  sempPrint :string;    //��ʦ����ӡ
  sdelphoto :string;    //ɾ����Ƭ
  ssavephoto :string;   //������Ƭ
  scustImport :string;  //��Ա��Ϣ��������
  sphotocopy :string;   //��Ƭ����
  procedure chkLimit(itag:Integer;lmt:string);
  begin
    case itag of
      0: sIfUse:=lmt;
      1: slimit:=lmt;
      2: sphotoStat:=lmt;
      3: sphotoQuery:=lmt;
      4: simport:=lmt;
      5: sexport:=lmt;
      6: saddCust:=lmt;
      7: sEditCust:=lmt;
      8: sstuPrint:=lmt;
      9: sempPrint:=lmt;
      10: sdelphoto:=lmt;
      11: ssavephoto:=lmt;
      12: scustImport:=lmt;
      13: sphotocopy := lmt;
    else

    end;
  end;
begin
  limitStr:='';
  for i := 0 to grpLimit.ControlCount-1 do
  begin
    itag:=TCheckBox(grpLimit.Controls[i]).Tag;
    if grpLimit.Controls[i] is TCheckBox then
    begin
      if TCheckBox(grpLimit.Controls[i]).Checked then
      begin
        chkLimit(itag,'1');
      end
      else
      begin
        chkLimit(itag,'0');
      end;
    end;
  end;
  limitStr := sIfUse+slimit+sphotoStat+sphotoQuery+simport+sexport+saddCust+sEditCust;
  limitStr := limitStr+sstuPrint+sempPrint+sdelphoto+ssavephoto+scustImport+sphotocopy;
  Result:=Trim(limitStr);
end;

procedure TfrmLimit.addLimitInfo;
var
  operQuery:TADOQuery;
  operStr:string;
begin
  if ifHaveOper(Trim(edtCode.Text)) then
  begin
    ShowMessage('�õ�¼���Ѿ����ڣ����������룡');
    edtCode.SetFocus;
    Exit;
  end;
  operStr:='insert into '+tblLimit+'('+lmtOperCode+','+lmtOperName+','+lmtBeginDate+',';
  operStr:=operStr+lmtEndDate+','+lmtpwd+','+lmtLimit+')values(';
  operStr:=operStr+#39+edtcode.Text+#39+',';
  operStr:=operStr+#39+edtName.Text+#39+',';
  operStr:=operStr+#39+edtbegin.Text+#39+',';
  operStr:=operStr+#39+edtend.Text+#39+',';
  operStr:=operStr+#39+EncryptString(trim(edtpwd.Text),'ksykt123')+#39+',';
  operStr:=operStr+#39+selectForLimit()+#39+')';
  operQuery:=nil;
  try
    operQuery:=TADOQuery.Create(nil);
    operQuery.Connection:=frmdm.conn;

    operQuery.Close;
    operQuery.SQL.Clear;
    operQuery.SQL.Add(operStr);

    frmdm.conn.BeginTrans;
    try
      operQuery.ExecSQL;
      frmdm.conn.CommitTrans;
      if Application.MessageBox(PChar('������Ա��Ϣ�ɹ������Ƿ�Ҫ������ӣ�'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idyes then
        btnAdd.Click;
    except
      on e:Exception do
      begin
        frmdm.conn.RollbackTrans;
        ShowMessage('�����Ա��Ϣʧ�ܣ�����ԭ��--'+e.Message);
      end;
    end;
  finally
    operQuery.Destroy;
  end;
end;

procedure TfrmLimit.editLimitInfo;
var
  operQuery:TADOQuery;
  operStr:string;
begin
  operStr:='update '+tblLimit+' set '+lmtOperName+'='+#39+edtName.Text+#39+',';
  operStr:=operStr+lmtBeginDate+'='+#39+edtBegin.Text+#39+',';
  operStr:=operStr+lmtEndDate+'='+#39+edtEnd.Text+#39+',';
  operStr:=operStr+lmtpwd+'='+#39+EncryptString(trim(edtpwd.Text),'ksykt123')+#39+',';
  operStr:=operStr+lmtLimit+'='+#39+selectForLimit()+#39+' where ';
  operStr:=operStr+lmtOperCode+'='+#39+edtCode.Text+#39;
  operQuery:=nil;
  try
    operQuery:=TADOQuery.Create(nil);
    operQuery.Connection:=frmdm.conn;

    operQuery.Close;
    operQuery.SQL.Clear;
    operQuery.SQL.Add(operStr);
    frmdm.conn.BeginTrans;
    try
      operQuery.ExecSQL;
      frmdm.conn.CommitTrans;
      ShowMessage('������Ա��Ϣ�ɹ���');
    except
      frmdm.conn.RollbackTrans;
      ShowMessage('������Ա��Ϣʧ�ܣ�����ԭ��');
    end;
  finally
    operQuery.Destroy;
  end;
end;

procedure TfrmLimit.btnSaveClick(Sender: TObject);
begin
  if Trim(edtCode.Text)='' then
  begin
    ShowMessage('��¼������Ϊ�գ������룡');
    edtCode.SetFocus;
    Exit;
  end;
  if Trim(edtpwd.Text)='' then
  begin
    ShowMessage('�������벻��Ϊ�գ�');
    edtpwd.SetFocus;
    Exit;
  end;
  if Trim(edtpwd.Text)<>Trim(edtRepwd.Text) then
  begin
    ShowMessage('������������벻һ�������������룡');
    edtpwd.SetFocus;
    Exit;
  end;
  if (edtBegin.Text <> '') and (length(edtBegin.Text) <> 14) then
  begin
    showmessage('��Чʱ���λ�����ԣ����������룡');
    edtBegin.SetFocus;
    exit;
  end;
  if (edtEnd.Text <> '') and (length(edtEnd.Text) <> 14) then
  begin
    showmessage('ʧЧʱ���λ�����ԣ����������룡');
    edtEnd.SetFocus;
    exit;
  end;
  if formatdate(trim(edtBegin.text)) = false then
  begin
    edtBegin.SetFocus;
    exit;
  end;
  if formatdate(trim(edtEnd.text)) = false then
  begin
    edtEnd.SetFocus;
    exit;
  end;

  if Trim(edtCode.Text)='admin' then
  begin
    ShowMessage('�����޸Ĺ���Ա��Ϣ��');
    Exit;
  end;
  if operType='add' then
    addLimitInfo();
  if operType='edit' then
    editLimitInfo();

  queryOperList();
end;

procedure TfrmLimit.qryQueryAfterScroll(DataSet: TDataSet);
begin
  fillDataInfo();
end;

procedure TfrmLimit.clearSelect;
var
  i:Integer;
begin
  for i := 0 to grpLimit.ControlCount-1 do
    if grpLimit.Controls[i] is TCheckBox then
      TCheckBox(grpLimit.Controls[i]).Checked:=False;
end;

function TfrmLimit.ifHaveOper(operCode: string): Boolean;
var
  sqlStr:string;
  tmpQuery:TADOQuery;
begin
  sqlStr:='select count(*)as num from '+tblLimit+' where '+lmtOperCode+'='+#39+edtCode.Text+#39;
  tmpQuery := nil;
  try
    tmpQuery := TADOQuery.Create(nil);
    tmpQuery.Connection := frmdm.conn;
    tmpQuery.Close;
    tmpQuery.sql.Clear;
    tmpQuery.SQL.Add(sqlstr);
    tmpQuery.Open;
    if tmpQuery.FieldByName('num').AsInteger=0 then
      Result:=False
    else
      Result:=True;
  finally
    tmpQuery.Destroy;
  end;
end;

procedure TfrmLimit.delLimitInfo;
var
  sqlStr:string;
  tmpQuery:TADOQuery;
begin
  sqlStr:='delete from '+tblLimit+' where '+lmtOperCode+'='+#39+edtCode.Text+#39;
  tmpQuery := nil;
  try
    tmpQuery := TADOQuery.Create(nil);
    tmpQuery.Connection := frmdm.conn;
    tmpQuery.Close;
    tmpQuery.sql.Clear;
    tmpQuery.SQL.Add(sqlstr);
    tmpQuery.Prepared;
    tmpQuery.ExecSQL;
  finally
    tmpQuery.Destroy;
  end;
end;

procedure TfrmLimit.BitBtn1Click(Sender: TObject);
begin
  if Trim(edtCode.Text)='admin' then
  begin
    ShowMessage('�㲻��ɾ������Ա��');
    Exit;
  end;
  if Application.MessageBox(PChar('��ȷ��Ҫɾ���ò���Ա��'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  delLimitInfo();
  queryOperList();
end;

function TfrmLimit.FormatDate(str: string): boolean;
begin
  if trim(str) = '' then
  begin
    result := true;
    exit;
  end;
  if (strtoint(copy(str, 5, 2)) > 12) or (strtoint(copy(str, 5, 2)) < 1) then
  begin
    showmessage('�·���������');
    result := false;
    exit;
  end;
  if (strtoint(copy(str, 7, 2)) > 31) or (strtoint(copy(str, 7, 2)) < 1) then
  begin
    showmessage('����������');
    result := false;
    exit;
  end;
  if (strtoint(copy(str, 9, 2)) > 24) or (strtoint(copy(str, 9, 2)) < 1) then
  begin
    showmessage('Сʱ��������');
    result := false;
    exit;
  end;
  if (strtoint(copy(str, 11, 2)) > 60) or (strtoint(copy(str, 11, 2)) < 0) then
  begin
    showmessage('������������');
    result := false;
    exit;
  end;
  if (strtoint(copy(str, 13, 2)) > 60) or (strtoint(copy(str, 13, 2)) < 0) then
  begin
    showmessage('������������');
    result := false;
    exit;
  end;
  result := true;

end;

end.

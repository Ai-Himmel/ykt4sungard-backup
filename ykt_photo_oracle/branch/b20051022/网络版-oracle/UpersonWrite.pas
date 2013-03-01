unit UpersonWrite;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls, Db, ADODB;

type
  TFrmPersonWrite = class(TForm)
    pnl1: TPanel;
    grpMast: TGroupBox;
    lblNo: TLabel;
    edtNo: TEdit;
    lblName: TLabel;
    edtName: TEdit;
    lbltype: TLabel;
    cbbType: TComboBox;
    lblDep: TLabel;
    cbbDep: TComboBox;
    lblsex: TLabel;
    cbbsex: TComboBox;
    grpother: TGroupBox;
    lbldep2: TLabel;
    cbbdep2: TComboBox;
    lblIDCard: TLabel;
    edtIDCard: TEdit;
    lblGrade: TLabel;
    cbbGrade: TComboBox;
    btnSave: TButton;
    btnExit: TButton;
    qryExecSQL: TADOQuery;
    procedure btnAddClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
  private
    { Private declarations }
    procedure iniData;
    function  saveJudge:Boolean;
  public
    { Public declarations }
  end;

var
  FrmPersonWrite: TFrmPersonWrite;
  procedure PersonWrite(Conn: TADOConnection);

implementation

uses Udb;

{$R *.DFM}
procedure PersonWrite(Conn: TADOConnection);
var
  FrmPersonWrite: TFrmPersonWrite;
begin
  {FrmPersonWrite := FrmPersonWrite.Create(Application);
  //FrmPersonWrite.qryExecSQL.Connection := Conn;
  FrmPersonWrite.ShowModal;
  FrmPersonWrite.Free; }
end;

procedure TFrmPersonWrite.btnAddClick(Sender: TObject);
begin
end;

{-------------------------------------------------------------------------------
  ������:    TFrmPersonWrite.iniDate��ʼ������������
  ����:      Wang xiaoguo
  ����:      2005.10.22
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TFrmPersonWrite.iniData;
var
  sqltype:string;
  sqldep1:string;
  sqldep2:string;
  sqlgrade:string;
  procedure AddData(cbb:TComboBox;sqlstr:string);
  begin
    cbb.Items.Clear;
    qryExecSQL.Close;
    qryExecSQL.sql.Clear;
    qryExecSQL.SQL.Add(sqlstr);
    qryExecSQL.Prepared;
    qryExecSQL.Open;
    if qryExecSQL.RecordCount>0 then
    begin
      qryExecSQL.First;
      while not qryExecSQL.Eof do
      begin
        cbb.Items.Add(qryExecSQL.Fields[0].Text);
        qryExecSQL.Next;
      end;
    end;
    qryExecSQL.Recordset.Close;
    qryExecSQL.Close;
  end;
begin
  sqltype:='select distinct cut_type from t_cif_photo';
  sqldep1:='select distinct dept_name from t_cif_photo';
  sqldep2:='select distinct s_code from t_cif_photo';
  sqlgrade:='select distinct in_date from t_cif_photo';
  AddData(cbbType,sqltype);
  AddData(cbbDep,sqldep1);
  AddData(cbbdep2,sqldep2);
  AddData(cbbGrade,sqlgrade);
end;

procedure TFrmPersonWrite.FormShow(Sender: TObject);
begin
  iniData;
end;

procedure TFrmPersonWrite.btnSaveClick(Sender: TObject);
var
  sqlstr:string;
begin
  if (edtNo.Text)='' then
  begin
    ShowMessage('ѧ���Ų���Ϊ�գ������룡');
    edtNo.SetFocus;
    Exit;
  end;
  if trim(edtName.Text)='' then
  begin
    ShowMessage('��������Ϊ�գ������룡');
    edtName.SetFocus;
    Exit;
  end;
  if Trim(cbbsex.Text)='' then
  begin
    ShowMessage('�ձ���Ϊ�գ������룡');
    cbbsex.SetFocus;
    Exit;
  end;
  if Trim(cbbType.Text)='' then
  begin
    ShowMessage('�����Ϊ�գ������룡');
    cbbType.SetFocus;
    Exit;
  end;
  if Trim(cbbDep.Text)='' then
  begin
    ShowMessage('һ����λ����Ϊ�գ������룡');
    cbbDep.SetFocus;
    Exit;
  end;
  if saveJudge=True then
    Exit;
  sqlstr:='insert into t_cif_photo(cut_type,stuemp_no,stuemp_name,dept_name,';
  sqlstr:=sqlstr+'s_code,sex_code,sex_name,id2,in_date,addperson_date)values(';
  sqlstr:=sqlstr+#39+trim(cbbType.Text)+#39;              //���
  sqlstr:=sqlstr+','+#39+trim(edtNo.Text)+#39;            //ѧ����
  sqlstr:=sqlstr+','+#39+trim(edtName.Text)+#39;          //����
  sqlstr:=sqlstr+','+#39+trim(cbbDep.Text)+#39;           //һ������
  sqlstr:=sqlstr+','+#39+trim(cbbdep2.Text)+#39;          //��������
  sqlstr:=sqlstr+','+inttostr(cbbsex.ItemIndex);          //�ձ����
  sqlstr:=sqlstr+','+#39+trim(cbbsex.Text)+#39;           //�ձ�
  sqlstr:=sqlstr+','+#39+trim(edtIDCard.Text)+#39;        //���֤��
  sqlstr:=sqlstr+','+#39+trim(cbbGrade.Text)+#39;
  sqlstr:=sqlstr+','+#39+formatdatetime('yyyy-mm-dd',date)+#39+')';         //�꼶
  qryExecSQL.Close;
  qryExecSQL.sql.Clear;
  qryExecSQL.SQL.Add(sqlstr);
  qryExecSQL.Prepared;
  qryExecSQL.ExecSQL;
  ShowMessage('��Ա��Ϣ��ӳɹ���');
  
  edtNo.Text:='';
  edtIDCard.Text:='';
  edtNo.SetFocus;
end;

function  TFrmPersonWrite.saveJudge:Boolean;
var
  sqlstr:string;
begin
  Result:=False;
  sqlstr:='select stuemp_no from t_cif_photo where stuemp_no='+#39+trim(edtNo.Text)+#39;
  qryExecSQL.close;
  qryExecSQL.sql.Clear;
  qryExecSQL.SQL.Add(sqlstr);
  qryExecSQL.Prepared;
  qryExecSQL.Open;
  if qryExecSQL.RecordCount>0 then
  begin
    ShowMessage('����Աѧ�����Ѿ����ڣ����޸�ѧ���ţ�');
    edtNo.SetFocus;
    Result:=True;
  end;
  qryExecSQL.Recordset.Close;
  qryExecSQL.Close;
end;

procedure TFrmPersonWrite.btnExitClick(Sender: TObject);
begin
  //qryExecSQL.Recordset.Close;
  qryExecSQL.Close;
  close;
end;

end.

unit UOperator;
     
{ ***********************************************************************
  Copyright (c) 2005 �Ϻ��������˴��������޹�˾
  ��    ��: ����Ա����, Ȩ������
  ԭ �� ��: ����
  ��������: �޴ӿ���
  �޸�����: '2005-06-01'
  �� �� ��: Haifeng Zhu
  ��    ��: Ver 2.0
  ��    ��: �������¹���ģ���Ȩ�޹���, ����ģ���ŵ������淶��, ԭ����
            ���ִ���,  ������չ, �ɶ��Բ�.
  ************************************************************************ }

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, Grids, DBGrids, Db, ADODB, StdCtrls, Mask, DBCtrls;

type
  TOperatorForm = class(TForm)
    Panel1: TPanel;
    DBGrid1: TDBGrid;
    DataSource1: TDataSource;
    ADOTable1: TADOTable;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    DBEdit1: TDBEdit;
    DBEdit2: TDBEdit;
    DBEdit3: TDBEdit;
    DBEdit4: TDBEdit;
    DBEdit5: TDBEdit;
    DBEdit6: TDBEdit;
    DBEdit7: TDBEdit;
    btnADd: TButton;
    btnDelete: TButton;
    btnSave: TButton;
    btnExit: TButton;
    Label12: TLabel;
    Label13: TLabel;
    edtrepwd: TEdit;
    edtpwd: TDBEdit;
    ADOQuery1: TADOQuery;
    chkuse: TCheckBox;
    cbQuery: TCheckBox;
    cbEditData: TCheckBox;
    cbLoadPic: TCheckBox;
    cbExpData: TCheckBox;
    cbExpPic: TCheckBox;
    cbPrint: TCheckBox;
    cbImpPic: TCheckBox;
    cbImpData: TCheckBox;
    cbMakeCard: TCheckBox;
    cbDelData: TCheckBox;
    chkMakeCard: TCheckBox;
    procedure btnExitClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnADdClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure ADOTable1AfterScroll(DataSet: TDataSet);
    procedure chkuseClick(Sender: TObject);
  private
    { Private declarations }
    slimit:string;
    function checkData: boolean;
    function FormatDate(str: string): Boolean;
    procedure chkLimit;
  public
    { Public declarations }
  end;

var
  OperatorForm: TOperatorForm;

implementation

uses Udb, UtConfigs;

{$R *.DFM}

procedure TOperatorForm.btnExitClick(Sender: TObject);
begin
  ADOTable1.Close;
  close;
end;

procedure TOperatorForm.FormShow(Sender: TObject);
begin
  if not adotable1.Active then
    adotable1.Open;
end;

procedure TOperatorForm.btnADdClick(Sender: TObject);
begin
  adotable1.Append;
  dbedit1.SetFocus;
end;

procedure TOperatorForm.btnDeleteClick(Sender: TObject);
begin
  if (adotable1.FieldByName('oper_code').asstring = 'tjxxb1')
   or ((adotable1.FieldByName('oper_code').asstring = 'tjxxb2')) then
  begin
    showmessage('��������Ա����ɾ����');
    exit;
  end;
  if application.MessageBox('��ȷ��Ҫɾ���ò���Ա��', pchar(application.Title), mb_iconquestion + mb_yesno) = idyes then
    adotable1.Delete;
  adotable1.Refresh;
end;

function TOperatorForm.checkData: boolean;
begin
  if trim(dbedit1.Text) = '' then
  begin
    showmessage('����Ա���벻��Ϊ�գ������룡');
    dbedit1.SetFocus;
    result := false;
    exit;
  end;
  if trim(dbedit1.Text) = '' then
  begin
    showmessage('����Ա���Ʋ���Ϊ�գ������룡');
    dbedit1.SetFocus;
    result := false;
    exit;
  end;
  if edtpwd.Text <> edtrepwd.Text then
  begin
    showmessage('������������벻һ�������������룡');
    edtrepwd.SetFocus;
    result := false;
    exit;
  end;
  if (dbedit6.Text <> '') and (length(dbedit6.Text) <> 14) then
  begin
    showmessage('��Чʱ���λ�����ԣ����������룡');
    dbedit6.SetFocus;
    result := false;
    exit;
  end;
  if (dbedit7.Text <> '') and (length(dbedit7.Text) <> 14) then
  begin
    showmessage('ʧЧʱ���λ�����ԣ����������룡');
    dbedit7.SetFocus;
    result := false;
    exit;
  end;
  if formatdate(trim(dbedit6.text)) = false then
  begin
    result := false;
    dbedit6.SetFocus;
    exit;
  end;
  if formatdate(trim(dbedit7.text)) = false then
  begin
    result := false;
    dbedit7.SetFocus;
    exit;
  end;
  result := true;
end;

function TOperatorForm.FormatDate(str: string): boolean;
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
  if (strtoint(copy(str, 11, 2)) > 60) or (strtoint(copy(str, 11, 2)) < 1) then
  begin
    showmessage('������������');
    result := false;
    exit;
  end;
  if (strtoint(copy(str, 13, 2)) > 60) or (strtoint(copy(str, 13, 2)) < 1) then
  begin
    showmessage('������������');
    result := false;
    exit;
  end;
  result := true;
end;

procedure TOperatorForm.btnSaveClick(Sender: TObject);
begin
  if checkData = false then
    exit;
  chkLimit;
  adotable1.fieldbyname('pwd').asstring := dm.csh(edtpwd.text);
  adotable1.fieldbyname('status').asboolean := chkuse.Checked;
  adotable1.fieldbyname('FUNC_SET').asstring := slimit;
  if adotable1.State in [dsinsert, dsedit] then
  begin
    try
      adotable1.Post;
      showmessage('����ɹ���');
    except
      showmessage('����ʧ�ܣ�');
    end;
  end;
end;

procedure TOperatorForm.ADOTable1AfterScroll(DataSet: TDataSet);
var
  sQuery,sEditData,sLoadPic,sExpData,sPrint,sExpPic,
  sDelPic, sDelData, sImpPic, sImpData, sMakeCard,scard: string;
  procedure SetCheckBox(Value: Boolean; CB: TCheckBox);
  begin
    if Value then
      CB.Checked := True
    else
      CB.Checked := False;
  end;
begin
  if (adotable1.FieldByName('oper_code').asstring='tjxxb1')
  or(adotable1.FieldByName('oper_code').asstring='tjxxb2') then
  begin
    dbedit1.ReadOnly:=true;
    dbedit2.ReadOnly:=true;
  end
  else
  begin
    dbedit1.ReadOnly:=false;
    dbedit2.ReadOnly:=false;
  end;
  sQuery:=copy(adotable1.fieldbyname('FUNC_SET').asstring,Mdl_Query,1);
  sEditData:=copy(adotable1.fieldbyname('FUNC_SET').asstring,Mdl_EditData,1);
  sLoadPic:=copy(adotable1.fieldbyname('FUNC_SET').asstring,Mdl_LoadPic,1);
  sExpData:=copy(adotable1.fieldbyname('FUNC_SET').asstring,Mdl_ExpData,1);
  sPrint:=copy(adotable1.fieldbyname('FUNC_SET').asstring,Mdl_Print,1);
  sExpPic:=copy(adotable1.fieldbyname('FUNC_SET').asstring,Mdl_ExpPic,1);
  sDelData := Copy(ADOTable1.FieldByName('FUNC_SET').AsString,Mdl_DelData,1);
  sImpPic := Copy(ADOTable1.FieldByName('FUNC_SET').AsString,Mdl_ImpPic,1);
  sImpData := Copy(ADOTable1.FieldByName('FUNC_SET').AsString,Mdl_ImpData,1);
  sMakeCard := Copy(ADOTable1.FieldByName('FUNC_SET').AsString,Mdl_MakeCard,1);
  scard := Copy(ADOTable1.FieldByName('FUNC_SET').AsString,Mdl_Card,1);
  chkuse.Checked := adotable1.fieldbyname('status').asboolean;
  if sQuery='1' then
    cbQuery.Checked:=true
  else
    cbQuery.Checked:=false;
  if sEditData='1' then
    cbEditData.Checked:=true
  else
    cbEditData.Checked:=false;
  if sLoadPic='1' then
    cbLoadPic.Checked:=true
  else
    cbLoadPic.Checked:=false;

  if sExpData='1' then
    cbExpData.Checked:=true
  else
    cbExpData.Checked:=false;
  if sPrint='1' then
    cbPrint.Checked:=true
  else
    cbPrint.Checked:=false;
  if sExpPic='1' then
    cbExpPic.Checked:=true
  else
    cbExpPic.Checked:=false;

  if sMakeCard='1' then
    cbMakeCard.Checked:=True
  else
    cbMakeCard.Checked:=False;

  if scard='1' then
    chkMakeCard.Checked:=True
  else
    chkMakeCard.Checked:=False;

  //SetCheckBox(sDelPic='1', cbDelPic);
  SetCheckBox(sDelData='1', cbDelData);
  SetCheckBox(sImpPic='1', cbImpPic);
  SetCheckBox(sImpData='1', cbImpData);
  SetCheckBox(sMakeCard='1', cbMakeCard);

  edtrepwd.Text := '';
end;

procedure TOperatorForm.chkuseClick(Sender: TObject);
begin
  adotable1.Edit;
end;

//���Ȩ��
procedure TOperatorForm.chkLimit;
var
  sQuery,sEditData,sLoadPic,sExpData,sPrint,sExpPic,
  sDelData, sImpPic, sImpData, sMakeCard,sCard: string;
  function GetValue(CB: TCheckBox): string;
  begin
    if CB.Checked then
      Result := '1'
    else
      Result := '0';
  end;
begin
  slimit:='';
  if cbQuery.Checked=true then      //��ѯ
    sQuery:='1'
  else
    sQuery:='0';
  if cbEditData.Checked=true then    //�޸���Ϣ
    sEditData:='1'
  else
    sEditData:='0';
  if cbLoadPic.Checked=true then    //ȡ��Ƭ
    sLoadPic:='1'
  else
    sLoadPic:='0';
  if cbExpData.Checked=true then    //��������
    sExpData:='1'
  else
    sExpData:='0';
  if cbPrint.Checked=true then      //��ӡ
    sprint:='1'
  else
    sprint:='0';
  if cbExpPic.Checked=true then     //������Ƭ
    sExpPic:='1'
  else
    sExpPic:='0';
  if cbMakeCard.Checked=True then   //�ƿ�����
    sMakeCard:='1'
  else
    sMakeCard:='0';

  if chkMakeCard.Checked=True then //�ƿ�
    sCard:='1'
  else
    sCard:='0';

  //sDelPic := GetValue(cbDelPic);
  sDelData := GetValue(cbDelData);     //ɾ����Ϣ
  sImpPic := GetValue(cbImpPic);      //������Ƭ
  sImpData := GetValue(cbImpData);    //��������
  sMakeCard := GetValue(cbMakeCard);

  slimit:=sQuery+sEditData+sLoadPic+sExpData+sPrint+sExpPic
      + sDelData + sImpPic + sImpData + sMakeCard+scard;
end;

end.

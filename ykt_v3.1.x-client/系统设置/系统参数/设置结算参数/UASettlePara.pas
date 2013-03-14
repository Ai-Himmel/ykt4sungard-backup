unit UASettlePara;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  USetParamsTemp;

type
  TfaqhSettlePara = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    Label9: TLabel;
	WVEdit1: TWVEdit;
	WVEdit2: TWVEdit;
	WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Label_snote: TLabel;
    WVEdit_snote: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure WVComboBox1Exit(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSettlePara: TfaqhSettlePara;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSettlePara.Init;
begin
  inherited;
  WorkView.FieldByName('��ѯ.��ѯ��־��1�����㣻2�����ף�').DefaultValue := 1;
  WorkView.FieldByName('��ѯ.ϯ_λ').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��������').DefaultValue := '';
  WorkView.FieldByName('ϯ_λ_��_��').DefaultValue := '';  //wlj20031222 Ϊ�˽��������޸ģ����ֲ��ܰ���ϯλ������ģ����޸�
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('��������ֵ').DefaultValue := '';
  WorkView.FieldByName('�������').DefaultValue := '';
  WorkView.Reset;
end;

procedure TfaqhSettlePara.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSettlePara.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhSettlePara.btnOKClick(Sender: TObject);
var
  tempValue : string;
  iPos : integer;
begin
  tempValue :=  workview.fieldbyname('ϯ_λ_��_��').data.asstring;
  iPos := Pos('-',tempValue);
  if iPos <> 0 then             //����� �� ����д���
    workview.fieldbyname('ϯ_λ_��_��').data.SetString(Copy(tempValue,1, iPos - 1));

  if(Status = ssDelete) then
  begin
    inherited;
  end
  else  if(WVEdit4.Text = '') then
  begin
    context.GetDialogSystem.ShowMessage('������ϯλ����');
    WVComboBox1.SetFocus;
  end
  else inherited;
  WVEdit_snote.Visible := true;  //��ʾ����
  Label_snote.Visible := true;
end;

procedure TfaqhSettlePara.btnChangeClick(Sender: TObject);
begin
  inherited;
  WVEdit_snote.Visible := false;  //��������
  Label_snote.Visible := false;

  WVEdit5.Enabled := false;
  WVComboBox1.Enabled := false;
  WVEdit6.SetFocus;
  WVEdit6.SelectAll;
end;

procedure TfaqhSettlePara.btnAddClick(Sender: TObject);
begin
  inherited;
  WVEdit_snote.Visible := false;  //��������
  Label_snote.Visible := false;

  WVEdit5.Enabled := true;
  WVComboBox1.Enabled := true;
  WVComboBox1.selectAll;
end;

procedure TfaqhSettlePara.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WVEdit_snote.Visible := false;  //��������
  Label_snote.Visible := false;

end;

procedure TfaqhSettlePara.btnCancelClick(Sender: TObject);
begin
  inherited;
  WVEdit_snote.Visible := true;  //��ʾ����
  Label_snote.Visible := true;
end;

procedure TfaqhSettlePara.WVComboBox1Exit(Sender: TObject);
var
  tempValue : string;
  sSeat_no : string;
  iPos : integer;
begin
//  inherited;


  // wlj 20040115 ���Ӷ�ϯλ��Ч�Եļ��
  if workview.fieldbyname('ϯ_λ_��_��').data.asstring = '' then exit;
  if workview.fieldbyname('ϯ_λ_��_��').data.asstring = '0' then exit;
  if workview.fieldbyname('ϯ_λ_��_��').data.asstring = '*' then exit;

  tempValue :=  workview.fieldbyname('ϯ_λ_��_��').data.asstring;
  iPos := Pos('-',tempValue);
  if iPos <> 0 then             //����� �� ����д���
    sSeat_no := Copy(tempValue,1, iPos - 1)
  else
    sSeat_no := tempValue;

  //wlj 20040219 �����esc��ϯλ��disable �� invisible ��ô����setfocus�ͻ�ʧ�ܡ�

  if GetIdObjectName(-23,sSeat_no) = '' then
  begin
    try
      WVComboBox1.SelectAll;
      WVComboBox1.SetFocus;
      context.GetDialogSystem.ShowMessage('�����ϯλ������');
    except
    end;
  end;


end;

initialization
  TUIStdClassFactory.Create('���ý������',TfaqhSettlePara);

end.
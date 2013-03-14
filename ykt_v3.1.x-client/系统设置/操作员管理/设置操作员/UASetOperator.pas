unit UASetOperator;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls,CardDll, 
  UAuth, USetParamsTemp, UIncrementComboBox, RzDBNav, RzButton, RzRadChk,
  RzDBGrid, RzTabs,KCDataAccess,SmartCardCommon, Buttons, EditExts;

type
  TfaqhSetOperator = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Labeloper_code1: TLabel;
    WVComboBox1: TWVComboBox;
    QryModuleAuth: TWVRequest;
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    Panel2: TPanel;
    Panel3: TPanel;
    faAuth1: TfaAuth;
    WVEditemail8: TWVEdit;
    Labelemail8: TLabel;
    Labeladdr6: TLabel;
    WVEditaddr6: TWVEdit;
    WVEditphone4: TWVEdit;
    Labelphone4: TLabel;
    lblpwd: TLabel;
    edtPwd: TWVEdit;
    WVEditoper_name3: TWVEdit;
    Labeloper_name3: TLabel;
    Labeloper_code2: TLabel;
    WVEditoper_code2: TWVEdit;
    Labelif_station9: TLabel;
    WVComboBoxif_station9: TWVComboBox;
    WVComboBoxif_access10: TWVComboBox;
    Labelif_access10: TLabel;
    lblrepwd: TLabel;
    edtPwdCheck: TWVEdit;
    WVEditmobile5: TWVEdit;
    Labelmobile5: TLabel;
    Label1: TLabel;
    cbbNetInfo: TWVComboBox;
    Label2: TLabel;
    cbbType: TWVComboBox;
    edtMoneyLimit: TWVDigitalEdit;
    Label3: TLabel;
    Label4: TLabel;
    WVEdit1: TWVEdit;
    Label5: TLabel;
    WVComboBox3: TWVComboBox;
    Labelmenu_set14: TLabel;
    WVComboBoxmenu_set14: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure edtPwdCheckKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure WorkViewWorkFields20ValueChanged(WorkField: TWVField);
    procedure btnViewDetailClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  protected
    //��ȡ����Ϊ800���ַ���
    procedure DisplayData; override;
    //����ѯ����Ȩ��λ����ʾ�����Խṹ��
    procedure SaveModifiedData; override;
    procedure BeforeAdd; override;
    function  Get800Str: string;
    function  Get200Str: string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetOperator: TfaqhSetOperator;

implementation

uses KsFrameworks, KSClientConsts, KSDataDictionary;

{$R *.DFM}

function  TfaqhSetOperator.Get200Str: string;
begin
  Result := StringOfChar('0',200);   //wlj 20031209 ȱʡ��Ϊû��Ȩ��
end;


function TfaqhSetOperator.Get800Str: string;
begin
  Result := StringOfChar('0',800);   //wlj 20031209 ȱʡ��Ϊû��Ȩ��
end;

procedure TfaqhSetOperator.BeforeAdd;
var TmpStr:WideString;
begin
  inherited;
  //wsn  �����Ӻ��Ȩ���ַ������µ�����
  TmpStr:=Copy(WorkView.FieldByName('�˵�Ȩ��1').Data.AsString,1,200)+
          Copy(WorkView.FieldByName('�˵�Ȩ��2').Data.AsString,1,200)+
          Copy(WorkView.FieldByName('�˵�Ȩ��3').Data.AsString,1,200)+
          Copy(WorkView.FieldByName('�˵�Ȩ��4').Data.AsString,1,200);
  faAuth1.SetAuth(TmpStr,Get800Str);
end;

procedure TfaqhSetOperator.DisplayData;
var TmpStr:WideString;
begin
  inherited;
  TmpStr:='';
  TmpStr:=TmpStr+trim(Copy(WorkView.FieldByName('�˵�Ȩ��1').Data.AsString,1,200));
  TmpStr:=TmpStr+trim(Copy(WorkView.FieldByName('�˵�Ȩ��2').Data.AsString,1,200));
  TmpStr:=TmpStr+trim(Copy(WorkView.FieldByName('�˵�Ȩ��3').Data.AsString,1,200));
  TmpStr:=TmpStr+trim(Copy(WorkView.FieldByName('�˵�Ȩ��4').Data.AsString,1,200)); 
  faAuth1.SetAuth(TmpStr,Get800Str);
end;

procedure TfaqhSetOperator.SaveModifiedData;
var TmpStr:String;
    lst:TStringlist;
begin
  inherited;
  TmpStr:=faAuth1.MenuSet; 
  WorkView.FieldByName('�˵�Ȩ��1').Data.SetString(Copy(TmpStr,1,200));
  WorkView.FieldByName('�˵�Ȩ��2').Data.SetString(Copy(TmpStr,201,200));
  WorkView.FieldByName('�˵�Ȩ��3').Data.SetString(Copy(TmpStr,401,200));
  WorkView.FieldByName('�˵�Ȩ��4').Data.SetString(Copy(TmpStr,601,200));
  WorkView.FieldByName('����Ȩ��').Data.SetString(Get800Str);
end;

procedure TfaqhSetOperator.Init;
begin
  faAuth1.HandleNeeded;
  faAuth1.TreeView.HandleNeeded;
  faAuth1.BuildTree;
  faAuth1.RefreshTreeDisplay;
  faAuth1.SetAuth(Get800Str, Get800Str);
  inherited;
  //WorkView.FieldByName('�Ƿ����Ʒ���վ��').DefaultValue := GetFirstItemID(15);
  //WorkView.FieldByName('�Ƿ����Ʒ���').DefaultValue := GetFirstItemID(15);
  WorkView.FieldByName('����Ա״̬').DefaultValue := GetFirstItemID(2);
  WorkView.FieldByName('����Ա����').DefaultValue := '';
  WorkView.FieldByName('�˵�Ȩ��1').DefaultValue := Get200Str;
  WorkView.FieldByName('�˵�Ȩ��2').DefaultValue := Get200Str;
  WorkView.FieldByName('�˵�Ȩ��3').DefaultValue := Get200Str;
  WorkView.FieldByName('�˵�Ȩ��4').DefaultValue := Get200Str;
  WorkView.FieldByName('����Ȩ��').defaultValue := Get800Str;
  WorkView.Reset;
end;

procedure TfaqhSetOperator.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetOperator.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetOperator.btnAddClick(Sender: TObject);
begin
  WorkView.FieldByName('Ȩ��ģ��').data.setstring('');  
  inherited;
  WorkView.FieldByName('�������').data.setstring('A');
  edtPwd.Text := '';
  WVEditoper_code2.Enabled := true;
  WVEditoper_code2.SetFocus;
  WVEditoper_code2.SelectAll;
  edtPwd.Enabled:=True;
  edtPwdCheck.Enabled:=True;
  edtPwdCheck.ParentColor := False;
  edtPwdCheck.Color := clWhite;
  edtPwdCheck.Text:='';
  edtPwd.Enabled:=True;
end;

procedure TfaqhSetOperator.btnChangeClick(Sender: TObject);
var tmpstr:STring;
begin
  WorkView.FieldByName('Ȩ��ģ��').data.setstring('');  //wlj 20040115 ����ǰ�Ȱ�Ȩ��ģ����Ϊ�գ�����Ͳ�ѯ���Ŀͻ���Ȩ�޲�һ������һ����
  inherited;
  if WorkView.FieldByName('����Ա����').Data.AsString = SuperOperator then
  begin
     Context.GetDialogSystem.ShowMessage('��������Ա����Ϣ�������޸ģ�');
     self.CancelEdit;
     Exit;
  end;
  WorkView.FieldByName('�������').data.setstring('U');
  WVEditoper_code2.Enabled := false;
  WVEditoper_name3.SetFocus;
  WVEditoper_name3.SelectAll;
  edtPwd.Text:='';
  edtPwdCheck.Text := '';
  edtPwd.Enabled:=False;
  edtPwdCheck.Enabled:=False;
  edtPwdCheck.ParentColor := True;
  edtPwd.Enabled:=False;
  cbbNetInfo.Enabled := False;
end;


procedure TfaqhSetOperator.btnOKClick(Sender: TObject);
var
  ss:string;
  operCode:string;
  operPwd:string;
begin
  if (Status = ssAdd) then
  begin
    if Trim(edtPwd.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('����Ա���벻��Ϊ�գ�');
      edtPwd.SetFocus;
      exit;
    end;
    ss := Copy(cbbNetInfo.Text,1,Pos('-',cbbNetInfo.Text)-1);
    if (ss='') or (ss='-') then
    begin
      Context.GetDialogSystem.ShowMessage('����ѡ�����Ա���ڵ�����ţ�');
      Exit;
    end;
    ss := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    if (ss='') or (ss='-') then
    begin
      Context.GetDialogSystem.ShowMessage('����ѡ�����Ա�������ͣ�');
      Exit;
    end;
  end;
  if ((Status = ssAdd)or(Status = ssChange)) then
  begin
    ss := Copy(WVComboBoxif_station9.Text,1,Pos('-',WVComboBoxif_station9.Text)-1);
    if (ss='') or (ss='-') then
    begin
      Context.GetDialogSystem.ShowMessage('����ѡ�����Ա�Ƿ�����վ�㣡');
      Exit;
    end;
    if (edtPwdCheck.Text <> edtPwd.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('������������벻��ͬ��');
      edtPwd.SetFocus;
      edtPwd.SelectAll;
      exit;
    end;
    if not CheckCodeValid(Trim(WVEditoper_code2.Text)) then
    begin
      Context.GetDialogSystem.ShowMessage('����Ա������������');
      WVEditoper_code2.SetFocus;
      WVEditoper_code2.SelectAll;
      exit;
    end;
    if (Trim(WVEditphone4.Text)<>'') and (CheckTelNumber(Trim(WVEditphone4.Text))=false) then
    begin
      Context.GetDialogSystem.ShowMessage('�绰������������');
      WVEditphone4.SetFocus;
      WVEditphone4.SelectAll;
      exit;
    end;
    if (Trim(WVEditmobile5.Text)<>'') and (CheckMobileNumber(Trim(WVEditmobile5.Text))=false) then
    begin
      Context.GetDialogSystem.ShowMessage('�ֻ�������������');
      WVEditmobile5.SetFocus;
      WVEditmobile5.SelectAll;
      exit;
    end;
  end;
  if (status = ssDelete ) then
  begin
    if workview.FieldByName('����Ա����').Data.AsString = Context.ParamData(svOperatorNoName).AsString then
    begin
       Context.GetDialogSystem.ShowMessage('����Ա����ɾ���Լ���');
       Exit;
    end;
    if (context.GetDialogSystem.Confirm('�Ƿ�ɾ������Ա'+WorkView.FieldByName('����Ա����').data.asstring+ '����������?') = uaNo) then
    begin
      exit;
    end;
  end;
  SaveModifiedData;
  operCode := Trim(WVEditoper_code2.Text);
  operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
  WorkView.FieldByName('����Ա����').Data.SetString(operPwd);
  inherited;
  edtPwdCheck.Text:='';
  btnQuery.Click;
  //wlj 20031202���Ӳ���Ա��,���ϸ��������ֵ�ʹ����б�
  FreeIDObjects(-30);  // update the data dict
  //NeedIdObjectList(-30);
  WVComboBox1.ItemsDataEntry := '';
  WVComboBox1.itemsdataentry := '*-30';
end;



procedure TfaqhSetOperator.btnDeleteClick(Sender: TObject);
begin
  WorkView.FieldByName('Ȩ��ģ��').data.setstring('');  //wlj 20040115 ����ǰ�Ȱ�Ȩ��ģ����Ϊ�գ�����Ͳ�ѯ���Ŀͻ���Ȩ�޲�һ������һ����
  inherited;
  if WorkView.FieldByName('����Ա����').Data.AsString = SuperOperator then
  begin
     Context.GetDialogSystem.ShowMessage('��������Ա����Ϣ�������޸ģ�');
     self.CancelEdit;
     Exit;
  end;
  edtPwdCheck.Enabled :=False;
  edtPwdCheck.ParentColor := True;
  WorkView.FieldByName('�������').data.setstring('D');
end;

procedure TfaqhSetOperator.edtPwdCheckKeyDown(Sender: TObject;
  var Key: Word; Shift: TShiftState);
begin
  inherited;
  if Key = VK_RETURN then
    SelectNext(TWinControl(Sender),True,True);
end;

procedure TfaqhSetOperator.WorkViewWorkFields20ValueChanged(
  WorkField: TWVField);
var
  dataset: TDataset;
  TmpStr:WideString;
  lst:TStringList;
begin
  inherited;
  //wlj 20031209 ���Ȩ��ģ��Ϊ�գ���Ȩ��ȫ��ȥ��
  if WorkView.FieldByName('Ȩ��ģ��').data.AsString = '' then
  begin
        faAuth1.SetAuth(Get800Str, Get800Str);
        WorkView.FieldByName('�˵�Ȩ��1').data.setstring(Get200Str);
        WorkView.FieldByName('�˵�Ȩ��2').data.setstring(Get200Str);
        WorkView.FieldByName('�˵�Ȩ��3').data.setstring(Get200Str);
        WorkView.FieldByName('�˵�Ȩ��4').data.setstring(Get200Str);
        WorkView.FieldByName('����Ȩ��').data.setstring(Get800Str);
        exit;
  end;
  //ѡ����Ȩ��ģ��
  QryModuleAuth.SendCommand;
  dataset := TKCDataset(WorkView.FieldByName('Ȩ��ģ������').Data.AsObject);
  try
    if(dataset <> nil) then
    begin
      dataset.First;
      while not dataset.Eof do
      begin
        TmpStr:=Copy(dataset.Fields.FieldByName('vsvarstr0').asstring,1,200)+
                Copy(dataset.Fields.FieldByName('vsvarstr1').asstring,1,200)+
                Copy(dataset.Fields.FieldByName('vsvarstr2').asstring,1,200)+
                Copy(dataset.Fields.FieldByName('vsvarstr3').asstring,1,200);
        WorkView.FieldByName('�˵�Ȩ��1').data.setstring(Copy(dataset.Fields.FieldByName('vsvarstr0').asstring,1,200));
        WorkView.FieldByName('�˵�Ȩ��2').data.setstring(Copy(dataset.Fields.FieldByName('vsvarstr1').asstring,1,200));
        WorkView.FieldByName('�˵�Ȩ��3').data.setstring(Copy(dataset.Fields.FieldByName('vsvarstr2').asstring,1,200));
        WorkView.FieldByName('�˵�Ȩ��4').data.setstring(Copy(dataset.Fields.FieldByName('vsvarstr3').asstring,1,200));

        faAuth1.SetAuth(TmpStr, WorkView.FieldByName('����Ȩ��').Data.AsString);
        dataset.Next;
      end;
    end;
  except
    faAuth1.SetAuth(Get800Str, Get800Str);
    WorkView.FieldByName('�˵�Ȩ��1').data.setstring(Get200Str);
    WorkView.FieldByName('�˵�Ȩ��2').data.setstring(Get200Str);
    WorkView.FieldByName('�˵�Ȩ��3').data.setstring(Get200Str);
    WorkView.FieldByName('�˵�Ȩ��4').data.setstring(Get200Str);
    //WorkView.FieldByName('����Ȩ��').data.setstring(Get800Str);
  end;

end;

procedure TfaqhSetOperator.btnViewDetailClick(Sender: TObject);
begin
  WorkView.FieldByName('Ȩ��ģ��').data.setstring('');  
  inherited;
end;

procedure TfaqhSetOperator.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('�������').data.setstring('R');
  inherited;

end;

initialization
  TUIStdClassFactory.Create('����Ա����',TfaqhSetOperator);

end.

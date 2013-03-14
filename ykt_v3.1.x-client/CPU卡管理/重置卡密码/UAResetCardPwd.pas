unit UAResetCardPwd;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, RzStatus, RzPanel, Buttons, RzEdit;

type
  TfaResetCardPwd = class(TfaInputTemp)
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    btnEdPwd: TBitBtn;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtSex: TRzEdit;
    edtCert: TRzEdit;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    edtNewPwd: TRzEdit;
    edtVertPwd: TRzEdit;
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure WVEdit2KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure WVEdit3KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure btnEdPwdClick(Sender: TObject);
  private
    { Private declarations }
    procedure ClearPassWord;
  public
    { Public declarations }
    procedure Init; override;
  end;

var
  faResetCardPwd: TfaResetCardPwd;

implementation
uses ksframeworks, KSClientConsts,CardDll;

{$R *.DFM}

procedure TfaResetCardPwd.Init;
begin
  inherited;
end;

procedure TfaResetCardPwd.btnReadCardInfoClick(Sender: TObject);
var
  cm: TCM;
  CurExCardId: string;
  st:integer;
  phyId:string;
begin
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    setOperReadMode(cm);
    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    CurExCardId := cm.getCardNo;
    if  CurExCardId='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ���׿���ʧ�ܣ���ȷ�϶������Ϳ���״̬��');
      Exit;
    end;
    edtCardNo.Text := CurExCardId;
    edtName.Text := cm.getCustName;
    edtCert.Text := cm.getCertNo;
    if Copy(cm.getCustSex,1,1)='1' then
      edtSex.Text := '��'
    else if Copy(cm.getCustSex,1,1)='2' then
      edtSex.Text := 'Ů'
    else
      edtSex.Text := '';
    btnEdPwd.Enabled := True;
  finally
    cm.Destroy;
  end;
end;

procedure TfaResetCardPwd.ClearPassWord;
begin
  edtNewPwd.Text := '';
  edtVertPwd.Text := '';
end;

procedure TfaResetCardPwd.WVEdit2KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  inherited;
  if Key=vk_return then
    edtNewPwd.SetFocus;
end;

procedure TfaResetCardPwd.WVEdit3KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  inherited;
  if Key=vk_return then
    edtVertPwd.SetFocus;
end;

procedure TfaResetCardPwd.btnEdPwdClick(Sender: TObject);
var
  cardID: string;
  cm: TCM;
  st: smallint;
  phyId:string;
begin
  if not preReadCard then
    Exit;
  cardID := edtCardNo.Text;

  try
    StrToInt(edtNewPwd.Text);
    StrToInt(edtVertPwd.Text);
  except
    Context.GetDialogSystem.ShowWarning('������������Ϊ���룡');
    Exit;
  end;

  if Length(edtNewPwd.Text) = 6 then
  begin
    if trim(edtNewPwd.Text) <> trim(edtVertPwd.Text) then
    begin
      Context.GetDialogSystem.ShowWarning('��������������벻ͬ��������������ͬ��6λ���룡');
      edtNewPwd.Text := '';
      edtVertPwd.Text := '';
      edtNewPwd.SetFocus;
    end
    else
    begin
      //��д��,���д�ɹ�����д��
      cm:= nil;
      try
        cm := TCM.Create;
        st := cm.card(phyid);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('�����Ҫ�޸�����Ŀ���');
          Exit;
        end;
        st := cm.resetpasswd(phyid,edtNewPwd.Text);
        if st = 0 then
        begin
          //���¿�����
          WorkView.FieldByName('����ʶ').Data.SetInteger(StrToInt(cardID));
          WorkView.FieldByName('������').Data.SetString(edtNewPwd.Text);
          try
            MainRequest.SendCommand;
            cm.beep;
            Context.GetDialogSystem.ShowSuccess('�޸Ŀ�����ɹ���');
            btnEdPwd.Enabled := False;
            ClearPassWord;
          except
            WorkView.FieldByName('����ʶ').Data.SetInteger(StrToInt(cardID));
            WorkView.FieldByName('������').Data.SetString(edtNewPwd.Text);
            MainRequest.SendCommand;
          end;
        end
        else
        begin
          //���д��ʧ�ܣ���ֹ����
          Context.GetDialogSystem.ShowWarning('�޸Ŀ�����ʧ�ܣ�');
          Exit;
        end;
      finally
        cm.Destroy;
      end;
    end;
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('������6λ���룡');
    Exit;
  end;
end;

initialization
  TUIStdClassFactory.Create('����������', TfaResetCardPwd);

end.

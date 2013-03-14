unit UAChangeCardPwd;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, RzStatus, RzPanel, Buttons, RzEdit, UtCardDll;

type
  TfaChangeCardPwd = class(TfaInputTemp)
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
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    edtOldPwd: TRzEdit;
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
    sPwd:string;
    procedure ClearPassWord;
  public
    { Public declarations }
    procedure Init; override;
  end;

var
  faChangeCardPwd: TfaChangeCardPwd;

implementation
uses ksframeworks, KSClientConsts;

{$R *.DFM}
procedure TfaChangeCardPwd.Init;
begin
  inherited;
  edtNewPwd.SetFocus;
end;

procedure TfaChangeCardPwd.btnReadCardInfoClick(Sender: TObject);
var
  CardManage: TCardManage;
  PCM: TPublishCardMes;
  ResInt: SmallInt;
  CurExCardId: string;
begin
  if PrepareReadCardInfo=False then
    Exit;
  CardManage := TCardManage.Create;
  ResInt := CardManage.ReadExCardID(CurExCardId);
  if ResInt <> 0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ȡ���׿���ʧ�ܣ���ȷ�϶������Ϳ���״̬��');
    CardManage.Destroy;
    Exit;
  end;
  edtCardNo.Text := CurExCardId;
  ResInt := CardManage.ReadCardInfo(PCM);

  if ResInt = 0 then
  begin
    edtName.Text := PCM.ucName;
    edtCert.Text := PCM.ucCertificateNo;
    if Copy(PCM.ucSexNo,1,1)='1' then
      edtSex.Text := '��'
    else if Copy(PCM.ucSexNo,1,1)='2' then
      edtSex.Text := 'Ů'
    else
      edtSex.Text := ''
  end;
  sPwd := CardManage.ReadCardPsw;
  if sPwd = 'error' then
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ������ʧ�ܣ�');
    CardManage.Destroy;
    Exit;
  end;
  edtOldPwd.Text := Trim(sPwd);
  btnEdPwd.Enabled := True;
  CardManage.Destroy;
end;

procedure TfaChangeCardPwd.ClearPassWord;
begin
  edtOldPwd.Text := '';
  edtNewPwd.Text := '';
  edtVertPwd.Text := '';
end;

procedure TfaChangeCardPwd.WVEdit2KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  inherited;
  if Key=vk_return then
    edtNewPwd.SetFocus;
end;

procedure TfaChangeCardPwd.WVEdit3KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  inherited;
  if Key=vk_return then
    edtVertPwd.SetFocus;
end;

procedure TfaChangeCardPwd.btnEdPwdClick(Sender: TObject);
var
  cardID: string;
  CardManage: TCardManage;
  st: smallint;
begin
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
    Exit;
  end;
  if not SmartCardAuthStatus then
  begin
    Context.GetDialogSystem.ShowWarning('����Ϊ��д����Ȩ��');
    Exit;
  end;
  cardID := edtCardNo.Text;

  try
    StrToInt(edtNewPwd.Text);
    StrToInt(edtVertPwd.Text);
  except
    Context.GetDialogSystem.ShowWarning('������������Ϊ���룡');
    Exit;
  end;
  {
  if trim(edtOldPwd.Text) <> trim(sPwd) then
  begin
    Context.GetDialogSystem.ShowWarning('������ľ��������');
    edtOldPwd.SetFocus;
    exit;
  end;
  }
  CardManage := TCardManage.Create;

  if Length(edtNewPwd.Text) = 6 then
  begin
    if trim(edtNewPwd.Text) <> trim(edtVertPwd.Text) then
    begin
      Context.GetDialogSystem.ShowWarning('��������������벻ͬ��������������ͬ��6λ���룡');
      edtNewPwd.Text := '';
      edtVertPwd.Text := '';
      edtNewPwd.SetFocus;
      CardManage.Destroy;
      Exit;
    end
    else
    begin
      //��д��,���д�ɹ�����д��
      st := CardManage.ChangeCardPsw(edtNewPwd.Text);
      if st = 0 then
      begin
        //���¿�����
        WorkView.FieldByName('����ʶ').Data.SetInteger(StrToInt(cardID));
        WorkView.FieldByName('������').Data.SetString(edtNewPwd.Text);
        try
          MainRequest.SendCommand;
          Context.GetDialogSystem.ShowSuccess('�޸Ŀ�����ɹ���');
          btnEdPwd.Enabled := False;
          ClearPassWord;
        except
          WorkView.FieldByName('����ʶ').Data.SetInteger(StrToInt(cardID));
          WorkView.FieldByName('������').Data.SetString(edtOldPwd.Text);
          try
            //ShowWaiting(SWaitingOperation);
            MainRequest.SendCommand;
          finally
            //CloseWaiting;
          end;
        end;
      end
      else
      begin
        //���д��ʧ�ܣ���ֹ����
        Context.GetDialogSystem.ShowWarning('�޸Ŀ�����ʧ�ܣ�');
        CardManage.Destroy;
        Exit;
      end;
    end;
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('������6λ�����룡');
    CardManage.Destroy;
    Exit;
  end;

  CardManage.Destroy;
end;

initialization
  TUIStdClassFactory.Create('�������޸�', TfaChangeCardPwd);

end.

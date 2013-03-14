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
    Context.GetDialogSystem.ShowMessage('读取交易卡号失败！请确认读卡器和卡的状态！');
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
      edtSex.Text := '男'
    else if Copy(PCM.ucSexNo,1,1)='2' then
      edtSex.Text := '女'
    else
      edtSex.Text := ''
  end;
  sPwd := CardManage.ReadCardPsw;
  if sPwd = 'error' then
  begin
    Context.GetDialogSystem.ShowWarning('读取卡密码失败！');
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
    Context.GetDialogSystem.ShowWarning('请先打开串口！');
    Exit;
  end;
  if not SmartCardAuthStatus then
  begin
    Context.GetDialogSystem.ShowWarning('请先为读写器授权！');
    Exit;
  end;
  cardID := edtCardNo.Text;

  try
    StrToInt(edtNewPwd.Text);
    StrToInt(edtVertPwd.Text);
  except
    Context.GetDialogSystem.ShowWarning('请输入数字作为密码！');
    Exit;
  end;
  {
  if trim(edtOldPwd.Text) <> trim(sPwd) then
  begin
    Context.GetDialogSystem.ShowWarning('你输入的旧密码错误！');
    edtOldPwd.SetFocus;
    exit;
  end;
  }
  CardManage := TCardManage.Create;

  if Length(edtNewPwd.Text) = 6 then
  begin
    if trim(edtNewPwd.Text) <> trim(edtVertPwd.Text) then
    begin
      Context.GetDialogSystem.ShowWarning('您两次输入的密码不同，请重新输入相同的6位密码！');
      edtNewPwd.Text := '';
      edtVertPwd.Text := '';
      edtNewPwd.SetFocus;
      CardManage.Destroy;
      Exit;
    end
    else
    begin
      //先写卡,如果写成功，则写库
      st := CardManage.ChangeCardPsw(edtNewPwd.Text);
      if st = 0 then
      begin
        //更新卡密码
        WorkView.FieldByName('卡标识').Data.SetInteger(StrToInt(cardID));
        WorkView.FieldByName('新密码').Data.SetString(edtNewPwd.Text);
        try
          MainRequest.SendCommand;
          Context.GetDialogSystem.ShowSuccess('修改卡密码成功！');
          btnEdPwd.Enabled := False;
          ClearPassWord;
        except
          WorkView.FieldByName('卡标识').Data.SetInteger(StrToInt(cardID));
          WorkView.FieldByName('新密码').Data.SetString(edtOldPwd.Text);
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
        //如果写卡失败，中止交易
        Context.GetDialogSystem.ShowWarning('修改卡密码失败！');
        CardManage.Destroy;
        Exit;
      end;
    end;
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('请输入6位卡密码！');
    CardManage.Destroy;
    Exit;
  end;

  CardManage.Destroy;
end;

initialization
  TUIStdClassFactory.Create('卡密码修改', TfaChangeCardPwd);

end.

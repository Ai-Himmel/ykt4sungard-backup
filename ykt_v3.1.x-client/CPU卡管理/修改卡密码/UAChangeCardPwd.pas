unit UAChangeCardPwd;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, RzStatus, RzPanel, Buttons, RzEdit;

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
    FPwd:string;
    procedure setPwd(pwd:string);
    function getPwd: string;
    procedure ClearPassWord;
  public
    { Public declarations }
    procedure Init; override;
  end;

var
  faChangeCardPwd: TfaChangeCardPwd;

implementation
uses ksframeworks, KSClientConsts,CardDll;

{$R *.DFM}

procedure TfaChangeCardPwd.Init;
begin
  inherited;
  edtOldPwd.SetFocus;
end;

procedure TfaChangeCardPwd.btnReadCardInfoClick(Sender: TObject);
var
  cm: TCM;
  CurExCardId: string;
begin
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    //先清除所有的读取权限
    cm.clearallfieldreadmode;
    //设置要读取内容的权限
    setOperReadMode(cm);
    if cm.readCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取卡信息失败，请重试！');
      Exit;
    end;
    CurExCardId := cm.getCardNo;
    if  CurExCardId='' then
    begin
      Context.GetDialogSystem.ShowMessage('读取交易卡号失败！请确认读卡器和卡的状态！');
      Exit;
    end;

    setPwd(cm.getCardPwd);
    edtCardNo.Text := CurExCardId;
    edtName.Text := cm.getCustName;
    edtCert.Text := cm.getCertNo;
    if Copy(cm.getCustSex,1,1)='1' then
      edtSex.Text := '男'
    else if Copy(cm.getCustSex,1,1)='2' then
      edtSex.Text := '女'
    else
      edtSex.Text := '';
    btnEdPwd.Enabled := True;
  finally
    cm.Destroy;
  end;
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
    Context.GetDialogSystem.ShowWarning('请输入数字作为密码！');
    Exit;
  end;
  if Length(edtNewPwd.Text) = 6 then
  begin
    if trim(edtNewPwd.Text) <> trim(edtVertPwd.Text) then
    begin
      Context.GetDialogSystem.ShowWarning('您两次输入的密码不同，请重新输入相同的6位密码！');
      edtNewPwd.Text := '';
      edtVertPwd.Text := '';
      edtNewPwd.SetFocus;
    end
    else
    begin
      //先写卡,如果写成功，则写库
      cm:= nil;
      try
        cm := TCM.Create;
        st := cm.card(phyid);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('请放置要修改密码的卡！');
          Exit;
        end;
        //st := cm.verifyPin(phyId,trim(edtOldPwd.Text));
        if getPwd<>Trim(edtOldPwd.Text) then
        begin
          Context.GetDialogSystem.ShowMessage('输入的旧密码不正确，请重新的输入！');
          edtOldPwd.SetFocus;
          Exit;
        end;
        st := cm.resetpasswd(phyId,edtNewPwd.Text);
        if st = 0 then
        begin
          //更新卡密码
          WorkView.FieldByName('卡标识').Data.SetInteger(StrToInt(cardID));
          WorkView.FieldByName('新密码').Data.SetString(edtNewPwd.Text);
          try
            MainRequest.SendCommand;
            cm.beep;
            Context.GetDialogSystem.ShowSuccess('修改卡密码成功！');
            btnEdPwd.Enabled := False;
            ClearPassWord;
          except
            WorkView.FieldByName('卡标识').Data.SetInteger(StrToInt(cardID));
            WorkView.FieldByName('新密码').Data.SetString(edtOldPwd.Text);
            MainRequest.SendCommand;
          end;
        end
        else
        begin
          //如果写卡失败，中止交易
          Context.GetDialogSystem.ShowWarning('修改卡密码失败！');
          Exit;
        end;
      finally
        cm.Destroy;
      end;
    end;
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('请输入6位密码！');
    Exit;
  end;
end;

function TfaChangeCardPwd.getPwd: string;
begin
  Result := FPwd;
end;

procedure TfaChangeCardPwd.setPwd(pwd: string);
begin
  if pwd<>FPwd then
    FPwd := pwd;
end;

initialization
  TUIStdClassFactory.Create('卡密码修改', TfaChangeCardPwd);

end.

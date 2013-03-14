unit UAmodifyAuthCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, RzPanel, RzRadGrp, RzEdit,
  UIncrementComboBox,Math, RzStatus, Buttons;

type
  TfaqhmodifyAuthCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    rzchckgrp1: TRzCheckGroup;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp1: TGroupBox;
    edtCardNo: TRzEdit;
    edtNo: TRzEdit;
    edtLimitDate: TRzEdit;
    Label2: TLabel;
    edtName: TRzEdit;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    btnEdit: TBitBtn;
    btnReadCard: TBitBtn;
    procedure btnEditClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  OperatorNoName:string;
  function getAuthLimit: Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhmodifyAuthCard: TfaqhmodifyAuthCard;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils, UtCardDll;
     
{$R *.DFM}

procedure TfaqhmodifyAuthCard.Init;
begin
  inherited;
  {
  WorkView.FieldByName('交易卡号').DefaultValue := 0;
  WorkView.FieldByName('更新有效期').DefaultValue := '';
  WorkView.FieldByName('卡权限').DefaultValue := 0;
  WorkView.FieldByName('业务操作员号').DefaultValue := '';
  WorkView.Reset;
  }
  btnQuery.Caption:='&R 读卡';
  btnEdit.Caption:='修改参数';
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
end;

procedure TfaqhmodifyAuthCard.btnEditClick(Sender: TObject);
var
  CardManage: TCardManage;
  mainKey:string;
  cardLimit:Byte;
  ireadCardLimit:Integer;
  ireadCard:Integer;
  PCM: TPublishCardMes;
  i:Integer;
  chkValue:Integer;
  flag:Integer;
  rCardNo:Integer;
  rcardLimit:Integer;
  rDate:string;
begin
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('请先打开串口！');
     Exit;
  end;
  CardManage := nil;
  WorkView.FieldByName('交易卡号').Data.SetInteger(StrToInt(Trim(edtCardNo.Text)));
  WorkView.FieldByName('更新有效期').Data.SetString(Trim(edtLimitDate.Text));
  WorkView.FieldByName('卡权限').Data.SetInteger(getAuthLimit);
  WorkView.FieldByName('业务操作员号').Data.SetString(OperatorNoName);
  MainRequest.SendCommand;
  rCardNo:=WorkView.fieldbyname('交易卡号').Data.AsInteger;
  rcardLimit:=WorkView.fieldbyname('卡权限').Data.AsInteger;
  rDate:=WorkView.fieldbyname('更新有效期').Data.AsString;
  try
    CardManage := TCardManage.Create;
    ireadCard := ReadAuthCardInfo(pcm);
    if ireadCard<>0 then
    begin
      ShowMessage('读取卡信息失败！');
      btnEdit.Enabled := False;
      Exit;
    end;
    if StrToInt(PCM.CardNo)<>rCardNo then
    begin
      ShowMessage('你要更新的授权卡和读写器上的卡不一致，请检查！');
      btnEdit.Enabled := False;
      Exit;
    end;
    flag:=CardManage.SMT_ModifyDeadLineDateAndFlag(rDate,rcardLimit);
    if flag<>0 then
      ShowMessage('更新授权卡失败！')
    else
      ShowMessage('更新授权卡成功！');
  finally
    CardManage.Destroy;
  end;
  btnEdit.Enabled := False;
end;

function TfaqhmodifyAuthCard.getAuthLimit: Integer;
var
  ss,i:Integer;
  chkValue:Integer;
begin
  ss:=0;
  for i := 0 to rzchckgrp1.Items.Count-1 do
  begin
    if rzchckgrp1.ItemChecked[i] then
    begin
      chkValue := 1 shl i;
      ss := ss or chkValue;
    end;
  end;
  Result := ss;
end;

procedure TfaqhmodifyAuthCard.btnReadCardClick(Sender: TObject);
var
  CardManage: TCardManage;
  mainKey:string;
  cardLimit:Byte;
  ireadCardLimit:Integer;
  ireadCard:Integer;
  PCM: TPublishCardMes;
  i:Integer;
  chkValue:Integer;
  flag:Integer;
begin
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('请先打开串口！');
     Exit;
  end;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    ireadCard := ReadAuthCardInfo(pcm);
    if ireadCard<>0 then
    begin
      ShowMessage('读取卡信息失败！');
      Exit;
    end;
    edtName.Text := pcm.ucName;
    edtNo.Text:=PCM.ucLibraryNo;
    edtCardNo.Text:= PCM.CardNo;
    edtLimitDate.Text:=PCM.DeadLineDate;
    ireadCardLimit := CardManage.SMT_ReadAuthorWorkKeyAndFlag(mainKey,cardLimit);
    if ireadCardLimit<>0 then
    begin
      ShowMessage('读取卡权限失败！');
      Exit;
    end;
    for i := 0 to rzchckgrp1.Items.Count-1 do
    begin
      chkValue:= 1 shl i;
      if cardLimit and chkValue <> 0 then
        rzchckgrp1.ItemChecked[i]:=True
      else
        rzchckgrp1.ItemChecked[i]:=False;
    end;

  finally
    CardManage.Destroy;
  end;
  btnEdit.Enabled := True;
end;

initialization
  TUIStdClassFactory.Create('修改授权卡参数',TfaqhmodifyAuthCard);

end.
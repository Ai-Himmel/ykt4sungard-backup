unit UApubAuthCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzRadGrp, RzEdit,
  UIncrementComboBox, RzStatus, Buttons, UtCardDll;

type
  TfaqhpubAuthCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    rzchckgrp1: TRzCheckGroup;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp1: TGroupBox;
    WVComboBox3: TWVComboBox;
    edtLimitDate: TRzEdit;
    Label2: TLabel;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    btnPubAuth: TBitBtn;
    procedure btnPubAuthClick(Sender: TObject);
  private

    { Private declarations }
  OperatorNoName:string;
  function getAuthLimit: Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhpubAuthCard: TfaqhpubAuthCard;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhpubAuthCard.Init;
begin
  inherited;
  {
  WorkView.FieldByName('操作员号').DefaultValue := '';
  WorkView.FieldByName('物理卡号').DefaultValue := '';
  WorkView.FieldByName('授权卡权限').DefaultValue := 0;
  WorkView.FieldByName('交易卡号').DefaultValue := 0;
  WorkView.FieldByName('业务操作员').DefaultValue := '';
  WorkView.FieldByName('有效期').DefaultValue := '';
  WorkView.Reset;
  }
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  btnQuery.Caption:='发行授权卡';
  edtLimitDate.Text:=FormatDateTime('yyyymmdd',Date()+365);
end;

function TfaqhpubAuthCard.getAuthLimit: Integer;
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

procedure TfaqhpubAuthCard.btnPubAuthClick(Sender: TObject);
var
  CardManage: TCardManage;
  Pcardid:string;
  mainKey:string;
  cardLimit:Integer;
  limitDate:string;
  cardNo:Integer;
  operCode:string;
  operName:string;
  iIniAuthCard:Integer;
  iPubAuthCard:Integer;
  tempStr: PChar;
  tempArr: array[0..8] of char;
  tempErr: string;
  PCM: TPublishCardMes;
  sErrInfo:string;
begin
  CardManage:=nil;
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('请先打开串口！');
    Exit;
  end;
  if getAuthLimit=0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择授权卡所拥有的权限!');
    exit;
  end;
  try
    CardManage:=Tcardmanage.Create();
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      context.GetDialogSystem.ShowWarning('读卡序列号失败！');
      exit;
    end;
    WorkView.FieldByName('授权卡权限').Data.SetInteger(getAuthLimit);
    WorkView.FieldByName('业务操作员').Data.SetString(OperatorNoName);
    WorkView.FieldByName('物理卡号').Data.SetString(PCardID);
    WorkView.FieldByName('有效期').Data.SetString(Trim(edtLimitDate.Text));
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger=0 then
    begin
      mainKey:=WorkView.fieldbyname('工作密钥').Data.AsString;
      cardLimit:=WorkView.fieldbyname('授权卡权限').Data.AsInteger;
      cardNo:=WorkView.fieldbyname('交易卡号').Data.AsInteger;
      limitDate:=WorkView.fieldbyname('有效期').Data.AsString;
      operCode:=WorkView.fieldbyname('操作员号').Data.AsString;
      operName:=WorkView.fieldbyname('操作员名称').Data.AsString;
      tempErr := '';
      ZeroMemory(@tempArr, 8);
      tempStr := @tempArr;
      CardManage.ConvertHexStrToPChar(mainKey, 16, tempStr, tempErr);
      sErrInfo := '请到授权卡操作中把该授权卡无卡回收，然后重新发行！';
      if tempErr <> '' then
      begin
        Context.GetDialogSystem.ShowMessage('转化失败--'+tempErr+sErrInfo);
        Exit;
      end;
      iIniAuthCard := CardManage.InitNewAuthCard(tempStr,cardLimit);
      if iIniAuthCard<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('初始化授权卡失败--'+sErrInfo);
        Exit;
      end;
      strcopy(@PCM.CardNo, PChar(IntToStr(cardNo)));         //交易卡号
      strcopy(@PCM.DeadLineDate, PChar(limitDate));          //截止日期
      strcopy(@PCM.ucLibraryNo, PChar(operCode));            //操作员号
      strcopy(@PCM.ucName, PChar(operName));                 //操作员名称

      iPubAuthCard := CardManage.PublishAuthCard(pcm);
      if iPubAuthCard<>0 then
        Context.GetDialogSystem.ShowMessage('发行授权卡失败--'+sErrInfo)
      else
        Context.GetDialogSystem.ShowMessage('发行授权卡成功！');
    end;
  finally
    CardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('发行授权卡',TfaqhpubAuthCard);

end.
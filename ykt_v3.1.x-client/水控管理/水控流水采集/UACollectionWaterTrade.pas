unit UACollectionWaterTrade;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVDBBinders, Db, 
  RzDBGrid, ComCtrls, RzListVw, UtCardDll, Buttons;

type
  TfaqhCollectionWaterTrade = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnUpLoad: TBitBtn;
    lvSerial: TRzListView;
    pb1: TProgressBar;
    stat1: TStatusBar;
    btnClear: TBitBtn;
    procedure btnQueryClick(Sender: TObject);
    procedure btnUpLoadClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
  private

    { Private declarations }
    collectBalance: array[1..90]of Tcollect_balance;
    collCount:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCollectionWaterTrade: TfaqhCollectionWaterTrade;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhCollectionWaterTrade.Init;
begin
  inherited;
  WorkView.FieldByName('设备号').DefaultValue := '';
  WorkView.FieldByName('金额').DefaultValue := 0.00;
  WorkView.Reset;
end;

procedure TfaqhCollectionWaterTrade.btnQueryClick(Sender: TObject);
var
  CardManage: TCardManage;
  st:SmallInt;
  err_code:Integer;
  i:Integer;
  tmpItem: TListItem;
begin
  CardManage := nil;
  err_code := 0;
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('请先打开串口！');
     Exit;
  end;
  try
    CardManage := TCardManage.Create;
    st := CardManage.CollectionCardReceiveData(@err_code,@collectBalance,@collCount);
    if st<>0 then
    begin
      ShowMessage('读取流水失败--'+inttostr(st));
      Exit;
    end;
    lvSerial.Items.Clear;
    for i := 1 to collCount do
    begin
      tmpItem := lvSerial.Items.Add;
      tmpItem.Caption:=IntToStr(i);
      tmpItem.SubItems.Add(collectBalance[i].devId);
      tmpItem.SubItems.Add(FloatToStr(collectBalance[i].sum_balance));
    end;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhCollectionWaterTrade.btnUpLoadClick(Sender: TObject);
var
  i,re:Integer;
  cardManage:TCardManage;
  returnInfo:string;
  operCode:string;
begin
  operCode := Context.ParamData(svOperatorNoName).AsString;
  pb1.Max:=lvSerial.Items.Count-1;
  for i :=0  to lvSerial.Items.Count-1 do
  begin
    WorkView.FieldByName('设备号').Data.SetString(lvSerial.Items[i].SubItems[0]);
    WorkView.FieldByName('金额').Data.SetFloat(StrToFloat(lvSerial.Items[i].SubItems[1]));
    WorkView.FieldByName('操作员代码').Data.SetString(operCode);
    MainRequest.SendCommand;
    if WorkView.FieldByName('失败码').Data.AsInteger<>0 then
    begin
      returnInfo := WorkView.FieldByName('返回信息').Data.AsString;
      stat1.Panels[0].Text:= returnInfo;
      if Application.MessageBox(PChar(returnInfo+'--你是否继续？'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
        Exit
      else
        Continue;
    end
    else
    begin
      returnInfo := WorkView.FieldByName('返回信息').Data.AsString;
      stat1.Panels[0].Text:= returnInfo;
    end;
    pb1.Position:=i;
  end;
  cardManage := nil;
  try
    cardManage := TCardManage.Create;
    re := cardManage.ClearCollectCardData;
    if re<>0 then
      ShowMessage('清空采集卡内数据失败！');
  finally
    cardManage.Destroy;
  end;
  ShowMessage('流水全部上传成功！');
  pb1.Position:=0;
end;

procedure TfaqhCollectionWaterTrade.btnClearClick(Sender: TObject);
var
  re:Integer;
  cardManage:TCardManage;
begin
  if Application.MessageBox('在清空采集卡内数据前请确定你已经上传该卡内的流水，要清空吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  cardManage := nil;
  try
    cardManage := TCardManage.Create;
    re := cardManage.ClearCollectCardData;
    if re<>0 then
      ShowMessage('清空采集卡内数据失败！')
    else
      ShowMessage('清空采集卡内数据成功！');
  finally
    cardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('水控流水采集',TfaqhCollectionWaterTrade);

end.
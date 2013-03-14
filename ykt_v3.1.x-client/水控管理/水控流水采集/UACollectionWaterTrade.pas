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
  WorkView.FieldByName('�豸��').DefaultValue := '';
  WorkView.FieldByName('���').DefaultValue := 0.00;
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
     Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
     Exit;
  end;
  try
    CardManage := TCardManage.Create;
    st := CardManage.CollectionCardReceiveData(@err_code,@collectBalance,@collCount);
    if st<>0 then
    begin
      ShowMessage('��ȡ��ˮʧ��--'+inttostr(st));
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
    WorkView.FieldByName('�豸��').Data.SetString(lvSerial.Items[i].SubItems[0]);
    WorkView.FieldByName('���').Data.SetFloat(StrToFloat(lvSerial.Items[i].SubItems[1]));
    WorkView.FieldByName('����Ա����').Data.SetString(operCode);
    MainRequest.SendCommand;
    if WorkView.FieldByName('ʧ����').Data.AsInteger<>0 then
    begin
      returnInfo := WorkView.FieldByName('������Ϣ').Data.AsString;
      stat1.Panels[0].Text:= returnInfo;
      if Application.MessageBox(PChar(returnInfo+'--���Ƿ������'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
        Exit
      else
        Continue;
    end
    else
    begin
      returnInfo := WorkView.FieldByName('������Ϣ').Data.AsString;
      stat1.Panels[0].Text:= returnInfo;
    end;
    pb1.Position:=i;
  end;
  cardManage := nil;
  try
    cardManage := TCardManage.Create;
    re := cardManage.ClearCollectCardData;
    if re<>0 then
      ShowMessage('��ղɼ���������ʧ�ܣ�');
  finally
    cardManage.Destroy;
  end;
  ShowMessage('��ˮȫ���ϴ��ɹ���');
  pb1.Position:=0;
end;

procedure TfaqhCollectionWaterTrade.btnClearClick(Sender: TObject);
var
  re:Integer;
  cardManage:TCardManage;
begin
  if Application.MessageBox('����ղɼ���������ǰ��ȷ�����Ѿ��ϴ��ÿ��ڵ���ˮ��Ҫ�����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  cardManage := nil;
  try
    cardManage := TCardManage.Create;
    re := cardManage.ClearCollectCardData;
    if re<>0 then
      ShowMessage('��ղɼ���������ʧ�ܣ�')
    else
      ShowMessage('��ղɼ��������ݳɹ���');
  finally
    cardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('ˮ����ˮ�ɼ�',TfaqhCollectionWaterTrade);

end.
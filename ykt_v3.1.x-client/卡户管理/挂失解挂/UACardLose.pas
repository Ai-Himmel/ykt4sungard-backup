unit UACardLose;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, UtCardDll;

type
  TfaqhCardLose = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    Label5: TLabel;
    btnLose: TBitBtn;
    WVCardLose: TWorkView;
    WVRCardLose: TWVRequest;
    btnUnLose: TBitBtn;
    WVEdit4: TWVEdit;
    cbb1: TWVComboBox;
    Label4: TLabel;
    WVEdit5: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnLoseClick(Sender: TObject);
    procedure btnUnLoseClick(Sender: TObject);
  private
    { Private declarations }

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardLose: TfaqhCardLose;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardLose.Init;
begin
  inherited;
end;

procedure TfaqhCardLose.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardLose.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  WorkView.FieldByName('钱包号').Data.SetInteger(1);
  inherited;
end;


procedure TfaqhCardLose.btnLoseClick(Sender: TObject);
var
  CardID: integer;
  showCardNo,tmpName,custName:string;
  tipINfo:string;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;

  CardID := (WorkView.FieldByName('查询结果集').Data.AsObject as
    TDataSet).FieldByName('lvol0').AsInteger;
  custName := (WorkView.FieldByName('查询结果集').Data.AsObject as
    TDataSet).FieldByName('sall_name').AsString;
  showCardNo := (WorkView.FieldByName('查询结果集').Data.AsObject as
    TDataSet).FieldByName('sorder0').AsString;

  if Trim(custName)='' then
    tmpName := showCardNo
  else
    tmpName := custName;

  if Application.MessageBox(PChar('你确定要挂失['+tmpName+']的卡吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;

  WVCardLose.FieldByName('卡号').Data.SetInteger(CardID);
  WVCardLose.FieldByName('操作标志').Data.SetString('1');

  try
   //ShowWaiting(SWaitingOperation);
    WVRCardLose.SendCommand;
  finally
    //CloseWaiting;
    tipINfo := WVCardLose.fieldbyname('返回信息').Data.AsString;
    if (WVCardLose.FieldByName('返回码').Data.AsInteger = 0) then
    begin
      Context.GetDialogSystem.ShowSuccess('挂失校园卡操作成功  '+tipINfo);
      RzStatusPane1.Caption := '挂失校园卡操作成功  '+tipINfo
    end
    else
    begin
      getReturn('挂失校园卡失败  ',WVCardLose);
      RzStatusPane1.Caption := '挂失校园卡失败  '+tipINfo
    end;
  end;
  try
    MainRequest.SendCommand;
  except
  end;
end;

procedure TfaqhCardLose.btnUnLoseClick(Sender: TObject);
var
  CardID: integer;
  CardExID:string;
  CardManage: TCardManage;
  tipInfo:string;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;

  if PrepareReadCardInfo=False then
    Exit;
  CardID := (WorkView.FieldByName('查询结果集').Data.AsObject as
    TDataSet).FieldByName('lvol0').AsInteger;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    if CardManage.ReadExCardID(CardExID) <> 0 then
    begin
      Context.GetDialogSystem.ShowWarning('读取交易卡号失败！');
      Exit;
    end;

    if StrToInt(CardExID) <> CardID then
    begin
      Context.GetDialogSystem.ShowWarning('你所操作的卡和读写器上放置的不是同一张卡！');
      Exit;
    end;

    WVCardLose.FieldByName('卡号').Data.SetInteger(CardID);
    WVCardLose.FieldByName('操作标志').Data.SetString('2');

    //ShowWaiting(SWaitingOperation);
    WVRCardLose.SendCommand;
    if WVCardLose.FieldByName('返回码').Data.AsInteger = 0 then
    begin
      tipINfo := WVCardLose.fieldbyname('返回信息').Data.AsString;
      if CardManage.SetNormalFlagbyVer(PChar(WVCardLose.FieldByName('卡版本号').Data.AsString)) <> 0 then
      begin
        Context.GetDialogSystem.ShowWarning('没有取到版本号，解挂卡失败！');
      end
      else
      begin
        CardManage.ControlBuzzer;
        Context.GetDialogSystem.ShowSuccess('解挂卡成功  '+tipInfo);
        RzStatusPane1.Caption := '解挂卡成功  '+tipINfo
      end;
    end
    else
    begin
      getReturn('解挂卡失败  ',WVCardLose);
      RzStatusPane1.Caption := '解挂卡失败  '+tipINfo
    end;
  finally
    CardManage.Destroy;
    //CloseWaiting;
  end;
end;

initialization
  TUIStdClassFactory.Create('挂失解挂操作', TfaqhCardLose);

end.



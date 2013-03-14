unit UAauthCardOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, RzButton,
  RzRadChk, RzStatus, RzPanel, Buttons, UtCardDll;

type
  TfaqhauthCardOper = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    WVEdit1: TWVEdit;
    WVEdit3: TWVEdit;
    WVComboBox3: TWVComboBox;
    cbxNoCard: TRzCheckBox;
    btnLose: TBitBtn;
    btnRLose: TBitBtn;
    btnReturn: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    WorkView3: TWorkView;
    WVRequest3: TWVRequest;
    Label6: TLabel;
    WVEdit2: TWVEdit;
    WVComboBox1: TWVComboBox;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    procedure btnReturnClick(Sender: TObject);
    procedure btnLoseClick(Sender: TObject);
    procedure btnRLoseClick(Sender: TObject);
  private

    { Private declarations }
    OperatorNoName:string;
    ireturnNocard:Integer;
    procedure returnNoCard();
    procedure returnUseCard();

    function readCardNo: Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhauthCardOper: TfaqhauthCardOper;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhauthCardOper.Init;
begin
  inherited;
  {
  WorkView.FieldByName('交易卡号').DefaultValue := 0;
  WorkView.FieldByName('操作员代码').DefaultValue := '';
  WorkView.FieldByName('物理卡号').DefaultValue := '';
  WorkView.FieldByName('状态').DefaultValue := 0;
  WorkView.Reset;
  }
  btnLose.Caption:='挂失授权卡';
  btnRLose.Caption:='解挂授权卡';
  btnReturn.Caption:='&R 回收';
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
end;

procedure TfaqhauthCardOper.returnNoCard;
var
  tmpdataset:TDataSet;
  Pcardid:string;
  rCardNo:string;
begin
  tmpdataset := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  Pcardid := tmpdataset.fieldbyname('sname').AsString;
  rCardNo := tmpdataset.fieldbyname('lvol0').AsString;
  WorkView1.FieldByName('交易卡号').Data.SetInteger(StrToInt(rCardNo));
  WorkView1.FieldByName('操作员代码').Data.SetString(OperatorNoName);
  WorkView1.FieldByName('物理卡号').Data.SetString(Pcardid);
  WorkView1.FieldByName('无卡回收').Data.SetInteger(ireturnNocard);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
    ShowMessage('回收授权卡成功！');
end;

procedure TfaqhauthCardOper.returnUseCard;
var
  CardManage: TCardManage;
  Pcardid:string;
  cardNo:Integer;
  rCardNo:string;
  iReturnCard:Integer;
  tmpdataset:TDataSet;
  err_code:Integer;
begin
  CardManage:=nil;
  err_code:= 0;
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('请先打开串口！');
    Exit;
  end;
  try
    try
      CardManage := TCardManage.Create;
      if CardManage.ReadCardPhyID(PCardID) <> 0 then
      begin
        context.GetDialogSystem.ShowWarning('读卡序列号失败！');
        exit;
      end;
      cardNo := readCardNo;
      //判断读取的卡号和
      tmpdataset := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
      rCardNo := tmpdataset.fieldbyname('sname').AsString;
      if Trim(PCardID)<>Trim(rCardNo) then
      begin
        ShowMessage('你要回收的卡和你放置在读写器上的卡不一致，请检查！');
        Exit;
      end;
      iReturnCard := CardManage.ResetNewAuthCard(err_code);
      if iReturnCard<>0 then
      begin
        ShowMessage('回收授权卡失败--'+IntToStr(err_code));
        Exit;
      end;
        WorkView1.FieldByName('交易卡号').Data.SetInteger(cardNo);
        WorkView1.FieldByName('操作员代码').Data.SetString(OperatorNoName);
        WorkView1.FieldByName('物理卡号').Data.SetString(Pcardid);
        WorkView1.FieldByName('无卡回收').Data.SetInteger(ireturnNocard);
        WVRequest1.SendCommand;
        if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
          ShowMessage('回收授权卡成功！');
    except
      ShowMessage('回收授权卡失败，请重新回收或无卡回收！');
      Exit;
    end;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhauthCardOper.btnReturnClick(Sender: TObject);
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    ShowMessage('请先查询出要回收的授权卡，然后回收！');
    Exit;
  end;
  if cbxNoCard.Checked then
  begin
    if Application.MessageBox(PChar('你是否确定使用无卡回收该授权卡！'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
      Exit;
    ireturnNocard := 1;
    returnNoCard;
  end
  else
  begin
    if Application.MessageBox(PChar('你是否确定回收该授权卡！'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
      Exit;
    ireturnNocard := 0;
    returnUseCard;
  end;
  btnQuery.Click;
end;

procedure TfaqhauthCardOper.btnLoseClick(Sender: TObject);
var
  tmpdataset:TDataSet;
  operCode:string;
  iCardno:Integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    ShowMessage('请先查询出记录集，然后再操作！');
    Exit;
  end;
  if Application.MessageBox(PChar('你是否确定挂失该授权卡！'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  tmpdataset := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  iCardno := tmpdataset.fieldbyname('lvol0').AsInteger;
  operCode:=tmpdataset.fieldbyname('scust_limit').AsString;
  WorkView2.FieldByName('交易卡号').Data.SetInteger(iCardno);
  WorkView2.FieldByName('业务操作员号').Data.SetString(OperatorNoName);
  WorkView2.FieldByName('操作员代码').Data.SetString(operCode);
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('返回码').Data.AsInteger=0 then
    ShowMessage('挂失授权卡成功！');
  btnQuery.Click;
end;

procedure TfaqhauthCardOper.btnRLoseClick(Sender: TObject);
var
  CardManage: TCardManage;
  cardNo:Integer;
  rBlackVer:string;
  rCardNo:Integer;
  iRLoseCard:Integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    ShowMessage('请先查询出记录集，然后再操作！');
    Exit;
  end;
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('请先打开串口！');
    Exit;
  end;
  CardManage:=nil;
  try
    CardManage:=TCardManage.Create;
    cardNo:=readCardNo;
    WorkView3.FieldByName('业务操作员号').Data.SetString(OperatorNoName);
    WorkView3.FieldByName('交易卡号').Data.SetInteger(cardNo);
    WVRequest3.SendCommand;
    if WorkView3.FieldByName('返回码').Data.AsInteger=0 then
    begin
      rBlackVer := WorkView3.fieldbyname('黑名单版本').Data.AsString;
      rCardNo := WorkView3.fieldbyname('交易卡号').Data.AsInteger;
      if rCardNo<>readCardNo then
      begin
        ShowMessage('你要解挂的卡和放置的卡不是一张卡！');
        Exit;
      end;
      iRLoseCard := SMT_SetAuthNormalFlagByBlkVerion(PChar(rBlackVer));
      if iRLoseCard=0 then
        ShowMessage('解挂授权卡成功！');
      btnQuery.Click;
    end;
  finally
    CardManage.Destroy;
  end;
end;

function TfaqhauthCardOper.readCardNo: Integer;
var
  ireadAuthCard:Integer;
  PCM: TPublishCardMes;
begin
  ireadAuthCard := ReadAuthCardInfo(pcm);
  if ireadAuthCard<>0 then
  begin
    //ShowMessage('读取授权卡信息失败或该授权卡已经回收！');
    Result:=0;
  end
  else
    Result := StrToInt(pcm.CardNo);
end;

initialization
  TUIStdClassFactory.Create('授权卡操作',TfaqhauthCardOper);

end.
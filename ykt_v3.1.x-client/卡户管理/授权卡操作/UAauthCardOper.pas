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
  WorkView.FieldByName('���׿���').DefaultValue := 0;
  WorkView.FieldByName('����Ա����').DefaultValue := '';
  WorkView.FieldByName('������').DefaultValue := '';
  WorkView.FieldByName('״̬').DefaultValue := 0;
  WorkView.Reset;
  }
  btnLose.Caption:='��ʧ��Ȩ��';
  btnRLose.Caption:='�����Ȩ��';
  btnReturn.Caption:='&R ����';
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
end;

procedure TfaqhauthCardOper.returnNoCard;
var
  tmpdataset:TDataSet;
  Pcardid:string;
  rCardNo:string;
begin
  tmpdataset := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  Pcardid := tmpdataset.fieldbyname('sname').AsString;
  rCardNo := tmpdataset.fieldbyname('lvol0').AsString;
  WorkView1.FieldByName('���׿���').Data.SetInteger(StrToInt(rCardNo));
  WorkView1.FieldByName('����Ա����').Data.SetString(OperatorNoName);
  WorkView1.FieldByName('������').Data.SetString(Pcardid);
  WorkView1.FieldByName('�޿�����').Data.SetInteger(ireturnNocard);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger=0 then
    ShowMessage('������Ȩ���ɹ���');
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
    Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
    Exit;
  end;
  try
    try
      CardManage := TCardManage.Create;
      if CardManage.ReadCardPhyID(PCardID) <> 0 then
      begin
        context.GetDialogSystem.ShowWarning('�������к�ʧ�ܣ�');
        exit;
      end;
      cardNo := readCardNo;
      //�ж϶�ȡ�Ŀ��ź�
      tmpdataset := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
      rCardNo := tmpdataset.fieldbyname('sname').AsString;
      if Trim(PCardID)<>Trim(rCardNo) then
      begin
        ShowMessage('��Ҫ���յĿ���������ڶ�д���ϵĿ���һ�£����飡');
        Exit;
      end;
      iReturnCard := CardManage.ResetNewAuthCard(err_code);
      if iReturnCard<>0 then
      begin
        ShowMessage('������Ȩ��ʧ��--'+IntToStr(err_code));
        Exit;
      end;
        WorkView1.FieldByName('���׿���').Data.SetInteger(cardNo);
        WorkView1.FieldByName('����Ա����').Data.SetString(OperatorNoName);
        WorkView1.FieldByName('������').Data.SetString(Pcardid);
        WorkView1.FieldByName('�޿�����').Data.SetInteger(ireturnNocard);
        WVRequest1.SendCommand;
        if WorkView1.FieldByName('������').Data.AsInteger=0 then
          ShowMessage('������Ȩ���ɹ���');
    except
      ShowMessage('������Ȩ��ʧ�ܣ������»��ջ��޿����գ�');
      Exit;
    end;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhauthCardOper.btnReturnClick(Sender: TObject);
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    ShowMessage('���Ȳ�ѯ��Ҫ���յ���Ȩ����Ȼ����գ�');
    Exit;
  end;
  if cbxNoCard.Checked then
  begin
    if Application.MessageBox(PChar('���Ƿ�ȷ��ʹ���޿����ո���Ȩ����'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
      Exit;
    ireturnNocard := 1;
    returnNoCard;
  end
  else
  begin
    if Application.MessageBox(PChar('���Ƿ�ȷ�����ո���Ȩ����'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
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
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    ShowMessage('���Ȳ�ѯ����¼����Ȼ���ٲ�����');
    Exit;
  end;
  if Application.MessageBox(PChar('���Ƿ�ȷ����ʧ����Ȩ����'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  tmpdataset := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  iCardno := tmpdataset.fieldbyname('lvol0').AsInteger;
  operCode:=tmpdataset.fieldbyname('scust_limit').AsString;
  WorkView2.FieldByName('���׿���').Data.SetInteger(iCardno);
  WorkView2.FieldByName('ҵ�����Ա��').Data.SetString(OperatorNoName);
  WorkView2.FieldByName('����Ա����').Data.SetString(operCode);
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger=0 then
    ShowMessage('��ʧ��Ȩ���ɹ���');
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
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    ShowMessage('���Ȳ�ѯ����¼����Ȼ���ٲ�����');
    Exit;
  end;
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
    Exit;
  end;
  CardManage:=nil;
  try
    CardManage:=TCardManage.Create;
    cardNo:=readCardNo;
    WorkView3.FieldByName('ҵ�����Ա��').Data.SetString(OperatorNoName);
    WorkView3.FieldByName('���׿���').Data.SetInteger(cardNo);
    WVRequest3.SendCommand;
    if WorkView3.FieldByName('������').Data.AsInteger=0 then
    begin
      rBlackVer := WorkView3.fieldbyname('�������汾').Data.AsString;
      rCardNo := WorkView3.fieldbyname('���׿���').Data.AsInteger;
      if rCardNo<>readCardNo then
      begin
        ShowMessage('��Ҫ��ҵĿ��ͷ��õĿ�����һ�ſ���');
        Exit;
      end;
      iRLoseCard := SMT_SetAuthNormalFlagByBlkVerion(PChar(rBlackVer));
      if iRLoseCard=0 then
        ShowMessage('�����Ȩ���ɹ���');
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
    //ShowMessage('��ȡ��Ȩ����Ϣʧ�ܻ����Ȩ���Ѿ����գ�');
    Result:=0;
  end
  else
    Result := StrToInt(pcm.CardNo);
end;

initialization
  TUIStdClassFactory.Create('��Ȩ������',TfaqhauthCardOper);

end.
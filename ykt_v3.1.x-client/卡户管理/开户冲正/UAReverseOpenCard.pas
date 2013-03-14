unit UAReverseOpenCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,UtCardDll,
  RzStatus, RzPanel;

type
  TfaqhReverseOpenCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    edtSeriNo: TWVEdit;
    WVEdit6: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnReverse: TBitBtn;
    btnReadCard: TBitBtn;
    WVRReserveOpenCard: TWVRequest;
    WVReserveOpenCard: TWorkView;
    Label13: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    lbl1: TLabel;
    edtPwd: TWVEdit;
    cbbErrOperNo: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReverseClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhReverseOpenCard: TfaqhReverseOpenCard;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhReverseOpenCard.Init;
var
  strDate:string;
begin
  inherited;
  //strDate := FormatDateTime('yyyymmdd',Date);
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
end;

procedure TfaqhReverseOpenCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhReverseOpenCard.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('��ѯ����').Data.SetString('1');
  btnReverse.Enabled := False;
  inherited;
  btnReverse.Enabled := True;
end;

procedure TfaqhReverseOpenCard.btnReverseClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  operDate:string;
  seriId:Integer;
  stationId:Integer;
  CardManage : TCardManage;
  ResInt2:Integer;
  phyId:string;
  PCardID:string;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  tradeNum:Integer;
  operCode:string;
  operPwd:string;
begin
  if Application.MessageBox('���Ҫ�����ü�¼����ѿ����õ���д���ϣ�ȷ��Ҫ������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tmpDataSet := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //��ȡ���״���
    if CardManage.ReadCardConsumeInfo(LPI, nPacketNo)=False then
    begin
      //Context.GetDialogSystem.ShowMessage('��ȡ������Ϣʧ�ܣ��źÿ����½��иò�����');
      //Exit;
      tradeNum := 0;
    end
    else
    begin
      tradeNum := StrToInt(format('%d', [LPI.DealTimes]));
    end;
    operDate := tmpDataSet.fieldbyname('sdate3').AsString;
    seriId := tmpDataSet.fieldbyname('lserial1').AsInteger;
    stationId := tmpDataSet.fieldbyname('lwithdraw_flag').AsInteger;
    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    //WorkView.FieldByName('������').Data.SetString(operPwd);
    WVReserveOpenCard.FieldByName('ҵ������').Data.SetString(operDate);
    WVReserveOpenCard.FieldByName('��ˮ��').Data.SetInteger(seriId);
    WVReserveOpenCard.FieldByName('�ն˱��').Data.SetInteger(stationId);
    WVReserveOpenCard.FieldByName('���״���').Data.SetInteger(tradeNum);
    //WVReserveOpenCard.FieldByName('��֤����Ա').Data.SetString(Trim(edtOper.text));
    WVReserveOpenCard.FieldByName('����Ա����').Data.SetString(operPwd);
    WVReserveOpenCard.FieldByName('�Ƿ���Ȩ').Data.SetString('1');
    WVRReserveOpenCard.SendCommand;
    phyId := WVReserveOpenCard.FieldByName('������').Data.AsString;
    //ȡ������
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('��������ʧ�ܣ������³����ý��ף�');
      exit;
    end;

    if PCardID<>phyId then
    begin
      Context.GetDialogSystem.ShowMessage('Ҫ�����Ŀ��ͷ��õĿ�����ͬһ�ſ��������²�����');
      Exit;
    end;
    try
      ResInt2 := CardManage.ClearCard;
      if ResInt2=0 then
      begin
        CardManage.ControlBuzzer;
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ������ɹ���');
        //CardManage.ControlBuzzer;
        RzStatusPane1.Caption := WVReserveOpenCard.fieldbyname('������Ϣ').Data.AsString;
        btnQuery.Click;
      end
      else
        Context.GetDialogSystem.ShowMessage('�ڳ���ʱû����տ���Ϣ���뵥����ոÿ���Ϣ��');
    except
      Context.GetDialogSystem.ShowMessage('�ڳ���ʱû����տ���Ϣ���뵥����ոÿ���Ϣ��');
    end;
  finally
    CardManage.Destroy;
  end;
  edtPwd.Text := '';
end;

procedure TfaqhReverseOpenCard.btnReadCardClick(Sender: TObject);
begin
  edtCardNo.Text:=readCardNo;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('��������',TfaqhReverseOpenCard);

end.
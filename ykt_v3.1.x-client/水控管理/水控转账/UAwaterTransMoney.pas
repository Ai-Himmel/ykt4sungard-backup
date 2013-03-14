unit UAwaterTransMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, UtCardDll;

type
  TfaqhwaterTransMoney = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    WVRBackState: TWVRequest;
    WVBackState: TWorkView;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    GroupBox1: TGroupBox;
    edtsmlMoney: TWVEdit;
    edtMoney: TWVEdit;
    edtNo: TWVEdit;
    edtName: TWVEdit;
    edtCardNo: TWVEdit;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    grp1: TGroupBox;
    edtAddMoney: TWVEdit;
    RzStatusPane6: TRzStatusPane;
    btnTran: TBitBtn;
    btnReadCard: TButton;
    procedure btnTranClick(Sender: TObject);
    procedure edtAddMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
    bigMoney:Integer;
    bigCnt:Integer;
    smallMoney:Integer;
    smallCnt:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhwaterTransMoney: TfaqhwaterTransMoney;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterTransMoney.Init;
begin
  inherited;
  {
  WorkView1.FieldByName('���׿���').DefaultValue := 0;
  WorkView1.FieldByName('��ֵ���').DefaultValue := 0.00;
  WorkView1.FieldByName('����Ա����').DefaultValue := '';
  WorkView1.FieldByName('��Ǯ�����').DefaultValue := 0.00;
  WorkView1.FieldByName('��Ǯ������').DefaultValue := 0;
  WorkView1.FieldByName('СǮ������').DefaultValue := 0;
  WorkView1.FieldByName('СǮ�����').DefaultValue := 0.00;
  WorkView1.Reset;
  }
  btnTran.Enabled := False;
end;

procedure TfaqhwaterTransMoney.btnTranClick(Sender: TObject);
var
  operatorNoName:string;  //����Ա
  CardManage: TCardManage;
  st:Integer;
  consumeId:Integer;
  buyWaterId:Integer;
  smloutmoney,bigoutmoney:Real;
  smlMoney,bigMoney:LongInt;
begin
  CardManage := nil;
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  WorkView1.FieldByName('����Ա����').Data.SetString(operatorNoName);
  WorkView1.FieldByName('СǮ������').Data.SetInteger(smallCnt);
  WorkView1.FieldByName('��Ǯ������').Data.SetInteger(bigCnt);
  WorkView1.FieldByName('���׿���').Data.SetInteger(StrToInt(edtCardNo.Text));
  WorkView1.FieldByName('��Ǯ�����').Data.SetFloat(StrToFloat(edtMoney.Text));
  WorkView1.FieldByName('СǮ�����').Data.SetFloat(StrToFloat(edtsmlMoney.Text));
  WVRequest1.SendCommand;
  //��̨��ֵ�ɹ���д��
  if WorkView1.fieldbyname('������').data.asinteger<>0 then
  begin
    getReturn('',WorkView);
    showmessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  consumeId:=WorkView1.fieldbyname('��̨��ˮ��').Data.AsInteger;
  buyWaterId:=WorkView1.fieldbyname('��ˮ��̨��ˮ��').Data.AsInteger;
  smloutmoney:=WorkView1.fieldbyname('СǮ�����').Data.AsFloat;
  bigoutmoney:=WorkView1.fieldbyname('��Ǯ�����').Data.AsFloat;
  smlMoney:=Round(smloutmoney*100);
  bigMoney:=Round(bigoutmoney*100);
  try
    CardManage := TCardManage.Create;
    //��Ǯ
    st :=CardManage.setCardMoney(bgPacketNo,bigMoney);
    if st<>0 then
    begin
      //д�������лع�����
      WVBackState.FieldByName('������ˮ').Data.SetInteger(consumeId);
      WVBackState.FieldByName('��ֵ��ˮ').Data.SetInteger(buyWaterId);
      WVBackState.FieldByName('ʧ�ܱ�־').Data.SetInteger(0);
      WVRBackState.SendCommand;
      Context.GetDialogSystem.ShowMessage('��Ǯ����Ϣʧ�ܣ��벹дˮ��Ǯ����Ϣ��');
      Exit;
    end;

    //��Ǯ
    st :=CardManage.setCardMoney(SmlPacketNo,smlMoney);
    if st<>0 then
    begin
      //д�������лع�����
      WVBackState.FieldByName('������ˮ').Data.SetInteger(consumeId);
      WVBackState.FieldByName('��ֵ��ˮ').Data.SetInteger(buyWaterId);
      WVBackState.FieldByName('ʧ�ܱ�־').Data.SetInteger(1);
      WVRBackState.SendCommand;
      Context.GetDialogSystem.ShowMessage('ˮ��Ǯ����Ǯʧ�ܣ��벹дˮ��Ǯ����Ϣ��');
      Exit;
    end;
    ShowMessage('ˮ��ת�˳ɹ�--'+WorkView1.FieldByName('������Ϣ').Data.AsString);
    edtAddMoney.Text:='0';
    btnTran.Enabled := False;
  finally
    CardManage.Destroy;
  end;
  btnPrint.Enabled:=False;
end;

procedure TfaqhwaterTransMoney.edtAddMoneyKeyPress(Sender: TObject;var Key: Char);
begin
  inherited;
  if Checkedt(Key,edtAddMoney.Text)=False then
    Key := #0;

end;

procedure TfaqhwaterTransMoney.btnReadCardClick(Sender: TObject);
var
  CardManage: TCardManage;
  PCM: TPublishCardMes;
  re: string;
  st:SmallInt;
begin
  CardManage := nil;
  if PrepareReadCardInfo=False then
    Exit;
  try
    CardManage := TCardManage.Create;
    if CardManage.ReadCardPhyID(re) <> 0 then
    begin
      showmessage('�������к�ʧ��,�ÿ��Ѿ��𻵣�');
      Exit;
    end;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      showmessage('������Ϣʧ�ܣ������: ' + IntToStr(st));
      Exit;
    end
    else
    begin
      edtCardNo.Text:=PCM.CardNo;
      edtName.Text:=PCM.ucName;
      edtNo.Text:=PCM.ucCardNo;
    end;
    st := CardManage.ReadBalance(SmlPacketNo,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      ShowMessage('��ȡСǮ��ʧ�ܣ�');
      Exit;
    end
    else
    begin
      edtsmlMoney.Text:=format('%f', [smallMoney / 100.0]);
    end;
    st := CardManage.ReadBalance(bgPacketNo,@bigMoney,@bigCnt);
    if st <> 0 then
      showmessage('���û���������Ϣʧ�ܣ������: ' + IntToStr(st))
    else
      edtmoney.Text:=format('%f', [bigMoney / 100.0]);
    btnTran.Enabled := true;
  finally
    CardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('ˮ��Ǯ����ֵ',TfaqhwaterTransMoney);

end.
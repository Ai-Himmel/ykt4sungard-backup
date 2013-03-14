unit UAwaterCardPatch;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzStatus, Buttons, UtCardDll;

type
  TfaqhwaterCardPatch = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    Label1: TLabel;
    edtCardNo: TWVEdit;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    Label4: TLabel;
    WVEdit4: TWVEdit;
    Label5: TLabel;
    WVEdit1: TWVEdit;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    WVRReCreCardOK: TWVRequest;
    WVReCreCardOK: TWorkView;
    WorkView3: TWorkView;
    WVRequest3: TWVRequest;
    btnPacth: TBitBtn;
    btnReadCardQuery: TBitBtn;
    RzStatusPane1: TRzStatusPane;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure btnPacthClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhwaterCardPatch: TfaqhwaterCardPatch;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterCardPatch.Init;
begin
  inherited;
  WorkView.FieldByName('��ʾ����').DefaultValue := '';
  WorkView.FieldByName('ѧ����').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('���֤��').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := 0;
  WorkView.Reset;
end;

procedure TfaqhwaterCardPatch.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhwaterCardPatch.btnQueryClick(Sender: TObject);
begin
  if Trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('ѧ����').Data.SetString('');
  end;
  if Trim(edtCardNo.Text)='' then
    WorkView.FieldByName('����').Data.SetInteger(0);
  inherited;

end;

procedure TfaqhwaterCardPatch.btnReadCardQueryClick(Sender: TObject);
begin
  inherited;
  edtCardNo.Text:=readCardNo;
  btnQuery.Click();
end;

procedure TfaqhwaterCardPatch.btnPacthClick(Sender: TObject);
var
  BackSerilID: integer;
  CardPhyID: string;
  tempDataSet: TDataSet;
  CardID: integer;
  EMoneyInCard: string;
  CardManage: TCardManage;
  OperatorNoName: string;
  TranExID: integer;
  isOldCard: Boolean;
  dealNum :integer;
  cardMoney:LongInt;         //�����
  backTradeID:Integer;
  iPacket:Integer;
  re:Integer;
  money:Integer;
begin
  if PrepareReadCardInfo=False then
    Exit;

  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('û�����ݣ��޷����д˲�����');
    Exit;
  end;

  //ȡ��ǰ��ѯ���ݼ�
  tempDataSet := WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
  TranExID := tempDataSet.FieldByName('lvol2').AsInteger;
  iPacket := tempDataSet.FieldByName('lvol4').AsInteger;
  CardManage := TCardManage.Create;

  //ȡ�������к� CardPhyID
  CardPhyID := '';
  if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ���������к�ʧ�ܣ�');
    CardManage.Destroy;
    Exit; 
  end;

  //�жϽ��׺ţ�ȷ�����Ƿ�Ϊ�·��Ŀ�
  if ((TranExID = 847101) or (TranExID = 847125) or (TranExID = 847116) or
    (TranExID = 847104)) then
  begin
    isOldCard := False;
  end
  else
  begin
    isOldCard := True;
  end;
  if isOldCard = False then
  begin
    //���
    EMoneyInCard := '0.00';
    //���״���
    dealNum := 0;
  end
  else if isOldCard = True then
  begin
    //����Ƿ����¿����׳����򲻶����ϵ����
    //������������׳�����Ҫ��ȡ���ϵ����
    //TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
    re := CardManage.ReadBalance(iPacket+1,@Money,@dealNum);
    if re <> 0 then
    begin
      Context.GetDialogSystem.ShowWarning('���û���������Ϣʧ��-'+inttostr(re));
      CardManage.Destroy;
      Exit;
    end
    else
    begin
      EMoneyInCard := format('%f', [Money / 100.0]);
    end;
  end;

  CardID := tempDataSet.FieldByName('lvol0').AsInteger;
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;

  //���ù��ܺţ����̨д��Ϣ
  WorkView2.FieldByName('������').Data.SetString(CardPhyID);
  WorkView2.FieldByName('����ʶ').Data.SetInteger(CardID);
  WorkView2.FieldByName('�뿨ֵ').Data.SetFloat(StrToFloat(EMoneyInCard));
  WorkView2.FieldByName('����Ա��').Data.SetString(OperatorNoName);
  WorkView2.FieldByName('�豸��').Data.SetInteger(SmartCardSubSystemNo);
  WorkView2.FieldByName('����վ��').Data.SetInteger(SmartCardSubSystemNo);
  WorkView2.FieldByName('���״���').Data.SetInteger(dealNum);
  WorkView2.FieldByName('Ǯ����').Data.SetInteger(iPacket);
  WVRequest2.SendCommand;
  
  if WorkView2.fieldbyname('������').data.asinteger=0 then
  begin
    BackSerilID:=WorkView2.FieldByName('��̨������ˮ��').Data.AsInteger;
    CardID:=WorkView2.FieldByName('���׿���').Data.AsInteger;

    //��������·��еĿ���ֻ��Ҫ���¿����
    if isOldCard=True then
    begin
      cardMoney := StrToInt(FloatToStr(WorkView2.fieldbyname('����ֵ').Data.AsFloat* 100));
      backTradeID:=WorkView2.fieldbyname('��̨������ˮ��').Data.Asinteger;
      //ʹ���µ�����Ǯ����Ϣ����setCardMoney(nPacketNo, money: Integer)��0�ɹ�
      re := CardManage.setCardMoney(iPacket+1,Cardmoney);
      if re=0 then
      begin
        CardManage.ControlBuzzer;
        RzStatusPane1.Caption:='��д���ɹ��������Ϊ:'+FloatToStr(WorkView2.fieldbyname('����ֵ').Data.AsFloat);
      end
      else
      begin
        WorkView3.FieldByName('����ʶ').Data.SetInteger(CardID);
        WorkView3.FieldByName('��̨������ˮ��').Data.SetInteger(backTradeID);
        WorkView3.FieldByName('������').Data.SetInteger(847119);
        WVRequest3.SendCommand;
        Context.GetDialogSystem.ShowSuccess('д��ʧ��:'+'--��״̬Ϊд��ʧ��״̬�������²�д����Ϣ��');
        RzStatusPane1.Caption:='д��ʧ��:'+'--��״̬Ϊд��ʧ��״̬�������²�д����Ϣ��';
        CardManage.Destroy;
        exit;
      end;
    end;
    WVReCreCardOK.FieldByName('Ǯ����').Data.SetInteger(iPacket);
    WVReCreCardOK.FieldByName('����ʶ').Data.SetInteger(CardID);
    WVReCreCardOK.FieldByName('������').Data.SetInteger(847119);
    WVReCreCardOK.FieldByName('������ˮ��').Data.SetInteger(BackSerilID);
    WVRReCreCardOK.SendCommand;
  end
  else
  begin
    getReturn('',WorkView2);
    RzStatusPane1.Caption:=WorkView2.FieldByName('������Ϣ').Data.AsString;
  end;

  MainRequest.SendCommand;
  CardManage.Destroy;
end;

initialization
  TUIStdClassFactory.Create('ˮ�ؿ���Ϣ��д',TfaqhwaterCardPatch);

end.
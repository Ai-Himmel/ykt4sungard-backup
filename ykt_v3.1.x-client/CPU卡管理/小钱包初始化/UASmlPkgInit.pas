unit UASmlPkgInit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, CardDll,WaterDll, RzPanel, RzRadGrp,
  UIncrementComboBox;

type
  TfaqhSmlPkgInit = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnReadCard: TButton;
    grp1: TGroupBox;
    rzstspn2: TRzStatusPane;
    cbbSmlNo: TWVComboBox;
    lbl1: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVWaterPrice: TWorkView;
    WVRWaterPrice: TWVRequest;
    procedure btnReadCardClick(Sender: TObject);
  private
    { Private declarations }
    //function ifincludehz(strtxt:string):boolean;
    function initSmlBag(cardno,custId,custType:Integer;cardEndDate,oldPhyId:string;smlBagNo:Integer):Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSmlPkgInit: TfaqhSmlPkgInit;

implementation

uses KsFrameworks,KSClientConsts;
     
{$R *.DFM}

procedure TfaqhSmlPkgInit.Init;
begin
  inherited;
  cbbSmlNo.ItemIndex := 0;
  //cbbWaterType.ItemIndex := waterType;
end;

procedure TfaqhSmlPkgInit.btnReadCardClick(Sender: TObject);
var
  cm: TCM;
  st:Integer;
  waterPack:TWATERCOMMPACK;
  smlPhyId:string;
  smlbgNo:Integer;
  //expireddate:string;
  cardId,custId,feeType,expDate:string;
  //smlPkgName:string;
begin
  if preReadCard=False then
    Exit;
  try
    smlbgNo := StrToInt(Copy(cbbSmlNo.Text,1,Pos('-',cbbSmlNo.Text)-1));
    if (smlbgNo<=0) then
    begin
      Context.GetDialogSystem.ShowMessage('Ǯ�����ʹ���,������ѡ��');
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ��ʼ����Ǯ������');
      Exit;
    end;
  end;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ�--'+inttostr(st));
      Exit;
    end;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CUST_NO);
    cm.setfieldreadmode(CARD_LIMIT_TYPE);
    //����Ҫ��ȡ���ݵ�Ȩ��
    st := cm.readCard(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����Ϣʧ�ܣ���źÿ������¶�ȡ-'+inttostr(st));
      Exit;
    end;
    cardId := cm.getCardNo;
    custId := cm.getCustNo;
    feeType := cm.getCardLimitType;
    try
      if (StrToInt(cardId)<=0)or (StrToInt(feeType)<=0) then
      begin
        Context.GetDialogSystem.ShowMessage('�ÿ��Ŀ��Ż��շ������ȷ����鿴�ÿ��Ƿ��ѷ��У�');
        Exit;
      end;
      if custId='' then
        custId := '0';
    except
      Context.GetDialogSystem.ShowMessage('�ÿ��Ŀ��Ż��շ������ȷ����鿴�ÿ��Ƿ��ѷ��У�');
      Exit;
    end;
    //�ۿ�ɹ���ʼдˮ����� ,д֮ǰҪ��Ѱ��
    //��СǮ����Ϣ

    st := mfcard(smlPhyId);
    if st=0 then
    begin
      preCommWaterPack(waterPack);
      st := ks_water_readmoney(smlbgNo,@waterPack);
      if st = 0 then
      begin
        Context.GetDialogSystem.ShowMessage('��СǮ���Ѿ�����ʼ����');
        Exit;
      end;
    end;

    setWaterPrice(WVWaterPrice,WVRWaterPrice,StrToInt(feeType));
    expDate := FormatDateTime('yyyymmdd',Date+waterExpiredate);
    st := initSmlBag(StrToInt(cardId),StrToInt(custId),StrToInt(feeType),expDate,smlPhyId,smlbgNo);
    if st=0 then
    begin
      cm.beep;
      RzStatusPane1.Caption:='<'+cbbSmlNo.Text+'>СǮ����ʼ���ɹ���';
    end
    else
    begin
      RzStatusPane1.Caption:='<'+cbbSmlNo.Text+'>СǮ����ʼ��ʧ�ܣ�ʧ��ԭ��<'+getErrMsg+'>';
    end;
    Context.GetDialogSystem.ShowMessage(RzStatusPane1.Caption);
  finally
    cm.Destroy;
  end;
end;

function TfaqhSmlPkgInit.initSmlBag(cardno, custId, custType: Integer;
  cardEndDate, oldPhyId: string;smlBagNo:Integer): Integer;
var
  waterCard:TWATERCOMMPACK;
  st:Integer;
  phyId:string;
begin
  st := mfcard(phyId);
  if st<>0 then
  begin
    //Ѱ��ʧ��
    result := -100;
    Exit;
  end;
  if phyId<>oldPhyId then
  begin
    //Ҫ��ʼ����СǮ������������ͬһ�ſ�
    Result := -200;
    Exit;
  end;
  waterCard.cardno := cardNo;
  waterCard.custno := custId;
  watercard.custtype := custType;
  StrCopy(@waterCard.expireddate,PChar(cardEndDate));
  waterCard.lockflag := 255;
  waterCard.money := 0;
  waterCard.totalmoney := 0;
  StrCopy(@waterCard.addtime,PChar('00000000000000'));
  waterCard.addcount := 0;
  waterCard.price1 := cpuWaterPrice1;
  waterCard.price2 := cpuWaterPrice2;
  waterCard.price3 := cpuWaterPrice3;
  //ShowMessage(waterStrings[i]);
  st := ks_water_publishcard(smlBagNo,@waterCard);
  if st<>0 then
  begin
    Result := st;
    Exit;
  end;
  result := 0;
end;

initialization
  TUIStdClassFactory.Create('СǮ����ʼ��',TfaqhSmlPkgInit);

end.
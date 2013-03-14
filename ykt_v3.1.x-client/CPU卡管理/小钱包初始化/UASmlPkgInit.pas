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
      Context.GetDialogSystem.ShowMessage('钱包类型错误,请重新选择！');
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('请选择要初始化的钱包类型');
      Exit;
    end;
  end;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡--'+inttostr(st));
      Exit;
    end;
    //先清除所有的读取权限
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CUST_NO);
    cm.setfieldreadmode(CARD_LIMIT_TYPE);
    //设置要读取内容的权限
    st := cm.readCard(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取卡信息失败，请放好卡后重新读取-'+inttostr(st));
      Exit;
    end;
    cardId := cm.getCardNo;
    custId := cm.getCustNo;
    feeType := cm.getCardLimitType;
    try
      if (StrToInt(cardId)<=0)or (StrToInt(feeType)<=0) then
      begin
        Context.GetDialogSystem.ShowMessage('该卡的卡号或收费类别不正确，请查看该卡是否已发行！');
        Exit;
      end;
      if custId='' then
        custId := '0';
    except
      Context.GetDialogSystem.ShowMessage('该卡的卡号或收费类别不正确，请查看该卡是否已发行！');
      Exit;
    end;
    //扣款成功开始写水控余额 ,写之前要先寻卡
    //读小钱包信息

    st := mfcard(smlPhyId);
    if st=0 then
    begin
      preCommWaterPack(waterPack);
      st := ks_water_readmoney(smlbgNo,@waterPack);
      if st = 0 then
      begin
        Context.GetDialogSystem.ShowMessage('该小钱包已经被初始化！');
        Exit;
      end;
    end;

    setWaterPrice(WVWaterPrice,WVRWaterPrice,StrToInt(feeType));
    expDate := FormatDateTime('yyyymmdd',Date+waterExpiredate);
    st := initSmlBag(StrToInt(cardId),StrToInt(custId),StrToInt(feeType),expDate,smlPhyId,smlbgNo);
    if st=0 then
    begin
      cm.beep;
      RzStatusPane1.Caption:='<'+cbbSmlNo.Text+'>小钱包初始化成功！';
    end
    else
    begin
      RzStatusPane1.Caption:='<'+cbbSmlNo.Text+'>小钱包初始化失败，失败原因<'+getErrMsg+'>';
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
    //寻卡失败
    result := -100;
    Exit;
  end;
  if phyId<>oldPhyId then
  begin
    //要初始化的小钱包和主卡不是同一张卡
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
  TUIStdClassFactory.Create('小钱包初始化',TfaqhSmlPkgInit);

end.
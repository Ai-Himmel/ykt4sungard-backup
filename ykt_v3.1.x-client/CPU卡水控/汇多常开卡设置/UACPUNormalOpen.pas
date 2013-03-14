unit UACPUNormalOpen;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, CardDll,WaterDll, RzPanel, RzRadGrp,
  UIncrementComboBox;

type
  TfaqhNormalOpen = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    GroupBox1: TGroupBox;
    edtMoney: TWVEdit;
    edtNo: TWVEdit;
    edtName: TWVEdit;
    edtCardNo: TWVEdit;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    btnReadCard: TButton;
    rzstspn1: TRzStatusPane;
    edtBigNum: TWVEdit;
    btnNorOpen: TButton;
    btnNormal: TButton;
    RzStatusPane8: TRzStatusPane;
    edtPhyId: TWVEdit;
    rzstspn3: TRzStatusPane;
    edtOpenCard: TWVEdit;
    procedure btnReadCardClick(Sender: TObject);
    procedure btnNorOpenClick(Sender: TObject);
    procedure btnNormalClick(Sender: TObject);
  private
    { Private declarations }
    //function ifincludehz(strtxt:string):boolean;

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhNormalOpen: TfaqhNormalOpen;

implementation

uses KsFrameworks,KSClientConsts;
     
{$R *.DFM}

procedure TfaqhNormalOpen.Init;
begin
  inherited;
  //cbbSmlNo.ItemIndex := 0;
  //cbbWaterType.ItemIndex := waterType;
end;

procedure TfaqhNormalOpen.btnReadCardClick(Sender: TObject);
var
  cm: TCM;
  st:Integer;
  //waterPack:TWATERCOMMPACK;
  smlPhyId:string;
  //smlbgNo:Integer;
  //expireddate:string;
begin
  //if ifincludehz(sAppPath)=True then
    //ShowMessage('ddd');
  if preReadCard=False then
    Exit;
    {
  try
    smlbgNo := StrToInt(Copy(cbbSmlNo.Text,1,Pos('-',cbbSmlNo.Text)-1));
    if (smlbgNo<=0) then
    begin
      Context.GetDialogSystem.ShowMessage('水控类型错误,请重新选择！');
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('请选择要读取的水控类型');
      Exit;
    end;
  end;
  }
  {
  if cbbWaterType.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择水控设备！');
    cbbWaterType.SetFocus;
    Exit;
  end;
  }
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
    cm.setfieldreadmode(CUST_NAME);
    cm.setfieldreadmode(STUEMP_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CF_NORMALLYOPEN);
    //设置要读取内容的权限
    //setOperReadMode(cm);
    st := cm.readCard(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取卡信息失败，请放好卡后重新读取-'+inttostr(st));
      Exit;
    end;
    edtPhyId.Text := smlPhyId;
    edtCardNo.Text := cm.getCardNo;
    edtName.Text := cm.getCustName;
    edtNo.Text := cm.getStuempNo;
    edtMoney.Text := format('%f', [strtofloat(cm.getCardBalance) / 100.0]);
    edtBigNum.Text := cm.getDptCardCnt;
    if cm.getWaterNorOpen='153' then
      //rgOpenCard.ItemIndex := 1
      edtOpenCard.Text := '常开卡'
    else
      edtOpenCard.Text := '正常卡';
      //rgOpenCard.ItemIndex := 0;

    //扣款成功开始写水控余额 ,写之前要先寻卡
    //读小钱包信息
    st := mfcard(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('水控钱包寻卡失败--'+inttostr(st));
      Exit;
    end;
    {
    preCommWaterPack(waterPack);
    st := ks_water_readmoney(smlbgNo,@waterPack);
    if st = 0 then
    begin
      edtsmlMoney1.Text := format('%f', [waterPack.money / 100.0]);
      edtTotalMoney.Text := format('%f', [waterPack.totalmoney / 100.0]);
      expireddate := waterPack.expireddate;
      //ShowMessage(expireddate);
      edtExpireDate.Text := expireddate;

      edtP1.Text := IntToStr(waterPack.price1);
      edtP2.Text := IntToStr(waterPack.price2);
      edtP3.Text := IntToStr(waterPack.price3);
      
    end
    else
      Context.GetDialogSystem.ShowMessage('读取小钱包失败--'+inttostr(st));  }
  finally
    cm.Destroy;
  end;
end;
{
function TfaqhwaterInfo_cqcsgl.ifincludehz(strtxt: string): boolean;
var
  i:integer;
begin
  //先判断要截取的字符串最后一个字节的类型
  //如果为汉字的第一个字节则减(加)一位
  result:=false;
  for i:=0 to length(strtxt) do
  begin
    if ByteType(strtxt,i) = mbLeadByte then
    begin
      result:=true;
      break;
    end;
  end;
end;
}
procedure TfaqhNormalOpen.btnNorOpenClick(Sender: TObject);
var
  cm:TCM;
  re:Integer;
  phyId:string;
begin
  cm := nil;
  try
    cm := TCM.Create;
    re := cm.card(phyId);
    if re<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，放置好卡重新读取--'+inttostr(re));
      exit;
    end;
    {
    if phyId<>edtphyid.Text then
    begin
      reCode := -4;
      context.GetDialogSystem.ShowMessage('放置的卡物理编号和发送交易的卡物理编号不符，请冲正该交易！');
      exit;
    end;
    }
    cm.clearallfieldwritemode;
    cm.setWaterNorOpen('153');
    re := cm.writeData(phyId);
    if re<>0 then
      context.GetDialogSystem.ShowMessage('设置卡为常开卡失败--'+inttostr(re))
    else
      cm.beep;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhNormalOpen.btnNormalClick(Sender: TObject);
var
  cm:TCM;
  re:Integer;
  phyId:string;
begin
  cm := nil;
  try
    cm := TCM.Create;
    re := cm.card(phyId);
    if re<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，放置好卡重新读取--'+inttostr(re));
      exit;
    end;
    {
    if phyId<>edtphyid.Text then
    begin
      reCode := -4;
      context.GetDialogSystem.ShowMessage('放置的卡物理编号和发送交易的卡物理编号不符，请冲正该交易！');
      exit;
    end;
    }
    cm.clearallfieldwritemode;
    cm.setWaterNorOpen('0');
    re := cm.writeData(phyId);
    if re<>0 then
      context.GetDialogSystem.ShowMessage('设置卡为正常卡失败--'+inttostr(re))
    else
      cm.beep;
  finally
    cm.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('常开卡设置',TfaqhNormalOpen);

end.
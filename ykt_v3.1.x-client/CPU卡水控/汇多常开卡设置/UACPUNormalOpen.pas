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
      Context.GetDialogSystem.ShowMessage('ˮ�����ʹ���,������ѡ��');
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ��ȡ��ˮ������');
      Exit;
    end;
  end;
  }
  {
  if cbbWaterType.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��ˮ���豸��');
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
      Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ�--'+inttostr(st));
      Exit;
    end;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CUST_NAME);
    cm.setfieldreadmode(STUEMP_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CF_NORMALLYOPEN);
    //����Ҫ��ȡ���ݵ�Ȩ��
    //setOperReadMode(cm);
    st := cm.readCard(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����Ϣʧ�ܣ���źÿ������¶�ȡ-'+inttostr(st));
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
      edtOpenCard.Text := '������'
    else
      edtOpenCard.Text := '������';
      //rgOpenCard.ItemIndex := 0;

    //�ۿ�ɹ���ʼдˮ����� ,д֮ǰҪ��Ѱ��
    //��СǮ����Ϣ
    st := mfcard(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('ˮ��Ǯ��Ѱ��ʧ��--'+inttostr(st));
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
      Context.GetDialogSystem.ShowMessage('��ȡСǮ��ʧ��--'+inttostr(st));  }
  finally
    cm.Destroy;
  end;
end;
{
function TfaqhwaterInfo_cqcsgl.ifincludehz(strtxt: string): boolean;
var
  i:integer;
begin
  //���ж�Ҫ��ȡ���ַ������һ���ֽڵ�����
  //���Ϊ���ֵĵ�һ���ֽ����(��)һλ
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
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ����úÿ����¶�ȡ--'+inttostr(re));
      exit;
    end;
    {
    if phyId<>edtphyid.Text then
    begin
      reCode := -4;
      context.GetDialogSystem.ShowMessage('���õĿ������źͷ��ͽ��׵Ŀ������Ų�����������ý��ף�');
      exit;
    end;
    }
    cm.clearallfieldwritemode;
    cm.setWaterNorOpen('153');
    re := cm.writeData(phyId);
    if re<>0 then
      context.GetDialogSystem.ShowMessage('���ÿ�Ϊ������ʧ��--'+inttostr(re))
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
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ����úÿ����¶�ȡ--'+inttostr(re));
      exit;
    end;
    {
    if phyId<>edtphyid.Text then
    begin
      reCode := -4;
      context.GetDialogSystem.ShowMessage('���õĿ������źͷ��ͽ��׵Ŀ������Ų�����������ý��ף�');
      exit;
    end;
    }
    cm.clearallfieldwritemode;
    cm.setWaterNorOpen('0');
    re := cm.writeData(phyId);
    if re<>0 then
      context.GetDialogSystem.ShowMessage('���ÿ�Ϊ������ʧ��--'+inttostr(re))
    else
      cm.beep;
  finally
    cm.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('����������',TfaqhNormalOpen);

end.
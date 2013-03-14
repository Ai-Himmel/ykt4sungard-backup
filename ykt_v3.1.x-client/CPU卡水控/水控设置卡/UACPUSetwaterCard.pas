unit UACPUSetwaterCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, CardDll,WaterDll, RzPanel, RzRadGrp;

type
  TfaqhSetWaterCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    GroupBox1: TGroupBox;
    edtTransMoney: TWVEdit;
    RzStatusPane4: TRzStatusPane;
    btnReadCard: TButton;
    rzstspn1: TRzStatusPane;
    edtUnitMoney: TWVEdit;
    lbl3: TLabel;
    btnReleaseCard: TButton;
    rzstspn4: TRzStatusPane;
    rgWaterType: TRzRadioGroup;
    RzStatusPane6: TRzStatusPane;
    rgCardFlag: TRzRadioGroup;
    lbl4: TLabel;
    btnReadWaterFee: TButton;
    RzStatusPane1: TRzStatusPane;
    edtMin: TWVEdit;
    RzStatusPane2: TRzStatusPane;
    edtMax: TWVEdit;
    Label1: TLabel;
    Label2: TLabel;
    RzStatusPane3: TRzStatusPane;
    edtUnit: TWVEdit;
    Label3: TLabel;
    procedure btnReadCardClick(Sender: TObject);
    procedure btnReleaseCardClick(Sender: TObject);
    procedure btnReadWaterFeeClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetWaterCard: TfaqhSetWaterCard;

implementation

uses KsFrameworks, KSClientConsts;
     
{$R *.DFM}

procedure TfaqhSetWaterCard.Init;
begin
  inherited;
  //cbbWaterType.ItemIndex := waterType;
end;

function HexStrToByteBuf(sHexStr:string;var Buf:array of Byte):integer;
var
i:integer;
begin
  i:=0;
  while sHexStr<>'' do
  begin
   Buf[i]:=Byte(strtoint('$'+Copy(sHexStr,1,2)));
   delete(sHexStr,1,2);
   inc(i);
  end;
end;

procedure TfaqhSetWaterCard.btnReadCardClick(Sender: TObject);
var
  st:Integer;
  rePhyid : array[0..16] of Char;
begin
  if preReadCard=False then
    Exit;
  if Application.MessageBox('你确定要清空该水控设置卡吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  st := ks_card(PChar(@rePhyid));
  if st<>0 then
  begin

  end;
  try
    st := ks_water_recycleparamcard(rgWaterType.ItemIndex+2);
  except
    on e:Exception do
    Context.GetDialogSystem.ShowMessage(e.Message);
  end;
  if st = 0 then
  begin
    KNG_beep;
    Context.GetDialogSystem.ShowMessage('清空水控设置卡成功！');
  end
  else
    Context.GetDialogSystem.ShowMessage('清空水控设置卡失败-'+geterrmsg);
end;

procedure TfaqhSetWaterCard.btnReleaseCardClick(Sender: TObject);
var
  wp:TWATERPARAM;
  st:Integer;
  WaterSect:Integer;
  rePhyid : array[0..16] of Char;
  tempArr: array[1..8] of Byte;
  reMainKey:string;
begin
  if preReadCard=False then
    Exit;

  if Application.MessageBox('你确定要发行该水控设置卡吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  try
    st := ks_card(PChar(@rePhyid));
    if st<>0 then
    begin

    end;
    WorkView.FieldByName('参数标志').Data.SetInteger(2009);
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      ShowMessage(WorkView.FieldByName('返回信息').Data.AsString);
      Exit;
    end;
    ZeroMemory(@wp,SizeOf(wp));
    if rgWaterType.ItemIndex=0 then
    begin
      WaterSect := 8;
      reMainKey := '123456';
    end
    else
    begin
      WaterSect := 14;
      reMainKey := Trim(WorkView.fieldbyname('密钥').Data.AsString);
    end;
    //HexStrToByteBuf(reMainKey,tempArr);
    //CopyMemory(@wp.sWorkKey,@tempArr,SizeOf(wp.sworkkey)-1);
    StrCopy(@wp.sworkkey,PChar(reMainKey));
    wp.iMinMoney := StrToInt(edtMin.Text);
    wp.iMaxMoney := StrToInt(edtMax.Text);
    wp.iUnit := StrToInt(edtUnit.Text);
    wp.iTransMone := StrToInt(edtTransMoney.Text);
    wp.iUnitMoney := StrToInt(edtUnitMoney.Text);
    wp.iPpriceIndex := 1;
    wp.iWaterSect := WaterSect;
    wp.iCardFlag := rgCardFlag.ItemIndex;
    wp.iTermId := 4;
  except
    Context.GetDialogSystem.ShowMessage('各项值均为整数，请填写正确！');
    Exit;
  end;
  try
    st := ks_water_publishparamcard(rgWaterType.ItemIndex+2,@wp);
    if st<>0 then
      Context.GetDialogSystem.ShowMessage('发行水控设置卡失败-'+geterrmsg)
    else
    begin
      KNG_beep;
      Context.GetDialogSystem.ShowMessage('发行水控设置卡成功！');
    end;
  except
    on e:Exception do
      Context.GetDialogSystem.ShowMessage(e.Message);
  end;

end;

procedure TfaqhSetWaterCard.btnReadWaterFeeClick(Sender: TObject);
var
  wp:TWATERPARAM;
  st:Integer;
  rePhyid : array[0..16] of Char;
begin
  if preReadCard=False then
    Exit;

  try
    st := ks_card(PChar(@rePhyid));
    if st<>0 then
    begin

    end;
    ZeroMemory(@wp,SizeOf(wp));
    st := ks_water_readparamcard(rgWaterType.ItemIndex+2,@wp);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取水控设置卡失败-'+inttostr(st));
      Exit;
    end;
    rgCardFlag.ItemIndex := wp.iCardFlag;
    edtTransMoney.Text := IntToStr(wp.iTransMone);
    edtUnitMoney.Text := IntToStr(wp.iUnitMoney);
    edtMin.Text := IntToStr(wp.iMinMoney);
    edtMax.Text := IntToStr(wp.iMaxMoney);
    edtUnit.Text := IntToStr(wp.iUnit);
  except
    Context.GetDialogSystem.ShowMessage('各项值均为整数，请填写正确！');
    Exit;
  end;
end;

initialization
  TUIStdClassFactory.Create('水控设置卡发行',TfaqhSetWaterCard);

end.
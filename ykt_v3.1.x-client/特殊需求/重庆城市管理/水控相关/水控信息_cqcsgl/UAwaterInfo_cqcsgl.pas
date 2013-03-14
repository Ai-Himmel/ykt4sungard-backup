unit UAwaterInfo_cqcsgl;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, CardDll,WaterDll;

type
  TfaqhwaterInfo_cqcsgl = class(TfaqhSimpleQueryTemp)
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
    grp1: TGroupBox;
    RzStatusPane5: TRzStatusPane;
    edtsmlMoney1: TWVEdit;
    edtsmlNum1: TWVEdit;
    rzstspn2: TRzStatusPane;
    rzstspn3: TRzStatusPane;
    edtsmlFillMoney: TWVEdit;
    edtsmlMoneyTime: TWVEdit;
    rzstspn4: TRzStatusPane;
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhwaterInfo_cqcsgl: TfaqhwaterInfo_cqcsgl;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterInfo_cqcsgl.Init;
begin
  inherited;
end;

procedure TfaqhwaterInfo_cqcsgl.btnReadCardClick(Sender: TObject);
var
  cm: TCM;
  st:Integer;
  waterPack:TWATERPACK;
  smlPhyId:string;
begin
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    setOperReadMode(cm);
    st := cm.readCard;
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����Ϣʧ�ܣ���źÿ������¶�ȡ-'+inttostr(st));
      Exit;
    end;
    edtCardNo.Text := cm.getCardNo;
    edtName.Text := cm.getCustName;
    edtNo.Text := cm.getStuempNo;
    edtMoney.Text := format('%f', [strtofloat(cm.getCardBalance) / 100.0]);
    edtBigNum.Text := cm.getCardCnt;

    //�ۿ�ɹ���ʼдˮ����� ,д֮ǰҪ��Ѱ��
    //��СǮ����Ϣ
    st := mfcard(smlPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('СǮ��Ѱ��ʧ��--'+inttostr(st));
      Exit;
    end;
    
    preReadWaterPack(waterPack);
    st := ks_sr_readmoney(@waterPack);
    if st = 0 then
    begin
      edtsmlMoney1.Text := format('%f', [waterPack.money / 100.0]);
      edtsmlNum1.Text := Format('%d',[waterpack.add_count]);
      edtsmlFillMoney.Text := Format('%f',[waterPack.pre_money / 100.0]);
      edtsmlMoneyTime.Text := waterPack.add_time;
    end
    else
      Context.GetDialogSystem.ShowMessage('��ȡˮ��Ǯ����Ϣʧ�ܣ�');
  finally
    cm.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('ˮ��Ǯ����Ϣ',TfaqhwaterInfo_cqcsgl);

end.
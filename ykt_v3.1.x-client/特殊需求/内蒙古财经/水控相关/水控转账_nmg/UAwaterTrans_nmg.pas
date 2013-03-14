unit UAwaterTrans_nmg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, UtCardDll;

type
  TfaqhwaterTrans_nmg = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
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
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    procedure edtAddMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnTranClick(Sender: TObject);
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
  faqhwaterTrans_nmg: TfaqhwaterTrans_nmg;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterTrans_nmg.Init;
begin
  inherited;
  btnTran.Enabled := False;
end;

procedure TfaqhwaterTrans_nmg.edtAddMoneyKeyPress(Sender: TObject;var Key: Char);
begin
  inherited;
  if Checkedt(Key,edtAddMoney.Text)=False then
    Key := #0;
end;

procedure TfaqhwaterTrans_nmg.btnReadCardClick(Sender: TObject);
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
      Context.GetDialogSystem.showmessage('�������к�ʧ��,�ÿ��Ѿ��𻵣�');
      Exit;
    end;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      Context.GetDialogSystem.showmessage('������Ϣʧ�ܣ������: ' + IntToStr(st));
      Exit;
    end
    else
    begin
      edtCardNo.Text:=PCM.CardNo;
      edtName.Text:=PCM.ucName;
      edtNo.Text:=PCM.ucCardNo;
    end;
    st := CardManage.ReadBalance(SmlPacketNo2,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡСǮ��ʧ�ܣ�');
      Exit;
    end
    else
    begin
      edtsmlMoney.Text:=format('%f', [smallMoney / 100.0]);
    end;
    st := CardManage.ReadBalance(bgPacketNo,@bigMoney,@bigCnt);
    if st <> 0 then
      Context.GetDialogSystem.showmessage('���û���������Ϣʧ�ܣ������: ' + IntToStr(st))
    else
      edtmoney.Text:=format('%f', [bigMoney / 100.0]);
    btnTran.Enabled := true;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhwaterTrans_nmg.btnTranClick(Sender: TObject);
var
  cardManage: TCardManage;
  PCardID:string;
  smallMoney:Integer;
  smallCnt:Integer;
  st:Integer;
begin
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //ȡ������
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
      exit;
    end;
    //�����ɹ����СǮ����Ǯ
    st := CardManage.ReadBalance(smlPacketNo2,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ˮǮ��ʧ�ܣ������: ' + IntToStr(st));
      Exit;
    end;
    WorkView1.FieldByName('����').Data.SetInteger(StrToInt(readCardNo));
    WorkView1.FieldByName('�뿨���').Data.SetInteger(smallMoney);
    WorkView1.FieldByName('���״���').Data.SetInteger(smallCnt);
    WorkView1.FieldByName('���').Data.SetFloat(StrToFloat(edtAddMoney.Text));
    WorkView1.FieldByName('������').Data.SetString(pCardID);
    WVRequest1.SendCommand;
    if (WorkView1.FieldByName('������').Data.AsInteger=0) then
    begin
      Context.GetDialogSystem.ShowMessage(writeWaterMoney(WorkView1,WVcashOperCancel,WVRcashOperCancel));
    end
    else
      Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString+'--��ֱ�ӵ�������ˮ������������ý��');
  finally
    CardManage.Destroy;
  end;

end;

initialization
  TUIStdClassFactory.Create('ˮ��Ǯ����ֵ',TfaqhwaterTrans_nmg);

end.
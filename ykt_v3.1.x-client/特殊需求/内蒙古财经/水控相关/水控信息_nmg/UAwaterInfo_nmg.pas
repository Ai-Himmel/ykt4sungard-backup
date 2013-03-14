unit UAwaterInfo_nmg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, UtCardDll;

type
  TfaqhwaterInfo_nmg = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    GroupBox1: TGroupBox;
    edtsmlMoney1: TWVEdit;
    edtMoney: TWVEdit;
    edtNo: TWVEdit;
    edtName: TWVEdit;
    edtCardNo: TWVEdit;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    btnReadCard: TButton;
    rzstspn1: TRzStatusPane;
    edtBigNum: TWVEdit;
    rzstspn2: TRzStatusPane;
    edtsmlNum1: TWVEdit;
    rzstspn3: TRzStatusPane;
    edtsmlMoney2: TWVEdit;
    rzstspn4: TRzStatusPane;
    edtsmlNum2: TWVEdit;
    rzstspn5: TRzStatusPane;
    rzstspn6: TRzStatusPane;
    edtsmlMoney3: TWVEdit;
    edtsmlNum3: TWVEdit;
    lbl1: TLabel;
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
  faqhwaterInfo_nmg: TfaqhwaterInfo_nmg;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterInfo_nmg.Init;
begin
  inherited;
end;

procedure TfaqhwaterInfo_nmg.btnReadCardClick(Sender: TObject);
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

    st := CardManage.ReadBalance(bgPacketNo,@bigMoney,@bigCnt);
    if st <> 0 then
      showmessage('���û���������Ϣʧ�ܣ������: ' + IntToStr(st))
    else
    begin
      edtmoney.Text:=format('%f', [bigMoney / 100.0]);
      edtBigNum.Text :=format('%d', [bigCnt]);
    end;
      
    smallMoney:=0;
    smallCnt:=0;
    st := CardManage.ReadBalance(SmlPacketNo,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡϴԡǮ��ʧ�ܣ������: ' + IntToStr(st));
      Exit;
    end
    else
    begin
      edtsmlMoney1.Text:=format('%f', [smallMoney / 100.0]);
      edtsmlNum1.Text := format('%d', [smallCnt]);
    end;

    smallMoney:=0;
    smallCnt:=0;
    st := CardManage.ReadBalance(smlPacketNo2,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ˮǮ��ʧ�ܣ������: ' + IntToStr(st));
      Exit;
    end
    else
    begin
      edtsmlMoney2.Text:=format('%f', [smallMoney / 100.0]);
      edtsmlNum2.Text := format('%d', [smallCnt]);
    end;

    smallMoney:=0;
    smallCnt:=0;
    st := CardManage.ReadBalance(smlPacketNo3,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ˮǮ��ʧ�ܣ������: ' + IntToStr(st));
      Exit;
    end
    else
    begin
      edtsmlMoney3.Text:=format('%f', [smallMoney / 100.0]);
      edtsmlNum3.Text := format('%d', [smallCnt]);
    end;
  finally
    CardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('ˮ��Ǯ����Ϣ',TfaqhwaterInfo_nmg);

end.
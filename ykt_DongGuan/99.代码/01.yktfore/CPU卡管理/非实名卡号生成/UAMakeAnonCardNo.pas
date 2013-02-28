unit UAMakeAnonCardNo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, RzEdit,
  Buttons;

type
  TfaqhMakeAnonCardNo = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    grp2: TGroupBox;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    RzStatusPane9: TRzStatusPane;
    edtmoneymoneymoney: TRzNumericEdit;
    WVComboBox1: TWVComboBox;
    edtCardNum: TWVEdit;
    cbbCardType: TWVComboBox;
    edtPatchNo: TRzEdit;
    edtBCardNo: TRzEdit;
    edtECardNo: TRzEdit;
    lblTipInfo: TLabel;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure cbbCardTypeChange(Sender: TObject);
  private
    { Private declarations }
    function getFeeInfo():string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhMakeAnonCardNo: TfaqhMakeAnonCardNo;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon;

{$R *.DFM}

procedure TfaqhMakeAnonCardNo.Init;
begin
  inherited;
  lblTipInfo.Caption := '';
end;

procedure TfaqhMakeAnonCardNo.btnReadCardInfoClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ���ɷǼ���������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsString<>'0' then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  edtPatchNo.Text := WorkView.FieldByName('���κ�').Data.AsString;
  edtBCardNo.Text := WorkView.FieldByName('��ʼ����').Data.AsString;
  edtECardNo.Text := WorkView.FieldByName('��������').Data.AsString;
  Context.GetDialogSystem.ShowMessage('���ɷǼ������ųɹ���');
end;

function TfaqhMakeAnonCardNo.getFeeInfo: string;
var
  cardType:Integer;
begin
  try
    cardType:=StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except
    cardType :=0;
  end;
  WorkView2.FieldByName('�ͻ���').Data.SetInteger(0);
  WorkView2.FieldByName('����').Data.SetString('');
  WorkView2.FieldByName('�����').Data.SetInteger(cardType);
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger=0 then
  begin
    lblTipInfo.Caption := WorkView2.fieldbyname('�ɷ���Ϣ').Data.AsString;
    //edtMoney.Text := WorkView2.fieldbyname('Ԥ�����').Data.AsString;
  end
  else
    lblTipInfo.Caption := WorkView2.fieldbyname('������Ϣ').Data.AsString;
  Result := '';              
end;

procedure TfaqhMakeAnonCardNo.cbbCardTypeChange(Sender: TObject);
begin
  getFeeInfo;

end;

initialization
  TUIStdClassFactory.Create('�Ǽ�����������', TfaqhMakeAnonCardNo);

end.


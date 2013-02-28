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
  if Application.MessageBox('你确定要生成非记名卡号吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsString<>'0' then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  edtPatchNo.Text := WorkView.FieldByName('批次号').Data.AsString;
  edtBCardNo.Text := WorkView.FieldByName('开始卡号').Data.AsString;
  edtECardNo.Text := WorkView.FieldByName('结束卡号').Data.AsString;
  Context.GetDialogSystem.ShowMessage('生成非记名卡号成功！');
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
  WorkView2.FieldByName('客户号').Data.SetInteger(0);
  WorkView2.FieldByName('卡号').Data.SetString('');
  WorkView2.FieldByName('卡类别').Data.SetInteger(cardType);
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('返回码').Data.AsInteger=0 then
  begin
    lblTipInfo.Caption := WorkView2.fieldbyname('缴费信息').Data.AsString;
    //edtMoney.Text := WorkView2.fieldbyname('预交金额').Data.AsString;
  end
  else
    lblTipInfo.Caption := WorkView2.fieldbyname('返回信息').Data.AsString;
  Result := '';              
end;

procedure TfaqhMakeAnonCardNo.cbbCardTypeChange(Sender: TObject);
begin
  getFeeInfo;

end;

initialization
  TUIStdClassFactory.Create('非记名卡号生成', TfaqhMakeAnonCardNo);

end.


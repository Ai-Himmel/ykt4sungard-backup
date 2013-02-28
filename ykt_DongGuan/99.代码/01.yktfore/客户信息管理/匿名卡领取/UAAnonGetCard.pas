unit UAAnonGetCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox, jpeg,
  RM_Common, RM_Class, ComCtrls, RzStatus,CardDll;

type
  TfaqhAnonGetCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label4: TLabel;
    Label12: TLabel;
    Label7: TLabel;
    cbb1: TWVComboBox;
    edtBirthdayQ: TWVEdit;
    cbbDept: TWVComboBox;
    WVEdit17: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVEdit9: TWVEdit;
    Label9: TLabel;
    Label14: TLabel;
    Label17: TLabel;
    Label15: TLabel;
    Label10: TLabel;
    cbbIDType: TWVComboBox;
    WVEdit15: TWVEdit;
    Label16: TLabel;
    Label11: TLabel;
    WVEdit11: TWVEdit;
    WVEdit16: TWVEdit;
    QueryRequest: TWVRequest;
    WorkView1: TWorkView;
    btnGetCard: TBitBtn;
    chkPrint: TCheckBox;
    rpt1: TRMReport;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    btnReadCard: TBitBtn;
    Label2: TLabel;
    edtMoney: TWVEdit;
    WVRequest1: TWVRequest;
    WorkView2: TWorkView;
    Label3: TLabel;
    WVEdit2: TWVEdit;
    rzstspn1: TRzStatusPane;
    procedure btnQueryClick(Sender: TObject);
    procedure btnGetCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhAnonGetCard: TfaqhAnonGetCard;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,filetrans;
     
{$R *.DFM}

procedure TfaqhAnonGetCard.Init;
begin
  inherited;
end;

procedure TfaqhAnonGetCard.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBirthdayQ.Text)<>'' then
    if CheckInputDateFormat(edtBirthdayQ.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtBirthdayQ.SetFocus;
      Exit;
    end;

  WorkView1.FieldByName('������־').Data.SetString('R');
  QueryRequest.SendCommand;
  if WorkView1.FieldByName('������').Data.AsString<>'0' then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);
    Exit;
  end;
  if WorkView1.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    btnGetCard.Enabled := False;
    //btnFee.Enabled := False;
  end
  else
  begin
    btnGetCard.Enabled := True;
    //btnFee.Enabled := True;
  end;
  //inherited;

end;

procedure TfaqhAnonGetCard.btnGetCardClick(Sender: TObject);
var
  custId:Integer;
  cardNo:string;
begin
  if Application.MessageBox('��ȷ��Ҫ�����쿨������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  cardNo := Grid.DataSource.DataSet.fieldbyname('scard0').AsString;
  WorkView.FieldByName('������־').Data.SetString('N');
  WorkView.FieldByName('����').Data.SetString(cardNo);
  WorkView.FieldByName('�ͻ���').Data.SetInteger(custId);
  WorkView.FieldByName('Ԥ����').Data.SetFloat(StrToFloat(edtMoney.text));
  if WorkView.FieldByName('������').Data.AsInteger<>0 then
    Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString)
  else
    Context.GetDialogSystem.ShowMessage('�쿨�ɹ���');
end;

procedure TfaqhAnonGetCard.GridCellClick(Column: TColumn);
var
  custId:Integer;
begin
  try
    custId:=Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  except
    custId := 0;
  end;
  WorkView2.FieldByName('�ͻ���').Data.SetInteger(custId);
  WVRequest1.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger=0 then
  begin
    rzstspn1.Caption := WorkView2.fieldbyname('�ɷ���Ϣ').Data.AsString;
    edtMoney.Text := WorkView2.fieldbyname('Ԥ�����').Data.AsString;
  end
  else
    rzstspn1.Caption := WorkView2.fieldbyname('������Ϣ').Data.AsString;
end;

initialization
  TUIStdClassFactory.Create('��������ȡ',TfaqhAnonGetCard);

end.
unit UAdeleteSublidyList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, RzStatus, UIncrementComboBox,
  Buttons;

type
  TfaqhdeleteSublidyList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    WVEdit1: TWVEdit;
    edtPatchNo: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    Label10: TLabel;
    edtPNo: TWVEdit;
    btnPDelete: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    RzStatusPane1: TRzStatusPane;
    cbbType: TWVComboBox;
    Label11: TLabel;
    edtCustNo: TWVEdit;
    Label9: TLabel;
    edtCardNo: TWVEdit;
    procedure btnQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnPDeleteClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhdeleteSublidyList: TfaqhdeleteSublidyList;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhdeleteSublidyList.Init;
begin
  inherited;
  {
  WorkView.FieldByName('学工号').DefaultValue := '';
  WorkView.FieldByName('客户号').DefaultValue := 0;
  WorkView.FieldByName('补助批次号').DefaultValue := 0;
  WorkView.FieldByName('卡号').DefaultValue := 0;
  WorkView.FieldByName('导入批次号').DefaultValue := '';
  WorkView.FieldByName('发生日期').DefaultValue := '';
  WorkView.FieldByName('领取日期').DefaultValue := '';
  WorkView.FieldByName('经办人身份证号').DefaultValue := '';
  WorkView.FieldByName('经办人姓名').DefaultValue := '';
  WorkView.FieldByName('状态').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhdeleteSublidyList.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtPatchNo.Text)='' then
    edtPatchNo.Text := '0';
  if Trim(edtCardno.Text)='' then
    WorkView.FieldByName('卡号').Data.SetInteger(0);
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;

end;

procedure TfaqhdeleteSublidyList.btnPrintClick(Sender: TObject);
var
  custNo : string;
  tempDataSet : TDataSet;
  scustlimit:string;
begin
  //inherited;
  tempDataSet := WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet;
  custNo := tempDataSet.fieldbyname('scust_auth').AsString;
  scustlimit := tempDataSet.fieldbyname('scust_limit').AsString;
  WorkView1.FieldByName('学工号').Data.SetString(custNo);
  WorkView1.FieldByName('导入批次号').Data.SetString(scustlimit);
  WorkView1.FieldByName('删除标志').Data.SetInteger(0);
  WorkView1.FieldByName('交易类型').Data.SetString('D');
  WVRequest1.SendCommand;
  ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString);
  RzStatusPane1.Caption:=WorkView1.fieldbyname('返回信息').Data.AsString;
  btnQuery.Click;

end;

procedure TfaqhdeleteSublidyList.btnPDeleteClick(Sender: TObject);
begin
  if Trim(edtPNo.Text)='' then
  begin
    ShowMessage('请先输入要批量删除的批次号');
    edtPNo.SetFocus;
    Exit;
  end;
  if Application.MessageBox('你确定要批量删除该批补助信息吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  WorkView1.FieldByName('学工号').Data.SetString('');
  WorkView1.FieldByName('交易类型').Data.SetString('D');
  WorkView1.FieldByName('导入批次号').Data.SetString(edtPNo.Text);
  WorkView1.FieldByName('删除标志').Data.SetInteger(1);
  WVRequest1.SendCommand;
  ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString);
  RzStatusPane1.Caption:=WorkView1.fieldbyname('返回信息').Data.AsString;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('补助信息删除',TfaqhdeleteSublidyList);

end.
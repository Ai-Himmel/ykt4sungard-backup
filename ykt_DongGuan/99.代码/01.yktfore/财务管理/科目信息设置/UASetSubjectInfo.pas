unit UASetSubjectInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,
  UIncrementComboBox, RzDBNav, RzButton, RzRadChk, RzDBGrid,
  RzTabs, USMSetTreeParamsTemp, RzTreeVw,WVCommands, Buttons,
  UqhSetParamsTemp;


type
  TfaqhSetSubjectInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label25: TLabel;
    WVEdit2: TWVEdit;
    Label26: TLabel;
    WVComboBox8: TWVComboBox;
    Label27: TLabel;
    WVComboBox9: TWVComboBox;
    edtBusiId: TWVEdit;
    Label30: TLabel;
    Label9: TLabel;
    WVComboBox1: TWVComboBox;
    Label17: TLabel;
    WVComboBox2: TWVComboBox;
    Label2: TLabel;
    Label3: TLabel;
    WVComboBox3: TWVComboBox;
    edtSubjNo: TWVEdit;
    Label4: TLabel;
    Label5: TLabel;
    WVComboBox4: TWVComboBox;
    WVEdit3: TWVEdit;
    Label6: TLabel;
    WVComboBox5: TWVComboBox;
    Label7: TLabel;
    WVComboBox6: TWVComboBox;
    Label8: TLabel;
    edtId: TWVEdit;
    Label11: TLabel;
    edtSubjName: TWVEdit;
    Label12: TLabel;
    WVComboBox7: TWVComboBox;
    Label13: TLabel;
    WVComboBox10: TWVComboBox;
    Label14: TLabel;
    WVComboBox11: TWVComboBox;
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    {刷新树视图结构}
  public

    procedure Init; override;

    { Public declarations }
  end;

var
  faqhSetSubjectInfo: TfaqhSetSubjectInfo;

implementation

uses KsFrameworks, KSClientConsts, SmartCardCommon;

{$R *.DFM}


procedure TfaqhSetSubjectInfo.Init;
begin
  inherited;
end;

procedure TfaqhSetSubjectInfo.btnAddClick(Sender: TObject);
begin
  Inherited;
  WorkView.FieldByName('标志').Data.SetString('A');
end;

procedure TfaqhSetSubjectInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('标志').Data.SetString('D');
end;

procedure TfaqhSetSubjectInfo.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('标志').Data.SetString('R');
  inherited;
end;

procedure TfaqhSetSubjectInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('标志').Data.SetString('U');
end;

procedure TfaqhSetSubjectInfo.btnCancelClick(Sender: TObject);
begin
  Inherited;
  //WorkView.FieldByName('标志').Data.SetString('R');
  btnQueryClick(Sender);
end;


procedure TfaqhSetSubjectInfo.btnOKClick(Sender: TObject);
begin
  if Trim(edtsubjno.Text)='' then
  Begin
    Context.GetDialogSystem.ShowMessage('请输入科目号！');
    edtsubjno.SetFocus;
    Exit;
  end;
  if Trim(edtSubjName.Text)='' then
  Begin
    Context.GetDialogSystem.ShowMessage('请输入科目名称！');
    edtSubjName.SetFocus;
    Exit;
  end;
  inherited;

end;

initialization
  TUIStdClassFactory.Create('科目信息设置',TfaqhSetSubjectInfo);

end.

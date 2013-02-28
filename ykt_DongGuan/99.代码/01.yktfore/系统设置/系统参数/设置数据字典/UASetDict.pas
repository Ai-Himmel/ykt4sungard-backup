{wsn 20040101 在数据字典接口中添加“大类名称”字段，并添加相应显示信息
　注：大类名称、大类代码　用户不可修改}
unit UASetDict;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,
  USetParamsTemp, KSDataDictionary, RzDBNav, RzButton, RzRadChk, RzDBGrid,
  RzTabs, Buttons;

Const
  DictionaryCanEditCount=2000;


type
  TfaqhSetDict = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Labeldict_no2: TLabel;
    Labeldict_value3: TLabel;
    Labeldict_caption4: TLabel;
    WVEditdict_value3: TWVEdit;
    WVEditdict_caption4: TWVEdit;
    WVDigitalEdit1: TWVDigitalEdit;
    Label1: TLabel;
    WVEdit2: TWVEdit;
    Label3: TLabel;
    edtSName: TWVEdit;
    Label4: TLabel;
    edtSCode: TWVEdit;
    Label5: TLabel;
    edtBCode: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure tvCategoryDblClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetDict: TfaqhSetDict;

implementation

uses KsFrameworks, 
     KSClientConsts;

{$R *.DFM}

procedure TfaqhSetDict.Init;
begin
  inherited;
  btnAdd.Enabled := False;
end;


procedure TfaqhSetDict.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSetDict.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetDict.btnQueryClick(Sender: TObject);
begin
  if Trim(edtsCode.Text)='' then
    edtsCode.Text := '0';
  WorkView.FieldByName('操作类别').Data.SetString('R');
  inherited;
  btnDelete.Enabled := false;
  btnChange.Enabled := False;
  btnAdd.Enabled :=False;
end;

procedure TfaqhSetDict.btnChangeClick(Sender: TObject);
begin

  WVDigitalEdit1.Enabled:=True;
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('U');
  WVDigitalEdit1.Enabled := false;
  WVEditdict_value3.Enabled := false;   
  WVEditdict_caption4.SetFocus;
  WVEditdict_caption4.SelectAll;
  WVDigitalEdit1.Enabled:=False;
end;

procedure TfaqhSetDict.btnAddClick(Sender: TObject);
begin

  WVDigitalEdit1.Enabled:=True;
  WVEdit2.Enabled:=True;
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('A');
  WVDigitalEdit1.Enabled := False;
  WVEdit2.Enabled:=False;

  WVEditdict_value3.Enabled := True;
  WVEditdict_value3.SelectAll;
  WVEditdict_value3.SetFocus;

  WVDigitalEdit1.Enabled:=False;
  //WVDigitalEdit1.selectall;
end;

procedure TfaqhSetDict.tvCategoryDblClick(Sender: TObject);
begin
  inherited;
  DoQuery;
end;

procedure TfaqhSetDict.btnDeleteClick(Sender: TObject);
begin
  WVDigitalEdit1.Enabled:=True;
  WVEdit2.Enabled:=True;
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('D');
  WVDigitalEdit1.Enabled:=False;
  WVEdit2.Enabled:=False;
end;

procedure TfaqhSetDict.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQuery.click;
end;

initialization
  TUIStdClassFactory.Create('数据字典设置',TfaqhSetDict);

end.
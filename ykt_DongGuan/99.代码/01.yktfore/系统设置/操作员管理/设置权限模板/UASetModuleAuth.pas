unit UASetModuleAuth;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  USetParamsTemp,KSCmdModules, UAuth, UIncrementComboBox, RzDBNav,
  RzButton, RzRadChk, RzDBGrid, RzTabs,KCDataAccess, Buttons;

type
  TfaqhSetModuleAuth = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Labelmodule_code2: TLabel;
    WVEditmodule_code2: TWVEdit;
    WVComboBox1: TWVComboBox;
    Panel2: TPanel;
    faAuth1: TfaAuth;
    Panel3: TPanel;
    WVEditmodule_name4: TWVEdit;
    Labelmodule_name4: TLabel;
    Labelmodule_code3: TLabel;
    WVEditmodule_code3: TWVEdit;
    Panel4: TPanel;
    Label1: TLabel;

    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure faAuth1TreeViewKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
  protected
    { Private declarations }
    procedure BeforeAdd; override;
    function  Get800Str: string;
    //获取长度为800的字符串
    procedure DisplayData; override;
    //将查询出的权限位串显示在属性结构中
    procedure SaveModifiedData; override;

    function  Get200Str: string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetModuleAuth: TfaqhSetModuleAuth;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;

{$R *.DFM}


function  TfaqhSetModuleAuth.Get200Str: string;
begin
  Result := StringOfChar('0',200);   //wlj 20031209 缺省改为没有权限
end;


// save to workview
procedure TfaqhSetModuleAuth.SaveModifiedData;
var TmpStr:String;
    //lst:TStringlist;
begin
  inherited;
  TmpStr:=faAuth1.MenuSet;
  WorkView.FieldByName('菜单权限1').Data.SetString(Copy(TmpStr,1,200));
  WorkView.FieldByName('菜单权限2').Data.SetString(Copy(TmpStr,201,200));
  WorkView.FieldByName('菜单权限3').Data.SetString(Copy(TmpStr,401,200));
  WorkView.FieldByName('菜单权限4').Data.SetString(Copy(TmpStr,601,200));
  WorkView.FieldByName('功能权限').Data.SetString(Get800Str);
end;

// display the tree
procedure TfaqhSetModuleAuth.DisplayData;
var TmpStr:string;
begin
  inherited;
  TmpStr:='';
  TmpStr:=TmpStr+trim(Copy(WorkView.FieldByName('菜单权限1').Data.AsString,1,200));
  TmpStr:=TmpStr+trim(Copy(WorkView.FieldByName('菜单权限2').Data.AsString,1,200));
  TmpStr:=TmpStr+trim(Copy(WorkView.FieldByName('菜单权限3').Data.AsString,1,200));
  TmpStr:=TmpStr+trim(Copy(WorkView.FieldByName('菜单权限4').Data.AsString,1,200));

  faAuth1.SetAuth(TmpStr,Get800Str);
end;


function TfaqhSetModuleAuth.Get800Str: string;
begin
  Result := StringOfChar('0',800);   //wlj 20031209 缺省改为没有权限
end;


// clear the faAuth1
procedure TfaqhSetModuleAuth.BeforeAdd;
var TmpStr:String;
begin
  inherited;
  //wsn 20050119用连接后的权限字符串更新到树中
  TmpStr:=Copy(WorkView.FieldByName('菜单权限1').Data.AsString,1,200)+
          Copy(WorkView.FieldByName('菜单权限2').Data.AsString,1,200)+
          Copy(WorkView.FieldByName('菜单权限3').Data.AsString,1,200)+
          Copy(WorkView.FieldByName('菜单权限4').Data.AsString,1,200);
  faAuth1.SetAuth(TmpStr,Get800Str);
end;

procedure TfaqhSetModuleAuth.Init;
begin
  inherited;
  {加速显示}
  faAuth1.HandleNeeded;
  faAuth1.TreeView.HandleNeeded;
  faAuth1.BuildTree;
  faAuth1.RefreshTreeDisplay;
  faAuth1.SetAuth(Get800Str, Get800Str);

  //WorkView.FieldByName('查询.模板代码').DefaultValue := '';
  //WorkView.FieldByName('模板代码').DefaultValue := '';
  //WorkView.FieldByName('模板名称').DefaultValue := '';
  WorkView.FieldByName('菜单权限1').DefaultValue := Get200Str;
  WorkView.FieldByName('菜单权限2').DefaultValue := Get200Str;
  WorkView.FieldByName('菜单权限3').DefaultValue := Get200Str;
  WorkView.FieldByName('菜单权限4').DefaultValue := Get200Str;
  WorkView.FieldByName('功能权限').DefaultValue := Get800Str;
  //WorkView.FieldByName('操作类别').DefaultValue := '';
  WorkView.Reset;
end;

procedure TfaqhSetModuleAuth.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetModuleAuth.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhSetModuleAuth.btnOKClick(Sender: TObject);
begin
  SaveModifiedData;
  inherited;
  btnQuery.Click;
  {
  FreeIDObjects(-29);  // update the data dict
      //wlj 20031202增加权限模板后,马上更新数据字典和窗口列表
  WVComboBox1.ItemsDataEntry := '';
  WVComboBox1.itemsdataentry := '*-29';
  }
end;

procedure TfaqhSetModuleAuth.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('A');
  WVEditmodule_code3.Enabled := true;
  WVEditmodule_code3.SetFocus;        //模板代码
  WVEditmodule_code3.SelectAll;
end;

procedure TfaqhSetModuleAuth.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('U');
  WVEditmodule_code3.Enabled := false;
  WVEditmodule_name4.SetFocus;         //模板名称
  WVEditmodule_name4.selectall;   
end;

procedure TfaqhSetModuleAuth.faAuth1TreeViewKeyDown(Sender: TObject;
  var Key: Word; Shift: TShiftState);
begin
  inherited;
  if (key = VK_RETURN) then
    btnOK.SetFocus;    //如果按回车就到确定按钮
end;

procedure TfaqhSetModuleAuth.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作类别').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetModuleAuth.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('D');

end;

initialization
  TUIStdClassFactory.Create('权限模板设置',TfaqhSetModuleAuth);

end.



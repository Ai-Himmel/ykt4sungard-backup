unit UCMMenu;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdProc, KCWVProcBinds, WVCmdTypeInfo, Db, BDAImpEx,
  KCDataAccess, WorkViews, KSFrameWorks, Contnrs;

type
  TdmMenu = class(TDataModule, IKSModule)
    ctQueryMenu: TWVCommandTypeInfo;
    cpQueryMenu: TKCWVQuery;
    ctQueryMenuStructure: TWVCommandTypeInfo;
    cpQueryMenuStructure: TKCWVQuery;
    cpGetFunction: TKCWVQuery;
    ctGetFunction: TWVCommandTypeInfo;
    ctGetQhFunction: TWVCommandTypeInfo;
    cpGetQhFunction: TKCWVQuery;
    procedure DataModuleCreate(Sender: TObject);
    procedure DataModuleDestroy(Sender: TObject);
  private
    { Private declarations }
    {
    procedure DoGetMenu(Sender : TObject);
    procedure DoGetMenuStructure(Sender : TObject);
    }
    //procedure DoGetFunction(Sender: TObject);
    procedure DoGetMenuFromFile;
  protected
    { Private declarations }
  public
    { Public declarations }
    procedure Start;
    procedure ShutDown;
  end;

var
  dmMenu: TdmMenu;

implementation

uses KSClientConsts, KSFrameWorkUtils, StdCtrls, WVCtrls, SafeCode, DataTypes,
  LogFile, KSDataDictionary, WVCommands, KSMenuAdmin, KSMenuFiles,
    UQhClientConsts;

{$R *.DFM}

{ TdmMenu }

procedure TdmMenu.DataModuleCreate(Sender: TObject);
begin
  SysModule2 := Self;
  MenuAdmin := TMenuAdmin.Create;
  {
  MenuAdmin.OnGetMenus := DoGetMenu;
  MenuAdmin.OnGetMenuStructures:= DoGetMenuStructure;
  }
  //MenuAdmin.OnGetFunctions := DoGetFunction;
end;

procedure TdmMenu.DataModuleDestroy(Sender: TObject);
begin
  WriteLog('dmMenu Destroying...', lcConstruct_Destroy);
  SysModule2 := nil;
  FreeAndNil(MenuAdmin);
  WriteLog('dmMenu Destroyed', lcConstruct_Destroy);
end;

procedure TdmMenu.ShutDown;
begin
  FreeAndNil(MenuAdmin);
end;

procedure TdmMenu.Start;
begin
  RegisterModule(Self);
  //MenuAdmin.Init;
  DoGetMenuFromFile;
end;
{hanjiwei delete it 20080528*****************************************************
procedure TdmMenu.DoGetFunction(Sender: TObject);
var
  Dataset: TDataset;
  AFunction: TKSMetaFunction;
  Command: TWVCommand;
  IDField, CaptionField, NoField: TField;
begin
  WriteLog('Begin TdmMenu.DoGetQhFunction', lcKSClientStart);
  CheckObject(Context, 'Invalid Context');
  //wlj 20031114 修改为调用期货的功能列表Command := Context.CommandFactory.NewCommand(ctGetFunction.ID, ctGetFunction.Version);
  Command := Context.CommandFactory.NewCommand(ctGetQhFunction.ID,
    ctGetQhFunction.Version);

  Dataset := nil;
  try
    Command.ParamData('查询标志').SetString('1');

    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    IDField := Dataset.FieldByName('lcert_code');
    CaptionField := Dataset.FieldByName('scust_limit');
    //NoField := Dataset.FieldByName('lsafe_level2');
    NoField := IDField;
    while not Dataset.Eof do
    begin
      AFunction := TKSMetaFunction.Create;
      AFunction.Id := IDField.AsInteger;
      AFunction.Caption := CaptionField.AsString;
      AFunction.No := NoField.AsInteger;
      TMenuAdmin(Sender).FunctionList.Add(AFunction);
      Dataset.Next;
    end;
  finally
    Dataset.Free;
    Command.Free;
  end;
  WriteLog('End TdmMenu.DoGetFunction', lcKSClientStart);
end;
}
(*
procedure TdmMenu.DoGetMenu(Sender: TObject);
var
  Command : TWVCommand;
  Dataset: TDataset;
  AMenu: TKSMetaMenu;
begin
  CheckObject(Context,'Invalid Context');
  Dataset := nil;
  Command := Context.CommandFactory.NewCommand(ctQueryMenu.ID, ctQueryMenu.Version);
  try
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    while not Dataset.Eof do
    begin
      AMenu := TKSMetaMenu.Create;
      AMenu.Id := Dataset.FieldByName('sname').AsString;
      AMenu.Caption := Dataset.FieldByName('scust_limit').AsString;
      AMenu.AuthNo := Dataset.FieldByName('lsafe_level2').AsInteger;
      AMenu.FunctionSet := Dataset.FieldByName('scusttypes').AsString;
      AMenu.MenuType := Dataset.FieldByName('sstatus0').AsString;
      TMenuAdmin(Sender).MenuList.Add(AMenu);
      Dataset.Next;
    end;
  finally
    Dataset.Free;
    Command.Free;
  end;
end;

procedure TdmMenu.DoGetMenuStructure(Sender: TObject);
var
  Dataset: TDataset;
  AMenuStructure: TKSMenuStructure;
  Command : TWVCommand;
begin
  CheckObject(Context,'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctQueryMenuStructure.ID, ctQueryMenuStructure.Version);
  Dataset := nil;
  try
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    while not Dataset.Eof do
    begin
      AMenuStructure := TKSMenuStructure.Create;
      AMenuStructure.ParentId := Dataset.FieldByName('sname').AsString;
      AMenuStructure.ChildId := Dataset.FieldByName('sname2').AsString;
      AMenuStructure.SequenceNo := Dataset.FieldByName('lsafe_level').AsInteger;
      TMenuAdmin(Sender).MenuStructureList.Add(AMenuStructure);
      Dataset.Next;
    end;
  finally
    Dataset.Free;
    Command.Free;
  end;
end;
*)

procedure TdmMenu.DoGetMenuFromFile;
begin
  {
  ReadMenuAdminFromFile(
    MenuAdmin,
    GetFileName(dkConfig,MenuInfoFileName),
    False);
  }
  {
  ReadMenuAdminFromDataFile(
    MenuAdmin,
    GetFileName(dkConfig,MenuInfoDataFileName),
    SApplicationTitle,
    False);
    }
    {
  ReadMenuAdminFromDataFile(
    MenuAdmin,
    GetFileName(dkConfig,
    Context.GetConfigSystem.ReadString(ccMain, 'Menu', MenuInfoDataFileName)),
    SKingStarFutureBinMnuKey,
    False);}
  ReadMenuAdminFromDataFile(
    MenuAdmin,
    GetFileName(dkConfig,
    yktMenu),
    SKingStarFutureBinMnuKey,
    False);

end;

end.

unit KSBaseAbout;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UAbout
   <What>关于对话框
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, jpeg, ExtCtrls, ImageCtrls, UICtrls, ComCtrls, RzListVw,
  Buttons, AAFont, AACtrls;

type
  TdlgKSBaseAbout = class(TForm)
    UIPanel1: TUIPanel;
    Image1: TImage;
    ImageButton1: TBitBtn;
    Bevel1: TBevel;
    ListView1: TRzListView;
    albl1: TAALabel;
    albl2: TAALabel;
    albl3: TAALabel;
    alnklbl1: TAALinkLabel;
    alblBackVer: TAALabel;
    procedure GoWeb(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dlgKSBaseAbout: TdlgKSBaseAbout;

procedure ShowAbout;

procedure GetProcessModules(ListView : TRzListView);

implementation

{$R *.DFM}

uses ExtUtils,KSClientConsts;

procedure ShowAbout;
var
  Dialog : TdlgKSBaseAbout;
begin
  Dialog := TdlgKSBaseAbout.Create(nil);
  try
    Dialog.ShowModal;
  finally
    Dialog.Free;
  end;
end;

procedure GetProcessModules(ListView : TRzListView);
var
  Modules : TKSProcessModules;
  Count, I : Integer;
  ModuleInfo : TKSModuleInfo;
  Item : TListItem;
  VersionInfo : TKSFileVersionInfo;
  Version, Company, Description : string;
  FileTime : string;
begin
  Modules := nil;
  VersionInfo := nil;
  try
    Modules := TKSProcessModules.Create;
    VersionInfo := TKSFileVersionInfo.Create;
    Modules.Refresh;
    ListView.Items.BeginUpdate;
    ListView.Items.Clear;
    Count := Modules.Count;
    for I:=0 to Count-1 do
    begin
      ModuleInfo := Modules.Modules[I];
      Item := ListView.Items.Add;
      Item.Caption := ModuleInfo.ModuleName;
      VersionInfo.OpenFile(ModuleInfo.ModulePath);
      if VersionInfo.Available then
      begin
        Version := VersionInfo.GetInfo('FileVersion');
        //Company := VersionInfo.GetInfo('CompanyName');
        Description := VersionInfo.GetInfo('FileDescription');
      end else
      begin
        Version := '';
        Company := '';
        Description := '';
      end;
      FileTime := FormatDateTime('yyyy-mm-dd',FileDateToDateTime(FileAge(ModuleInfo.ModulePath)));
      Item.SubItems.Add(Version);
      Item.SubItems.Add(FileTime);
      Item.SubItems.Add(Description);
      //Item.SubItems.Add(Company);
      Item.SubItems.Add(ModuleInfo.ModulePath);
    end;
    ListView.Items.EndUpdate;
  finally
    Modules.Free;
    VersionInfo.Free;
  end;
end;

procedure TdlgKSBaseAbout.GoWeb(Sender: TObject);
begin
  ShellOpenFile(TLabel(Sender).Caption);
end;

procedure TdlgKSBaseAbout.FormCreate(Sender: TObject);
begin
  GetProcessModules(ListView1);
  albl2.Caption := '前台版本 '+yktversion;
  alblBackVer.Caption := '后台版本 '+backver;
end;

end.

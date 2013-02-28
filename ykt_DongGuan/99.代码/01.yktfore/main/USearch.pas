unit USearch;

interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls, Forms,
KSFrameWorks, KSFrames,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, Grids, DBGrids, Db, ComCtrls;

type
  TfaSearch = class(TKSFrame)
    DataSource1: TDataSource;
    UIPanel2: TUIPanel;
    Label1: TLabel;
    btnQuery: TImageButton;
    lvMenus: TListView;
    Label2: TLabel;
    GroupBox1: TGroupBox;
    ckTitle: TCheckBox;
    ckKeywords: TCheckBox;
    ckDescription: TCheckBox;
    edText: TEdit;
    procedure btnQueryClick(Sender: TObject);
    procedure lvMenusDblClick(Sender: TObject);
    procedure edTextKeyPress(Sender: TObject; var Key: Char);
    procedure lvMenusKeyPress(Sender: TObject; var Key: Char);
  private
    procedure SearchMenus;
    procedure ShowMenu;
  protected
    procedure Init; override;
  public

  end;

var
  faSearch: TfaSearch;

implementation

uses KSClientConsts, KSMenuAdmin;

{$R *.DFM}

procedure TfaSearch.btnQueryClick(Sender: TObject);
begin
  SearchMenus;
end;

procedure TfaSearch.Init;
begin
  if edText.CanFocus then
    edText.SetFocus;
end;

procedure TfaSearch.SearchMenus;
var
  List: TList;
  SearchTypes: TMenuSearchTypes;
  I: Integer;
  ListItem: TListItem;
  Auth: string;
  MetaMenu: TKSMetaMenu;
begin
  List := TList.Create;
  try
    lvMenus.Items.BeginUpdate;
    lvMenus.Items.Clear;
    SearchTypes := [];
    if ckTitle.Checked then
      SearchTypes := SearchTypes + [mstTitle];
    if ckKeywords.Checked then
      SearchTypes := SearchTypes + [mstKeywords];
    if ckDescription.Checked then
      SearchTypes := SearchTypes + [mstDescription];
    MenuAdmin.MenuList.Search(SearchTypes, edText.Text, List);
    Auth := Context.GetParamValue(svOperatorMenuAuthName);
    for I := 0 to List.Count - 1 do
    begin
      MetaMenu := TKSMetaMenu(List[I]);
      if MetaMenu.HaveAuth(Auth) = 1 then
      begin
        ListItem := lvMenus.Items.Add;
        ListItem.Caption := MetaMenu.Caption;
        ListItem.SubItems.Add(MetaMenu.Keywords);
        ListItem.SubItems.Add(MetaMenu.Description);
        ListItem.Data := MetaMenu;
      end;
    end;
  finally
    lvMenus.Items.EndUpdate;
    List.Free;
  end;
  if lvMenus.CanFocus then
  begin
    lvMenus.SetFocus;
    if lvMenus.Items.Count > 0 then
      lvMenus.Selected := lvMenus.Items[0];
  end;
end;

procedure TfaSearch.lvMenusDblClick(Sender: TObject);
begin
  ShowMenu;
end;

procedure TfaSearch.edTextKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = #13 then
    SearchMenus;
end;

procedure TfaSearch.lvMenusKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = #13 then
    ShowMenu;
end;

procedure TfaSearch.ShowMenu;
var
  MetaMenu: TKSMetaMenu;
begin
  if lvMenus.Selected <> nil then
  begin
    MetaMenu := TKSMetaMenu(lvMenus.Selected.Data);
    if MainForm <> nil then
      MainForm.ShowUI(MetaMenu.ID);
  end;
end;

initialization
  TUIStdClassFactory.Create(UISearch, TfaSearch);

end.

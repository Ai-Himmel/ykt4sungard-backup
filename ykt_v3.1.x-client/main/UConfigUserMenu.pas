unit UConfigUserMenu;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, UICtrls, StdCtrls, ImageCtrls, KSActions, ActnList;

type
  TdlgManagePersonalMenu = class(TForm)
    UIPanel1: TUIPanel;
    lsMenuIDs: TListBox;
    btnOk: TImageButton;
    btnCancel: TImageButton;
    btnUp: TImageButton;
    btnDown: TImageButton;
    btnDelete: TImageButton;
    ActionList1: TActionList;
    KSListDelete1: TKSListDelete;
    KSListMoveDown1: TKSListMoveDown;
    KSListMoveUp1: TKSListMoveUp;
  private
    { Private declarations }
  public
    { Public declarations }
    function Execute(IDs: TStrings): Boolean;
  end;

var
  dlgManagePersonalMenu: TdlgManagePersonalMenu;

function ManagePersonMenu(IDs: TStrings): Boolean;

implementation

{$R *.DFM}

function ManagePersonMenu(IDs: TStrings): Boolean;
var
  Dialog: TdlgManagePersonalMenu;
begin
  Dialog := TdlgManagePersonalMenu.Create(Application);
  try
    Result := Dialog.Execute(IDs);
  finally
    Dialog.Free;
  end;
end;

{ TdlgManagePersonalMenu }

function TdlgManagePersonalMenu.Execute(IDs: TStrings): Boolean;
begin
  lsMenuIDs.Items.Assign(IDs);
  Result := ShowModal = mrOK;
  if Result then
    IDs.Assign(lsMenuIDs.Items);
end;

end.

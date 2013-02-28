unit UBranchManWindow;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UBranchManager,WorkViews;

type
  TfmBranchMan = class(TForm)
    faBranchMan: TfaBranchMan;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure Init(WorkView:TWorkView;SingleSelect:Boolean;BranchName,IncludeStr: String);
  end;

var
  fmBranchMan: TfmBranchMan;


implementation

{$R *.DFM}


{ TfmBranchMan }

procedure TfmBranchMan.Init(WorkView: TWorkView; SingleSelect: Boolean;
  BranchName,IncludeStr: String);
begin
  faBranchMan.FSingleSelect :=SingleSelect;
  faBranchMan.FWorkView:=WorkView;
  faBranchMan.BranchName:=BranchName;
  faBranchMan.IncludeName:= IncludeStr;
end;

procedure TfmBranchMan.FormClose(Sender: TObject;var Action: TCloseAction);
begin
  Action := caFree;
end;

end.

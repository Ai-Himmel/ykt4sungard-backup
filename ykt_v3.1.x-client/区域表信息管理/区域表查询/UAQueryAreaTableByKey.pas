unit UAQueryAreaTableByKey;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, Db, WVDBBinders, WVCmdReq, WorkViews, Grids, DBGrids,
  StdCtrls, ImageCtrls, ExtCtrls, UICtrls, WVCtrls, UIncrementComboBox,
  Mask, RzDBGrid, Buttons;

type
  TfaQueryAreaTable = class(TfaqhSimpleQueryTemp)
    WVLabel4: TWVLabel;
  private
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faQueryAreaTable: TfaQueryAreaTable;

implementation
uses KSFrameWorks,KSDataDictionary;

{$R *.DFM}
{ TfaQueryAreaTable }

procedure TfaQueryAreaTable.Init;
begin
  inherited;
  //FreeIdObjects(-28);
end;

initialization
  TUIStdClassFactory.Create('«¯”Ú≤È—Ø',TfaQueryAreaTable);

end.

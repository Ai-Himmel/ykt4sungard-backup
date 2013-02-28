unit UFieldDomains;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WorkViews;

type
  TdmFieldDomains = class(TDataModule)
    WVFieldDomain1: TWVFieldDomain;
    WVFieldDomain5: TWVFieldDomain;
    procedure WVFieldDomain5CheckValid(WorkField: TWVField);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dmFieldDomains: TdmFieldDomains;

implementation

{$R *.DFM}

procedure TdmFieldDomains.WVFieldDomain5CheckValid(WorkField: TWVField);
var
  CheckedFieldName : string;
  CheckedField : TWVField;
begin
  CheckedFieldName := WorkField.MonitorValueChangedFields;
  CheckedFieldName := StringReplace(CheckedFieldName,'|','',[rfReplaceAll]);
  CheckedField := WorkField.WorkView.FieldByName(CheckedFieldName);
  if CheckedField<>nil then
    WorkField.Valid := CheckedField.Valid and (WorkField.Data.AsString = CheckedField.Data.AsString);
end;

end.

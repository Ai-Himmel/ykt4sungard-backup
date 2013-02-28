unit UfmCheckPrice;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Mask, WVCtrls, WorkViews, ImageCtrls, ActnList, EditExts;

type
  TfmCheckPrice = class(TForm)
    WorkView: TWorkView;
    btnOK: TImageButton;
    btnCancel: TImageButton;
    Label1: TLabel;
    Label2: TLabel;
    ActionList: TActionList;
    acOK: TAction;
    acCancel: TAction;
    edtPrice: TWVDigitalEdit;
    edtNum: TWVDigitalEdit;
    procedure acCancelExecute(Sender: TObject);
    procedure acOKExecute(Sender: TObject);
    procedure WorkViewFieldsMonitors0ValidChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
  private
    { Private declarations }
  public
    { Public declarations }
    constructor Create(APrice, ANum : Integer); reintroduce;
  end;

function GetProperPriceAndNum(var Price, Num : Integer) : Boolean;

implementation

{$R *.DFM}

function GetProperPriceAndNum(var Price, Num : Integer) : Boolean;
var
  tempForm : TfmCheckPrice;
begin
  tempForm := TfmCheckPrice.Create(Price,Num);
  try
    tempForm.ShowModal;
    Price := StrToIntDef(tempForm.edtPrice.Text,Price);
    Num := StrToIntDef(tempForm.edtNum.Text,Num);
    Result := tempForm.ModalResult = mrOk;
  finally
    tempForm.Free;
  end;
end;

{ TfmCheckPrice }

constructor TfmCheckPrice.Create(APrice, ANum: Integer);
begin
  inherited Create(nil);
  with WorkView do
  begin
    if APrice < 0 then
    begin
      Fields[0].Data.SetInteger(0);
      edtPrice.Enabled := True;
    end
    else begin
      Fields[0].Data.SetInteger(APrice);
      edtPrice.Enabled := False;
    end;
    if ANum < 1 then
    begin
      Fields[1].Data.SetInteger(1);
      edtNum.Enabled := True;
    end
    else begin
      Fields[1].Data.SetInteger(ANum);
      edtNum.Enabled := False;
    end;
  end;
end;

procedure TfmCheckPrice.acCancelExecute(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TfmCheckPrice.acOKExecute(Sender: TObject);
begin
  ModalResult := mrOK;
end;

procedure TfmCheckPrice.WorkViewFieldsMonitors0ValidChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  btnOK.Enabled := Valid;
end;

end.

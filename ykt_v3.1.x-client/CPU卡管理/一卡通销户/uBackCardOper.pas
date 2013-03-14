unit uBackCardOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, RzPanel, RzRadGrp, RzButton, StdCtrls, UIncrementComboBox,
  WVCtrls;

type
  TfrmBackCardOper = class(TForm)
    rgyj: TRzRadioGroup;
    btnOk: TRzBitBtn;
    btnCancle: TRzBitBtn;
    WVLabel11: TWVLabel;
    cbbType: TWVComboBox;
    procedure btnOkClick(Sender: TObject);
    procedure btnCancleClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    iType:Integer;
  end;

var
  frmBackCardOper: TfrmBackCardOper;

implementation

{$R *.DFM}

procedure TfrmBackCardOper.btnOkClick(Sender: TObject);
begin
  if (rgyj.ItemIndex<0) then
  begin
    ShowMessage('ÇëÑ¡ÔñÊÇ·ñÍËÑº½ð');
    Exit;
  end;
  iType := 1;
  close;
end;

procedure TfrmBackCardOper.btnCancleClick(Sender: TObject);
begin
  iType := 0;
  Close;
end;

procedure TfrmBackCardOper.FormShow(Sender: TObject);
begin
  cbbType.ItemIndex := 0;
end;

end.

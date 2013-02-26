unit input;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls,datareplist;

type
  Tinpfrm = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    doctor: TEdit;
    stuno: TLabel;
    studentno: TEdit;
    Label5: TLabel;
    Label7: TLabel;
    oldbegdate: TDateTimePicker;
    oldenddate: TDateTimePicker;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure procviewnow;
    procedure procviewold;
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  inpfrm: Tinpfrm;

implementation

{$R *.dfm}

procedure Tinpfrm.Button1Click(Sender: TObject);
begin
  procviewnow;
end;

procedure Tinpfrm.procviewnow;
var
  frm: Tdatreplistfrm;
begin
  Screen.Cursor := crHourGlass;
  try
    frm := Tdatreplistfrm.Create(self);
    try
      frm.begindate := FormatDateTime('yyyymmdd',nowbegDate.DateTime);
      frm.enddate:= FormatDateTime('yyyymmdd',nowenddate.DateTime);
      frm.doctcode:=trim(doctor.Text);
      frm.stdcode:=trim(studentno.Text);
      frm.ShowModal;
    finally
      frm.Free;
    end;
  finally
    Screen.Cursor := crDefault;
  end;
end;
procedure Tinpfrm.procviewold;
var
  frm: Tdatreplistfrm;
begin
  Screen.Cursor := crHourGlass;
  try
    frm := Tdatreplistfrm.Create(self);
    try
      frm.begindate := FormatDateTime('yyyymmdd',oldbegdate.DateTime);
      frm.enddate:= FormatDateTime('yyyymmdd',oldenddate.DateTime);
      frm.doctcode:=trim(doctor.Text);
      frm.stdcode:=trim(studentno.Text);
      frm.ShowModal;
    finally
      frm.Free;
    end;
  finally
    Screen.Cursor := crDefault;
  end;
end;


procedure Tinpfrm.Button2Click(Sender: TObject);
begin
procviewold;
end;

end.


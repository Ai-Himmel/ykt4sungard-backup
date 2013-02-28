unit UCalendar;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, ComCtrls, StdCtrls;

type
  TfaCalendar = class(TFrame)
    cbMonth: TComboBox;
    edYear: TEdit;
    UpDown: TUpDown;
    Image: TImage;
    lblDate: TLabel;
    procedure UpDownClick(Sender: TObject; Button: TUDBtnType);
    procedure DateTimeChange(Sender: TObject);
    procedure ImageClick(Sender: TObject);
  private
    FDate: TDateTime;
    FYear: Word;
    FMonth:Word;
    FDay:  Word;
    FCurrentDate:string;
    FMaxYear:    Integer;
    FMinYear:    Integer;
    procedure WMPaint(var Message: TWMPaint); message WM_PAINT;
    procedure DrawCalendar;
    procedure SetCurrentDate(const Value: string);
    procedure SetMaxYear(const Value: Integer);
    procedure SetMinYear(const Value: Integer);
    { Private declarations }
  protected
    offsetX:   Integer;
    offsetY:   Integer;
    LineCount: Integer;
    ColWidth:  Integer;
    RowHeight: Integer;
    DaysPanelTop: Integer;
    IsDrawing:  Boolean;
    function fmtstr(const str: string;len: Integer): string;
    { protected declarations }
  public
    constructor Create(AOwner: TComponent);override;
    procedure RefreshCalendar(InputDate: TDateTime);
    procedure Initial;
    function CheckDateValid(sDate: string):Boolean;
    { Public declarations }
  published
    property CurrentDate: string read FCurrentDate write SetCurrentDate;
    property MaxYear: Integer read FMaxYear write SetMaxYear;
    property MinYear: Integer read FMinYear write SetMinYear;
  end;

var
  days:array[1..44] of Integer;
  month:array[1..12] of Integer;

implementation

{$R *.DFM}

constructor TfaCalendar.Create(AOwner: TComponent);
begin
  inherited;
  Initial;
end;

procedure TfaCalendar.DateTimeChange(Sender: TObject);
begin
  if not IsDrawing then
    CurrentDate := edYear.Text+fmtstr(IntToStr(cbMonth.ItemIndex+1),2)+fmtstr(IntToStr(FDay),2);
end;

procedure TfaCalendar.DrawCalendar;
var
  bmp: TBitMap;
  i,Row,Col: Integer;
  sdate: string;
begin
  bmp := TBitMap.Create;
  bmp.Width := Image.Width;
  bmp.Height := Image.Height;
  bmp.Canvas.Brush.Color := Color;
  bmp.Canvas.FillRect(Image.ClientRect);
  bmp.Canvas.Brush.Color := clGray;
  bmp.Canvas.Brush.Style := bsSolid;
  bmp.Canvas.Pen.Color := Color;
  bmp.Canvas.Rectangle(0,0,400,20);

  bmp.Canvas.Font.Name := '宋体';
  bmp.Canvas.Font.Charset := GB2312_CHARSET;
  bmp.Canvas.Font.Size := 9;
  bmp.Canvas.Font.Height := -12;

  bmp.Canvas.Font.Color := clRed;

  ColWidth := bmp.Canvas.TextWidth('星期日') + offsetX;

  bmp.Canvas.TextOut(offsetX,offsetY,'星期日');

  bmp.Canvas.Font.Color := clBlack;
  bmp.Canvas.TextOut(ColWidth + offsetX,offsetY,'星期一');
  bmp.Canvas.TextOut(2*ColWidth + offsetX,offsetY,'星期二');
  bmp.Canvas.TextOut(3*ColWidth + offsetX,offsetY,'星期三');
  bmp.Canvas.TextOut(4*ColWidth + offsetX,offsetY,'星期四');
  bmp.Canvas.TextOut(5*ColWidth + offsetX,offsetY,'星期五');

  bmp.Canvas.Font.Color := clRed;
  bmp.Canvas.TextOut(6*ColWidth + offsetX,offsetY,'星期六');

  bmp.Canvas.Pen.Color := clGray;
  for i:=0 to 7 do
    bmp.Canvas.Rectangle(Rect(i*ColWidth + Round(offsetX/2),DaysPanelTop,i*ColWidth + Round(offsetX/2) + 1,DaysPanelTop + LineCount*RowHeight));

  for i:=1 to 44 do
  begin
    if days[i]<>0 then
    begin
      Col := i mod 7;
      Row := i div 7;
      if Col=0 then
        Row := Row - 1;

      Col := Col - 1;
      if Col<0 then
        Col := 6;

      if (Col=6) or (Col=0) then // or (days[i]=1) or (days[i]=FDay)
        bmp.Canvas.Font.Color := clRed
      else
        bmp.Canvas.Font.Color := clBlack;

      sdate := IntToStr(days[i]);
      while Length(sdate)<6 do
        sdate := ' ' + sdate;

      if days[i]=FDay then
      begin
        bmp.Canvas.Brush.Color := clGray;
        bmp.Canvas.Brush.Style := bsSolid;
        bmp.Canvas.Pen.Color := Color;
        bmp.Canvas.Rectangle(Rect(Col*ColWidth + Trunc(offsetX/2) + 1,DaysPanelTop + Row*RowHeight,(Col+1)*ColWidth + Trunc(offsetX/2),DaysPanelTop + (Row + 1)*RowHeight));
      end
      else
        bmp.Canvas.Brush.Style := bsClear;

      bmp.Canvas.TextOut(Col*ColWidth + offsetX,DaysPanelTop + offsetY + Row*RowHeight,sdate);
    end;
  end;

  Image.Canvas.Draw(0,0,bmp);
  bmp.Free;
end;

procedure TfaCalendar.RefreshCalendar(InputDate: TDateTime);
var
  i,Week: Integer;
begin
    month[1] := 31;
    month[2] := 28;
    month[3] := 31;
    month[4] := 30;
    month[5] := 31;
    month[6] := 30;
    month[7] := 31;
    month[8] := 31;
    month[9] := 30;
    month[10] := 31;
    month[11] := 30;
    month[12] := 31;

    if IsLeapYear(FYear) then
      month[2] := 29;

  for i:= 1 to 44 do
    days[i]:= 0;
  Week := DayOfWeek(FDate - FDay + 1);

  LineCount := ((Week + month[FMonth] - 1) Div 7) + 1;
  if ((Week + month[FMonth] - 1) Mod 7)=0 then
    LineCount := LineCount - 1;

  for i:= Week to Week + month[FMonth] - 1 do
    days[i]:= i - Week +1;
    
  Invalidate;
end;

procedure TfaCalendar.Initial;
begin
  DaysPanelTop := 40;
  RowHeight := 30;
  offsetX := 18;
  offsetY := 5;

  MaxYear := 3000;
  MinYear := 1949;
  FDate := Now;

  CurrentDate := FormatDateTime('YYYYMMDD',Now);

  cbMonth.ItemIndex:= FMonth-1;
  edYear.Text:=fmtstr(IntToStr(FYear),4);
  UpDown.Position:=FYear;
end;

procedure TfaCalendar.UpDownClick(Sender: TObject; Button: TUDBtnType);
begin
  if UpDown.Position=UpDown.Max then
    UpDown.Position:=UpDown.Min+1
  else if UpDown.Position=UpDown.Min then
    UpDown.Position:=UpDown.Max-1;
  edYear.Text:=fmtstr(IntToStr(UpDown.Position),4);
end;

procedure TfaCalendar.WMPaint(var Message: TWMPaint);
begin
  DrawCalendar;
  inherited;
end;

procedure TfaCalendar.ImageClick(Sender: TObject);
var
  i: Integer;
  Row,Col: Integer;
  pos: TPoint;
begin
  pos := ScreenToClient(Mouse.CursorPos);
  pos.x := pos.x - Image.Left;
  pos.y := pos.y - Image.Top;

  for i:=1 to 44 do
  begin
    if days[i]<>0 then
    begin
       Col := i mod 7;
      Row := i div 7;
      if Col=0 then
        Row := Row - 1;

      Col := Col - 1;
      if Col<0 then
        Col := 6;
      if (pos.x>Col*ColWidth + Trunc(offsetX/2) + 1) and (pos.x<(Col + 1)*ColWidth + Trunc(offsetX/2)) and (pos.y>(DaysPanelTop + Row*RowHeight)) and (pos.y<(DaysPanelTop + (Row + 1)*RowHeight)) then
      begin
        CurrentDate := edYear.Text+fmtstr(IntToStr(cbMonth.ItemIndex+1),2)+fmtstr(IntToStr(days[i]),2);
        Break;
      end;
    end;
  end;

end;

procedure TfaCalendar.SetCurrentDate(const Value: string);
var
  sDate: string;
begin
  if CheckDateValid(Value) then
  begin
    //一次跳n年
    {
    sDate := FormatDateTime('YYYYMMDD',FDate);
    if Value <> sDate then
    begin
      if  sDate < Value then
        FDate := Fdate + Trunc(Abs(StrToInt(Copy(Value,1,4))-FYear))*365
      else if sDate > Value then
        FDate := Fdate - Trunc(Abs(StrToInt(Copy(Value,1,4))-FYear))*365;
    end;

    //一次跳一天
    sDate := FormatDateTime('YYYYMMDD',FDate);
    while Value <> sDate do
    begin
      if  sDate < Value then
        FDate := Fdate + 1
      else if sDate > Value then
        FDate := Fdate - 1;
      sDate := FormatDateTime('YYYYMMDD',FDate);
    end;
    }

    FCurrentDate := Value;
    FYear := StrToInt(Copy(Value,1,4));
    FMonth := StrToInt(Copy(Value,5,2));
    FDay := StrToInt(Copy(Value,7,2));
    FDate := EnCodeDate(FYear,FMonth,FDay);

    IsDrawing := True; //此处加IsDrawing可防止重复画
    cbMonth.ItemIndex := FMonth - 1;
    edYear.Text := fmtstr(IntToStr(FYear),4);
    UpDown.Position:=FYear;

    RefreshCalendar(FDate);
    IsDrawing := False;
    lblDate.Caption := Value;
  end;
end;

function TfaCalendar.CheckDateValid(sDate: string): Boolean;
var
  MonthDays:array[1..12] of Integer;
  Year,Month,Day: Word;
begin
  MonthDays[1]:=31;
  MonthDays[2]:=28;
  MonthDays[3]:=31;
  MonthDays[4]:=30;
  MonthDays[5]:=31;
  MonthDays[6]:=30;
  MonthDays[7]:=31;
  MonthDays[8]:=31;
  MonthDays[9]:=30;
  MonthDays[10]:=31;
  MonthDays[11]:=30;
  MonthDays[12]:=31;

  if Length(sDate)<>8 then
  begin
    Result := False;
    Exit;
  end;

  try
    StrToInt(sDate);
  except
    Result := False;
    Exit
  end;

  Year := StrToInt(Copy(sDate,1,4));
  Month := StrToInt(Copy(sDate,5,2));
  Day := StrToInt(Copy(sDate,7,2));

  if year < 1 then
  begin
    Result := False;
    Exit;
  end;

  if year > 9999 then
  begin
    Result := False;
    Exit;
  end;

  if IsLeapYear(Year) then
    MonthDays[2] := 29;

  if (Month < 1) or (Month > 12) then
  begin
    Result := False;
    Exit;
  end;

  if (Day > MonthDays[Month]) or (Day < 1) then
  begin
    Result := False;
    Exit;
  end;

  Result := True;
end;

procedure TfaCalendar.SetMaxYear(const Value: Integer);
begin
  if Value < FMinYear then
    Exit;

  if Value > 9999 then
    FMaxYear := 9999
  else if Value < 1 then
    FMaxYear := 1
  else
    FMaxYear := Value;

  UpDown.Max := Value + 1;
end;

procedure TfaCalendar.SetMinYear(const Value: Integer);
begin
  if Value > FMaxYear then
    Exit;

  if Value > 9999 then
    FMinYear := 9999
  else if Value < 1 then
    FMinYear := 1
  else
    FMinYear := Value;

  UpDown.Min := Value - 1;
end;

function TfaCalendar.fmtstr(const str: string;len: Integer): string;
begin
  Result := str;
  while Length(Result) < len do
    Result := '0' + Result;
end;

end.

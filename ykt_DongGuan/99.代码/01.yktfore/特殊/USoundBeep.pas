unit USoundBeep;

interface

uses
  windows;

  procedure BeepAlarm_Warning;
  procedure BeepAlarm_Fatal;

implementation

procedure BeepAlarm_Warning;
begin
  Windows.Beep(1000,100);
  Sleep(10);
  Windows.Beep(800,100);
  Sleep(10);
  Windows.Beep(1000,100);
end;

procedure BeepAlarm_Fatal;
begin
  Windows.Beep(1000,200);
  Sleep(10);
  Windows.Beep(1000,200);
end;

end.

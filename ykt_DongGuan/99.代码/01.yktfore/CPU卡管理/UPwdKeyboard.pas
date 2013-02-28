unit UPwdKeyboard;

interface

const
  NormalMode = 0;
  NormalBaud = 9600;
  //NormalTimeOut = 60;
  MaxPassWordLength = 32;

{
  <Function>GetPWD_NormalPinpad
  <What>来自DLL的输出函数
  <Params>
    -
  <Return>
  <Exception>
}
function GetPWD_NormalPinpad(ComNo, Baud, Mode, Timeout, Leng : Integer;
  Keycode : PChar):Integer; stdcall;

{
  <Function>GetFromPasswordKeyboard
  <What>对DLL输出函数的基本包装，尽量使用缺省值。
  <Params>
    -
  <Return>
    是否成功，如果成功，将文字保存在AText里面。否则不修改AText。
  <Exception>
}
function GetFromPasswordKeyboard(ComNo, Leng, Timeout : Integer; var AText : string) : Boolean;

implementation

const
  PwdKeyDLL = 'pin.dll';

function GetPWD_NormalPinpad(ComNo, Baud, Mode, Timeout, Leng : Integer;
  Keycode : PChar):Integer; external PwdKeyDLL;

function GetFromPasswordKeyboard(ComNo, Leng, Timeout : Integer; var AText : string) : Boolean;
var
  Password : array[0..MaxPassWordLength+1] of Char;
begin
  Assert((0<Leng) and (Leng<=MaxPassWordLength));
  FillChar(Password,SizeOf(Password),0);
  // Leng+1 的目的是避免输入6位密码以后不确认就马上返回。
  Result := GetPWD_NormalPinpad(ComNo, NormalBaud, NormalMode, Timeout, Leng+1, @Password)>=0;
  if Result then
  begin
    AText := Password;
    // 长度截断
    AText := Copy(AText,1,Leng);
  end;
end;

end.

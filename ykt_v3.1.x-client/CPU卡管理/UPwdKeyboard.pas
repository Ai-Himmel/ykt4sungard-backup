unit UPwdKeyboard;

interface

const
  NormalMode = 0;
  NormalBaud = 9600;
  //NormalTimeOut = 60;
  MaxPassWordLength = 32;

{
  <Function>GetPWD_NormalPinpad
  <What>����DLL���������
  <Params>
    -
  <Return>
  <Exception>
}
function GetPWD_NormalPinpad(ComNo, Baud, Mode, Timeout, Leng : Integer;
  Keycode : PChar):Integer; stdcall;

{
  <Function>GetFromPasswordKeyboard
  <What>��DLL��������Ļ�����װ������ʹ��ȱʡֵ��
  <Params>
    -
  <Return>
    �Ƿ�ɹ�������ɹ��������ֱ�����AText���档�����޸�AText��
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
  // Leng+1 ��Ŀ���Ǳ�������6λ�����Ժ�ȷ�Ͼ����Ϸ��ء�
  Result := GetPWD_NormalPinpad(ComNo, NormalBaud, NormalMode, Timeout, Leng+1, @Password)>=0;
  if Result then
  begin
    AText := Password;
    // ���Ƚض�
    AText := Copy(AText,1,Leng);
  end;
end;

end.

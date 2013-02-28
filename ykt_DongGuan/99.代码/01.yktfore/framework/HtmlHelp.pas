unit HtmlHelp;

interface
uses
  Windows, Messages, SysUtils, Classes,Forms, Dialogs;

  function  HtmlHelpA(hwndCaller: THandle; pazfile: String;uCommand, dwData: DWord): DWord; stdcall;

  procedure htmHelp(hwndCaller: THandle;inStr:string);


implementation
function  HtmlHelpA(hwndCaller: THandle; pazfile: String;uCommand, dwData: DWord): DWord; stdcall external 'hhctrl.ocx';

procedure htmHelp(hwndCaller: THandle;inStr:string);
var
  exePath:string;
  //myFile:TIniFile;
  htmName:string;
  //iniName:string;
begin
  exePath := ExtractFilePath(Application.ExeName);
  //myFile := TIniFile.Create(exePath+'.\configs\SetPara.ini');
  //iniName := myFile.ReadString('htmlHelp','htmlName','');
  //ShowMessage(iniName);
  htmName := exePath+'校园一卡通管理系统帮助手册.CHM'+'::'+instr;
  //ShowMessage(htmName);
  HtmlHelpA (hwndCaller, htmName,0,0);
end;


end.

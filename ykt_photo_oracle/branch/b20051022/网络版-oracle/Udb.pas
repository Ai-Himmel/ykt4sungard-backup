unit Udb;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB,IniFiles;

type
  Tdm = class(TDataModule)
    ConnectPhoto: TADOConnection;
    procedure DataModuleCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    //soper中的1query,2edit,3pic,4import,5print,6data
    oper_code, oper_name, login, loginout,soper,sdata: string;
    status: boolean;
    sconnstring:string;  //连接数据库字符串
    function CSH(s: string): string;
    function judgelimit(oper: string; code:integer):boolean;
  end;

var
  dm: Tdm;

implementation

{$R *.DFM}

{ Tdm }

function Tdm.CSH(s: string): string;
var i1, i3, k: integer;
begin
  i1 := length(s);
  for i3 := 1 to i1 do
  begin
    if ((s[i3] >= 'a') and (s[i3] <= 'z')) or ((s[i3] >= 'A') and (s[i3] <= 'Z')) then
    begin
      k := ord(s[i3]) - 8;
    end
    else
      if (s[i3] >= '0') and (s[i3] <= '9') then
      begin
        k := ord(s[i3]) + 9;
      end
      else
      begin
        k := ord(s[i3]) + 18;
      end;
    if (k < 1) or (k > 255) then
    begin
      k := 88;
    end;
    s[i3] := chr(k);
  end;
  result := s;

end;

procedure Tdm.DataModuleCreate(Sender: TObject);
//begin
  //if ConnectPhoto.Connected = false then
    //ConnectPhoto.Connected := true;
var
  inifile:TIniFile;
  sfilename:string;
begin
  sfilename:= ExtractFilePath(Paramstr(0)) + 'file.ini';
  inifile:= TIniFile.Create(sfilename);
  sconnstring:=inifile.ReadString('DataBase','conn',sconnstring);
  if ConnectPhoto.Connected then
    ConnectPhoto.Connected:=false;
  try
  ConnectPhoto.ConnectionString:= sconnstring;
    ConnectPhoto.Connected:=True;
  except
    ShowMessage('数据库连接失败，请检查配置库是否正确！');
  end;
end;

//判断权限,code为权限编号，oper为所有权限
function Tdm.judgelimit(oper: string; code:integer): boolean;
begin
  if copy(oper,code,1)='1' then
    result:=true
  else
    result:=false;
end;

end.


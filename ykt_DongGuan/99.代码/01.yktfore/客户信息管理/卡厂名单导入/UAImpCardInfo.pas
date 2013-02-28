unit UAImpCardInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls,Contnrs;

type
  TStrArray = array[1..7] of string;
  
type
  TfaqhImpCardInfo = class(TfaqhSimpleQueryTemp)
    btnImport: TBitBtn;
    dlgOpen: TOpenDialog;
    lbl1: TLabel;
    lblFile: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    pbStatues: TProgressBar;
    mmoList: TMemo;
    dlgSave1: TSaveDialog;
    procedure btnImportClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private
    { Private declarations }
    function  RegulateStr(aString,Sepchar:string):string;//去掉多余的分割符,规范字符串
    function GetSubStr(var aString:string;SepChar:String):String;//得到字符串中一个子串,因要改变参数aString的值,所以将它用var定义。
    function GetSubStrNum(aString,SepChar:String):Integer;//计算一个字符串要被分割成几个字段。 
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImpCardInfo: TfaqhImpCardInfo;

  Const Space= ' ';

implementation

uses KsFrameworks, KSClientConsts;
     
{$R *.DFM}

procedure TfaqhImpCardInfo.Init;
begin
  inherited;
end;

function TfaqhImpCardInfo.RegulateStr(aString, Sepchar: string): string;
var 
  i,Num:Integer;
  Flag:Boolean;
  MyStr,TempStr:String;
begin
  Flag:=False;//进行标志,去除多余的分割符
  Num:=Length(aString);//计算aString串的长度
  for i:=1 to Num do
  begin
    TempStr:=Copy(aString,i,1);//取aString串中的一字符
    if TempStr <> SepChar then
    begin
      MyStr:=MyStr+TempStr;
      Flag:=True;
    end
    else
    if(Flag = True)then
    begin
      Mystr:=Mystr+TempStr;
      Flag:=False;
    end;
  end;
  if MyStr[Length(MyStr)] <> SepChar then
  MyStr:=MyStr+SepChar;
  RegulateStr:=MyStr;
end;

function TfaqhImpCardInfo.GetSubStr(var aString:string;SepChar:String): String;
var
  Mystr:String;
  //StrLen:Integer;
  SepCharPos:Integer;
begin
  //StrLen:=Length(aString);
  SepCharPos:=Pos(SepChar,aString);//计算分割符在子串中的位置
  MyStr:=Copy(aString,1,SepCharPos-1);//将分割符前所有字符放到mystr串中
  Delete(aString,1,SepCharPos);//除去分割符和分割符前的子串
  ShowMessage(astring);
  GetSubStr:=MyStr;//返回一个字段
end;

function TfaqhImpCardInfo.GetSubStrNum(aString, SepChar: String): Integer;
var
  i:Integer;
  StrLen:Integer;
  Num:Integer;
begin
  StrLen:=Length(aString);
  Num:=0;
  for i:=1 to StrLen do
  if Copy(aString,i,1)=SepChar then
    Num:=Num+1;
  GetSubStrNum:=Num;
end;

procedure TfaqhImpCardInfo.btnImportClick(Sender: TObject);
const
  TabChar = ' ';//定义空格键
var
  i, j: integer;
  dd : TStrArray;
  str:String;
  errList:TStringList;
begin
  pbStatues.Max := mmoList.Lines.Count;
  errList := nil;
  try
    errList := TStringList.Create;
    //mmo1.Lines.Clear;
    for i:=0 to mmoList.Lines.Count-1 do
    begin
      str := mmoList.Lines[i];
      if Trim(str)='' then
        Continue;
      j:=1;
      while pos(TabChar, str) > 0 do
      begin
        dd[j] := Trim(Copy(str, 1, pos(TabChar, str)));
        Delete(str, 1, Pos(TabChar, str));
        Str := Trim(Str);
        Inc(j);
      end;
      DD[7] := Trim(str);

      WorkView.FieldByName('物理卡号').Data.SetString(dd[1]);
      WorkView.FieldByName('业务编号').Data.SetString(dd[2]);
      WorkView.FieldByName('资源号').Data.SetString(dd[3]);
      WorkView.FieldByName('应用序列号').Data.SetString(dd[4]);
      WorkView.FieldByName('UCID').Data.SetString(dd[5]);
      WorkView.FieldByName('激活码').Data.SetString(dd[7]);
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('物理卡号：'+dd[1]+'的卡导入失败，原因-'+e.Message);
          //pbStatues.Position := pbStatues.Position+1;
          //Continue;
        end;
      end;
      if WorkView.FieldByName('返回码').Data.AsString<>'0' then
      begin
        errList.Add('物理卡号：'+dd[1]+'的卡导入失败，原因-'+WorkView.FieldByName('返回信息').Data.AsString);
      end;
      pbStatues.Position := pbStatues.Position+1;
    end;
  finally
    if errList.Count>0 then
    begin
      if dlgSave1.Execute then
        errList.SaveToFile(dlgSave1.FileName+'-卡厂数据失败记录.txt');
    end;
    errList.Destroy;
  end;
  Context.GetDialogSystem.ShowMessage('卡厂数据导入完成！');
end;

procedure TfaqhImpCardInfo.btnQueryClick(Sender: TObject);
begin
  if dlgOpen.Execute then
    mmoList.Lines.LoadFromFile(dlgOpen.FileName);
  LabRecordCount.Caption := '打开文件的记录条数：'+IntToStr(mmoList.Lines.Count);
  lblFile.Caption := dlgOpen.FileName;
end;

initialization
  TUIStdClassFactory.Create('卡厂名单导入',TfaqhImpCardInfo);

end.
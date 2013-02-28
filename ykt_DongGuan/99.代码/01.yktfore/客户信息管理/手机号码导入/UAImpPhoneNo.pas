unit UAImpPhoneNo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls,Contnrs;

type
  TStrArray = array[1..2] of string;
  
type
  TfaqhImpPhoneNo = class(TfaqhSimpleQueryTemp)
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
    function  RegulateStr(aString,Sepchar:string):string;//ȥ������ķָ��,�淶�ַ���
    function GetSubStr(var aString:string;SepChar:String):String;//�õ��ַ�����һ���Ӵ�,��Ҫ�ı����aString��ֵ,���Խ�����var���塣
    function GetSubStrNum(aString,SepChar:String):Integer;//����һ���ַ���Ҫ���ָ�ɼ����ֶΡ� 
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImpPhoneNo: TfaqhImpPhoneNo;

  Const Space= ' ';

implementation

uses KsFrameworks, KSClientConsts;
     
{$R *.DFM}

procedure TfaqhImpPhoneNo.Init;
begin
  inherited;
end;

function TfaqhImpPhoneNo.RegulateStr(aString, Sepchar: string): string;
var 
  i,Num:Integer;
  Flag:Boolean;
  MyStr,TempStr:String;
begin
  Flag:=False;//���б�־,ȥ������ķָ��
  Num:=Length(aString);//����aString���ĳ���
  for i:=1 to Num do
  begin
    TempStr:=Copy(aString,i,1);//ȡaString���е�һ�ַ�
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

function TfaqhImpPhoneNo.GetSubStr(var aString:string;SepChar:String): String;
var
  Mystr:String;
  //StrLen:Integer;
  SepCharPos:Integer;
begin
  //StrLen:=Length(aString);
  SepCharPos:=Pos(SepChar,aString);//����ָ�����Ӵ��е�λ��
  MyStr:=Copy(aString,1,SepCharPos-1);//���ָ��ǰ�����ַ��ŵ�mystr����
  Delete(aString,1,SepCharPos);//��ȥ�ָ���ͷָ��ǰ���Ӵ�
  ShowMessage(astring);
  GetSubStr:=MyStr;//����һ���ֶ�
end;

function TfaqhImpPhoneNo.GetSubStrNum(aString, SepChar: String): Integer;
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

procedure TfaqhImpPhoneNo.btnImportClick(Sender: TObject);
const
  TabChar = ' ';//����ո��
var
  i, j: integer;
  dd : TStrArray;
  str:String;
  errList:TStringList;
  sTime:string;
begin
  if Application.MessageBox('��ȷ��Ҫ�����ֻ�������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  sTime := FormatDateTime('yyyyMMddhhMMss',Now);
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
      DD[2] := Trim(str);

      WorkView.FieldByName('�ֻ�ͨ������').Data.SetString(dd[1]);
      WorkView.FieldByName('�ֻ���').Data.SetString(dd[2]);
      WorkView.FieldByName('ʱ���').Data.SetString(sTime);
      //WorkView.FieldByName('Ӧ�����к�').Data.SetString(dd[4]);
      //WorkView.FieldByName('UCID').Data.SetString(dd[5]);
      //WorkView.FieldByName('������').Data.SetString(dd[6]);
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('�ֻ�ͨ�����ţ�'+dd[1]+'�Ŀ�����ʧ�ܣ�ԭ��-'+e.Message);
          //pbStatues.Position := pbStatues.Position+1;
          //Continue;
        end;
      end;
      if WorkView.FieldByName('������').Data.AsString<>'0' then
      begin
        errList.Add('�ֻ�ͨ�����ţ�'+dd[1]+'�Ŀ�����ʧ�ܣ�ԭ��-'+WorkView.FieldByName('������Ϣ').Data.AsString);
      end;
      pbStatues.Position := pbStatues.Position+1;
    end;
  finally
    if errList.Count>0 then
    begin
      if dlgSave1.Execute then
        errList.SaveToFile(dlgSave1.FileName+'-�ֻ����뵼��ʧ�ܼ�¼.txt');
    end;
    errList.Destroy;
  end;
  Context.GetDialogSystem.ShowMessage('�ֻ����뵼����ɣ�');
end;

procedure TfaqhImpPhoneNo.btnQueryClick(Sender: TObject);
begin
  if dlgOpen.Execute then
    mmoList.Lines.LoadFromFile(dlgOpen.FileName);
  LabRecordCount.Caption := '���ļ��ļ�¼������'+IntToStr(mmoList.Lines.Count);
  lblFile.Caption := dlgOpen.FileName;
end;

initialization
  TUIStdClassFactory.Create('�ֻ����뵼��',TfaqhImpPhoneNo);

end.
unit UAPrint;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  QuickRpt, Qrctrls, ExtCtrls, StdCtrls, Db, ADODB,JPEG;

type
  TAPrintForm = class(TForm)
    QuickRep1: TQuickRep;
    DetailBand1: TQRBand;
    QRLabel4: TQRLabel;
    Label1: TLabel;
    edtNo: TEdit;
    btnQuery: TButton;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    LName: TLabel;
    LDep: TLabel;
    LNo: TLabel;
    ADOQuery1: TADOQuery;
    ADOQuery2: TADOQuery;
    btnPreview: TButton;
    chkS: TCheckBox;
    Button1: TButton;
    Panel1: TPanel;
    Image1: TImage;
    cbType: TComboBox;
    Label5: TLabel;
    procedure btnQueryClick(Sender: TObject);
    procedure btnPreviewClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure edtNoKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
    procedure GetFont;
  public
    { Public declarations }
  end;

var
  APrintForm: TAPrintForm;

implementation

uses UConfigs, Udb;

{$R *.DFM}

procedure TAPrintForm.btnQueryClick(Sender: TObject);
var
  content:String;
  StuEmpNumber:String;
  sqlstr:string;
  F3:TADOBlobStream;
  M1:TMemoryStream;  //�ڴ�����
  Fjpg: TJpegImage;  //��Image ��� Jpeg ���м���ʽ��
  SpeCode:String;  //רҵ���룬��Ժϵ���룬
  DeptCode:String; //���Ŵ���
begin
  If edtNo.Text='' then
  begin
    ShowMessage('�������ѧ����Ϊ�գ�');
    edtno.SetFocus;
    exit;
  end;
  Image1.Picture.Assign(nil);
  StuEmpNumber:=Trim(edtNo.text);
  AdoQuery2.Close;             //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸�
  AdoQuery2.SQL.Clear;

  AdoQuery2.SQL.Add('SELECT * from '+PersonTableName+'  where '+
       PersonNo+'='+QuotedStr(StuEmpNumber));
  AdoQuery2.Open;
  if AdoQuery2.RecordCount=0 then
  begin
    ShowMessage('��ѧ���ż�¼�����ڣ�');          //����©����
    edtNo.Text:='';
    exit;
  end;

  DeptCode:= AdoQuery2.FieldByName(PersonKindName2).AsString;
  LName.Caption:=AdoQuery2.FieldByName(PersonName).AsString;
  //QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString+'('+AdoQuery2.FieldByName(PersinKindNo3).AsString+')';  //��ʦ���������ټ�ְ��
  LNo.Caption:= AdoQuery2.FieldByName(PersonNo).AsString;  //����
  SpeCode:=AdoQuery2.FieldByName(PersonKindNo1).AsString;
  //�����ѧ����,ȡ��רҵ��Ϣ��Ժϵ��Ϣ;
  //----ȡ��רҵ��Ϣ------
  AdoQuery2.Close;
  AdoQuery2.SQL.Clear;
  AdoQuery2.SQL.Add('select * from '+SpecialTableName+' where '+
       PersonKindNo1+'='+QuotedStr(SpeCode));
  AdoQuery2.Open;
  //----ȡ�ò�����Ϣ------
  AdoQuery2.Close;
  AdoQuery2.SQL.Clear;
  AdoQuery2.SQL.Add('select '+PersonKindName2+' from '+DepartmentTableName+' where '+
       PersonKindNo2+'='+QuotedStr(DeptCode));
  AdoQuery2.Open;
  Ldep.Caption:=AdoQuery2.FieldByName(PersonKindName2).AsString;
  //----ȡ�ò�����Ϣ------

  //��ADOQuery1 ִ����Ƭ��Ĳ�ѯ��
  //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸ģ�
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add('select * from '+PhotoTableName+' where '+
       PersonNo+'='+QuotedStr(StuEmpNumber));
  ADOQuery1.Open;
  ADOQuery1.Edit;
  F3:=TADOBlobStream.Create(TBlobField(ADOQuery1.fieldbyname(PhotoRecord)),bmread);
  Try
    If TBlobField(AdoQuery1.FieldByName(PhotoRecord)).AsString<>null then
    TBlobField(AdoQuery1.FieldByName(PhotoRecord) ).SaveToStream(F3);

    Fjpg :=TJpegImage.Create ;
    Try
      F3.Position:=0;
      image1.Picture.Graphic := nil;
      If  F3.Size>100 then
      begin
        FJpg.LoadFromStream(F3);
        image1.Picture.Graphic :=FJpg;
      end
      else
      begin
      
      end;
    Finally
     Fjpg.Free;
    end;
  Finally
    F3.Destroy;
  end;
end;

procedure TAPrintForm.btnPreviewClick(Sender: TObject);
begin
  if trim(LName.Caption)='' then
  begin
    showmessage('���Ȳ�ѯ��Ҫ�������Ա��Ϣ��');
    edtNo.SetFocus;
    Exit;
  end;
  if application.MessageBox('��ȷ��Ҫ����Ƭ��Ϣ��',pchar(application.Title),mb_iconquestion+mb_yesno)=idyes then
  begin
    GetFont;
    QuickRep1.Preview;
  end;
end;

procedure TAPrintForm.GetFont;
var
  i,iL,j,jL:integer;
  s,m:string;
begin
  iL:=length(trim(LName.caption));
  jL:=Length(cbType.Text)-length(Trim(cbType.Text));
  for j := 1 to jL do
  begin
    m:=m+' ';
  end;
  for i:=1 to iL do
  begin
    s:=s+' ';
  end;
  if chkS.Checked then
    QRLabel4.Caption:=s+'  '+m+'('+trim(cbtype.Text)+')'
  else
    QRLabel4.Caption:=s+m+'('+trim(cbtype.Text)+')';
end;

procedure TAPrintForm.Button1Click(Sender: TObject);
begin
  Close;
end;

procedure TAPrintForm.edtNoKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if key = vk_return then
    btnquery.Click();
end;

procedure TAPrintForm.FormCreate(Sender: TObject);
var
  path : string;
begin
  path := ExtractFilePath(Application.ExeName);
  cbtype.Items.Clear;
  cbtype.Items.LoadFromFile(path+'Type.txt');
  cbtype.ItemIndex:=0;
end;

end.

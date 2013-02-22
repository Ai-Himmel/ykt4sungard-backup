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
    Label4: TLabel;
    LName: TLabel;
    LNo: TLabel;
    ADOQuery1: TADOQuery;
    ADOQuery2: TADOQuery;
    btnPreview: TButton;
    Button1: TButton;
    Panel1: TPanel;
    Image1: TImage;
    chkType: TCheckBox;
    chkRetire: TCheckBox;
    qryType: TADOQuery;
    procedure btnQueryClick(Sender: TObject);
    procedure btnPreviewClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure edtNoKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    perName:string;
    ifHeighLevel:string;  //����ְ�ж�
    ifRetire:string;      //������
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
       PersonNo+'='+QuotedStr(StuEmpNumber)+' with ur');
  AdoQuery2.Open;
  if AdoQuery2.RecordCount=0 then
  begin
    ShowMessage('��ѧ���ż�¼�����ڣ�');          //����©����
    edtNo.Text:='';
    exit;
  end;

  {20051009�ռ���--------------------------------------------------------------}
  //���������ְ����ʾ��ְ��
  if Copy(ADOQuery2.fieldbyname(reserve_2).AsString,Length(ADOQuery2.fieldbyname(reserve_2).AsString),1)='1' then
  begin
    qryType.Close;
    qryType.sql.Clear;
    qryType.sql.Add('select * from '+persontype+' where '+jobcode+'='+ #39+
                    ADOQuery2.fieldbyname(reserve_2).AsString+#39+' with ur');
    qryType.Open;
    if qryType.RecordCount=0 then
    begin
      ShowMessage('�ù��ŵ�ְ�������ϵͳ�в����ڣ���͹�����Ա��ϵ��');
      Exit;
    end;
    ifHeighLevel:='('+qryType.fieldbyname(jobname).asstring+')';
  end
  else
  begin
    ifHeighLevel:='';
  end;
  //���Ϊ��������Ա�����ں����ӡ
  if ADOQuery2.FieldByName(status).AsString='22' then
    ifRetire:='(����)'
  else if ADOQuery2.FieldByName(status).AsString='23' then
    ifRetire:='(����)'
  else
    ifRetire:='';
  {20051009�ռ������----------------------------------------------------------}

  //DeptCode:= AdoQuery2.FieldByName(PersonKindName2).AsString;
  perName:=AdoQuery2.FieldByName(PersonName).AsString;
  LName.Caption:=Trim(AdoQuery2.FieldByName(PersonName).AsString)+ifHeighLevel+ifRetire;
  LNo.Caption:= AdoQuery2.FieldByName(PersonNo).AsString;  //����
  SpeCode:=AdoQuery2.FieldByName(PersonKindNo1).AsString;

  //��ADOQuery1 ִ����Ƭ��Ĳ�ѯ��
  //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸ģ�
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add('select * from '+PhotoTableName+' where '+
       PersonNo+'='+QuotedStr(StuEmpNumber)+' with ur');
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
  {if Trim(QRLabel4.Caption)='' then
  begin
    ShowMessage('��Ҫ���������Ϊ�գ�����ȷ����Ϊ���ٲ�����Ϣ��');
    Exit;
  end;}
  if trim(LName.Caption)='' then
  begin
    showmessage('���Ȳ�ѯ��Ҫ�������Ա��Ϣ��');
    edtNo.SetFocus;
    Exit;
  end;
  GetFont;
  QuickRep1.Preview;
end;

procedure TAPrintForm.GetFont;
var
  i,iL,j,jL:integer;
  m,s:string;
begin
  iL:=length(trim(perName));
  jL:=Length(ifHeighLevel);
  for i := 1 to iL do
  begin
    m:=m+' ';
  end;
  for j := 1 to jL do
  begin
    s:=s+' ';
  end;
  if (chkType.Checked)and(chkRetire.Checked) then
    QRLabel4.Caption:=m+ifHeighLevel+ifretire
  else if (chkType.Checked) and (chkRetire.Checked=False) then
    QRLabel4.Caption:=m+ifHeighLevel
  else if (chkType.Checked=False) and (chkRetire.Checked) then
    QRLabel4.Caption:=m+s+ifretire
  else if (chkType.Checked=False) and (chkRetire.Checked=False) then
    QRLabel4.Caption:='';

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

end.

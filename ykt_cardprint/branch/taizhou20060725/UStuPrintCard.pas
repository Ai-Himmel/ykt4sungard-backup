unit UStuPrintCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB, Qrctrls, QuickRpt, ExtCtrls, StdCtrls, JPEG,printers;

type
  TStuPrintForm = class(TForm)
    ADOQuery1: TADOQuery;
    ADOQuery2: TADOQuery;
    QuickRep1: TQuickRep;
    DetailBand1: TQRBand;
    QRLabel1: TQRLabel;
    QRLabel2: TQRLabel;
    QRLabel3: TQRLabel;
    QRLabel4: TQRLabel;
    QRLType: TQRLabel;
    QRLabel6: TQRLabel;
    Image1: TQRImage;
    Label1: TLabel;
    Edit1: TEdit;
    btnQuery: TButton;
    btn: TButton;
    Button3: TButton;
    Button1: TButton;
    lblMakecard: TLabel;
    lbl1: TLabel;
    cbbArea: TComboBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnClick(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Edit1KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure Button1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
    procedure GetStuCardInfo;
  public
    { Public declarations }
  end;

var
  StuPrintForm: TStuPrintForm;

implementation
uses
  udb,UConfigs,USetPix, UEditName;

{$R *.DFM}

procedure TStuPrintForm.btnQueryClick(Sender: TObject);
var
  content:String;
  StuEmpNumber:String;
  F3:TADOBlobStream;
  M1:TMemoryStream;  //�ڴ�����
  Fjpg: TJpegImage;  //��Image ��� Jpeg ���м���ʽ��
  SpeCode:String;  //רҵ���룬��Ժϵ���룬
  DeptCode:String; //���Ŵ���
  areaCode:string;//У������
begin
  If Edit1.Text='' then
  begin
    ShowMessage('�������ѧ����Ϊ�գ�');
    exit;
  end;
  areaCode:=Copy(cbbArea.Text,1,Pos('-',cbbArea.Text)-1);
  Image1.Picture.Assign(nil);
  StuEmpNumber:=Trim(Edit1.text);
  AdoQuery2.Close;             //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸ģ�
  AdoQuery2.SQL.Clear;

  AdoQuery2.SQL.Add('SELECT * from '+PersonTableName+'  where '+
       PersonNo+'='+QuotedStr(StuEmpNumber)+' and area='+areaCode);
  AdoQuery2.Open;
  if AdoQuery2.RecordCount=0 then
  begin
    ShowMessage('��ѧ���ż�¼�����ڣ�');          //����©����
    Edit1.Text:='';
    exit;
  end;
  {20051105�ռ��룬�Ƿ��ƿ����ƿ������ж�--------------------------------------}
  if ADOQuery2.FieldByName(ifcard).AsInteger=1 then
  begin
    ShowMessage('��ѧ���Ѿ��ƹ���');
    lblMakecard.Caption:='�ѹ��ƿ����ƿ����ڣ�'+adoquery2.fieldbyname(makecarddate).AsString;
  end
  else
    lblMakecard.Caption:='';
  {20051105�ռ������----------------------------------------------------------}

  //DeptCode:= AdoQuery2.FieldByName(PersonKindName2).AsString;
  //2005-10-08�ռ���
  QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString;  //ѧ�����������ټ�ְ��
  sname:=trim(QRLabel4.Caption);
  QRLabel6.Caption:= AdoQuery2.FieldByName(PersonNo).AsString;  //ѧ��
  SpeCode:=AdoQuery2.FieldByName(PersonKindNo1).AsString; //ȡ��רҵ����

  //2005-10-08��ע��------------------------------------------------------------
  //QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString;  //ѧ�����������ټ�ѧ�����
  {if (AdoQuery2.FieldByName(PersinKindNo3).AsString='������')or(AdoQuery2.FieldByName(PersinKindNo3).AsString='��ְ��') then
  begin
    QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString;  //ѧ�����������ټ�ְ��
    sname:=trim(QRLabel4.Caption);
  end
  else
  begin
    QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString+'('+AdoQuery2.FieldByName(PersinKindNo3).AsString+')';  //��ʦ���������ټ�ְ��
    sname:=trim(QRLabel4.Caption);
  end;}
  //2005-10-08��ע������--------------------------------------------------------


  //2005-10-08��ע��------------------------------------------------------------
  //�����ѧ����,ȡ��רҵ��Ϣ��Ժϵ��Ϣ;
  //----ȡ��רҵ��Ϣ------
  AdoQuery2.Close;
  AdoQuery2.SQL.Clear;
  AdoQuery2.SQL.Add('select '+PersonKindName1+' from '+SpecialTableName+' where '+
       PersonKindNo1+'='+QuotedStr(SpeCode));
  AdoQuery2.Open;
  //----ȡ��רҵ��Ϣ------
  QRLType.Caption:=ADOQuery2.FieldByName(PersonKindName1).AsString;



  //----ȡ�ò�����Ϣ------
  {AdoQuery2.Close;
  AdoQuery2.SQL.Clear;
  AdoQuery2.SQL.Add('select '+PersonKindName2+' from '+DepartmentTableName+' where '+
       PersonKindNo2+'='+QuotedStr(DeptCode));
  AdoQuery2.Open; }
  //----ȡ�ò�����Ϣ------
  //2005-10-08��ע������--------------------------------------------------------

  //��ADOQuery1 ִ����Ƭ��Ĳ�ѯ��
  //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸ģ�
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add('select * from '+PhotoTableName+' where '+
       PersonNo+'='+QuotedStr(StuEmpNumber)+' and area='+areaCode);
  ADOQuery1.Open;
  ADOQuery1.Edit;

  F3:=TADOBlobStream.Create(TBlobField(ADOQuery1.fieldbyname(PhotoRecord)),bmread);
  Try
    //F3.Clear;
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

procedure TStuPrintForm.btnClick(Sender: TObject);
begin
  dm.makecard(Trim(Edit1.Text));
  QuickRep1.Page.Orientation:= poLandscape;
  QuickRep1.Preview;
end;

procedure TStuPrintForm.Button3Click(Sender: TObject);
begin
  SetPix:=TSetPix.Create(Application);
  SetPix.flag:=2;
  GetStuCardInfo;
  SetPix.Show;
end;

procedure TStuPrintForm.GetStuCardInfo;
begin
  SetPix.Edit1.Text:=FloatToStr(Image1.Size.Height);
  SetPix.Edit2.Text:=FloatToStr(Image1.Size.Width);
  SetPix.Edit3.Text:=FloatToStr(Image1.Size.Top);
  SetPix.Edit4.Text:=FloatToStr(Image1.Size.Left);
end;

procedure TStuPrintForm.Edit1KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if key=vk_return then
    btnQuery.Click();

end;

procedure TStuPrintForm.Button1Click(Sender: TObject);
begin
  cardtype:='S';  //ѧ����
  Editnameform:=Teditnameform.Create(nil);
  editnameform.ShowModal;
  editnameform.Free;
  editnameform:=nil;
end;

procedure TStuPrintForm.FormShow(Sender: TObject);
begin
  cbbArea.Items.Clear;
  cbbArea.Items.LoadFromFile(ExtractFilePath(Application.ExeName)+'\area.txt');
  cbbArea.ItemIndex:=0;

end;

end.

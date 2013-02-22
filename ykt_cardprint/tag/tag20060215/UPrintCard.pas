unit UPrintCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, QuickRpt, StdCtrls, Qrctrls,ADODB,JPEG,DB,printers;

type
  TFrmPrintCard = class(TForm)
    Edit1: TEdit;
    Label1: TLabel;
    btnQuery: TButton;
    QuickRep1: TQuickRep;
    DetailBand1: TQRBand;
    QRLabel1: TQRLabel;
    QRLabel3: TQRLabel;
    QRLabel4: TQRLabel;
    QRLabel6: TQRLabel;
    ADOQuery1: TADOQuery;
    ADOQuery2: TADOQuery;
    btnPreview: TButton;
    Image1: TQRImage;
    btnSet: TButton;
    Button1: TButton;
    qryType: TADOQuery;
    lblMakecard: TLabel;
    procedure btnQueryClick(Sender: TObject);
    procedure btnPreviewClick(Sender: TObject);
    procedure btnSetClick(Sender: TObject);
    procedure Edit1KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
    procedure GetEmpCardInfo;
  public
    { Public declarations }
  end;

var
  FrmPrintCard: TFrmPrintCard;

implementation

uses
  udb,UConfigs,USetPix, UEditName, UStuPrintCard;

{$R *.DFM}

procedure TFrmPrintCard.btnQueryClick(Sender: TObject);
var
  content:String;
  StuEmpNumber:String;
  F3:TADOBlobStream;
  M1:TMemoryStream;   //�ڴ�����
  Fjpg: TJpegImage;   //��Image ��� Jpeg ���м���ʽ��
  SpeCode:String;     //רҵ���룬��Ժϵ���룬
  DeptCode:String;    //���Ŵ���
  ifRetire:string;    //�Ƿ�������
  ifHeighLevel:string;//�Ƿ���и߼�ְ��

begin
  If Edit1.Text='' then
  begin
    ShowMessage('�������ѧ����Ϊ�գ�');
    exit;
  end;
  Image1.Picture.Assign(nil);
  StuEmpNumber:=Trim(Edit1.text);
  AdoQuery2.Close;             //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸�
  AdoQuery2.SQL.Clear;

  AdoQuery2.SQL.Add('SELECT * from '+PersonTableName+'  where '+
       PersonNo+'='+QuotedStr(StuEmpNumber));
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
    ShowMessage('�ù����Ѿ��ƹ���');
    lblMakecard.Caption:='���ƹ������ƿ����ڣ�'+adoquery2.fieldbyname(makecarddate).AsString;
  end
  else
    lblMakecard.Caption:='';
  {20051105�ռ������}

  {20051009�ռ���--------------------------------------------------------------}
  //���������ְ�������ƺ����ӡ��ְ��
  if Copy(Trim(ADOQuery2.fieldbyname(reserve_2).AsString),Length(Trim(ADOQuery2.fieldbyname(reserve_2).AsString)),1)='1' then
  begin
    qryType.Close;
    qryType.sql.Clear;
    qryType.sql.Add('select * from '+persontype+' where '+jobcode+'='+ #39+
                    Trim(ADOQuery2.fieldbyname(reserve_2).AsString)+#39);
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
  QRLabel4.Caption:= trim(AdoQuery2.FieldByName(PersonName).AsString)+ifHeighLevel+ifretire;
  sname:=trim(QRLabel4.Caption);

  {20051009��ע��---------------------------------------------------------------
  if(AdoQuery2.FieldByName(PersinKindNo3).AsString='��ְ��') then
  begin
    QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString;  //��ʦ���������ټ�ְ��
    sname:=trim(QRLabel4.Caption);
  end
  else
  begin
    QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString+'('+AdoQuery2.FieldByName(PersinKindNo3).AsString+')';  //��ʦ���������ټ�ְ��
    sname:=trim(QRLabel4.Caption);
  end;
  20051009��ע������-----------------------------------------------------------}

  QRLabel6.Caption:= AdoQuery2.FieldByName(PersonNo).AsString;  //����
  SpeCode:=AdoQuery2.FieldByName(PersonKindNo1).AsString;

  //2005-10-08��ע��------------------------------------------------------------
  //�����ѧ����,ȡ��רҵ��Ϣ��Ժϵ��Ϣ;
  //----ȡ��רҵ��Ϣ------
  {AdoQuery2.Close;
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
  QRLabel5.Caption:=AdoQuery2.FieldByName(PersonKindName2).AsString;}
  //----ȡ�ò�����Ϣ------
  //2005-10-08��ע������--------------------------------------------------------

  //��ADOQuery1 ִ����Ƭ��Ĳ�ѯ��
  //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸�
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

procedure TFrmPrintCard.btnPreviewClick(Sender: TObject);
begin
  dm.makecard(Trim(Edit1.Text));
  QuickRep1.Page.Orientation:= poLandscape;
  QuickRep1.Preview;
end;

procedure TFrmPrintCard.btnSetClick(Sender: TObject);
begin
  SetPix:=TSetPix.Create(Application);
  SetPix.flag:=1;
  GetEmpCardInfo;
  SetPix.Show;

end;

procedure TFrmPrintCard.GetEmpCardInfo;
begin
  SetPix.Edit1.Text:=FloatToStr(Image1.Size.Height);
  SetPix.Edit2.Text:=FloatToStr(Image1.Size.Width);
  SetPix.Edit3.Text:=FloatToStr(Image1.Size.Top);
  SetPix.Edit4.Text:=FloatToStr(Image1.Size.Left);
end;

procedure TFrmPrintCard.Edit1KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
    btnQuery.Click;
end;

procedure TFrmPrintCard.Button1Click(Sender: TObject);
begin
  cardtype:='T';  //���ڿ�
  Editnameform:=Teditnameform.Create(nil);
  editnameform.ShowModal;
  editnameform.Free;
  editnameform:=nil;
end;

end.

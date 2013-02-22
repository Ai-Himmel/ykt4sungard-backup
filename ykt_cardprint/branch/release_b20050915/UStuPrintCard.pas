unit UStuPrintCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB, Qrctrls, QuickRpt, ExtCtrls, StdCtrls, JPEG;

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
    QRLabel5: TQRLabel;
    QRLabel6: TQRLabel;
    Image1: TQRImage;
    Label1: TLabel;
    Edit1: TEdit;
    btnQuery: TButton;
    btn: TButton;
    QRLabel7: TQRLabel;
    QRLabel8: TQRLabel;
    Button3: TButton;
    Button1: TButton;
    procedure btnQueryClick(Sender: TObject);
    procedure btnClick(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Edit1KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure Button1Click(Sender: TObject);
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
  M1:TMemoryStream;  //内存流，
  Fjpg: TJpegImage;  //用Image 存放 Jpeg 的中间形式，
  SpeCode:String;  //专业代码，非院系代码，
  DeptCode:String; //部门代码
begin
  If Edit1.Text='' then
  begin
    ShowMessage('您输入的学工号为空！');
    exit;
  end;
  Image1.Picture.Assign(nil);
  StuEmpNumber:=Trim(Edit1.text);
  AdoQuery2.Close;             //如果其他地方有对ADOQuery1的引用，只有先关闭它，才能进行修改，
  AdoQuery2.SQL.Clear;

  AdoQuery2.SQL.Add('SELECT * from '+PersonTableName+'  where '+
       PersonNo+'='+QuotedStr(StuEmpNumber));
  AdoQuery2.Open;
  if AdoQuery2.RecordCount=0 then
  begin
    ShowMessage('该学工号记录不存在！');          //需求漏洞，
    Edit1.Text:='';
    exit;
  end;

  DeptCode:= AdoQuery2.FieldByName(PersonKindName2).AsString;
  //QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString;  //学生卡姓名后再加学生类别
  if (AdoQuery2.FieldByName(PersinKindNo3).AsString='本科生')or(AdoQuery2.FieldByName(PersinKindNo3).AsString='教职工') then
  begin
    QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString;  //学生卡姓名后再加职称
    sname:=trim(QRLabel4.Caption);
  end
  else
  begin
    QRLabel4.Caption:= AdoQuery2.FieldByName(PersonName).AsString+'('+AdoQuery2.FieldByName(PersinKindNo3).AsString+')';  //教师卡姓名后再加职称
    sname:=trim(QRLabel4.Caption);
  end;
  QRLabel6.Caption:= AdoQuery2.FieldByName(PersonNo).AsString;  //学号
  //Edit5.text:=ADOQuery1.FieldByName(PersonKindName2).AsString;
  SpeCode:=AdoQuery2.FieldByName(PersonKindNo1).AsString; //取得专业代码
//  QRLabel5.Caption:=AdoQuery2.FieldByName(PersinKindNo3).AsString;
//  FKindName:=ADOQuery1.FieldByName(PersinKindNo3).AsString;
//  FPersonNo:=StuEmpNumber;


  //如果是学生卡,取得专业信息和院系信息;
  //----取得专业信息------
  AdoQuery2.Close;
  AdoQuery2.SQL.Clear;
  AdoQuery2.SQL.Add('select '+PersonKindName1+' from '+SpecialTableName+' where '+
       PersonKindNo1+'='+QuotedStr(SpeCode));
  AdoQuery2.Open;
  QRLabel8.Caption:=ADOQuery2.FieldByName(PersonKindName1).AsString;
//  Edit6.Text:= Label17.Caption;
//  FSpecName:= ADOQuery1.FieldByName(PersonKindName1).AsString;
  //----取得专业信息------



  //----取得部门信息------
  AdoQuery2.Close;
  AdoQuery2.SQL.Clear;
  AdoQuery2.SQL.Add('select '+PersonKindName2+' from '+DepartmentTableName+' where '+
       PersonKindNo2+'='+QuotedStr(DeptCode));
  AdoQuery2.Open;
  QRLabel5.Caption:=AdoQuery2.FieldByName(PersonKindName2).AsString;
//  FDeptName:= ADOQuery1.FieldByName(PersonKindName2).AsString;
  //----取得部门信息------

  //用ADOQuery1 执行照片表的查询，
  //如果其他地方有对ADOQuery1的引用，只有先关闭它，才能进行修改，
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add('select * from '+PhotoTableName+' where '+
       PersonNo+'='+QuotedStr(StuEmpNumber));
  ADOQuery1.Open;
  ADOQuery1.Edit;
//  Label20.Caption:=ADOQuery1.FieldByName(PhotoDateRecord).AsString;

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
        //Panel6.Caption:='没有原始照片';
      end;
    Finally
     Fjpg.Free;
    end;
  Finally
    F3.Destroy;
  end;

{  if not ADOTable1.Active then
  begin
    ADOTable1.Active:=True;
  end;
  ADOTable1.Locate(PersonNo,StuEmpNumber,[loCaseInsensitive]);
  Label20.Caption:=ADOTable1.FieldByName(PhotoDateRecord).AsString;
  Button5.Enabled:=True;
  Button2.Enabled:=True;
  Label12.Width:=180;

{  Fjpg :=TJpegImage.Create ;
  F3:=TADOBlobStream.Create(TBlobField(ADOTable1.fieldbyname(PhotoRecord)),bmread);
  Try
    //F3.Clear;
    If TBlobField(ADOTable1.FieldByName(PhotoRecord)).AsString<>null then
    TBlobField(ADOTable1.FieldByName(PhotoRecord) ).SaveToStream(F3);
    //M1.LoadFromFile('D:\b11.jpg');

    F3.Position:=0;
    image2.Picture.Graphic := nil;
    If  F3.Size>100 then
    begin
      FJpg.LoadFromStream(F3);
      image2.Picture.Graphic :=FJpg;
    end
    else
    begin
      Panel6.Caption:='没有原始照片';
    end;
  Finally
    F3.Free;
    FJpg.Free;
  end; }
end;

procedure TStuPrintForm.btnClick(Sender: TObject);
begin
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
  cardtype:='S';  //学生卡
  Editnameform:=Teditnameform.Create(nil);
  editnameform.ShowModal;
  editnameform.Free;
  editnameform:=nil;
end;

end.

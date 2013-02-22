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
    ifHeighLevel:string;  //正高职判断
    ifRetire:string;      //离退休
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
  M1:TMemoryStream;  //内存流，
  Fjpg: TJpegImage;  //用Image 存放 Jpeg 的中间形式，
  SpeCode:String;  //专业代码，非院系代码，
  DeptCode:String; //部门代码
begin
  If edtNo.Text='' then
  begin
    ShowMessage('您输入的学工号为空！');
    edtno.SetFocus;
    exit;
  end;
  Image1.Picture.Assign(nil);
  StuEmpNumber:=Trim(edtNo.text);
  AdoQuery2.Close;             //如果其他地方有对ADOQuery1的引用，只有先关闭它，才能进行修改
  AdoQuery2.SQL.Clear;

  AdoQuery2.SQL.Add('SELECT * from '+PersonTableName+'  where '+
       PersonNo+'='+QuotedStr(StuEmpNumber)+' with ur');
  AdoQuery2.Open;
  if AdoQuery2.RecordCount=0 then
  begin
    ShowMessage('该学工号记录不存在！');          //需求漏洞，
    edtNo.Text:='';
    exit;
  end;

  {20051009日加入--------------------------------------------------------------}
  //如果是正高职，显示其职务
  if Copy(ADOQuery2.fieldbyname(reserve_2).AsString,Length(ADOQuery2.fieldbyname(reserve_2).AsString),1)='1' then
  begin
    qryType.Close;
    qryType.sql.Clear;
    qryType.sql.Add('select * from '+persontype+' where '+jobcode+'='+ #39+
                    ADOQuery2.fieldbyname(reserve_2).AsString+#39+' with ur');
    qryType.Open;
    if qryType.RecordCount=0 then
    begin
      ShowMessage('该工号的职务代码在系统中不存在，请和管理人员联系！');
      Exit;
    end;
    ifHeighLevel:='('+qryType.fieldbyname(jobname).asstring+')';
  end
  else
  begin
    ifHeighLevel:='';
  end;
  //如果为离退休人员，则在后面打印
  if ADOQuery2.FieldByName(status).AsString='22' then
    ifRetire:='(退休)'
  else if ADOQuery2.FieldByName(status).AsString='23' then
    ifRetire:='(离休)'
  else
    ifRetire:='';
  {20051009日加入结束----------------------------------------------------------}

  //DeptCode:= AdoQuery2.FieldByName(PersonKindName2).AsString;
  perName:=AdoQuery2.FieldByName(PersonName).AsString;
  LName.Caption:=Trim(AdoQuery2.FieldByName(PersonName).AsString)+ifHeighLevel+ifRetire;
  LNo.Caption:= AdoQuery2.FieldByName(PersonNo).AsString;  //工号
  SpeCode:=AdoQuery2.FieldByName(PersonKindNo1).AsString;

  //用ADOQuery1 执行照片表的查询，
  //如果其他地方有对ADOQuery1的引用，只有先关闭它，才能进行修改，
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
    ShowMessage('你要补打的内容为空，请先确定不为空再补打信息！');
    Exit;
  end;}
  if trim(LName.Caption)='' then
  begin
    showmessage('请先查询出要补打的人员信息！');
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

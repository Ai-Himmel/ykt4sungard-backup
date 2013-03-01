unit PhotoTrans;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB,IniFiles, StdCtrls, ComCtrls,jpeg, Grids, DBGrids;

type
  TForm1 = class(TForm)
    ADOConnection1: TADOConnection;
    qry1: TADOQuery;
    pb1: TProgressBar;
    mmoError: TMemo;
    btn1: TButton;
    qry2: TADOQuery;
    ds1: TDataSource;
    dbgrd1: TDBGrid;
    btn2: TButton;
    lbl1: TLabel;
    lbl2: TLabel;
    dtpBDate: TDateTimePicker;
    dtpEDate: TDateTimePicker;
    btn3: TButton;
    dlgSave1: TSaveDialog;
    lblcount: TLabel;
    btn4: TButton;
    procedure FormShow(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
    procedure btn3Click(Sender: TObject);
    procedure btn4Click(Sender: TObject);
  private
    { Private declarations }
    sconnstring:string;  //�������ݿ��ַ���
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses UtConfigs;

{$R *.DFM}

procedure TForm1.FormShow(Sender: TObject);
var
  inifile:TIniFile;
  sfilename:string;
begin
  sfilename:= ExtractFilePath(Paramstr(0)) + 'file.ini';
  inifile:= TIniFile.Create(sfilename);
  sconnstring:=inifile.ReadString('DataBase','conn',sconnstring);
  if ADOConnection1.Connected then
    ADOConnection1.Connected:=false;
  try
  ADOConnection1.ConnectionString:= sconnstring;
    ADOConnection1.Connected:=True;
  except
    ShowMessage('���ݿ�����ʧ�ܣ����飡');
  end;
  GetConfigs;
  lblcount.Caption := '';
end;

procedure TForm1.btn1Click(Sender: TObject);
var
  stuempno:string;
  F3:TMemoryStream;
  Fjpg :TJpegImage;

  tmpBmp:TBitmap;
  OldGraphics : TBitmap;
  expJpg:TJPEGImage;
  FMin:TmemoryStream;

begin
  if Application.MessageBox('��ȷ��Ҫת��С��Ƭ��','��Ƭת��',MB_YESNO+mb_iconquestion)=idno then
    Exit;
  pb1.Position := 0;
  pb1.Max := qry1.RecordCount;
  mmoError.Lines.Clear;
  qry1.first;
  while not qry1.Eof do
  begin
    stuempno := qry1.fieldbyname(PersonNo).AsString;
    qry2.Close;
    qry2.SQL.Clear;
    qry2.SQL.Add('select STUEMP_NO,photo,minphoto from ' + PhotoTableName + ' where ' + PersonNo + '='+#39+stuempno+#39);
    qry2.Open;
    qry2.Edit;
    try
      Fjpg := TJpegImage.Create;
      
      try
        //��ȡ��Ƭ
        F3 := TMemoryStream.Create;//(TBlobField(qry2.fieldbyname(PhotoRecord)), bmread);
        if TBlobField(qry2.FieldByName(PhotoRecord)).AsString <> null then
          TBlobField(qry2.FieldByName(PhotoRecord)).SaveToStream(F3);
          F3.Position := 0;
        FJpg.LoadFromStream(F3);
        //����С��Ƭ
        OldGraphics := TBitmap.Create;
        //�Ȱ�jpg��ʽ����Ƭת��Ϊbmp��ʽ

        OldGraphics.Assign(FJpg);
        //���¶�����Ƭ�Ĵ�С
        tmpBmp := TBitmap.Create;
        tmpBmp.Width := minWidth;
        tmpBmp.Height := minHeight;
        tmpBmp.Canvas.StretchDraw(Rect(0, 0, tmpBmp.Width, tmpBmp.Height),OldGraphics);

        //���°���Ƭת��Ϊjpg��ʽ
        expJpg := TJPEGImage.Create;

        expJpg.Assign(tmpBmp);
        FMin := TmemoryStream.Create;
        expJpg.SaveToStream(FMin);
        //------------------------
        //����С��Ƭ
        //FMin.SaveToFile('c:\FMin.jpg');
        TBlobField(qry2.FieldByName(minPhoto)).loadfromStream(FMin);
        qry2.Post;
      except
        mmoError.Lines.Add(stuempno+'---ת��ʧ��');
        qry1.Next;
        Continue;
      end;
    finally
      Fjpg.Destroy;
      F3.Destroy;
      tmpBmp.Destroy;
      OldGraphics.Destroy;
      expJpg.Destroy;
      FMin.Destroy;
    end;
    pb1.Position := pb1.Position+1;
    qry1.Next;
  end;
  ShowMessage('ת����ɣ�');
end;

procedure TForm1.btn2Click(Sender: TObject);
begin
  qry1.Close;
  qry1.SQL.Clear;
  //qry1.SQL.Add('select STUEMP_NO from ' + PhotoTableName + ' where ' + SaveFileName + '<>' + QuotedStr(''));
  qry1.SQL.Add('select STUEMP_NO,stuemp_name from ' + PhotoTableName +
    ' where ' + SaveFileName + '<>' + QuotedStr('') + ' and photo_date>=' + QuotedStr(FormatDateTime('yyyy-mm-dd', dtpBDate.Date))+
    ' and photo_date<=' + QuotedStr(FormatDateTime('yyyy-mm-dd', dtpEDate.Date)));
  qry1.Open;
  lblcount.Caption:='��ѯ��¼������'+inttostr(qry1.RecordCount);
end;

procedure TForm1.btn3Click(Sender: TObject);
begin
  if dlgSave1.Execute then
    mmoError.Lines.SaveToFile(dlgSave1.FileName+'.txt');
end;

procedure TForm1.btn4Click(Sender: TObject);
begin
  Application.Terminate;
end;

end.

unit uPhotoPatchCopy;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, GridsEh, DBGridEh, ComCtrls, Buttons, DB, ADODB;

type
  TfrmPhotoPatchCopy = class(TForm)
    dbgrdhDb: TDBGridEh;
    pb1: TProgressBar;
    grp2: TGroupBox;
    lbl1: TLabel;
    edtSheetName: TEdit;
    btnOpenExcel: TBitBtn;
    btnCloseExcel: TBitBtn;
    btnImport: TBitBtn;
    btnExit: TBitBtn;
    Label1: TLabel;
    lblFilePath: TLabel;
    dsOpen: TDataSource;
    conOpen: TADOConnection;
    qryOpen: TADOQuery;
    dlgOpen: TOpenDialog;
    btnQueryData: TBitBtn;
    grp1: TGroupBox;
    mmo1: TMemo;
    BitBtn1: TBitBtn;
    dlgSave: TSaveDialog;
    procedure btnExitClick(Sender: TObject);
    procedure btnOpenExcelClick(Sender: TObject);
    procedure btnCloseExcelClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnQueryDataClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
    procedure closeDataSet;
  public
    { Public declarations }
  end;

var
  frmPhotoPatchCopy: TfrmPhotoPatchCopy;

implementation

uses uCommon, UPhotoCopy;

{$R *.dfm}

procedure TfrmPhotoPatchCopy.btnExitClick(Sender: TObject);
begin
  qryOpen.Close;
  conOpen.Connected:=false;
  close;
end;

procedure TfrmPhotoPatchCopy.btnOpenExcelClick(Sender: TObject);
begin
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFilePath.Caption := dlgOpen.FileName;
end;

procedure TfrmPhotoPatchCopy.btnCloseExcelClick(Sender: TObject);
begin
  closeDataSet;
  btnImport.Enabled:=False;
  btnCloseExcel.Enabled := False;
end;

procedure TfrmPhotoPatchCopy.btnImportClick(Sender: TObject);
var
  i:Integer;
  oldStuempNo,newStuempNo:string;
  procedure pbStatus();
  begin
    pb1.Position := i;
    qryOpen.Next;
  end;
begin
  if qryOpen.RecordCount=0 then
  begin
    ShowMessage('û����Ҫ��������ݣ�');
    Exit;
  end;
  mmo1.Clear;
  qryOpen.First;
  pb1.Max := qryOpen.RecordCount;
  for i := 1 to qryOpen.RecordCount do
  begin
    oldStuempNo := Trim(qryOpen.fieldbyname('��ѧ����').AsString);
    newStuempNo := Trim(qryOpen.fieldbyname('��ѧ����').AsString);
    try
      frmPhotoCopy := TfrmPhotoCopy.Create(nil);
      frmPhotoCopy.oldStuempNo := oldStuempNo;
      frmPhotoCopy.newStuempNo := newStuempNo;
      frmPhotoCopy.custId := IntToStr(haveStuEmpNo(oldStuempNo));
      frmPhotoCopy.patchSign := 1;
      frmPhotoCopy.errMsg := '';
      frmPhotoCopy.ShowModal;
      if frmPhotoCopy.errMsg<>'' then
        mmo1.Lines.Add(frmPhotoCopy.errMsg);
    finally
      frmPhotoCopy.Free;
    end;
    pbStatus;
  end;
  ShowMessage('��������ͻ���Ϣ��ɣ�');
  closeDataSet;
  btnImport.Enabled:=False;
  btnCloseExcel.Enabled:=False;
end;

procedure TfrmPhotoPatchCopy.btnQueryDataClick(Sender: TObject);
var
  sqlstr:string;
  i:Integer;
begin
  try
    if conOpen.Connected=True then
      conOpen.Connected:=False;
    conOpen.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(lblFilePath.Caption)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conOpen.Connected :=True;
    qryOpen.Connection := conOpen;

    sqlstr:='select * from ['+Trim(edtSheetName.Text)+'$] where ��ѧ����<>'+#39+''+#39+' and ��ѧ����<>'+#39+''+#39;
    qryOpen.Close;
    qryOpen.SQL.Clear;
    qryOpen.SQL.Add(sqlstr);
    qryOpen.Open;
    for  i:= 0 to dbgrdhDb.Columns.Count-1 do
    begin
      dbgrdhDb.Columns[i].Width:=100;
      dbgrdhDb.Columns[i].Title.Alignment:=taCenter;
    end;
  except
    ShowMessage('�����ݱ�ʧ�ܣ�����򿪵�Excel�ļ��Ƿ���ȷ��');
    Exit;
  end;
  btnImport.Enabled:=True;
  btnCloseExcel.Enabled := True;
end;

procedure TfrmPhotoPatchCopy.closeDataSet;
begin
  if qryOpen.Active then
  begin
    qryOpen.Recordset.Close;
    qryOpen.Close;
  end;
  if conOpen.Connected then
    conOpen.Connected:=false;
end;

procedure TfrmPhotoPatchCopy.FormDestroy(Sender: TObject);
begin
  closeDataSet;
end;

procedure TfrmPhotoPatchCopy.BitBtn1Click(Sender: TObject);
begin
  if mmo1.Text='' then
  begin
    ShowMessage('û��Ҫ������ı���Ϣ��');
    Exit;
  end;
  dlgSave.Title := '��ѡ��Ҫ������ļ�·��';
  dlgSave.Filter := '�ı��ļ�|*.txt';
  if dlgSave.Execute then
    mmo1.Lines.SaveToFile(dlgSave.FileName+'.txt');
end;

end.

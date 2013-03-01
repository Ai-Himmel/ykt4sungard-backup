unit uCustImport;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, GridsEh, DBGridEh, ComCtrls, Buttons, DB, ADODB;

type
  TfrmCustImport = class(TForm)
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
  frmCustImport: TfrmCustImport;

implementation

uses uCommon;

{$R *.dfm}

procedure TfrmCustImport.btnExitClick(Sender: TObject);
begin
  qryOpen.Close;
  conOpen.Connected:=false;
  close;
end;

procedure TfrmCustImport.btnOpenExcelClick(Sender: TObject);
begin
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFilePath.Caption := dlgOpen.FileName;
end;

procedure TfrmCustImport.btnCloseExcelClick(Sender: TObject);
begin
  closeDataSet;
  btnImport.Enabled:=False;
  btnCloseExcel.Enabled := False;
end;

procedure TfrmCustImport.btnImportClick(Sender: TObject);
var
  i:Integer;
  sNo,sCardNo,sName,sDept:string;
  sType,sArea,sFeeType,sSpec:string;
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
  if qryOpen.RecordCount<2 then
  begin
    ShowMessage('Ҫ���������С��2������ֱ�ӵ��ͻ���Ϣ����������ӿͻ���Ϣ��');
    Exit;
  end;
  mmo1.Clear;
  qryOpen.First;
  pb1.Max := qryOpen.RecordCount;
  for i := 1 to qryOpen.RecordCount do
  begin
    sNo := qryOpen.fieldbyname('ѧ����').AsString;
    sCardNo := qryOpen.fieldbyname('���֤��').AsString;
    sName := qryOpen.fieldbyname('����').AsString;
    sType := qryOpen.fieldbyname('�ͻ����').AsString;
    sArea := qryOpen.fieldbyname('У��').AsString;
    sFeeType := qryOpen.fieldbyname('�շ����').AsString;
    sDept := qryOpen.fieldbyname('����').AsString;
    sSpec := qryOpen.fieldbyname('רҵ').AsString;
    if Trim(sNo)='####' then
    begin
      pb1.Position := pb1.Max;
      mmo1.Lines.Add('��Ա��Ϣ�������...');
      Break;
    end;
    if (Trim(sNo)='') and (Trim(sCardNo)='') then
    begin
      mmo1.Lines.Add('���� '+sName+' ��Ϣ��ȫ��������¼û�е��룬�����ѧ/���Ż����֤��');
      pbStatus;
    end;
    if (Trim(sType)='') or (Trim(sFeeType)='')or (Trim(sArea)='') then
    begin
      mmo1.Lines.Add('���� '+sName+' ��Ϣ��ȫ��������¼û�е��룬У�����ͻ�����շ���𶼲���Ϊ��');
      pbStatus;
      Continue;
    end;
    //�����ǰ�ȼ���Ƿ����ѧ���ź����֤��
    if haveStuEmpNo(sNo) then
    begin
      //д�Ѿ�������Ϣ
      mmo1.Lines.Add('ѧ/���� '+sNo+' ��Ϣ�Ѿ����ڣ�������Ϣû�е���');
      pbStatus;
      Continue;
    end;
    //����ͻ���Ϣ
    if addCustInfo(sNo,sName,stype,sArea,sCardNo,sDept,sSpec,sFeeType) then
    begin
      pbStatus;
      Continue;
    end
    else
    begin
      //дʧ����Ϣ
      mmo1.Lines.Add('ѧ/���� '+sNo+' ��Ϣ�Ѿ�����ʧ��');
      pbStatus;
      Continue;
    end;
  end;
  ShowMessage('��������ͻ���Ϣ��ɣ�');
  closeDataSet;
  btnImport.Enabled:=False;
  btnCloseExcel.Enabled:=False;
end;

procedure TfrmCustImport.btnQueryDataClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtSheetName.Text)+'$]';
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

procedure TfrmCustImport.closeDataSet;
begin
  if qryOpen.Active then
  begin
    qryOpen.Recordset.Close;
    qryOpen.Close;
  end;
  if conOpen.Connected then
    conOpen.Connected:=false;
end;

procedure TfrmCustImport.FormDestroy(Sender: TObject);
begin
  closeDataSet;
end;

procedure TfrmCustImport.BitBtn1Click(Sender: TObject);
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

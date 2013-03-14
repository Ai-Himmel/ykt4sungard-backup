unit UAEditStuempNo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons;

type
  TfaqhEditStuempNo = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnImport: TImageButton;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    btnOpen: TImageButton;
    dlgOpen: TOpenDialog;
    Label5: TLabel;
    edtTable: TWVEdit;
    lbl1: TLabel;
    lblFile: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    dlgSave1: TSaveDialog;
    RzDBGrid1: TRzDBGrid;
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
  private
    { Private declarations }
    procedure clsDataSet;//�رռ�¼��
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhEditStuempNo: TfaqhEditStuempNo;

implementation

uses KsFrameworks, KSClientConsts,UCMqhCustomerImp;
     
{$R *.DFM}

procedure TfaqhEditStuempNo.Init;
begin
  inherited;

end;

procedure TfaqhEditStuempNo.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhEditStuempNo.btnQueryClick(Sender: TObject);
var
  sqlstr:string;
  i:Integer;
begin
  //inherited;
  try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(lblFile.Caption)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where ԭѧ����<>'+#39+''+#39;
    sqlstr := sqlstr+ ' and ��ѧ����<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    try
      qrySource.Open;

    except
      Context.GetDialogSystem.ShowMessage('��ѯ��������excel�ļ����������Ƿ���ȷ��');
      Exit;
    end;

    for  i:= 0 to RzDBGrid1.Columns.Count-1 do
    begin
      RzDBGrid1.Columns[i].Width:=120;
      RzDBGrid1.Columns[i].Title.Alignment:=taCenter;
    end;

  except
    Context.GetDialogSystem.ShowMessage('�����ݱ�ʧ�ܣ����򿪵�Excel�ļ���������Ƿ���ȷ��');
  end;
  
end;

procedure TfaqhEditStuempNo.btnImportClick(Sender: TObject);
var
  sOldNo,sNewNo:string;
  errList:TStrings;
begin
  //inherited;
  if qrySource.RecordCount=0 then
  begin
    Context.GetDialogSystem.ShowMessage('û����Ҫ��������ݣ�');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ�����޸�ѧ������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  errList := nil;
  qrySource.First;
  try
    errList := TStringList.Create;
    while not qrySource.Eof do
    begin
      sOldNo := Trim(qrySource.fieldbyname('ԭѧ����').AsString);
      sNewNo := Trim(qrySource.fieldbyname('��ѧ����').AsString);

      WorkView.FieldByName('ԭѧ����').Data.SetString(sOldNo);
      WorkView.FieldByName('��ѧ����').Data.SetString(sNewNo);
      WorkView.FieldByName('������־').Data.SetString('U');
      WorkView.FieldByName('������־').Data.SetString('1');
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('ԭѧ/����:'+sOldNo+' �޸�ʧ�ܣ�ʧ��ԭ��--'+e.Message);
        end;
      end;
      qrySource.Next;
    end;
  finally
    if errList.Count>0 then
    begin
      if dlgSave1.Execute then
      begin
        errList.SaveToFile(dlgSave1.FileName+'.txt');
        Context.GetDialogSystem.ShowMessage('�����޸�ѧ/�������,ʧ����Ϣ������'+dlgSave1.FileName+'.txt��');
      end
    end
    else
      Context.GetDialogSystem.ShowMessage('�����޸�ѧ/�������!');
    errList.Destroy;
  end;

  RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
  clsDataSet;
end;

procedure TfaqhEditStuempNo.btnPrintClick(Sender: TObject);
begin
  //inherited;
  clsDataSet;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhImportCustomerInfo.closeDataSet�ر�Excel��¼��
  ����:      Administrator
  ����:      2005.08.01
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhEditStuempNo.clsDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhEditStuempNo.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('�����޸�ѧ����',TfaqhEditStuempNo);

end.
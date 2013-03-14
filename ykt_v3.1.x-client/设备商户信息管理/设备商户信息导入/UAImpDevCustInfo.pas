unit UAImpDevCustInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls;

type
  TfaqhImpDevCustInfo = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnImport: TBitBtn;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    btnOpen: TBitBtn;
    dlgOpen: TOpenDialog;
    Label5: TLabel;
    edtTable: TWVEdit;
    lbl1: TLabel;
    lblFile: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    RzDBGrid1: TRzDBGrid;
    pbstat: TProgressBar;
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
  private
    { Private declarations }
    //procedure iniGridSize;
    procedure closeDataSet;//�رռ�¼��
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImpDevCustInfo: TfaqhImpDevCustInfo;

implementation

uses KsFrameworks, KSClientConsts;
     
{$R *.DFM}

procedure TfaqhImpDevCustInfo.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhImpDevCustInfo.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImpDevCustInfo.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where �豸���<>'+#39+''+#39;
    sqlstr:=sqlstr+' and �̻����<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    try
      qrySource.Open;
    except
      ShowMessage('��ѯ��������excel�ļ����������Ƿ���ȷ��');
      Exit;
    end;
    for  i:= 0 to RzDBGrid1.Columns.Count-1 do
    begin
      RzDBGrid1.Columns[i].Width:=120;
      RzDBGrid1.Columns[i].Title.Alignment:=taCenter;
    end;
  except
    ShowMessage('�����ݱ�ʧ�ܣ����򿪵�Excel�ļ���������Ƿ���ȷ��');
  end;
end;

procedure TfaqhImpDevCustInfo.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  devId,busiId:Integer;
  stopDate,startDate,stopTime:string;
  pNo:string;
begin
  //inherited;
  if qrySource.Active=False then
  begin
    ShowMessage('���ȴ�ҪҪ�����Excel��');
    Exit;
  end;
  if qrySource.RecordCount=0 then
  begin
    ShowMessage('û����Ҫ��������ݣ�');
    Exit;
  end;
  if qrySource.RecordCount<2 then
  begin
    ShowMessage('Ҫ���������С��2������ֱ�ӵ��豸�̻����������ã�');
    Exit;
  end;
  xH:=1;//���
  qrySource.First;
  try
  devId := qrySource.fieldbyname('�豸���').AsInteger;
  busiId := qrySource.fieldbyname('�̻����').AsInteger;
  except
    ShowMessage('��������Ч���豸��ź��̻���ţ�');
    Exit;
  end;
  stopDate := qrySource.fieldbyname('ͣ������').AsString;
  startDate := qrySource.fieldbyname('��������').AsString;
  stopTime := qrySource.fieldbyname('ͣ��ʱ��').asstring;

  pNo := ' ';

  WorkView.FieldByName('���').Data.SetInteger(xh);
  WorkView.FieldByName('���κ�').Data.SetString(pNo);
  WorkView.FieldByName('������־').Data.SetString('A');
  WorkView.FieldByName('�豸���').Data.SetInteger(devId);
  WorkView.FieldByName('�̻����').Data.SetInteger(busiId);
  WorkView.FieldByName('ͣ������').Data.SetString(stopDate);
  WorkView.FieldByName('��������').Data.SetString(startDate);
  WorkView.FieldByName('ͣ��ʱ��').Data.SetString(stopTime);
  //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
  //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ
  WorkView.FieldByName('�Ƿ������').Data.SetString('0');
  
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString);
    RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
    Exit;
  end
  else
  begin
    RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
    pNo:=WorkView.fieldbyname('���κ�').Data.AsString;
    //ShowMessage(pNo);
  end;
  qrySource.Next;
  f:=1;
  pbstat.Max := qrySource.RecordCount;
  //while not qrySource.Eof do
  for i := 1 to qrySource.RecordCount-1 do
  begin

    //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
    //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ
    xh:=xh+1;
    f:=f+1;
    if f=qrySource.RecordCount then
    begin
      WorkView.FieldByName('�Ƿ������').Data.SetString('1');
    end
    else
    begin
      WorkView.FieldByName('�Ƿ������').Data.SetString('0');
    end;

    try
    devId := qrySource.fieldbyname('�豸���').AsInteger;
    busiId := qrySource.fieldbyname('�̻����').AsInteger;
    except
      ShowMessage('��������Ч���豸��ź��̻���ţ�');
      Exit;
    end;
    stopDate := qrySource.fieldbyname('ͣ������').AsString;
    startDate := qrySource.fieldbyname('��������').AsString;
    stopTime := qrySource.fieldbyname('ͣ��ʱ��').asstring;

    WorkView.FieldByName('���').Data.SetInteger(xh);
    WorkView.FieldByName('���κ�').Data.SetString(pNo);
    WorkView.FieldByName('������־').Data.SetString('A');
    WorkView.FieldByName('�豸���').Data.SetInteger(devId);
    WorkView.FieldByName('�̻����').Data.SetInteger(busiId);
    WorkView.FieldByName('ͣ������').Data.SetString(stopDate);
    WorkView.FieldByName('��������').Data.SetString(startDate);
    WorkView.FieldByName('ͣ��ʱ��').Data.SetString(stopTime);
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger<>0 then
    begin
      Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString);
      RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
      Exit;
    end
    else
    begin
      RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
    end;
    pbstat.Position := pbstat.Position+1;
    qrySource.Next;
  end;
  pbstat.Position := pbstat.Max;
  Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString);
  RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
  closeDataSet;
end;

procedure TfaqhImpDevCustInfo.btnPrintClick(Sender: TObject);
begin
  //inherited;
  closeDataSet;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhImportCustomerInfo.closeDataSet�ر�Excel��¼��
  ����:      Administrator
  ����:      2005.08.01
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhImpDevCustInfo.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhImpDevCustInfo.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('�豸�̻���Ϣ����',TfaqhImpDevCustInfo);

end.
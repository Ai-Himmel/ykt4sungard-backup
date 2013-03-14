unit UAImportPosSerial;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons;

type
  TfaqhPosSerialImport = class(TfaqhSimpleQueryTemp)
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
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
  private
    { Private declarations }
    procedure iniGridSize;
    procedure closeDataSet;//�رռ�¼��
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPosSerialImport: TfaqhPosSerialImport;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhPosSerialImport.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhPosSerialImport.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhPosSerialImport.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where ����<>'+#39+''+#39;
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
      RzDBGrid1.Columns[i].Width:=100;
      RzDBGrid1.Columns[i].Title.Alignment:=taCenter;
    end;
  except
    ShowMessage('�����ݱ�ʧ�ܣ����򿪵�Excel�ļ���������Ƿ���ȷ��');
  end;
end;

procedure TfaqhPosSerialImport.iniGridSize;
begin

end;

procedure TfaqhPosSerialImport.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  sDate,sTime,sDevId,pNo:string;
  iSerial,iBusiId,iTradeCode,iCardNo,iPckNo,iTrdNo,iSign:Integer;
  fBMoney,fEMoney,fMoney,fMMoney:Real;
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
    ShowMessage('Ҫ���������С��2������ֱ�ӵ�POS��ˮ�����������ˮ��Ϣ��');
    Exit;
  end;
  xH:=1;//���
  qrySource.First;
  sDate := Trim(qrySource.fieldbyname('��������').AsString);
  sTime := qrySource.fieldbyname('����ʱ��').AsString;
  sDevId := qrySource.fieldbyname('�豸������').AsString;

  iSerial := qrySource.fieldbyname('�豸��ˮ��').AsInteger;
  iBusiId := qrySource.fieldbyname('�̻���').AsInteger;
  iTradeCode := 0;//qrySource.fieldbyname('������').AsInteger;
  iCardNo := qrySource.fieldbyname('����').AsInteger;
  iPckNo := qrySource.fieldbyname('Ǯ����').AsInteger;
  iTrdNo := qrySource.fieldbyname('�����״���').AsInteger;
  iSign := qrySource.fieldbyname('���ױ��').AsInteger;

  fBMoney := qrySource.fieldbyname('������ǰ���').AsFloat;
  fEMoney := qrySource.fieldbyname('�����׺����').AsFloat;
  fMoney := qrySource.fieldbyname('������').AsFloat;
  fMMoney := qrySource.fieldbyname('����').AsFloat;

  pNo := ' ';

  WorkView.FieldByName('���').Data.SetInteger(xh);
  WorkView.FieldByName('���κ�').Data.SetString(pNo);
  WorkView.FieldByName('�Ƿ������').Data.SetString('0');
  WorkView.FieldByName('��������').Data.SetString(sDate);
  WorkView.FieldByName('����ʱ��').Data.SetString(sTime);
  WorkView.FieldByName('�豸������').Data.SetString(sDevId);
  WorkView.FieldByName('�豸��ˮ��').Data.SetInteger(iSerial);
  WorkView.FieldByName('�̻�����').Data.SetInteger(iBusiId);
  WorkView.FieldByName('������').Data.SetInteger(iTradeCode);
  WorkView.FieldByName('����').Data.SetInteger(iCardNo);
  WorkView.FieldByName('Ǯ����').Data.SetInteger(iPckNo);
  WorkView.FieldByName('�����״���').Data.SetInteger(iTrdNo);
  WorkView.FieldByName('���ױ��').Data.SetInteger(iSign);

  WorkView.FieldByName('������ǰ���').Data.SetFloat(fBMoney);
  WorkView.FieldByName('�����׺����').Data.SetFloat(fEMoney);
  WorkView.FieldByName('������').Data.SetFloat(fMoney);
  WorkView.FieldByName('�����').Data.SetFloat(fMMoney);
  //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
  //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ

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
  end;
  qrySource.Next;
  f:=1;
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
    
    sDate := Trim(qrySource.fieldbyname('��������').AsString);
    sTime := qrySource.fieldbyname('����ʱ��').AsString;
    sDevId := qrySource.fieldbyname('�豸������').AsString;

    iSerial := qrySource.fieldbyname('�豸��ˮ��').AsInteger;
    iBusiId := qrySource.fieldbyname('�̻���').AsInteger;
    iTradeCode := 0;//qrySource.fieldbyname('������').AsInteger;
    iCardNo := qrySource.fieldbyname('����').AsInteger;
    iPckNo := qrySource.fieldbyname('Ǯ����').AsInteger;
    iTrdNo := qrySource.fieldbyname('�����״���').AsInteger;
    iSign := qrySource.fieldbyname('���ױ��').AsInteger;

    fBMoney := qrySource.fieldbyname('������ǰ���').AsFloat;
    fEMoney := qrySource.fieldbyname('�����׺����').AsFloat;
    fMoney := qrySource.fieldbyname('������').AsFloat;
    fMMoney := qrySource.fieldbyname('����').AsFloat;

    WorkView.FieldByName('���').Data.SetInteger(xh);
    WorkView.FieldByName('���κ�').Data.SetString(pNo);
    //WorkView.FieldByName('�Ƿ������').Data.SetString('0');
    WorkView.FieldByName('��������').Data.SetString(sDate);
    WorkView.FieldByName('����ʱ��').Data.SetString(sTime);
    WorkView.FieldByName('�豸������').Data.SetString(sDevId);
    WorkView.FieldByName('�豸��ˮ��').Data.SetInteger(iSerial);
    WorkView.FieldByName('�̻�����').Data.SetInteger(iBusiId);
    WorkView.FieldByName('������').Data.SetInteger(iTradeCode);
    WorkView.FieldByName('����').Data.SetInteger(iCardNo);
    WorkView.FieldByName('Ǯ����').Data.SetInteger(iPckNo);
    WorkView.FieldByName('�����״���').Data.SetInteger(iTrdNo);
    WorkView.FieldByName('���ױ��').Data.SetInteger(iSign);

    WorkView.FieldByName('������ǰ���').Data.SetFloat(fBMoney);
    WorkView.FieldByName('�����׺����').Data.SetFloat(fEMoney);
    WorkView.FieldByName('������').Data.SetFloat(fMoney);
    WorkView.FieldByName('�����').Data.SetFloat(fMMoney);
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
    qrySource.Next;
  end;

  Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString);
  RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
  closeDataSet;
end;

procedure TfaqhPosSerialImport.btnPrintClick(Sender: TObject);
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
procedure TfaqhPosSerialImport.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhPosSerialImport.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('POS��ˮ����',TfaqhPosSerialImport);

end.
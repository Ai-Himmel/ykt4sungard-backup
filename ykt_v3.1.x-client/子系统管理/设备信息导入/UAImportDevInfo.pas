unit UAImportDevInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls;

type
  TfaqhImportDevInfo = class(TfaqhSimpleQueryTemp)
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
    procedure closeDataSet;//�رռ�¼��
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImportDevInfo: TfaqhImportDevInfo;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhImportDevInfo.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhImportDevInfo.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImportDevInfo.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where �豸����<>'+#39+''+#39;
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
    pbstat.Position := 0;
  except
    ShowMessage('�����ݱ�ʧ�ܣ����򿪵�Excel�ļ���������Ƿ���ȷ��');
  end;
end;

procedure TfaqhImportDevInfo.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  devName:string;
  devType:Integer;
  devMaType:string;
  devUse:Integer;
  devphyId:string;
  area:string;
  parentDev:Integer;
  subSystem:Integer;
  subFee:Integer;
  cardCon:string;
  portNo:Integer;
  devMaNo:Integer;
  IpAddr:string;
  linkType:Integer;
  portNum:Integer;
  linkNo:Integer;
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
    ShowMessage('Ҫ���������С��2������ֱ�ӵ��豸��Ϣ����������豸��');
    Exit;
  end;
  xH:=1;//���
  qrySource.First;
  devName := Trim(qrySource.fieldbyname('�豸����').AsString);
  devType := qrySource.fieldbyname('�豸����').AsInteger;
  devMaType := qrySource.fieldbyname('�豸����').AsString;
  devUse := qrySource.fieldbyname('�豸��;').AsInteger;
  devphyId := qrySource.fieldbyname('�豸������').AsString;
  area := qrySource.fieldbyname('��������').AsString;

  parentDev := qrySource.fieldbyname('�ϼ��豸').AsInteger;
  subSystem := qrySource.fieldbyname('������ϵͳ').AsInteger;
  subFee := 0;//qrySource.fieldbyname('֧�ֿ�Ŀ�շ�').AsInteger;
  cardCon := Trim(qrySource.fieldbyname('��Ƭ�ṹ').AsString);
  portNo := qrySource.fieldbyname('�������˿ں�').AsInteger;
  devMaNo := qrySource.fieldbyname('�豸����').AsInteger;
  IpAddr := qrySource.fieldbyname('IP��ַ').AsString;
  linkType := qrySource.fieldbyname('ͨѶ���').AsInteger;
  portNum := qrySource.fieldbyname('�������˿���').AsInteger;
  linkNo := qrySource.fieldbyname('ͨѶ�˿�').AsInteger;
  pNo := ' ';

  WorkView.FieldByName('���').Data.SetInteger(xh);
  WorkView.FieldByName('���κ�').Data.SetString(pNo);
  WorkView.FieldByName('�Ƿ������').Data.SetString('0');
  
  WorkView.FieldByName('�豸����').Data.SetString(devName);
  WorkView.FieldByName('�豸����').Data.SetInteger(devType);
  WorkView.FieldByName('�豸����').Data.SetString(devMaType);
  WorkView.FieldByName('�豸��;').Data.SetInteger(devUse);
  WorkView.FieldByName('�豸������').Data.SetString(devphyId);
  WorkView.FieldByName('��������').Data.SetString(area);
  WorkView.FieldByName('�ϼ��豸').Data.SetInteger(parentDev);
  WorkView.FieldByName('������ϵͳ').Data.SetInteger(subSystem);
  WorkView.FieldByName('֧�ֿ�Ŀ�շ�').Data.SetInteger(subFee);
  WorkView.FieldByName('��Ƭ�ṹ').Data.SetString(cardCon);
  WorkView.FieldByName('�������˿ں�').Data.SetInteger(portNo);
  WorkView.FieldByName('�豸����').Data.SetInteger(devMaNo);
  WorkView.FieldByName('IP��ַ').Data.SetString(IpAddr);
  WorkView.FieldByName('ͨѶ���').Data.SetInteger(linkType);
  WorkView.FieldByName('�������˿���').Data.SetInteger(portNum);
  WorkView.FieldByName('ͨѶ�˿�').Data.SetInteger(linkNo);
  WorkView.FieldByName('������־').Data.SetString('A');
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
    
    devName := Trim(qrySource.fieldbyname('�豸����').AsString);
    devType := qrySource.fieldbyname('�豸����').AsInteger;
    devMaType := qrySource.fieldbyname('�豸����').AsString;
    devUse := qrySource.fieldbyname('�豸��;').AsInteger;
    devphyId := qrySource.fieldbyname('�豸������').AsString;
    area := qrySource.fieldbyname('��������').AsString;

    parentDev := qrySource.fieldbyname('�ϼ��豸').AsInteger;
    subSystem := qrySource.fieldbyname('������ϵͳ').AsInteger;
    subFee := 0;//qrySource.fieldbyname('֧�ֿ�Ŀ�շ�').AsInteger;
    cardCon := Trim(qrySource.fieldbyname('��Ƭ�ṹ').AsString);
    portNo := qrySource.fieldbyname('�������˿ں�').AsInteger;
    devMaNo := qrySource.fieldbyname('�豸����').AsInteger;
    IpAddr := qrySource.fieldbyname('IP��ַ').AsString;
    linkType := qrySource.fieldbyname('ͨѶ���').AsInteger;
    portNum := qrySource.fieldbyname('�������˿���').AsInteger;
    linkNo := qrySource.fieldbyname('ͨѶ�˿�').AsInteger;
    //pNo := ' ';

    WorkView.FieldByName('���').Data.SetInteger(xh);
    WorkView.FieldByName('���κ�').Data.SetString(pNo);
    //WorkView.FieldByName('�Ƿ������').Data.SetString('0');
  
    WorkView.FieldByName('�豸����').Data.SetString(devName);
    WorkView.FieldByName('�豸����').Data.SetInteger(devType);
    WorkView.FieldByName('�豸����').Data.SetString(devMaType);
    WorkView.FieldByName('�豸��;').Data.SetInteger(devUse);
    WorkView.FieldByName('�豸������').Data.SetString(devphyId);
    WorkView.FieldByName('��������').Data.SetString(area);
    WorkView.FieldByName('�ϼ��豸').Data.SetInteger(parentDev);
    WorkView.FieldByName('������ϵͳ').Data.SetInteger(subSystem);
    WorkView.FieldByName('֧�ֿ�Ŀ�շ�').Data.SetInteger(subFee);
    WorkView.FieldByName('��Ƭ�ṹ').Data.SetString(cardCon);
    WorkView.FieldByName('�������˿ں�').Data.SetInteger(portNo);
    WorkView.FieldByName('�豸����').Data.SetInteger(devMaNo);
    WorkView.FieldByName('IP��ַ').Data.SetString(IpAddr);
    WorkView.FieldByName('ͨѶ���').Data.SetInteger(linkType);
    WorkView.FieldByName('�������˿���').Data.SetInteger(portNum);
    WorkView.FieldByName('ͨѶ�˿�').Data.SetInteger(linkNo);
    WorkView.FieldByName('������־').Data.SetString('A');
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
    pbstat.Position := pbstat.Position + 1;
    qrySource.Next;
  end;
  pbstat.Position := pbstat.Max;
  Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString);
  RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
  closeDataSet;
end;

procedure TfaqhImportDevInfo.btnPrintClick(Sender: TObject);
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
procedure TfaqhImportDevInfo.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhImportDevInfo.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('�豸��Ϣ����',TfaqhImportDevInfo);

end.
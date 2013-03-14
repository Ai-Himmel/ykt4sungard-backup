unit UAImportBankCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls;

type
  TfaqhImportBankCard = class(TfaqhSimpleQueryTemp)
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
    dlgSave1: TSaveDialog;
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
  faqhImportBankCard: TfaqhImportBankCard;

implementation

uses KsFrameworks, KSClientConsts,UCMqhCustomerImp;
     
{$R *.DFM}

procedure TfaqhImportBankCard.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhImportBankCard.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImportBankCard.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where ���п���<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    //ShowMessage(sqlstr);
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

procedure TfaqhImportBankCard.iniGridSize;
begin

end;

procedure TfaqhImportBankCard.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  stuempNo:string;
  custId:string;
  bankCode:string;
  bankCardNo:string;
  area:string;
  custName:string;
  pNo,ssign:string;
  errList:TStringList;
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
    ShowMessage('Ҫ���������С��2������ֱ�ӵ��ͻ���Ϣ����������ӿͻ���Ϣ��');
    Exit;
  end;
  errList := nil;
  try
    errList := TStringList.Create;
    xH:=1;//���
    qrySource.First;
    stuempNo := Trim(qrySource.fieldbyname('ѧ����').AsString);
    custId := qrySource.fieldbyname('�ͻ���').AsString;
    bankCode := qrySource.fieldbyname('���д���').AsString;
    bankCardNo := Trim(qrySource.fieldbyname('���п���').AsString);
    area := Trim(qrySource.fieldbyname('У��').AsString);
    custName := Trim(qrySource.fieldbyname('����').AsString);

    WorkView.FieldByName('���').Data.SetInteger(xh);
    WorkView.FieldByName('���κ�').Data.SetString(pNo);
    WorkView.FieldByName('�Ƿ������').Data.SetString('0');
    WorkView.FieldByName('������־').Data.SetString('I');
    WorkView.FieldByName('ѧ����').Data.SetString(stuempNo);
    WorkView.FieldByName('У��').Data.SetString(area);
    WorkView.FieldByName('����').Data.SetString(custName);

    if custId = '' then
      WorkView.FieldByName('�ͻ���').Data.SetInteger(0)
    else
      WorkView.FieldByName('�ͻ���').Data.SetInteger(StrToInt(custId));
    WorkView.FieldByName('���д���').Data.SetString(bankCode);
    WorkView.FieldByName('���п���').Data.SetString(bankCardNo);
    //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
    //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ

    try
      MainRequest.SendCommand;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('����ʧ�ܣ��뱣֤��һ����¼�ȵ���ɹ�-'+e.Message);
        Exit;
      end;
    end;
    if WorkView.FieldByName('������').Data.AsInteger<>0 then
    begin
      //errList.Add('ѧ����['+stuempNo+']����ʧ�ܣ�ԭ��--'+WorkView.fieldbyname('������Ϣ').Data.AsString);
      Context.GetDialogSystem.ShowMessage('����ʧ�ܣ��뱣֤��һ����¼�ȵ���ɹ���');
      Exit;
    end
    else
    begin
      //RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
      pNo:=WorkView.fieldbyname('���κ�').Data.AsString;
    end;
    qrySource.Next;
    f:=1;
    //while not qrySource.Eof do
    pbstat.Max := qrySource.RecordCount;
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

      stuempNo := Trim(qrySource.fieldbyname('ѧ����').AsString);
      custId := qrySource.fieldbyname('�ͻ���').AsString;
      bankCode := qrySource.fieldbyname('���д���').AsString;
      bankCardNo := Trim(qrySource.fieldbyname('���п���').AsString);
      area := Trim(qrySource.fieldbyname('У��').AsString);
      custName := Trim(qrySource.fieldbyname('����').AsString);

      WorkView.FieldByName('���').Data.SetInteger(xh);
      WorkView.FieldByName('���κ�').Data.SetString(pNo);
      //WorkView.FieldByName('�Ƿ������').Data.SetString('0');
      WorkView.FieldByName('������־').Data.SetString('I');
      WorkView.FieldByName('ѧ����').Data.SetString(stuempNo);
      WorkView.FieldByName('У��').Data.SetString(area);
      WorkView.FieldByName('����').Data.SetString(custName);
      if custId = '' then
        WorkView.FieldByName('�ͻ���').Data.SetInteger(0)
      else
        WorkView.FieldByName('�ͻ���').Data.SetInteger(StrToInt(custId));
      WorkView.FieldByName('���д���').Data.SetString(bankCode);
      WorkView.FieldByName('���п���').Data.SetString(bankCardNo);
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('ѧ����['+stuempNo+']����ʧ�ܣ�ԭ��--'+e.Message);
          qrySource.Next;
          Continue;
        end;
      end;
      if WorkView.FieldByName('������').Data.AsString<>'0' then
      begin
        errList.Add('ѧ����['+stuempNo+']����ʧ�ܣ�ԭ��--'+WorkView.fieldbyname('������Ϣ').Data.AsString);
        qrySource.Next;
        Continue;
      end;
      pbstat.Position := pbstat.Position+1;
      Sleep(500);
      qrySource.Next;
    end;
  finally
    if errList.Count>0 then
      if dlgSave1.Execute then
      begin
        errList.SaveToFile(dlgSave1.FileName+'.txt');
      end;      
    errList.Destroy;
  end;
  //pbstat.Position := pbstat.Max;
  Context.GetDialogSystem.ShowMessage('������ɣ�');
  //RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
  closeDataSet;
end;

procedure TfaqhImportBankCard.btnPrintClick(Sender: TObject);
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
procedure TfaqhImportBankCard.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhImportBankCard.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('���п��󶨵���',TfaqhImportBankCard);

end.
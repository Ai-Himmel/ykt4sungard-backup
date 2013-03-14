unit UAdownSublidyList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzStatus, ADODB, Buttons;

type
  TfaqhdownSublidyList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    lbl1: TLabel;
    lblFile: TLabel;
    Label3: TLabel;
    edtTable: TWVEdit;
    btnOpen: TBitBtn;
    RzStatusPane1: TRzStatusPane;
    btnImport: TBitBtn;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    dlgOpen: TOpenDialog;
    grid1: TRzDBGrid;
    dlgSave1: TSaveDialog;
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
  private

    { Private declarations }
    procedure closeDateSet;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhdownSublidyList: TfaqhdownSublidyList;

implementation

uses KsFrameworks, 
     KSClientConsts,UCMqhSubsidyImp;
     
{$R *.DFM}

procedure TfaqhdownSublidyList.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhdownSublidyList.btnOpenClick(Sender: TObject);
begin
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhdownSublidyList.btnQueryClick(Sender: TObject);
var
  sqlstr:string;
  i:Integer;
begin
  //try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(lblFile.Caption)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where ѧ����<>'+#39+''+#39+' or �ͻ���<>'+#39+''+#39;
    {
    if Trim(edtNo.Text)<>'' then
      sqlstr:=sqlstr+' and ѧ����='+#39+Trim(edtNo.Text)+#39;
    if Trim(edtMoney.Text)<>'' then
      sqlstr:=sqlstr+' and ������� ='+Trim(edtMoney.Text);
    if Trim(edtDate.Text)<>'' then
      sqlstr:=sqlstr+' and ��ֹ���� ='+Trim(edtDate.Text);
      }
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    qrySource.Open;
    for  i:= 0 to Grid1.Columns.Count-1 do
    begin
      Grid1.Columns[i].Width:=120;
      Grid1.Columns[i].Title.Alignment:=taCenter;
    end;
  //except
    //ShowMessage('�����ݱ�ʧ�ܣ�����򿪵�Excel�ļ��Ƿ���ȷ��');
  //end;
end;

procedure TfaqhdownSublidyList.closeDateSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;

end;

procedure TfaqhdownSublidyList.btnPrintClick(Sender: TObject);
begin
  //inherited;
  closeDateSet;
end;

procedure TfaqhdownSublidyList.btnImportClick(Sender: TObject);
var
  xH,f,i,custno:integer;
  scust_auth,sdate2,pNo,operCode:string;
  damt0:Real;
  returnInfo : String;
  errList:TStringList;
begin
  //inherited;
  operCode := Context.ParamData(svOperatorNoName).AsString;
  if qrySource.RecordCount=0 then
  begin
    Context.GetDialogSystem.ShowMessage('û����Ҫ��������ݣ�');
    Exit;
  end;
  if qrySource.RecordCount=1 then
  begin
    xH:=1;//���
    qrySource.First;
    if Trim(qrySource.fieldbyname('�ͻ���').asstring)='' then
      custno := 0
    else
      custno :=qrySource.fieldbyname('�ͻ���').AsInteger;
    scust_auth := qrySource.fieldbyname('ѧ����').AsString;
    //sdate0 := qrySource.fieldbyname('�������κ�').asstring;
    try
      damt0 := qrySource.fieldbyname('�������').AsFloat;
    except
      damt0 := 0;
    end;
    sdate2 := qrySource.fieldbyname('��ֹ����').AsString;
    pNo := ' ';

    WorkView.FieldByName('˳���').Data.SetInteger(xh);
    WorkView.FieldByName('�ͻ���').Data.SetInteger(custno);
    WorkView.FieldByName('ѧ����').Data.SetString(scust_auth);
    WorkView.FieldByName('�������κ�').Data.SetString(pNo);
    WorkView.FieldByName('�������κ�').Data.SetString('');
    WorkView.FieldByName('�������').Data.SetFloat(damt0);
    WorkView.FieldByName('��ֹ����').Data.SetString(sdate2);
    WorkView.FieldByName('����Ա').Data.SetString(operCode);
    //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
    //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ
    WorkView.FieldByName('�����־').Data.SetString('1');

    MainRequest.SendCommand;
    returnInfo:=WorkView.fieldbyname('������Ϣ').Data.AsString;
    Context.GetDialogSystem.ShowMessage(returnInfo);
    RzStatusPane1.Caption:=returnInfo;
    Exit;
  end;
  xH:=1;//���
  qrySource.First;
    if Trim(qrySource.fieldbyname('�ͻ���').asstring)='' then
      custno := 0
    else
      custno :=qrySource.fieldbyname('�ͻ���').AsInteger;
  scust_auth := qrySource.fieldbyname('ѧ����').AsString;
  //sdate0 := qrySource.fieldbyname('�������κ�').AsString;
  try
    damt0 := qrySource.fieldbyname('�������').AsFloat;
  except
    damt0 := 0;
  end;
  sdate2 := qrySource.fieldbyname('��ֹ����').AsString;
  pNo := ' ';

  WorkView.FieldByName('˳���').Data.SetInteger(xh);
  WorkView.FieldByName('�ͻ���').Data.SetInteger(custno);
  WorkView.FieldByName('ѧ����').Data.SetString(scust_auth);
  WorkView.FieldByName('�������κ�').Data.SetString(pNo);
  WorkView.FieldByName('�������κ�').Data.SetString('');
  WorkView.FieldByName('�������').Data.SetFloat(damt0);
  WorkView.FieldByName('��ֹ����').Data.SetString(sdate2);
  WorkView.FieldByName('����Ա').Data.SetString(operCode);
  //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
  //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ
  WorkView.FieldByName('�����־').Data.SetString('0');

  MainRequest.SendCommand;
  returnInfo := WorkView.fieldbyname('������Ϣ').Data.AsString;
  if WorkView.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(returnInfo);
    RzStatusPane1.Caption:=returnInfo;
    Exit;
  end
  else
  begin
    RzStatusPane1.Caption:=returnInfo;
    pNo:=WorkView.fieldbyname('�������κ�').Data.AsString;
  end;
  qrySource.Next;
  f:=1;
  errList := nil;
  try
    errList := TStringList.Create;
    //while not qrySource.Eof do
    for i := 1 to qrySource.RecordCount-1 do
    begin

      //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
      //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ
      xh:=xh+1;
      f:=f+1;
      if f=qrySource.RecordCount then
      begin
        WorkView.FieldByName('�����־').Data.SetString('1');
      end
      else
      begin
        WorkView.FieldByName('�����־').Data.SetString('0');
      end;

      if Trim(qrySource.fieldbyname('�ͻ���').asstring)='' then
        custno := 0
      else
        custno :=qrySource.fieldbyname('�ͻ���').AsInteger;
      scust_auth := qrySource.fieldbyname('ѧ����').AsString;
      //sdate0 := qrySource.fieldbyname('�������κ�').asstring;
      try
      damt0 := qrySource.fieldbyname('�������').AsFloat;
      except
        damt0:=0;
      end;
      sdate2 := qrySource.fieldbyname('��ֹ����').AsString;

      WorkView.FieldByName('˳���').Data.SetInteger(xh);
      WorkView.FieldByName('�ͻ���').Data.SetInteger(custno);
      WorkView.FieldByName('ѧ����').Data.SetString(scust_auth);
      WorkView.FieldByName('�������κ�').Data.SetString(pNo);
      WorkView.FieldByName('�������κ�').Data.SetString('');
      WorkView.FieldByName('�������').Data.SetFloat(damt0);
      WorkView.FieldByName('��ֹ����').Data.SetString(sdate2);
      WorkView.FieldByName('����Ա').Data.SetString(operCode);
      {
      MainRequest.SendCommand;
      returnInfo:= WorkView.fieldbyname('������Ϣ').Data.AsString;
      if WorkView.FieldByName('������').Data.AsInteger<>0 then
      begin
        RzStatusPane1.Caption:=returnInfo;

        Context.GetDialogSystem.ShowMessage(returnInfo);
        RzStatusPane1.Caption:=returnInfo;
        Exit;
      end;
      }
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('ѧ����['+scust_auth+']����ʧ�ܣ�ԭ��--'+e.Message);
          qrySource.Next;
          Continue;
        end;
      end;
      if WorkView.FieldByName('������').Data.AsString<>'0' then
      begin
        errList.Add('ѧ����['+scust_auth+']����ʧ�ܣ�ԭ��--'+WorkView.fieldbyname('������Ϣ').Data.AsString);
        qrySource.Next;
        Continue;
      end;

      RzStatusPane1.Caption:=returnInfo;
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

  Context.GetDialogSystem.ShowMessage(returnInfo);
  RzStatusPane1.Caption:=returnInfo;
  //closeDataSet;
end;

initialization
  TUIStdClassFactory.Create('������Ϣ����',TfaqhdownSublidyList);

end.
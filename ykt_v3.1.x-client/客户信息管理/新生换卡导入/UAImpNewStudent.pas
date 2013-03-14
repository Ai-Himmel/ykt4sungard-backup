unit UAImpNewStudent;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls;

type
  TfaqhImpNewStudent = class(TfaqhSimpleQueryTemp)
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
    FPath:string;
    procedure iniGridSize;
    procedure closeDataSet;//�رռ�¼��
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImpNewStudent: TfaqhImpNewStudent;

implementation

uses KsFrameworks, 
     KSClientConsts,UCMqhCustomerImp;
     
{$R *.DFM}

procedure TfaqhImpNewStudent.Init;
begin
  inherited;
  WorkView.Reset;
  FPath := ExtractFileDir(application.ExeName) + '\' + 'PatchLog';
end;

procedure TfaqhImpNewStudent.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImpNewStudent.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where ѧ����<>'+#39+''+#39+' and �¿���ʾ����<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    //ShowMessage(sqlstr);
    try
      qrySource.Open;
    except
      on e:Exception do
      begin
        ShowMessage('��ѯ��������excel�ļ����������Ƿ���ȷ--'+e.Message);
        //closeDataSet;
        Exit;
      end;
    end;
    for  i:= 0 to RzDBGrid1.Columns.Count-1 do
    begin
      RzDBGrid1.Columns[i].Width:=120;
      RzDBGrid1.Columns[i].Title.Alignment:=taCenter;
    end;
    pbstat.Position := 0;
  except
    on e:Exception do
    begin
      ShowMessage('�����ݱ�ʧ�ܣ����򿪵�Excel�ļ���������Ƿ���ȷ--'+e.Message);
      //closeDataSet;
    end;
  end;
end;

procedure TfaqhImpNewStudent.iniGridSize;
begin

end;

procedure TfaqhImpNewStudent.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  stuempNo:string;
  showCardNo:string;
  dealDate:string;
  pNo:string;
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
  xH:=1;//���
  qrySource.First;
  stuempNo := Trim(qrySource.fieldbyname('ѧ����').AsString);
  showCardNo := Trim(qrySource.fieldbyname('�¿���ʾ����').AsString);
  dealDate := Trim(qrySource.fieldbyname('����Ч��').AsString);
  WorkView.FieldByName('���').Data.SetInteger(xh);
  WorkView.FieldByName('���κ�').Data.SetString(pNo);
  WorkView.FieldByName('�Ƿ������').Data.SetString('0');
  WorkView.FieldByName('������־').Data.SetString('A');
  WorkView.FieldByName('ѧ����').Data.SetString(stuempNo);
  WorkView.FieldByName('�¿���ʾ����').Data.SetString(showCardNo);
  WorkView.FieldByName('����Ч��').Data.SetString(dealDate);
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
    //RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
    pNo:=WorkView.fieldbyname('���κ�').Data.AsString;
  end;
  
  //pNo:= '';
  qrySource.Next;
  f:=1;
  //while not qrySource.Eof do
  errList := nil;
  try
    errList := TStringList.Create;
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
      showCardNo := qrySource.fieldbyname('�¿���ʾ����').AsString;
      dealDate := Trim(qrySource.fieldbyname('����Ч��').AsString);
      WorkView.FieldByName('���').Data.SetInteger(xh);
      WorkView.FieldByName('���κ�').Data.SetString(pNo);
      WorkView.FieldByName('ѧ����').Data.SetString(stuempNo);
      WorkView.FieldByName('������־').Data.SetString('A');
      WorkView.FieldByName('�¿���ʾ����').Data.SetString(showCardNo);
      WorkView.FieldByName('����Ч��').Data.SetString(dealDate);
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('ѧ����['+stuempNO+'],�¿���ʾ����['+showcardno+']����ʧ�ܣ�ʧ��ԭ��--'+e.Message);
          pbstat.Position := pbstat.Position+1;
          qrySource.Next;
          Continue;
        end;
      end;
      {       412702198112238124
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
      }
      pbstat.Position := pbstat.Position+1;
      qrySource.Next;
    end;
    pbstat.Position := pbstat.Max;
    if ErrList.Count>0 then
    begin
      ErrList.SaveToFile(FPath+'\����������������ʧ�ܼ�¼'+FormatDateTime('yyyymmddhhmmss',Now)+'.txt');
      Context.GetDialogSystem.ShowMessage('������������������ɣ�ʧ����Ϣ����\bin\PATCHLOG��');
    end
    else
      //Context.GetDialogSystem.ShowMessage('�������������������!');
      Context.GetDialogSystem.ShowMessage('������ɣ�'+WorkView.fieldbyname('������Ϣ').Data.AsString);
    RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
  finally
    errList.Destroy;
    closeDataSet;
  end;
end;

procedure TfaqhImpNewStudent.btnPrintClick(Sender: TObject);
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
procedure TfaqhImpNewStudent.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhImpNewStudent.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('����������������',TfaqhImpNewStudent);

end.
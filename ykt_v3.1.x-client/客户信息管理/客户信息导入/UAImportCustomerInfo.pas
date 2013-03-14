unit UAImportCustomerInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls,Contnrs,
  UIncrementComboBox;

const
  MAN = '��';
  WOMEN = 'Ů';

type
  TCustInfo = class
  private
    FFCustNo:string;          //ѧ����
    FFCustType:Integer;       //�ͻ����
    FFFeeType:Integer;        //�շ����
    FFCustName:string;        //�ͻ�����
    FFArea:string;            //У��
    FFDept:string;            //����
    FFSpec:string;            //רҵ
    FFCertType:string;        //֤������
    FFCertNo:string;          //֤������
    FFSex:string;             //�Ա�
    FFNation:string;          //����
    FFPeople:string;          //����
    FFEmail:string;           //��������
    FFTel:string;             //�绰
    FFPhone:string;           //�ֻ�
    FFAddr:string;            //��ַ
    FFPostCode:string;        //�ʱ�
    FFRegDate:string;         //��У����
    FFDestoryDate:string;     //��У����
    FFClassNo:string;         //�༶
  protected

  public
    property CustNo:string read FFCustNo write FFCustNo;
    property CustType:Integer read FFCustType write FFCustType;
    property FeeType:Integer read FFFeeType write FFFeeType;
    property CustName:string read FFCustName write FFCustName;
    property Area:string read FFArea write FFArea;
    property Dept:string read FFDept write FFDept;
    property Spec:string read FFSpec write FFSpec;
    property CertType:string read FFCertType write FFCertType;
    property CertNo:string read FFCertNo write FFCertNo;
    property Sex:string read FFSex write FFSex;
    property Nation:string read FFNation write FFNation;
    property People:string read FFPeople write FFPeople;
    property Email:string read FFEmail write FFEmail;
    property Tel:string read FFTel write FFTel;
    property Phone:string read FFPhone write FFPhone;
    property Addr:string read FFAddr write FFAddr;
    property PostCode:string read FFPostCode write FFPostCode;
    property RegDate:string read FFRegDate write FFRegDate;
    property DestoryDate:string read FFDestoryDate write FFDestoryDate;
    property ClassNo:string read FFClassNo write FFClassNo;
  end;
  
type
  TCustInfoList = class(TObjectList)
  private
    function GetItems(index:Integer): TCustInfo;
  public
    property Items[Index:Integer]:TCustInfo read GetItems;default;
  end;
  
type
  TfaqhImportCustomerInfo = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    edtNo: TWVEdit;
    edtCardNo: TWVEdit;
    edtName: TWVEdit;
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
    pbStatues: TProgressBar;
    btnCheck: TBitBtn;
    cbbFeeType: TWVComboBox;
    cbbCustType: TWVComboBox;
    cbbArea: TWVComboBox;
    cbbDept: TWVComboBox;
    cbbSpec: TWVComboBox;
    cbbNation: TWVComboBox;
    cbbPeople: TWVComboBox;
    cbbCertType: TWVComboBox;
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
  private
    { Private declarations }
    FCustType:string;        //�ͻ����-34
    FFeeType:string;         //�շ����-43
    FArea:string;            //У��-27
    FDept:string;            //����-22
    FErrDept:string;         //�����ڵĲ���
    FSpec:string;            //רҵ-23
    FErrSpec:string;         //�����ڵ�רҵ
    FCertType:string;        //֤������87
    FNation:string;          //����2001
    FErrNation:string;
    FPeople:string;          //����89
    FErrPeople:string;

    FCustInfoErrList:TStrings;
    FCustInfoList:TCustInfoList;

    FPath:string;

    function findStr(srcStr,destStr,errStr:string;strS:TStrings):string;
    //procedure iniGridSize;
    procedure clsDataSet;//�رռ�¼��
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImportCustomerInfo: TfaqhImportCustomerInfo;

implementation

uses KsFrameworks, KSClientConsts,UCMqhCustomerImp;
     
{$R *.DFM}

procedure TfaqhImportCustomerInfo.Init;
begin
  inherited;
  btnImport.Enabled := False;
  btnCheck.Enabled := False;
  FPath := ExtractFileDir(application.ExeName) + '\' + 'logs';
end;

procedure TfaqhImportCustomerInfo.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImportCustomerInfo.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where �շ����<>'+#39+''+#39;
    sqlstr:=sqlstr+' and ����<>'+#39+''+#39+' and У��<>'+#39+''+#39;
    if Trim(edtNo.Text)<>'' then
      sqlstr:=sqlstr+' and ѧ����='+#39+Trim(edtNo.Text)+#39;
    if Trim(edtCardNo.Text)<>'' then
      sqlstr:=sqlstr+' and ���֤�� like '+#39+'%'+Trim(edtCardNo.Text)+'%'+#39;
    if Trim(edtName.Text)<>'' then
      sqlstr:=sqlstr+' and ���� like '+#39+'%'+Trim(edtName.Text)+'%'+#39;
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
    btnCheck.Enabled := True;
    pbStatues.Position := 0;
  except
    Context.GetDialogSystem.ShowMessage('�����ݱ�ʧ�ܣ����򿪵�Excel�ļ���������Ƿ���ȷ��');
  end;
end;

procedure TfaqhImportCustomerInfo.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  stuempNo:string;
  custType:Integer;
  feeType:Integer;
  custName:string;
  area:string;
  dept:string;
  spec:string;
  classes:string;
  cardType:string;
  cardNo:string;
  sex:string;
  nation:string;
  mz:string;
  email:string;
  tel:string;
  phone:string;
  addr:string;
  post:string;
  inDate:string;
  outDate:string;
  pNo:string;

  FErrList:TStrings;
begin
  //inherited;
  pbStatues.Position := 0;
  xH:=1;//���
  stuempNo := FCustInfoList.Items[0].CustNo;
  custType := FCustInfoList.Items[0].CustType;
  feeType := FCustInfoList.Items[0].FeeType;
  custName := FCustInfoList.Items[0].CustName;
  area := FCustInfoList.Items[0].Area;
  dept := FCustInfoList.Items[0].Dept;
  spec := FCustInfoList.Items[0].Spec;
  classes := FCustInfoList.Items[0].ClassNo;
  cardType := FCustInfoList.Items[0].CertType;
  cardNo := FCustInfoList.Items[0].CertNo;
  sex :=FCustInfoList.Items[0].Sex;
  nation := FCustInfoList.Items[0].Nation;
  mz := FCustInfoList.Items[0].People;
  email := FCustInfoList.Items[0].Email;
  tel := FCustInfoList.Items[0].Tel;
  phone := FCustInfoList.Items[0].Phone;
  addr := FCustInfoList.Items[0].Addr;
  post := FCustInfoList.Items[0].PostCode;
  inDate := FCustInfoList.Items[0].RegDate;
  outDate := FCustInfoList.Items[0].DestoryDate;

  WorkView.FieldByName('���').Data.SetInteger(xh);
  WorkView.FieldByName('���κ�').Data.SetString(pNo);
  WorkView.FieldByName('�Ƿ������').Data.SetString('0');
  WorkView.FieldByName('������־').Data.SetString('A');
  WorkView.FieldByName('ѧ����').Data.SetString(stuempNo);
  WorkView.FieldByName('�ͻ����').Data.SetInteger(custtype);
  WorkView.FieldByName('�շ����').Data.SetInteger(feeType);
  WorkView.FieldByName('����').Data.SetString(custName);
  WorkView.FieldByName('У��').Data.SetString(area);
  WorkView.FieldByName('��������').Data.SetString(dept);
  WorkView.FieldByName('רҵ').Data.SetString(spec);
  WorkView.FieldByName('�༶').Data.SetString(classes);
  WorkView.FieldByName('֤������').Data.SetString(cardType);
  WorkView.FieldByName('֤������').Data.SetString(cardNo);
  WorkView.FieldByName('�Ա�').Data.SetString(sex);
  WorkView.FieldByName('����').Data.SetString(mz);
  WorkView.FieldByName('����').Data.SetString(nation);
  WorkView.FieldByName('��������').Data.SetString(email);
  WorkView.FieldByName('�绰').Data.SetString(tel);
  WorkView.FieldByName('�ֻ�').Data.SetString(phone);
  WorkView.FieldByName('��ַ').Data.SetString(addr);
  WorkView.FieldByName('�ʱ�').Data.SetString(post);
  WorkView.FieldByName('��У����').Data.SetString(inDate);
  WorkView.FieldByName('Ԥ����У����').Data.SetString(outDate);
  //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
  //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ

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
    pNo:=WorkView.fieldbyname('���κ�').Data.AsString;
  end;
  f:=1;
  pbStatues.Max := FCustInfoList.Count;
  FErrList := nil;
  try
    FErrList := TStringList.Create;
    for i := 1 to FCustInfoList.Count-1 do
    begin
      //���е���Ϣ������ɺ���һ����ɱ�־��Ȼ��ȴ���̨�����Ƿ�д�����ݿ��־
      //�ɹ��򷵻سɹ���ʾ��Ϣ��ʧ���򷵻���һ����¼ʧ�ܣ�������ʧ����Ϣ
      xh:=xh+1;
      f:=f+1;
      if f=FCustInfoList.Count then
      begin
        WorkView.FieldByName('�Ƿ������').Data.SetString('1');
      end
      else
      begin
        WorkView.FieldByName('�Ƿ������').Data.SetString('0');
      end;

      stuempNo := FCustInfoList.Items[i].CustNo;
      custType := FCustInfoList.Items[i].CustType;
      feeType := FCustInfoList.Items[i].FeeType;
      custName := FCustInfoList.Items[i].CustName;
      area := FCustInfoList.Items[i].Area;
      dept := FCustInfoList.Items[i].Dept;
      spec := FCustInfoList.Items[i].Spec;
      classes := FCustInfoList.Items[i].ClassNo;
      cardType := FCustInfoList.Items[i].CertType;
      cardNo := FCustInfoList.Items[i].CertNo;
      sex :=FCustInfoList.Items[i].Sex;
      nation := FCustInfoList.Items[i].Nation;
      mz := FCustInfoList.Items[i].People;
      email := FCustInfoList.Items[i].Email;
      tel := FCustInfoList.Items[i].Tel;
      phone := FCustInfoList.Items[i].Phone;
      addr := FCustInfoList.Items[i].Addr;
      post := FCustInfoList.Items[i].PostCode;
      inDate := FCustInfoList.Items[i].RegDate;
      outDate := FCustInfoList.Items[i].DestoryDate;

      WorkView.FieldByName('���').Data.SetInteger(xh);
      WorkView.FieldByName('���κ�').Data.SetString(pNo);
      WorkView.FieldByName('������־').Data.SetString('A');
      WorkView.FieldByName('ѧ����').Data.SetString(stuempNo);
      WorkView.FieldByName('�ͻ����').Data.SetInteger(custtype);
      WorkView.FieldByName('�շ����').Data.SetInteger(feeType);
      WorkView.FieldByName('����').Data.SetString(custName);
      WorkView.FieldByName('У��').Data.SetString(area);
      WorkView.FieldByName('��������').Data.SetString(dept);
      WorkView.FieldByName('רҵ').Data.SetString(spec);
      WorkView.FieldByName('�༶').Data.SetString(classes);
      WorkView.FieldByName('֤������').Data.SetString(cardType);
      WorkView.FieldByName('֤������').Data.SetString(cardNo);
      WorkView.FieldByName('�Ա�').Data.SetString(sex);
      WorkView.FieldByName('����').Data.SetString(mz);
      WorkView.FieldByName('����').Data.SetString(nation);
      WorkView.FieldByName('��������').Data.SetString(email);
      WorkView.FieldByName('�绰').Data.SetString(tel);
      WorkView.FieldByName('�ֻ�').Data.SetString(phone);
      WorkView.FieldByName('��ַ').Data.SetString(addr);
      WorkView.FieldByName('�ʱ�').Data.SetString(post);
      WorkView.FieldByName('��У����').Data.SetString(inDate);
      WorkView.FieldByName('Ԥ����У����').Data.SetString(outDate);
      MainRequest.SendCommand;
      if WorkView.FieldByName('������').Data.AsInteger<>0 then
      begin
        FErrList.Add('ѧ����Ϊ['+stuempNo+'],����Ϊ['+custName+']�Ŀͻ�����ʧ�ܣ�ʧ��ԭ��--'+WorkView.FieldByName('������Ϣ').Data.AsString);
        Continue;
      end;
      Sleep(50);
      pbStatues.Position := pbStatues.Position + 1;
    end;
    pbStatues.Position := pbStatues.Max;
    if FErrList.Count>0 then
    begin
      FErrList.SaveToFile(FPath+'\�ͻ���Ϣ����ʧ�ܼ�¼'+FormatDateTime('yyyymmddhhmmss',Now)+'.txt');
      Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString+'����ʧ����Ϣ����\bin\logs��');
    end
    else
      Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString);
    RzStatusPane1.Caption:=WorkView.fieldbyname('������Ϣ').Data.AsString;
  finally
    FErrList.Destroy;
  end;
  clsDataSet;
  if FCustInfoList<>nil then
    FCustInfoList.Destroy;
  btnImport.Enabled := False;
  btnCheck.Enabled := False;
end;

procedure TfaqhImportCustomerInfo.btnPrintClick(Sender: TObject);
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
procedure TfaqhImportCustomerInfo.clsDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

function TfaqhImportCustomerInfo.findStr(srcStr, destStr, errStr: string;strS: TStrings): string;
var
  tempStr:string;
  tempNo:string;
  i:Integer;
begin
  Result := '';
  if errStr<>'' then
    if srcStr=errStr then
    begin
      Exit;
    end;
  tempNo := Copy(destStr,1,Pos('-',destStr)-1);
  tempStr := Copy(destStr,Pos('-',destStr)+1,Length(destStr));

  if srcStr=tempStr then
  begin
    //ShowMessage(tempNo);
    Result := tempNo;
  end
  else
  begin
    //�������ֵ���ȥ����
    for i := 0 to strS.Count-1 do
    begin
      tempStr := Copy(strS.Strings[i],Pos('-',strS.Strings[i])+1,Length(strS.Strings[i]));
      if tempStr=srcStr then
      begin
        tempNo := Copy(strS.Strings[i],1,Pos('-',strS.Strings[i])-1);
        destStr := strS.strings[i];
        Result := tempNo;
        Break;
      end;
    end;
  end;
end;

procedure TfaqhImportCustomerInfo.btnCheckClick(Sender: TObject);
var
  i:Integer;  
  qCustType:string;        //�ͻ����
  qFeeType:string;         //�շ����
  qArea:string;            //У��
  qDept:string;            //����
  qSpec:string;            //רҵ
  qCertType:string;        //֤������
  qNation:string;          //����
  qPeople:string;          //����
  qSex:string;             //�Ա�
  qCustName:string;        //�ͻ�����
  qCustNo:string;          //ѧ����
  qClassNo:string;         //�༶
  qCertNo:string;          //֤������
  qEmail:string;           //��������
  qTel:string;             //�绰
  qPhone:string;           //�ֻ�
  qAddress:string;         //��ַ
  qPostCode:string;        //�ʱ�
  qRegDate :string;        //��У����
  qDestoryDate:string;     //Ԥ����У����

  tempCode:string;
  custInfo:TCustInfo;
begin
  if qrySource.Active=False then
  begin
    Context.GetDialogSystem.ShowMessage('���ȴ�ҪҪ�����Excel��');
    Exit;
  end;
  if qrySource.RecordCount=0 then
  begin
    Context.GetDialogSystem.ShowMessage('û����Ҫ�������ݣ�');
    Exit;
  end;
  if qrySource.RecordCount<2 then
  begin
    Context.GetDialogSystem.ShowMessage('Ҫ���������С��2������ֱ�ӵ��ͻ���Ϣ����������ӿͻ���Ϣ��');
    Exit;
  end;
  try
    FCustInfoErrList := TStringList.Create;
    FCustInfoList := TCustInfoList.Create;
    pbStatues.Position := 0;
    qrySource.First;
    pbStatues.Max := qrySource.RecordCount;

    //custInfo := nil;
    for i := 0 to qrySource.RecordCount-1 do
    begin
      qCustType := Trim(qrySource.fieldbyname('�ͻ����').AsString);
      qFeeType := Trim(qrySource.fieldbyname('�շ����').AsString);
      qArea := Trim(qrySource.fieldbyname('У��').AsString);
      qDept := Trim(qrySource.fieldbyname('��������').AsString);
      qSpec := Trim(qrySource.fieldbyname('רҵ').AsString);
      qCertType := Trim(qrySource.fieldbyname('֤������').AsString);
      qSex := Trim(qrySource.fieldbyname('�Ա�').AsString);
      qNation := Trim(qrySource.fieldbyname('����').AsString);
      qPeople := Trim(qrySource.fieldbyname('����').AsString);
      qCustNo := Trim(qrySource.fieldbyname('ѧ����').AsString);
      qCustName := Trim(qrySource.fieldbyname('����').AsString);

      qClassNo := Trim(qrySource.fieldbyname('�༶').AsString);
      qCertNo := Trim(qrySource.fieldbyname('֤������').AsString);
      qEmail := Trim(qrySource.fieldbyname('��������').AsString);
      qTel := Trim(qrySource.fieldbyname('�绰').AsString);
      qPhone := Trim(qrySource.fieldbyname('�ֻ�').AsString);
      qAddress := Trim(qrySource.fieldbyname('��ַ').AsString);
      qPostCode := Trim(qrySource.fieldbyname('�ʱ�').AsString);
      qRegDate := Trim(qrySource.fieldbyname('��У����').AsString);
      qDestoryDate := Trim(qrySource.fieldbyname('Ԥ����У����').AsString);
      
      custInfo := TCustInfo.Create;
      custInfo.CustNo := qCustNo;
      custInfo.CustName := qCustName;
      custInfo.ClassNo := qClassNo;
      custInfo.CertNo := qCertNo;
      custInfo.Email := qEmail;
      custInfo.Tel := qTel;
      custInfo.Phone := qPhone;
      custInfo.Addr := qAddress;
      custInfo.PostCode := qPostCode;
      custInfo.RegDate := qRegDate;
      custInfo.DestoryDate := qDestoryDate;
      //�ȽϿͻ����
      if qCustType<>'' then
      begin
        tempCode := findStr(qCustType,FCustType,'',cbbcusttype.items);
        if tempCode = '' then
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�������('+qcustType+')�ÿͻ����')
        else
        begin
          FCustType := tempCode+'-'+qcustType;
          custInfo.CustType := StrToInt(tempCode);
        end;
      end
      else
        FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ��ͻ����Ϊ��');

      //�Ƚ��շ����
      if qfeeType<>'' then
      begin
        tempCode := findStr(qFeeType,FFeeType,'',cbbFeeType.Items);
        if tempCode='' then
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�������('+qfeetype+')���շ����')
        else
        begin
          FFeeType := tempCode+'-'+qfeeType;
          custInfo.FeeType := StrToInt(tempCode);
        end;
      end
      else
        FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ��շ����Ϊ��');

      //�Ƚ�У��
      if qArea<>'' then
      begin
        tempCode := findStr(qArea,FArea,'',cbbArea.Items);
        if tempCode='' then
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�������('+qarea+')��У��')
        else
        begin
          FArea := tempCode+'-'+qArea;
          custInfo.Area := tempCode;
        end;
      end
      else
        FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�У��Ϊ��');

      //�Ƚ�֤������
      if qCertType<>'' then
      begin
        tempCode := findStr(qCertType,FCertType,'',cbbCertType.Items);
        if tempCode='' then
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�������('+qCertType+')��֤������')
        else
        begin
          FCertType := tempCode+'-'+qCertType;
          custInfo.CertType := tempCode;
        end;
      end;
      
      //�ȽϹ���
      if qNation<>'' then
      begin
        tempCode := findStr(qNation,FNation,FErrNation,cbbNation.Items);
        if tempCode='' then
        begin
          FErrNation := qNation;
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�������('+qnation+')�ù���');
        end
        else
        begin
          FNation := tempCode+'-'+qNation;
          custInfo.Nation := tempCode;
        end;
      end;

      //�Ƚ�����
      if qPeople<>'' then
      begin
        tempCode := findStr(qPeople,FPeople,FErrPeople,cbbPeople.Items);
        if tempCode='' then
        begin
          FErrPeople := qPeople;
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�������('+qpeople+')������');
        end
        else
        begin
          FPeople := tempCode+'-'+qPeople;
          custInfo.People := tempCode;
        end;
      end;
      
      //�Ƚ��Ա�
      if qSex<>'' then
      begin
        if ((qSex<>MAN) and (qSex<>WOMEN)) then
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ��Ա���ȷ')
        else
        begin
          if qSex=MAN then
            custInfo.Sex := '1'
          else if qSex=WOMEN then
            custInfo.Sex := '2'
          else
            custInfo.Sex := '3';
        end;
      end;
      
      //�Ƚϲ���

      if qDept<>'' then
      begin
        //ShowMessage(FDept);
        tempCode := findStr(qDept,FDept,FErrDept,cbbDept.Items);
        if tempCode='' then
        begin
          FErrDept := qDept;
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�������('+qdept+')�ò���');
        end
        else
        begin
          FDept := tempCode+'-'+qDept;
          custInfo.Dept := tempCode;
        end;
      end;
     
      //�Ƚ�רҵ
      if qSpec<>'' then
      begin
        tempCode := findStr(qSpec,FSpec,FErrSpec,cbbSpec.Items);
        if tempCode='' then
        begin
          FErrSpec := qSpec;
          FCustInfoErrList.Add('ѧ����['+qcustNo+'],����['+qcustname+']���ʧ�ܣ�������('+qspec+')��רҵ');
        end
        else
        begin
          FSpec := tempCode+'-'+qSpec;
          custInfo.Spec := tempCode;
        end;
      end;

      FCustInfoList.Add(custInfo);
      pbStatues.Position := pbStatues.Position + 1;
      qrySource.Next;
    end;
    if FCustInfoErrList.Count>0 then
    begin                                       //..\bin\PATCHLOG\
      FCustInfoErrList.SaveToFile(FPath+'\�ͻ���Ϣ������ʧ�ܼ�¼'+FormatDateTime('yyyymmddhhmmss',Now)+'.txt');
      FCustInfoList.Destroy;
      //����ʹ�������
      Context.GetDialogSystem.ShowMessage('�ͻ���Ϣ���������,������־�ڰ�װĿ¼bin\logs��,�����޸�,Ȼ���ٵ��룡');
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage('�ͻ���Ϣ��������ɣ�����ִ�е��룡');
      btnImport.Enabled := True;
    end;
  finally
    FCustInfoErrList.Destroy;
  end;
end;

{ TCustInfoList }

function TCustInfoList.GetItems(index: Integer): TCustInfo;
begin
  Result := TCustInfo(inherited Items[Index]);
end;

initialization
  TUIStdClassFactory.Create('�ͻ���Ϣ����',TfaqhImportCustomerInfo);

end.
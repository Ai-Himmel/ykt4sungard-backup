unit UAImportCustomerInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls,Contnrs,
  UIncrementComboBox;

const
  MAN = '男';
  WOMEN = '女';

type
  TCustInfo = class
  private
    FFCustNo:string;          //学工号
    FFCustType:Integer;       //客户类别
    FFFeeType:Integer;        //收费类别
    FFCustName:string;        //客户姓名
    FFArea:string;            //校区
    FFDept:string;            //部门
    FFSpec:string;            //专业
    FFCertType:string;        //证件类型
    FFCertNo:string;          //证件号码
    FFSex:string;             //性别
    FFNation:string;          //国籍
    FFPeople:string;          //民族
    FFEmail:string;           //电子信箱
    FFTel:string;             //电话
    FFPhone:string;           //手机
    FFAddr:string;            //地址
    FFPostCode:string;        //邮编
    FFRegDate:string;         //入校日期
    FFDestoryDate:string;     //离校日期
    FFClassNo:string;         //班级
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
    FCustType:string;        //客户类别-34
    FFeeType:string;         //收费类别-43
    FArea:string;            //校区-27
    FDept:string;            //部门-22
    FErrDept:string;         //不存在的部门
    FSpec:string;            //专业-23
    FErrSpec:string;         //不存在的专业
    FCertType:string;        //证件类型87
    FNation:string;          //国籍2001
    FErrNation:string;
    FPeople:string;          //民族89
    FErrPeople:string;

    FCustInfoErrList:TStrings;
    FCustInfoList:TCustInfoList;

    FPath:string;

    function findStr(srcStr,destStr,errStr:string;strS:TStrings):string;
    //procedure iniGridSize;
    procedure clsDataSet;//关闭记录集
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
  dlgOpen.Title := '请选择相应的Excel文件';
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 收费类别<>'+#39+''+#39;
    sqlstr:=sqlstr+' and 姓名<>'+#39+''+#39+' and 校区<>'+#39+''+#39;
    if Trim(edtNo.Text)<>'' then
      sqlstr:=sqlstr+' and 学工号='+#39+Trim(edtNo.Text)+#39;
    if Trim(edtCardNo.Text)<>'' then
      sqlstr:=sqlstr+' and 身份证号 like '+#39+'%'+Trim(edtCardNo.Text)+'%'+#39;
    if Trim(edtName.Text)<>'' then
      sqlstr:=sqlstr+' and 姓名 like '+#39+'%'+Trim(edtName.Text)+'%'+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    try
      qrySource.Open;
    except
      Context.GetDialogSystem.ShowMessage('查询错误，请检查excel文件及表单名称是否正确！');
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
    Context.GetDialogSystem.ShowMessage('打开数据表失败，检查打开的Excel文件或表单名称是否正确！');
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
  xH:=1;//序号
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

  WorkView.FieldByName('序号').Data.SetInteger(xh);
  WorkView.FieldByName('批次号').Data.SetString(pNo);
  WorkView.FieldByName('是否传送完毕').Data.SetString('0');
  WorkView.FieldByName('操作标志').Data.SetString('A');
  WorkView.FieldByName('学工号').Data.SetString(stuempNo);
  WorkView.FieldByName('客户类别').Data.SetInteger(custtype);
  WorkView.FieldByName('收费类别').Data.SetInteger(feeType);
  WorkView.FieldByName('姓名').Data.SetString(custName);
  WorkView.FieldByName('校区').Data.SetString(area);
  WorkView.FieldByName('所属部门').Data.SetString(dept);
  WorkView.FieldByName('专业').Data.SetString(spec);
  WorkView.FieldByName('班级').Data.SetString(classes);
  WorkView.FieldByName('证件类型').Data.SetString(cardType);
  WorkView.FieldByName('证件号码').Data.SetString(cardNo);
  WorkView.FieldByName('性别').Data.SetString(sex);
  WorkView.FieldByName('民族').Data.SetString(mz);
  WorkView.FieldByName('国籍').Data.SetString(nation);
  WorkView.FieldByName('电子邮箱').Data.SetString(email);
  WorkView.FieldByName('电话').Data.SetString(tel);
  WorkView.FieldByName('手机').Data.SetString(phone);
  WorkView.FieldByName('地址').Data.SetString(addr);
  WorkView.FieldByName('邮编').Data.SetString(post);
  WorkView.FieldByName('入校日期').Data.SetString(inDate);
  WorkView.FieldByName('预计离校日期').Data.SetString(outDate);
  //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
  //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息

  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString);
    RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
    Exit;
  end
  else
  begin
    RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
    pNo:=WorkView.fieldbyname('批次号').Data.AsString;
  end;
  f:=1;
  pbStatues.Max := FCustInfoList.Count;
  FErrList := nil;
  try
    FErrList := TStringList.Create;
    for i := 1 to FCustInfoList.Count-1 do
    begin
      //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
      //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息
      xh:=xh+1;
      f:=f+1;
      if f=FCustInfoList.Count then
      begin
        WorkView.FieldByName('是否传送完毕').Data.SetString('1');
      end
      else
      begin
        WorkView.FieldByName('是否传送完毕').Data.SetString('0');
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

      WorkView.FieldByName('序号').Data.SetInteger(xh);
      WorkView.FieldByName('批次号').Data.SetString(pNo);
      WorkView.FieldByName('操作标志').Data.SetString('A');
      WorkView.FieldByName('学工号').Data.SetString(stuempNo);
      WorkView.FieldByName('客户类别').Data.SetInteger(custtype);
      WorkView.FieldByName('收费类别').Data.SetInteger(feeType);
      WorkView.FieldByName('姓名').Data.SetString(custName);
      WorkView.FieldByName('校区').Data.SetString(area);
      WorkView.FieldByName('所属部门').Data.SetString(dept);
      WorkView.FieldByName('专业').Data.SetString(spec);
      WorkView.FieldByName('班级').Data.SetString(classes);
      WorkView.FieldByName('证件类型').Data.SetString(cardType);
      WorkView.FieldByName('证件号码').Data.SetString(cardNo);
      WorkView.FieldByName('性别').Data.SetString(sex);
      WorkView.FieldByName('民族').Data.SetString(mz);
      WorkView.FieldByName('国籍').Data.SetString(nation);
      WorkView.FieldByName('电子邮箱').Data.SetString(email);
      WorkView.FieldByName('电话').Data.SetString(tel);
      WorkView.FieldByName('手机').Data.SetString(phone);
      WorkView.FieldByName('地址').Data.SetString(addr);
      WorkView.FieldByName('邮编').Data.SetString(post);
      WorkView.FieldByName('入校日期').Data.SetString(inDate);
      WorkView.FieldByName('预计离校日期').Data.SetString(outDate);
      MainRequest.SendCommand;
      if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
      begin
        FErrList.Add('学工号为['+stuempNo+'],姓名为['+custName+']的客户导入失败，失败原因--'+WorkView.FieldByName('返回信息').Data.AsString);
        Continue;
      end;
      Sleep(50);
      pbStatues.Position := pbStatues.Position + 1;
    end;
    pbStatues.Position := pbStatues.Max;
    if FErrList.Count>0 then
    begin
      FErrList.SaveToFile(FPath+'\客户信息导入失败记录'+FormatDateTime('yyyymmddhhmmss',Now)+'.txt');
      Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString+'导入失败信息存在\bin\logs下');
    end
    else
      Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString);
    RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
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
  过程名:    TfaqhImportCustomerInfo.closeDataSet关闭Excel记录集
  作者:      Administrator
  日期:      2005.08.01
  参数:      无
  返回值:    无
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
    //到数据字典项去查找
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
  qCustType:string;        //客户类别
  qFeeType:string;         //收费类别
  qArea:string;            //校区
  qDept:string;            //部门
  qSpec:string;            //专业
  qCertType:string;        //证件类型
  qNation:string;          //国籍
  qPeople:string;          //民族
  qSex:string;             //性别
  qCustName:string;        //客户姓名
  qCustNo:string;          //学工号
  qClassNo:string;         //班级
  qCertNo:string;          //证件号码
  qEmail:string;           //电子邮箱
  qTel:string;             //电话
  qPhone:string;           //手机
  qAddress:string;         //地址
  qPostCode:string;        //邮编
  qRegDate :string;        //入校日期
  qDestoryDate:string;     //预计离校日期

  tempCode:string;
  custInfo:TCustInfo;
begin
  if qrySource.Active=False then
  begin
    Context.GetDialogSystem.ShowMessage('请先打开要要导入的Excel！');
    Exit;
  end;
  if qrySource.RecordCount=0 then
  begin
    Context.GetDialogSystem.ShowMessage('没有你要检测的数据！');
    Exit;
  end;
  if qrySource.RecordCount<2 then
  begin
    Context.GetDialogSystem.ShowMessage('要导入的数据小于2条，请直接到客户信息设置里面添加客户信息！');
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
      qCustType := Trim(qrySource.fieldbyname('客户类别').AsString);
      qFeeType := Trim(qrySource.fieldbyname('收费类别').AsString);
      qArea := Trim(qrySource.fieldbyname('校区').AsString);
      qDept := Trim(qrySource.fieldbyname('所属部门').AsString);
      qSpec := Trim(qrySource.fieldbyname('专业').AsString);
      qCertType := Trim(qrySource.fieldbyname('证件类型').AsString);
      qSex := Trim(qrySource.fieldbyname('性别').AsString);
      qNation := Trim(qrySource.fieldbyname('国籍').AsString);
      qPeople := Trim(qrySource.fieldbyname('民族').AsString);
      qCustNo := Trim(qrySource.fieldbyname('学工号').AsString);
      qCustName := Trim(qrySource.fieldbyname('姓名').AsString);

      qClassNo := Trim(qrySource.fieldbyname('班级').AsString);
      qCertNo := Trim(qrySource.fieldbyname('证件号码').AsString);
      qEmail := Trim(qrySource.fieldbyname('电子邮箱').AsString);
      qTel := Trim(qrySource.fieldbyname('电话').AsString);
      qPhone := Trim(qrySource.fieldbyname('手机').AsString);
      qAddress := Trim(qrySource.fieldbyname('地址').AsString);
      qPostCode := Trim(qrySource.fieldbyname('邮编').AsString);
      qRegDate := Trim(qrySource.fieldbyname('入校日期').AsString);
      qDestoryDate := Trim(qrySource.fieldbyname('预计离校日期').AsString);
      
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
      //比较客户类别
      if qCustType<>'' then
      begin
        tempCode := findStr(qCustType,FCustType,'',cbbcusttype.items);
        if tempCode = '' then
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，不存在('+qcustType+')该客户类别')
        else
        begin
          FCustType := tempCode+'-'+qcustType;
          custInfo.CustType := StrToInt(tempCode);
        end;
      end
      else
        FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，客户类别为空');

      //比较收费类别
      if qfeeType<>'' then
      begin
        tempCode := findStr(qFeeType,FFeeType,'',cbbFeeType.Items);
        if tempCode='' then
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，不存在('+qfeetype+')该收费类别')
        else
        begin
          FFeeType := tempCode+'-'+qfeeType;
          custInfo.FeeType := StrToInt(tempCode);
        end;
      end
      else
        FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，收费类别为空');

      //比较校区
      if qArea<>'' then
      begin
        tempCode := findStr(qArea,FArea,'',cbbArea.Items);
        if tempCode='' then
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，不存在('+qarea+')该校区')
        else
        begin
          FArea := tempCode+'-'+qArea;
          custInfo.Area := tempCode;
        end;
      end
      else
        FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，校区为空');

      //比较证件类型
      if qCertType<>'' then
      begin
        tempCode := findStr(qCertType,FCertType,'',cbbCertType.Items);
        if tempCode='' then
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，不存在('+qCertType+')该证件类型')
        else
        begin
          FCertType := tempCode+'-'+qCertType;
          custInfo.CertType := tempCode;
        end;
      end;
      
      //比较国籍
      if qNation<>'' then
      begin
        tempCode := findStr(qNation,FNation,FErrNation,cbbNation.Items);
        if tempCode='' then
        begin
          FErrNation := qNation;
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，不存在('+qnation+')该国籍');
        end
        else
        begin
          FNation := tempCode+'-'+qNation;
          custInfo.Nation := tempCode;
        end;
      end;

      //比较民族
      if qPeople<>'' then
      begin
        tempCode := findStr(qPeople,FPeople,FErrPeople,cbbPeople.Items);
        if tempCode='' then
        begin
          FErrPeople := qPeople;
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，不存在('+qpeople+')该民族');
        end
        else
        begin
          FPeople := tempCode+'-'+qPeople;
          custInfo.People := tempCode;
        end;
      end;
      
      //比较性别
      if qSex<>'' then
      begin
        if ((qSex<>MAN) and (qSex<>WOMEN)) then
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，性别不正确')
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
      
      //比较部门

      if qDept<>'' then
      begin
        //ShowMessage(FDept);
        tempCode := findStr(qDept,FDept,FErrDept,cbbDept.Items);
        if tempCode='' then
        begin
          FErrDept := qDept;
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，不存在('+qdept+')该部门');
        end
        else
        begin
          FDept := tempCode+'-'+qDept;
          custInfo.Dept := tempCode;
        end;
      end;
     
      //比较专业
      if qSpec<>'' then
      begin
        tempCode := findStr(qSpec,FSpec,FErrSpec,cbbSpec.Items);
        if tempCode='' then
        begin
          FErrSpec := qSpec;
          FCustInfoErrList.Add('学工号['+qcustNo+'],姓名['+qcustname+']检测失败，不存在('+qspec+')该专业');
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
      FCustInfoErrList.SaveToFile(FPath+'\客户信息导入检测失败记录'+FormatDateTime('yyyymmddhhmmss',Now)+'.txt');
      FCustInfoList.Destroy;
      //检查后使导入可用
      Context.GetDialogSystem.ShowMessage('客户信息导入检测完成,错误日志在安装目录bin\logs下,请先修复,然后再导入！');
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage('客户信息导入检测完成，可以执行导入！');
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
  TUIStdClassFactory.Create('客户信息导入',TfaqhImportCustomerInfo);

end.
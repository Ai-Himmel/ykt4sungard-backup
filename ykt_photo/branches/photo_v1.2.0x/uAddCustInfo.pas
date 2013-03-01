unit uAddCustInfo;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, Buttons, DBGridEh, Mask, DBCtrlsEh,
  DBLookupEh, DB, ADODB;

type
  TfrmAddCustInfo = class(TForm)
    pnl1: TPanel;
    lbl1: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    btnOper: TBitBtn;
    BitBtn1: TBitBtn;
    cbbType: TDBLookupComboboxEh;
    cbbArea: TDBLookupComboboxEh;
    cbbDept: TDBLookupComboboxEh;
    cbbSpec: TDBLookupComboboxEh;
    qryType: TADOQuery;
    dsType: TDataSource;
    qryDept: TADOQuery;
    dsDept: TDataSource;
    qryArea: TADOQuery;
    dsArea: TDataSource;
    qrySpec: TADOQuery;
    dsSpec: TDataSource;
    qryAdd: TADOQuery;
    dsAdd: TDataSource;
    edtStuempNo: TDBEditEh;
    edtName: TDBEditEh;
    edtCardId: TDBEditEh;
    lblCustId: TLabel;
    Label7: TLabel;
    cbbFeeType: TDBLookupComboboxEh;
    qryFeeType: TADOQuery;
    dsFeeType: TDataSource;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnOperClick(Sender: TObject);
  private
    { Private declarations }
    sDept:string;
    sSpec:string;
    sArea:string;
    sType:string;
    sFeeType:string;
    procedure fillDataToCbb();

    //procedure addCustInfo();
    procedure editCustInfo();
    procedure queryCustInfo();
    procedure queryForAdd();
    procedure readLstInfo();
  public
    { Public declarations }
    operType:string;
  end;

var
  frmAddCustInfo: TfrmAddCustInfo;

implementation

uses uCommon, Udm;

{$R *.dfm}

procedure TfrmAddCustInfo.BitBtn1Click(Sender: TObject);
begin
  close();
end;

procedure TfrmAddCustInfo.fillDataToCbb;
var
  deptSql:string;
  specSql:string;
  typeSql:string;
  areaSql:string;
  feeSql:string;
begin
  edtStuempNo.DataField:=stuempNo;
  edtName.DataField:=custName;
  edtCardId.DataField:=custCardId;
  cbbDept.DataField:=custDeptNo;
  cbbType.DataField:=custType;
  cbbSpec.DataField:=custSpecNo;
  cbbArea.DataField:=custArea;
  cbbFeeType.DataField:=custFeeType;

  //deptSql:='select '+deptcode+','+deptName+' from '+tbldept+' order by '+deptName;
  //specSql:='select '+specCode+','+specName+' from '+tblspec+' order by '+specName;
  //typeSql:='select '+typeNo+','+typeName+' from '+tblCutType+' order by '+typeName;
  //areaSql:='select '+areaNo+','+areaName+' from '+tblArea+' where '+areaFather+'=1';
  getFillQuerySql(deptSql,specSql,typeSql,areaSql);
  feeSql:='select '+feeFeeType+','+feeFeeName+' from '+tblFeeType+' order by '+feeFeeType;
  cbbDept.ListField:=deptName;
  cbbDept.KeyField:=deptCode;
  qryDept.Close;
  qryDept.SQL.Clear;
  qryDept.SQL.Add(deptSql);
  qryDept.Open;

  cbbType.KeyField:=typeNo;
  cbbType.ListField:=typeName;
  qryType.Close;
  qryType.SQL.Clear;
  qryType.SQL.Add(typeSql);
  qryType.Open;

  cbbSpec.KeyField:=specCode;
  cbbSpec.ListField:=specName;
  qrySpec.Close;
  qrySpec.SQL.Clear;
  qrySpec.SQL.Add(specSql);
  qrySpec.Open;

  cbbArea.KeyField:=areaNo;
  cbbArea.ListField:=areaName;
  qryArea.Close;
  qryArea.SQL.Clear;
  qryArea.SQL.Add(areaSql);
  qryArea.Open;

  cbbFeeType.KeyField:=feeFeeType;
  cbbFeeType.ListField:=feeFeeName;
  qryFeeType.Close;
  qryFeeType.SQL.Clear;
  qryFeeType.SQL.Add(feeSql);
  qryFeeType.Open;
end;

procedure TfrmAddCustInfo.FormShow(Sender: TObject);
begin
  if operType='add' then
  begin
    Self.Caption := '添加人员信息';
    btnOper.Caption:='添 加';
    btnOper.Visible:=True;
  end
  else if operType='edit' then
  begin
    Self.Caption := '修改人员信息';
    btnOper.Caption:='修 改';
    btnOper.Visible:=True;
  end
  else
    btnOper.Visible:=False;

  fillDataToCbb();
  if operType='edit' then
  begin
    edtStuempNo.Enabled:=False;
    queryCustInfo();
  end
  else if operType='add' then
  begin
    edtStuempNo.Enabled:=True;
    queryForAdd;
  end;
end;

procedure TfrmAddCustInfo.btnOperClick(Sender: TObject);
begin
  if (Trim(edtName.Text)='')or(Trim(edtStuempNo.Text)='') then
  begin
    ShowMessage('学/工号和姓名不能为空！');
    Exit;
  end;
  if (cbbType.Text='')or(cbbArea.Text='') then
  begin
    ShowMessage('人员类别和校区必须选择！');
    Exit;
  end;
  if (cbbFeeType.Text='') then
  begin
    ShowMessage('收费类别必须选择！');
    Exit;
  end;
  readLstInfo();
  if operType='add' then
  begin
    if haveStuEmpNo(Trim(edtStuempNo.Text)) then
    begin
      ShowMessage('该学工号已经存在，请重新输入！');
      edtStuempNo.SetFocus;
      Exit;
    end;
    if addCustInfo(edtStuempNo.Text,edtName.Text,stype,sArea,edtCardId.Text,sDept,sSpec,sFeeType) then
    begin
      if Application.MessageBox('添加人员信息成功，你是否继续添加？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
        Self.Close
      else
        queryForAdd();
    end
    else
      ShowMessage('添加人员信息失败，请重新添加！');
  end
  else if operType='edit' then
  begin
    editCustInfo();
  end;
end;

procedure TfrmAddCustInfo.editCustInfo;
var
  custQuery:TADOQuery;
  photoQuery:TADOQuery;
  custStr:string;
  photoStr:string;
begin
  custStr:='update '+tblCust+' set '+stuempNo+'='+#39+edtStuempNo.Text+#39+',';
  custStr:=custStr+custName+'='+#39+edtName.Text+#39+',';
  custStr:=custStr+custType+'='+sType+',';
  custStr:=custStr+custArea+'='+sArea+',';
  custStr:=custStr+custCardId+'='+#39+edtCardId.Text+#39+',';
  custStr:=custStr+custDeptNo+'='+#39+sDept+#39+',';
  custStr:=custStr+custSpecNo+'='+#39+sSpec+#39+',';
  custStr:=custStr+custFeeType+'='+sfeeType+' where ';
  custStr:=custStr+custId+'='+lblcustId.Caption;

  photoStr:='update '+tblPhoto+' set '+stuempNo+'='+#39+edtStuempNo.Text+#39;
  photoStr:=photoStr+' where '+custId+'='+lblcustId.Caption;
  
  custQuery:=nil;
  photoQuery:=nil;
  try
    custQuery:=TADOQuery.Create(nil);
    custQuery.Connection:=frmdm.conn;
    photoQuery:=TADOQuery.Create(nil);
    photoQuery.Connection:=frmdm.conn;
    
    custQuery.Close;
    custQuery.SQL.Clear;
    custQuery.SQL.Add(custStr);
    photoQuery.Close;
    photoQuery.SQL.Clear;
    photoQuery.SQL.Add(photoStr);

    frmdm.conn.BeginTrans;
    try
      custQuery.ExecSQL;
      photoQuery.ExecSQL;
      frmdm.conn.CommitTrans;
      ShowMessage('保存人员信息成功！');
    except
      frmdm.conn.RollbackTrans;
      ShowMessage('保存人员信息失败，请检查原因！');
    end;
  finally
    custQuery.Destroy;
    photoQuery.Destroy;
  end;
end;

procedure TfrmAddCustInfo.queryCustInfo;
var
  strSql:string;
begin
  strSql:=queryBaseInfoSql('','',lblCustId.Caption);
  qryAdd.Close;
  qryAdd.SQL.Clear;
  qryAdd.SQL.Add(strSql);
  qryAdd.Open;
end;

procedure TfrmAddCustInfo.queryForAdd;
var
  strSql:string;
begin
  strSql:=queryBaseInfoSql('','','-1');
  qryAdd.Close;
  qryAdd.SQL.Clear;
  qryAdd.SQL.Add(strSql);
  qryAdd.Open;
end;

procedure TfrmAddCustInfo.readLstInfo;
begin
  if cbbDept.Text='' then
    sDept:=''
  else
    sDept:=IntToStr(cbbDept.KeyValue);
  if cbbArea.Text='' then
    sArea:=''
  else
    sArea:=IntToStr(cbbArea.KeyValue);
  if cbbSpec.Text='' then
    sSpec:=''
  else
    sSpec:=IntToStr(cbbSpec.KeyValue);
  if cbbType.Text='' then
    sType:=''
  else
    sType:=IntToStr(cbbType.KeyValue);
    
  if cbbFeeType.Text='' then
    sFeeType:=''
  else
    sFeeType:=IntToStr(cbbFeeType.KeyValue);

end;

end.

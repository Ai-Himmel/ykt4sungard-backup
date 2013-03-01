unit uPhotoQuery;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, DBGridEh, StdCtrls, Mask, DBCtrlsEh, DBLookupEh,
  Buttons, GridsEh,IniFiles, DB, jpeg,ADODB;

type
  TfrmPhotoQuery = class(TForm)
    pnl1: TPanel;
    Label5: TLabel;
    Label2: TLabel;
    cbbType: TDBLookupComboboxEh;
    Label3: TLabel;
    Label4: TLabel;
    cbbSpec: TDBLookupComboboxEh;
    cbbDept: TDBLookupComboboxEh;
    Label1: TLabel;
    Label6: TLabel;
    edtStuEmpNo: TEdit;
    edtName: TEdit;
    rgPhoto: TRadioGroup;
    btnOper: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn1: TBitBtn;
    dbgrdhDb: TDBGridEh;
    qryType: TADOQuery;
    dsType: TDataSource;
    dsDept: TDataSource;
    qryDept: TADOQuery;
    qryArea: TADOQuery;
    dsArea: TDataSource;
    qrySpec: TADOQuery;
    dsSpec: TDataSource;
    dsQuery: TDataSource;
    qryQuery: TADOQuery;
    SaveDialog1: TSaveDialog;
    btnPhoto: TBitBtn;
    pnlPhoto: TPanel;
    imgPhoto: TImage;
    cbb1: TComboBox;
    procedure BitBtn1Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnOperClick(Sender: TObject);
    procedure btnPhotoClick(Sender: TObject);
    procedure dbgrdhDbCellClick(Column: TColumnEh);
  private
    { Private declarations }
    procedure fillCbb();
    procedure queryData();
    procedure showPhoto(scustId:string);
  public
    { Public declarations }
  end;

var
  frmPhotoQuery: TfrmPhotoQuery;

implementation

uses uCommon, Udm, mainUnit, DBGrid2Excel;

{$R *.dfm}

procedure TfrmPhotoQuery.BitBtn1Click(Sender: TObject);
begin
  close();
end;

procedure TfrmPhotoQuery.BitBtn2Click(Sender: TObject);
var
  dg2E: TDBGridToExcel;
begin
  with frmdm do
    begin
    if qryQuery.IsEmpty then
    begin
      ShowMessage('请先查询数据，然后再导出！');
      Exit;
    end;
    //ExportData(SaveDialog1,dbgrdhdb);
    if SaveDialog1.Execute then
    begin
      dg2E := TDBGridToExcel.Create(Self);
      dg2E.FileName := SaveDialog1.FileName;
      dg2E.TitleFont.Name := '宋体';
      dg2E.TitleFont.Size := 10;
      dg2E.DataFont.Name := '宋体';
      dg2E.DataFont.Size := 9;
      dg2E.ExportToExcel(dbgrdhDb);
      dg2E.Free;
    end;
  end;

end;

procedure TfrmPhotoQuery.fillCbb;
var
  deptSql:string;
  specSql:string;
  typeSql:string;
  areaSql:string;
begin
  //deptSql:='select '+deptcode+','+deptName+' from '+tbldept+' order by '+deptName;
  //specSql:='select '+specCode+','+specName+' from '+tblspec+' order by '+specName;
  //typeSql:='select '+typeNo+','+typeName+' from '+tblCutType+' order by '+typeName;
  //areaSql:='select '+areaNo+','+areaName+' from '+tblArea+' where '+areaFather+'=1';
  getFillQuerySql(deptSql,specSql,typeSql,areaSql);
  qryDept.Close;
  qryDept.SQL.Clear;
  qryDept.SQL.Add(deptSql);
  qryDept.Open;
  qryDept.Sort := deptName;
  cbbDept.KeyField:=deptCode;
  cbbDept.ListField:=deptName;

  qryType.Close;
  qryType.SQL.Clear;
  qryType.SQL.Add(typeSql);
  qryType.Open;
  qryType.Sort := typeName;
  cbbType.KeyField:=typeNo;
  cbbType.ListField:=typeName;

  qrySpec.Close;
  qrySpec.SQL.Clear;
  qrySpec.SQL.Add(specSql);
  qrySpec.Open;
  qrySpec.Sort := specName;
  cbbSpec.KeyField:=specCode;
  cbbSpec.ListField:=specName;
  
  cbb1.Items.Clear;
  cbb1.Items.LoadFromFile(apppath+'printset\grade.txt');

end;

procedure TfrmPhotoQuery.FormShow(Sender: TObject);
begin
  fillCbb();
  dbgrdhDb.Columns[0].FieldName:=custId;
  dbgrdhDb.Columns[1].FieldName:=stuempNo;
  dbgrdhDb.Columns[2].FieldName:=custName;
  dbgrdhDb.Columns[3].FieldName:=typeName;
  dbgrdhDb.Columns[4].FieldName:=specName;
  dbgrdhDb.Columns[5].FieldName:=deptName;
  //dbgrdhDb.Columns[6].FieldName:=areaName;
  dbgrdhDb.Columns[6].FieldName:=custCardId;
  dbgrdhDb.Columns[7].FieldName:=deptCode;
  dbgrdhDb.Columns[8].FieldName:=specCode;
  dbgrdhDb.Columns[9].FieldName:=typeNo;
  dbgrdhDb.Columns[2].Footer.FieldName:=custName;
end;

procedure TfrmPhotoQuery.queryData;
var
  queryIni:TIniFile;
  sqlStr:string;
begin
  queryIni := nil;
  if FileExists(apppath+'photoquery.ini') = false then
  begin
    Application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
      '系统错误！', mb_ok + mb_iconerror);
    Application.Terminate;
  end;
  try
    queryIni := TIniFile.Create(apppath+'photoquery.ini');
    sqlStr := queryIni.ReadString('photoquery','photoquerysql','');
  finally
    queryIni.Destroy;
  end;

  if edtStuEmpNo.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+stuempNo+' like '+#39+'%'+edtStuEmpNo.Text+'%'+#39;
  if edtName.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+custName+' like '+#39+'%'+edtname.Text+'%'+#39;
  if cbb1.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+inDate+'='+#39+trim(cbb1.Text)+#39;
  if cbbDept.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+custDeptNo+'='+#39+cbbdept.KeyValue+#39;
  if cbbType.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+custType+'='+inttostr(cbbType.KeyValue);
  if cbbSpec.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+custSpecNo+'='+#39+cbbspec.KeyValue+#39;

  if rgPhoto.ItemIndex=0 then
    sqlStr:=sqlStr+' and photo.'+pPhotoDate+' is not null'
  else if rgPhoto.ItemIndex=1 then
    sqlStr:=sqlStr+' and photo.'+pPhotoDate+' is null'
  else
    sqlStr:=sqlStr+'';

    
  qryQuery.Close;
  qryQuery.SQL.Clear;
  qryQuery.SQL.Add(sqlStr);
  qryQuery.Prepared;
  //qryQuery.SQL.SaveToFile('123.txt');
  qryQuery.Open;
  if qryQuery.IsEmpty then
    ShowMessage('没有你指定条件的数据，请重新选择统计条件！');
end;

procedure TfrmPhotoQuery.btnOperClick(Sender: TObject);
begin
  queryData();
end;

procedure TfrmPhotoQuery.btnPhotoClick(Sender: TObject);
begin
  if dbgrdhDb.DataSource.DataSet.IsEmpty then
  begin
    ShowMessage('请先查询并选择一个要拍照的人员，然后再拍照');
    Exit;
  end;
  frmMain.iCustId:=dbgrdhDb.DataSource.DataSet.fieldbyname(custId).AsInteger;
  frmMain.ifPhoto:=True;
  Self.Close;
end;

procedure TfrmPhotoQuery.showPhoto(scustId: string);
var
  Fjpg: TJpegImage;
begin
  Fjpg:=nil;
  imgPhoto.Picture.Graphic:=nil;
  try
    Fjpg := TJpegImage.Create;
    Fjpg := getPhotoInfo(scustId);
    if Fjpg=nil then
      pnlphoto.Caption := '没有照片'
    else
      imgPhoto.Picture.Graphic:=Fjpg;
  finally
    Fjpg.Free;
  end;
end;

procedure TfrmPhotoQuery.dbgrdhDbCellClick(Column: TColumnEh);
begin
  if (qryQuery.IsEmpty or qryQuery.Active=False) then
    Exit;
  if dbgrdhDb.DataSource.DataSet.IsEmpty then
    Exit;
  showPhoto(dbgrdhDb.DataSource.DataSet.fieldbyname(custId).AsString);

end;

end.

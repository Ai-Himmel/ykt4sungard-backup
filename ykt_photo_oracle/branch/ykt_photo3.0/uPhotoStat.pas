unit uPhotoStat;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, DBGridEh, StdCtrls, Mask, DBCtrlsEh, DBLookupEh, ExtCtrls, DB,
  ADODB, ComCtrls, GridsEh, Buttons,IniFiles;

type
  TfrmPhotoStat = class(TForm)
    pnl1: TPanel;
    cbbType: TDBLookupComboboxEh;
    cbbDept: TDBLookupComboboxEh;
    cbbSpec: TDBLookupComboboxEh;
    cbbArea: TDBLookupComboboxEh;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    dtpBegin: TDateTimePicker;
    dtpEnd: TDateTimePicker;
    chkDate: TCheckBox;
    dbgrdhData: TDBGridEh;
    BitBtn1: TBitBtn;
    btnOper: TBitBtn;
    BitBtn2: TBitBtn;
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
    Label1: TLabel;
    Label6: TLabel;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnOperClick(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
  private
    { Private declarations }

    procedure fillCbb();
    procedure queryData();
  public
    { Public declarations }
  end;

var
  frmPhotoStat: TfrmPhotoStat;

implementation

uses Udm, uCommon;

{$R *.dfm}

procedure TfrmPhotoStat.BitBtn1Click(Sender: TObject);
begin
  Close;
end;

procedure TfrmPhotoStat.fillCbb;
var
  deptSql:string;
  specSql:string;
  typeSql:string;
  areaSql:string;
begin
  //deptSql:='select '+deptcode+','+deptName+' from (';
  //deptSql:=deptSql+'select '+sNull+' as '+deptcode+','+sNull+' as '+deptName+' from '+tbldept;
  //deptSql:=deptSql+'union select '+deptcode+','+deptName+' from '+tbldept+') t order by '+deptName;
  //specSql:='select '+specCode+','+specName+' from '+tblspec+' order by '+specName;
  //typeSql:='select '+typeNo+','+typeName+' from '+tblCutType+' order by '+typeName;
  //areaSql:='select '+areaNo+','+areaName+' from '+tblArea+' where '+areaFather+'=1';
  getFillQuerySql(deptSql,specSql,typeSql,areaSql);
  qryDept.Close;
  qryDept.SQL.Clear;
  qryDept.SQL.Add(deptSql);
  qryDept.Open;
  qryDept.Sort := deptName;
  cbbDept.ListField:=deptName;
  cbbDept.KeyField:=deptCode;

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

  qryArea.Close;
  qryArea.SQL.Clear;
  qryArea.SQL.Add(areaSql);
  qryArea.Open;
  qryArea.Sort := areaName;
  cbbArea.KeyField:=areaNo;
  cbbArea.ListField:=areaName;
end;

procedure TfrmPhotoStat.FormShow(Sender: TObject);
begin
  fillCbb();
  dtpEnd.Date:=Date();
  dtpBegin.Date:=Date();
  dbgrdhData.Columns[0].FieldName:=areaName;
  dbgrdhData.Columns[1].FieldName:=deptName;
  dbgrdhData.Columns[2].FieldName:=specName;
  dbgrdhData.Columns[3].FieldName:='totNum';
  dbgrdhData.Columns[4].FieldName:='photoNum';
  dbgrdhData.Columns[5].FieldName:='unPhotoNum';
  dbgrdhData.Columns[3].Footer.FieldName:='totNum';
  dbgrdhData.Columns[4].Footer.FieldName:='photoNum';
  dbgrdhData.Columns[5].Footer.FieldName:='unPhotoNum';

end;

procedure TfrmPhotoStat.btnOperClick(Sender: TObject);
begin
  if (chkDate.Checked)and(dtpBegin.Date>dtpEnd.Date) then
  begin
    showmessage('你选择的开始日期大于结束日期，请从新选择！');
    exit;
  end;
  queryData();
end;

procedure TfrmPhotoStat.queryData;
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
    sqlStr := queryIni.ReadString('photostat','photostatsql','');
  finally
    queryIni.Destroy;
  end;
  if chkDate.Checked then
  begin
    sqlStr:=sqlStr+' and photo.'+pPhotoDate+'>='+#39+formatdatetime('yyyymmdd',dtpBegin.Date)+#39;
    sqlStr:=sqlStr+' and photo.'+pPhotoDate+'<='+#39+formatdatetime('yyyymmdd',dtpEnd.Date)+#39;
  end;
  if cbbArea.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+custArea+'='+inttostr(cbbArea.KeyValue);
  if cbbDept.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+custDeptNo+'='+#39+cbbdept.KeyValue+#39;
  if cbbType.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+custType+'='+inttostr(cbbType.KeyValue);
  if cbbSpec.Text<>'' then
    sqlStr:=sqlStr+' and cust.'+custSpecNo+'='+#39+cbbspec.KeyValue+#39;

  sqlStr:=sqlStr+' group by area.'+areaName+',dept.'+deptName+', spec.'+specName;
  sqlStr:=sqlStr+' order by area.'+areaName;
  qryQuery.Close;
  qryQuery.SQL.Clear;
  qryQuery.SQL.Add(sqlStr);
  qryQuery.Open;
  if qryQuery.IsEmpty then
    ShowMessage('没有你指定条件的数据，请重新选择统计条件！');
end;

procedure TfrmPhotoStat.BitBtn2Click(Sender: TObject);
begin
  if qryQuery.IsEmpty then
  begin
    ShowMessage('请先查询数据，然后再导出！');
    Exit;
  end;
  ExportData(SaveDialog1,dbgrdhData);
end;

end.

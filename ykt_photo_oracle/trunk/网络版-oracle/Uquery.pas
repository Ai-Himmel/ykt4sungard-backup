unit Uquery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, Grids, DBGridEh, StdCtrls, Db, ADODB, PrnDbgeh,DBGridEhImpExp,
  ComCtrls;

type
  TQueryForm = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    Panel3: TPanel;
    DBGridEh1: TDBGridEh;
    btnQuery: TButton;
    btnExport: TButton;
    btnPrint: TButton;
    btnExit: TButton;
    ADOQuery1: TADOQuery;
    DataSource1: TDataSource;
    PrintDBGridEh1: TPrintDBGridEh;
    Label1: TLabel;
    edtNo: TEdit;
    Label2: TLabel;
    edtName: TEdit;
    SaveDialog1: TSaveDialog;
    Label3: TLabel;
    cbdept: TComboBox;
    Label4: TLabel;
    cbCode: TComboBox;
    Label5: TLabel;
    cbnj: TComboBox;
    Button1: TButton;
    Label7: TLabel;
    cbtype: TComboBox;
    grPic: TRadioGroup;
    Label8: TLabel;
    qryFilltypeData: TADOQuery;
    qryFillcodeData: TADOQuery;
    qryFilldeptData: TADOQuery;
    qryFillnjData: TADOQuery;
    Label9: TLabel;
    edttitle: TEdit;
    ProgressBar1: TProgressBar;
    lbl1: TLabel;
    dtpBeginDate: TDateTimePicker;
    dtpEndDate: TDateTimePicker;
    lbl2: TLabel;
    procedure btnExitClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnExportClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
    procedure filltypeData;  //类别
    procedure filldeptdata;    //学院
    procedure fillcodedata;      //系所
    procedure fillnjdata;          //年级

  public
    { Public declarations }
  end;

var
  QueryForm: TQueryForm;

implementation

uses Udb, UtConfigs;

{$R *.DFM}

procedure TQueryForm.btnExitClick(Sender: TObject);
begin
  if qryFilltypeData.Active=true then
    if qryFilltypeData.IsEmpty=true then
    begin
      qryFilltypeData.Recordset.Close;
      qryFilltypeData.Close;
    end;
  if qryFillcodeData.Active=true then
    if qryFillcodeData.IsEmpty=true then
    begin
      qryFillcodeData.Recordset.Close;
      qryFillcodeData.Close;
    end;
  if qryFilldeptData.Active=true then
    if qryFilldeptData.IsEmpty=true then
    begin
      qryFilldeptData.Recordset.Close;
      qryFilldeptData.Close;
    end;
  if qryFillnjData.Active=true then
    if qryFillnjData.IsEmpty=true then
    begin
      qryFillnjData.Recordset.Close;
      qryFillnjData.Close;
    end;
  if ADOQuery1.Active=true then
    if ADOQuery1.IsEmpty=true then
    begin
      ADOQuery1.Recordset.Close;
      ADOQuery1.Close;
    end;
  close;
end;

procedure TQueryForm.btnPrintClick(Sender: TObject);
begin
  if dm.judgelimit(dm.soper,Mdl_Print)=false then   // 原先是 1 (Mdl_Query),
  begin                                             // 可以看出无意义的数字容易出错
    showmessage('你没有打印的权限，请找管理人员开通该权限！');
    exit;
  end;
  PrintDBGridEh1.Preview;
end;

procedure TQueryForm.btnQueryClick(Sender: TObject);
var
  sqlstr:string;
begin
  if grpic.ItemIndex=1 then
  begin
    sqlstr:='select '+filename+','+cuttype+','+stuempno+','+stuempname+','+deptname+','+scode+','+sexname+','
      +opername+','+id2+','+indate+','+addpersondate+' from '+PhotoTableName+' where '+filename+' is null';
    if trim(cbtype.Text)<>'' then
      sqlstr:=sqlstr+' and '+cuttype+'='+#39+trim(cbtype.text)+#39;
    if trim(cbdept.Text)<>'' then
      sqlstr:=sqlstr+' and '+deptname+'='+#39+trim(cbdept.text)+#39;
    if trim(cbcode.Text)<>'' then
      sqlstr:=sqlstr+' and '+scode+'='+#39+trim(cbcode.text)+#39;
    if trim(cbnj.text)<>'' then
      sqlstr:=sqlstr+' and '+indate+'='+#39+trim(cbnj.text)+#39;
    if trim(edtno.text)<>'' then
      sqlstr:=sqlstr+' and '+stuempno+'='+#39+trim(edtno.text)+#39;
    if trim(edtname.text)<>'' then
      sqlstr:=sqlstr+' and '+stuempname+' like '+#39+'%'+trim(edtname.text)+'%'+#39;
  end;
  if grpic.ItemIndex=0 then
  begin
    sqlstr:='select '+filename+','+cuttype+','+stuempno+','+stuempname+','+deptname+','+scode+','+sexname+','
      +opername+','+id2+','+indate+','+addpersondate+' from '+PhotoTableName+' where '+filename+' is not null';
    if trim(cbtype.Text)<>'' then
      sqlstr:=sqlstr+' and '+cuttype+'='+#39+trim(cbtype.text)+#39;
    if trim(cbdept.Text)<>'' then
      sqlstr:=sqlstr+' and '+deptname+'='+#39+trim(cbdept.text)+#39;
    if trim(cbcode.Text)<>'' then
      sqlstr:=sqlstr+' and '+scode+'='+#39+trim(cbcode.text)+#39;
    if trim(cbnj.text)<>'' then
      sqlstr:=sqlstr+' and '+indate+'='+#39+trim(cbnj.text)+#39;
    if trim(edtno.text)<>'' then
      sqlstr:=sqlstr+' and '+stuempno+'='+#39+trim(edtno.text)+#39;
    if trim(edtname.text)<>'' then
      sqlstr:=sqlstr+' and '+stuempname+' like '+#39+'%'+trim(edtname.text)+'%'+#39;
  end;
  if grpic.ItemIndex=2 then
  begin
    sqlstr:='select '+filename+','+cuttype+','+stuempno+','+stuempname+','+deptname+','+scode+','+sexname+','
      +opername+','+id2+','+indate+','+addpersondate+' from '+PhotoTableName+' where '+ addpersondate +'>='
      +#39+formatdatetime('yyyy-mm-dd',dtpBeginDate.Date)+#39+' and '+ addpersondate+'<='
      +#39+formatdatetime('yyyy-mm-dd',dtpEndDate.Date)+#39;
    if trim(cbtype.Text)<>'' then
      sqlstr:=sqlstr+' and '+cuttype+'='+#39+trim(cbtype.text)+#39;
    if trim(cbdept.Text)<>'' then
      sqlstr:=sqlstr+' and '+deptname+'='+#39+trim(cbdept.text)+#39;
    if trim(cbcode.Text)<>'' then
      sqlstr:=sqlstr+' and '+scode+'='+#39+trim(cbcode.text)+#39;
    if trim(cbnj.text)<>'' then
      sqlstr:=sqlstr+' and '+indate+'='+#39+trim(cbnj.text)+#39;
    if trim(edtno.text)<>'' then
      sqlstr:=sqlstr+' and '+stuempno+'='+#39+trim(edtno.text)+#39;
    if trim(edtname.text)<>'' then
      sqlstr:=sqlstr+' and '+stuempname+' like '+#39+'%'+trim(edtname.text)+'%'+#39;
  end;
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add(sqlstr);
  ADOQuery1.Prepared;
  ADOQuery1.Open;
  if ADOQuery1.IsEmpty=true then
  begin
    ADOQuery1.Recordset.Close;
    ADOQuery1.close;
    showmessage('没有你要的记录，请从新指定查询条件！');
    exit;
  end;
end;

procedure TQueryForm.btnExportClick(Sender: TObject);
var
  ExpClass:TDBGridEhExportClass;
  Ext:String;
begin
  if dm.judgelimit(dm.soper,Mdl_ExpData)=false then
  begin
    showmessage('你没有导出的权限，请找管理人员开通该权限！');
    exit;
  end;
  if trim(edttitle.Text)='' then
  begin
    showmessage('请输入要保存的文件名！');
    Exit;
  end;
  try
  begin
    SaveDialog1.FileName := edttitle.Text;
    DBGridEh1.Selection.SelectAll ;
    if SaveDialog1.Execute then
    begin
     case SaveDialog1.FilterIndex of
        1: begin ExpClass := TDBGridEhExportAsText; Ext := 'txt'; end;
        5: begin ExpClass := TDBGridEhExportAsCSV; Ext := 'csv'; end;
        2: begin ExpClass := TDBGridEhExportAsHTML; Ext := 'htm'; end;
        3: begin ExpClass := TDBGridEhExportAsRTF; Ext := 'rtf'; end;
        4: begin ExpClass := TDBGridEhExportAsXLS; Ext := 'xls'; end;
      else
        ExpClass := nil; Ext := '';
      end;
        if ExpClass <> nil then
      begin
        if UpperCase(Copy(SaveDialog1.FileName,Length(SaveDialog1.FileName)-2,3)) <>  UpperCase(Ext) then
          SaveDialog1.FileName := SaveDialog1.FileName + '.' + Ext;
        SaveDBGridEhToExportFile(ExpClass,DBGridEh1, SaveDialog1.FileName,False);
      end;
    end;
   end ;
   except
     showmessage('导出失败！请检查...');
   end;
end;

procedure TQueryForm.Button1Click(Sender: TObject);
var
  sqlstr:string;
begin
  sqlstr:='select '+cuttype+','+stuempno+','+stuempname+','+deptname+','+scode+','+sexname+','+id2+','+indate+' from '+PhotoTableName;
  sqlstr:=sqlstr+' where (length('+id2+')<>18 and length('+id2+')<>15) or '+id2+' is null';
  if trim(cbtype.Text)<>'' then
    sqlstr:=sqlstr+' and '+cuttype+'='+#39+trim(cbtype.text)+#39;
  if trim(cbdept.Text)<>'' then
    sqlstr:=sqlstr+' and '+deptname+'='+#39+trim(cbdept.text)+#39;
  if trim(cbcode.Text)<>'' then
    sqlstr:=sqlstr+' and '+scode+'='+#39+trim(cbcode.text)+#39;
  if trim(cbnj.text)<>'' then
    sqlstr:=sqlstr+' and '+indate+'='+#39+trim(cbnj.text)+#39;
  if trim(edtno.text)<>'' then
    sqlstr:=sqlstr+' and '+stuempno+'='+#39+trim(edtno.text)+#39;
  if trim(edtname.text)<>'' then
    sqlstr:=sqlstr+' and '+stuempname+' like '+#39+'%'+trim(edtname.text)+'%'+#39;
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add(sqlstr);
  ADOQuery1.Prepared;
  ADOQuery1.Open;
  if ADOQuery1.IsEmpty=true then
  begin
    ADOQuery1.Recordset.Close;
    ADOQuery1.close;
    showmessage('没有你要的记录，请从新指定查询条件！');
    exit;
  end;
end;

//填充数据
procedure TQueryForm.filltypeData;
var
  sqlstr:string;
begin
  sqlstr:='select distinct '+cuttype+' from '+PhotoTableName+' order by '+cuttype+' desc';
  qryFilltypeData.Close;
  qryFilltypeData.SQL.clear;
  qryFilltypeData.SQL.Add(sqlstr);
  qryFilltypeData.Open;
  if qryFilltypeData.IsEmpty=true then
  begin
    qryFilltypeData.Recordset.Close;
    qryFilltypeData.Close;
    exit;
  end;
  qryFilltypeData.First;
  cbtype.Items.Clear;
  while not qryFilltypeData.Eof do
  begin
    cbtype.Items.Add(qryFilltypeData.fieldbyname(cuttype).asstring);
    qryFilltypeData.Next;
  end;
end;

procedure TQueryForm.fillcodedata;
var
  sqlstr:string;
begin
  sqlstr:='select distinct '+scode+' from '+PhotoTableName+' order by '+scode+' desc';
  qryFillcodeData.Close;
  qryFillcodeData.SQL.clear;
  qryFillcodeData.SQL.Add(sqlstr);
  qryFillcodeData.Open;
  if qryFillcodeData.IsEmpty=true then
  begin
    qryFillcodeData.Recordset.Close;
    qryFillcodeData.Close;
    exit;
  end;
  qryFillcodeData.First;
  cbcode.Items.Clear;
  while not qryFillcodeData.Eof do
  begin
    cbcode.Items.Add(qryFillcodeData.fieldbyname(scode).asstring);
    qryFillcodeData.Next;
  end;
end;

procedure TQueryForm.filldeptdata;
var
  sqlstr:string;
begin
  sqlstr:='select distinct '+deptname+' from '+PhotoTableName+' order by '+deptname+' desc';
  qryFilldeptData.Close;
  qryFilldeptData.SQL.clear;
  qryFilldeptData.SQL.Add(sqlstr);
  qryFilldeptData.Open;
  if qryFilldeptData.IsEmpty=true then
  begin
    qryFilldeptData.Recordset.Close;
    qryFilldeptData.Close;
    exit;
  end;
  qryFilldeptData.First;
  cbdept.Items.Clear;
  while not qryFilldeptData.Eof do
  begin
    cbdept.Items.Add(qryFilldeptData.fieldbyname(deptname).asstring);
    qryFilldeptData.Next;
  end;
end;

procedure TQueryForm.fillnjdata;
var
  sqlstr:string;
begin
  sqlstr:='select distinct '+indate+' from '+PhotoTableName+' order by '+indate+' desc';
  qryFillnjData.Close;
  qryFillnjData.SQL.clear;
  qryFillnjData.SQL.Add(sqlstr);
  qryFillnjData.Open;
  if qryFillnjData.IsEmpty=true then
  begin
    qryFillnjData.Recordset.Close;
    qryFillnjData.Close;
    exit;
  end;
  qryFillnjData.First;
  cbnj.Items.Clear;
  while not qryFillnjData.Eof do
  begin
    cbnj.Items.Add(qryFillnjData.fieldbyname(indate).asstring);
    qryFillnjData.Next;
  end;
end;

procedure TQueryForm.FormShow(Sender: TObject);
begin
  filltypeData;
  fillcodedata;
  filldeptdata;
  fillnjdata;
  dtpBeginDate.Date:=Date;
  dtpEndDate.Date:=Date;
end;

end.

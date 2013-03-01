unit uCommon;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,DBGridEh,
  Dialogs, StdCtrls, ExtCtrls, INIFiles, ADODB,DB, AES,jpeg,DBGridEhImpExp,
  ShellAPI;
const
  // Ȩ�޹���, ģ���
  Mdl_ifUse = 0;        //�Ƿ����
  Mdl_limit = 1;        //Ȩ�޹���
  Mdl_photoStat = 2;    //����ͳ��
  Mdl_photoQuery = 3;   //���ղ�ѯ
  Mdl_import = 4;       //������Ƭ
  Mdl_export = 5;       //������Ƭ
  Mdl_addCust = 6;      //�����Ա��Ϣ
  Mdl_EditCust = 7;     //�޸���Ա��Ϣ

  Mdl_stuPrint = 8;     //ѧ������ӡ
  Mdl_empPrint = 9;     //��ʦ����ӡ
  Mdl_delphoto = 10;    //ɾ����Ƭ
  mdl_savephoto = 11;   //������Ƭ
  mdl_custImport = 12;  //��Ա���
  mdl_photocopy = 13;   //��Ƭ����

  selectH = 316;
  selectW = 237;
  imgW = 420;

var
  useRemoteSoft:Boolean;      //ʹ�õ�����Զ���������,ʹ��Ϊtrue
  {������ԿΪksykt123}
  ifconn:Boolean;             //�Ƿ����������ݿ�
  apppath:string ;            //ϵͳ�ļ�·��
  connStr:string ;            //���ݿ������ַ���
  dbName:string;              //���ݿ�����
  //dbprovider:string;          //���ݿ����Ӵ�
  datasource:string;          //����Դ����
  dbuId :string;              //��¼���ݿ��û���
  dbPwd :string;              //��¼���ݿ�����

  tblPhoto:String ;		        //��Ƭ��
  tblDept:String ;	          //���ű�
  tblSpec:String ;		        //רҵ��
  tblDict:String ;			      //�����ֵ�
  tblCust:string ;            //�ͻ���
  tblArea:string;             //�����
  tblCutType:string;          //�ͻ�����
  tblLimit:string;            //Ȩ�ޱ�
  //tblFeeType:string;          //�շ�����
  //tblSysKey:string;           //ϵͳ��ֵ��
  //tblCard : string;           //����
  
  custId:String ;		          //�ͻ���
  stuempNo:string;            //ѧ����
  custName:String ;		        //����
  custType:string;            //��Ա���
  custState:string;           //�ͻ�״̬
  custArea:string;            //�ͻ���������
  custSex:String ;			      //�Ա�
  custCardId:String ;			    //���֤��
  custDeptNo:string;          //�ͻ����ڲ��ź�
  custSpecNo:string;          //�ͻ�����רҵ��
  custRegTime:string;         //�ͻ�ע��ʱ��
  custFeeType:string;         //�շ����
  classNo:string;             //�༶
  inDate:string;              //�꼶

  pPhoto:string;              //��Ƭ
  //PMinPhoto:string;           //С��Ƭ
  pIfCard:String ;		        //�Ƿ��ƿ�
  pCardDate:String ;		      //�ƿ�����
  pCardTime:string;           //�ƿ�ʱ��
  pPhotoDate:String ;		      //��������
  pPhotoTime:String ;		      //����ʱ��
  pPhotoDTime:STRING;         //���վ�ȷʱ�䣬������
  res_1:String ;		          //Ԥ���ֶ�
  res_2:String ;
  res_3:String ;

  lmtOperCode:String ;        //����Ա����
  lmtOperName:String ;        //����Ա����
  lmtBeginDate:String ;       //��Чʱ��
  lmtEndDate:String ;         //ʵЧʱ��
  lmtpwd:String ;             //����
  lmtLimit:String ;           //Ȩ��
  lmtEnabled:String ;         //�Ƿ����

  deptCode:String ;		        //���Ŵ���
  deptName:String ;		        //��������
  deptParent:String ;	        //�������
  deptLevel:String ;	        //���ż���

  specCode:string;            //רҵ����
  specName:string;            //רҵ����

  dictNo:string;              //�ֵ���
  dictValue:string;           //�ֵ��ӱ��
  dictCaption:string;         //�ֵ�����

  areaNo:string;              //������
  areaName:string;            //��������
  areaFather:string;          //���򸸱��

  typeNo:string;              //�����
  typeName:string;            //�������

  cpIfCard:string;            //��Ƭ��ӡ����ʾ�Ƿ��ƿ�
  cpCardDate:string;          //�ƿ�����
  cpCardTime:string;          //�ƿ�ʱ��


  loginLimit:string;          //��¼��ͻ���Ȩ��
  loginName:string;           //��¼��
  loginPwd:string;            //��¼����
  
  feeFeeType:string;          //������
  {feeFeeName:string;          //�������

  keyCode:string;             //��ֵ����
  keyName:string;             //��ֵ����
  keyValue:string;            //��ֵ����
  keyMaxValue:string;         //����ֵ
  keyCustId:string;           //�ͻ����ڼ�ֵ���еĴ���

  cardCardId:string;          //����
  cardStateId:string;         //��״̬
  cardCustId:string;          //�ͻ���
  }
  photopath :string;          //��Ƭ����λ��
  photopre:string;            //��Ƭǰ׺
  diskpath:string;            //����λ��

  rotate:Boolean;             //�Ƿ���ת
  angle:Integer;              //��ת�Ƕ�

  minWidth:Integer;           //С��Ƭ�Ŀ��
  minHeight:Integer;          //С��Ƭ�ĸ߶�

  //ȡ����������ʾ��λ������
  ve_visible:Boolean;
  veL_top:Integer;
  veL_left:Integer;
  veL_height:Integer;

  veR_top:Integer;
  veR_left:Integer;
  veR_height:Integer;

  veT_top:Integer;
  veT_left:Integer;
  veT_width:Integer;

  veB_top:Integer;
  veB_left:Integer;
  veB_width:Integer;

  veA_top:Integer;
  veA_left:Integer;
  veA_width:Integer;


  procedure getphotoconfigs;
  procedure getViewBoxConf;
  procedure AddData(cbb:TComboBox;sqlstr:string);
  function subString(ssname:string;str:string;posi:string):string;
  function sqlExec(sqlstr:string;rname:string): string;
  function getDeptName(sDeptCode:string):string;
  function getSName(ssCode:string):string;
  function getAreaName(sareaNo:string): String;
  function getStatesName(StateNo:string): String;
  function getTypeName(stypeNo:string): String;
  //function getCardNo(custId:string):string;

  function queryBaseInfoSql(sstuempNo:string;sareaId:string;scustId:string): string;
  function getPhotoInfo(scustId: string): TJpegImage;

  function getJpgNo(jpgName:string):string;

  function ExportData(SaveDialog1: TSaveDialog;DBGridEh1: TDBGridEh):Boolean;

  function haveStuEmpNo(sstuEmpNo:string): Integer;

  function qryOperSql(soperCode:string;spwd:string): string;

  function judgelimit(oper: string; code:integer):boolean;

  procedure insertPhotoData(sCustId, sStuempNo: string);

  //function getMaxCustId():Integer;

  function addCustInfo(sstuempNo,sname,stype,sArea,scardId,sDept,sSpec,sFeeType:string):Boolean;

  procedure delFileBat(filePath,fileName:string);

  procedure getFillQuerySql(var deptSql,specSql,typeSql,areaSql:string);

  function getDbTime: string;

  function photoHaveRecord(sstuEmpNo:string):string;

  function updatePhoto(oldNo,newNo:string):Integer;

  function insertPhoto(incustId,oldNo,newNo:string):Integer;

implementation

uses uDM, mainUnit;
{-------------------------------------------------------------------------------
  ������:    getphotoconfigs�õ���Ƭ���е������ļ�
  ����:      ����ΰ
  ����:      2006.02.24
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure getphotoconfigs;
const
  connString = 'Provider=%s;Data Source=%s;User ID=%s;Password=%s';
var
  photoinifile:TIniFile;
  dbprovider :string;
begin
  photoinifile := nil;
  if FileExists(apppath+'photo.ini') = false then
  begin
    Application.MessageBox('ϵͳ�����ļ��Ѿ����ƻ�������ϵͳ����Ա��ϵ��',
      'ϵͳ����', mb_ok + mb_iconerror);
    Application.Terminate;
  end;
  try
    photoinifile := TIniFile.Create(apppath+'photo.ini');

    //connStr := DecryptString(photoinifile.ReadString('connection','conn',''),'ksykt123');
    dbName :=  photoinifile.ReadString('connection','dbtype','');
    dbprovider := photoinifile.ReadString('connection','dbprovider','');
    datasource := photoinifile.ReadString('connection','datasource','');
    dbuId := Trim(DecryptString(photoinifile.ReadString('connection','dbuid',''),'ksykt123'));
    dbPwd := Trim(DecryptString(photoinifile.ReadString('connection','dbpwd',''),'ksykt123'));
    //dbuId := photoinifile.ReadString('connection','dbuid','');
    //dbPwd := photoinifile.ReadString('connection','dbpwd','');
    //Provider=MSDASQL.1;Password=kingstar;Persist Security Info=True;User ID=ykt_cur;Data Source=yktv3db
    if (Trim(dbName)='ORACLE') then
      dbprovider := 'OraOLEDB.Oracle.1'
    else if (Trim(dbName)='DB2') then
      dbprovider := 'MSDASQL.1'
    else if (Trim(dbName)='MYSQL') then
      dbprovider := 'MySQLProv'
    else
    begin
      ShowMessage('��鿴��������ļ���ȷ�����ݿ����Ƿ���ȷ��');
      Exit;
    end;

    connStr := Format(connString,[dbprovider,datasource,dbuId,dbPwd]);
    
    tblPhoto := photoinifile.ReadString('tablename','tblphoto','');
    tblDept := photoinifile.ReadString('tablename','tbldept','');
    tblSpec := photoinifile.ReadString('tablename','tblspec','');
    tblDict := photoinifile.ReadString('tablename','tbldict','');
    tblCust := photoinifile.ReadString('tablename','tblcust','');
    tbllimit := photoinifile.ReadString('tablename','tbllimit','');
    tblArea := photoinifile.ReadString('tablename','tblArea','');
    tblCutType := photoinifile.ReadString('tablename','tblCutType','');
    //tblFeeType := photoinifile.ReadString('tablename','tblFeeType','');
    //tblSysKey := photoinifile.ReadString('tablename','tblSysKey','');
    //tblCard := photoinifile.ReadString('tablename','tblCard','');

    custId := photoinifile.ReadString('fieldname','custId','');
    stuempNo := photoinifile.ReadString('fieldname','stuempNo','');
    custName := photoinifile.ReadString('fieldname','custName','');
    custType := photoinifile.ReadString('fieldname','custType','');
    custState := photoinifile.ReadString('fieldname','custState','');
    custArea := photoinifile.ReadString('fieldname','custArea','');
    custSex := photoinifile.ReadString('fieldname','custSex','');
    custcardId := photoinifile.ReadString('fieldname','custcardId','');
    custDeptNo := photoinifile.ReadString('fieldname','custDeptNo','');
    custSpecNo := photoinifile.ReadString('fieldname','custSpecNo','');
    custRegTime := photoinifile.ReadString('fieldname','custRegTime','');
    custFeeType := photoinifile.ReadString('fieldname','custFeeType','');
    classNo := photoinifile.ReadString('fieldname','classNo','');
    inDate := photoinifile.ReadString('fieldname','inDate','');

    pPhoto := photoinifile.ReadString('fieldname','pPhoto','');
    //PMinPhoto := photoinifile.ReadString('fieldname','pMinPhoto','');
    pIfCard := photoinifile.ReadString('fieldname','pIfCard','');
    pCardDate := photoinifile.ReadString('fieldname','pCardDate','');
    pCardTime := photoinifile.ReadString('fieldname','pCardTime','');
    pPhotoDate := photoinifile.ReadString('fieldname','pPhotoDate','');
    pPhotoTime := photoinifile.ReadString('fieldname','pPhotoTime','');
    pPhotoDTime := photoinifile.ReadString('fieldname','pPhotoDTime','');
    res_1 := photoinifile.ReadString('fieldname','res_1','');
    res_2 := photoinifile.ReadString('fieldname','res_2','');
    res_3 := photoinifile.ReadString('fieldname','res_3','');

    lmtOperCode := photoinifile.ReadString('fieldname','lmtOperCode','');
    lmtOperName := photoinifile.ReadString('fieldname','lmtOperName','');
    lmtBeginDate := photoinifile.ReadString('fieldname','lmtBeginDate','');
    lmtEndDate := photoinifile.ReadString('fieldname','lmtEndDate','');
    lmtpwd := photoinifile.ReadString('fieldname','lmtpwd','');
    lmtLimit := photoinifile.ReadString('fieldname','lmtLimit','');
    lmtEnabled := photoinifile.ReadString('fieldname','lmtEnabled','');

    deptCode := photoinifile.ReadString('fieldname','deptCode','');
    deptName := photoinifile.ReadString('fieldname','deptName','');
    deptParent := photoinifile.ReadString('fieldname','deptParent','');
    deptLevel := photoinifile.ReadString('fieldname','deptLevel','');

    specCode := photoinifile.ReadString('fieldname','specCode','');
    specName := photoinifile.ReadString('fieldname','specName','');

    dictNo := photoinifile.ReadString('fieldname','dictNo','');
    dictValue := photoinifile.ReadString('fieldname','dictValue','');
    dictCaption := photoinifile.ReadString('fieldname','dictCaption','');

    areaNo := photoinifile.ReadString('fieldname','areaNo','');
    areaName := photoinifile.ReadString('fieldname','areaName','');
    areaFather := photoinifile.ReadString('fieldname','areaFather','');
    
    typeName := photoinifile.ReadString('fieldname','typeName','');
    typeNo := photoinifile.ReadString('fieldname','typeNo','');
    
    feeFeeType := photoinifile.ReadString('fieldname','feeFeeType','');
    {feeFeeName := photoinifile.ReadString('fieldname','feeFeeName','');
    
    keyCode := photoinifile.ReadString('fieldname','keyCode','');
    keyName := photoinifile.ReadString('fieldname','keyName','');
    keyValue := photoinifile.ReadString('fieldname','keyValue','');
    keyMaxValue := photoinifile.ReadString('fieldname','keyMaxValue','');
    keyCustId := photoinifile.ReadString('fieldname','keyCustId','');

    cardCardId := photoinifile.ReadString('fieldname','cardCardId','');
    cardStateId := photoinifile.ReadString('fieldname','cardStateId','');
    cardCustId := photoinifile.ReadString('fieldname','cardCustId','');
    }
    useRemoteSoft := photoinifile.ReadBool('remote','remotecapture',True);

    photopath :=photoinifile.ReadString('getphoto','photopath','');
    photopre:=photoinifile.ReadString('getphoto','photopre','');
    diskpath:=photoinifile.ReadString('getphoto','diskpath','');

    rotate := photoinifile.ReadBool('photorotate','rotate',True);
    angle := photoinifile.ReadInteger('photorotate','angle',0);

    minWidth := photoinifile.ReadInteger('minphoto','width',0);
    minHeight := photoinifile.ReadInteger('minphoto','height',0);
    if (minWidth/minHeight)<>0.75 then
      minHeight := Round(minWidth*4/3 + 1);
  finally
    photoinifile.Destroy;
  end;
end;

procedure getViewBoxConf;
var
  viewConfFile:TIniFile;
begin
  viewConfFile := nil;
  try
    viewConfFile := TIniFile.Create(apppath+'photo.ini');
    ve_visible := viewConfFile.ReadBool('photoviewbox','visible',False);
    if ve_visible=False then
      Exit;
    veL_top := viewConfFile.ReadInteger('photoviewbox','lneL_top',0);
    veL_left := viewConfFile.ReadInteger('photoviewbox','lneL_left',0);
    veL_height := viewConfFile.ReadInteger('photoviewbox','lneL_height',0);

    veR_top := viewConfFile.ReadInteger('photoviewbox','lneR_top',0);
    veR_left := viewConfFile.ReadInteger('photoviewbox','lneR_left',0);
    veR_height := viewConfFile.ReadInteger('photoviewbox','lneR_height',0);

    veT_top := viewConfFile.ReadInteger('photoviewbox','lneT_top',0);
    veT_left := viewConfFile.ReadInteger('photoviewbox','lneT_left',0);
    veT_width := viewConfFile.ReadInteger('photoviewbox','lneT_width',0);

    veB_top := viewConfFile.ReadInteger('photoviewbox','lneB_top',0);
    veB_left := viewConfFile.ReadInteger('photoviewbox','lneB_left',0);
    veB_width := viewConfFile.ReadInteger('photoviewbox','lneB_width',0);

    veA_top := viewConfFile.ReadInteger('photoviewbox','lneA_top',0);
    veA_left := viewConfFile.ReadInteger('photoviewbox','lneA_left',0);
    veA_width := viewConfFile.ReadInteger('photoviewbox','lneA_width',0);
  finally
    viewConfFile.Destroy;
  end;
end;
{-------------------------------------------------------------------------------
  ������:    AddData�������б����������
  ����:      ����ΰ
  ����:      2006.03.03
  ����:      cbb:TComboBox;sqlstr:string
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure AddData(cbb:TComboBox;sqlstr:string);
var
  qryExecSQL:TADOQuery;
begin
  qryExecSQL := nil;//frmdm.qryQuery;
  try
    qryExecSQL := TADOQuery.Create(Application.MainForm);
    qryExecSQL.Connection := frmdm.conn;
    //qryExecSQL.LockType := ltUnspecified;
    cbb.Items.Clear;
    cbb.Items.Add('');
    qryExecSQL.Close;
    qryExecSQL.sql.Clear;
    qryExecSQL.SQL.Add(sqlstr);
    qryExecSQL.Prepared;
    qryExecSQL.Open;
    if not qryExecSQL.IsEmpty then
    begin
      qryExecSQL.First;
      while not qryExecSQL.Eof do
      begin
        cbb.Items.Add(qryExecSQL.Fields[1].Text+'-'+qryexecSql.Fields[0].Text);
        qryExecSQL.Next;
      end;
      //cbb.Sorted := True;
    end;
  finally
    qryExecSQL.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    subString
  ����:      hanjiwei
  ����:      2007.01.16
  ����:      ssname:string;str:string;posi:string�ַ������ָ��ַ�������ȡ����
  ����ֵ:    string
-------------------------------------------------------------------------------}
function subString(ssname:string;str:string;posi:string):string;
begin
  if LowerCase(posi)='l' then
    Result := Copy(ssname,0,Pos(str,ssname)-1);
  if LowerCase(posi)='r' then
    Result := Copy(ssname,Pos(str,ssname)+1,Length(ssname));
end;

{-------------------------------------------------------------------------------
  ������:    getDeptName���ݲ��ű��뷵�ز�������
  ����:      ����ΰ
  ����:      2006.03.01
  ����:      sDeptCode:string
  ����ֵ:    string
-------------------------------------------------------------------------------}
function getDeptName(sDeptCode:string):string;
var
  sqlstr:string;
begin
  sqlstr := 'select '+deptname+' from '+tblDept+' where '+deptcode+'='+QuotedStr(sDeptCode);
  Result := sqlExec(sqlstr,deptname);
end;

{-------------------------------------------------------------------------------
  ������:    getSName����רҵ���뷵��רҵ����
  ����:      ����ΰ
  ����:      2006.03.01
  ����:      ssCode:string
  ����ֵ:    string
-------------------------------------------------------------------------------}
function getSName(ssCode:string):string;
var
  sqlstr:string;
begin
  sqlstr := 'select '+specName+' from '+tblSpec+' where '+specCode+'='+QuotedStr(ssCode);
  Result := sqlExec(sqlstr,specName);
end;

{-------------------------------------------------------------------------------
  ������:    sqlExec���ݴ��������ص����ƣ������ء��������ĺ����޸�Ϊ���ô�
  ����:      ����ΰ
  ����:      2006.03.03
  ����:      sqlstr:string;rname:string
  ����ֵ:    string
-------------------------------------------------------------------------------}
function sqlExec(sqlstr:string;rname:string): string;
var
  tempQuery:TADOQuery;
begin
  tempQuery := nil;
  try
    tempQuery := TADOQuery.Create(nil);
    tempQuery.Connection := frmDM.conn;
    tempQuery.Close;
    tempQuery.SQL.Clear;
    tempQuery.SQL.Add(sqlstr);
    try
      tempQuery.Open;
    if not tempQuery.IsEmpty then
      Result := tempQuery.fieldbyname(rname).AsString
    else
      Result := '';
    except
      Result := '';
    end;
  finally
    tempQuery.Destroy;
  end;
end; 
{-------------------------------------------------------------------------------
  ������:    getAreaName����������ȡ����������
  ����:      hanjiwei
  ����:      2007.01.15
  ����:      areaNo:string
  ����ֵ:    String
-------------------------------------------------------------------------------}
function getAreaName(sareaNo:string): String;
var
  sqlstr:string;
begin
  sqlstr := 'select '+areaName+' from '+tblArea+' where '+areaFather+'=1 and ';
  if sareaNo='' then
    sqlstr := sqlstr+areaNo+'=1'
  else
    sqlstr := sqlstr+areaNo+'='+sareaNo;
  Result := sqlExec(sqlstr,areaName);
end;

{-------------------------------------------------------------------------------
  ������:    getStatesNameȡ��״̬����
  ����:      hanjiwei
  ����:      2007.01.15
  ����:      StateNo:string
  ����ֵ:    String
-------------------------------------------------------------------------------}
function getStatesName(StateNo:string): String;
var
  sqlstr:string;
begin
  sqlstr := 'select '+dictCaption+' from '+tblDict+' where '+dictNo+'=70 and ';
  sqlstr := sqlstr+dictValue+'='+QuotedStr(StateNo);
  Result := sqlExec(sqlstr,dictCaption);
end;

{-------------------------------------------------------------------------------
  ������:    getTypeNameȡ���������
  ����:      hanjiwei
  ����:      2007.01.15
  ����:      typeNo:string
  ����ֵ:    String
-------------------------------------------------------------------------------}
function getTypeName(stypeNo:string): String;
var
  sqlstr:string;
begin
  if stypeNo='' then
    sqlstr := 'select '+typeName+' from '+tblCutType+' where '+typeNo+'=0'
  else
    sqlstr := 'select '+typeName+' from '+tblCutType+' where '+typeNo+'='+stypeNo;
  try
    Result := sqlExec(sqlstr,typeName);
  except
    Result := '';
  end;
end;

{-------------------------------------------------------------------------------
  ������:    photoHaveRecord�Ƿ������Ƭ��¼
  ����:      hanjiwei
  ����:      2009.09.22
  ����:      sstuEmpNo:string
  ����ֵ:    string�������ڷ���'',���ڷ���ѧ����
-------------------------------------------------------------------------------}
function photoHaveRecord(sstuEmpNo:string):string;
var
  sqlstr:string;
begin
  sqlstr := 'select '+custId+' from '+tblPhoto+' where '+stuempNo+'='+QuotedStr(sstuEmpNo);
  try
    Result := sqlExec(sqlstr,custId);
  except
    Result := '';
  end;
end;

{-------------------------------------------------------------------------------
  ������:    getTypeNameȡ�ÿ���
  ����:      hanjiwei
  ����:      2007.01.15
  ����:      typeNo:string
  ����ֵ:    String
-------------------------------------------------------------------------------}
{
function getCardNo(custId:string):string;
var
  sqlstr:string;
begin
  sqlstr := 'select '+cardCardId+' from '+tblCard+' where '+cardStateId;
  sqlstr := sqlstr+' in ('+#39+'1'+#39+') and '+cardCustId+'='+custId;
  Result := sqlExec(sqlstr,cardCardId);
end;
}
function queryBaseInfoSql(sstuempNo:string;sareaId:string;scustId:string): string;
var
  sqlStr:string;
begin
  sqlStr:='select '+custId+','+stuempNo+','+custName+','+custType+','+custState;
  sqlStr:=sqlStr+','+custArea+','+custCardId+','+custDeptNo+','+custSpecNo+','+classNo;
  sqlStr:=sqlStr+','+custRegTime+','+custFeeType+' from '+tblCust+' where 1>0';
  if Trim(sstuempNo)<>'' then
    sqlStr:=sqlStr+' and '+stuempNo+'='+#39+sstuempNo+#39;
  if Trim(sareaId)<>'' then
    sqlStr:=sqlStr+' and '+custArea+'='+sareaId;
  if Trim(scustId)<>'' then
    sqlStr:=sqlStr+' and '+ custId+'='+scustId;

  Result:=sqlStr;
end;

{-------------------------------------------------------------------------------
  ������:    getPhotoInfo
  ����:      hanjiwei
  ����:      2007.02.24
  ����:      scustId: string
  ����ֵ:    TJpegImage
-------------------------------------------------------------------------------}
function getPhotoInfo(scustId: string): TJpegImage;
var
  sqlStr:string;
  qrySQL:TADOQuery;
  F3: TADOBlobStream;
  Fjpg: TJpegImage;
begin
  sqlStr:='select '+pPhoto+','+pIfCard+','+pPhotoDate+','+pPhotoTime;
  sqlStr:=sqlStr+','+pcardDate+','+pCardTime;
  sqlStr:=sqlStr+' from '+tblPhoto+' where '+custId+'='+scustId;
  qrySQL := nil;
  //F3:=nil;
  //Fjpg:=nil;
  Result:=nil;
  cpIfCard:='';
  cpCardDate:='';
  cpCardTime:='';
  try
    qrySQL := TADOQuery.Create(nil);
    qrySQL.Connection := frmdm.conn;
    qrySQL.Close;
    qrySQL.SQL.Clear;
    qrySQL.SQL.Add(sqlStr);
    qrySQL.Prepared;
    qrySQL.Open;
    if not qrySQL.IsEmpty then
    begin
      qrySQL.First;
      cpIfCard:=qrySQL.fieldbyname(pIfCard).AsString;
      cpCardDate:=qrySQL.fieldbyname(pCardDate).AsString;
      cpCardTime:=qrySQL.fieldbyname(pCardTime).AsString;
      F3 := TADOBlobStream.Create(TBlobField(qrySQL.fieldbyname(pPhoto)), bmread);
      try
        Fjpg := TJpegImage.Create;
        F3.Position := 0;
        if F3.Size > 1 then
        begin
          FJpg.LoadFromStream(F3);
          Result:=Fjpg;
        end;
      finally
        //Fjpg.Free;
        F3.Destroy;
      end;
    end
    else
      Result := nil;
  finally
    qrySQL.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    getJpgNoȡ����Ƭ�ı��
  ����:      hanjiwei
  ����:      2007.01.16
  ����:      jpgName:string
  ����ֵ:    string
-------------------------------------------------------------------------------}
function getJpgNo(jpgName:string):string;
begin
  result := subString(jpgName,'.','l');
end;

{-------------------------------------------------------------------------------
  ������:    ExportData
  ����:      hanjiwei
  ����:      2007.01.17
  ����:      SaveDialog1: TSaveDialog;DBGridEh1: TDBGridEh
  ����ֵ:    ��
-------------------------------------------------------------------------------}
function ExportData(SaveDialog1: TSaveDialog;DBGridEh1: TDBGridEh):Boolean;
var
  ExpClass:TDBGridEhExportClass;
  Ext:String;
begin
  Result := False;
  try
    begin
      SaveDialog1.FileName := '��������'+formatdatetime('yyyymmdd',date());
      DBGridEh1.Selection.SelectAll ;
      if SaveDialog1.Execute then
      begin
        case SaveDialog1.FilterIndex of
          4: begin ExpClass := TDBGridEhExportAsText; Ext := 'txt'; end;
          2: begin ExpClass := TDBGridEhExportAsHTML; Ext := 'htm'; end;
          3: begin ExpClass := TDBGridEhExportAsRTF; Ext := 'rtf'; end;
          1: begin ExpClass := TDBGridEhExportAsXLS; Ext := 'xls'; end;
        else
          ExpClass := nil; Ext := '';
        end;
        if ExpClass <> nil then
        begin
          if UpperCase(Copy(SaveDialog1.FileName,Length(SaveDialog1.FileName)-2,3)) <>  UpperCase(Ext) then
            SaveDialog1.FileName := SaveDialog1.FileName + '.' + Ext;
          SaveDBGridEhToExportFile(ExpClass,DBGridEh1, SaveDialog1.FileName,False);
        end;
        Result := True;
      end;
     end ;
   except
     showmessage('����ʧ�ܣ�����...');
   end;
end;

{-------------------------------------------------------------------------------
  ������:    TfrmAddCustInfo.haveStuEmpNo����Ƿ����ѧ����
  ����:      hanjiwei
  ����:      2007.01.18
  ����:      ��
  ����ֵ:    ���ڷ��ظÿͻ��ţ����򷵻�0
-------------------------------------------------------------------------------}
function haveStuEmpNo(sstuEmpNo:string): Integer;
var
  tmpQuery:TADOQuery;
  strSql:string;
begin
  strSql:=queryBaseInfoSql(sstuEmpNo,'','');
  tmpQuery:=nil;
  //Result:=-1;
  try
    tmpQuery:=TADOQuery.Create(nil);
    tmpQuery.Connection:=frmdm.conn;
    tmpQuery.Close;
    tmpQuery.SQL.Clear;
    tmpQuery.SQL.Add(strSql);
    tmpQuery.Open;
    if not tmpQuery.IsEmpty then
      Result:=tmpQuery.fieldbyname(custId).AsInteger
    else
      Result := 0;
  finally
    tmpQuery.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    qryOperSql
  ����:      hanjiwei
  ����:      2007.03.14
  ����:      soperCode:string;spwd:string
  ����ֵ:    string
-------------------------------------------------------------------------------}
function qryOperSql(soperCode:string;spwd:string): string;
var
  sqlStr:string;
begin
  sqlStr:='select '+lmtOperCode+','+lmtOperName+','+lmtBeginDate+','+lmtEndDate;
  sqlStr:=sqlStr+','+lmtpwd+','+lmtLimit+','+lmtEnabled+' from '+tblLimit;
  sqlStr:=sqlStr+' where 1>0 ';
  if soperCode<>'' then
    sqlStr:=sqlStr+' and '+lmtOperCode+'='+#39+sopercode+#39;
  if spwd<>'' then
    sqlStr:=sqlStr+' and '+lmtpwd+'='+#39+DecryptString(spwd,'ksykt123')+#39;

  Result:=sqlStr;
end;

function judgelimit(oper: string; code:integer):boolean;
begin
  if copy(oper,code+1,1)='1' then
    result:=true
  else
    result:=false;
end;

{-------------------------------------------------------------------------------
  ������:    insertPhotoData
  ����:      hanjiwei
  ����:      2007.03.14
  ����:      sCustId, sStuempNo: string
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure insertPhotoData(sCustId, sStuempNo: string);
var
  photoQuery:TADOQuery;
  photoStr:string;
begin
  photoQuery := nil;
  try
    photoQuery:=TADOQuery.Create(nil);
    photoQuery.Connection:=frmdm.conn;
    //photoQuery.LockType := ltUnspecified;
    photoQuery.Close;
    photoQuery.SQL.Clear;
    photoQuery.SQL.Add('select count(*) as num from '+tblPhoto+' where '+custId+'='+sCustId);
    photoQuery.Open;
    if photoQuery.FieldByName('num').AsInteger=0 then
    begin
      photoStr:='insert into '+tblPhoto+'('+custId+','+stuempNo+')values(';
      photoStr:=photoStr+sCustId+',';
      photoStr:=photoStr+#39+sStuempNo+#39+')';
      photoQuery.Close;
      photoQuery.SQL.Clear;
      photoQuery.SQL.Add(photoStr);
      photoQuery.ExecSQL;
    end;
  finally
    photoQuery.Free;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    getMaxCustIdȡ�ͻ���
  ����:      ��
  ����ֵ:    Integer
-------------------------------------------------------------------------------}
{
function getMaxCustId: Integer;
var
  tmpQuery:TADOQuery;
  sqlStr:string;
  icustId:Integer;
begin
  sqlStr:='select '+keyValue+' from '+tblSysKey+' where '+keyCode+'='+#39+keyCustId+#39;
  tmpQuery:=nil;
  icustId:=0;
  try
    tmpQuery:=TADOQuery.Create(nil);
    tmpQuery.Connection:=frmdm.conn;
    tmpQuery.Close;
    tmpQuery.SQL.Clear;
    tmpQuery.SQL.Add(sqlStr);
    tmpQuery.Open;
    if not tmpQuery.IsEmpty then
      icustId:=tmpQuery.fieldbyname(keyValue).AsInteger;
    Result:=icustId+1;
  finally
    tmpQuery.Destroy;
  end;
end;
}
function addCustInfo(sstuempNo,sname,stype,sArea,scardId,sDept,sSpec,sFeeType:string):Boolean;
var
  custQuery:TADOQuery;
  //keyQuery:TADOQuery;
  //keyStr:string;
  custStr:string;
  //icustId:Integer;
begin
  Result := False;
  //icustId:=getMaxCustId();
  custStr:='insert into '+tblCust+'('+stuempNo+','+custName+',';
  custStr:=custStr+custType+','+custState+','+custArea+','+custCardId+',';
  custStr:=custStr+custDeptNo+','+custSpecNo+','+custRegTime+','+feeFeeType+')values(';
  //custStr:=custStr+inttostr(icustId)+',';
  custStr:=custStr+#39+sstuempNo+#39+',';
  custStr:=custStr+#39+sname+#39+',';
  custStr:=custStr+stype+',';
  custStr:=custStr+'1'+',';
  custStr:=custStr+sArea+',';
  custStr:=custStr+#39+scardId+#39+',';
  custStr:=custStr+#39+sDept+#39+',';
  custStr:=custStr+#39+sSpec+#39+',';
  custStr:=custStr+#39+formatdatetime('yyyymmdd',now())+#39+',';
  custStr:=custStr+sFeeType+')';
  //keyStr := 'update '+tblSysKey+' set '+keyValue + '='+inttostr(icustId);
  //keyStr := keyStr + ' where '+keyCode+'='+#39+keyCustId+#39;;
  custQuery:=nil;
  //keyQuery := nil;
  try
    custQuery:=TADOQuery.Create(nil);
    custQuery.Connection:=frmdm.conn;

    custQuery.Close;
    custQuery.SQL.Clear;
    custQuery.SQL.Add(custStr);
    {
    keyQuery:=TADOQuery.Create(nil);
    keyQuery.Connection:=frmdm.conn;

    keyQuery.Close;
    keyQuery.SQL.Clear;
    keyQuery.SQL.Add(keyStr);
    }
    //frmdm.conn.BeginTrans;
    //try
      //keyQuery.ExecSQL;
      custQuery.ExecSQL;
      //frmdm.conn.CommitTrans;
      Result := True;
    //except

      //frmdm.conn.RollbackTrans;
      //Result := False;
    //end;
  finally
    custQuery.Destroy;
  end;
end;
{-------------------------------------------------------------------------------
  ������:    delFileBat����ɾ���ļ�
  ����:      filePath,fileName:string
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
procedure delFileBat(filePath,fileName:string);
var
  FileDir :string;
  FileStruct:TSHFileOpStruct;
begin
  try
    FileDir := filePath+'\'+filename;
    FileStruct.Wnd :=0;
    FileStruct.wFunc :=FO_delete;
    FileStruct.pFrom:=Pchar(FileDir+#0);
    FileStruct.fFlags:=FOF_NOCONFIRMATION;
    FileStruct.pTo :='';
    if SHFileOperation(FileStruct)=0 then
      Exit;
  except
  end;
end;

procedure getFillQuerySql(var deptSql,specSql,typeSql,areaSql:string);
var
  queryIni:TIniFile;
  //sqlStr:string;
begin
  queryIni := nil;
  if FileExists(apppath+'photoquery.ini') = false then
  begin
    Application.MessageBox('ϵͳ�����ļ��Ѿ����ƻ�������ϵͳ����Ա��ϵ��',
      'ϵͳ����', mb_ok + mb_iconerror);
    Application.Terminate;
  end;
  try
    queryIni := TIniFile.Create(apppath+'photoquery.ini');
    deptSql := queryIni.ReadString('filldata','deptSql','');
    specSql := queryIni.ReadString('filldata','specSql','');
    typeSql := queryIni.ReadString('filldata','typeSql','');
    areaSql := queryIni.ReadString('filldata','areaSql','');
  finally
    queryIni.Destroy;
  end;
end;

function getDbTime: string;
var
  tmpQuery:TADOQuery;
  sqlStr:string;
  //icustId:Integer;
begin
  if (Trim(dbName)='ORACLE') then
    sqlStr:='select to_char(current_timestamp,''YYYYMMDDHH24MISSFF'')dbtime from dual'
  else if (Trim(dbName)='DB2') then
    sqlStr:='select replace(replace(char(current timestamp),''-'',''''),''.'','''')dbtime from sysibm.sysdummy1'
  else if (Trim(dbName)='MYSQL') then
    //sqlStr:='select '+keyValue+' from '+tblSysKey+' where '+keyCode+'='+#39+keyCustId+#39
  else
  begin
    ShowMessage('��鿴��������ļ���ȷ�����ݿ����Ƿ���ȷ��');
    Exit;
  end;

  tmpQuery:=nil;
  //icustId:=0;
  try
    tmpQuery:=TADOQuery.Create(nil);
    tmpQuery.Connection:=frmdm.conn;
    tmpQuery.Close;
    tmpQuery.SQL.Clear;
    tmpQuery.SQL.Add(sqlStr);
    tmpQuery.Open;
    Result := tmpQuery.fieldbyname('dbtime').AsString;
  finally
    tmpQuery.Free;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    updatePhoto ���ݾɵ�ѧ���Ÿ����µ�ѧ������Ƭ��Ϣ
  ����:      oldNo,newNo:string
  ����ֵ:    Integer
-------------------------------------------------------------------------------}
function updatePhoto(oldNo,newNo:string):Integer;
var
  tempQuery:TADOQuery;
  sqlstr:string;
begin
  sqlstr := 'update '+ tblPhoto +' set '+pphoto+'=(select '+pphoto+' from ';
  sqlstr := sqlstr+tblPhoto+' where '+stuempNo+'='+QuotedStr(oldNo)+'),';
  sqlstr := sqlstr+pPhotoDate+'='+QuotedStr(FormatDateTime('yyyymmdd',Date))+',';
  sqlstr := sqlstr+pPhototime+'='+QuotedStr(FormatDateTime('hhmmss',Now))+',';
  sqlstr := sqlstr+pPhotoDTime+'='+QuotedStr(getDbTime)+' where '+stuempNo+'='+QuotedStr(newNo);
  tempQuery := nil;
  try
    tempQuery := TADOQuery.Create(nil);
    tempQuery.Connection := frmDM.conn;
    tempQuery.Close;
    tempQuery.SQL.Clear;
    tempQuery.SQL.Add(sqlstr);
    //tempQuery.SQL.SaveToFile('dsdl.txt');
    try
      tempQuery.ExecSQL;
      Result := 0;
    except
      Result := -1;
    end;
  finally
    tempQuery.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    insertPhoto���ݾ�ѧ���Ÿ�����Ƭ����ѧ����
  ����:      oldNo,newNo:string
  ����ֵ:    Integer
-------------------------------------------------------------------------------}
function insertPhoto(incustId,oldNo,newNo:string):Integer;
var
  tempQuery:TADOQuery;
  sqlstr:string;
begin
  sqlstr := 'insert into '+ tblPhoto +'('+custId+','+stuempNo+','+pphoto+',';
  sqlstr := sqlstr+pPhotoDate+','+pPhototime+','+pPhotoDTime+')values(';
  sqlstr := sqlstr+incustId+','+QuotedStr(newNo)+',';
  sqlstr := sqlstr+'(select '+pphoto+' from '+tblPhoto+' where '+stuempNo+'='+QuotedStr(oldNo)+'),';
  sqlstr := sqlstr+QuotedStr(FormatDateTime('yyyymmdd',Date))+',';
  sqlstr := sqlstr+QuotedStr(FormatDateTime('hhmmss',Now))+',';
  sqlstr := sqlstr+QuotedStr(getDbTime)+')';

  tempQuery := nil;
  try
    tempQuery := TADOQuery.Create(nil);
    tempQuery.Connection := frmDM.conn;
    tempQuery.Close;
    tempQuery.SQL.Clear;
    tempQuery.SQL.Add(sqlstr);
    //tempQuery.SQL.SaveToFile('dsdl.txt');
    try
      tempQuery.ExecSQL;
      Result := 0;
    except
      Result := -1;
    end;
  finally
    tempQuery.Destroy;
  end;
end;

end.

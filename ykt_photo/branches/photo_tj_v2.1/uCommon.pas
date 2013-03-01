unit uCommon;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,DBGridEh,
  Dialogs, StdCtrls, ExtCtrls, INIFiles, ADODB,DB, AES,jpeg,DBGridEhImpExp,
  ShellAPI;
const
  // 权限管理, 模块号
  Mdl_ifUse = 0;        //是否可用
  Mdl_limit = 1;        //权限管理
  Mdl_photoStat = 2;    //拍照统计
  Mdl_photoQuery = 3;   //拍照查询
  Mdl_import = 4;       //导入照片
  Mdl_export = 5;       //导出照片
  Mdl_addCust = 6;      //添加人员信息
  Mdl_EditCust = 7;     //修改人员信息

  Mdl_stuPrint = 8;     //学生卡打印
  Mdl_empPrint = 9;     //教师卡打印
  Mdl_delphoto = 10;    //删除照片
  mdl_savephoto = 11;   //保存照片
  mdl_custImport = 12;  //人员添加
  mdl_photocopy = 13;   //照片复制

  selectH = 316;
  selectW = 237;
  imgW = 420;

var
  useRemoteSoft:Boolean;      //使用第三方远景拍摄软件,使用为true
  {加密密钥为ksykt123}
  ifconn:Boolean;             //是否连接上数据库
  apppath:string ;            //系统文件路径
  connStr:string ;            //数据库连接字符串
  dbName:string;              //数据库名称
  //dbprovider:string;          //数据库连接串
  datasource:string;          //数据源名称
  dbuId :string;              //登录数据库用户名
  dbPwd :string;              //登录数据库密码

  tblPhoto:String ;		        //照片表
  tblDept:String ;	          //部门表
  tblSpec:String ;		        //专业表
  tblDict:String ;			      //数据字典
  tblCust:string ;            //客户表
  tblArea:string;             //区域表
  tblCutType:string;          //客户类别表
  tblLimit:string;            //权限表
  //tblFeeType:string;          //收费类别表
  //tblSysKey:string;           //系统键值表
  //tblCard : string;           //卡表
  
  custId:String ;		          //客户号
  stuempNo:string;            //学工号
  custName:String ;		        //姓名
  custType:string;            //人员类别
  custState:string;           //客户状态
  custArea:string;            //客户所在区域
  custSex:String ;			      //性别
  custCardId:String ;			    //身份证号
  custDeptNo:string;          //客户所在部门号
  custSpecNo:string;          //客户所在专业号
  custRegTime:string;         //客户注册时间
  custFeeType:string;         //收费类别
  classNo:string;             //班级
  inDate:string;              //年级

  pPhoto:string;              //照片
  //PMinPhoto:string;           //小照片
  pIfCard:String ;		        //是否制卡
  pCardDate:String ;		      //制卡日期
  pCardTime:string;           //制卡时间
  pPhotoDate:String ;		      //拍照日期
  pPhotoTime:String ;		      //拍照时间
  pPhotoDTime:STRING;         //拍照精确时间，到毫秒
  res_1:String ;		          //预留字段
  res_2:String ;
  res_3:String ;

  lmtOperCode:String ;        //操作员代码
  lmtOperName:String ;        //操作员名称
  lmtBeginDate:String ;       //生效时间
  lmtEndDate:String ;         //实效时间
  lmtpwd:String ;             //密码
  lmtLimit:String ;           //权限
  lmtEnabled:String ;         //是否可用

  deptCode:String ;		        //部门代码
  deptName:String ;		        //部门名称
  deptParent:String ;	        //父类代码
  deptLevel:String ;	        //部门级别

  specCode:string;            //专业代码
  specName:string;            //专业名称

  dictNo:string;              //字典编号
  dictValue:string;           //字典子编号
  dictCaption:string;         //字典名称

  areaNo:string;              //区域编号
  areaName:string;            //区域名称
  areaFather:string;          //区域父编号

  typeNo:string;              //类别编号
  typeName:string;            //类别名称

  cpIfCard:string;            //卡片打印中显示是否制卡
  cpCardDate:string;          //制卡日期
  cpCardTime:string;          //制卡时间


  loginLimit:string;          //登录后客户的权限
  loginName:string;           //登录名
  loginPwd:string;            //登录密码
  
  feeFeeType:string;          //类别代码
  {feeFeeName:string;          //类别名称

  keyCode:string;             //键值代码
  keyName:string;             //键值名称
  keyValue:string;            //键值数据
  keyMaxValue:string;         //最大键值
  keyCustId:string;           //客户号在键值表中的代码

  cardCardId:string;          //卡号
  cardStateId:string;         //卡状态
  cardCustId:string;          //客户号
  }
  photopath :string;          //照片所在位置
  photopre:string;            //照片前缀
  diskpath:string;            //本地位置

  rotate:Boolean;             //是否旋转
  angle:Integer;              //旋转角度

  minWidth:Integer;           //小照片的宽度
  minHeight:Integer;          //小照片的高度

  //取景框设置显示及位置设置
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
  过程名:    getphotoconfigs得到照片库中的配置文件
  作者:      韩纪伟
  日期:      2006.02.24
  参数:      无
  返回值:    无
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
    Application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
      '系统错误！', mb_ok + mb_iconerror);
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
      ShowMessage('请查看你的配置文件，确定数据库名是否正确！');
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
  过程名:    AddData向下拉列表中添加数据
  作者:      韩纪伟
  日期:      2006.03.03
  参数:      cbb:TComboBox;sqlstr:string
  返回值:    无
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
  过程名:    subString
  作者:      hanjiwei
  日期:      2007.01.16
  参数:      ssname:string;str:string;posi:string字符串，分割字符串，截取方向
  返回值:    string
-------------------------------------------------------------------------------}
function subString(ssname:string;str:string;posi:string):string;
begin
  if LowerCase(posi)='l' then
    Result := Copy(ssname,0,Pos(str,ssname)-1);
  if LowerCase(posi)='r' then
    Result := Copy(ssname,Pos(str,ssname)+1,Length(ssname));
end;

{-------------------------------------------------------------------------------
  过程名:    getDeptName根据部门编码返回部门名称
  作者:      韩纪伟
  日期:      2006.03.01
  参数:      sDeptCode:string
  返回值:    string
-------------------------------------------------------------------------------}
function getDeptName(sDeptCode:string):string;
var
  sqlstr:string;
begin
  sqlstr := 'select '+deptname+' from '+tblDept+' where '+deptcode+'='+QuotedStr(sDeptCode);
  Result := sqlExec(sqlstr,deptname);
end;

{-------------------------------------------------------------------------------
  过程名:    getSName根据专业编码返回专业名称
  作者:      韩纪伟
  日期:      2006.03.01
  参数:      ssCode:string
  返回值:    string
-------------------------------------------------------------------------------}
function getSName(ssCode:string):string;
var
  sqlstr:string;
begin
  sqlstr := 'select '+specName+' from '+tblSpec+' where '+specCode+'='+QuotedStr(ssCode);
  Result := sqlExec(sqlstr,specName);
end;

{-------------------------------------------------------------------------------
  过程名:    sqlExec根据代码查找相关的名称，并返回。把其它的函数修改为调用此
  作者:      韩纪伟
  日期:      2006.03.03
  参数:      sqlstr:string;rname:string
  返回值:    string
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
  过程名:    getAreaName根据区域编号取得区域名称
  作者:      hanjiwei
  日期:      2007.01.15
  参数:      areaNo:string
  返回值:    String
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
  过程名:    getStatesName取得状态名称
  作者:      hanjiwei
  日期:      2007.01.15
  参数:      StateNo:string
  返回值:    String
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
  过程名:    getTypeName取得类别名称
  作者:      hanjiwei
  日期:      2007.01.15
  参数:      typeNo:string
  返回值:    String
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
  过程名:    photoHaveRecord是否存在照片记录
  作者:      hanjiwei
  日期:      2009.09.22
  参数:      sstuEmpNo:string
  返回值:    string，不存在返回'',存在返回学工号
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
  过程名:    getTypeName取得卡号
  作者:      hanjiwei
  日期:      2007.01.15
  参数:      typeNo:string
  返回值:    String
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
  过程名:    getPhotoInfo
  作者:      hanjiwei
  日期:      2007.02.24
  参数:      scustId: string
  返回值:    TJpegImage
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
  过程名:    getJpgNo取得照片的编号
  作者:      hanjiwei
  日期:      2007.01.16
  参数:      jpgName:string
  返回值:    string
-------------------------------------------------------------------------------}
function getJpgNo(jpgName:string):string;
begin
  result := subString(jpgName,'.','l');
end;

{-------------------------------------------------------------------------------
  过程名:    ExportData
  作者:      hanjiwei
  日期:      2007.01.17
  参数:      SaveDialog1: TSaveDialog;DBGridEh1: TDBGridEh
  返回值:    无
-------------------------------------------------------------------------------}
function ExportData(SaveDialog1: TSaveDialog;DBGridEh1: TDBGridEh):Boolean;
var
  ExpClass:TDBGridEhExportClass;
  Ext:String;
begin
  Result := False;
  try
    begin
      SaveDialog1.FileName := '导出数据'+formatdatetime('yyyymmdd',date());
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
     showmessage('导出失败！请检查...');
   end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmAddCustInfo.haveStuEmpNo检查是否存在学工号
  作者:      hanjiwei
  日期:      2007.01.18
  参数:      无
  返回值:    存在返回该客户号，否则返回0
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
  过程名:    qryOperSql
  作者:      hanjiwei
  日期:      2007.03.14
  参数:      soperCode:string;spwd:string
  返回值:    string
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
  过程名:    insertPhotoData
  作者:      hanjiwei
  日期:      2007.03.14
  参数:      sCustId, sStuempNo: string
  返回值:    无
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
  过程名:    getMaxCustId取客户号
  参数:      无
  返回值:    Integer
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
  过程名:    delFileBat批量删除文件
  参数:      filePath,fileName:string
  返回值:    Boolean
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
    Application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
      '系统错误！', mb_ok + mb_iconerror);
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
    ShowMessage('请查看你的配置文件，确定数据库名是否正确！');
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
  过程名:    updatePhoto 根据旧的学工号更新新的学工号照片信息
  参数:      oldNo,newNo:string
  返回值:    Integer
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
  过程名:    insertPhoto根据旧学工号复制照片到新学工号
  参数:      oldNo,newNo:string
  返回值:    Integer
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

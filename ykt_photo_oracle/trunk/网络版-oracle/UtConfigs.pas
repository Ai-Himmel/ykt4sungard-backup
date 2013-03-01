unit UtConfigs;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Mask, ExtCtrls, INIFiles, jpeg, ADODB, udb;

const
  ExpirationDate = 31; {有效期限}
  DataBaseName = 'SmartCardDB'; {数据库名称}

  PhotoDate= 'photo_date'; //照相日期字段名称PhotoDateRecord
  PhotoTime= 'photo_time'; //照相时间字段名称PhotoTimeRecord
  Photo= 'photo';          //图片字段名字PhotoRecord

  opername='Oper';        //操作员

  DeptCode = 'DEPT_CODE'; //学院PersonKindNo1
  DeptName = 'Dept_name'; //人员类型一字段名称PersonKindName1
  BanchCode= 'BRANCH_CODE'; //人员类型二代码字段名称PersonKindNo2
  SCode= 'S_CODE';          //人员类型二代码字段名称PersonKindName2

  CutType= 'CUT_TYPE';      //人员类型PersonKindName3

  SexCode= 'SEX_CODE';     //PersonSexNo
  SexName= 'SEX_NAME';     //PersonSexName

  //PersonTableName = 'photo.T_CIF_Photo';
  PhotoTableName = 'photo.T_CIF_Photo';
  DepartmentTableName = 'tab_dept_info';
  SpecialTableName = 'photo.T_XB_BZKS_ZYJBXX';

  ID2= 'ID2';             //证件号码PersonIdCardName
  InDate='In_Date';       //入学年级
  NowLayer= 'nowlayer';   //现在年级PersonNowLayer
  EditDate= 'EditDate';   //修改时间PersonEditDate

  StuEmpNo= 'STUEMP_NO';     //人员编号字段名称PersonNo
  StuempName= 'STUEMP_NAME'; //人员名称字段名称PersonName
  FileName= 'filename';      //保存路径的字段SaveFileName

  Editflag = 'Edit_flag';    //是否改变过人员信息
  CGRADE = 'C_GRADE';        //
  ifmakecard = 'if_makeCard';
  makecardtime = 'makecard_time';
  addpersondate = 'addperson_date';

  EditPersonTable = 'T_Edit_Person';

  FCurrentLabelLeft = 20;
  FCurrentLabelTop = 15;


  // 权限管理, 模块号
  Mdl_Query = 1;
  Mdl_EditData = 2;
  Mdl_LoadPic = 3;  
  Mdl_ExpData = 4;  //导出数据
  Mdl_Print = 5;    //打印
  Mdl_ExpPic = 6;    //导出照片
  Mdl_DelData = 7;   //删除数据

  Mdl_ImpPic = 8;   //导入照片
  Mdl_ImpData = 9;   //导入数据
  Mdl_MakeCard = 10;   //制卡管理
  mdl_Card = 11;       //卡片打印
  mdl_PersonAdd = 12; //人员添加
  
var
  IpString: string;
  UserId: string;
  PswString: string;
  InitialCatalog: string;
  DataSource: string;

  OldDirPath: string;
  NewDirPath: string;
  Pre: string;
  NumberLen: Integer;
  StartNum: string;
  StartNumber: string;
  InitNumber: string;
  AddLength: Integer;
  OldNumber1: string;
  CurrentNumber: string;
  OldNumber2: string; //用于当前取最大序号的文件的比较，

  {设置图片的长度和宽度}
  PictureWidth: integer;
  PictureHeight: integer;
  PaintBoxWidth: integer;
  PaintBoxHeight: integer;
  {字幕字体设置}
  CaptionFontName: string;
  CaptionFontSize: Integer;
  CaptionFontStyle: string;
  CaptionFontColor: string;



procedure GetConfigs;
procedure ConfigConnectDB;

implementation


procedure ConfigConnectDB;
var
  ConnectStr: string;
begin
  with TIniFile.Create(ChangeFileExt('file_Sql', '.ini')) do
  try
    IpString := ReadString('DATABASE', 'IP', 'wsn');
    UserId := ReadString('DATABASE', 'User ID', 'sa');
    PswString := ReadString('DATABASE', 'Password', '8888');
    InitialCatalog := ReadString('DATABASE', 'Initial Catalog', 'SmartCardDB');
    DataSource := ReadString('DATABASE', 'Data Source', 'SmartCard');
  finally
    Free;
  end;

  {dm.ADOConnection1.Connected:=False;
  ConnectStr:=
        'Provider=SQLOLEDB.1;'+
        'Password='+PswString+';'+
        'Persist Security Info=True;'+
        'User ID='+UserId+';'+
        'Initial Catalog='+InitialCatalog+';'+
        'Data Source='+DataSource+';'+
        'Use Procedure for Prepare=1;'+
        'Auto Translate=True;'+
        'Packet Size=4096;'+
        'Workstation ID='+IpString+
        'Use Encryption for Data=False;'+
        'ag with column collation when possible=False';
{  ConnectStr:='Provider=SQLOLEDB.1;Password=0000;Persist Security Info=True;'+
         'User ID=sa;Initial Catalog=BSCS;Data Source=SERVER3\INFO_2;'+
         'Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;'+
         'Use Encryption for Data=False;Tag with column collation when possible=False';
}
{    dm.ConnectPhoto.Connected:=False;
    ConnectStr:='Provider=MSDASQL.1;Password='+PswString+';Persist Security Info=True;'+
      'User ID='+UserId+';Data Source='+DataSource+';Initial Catalog='+InitialCatalog;
    dm.ConnectPhoto.ConnectionString:=ConnectStr;
    try
     dm.ConnectPhoto.Connected:=True;
    except
      showmessage('连接数据库错误！');
      application.Terminate;
      exit;
    end; }
end;


procedure GetConfigs;
var
  my: TInifile;
  temp: string;
  temp1: string;
begin
  if FileExists(ChangeFileExt('file', '.ini')) = false then
  begin
    application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
      '系统严重警告', mb_ok + mb_iconerror);
    application.Terminate;
    exit;
  end
  else
  begin
    my := TIniFile.Create(ChangeFileExt('file', '.ini'));
    OldDirPath := my.ReadString('FILEDIR', 'OLDDIR', '');
    NewDirPath := my.ReadString('FILEDIR', 'NEWDIR', '');
    Pre := my.ReadString('FILEDIR', 'PRENAME', '');
    NumberLen := my.ReadInteger('FILEDIR', 'NUMBER', 0);
    StartNum := my.ReadString('FILEDIR', 'STARTNUM', '');
    temp1 := '0000000000' + StartNum;
    startNumber := Copy(temp1, (Length(temp1) - NumberLen + 1), NumberLen);
    my.WriteString('CANON', 'INITNUM', startNumber);
    initNumber := my.ReadString('CANON', 'INITNUM', '');
    my.WriteString('CANON', 'CURRENTNUM', startNumber);
    addLength := my.ReadInteger('CANON', 'LENGTH', 0);
    OldNumber1 := my.ReadString('CANON', 'INITNUM', '');

    PictureWidth := my.ReadInteger('PictureSize', 'PictureWidth', 192);
    PictureHeight := my.ReadInteger('PictureSize', 'PictureHeight', 280);
    PaintBoxWidth := my.ReadInteger('PictureSize', 'PaintBoxWidth', 196);
    PaintBoxHeight := my.ReadInteger('PictureSize', 'PaintBoxHeight', 284);

    CaptionFontName := my.ReadString('CaptionFontStyle', 'CaptionFontName', 'Arial Narrow');
    CaptionFontSize := my.ReadInteger('CaptionFontStyle', 'CaptionFontSize', 10);
    CaptionFontStyle := my.ReadString('CaptionFontStyle', 'CaptionFontStyle', 'fsBold');
    CaptionFontColor := my.ReadString('CaptionFontStyle', 'CaptionFontColor', 'clWhite');
    my.Destroy;
  end;
end;

initialization
  begin

  end;

finalization
  begin

  end;

end.

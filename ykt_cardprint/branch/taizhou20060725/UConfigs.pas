unit UConfigs;

interface

uses
  Windows, Messages, SysUtils,  Classes, Graphics, Controls, Forms,
  Dialogs,  StdCtrls,  Mask,  ExtCtrls, INIFiles, jpeg, RzBckgnd,ADODB,udb;

const
  ExpirationDate=90;      {有效期限}
  DataBaseName='h_test2'; {数据库名称}

  PhotoDateRecord='photo_date'; {照相日期字段名称}
  PhotoTimeRecord='photo_time'; {照相时间字段名称}
  PhotoRecord='photo';          {图片字段名字}

  PersonKindNo1='s_code';   {人员类型一代码字段名称}
  PersonKindName1='s_name'; {人员类型一字段名称}
  PersonKindNo2='dept_code';{人员类型二代码字段名称}
  PersonKindName2='dept_name';{人员类型二代码字段名称}
  PersinKindNo3 = 'cut_type';


  PersonTableName='YKT_CUR.T_CIF_PHOTO';
  PhotoTableName='YKT_CUR.T_CIF_PHOTO';
  DepartmentTableName='YKT_CUR.T_CIF_DEPT';
  SpecialTableName='YKT_CUR.T_CIF_SPECIALITY';
  PersonType='YKT_CUR.T_CIF_JOB';

  PersonNo='stuemp_no';     {人员编号字段名称}
  PersonName='stuemp_name'; {人员名称字段名称}
  SaveFileName='filename';  {保存路径的字段}

  reserve_2='reserve_2';    {是否正高职判断}
  jobname='Job_Name';       {人员职务名称}
  jobcode='Job_code';       {人员职务代码}
  status='status';          {人员状态}
  ifcard = 'ifcard';     {是否制卡}
  makecarddate = 'makecarddate';{制卡日期}

  FCurrentLabelLeft = 20;
  FCurrentLabelTop = 15;

var
  IpString:String;
  UserId:String;
  PswString:String;
  InitialCatalog:String;
  DataSource:String;

  OldDirPath:String;
  NewDirPath:String;
  Pre:String;
  NumberLen:Integer;
  StartNum:String;
  StartNumber:String;
  InitNumber:String;
  AddLength:Integer;
  OldNumber1:String;
  CurrentNumber:String;
  OldNumber2:String;  //用于当前取最大序号的文件的比较，

  {设置图片的长度和宽度}
  PictureWidth :integer;
  PictureHeight :integer;
  PaintBoxWidth :integer;
  PaintBoxHeight :integer;
  {字幕字体设置}
  CaptionFontName:String;
  CaptionFontSize:Integer;
  CaptionFontStyle:String;
  CaptionFontColor:String;

  {确定是教师卡还是学生卡，}
  CardType:string;  //T教师卡，S学生卡
  SName:string;//要修改的学生或教师的名称

  procedure GetConfigs;
  procedure ConfigConnectDB;

implementation


procedure ConfigConnectDB;
var
  ConnectStr:String;
begin
  with TIniFile.Create(ChangeFileExt('file_Sql','.ini')) do
  try
    IpString:= ReadString('Connect', 'IP', 'erver3\info_2');
    UserId:= ReadString('Connect', 'User ID', 'sa');
    PswString:= ReadString('Connect', 'Password', '0000');
    InitialCatalog:= ReadString('Connect', 'Initial Catalog', 'bscs');
    DataSource:= ReadString('Connect', 'Data Source', 'erver3\info_2');
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
{    dm.ADOConnection1.ConnectionString:=ConnectStr;
    try
     dm.ADOConnection1.Connected:=True;
    except
      showmessage('连接数据库错误！');
      application.Terminate;
      exit;
    end;  }
end;


procedure GetConfigs;
var
  my:TInifile;
  temp:String;
  temp1:String;
begin 
  if FileExists(ChangeFileExt('file','.ini'))=false then
  begin
    application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
        '系统严重警告',mb_ok+mb_iconerror);
    application.Terminate;
    exit;
  end
  else
  begin
    my:=TIniFile.Create(ChangeFileExt('file','.ini'));
    OldDirPath:=my.ReadString('FILEDIR','OLDDIR','');
    NewDirPath:=my.ReadString('FILEDIR','NEWDIR','');
    Pre:=my.ReadString('FILEDIR','PRENAME','');
    NumberLen:=my.ReadInteger('FILEDIR','NUMBER',0);
    StartNum:=my.ReadString('FILEDIR','STARTNUM','');
    temp1:='0000000000'+StartNum;
    startNumber:=Copy(temp1,(Length(temp1)-NumberLen+1),NumberLen);
    my.WriteString('CANON','INITNUM',startNumber);
    initNumber:=my.ReadString('CANON','INITNUM','');
    my.WriteString('CANON','CURRENTNUM',startNumber);
    addLength:=my.ReadInteger('CANON','LENGTH',0);
    OldNumber1:=my.ReadString('CANON','INITNUM','');

    PictureWidth:=my.ReadInteger('PictureSize','PictureWidth',192);
    PictureHeight:=my.ReadInteger('PictureSize','PictureHeight',280);
    PaintBoxWidth:=my.ReadInteger('PictureSize','PaintBoxWidth',196);
    PaintBoxHeight:=my.ReadInteger('PictureSize','PaintBoxHeight',284);

    CaptionFontName:=my.ReadString('CaptionFontStyle','CaptionFontName','Arial Narrow');
    CaptionFontSize:=my.ReadInteger('CaptionFontStyle','CaptionFontSize',10);
    CaptionFontStyle:=my.ReadString('CaptionFontStyle','CaptionFontStyle','fsBold');
    CaptionFontColor:=my.ReadString('CaptionFontStyle','CaptionFontColor','clWhite');
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

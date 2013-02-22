unit UConfigs;

interface

uses
  Windows, Messages, SysUtils,  Classes, Graphics, Controls, Forms,
  Dialogs,  StdCtrls,  Mask,  ExtCtrls, INIFiles, jpeg, RzBckgnd,ADODB,udb;

const
  ExpirationDate=90;      {��Ч����}
  DataBaseName='h_test2'; {���ݿ�����}

  PhotoDateRecord='photo_date'; {���������ֶ�����}
  PhotoTimeRecord='photo_time'; {����ʱ���ֶ�����}
  PhotoRecord='photo';          {ͼƬ�ֶ�����}

  PersonKindNo1='s_code';   {��Ա����һ�����ֶ�����}
  PersonKindName1='s_name'; {��Ա����һ�ֶ�����}
  PersonKindNo2='dept_code';{��Ա���Ͷ������ֶ�����}
  PersonKindName2='dept_name';{��Ա���Ͷ������ֶ�����}
  PersinKindNo3 = 'cut_type';


  PersonTableName='YKT_CUR.T_CIF_PHOTO';
  PhotoTableName='YKT_CUR.T_CIF_PHOTO';
  DepartmentTableName='YKT_CUR.T_CIF_DEPT';
  SpecialTableName='YKT_CUR.T_CIF_SPECIALITY';
  PersonType='YKT_CUR.T_CIF_JOB';

  PersonNo='stuemp_no';     {��Ա����ֶ�����}
  PersonName='stuemp_name'; {��Ա�����ֶ�����}
  SaveFileName='filename';  {����·�����ֶ�}

  reserve_2='reserve_2';    {�Ƿ�����ְ�ж�}
  jobname='Job_Name';       {��Աְ������}
  jobcode='Job_code';       {��Աְ�����}
  status='status';          {��Ա״̬}
  ifcard = 'ifcard';     {�Ƿ��ƿ�}
  makecarddate = 'makecarddate';{�ƿ�����}

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
  OldNumber2:String;  //���ڵ�ǰȡ�����ŵ��ļ��ıȽϣ�

  {����ͼƬ�ĳ��ȺͿ��}
  PictureWidth :integer;
  PictureHeight :integer;
  PaintBoxWidth :integer;
  PaintBoxHeight :integer;
  {��Ļ��������}
  CaptionFontName:String;
  CaptionFontSize:Integer;
  CaptionFontStyle:String;
  CaptionFontColor:String;

  {ȷ���ǽ�ʦ������ѧ������}
  CardType:string;  //T��ʦ����Sѧ����
  SName:string;//Ҫ�޸ĵ�ѧ�����ʦ������

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
      showmessage('�������ݿ����');
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
    application.MessageBox('ϵͳ�����ļ��Ѿ����ƻ�������ϵͳ����Ա��ϵ��',
        'ϵͳ���ؾ���',mb_ok+mb_iconerror);
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

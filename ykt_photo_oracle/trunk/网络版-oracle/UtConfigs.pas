unit UtConfigs;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Mask, ExtCtrls, INIFiles, jpeg, ADODB, udb;

const
  ExpirationDate = 31; {��Ч����}
  DataBaseName = 'SmartCardDB'; {���ݿ�����}

  PhotoDate= 'photo_date'; //���������ֶ�����PhotoDateRecord
  PhotoTime= 'photo_time'; //����ʱ���ֶ�����PhotoTimeRecord
  Photo= 'photo';          //ͼƬ�ֶ�����PhotoRecord

  opername='Oper';        //����Ա

  DeptCode = 'DEPT_CODE'; //ѧԺPersonKindNo1
  DeptName = 'Dept_name'; //��Ա����һ�ֶ�����PersonKindName1
  BanchCode= 'BRANCH_CODE'; //��Ա���Ͷ������ֶ�����PersonKindNo2
  SCode= 'S_CODE';          //��Ա���Ͷ������ֶ�����PersonKindName2

  CutType= 'CUT_TYPE';      //��Ա����PersonKindName3

  SexCode= 'SEX_CODE';     //PersonSexNo
  SexName= 'SEX_NAME';     //PersonSexName

  //PersonTableName = 'photo.T_CIF_Photo';
  PhotoTableName = 'photo.T_CIF_Photo';
  DepartmentTableName = 'tab_dept_info';
  SpecialTableName = 'photo.T_XB_BZKS_ZYJBXX';

  ID2= 'ID2';             //֤������PersonIdCardName
  InDate='In_Date';       //��ѧ�꼶
  NowLayer= 'nowlayer';   //�����꼶PersonNowLayer
  EditDate= 'EditDate';   //�޸�ʱ��PersonEditDate

  StuEmpNo= 'STUEMP_NO';     //��Ա����ֶ�����PersonNo
  StuempName= 'STUEMP_NAME'; //��Ա�����ֶ�����PersonName
  FileName= 'filename';      //����·�����ֶ�SaveFileName

  Editflag = 'Edit_flag';    //�Ƿ�ı����Ա��Ϣ
  CGRADE = 'C_GRADE';        //
  ifmakecard = 'if_makeCard';
  makecardtime = 'makecard_time';
  addpersondate = 'addperson_date';

  EditPersonTable = 'T_Edit_Person';

  FCurrentLabelLeft = 20;
  FCurrentLabelTop = 15;


  // Ȩ�޹���, ģ���
  Mdl_Query = 1;
  Mdl_EditData = 2;
  Mdl_LoadPic = 3;  
  Mdl_ExpData = 4;  //��������
  Mdl_Print = 5;    //��ӡ
  Mdl_ExpPic = 6;    //������Ƭ
  Mdl_DelData = 7;   //ɾ������

  Mdl_ImpPic = 8;   //������Ƭ
  Mdl_ImpData = 9;   //��������
  Mdl_MakeCard = 10;   //�ƿ�����
  mdl_Card = 11;       //��Ƭ��ӡ
  mdl_PersonAdd = 12; //��Ա���
  
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
  OldNumber2: string; //���ڵ�ǰȡ�����ŵ��ļ��ıȽϣ�

  {����ͼƬ�ĳ��ȺͿ��}
  PictureWidth: integer;
  PictureHeight: integer;
  PaintBoxWidth: integer;
  PaintBoxHeight: integer;
  {��Ļ��������}
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
      showmessage('�������ݿ����');
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
    application.MessageBox('ϵͳ�����ļ��Ѿ����ƻ�������ϵͳ����Ա��ϵ��',
      'ϵͳ���ؾ���', mb_ok + mb_iconerror);
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

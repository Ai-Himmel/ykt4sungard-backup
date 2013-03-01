unit UtConfigs;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Mask, ExtCtrls, INIFiles, jpeg, RzBckgnd, ADODB, udb;

const
  ExpirationDate = 90; {有效期限}
  DataBaseName = 'h_test2'; {数据库名称}

  PhotoDateRecord = 'photo_date'; {照相日期字段名称}
  PhotoTimeRecord = 'photo_time'; {照相时间字段名称}
  PhotoRecord = 'photo'; {图片字段名字}
  minPhoto = 'minphoto';

  PersonKindNo1 = 's_code'; {人员类型一代码字段名称}
  PersonKindName1 = 's_name'; {人员类型一字段名称}
  PersonKindNo2 = 'dept_code'; {人员类型二代码字段名称}
  PersonKindName2 = 'dept_name'; {人员类型二代码字段名称} //
  PersinKindNo3 = 'cut_type';
  status = 'status';


  PersonTableName = 'YKT_CUR.T_CIF_PHOTO';
  PhotoTableName = 'YKT_CUR.T_CIF_PHOTO';
  DepartmentTableName = 'YKT_CUR.T_CIF_DEPT';
  SpecialTableName = 'YKT_CUR.T_CIF_SPECIALITY';

  PersonNo = 'stuemp_no'; {人员编号字段名称}
  PersonName = 'stuemp_name'; {人员名称字段名称}
  SaveFileName = 'filename'; {保存路径的字段}

  FCurrentLabelLeft = 20;
  FCurrentLabelTop = 15;

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

  minWidth:Integer;           //小照片的宽度
  minHeight:Integer;          //小照片的高度

procedure GetConfigs;
procedure ConfigConnectDB;

implementation


procedure ConfigConnectDB;
var
  ConnectStr: string;
begin
  with TIniFile.Create(ChangeFileExt('file_Sql', '.ini')) do
  try
    IpString := ReadString('Connect', 'IP', 'erver3\info_2');
    UserId := ReadString('Connect', 'User ID', 'sa');
    PswString := ReadString('Connect', 'Password', '0000');
    InitialCatalog := ReadString('Connect', 'Initial Catalog', 'bscs');
    DataSource := ReadString('Connect', 'Data Source', 'erver3\info_2');
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
    //my := TIniFile.Create(ChangeFileExt('file', '.ini'));
    my:=TIniFile.Create( GetCurrentDir + '\file.ini');
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

    minWidth := my.ReadInteger('minphoto','width',0);
    minHeight := my.ReadInteger('minphoto','height',0);
    if (minWidth/minHeight)<>0.75 then
      minHeight := Round(minWidth*4/3 + 1);

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

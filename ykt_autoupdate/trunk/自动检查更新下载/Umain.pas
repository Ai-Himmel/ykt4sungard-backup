unit Umain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, ComCtrls, IdIntercept, IdLogBase,IniFiles,Umd5,
  IdLogDebug, IdAntiFreezeBase, IdAntiFreeze, IdBaseComponent, IdComponent,
  IdTCPConnection, IdTCPClient, IdFTP,IdFTPCommon, ImgList, Menus,
  WinSkinData, TlHelp32, jpeg, RzTray, SkinCaption;

type
  TfrmMain = class(TForm)
    pnl1: TPanel;
    pnlleft: TPanel;
    lstList: TListBox;
    idFtp: TIdFTP;
    idAntiFreeze: TIdAntiFreeze;
    idLogDebug: TIdLogDebug;
    status: TStatusBar;
    pnlright: TPanel;
    lstStatus: TListBox;
    ProgressBar1: TProgressBar;
    btnupdate: TButton;
    btnFindUpdate: TButton;
    tmr1: TTimer;
    PopupMenu1: TPopupMenu;
    ShowWindow1: TMenuItem;
    HideWindow1: TMenuItem;
    N2: TMenuItem;
    Exit1: TMenuItem;
    ImageList2: TImageList;
    btnMin: TButton;
    SkinData1: TSkinData;
    Image1: TImage;
    lblTip: TLabel;
    lblProgress: TLabel;
    skncptn1: TSkinCaption;
    rztrycn1: TRzTrayIcon;
    procedure idFtpDisconnected(Sender: TObject);
    procedure idFtpStatus(ASender: TObject; const AStatus: TIdStatus;
      const AStatusText: String);
    procedure idFtpWork(Sender: TObject; AWorkMode: TWorkMode;
      const AWorkCount: Integer);
    procedure idFtpWorkBegin(Sender: TObject; AWorkMode: TWorkMode;
      const AWorkCountMax: Integer);
    procedure idFtpWorkEnd(Sender: TObject; AWorkMode: TWorkMode);
    procedure FormCreate(Sender: TObject);
    procedure btnFindUpdateClick(Sender: TObject);
    procedure btnupdateClick(Sender: TObject);
    procedure tmr1Timer(Sender: TObject);
    procedure ShowWindow1Click(Sender: TObject);
    procedure HideWindow1Click(Sender: TObject);
    procedure btnMinClick(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure Exit1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    appPath:string;
    ftpip:string;
    ftpport:string;
    ftpuser:string;
    ftppassword:string;
    ftpdir:string;
    checktime:Integer;
    updateFile:TStrings;

    AbortTransfer: Boolean;
    TransferrignData: Boolean;
    BytesToTransfer: LongWord;
    STime: TDateTime;
    uploading:string;
    { Private declarations }
    procedure checkUpdate();
    procedure getIniFile();
    procedure connectFtpServer();
    procedure getDir(dirName: string);
    function  compareIniFiles():Boolean;
    procedure getIniFiles();
    procedure downIniFiles();
    procedure compareUpdateFiles();
    procedure downUpdateFiles();
    procedure moveIniFiles();
    function  MyFun_GetProcessID(ProcessName:  string):  Cardinal;
    function  KillExe(strFileName:string):Boolean; 
  public
    { Public declarations }
  end;

var
  frmMain: TfrmMain;
  AverageSpeed: Double = 0;

implementation

{$R *.dfm}

{ TfrmMain }

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.connectFtpServer连接Ftp服务器
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.connectFtpServer;
begin
  if idFtp.Connected then
  begin
    Status.SimpleText:='连接服务器成功';
    Exit;
  end;
  try
    IdFTP.Username := ftpuser;
    IdFTP.Password := ftppassword;
    IdFTP.Host := ftpip;
    IdFTP.Connect;
    GetDir(ftpdir);
  except
    Status.SimpleText:='连接服务器失败，请检查配置文件...';
  end;
  Status.SimpleText:='连接服务器成功';
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.getDir得到远程目录名
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      dirName: string
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.getDir(dirName: string);
begin
  try
    IdFTP.ChangeDir(DirName);
    IdFTP.TransferType:=ftASCII;
    ftpdir := IdFTP.RetrieveCurrentDir;
    //lstSerDir.Items.Clear;
    //列出文件和目录
    //IdFTP.List(lstSerDir.Items,'',false);
  except
    ShowMessage('不能打开目录，请检查配置文件');
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.getIniFile读取配置文件
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.getIniFile;
var
  //dirs: TStrings;
  update:TIniFile;
begin
  update := nil;
  try
    update := TIniFile.Create(appPath + 'update.ini');

    //连接服务器基本参数
    ftpip:= update.ReadString('ftp','ip','');
    ftpport:= update.ReadString('ftp','port','');
    ftpuser:= update.ReadString('ftp','user','');
    ftppassword:= update.ReadString('ftp','password','');
    ftpdir:=update.ReadString('ftp','dir','');
    checktime:=update.ReadInteger('time','time',0);
    {
    dirs := TStringList.Create;
    AppIni.ReadSectionValues('dir', dirs);
    for i := 0 to dirs.Count - 1 do
      lstDir.Items.Add(copy(dirs[i], pos('=', dirs[i]) + 1, Length(dirs[i])));
    }
  finally
    update.Free;
  end;
end;

procedure TfrmMain.idFtpDisconnected(Sender: TObject);
begin
  Status.SimpleText:='状态：已经断开连接！';
end;

procedure TfrmMain.idFtpStatus(ASender: TObject; const AStatus: TIdStatus;
  const AStatusText: String);
begin
  lststatus.ItemIndex := lststatus.Items.Add(AStatusText);
end;

procedure TfrmMain.idFtpWork(Sender: TObject; AWorkMode: TWorkMode;
  const AWorkCount: Integer);
var
  S: String;
  TotalTime: TDateTime;
  H, M, Sec, MS: Word;
  DLTime: Double;
begin
  TotalTime :=  Now-STime;
  DecodeTime(TotalTime, H, M, Sec, MS);
  Sec := Sec+M*60+H*3600;
  DLTime := Sec+MS/1000;
  if DLTime>0 then
     AverageSpeed := (AWorkCount/1024)/DLTime;
  S := FormatFloat('0.00 KB/s', AverageSpeed);
  case AWorkMode of
    wmRead: Status.SimpleText:='状态：下载速度  '+S;
    wmWrite: Status.SimpleText:='状态：上传速度  '+S;
  end;
  if AbortTransfer then
     IdFTP.Abort;
  ProgressBar1.Position:=AWorkCount;
  lblProgress.Caption :='正在传输:'+uploading+' (已完成  '+IntToStr(AWorkCount)+'  字节)';
  Application.ProcessMessages;
  AbortTransfer := false;
end;

procedure TfrmMain.idFtpWorkBegin(Sender: TObject; AWorkMode: TWorkMode;
  const AWorkCountMax: Integer);
begin
  TransferrignData := true;
  AbortTransfer := false;
  STime := Now;
  if AWorkCountMax > 0 then
     ProgressBar1.Max:=AWorkCountMax
  else
     ProgressBar1.Max:=BytesToTransfer;
  AverageSpeed := 0;

end;

procedure TfrmMain.idFtpWorkEnd(Sender: TObject; AWorkMode: TWorkMode);
begin
  Status.SimpleText := '状态：文件传输完毕！';
  lblProgress.Caption:='';
  BytesToTransfer := 0;
  TransferrignData := false;
  AverageSpeed := 0;

end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  appPath:=ExtractFilePath(application.ExeName);
  checkUpdate;
  tmr1.Enabled:=False;
  tmr1.Interval:=checktime*60000;
  tmr1.Enabled:=True;
  //rztrycn1.c := 400;
  //rztrycn1.CycleIcons := True;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.getUpdateFiles得到要更新的文件列表
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.getIniFiles;
var
  updateFileIni:TIniFile;
begin
  updateFileIni := nil;
  try
    updateFileIni := TIniFile.Create(appPath + 'update.ini');

    updateFile := TStringList.Create;
    updateFileIni.ReadSectionValues('updatefile', updateFile);
    {
    for i := 0 to dirs.Count - 1 do
      lstDir.Items.Add(copy(dirs[i], pos('=', dirs[i]) + 1, Length(dirs[i])));
    }
  finally
    updateFileIni.Free;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.downUpdateFiles下载ini文件
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.downIniFiles;
var
  i:Integer;
  inifilename:string;
  inifilepath:string;
  dirfilename:string;
begin
  try
    IdFTP.TransferType := ftBinary;
    for i := 0 to updateFile.Count-1 do
    begin
      inifilename:=Copy(updateFile[i],pos('=', updateFile[i]) + 1, Length(updateFile[i]));
      inifilepath:=Copy(updateFile[i],1,Pos('=',updateFile[i])-1);
      dirfilename:=ftpdir+'/'+inifilepath+'/'+inifilename;
      BytesToTransfer := IdFTP.Size(dirfilename);
      IdFTP.Get(dirfilename, appPath+'\'+inifilepath+'\'+inifilename, true);
    end;
  except
    ShowMessage('找不到配置文件，请检查配置文件');
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.compareUpdateFiles比较ini文件，得到要更新的项目列表
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.compareUpdateFiles;
var
  k:Integer;
  inifilename:string;
  inifilepath:string;
  bplfilename:string;

  newfilename:string;
  oldfilename:string;
  newinifiles:TIniFile;
  oldinifiles:TIniFile;
  newbplfiles: TStrings;
  oldbplfiles: TStrings;
  i:Integer;
  j:Integer;
  equal:Boolean;
begin
  
  for k := 0 to updateFile.Count-1 do
  begin
    inifilename:=Copy(updateFile[k],pos('=', updateFile[k]) + 1, Length(updateFile[k]));
    inifilepath:=Copy(updateFile[k],1,Pos('=',updateFile[k])-1);
    
    newfilename := appPath+'\'+inifilepath+'\'+inifilepath+'md5.ini';
    oldfilename := appPath+'\'+inifilepath+'\'+inifilepath+'oldmd5.ini';

    newinifiles:= TIniFile.Create(newfilename);
    newbplfiles:=TStringList.Create;
    newinifiles.ReadSectionValues('md5',newbplfiles);

    //目标ini文件
    oldinifiles:= TIniFile.Create(oldfilename);
    oldbplfiles:=TStringList.Create;
    oldinifiles.ReadSectionValues('md5',oldbplfiles);

    for i := 0 to newbplfiles.Count - 1 do
    begin
      bplfilename :=copy(newbplfiles[i], 1, pos('=', newbplfiles[i]) - 1);
      equal:=False;
      for j := 0 to oldbplfiles.Count - 1 do
      begin
        if newbplfiles[i]=oldbplfiles[j] then
        begin
          equal:=True;
          Break;
        end;
      end;
      if equal=False then
        lstList.Items.Add(bplfilename);
    end;
    if lstList.Items.Count<>0 then
    begin
      status.SimpleText:='共找到'+inttostr(lstList.Items.Count)+'个更新';
      btnupdate.Enabled:=True;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.downUpdateFiles下载查找到的更新项目
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.downUpdateFiles;
var
  i:Integer;
  getpathname:string;
  getfilename:string;
  dirfilename:string;
  localfilename:string;
begin
  try
  IdFTP.TransferType := ftBinary;
  for i := 0 to lstList.Items.Count-1 do
  begin
    uploading:=lstList.Items.Strings[i];
    //得到目录名称
    getpathname:=copy(lstList.Items.Strings[i],1,Pos('\',lstList.Items.Strings[i])-1);
    //得到文件名称
    getfilename:=ExtractFileName(lstList.Items.Strings[i]);
    dirfilename:=ftpdir+'/'+getpathname+'/'+getfilename;
    localfilename:=appPath+lstList.Items.Strings[i];
    BytesToTransfer := IdFTP.Size(dirfilename);
    IdFTP.Get(dirfilename, localfilename, true);
  end;
  lblTip.Caption:='完成更新部分下载...';
  lstList.Clear;
  ProgressBar1.Position:=0;
  except
    ShowMessage('找不到要更新的文件目录，请检查配置文件');
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.moveIniFiles下载完成后对更新的Ini文件更名
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.moveIniFiles;
var
  i:Integer;
  sourcefile,decfile:string;
  getpathname:string;
begin
  for i := 0 to updateFile.Count-1 do
  begin
    getpathname:=copy(updateFile[i],1,Pos('=',updateFile[i])-1);
    sourcefile:=appPath+getpathname+'\'+getpathname+'md5.ini';
    decfile:=appPath+getpathname+'\'+getpathname+'oldmd5.ini';
    if FileExists(decfile) then
      DeleteFile(decfile);
    MoveFile(PAnsiChar(sourcefile),PAnsiChar(decfile));
  end;
end;

procedure TfrmMain.btnFindUpdateClick(Sender: TObject);
begin
  lstList.Clear;
  compareUpdateFiles;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.compareIniFiles查找是否有更新文件
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    Boolean  false为没有更新，true有更新
-------------------------------------------------------------------------------}
function  TfrmMain.compareIniFiles:Boolean;
var
  i:integer;
  oldinifilename,newinifilename:string;
  getpathname:string;
begin
  Result:=False;
  for i := 0 to updateFile.Count-1 do
  begin
    getpathname:=copy(updateFile[i],1,Pos('=',updateFile[i])-1);
    oldinifilename:=appPath+getpathname+'\'+getpathname+'oldmd5.ini';
    newinifilename:=appPath+getpathname+'\'+getpathname+'md5.ini';
    if RivestFile(oldinifilename)<>RivestFile(newinifilename) then
    begin
      Result:=True;
      Exit;
    end;
  end;
end;

procedure TfrmMain.btnupdateClick(Sender: TObject);
begin
  if Application.MessageBox('在下载更新前会关闭一卡通前台程序，你确定吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idyes then
  begin
    KillExe('KSClient50d.exe');
    btnFindUpdate.Enabled:=False;
    downUpdateFiles;
    moveIniFiles;
    btnupdate.Enabled:=False;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.checkUpdate检查更新
  作者:      韩纪伟
  日期:      2006.02.10
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.checkUpdate;
begin
  getIniFile;
  connectFtpServer;
  getIniFiles;
  downIniFiles;
  btnFindUpdate.Enabled:=False;
  if compareIniFiles then
  begin
    lblTip.Caption:='找到要更新的软件，在下载更新前要关闭前台程序，然后更新系统...';
    rztrycn1.Animate;
    frmMain.BringToFront;
    btnFindUpdate.Enabled:=True;
    btnupdate.Enabled:=False;
  end
  else
  begin
    lblTip.Caption:='今日没有要更新的模块...';
    btnFindUpdate.Enabled:=False;
    btnupdate.Enabled:=False;
  end;
end;

procedure TfrmMain.tmr1Timer(Sender: TObject);
begin
  checkUpdate;
end;

procedure TfrmMain.ShowWindow1Click(Sender: TObject);
begin
  rztrycn1.RestoreApp;
end;

procedure TfrmMain.HideWindow1Click(Sender: TObject);
begin
  Application.Minimize;
  rztrycn1.MinimizeApp;
end;

procedure TfrmMain.btnMinClick(Sender: TObject);
begin
  Application.Minimize;
  rztrycn1.MinimizeApp;
end;

procedure TfrmMain.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
  if Application.MessageBox('你确定要退出升级程序监控吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=IDYES then
    CanClose := True
  else
    CanClose := False;
end;

procedure TfrmMain.Exit1Click(Sender: TObject);
begin
  Close;
end;

procedure TfrmMain.FormShow(Sender: TObject);
begin
  lblProgress.Caption:='';
end;

function TfrmMain.KillExe(strFileName: string): Boolean;
var  
   ProcessID:  THandle;  
   FHandle:  THandle;  
begin  
   ProcessID  :=  MyFun_GetProcessID(strFileName);  
   FHandle  :=  OpenProcess(PROCESS_ALL_ACCESS            ,False,ProcessID);  
   Result  :=  TerminateProcess(FHandle,0);  
end;

function TfrmMain.MyFun_GetProcessID(ProcessName: string): Cardinal;
var  
   FSnapshotHandle:  THandle;  
   FProcessEntry32:  TProcessEntry32;  
   Ret:  Boolean;  
   TmpProcessName:  string;  
   TmpProcessID:  DWORD;  
begin  
   TmpProcessID  :=  0;                                        //如果没有找到  
   //创建系统快照  
   FSnapshotHandle  :=  CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,  0);  
   //先初始化  FProcessEntry32  的大小  
   FProcessEntry32.dwSize  :=  SizeOf(FProcessEntry32);  
   Ret  :=  Process32First(FSnapshotHandle,  FProcessEntry32);  
   //循环枚举出系统开启的所有进程，找出“ProcessName”所指定的进程  
   while  Ret  do  
   begin  
       TmpProcessName  :=  ExtractFileName(FProcessEntry32.szExeFile);  
       if  TmpProcessName  =  ProcessName  then  
       begin  
           TmpProcessID  :=  FProcessEntry32.th32ProcessID;  
           Break;  
       end;  
       Ret  :=  Process32Next(FSnapshotHandle,  FProcessEntry32);  
   end;  
   CloseHandle(FSnapshotHandle);  
   Result  :=  TmpProcessID;  
end;

end.

unit Umain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls,IniFiles, ComCtrls, IdIntercept, IdLogBase,
  IdLogDebug, IdAntiFreezeBase, IdAntiFreeze, IdBaseComponent, IdComponent,
  IdTCPConnection, IdTCPClient, IdFTP, Buttons,IdFTPCommon, WinSkinData,
  SkinCaption;

type
  TfrmMain = class(TForm)
    pnl1: TPanel;
    pnl2: TPanel;
    lstDir: TListBox;
    lstList: TListBox;
    splleft: TSplitter;
    pnlright: TPanel;
    btnCreate: TButton;
    btnNew: TButton;
    btnUpLode: TButton;
    btnExit: TButton;
    pnltop: TPanel;
    lbl1: TLabel;
    edtMd5: TEdit;
    edtOldMd5: TEdit;
    lbl2: TLabel;
    lststatus: TListBox;
    idFtp: TIdFTP;
    idAntiFreeze: TIdAntiFreeze;
    idLogDebug: TIdLogDebug;
    grpservice: TGroupBox;
    lbl3: TLabel;
    lbl4: TLabel;
    lbl5: TLabel;
    lbl6: TLabel;
    Label6: TLabel;
    SpeedButton2: TSpeedButton;
    edtip: TEdit;
    edtuser: TEdit;
    edtpass: TEdit;
    edtport: TEdit;
    btnconnect: TButton;
    btndisconn: TButton;
    edtSerDir: TEdit;
    lstSerDir: TListBox;
    status: TStatusBar;
    lblProgress: TLabel;
    ProgressBar1: TProgressBar;
    SkinData1: TSkinData;
    skncptn1: TSkinCaption;
    procedure btnCreateClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure btnNewClick(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
    procedure btnconnectClick(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
    procedure btndisconnClick(Sender: TObject);
    procedure btnUpLodeClick(Sender: TObject);
    procedure idFtpDisconnected(Sender: TObject);
    procedure idFtpStatus(ASender: TObject; const AStatus: TIdStatus;
      const AStatusText: String);
    procedure idFtpWork(Sender: TObject; AWorkMode: TWorkMode;
      const AWorkCount: Integer);
    procedure idFtpWorkBegin(Sender: TObject; AWorkMode: TWorkMode;
      const AWorkCountMax: Integer);
    procedure idFtpWorkEnd(Sender: TObject; AWorkMode: TWorkMode);
    procedure lstDirClick(Sender: TObject);
  private
    appPath:string;
    AbortTransfer: Boolean;
    TransferrignData: Boolean;
    BytesToTransfer: LongWord;
    STime: TDateTime;
    uploading:string;

    selectDirName:string;//ѡ���Ŀ¼����
    { Private declarations }
    procedure FileSearch(FullPathName: string);
    procedure getIniFiles();
    procedure md5Compare();
    procedure getDir(dirName:string);
    procedure getSelectDir();
    procedure moveIniFiles();
  public
    { Public declarations }
  end;

var
  frmMain: TfrmMain;
  AverageSpeed: Double = 0;
implementation

uses Umd5;

{$R *.dfm}
{ TfrmMain }

{-------------------------------------------------------------------------------
  ������:    TfrmMain.FileSearch
  ����:      ����ΰ
  ����:      2006.02.09
  ����:      FullPathName: string
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfrmMain.FileSearch(FullPathName: string);
var
  F: TSearchRec;
  Found : Boolean;
  iniFiles:TIniFile;
  filename : string;
begin
  filename:= Trim(edtMd5.Text)+'\'+ExtractFileName(FullPathName)+'md5.ini';
  iniFiles:= Tinifile.Create(filename);
  ChDir(FullPathName);
  Found := (FindFirst('*.*', faArchive, F) = 0);
  while Found do
  begin
    if (F.Name = '.') or (F.Name = '..') then
    begin
      Found := (FindNext(F) = 0);
      Continue;
    end;
    lstList.Items.Add(ExtractFileName(FullPathName)+'\'+F.Name+'='+RivestFile(FullPathName+'\'+F.Name));
    iniFiles.WriteString('md5',ExtractFileName(FullPathName)+'\'+F.Name,RivestFile(FullPathName+'\'+F.Name));
    if (F.Attr and faDirectory) > 0 then
      FileSearch(FullPathName + F.Name + '\');
    Found := (FindNext(F) = 0);
  end;
  SysUtils.FindClose(F);
  ChDir('..\');
end;

procedure TfrmMain.btnCreateClick(Sender: TObject);
var
  i:Integer;
  filename:string;
begin
  lstList.Items.Clear;
  filename:=Trim(edtMd5.Text)+'\'+ExtractFileName(selectDirName)+'md5.ini';
  if FileExists(filename) then
    DeleteFile(filename);
  for i := 0 to lstDir.Items.Count-1 do
  begin
    if lstDir.Selected[i] then
      FileSearch(lstDir.Items.Strings[i]);
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfrmMain.getIniFiles
  ����:      ����ΰ
  ����:      2006.02.09
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfrmMain.getIniFiles;
var
  dirs: TStrings;
  i: integer;
  appIni:TIniFile;
begin
  lstDir.Items.Clear;
  try
    AppIni := TIniFile.Create(appPath + 'config.ini');

    edtMd5.Text:=appIni.ReadString('md5dir','md5dir','');
    edtOldMd5.Text:=appIni.ReadString('oldmd5dir','oldmd5dir','');

    //���ӷ�������������
    edtip.Text:= appIni.ReadString('ftp','ip','');
    edtport.Text:= appIni.ReadString('ftp','port','');
    edtuser.Text:= appIni.ReadString('ftp','user','');
    edtpass.Text:= appIni.ReadString('ftp','password','');
    edtSerDir.Text:=appIni.ReadString('ftp','serdir','');
    dirs := TStringList.Create;
    AppIni.ReadSectionValues('dir', dirs);
    for i := 0 to dirs.Count - 1 do
      lstDir.Items.Add(copy(dirs[i], pos('=', dirs[i]) + 1, Length(dirs[i])));
  finally
    AppIni.Free;
  end;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  appPath:=ExtractFilePath(application.ExeName);
  getIniFiles;
  lblProgress.Caption:='';
  btnUpLode.Enabled:=False;
  lstDir.ItemIndex:=0;
  getSelectDir;
end;

{-------------------------------------------------------------------------------
  ������:    TfrmMain.md5Compare�Ƚ�����md5�ļ����ҳ����µĸ����ļ�
  ����:      ����ΰ
  ����:      2006.02.09
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfrmMain.md5Compare;
var
  filename:string;
  decfilename:string;
  bplfilename:string;
  inifiles:TIniFile;
  decinifiles:TIniFile;
  bplfiles: TStrings;
  decbplfiles: TStrings;
  i:Integer;
  j:Integer;
  equal:Boolean;
begin
  filename := Trim(edtMd5.Text)+'\'+ExtractFileName(selectDirName)+'md5.ini';
  if FileExists(filename)=False then
  begin
    ShowMessage('�������ɼ����ļ����ټ����£�');
    Exit;
  end;

  inifiles:= TIniFile.Create(filename);
  bplfiles:=TStringList.Create;
  inifiles.ReadSectionValues('md5',bplfiles);

  //Ŀ��ini�ļ�
  decfilename := Trim(edtOldMd5.Text)+'\'+ExtractFileName(selectDirName)+'oldmd5.ini';
  decinifiles:= TIniFile.Create(decfilename);
  decbplfiles:=TStringList.Create;
  decinifiles.ReadSectionValues('md5',decbplfiles);

  for i := 0 to bplfiles.Count - 1 do
  begin
    bplfilename :=copy(bplfiles[i], 1, pos('=', bplfiles[i]) - 1);
    equal:=False;
    for j := 0 to decbplfiles.Count - 1 do
    begin
      if bplfiles[i]=decbplfiles[j] then
      begin
        equal:=True;
        Break;
      end;
    end;
    if equal=False then
      lstList.Items.Add(bplfilename);
  end;
  if lstList.Items.Count=0 then
  begin
    btnUpLode.Enabled:=False;
    lstList.Items.Add('û���ҵ�Ҫ���µ���Ŀ');
  end
  else
    btnUpLode.Enabled:=True;
end;

procedure TfrmMain.btnNewClick(Sender: TObject);
begin
  lstList.Items.Clear;
  md5Compare;
end;

procedure TfrmMain.btnExitClick(Sender: TObject);
begin
  Application.Terminate;
end;

procedure TfrmMain.btnconnectClick(Sender: TObject);
begin
  lststatus.Items.Clear;
  if idFtp.Connected then
  begin
    Status.SimpleText:='���ӷ������ɹ�';
    Exit;
  end;
  try
    IdFTP.Username := edtuser.Text;
    IdFTP.Password := edtpass.Text;
    IdFTP.Host := edtip.Text;
    IdFTP.Connect;
    GetDir(edtSerDir.text);
  except
    Status.SimpleText:='���ӷ�����ʧ��';
  end;
  Status.SimpleText:='���ӷ������ɹ�';
end;

{-------------------------------------------------------------------------------
  ������:    TfrmMain.getDir�õ�Զ��Ŀ¼
  ����:      ����ΰ
  ����:      2006.02.09
  ����:      dirName: string
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfrmMain.getDir(dirName: string);
begin
  try
    IdFTP.ChangeDir(DirName);
    IdFTP.TransferType:=ftASCII;
    edtSerDir.Text := IdFTP.RetrieveCurrentDir;
    lstSerDir.Items.Clear;
    //�г��ļ���Ŀ¼
    IdFTP.List(lstSerDir.Items,'',false);
  finally
    //
  end;

end;

procedure TfrmMain.SpeedButton2Click(Sender: TObject);
begin
  GetDir(edtSerDir.Text);
end;

procedure TfrmMain.btndisconnClick(Sender: TObject);
begin
  lststatus.Items.Clear;
  if IdFTP.Connected then
    try
      if TransferrignData then
         IdFTP.Abort;
      IdFTP.Quit;
    finally
      lstSerDir.Items.Clear;
      Status.SimpleText:='״̬���Ѿ��Ͽ����ӣ�';
    end
end;

procedure TfrmMain.btnUpLodeClick(Sender: TObject);
var
  i:Integer;
  filename:string;
begin
  if idFtp.Connected=False then
  begin
    ShowMessage('�������ӷ�������Ȼ���ϴ���');
    Exit;
  end;
  IdFTP.TransferType := ftBinary;
  for i := 0 to lstList.Items.Count-1 do
  begin
    lststatus.Items.Clear;
    filename:=ExtractFileName(lstList.Items.Strings[i]);
    uploading:=filename;
    IdFTP.Put(lstList.Items.Strings[i],filename);
  end;
  GetDir(IdFTP.RetrieveCurrentDir);
  moveIniFiles;
  btnUpLode.Enabled:=False;
end;

procedure TfrmMain.idFtpDisconnected(Sender: TObject);
begin
  Status.SimpleText:='״̬���Ѿ��Ͽ����ӣ�';
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
    wmRead: Status.SimpleText:='״̬�������ٶ�  '+S;
    wmWrite: Status.SimpleText:='״̬���ϴ��ٶ�  '+S;
  end;
  if AbortTransfer then
     IdFTP.Abort;
  ProgressBar1.Position:=AWorkCount;
  lblProgress.Caption :='���ڴ���:'+uploading+' (�����  '+IntToStr(AWorkCount)+'  �ֽ�)';
  Application.ProcessMessages;
  AbortTransfer := false;
end;

procedure TfrmMain.idFtpWorkBegin(Sender: TObject; AWorkMode: TWorkMode;
  const AWorkCountMax: Integer);
begin
  //Panel1.Visible:=true;
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
  Status.SimpleText := '״̬���ļ�������ϣ�';
  lblProgress.Caption:='';
  BytesToTransfer := 0;
  TransferrignData := false;
  AverageSpeed := 0;
end;

procedure TfrmMain.lstDirClick(Sender: TObject);
begin
  getSelectDir;
end;

{-------------------------------------------------------------------------------
  ������:    TfrmMain.getSelectDir�õ�ѡ���Ŀ¼����
  ����:      ����ΰ
  ����:      2006.02.09
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfrmMain.getSelectDir;
var
  i:Integer;
begin
  for i := 0 to lstDir.Items.Count-1 do
    if lstDir.Selected[i] then
      selectDirName:=lstDir.Items.Strings[i];
  edtMd5.Text:=selectDirName;
end;

{-------------------------------------------------------------------------------
  ������:    TfrmMain.moveIniFiles�ƶ��Ѿ����¹��ļ����ļ���ָ����λ�ã������´αȽ�
  ����:      ����ΰ
  ����:      2006.02.09
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfrmMain.moveIniFiles;
var
  sourcefile,decfile:string;
begin
  sourcefile:=selectDirName+'\'+ExtractFileName(selectDirName)+'md5.ini';
  decfile:=trim(edtOldMd5.Text)+'\'+ ExtractFileName(selectDirName)+'oldmd5.ini';
  if FileExists(decfile) then
    DeleteFile(decfile);
  MoveFile(PAnsiChar(sourcefile),PAnsiChar(decfile));
end;

end.

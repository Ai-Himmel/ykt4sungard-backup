unit main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, jpeg, SQLiteTable3, mmsystem, MPlayer, DB, commu,
  StdCtrls;

type
  Tmainfrm = class(TForm)
    mainp: TPanel;
    photo: TPanel;
    messagep: TPanel;
      name: TPanel;
    studentno: TPanel;
    welcome: TPanel;
    Timer1: TTimer;
    Timer2: TTimer;
    Image1: TImage;
    Label1: TLabel;
    Panel1: TPanel;
    Panel2: TPanel;
    Panel3: TPanel;
    procedure FormResize(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Timer1Timer(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);

  private
    endthread: integer;
    procedure setform;
    { Private declarations }
  public


    { Public declarations }
  end;

var
  mainfrm: Tmainfrm;

implementation

{$R *.dfm}

procedure showphoto(phicode: string);
var
  sSQL: string;
  imagestream: Tmemorystream;
  jpg: TJPEGImage;
begin
  try
    mainfrm.image1.Picture.assign(nil);
  except
  end;
  sSQL := 'select t1.photo from t_cif_photo t1,t_pif_card t2 where t1.cut_id=t2.cosumer_id and t2.physical_no=' + '''' + trim(phicode) + ''' and t2.state_id=''1000''';
  if debug = 'true' then
    writelog(sSql);
  funcSelectSql(sSql, DBQuery);
  if DBQuery.RecordCount < 1 then
  begin
  end
  else
  begin
    imagestream := Tmemorystream.Create;
    try
      jpg := TJPEGImage.Create;
      imagestream.Position := 0;
      TBlobField(DBQuery.FieldByName('PHOTO')).SaveToStream(imagestream);
      imagestream.Position := 0;
      jpg.LoadFromStream(imagestream);
      mainfrm.Image1.Picture.Assign(jpg);
    finally
      imagestream.Free;
    end;
  end;
  DBQuery.Close;
end;

procedure finduse(phicode: string);
var
  i: integer;
  sSql: string;
  sltb: TSQLIteTable;
  cmd: string;
  no: integer;
  cut_name: string;
  stuemp_no: string;
  serno: string;
  cardid: string;
  bgtime: string;
  endtime: string;
  time: string;
  nowtime: string;
begin
  mainfrm.Label1.Caption := phicode;
  bgtime := g_begintime;
  endtime := g_endtime;

  time := FormatdateTime('hhmmss', now());
  if (time < bgtime) or (time > endtime) then
  begin
    mainfrm.welcome.Caption := '对不起，现在不是就餐时间！';
    exit;
  end;

  showphoto(phicode);
  try
    sltb := slDb.GetTable('SELECT * FROM t_pif_cosumer where  phy_id=''' + phicode + '''');
  //FOR TEST
    if sltb.Count > 0 then
    begin
      cut_name := sltb.FieldAsString(sltb.FieldIndex['cut_name']);
      stuemp_no := sltb.FieldAsString(sltb.FieldIndex['stuemp_no']);
      cardid := sltb.FieldAsString(sltb.FieldIndex['card_id']);
      try
        sltb := slDb.GetTable('SELECT * FROM T_TIF_LUNCHRCVDTL where  TX_DATE=''' + FormatdateTime('yyyymmdd', now()) + ''' and CARD_NO=''' + cardid + '''');
      except
        writelog('查询T_TIF_LUNCHRCVDTL表错误！');
      end;
      if sltb.Count > 0 then
      begin
        mainfrm.name.Caption := '姓名：' + cut_name;
        mainfrm.studentno.Caption := '学工号：' + stuemp_no;
        mainfrm.welcome.Caption := cut_name + '   对不起！您今日已在此消费过！';
        cmd := ExtractFilePath(Application.ExeName) + voice + 'sorry.wav';
        SndPlaySound(pchar(cmd), SND_ASYNC or SND_ASYNC);
      end
      else
      begin
        try
          sltb := slDb.GetTable('SELECT max(SERIAL_NO) as SERIAL_NO FROM T_TIF_LUNCHRCVDTL');
          if sltb.Count > 0 then
          begin
            serno := sltb.FieldAsString(sltb.FieldIndex['SERIAL_NO']);
            if serno = '' then
              serno := '0';
            no := strtoint(serno) + 1;
            serno := inttostr(no);
          end
          else
          begin
            serno := '1';
          end;
//          sldb.BeginTransaction;
          sSQL := 'INSERT INTO T_TIF_LUNCHRCVDTL(TX_DATE,TX_TIME,CARD_NO,DEVICE_ID,SERIAL_NO,STATUS) VALUES (';
          sSQL := sSQL + '"' + FormatdateTime('yyyymmdd', now()) + '",';
          sSQL := sSQL + '"' + FormatdateTime('hhmmss', now()) + '",';
          sSQL := sSQL + '"' + cardid + '",';
          sSQL := sSQL + '"' + DEVPHYID + '",';
          sSQL := sSQL + '"' + serno + '",';
          sSQL := sSQL + '"' + '1' + '"';
          sSQL := sSQL + ');';
      //do the insert
          sldb.ExecSQL(sSQL);
//          sldb.Commit;
          mainfrm.name.Caption := '姓名：' + cut_name;
          mainfrm.studentno.Caption := '学工号：' + stuemp_no;
          mainfrm.welcome.Caption := cut_name + '   欢迎光临！';
          cmd := ExtractFilePath(Application.ExeName) + voice + 'welcome.wav';
          SndPlaySound(pchar(cmd), SND_ASYNC or SND_ASYNC);
        except
        end;
      end;
    end
    else
    begin
      mainfrm.image1.Picture.assign(nil);
      mainfrm.name.Caption := '姓名：';
      mainfrm.studentno.Caption := '学工号：';
      mainfrm.welcome.Caption := cut_name + '   对不起，你没有被分配权限！';
      cmd := ExtractFilePath(Application.ExeName) + voice + 'security.wav';
      SndPlaySound(pchar(cmd), SND_ASYNC or SND_ASYNC);
    end;
  finally
    sltb.Free;
  end;
end;

function ReadCardPhyID(var CardIdString: string): smallint;
var
  ucSerialNo: pchar;
  ucType: pchar;
begin
  ucSerialNo := nil;
  ucType := nil;
  ReallocMem(ucSerialNo, 9);
  ReallocMem(ucType, 3);
  Result := RequestCard(ucSerialNo, ucType);
  if Result = 0 then
  begin
    CardIdString := ucSerialNo;
  end;
end;

function ThreadreadcardFunc(P: pointer): Longint; stdcall;
var
  phicd: string;
  oldphicd: string;
  S: string;
  endthread: integer;
begin

  while 1 = 1 do
  begin
  //  ReadCardInfo(PCM);
    sleep(100000);
  end;

end;

procedure Tmainfrm.setform;
begin
  photo.Width := 300;
  photo.Height := 400;
  name.Height := 70;
  studentno.Height := 70;
  photo.Top := self.Top + ((self.Height - photo.Width) div 4);
  photo.Left := (self.Width div 2) - photo.Width - 20;
  messagep.Left := photo.Left + photo.Width + 10;
  messagep.Top := photo.Top;
  messagep.Width := 400;
  messagep.Height := photo.Height;
  name.Width := messagep.Width - 30;
  studentno.Width := name.Width;
  name.Top := messagep.Top + ((messagep.Height - (photo.Width + name.Height)) div 2);
  studentno.Top := name.Top + name.Height + 20;
  studentno.Left := name.Left;
  welcome.Height := self.Height div 4;
  //Image1.Top := photo.Top;
 // Image1.Left := photo.Left;
  //name.Left := messagep.Left;
  if (endthread > 1) then
  begin
  end;
end;

procedure Tmainfrm.FormResize(Sender: TObject);
begin
  setform;
end;

procedure Tmainfrm.FormShow(Sender: TObject);
var
  hThread: Thandle; //定义一个句柄
  ThreadID: DWord;
  sltb: TSQLIteTable;
  nowtime: string;
begin
  self.WindowState := wsMaximized;
  setform;
  procGetIniInfo;
  Image1.AutoSize := False;
  Image1.Stretch := False;
  Image1.Center := true;
  Image1.Proportional := True; //自动按比例显示
 // hthread := CreateThread(nil, 0, @ThreadreadcardFunc, nil, 0, ThreadID);
  mainfrm.name.Caption := '暂无卡片';
  mainfrm.studentno.Caption := '暂无卡片';
  mainfrm.welcome.Caption := '欢迎光临！';
  if updatetime = 0 then begin
    Timer2.Interval := updatetime;
    timer2.Enabled := false;
  end else begin
    Timer2.Interval := updatetime;
    timer2.Enabled := true;
  end;

  try
    sltb := slDb.GetTable('SELECT * FROM T_TIF_LUNCHRDATE');
    if sltb.Count > 0 then
    begin
      nowtime := FormatdateTime('yyyymmdd hhmmss', now());
      g_begintime := sltb.FieldAsString(sltb.FieldIndex['BG_TIME']);
      g_endtime := sltb.FieldAsString(sltb.FieldIndex['ED_TIME']);
      mainfrm.Panel1.Caption := '就餐开始时间：' + g_begintime;
      mainfrm.Panel2.Caption := '就餐结束时间：' + g_endtime;
      mainfrm.Panel3.Caption := '现在时间：' + nowtime;

    end;
  finally
    sltb.Free;
  end;



  // sndPlaySound(nil, 0);
end;

procedure Tmainfrm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  sldb.Free;
  CloseMF;
  procDestroyDBSET;
end;

procedure Tmainfrm.Timer1Timer(Sender: TObject);
var
  ret: integer;
  phicd: string;

begin
                // StrCopy(g_begintime, PChar(Label1.Caption));
  mainfrm.Panel1.Caption := '开始时间：' + copy(g_begintime,1,2) + ':' +copy(g_begintime,3,2)+':'+copy(g_begintime,5,2);
  mainfrm.Panel2.Caption := '结束时间：' + copy(g_endtime,1,2) + ':' +copy(g_endtime,3,2)+':'+copy(g_endtime,5,2);
  mainfrm.Panel3.Caption := '现在时间：' + FormatdateTime('yyyy-mm-dd hh:mm:ss', now());

  ret := ReadCardPhyID(phicd);
  //phicd:='1EC6A932';
  if phicd <> '' then
    if (phicd <> oldphicd) or (oldphicd = '') then
    begin
      oldphicd := phicd;
      finduse(phicd);

    end;

end;

procedure Tmainfrm.Timer2Timer(Sender: TObject);
begin
  procUploaddata;
  procDownloaddata;
end;




end.


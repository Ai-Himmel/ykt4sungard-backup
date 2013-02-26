unit main;

interface

uses
    Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
    Dialogs, ExtCtrls, jpeg, SQLiteTable3, mmsystem, MPlayer, DB, commu,
    StdCtrls;

type
    Tmainfrm = class(TForm)
        mainp: TPanel;
        Timer1: TTimer;
        Timer2: TTimer;
        Panel1: TPanel;
        Panel3: TPanel;
        Panel2: TPanel;
        photo: TPanel;
        Image1: TImage;
        messagep: TPanel;
        philab: TLabel;
            name: TPanel;
        department: TPanel;
        phiinput: TEdit;
        studentno: TPanel;
        welcome: TPanel;
        procedure FormResize(Sender: TObject);
        procedure FormShow(Sender: TObject);
        procedure FormClose(Sender: TObject; var Action: TCloseAction);
        procedure Timer1Timer(Sender: TObject);
        procedure Timer2Timer(Sender: TObject);

    private
        //        endthread: integer;
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
    sSQL, sSQL2, cmd: string;
    cut_name, stuemp_no, deptment: string;
    imagestream: Tmemorystream;
    jpg: TJPEGImage;
begin
    try
        mainfrm.image1.Picture.assign(nil);
    except
    end;
    sSQL := 'select  t3.custname, t3.deptname, t3.stuempno,cd.status from  t_card cd left join '
        + ' (select cu.custid,dp.deptname,cu.stuempno,cu.custname from t_customer cu '
        + ' left join t_dept dp on cu.deptcode=dp.deptcode) t3 on cd.custid=t3.custid '
        + ' where  cd.custid=t3.custid '
        + ' and cd.cardphyid=''' + trim(phicode) + ''' '
        + ' and cd.status=''1'' ';

    sSQL2 := 'select t1.photo from t_photo t1, t_card t2 where t1.custid = t2.custid  and t2.cardphyid='
        + '''' + trim(phicode) + ''' and t2.status=''1''';
    if debug = 'true' then
        writelog(sSql);
    funcConnectDB;

    funcSelectSql(sSql, DBQuery);
    funcSelectSql(sSql2, DBQueryTmp);
    if DBQuery.RecordCount < 1 then begin
        mainfrm.image1.Picture.assign(nil);
        mainfrm.department.Caption := '    部门：';
        mainfrm.name.Caption := '    姓名：';
        mainfrm.studentno.Caption := '    学工号：';
        mainfrm.welcome.Caption := cut_name + '   对不起，你没有被分配权限！';
        cmd := ExtractFilePath(Application.ExeName) + voice + 'security.wav';
        SndPlaySound(pchar(cmd), SND_ASYNC or SND_ASYNC);
    end
    else begin
        if DBQueryTmp.RecordCount > 0 then begin
            imagestream := Tmemorystream.Create;
            try
                if (TBlobfield(DBQueryTmp.FieldByName('PHOTO')).IsNull) then begin
                end
                else begin
                    jpg := TJPEGImage.Create;
                    imagestream.Position := 0;
                    TBlobField(DBQueryTmp.FieldByName('PHOTO')).SaveToStream(imagestream);
                    imagestream.Position := 0;
                    jpg.LoadFromStream(imagestream);
                    mainfrm.Image1.Picture.Assign(jpg);
                end
            finally
                imagestream.Free;
            end;
        end;
        cut_name := DBQuery.FieldByName('custname').AsString;
        stuemp_no := DBQuery.FieldByName('stuempno').AsString;
        deptment := DBQuery.FieldByName('deptname').AsString;
        mainfrm.name.Caption := '    姓名：' + cut_name;
        mainfrm.studentno.Caption := '    学工号：' + stuemp_no;
        mainfrm.department.Caption := '    部门：' + deptment;
        mainfrm.welcome.Caption := cut_name + '   欢迎光临！';
        cmd := ExtractFilePath(Application.ExeName) + voice + 'welcome.wav';
        SndPlaySound(pchar(cmd), SND_ASYNC or SND_ASYNC);
    end;
    DBQuery.Close;
    DBQueryTmp.Close;
end;

procedure finduse(phicode: string);
begin
    showphoto(phicode);
end;

function ThreadreadcardFunc(P: pointer): Longint; stdcall;
begin

    while 1 = 1 do begin
        //  ReadCardInfo(PCM);
        sleep(100000);
    end;

end;

procedure Tmainfrm.setform;
begin
    { photo.Width := 600;
      photo.Height := 800;
      name.Height := 70;
      philab.Height:=70;
      phiinput.Height:=70;
      department.Height:=70;
      studentno.Height := 70;
      photo.Top := self.Top + ((self.Height - photo.Width) div 4)+5;
      photo.Left := (self.Width div 2) - photo.Width - 20;
      messagep.Left := photo.Left + photo.Width + 10;
      messagep.Top := photo.Top;
      messagep.Width := 500;
      messagep.Height := photo.Height;
      philab.Top:= messagep.Top-50;
      }
    //  philab.Left:= messagep.Left+5;
    //  phiinput.Top:=  philab.Top;
    // philab.Left:=  philab.Left+philab.Width+5;
     // name.Width := messagep.Width - 30;
     // studentno.Width := name.Width;
     // name.Top := messagep.Top + ((messagep.Height - (photo.Width + name.Height)) div 2);
     // studentno.Top := name.Top + name.Height + 20;
    //  studentno.Left := name.Left;
    //  welcome.Height := self.Height div 4;
      //Image1.Top := photo.Top;
     // Image1.Left := photo.Left;
      //name.Left := messagep.Left;

end;

procedure Tmainfrm.FormResize(Sender: TObject);
begin
    setform;
end;

procedure Tmainfrm.FormShow(Sender: TObject);
//var
//    hThread: Thandle; //定义一个句柄
//    ThreadID: DWord;
//  sltb: TSQLIteTable;
//    nowtime: string;
begin
    self.WindowState := wsMaximized;
    setform;
    procGetIniInfo;
    Image1.AutoSize := False;
    Image1.Stretch := False;
    Image1.Center := true;
    Image1.Proportional := True; //自动按比例显示
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
end;

procedure Tmainfrm.FormClose(Sender: TObject; var Action: TCloseAction);
begin

    procDestroyDBSET;
end;

procedure Tmainfrm.Timer1Timer(Sender: TObject);
var
    //    ret: integer;
    phicd: string;

begin

    mainfrm.Panel3.Caption := '现在时间：' + FormatdateTime('yyyy-mm-dd hh:mm:ss', now());

    phiinput.SetFocus;
    phicd := trim(phiinput.Text);
    phicd := UpperCase(phicd);
    if phicd <> '' then
        if (phicd <> oldphicd) or (oldphicd = '') then begin
            oldphicd := phicd;
            phiinput.Text := '';
            finduse(phicd);
        end;

end;

procedure Tmainfrm.Timer2Timer(Sender: TObject);
begin
    // procUploaddata;
   //  procDownloaddata;
end;

end.


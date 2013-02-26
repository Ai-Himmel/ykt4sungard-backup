unit main;

interface

uses
    Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
    Dialogs, ExtCtrls, jpeg, mmsystem, MPlayer, DB, commu,
    StdCtrls, ADODB, DateUtils;

type
    Tmainfrm = class(TForm)
        mainp: TPanel;
        photo: TPanel;
        messagep: TPanel;
        name: TPanel;
        studentno: TPanel;
        welcome: TPanel;
        Timer1: TTimer;
        Image1: TImage;
        Label1: TLabel;
        Panel3: TPanel;
        Pbala: TPanel;
        entertime: TPanel;
        Timer2: TTimer;
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

    PTtagPackage = ^TtagPackage;

    TtagPackage = record
        strvarname: array [0 .. 63] of char;
        nint: integer;
        f: Single;
        dw: longint;
        dl1: double;
    end;

var
    mainfrm: Tmainfrm;

implementation

{$R *.dfm}

function get_STAGE_VALUE: string;
var
    sSQL, STAGE_VALUE: string;
    week: integer;
begin
    // 收费  查询是否指定特殊日期
    sSQL := 'select t1.STAGE_VALUE from ykt_cur.T_STATIUM_FEEDATE t1 where  t1.FEE_DATA=''' + FormatdateTime
      ('yyyymmdd', now()) + '''';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.RecordCount > 0 then begin
        // 特殊日期
        STAGE_VALUE := DBQuerytmp.FieldByName('STAGE_VALUE').AsString;
    end
    else begin
        // 普通日期
        week := dayofweek(date);
        sSQL := 'select t1.STAGE_VALUE from ykt_cur.T_STATIUM_FEEDATE t1 where  t1.DATA_ID=' + inttostr(week);
        if debug = 'true' then
            writelog(sSQL);
        funcSelectSql(sSQL, DBQuerytmp);
        if DBQuerytmp.RecordCount > 0 then begin
            STAGE_VALUE := DBQuerytmp.FieldByName('STAGE_VALUE').AsString;
        end;
    end;
    result := STAGE_VALUE;
end;

function getviptime(stuemp_no: string; cut_name: string): boolean;
var
    sSQL: string;
    TIMS: integer;
begin
    result := true;
    sSQL := 'select t.TIMS from ykt_cur.T_STATIUM_VIPMNG t where   t.stuemp_no=''' + stuemp_no + '''';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.RecordCount > 0 then begin
        TIMS := DBQuerytmp.FieldByName('TIMS').AsInteger;
        if TIMS <= 0 then begin
            mainfrm.Pbala.Caption := 'VIP次数：' + inttostr(TIMS);
            mainfrm.name.Caption := '姓名：  ' + cut_name;
            mainfrm.studentno.Caption := '学工号：' + stuemp_no;
            mainfrm.welcome.Caption := cut_name + '   对不起！VIP次数已消费完！';
            result := false;
        end;
    end;
end;

function getmaxserno: integer;
var
    sSQL: string;
    SERIAL_NO: integer;
begin

    sSQL := 'select max(SERIAL_NO) as SERIAL_NO from ykt_cur.T_STATIUM_RCVDTL';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.FieldByName('SERIAL_NO').AsInteger = 0 then begin
        SERIAL_NO := 1;
    end
    else begin
        SERIAL_NO := DBQuerytmp.FieldByName('SERIAL_NO').AsInteger + 1;
    end;

    result := SERIAL_NO;
end;

function getmoney(fee: double; min: integer): integer;
var
    minmoney, totalmoney, outmin, myhour: integer;

begin
    if min > 10 then begin
        myhour := min div 60;
        outmin := min mod 60;
        totalmoney := round(myhour * fee * 100);
        if totalmoney = 0 then begin
            if (outmin) > 10 then begin
                minmoney := round(fee * 100);
            end
            else begin
                minmoney := 0;
            end;
        end
        else begin
            if (outmin > 30) then begin
                minmoney := round(fee * 100);
            end
            else begin
                minmoney := round(fee * 100 * 0.5);
            end;
        end;
        totalmoney := totalmoney + minmoney;

    end
    else begin
        totalmoney := 0;
    end;
    result := totalmoney;
end;

function getfeetime(STAGE_VALUE: string; out_time: string; in_TIME: string): integer;
var
    sSQL, getedtime, begintime, getbgtime, endtime, VALUE: string;
    min: integer;
begin
    VALUE := GetNextStr(STAGE_VALUE);
    min := 0;
    while VALUE <> '' do begin
        begintime := '';
        endtime := '';
        getbgtime := '';
        getedtime := '';
        sSQL := 'select t.BEGIN_TIME,t.END_TIME from ykt_cur.T_STATIUM_STAGE t where  t.STAGE_ID=' + VALUE + '';
        if debug = 'true' then
            writelog(sSQL);
        funcSelectSql(sSQL, DBQuerytmp);
        if DBQuerytmp.RecordCount > 0 then begin
            begintime := DBQuerytmp.FieldByName('BEGIN_TIME').AsString;
            endtime := DBQuerytmp.FieldByName('END_TIME').AsString;
        end;
        if in_TIME > begintime then begin
            getbgtime := in_TIME;
        end
        else begin
            getbgtime := begintime;
        end;
        if out_time > endtime then begin
            getedtime := endtime;
        end
        else begin
            getedtime := out_time;
        end;
        if ((getedtime <> '') and (getbgtime <> '')) then
            min := min + (strtoint(copy(getedtime, 0, 2)) - strtoint(copy(getbgtime, 0, 2))) * 60 +
              (strtoint(copy(getedtime, 3, 2)) - strtoint(copy(getbgtime, 3, 2)));
        VALUE := GetNextStr(STAGE_VALUE);
    end;
    result := min;
end;

function tranvip(card_no: string; stuemp_no: string): integer;
var
    sSQL: string;
    SERIAL_NO, TIMS: integer;
begin
    sSQL := 'select t.TIMS from ykt_cur.T_STATIUM_VIPMNG t where   t.stuemp_no=''' + stuemp_no + '''';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.RecordCount > 0 then begin
        TIMS := DBQuerytmp.FieldByName('TIMS').AsInteger;
        sSQL := 'update ykt_cur.T_STATIUM_VIPMNG t set t.TIMS=' + inttostr(TIMS - 1)
          + ' where t.stuemp_no=''' + stuemp_no + '''';
        if debug = 'true' then
            writelog(sSQL);
        if not funcExcuteSql(sSQL, DBQueryBaK) then begin
            if debug = 'true' then begin
                writelog('修改数据失败！');
            end
        end;
    end;
    sSQL :=
      'select t.SERIAL_NO,t.in_DATE,t.in_TIME from ykt_cur.T_STATIUM_RCVDTL t where  t.CARD_NO=' +
      card_no + ' and t.STATUS=''1''';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.RecordCount > 0 then begin
        SERIAL_NO := DBQuerytmp.FieldByName('SERIAL_NO').AsInteger;
    end;
    sSQL := 'update ykt_cur.T_STATIUM_RCVDTL t set t.VIP_FLAG=''1'',STATUS=''2'',OUT_DATE=''' + FormatdateTime
      ('yyyymmdd', now()) + ''',OUT_TIME=''' + FormatdateTime('hhmmss', now()) + ''' where t.SERIAL_NO=' + inttostr
      (SERIAL_NO) + '';
    if debug = 'true' then
        writelog(sSQL);
    if not funcExcuteSql(sSQL, DBQueryBaK) then begin
        if debug = 'true' then begin
            writelog('修改数据失败！');
        end
    end;
    result := TIMS - 1;
end;

function totalmoney(STAGE_VALUE: string; card_no: string; FEE_TYPE: integer; stuemp_no: string): double;
var
    fee: double;
    TIMS, timetotal, t, totalmoney, ret, termid, SERIAL_NO, min: integer;
    cmd, STATUS, sSQL, VALUE: string;
    in_DATE, timetotalstr, begintime, endtime, in_TIME, out_time, getbgtime, getedtime: string;
begin
    result := 0;
    totalmoney := 0;
    SERIAL_NO := 0;
    fee := 0;
    sSQL := 'select t.MONEY from ykt_cur.T_STATIUM_FEEMNG t where  t.FEE_TYPE=' + inttostr(FEE_TYPE) + '';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.RecordCount > 0 then begin
        fee := DBQuerytmp.FieldByName('MONEY').AsFloat;
    end;
    sSQL :=
      'select t.SERIAL_NO,t.in_DATE,t.in_TIME from ykt_cur.T_STATIUM_RCVDTL t where  t.CARD_NO=' +
      card_no + ' and t.STATUS=''1''';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.RecordCount > 0 then begin
        SERIAL_NO := DBQuerytmp.FieldByName('SERIAL_NO').AsInteger;
        in_DATE := DBQuerytmp.FieldByName('in_DATE').AsString;
        in_TIME := copy(DBQuerytmp.FieldByName('in_TIME').AsString, 0, 4);
        if in_DATE = FormatdateTime('yyyymmdd', now()) then begin
            out_time := copy(FormatdateTime('hhmmss', now()), 0, 4);
        end
        else begin
            out_time := '2300';
        end;
        timetotal := (strtoint(copy(out_time, 0, 2)) - strtoint(copy(in_TIME, 0, 2))) * 60 +
          (strtoint(copy(out_time, 3, 2)) - strtoint(copy(in_TIME, 3, 2)));
        mainfrm.entertime.Caption := '进场时长：' + inttostr(timetotal div 60) + '时' + inttostr(timetotal mod 60) + '分';
    end;
    min := getfeetime(STAGE_VALUE, out_time, in_TIME);
    totalmoney := getmoney(fee, min);
    ret := 1;

    if totalmoney > 0 then begin
        ret := SMT_PacketDelMomey(totalmoney, termid);
        sleep(_internal);
    end;
    if ((ret > 0) and (totalmoney <> 0)) then begin
        ret := FuncShowMessage(Application.Handle, '金额不足或扣卡失败！请付现' + floattostr(totalmoney / 100) + '（元）！', 2);
    end
    else begin
        if in_DATE < FormatdateTime('yyyymmdd', now()) then begin
            oldphicd := '';
            FuncShowMessage(Application.Handle, '你上次出场没有刷卡,请在刷一次进场！', 2);
        end
    end;
    STATUS := '2';

    sSQL := 'update ykt_cur.T_STATIUM_RCVDTL t set t.AMOUNT=' + floattostr(totalmoney / 100)
      + ',STATUS=''' + STATUS + ''',OUT_DATE=''' + FormatdateTime('yyyymmdd', now())
      + ''',OUT_TIME=''' + out_time + ''' where t.SERIAL_NO=' + inttostr(SERIAL_NO) + '';

    if debug = 'true' then
        writelog(sSQL);
    if not funcExcuteSql(sSQL, DBQueryBaK) then begin
        if debug = 'true' then begin
            writelog('修改数据失败！');
        end
    end;
    result := totalmoney / 100;
end;

function GetFieldImg(Field: TField): TJPEGImage;
var
    MS: TMemoryStream;
begin
    result := TJPEGImage.Create;
    MS := TMemoryStream.Create;
    TBlobField(Field).SaveToStream(MS);
    MS.Position := 0;
    result.LoadFromStream(MS);
    MS.Free;
end;

procedure showphoto(stuemp_no: string);
var
    sSQL: string;
    // imagestream: Tmemorystream;
    // jpg: TJPEGImage;
    F3: TADOBlobStream;
    M1: TMemoryStream; // 内存流，
    Fjpg: TJPEGImage; // 用Image 存放 Jpeg 的中间形式，
begin
    try
        mainfrm.Image1.Picture.assign(nil);
    except
    end;
    // ykt_cur.t_cif_photo
    sSQL := 'select t.photo from ykt_cur.v_photo t where  t.STUEMP_NO=' + '''' + trim(stuemp_no) + '''';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.RecordCount < 1 then begin
    end
    else begin
        DBQuerytmp.Edit;
        F3 := TADOBlobStream.Create(TBlobField(DBQuerytmp.FieldByName('PHOTO')), bmread);
        try
            if TBlobField(DBQuerytmp.FieldByName('PHOTO')).AsString <> null then
                TBlobField(DBQuerytmp.FieldByName('PHOTO')).SaveToStream(F3);
            Fjpg := TJPEGImage.Create;
            try
                F3.Position := 0;
                mainfrm.Image1.Picture.Graphic := nil;
                if F3.Size > 100 then begin
                    Fjpg.LoadFromStream(F3);
                    mainfrm.Image1.Picture.Graphic := Fjpg;
                end;
            finally
                Fjpg.Free;
            end;
        finally
            F3.Destroy;

        end;
    end;
    DBQuerytmp.Close;
end;

procedure finduse(cardno: string; bala: double);
var
    i, week, SERIAL_NO: integer;
    sSQL: string;
    cmd: string;
    no: integer;
    state, cut_name: string;
    stuemp_no: string;
    serno: string;
    cardid: string;
    TIMS, card_no, FEE_TYPE: integer;
    intime, time: string;
    MONEY: double;
    STAGE_VALUE, VALUE: string;

begin
    state := '';
    stuemp_no := '';
    cut_name := '';
    time := FormatdateTime('hhmmss', now());
    try
        mainfrm.Image1.Picture.assign(nil);
    except
    end;
    sSQL := 'select t1.stuemp_no,t1.cut_name,t1.fee_Type,t2.STATE_ID,t2.CARD_ID,t3.CUR_BALA from YKT_CUR.T_CIF_CUSTOMER t1,ykt_cur.t_pif_card t2,YKT_CUR.T_AIF_ACCOUNT t3 where t1.CUT_ID = t2.COSUMER_ID  and t2.COSUMER_ID=t3.CUSTOMER_ID and  t2.CARD_ID=' + trim(cardno) + ' and t2.state_id=''1000'' and t3.CURRENT_STATE=1';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuery);
    if DBQuery.RecordCount < 1 then begin
        mainfrm.name.Caption := '姓名：  ';
        mainfrm.studentno.Caption := '学工号：';
        mainfrm.welcome.Caption := cut_name + '   对不起，你的卡状态不正常！';
    end
    else begin
        mainfrm.Pbala.Caption := '';
        FEE_TYPE := DBQuery.FieldByName('fee_Type').AsInteger;
        state := DBQuery.FieldByName('state_id').AsString;
        stuemp_no := DBQuery.FieldByName('stuemp_no').AsString;
        cut_name := DBQuery.FieldByName('cut_name').AsString;
        card_no := DBQuery.FieldByName('CARD_ID').AsInteger;
        mainfrm.Label1.Caption := stuemp_no;
        showphoto(stuemp_no);
        mainfrm.entertime.Caption := '进场时长：0时0分';
        sSQL := 'select *  from ykt_cur.T_STATIUM_FEEMNG where FEE_TYPE=' + inttostr(FEE_TYPE) + '';
        if debug = 'true' then
            writelog(sSQL);
        DBQuery.Close;
        funcSelectSql(sSQL, DBQuery);
        MONEY := DBQuery.FieldByName('MONEY').AsFloat;
    end;
    if state <> '1000' then begin
        mainfrm.Pbala.Caption := '';
        mainfrm.name.Caption := '姓名：  ' + cut_name;
        mainfrm.studentno.Caption := '学工号：' + stuemp_no;
        mainfrm.welcome.Caption := cut_name + '   对不起！卡状态不正常！';
        exit;
    end;
    if bala < MONEY then begin
        mainfrm.Pbala.Caption := '卡余额：' + floattostr(bala);
        mainfrm.name.Caption := '姓名：  ' + cut_name;
        mainfrm.studentno.Caption := '学工号：' + stuemp_no;
        mainfrm.welcome.Caption := cut_name + '   对不起！帐号卡余额不足！';
        exit;
    end;
    if FEE_TYPE = 100 then begin
        oldphicd := '';
        if not getviptime(stuemp_no, cut_name) then begin
            writelog('vip次数已经用完！');
            exit;
        end;
        SERIAL_NO := getmaxserno;
        sSQL :=
          'insert into ykt_cur.T_STATIUM_RCVDTL(DEVICE_ID,CARD_NO,SERIAL_NO,VIP_FLAG,AMOUNT,STATUS,in_DATE,in_TIME,OUT_DATE,OUT_TIME)'
          + ' values(''' + DEVPHYID + ''',' + inttostr(card_no) + ',' + inttostr(SERIAL_NO)
          + ',''0'',0,' + '''1'',''' + FormatdateTime('yyyymmdd', now()) + ''',''' + FormatdateTime('hhmmss', now()) + ''','' '','' '')';
        if debug = 'true' then
            writelog(sSQL);
        if not funcExcuteSql(sSQL, DBQueryBaK) then begin
            writelog('插入数据失败！');
        end;
        TIMS := tranvip(inttostr(card_no), stuemp_no);
        mainfrm.Pbala.Caption := 'vip可用次数：' + inttostr(TIMS);
        mainfrm.name.Caption := '姓名：  ' + cut_name;
        mainfrm.studentno.Caption := '学工号：' + stuemp_no;
        mainfrm.welcome.Caption := cut_name + '   欢迎光临！';
        exit;
    end;
    sSQL := 'select t1.SERIAL_NO from ykt_cur.T_STATIUM_RCVDTL t1 where  t1.CARD_NO=' + inttostr(card_no)
      + ' and t1.STATUS=''1''';
    if debug = 'true' then
        writelog(sSQL);
    funcSelectSql(sSQL, DBQuerytmp);
    if DBQuerytmp.RecordCount < 1 then begin
        SERIAL_NO := getmaxserno;
        sSQL :=
          'insert into ykt_cur.T_STATIUM_RCVDTL(DEVICE_ID,CARD_NO,SERIAL_NO,VIP_FLAG,AMOUNT,STATUS,in_DATE,in_TIME,OUT_DATE,OUT_TIME)'
          + ' values(''' + DEVPHYID + ''',' + inttostr(card_no) + ',' + inttostr(SERIAL_NO)
          + ',''0'',0,' + '''1'',''' + FormatdateTime('yyyymmdd', now()) + ''',''' + FormatdateTime('hhmmss', now()) + ''','' '','' '')';
        if debug = 'true' then
            writelog(sSQL);
        if not funcExcuteSql(sSQL, DBQueryBaK) then begin
            writelog('插入数据失败！');
        end;
        mainfrm.Pbala.Caption := '卡余额：' + floattostr(bala);
        mainfrm.name.Caption := '姓名：  ' + cut_name;
        mainfrm.studentno.Caption := '学工号：' + stuemp_no;
        mainfrm.welcome.Caption := cut_name + '   欢迎光临！';
        exit;
    end;

    STAGE_VALUE := get_STAGE_VALUE;
    bala := totalmoney(STAGE_VALUE, inttostr(card_no), FEE_TYPE, stuemp_no);
    mainfrm.Pbala.Caption := '本次消费：' + floattostr(bala);
    mainfrm.name.Caption := '姓名：  ' + cut_name;
    mainfrm.studentno.Caption := '学工号：' + stuemp_no;
    mainfrm.welcome.Caption := cut_name + '   欢迎再次光临！';

end;

function ReadCardID(var CardIdString: string): smallint;
var
    ucSerialNo: integer;
begin

    result := ReadCardNO(@ucSerialNo);
    if result = 0 then begin
        CardIdString := inttostr(ucSerialNo);
    end;
end;

procedure Tmainfrm.setform;
begin
    photo.Width := 400;
    photo.Height := 500;
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
    Pbala.Top := studentno.Top + studentno.Height + 20;
    Pbala.Width := studentno.Width;
    Pbala.Height := studentno.Height;
    entertime.Top := Pbala.Top + Pbala.Height + 20;
    entertime.Width := Pbala.Width;
    entertime.Height := Pbala.Height;

    welcome.Height := self.Height div 4;
    if (endthread > 1) then begin
    end;
end;

procedure Tmainfrm.FormResize(Sender: TObject);
begin
    setform;
end;

procedure Tmainfrm.FormShow(Sender: TObject);
var
    hThread: Thandle; // 定义一个句柄
    ThreadID: DWord;
    nowtime: string;
begin
    self.WindowState := wsMaximized;
    setform;
    procGetIniInfo;
    Image1.AutoSize := false;
    Image1.Stretch := false;
    Image1.Center := true;
    Image1.Proportional := true; // 自动按比例显示
    mainfrm.name.Caption := '暂无卡片';
    mainfrm.studentno.Caption := '暂无卡片';
    mainfrm.welcome.Caption := '欢迎光临！';
    mainfrm.Image1.Picture.LoadFromFile('log.jpg');
    entertime.Caption := '进场时间：';
end;

procedure Tmainfrm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
    SMT_CloseMF280;
    procDestroyDBSET;
end;

procedure Tmainfrm.Timer1Timer(Sender: TObject);
var
    MONEY, ret: integer;
    phicd: string;
    bala: double;

begin
    mainfrm.Panel3.Caption := '现在时间：' + FormatdateTime('yyyy-mm-dd hh:mm:ss', now());
    ret := ReadCardID(phicd);
    // phicd := '0704060374';
    if phicd <> '' then
        if (phicd <> oldphicd) or (oldphicd = '') then begin
            oldphicd := phicd;
            bala := 0;
            ret := SMT_ReadBalance(MONEY);
            SMT_ControlBuzzer;
            sleep(2000);
            bala := MONEY / 100;
            if ret > 0 then
                exit;
            finduse(phicd, bala);
        end;

end;

procedure Tmainfrm.Timer2Timer(Sender: TObject);
begin
    oldphicd := '';
    mainfrm.Pbala.Caption := '';
    mainfrm.name.Caption := '姓名：  ';
    mainfrm.studentno.Caption := '学工号：';
    mainfrm.welcome.Caption := '请刷卡！';
    entertime.Caption := '进场时间：';
    mainfrm.Image1.Picture.LoadFromFile('log.jpg');
end;

end.

unit LoginU;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ExtCtrls, SQLiteTable3, commu;

type
  TLoginFrm = class(TForm)
    bbnOK: TBitBtn;
    bbnCancel: TBitBtn;
    mess: TPanel;
    procedure bbnCancelClick(Sender: TObject);
    procedure bbnOKClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    beging:boolean;
    isTerminate: boolean;
  end;

var
  LoginFrm: TLoginFrm;

implementation


{$R *.dfm}

procedure TLoginFrm.bbnCancelClick(Sender: TObject);
begin
  isTerminate := true;
  Close;
end;

procedure TLoginFrm.bbnOKClick(Sender: TObject);
var
  ret: integer;
  sltb: TSQLIteTable;
  sSql: string;
begin

  procGetIniInfo;
  ret := ConnectMF(posport, baud);
  if ret <> 0 then
  begin
    CloseMF;
  end;




  //表不存在，创建 t_pif_cosumer
  try
    if not sldb.TableExists('t_pif_cosumer') then
    begin
      sSql := 'CREATE TABLE t_pif_cosumer([cut_id] INTEGER PRIMARY KEY,[cut_type] INTEGER,[cut_state] INTEGER,' +
        '[cut_name] VARCHAR (255),[stuemp_no] VARCHAR(20), [sex] VARCHAR(1),[man_id]  VARCHAR(20),[card_id] NUMBER,[phy_id] VARCHAR(9));';
      sldb.execsql(sSql);
      sldb.execsql('CREATE INDEX cut_id ON [t_pif_cosumer]([cut_id]);');
    end;
  except
    writelog('创建t_pif_cosumer失败！');
  end;
    //表不存在，创建  T_TIF_LUNCHRDATE
  try
    if not sldb.TableExists('T_TIF_LUNCHRDATE') then
    begin
      sSql := 'CREATE TABLE T_TIF_LUNCHRDATE([ORDID] INTEGER PRIMARY KEY,[BG_DATE] VARCHAR(8),[BG_TIME] VARCHAR(6),' +
        '[ED_DATE] VARCHAR(8),[ED_TIME] VARCHAR(6), [RECODE] VARCHAR(100));';
      sldb.execsql(sSql);
      sldb.execsql('CREATE INDEX ORDID ON [T_TIF_LUNCHRDATE]([ORDID]);');
    end;
  except
    writelog('创建T_TIF_LUNCHRDATE失败！');
  end;
      //表不存在，创建  T_TIF_LUNCHRCVDTL
  try
    if not sldb.TableExists('T_TIF_LUNCHRCVDTL') then
    begin
      sSql := 'CREATE TABLE T_TIF_LUNCHRCVDTL([TX_DATE] VARCHAR(8),[TX_TIME] VARCHAR(6),[DEVICE_ID] VARCHAR(8),[CARD_NO] INTEGER PRIMARY KEY,' +
        '[SERIAL_NO] FLOAT ,[PURSE_NO] FLOAT,[IN_BALA] FLOAT,[OUT_BALA] FLOAT,  [AMOUNT] FLOAT, [TOTAL_CNT] FLOAT,' +
        '[TX_CODE] INTEGER,[TX_MARK] INTEGER,[COMU_VER] INTEGER,[RUN_REASON] INTEGER,[CRC] VARCHAR(4),[INPOWER_NO] VARCHAR(8),' +
        '[SYS_ID] INTEGER,[OPER_NO] VARCHAR(8),[STATUS] VARCHAR(1),[COL_TIMESTAMP] VARCHAR(20),[FEE_CODE] INTEGER,[ERR_CODE] INTEGER,' +
        '[MANAGE_FEE] FLOAT,[OPERATE_DATE] VARCHAR(8),[OPERATE_TIME] VARCHAR(6));';
      sldb.execsql(sSql);
      sldb.execsql('CREATE INDEX CARD_NO ON [T_TIF_LUNCHRCVDTL]([CARD_NO]);');
    end;
  except
    writelog('创建T_TIF_LUNCHRCVDTL失败！');
  end;
  sSQL := 'delete from T_TIF_LUNCHRCVDTL  where TX_DATE<''' + FormatdateTime('yyyymmdd', now()) + ''' and STATUS=''2''';
  sldb.ExecSQL(sSQL);
  if debug = 'true' then
    writelog(sSql + '提交成功！');
  mess.Caption := '正在更新客户表...';
  application.ProcessMessages;
  procDownloadcustomer;
  mess.Caption := '正在更新日期...';
  application.ProcessMessages;
  procDownloadLUNCHRDATE;
  mess.Caption := '正在上传流水...';
  application.ProcessMessages;
  procUploaddata;
  mess.Caption := '正在下载流水...';
  procDownloaddata;
  isTerminate := false;
  beging:=true;
  close;
end;


procedure TLoginFrm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if not beging then
  isTerminate:=true;
end;

procedure TLoginFrm.FormShow(Sender: TObject);
begin
beging:=false;
end;

end.


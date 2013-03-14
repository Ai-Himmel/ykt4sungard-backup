unit UAGetBusPosWater;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,ZLibEx,zlibexgz, 
  RzDBGrid, UIncrementComboBox,PublicFunc, EditExts, ComCtrls, Buttons;

type
  TfaqhGetBusPosWater = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVComboBox1: TWVComboBox;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    Panel2: TPanel;
    ImageButton1: TImageButton;
    SaveDialog1: TSaveDialog;
    Panel4: TPanel;
    Label3: TLabel;
    edtFile: TEdit;
    btnOpenfile: TImageButton;
    btnAnaSerial: TImageButton;
    btngetSerial: TImageButton;
    OpenDialog1: TOpenDialog;
    ListView1: TListView;
    upwaterdata: TWorkView;
    WVRequest1: TWVRequest;
    Label4: TLabel;
    btnTrans: TImageButton;
    procedure btnOpenfileClick(Sender: TObject);
    procedure btnAnaSerialClick(Sender: TObject);
    procedure ImageButton1Click(Sender: TObject);
    procedure ImageButton2Click(Sender: TObject);
    procedure btngetSerialClick(Sender: TObject);
    procedure btnTransClick(Sender: TObject);
  private
     function AnalysisWater(WaterByte : Tarraybyte; Dlen : Integer; var lv : TListView) : Boolean;  //分析流水
//     function CheckCRC(var temparry : array of byte) : string;  //校验CRC
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhGetBusPosWater: TfaqhGetBusPosWater;
implementation

uses KsFrameworks,KSClientConsts,SmartCardCommon;

{$R *.DFM}



procedure TfaqhGetBusPosWater.Init;
begin
  {
  ImageButton1.Caption := '确定';
  Label4.Caption := '';
  ImageButton3.Caption := '打开文件';
  ImageButton4.Caption := '分析流水';
  ImageButton5.Caption := '提取流水';
  btnTrans.Caption := '上传流水';
  Edit1.Text := '';
  }
  ReadConfig;
end;

procedure TfaqhGetBusPosWater.btnOpenfileClick(Sender: TObject);
begin
  OpenDialog1.InitialDir := DownLoadDir;
  if not  OpenDialog1.Execute then exit;
  edtFile.Text := OpenDialog1.FileName;
end;

procedure TfaqhGetBusPosWater.btnAnaSerialClick(Sender: TObject);
var
  WaterByte : Tarraybyte;
  Dlen : Integer;
  inBusPosFile,outBusPosFile:TMemoryStream;
  sBusPosFile:string;
begin
  if Trim(edtFile.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请先打开文件，然后再分析流水！');
    Exit;
  end;
  //先解压文件
  sBusPosFile := sAppPath+'buspos.DAT';
  try
  if FileExists(sBusPosFile) then
    DeleteFile(sBusPosFile);
  except
    on e:Exception do
      WriteLog('删除'+sBusPosFile+'失败--'+e.Message);
  end;
  inBusPosFile := nil;
  outBusPosFile := nil;
  try
    inBusPosFile := TMemoryStream.Create;
    outBusPosFile := TMemoryStream.Create;
    inBusPosFile.LoadFromFile(edtFile.Text);
    try
      ZDecompressStream(inBusPosFile,outBusPosFile);
      outBusPosFile.SaveToFile(sBusPosFile);
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('解压流水文件失败，请检查打开的文件是否正确-'+e.Message);
        Exit;
      end;
    end;
  finally
    inBusPosFile.Free;
    outBusPosFile.Free;
  end;

  LoadBinaryFile(sBusPosFile,WaterByte,Dlen);
  AnalysisWater(WaterByte,Dlen,ListView1);
  //sleep(100);
end;

procedure TfaqhGetBusPosWater.ImageButton1Click(Sender: TObject);
var
 i : integer;
 errlist: Tstrings;
 tradeSign:string;
begin

  errlist := Tstringlist.Create;
  for i := 0 to listview1.Items.Count -1 do
  begin
    try
      upwaterdata.Reset;
      upwaterdata.FieldByName('流水号').data.SetInteger(strtoint(ListView1.Items[i].SubItems[0]));
      upwaterdata.FieldByName('物理卡号').data.SetString( ListView1.Items[i].Caption );
      upwaterdata.FieldByName('物理编号2').data.SetString( ListView1.Items[i].Caption );
      upwaterdata.FieldByName('交易卡号').data.SetInteger(strtoint( ListView1.Items[i].SubItems[1] ));
      upwaterdata.FieldByName('工作站标示').data.SetInteger(0);
      upwaterdata.FieldByName('入卡金额').data.SetInteger(strtoint(floattostr((strtofloat(ListView1.Items[i].SubItems[2])*100))));
      upwaterdata.FieldByName('消费金额').data.SetInteger(strtoint(floattostr((strtofloat(ListView1.Items[i].SubItems[3])*100))));
      upwaterdata.FieldByName('出卡金额').data.SetInteger(strtoint(floattostr((strtofloat(ListView1.Items[i].SubItems[4])*100))));
      upwaterdata.FieldByName('消费次数').data.SetInteger(strtoint(ListView1.Items[i].SubItems[5]));
      upwaterdata.FieldByName('发生日期').data.SetString(ListView1.Items[i].SubItems[6]);
      upwaterdata.FieldByName('发生时间').data.SetString(ListView1.Items[i].SubItems[7]);
      tradeSign := ListView1.Items[i].SubItems[8];
      if tradeSign='正常交易' then
        upwaterdata.FieldByName('交易标志').data.SetInteger(153)
      else
      if (tradeSign='黑卡交易') or (tradeSign='无效流水') or (tradeSign='中途拔卡流水') then
        upwaterdata.FieldByName('交易标志').data.SetInteger(0)
      else
      begin
        errlist.Add('流水号 ['+ListView1.Items[i].SubItems[0]+'] 交易卡号 ['+ListView1.Items[i].SubItems[1]+']消费金额 ['+ListView1.Items[i].SubItems[3]+'] 上传失败');
        Continue;
      end;
      upwaterdata.FieldByName('钱包').data.SetInteger(strtoint( ListView1.Items[i].SubItems[10] ));
      upwaterdata.FieldByName('CRC校验码').data.SetString(ListView1.Items[i].SubItems[11]);

    except
      on e:Exception do
      begin
        //ShowMessage(e.Message);
        errlist.Add('流水号 ['+ListView1.Items[i].SubItems[0]+'] 交易卡号 ['+ListView1.Items[i].SubItems[1]+']消费金额 ['+ListView1.Items[i].SubItems[3]+'] 上传失败');
        Continue;
      end;
    end;
      WVRequest1.SendCommand;
     if upwaterdata.FieldByName('返回码').DATA.AsInteger <> 0 then
       errlist.Add('流水号 ['+ListView1.Items[i].SubItems[0]+'] 交易卡号 ['+ListView1.Items[i].SubItems[1]+']消费金额 ['+ListView1.Items[i].SubItems[3]+'] 上传失败');
  end;
  if errlist.Count>0 then
  begin
    if SaveDialog1.Execute then
      errlist.SaveToFile(SaveDialog1.FileName+'.txt');
  end;
  freeandnil(errlist);
  showmessage('采集流上传水完成!');
end;

procedure TfaqhGetBusPosWater.ImageButton2Click(Sender: TObject);
begin
close;
end;

procedure TfaqhGetBusPosWater.btngetSerialClick(Sender: TObject);
var
  PCDir : Pchar;
  HTDir : Pchar;
  pc,ht,zlibPc:string;
  inBusPosFile,outBusPosFile:TMemoryStream;
  st:Integer;
begin
  pc:=DownLoadDir;
  if pc[length(pc)]='\' then
    pc:=PC+'REC'+formatdatetime('yyMMdd',now)
  else
    pc:=PC+'\REC'+formatdatetime('yyMMdd',now);

  pc := pc+'.DAT';
  zlibPc := pc+'.bps';

  pcdir := pchar(pc);
  ht :=Recordfile;
  htdir:=pchar(ht);
  CloseCommPort;
  st := ExFGet(PCDir,HTDir,Port,BAUT,Index);
  if st <> 0 then
  begin
   ShowMessage('下载车载机流水文件失败-'+inttostr(st));
   exit;
  end;
  //下载成功，开始压缩该文件
  outBusPosFile := nil;
  inBusPosFile := nil;
  try
    inBusPosFile := TMemoryStream.Create;
    outBusPosFile := TMemoryStream.Create;
    inBusPosFile.LoadFromFile(pc);
    try
      ZCompressStream(inBusPosFile,outBusPosFile,zcDefault);
      outBusPosFile.SaveToFile(zlibPc);
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('压缩流水文件失败，重新连接机器下载--'+e.Message);
        Exit;
      end;
    end;
  finally
    inBusPosFile.Free;
    outBusPosFile.Free;
    if FileExists(pc) then
      DeleteFile(pc);
  end;
  //压缩完成
  if DelHtFile(htdir,Port,BAUT) <> 0 then
  begin
    showmessage('删除文件失败');
    exit;
  end;
  if MessageDlg('您需要要打开刚刚提取的文件么？',mtInformation,[mbYES,mbNo],0)=mrYes then
     edtFile.Text :=zlibPc;
end;

function TfaqhGetBusPosWater.AnalysisWater(WaterByte: Tarraybyte; Dlen : Integer;
  var lv: TListView): Boolean;
var
   Rc : Integer;
   temp : array[0..63] of byte;
   paycount : real;
   tempcount : integer;
   copycount : integer;
   tempItem : TListItem;
   trade : string; //交易标志
   tmpMoney:Real;
begin
 rc := 0;
 lv.Items.Clear;
 paycount :=0.00;
  while (rc < dLen) do
   begin
      for tempcount := 0 to sizeof(temp)-1 do
         temp[tempcount] := 0;

      tempcount := 0;
      for copycount := Rc to Rc+63 do
      begin
         temp[tempcount] := WaterByte[copycount];
         inc(tempcount);
      end;

        tempItem:= lv.Items.Add;
        tempItem.Caption :=ProcessToMenory(temp[1],1)+ProcessToMenory(temp[2],1)+ProcessToMenory(temp[3],1)+ProcessToMenory(temp[4],1);   //物理ID号
        //tempItem.SubItems.Add(inttostr(temp[5])+inttostr(temp[6])+inttostr(temp[7])+inttostr(temp[8]));  //流水号
        tempItem.SubItems.Add(IntToStr(strtoint('$'+ProcessToMenory(temp[5],1)+ProcessToMenory(temp[6],1)+ProcessToMenory(temp[7],1)+ProcessToMenory(temp[8],1))));  //???
        tempItem.SubItems.Add(inttostr(strtoint('$'+ProcessToMenory(temp[9],1)+ProcessToMenory(temp[10],1)+ProcessToMenory(temp[11],1)))); //交易卡号
        tempItem.SubItems.Add((Format('%.2f',[StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[12],1)+ProcessToMenory(temp[13],1)+ProcessToMenory(temp[14],1)+ProcessToMenory(temp[15],1)))) / 100 ]))); //入卡金额
        tempItem.SubItems.Add((Format('%.2f',[StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[16],1)+ProcessToMenory(temp[17],1)+ProcessToMenory(temp[18],1)))) / 100 ]))); //交易金额
        paycount := paycount+(StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[16],1)+ProcessToMenory(temp[17],1)+ProcessToMenory(temp[18],1)))) / 100);
        tmpMoney := (StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[12],1)+ProcessToMenory(temp[13],1)+ProcessToMenory(temp[14],1)+ProcessToMenory(temp[15],1)))) / 100)- (StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[16],1)+ProcessToMenory(temp[17],1)+ProcessToMenory(temp[18],1)))) / 100);
        tempItem.SubItems.Add(Format('%.2f',[tmpMoney]));
        tempItem.SubItems.Add(inttostr(strtoint('$'+ProcessToMenory(temp[19],1)+ProcessToMenory(temp[20],1)))); //卡中交易次数
        tempItem.SubItems.Add(ProcessToMenory(temp[21],1)+ProcessToMenory(temp[22],1)+ProcessToMenory(temp[23],1));  //交易日期
        tempItem.SubItems.Add(ProcessToMenory(temp[24],1)+ProcessToMenory(temp[25],1)+ProcessToMenory(temp[26],1));  //，时间
        trade:=ProcessToMenory(temp[27],1);
        if trade='0A' then
        tempItem.SubItems.Add('正常交易') //交易标志
        else if trade ='00' then
        tempItem.SubItems.Add('黑卡交易') //交易标志
        else if trade ='FF' then
        tempItem.SubItems.Add('无效流水') //交易标志
        else if trade ='02' then
        tempItem.SubItems.Add('中途拔卡流水'); //交易标志
        tempItem.SubItems.Add(inttostr(strtoint('$'+ProcessToMenory(temp[28],1)))); //交易类型
        tempItem.SubItems.Add(inttostr(strtoint('$'+ProcessToMenory(temp[29],1)))); //钱包号
        {
        tempItem.SubItems.Add(ProcessToMenory(temp[30],1)+ProcessToMenory(temp[31],1)+ProcessToMenory(temp[32],1)+ProcessToMenory(temp[33],1));   //物理ID号
        tempItem.SubItems.Add(ProcessToMenory(temp[34],1)+' 日'+ProcessToMenory(temp[35],1)+ProcessToMenory(temp[36],1)+ProcessToMenory(temp[37],1));  //交易日期
        tempItem.SubItems.Add((Format('%.2f',[StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[38],1)+ProcessToMenory(temp[39],1)+ProcessToMenory(temp[40],1)+ProcessToMenory(temp[41],1)))) / 100 ]))); //入卡金额
        tempItem.SubItems.Add((Format('%.2f',[StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[42],1)+ProcessToMenory(temp[43],1)+ProcessToMenory(temp[44],1)))) / 100 ]))); //交易金额
        trade:=ProcessToMenory(temp[45],1);
        if trade='0A' then
        tempItem.SubItems.Add('正常交易') //交易标志
        else if trade ='00' then
        tempItem.SubItems.Add('黑卡交易') //交易标志
        else if trade ='FF' then
        tempItem.SubItems.Add('无效流水') //交易标志
        else if trade ='02' then
        tempItem.SubItems.Add('中途拔卡流水'); //交易标志
        }
        tempItem.SubItems.Add(ProcessToMenory(temp[61],1)+ProcessToMenory(temp[62],1)); //CRC校验码
      inc(rc,64);
   end;
   labrecordcount.Caption :='提取流水为['+inttostr(lv.Items.Count)+']条,交易总金额为['+floattostr(paycount)+']元';
   Result := True;
end;



procedure TfaqhGetBusPosWater.btnTransClick(Sender: TObject);
begin
  if ListView1.Items.Count=0 then
  begin
    Context.GetDialogSystem.ShowMessage('请先打开文件，分析流水，然后再进行上传流水操作！');
    Exit;
  end;
  if Application.MessageBox('你确定要上传流水吗？',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  ImageButton1.Click;
end;

initialization
  TUIStdClassFactory.Create('流水采集', TfaqhGetBusPosWater);

end.

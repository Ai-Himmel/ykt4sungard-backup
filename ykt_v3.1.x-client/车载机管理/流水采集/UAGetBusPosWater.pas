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
     function AnalysisWater(WaterByte : Tarraybyte; Dlen : Integer; var lv : TListView) : Boolean;  //������ˮ
//     function CheckCRC(var temparry : array of byte) : string;  //У��CRC
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
  ImageButton1.Caption := 'ȷ��';
  Label4.Caption := '';
  ImageButton3.Caption := '���ļ�';
  ImageButton4.Caption := '������ˮ';
  ImageButton5.Caption := '��ȡ��ˮ';
  btnTrans.Caption := '�ϴ���ˮ';
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
    Context.GetDialogSystem.ShowMessage('���ȴ��ļ���Ȼ���ٷ�����ˮ��');
    Exit;
  end;
  //�Ƚ�ѹ�ļ�
  sBusPosFile := sAppPath+'buspos.DAT';
  try
  if FileExists(sBusPosFile) then
    DeleteFile(sBusPosFile);
  except
    on e:Exception do
      WriteLog('ɾ��'+sBusPosFile+'ʧ��--'+e.Message);
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
        Context.GetDialogSystem.ShowMessage('��ѹ��ˮ�ļ�ʧ�ܣ�����򿪵��ļ��Ƿ���ȷ-'+e.Message);
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
      upwaterdata.FieldByName('��ˮ��').data.SetInteger(strtoint(ListView1.Items[i].SubItems[0]));
      upwaterdata.FieldByName('������').data.SetString( ListView1.Items[i].Caption );
      upwaterdata.FieldByName('������2').data.SetString( ListView1.Items[i].Caption );
      upwaterdata.FieldByName('���׿���').data.SetInteger(strtoint( ListView1.Items[i].SubItems[1] ));
      upwaterdata.FieldByName('����վ��ʾ').data.SetInteger(0);
      upwaterdata.FieldByName('�뿨���').data.SetInteger(strtoint(floattostr((strtofloat(ListView1.Items[i].SubItems[2])*100))));
      upwaterdata.FieldByName('���ѽ��').data.SetInteger(strtoint(floattostr((strtofloat(ListView1.Items[i].SubItems[3])*100))));
      upwaterdata.FieldByName('�������').data.SetInteger(strtoint(floattostr((strtofloat(ListView1.Items[i].SubItems[4])*100))));
      upwaterdata.FieldByName('���Ѵ���').data.SetInteger(strtoint(ListView1.Items[i].SubItems[5]));
      upwaterdata.FieldByName('��������').data.SetString(ListView1.Items[i].SubItems[6]);
      upwaterdata.FieldByName('����ʱ��').data.SetString(ListView1.Items[i].SubItems[7]);
      tradeSign := ListView1.Items[i].SubItems[8];
      if tradeSign='��������' then
        upwaterdata.FieldByName('���ױ�־').data.SetInteger(153)
      else
      if (tradeSign='�ڿ�����') or (tradeSign='��Ч��ˮ') or (tradeSign='��;�ο���ˮ') then
        upwaterdata.FieldByName('���ױ�־').data.SetInteger(0)
      else
      begin
        errlist.Add('��ˮ�� ['+ListView1.Items[i].SubItems[0]+'] ���׿��� ['+ListView1.Items[i].SubItems[1]+']���ѽ�� ['+ListView1.Items[i].SubItems[3]+'] �ϴ�ʧ��');
        Continue;
      end;
      upwaterdata.FieldByName('Ǯ��').data.SetInteger(strtoint( ListView1.Items[i].SubItems[10] ));
      upwaterdata.FieldByName('CRCУ����').data.SetString(ListView1.Items[i].SubItems[11]);

    except
      on e:Exception do
      begin
        //ShowMessage(e.Message);
        errlist.Add('��ˮ�� ['+ListView1.Items[i].SubItems[0]+'] ���׿��� ['+ListView1.Items[i].SubItems[1]+']���ѽ�� ['+ListView1.Items[i].SubItems[3]+'] �ϴ�ʧ��');
        Continue;
      end;
    end;
      WVRequest1.SendCommand;
     if upwaterdata.FieldByName('������').DATA.AsInteger <> 0 then
       errlist.Add('��ˮ�� ['+ListView1.Items[i].SubItems[0]+'] ���׿��� ['+ListView1.Items[i].SubItems[1]+']���ѽ�� ['+ListView1.Items[i].SubItems[3]+'] �ϴ�ʧ��');
  end;
  if errlist.Count>0 then
  begin
    if SaveDialog1.Execute then
      errlist.SaveToFile(SaveDialog1.FileName+'.txt');
  end;
  freeandnil(errlist);
  showmessage('�ɼ����ϴ�ˮ���!');
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
   ShowMessage('���س��ػ���ˮ�ļ�ʧ��-'+inttostr(st));
   exit;
  end;
  //���سɹ�����ʼѹ�����ļ�
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
        Context.GetDialogSystem.ShowMessage('ѹ����ˮ�ļ�ʧ�ܣ��������ӻ�������--'+e.Message);
        Exit;
      end;
    end;
  finally
    inBusPosFile.Free;
    outBusPosFile.Free;
    if FileExists(pc) then
      DeleteFile(pc);
  end;
  //ѹ�����
  if DelHtFile(htdir,Port,BAUT) <> 0 then
  begin
    showmessage('ɾ���ļ�ʧ��');
    exit;
  end;
  if MessageDlg('����ҪҪ�򿪸ո���ȡ���ļ�ô��',mtInformation,[mbYES,mbNo],0)=mrYes then
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
   trade : string; //���ױ�־
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
        tempItem.Caption :=ProcessToMenory(temp[1],1)+ProcessToMenory(temp[2],1)+ProcessToMenory(temp[3],1)+ProcessToMenory(temp[4],1);   //����ID��
        //tempItem.SubItems.Add(inttostr(temp[5])+inttostr(temp[6])+inttostr(temp[7])+inttostr(temp[8]));  //��ˮ��
        tempItem.SubItems.Add(IntToStr(strtoint('$'+ProcessToMenory(temp[5],1)+ProcessToMenory(temp[6],1)+ProcessToMenory(temp[7],1)+ProcessToMenory(temp[8],1))));  //???
        tempItem.SubItems.Add(inttostr(strtoint('$'+ProcessToMenory(temp[9],1)+ProcessToMenory(temp[10],1)+ProcessToMenory(temp[11],1)))); //���׿���
        tempItem.SubItems.Add((Format('%.2f',[StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[12],1)+ProcessToMenory(temp[13],1)+ProcessToMenory(temp[14],1)+ProcessToMenory(temp[15],1)))) / 100 ]))); //�뿨���
        tempItem.SubItems.Add((Format('%.2f',[StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[16],1)+ProcessToMenory(temp[17],1)+ProcessToMenory(temp[18],1)))) / 100 ]))); //���׽��
        paycount := paycount+(StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[16],1)+ProcessToMenory(temp[17],1)+ProcessToMenory(temp[18],1)))) / 100);
        tmpMoney := (StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[12],1)+ProcessToMenory(temp[13],1)+ProcessToMenory(temp[14],1)+ProcessToMenory(temp[15],1)))) / 100)- (StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[16],1)+ProcessToMenory(temp[17],1)+ProcessToMenory(temp[18],1)))) / 100);
        tempItem.SubItems.Add(Format('%.2f',[tmpMoney]));
        tempItem.SubItems.Add(inttostr(strtoint('$'+ProcessToMenory(temp[19],1)+ProcessToMenory(temp[20],1)))); //���н��״���
        tempItem.SubItems.Add(ProcessToMenory(temp[21],1)+ProcessToMenory(temp[22],1)+ProcessToMenory(temp[23],1));  //��������
        tempItem.SubItems.Add(ProcessToMenory(temp[24],1)+ProcessToMenory(temp[25],1)+ProcessToMenory(temp[26],1));  //��ʱ��
        trade:=ProcessToMenory(temp[27],1);
        if trade='0A' then
        tempItem.SubItems.Add('��������') //���ױ�־
        else if trade ='00' then
        tempItem.SubItems.Add('�ڿ�����') //���ױ�־
        else if trade ='FF' then
        tempItem.SubItems.Add('��Ч��ˮ') //���ױ�־
        else if trade ='02' then
        tempItem.SubItems.Add('��;�ο���ˮ'); //���ױ�־
        tempItem.SubItems.Add(inttostr(strtoint('$'+ProcessToMenory(temp[28],1)))); //��������
        tempItem.SubItems.Add(inttostr(strtoint('$'+ProcessToMenory(temp[29],1)))); //Ǯ����
        {
        tempItem.SubItems.Add(ProcessToMenory(temp[30],1)+ProcessToMenory(temp[31],1)+ProcessToMenory(temp[32],1)+ProcessToMenory(temp[33],1));   //����ID��
        tempItem.SubItems.Add(ProcessToMenory(temp[34],1)+' ��'+ProcessToMenory(temp[35],1)+ProcessToMenory(temp[36],1)+ProcessToMenory(temp[37],1));  //��������
        tempItem.SubItems.Add((Format('%.2f',[StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[38],1)+ProcessToMenory(temp[39],1)+ProcessToMenory(temp[40],1)+ProcessToMenory(temp[41],1)))) / 100 ]))); //�뿨���
        tempItem.SubItems.Add((Format('%.2f',[StrToFloat(inttostr(strtoint('$'+ ProcessToMenory(temp[42],1)+ProcessToMenory(temp[43],1)+ProcessToMenory(temp[44],1)))) / 100 ]))); //���׽��
        trade:=ProcessToMenory(temp[45],1);
        if trade='0A' then
        tempItem.SubItems.Add('��������') //���ױ�־
        else if trade ='00' then
        tempItem.SubItems.Add('�ڿ�����') //���ױ�־
        else if trade ='FF' then
        tempItem.SubItems.Add('��Ч��ˮ') //���ױ�־
        else if trade ='02' then
        tempItem.SubItems.Add('��;�ο���ˮ'); //���ױ�־
        }
        tempItem.SubItems.Add(ProcessToMenory(temp[61],1)+ProcessToMenory(temp[62],1)); //CRCУ����
      inc(rc,64);
   end;
   labrecordcount.Caption :='��ȡ��ˮΪ['+inttostr(lv.Items.Count)+']��,�����ܽ��Ϊ['+floattostr(paycount)+']Ԫ';
   Result := True;
end;



procedure TfaqhGetBusPosWater.btnTransClick(Sender: TObject);
begin
  if ListView1.Items.Count=0 then
  begin
    Context.GetDialogSystem.ShowMessage('���ȴ��ļ���������ˮ��Ȼ���ٽ����ϴ���ˮ������');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ�ϴ���ˮ��',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  ImageButton1.Click;
end;

initialization
  TUIStdClassFactory.Create('��ˮ�ɼ�', TfaqhGetBusPosWater);

end.

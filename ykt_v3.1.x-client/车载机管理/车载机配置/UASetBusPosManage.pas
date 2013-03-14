unit UASetBusPosManage;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,
  RzDBGrid, UIncrementComboBox,  PublicFunc,
  EditExts, ComCtrls, Buttons, RzCmboBx;

type
  TfaqhBusPosManage = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVComboBox1: TWVComboBox;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    Panel2: TPanel;
    GroupBox2: TGroupBox;
    Label5: TLabel;
    edtConParaVer: TWVEdit;
    Label6: TLabel;
    edtBaseFee: TWVEdit;
    Label7: TLabel;
    Label8: TLabel;
    edtTimeSplit: TWVEdit;
    Label9: TLabel;
    Label10: TLabel;
    edtCardTimeSpace: TWVEdit;
    Label11: TLabel;
    grpWelcome: TGroupBox;
    Label13: TLabel;
    edtWelcome: TWVEdit;
    grpBlackList: TGroupBox;
    GroupBox5: TGroupBox;
    Label15: TLabel;
    edtCardLimit: TWVEdit;
    SaveDialog1: TSaveDialog;
    btnCreateFile: TImageButton;
    ImageButton2: TImageButton;
    btnBala: TImageButton;
    btnSetLimit: TImageButton;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    WorkView2: TWorkView;
    WVDBBinder2: TWVDBBinder;
    WVRequest2: TWVRequest;
    DataSource2: TDataSource;
    ListView1: TListView;
    Label4: TLabel;
    edtFeeBal: TEdit;
    btnTime: TImageButton;
    CheckBox5: TCheckBox;
    btnLimitEdit: TImageButton;
    GroupBox1: TGroupBox;
    btnSoundSet: TImageButton;
    CheckBox6: TCheckBox;
    lvSound: TListView;
    lbl2: TLabel;
    cbbSound: TRzComboBox;
    lblFeeType: TLabel;
    procedure ImageButton2Click(Sender: TObject);
    procedure btnCreateFileClick(Sender: TObject);
    procedure btnBalaClick(Sender: TObject);
    procedure btnSetLimitClick(Sender: TObject);
    procedure ListView1Click(Sender: TObject);
    procedure edtFeeBalKeyPress(Sender: TObject; var Key: Char);
    procedure btnTimeClick(Sender: TObject);
    procedure CheckBox5Click(Sender: TObject);
    procedure btnLimitEditClick(Sender: TObject);
    procedure lvSoundClick(Sender: TObject);
    procedure btnSoundSetClick(Sender: TObject);
    procedure cbbSoundChange(Sender: TObject);
  private
     function Process(Pro_Type : Integer;CHK : TCheckBox) : Boolean;
     function Pro_Pay_Set(var TempData : string) : Boolean;
     function Pro_WelcomeInfo_Set(var TempData : string) : Boolean;
     function Pro_BlackList_Set(var TempData: string) : Boolean;
     function Pro_Card_Purview_Set(var TempData : string) : Boolean;
     function Fill_ListView(DS : TdataSet; lv  : TListView) : Boolean;
     function Fill_ListView2(DS : TdataSet; lv  : TListView) : Boolean;

     function Make_Purivew(lv : TListview) : String;
     function Make_Purview_Fee(lv : TListView) : String;

     function UploadSound(lv : TListview):Integer;

     function UploadBlackList():Integer;
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBusPosManage: TfaqhBusPosManage;
  cap,cap2 : string;

implementation

uses KsFrameworks,filetrans,KSClientConsts;

{$R *.DFM}

procedure TfaqhBusPosManage.Init;
var
  tempds : Tdataset;
begin
  WVRequest2.SendCommand;
  tempds:= Tdataset(WorkView2.FieldByName('返回数据集').Data.AsObject);
  Fill_ListView(tempds,ListView1);
  Fill_ListView2(tempds,lvSound);
  edtConParaVer.Text := FormatDateTime('yyMMddhhnnss',now());
  //edtBlackVer.Text := FormatDateTime('yyMMddhhnnss',now());
  edtCardLimit.Text := FormatDateTime('yyMMddhhnnss',now());
  edtBaseFee.Text := '10';
  edtTimeSplit.Text := '10';
  edtCardTimeSpace.Text := '60';
  edtWelcome.Text := '';
  edtFeeBal.Text := '';
  ReadConfig;
  lblFeeType.Caption := '';
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    //endGetPhotoSign := True;
    //filePath := sAppPath+'nophoto.jpg';
    //imgPhoto.Picture.LoadFromFile(filePath);
  except

  end;
   
end;

function TfaqhBusPosManage.Process(Pro_Type: Integer;CHK : TCheckBox): Boolean;
var
   ErrMsg : String;
   TempData : string;
   ret : Boolean;
   filenames: string;
   files : string;
begin
  Result := False;
  ret := False;
  case  Pro_Type of
     1 : ret := Pro_WelcomeInfo_Set(TempData);
     2 : ret := Pro_Pay_Set(TempData);
     3 : ret := Pro_BlackList_Set(TempData);
     4 : ret := Pro_Card_Purview_Set(TempData);
  end;
  if (ret) and (Pro_Type>1) then
  begin
    case Pro_Type of
      2 :
         begin
          files := PAYFILE;
          filenames:=UPLOADDIR+files;
         end;
      3 :
         begin
           files := BLACKLIST;
           filenames:=UPLOADDIR+files;
         end;
      4 :
         begin
          files := PURVIEW;
          filenames:=UPLOADDIR+PURVIEW;
         end;
    end;
    SaveToBinary(TempData,filenames,length(TempData) div 2);
  end
  else if (ret) and (Pro_Type=1) then
  begin
   files := WELCOME;
   filenames := UPLOADDIR+WELCOME;
   SaveToFile(TempData,filenames);
  end
  else
   ConText.GetDialogSystem.ShowError('操作错误请重试!');

  if (CHK.Checked) and (ret) then
  begin
    UploadFile(pchar(filenames),pchar(files),PORT,BAUT,INDEX,0,ErrMsg);
    if(Trim(ErrMsg)<>'') then
    showmessage(ErrMsg);
    Result := True;
  end;
end;

function TfaqhBusPosManage.Pro_BlackList_Set(var TempData : string): Boolean;
//var
  //GetTempData : TDataSet;
  //fileName:string;
  //B_list : TList;
  //i : Integer;
begin
  //TempData := '';
  WVRequest1.SendCommand;
  {
  //B_list := TList.Create;
  //GetTempData := TDataSet(WorkView1.FieldByName('返回数据集').Data.AsObject);
  //Write_Record(B_list,GetTempData); //读取数据集中的位图数据
  //Read_Record_Str(B_list,TempData); //组织位图数据
  //TempData := TempData+edtBlackVer.Text; //日期
  TempData := TempData+GetCRC16Str(TempData); //CRC校验码
  for i := 0 to B_list.Count -1 do
    if B_list<> nil then
       FreeMemory(B_list[i]);
  freeandnil(B_list);
  }
  Result := True;
end;

function TfaqhBusPosManage.Pro_Card_Purview_Set(var TempData : string): Boolean;
begin
 TempData := '';
 TempData := TempData+edtCardLimit.Text;  //卡权限版本
 TempData:=TempData+BinToHex(Make_Purivew(ListView1)); //卡权限设置位图
 TempData:=TempData+Make_Purview_Fee(ListView1); //卡费率
 Result := True;
end;

function TfaqhBusPosManage.Pro_Pay_Set(var TempData : string): Boolean;
begin
   TempData:= '';
   TempData := TempData+edtConParaVer.Text;//天数
   TempData := TempData+ProcessToMenory(strtoint(floattostr((strtofloat(edtBaseFee.Text)*100))),3); //基本消费基数
   TempData := TempData+ProcessToMenory(strtoint(edtTimeSplit.Text),1); //流水采集天数
   TempData := TempData+ProcessToMenory(strtoint(edtCardTimeSpace.Text),2); //连续刷卡时间
   TempData := TempData+'FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF'; //保留空间
   TempData :=TempData+GetCRC16Str(TempData); //校验码
   Result := True;
end;

function TfaqhBusPosManage.Pro_WelcomeInfo_Set(var TempData : string): Boolean;
begin
  Result := False;
  if Trim(edtWelcome.Text) = '' then
  begin
     ConText.GetDialogSystem.ShowError('输入数据为空!');
     exit;
  end;
  TempData:=edtWelcome.Text;
  Result := True;   
end;

procedure TfaqhBusPosManage.ImageButton2Click(Sender: TObject);
begin
   Process(1,CheckBox2);
end;

procedure TfaqhBusPosManage.btnCreateFileClick(Sender: TObject);
begin
   edtConParaVer.Text := FormatDateTime('yyMMddhhnnss',now());
   if strtoint(edtCardTimeSpace.text) < maxbrushtime then
   begin
     ConText.GetDialogSystem.showmessage('连续刷卡时间不能小于['+inttostr(maxbrushtime)+']秒');
     exit;
   end;
   Process(2,CheckBox1);
end;

procedure TfaqhBusPosManage.btnBalaClick(Sender: TObject);
begin
   //Process(3,CheckBox3);
  UploadBlackList;
end;

procedure TfaqhBusPosManage.btnSetLimitClick(Sender: TObject);
begin
  edtCardLimit.Text := FormatDateTime('yyMMddhhnnss',now());
  Process(4,CheckBox4);
end;


function TfaqhBusPosManage.Fill_ListView(DS: TdataSet;lv: TListView): Boolean;
var
 temp : TListItem;
begin
   ds.First;
   while (not ds.Eof) do
   begin
     temp:=lv.Items.Add;
     temp.Caption := DS.fieldbyname('lvol1').asstring;
     temp.SubItems.Add(DS.fieldbyname('scusttypes').asstring);
     temp.SubItems.add('100');  //默认费率
     ds.Next;
   end;
   lv.AlphaSort;
   Result := True;
end;

function TfaqhBusPosManage.Make_Purivew(lv: TListview): String;
var
  i : Integer;
  temp : array[0..255] of char;
begin
    Result := '';
    for i:=0 to sizeof(temp) -1 do
       temp[i]:='0';
   for i:=0 to lv.Items.Count -1 do
    temp[strtoint(lv.Items[i].Caption)-1]:=inttostr(ord(lv.Items[i].checked))[1];
    Result := temp;
end;

function TfaqhBusPosManage.Make_Purview_Fee(lv: TListView): String;
var
   buffer : array[0..511] of char;
   i : integer;
   tempstr : string;
begin
   Result := '';
   for i:=0 to sizeof(buffer)-1 do
      buffer[i]:='0';
   for i:=0 to lv.Items.Count -1 do
    if lv.Items[i].Checked then
   begin
      tempstr := ProcessToMenory(strtoint(floattostr(strtofloat(lv.Items[i].SubItems[1]))),1);
      buffer[(strtoint(lv.Items[i].Caption)*2)-2]:=tempstr[1];
      buffer[(strtoint(lv.Items[i].Caption)*2)-1]:=tempstr[2];
   end;
   Result := buffer;
end;

procedure TfaqhBusPosManage.ListView1Click(Sender: TObject);
begin
if ListView1.Selected = nil then  Exit;
 cap :=  ListView1.Selected.Caption;
 edtFeeBal.Text := ListView1.Selected.SubItems[1];
end;

procedure TfaqhBusPosManage.edtFeeBalKeyPress(Sender: TObject; var Key: Char);
begin
 if not (key in ['0'..'9',#8]) then key:=#0;
end;

procedure TfaqhBusPosManage.btnTimeClick(Sender: TObject);
var
  dates : string;
  times : string;
begin
 if HTTest(port,baut)<>0 then
  begin
     ConText.GetDialogSystem.showmessage('手持机未连接!');
     exit;
  end;
  dates := formatdatetime('yyyyMMdd',now());
  times := formatdatetime('hh:mm:ss',now());
  if wSetDateTime(pchar(dates),pchar(times),port,baut) <> 0 then
  begin
    ConText.GetDialogSystem.ShowError('同步手持机时间失败!');
    exit;
  end;
  ConText.GetDialogSystem.showmessage('同步时钟完成!');
end;

procedure TfaqhBusPosManage.CheckBox5Click(Sender: TObject);
var
  i : integer;
  isselected: boolean;
begin
  if CheckBox5.Checked then
     isselected := true
  else
     isselected :=false;
  for i :=0 to listview1.Items.Count -1 do
     listview1.Items[i].Checked := isselected;
end;

procedure TfaqhBusPosManage.btnLimitEditClick(Sender: TObject);
var
  i : integer;
begin
if trim(cap) ='' then
 begin
    ConText.GetDialogSystem.ShowError('请选择要修改的记录');
    exit;
 end;
 for i :=0 to ListView1.Items.Count -1 do
   begin
     if ListView1.Items[i].Caption = cap then
        begin
           ListView1.Items[i].SubItems[1]:=edtFeeBal.text;
           exit;
        end;
   end;
  ListView1.Enabled := True;
end;

function TfaqhBusPosManage.Fill_ListView2(DS: TdataSet;lv: TListView): Boolean;
var
 temp : TListItem;
begin
   ds.First;
   while (not ds.Eof) do
   begin
     temp:=lv.Items.Add;
     temp.Caption := DS.fieldbyname('lvol1').asstring;
     temp.SubItems.Add(DS.fieldbyname('scusttypes').asstring);
     temp.SubItems.add('0');  //默认费率
     temp.SubItems.add('默认类别');  //默认费率
     ds.Next;
   end;
   lv.AlphaSort;
   Result := True;
end;

procedure TfaqhBusPosManage.lvSoundClick(Sender: TObject);
begin
  //if lvSound.Selected = nil then  Exit;
  cap2 :=  lvSound.Selected.Caption;
  lblFeeType.Caption := lvSound.Selected.SubItems[0];
  try
    cbbSound.ItemIndex := StrToInt(lvSound.Selected.SubItems[1]);
  except
    cbbSound.ItemIndex := 0;
  end;
 //edtFeeBal.Text := ListView1.Selected.SubItems[1];
end;

function TfaqhBusPosManage.UploadSound(lv: TListview): Integer;
var
  acardGrp:array[0..255] of string;
  str:string;
  i:Integer;
  feeType,soundType:Integer;
  ErrMsg:string;
begin
  for i := 0 to 255 do
  begin
    acardGrp[i] := IntToHex(0,2);
  end;
  
  for i:= 0 to lvSound.Items.Count-1 do
  begin
    feeType := StrToInt(lvSound.Items[i].Caption);
    soundType := StrToInt(lvSound.Items[i].SubItems[1]);
    acardGrp[feeType-1] := IntToHex(soundType,2);
  end;

  for i := 0 to 255 do
  begin
    str := str+acardgrp[i];
  end;

  SaveToBinary(str,UPLOADDIR+CARDGRP,length(str) div 2);
  UploadFile(pchar(UPLOADDIR+CARDGRP),pchar(CARDGRP),PORT,BAUT,INDEX,0,ErrMsg);
  if(Trim(ErrMsg)<>'') then
  showmessage(ErrMsg);

end;

procedure TfaqhBusPosManage.btnSoundSetClick(Sender: TObject);
begin
  UploadSound(lvSound);

end;

procedure TfaqhBusPosManage.cbbSoundChange(Sender: TObject);
var
  i : integer;
begin
if trim(cap2) ='' then
 begin
    ConText.GetDialogSystem.ShowError('请选择要修改的记录');
    exit;
 end;
 for i :=0 to lvSound.Items.Count -1 do
   begin
     if lvSound.Items[i].Caption = cap2 then
        begin
           lvSound.Items[i].SubItems[1]:=Copy(cbbSound.Text,1,Pos('-',cbbSound.Text)-1);
           lvSound.Items[i].SubItems[2]:=Copy(cbbSound.Text,Pos('-',cbbSound.Text)+1,Length(cbbSound.Text));
           exit;
        end;
   end;
  lvSound.Enabled := True;
end;

function TfaqhBusPosManage.UploadBlackList: Integer;
var
  fileName:string;
  dFile:string;
  ret:Integer;
  ErrMsg:string;
begin
  if Application.MessageBox('从后台获取黑名单时间可能比较长，请耐心等待，确定开始获取吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVRequest1.SendCommand;
  fileName := WorkView1.fieldbyname('返回信息').Data.AsString;
  dFile := UPLOADDIR+BLACKLIST;
  try
    ret := KSG_Download_File_Ext(fileName,dFile);
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  if ret<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('下载黑名单失败，失败码：'+inttostr(ret));
    Exit;
  end;
  if Application.MessageBox('获取黑名单成功，请确认手持机处于正常状态，然后传黑名单记录，开始传名单吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  UploadFile(pchar(dFile),pchar(BLACKLIST),PORT,BAUT,INDEX,0,ErrMsg);
  if(Trim(ErrMsg)<>'') then
  Context.GetDialogSystem.showmessage(ErrMsg);

end;

initialization
  TUIStdClassFactory.Create('车载机配置', TfaqhBusPosManage);

end.

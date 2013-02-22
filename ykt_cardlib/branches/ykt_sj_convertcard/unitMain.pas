unit unitMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, DB, ADODB, Grids, DBGrids, StdCtrls, Buttons, ExtCtrls, RzPanel,
  RzLabel, RzButton, Mask, RzEdit, RzStatus, Menus, ComCtrls, IniFiles;

type
  TfrmMain = class(TForm)
    con1: TADOConnection;
    qry1: TADOQuery;
    ds1: TDataSource;
    btnInitCard: TBitBtn;
    btnCloseCard: TBitBtn;
    btnCardUpdate: TBitBtn;
    btnReadCard: TBitBtn;
    rzgrpbx1: TRzGroupBox;
    lbl1: TRzLabel;
    lbl2: TRzLabel;
    lbl3: TRzLabel;
    lbl4: TRzLabel;
    lbl5: TRzLabel;
    lbl6: TRzLabel;
    lbl7: TRzLabel;
    lbl8: TRzLabel;
    btnQueryCard: TBitBtn;
    lbl9: TRzLabel;
    lbl10: TRzLabel;
    lbl11: TRzLabel;
    lbl12: TRzLabel;
    edtShowCardNo: TRzEdit;
    edtCardNo: TRzEdit;
    edtCardPhyID: TRzEdit;
    edtCutID: TRzEdit;
    edtName: TRzEdit;
    edtCutType: TRzEdit;
    edtFeeType: TRzEdit;
    edtStuempNo: TRzEdit;
    edtDept: TRzEdit;
    edtCardStatus: TRzEdit;                                     
    edtEndDate: TRzEdit;
    btnQueryByCutID: TBitBtn;
    btnCLean: TBitBtn;
    lbl13: TRzLabel;
    edtSex: TRzEdit;
    edtSchoolCode: TRzEdit;
    lbl14: TRzLabel;
    lbl15: TRzLabel;
    edtCardPwd: TRzEdit;
    edtDuty: TRzEdit;
    lbl16: TRzLabel;
    lbl18: TRzLabel;
    edtIDType: TRzEdit;
    lbl19: TRzLabel;
    edtIDNo: TRzEdit;
    lblInfo: TRzLabel;
    edtBalance: TRzEdit;
    lbl17: TRzLabel;
    edtCountry: TRzEdit;
    lbl21: TRzLabel;
    edtNation: TRzEdit;
    lbl22: TRzLabel;
    btnReWriteCard: TBitBtn;
    btnRWCardInfo: TBitBtn;
    lbl23: TRzLabel;
    editTxCnt: TRzEdit;
    cbbSchool: TComboBox;
    lblschool: TRzLabel;
    btnShowInfo: TBitBtn;
    btnUpdatePhyNo: TButton;
    procedure AppMessage(var   Msg:   TMsg;   var   Handled:   Boolean);
    procedure btnInitCardClick(Sender: TObject);
    procedure btnCloseCardClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnCLeanClick(Sender: TObject);
    procedure btnQueryCardClick(Sender: TObject);
    procedure btnCardUpdateClick(Sender: TObject);
    procedure btnQueryByCutIDClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnReWriteCardClick(Sender: TObject);
    procedure btnRWCardInfoClick(Sender: TObject);
    procedure btnShowInfoClick(Sender: TObject);
    procedure btnUpdatePhyNoClick(Sender: TObject);
  private
    { Private declarations }
    {�ȼ���ʶID}
    IDSpace:Integer;
    IDR:Integer;
    bInit:boolean;
    procedure WMHotKey(var Msg : TWMHotKey); message WM_HOTKEY;
  public
    { Public declarations }
//    function QueryTestInfo(SQL:string):boolean;
    function QueryCardInfo(SQL:string):boolean;
    function QueryCardMoney(SQL:string):Boolean;
    function QuerySerialInfo(SQL:string):boolean;
    function WriteCardInfo():boolean;
    function WriteCardInfo2():boolean;
    function SaveSerial(cardphyid:string; balance:Integer; txcnt:Integer; oldcardphyid:string; transferflag:Integer; card_id:string):boolean;
    function SaveMoney(cardphyid:string; balance:Integer; txcnt:Integer):boolean;
    function SaveWriteUpdateLog(cardphyid,cutid:string;balance:Integer):boolean;
    function SaveWriteErrorLog(cardphyid,cutid:string):boolean;
    function SaveReWriteLog(cardphyid,cutid:string):boolean;
    function CheckFeeType(nFeeType:Integer):Integer;
  end;

var
  frmMain: TfrmMain;
  myinifile:TInifile;
  
implementation
uses
  UtCardDll;
const
// sWorkKey ='EAD781FEF965B3414ECE3D21';
// sWorkKey ='8E8BFC8FF68FF488';
 CARD_STRUCT_VERSION :string='1';
 CARD_REGISTER_PUBLISH_CODE:string ='9156000027';
 CARD_REGISTER_SERVICE_CODE:string ='D156000026';
var
  CardManage: TCardManage;

  WorkKey:array[0..16] of char;
  sWorkKey:string = '8E8BFC8FF68FF488';
  nSchoolType:Integer;
  sTotalCardNum:string;
  sTotalMoney:string;
  FeeTypeArray:array[1..20] of integer;
{$R *.dfm}

procedure   TfrmMain.AppMessage(var Msg:TMsg;var Handled:Boolean);
var
hwndedit:HWND;
begin
    Handled   :=   False;   //   ��Ϣ�������ɸ��������崦��
//    Handled   :=   True;     //   ��Ϣ�Ѿ��������,���Ϸ���
  if Msg.message =WM_KEYUP then
  begin
      lblInfo.Caption:='';
      if Msg.wParam=VK_RETURN then
      begin
//            if assigned (Screen.ActiveForm.ActiveControl) then
//            begin
//               if (Screen.ActiveForm.ActiveControl.Tag =1 ) then
//               begin
//                  if btnQueryByCutID.Enabled then
//                  begin
//                    Handled:=True;
//                    btnQueryByCutID.Click;
//                    exit;
//                  end;
//               end;
//           end;
           if btnReadCard.Enabled then
           begin
              Handled:=True;
              btnReadCard.Click;
           end;
      end;
      if Msg.wParam=VK_SPACE then
      begin
          if btnCardUpdate.Enabled then
          begin
            Handled:=True;
            btnCardUpdate.Click;
          end;
      end;
  end;
end;
procedure TfrmMain.WMHotKey(var Msg : TWMHotKey);
begin 
if msg.HotKey = IDSpace then
begin
    if btnCardUpdate.Enabled then
       btnCardUpdate.Click;
end;
frmMain.Visible :=true;
end;

procedure TfrmMain.btnInitCardClick(Sender: TObject);
var
ret:longint;
i:Integer;
src_text: array[1..17] of Char;
des_text: array[1..17] of Char;
begin
//    StrLCopy(@src_text, 'DAC20F5178EB96BC', 16);
//    encrypt_work_key_asc(@src_text, @des_text);
    
    lblInfo.Caption:='';
    ret:=ConnectMF(1,19200);
    if ret<>0 then
    begin
//        MessageBox(0, '��ʼ��������ʧ��', '����', MB_ICONWARNING or MB_OK);
        lblInfo.Font.color:=clred;
        lblInfo.Caption:='��ʼ��������ʧ��';
        exit;
    end;

    // װ����Կ
    ret := CardManage.ReadMachineAuth2(WorkKey);
    if ret <> 0 then
    begin
      ShowMessage('װ����Կʧ��');;
      Close;
    end;
    
    bInit:=true;
    btnInitCard.Enabled:=false;
    btnCloseCard.Enabled:=True;
    btnReadCard.Enabled:=True;
    btnQueryCard.Enabled:=True;
    btnCardUpdate.Enabled:=True;
    btnRWCardInfo.Enabled:=True;
end;

procedure TfrmMain.btnCloseCardClick(Sender: TObject);
begin
    SMT_ControlBuzzer;
    CloseMF();
    lblInfo.Caption:='';
    bInit:=false;
    btnInitCard.Enabled:=True;
    btnCloseCard.enabled:=false;
    btnReadCard.Enabled:=False;
    btnQueryCard.Enabled:=False;
    btnCardUpdate.Enabled:=False;
    btnReWriteCard.Enabled:=False;
    btnRWCardInfo.Enabled:=False;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
var
ret:integer;
str:string;
filename:string;
count:Integer;
pos:Integer;
Const 
{ALT��CTRL���������ֵ}
MOD_ALT = 1;
MOD_CONTROL = 2;
FEETYPE:string='TYPE';
begin
    Application.OnMessage   := AppMessage;
    bInit:=false;
    {�����жϳ����Ƿ��Ѿ�����}
//    if GlobalFindAtom('CardUpdateSpaceHotkey') = 0 then
//    begin
      {ע��ȫ���ȼ�}
//    IDSpace:=GlobalAddAtom('CardUpdateSpaceHotkey');
//    RegisterHotKey(handle,IDSpace,0,VK_SPACE);
//    IDR:=GlobalAddAtom('CardUpdateRHotkey');
//    RegisterHotKey(handle,IDR,0,VK_RETURN);
    btnCloseCard.enabled:=false;
    btnReadCard.Enabled:=False;
    btnQueryCard.Enabled:=False;
    btnCardUpdate.Enabled:=False;
    btnReWriteCard.Enabled:=False;
    btnRWCardInfo.Enabled:=False;
    CardManage:=TCardManage.Create;
    
    con1.ConnectionString:='FILE NAME=connaccess.udl';
    qry1.Connection:=con1;

    // �������ļ��ж�ȡWORKKEY�ַ���(����), ��̨�ַ���Ϊ(����)
    filename := ExtractFilePath(paramstr(0)) + 'CardDll.ini';
    myinifile := TInifile.Create(filename);
    str := myinifile.ReadString('WORKKEY', 'KEY', '');
    if str <> '' then
      sWorkKey := str;

 //   str:=Copy(sWorkKey,1,16);
    StrLCopy(@WorkKey, PChar(sWorkKey), 16);

    str := myinifile.ReadString('FEETYPECOUNT', 'NUM', '');
    count := StrToInt(str);
    for pos := 1 to count do
    begin
      str := FEETYPE + IntToStr(pos);
      str := myinifile.ReadString('FEETYPE', str, '');
      FeeTypeArray[pos] := StrToInt(str);
    end;
 
//    str := 'select no1, no2, no3 from test1 where no1 = 11';
//    QueryTestInfo(str);
    {
    HexStrToCharBuf(str,WorkKey);
    ret := CardManage.ReadMachineAuth(pchar(@WorkKey));
    if ret<>0 then
    begin
       ShowMessage('װ����Կʧ��');
//       Terminate;
      Close;
//      Exit;
    end;
    }
end;

procedure TfrmMain.btnReadCardClick(Sender: TObject);
var
pcm:TPublishCardMes;
//PurseInfo:LOOPPURSEINFO;
ret:smallint;
sCardPhyID:string;
CardSerialNo:Cardinal;
Buf:array [0..3] of Char;
CardPasswd:array[0..12] of char;
bSucc:boolean;
Balance:Integer;
TxCnt:Integer;
begin
  btnCLean.Click;
  bSucc:=false;
  ZeroMemory(@pcm,sizeof(pcm));
//  ZeroMemory(@PurseInfo,sizeof(PurseInfo));
  FillChar(CardPasswd, SizeOf(CardPasswd),0);
  //�������к�
  ret:=SimpleReadCardPhyID(sCardPhyID);
  if ret<>0 then
  begin
      lblinfo.Font.Color:=clRed;
      lblInfo.Caption:='��������ʧ��';
      exit;
  end;

  HexStrToCharBuf(sCardPhyID,Buf);
  CopyMemory(@CardSerialNo,@Buf,sizeof(CardSerialNo));
  edtCardPhyID.Text:= IntToStr(CardSerialNo);
  
  ret:=CardManage.ReadCardInfo(pcm);
  if ret<>0 then
  begin
      lblInfo.Font.Color:=clRed;
      lblInfo.Caption:='������Ϣʧ��';
      SMT_ControlBuzzer;
//      SMT_ControlBuzzer;
//      SMT_ControlBuzzer;
      exit;
  end;

  edtShowCardNo.Text:=string(pcm.ShowCardNo);
  edtCardNo.Text:=string(pcm.CardNo);
//  edtCutId.Text:=IntTostr(pcm.cut_id);
  edtName.Text:=string(pcm.ucName);
  edtCutType.Text:=string(pcm.ucIdentifyNo);
  edtFeeType.Text:=IntToStr(pcm.CardRightType);
  edtStuempNo.Text:=string(pcm.ucCardNo);
  edtDept.Text:=string(pcm.ucDepartmentNo);
  edtCardStatus.Text:='';
  edtEndDate.Text:=string(pcm.DeadLineDate);
  edtSex.Text:=string(pcm.ucSexNo);
//  edtIDType.Text:=string(pcm.certificate_type);
  edtIDNo.Text:=string(pcm.ucCertificateNo);
//  edtBalance.Text:=string(pcm.ucName);
// edtSchoolCode.Text:=(pcm.area_code);
//  edtCardPwd.Text:=string(pcm.ucPwd);
  ReadPersonalPassword(CardPasswd);
  edtCardPwd.Text:=string(CardPasswd);
  ret := ReadCardBalance(1, @Balance, @TxCnt);
  if ret <> 0 then
  begin
     lblInfo.Font.Color:=clRed;
     lblInfo.Caption:='�������ʧ��';
     exit;
  end;

  edtBalance.Text:= InttoStr(Balance);
  {
  bSucc:=CardManage.ReadCardConsumeInfo(PurseInfo,0);
  if not bSucc then
  begin
     lblInfo.Font.Color:=clRed;
     lblInfo.Caption:='�������ʧ��';
     exit;
  end;

  edtBalance.Text:= InttoStr(PurseInfo.RemainMoney);
  }

  if ((StrToInt(edtFeeType.Text)<1) or (StrToInt(edtFeeType.Text)>100)) then
  begin
      lblInfo.Font.Color:=clRed;
      lblInfo.Caption:='����:��������,�����·���';
      Exit;
  end;

  if StrToInt(edtCardNo.Text)<1 then
  begin
      lblInfo.Font.Color:=clRed;
      lblInfo.Caption:='����:����Ϊ0,�����·���';
      Exit;
  end;

  lblInfo.Font.Color:=clblue;
  SMT_ControlBuzzer;  
  lblInfo.Caption:='�����ɹ�';
  frmMain.SetFocus;  
//  if (StrLComp(PChar(qry1.FieldByName('��״̬').AsString),'11',2)=0) then
//  begin
//      lblInfo.Caption:='�ÿ��ѹ�ʧ';
//      Exit;
//  end;
//  btnReWriteCard.Enabled:=True; 
end;

procedure TfrmMain.btnCLeanClick(Sender: TObject);
var
   Index:Integer;
begin
   lblInfo.Caption:='';
   For Index:=0 to rzgrpbx1.ControlCount-1 do
   begin
       if rzgrpbx1.Controls[Index] is TRzEdit then
        begin
            TRzEdit(rzgrpbx1.Controls[Index]).Text:='';
        end;
   end;
   btnReWriteCard.Enabled:=false;
end;
procedure TfrmMain.btnQueryCardClick(Sender: TObject);
var
strSQL:string;
CardPhyID:string;
ret:integer;
CardSerialNo:Cardinal;
Buf:array [0..7] of Char;
SQLStr:string;
bQuery:boolean;
nBalance:Integer;
nTxCnt:Integer;
begin
  //�������к�
  btnCLean.Click;
  ret:=SimpleReadCardPhyID(CardPhyID);
  if ret<>0 then
  begin
      lblinfo.Font.Color:=clRed;
      lblInfo.Caption:='����ʧ��';
      exit;
  end;
  HexStrToCharBuf(CardPhyID,Buf);
  CopyMemory(@CardSerialNo,@Buf,sizeof(CardSerialNo));
  edtCardPhyID.Text:= IntToStr(CardSerialNo);
  SQLStr:=Format('select * from card where �����к� = ''%s'' and ��״̬ <> ''2000''',[edtCardPhyID.Text]);
  bQuery:=QueryCardInfo(SQLStr);
  if not bQuery then
  begin
      exit;
  end;

  // ��ȡ�Ͽ�Ǯ�����
  ret := CardManage.ReadCardBalance(@nBalance, @nTxCnt);
  if ret<>0 then
  begin
      lblInfo.Font.Color:=clRed;
      if ret = 100 then
      begin
        lblInfo.Caption:='��ȡǮ���������,�뻻��';
      end
      else
      begin
        lblInfo.Caption:='Ǯ�������Ѿ�����';
      end;
      exit;
  end;

  edtBalance.Text := Trim(IntToStr(nBalance));
  editTxCnt.Text := Trim(IntToStr(nTxCnt));
  
  if btnReWriteCard.Enabled = false then
      btnReWriteCard.Enabled:=True;
  lblInfo.Font.Color:=clblue;
  lblInfo.Caption:='��ѯ�ɹ� ' + '���:' + FloatToStr((StrToFloat(edtBalance.Text) / 100.0)) + 'Ԫ';;
end;

procedure TfrmMain.btnCardUpdateClick(Sender: TObject);
var
sCardNo:string;
ret:integer;
CardInfo: TPublishCardMes;
CardBalance:Integer;
bQuery:boolean;
sCardPhyID:string;
Buf:array [0..3] of Char;
CardSerialNo:Cardinal;
SQLStr:string;
bSucc:boolean;
StartTime:Integer;
EndTime:Integer;
nOutSchoolType:Integer;
begin
//    StartTime:=GetTickCount();
    CardSerialNo:=0;
    CardBalance:=0;
    lblInfo.Caption:='';
    bSucc:=false;

//    SQLStr:='delete from card where ��״̬ = ''2000''';
//    con1.Execute(SQLStr);

    // ѡ��ѧУ
    nSchoolType := cbbSchool.ItemIndex;
    if (nSchoolType < 0) or (nSchoolType > cbbSchool.Items.Count + 1) then
    begin
      ShowMessage('��ѡ��ѧУ');
      exit;
    end;

    // ��⿨Ƭ
    ret := CardManage.CheckCard(nSchoolType, @nOutSchoolType);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='���ת������ʧ��';    // �Ǳ�У��
        exit;
    end;

    nSchoolType := nOutSchoolType;

   //�������к�
    btnCLean.Click;
    ret:=SimpleReadCardPhyID(sCardPhyID);
    if ret<>0 then
    begin
        lblinfo.Font.Color:=clRed;
        lblInfo.Caption:='����ʧ��';
        exit;
    end;
    HexStrToCharBuf(sCardPhyID,Buf);
    CopyMemory(@CardSerialNo,@Buf,sizeof(CardSerialNo));
    edtCardPhyID.Text:= IntToStr(CardSerialNo);

    if CardManage.ReadExCardID(sCardNo)=0 then
    begin
      lblInfo.Font.Color:=clRed;
      lblInfo.Caption:='��������';
      frmMain.SetFocus;
//      SMT_ControlBuzzer;
      exit;
    end;

  //�����ݿ��в�ѯ����Ϣ
    {edtCardPhyID.Text := '1964642610';}
    SQLStr:=Format('select * from card where �����к� = ''%s'' and ��״̬ <> ''2000''',[edtCardPhyID.Text]);
    bQuery:=QueryCardInfo(SQLStr);
    if not bQuery then
    begin
       exit;
    end;

  //�жϿͻ��շ�������������ʦ����������ֹ����ת��
    ret := CheckFeeType(StrToInt(Trim(edtFeeType.Text)));
    if ret <> 0 then
    begin
      lblinfo.Font.Color:=clRed;
      lblInfo.Caption:='����𲻷�';
      exit;
    end;

    bSucc:=WriteCardInfo();
    if not bSucc then
    begin
      SaveWriteErrorLog(edtCardPhyID.Text,edtCutID.Text);
      exit;
    end;
//    SaveWriteUpdateLog(edtCardPhyID.Text,edtCutID.Text);
    endTime:=GetTickCount();
    lblInfo.Font.Color:=clBlue;         //TColor($FF8000);
    lblInfo.Caption:='�ɹ�';            //,�������֤';
    lblInfo.Caption := lblInfo.Caption + ' ' + '���:' + FloatToStr((StrToFloat(edtBalance.Text) / 100.0)) + 'Ԫ';
//    lblInfo.Caption := lblInfo.Caption + 'ʱ��:' + FloatToStr((EndTime-StartTime)/1000.0) + '��';
    frmMain.SetFocus;
end;

procedure TfrmMain.btnQueryByCutIDClick(Sender: TObject);
var
SQLStr:string;
bQuery:boolean;
begin
  lblInfo.Caption:='';
  if trim(edtCutID.Text) = '' then
  begin
    lblInfo.Font.Color:=clBlue;
    lblInfo.Caption:='������ͻ���';
    edtCutID.SetFocus;
    exit;
  end;
  SQLStr:=Format('select * from card where �ͻ��� = %s',[edtCutID.Text]);
  bQuery:=QueryCardInfo(SQLStr);
  if not bQuery then
    exit;
  if  bInit then
    if btnReWriteCard.Enabled = false then
        btnReWriteCard.Enabled:=True;
  lblInfo.Font.Color:=clblue;
  lblInfo.Caption:='���ͻ��Ų�ѯ�ɹ�';
end;

procedure TfrmMain.FormClose(Sender: TObject; var Action: TCloseAction);
begin
    myinifile.Destroy;
    if GlobalFindAtom('CardUpdateSpaceHotkey') <> 0 then
    begin
      UnregisterHotKey(handle,IDSpace);
      GlobalDeleteAtom(IDSpace);
    end;
    if GlobalFindAtom('CardUpdateRHotkey') <> 0 then
    begin
      UnregisterHotKey(handle,IDR);
      GlobalDeleteAtom(IDR);
    end;
end;

function TfrmMain.QueryCardInfo(SQL:string):boolean;
begin
  result:=false;
  if not con1.Connected then  con1.Connected:=true;
  qry1.SQL.Text:=SQL;
  qry1.Open;
  try
      if qry1.Eof then
      begin
         lblInfo.Font.Color:=clRed;
         lblInfo.Caption:='ϵͳ��û�иÿ�Ƭ����';
         exit;
      end;
      edtCardPhyID.Text:= trim(qry1.FieldByName('�����к�').AsString);
      edtShowCardNo.Text:=trim(qry1.FieldByName('��ʾ����').AsString);
      edtCardNo.Text:=qry1.FieldByName('����').AsString;
      edtCutID.Text:=qry1.FieldByName('�ͻ���').AsString;
      edtName.Text:=trim(qry1.FieldByName('����').AsString);
      edtCutType.Text:=qry1.FieldByName('�ͻ����').AsString;
      edtFeeType.Text:=qry1.FieldByName('�շ����').AsString;
      edtStuempNo.Text:=trim(qry1.FieldByName('ѧ��').AsString);
      edtDept.Text:=qry1.FieldByName('���Ŵ���').AsString;
      edtCardStatus.Text:=qry1.FieldByName('��״̬').AsString;
      edtEndDate.Text:=trim(qry1.FieldByName('��������').AsString);
      edtSex.Text:=trim(qry1.FieldByName('�Ա�').AsString);
//      edtBankAcc.Text:=trim(qry1.FieldByName('�����ʺ�').AsString);
      edtIDType.Text:=trim(qry1.FieldByName('֤������').AsString);
      edtIDNo.Text:=trim(qry1.FieldByName('֤������').AsString);
//      edtBalance.Text:=qry1.FieldByName('�����').AsString;
      edtSchoolCode.Text:= trim(qry1.FieldByName('�������').AsString);
      edtCardPwd.Text:= trim(qry1.FieldByName('������').AsString);
      edtCountry.Text:=Trim(qry1.FieldByName('����').AsString);
      edtNation.Text:=Trim(qry1.FieldByName('����').AsString);
      if (qry1.FieldByName('�շ����').AsInteger<1) or (qry1.FieldByName('�շ����').AsInteger>100) then
      begin
          lblInfo.Caption:='��ѯ��������:��������,��������ݿ�����';
          Exit;
      end;
      if qry1.FieldByName('����').AsInteger<1 then
      begin
          lblInfo.Caption:='��ѯ��������:����Ϊ0,��������ݿ�����';
          Exit;
      end;
      result:=true;
  finally
    qry1.Close;
  end;
end;
{
function TfrmMain.QueryTestInfo(SQL:string):boolean;
begin
  result:=false;
  if not con1.Connected then  con1.Connected:=true;
  qry1.SQL.Text:=SQL;
  qry1.Open;
  try
      if qry1.Eof then
      begin
         lblInfo.Font.Color:=clRed;
         lblInfo.Caption:='��ѯTEST��ʧ��';
         exit;
      end;
      ShowMessage('����1:' + qry1.FieldByName('no1').AsString +
                  '����2:' + qry1.FieldByName('no2').AsString +
                  '����3:' + qry1.FieldByName('no3').AsString);

      result:=true;
  finally
    qry1.Close;
  end;
end;
}

function TfrmMain.QuerySerialInfo(SQL:string):boolean;
begin
  result:=false;
  if not con1.Connected then  con1.Connected:=true;
  qry1.SQL.Text:=SQL;
  qry1.Open;
  try
      if qry1.Eof then
      begin
         lblInfo.Font.Color:=clRed;
         lblInfo.Caption:='ϵͳ��û�и���Ϣ';
         exit;
      end;

     sTotalCardNum := trim(qry1.FieldByName('total_card_num').AsString);
     sTotalMoney := trim(qry1.FieldByName('total_money').AsString);

      result:=true;
  finally
    qry1.Close;
  end;
end;

function TfrmMain.WriteCardInfo():boolean;
var
sCardNo:string;
ret:integer;
CardInfo: TPublishCardMes;
//CardBalance:Integer;
bQuery:boolean;
sCardPhyID:string;
Buf:array [0..3] of Char;
CardSerialNo:Cardinal;
errcode:integer;
nBalance:Integer;
nTxCnt:Integer;
nBlkFlag:Integer;
//pcAreaCode:array [1..3] of Char;
nAreaCode:Integer;
//tx_cnt : Integer;
begin
    //��ʼ��ʼ���ÿ�
    lblInfo.Font.Color:=clblue;
    lblInfo.Caption:='����д��,���Ե�...';

    result:=false;

    // ��ȡ�Ͽ�Ǯ�����
    ret := CardManage.ReadCardBalance(@nBalance, @nTxCnt);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        if ret = 100 then
        begin
          lblInfo.Caption:='��ȡǮ���������,�뻻��';
        end
        else
        begin
          lblInfo.Caption:='��Ƭ�������ܵ�¼';
        end;
        exit;
    end;

    // �ж��Ͽ�״̬
    // (1) ��ȡ���ݿ�card���Ͽ�״̬
    // (2) �ж��Ͽ�״̬
    // (3) �����Ϊ��ʧ�����쳣���ÿ���־Ϊ1, ����Ϊ0
    // (4) д����־������
    nBlkFlag := 0;
    ret := AnsiCompareStr(Trim(edtCardStatus.Text), '1000');
    if ret <> 0 then
    begin
      nBlkFlag := 1;
    end;

    nTxCnt := nTxCnt + 1;
    SaveMoney(edtCardPhyID.Text, nBalance, nTxCnt);
    edtBalance.Text:= Trim(IntToStr(nBalance));

     //����Ϣд�뿨�У�����dll����
    ZeroMemory(@CardInfo,sizeof(CardInfo));
    StrLCopy(@CardInfo.DeadLineDate, PChar(edtEndDate.Text),8);
    CardInfo.CardRightType := StrToInt(edtFeeType.Text);                   //�շ����
    StrLCopy(@CardInfo.CardNo, PChar(edtCardNo.Text),8);
    StrLCopy(@CardInfo.ucName, PChar(edtName.Text),8);
    StrLCopy(@CardInfo.ucDutyNo, PChar(edtDuty.Text),8);
    StrLCopy(@CardInfo.ucCertificateNo, PChar(edtIDNo.Text),20);           //���֤��
    StrLCopy(@CardInfo.ucDepartmentNo, PChar(edtDept.Text),10);
    StrLCopy(@CardInfo.ucSexNo, PChar(edtSex.Text),1);                     //ͼ��֤��
    StrLCopy(@CardInfo.ucIdentifyNo, PChar(edtCutType.Text),4);            //�ͻ����  cardPwd
    StrLCopy(@CardInfo.ucCardNo, PChar(edtStuempNo.Text),20);
    StrLCopy(@CardInfo.ucPwd, PChar(edtCardPwd.Text),6);
    StrLCopy(@CardInfo.ShowCardNo, PChar(edtShowCardNo.Text),10);
//    CardInfo.cut_id := StrToInt(edtCutID.Text);                            //�ͻ�ID��
//    StrLCopy(@CardInfo.area_code, PChar(edtSchoolCode.Text),2);            //ԺУ����
//    StrLCopy(@CardInfo.certificate_type, PChar(edtIDType.Text),2);         //֤������
//   StrLCopy(@CardInfo.people, PChar(edtNation.Text),2);                   //����
//    StrLCopy(@CardInfo.nationality, PChar(edtCountry.Text),3);             //����
//    StrLCopy(@CardInfo.card_version, PChar(CARD_STRUCT_VERSION),1);           //�ƿ��汾��
//    StrLCopy(@CardInfo.pub_card_flag,PChar(CARD_REGISTER_PUBLISH_CODE),10);   //����ע���ʶ��
//    StrLCopy(@CardInfo.ser_flag, PChar(CARD_REGISTER_SERVICE_CODE),10);        //����ע���ʶ��
//    CardBalance:=StrToInt(edtBalance.Text);
    ret := CardManage.RefineOldCard(nBlkFlag, nSchoolType, CardInfo);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='��������Ϣʧ��';
        exit;
    end;

    ret := CardManage.PacketSetMoney(1, nBalance);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='д������';
        exit;
    end;

    ret := CardManage.changeTradeNum(nTxCnt);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='Ǯ��д���״�������';
        exit;
    end;

 //   StrLCopy(@pcAreaCode, PChar(edtSchoolCode.Text),2);
    nAreaCode := StrToInt(Trim(edtSchoolCode.Text));
    ret := CardManage.WriteAreaCode(nAreaCode);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='д����������';
        exit;
    end;

    {
    ret := CardManage.UpdateCardBasicInfo(CardInfo);
    if ret<>0 then
    begin
      lblInfo.Font.Color:=clRed;
      lblInfo.Caption:='���¿���Ϣʧ��';
      exit;
    end;
    }
    {
    if CardManage.UpdateMoneyAndTxCnt(CardBalance,0,0)<>0 then
    begin
      lblInfo.Font.Color:=clRed;
      lblInfo.Caption:='���¿����ʧ��';
      exit;
    end;
    }
    // ������ˮ
    SaveSerial(edtCardPhyID.Text, nBalance, nTxCnt, edtCardPhyID.Text, 1, edtCardNo.Text);

    SMT_ControlBuzzer;
    result:=true;
end;

function TfrmMain.SaveSerial(cardphyid:string; balance:Integer; txcnt:Integer; oldcardphyid:string; transferflag:Integer; card_id:string):boolean;
var
SQLStr:string;
begin
  SQLStr:=format('insert into serial(cardphyid, card_money, tx_cnt, oldcardphyid, trans_flag, card_id) values(''%s'', ''%d'', ''%d'', ''%s'', ''%d'', ''%s'')',[cardphyid, balance, txcnt, oldcardphyid, transferflag, card_id]);
  con1.Execute(SQLStr);
end;

function TfrmMain.SaveMoney(cardphyid:string; balance:Integer; txcnt:Integer):boolean;
var
SQLStr:string;
begin
  SQLStr:=format('insert into moneylog(cardphyid, card_money, tx_cnt) values(''%s'', ''%d'', ''%d'')',[cardphyid, balance, txcnt]);
  con1.Execute(SQLStr);
end;

function TfrmMain.SaveWriteUpdateLog(cardphyid,cutid:string;balance:Integer):boolean;
var
SQLStr:string;
begin
  SQLStr:=format('insert into updatelog(cardphyid,cutid) values(''%s'',''%s'')',[cardphyid,cutid]);
  con1.Execute(SQLStr);
end;

function TfrmMain.SaveWriteErrorLog(cardphyid,cutid:string):boolean;
var
SQLStr:string;
begin
  SQLStr:=format('insert into errorlog(cardphyid,cutid) values(''%s'',''%s'')',[cardphyid,cutid]);
  con1.Execute(SQLStr);
end;

function TfrmMain.SaveReWriteLog(cardphyid,cutid:string):boolean;
var
SQLStr:string;
iRowsAffected:Integer;
begin
  SQLStr:=format('insert into rewritelog(cardphyid,cutid) values(''%s'',''%s'')',[cardphyid,cutid]);
  con1.Execute(SQLStr,iRowsAffected);
end;

function TfrmMain.CheckFeeType(nFeeType:Integer):Integer;
var
i:integer;
begin
  for i := 1 to 20 do       // ��ȡ�շ����
  begin
    if FeeTypeArray[i] = nFeeType then
    begin
      Result := 0;
      exit;
    end;
  end;

  Result := -1;
end;

procedure TfrmMain.btnReWriteCardClick(Sender: TObject);
var
bSucc:boolean;
ret:Integer;
nBlkFlag:Integer;
begin
  if(MessageBox(0, 'Ҫ��д����Ϣ��', '��ʾ', MB_ICONQUESTION or MB_OKCANCEL or MB_DEFBUTTON2)<>IDOK) then
    exit;

  nBlkFlag := 0;
  ret := AnsiCompareStr(Trim(edtCardStatus.Text), '1000');
  if ret <> 0 then
  begin
    nBlkFlag := 1;
  end;

  // ����ָ���������������ΪĬ������(6��FF), ���²�����д����Ϣ������
  nSchoolType := cbbSchool.ItemIndex;
  // ��д���ṹ
  ret := ReWriteCardInfo(nBlkFlag, nSchoolType);
  if ret<>0 then
  begin
      SaveWriteErrorLog(edtCardPhyID.Text, '0');
      lblInfo.Font.Color:=clRed;
      lblInfo.Caption:='���¿��ṹʧ��';
      exit;
  end;

  bSucc:=WriteCardInfo2();
  if not bSucc then
  begin
    SaveWriteErrorLog(edtCardPhyID.Text, '0');
    lblInfo.Font.Color:=clRed;
    lblInfo.Caption:='��Ƭ��дʧ��';
    exit;
  end;

//  SaveReWriteLog(edtCardPhyID.Text,edtCutID.Text);

  // ������ˮ
  SaveSerial(edtCardPhyID.Text, StrToInt(Trim(edtBalance.Text)), StrToInt(Trim(editTxCnt.Text)), edtCardPhyID.Text, 1, edtCardNo.Text);
//  btnCLean.Click;
  lblInfo.Font.Color:=clblue;
  lblInfo.Caption:='��Ƭ��д�ɹ�,�������֤';
  btnReWriteCard.Enabled:=false;
end;

function TfrmMain.WriteCardInfo2():boolean;
var
ret:integer;
CardInfo: TPublishCardMes;
bQuery:boolean;
CardPhyID:string;
SQLStr:string;
Buf:array [0..3] of Char;
CardSerialNo:Cardinal;
errcode : integer;
Balance : Integer;
//pcAreaCode:array [1..3] of Char;
nAreaCode:Integer;
nTxCnt:Integer;
begin
    ret:=SimpleReadCardPhyID(CardPhyID);
    if ret<>0 then
    begin
        lblinfo.Font.Color:=clRed;
        lblInfo.Caption:='����ʧ��';
        exit;
    end;
    HexStrToCharBuf(CardPhyID,Buf);
    CopyMemory(@CardSerialNo,@Buf,sizeof(CardSerialNo));
    SQLStr:=Format('select card_money, tx_cnt from moneylog where cardphyid = ''%s''',[Trim(IntToStr(CardSerialNo))]);
    bQuery := QueryCardMoney(SQLStr);
    if not bQuery then
    begin
        exit;
    end;
    //��ʼ��ʼ���ÿ�
    lblInfo.Font.Color:=clblue;
    lblInfo.Caption:='����д��,���Ե�...';
    result:=false;
    Balance := StrToInt(edtBalance.Text);
    //��ʽ��Ǯ������
    ret := CardManage.PacketSetMoney(1, Balance);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='��ʽ������Ϣ����';
        exit;
    end;

    nTxCnt := StrToInt(editTxCnt.Text);
    // �޸Ľ��״���
    ret := CardManage.changeTradeNum(nTxCnt);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='Ǯ��д���״�������';
        exit;
    end;

//    StrLCopy(@pcAreaCode, PChar(edtSchoolCode.Text),2);
    nAreaCode := StrToInt(Trim(edtSchoolCode.Text));
    ret := CardManage.WriteAreaCode(nAreaCode);
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='д����������';
        exit;
    end;

    //����Ϣд�뿨�У�����dll����
    ZeroMemory(@CardInfo,sizeof(CardInfo));
    StrLCopy(@CardInfo.DeadLineDate, PChar(edtEndDate.Text),8);
    CardInfo.CardRightType := StrToInt(edtFeeType.Text);                   //�շ����
    StrLCopy(@CardInfo.CardNo, PChar(edtCardNo.Text),8);
    StrLCopy(@CardInfo.ucName, PChar(edtName.Text),8);
    StrLCopy(@CardInfo.ucDutyNo, PChar(edtDuty.Text),8);
    StrLCopy(@CardInfo.ucCertificateNo, PChar(edtIDNo.Text),20);           //���֤��
    StrLCopy(@CardInfo.ucDepartmentNo, PChar(edtDept.Text),10);
    StrLCopy(@CardInfo.ucSexNo, PChar(edtSex.Text),1);                     //ͼ��֤��
    StrLCopy(@CardInfo.ucIdentifyNo, PChar(edtCutType.Text),4);            //�ͻ����  cardPwd
    StrLCopy(@CardInfo.ucCardNo, PChar(edtStuempNo.Text),20);
    StrLCopy(@CardInfo.ucPwd, PChar(edtCardPwd.Text),6);
    StrLCopy(@CardInfo.ShowCardNo, PChar(edtShowCardNo.Text),10);
    ret := CardManage.UpdateCardBasicInfo(CardInfo);
    if ret<>0 then
    begin
      lblInfo.Font.Color:=clRed;
      lblInfo.Caption:='���¿���Ϣʧ��';
      exit;
    end;
    SMT_ControlBuzzer;
    result:=true;
end;

procedure TfrmMain.btnRWCardInfoClick(Sender: TObject);
begin
{
    ret := ReWriteCardInfo();
    if ret<>0 then
    begin
        lblInfo.Font.Color:=clRed;
        lblInfo.Caption:='���¿��ṹʧ��';
        exit;
    end;
    SMT_ControlBuzzer;
    lblInfo.Font.Color:=clblue;
    lblInfo.Caption := '���¿��ṹ�ɹ�';
}
end;

function TfrmMain.QueryCardMoney(SQL:string):boolean;
begin
  result:=false;
  if not con1.Connected then  con1.Connected:=true;
  qry1.SQL.Text:=SQL;
  qry1.Open;
  try
      if qry1.Eof then
      begin
         lblInfo.Font.Color:=clRed;
         lblInfo.Caption:='ϵͳ��û�иÿ�Ƭ��Ϣ';
         exit;
      end;
      edtBalance.Text:= trim(qry1.FieldByName('card_money').AsString);
      editTxCnt.Text:= trim(qry1.FieldByName('tx_cnt').AsString);
      result:=true;
  finally
    qry1.Close;
  end;
end;

procedure TfrmMain.btnShowInfoClick(Sender: TObject);
var
  SQLStr:string;
  bQuery:boolean;
  sMsg:string;
begin
  SQLStr := 'select count(*) as total_card_num, sum(card_money) as total_money from serial';
  bQuery := QuerySerialInfo(SQLStr);
  if not bQuery then
  begin
      exit;
  end;
  sMsg := '��ǰ��ת������Ϊ:' + sTotalCardNum + ' �ܽ��Ϊ:' + FloatToStr((StrToFloat(sTotalMoney) / 100.0)) + 'Ԫ';
  ShowMessage(sMsg);
end;

procedure TfrmMain.btnUpdatePhyNoClick(Sender: TObject);
var
  SQLStr:string;
  bQuery:boolean;
  sMsg:string;
  physical_no:string;
  card_id:Integer;
begin
  physical_no := Trim(edtCardPhyID.Text);
  if (Trim(edtCardNo.Text) = '') then
  begin
    card_id := 0;
  end
  else
  begin
    card_id := StrtoInt(Trim(edtCardNo.Text));
  end;
  SQLStr:=format('update card set �����к�=' + '%s'+ ' where ����=' + '%d',[physical_no, card_id]);
{  SQLStr:='update moneylog set cardphyid=''1234'' where card_money=''0'''; }
{  SQLStr:=format('insert into moneylog(cardphyid, card_money, tx_cnt) values(''%s'', ''%d'', ''%d'')', ['1234567', 100, 10]);}
  con1.Execute(SQLStr);
  SMT_ControlBuzzer;
  
end;

end.

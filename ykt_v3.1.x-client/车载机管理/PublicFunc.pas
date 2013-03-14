{*******************************************************************************
    SunGard Kingstar Delphi Library
    Copyright (C) Kingstar Corporation

    <Unit>PublicFunc
    <What>���ֳֻ������ṩ��һЩ��̬����һ����ҵ���װ������λͼ,�·�������
          ת�������˷�װ
    <Written By> Lee.XiaoYang (������)  2009-07-03 16:20:35

    <History>-------------------------------------------------------------------
    
*******************************************************************************}

unit PublicFunc;

interface

uses
  Windows, Messages, SysUtils, Classes, ExtCtrls,Controls,Forms,Db,Dialogs,IniFiles,KSClientConsts;

//�������ļ��洢
type
   Tarraybyte = array of byte;  
  
//�������ڴ�洢�ṹ
type
    TBlack_Info_List = Packed Record
         usset0 : array[0..195] of char;
         usset1 : array[0..195] of char;
         usset2 : array[0..195] of char;
         usset3 : array[0..195] of char;
         usset4 : array[0..195] of char;
         usset5 : array[0..195] of char;
         usset6 : array[0..195] of char;
         scusttypes : array[0..397] of char;
         ssectypes  : array[0..397] of char;
         vsmess : array[0..505] of char;
         vsvarstr0 : array[0..505] of char;
         vsvarstr1 : array[0..505] of char;
         vsvarstr2 : array[0..505] of char;
         vsvarstr3 : array[0..505] of char;
end;
    PBlack_Info_List = ^TBlack_Info_List;

{-------------------------------------------------------------------------------
  ������:      ProcessToMenory
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               values : integer  ��Ҫת����ʮ��������
               Digit �� Integer  ת���ɼ�λByte
    ����:      ת����ָ����λByte��ʮ����������
  ����ֵ:      String
-------------------------------------------------------------------------------}
function ProcessToMenory(const values : integer; Digit : Integer) : String;


{-------------------------------------------------------------------------------
  ������:      StrToASCII
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               SRC : String  ��Դ�ַ���
               DES �� String  ת����ϵ�ASCII�ַ���
    ����:      ���ַ���ת��ASCII���ַ���
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function StrToASCII(SRC : String; var DES : String) : Boolean;

{-------------------------------------------------------------------------------
  ������:      HextoBinary
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Hex : String  ʮ�������ַ���
   ����:       ��ʮ�������ַ���ת�ɶ������ַ���
  ����ֵ:      String
-------------------------------------------------------------------------------}
function HextoBinary(Hex:string):string;

{-------------------------------------------------------------------------------
  ������:      IntToBin
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Value : LongInt ��Ҫת����ʮ���Ƴ���������
               Size �� Integer  ת������
   ����:       ��ʮ��������ת�ɶ������ַ���
  ����ֵ:      String
-------------------------------------------------------------------------------}
function IntToBin(Value: LongInt;Size: Integer): String;

{-------------------------------------------------------------------------------
  ������:      StrToBCD
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               str : string ��Ҫת�����ַ���

   ����:       ���ַ���ת��BCD����
  ����ֵ:      String
-------------------------------------------------------------------------------}
function StrToBCD(const str : string) : string;

{-------------------------------------------------------------------------------
  ������:      HTTest
    ����:      LandTech
    ����:      2009.7.3
    ����:
               Port : Integer  �ֳֻ����Ӷ˿�
               Baut : Integer   ���Ӳ�����
   ����:       ����Ƿ������ֳֻ�
               COM �ӿ�����
  ����ֵ:      Integer 0 �ɹ� !0ʧ��
-------------------------------------------------------------------------------}
function HTTest(const Port:Integer; const Baut : Integer) : integer;stdcall;
           external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      Usb_HTTest
    ����:      LandTech
    ����:      2009.7.3
    ����:
               index : Integer ���岻���
   ����:       ����Ƿ������ֳֻ�
               USB �ӿ�����
  ����ֵ:      Integer 0 �ɹ� !0ʧ��
-------------------------------------------------------------------------------}
function Usb_HTTest(const index : Integer) : integer;stdcall;
            external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      Usb_ExFGet
    ����:      LandTech
    ����:      2009.7.3
    ����:
               PCdir : Pchar PC���ļ�·��
               HTdir : Pchar �ֳֻ��ļ�·��
               Serial : Integer ���к�
   ����:       �����ֳֻ��ļ�
               USB �ӿ�����
  ����ֵ:      Integer 0 �ɹ� !0ʧ��
-------------------------------------------------------------------------------}
function Usb_ExFGet(PCdir : Pchar; HTdir :Pchar;Serial:integer):integer;stdcall;
             external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      Usb_ExFPut
    ����:      LandTech
    ����:      2009.7.3
    ����:
               PCdir : Pchar PC���ļ�·��
               HTdir : Pchar �ֳֻ��ļ�·��
               Serial : Integer ���к�
   ����:       �ϴ��ֳֻ��ļ�
               USB �ӿ�����
  ����ֵ:      Integer 0 �ɹ� !0ʧ��
-------------------------------------------------------------------------------}
function Usb_ExFPut(PCdir : Pchar; HTdir :Pchar;Serial:integer):integer;stdcall;
             external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      ExFGet
    ����:      LandTech
    ����:      2009.7.3
    ����:
               PCdir : Pchar PC���ļ�·��
               HTdir : Pchar �ֳֻ��ļ�·��
               Port : Integer  �ֳֻ����Ӷ˿�
               Baut : Integer   ���Ӳ�����
   ����:       �����ֳֻ��ļ�
               COM �ӿ�����
  ����ֵ:      Integer 0 �ɹ� !0ʧ��
-------------------------------------------------------------------------------}
function ExFGet(PCdir : Pchar; HTdir :Pchar;Port : integer ;Baut : integer;Serial:integer):integer;stdcall;
            external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      ExFPut
    ����:      LandTech
    ����:      2009.7.3
    ����:
               PCdir : Pchar PC���ļ�·��
               HTdir : Pchar �ֳֻ��ļ�·��
               Port : Integer  �ֳֻ����Ӷ˿�
               Baut : Integer   ���Ӳ�����
   ����:       �����ֳֻ��ļ�
               COM �ӿ�����
  ����ֵ:      Integer 0 �ɹ� !0ʧ��
-------------------------------------------------------------------------------}
function ExFPut(PCdir : Pchar; HTdir :Pchar;Port : integer ;Baut : integer;Serial:integer):integer;stdcall;
             external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      OpenCommPort
    ����:      LandTech
    ����:      2009.7.3
    ����:
               Port : Integer  �ֳֻ����Ӷ˿�
   ����:       �򿪴���
               COM �ӿ�����
  ����ֵ:      Integer 0 �ɹ� !0ʧ��
-------------------------------------------------------------------------------}
function OpenCommPort(Port : Integer) :integer;stdcall; external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      CloseCommPort
    ����:      LandTech
    ����:      2009.7.3
    ����:
   ����:       �رմ���
               COM �ӿ�����
  ����ֵ:      Integer 0 �ɹ� !0ʧ��
-------------------------------------------------------------------------------}
function CloseCommPort : integer;stdcall; external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      wSetDateTime
    ����:      Lee.XY
    ����:      2009.7.8
    ����:
               S_Date : ͬ������
               S_Time �� ͬ��ʱ��
               Port �� COM �˿�
               Baud : ������
   ����:       ͬ���ֳֻ�ʱ��
  ����ֵ:      Integer
-------------------------------------------------------------------------------}
function wSetDateTime(S_Date: Pchar; S_Time : Pchar; Port : Integer; Baud : Integer) : Integer; stdcall;
             external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      wSetDateTime
    ����:      Lee.XY
    ����:      2009.7.8
    ����:
               Filenames �� ɾ���ļ�
               Port �� COM �˿�
               Baud : ������
   ����:       ɾ���ļ�
  ����ֵ:      Integer
-------------------------------------------------------------------------------}
function DelHtFile(Filenames : Pchar; Port : Integer; Baud : Integer) : Integer; stdcall; external 'ht32dll.dll';

{-------------------------------------------------------------------------------
  ������:      DownloadFile
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               PCdir : Pchar PC���ļ�·��
               HTdir : Pchar �ֳֻ��ļ�·��
               Port : Integer  �ֳֻ����Ӷ˿�
               Baut : Integer   ���Ӳ�����
               Serial : Integer ���к�
               ConnType : Integer �ӿ�����
               ErrMsg : Sting ���ش�����Ϣ
   ����:       �����ļ���װ
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function DownloadFile(PCDir:Pchar; HTDir:Pchar; Port: Integer; Baut : Integer; Serial : Integer; ConnType : Integer; var ErrMsg : string) : boolean;

{-------------------------------------------------------------------------------
  ������:      UploadFile
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               PCdir : Pchar PC���ļ�·��
               HTdir : Pchar �ֳֻ��ļ�·��
               Port : Integer  �ֳֻ����Ӷ˿�
               Baut : Integer   ���Ӳ�����
               Serial : Integer ���к�
               ConnType : Integer �ӿ�����
               ErrMsg : Sting ���ش�����Ϣ
   ����:       �ϴ��ļ���װ
  ����ֵ:      IBoolean
-------------------------------------------------------------------------------}
function UploadFile(PCDir:Pchar; HTDir:Pchar; Port: Integer; Baut : Integer; Serial : Integer; ConnType : Integer; var ErrMsg : string) : boolean;

{-------------------------------------------------------------------------------
  ������:      Check_Machine
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Port : Integer  �ֳֻ����Ӷ˿�
               Baut : Integer   ���Ӳ�����
               Index : Integer ���к�
               ConnType : Integer �ӿ�����
               ErrMsg : Sting ���ش�����Ϣ
   ����:       �������Ƿ�����
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function Check_Machine(Const Port : integer; Const Baut : Integer; Const Index : Integer; Const ConnType : Integer; var ErrMsg:String) : Boolean;

{-------------------------------------------------------------------------------
  ������:      SaveToBinary
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Src : string  ��Ҫ����������ַ���
               Des : string  �����ļ���
               ByteCount : �������λbyte������
   ����:       ����ʮ�����Ƶ��������ļ�
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function SaveToBinary(const Src : string; const Des : String; const ByteCount : Integer) : Boolean;

{-------------------------------------------------------------------------------
  ������:      SaveToFile
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Src : string  ��Ҫ����������ַ���
               Filenames : string  �����ļ���
   ����:       ���泣�浽�������ļ�
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function SaveToFile( SrcStr : string; const Filenames : String) : Boolean;

{-------------------------------------------------------------------------------
  ������:      CRC16
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Src : string  ����У������ַ���
   ����:       ���������ַ�����CRC16��У����
  ����ֵ:      String 
-------------------------------------------------------------------------------}
function   GetCRC16Str(Str:String):String;

{-------------------------------------------------------------------------------
  ������:      CopyStrToChar
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Src : string  Դ�ַ���
               Des : array of char Ŀ������
               CopyCount : ��������
   ����:       �ַ���������char����
  ����ֵ:      Boolean 
-------------------------------------------------------------------------------}
function CopyStrToChar(const Src : String; var  Des: array of char; const CopyCount : Integer) : Boolean;

{-------------------------------------------------------------------------------
  ������:      Write_Record
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               BL ��Tlist ����ṹָ����б�
               ST_Pack : ��Ҫ��ȡ�����ݼ�
   ����:       �����ݼ�������д���ṹ��ָ��Ĵ洢��ȥ
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function Write_Record(BL:Tlist; ST_Pack : TDataSet) : Boolean;

{-------------------------------------------------------------------------------
  ������:      Read_Record_Str
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               BL ��Tlist ����ṹָ����б�
               Des : Ŀ���ַ���
   ����:       �����нṹ���е���������ʮ�������ַ���
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function  Read_Record_Str(BL:Tlist; var Des : String) : Boolean;

{-------------------------------------------------------------------------------
  ������:      CopyStrToChar
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Src ������
               Des : Ŀ���ַ���
   ����:       ����Ϊ�յ�Byte�滻��0
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function R_Byte(const Src : array of char; var Des : String) : Boolean;

{-------------------------------------------------------------------------------
  ������:      CopyStrToChar
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Bin ���������ַ���
   ����:       ������ת��ʮ������
  ����ֵ:      String
-------------------------------------------------------------------------------}
function BinToHex(Bin: String): String;

{-------------------------------------------------------------------------------
  ������:      LoadBinaryFile
    ����:      Lee.XY
    ����:      2009.7.3
    ����:
               Filenams : �������ļ�·��
               Des �� �������ļ���
   ����:       ��ȡ�������ļ����ݵ�byte����
  ����ֵ:      String
-------------------------------------------------------------------------------}
function LoadBinaryFile(Const Filenams: String;var Des : Tarraybyte; var Dlen : Integer): Boolean;

{-------------------------------------------------------------------------------
  ������:      ReadConfig
    ����:      Lee.XY
    ����:      2009.7.10
    ����:
               configdir:�����ļ�·��
   ����:       ��ȡ�����ļ�
  ����ֵ:      Boolean
-------------------------------------------------------------------------------}
function ReadConfig(const configdir:string='') : Boolean;

//�ǹ��ú��� ������ʹ�� ����˵��
function R_ASCII(var srcdes : string) : boolean;
  
const //Crc16��
  Table:Array[0..255] of Dword=
  (
        $0000, $1021, $2042, $3063, $4084, $50a5, $60c6, $70e7,
	$8108, $9129, $a14a, $b16b, $c18c, $d1ad, $e1ce, $f1ef,
	$1231, $0210, $3273, $2252, $52b5, $4294, $72f7, $62d6,
	$9339, $8318, $b37b, $a35a, $d3bd, $c39c, $f3ff, $e3de,
	$2462, $3443, $0420, $1401, $64e6, $74c7, $44a4, $5485,
	$a56a, $b54b, $8528, $9509, $e5ee, $f5cf, $c5ac, $d58d,
	$3653, $2672, $1611, $0630, $76d7, $66f6, $5695, $46b4,
	$b75b, $a77a, $9719, $8738, $f7df, $e7fe, $d79d, $c7bc,
	$48c4, $58e5, $6886, $78a7, $0840, $1861, $2802, $3823,
	$c9cc, $d9ed, $e98e, $f9af, $8948, $9969, $a90a, $b92b,
	$5af5, $4ad4, $7ab7, $6a96, $1a71, $0a50, $3a33, $2a12,
	$dbfd, $cbdc, $fbbf, $eb9e, $9b79, $8b58, $bb3b, $ab1a,
	$6ca6, $7c87, $4ce4, $5cc5, $2c22, $3c03, $0c60, $1c41,
	$edae, $fd8f, $cdec, $ddcd, $ad2a, $bd0b, $8d68, $9d49,
	$7e97, $6eb6, $5ed5, $4ef4, $3e13, $2e32, $1e51, $0e70,
	$ff9f, $efbe, $dfdd, $cffc, $bf1b, $af3a, $9f59, $8f78,
	$9188, $81a9, $b1ca, $a1eb, $d10c, $c12d, $f14e, $e16f,
	$1080, $00a1, $30c2, $20e3, $5004, $4025, $7046, $6067,
	$83b9, $9398, $a3fb, $b3da, $c33d, $d31c, $e37f, $f35e,
	$02b1, $1290, $22f3, $32d2, $4235, $5214, $6277, $7256,
	$b5ea, $a5cb, $95a8, $8589, $f56e, $e54f, $d52c, $c50d, 
	$34e2, $24c3, $14a0, $0481, $7466, $6447, $5424, $4405,
	$a7db, $b7fa, $8799, $97b8, $e75f, $f77e, $c71d, $d73c, 
	$26d3, $36f2, $0691, $16b0, $6657, $7676, $4615, $5634,
	$d94c, $c96d, $f90e, $e92f, $99c8, $89e9, $b98a, $a9ab, 
	$5844, $4865, $7806, $6827, $18c0, $08e1, $3882, $28a3,
	$cb7d, $db5c, $eb3f, $fb1e, $8bf9, $9bd8, $abbb, $bb9a, 
	$4a75, $5a54, $6a37, $7a16, $0af1, $1ad0, $2ab3, $3a92,
	$fd2e, $ed0f, $dd6c, $cd4d, $bdaa, $ad8b, $9de8, $8dc9, 
	$7c26, $6c07, $5c64, $4c45, $3ca2, $2c83, $1ce0, $0cc1,
	$ef1f, $ff3e, $cf5d, $df7c, $af9b, $bfba, $8fd9, $9ff8,
	$6e17, $7e36, $4e55, $5e74, $2e93, $3eb2, $0ed1, $1ef0
  );


var
  Recordfile : String;
  DownLoadDir : string;
  UpLoadDir : string;
  Port : Integer;
  BAUT : Integer;
  Index : Integer;
  PAYFILE : string;
  WELCOME : string;
  BLACKLIST : string;
  PURVIEW : string;
  KEY : STRING;
  uploadrecord:string;
  maxbrushtime : Integer;
  CARDGRP:string;
implementation


function ReadConfig(const configdir:string='') : Boolean;
var
  myinifile:Tinifile;
begin
  if Trim(configdir) = '' then
     myinifile :=Tinifile.Create(sPreAppPath+'configs\buspos.ini')
  else
     myinifile :=Tinifile.Create(configdir);
  try
    Recordfile := myinifile.ReadString('BUSPOS','RECORDFILE','RECORD.DAT');
    DownLoadDir := myinifile.ReadString('BUSPOS','DOWNLOADRECORDDIR','C:\');
    UpLoadDir := myinifile.ReadString('BUSPOS','UPLOADDIR','C:\');
    PORT :=  myinifile.ReadInteger('BUSPOS','PORT',0);
    BAUT :=  myinifile.ReadInteger('BUSPOS','BAUT',115200);
    Index :=  myinifile.ReadInteger('BUSPOS','INDEX',0);
    PAYFILE := myinifile.ReadString('BUSPOS','PAYFILE','PAY.DAT');
    WELCOME := myinifile.ReadString('BUSPOS','WELCOME','WELCOME.DAT');
    BLACKLIST := myinifile.ReadString('BUSPOS','BLACKLIST','blklst.dat');
    PURVIEW := myinifile.ReadString('BUSPOS','PURVIEW','PURVIEW.DAT');
    KEY := myinifile.ReadString('BUSPOS','KEY','KEY.DAT');
    uploadrecord :=myinifile.ReadString('BUSPOS','uploadrecord','c:\err.log');
    maxbrushtime := myinifile.ReadInteger('BUSPOS','maxbrushtime',60);
    CARDGRP :=myinifile.ReadString('BUSPOS','CARDGRP','cardgrp.dat');
  except
    on e:Exception do
      ShowMessage(e.Message);
  end;
  freeandnil(myinifile);
  Result := True;
end;

function R_ASCII(var srcdes : string ) : boolean;
var
  tempstr : string;
  i : integer;
begin
  tempstr := srcdes;
  srcdes := '';
  for i:=1 to length(tempstr) do
   srcdes:=srcdes+'3'+tempstr[i];
  Result := true;
end;

function BinToHex(Bin: String): String;
var
  vD: byte;
  i : integer;
  vHextstr : string;
  vp : pchar;
  vlen : integer;
begin
  vlen :=length(bin);
  if (vlen mod 4 > 0)  then
  begin
     SetLength(vHextstr,vlen div 4 + 1);
     vlen := vlen div 4 + 1;
  end
  else
  begin
     SetLength(vHextstr,vlen div 4 );
     vlen := vlen div 4 ;
  end;
  vd := 0;
  vp := Pchar(bin) + length(bin) -1;
  i := 0;
  while vp^ <> #0 do
  begin
    if vp^='1' then
    begin
       case i of
         0 : vd := vd+1;
         1 : vd := vd+2;
         2 : vd := vd+4;
         3 : vd := vd+8;
       end;
    end;
    dec(vp);
    inc(i);
    if i = 4 then
    begin
        case vd of
          0..9 : vhextstr[vlen] := chr(vd + $30);
          10..15 : vhextstr[vlen] := chr(vd -10 + $41);
        end;
        dec(vlen);
        i:=0;
        vd := 0;
    end;
  end;
  if i  > 0 then
  begin
    case vd of
          0..9 : vhextstr[vlen] := chr(vd + $30);
          10..15 : vhextstr[vlen] := chr(vd  + $41);
    end;
  end;
  Result := vhextstr;
end;


function R_Byte(const Src : array of char; var Des : String) : Boolean;
var
    i : Integer;
begin
    for i := 0 to sizeof(Src)-1 do
    begin
       if string(Src[i]) <> '' then
         Des := Des + string(Src[i])
       else  if string(Src[i]) = '' then
         Des := Des + '0';
    end;
    Result := True;
end;

function  Read_Record_Str(BL:Tlist; var Des : String) : Boolean;
var
     i : Integer;
begin
    Des := '';
    for i:=0 to BL.Count -1 do
    begin
       R_Byte(PBlack_Info_List(BL[i])^.usset0,Des);
       R_Byte(PBlack_Info_List(BL[i])^.usset1,Des);
       R_Byte(PBlack_Info_List(BL[i])^.usset2,Des);
       R_Byte(PBlack_Info_List(BL[i])^.usset3,Des);
       R_Byte(PBlack_Info_List(BL[i])^.usset4,Des);
       R_Byte(PBlack_Info_List(BL[i])^.usset5,Des);
       R_Byte(PBlack_Info_List(BL[i])^.usset6,Des); 
       R_Byte(PBlack_Info_List(BL[i])^.scusttypes,Des);
       R_Byte(PBlack_Info_List(BL[i])^.ssectypes,Des);
       R_Byte(PBlack_Info_List(BL[i])^.vsmess,Des);
       R_Byte(PBlack_Info_List(BL[i])^.vsvarstr0,Des);
       R_Byte(PBlack_Info_List(BL[i])^.vsvarstr1,Des);
       R_Byte(PBlack_Info_List(BL[i])^.vsvarstr2,Des);
       R_Byte(PBlack_Info_List(BL[i])^.vsvarstr3,Des);
    end;
    Result := True;
end;

function Write_Record(BL:Tlist; ST_Pack : TDataSet) : Boolean;
  var
     R_info : PBlack_Info_List;
     usset0_R  : String;
     usset1_R : String;
     usset2_R : String;
     usset3_R : String;
     usset4_R : String;
     usset5_R : String;
     usset6_R : String;
     scusttypes_R : String;
     ssectypes_R : String;
     vsmess_R : String;
     vsvarstr0_R : String;
     vsvarstr1_R : String;
     vsvarstr2_R : String;
     vsvarstr3_R : String;
begin
     ST_Pack.First;
     while not ST_Pack.Eof do
     begin
        new(R_info);
        usset0_R:=BinToHex(ST_Pack.fieldbyname('usset0').Asstring);
        usset1_R:=BinToHex(ST_Pack.fieldbyname('usset1').Asstring);
        usset2_R:=BinToHex(ST_Pack.fieldbyname('usset2').Asstring);
        usset3_R:=BinToHex(ST_Pack.fieldbyname('usset3').Asstring);
        usset4_R :=ST_Pack.fieldbyname('usset4').Asstring;
        R_ASCII(usset4_R);
        usset5_R :=ST_Pack.fieldbyname('usset5').Asstring;
        R_ASCII(usset5_R);
        usset6_R :=ST_Pack.fieldbyname('usset5').Asstring;
        R_ASCII(usset6_R);
        scusttypes_R:=ST_Pack.fieldbyname('scusttypes').Asstring;
        ssectypes_R:=ST_Pack.fieldbyname('ssectypes').Asstring;
        vsmess_R:=ST_Pack.fieldbyname('vsmess').Asstring;
        vsvarstr0_R:=ST_Pack.fieldbyname('vsvarstr0').Asstring;
        vsvarstr1_R:=ST_Pack.fieldbyname('vsvarstr1').Asstring;
        vsvarstr2_R:=ST_Pack.fieldbyname('vsvarstr2').Asstring;
        vsvarstr3_R:=ST_Pack.fieldbyname('vsvarstr3').Asstring;

        CopyStrToChar(usset0_R,R_info^.usset0,length(usset0_R)-4);
        CopyStrToChar(usset1_R,R_info^.usset1,length(usset1_R)-4);
        CopyStrToChar(usset2_R,R_info^.usset2,length(usset2_R)-4);
        CopyStrToChar(usset3_R,R_info^.usset3,length(usset3_R)-4);
        CopyStrToChar(usset4_R,R_info^.usset4,length(usset4_R)-2);
        CopyStrToChar(usset5_R,R_info^.usset5,length(usset5_R)-2);
        CopyStrToChar(usset6_R,R_info^.usset6,length(usset6_R)-2);
        CopyStrToChar(scusttypes_R,R_info^.scusttypes,length(scusttypes_R)-2);
        CopyStrToChar(ssectypes_R,R_info^.ssectypes,length(ssectypes_R)-2);
        CopyStrToChar(vsmess_R,R_info^.vsmess,length(vsmess_R)-4);
        CopyStrToChar(vsvarstr0_R,R_info^.vsvarstr0,length(vsvarstr0_R)-4);
        CopyStrToChar(vsvarstr1_R,R_info^.vsvarstr1,length(vsvarstr1_R)-4);
        CopyStrToChar(vsvarstr2_R,R_info^.vsvarstr2,length(vsvarstr2_R)-4);
        CopyStrToChar(vsvarstr3_R,R_info^.vsvarstr3,length(vsvarstr3_R)-4);

        BL.Add(R_info);
        ST_Pack.Next;
     end;
     Result := True;
end;

function CopyStrToChar(const Src: String; var Des: array of char; const CopyCount: Integer): Boolean;
  var
    i : Integer;
begin
    for i := 0 to sizeof(Des) -1 do
      Des[i]:=#0;
    for i:= 1 to CopyCount do
      Des[i-1]:=Src[i];
    Result := True;
end;

function HextoBinary(Hex:string):string;
  const
    BOX: array [0..15] of string =
         ('0000','0001','0010','0011',
          '0100','0101','0110','0111',
          '1000','1001','1010','1011',
          '1100','1101','1110','1111');
  var
    i:integer;
begin
    for i:=Length(Hex) downto 1 do
        Result:=BOX[StrToInt('$'+Hex[i])]+Result;
end;

function IntToBin(Value: LongInt;Size: Integer): String;
  var
    i: Integer;
begin
    Result:='';
    for i:=Size-1 downto 0 do
    begin
      if Value and (1 shl i)<>0 then
        Result:=Result+'1'
     else
       Result:=Result+'0';
   end;
end;

function StrToBCD(const str : string) : string;
 var
   i : integer;
begin
    i :=1;
    while (i<=length(str)) do
    begin
       result :=result+'$'+str[i]+str[i+1];
       inc(i,2);
    end;
end;

function DownloadFile(PCDir:Pchar; HTDir:Pchar; Port: Integer; Baut : Integer; Serial : Integer; ConnType : Integer;  var ErrMsg : string) : boolean;
  var
     ISOK : Integer;
begin
      ErrMsg := '';
      Result := false;
      if (length(PCDir)>100) then
      begin
        ErrMsg := '�ļ�·������̫�����뽫�ļ����ø�Ŀ¼����!';
        Exit;
      end;
      ISOK :=0;
      CloseCommPort;
      if not Check_Machine(Port,Baut,Serial,ConnType,ErrMsg) then exit;
      CloseCommPort;
      if (ConnType = 0) then
         ISOK := ExFGet(PCDir,HTDir,Port,Baut,Serial)
      else if (ConnType = 1) then
         ISOK := USB_ExFGet(PCDir,HTDir,Serial);
      if (ISOK <> 0) then
         ErrMsg:='�����ֳֻ��ļ�ʧ��!'+inttostr(isok)
      else
         Result := True;
end;

function UploadFile(PCDir:Pchar; HTDir:Pchar; Port: Integer; Baut : Integer; Serial : Integer; ConnType : Integer;  var ErrMsg : string) : boolean;
  var
     ISOK : Integer;
begin
     ErrMsg := '';
     Result := false;
     if (length(PCDir)>250) then
     begin
        ErrMsg := '�ļ�·������̫�����뽫�ļ����ø�Ŀ¼����!';
        Exit;
     end;
     CloseCommPort;

     ISOK :=0;
     if (ConnType = 0) then
     ISOK := ExFPut(PCDir,HTDir,Port,Baut,Serial)
     else  if (ConnType = 1) then
     ISOK := USB_ExFPut(PCDir,HTDir,Serial);
     if (ISOK <> 0) then
        ErrMsg:='�ϴ��ֳֻ��ļ�ʧ��!'
     else
      begin
        ErrMsg:= '�ϴ��ļ��ɹ�!';
        Result := True;
      end;
end;


function Check_Machine(Const Port : integer; Const Baut : Integer; Const Index : Integer; Const ConnType : Integer; var ErrMsg:String) : Boolean;
  var
    ISOK : Integer;
begin
      ErrMsg :='';
      ISOK := 0;
      Result := False;
      if (ConnType=0) then
        ISOK := HTTest(Port,Baut)
      else if (ConnType = 1) then
        ISOK := USB_HTTest(Index);
      if ISOK <> 0 then
          ErrMsg := '����ֳֻ������ڣ��������������ߣ��Լ��Ƿ񿪻���'
      else
         Result := True;
end;

function StrToASCII(SRC : String; var DES : String) : Boolean;
   var
     i : Integer;
begin
     DES := '';
     for i:=0 to length(SRC) do
     DES:=DES+IntToStr(Ord(SRC[i]));
     Result := True;
end;

function ProcessToMenory(const values : integer; Digit : Integer) : String;
begin
       Result := IntToHex(values,Digit*2);
end;

function SaveToFile( SrcStr : string; const Filenames : String) : Boolean;
var
     DestFile : FILE;
     Buf: array[0..31] of Char;
     writers,i : integer;
begin
      for i := 0 to sizeof(buf) -1 do
         buf[i]:=#0;
      for i := 0 to length(SrcStr) do
         Buf[i] := srcstr[i];

      AssignFile(DestFile, Filenames);
      Rewrite(DestFile,1);
      BlockWrite(DestFile,Buf,32,writers);
      CloseFile(DestFile);
      Result := True;
end;

function SaveToBinary(const Src : string; const Des : String; const ByteCount : Integer) : Boolean;
var
      DestFile:   File;
      BytesWritten:   Integer;
      Buffer:   array[0..20000] of byte;
      strConnect:   string;
      intLength:   Integer;
      i : integer;
      j : integer;
      x : integer;
begin
      AssignFile(DestFile,Des);
      StrConnect := Src;
      intLength := Length(strConnect);
      i:=0;
      j := 0;
      x :=1;

      while (i < intLength) do
      begin
            case Ord(StrConnect[x]) of
                 48 : begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$00;
                            49 : Buffer[j] :=$01;
                            50 : Buffer[j] :=$02;
                            51 : Buffer[j] :=$03;
                            52 : Buffer[j] :=$04;
                            53 : Buffer[j] :=$05;
                            54 : Buffer[j] :=$06;
                            55 : Buffer[j] :=$07;
                            56 : Buffer[j] :=$08;
                            57 : Buffer[j] :=$09;
                            65 : Buffer[j] :=$0A;
                            66 : Buffer[j] :=$0B;
                            67 : Buffer[j] :=$0C;
                            68 : Buffer[j] :=$0D;
                            69 : Buffer[j] :=$0E;
                            70 : Buffer[j] :=$0F;
                         end;
                     end;
                 49 : begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$10;
                            49 : Buffer[j] :=$11;
                            50 : Buffer[j] :=$12;
                            51 : Buffer[j] :=$13;
                            52 : Buffer[j] :=$14;
                            53 : Buffer[j] :=$15;
                            54 : Buffer[j] :=$16;
                            55 : Buffer[j] :=$17;
                            56 : Buffer[j] :=$18;
                            57 : Buffer[j] :=$19;
                            65 : Buffer[j] :=$1A;
                            66 : Buffer[j] :=$1B;
                            67 : Buffer[j] :=$1C;
                            68 : Buffer[j] :=$1D;
                            69 : Buffer[j] :=$1E;
                            70 : Buffer[j] :=$1F;
                         end;
                     end;
                 50 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$20;
                            49 : Buffer[j] :=$21;
                            50 : Buffer[j] :=$22;
                            51 : Buffer[j] :=$23;
                            52 : Buffer[j] :=$24;
                            53 : Buffer[j] :=$25;
                            54 : Buffer[j] :=$26;
                            55 : Buffer[j] :=$27;
                            56 : Buffer[j] :=$28;
                            57 : Buffer[j] :=$29;
                            65 : Buffer[j] :=$2A;
                            66 : Buffer[j] :=$2B;
                            67 : Buffer[j] :=$2C;
                            68 : Buffer[j] :=$2D;
                            69 : Buffer[j] :=$2E;
                            70 : Buffer[j] :=$2F;
                         end;
                     end;
                 51 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$30;
                            49 : Buffer[j] :=$31;
                            50 : Buffer[j] :=$32;
                            51 : Buffer[j] :=$33;
                            52 : Buffer[j] :=$34;
                            53 : Buffer[j] :=$35;
                            54 : Buffer[j] :=$36;
                            55 : Buffer[j] :=$37;
                            56 : Buffer[j] :=$38;
                            57 : Buffer[j] :=$39;
                            65 : Buffer[j] :=$3A;
                            66 : Buffer[j] :=$3B;
                            67 : Buffer[j] :=$3C;
                            68 : Buffer[j] :=$3D;
                            69 : Buffer[j] :=$3E;
                            70 : Buffer[j] :=$3F;
                         end;
                     end;
                 52 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$40;
                            49 : Buffer[j] :=$41;
                            50 : Buffer[j] :=$42;
                            51 : Buffer[j] :=$43;
                            52 : Buffer[j] :=$44;
                            53 : Buffer[j] :=$45;
                            54 : Buffer[j] :=$46;
                            55 : Buffer[j] :=$47;
                            56 : Buffer[j] :=$48;
                            57 : Buffer[j] :=$49;
                            65 : Buffer[j] :=$4A;
                            66 : Buffer[j] :=$4B;
                            67 : Buffer[j] :=$4C;
                            68 : Buffer[j] :=$4D;
                            69 : Buffer[j] :=$4E;
                            70 : Buffer[j] :=$4F;
                         end;
                     end;
                 53 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$50;
                            49 : Buffer[j] :=$51;
                            50 : Buffer[j] :=$52;
                            51 : Buffer[j] :=$53;
                            52 : Buffer[j] :=$54;
                            53 : Buffer[j] :=$55;
                            54 : Buffer[j] :=$56;
                            55 : Buffer[j] :=$57;
                            56 : Buffer[j] :=$58;
                            57 : Buffer[j] :=$59;
                            65 : Buffer[j] :=$5A;
                            66 : Buffer[j] :=$5B;
                            67 : Buffer[j] :=$5C;
                            68 : Buffer[j] :=$5D;
                            69 : Buffer[j] :=$5E;
                            70 : Buffer[j] :=$5F;
                         end;
                     end;
                 54 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$60;
                            49 : Buffer[j] :=$61;
                            50 : Buffer[j] :=$62;
                            51 : Buffer[j] :=$63;
                            52 : Buffer[j] :=$64;
                            53 : Buffer[j] :=$65;
                            54 : Buffer[j] :=$66;
                            55 : Buffer[j] :=$67;
                            56 : Buffer[j] :=$68;
                            57 : Buffer[j] :=$69;
                            65 : Buffer[j] :=$6A;
                            66 : Buffer[j] :=$6B;
                            67 : Buffer[j] :=$6C;
                            68 : Buffer[j] :=$6D;
                            69 : Buffer[j] :=$6E;
                            70 : Buffer[j] :=$6F;
                         end;
                     end;
                 55 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$70;
                            49 : Buffer[j] :=$71;
                            50 : Buffer[j] :=$72;
                            51 : Buffer[j] :=$73;
                            52 : Buffer[j] :=$74;
                            53 : Buffer[j] :=$75;
                            54 : Buffer[j] :=$76;
                            55 : Buffer[j] :=$77;
                            56 : Buffer[j] :=$78;
                            57 : Buffer[j] :=$79;
                            65 : Buffer[j] :=$7A;
                            66 : Buffer[j] :=$7B;
                            67 : Buffer[j] :=$7C;
                            68 : Buffer[j] :=$7D;
                            69 : Buffer[j] :=$7E;
                            70 : Buffer[j] :=$7F;
                         end;
                     end;
                 56 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$80;
                            49 : Buffer[j] :=$81;
                            50 : Buffer[j] :=$82;
                            51 : Buffer[j] :=$83;
                            52 : Buffer[j] :=$84;
                            53 : Buffer[j] :=$85;
                            54 : Buffer[j] :=$86;
                            55 : Buffer[j] :=$87;
                            56 : Buffer[j] :=$88;
                            57 : Buffer[j] :=$89;
                            65 : Buffer[j] :=$8A;
                            66 : Buffer[j] :=$8B;
                            67 : Buffer[j] :=$8C;
                            68 : Buffer[j] :=$8D;
                            69 : Buffer[j] :=$8E;
                            70 : Buffer[j] :=$8F;
                         end;
                     end;
                 57 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$90;
                            49 : Buffer[j] :=$91;
                            50 : Buffer[j] :=$92;
                            51 : Buffer[j] :=$93;
                            52 : Buffer[j] :=$94;
                            53 : Buffer[j] :=$95;
                            54 : Buffer[j] :=$96;
                            55 : Buffer[j] :=$97;
                            56 : Buffer[j] :=$98;
                            57 : Buffer[j] :=$99;
                            65 : Buffer[j] :=$9A;
                            66 : Buffer[j] :=$9B;
                            67 : Buffer[j] :=$9C;
                            68 : Buffer[j] :=$9D;
                            69 : Buffer[j] :=$9E;
                            70 : Buffer[j] :=$9F;
                         end;
                     end;
                 65 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$A0;
                            49 : Buffer[j] :=$A1;
                            50 : Buffer[j] :=$A2;
                            51 : Buffer[j] :=$A3;
                            52 : Buffer[j] :=$A4;
                            53 : Buffer[j] :=$A5;
                            54 : Buffer[j] :=$A6;
                            55 : Buffer[j] :=$A7;
                            56 : Buffer[j] :=$A8;
                            57 : Buffer[j] :=$A9;
                            65 : Buffer[j] :=$AA;
                            66 : Buffer[j] :=$AB;
                            67 : Buffer[j] :=$AC;
                            68 : Buffer[j] :=$AD;
                            69 : Buffer[j] :=$AE;
                            70 : Buffer[j] :=$AF;
                         end;
                     end;
                 66 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$B0;
                            49 : Buffer[j] :=$B1;
                            50 : Buffer[j] :=$B2;
                            51 : Buffer[j] :=$B3;
                            52 : Buffer[j] :=$B4;
                            53 : Buffer[j] :=$B5;
                            54 : Buffer[j] :=$B6;
                            55 : Buffer[j] :=$B7;
                            56 : Buffer[j] :=$B8;
                            57 : Buffer[j] :=$B9;
                            65 : Buffer[j] :=$BA;
                            66 : Buffer[j] :=$BB;
                            67 : Buffer[j] :=$BC;
                            68 : Buffer[j] :=$BD;
                            69 : Buffer[j] :=$BE;
                            70 : Buffer[j] :=$BF;
                         end;
                     end;
                 67 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$C0;
                            49 : Buffer[j] :=$C1;
                            50 : Buffer[j] :=$C2;
                            51 : Buffer[j] :=$C3;
                            52 : Buffer[j] :=$C4;
                            53 : Buffer[j] :=$C5;
                            54 : Buffer[j] :=$C6;
                            55 : Buffer[j] :=$C7;
                            56 : Buffer[j] :=$C8;
                            57 : Buffer[j] :=$C9;
                            65 : Buffer[j] :=$CA;
                            66 : Buffer[j] :=$CB;
                            67 : Buffer[j] :=$CC;
                            68 : Buffer[j] :=$CD;
                            69 : Buffer[j] :=$CE;
                            70 : Buffer[j] :=$CF;
                         end;
                     end;
                 68 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$D0;
                            49 : Buffer[j] :=$D1;
                            50 : Buffer[j] :=$D2;
                            51 : Buffer[j] :=$D3;
                            52 : Buffer[j] :=$D4;
                            53 : Buffer[j] :=$D5;
                            54 : Buffer[j] :=$D6;
                            55 : Buffer[j] :=$D7;
                            56 : Buffer[j] :=$D8;
                            57 : Buffer[j] :=$D9;
                            65 : Buffer[j] :=$DA;
                            66 : Buffer[j] :=$DB;
                            67 : Buffer[j] :=$DC;
                            68 : Buffer[j] :=$DD;
                            69 : Buffer[j] :=$DE;
                            70 : Buffer[j] :=$DF;
                         end;
                     end;
                   69 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$E0;
                            49 : Buffer[j] :=$E1;
                            50 : Buffer[j] :=$E2;
                            51 : Buffer[j] :=$E3;
                            52 : Buffer[j] :=$E4;
                            53 : Buffer[j] :=$E5;
                            54 : Buffer[j] :=$E6;
                            55 : Buffer[j] :=$E7;
                            56 : Buffer[j] :=$E8;
                            57 : Buffer[j] :=$E9;
                            65 : Buffer[j] :=$EA;
                            66 : Buffer[j] :=$EB;
                            67 : Buffer[j] :=$EC;
                            68 : Buffer[j] :=$ED;
                            69 : Buffer[j] :=$EE;
                            70 : Buffer[j] :=$EF;
                         end;
                     end;
                   70 :  begin
                         case Ord(strConnect[x+1]) of
                            48 : Buffer[j] :=$F0;
                            49 : Buffer[j] :=$F1;
                            50 : Buffer[j] :=$F2;
                            51 : Buffer[j] :=$F3;
                            52 : Buffer[j] :=$F4;
                            53 : Buffer[j] :=$F5;
                            54 : Buffer[j] :=$F6;
                            55 : Buffer[j] :=$F7;
                            56 : Buffer[j] :=$F8;
                            57 : Buffer[j] :=$F9;
                            65 : Buffer[j] :=$FA;
                            66 : Buffer[j] :=$FB;
                            67 : Buffer[j] :=$FC;
                            68 : Buffer[j] :=$FD;
                            69 : Buffer[j] :=$FE;
                            70 : Buffer[j] :=$FF;
                         end;
                     end;
            end;
            inc(i,2);
            inc(x,2);
            inc(j);
     end;
     Rewrite(DestFile, 1);
     try
       try
          BlockWrite(DestFile,Buffer,ByteCount,BytesWritten);
       except
          Erase(DestFile);
          raise;
       end;
     finally
       CloseFile(DestFile);
     end;
     Result := True;
end;

function  GetCRC16Str(Str:String):String;
var
    crc,i:WORD;
begin
    crc := 0;
    for i := 1 to length(str) do
        crc:=Table[(Byte(crc shr 8) and $FF) xor (ord(str[i]) and $FF )] xor (crc shl 8);
    Result:=IntTohex(crc,2);   
end;

function LoadBinaryFile(Const Filenams: String; var DES : Tarraybyte; var Dlen : Integer): Boolean;
var
  Cnt:Integer;
  MemStream:TMemoryStream;
begin
    MemStream:=TMemoryStream.Create;
    MemStream.LoadFromFile(Filenams);
    Cnt:=MemStream.Size;
    MemStream.Position:=0;
    SetLength(Des,Cnt);
    MemStream.ReadBuffer(Pointer(Des)^,Cnt);
    Dlen := Cnt;
    MemStream.free;
    Result := True;
end;


end.

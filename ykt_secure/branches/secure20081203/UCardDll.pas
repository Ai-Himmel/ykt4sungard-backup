unit UCardDll;

interface

uses messages, dialogs;

const
  SelectSmartCardType = '0x18';

  {��д������

  ��ڲ�����
  nPortNo�����ں�
  nBaudRate��ͨѶ������ 19200
  ���ڲ�������
  ����ֵ��
  0�����ӳɹ�
  -1������ʧ��}
function SMT_ConnectMF280(nPortNo: longint; nBaudRate: longint): longint;
stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ConnectMF280';

{��д���ض�

��ڲ�������
���ڲ�������
����ֵ��
 0���ضϳɹ�
-1���ض�ʧ��
}
function SMT_CloseMF280: longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_CloseMF280';

{��д������������

��ڲ�������
���ڲ�������
����ֵ��
 0���ɹ�
   -1��ʧ��
}
function SMT_ControlBuzzer: longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ControlBuzzer';

{����û����Ƿ��ڸ�Ӧ��

��ڲ�������
���ڲ�����
ucSerialNo���û���Ӳ�����к�
ucType��   �û������ʹ��루0x08��S50����
0x18��S70�� PHILIPS
0x53��S70�� ����΢���ӣ�
����ֵ��
 0����ȡ�ɹ�
��������ȡʧ��
}
function SMT_RequestCardExist(ucSerialNo: pChar; ucType: PChar): longint;
stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_RequestCardExist';

{�û�ʹ���Զ���������е�½

��ڲ�����
 Sector��������
key��6�ֽ�����
keyFlag��0��keyA    1��keyB
���ڲ�����
��
����ֵ
 0����½�ɹ�
��������½ʧ��
}
function SMT_Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_Login_With_UserKey';

{��ȡ����Ϣ

��ڲ���:
 Sector��������
 BlockNo�����
���ڲ���:
 BlockBuf��16�ֽ����� HEX
����ֵ��
 0���ɹ�
 ������ʧ��
}
function SMT_ReadBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ReadBlock';

{д����Ϣ

��ڲ�����
 Sector��������
 BlockNo�����
 BlockBuf��16�ֽ����ݣ�HEX
���ڲ�����
 BlockBuf����ָ���������ڵĶ�Ӧ�����������
����ֵ��
 0���ɹ�
 ������ʧ��
}
function SMT_WriteBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_WriteBlock';

{PHILIPSǮ������

��ڲ�����
 flag��0--��Ǯ 1--��Ǯ
 Sector��������
 Block�����
 Money�����
���ڲ�����
 BlockBuf��ִ�гɹ������ؿ���16�ֽ���������
����ֵ��
 0���ɹ�
 ������ʧ��
}
function SMT_Phlips_Packet_Proc(flag: longint; Sector: longint; BlockNo:
  longint;
  Money: longint; BlockBuf: PChar): longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_Phlips_Packet_Proc';

{�û�������

��ڲ�������
���ڲ�������
����ֵ��
 0���ɹ�
 ������ʧ��
}
function SMT_SleepCard: longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_SleepCard';

{���ݿ�COPY

��ڲ�����
 Sector��������
 souBlock��Դ���
 desBlock��Ŀ�Ŀ��
���ڲ�����
 BlockBuf��ִ�гɹ�������Ŀ�Ŀ���16�ֽ���������
����ֵ��
 0���ɹ�
 ������ʧ��
}
function SMT_Copy_DataBlock(Sector: longint; souBlock: longint; desBlock:
  longint; BlockBuf: PChar): longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_Copy_DataBlock';

{��������ID�� }
function RequestCard(ucSerialNo: pchar; ucType: pchar): longint; stdcall;
far; external 'CardDLL.dll' name 'RequestCard';

{��ʼ������ }
function ConnectMF(port: longint; baud: longint): longint; stdcall;
far; external 'CardDLL.dll' name 'ConnectMF';

{���ùرմ���}
function CloseMF: SmallInt; stdcall;
far; External 'CardDll.dll' name 'CloseMF';

{��д����Ȩ }
function ReaderAuthor(MoneyBuf: pchar): longint; stdcall;
far; external 'CardDLL.dll' name 'ReaderAuthor';

{������Կ����
������buf1~buf3,�ַ���ָ�룬ԭʼ�ַ�����ַ������8λ
key����Կ���ĵĵ�ַ
����ֵ��0���ɹ�������ʧ��
}
function gen_work_key(Key1: PChar; Key2: PChar; Key3: Pchar; OutPlainKey:
  Pchar): longint; stdcall;
far; external 'desdll.dll' name 'gen_work_key';

{������Կ����  ����������
������text,�ַ���ָ�룬�����ַ�����ַ������8λ
mtest�������ַ����ĵ�ַ
����ֵ��0���ɹ�������ʧ��
}
function encrypt_work_key(text: PChar; mtext: PChar): longint; stdcall;
far; external 'desdll.dll' name 'encrypt_work_key';

{������Կ���� ��������
������text,�ַ���ָ�룬�����ַ�����ַ������8λ
mtest�������ַ����ĵ�ַ
����ֵ��0���ɹ�������ʧ��
}
function decrypt_work_key(text: PChar; mtext: PChar): longint; stdcall;
far; external 'desdll.dll' name 'decrypt_work_key';

{����������Կ --��ԿA

������buf,�ַ���ָ�룬�����ַ�����ַ������8λ
key����ԿA����ԿB
����ֵ��0���ɹ�������ʧ�� }
function gen_auth_card_keyA(FUserInString: PChar; FOutKey: PChar): longint;
stdcall;
far; external 'desdll.dll' name 'gen_auth_card_keyA';

{����������Կ --��ԿB

������buf,�ַ���ָ�룬�����ַ�����ַ������8λ
key����ԿA����ԿB
����ֵ��0���ɹ�������ʧ�� }
function gen_auth_card_keyB(buf: Pchar; key: pchar): longint; stdcall;
far; external 'desdll.dll' name 'gen_auth_card_keyB';

{�����ַ�����У���

������buf,�ַ���ָ�룬У���ַ����ĵ�ַ
����ֵ���ַ�����У���
 }
function get_check_char(InCheckSumString: PChar): longint; stdcall;
far; external 'desdll.dll' name 'get_check_char';

{�����ַ�����У���
������buf,�ַ���ָ�룬У���ַ����ĵ�ַ
      check_char,�ַ�����У���
����ֵ��0���Ϸ����������Ϸ�
}
function check_valid(InCheckSumString: Pchar; check_char: PChar): longint;
stdcall;
far; external 'desdll.dll' name 'check_valid';

{DES�㷨��>KEY-A
������key,�ַ���ָ��,������Կ,����8λ
text, �ַ���ָ��,�û�����ID��
keyA, �ַ���ָ��,�û�����keyA
����ֵ��0���ɹ�������ʧ��
}
function gen_user_card_keyA(BaseKey: PChar; AddText: PChar; OutkeyA: PChar):
  longint; stdcall;
far; external 'desdll.dll' name 'gen_user_card_keyA';

{3DES�㷨��>KEY-B
������key,�ַ���ָ��,������Կ,����8λ
text, �ַ���ָ��,�û�����ID��
keyB, �ַ���ָ��,�û�����keyB
����ֵ��0���ɹ�������ʧ��
}
function gen_user_card_keyB(BaseKey: PChar; AddText: PChar; OutkeyB: PChar):
  longint; stdcall;
far; external 'desdll.dll' name 'gen_user_card_keyB';

{��д������}
function ConnectReadWrite(nPortNo: longint; nBaudRate: longint): longint;

{��д���ض�}
function CloseReadWrite: longint;

{��д������������}
function ControlBuzzer: longint;

{����û����Ƿ��ڸ�Ӧ��}
function RequestCardExist(ucSerialNo: pChar; ucType: PChar): longint;

{�û�ʹ���Զ���������е�½}
function Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):
  longint;

{��ȡ����Ϣ}
function ReaderBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint;

{д����Ϣ}
function WriteBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint;

{PHILIPSǮ������}
function Phlips_Packet_Proc(flag: longint; Sector: longint; BlockNo: longint;
  Money: longint; BlockBuf: PChar): longint;

{�û�������}
function SleepCard: longint;

{���ݿ�COPY}
function Copy_DataBlock(Sector: longint; souBlock: longint; desBlock: longint;
  BlockBuf: PChar): longint;

{��ȡ��������ID��}
function ReadCardPhyID(var PhyCardId: string): string;

{������Կ����}
function GetPrivacyKeyPlainText(UserKey1: PChar; UserKey2: PChar; UserKey3:
  Pchar;
  var OutKey: Pchar): Longint;

{������Կ���ģ�����}
function EncryptPrivacyKey(OldText: PChar; var newText: PChar): longint;

{������Կ���ģ�����}
function DecryptPrivacyKey(OldText: PChar; var newText: PChar): longint;

{��������Ȩ}
function ReadMachineAuth: smallint;

{�򿪴���}
function IniSerialPort(CommId: longint; BaudRate: longint): smallint;

{�رմ���}
function CloseSerialPort: smallint;

{DES�㷨��>KEY-A}
function GenUserCardKeyA(BaseKey: PChar; AddText: PChar; var OutkeyA: PChar):
  longint;

{����������Կ������ԿA}
function GenAuthCardKeyA(FInSeedKey: PChar; var FOutResultKey: PChar): longint;

{����������Կ������ԿB}
function GenAuthCardKeyB(FInSeedKey: PChar; var FOutResultKey: PChar): longint;

implementation

function GenAuthCardKeyB(FInSeedKey: PChar; var FOutResultKey: PChar): longint;
begin
  Result := gen_auth_card_keyB(FInSeedKey, FOutResultKey);
end;

function GenAuthCardKeyA(FInSeedKey: PChar; var FOutResultKey: PChar): longint;
begin
  Result := gen_auth_card_keyA(FInSeedKey, FOutResultKey);
end;

function GenUserCardKeyA(BaseKey: PChar; AddText: PChar; var OutkeyA: PChar):
  longint;
begin
  Result := gen_user_card_keyA(BaseKey, AddText, OutKeyA);
end;

function CloseSerialPort: smallint;
begin
  //0:�رմ��ڳɹ��� -1���رմ���ʧ�ܣ�-2�������̬�����ʧ��
  Result := CloseMF;
end;

function IniSerialPort(CommId: longint; BaudRate: longint): smallint;
begin
  //0:�򿪴��ڳɹ���
  //-1��Ӳ����̬�����ʧ�ܣ�
  //-2����д����ʼ��ʧ�ܣ�
  //-3�������̬�����ʧ��
  Result := ConnectMF(CommId, BaudRate);
  //Result:=SMT_ConnectMF280(CommId,BaudRate);
end;

function ReadMachineAuth: smallint;
var
  ucAuthorInfo: pchar;
begin
  ucAuthorInfo := nil;
  ReallocMem(ucAuthorInfo, 19);
  Result := ReaderAuthor(ucAuthorInfo);
  freemem(ucAuthorInfo);
end;

function EncryptPrivacyKey(OldText: PChar; var newText: PChar): longint;
begin
  Result := encrypt_work_key(OldText, newText);
end;

function DecryptPrivacyKey(OldText: PChar; var newText: PChar): longint;
begin
  Result := decrypt_work_key(OldText, newText);
end;

function GetPrivacyKeyPlainText(UserKey1: PChar; UserKey2: PChar; UserKey3:
  Pchar;
  var OutKey: Pchar): Longint;
begin
  Result := gen_work_key(UserKey1, UserKey2, UserKey3, OutKey);
end;

function ReadCardPhyID(var PhyCardId: string): string;
var
  ucSerialNo: pchar;
  ucType: pchar;
  st: smallint;
begin
  ucSerialNo := nil;
  ucType := nil;
  ReallocMem(ucSerialNo, 9);
  ReallocMem(ucType, 3);
  st := RequestCard(ucSerialNo, ucType);
  if st = 0 then
  begin
    PhyCardId := ucSerialNo;
  end
  else
  begin
    Result := '��ȡ������ID����';
  end;
end;

function ConnectReadWrite(nPortNo: longint; nBaudRate: longint): longint;
begin
  Result := SMT_ConnectMF280(nPortNo, nBaudRate);
end;

function CloseReadWrite: longint;
begin
  Result := SMT_CloseMF280;
end;

function ControlBuzzer: longint;
begin
  Result := SMT_ControlBuzzer;
end;

function RequestCardExist(ucSerialNo: pChar; ucType: PChar): longint;
begin
  Result := SMT_RequestCardExist(ucSerialNo, ucType);
end;

function Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):
  longint;
begin
  Result := SMT_Login_With_UserKey(Sector, Key, keyFlag);
end;

function ReaderBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint;
begin
  Result := SMT_ReadBlock(Sector, BlockNo, BlockBuf);
end;

function WriteBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint;
begin
  Result := SMT_WriteBlock(Sector, BlockNo, BlockBuf);
end;

function Phlips_Packet_Proc(flag: longint; Sector: longint; BlockNo: longint;
  Money: longint; BlockBuf: PChar): longint;
begin
  Result := SMT_Phlips_Packet_Proc(flag, Sector, BlockNo, Money, BlockBuf);
end;

function SleepCard: longint;
begin
  Result := SMT_SleepCard;
end;

function Copy_DataBlock(Sector: longint; souBlock: longint; desBlock: longint;
  BlockBuf: PChar): longint;
begin
  Result := SMT_Copy_DataBlock(Sector, souBlock, desBlock, BlockBuf);
end;

end.

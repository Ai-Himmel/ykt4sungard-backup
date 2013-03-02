unit UCardDll;

interface

uses messages, dialogs;

const
  SelectSmartCardType = '0x18';

  {读写器连接

  入口参数：
  nPortNo：串口号
  nBaudRate：通讯波特率 19200
  出口参数：无
  返回值：
  0：连接成功
  -1：连接失败}
function SMT_ConnectMF280(nPortNo: longint; nBaudRate: longint): longint;
stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ConnectMF280';

{读写器关断

入口参数：无
出口参数：无
返回值：
 0：关断成功
-1：关断失败
}
function SMT_CloseMF280: longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_CloseMF280';

{读写器蜂鸣器控制

入口参数：五
出口参数：无
返回值：
 0：成功
   -1：失败
}
function SMT_ControlBuzzer: longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ControlBuzzer';

{检查用户卡是否在感应区

入口参数：无
出口参数：
ucSerialNo：用户卡硬件序列号
ucType：   用户卡类型代码（0x08：S50卡，
0x18：S70卡 PHILIPS
0x53：S70卡 复旦微电子）
返回值：
 0：读取成功
其他：读取失败
}
function SMT_RequestCardExist(ucSerialNo: pChar; ucType: PChar): longint;
stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_RequestCardExist';

{用户使用自定义密码进行登陆

入口参数：
 Sector：扇区号
key：6字节密码
keyFlag：0：keyA    1：keyB
出口参数：
无
返回值
 0：登陆成功
其他：登陆失败
}
function SMT_Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_Login_With_UserKey';

{读取卡信息

入口参数:
 Sector：扇区号
 BlockNo：块号
出口参数:
 BlockBuf：16字节内容 HEX
返回值：
 0：成功
 其他：失败
}
function SMT_ReadBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ReadBlock';

{写卡信息

入口参数：
 Sector：扇区号
 BlockNo：块号
 BlockBuf：16字节内容，HEX
出口参数：
 BlockBuf：所指定的扇区内的对应块的数据内容
返回值：
 0：成功
 其他：失败
}
function SMT_WriteBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_WriteBlock';

{PHILIPS钱包操作

入口参数：
 flag：0--加钱 1--减钱
 Sector：扇区号
 Block：块号
 Money：金额
出口参数：
 BlockBuf：执行成功，返回块内16字节数据内容
返回值：
 0：成功
 其他：失败
}
function SMT_Phlips_Packet_Proc(flag: longint; Sector: longint; BlockNo:
  longint;
  Money: longint; BlockBuf: PChar): longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_Phlips_Packet_Proc';

{用户卡休眠

入口参数：无
出口参数：无
返回值：
 0：成功
 其他：失败
}
function SMT_SleepCard: longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_SleepCard';

{数据块COPY

入口参数：
 Sector：扇区号
 souBlock：源块号
 desBlock：目的块号
出口参数：
 BlockBuf：执行成功，返回目的块内16字节数据内容
返回值：
 0：成功
 其他：失败
}
function SMT_Copy_DataBlock(Sector: longint; souBlock: longint; desBlock:
  longint; BlockBuf: PChar): longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_Copy_DataBlock';

{读卡物理ID号 }
function RequestCard(ucSerialNo: pchar; ucType: pchar): longint; stdcall;
far; external 'CardDLL.dll' name 'RequestCard';

{初始化串口 }
function ConnectMF(port: longint; baud: longint): longint; stdcall;
far; external 'CardDLL.dll' name 'ConnectMF';

{调用关闭串口}
function CloseMF: SmallInt; stdcall;
far; External 'CardDll.dll' name 'CloseMF';

{读写器授权 }
function ReaderAuthor(MoneyBuf: pchar): longint; stdcall;
far; external 'CardDLL.dll' name 'ReaderAuthor';

{生成密钥明文
参数：buf1~buf3,字符串指针，原始字符串地址，长度8位
key，密钥明文的地址
返回值：0，成功；其它失败
}
function gen_work_key(Key1: PChar; Key2: PChar; Key3: Pchar; OutPlainKey:
  Pchar): longint; stdcall;
far; external 'desdll.dll' name 'gen_work_key';

{生成密钥密文  －－－加密
参数：text,字符串指针，明文字符串地址，长度8位
mtest，密文字符串的地址
返回值：0，成功；其它失败
}
function encrypt_work_key(text: PChar; mtext: PChar): longint; stdcall;
far; external 'desdll.dll' name 'encrypt_work_key';

{生成密钥密文 －－解密
参数：text,字符串指针，明文字符串地址，长度8位
mtest，密文字符串的地址
返回值：0，成功；其它失败
}
function decrypt_work_key(text: PChar; mtext: PChar): longint; stdcall;
far; external 'desdll.dll' name 'decrypt_work_key';

{生成两套密钥 --密钥A

参数：buf,字符串指针，输入字符串地址，长度8位
key，密钥A和密钥B
返回值：0，成功；其它失败 }
function gen_auth_card_keyA(FUserInString: PChar; FOutKey: PChar): longint;
stdcall;
far; external 'desdll.dll' name 'gen_auth_card_keyA';

{生成两套密钥 --密钥B

参数：buf,字符串指针，输入字符串地址，长度8位
key，密钥A和密钥B
返回值：0，成功；其它失败 }
function gen_auth_card_keyB(buf: Pchar; key: pchar): longint; stdcall;
far; external 'desdll.dll' name 'gen_auth_card_keyB';

{计算字符串的校验和

参数：buf,字符串指针，校验字符串的地址
返回值：字符串的校验和
 }
function get_check_char(InCheckSumString: PChar): longint; stdcall;
far; external 'desdll.dll' name 'get_check_char';

{计算字符串的校验和
参数：buf,字符串指针，校验字符串的地址
      check_char,字符串的校验和
返回值：0，合法，其他不合法
}
function check_valid(InCheckSumString: Pchar; check_char: PChar): longint;
stdcall;
far; external 'desdll.dll' name 'check_valid';

{DES算法－>KEY-A
参数：key,字符串指针,工作密钥,长度8位
text, 字符串指针,用户卡的ID号
keyA, 字符串指针,用户卡的keyA
返回值：0，成功；其它失败
}
function gen_user_card_keyA(BaseKey: PChar; AddText: PChar; OutkeyA: PChar):
  longint; stdcall;
far; external 'desdll.dll' name 'gen_user_card_keyA';

{3DES算法－>KEY-B
参数：key,字符串指针,工作密钥,长度8位
text, 字符串指针,用户卡的ID号
keyB, 字符串指针,用户卡的keyB
返回值：0，成功；其它失败
}
function gen_user_card_keyB(BaseKey: PChar; AddText: PChar; OutkeyB: PChar):
  longint; stdcall;
far; external 'desdll.dll' name 'gen_user_card_keyB';

{读写器连接}
function ConnectReadWrite(nPortNo: longint; nBaudRate: longint): longint;

{读写器关断}
function CloseReadWrite: longint;

{读写器蜂鸣器控制}
function ControlBuzzer: longint;

{检查用户卡是否在感应区}
function RequestCardExist(ucSerialNo: pChar; ucType: PChar): longint;

{用户使用自定义密码进行登陆}
function Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):
  longint;

{读取卡信息}
function ReaderBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint;

{写卡信息}
function WriteBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint;

{PHILIPS钱包操作}
function Phlips_Packet_Proc(flag: longint; Sector: longint; BlockNo: longint;
  Money: longint; BlockBuf: PChar): longint;

{用户卡休眠}
function SleepCard: longint;

{数据块COPY}
function Copy_DataBlock(Sector: longint; souBlock: longint; desBlock: longint;
  BlockBuf: PChar): longint;

{读取卡的物理ID号}
function ReadCardPhyID(var PhyCardId: string): string;

{生成密钥明文}
function GetPrivacyKeyPlainText(UserKey1: PChar; UserKey2: PChar; UserKey3:
  Pchar;
  var OutKey: Pchar): Longint;

{生成密钥密文－加密}
function EncryptPrivacyKey(OldText: PChar; var newText: PChar): longint;

{生成密钥明文－解密}
function DecryptPrivacyKey(OldText: PChar; var newText: PChar): longint;

{读卡器授权}
function ReadMachineAuth: smallint;

{打开串口}
function IniSerialPort(CommId: longint; BaudRate: longint): smallint;

{关闭串口}
function CloseSerialPort: smallint;

{DES算法－>KEY-A}
function GenUserCardKeyA(BaseKey: PChar; AddText: PChar; var OutkeyA: PChar):
  longint;

{生成两套密钥－－密钥A}
function GenAuthCardKeyA(FInSeedKey: PChar; var FOutResultKey: PChar): longint;

{生成两套密钥－－密钥B}
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
  //0:关闭串口成功； -1：关闭串口失败；-2：软件动态库调用失败
  Result := CloseMF;
end;

function IniSerialPort(CommId: longint; BaudRate: longint): smallint;
begin
  //0:打开串口成功；
  //-1：硬件动态库调用失败；
  //-2：读写器初始化失败；
  //-3：软件动态库调用失败
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
    Result := '读取卡物理ID出错！';
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

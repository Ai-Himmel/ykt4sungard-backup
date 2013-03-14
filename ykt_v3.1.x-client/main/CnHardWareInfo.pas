{******************************************************************************}
{                       CnPack For Delphi/C++Builder                           }
{                     �й����Լ��Ŀ���Դ�������������                         }
{                   (C)Copyright 2001-2007 CnPack ������                       }
{                   ------------------------------------                       }
{                                                                              }
{            ���������ǿ�Դ��������������������� CnPack �ķ���Э������        }
{        �ĺ����·�����һ����                                                }
{                                                                              }
{            ������һ��������Ŀ����ϣ�������ã���û���κε���������û��        }
{        �ʺ��ض�Ŀ�Ķ������ĵ���������ϸ���������� CnPack ����Э�顣        }
{                                                                              }
{            ��Ӧ���Ѿ��Ϳ�����һ���յ�һ�� CnPack ����Э��ĸ��������        }
{        ��û�У��ɷ������ǵ���վ��                                            }
{                                                                              }
{            ��վ��ַ��http://www.cnpack.org                                   }
{            �����ʼ���master@cnpack.org                                       }
{                                                                              }
{******************************************************************************}

unit CnHardWareInfo;
{* |<PRE>
================================================================================
* ������ƣ�CnPack �����
* ��Ԫ���ƣ�Ӳ����Ϣ��Ԫ
* ��Ԫ���ߣ�SkyJacker
* ��    ע��Ӳ����Ϣ��Ԫ��Ŀǰ��ֻʵ�ֻ�ȡ��ˡ���CPUϵͳ��ָ��CPU�����к�
* ����ƽ̨��WindowsXP sp2 + Delphi 6.0 up2
* ���ݲ��ԣ�Win2000/XP + Delphi 6
* �� �� �����õ�Ԫ�е��ַ��������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CnHardWareInfo.pas,v 1.2 2007/01/24 07:14:31 liuxiao Exp $
* �޸ļ�¼��2007.01.23 V1.0
*               ������Ԫ��ʵ�ֹ���
================================================================================
|</PRE>}

interface


uses
  Classes, Windows, SysUtils;
  
type
  TCnCPUIdFormat = (ifContinuous, ifDashed);
  {* CPU���к���ʾ��ʽ
   |<PRE>
     ifContinuous:  -������
     ifDashed:      -ʹ�÷ָ��'-'�ָ�
   |</PRE>
  }

  TCnCpuId = class(TPersistent)
  private
    FCPUCount: Integer;
    FCPUIds: TStrings;
    FCPUIdFormat: TCnCPUIdFormat;
    function GetFirstCPUId: string;
    function GetCPUId(Index: Integer): string;
    procedure SetCPUIdFormat(ACPUIdFormat: TCnCPUIdFormat);
    
  public
    constructor Create;
    {* ���캯�������� FCPUIds ������ ReadCPUId}
    destructor Destroy; override;

    procedure ReadCPUId;
    {* �������CPU�ں˵����кţ�������FCPUIds�б�}

    property CPUIdFormat: TCnCPUIdFormat read FCPUIdFormat write SetCPUIdFormat;
    {* CPU ���к���ʾ��ʽ}
    property CPUCount: Integer read FCPUCount;
    {* ϵͳ�� CPU ������}
    property FirstCPUId: string read GetFirstCPUId;
    {* ��ȡ�� 1 �� CPU �� ID�����ڵ� CPU ϵͳ}
    property CPUId[Index: Integer]: string read GetCPUId;
    {* ���ָ�� CPU �����кš����� Index �� 0 ��ʼ}
  end;

implementation

constructor TCnCpuId.Create;
begin
  FCPUIds := TStringList.Create;
  FCPUIdFormat := ifContinuous;
  ReadCPUId;
end;

destructor TCnCpuId.Destroy;
begin
  FCPUIds.Free;
end;

// ��ȡ���� CPU �����к�
procedure TCnCpuId.ReadCPUId;
var
  I: Integer;
  Mask: Integer;
  CurrProc: THandle;
  SysInfo: TSystemInfo;
  ProcessAffinityOld: Cardinal;
  ProcessAffinity: Cardinal;
  SystemAffinity: Cardinal;

  // ��ȡ CPU ���к�
  function GetCnCPUID: string;
  const
    cnIFContinuous = '%.8x%.8x%.8x%.8x';
    cnIFDashed = '%.8x-%.8x-%.8x-%.8x';
  var
    iEax,iEbx,iEcx,iEdx: Integer;
  begin
    asm
      push ebx
      push ecx
      push edx
      mov  eax, $1
      dw $A20F      //CPUID
      mov iEax, eax
      mov iEbx, ebx
      mov iEcx, ecx
      mov iEdx, edx
      pop edx
      pop ecx
      pop ebx
    end;
    if FCPUIdFormat=ifContinuous then
      Result := Format(cnIFContinuous, [iEax, iEbx, iEcx, iEdx])
    else
      Result := Format(cnIFDashed, [iEax, iEbx, iEcx, iEdx])
  end;
begin
  FCPUCount := 0;
  FCPUIds.Clear;
  
  // ��ȡ CPU ����
  GetSystemInfo(SysInfo);
  FCPUCount := SysInfo.dwNumberOfProcessors;

  // ��ȡ���� CPU �����к�
  Mask := $1;
  CurrProc := GetCurrentProcess;
  if not GetProcessAffinityMask(CurrProc, ProcessAffinityOld, SystemAffinity) then
    Exit;
    
  try
    for I:=0 to FCpuCount-1 do
    begin
      ProcessAffinity := Mask shl I;
      if not SetProcessAffinityMask(CurrProc, ProcessAffinity) then
        Break;

      FCPUIds.Add(GetCnCPUID);
    end;
  finally
    //�ָ�Ĭ��
    SetProcessAffinityMask(CurrProc, ProcessAffinityOld);
  end;
end;

procedure TCnCpuId.SetCPUIdFormat(ACPUIdFormat: TCnCPUIdFormat);
begin
  if FCPUIdFormat <> ACPUIdFormat then
  begin
    FCPUIdFormat := ACPUIdFormat;
    ReadCPUId;
  end;
end;

// ��õ� CPU ϵͳ ID
function TCnCpuId.GetFirstCPUId: string;
begin
  if FCPUIds.Count > 0 then
    Result := FCPUIds.Strings[0];
end;

// �õ��ڼ��� CPU �����к�
function TCnCpuId.GetCPUId(Index: Integer): string;
begin
  Result := '';
  // ��֤ FCPUIds �����ĺϷ���
  if (Index < 0) or (Index > FCPUIds.Count - 1) then
    Exit;

  Result := FCPUIds.Strings[Index];
end;

end.

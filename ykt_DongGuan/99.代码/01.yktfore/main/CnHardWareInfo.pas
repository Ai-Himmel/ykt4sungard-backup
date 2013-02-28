{******************************************************************************}
{                       CnPack For Delphi/C++Builder                           }
{                     中国人自己的开放源码第三方开发包                         }
{                   (C)Copyright 2001-2007 CnPack 开发组                       }
{                   ------------------------------------                       }
{                                                                              }
{            本开发包是开源的自由软件，您可以遵照 CnPack 的发布协议来修        }
{        改和重新发布这一程序。                                                }
{                                                                              }
{            发布这一开发包的目的是希望它有用，但没有任何担保。甚至没有        }
{        适合特定目的而隐含的担保。更详细的情况请参阅 CnPack 发布协议。        }
{                                                                              }
{            您应该已经和开发包一起收到一份 CnPack 发布协议的副本。如果        }
{        还没有，可访问我们的网站：                                            }
{                                                                              }
{            网站地址：http://www.cnpack.org                                   }
{            电子邮件：master@cnpack.org                                       }
{                                                                              }
{******************************************************************************}

unit CnHardWareInfo;
{* |<PRE>
================================================================================
* 软件名称：CnPack 组件包
* 单元名称：硬件信息单元
* 单元作者：SkyJacker
* 备    注：硬件信息单元，目前暂只实现获取多核、多CPU系统中指定CPU的序列号
* 开发平台：WindowsXP sp2 + Delphi 6.0 up2
* 兼容测试：Win2000/XP + Delphi 6
* 本 地 化：该单元中的字符串均符合本地化处理方式
* 单元标识：$Id: CnHardWareInfo.pas,v 1.2 2007/01/24 07:14:31 liuxiao Exp $
* 修改记录：2007.01.23 V1.0
*               创建单元，实现功能
================================================================================
|</PRE>}

interface


uses
  Classes, Windows, SysUtils;
  
type
  TCnCPUIdFormat = (ifContinuous, ifDashed);
  {* CPU序列号显示样式
   |<PRE>
     ifContinuous:  -连续型
     ifDashed:      -使用分割符'-'分割
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
    {* 构造函数，创建 FCPUIds 并调用 ReadCPUId}
    destructor Destroy; override;

    procedure ReadCPUId;
    {* 获得所有CPU内核的序列号，并存入FCPUIds列表}

    property CPUIdFormat: TCnCPUIdFormat read FCPUIdFormat write SetCPUIdFormat;
    {* CPU 序列号显示样式}
    property CPUCount: Integer read FCPUCount;
    {* 系统中 CPU 核总数}
    property FirstCPUId: string read GetFirstCPUId;
    {* 获取第 1 个 CPU 的 ID，用于单 CPU 系统}
    property CPUId[Index: Integer]: string read GetCPUId;
    {* 获得指定 CPU 的序列号。索引 Index 从 0 开始}
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

// 获取所有 CPU 的序列号
procedure TCnCpuId.ReadCPUId;
var
  I: Integer;
  Mask: Integer;
  CurrProc: THandle;
  SysInfo: TSystemInfo;
  ProcessAffinityOld: Cardinal;
  ProcessAffinity: Cardinal;
  SystemAffinity: Cardinal;

  // 获取 CPU 序列号
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
  
  // 获取 CPU 个数
  GetSystemInfo(SysInfo);
  FCPUCount := SysInfo.dwNumberOfProcessors;

  // 获取所有 CPU 的序列号
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
    //恢复默认
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

// 获得单 CPU 系统 ID
function TCnCpuId.GetFirstCPUId: string;
begin
  if FCPUIds.Count > 0 then
    Result := FCPUIds.Strings[0];
end;

// 得到第几个 CPU 的序列号
function TCnCpuId.GetCPUId(Index: Integer): string;
begin
  Result := '';
  // 保证 FCPUIds 索引的合法性
  if (Index < 0) or (Index > FCPUIds.Count - 1) then
    Exit;

  Result := FCPUIds.Strings[Index];
end;

end.

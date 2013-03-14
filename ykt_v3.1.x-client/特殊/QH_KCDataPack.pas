unit QH_KCDataPack;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation
   <Unit> ���ڽ��˴�ͨѶƽ̨��CPackͨѶЭ���һЩ���ù��ܺ�����װ��
   <What>
   <Written By> Zhu pengfei (�����)
   <History>
**********************************************}


interface

uses
  Windows, KCDataPack, KCDataAccess, DBAIntf;

function AddOneDataToPackedPkg(
                               DataFieldName : string;
                               PData : PByte;
                               const Data : TSTPack
                               ) : Integer;   //ѹ����İ��Ĵ�С

function AddOneRecToPackedPkg(
                               DataFieldName : array of String;
                               PData : PByte;
                               const Data : TSTPack
                               ) : Integer;   //ѹ����İ��Ĵ�С

procedure BindOneParam(DataSet: TKCDataSet; ParamName: string;
                       ParamDataType: TDBFieldType; ParamValue: Variant);

function AddParamBits(CpackNameList : array of String; PHead : PSTDataHead) : Boolean;

implementation

uses
  SysUtils, BDAImpEx;

function FindParamIndex(CPackName: string): Integer;
var
  I : Integer;
begin
  for I:=0 to PARAMBITS-1 do
  begin
    if SameText(CPackName,KCPackDataNames[I]) then
    begin
      Result := I;
      Exit;
    end;
  end;
  Result := -1;
end;

function AddOneDataToPackedPkg(
                               DataFieldName : string;
                               PData : PByte;
                               const Data : TSTPack
                               ) : Integer;   //ѹ����İ��Ĵ�С
var
  BindIndex, ByteIndex : Integer;
  Head : TSTDataHead;
  Mask : Byte;
begin
//  Result := 0;
  BindIndex := FindParamIndex(DataFieldName);
  Assert(BindIndex <> -1,Format('CPackFied :%s not Exist!',[DataFieldName]));
  Move(PData^,Head,SizeOf(TSTDataHead));

  ByteIndex := BindIndex div BITSPERBYTE;
  Mask := 1;
  Mask := Mask shl (BindIndex mod BITSPERBYTE);
  Head.ParamBits[ByteIndex] := Head.ParamBits[ByteIndex] or Mask;

  Move(Head,PData^,SizeOf(TSTDataHead));

  Result := KCDataPack.KCPackData(Head.ParamBits,Data,PByte(Integer(PData) + SizeOf(TSTDataHead))) + SizeOf(TSTDataHead);
end;

function AddOneRecToPackedPkg(
                               DataFieldName : array of String;
                               PData : PByte;
                               const Data : TSTPack
                               ) : Integer;   //ѹ����İ��Ĵ�С
begin
  Result := -1;
  if not AddParamBits(DataFieldName,PSTDataHead(PData)) then Exit;
  Result := KCDataPack.KCPackData(PSTDataHead(PData)^.ParamBits,Data,PByte(Integer(PData) +
    SizeOf(TSTDataHead))) + SizeOf(TSTDataHead);
end;

procedure BindOneParam(DataSet: TKCDataSet; ParamName: string;
                       ParamDataType: TDBFieldType; ParamValue: Variant);
var
  Param: THRPCParam;
begin
  if DataSet.Params.paramByName(ParamName) = nil then
  begin
    Param := Dataset.Params.Add;
    Param.Name := ParamName;
    Param.DataType := ParamDataType;
  end
  else Param := DataSet.Params.paramByName(ParamName);
  Param.Value := ParamValue;
end;

function AddParamBits(CpackNameList : array of String; PHead : PSTDataHead) : Boolean;
var
  BindIndex, ByteIndex : Integer;
  Head : TSTDataHead;
  Mask : Byte;
  I : Integer;
  tempName : string;
begin
  Result := False;
  if High(CpackNameList) = 0 then Exit;
  FillChar(Head,SizeOf(Head),0);
  Move(PHead^,Head,SizeOf(TSTDataHead));
  for I := Low(CPackNameList) to High(CPackNameList) do
  begin
    tempName := Trim(CPackNameList[I]);
    if tempName = '' then Continue;
    BindIndex := FindParamIndex(tempName);
    Assert(BindIndex <> -1,Format('CPackFied :%s not Exist!',[tempName]));

    ByteIndex := BindIndex div BITSPERBYTE;
    Mask := 1;
    Mask := Mask shl (BindIndex mod BITSPERBYTE);
    Head.ParamBits[ByteIndex] := Head.ParamBits[ByteIndex] or Mask;
  end;

  Move(Head,PHead^,SizeOf(TSTDataHead));
  Result := True;
end;

end.

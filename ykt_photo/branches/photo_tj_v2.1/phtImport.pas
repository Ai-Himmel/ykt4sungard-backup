unit phtImport;
    
{ ***********************************************************************
  Copyright (c) 2005 上海复旦金仕达计算机有限公司
  描    述: 导入外部数据
  作    者: Haifeng Zhu
  创建日期: '2005-05-13'
  修改日期:
  版    本: Ver 1.0
  改    进:
  ************************************************************************ }

interface

uses
  Windows, Messages, SysUtils, Classes, Forms, StdCtrls, ADODB, TSGrid;

type
  TphtSourceType = (stFoxpro, stAccess);

  TphtField = record
    EnName: string;
    ChName: string; 
    FldType: string;            // 字段类型的文本描述

    Matched: Boolean;           // 是否被匹配
    MatchField: string;         // 匹配的导入字段

    HasDefValue: Boolean;       // 设置了默认值
    DefValue: string;           // 目前任何类型都存为文本型，使用时进行转换
    Tag: Integer;               // 标签，目前用作未匹配字段于 tsGrid 中的对应行
  end;
  PphtField = ^TphtField;

  TphtMatch = record
    isImport: Boolean;          // 是否导入
    impFldName: string;         // 导入字段名称
    phtField: PphtField;        // 匹配的字段
  end;

  TphtImport = class(TPersistent)
  private      
    FImportConn: TADOConnection; // 导入数据源的连接
    FImportTable: TADOTable;

    FPhotoConn: TADOConnection;  // 拍照数据库连接的引用
    FPhotoSelect: TADOQuery;
    FPhotoInsert: TADOQuery;

    FDataSource: string;         // 数据源名称
    FSourceType: TphtSourceType; // 数据源类型

    FErrorMsg: string;           // 出错信息
  public       
    MatchGroup: array of TphtMatch;

    constructor Create;
    destructor Destroy; override;

    procedure Connect2Photo(Conn: TADOConnection);
    procedure Connect2Access(FileName: string);
    procedure Connect2FoxPro(FileName: string);

    procedure InitComboBox(cbField: TComboBox; Index: Integer);
    function IndexOfFields(AName: string): Integer;

    procedure BeforeMatch;
    function PreMatch(Index: Integer): Boolean;
    procedure Match(impI, phtI: Integer);
    function DeMatch(impI: Integer): Boolean;
           
    procedure InitTsGrid(tsGrid: TtsGrid);
    procedure GetDefValue(tsGrid: TtsGrid);

    function IsReady: Boolean;

    function Import: Boolean;  // 根据所配置的信息导入数据。
    
    property SourceType: TphtSourceType read FSourceType;
    property DataSource: string read FDataSource;

    property ImportConn: TADOConnection read FImportConn;
    property ImportTable: TADOTable read FImportTable;

    property ErrorMsg: string read FErrorMsg; 
  end;

  function G_phtImport: TphtImport;

implementation

uses
  ksgProgress,uCommon;
  
const
  CIF_Fields_Count = 8;

  ACCESS_CONN = 'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%S;'
    + 'Persist Security Info=False;Jet OLEDB:Database Password=';
  FOXPRO_CONN = 'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%S;'
    +'Extended Properties=dBase 5.0';
 
var
  AphtImport: TphtImport = nil; 
  CIF_Fields: array[0..CIF_Fields_Count - 1] of TphtField;

{ TphtImport }

constructor TphtImport.Create;
begin
  FImportConn := TADOConnection.Create(nil);
  FImportConn.LoginPrompt := False;
  FImportTable := TADOTable.Create(nil);
  FImportTable.Connection := FImportConn;

  FPhotoSelect := TADOQuery.Create(nil);
  FPhotoInsert := TADOQuery.Create(nil);
end;

destructor TphtImport.Destroy;
begin
  inherited;
  FImportConn.Free;
  FImportTable.Free;

  FPhotoSelect.Free;
  FPhotoInsert.Free;
end;

procedure TphtImport.Connect2Photo(Conn: TADOConnection);
// 连接至拍照数据库
begin
  FPhotoConn := Conn;
  FPhotoSelect.Connection := FPhotoConn;
  FPhotoInsert.Connection := FPhotoConn;
end;

procedure TphtImport.Connect2Access(FileName: string);
// Access 要读入库中的表，由用户选择具体的表后再进行字段匹配。
var
  ConnStr: string;
begin
  FImportConn.Connected := False;
  ConnStr := Format(ACCESS_CONN, [FileName]);
  FImportConn.ConnectionString := ConnStr;
  FImportConn.Connected := True;

  FDataSource := FileName;
  FSourceType := stAccess;
end;

procedure TphtImport.Connect2FoxPro(FileName: string);
// Foxpro 可直接连接至表。
var
  ConnStr: string;
  DataSrc: string;
  TableName: string;
begin
  DataSrc := ExtractFilePath(FileName);
  TableName := ExtractFileName(FileName);
  TableName := Copy(TableName, 1, Length(TableName)-4);

  FImportConn.Connected := False;
  ConnStr := Format(FOXPRO_CONN, [DataSrc]);
  FImportConn.ConnectionString := ConnStr;
  FImportConn.Connected := True;

  FDataSource := FileName;
  FSourceType := stFoxpro;

  FImportTable.Close;
  FImportTable.TableName := TableName;
  FImportTable.Open;
end;
  
procedure TphtImport.InitComboBox(cbField: TComboBox; Index: Integer);
var
  I: Integer;
  Text: string;
begin
  // 将尚未被匹配的目标字段名加入类型为 TComboBox 的 cbField中去
  // Index 为选中的导入数据字段位置
  cbField.Text := '';
  cbField.Items.Clear;
  if MatchGroup[Index].phtField <> nil then
  begin
    Text := MatchGroup[Index].phtField.ChName;
    cbField.Items.Add(Text);
    cbField.Text := Text;
  end;

  for I := 0 to CIF_Fields_Count - 1 do
    if not CIF_Fields[I].Matched then
      cbField.Items.Add(CIF_Fields[I].ChName);

end;

function TphtImport.IndexOfFields(AName: string): Integer;
var
  I: Integer;
begin
  // CIF_Fields中寻找名称为 AName 的字段
  for I := 0 to CIF_Fields_Count - 1 do
    if CIF_Fields[I].ChName = AName then
    begin
      Result := I;
      Exit;
    end;
  Result := -1;
end;

procedure TphtImport.BeforeMatch;
var
  I: Integer;
begin
  // CIF_Fields 的初始状态是未匹配
  for I := 0 to CIF_Fields_Count - 1 do
    CIF_Fields[I].Matched := False;

  SetLength(MatchGroup, 0);   // 清楚历史数据
  SetLength(MatchGroup, FImportTable.Fields.Count);
end;

function TphtImport.PreMatch(Index: Integer): Boolean;
var
  I: Integer;
begin
  // 寻找匹配的 CIF_Fields 字段
  for I := 0 to CIF_Fields_Count - 1 do
    if CIF_Fields[I].ChName = MatchGroup[Index].impFldName then
    begin
      CIF_Fields[I].Matched := True;
      CIF_Fields[I].MatchField := MatchGroup[Index].impFldName;

      MatchGroup[Index].isImport := True;
      MatchGroup[Index].phtField := @CIF_Fields[I];
      Result := True;
      Exit;
    end;
  Result := False;
end;

procedure TphtImport.Match(impI, phtI: Integer);
begin
  MatchGroup[impI].isImport := True;
  MatchGroup[impI].phtField := @CIF_Fields[phtI];

  CIF_Fields[phtI].Matched := True;
  CIF_Fields[phtI].MatchField := MatchGroup[impI].impFldName;
end;
 
function TphtImport.DeMatch(impI: Integer): Boolean;
begin
  // 若返回值为 True ，表示处于 impI 位置的导入数据字段原先匹配了
  MatchGroup[impI].isImport := False;
  if MatchGroup[impI].phtField <> nil then
  begin
    MatchGroup[impI].phtField.Matched := False;
    MatchGroup[impI].phtField.MatchField := '';
    
    MatchGroup[impI].phtField := nil;  
    Result := True;
  end
  else
    Result := False;
end;
 
procedure TphtImport.InitTsGrid(tsGrid: TtsGrid);
var
  I: Integer;
begin
  tsGrid.Rows := 0;
  for I := 0 to CIF_Fields_Count - 1 do
  begin
    if not CIF_Fields[I].Matched then
    begin
      tsGrid.Rows := tsGrid.Rows + 1; // tsGrid.InsertRow(0);
      tsGrid.Cell[1, tsGrid.Rows] := CIF_Fields[I].ChName;
      tsGrid.Cell[2, tsGrid.Rows] := CIF_Fields[I].FldType;
      if CIF_Fields[I].HasDefValue then
        tsGrid.Cell[3, tsGrid.Rows] := CIF_Fields[I].DefValue;

      CIF_Fields[I].Tag := tsGrid.Rows;
    end
    else
      CIF_Fields[I].HasDefValue := False;
  end;


end;

procedure TphtImport.GetDefValue(tsGrid: TtsGrid);
var
  I: Integer;
  DefValue: string;
begin
  for I := 0 to CIF_Fields_Count - 1 do
    if not CIF_Fields[I].Matched then
    begin
      DefValue := tsGrid.Cell[3, CIF_Fields[I].Tag];
      if DefValue <> '' then   // '' 表示没有设置默认值
      begin
        CIF_Fields[I].HasDefValue := True;
        CIF_Fields[I].DefValue := DefValue;
      end
      else
      begin  
        CIF_Fields[I].HasDefValue := False;
        CIF_Fields[I].DefValue := '';
      end;
    end;
end;

function TphtImport.IsReady: Boolean;
// 是否准备就绪
begin
  if not CIF_Fields[0].Matched and not CIF_Fields[0].HasDefValue then
  begin
    FErrorMsg := '字段''' + CIF_Fields[0].ChName + '''不能为空! ' + #13#10 +
        '请关联至对应的导入字段或设置默认值!';
    Result := False;
    Exit;
  end;

  if not CIF_Fields[1].Matched then
  begin
    FErrorMsg := '字段''' + CIF_Fields[1].ChName + '''不能为空! ' +#13#10 +
        '请关联至对应的导入字段!';
    Result := False;
    Exit;
  end;

  Result := True;
end;

function TphtImport.Import: Boolean;
// 返回值为真表示导入数据成功，否则表示失败。
const
  ErrorTbl = '导入失败记录';
  UnSelTbl = '未导入记录';
  ErrSQL = 'select * into [%S] from %S where %S = ''#$#^#'' '; // 创建空表
var
  InsSQL,
  FullSQL: string;
  I: Integer;

  ErrorCount,
  UnSelCount: Integer;
  qryInsertError: TADOQuery;
  tblError, tblUnSel: TADOTable;

  function SpellInsSQL: string;
  var
    SQL: string;
    I: Integer;
  begin
    SQL := 'insert into '+tblCust+' (';
    for I := 0 to CIF_Fields_Count - 1 do
      if CIF_Fields[I].Matched or CIF_Fields[I].HasDefValue then
        SQL := SQL + CIF_Fields[I].EnName + ', ';

    SQL := Copy(SQL, 1, Length(SQL)-2);
    SQL := SQL + ') values (' ;
    Result := SQL;
  end;
  function Exist(Stuemp_no: string): Boolean;
  begin  
    FPhotoSelect.Sql.Text := 'select '+stuempNo+' from '+tblCust+' where '+stuempNo+' = ' + QuotedStr(Stuemp_no);
    FPhotoSelect.Open;

    if FPhotoSelect.IsEmpty then
      Result := False
    else
      Result := True;

    FPhotoSelect.Recordset.Close;    // 没办法，这句不加就是不行
    FPhotoSelect.Close;
  end;
  procedure BeforeImport;
  begin
    qryInsertError := TADOQuery.Create(nil);
    qryInsertError.Connection := FImportTable.Connection;

    try
      qryInsertError.SQL.Text := 'drop table ' + ErrorTbl;
      qryInsertError.ExecSQL;
    except
    end;

    try
      qryInsertError.SQL.Text := 'drop table ' + UnSelTbl;
      qryInsertError.ExecSQL;
    except  
    end;

    qryInsertError.SQL.Text := Format(ErrSQL,
        [ErrorTbl, FImportTable.TableName, FImportTable.Fields[0].FieldName]);
    qryInsertError.ExecSQL;

    qryInsertError.SQL.Text := Format(ErrSQL,
        [UnSelTbl, FImportTable.TableName, FImportTable.Fields[0].FieldName]);
    qryInsertError.ExecSQL;

    tblError := TADOTable.Create(nil);
    tblUnSel := TADOTable.Create(nil);
    tblError.Connection := FImportTable.Connection;
    tblUnSel.Connection := FImportTable.Connection;
    tblError.TableName := ErrorTbl;
    tblUnSel.TableName := UnSelTbl;
    tblError.Open;
    tblUnSel.Open;
    UnSelCount := 0;
    ErrorCount := 0;
  end;
  procedure EndImport;
  begin
    tblError.Recordset.Close;
    tblError.Close;
    tblError.Free;
    tblUnSel.Free;

    qryInsertError.Close;
    if ErrorCount = 0 then
    begin
      qryInsertError.SQL.Text := 'drop table ' + ErrorTbl;
      qryInsertError.ExecSQL;
    end;
    if UnSelCount = 0 then
    begin
      qryInsertError.SQL.Text := 'drop table ' + UnSelTbl;
      qryInsertError.ExecSQL;
    end;

    qryInsertError.Free;
    //tblError.Close;
    //tblUnSel.Close;
  end;
begin
  InsSQL := SpellInsSQL;

  FPhotoInsert.Prepared := True;
  FImportTable.First;
     
  Result := True;  
  BeforeImport;
  frmProgress.BeginHandle('导入客户基本信息! ', 0, FImportTable.RecordCount);
  while not FImportTable.Eof do
  begin
    if Exist(FImportTable.FieldByName(CIF_Fields[1].MatchField).AsString) then
    begin  // 将未导入记录插入表中
      Result := False;
      tblUnSel.Append;
      for I := 0 to FImportTable.FieldCount - 1 do
        tblUnSel.Fields[I] := FImportTable.Fields[I];
      tblUnSel.Post;
      UnSelCount := UnSelCount + 1;
    end
    else
    begin   // 数据库中不存在对应于该学工号的记录, 则插入数据。
      FullSQL := InsSQL;
      for I := 0 to CIF_Fields_Count - 1 do
      begin
        if CIF_Fields[I].Matched then
        begin // 对应的导入字段
          FullSQL := FullSQL + '''' +
              FImportTable.FieldByName(CIF_Fields[I].MatchField).AsString +
              ''', ' ;
        end
        else if CIF_Fields[I].HasDefValue then
        begin // 默认值
          FullSQL := FullSQL + '''' +
              CIF_Fields[I].DefValue +
              ''', ' ;
        end;
      end; // end of for

      FullSQL := Copy(FullSQL, 1, Length(FullSQL)-2) + ')';

      try
        // 插入数据
        FPhotoInsert.SQL.Text := FullSQL;
        FPhotoInsert.ExecSQL;
        FPhotoInsert.Close;
      except  // 将导入失败记录插入表中
        Result := False;
        tblError.Append;
        for I := 0 to FImportTable.FieldCount - 1 do
          tblError.Fields[I] := FImportTable.Fields[I];
        tblError.Post;
        ErrorCount := ErrorCount + 1;
      end;
        
    end; // end of if
    FImportTable.Next;

    frmProgress.Progress;
  end; // end of while

  FImportTable.First;
  frmProgress.EndHandle;
  EndImport;

  if not Result then
  begin
    FErrorMsg := '';
    if UnSelCount > 0 then
      FErrorMsg := '共有' + IntToStr(UnSelCount) + '条记录未导入';
    if ErrorCount > 0 then
    begin
      if FErrorMsg <> '' then
        FErrorMsg := FErrorMsg + ', '
      else
        FErrorMsg := '共有';
      FErrorMsg := FErrorMsg + IntToStr(ErrorCount) + '条记录导入失败';
    end;
    FErrorMsg := FErrorMsg + '!';
  end;
end;

function G_phtImport: TphtImport;
begin
  if AphtImport = nil then
    AphtImport := TphtImport.Create;

  Result := AphtImport;
end;

procedure InitCIF_Fields;
var
  I: Integer;
begin
  CIF_Fields[0].EnName := custType;
  CIF_Fields[0].ChName := '人员类别';
  CIF_Fields[1].EnName := stuempNo;
  CIF_Fields[1].ChName := '学/工号';
  CIF_Fields[2].EnName := custName;
  CIF_Fields[2].ChName := '姓名';
  CIF_Fields[3].EnName := custSex;
  CIF_Fields[3].ChName := '性别';
  CIF_Fields[4].EnName := custDeptNo;
  CIF_Fields[4].ChName := '部门';
  CIF_Fields[5].EnName := custSpecNo;
  CIF_Fields[5].ChName := '专业';
  CIF_Fields[6].EnName := custCardId;
  CIF_Fields[6].ChName := '身份证号码';
  CIF_Fields[7].EnName := classNo;
  CIF_Fields[7].ChName := '年级';

  for I := 0 to CIF_Fields_Count - 1 do
    CIF_Fields[I].FldType := '文本';
end;

initialization
  InitCIF_Fields;
  
finalization
  if AphtImport = nil then
    AphtImport.Free;

end.

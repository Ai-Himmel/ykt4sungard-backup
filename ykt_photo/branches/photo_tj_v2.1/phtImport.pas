unit phtImport;
    
{ ***********************************************************************
  Copyright (c) 2005 �Ϻ��������˴��������޹�˾
  ��    ��: �����ⲿ����
  ��    ��: Haifeng Zhu
  ��������: '2005-05-13'
  �޸�����:
  ��    ��: Ver 1.0
  ��    ��:
  ************************************************************************ }

interface

uses
  Windows, Messages, SysUtils, Classes, Forms, StdCtrls, ADODB, TSGrid;

type
  TphtSourceType = (stFoxpro, stAccess);

  TphtField = record
    EnName: string;
    ChName: string; 
    FldType: string;            // �ֶ����͵��ı�����

    Matched: Boolean;           // �Ƿ�ƥ��
    MatchField: string;         // ƥ��ĵ����ֶ�

    HasDefValue: Boolean;       // ������Ĭ��ֵ
    DefValue: string;           // Ŀǰ�κ����Ͷ���Ϊ�ı��ͣ�ʹ��ʱ����ת��
    Tag: Integer;               // ��ǩ��Ŀǰ����δƥ���ֶ��� tsGrid �еĶ�Ӧ��
  end;
  PphtField = ^TphtField;

  TphtMatch = record
    isImport: Boolean;          // �Ƿ���
    impFldName: string;         // �����ֶ�����
    phtField: PphtField;        // ƥ����ֶ�
  end;

  TphtImport = class(TPersistent)
  private      
    FImportConn: TADOConnection; // ��������Դ������
    FImportTable: TADOTable;

    FPhotoConn: TADOConnection;  // �������ݿ����ӵ�����
    FPhotoSelect: TADOQuery;
    FPhotoInsert: TADOQuery;

    FDataSource: string;         // ����Դ����
    FSourceType: TphtSourceType; // ����Դ����

    FErrorMsg: string;           // ������Ϣ
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

    function Import: Boolean;  // ���������õ���Ϣ�������ݡ�
    
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
// �������������ݿ�
begin
  FPhotoConn := Conn;
  FPhotoSelect.Connection := FPhotoConn;
  FPhotoInsert.Connection := FPhotoConn;
end;

procedure TphtImport.Connect2Access(FileName: string);
// Access Ҫ������еı����û�ѡ�����ı���ٽ����ֶ�ƥ�䡣
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
// Foxpro ��ֱ����������
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
  // ����δ��ƥ���Ŀ���ֶ�����������Ϊ TComboBox �� cbField��ȥ
  // Index Ϊѡ�еĵ��������ֶ�λ��
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
  // CIF_Fields��Ѱ������Ϊ AName ���ֶ�
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
  // CIF_Fields �ĳ�ʼ״̬��δƥ��
  for I := 0 to CIF_Fields_Count - 1 do
    CIF_Fields[I].Matched := False;

  SetLength(MatchGroup, 0);   // �����ʷ����
  SetLength(MatchGroup, FImportTable.Fields.Count);
end;

function TphtImport.PreMatch(Index: Integer): Boolean;
var
  I: Integer;
begin
  // Ѱ��ƥ��� CIF_Fields �ֶ�
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
  // ������ֵΪ True ����ʾ���� impI λ�õĵ��������ֶ�ԭ��ƥ����
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
      if DefValue <> '' then   // '' ��ʾû������Ĭ��ֵ
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
// �Ƿ�׼������
begin
  if not CIF_Fields[0].Matched and not CIF_Fields[0].HasDefValue then
  begin
    FErrorMsg := '�ֶ�''' + CIF_Fields[0].ChName + '''����Ϊ��! ' + #13#10 +
        '���������Ӧ�ĵ����ֶλ�����Ĭ��ֵ!';
    Result := False;
    Exit;
  end;

  if not CIF_Fields[1].Matched then
  begin
    FErrorMsg := '�ֶ�''' + CIF_Fields[1].ChName + '''����Ϊ��! ' +#13#10 +
        '���������Ӧ�ĵ����ֶ�!';
    Result := False;
    Exit;
  end;

  Result := True;
end;

function TphtImport.Import: Boolean;
// ����ֵΪ���ʾ�������ݳɹ��������ʾʧ�ܡ�
const
  ErrorTbl = '����ʧ�ܼ�¼';
  UnSelTbl = 'δ�����¼';
  ErrSQL = 'select * into [%S] from %S where %S = ''#$#^#'' '; // �����ձ�
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

    FPhotoSelect.Recordset.Close;    // û�취����䲻�Ӿ��ǲ���
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
  frmProgress.BeginHandle('����ͻ�������Ϣ! ', 0, FImportTable.RecordCount);
  while not FImportTable.Eof do
  begin
    if Exist(FImportTable.FieldByName(CIF_Fields[1].MatchField).AsString) then
    begin  // ��δ�����¼�������
      Result := False;
      tblUnSel.Append;
      for I := 0 to FImportTable.FieldCount - 1 do
        tblUnSel.Fields[I] := FImportTable.Fields[I];
      tblUnSel.Post;
      UnSelCount := UnSelCount + 1;
    end
    else
    begin   // ���ݿ��в����ڶ�Ӧ�ڸ�ѧ���ŵļ�¼, ��������ݡ�
      FullSQL := InsSQL;
      for I := 0 to CIF_Fields_Count - 1 do
      begin
        if CIF_Fields[I].Matched then
        begin // ��Ӧ�ĵ����ֶ�
          FullSQL := FullSQL + '''' +
              FImportTable.FieldByName(CIF_Fields[I].MatchField).AsString +
              ''', ' ;
        end
        else if CIF_Fields[I].HasDefValue then
        begin // Ĭ��ֵ
          FullSQL := FullSQL + '''' +
              CIF_Fields[I].DefValue +
              ''', ' ;
        end;
      end; // end of for

      FullSQL := Copy(FullSQL, 1, Length(FullSQL)-2) + ')';

      try
        // ��������
        FPhotoInsert.SQL.Text := FullSQL;
        FPhotoInsert.ExecSQL;
        FPhotoInsert.Close;
      except  // ������ʧ�ܼ�¼�������
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
      FErrorMsg := '����' + IntToStr(UnSelCount) + '����¼δ����';
    if ErrorCount > 0 then
    begin
      if FErrorMsg <> '' then
        FErrorMsg := FErrorMsg + ', '
      else
        FErrorMsg := '����';
      FErrorMsg := FErrorMsg + IntToStr(ErrorCount) + '����¼����ʧ��';
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
  CIF_Fields[0].ChName := '��Ա���';
  CIF_Fields[1].EnName := stuempNo;
  CIF_Fields[1].ChName := 'ѧ/����';
  CIF_Fields[2].EnName := custName;
  CIF_Fields[2].ChName := '����';
  CIF_Fields[3].EnName := custSex;
  CIF_Fields[3].ChName := '�Ա�';
  CIF_Fields[4].EnName := custDeptNo;
  CIF_Fields[4].ChName := '����';
  CIF_Fields[5].EnName := custSpecNo;
  CIF_Fields[5].ChName := 'רҵ';
  CIF_Fields[6].EnName := custCardId;
  CIF_Fields[6].ChName := '���֤����';
  CIF_Fields[7].EnName := classNo;
  CIF_Fields[7].ChName := '�꼶';

  for I := 0 to CIF_Fields_Count - 1 do
    CIF_Fields[I].FldType := '�ı�';
end;

initialization
  InitCIF_Fields;
  
finalization
  if AphtImport = nil then
    AphtImport.Free;

end.

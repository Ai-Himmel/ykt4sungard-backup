unit gateComm;

interface
uses
  Windows, Messages, SysUtils, Classes, ExtCtrls,Graphics,WVCtrls,Controls, WorkViews,Dialogs,
  RzTabs,WVCmdReq,KSFrameWorks,RzGrids,RzListVw,RzChkLst,RzRadChk;
type
  TExCell = class(TRzStringGrid)
  public
    procedure   DeleteRow(ARow: Longint);
    procedure   DeleteColumn(ACol: Longint);
    procedure   InsertRow(ARow: LongInt);
    procedure   InsertColumn(ACol: LongInt);
end;
var
  operType:string;
  procedure queryType(operName:string;workview:Tworkview);
  procedure addType(operName:string;workview:Tworkview);
  procedure deleteType(operName:string;workview:Tworkview);
  procedure chargeType(operName:string;workview:Tworkview);
  procedure okClick(AddRequest,DeleteRequest,ChangeRequest:TWVRequest);
  function checkInputDate(input:string):Boolean ;
  function checkInputTime(input:string):Boolean;
  function SpliteDateStr(str: string): string;
  function checkQueryCbb(panel:TPanel): Boolean;
  function checkQueryEdit(panel:TPanel): Boolean;
  function checkListViewSelect(inLv:TRzListView): Boolean;
  function checkListSelcet(incheckList:TRzCheckList): Boolean;

  function listViewSelectAll(inListView:TRzListView;chkBox:TRzCheckBox):Boolean;
  function listViewReSelect(inListView:TRzListView):Boolean;

  function chkListSelectAll(incheckList:TRzCheckList;chkBox:TRzCheckBox):Boolean;
  function chkListReSelect(incheckList:TRzCheckList;chkBox:TRzCheckBox):Boolean;

implementation

{-------------------------------------------------------------------------------
  ������:    addType��Ӳ���
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure addType(operName:string;workview:Tworkview);
begin
  //WorkView.FieldByName('����Ա��').Data.SetString(operName);
  WorkView.FieldByName('��������').Data.SetString('A');
  opertype:='A';
end;
{-------------------------------------------------------------------------------
  ������:    queryType��ѯ����
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure queryType(operName:string;workview:Tworkview);
begin
  //WorkView.FieldByName('����Ա��').Data.SetString(operName);
  WorkView.FieldByName('��������').Data.SetString('R');
  opertype:='R';
end;
{-------------------------------------------------------------------------------
  ������:    deleteTypeɾ������
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure deleteType(operName:string;workview:Tworkview);
begin
  //WorkView.FieldByName('����Ա��').Data.SetString(operName);
  WorkView.FieldByName('��������').Data.SetString('D');
  opertype:='D';
end;
{-------------------------------------------------------------------------------
  ������:    chargeType�޸Ĳ���
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure chargeType(operName:string;workview:Tworkview);
begin
  //WorkView.FieldByName('����Ա��').Data.SetString(operName);
  WorkView.FieldByName('��������').Data.SetString('U');
  opertype:='U';
end;
{-------------------------------------------------------------------------------
  ������:    okClick��ɺ�ȷ������
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      requestType:TWVRequest
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure okClick(AddRequest,DeleteRequest,ChangeRequest:TWVRequest);
begin
  if operType='A' then
    AddRequest.SendCommand;
  if operType='D' then
    DeleteRequest.SendCommand;
  if operType='U' then
    ChangeRequest.SendCommand;
end;

{-------------------------------------------------------------------------------
  ������:    checkInputDate�������������Ƿ���ȷ
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      input:string
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function checkInputDate(input:string):Boolean ;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('���ڲ���Ϊ�գ������룡');
    Result := False;
    Exit;
  end;
  if length(input) = 8 then
  begin
    try
      StrToDateTime(SpliteDateStr(input));
      Result := True;
    except
      
    end;
  end;
  if not Result then
     ShowMessage(Format('�����������[%s]��ʽ����ȷ!'#13
      + '���Ҫ����2006��6��18��,������20060618',[input]));
end;
function SpliteDateStr(str: string): string;
begin
  Result := '';
  if length(str) <> 8 then
    Exit;
  Result := Format('%s-%s-%s',
    [Copy(str,1,4),Copy(str,5,2),Copy(str,7,2)]);
end;
{-------------------------------------------------------------------------------
  ������:    checkInputTime��������ʱ���Ƿ���ȷ
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      input:string
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function checkInputTime(input:string):Boolean;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('ʱ�䲻��Ϊ�գ������룡');
    exit;
  end;
  try
    if (StrToInt(Copy(input,1,2))>23)or(StrToInt(Copy(input,3,2))>59) then
    begin
      ShowMessage('�����ʱ���ʽ����ȷ�����������룡');
      Exit;
    end;
  except
    ShowMessage('�����ʱ���ʽ����ȷ�����������룡');
    Exit;
  end;
  Result := True;
end;
{-------------------------------------------------------------------------------
  ������:    checkQueryEdit���������Ƿ�Ϊ�ջ�Ϊ��
  ����:      ����ΰ
  ����:      2005.12.30
  ����:      panel:TPanel
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function checkQueryEdit(panel:TPanel): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to panel.ControlCount-1 do
  begin
    if (panel.Controls[i] is TWVEdit) then
      if (Trim(TWVEdit(panel.Controls[i]).Text) <> '')and(Trim(TWVEdit(panel.Controls[i]).Text) <> '0') then
        Result := True;
  end;
end;
{-------------------------------------------------------------------------------
  ������:    checkQueryCbb��������б���Ƿ�ѡ������
  ����:      ����ΰ
  ����:      2005.12.30
  ����:      panel:TPanel
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function checkQueryCbb(panel:TPanel): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to panel.ControlCount-1 do
  begin
    if (panel.Controls[i] is TWVComboBox) then
      if (TWVComboBox(panel.Controls[i]).ItemIndex<> -1)and(TWVComboBox(panel.Controls[i]).ItemIndex<>0) then
        Result := True;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    checkListViewSelect�ж�listview���Ƿ���ѡ������ݣ�û�з���false
  ����:      hanjiwei
  ����:      2007.04.06
  ����:      inLv:TRzListView
  ����ֵ:    Booleanʱ����������ֵ�-50
-------------------------------------------------------------------------------}
function checkListViewSelect(inLv:TRzListView): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i :=0  to inLv.Items.Count-1 do
    if inLv.Items[i].Checked = True then
    begin
      Result := True;
      Exit;
    end;
end;
{-------------------------------------------------------------------------------
  ������:    checkListSelcet�ж�checklist���Ƿ���ѡ��ģ�û���򷵻�false
  ����:      hanjiwei
  ����:      2007.04.09
  ����:      incheckList:TRzCheckList
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function checkListSelcet(incheckList:TRzCheckList): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to incheckList.Items.Count-1 do
  begin
    if incheckList.ItemChecked[i] then
    begin
      Result := True;
      Exit;
    end;
  end;
end;

function listViewSelectAll(inListView:TRzListView;chkBox:TRzCheckBox):Boolean;
var
  i: integer;
begin
  Result := False;
  if inListView.Items.Count = 0 then
  begin
    Result := False;
    Exit;
  end;
  if chkBox.Checked = True then
  begin
    for i := 0 to inListView.Items.Count - 1 do
    begin
      inListView.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to inListView.Items.Count - 1 do
    begin
      inListView.Items[i].Checked := False;
    end;
  end;
  Result := True;
end;

function listViewReSelect(inListView:TRzListView):Boolean;
var
  i: integer;
begin
  Result := False;
  if inListView.Items.Count = 0 then
  begin
    Result := False;
    Exit;
  end;
  for i := 0 to inListView.Items.Count - 1 do
  begin
    if inListView.Items[i].Checked then
      inListView.Items[i].Checked := False
    else
      inListView.Items[i].Checked := True;
  end;
  Result := True;
end;

function chkListSelectAll(incheckList:TRzCheckList;chkBox:TRzCheckBox):Boolean;
begin
end;
function chkListReSelect(incheckList:TRzCheckList;chkBox:TRzCheckBox):Boolean;
begin
end;

{ TExCell }

procedure TExCell.InsertColumn(ACol: Integer);
begin   
  ColCount :=ColCount +1;
  MoveColumn(ColCount-1, ACol);
end;
    
procedure TExCell.InsertRow(ARow: Integer);
begin   
  RowCount :=RowCount +1;
  MoveRow(RowCount-1, ARow);
end;
    
procedure TExCell.DeleteColumn(ACol: Longint);
begin   
  MoveColumn(ACol, ColCount -1);
  ColCount := ColCount - 1;
end;
    
procedure TExCell.DeleteRow(ARow: Longint);
begin   
  MoveRow(ARow, RowCount - 1);
  RowCount := RowCount - 1;
end;

end.

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
  过程名:    addType添加操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure addType(operName:string;workview:Tworkview);
begin
  //WorkView.FieldByName('操作员号').Data.SetString(operName);
  WorkView.FieldByName('交易类型').Data.SetString('A');
  opertype:='A';
end;
{-------------------------------------------------------------------------------
  过程名:    queryType查询操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure queryType(operName:string;workview:Tworkview);
begin
  //WorkView.FieldByName('操作员号').Data.SetString(operName);
  WorkView.FieldByName('交易类型').Data.SetString('R');
  opertype:='R';
end;
{-------------------------------------------------------------------------------
  过程名:    deleteType删除操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure deleteType(operName:string;workview:Tworkview);
begin
  //WorkView.FieldByName('操作员号').Data.SetString(operName);
  WorkView.FieldByName('交易类型').Data.SetString('D');
  opertype:='D';
end;
{-------------------------------------------------------------------------------
  过程名:    chargeType修改操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure chargeType(operName:string;workview:Tworkview);
begin
  //WorkView.FieldByName('操作员号').Data.SetString(operName);
  WorkView.FieldByName('交易类型').Data.SetString('U');
  opertype:='U';
end;
{-------------------------------------------------------------------------------
  过程名:    okClick完成后确定操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      requestType:TWVRequest
  返回值:    无
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
  过程名:    checkInputDate检查输入的日期是否正确
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      input:string
  返回值:    Boolean
-------------------------------------------------------------------------------}
function checkInputDate(input:string):Boolean ;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('日期不能为空，请输入！');
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
     ShowMessage(Format('您输入的日期[%s]格式不正确!'#13
      + '如果要输入2006年6月18日,请输入20060618',[input]));
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
  过程名:    checkInputTime检查输入的时间是否正确
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      input:string
  返回值:    Boolean
-------------------------------------------------------------------------------}
function checkInputTime(input:string):Boolean;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('时间不能为空，请输入！');
    exit;
  end;
  try
    if (StrToInt(Copy(input,1,2))>23)or(StrToInt(Copy(input,3,2))>59) then
    begin
      ShowMessage('输入的时间格式不正确，请重新输入！');
      Exit;
    end;
  except
    ShowMessage('输入的时间格式不正确，请重新输入！');
    Exit;
  end;
  Result := True;
end;
{-------------------------------------------------------------------------------
  过程名:    checkQueryEdit检查输入框是否为空或为零
  作者:      韩纪伟
  日期:      2005.12.30
  参数:      panel:TPanel
  返回值:    Boolean
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
  过程名:    checkQueryCbb检查下拉列表框是否选择内容
  作者:      韩纪伟
  日期:      2005.12.30
  参数:      panel:TPanel
  返回值:    Boolean
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
  过程名:    checkListViewSelect判断listview中是否有选择的内容，没有返回false
  作者:      hanjiwei
  日期:      2007.04.06
  参数:      inLv:TRzListView
  返回值:    Boolean时间段组数据字典-50
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
  过程名:    checkListSelcet判断checklist中是否有选择的，没有则返回false
  作者:      hanjiwei
  日期:      2007.04.09
  参数:      incheckList:TRzCheckList
  返回值:    Boolean
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

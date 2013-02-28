unit USimpleQueryTemp;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USimpleQueryTemp
   <What>简单查询界面模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks, KSFrames, KSClientConsts,
  Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls, WVCmdReq,Commctrl,
  WorkViews, WVCommands, Db, WVDBBinders, RzDBGrid, Dialogs, Buttons;

type
  TfaSimpleQueryTemp = class(TKSFrame)
    UIPanel1: TUIPanel;
    btnQuery: TBitBtn;
    WorkView: TWorkView;
    MainRequest: TWVRequest;
    btnPrint: TBitBtn;
    WVDBBinder: TWVDBBinder;
    DataSource: TDataSource;
    UIPnlQueryCount: TUIPanel;
    UIPanel2: TUIPanel;
    Grid: TRzDBGrid;
    Image1: TImage;
    LabRecordCount: TLabel;
    procedure  btnQueryClick(Sender: TObject);
    procedure  MainRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure  btnPrintClick(Sender: TObject);
    procedure DataSourceDataChange(Sender: TObject; Field: TField);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure GridKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure btn1Click(Sender: TObject);
  private
    {wsn20041230 处理鼠标滚动的消息}
    Procedure OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
    //20050316 wsn 在框架中加入取得当前数据集查询的数量的过程
    function  GetCurrentRecordCount:Integer;

  protected
    procedure   DoIt; virtual; // 继承该方法，设置数据
    procedure   SendCommand; virtual; // 继承该方法，处理错误(设置FHaveGotData=False，禁止切换page)
    function    CanDoAction(const ActionID : TCommonActionID) : Boolean; override;
    procedure   InitEx; override;
    procedure   Init; override; //重写workview 中类型为integer,float的值，hanjiwei add it 
  public
    constructor Create(AOwner : TComponent); override;
  end;

var
  faSimpleQueryTemp: TfaSimpleQueryTemp;

implementation

{$R *.DFM}

uses KSFrameWorkUtils, SmartCardCommon,TypInfo, DBAIntf,DataTypes;

{TfaSimpleQueryTemp}

constructor TfaSimpleQueryTemp.Create(AOwner: TComponent);
begin
  inherited;
  InitializeFlatSB(Grid.Handle);

  DataGrid := Grid;
  //Application.OnMessage:=OnMouseWheel;
end;

function  TfaSimpleQueryTemp.GetCurrentRecordCount:Integer;
begin
  if (FDataSource<>nil) and
    (FDataSource.Dataset<>nil) and
    (not FDataSource.Dataset.IsEmpty) and
    (FDataSource.DataSet.Active)
  then
  begin
    //ShowMessage(IntToStr(FDataSource.Dataset.RecordCount));
    Result:=FDataSource.Dataset.RecordCount;
  end
  else Result:=0;
end;

Procedure TfaSimpleQueryTemp.OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
begin 
  if Msg.message = WM_MouseWheel then
  begin
    if Msg.wParam > 0 then
    begin
      if Grid.Focused then
         SendMessage(Grid.Handle,WM_VSCROLL,SB_PAGEUP,0);
    end
    else
    begin
      if Grid.Focused then
         SendMessage(Grid.Handle,WM_VSCROLL,SB_PAGEDOWN,0);
    end;
    Handled:= True;
  end;
end;


procedure TfaSimpleQueryTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoIt;
end;

procedure TfaSimpleQueryTemp.DoIt;
begin
  WorkView.SynchronizeCtrlsToFields;
  SendCommand;    
end;

procedure TfaSimpleQueryTemp.SendCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    MainRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSimpleQueryTemp.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
  CheckCommandReturnValue(Command, False);
end;

procedure TfaSimpleQueryTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoIt;
end;

procedure TfaSimpleQueryTemp.btnPrintClick(Sender: TObject);
begin
  DoPrint;
end;

function TfaSimpleQueryTemp.CanDoAction(
  const ActionID: TCommonActionID): Boolean;
begin
  Result := inherited CanDoAction(ActionID);
  if ActionID=caPrint then
    btnPrint.Enabled := Result;
end;

procedure TfaSimpleQueryTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
end;


{-------------------------------------------------------------------------------
  过程名:    TfaSimpleQueryTemp.GridDrawColumnCell表格隔行显示
  作者:      韩纪伟
  日期:      2006.06.30
  参数:      Sender: TObject; const Rect: TRect; DataCol: Integer; Column: TColumn; State: TGridDrawState
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfaSimpleQueryTemp.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  inherited;
  with Grid do
  begin
    if ((State = [gdSelected]) or (State=[gdSelected,gdFocused])) then
    begin
      Canvas.Font.Color :=ClYellow;
      Canvas.Brush.Color :=ClNavy;
    end
    else
    begin
      if DataSource.DataSet.RecNo mod 2<>0 then {判断当前数据是奇数还是偶数行}
      Canvas.brush.Color :=clInfoBk {如果是奇数行，DBGrid背景以白色显示}
    else
      Canvas.brush.Color :=$00EBDED0; {如果是偶数行$00EBDED0，DBGrid背景以浅灰色显示}
    end;
    DefaultDrawColumnCell(Rect, DataCol, Column, State); {这行很关键的，一定不要遗漏了}
  end;
  DBGridRecordSize(Column);
end;

procedure TfaSimpleQueryTemp.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_F8) then
  begin
     DBGridAutoSize(Grid);
  end;

end;

procedure TfaSimpleQueryTemp.btn1Click(Sender: TObject);
{var
  i:Integer;
  titcaption:string;
  fieldname:string;
  id:string;
  width:string;
  visible:string;
  align:string;
  font:string;
  fontsize:string;
  fontcolor :string;
  titfont:string;
  titfontsize:string;
  titfontcolor :string;
  titalign:string;
  ss:string;
  mmo:TMemo;}
begin
  {mmo:=nil;
  try
  mmo:=TMemo.Create(nil);
  mmo.Parent:=UIPanel1;
  mmo.Lines.Clear;
  mmo.Lines.Add('功能号999'+',中文字段名'+',字段名'+',显示顺序号'+',表格宽度'+',是否显示'+',表格对齐方式'+',表格字体'+',表格字体大小'+',表头字体'+',表头字体大小'+',表头对齐方式'+',表格字体颜色'+',表头字体颜色');
  for i := 0 to Grid.Columns.Count-1 do
  begin
    ss:='';
    //中文字段名
    titcaption:= Grid.Columns[i].Title.Caption;
    //字段名
    fieldname:=Grid.Columns[i].FieldName;
    //顺序号
    id := IntToStr(i);
    //字段宽度
    width:= inttostr(Grid.Columns[i].width);
    //是否显示
    if Grid.Columns[i].Visible then
      visible:='1'
    else
      Visible:='0';
    //表格对齐方式
    if Grid.Columns[i].Alignment=Talignment(0) then
      align:='0'
    else if Grid.Columns[i].Alignment=Talignment(1) then
      align:='1'
    else if Grid.Columns[i].Alignment=Talignment(2) then
      align:='2';

    //表格字体
    font:=Grid.Columns[i].Font.Name;
    //表格字体颜色
    fontcolor:=ColorToString(Grid.Columns[i].Font.Color);
    //表格字体大小
    fontsize:=inttostr(Grid.Columns[i].Font.size);
    //表头字体
    titfont:= Grid.Columns[i].Title.Font.Name;
    //表头字体颜色
    titfontcolor:=ColorToString(Grid.Columns[i].Title.Font.Color);
    //表头字体大小
    titfontsize:=inttostr(Grid.Columns[i].Title.Font.size);
    //表头内容对齐方式
    if Grid.Columns[i].Title.Alignment=Talignment(0) then
      titalign:='0'
    else if Grid.Columns[i].Title.Alignment=Talignment(1) then
      titalign:='1'
    else if Grid.Columns[i].Title.Alignment=Talignment(2) then
      titalign:='2';
    mmo.Lines.Add('功能号999'+','+titcaption+','+fieldname+','+id+','+width+','+visible+','+align+','+font+','+fontsize+','+titfont+','+titfontsize+','+titalign+','+fontcolor+','+titfontcolor);
  end;
  mmo.Lines.SaveToFile('c:/query.txt');
  finally
    mmo.Destroy;
  end;}
end;

procedure TfaSimpleQueryTemp.Init;
var
  iwv:Integer;
  icomp:Integer;
  wv:TWorkView;
begin
  inherited;
  //自动初始化Integer的值,hanjiwei add it 20080421
  for icomp := 0 to Self.ComponentCount-1 do
  begin
    if Self.Components[icomp] is TWorkView then
    begin
      wv := TWorkView(Self.Components[icomp]);
      for iwv := 0 to wv.FieldCount-1 do
      begin
        if (wv.Fields[iwv].DataType = kdtInteger) or (wv.Fields[iwv].DataType = kdtFloat) then
          wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := 0
        else if wv.Fields[iwv].DataType = kdtstring then
          wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := '';
      end;
      wv.Reset;
    end;
  end;
end;

end.

unit UChkTreeRptTemp;

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
  WorkViews, WVCommands, Db, WVDBBinders, RzDBGrid, Dialogs, Buttons,
  ComCtrls, ImgList, ToolWin, RM_Dataset, RM_Common, RM_Class, RM_Preview,
  RM_Designer, RzPanel, RzButton, RM_e_main, RM_e_Xls, RM_e_Jpeg,
  RM_e_Graphic, RM_e_bmp, RM_e_htm, RzTreeVw, RzSplit,KsBranchTree,contnrs;

type  TfaChkTreeRptTemp = class(TKSFrame)
    upnlBottom: TUIPanel;
    WorkView: TWorkView;
    MainRequest: TWVRequest;
    WVDBBinder: TWVDBBinder;
    DataSource: TDataSource;
    UIPnlQueryCount: TUIPanel;
    UIPanel2: TUIPanel;
    Image1: TImage;
    LabRecordCount: TLabel;
    Grid: TRzDBGrid;
    ImageList1: TImageList;
    rptReport: TRMReport;
    rmDS: TRMDBDataSet;
    rmdsgnrD: TRMDesigner;
    rmprvwP: TRMPreview;
    tlb1: TRzToolbar;
    btn100: TRzToolButton;
    btnPageWidth: TRzToolButton;
    btnFirst: TRzToolButton;
    btnprevious: TRzToolButton;
    btnNext: TRzToolButton;
    btnLast: TRzToolButton;
    btnExpXls: TRzToolButton;
    btnPagePrint: TRzToolButton;
    btnSetup: TRzToolButton;
    btnDesign: TRzToolButton;
    rzspcr1: TRzSpacer;
    rzspcr2: TRzSpacer;
    rzspcr3: TRzSpacer;
    btnQuery: TBitBtn;
    rmhtmxprt1: TRMHTMExport;
    rmbmpxprt1: TRMBMPExport;
    rmjpgxprt1: TRMJPEGExport;
    SaveDialog: TSaveDialog;
    RzSizePanel1: TRzSizePanel;
    tvTree: TRzCheckTree;
    procedure  btnQueryClick(Sender: TObject);
    procedure  MainRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure DataSourceDataChange(Sender: TObject; Field: TField);
    procedure GridKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure btn100Click(Sender: TObject);
    procedure btnPageWidthClick(Sender: TObject);
    procedure btnFirstClick(Sender: TObject);
    procedure btnpreviousClick(Sender: TObject);
    procedure btnNextClick(Sender: TObject);
    procedure btnLastClick(Sender: TObject);
    procedure btnExpXlsClick(Sender: TObject);
    procedure btnPagePrintClick(Sender: TObject);
    procedure btnSetupClick(Sender: TObject);
    procedure btnDesignClick(Sender: TObject);
  private
    {wsn20041230 处理鼠标滚动的消息}
    //Procedure OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
    //20050316 wsn 在框架中加入取得当前数据集查询的数量的过程
    function  GetCurrentRecordCount:Integer;

  protected
    procedure   DoIt; virtual; // 继承该方法，设置数据
    procedure   SendCommand; virtual; // 继承该方法，处理错误(设置FHaveGotData=False，禁止切换page)
    function    CanDoAction(const ActionID : TCommonActionID) : Boolean; override;
    procedure   InitEx; override;
    procedure   Init; override; //重写workview 中类型为integer,float的值，hanjiwei add it 
  public
    FDataSet:TDataSet;
    FDataSetFieldName:String;     //树节点名称字段名
    FDataSetFieldID:String;       //树节点ID的字段名
    FDataSetParentFieldID:String; //父节点id字段名

    constructor Create(AOwner : TComponent); override;
    destructor Destroy;

    //从数据集中读取树结构的信息
    procedure   ReadTreeInfoFromDataSet(DataSet: TDataSet;CInfoAdmin:TInfoAdmin);

  end;

var
  faChkTreeRptTemp: TfaChkTreeRptTemp;

implementation

{$R *.DFM}

uses KSFrameWorkUtils, SmartCardCommon,TypInfo, DBAIntf,DataTypes,RM_Const, RM_Utils;

{TfaSimpleQueryTemp}

constructor TfaChkTreeRptTemp.Create(AOwner: TComponent);
begin
  inherited;
  InitializeFlatSB(Grid.Handle);

  DataGrid := Grid;
  if FInfoAdmin<>nil then
  begin
    FInfoAdmin.Free ;
  end;
  FInfoAdmin := TInfoAdmin.Create;

  //TreeView.ControlStyle := TreeView.ControlStyle - [csDoubleClicks];
  FDataSet:=TDataSet.Create(nil);
end;


function  TfaChkTreeRptTemp.GetCurrentRecordCount:Integer;
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

{
Procedure TfaReportMachineTemp.OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
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
}

procedure TfaChkTreeRptTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoIt;
end;

procedure TfaChkTreeRptTemp.DoIt;
begin
  WorkView.SynchronizeCtrlsToFields;
  SendCommand;    
end;

procedure TfaChkTreeRptTemp.SendCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    MainRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaChkTreeRptTemp.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
  CheckCommandReturnValue(Command, False);
end;

procedure TfaChkTreeRptTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoIt;
end;

function TfaChkTreeRptTemp.CanDoAction(
  const ActionID: TCommonActionID): Boolean;
begin
  Result := inherited CanDoAction(ActionID);
  if ActionID=caPrint then
    //btnPrint.Enabled := Result;
    //pnlReportTool.Visible := Result;
end;

procedure TfaChkTreeRptTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
end;

procedure TfaChkTreeRptTemp.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_F8) then
  begin
     DBGridAutoSize(Grid);
  end;

end;

procedure TfaChkTreeRptTemp.Init;
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

procedure TfaChkTreeRptTemp.btn100Click(Sender: TObject);
begin
  rmprvwP.Zoom := 100;
end;

procedure TfaChkTreeRptTemp.btnPageWidthClick(Sender: TObject);
begin
  rmprvwP.PageWidth;
end;

procedure TfaChkTreeRptTemp.btnFirstClick(Sender: TObject);
begin
  rmprvwP.First;
end;

procedure TfaChkTreeRptTemp.btnpreviousClick(Sender: TObject);
begin
  rmprvwP.Prev;
end;

procedure TfaChkTreeRptTemp.btnNextClick(Sender: TObject);
begin
  rmprvwP.Next;
end;

procedure TfaChkTreeRptTemp.btnLastClick(Sender: TObject);
begin
  rmprvwP.Last;
end;

type
  THackExport = class(TRMExportFilter)
  end;

procedure TfaChkTreeRptTemp.btnExpXlsClick(Sender: TObject);
var
  i: Integer;
  s: string;
begin
  if rmprvwP.Report = nil then
    Exit;

  s := RMLoadStr(SRepFile) + ' (*.rmp)|*.rmp';
  for i := 0 to RMFiltersCount - 1 do
    s := s + '|' + RMFilters(i).FilterDesc + '|' +
        RMFilters(i).FilterExt;

  SaveDialog.Filter := s;
  SaveDialog.FilterIndex := 1;
  if SaveDialog.Execute then
  begin
    rmprvwP.SaveToFile(SaveDialog.FileName, SaveDialog.FilterIndex);
  end;
end;

procedure TfaChkTreeRptTemp.btnPagePrintClick(Sender: TObject);
begin
  rmprvwP.Print;
end;

procedure TfaChkTreeRptTemp.btnSetupClick(Sender: TObject);
begin
  rmprvwP.DlgPageSetup;
end;

procedure TfaChkTreeRptTemp.btnDesignClick(Sender: TObject);
begin
  if Application.MessageBox('对报表设计将影响显示效果，继续进行该操作吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  rptReport.DesignReport;
end;


destructor TfaChkTreeRptTemp.Destroy;
begin
  FInfoAdmin.Free ;
  FDataSet.Free;
  inherited;
end;

procedure TfaChkTreeRptTemp.ReadTreeInfoFromDataSet(DataSet: TDataSet;CInfoAdmin: TInfoAdmin);
var
  LastNode,Node: TKSMetaNode;
  Structure:TKSTreeStructure;
begin
  LastNode:=nil;
  try
    CInfoAdmin.InfoList.Clear;
    CInfoAdmin.StructureList.Clear;
    Assert(DataSet<>nil);
    DataSet.first;
    while not DataSet.Eof do
    begin
      LastNode := TKSMetaNode.Create;              //树节点的名称和代码集合
      LastNode.ID := DataSet.FieldByName(FDataSetFieldID).AsString;
      LastNode.Caption := DataSet.FieldByName(FDataSetFieldName).AsString; //
      LastNode.Description :='';
      LastNode.NodeType := '';
      CInfoAdmin.InfoList.Add(LastNode);
      LastNode := nil;
      DataSet.Next;
    end;
    DataSet.first;
    while not DataSet.Eof do
    begin
      Node := CInfoAdmin.InfoList.Find(DataSet.FieldByName(FDataSetFieldID).AsString);   //
      if Node<>nil then
      begin
        Structure := TKSTreeStructure.Create;
        CInfoAdmin.StructureList.Add(Structure);  //树上级节点代码集合
        if (DataSet.FieldByName(FDataSetParentFieldID).AsString='') then  //
        begin
          Node.NodeType:=RootValue;
          Structure.ParentId := '';
          Structure.ChildId := Node.ID;
        end else
        begin
          Structure.ChildId := Node.ID;
          if Node.NodeType='' then Node.NodeType:=LeafValue;
          //上级节点
          LastNode:= CInfoAdmin.InfoList.Find(DataSet.FieldByName(FDataSetParentFieldID).AsString);
          if LastNode<>nil then
          begin
            Structure.ParentId := DataSet.FieldByName(FDataSetParentFieldID).AsString;
            if LastNode.NodeType<>RootValue then
            begin
              LastNode.NodeType:=GroupValue;
            end;
          end else
          begin
            Node.NodeType:=RootValue;
            Structure.ParentId := DataSet.FieldByName(FDataSetParentFieldID).AsString;
          end;
        end;
      end;
      Node:=nil;
      DataSet.Next;
    end
  finally
  end;
  CInfoAdmin.Init;
end;

end.

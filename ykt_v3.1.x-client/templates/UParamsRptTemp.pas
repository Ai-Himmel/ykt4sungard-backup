unit UParamsRptTemp;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USetParamsTemp
   <What>�������ò�������ģ��
   <Written By> Huang YanLai (������)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks, KSFrames, KSClientConsts,
  ComCtrls, Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,Commctrl,
  WVDBBinders, WVCmdReq, WorkViews, Db, WVCommands, DBCtrls, DBActns,
  ActnList, RzDBGrid, RzTabs, RzDBNav, RzButton, RzRadChk,Dialogs, Buttons,
  ImgList, RM_e_Xls, RM_e_Jpeg, RM_e_Graphic, RM_e_bmp, RM_Common,
  RM_Class, RM_e_main, RM_e_htm, RM_Preview, RM_Designer, RM_Dataset,
  RzPanel;
{
const
  TabMargin = 3;
}
type
  // �������ý����״̬
  TSettingStatus = (
    ssBrowse,         // ���״̬
    ssAdd,            // ����״̬
    ssChange,         // �޸�״̬
    ssDelete,         // ɾ��״̬
    ssViewDetail      // ���ϸ������״̬
    );

  // ����ά����ʽ
  TParamMaintainType = (
    pmtCenter,        // �ܲ�ά������
    pmtDepartment     // Ӫҵ��ά������
    );

  TfaParamsRptTemp = class(TKSFrame)
    DataSource: TDataSource;
    WorkView: TWorkView;
    QueryRequest: TWVRequest;
    QueryBinder: TWVDBBinder;
    AddRequest: TWVRequest;
    DeleteRequest: TWVRequest;
    ChangeRequest: TWVRequest;
    WVDataSource: TWVDataSource;
    alDatasetActions: TActionList;
    DataSetFirst: TDataSetFirst;
    DataSetPrior: TDataSetPrior;
    DataSetNext: TDataSetNext;
    DataSetLast: TDataSetLast;
    pcPages: TRzPageControl;
    tsQuery: TRzTabSheet;
    tsEdit: TRzTabSheet;
    UIPanel2: TUIPanel;
    btnOK: TBitBtn;
    btnCancel: TBitBtn;
    DBNavigator: TRzDBNavigator;
    UIPanel1: TUIPanel;
    btnQuery: TBitBtn;
    btnAdd: TBitBtn;
    btnChange: TBitBtn;
    btnDelete: TBitBtn;
    btnViewDetail: TBitBtn;
    ckAutoSetNewParams: TRzCheckBox;
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    Grid: TRzDBGrid;
    rmprvwP: TRMPreview;
    rmhtmxprt1: TRMHTMExport;
    rmbmpxprt1: TRMBMPExport;
    rmjpgxprt1: TRMJPEGExport;
    rmxlsxprt1: TRMXLSExport;
    ImageList1: TImageList;
    SaveDialog: TSaveDialog;
    dlgOpenRpt: TOpenDialog;
    rmdsgnrD: TRMDesigner;
    rmDS1: TRMDBDataSet;
    rptQRpt: TRMReport;
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
    btnOpenRpt: TRzToolButton;
    procedure   btnAddClick(Sender: TObject);
    procedure   btnChangeClick(Sender: TObject);
    procedure   btnQueryClick(Sender: TObject);
    procedure   btnDeleteClick(Sender: TObject);
    procedure   btnOKClick(Sender: TObject);
    procedure   btnCancelClick(Sender: TObject);
    procedure   CheckReturnData(Request: TWVRequest;
      Command: TWVCommand);
    procedure   pcPagesDrawTab(Control: TCustomTabControl; TabIndex: Integer;
      const Rect: TRect; Active: Boolean);
    procedure   DataSourceDataChange(Sender: TObject; Field: TField);
    procedure   DataSourceStateChange(Sender: TObject);
    procedure   btnViewDetailClick(Sender: TObject);
    procedure   CheckEditFieldValid(WorkField: TWVField);
    procedure   DBNavigatorClick(Sender: TObject; Button: TNavigateBtn);
    procedure   GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure   GridKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure alDatasetActionsExecute(Action: TBasicAction;
      var Handled: Boolean);
    procedure alDatasetActionsUpdate(Action: TBasicAction;
      var Handled: Boolean);
    procedure GridTitleClick(Column: TColumn);
    procedure pcPagesPaintTabBackground(Sender: TObject; ACanvas: TCanvas;
      ATabIndex: Integer; const ARect: TRect; var Handled: Boolean);
    procedure pcPagesChanging(Sender: TObject; NewIndex: Integer;
      var AllowChange: Boolean);
    procedure DataSetPriorExecute(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure GridMouseEnter(Sender: TObject);
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
    procedure btnOpenRptClick(Sender: TObject);
  private
    FStatus:    TSettingStatus;
    FAutoRefresh : Boolean;
    FCanEdit : Boolean;   //�������ӡ��޸ġ�ɾ��
    FCanDelete: Boolean;  // ����ɾ��
    FCanAdd: Boolean;     // ��������
    FCanChange: Boolean;  // �����޸�
    FLocalDepartment : string;  // ����Ӫҵ������
    procedure   SetStatus(const Value: TSettingStatus);

    procedure   CheckDataCanEdit;
    {wsn20041230 ��������������Ϣ}
    Procedure OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
    procedure RedrawBorder(const Clip: HRGN);
  protected
    FEditSucceed : Boolean;
    FDepartmentFieldName : string;
    FDepartmentWVField : TWVField;
    FMaintainType: TParamMaintainType;
    procedure   Init; override;
    procedure   EnableEditCtrls(AEnabled : Boolean); virtual; // ���ƿؼ��Ƿ���Ա༭
    procedure   BeforeAdd; virtual; // �̳и÷��������ӳ�ʼ������
    procedure   BeforeChange; virtual; // �̳и÷��������ӳ�ʼ������
    procedure   BeforeDelete; virtual; // �̳и÷��������ӳ�ʼ������
    procedure   BeforeViewDetail{(IsFirst : Boolean=True)}; virtual; // �̳и÷��������ӳ�ʼ������
    procedure   CancelEdit; virtual; // �̳и÷���������������ݲ���
    procedure   DoAdd; virtual; // �̳и÷���������EditRequest
    procedure   DoChange; virtual; // �̳и÷���������EditRequest
    procedure   DoDelete; virtual; // �̳и÷���������EditRequest
    procedure   SendEditCommand(Request : TWVRequest); virtual; // �̳и÷������������ã����ӡ��޸ġ�ɾ������������FEditSucceed
    function    GetCurrentRecordInfo : string; virtual; // �̳и÷���������һ�����ݵ�����������ɾ�����ݣ�
    procedure   DoQuery; virtual; // �̳и÷��������ò�ѯ����
    procedure   SendQueryCommand; virtual; // �̳и÷����������ѯ����
    procedure   EnableEdit(CanEdit : Boolean);  // �ϳ�
    procedure   UpdateButton; // ���°�����Enabled״̬
    function    InternalGetCanEdit : Boolean; virtual; // �ж��Ƿ�����޸ģ���������ά�����ͺ͵�ǰӪҵ������FCanEdit����
    procedure   InitEx; override;   // ����ĳ�ʼ����֧���Զ���ѯ
    procedure   StatusChanged; virtual; // �������״̬�����ı䣬���� DisplayData
    procedure   DisplayData; virtual;   // �����ݴ����ݼ�������ʾ������ͬ����������ͼ�������ʹ�����������Ŀؼ���Ҫ���ش˷�����
    procedure   SaveModifiedData; virtual;  // ���޸ĵ�����ͬ����������ͼ�����ʹ������Ŀؼ���Ҫ���ش˷�����
    function    ConfirmEdit : Boolean; virtual; // �����Ƿ������޸ġ��ڰ���ȷ�ϵ�ʱ�򱻵��á����������ﵯ���Ի�����ʾȷ�ϻ��߸��ˡ�
    //20050316 wsn �ڿ���м���ȡ�õ�ǰ���ݼ���ѯ�������Ĺ���
    function    GetCurrentRecordCount:Integer;virtual;

  public
    constructor Create(AOwner : TComponent); override;
    
    procedure   SetCanAdd(const Value: Boolean);
    procedure   SetCanChange(const Value: Boolean);
    procedure   SetCanDelete(const Value: Boolean);

    procedure   CloseDataset; override;
    property    Status : TSettingStatus read FStatus write SetStatus;
    property    AutoRefresh : Boolean read FAutoRefresh write FAutoRefresh default True;
    property    CanAdd : Boolean read FCanAdd write SetCanAdd default True;
    property    CanChange : Boolean read FCanChange write SetCanChange default True;
    property    CanDelete : Boolean read FCanDelete write SetCanDelete default True;
    property    MaintainType : TParamMaintainType read FMaintainType;
  end;

var
  faParamsRptTemp: TfaParamsRptTemp;

implementation

uses KSFrameWorkUtils, DataUsageUtils, LogFile, SmartCardCommon,TypInfo, DBAIntf,DataTypes
  ,RM_Const, RM_Utils;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

{ TfaSetParamsTemp }

constructor TfaParamsRptTemp.Create(AOwner: TComponent);
begin
  inherited;
  DataGrid := Grid;
  FStatus := ssBrowse;
  FCanEdit := True;
  FCanDelete := True;
  FCanAdd := True;
  FCanChange := True;
  FAutoRefresh := True;
  InitializeFlatSB(Grid.Handle);
  //Application.OnMessage:=OnMouseWheel;
end;


function  TfaParamsRptTemp.GetCurrentRecordCount:Integer;
begin
  if (FDataSource<>nil) and
    (FDataSource.Dataset<>nil) and
    (not FDataSource.Dataset.IsEmpty) and
    (FDataSource.DataSet.Active)
  then
    Result:=FDataSource.Dataset.RecordCount
  else Result:=0;
end;


Procedure TfaParamsRptTemp.OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
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



procedure TfaParamsRptTemp.btnAddClick(Sender: TObject);
begin
  Status := ssAdd;
end;

procedure TfaParamsRptTemp.Init;
var
  iwv:Integer;
  icomp:Integer;
  wv:TWorkView;
begin
  inherited;
  //��ʼ������Ϊinteger ,float��ֵΪ0;hanjiwei add it 
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

  //FAutoRefresh := False;
  FAutoRefresh := True;
  ckAutoSetNewParams.Checked := True;
  FDepartmentFieldName := 'sbranch_code0';
  FDepartmentWVField := nil;
  FLocalDepartment := Context.ParamData(svDepartNoName).AsString;
  FMaintainType := pmtCenter;
  pcPages.ActivePageIndex := 0;
  //pcPages.OwnerDraw := True;
  tsEdit.Caption := '����';//SSet;
  TWinControlAccess(tsQuery).SelectFirst;
  CheckDataCanEdit;
end;

procedure TfaParamsRptTemp.btnChangeClick(Sender: TObject);
begin
  Status := ssChange;
end;

procedure TfaParamsRptTemp.SetStatus(const Value: TSettingStatus);
begin
  // ���״̬ת��
  if FStatus <> Value then
  begin
    FStatus := Value;
    if FStatus=ssBrowse then
    begin
      // ���״̬
      tsQuery.Enabled := True;
      tsEdit.Enabled := False;
      tsEdit.Caption := '����';//SSet;
      pcPages.ActivePageIndex := 0;
      TWinControlAccess(tsQuery).SelectFirst;
    end else
    begin
      tsQuery.Enabled := False;
      tsEdit.Enabled := True;
      pcPages.ActivePageIndex := 1;
      case Status of
        ssAdd : BeforeAdd;
        ssChange : BeforeChange;
        ssDelete : BeforeDelete;
        ssViewDetail : BeforeViewDetail{(True)};
      end;
      TWinControlAccess(tsEdit).SelectFirst;
      
    end;
    btnOK.Visible := Status in [ssAdd,ssChange,ssDelete];
    DBNavigator.Visible := Status = ssViewDetail;
    WorkView.CheckValid;
    StatusChanged;
    if (Status = ssDelete) and btnOK.Enabled and btnOK.Visible then btnOK.SetFocus;
  end;
end;

procedure TfaParamsRptTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaParamsRptTemp.BeforeAdd;
begin
  tsEdit.Caption := '����';//SAdd;
  // ���е�������Ŀ���Ա༭
  EnableEditCtrls(True);
  // ��ʼ������������Ŀ
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaParamsRptTemp.BeforeChange;
begin
  tsEdit.Caption := '����';//SChange;
  // ���е�������Ŀ���Ա༭
  // ���������ظ÷�������ֹ�������Ա༭
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaParamsRptTemp.BeforeDelete;
begin
  tsEdit.Caption := '����';//SDelete;
  // ���е�������Ŀ�������Ա༭
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaParamsRptTemp.btnDeleteClick(Sender: TObject);
begin
  {
  case Context.GetDialogSystem.Confirm(Format('ɾ��%s��',[GetCurrentRecordInfo])) of
    uaYes : DoDelete;
    uaNo : ;
    uaCancel : ;
  end;
  }
  Status := ssDelete;
end;

function TfaParamsRptTemp.GetCurrentRecordInfo: string;
begin
  Result := '';
end;

procedure TfaParamsRptTemp.CancelEdit;
begin
  Status := ssBrowse;
end;

procedure TfaParamsRptTemp.DoAdd;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaParamsRptTemp.DoChange;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaParamsRptTemp.DoDelete;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(DeleteRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaParamsRptTemp.DoQuery;
begin
  try
    CloseDataSet;
    WorkView.SynchronizeCtrlsToFields;
    SendQueryCommand;
  except
    HandleException;
    CloseDataSet;
  end;
end;

procedure TfaParamsRptTemp.SendQueryCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    QueryRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaParamsRptTemp.btnOKClick(Sender: TObject);
var
  NeedDoRefresh : Boolean;
begin
  WorkView.SynchronizeCtrlsToFields;
  TWinControlAccess(tsEdit).SelectFirst;
  if btnOk.Enabled and ConfirmEdit then
  begin
    NeedDoRefresh := True;
    case Status of
      ssAdd :
        DoAdd;
      ssChange:
        DoChange;
      ssDelete :
        DoDelete;
      ssViewDetail :
        begin
          Assert(False,'never run into there!');
          {
          Status := ssBrowse;
          NeedDoRefresh := False; // not Refresh
          }
        end;
    else  Assert(False);
    end;
    if (Status=ssBrowse) and NeedDoRefresh and AutoRefresh then
      //DoQuery;
  end;
end;

procedure TfaParamsRptTemp.btnCancelClick(Sender: TObject);
begin
  CancelEdit;
end;

procedure TfaParamsRptTemp.SendEditCommand(Request : TWVRequest);
begin
  FEditSucceed := True;
  try
    ShowWaiting(SWaitingOperation);
    Request.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaParamsRptTemp.EnableEdit(CanEdit: Boolean);
begin
  //FCanEdit := CanEdit;
  //UpdateButton;
end;

procedure TfaParamsRptTemp.CheckReturnData(Request: TWVRequest;
  Command: TWVCommand);
begin
  LabRecordCount.Caption:='��ѯ�� '+IntToStr(GetCurrentRecordCount)+' ����¼';
  CheckCommandReturnValue(Command);
end;

procedure TfaParamsRptTemp.pcPagesDrawTab(Control: TCustomTabControl;
  TabIndex: Integer; const Rect: TRect; Active: Boolean);
var
  ARect : TRect;
begin
  if pcPages.Pages[TabIndex].Enabled then
    Control.Canvas.Font.Color := clWindowText else
    Control.Canvas.Font.Color := clGrayText;
  ARect := Rect;
  Windows.DrawText(Control.Canvas.Handle,PChar(pcPages.Pages[TabIndex].Caption),-1,
    ARect,DT_CENTER or DT_VCENTER or DT_SINGLELINE);
end;

procedure TfaParamsRptTemp.EnableEditCtrls(AEnabled: Boolean);
{
var
  I : Integer;
  Ctrl : TControl;
}
begin
  {
  for I:=0 to tsEdit.ControlCount-1 do
  begin
    Ctrl := tsEdit.Controls[I];
    if not (Ctrl is TPageControl) then
      Ctrl.Enabled := AEnabled;
  end;
  UIPanel2.Enabled := True;
  }
  MakeChildrenReadOnly(tsEdit,not AEnabled);
  UIPanel2.Enabled := True;
  MakeChildrenReadOnly(UIPanel2,False);
end;

procedure TfaParamsRptTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  if Field=nil then
  begin
    CheckDataCanEdit;
    if Status=ssViewDetail then
      DisplayData;
    LabRecordCount.Caption:='��ѯ�� '+IntToStr(GetCurrentRecordCount)+' ����¼';
  end;
end;

procedure TfaParamsRptTemp.SetCanAdd(const Value: Boolean);
begin
  FCanAdd := Value;
  UpdateButton;
end;

procedure TfaParamsRptTemp.SetCanChange(const Value: Boolean);
begin
  FCanChange := Value;
  UpdateButton;
end;

procedure TfaParamsRptTemp.SetCanDelete(const Value: Boolean);
begin
  FCanDelete := Value;
  UpdateButton;
end;

procedure TfaParamsRptTemp.UpdateButton;
begin
  FCanEdit := InternalGetCanEdit;
  btnAdd.Enabled := FCanEdit and CanAdd;
  btnDelete.Enabled := FCanEdit and CanDelete;
  btnChange.Enabled := FCanEdit and CanChange;
end;

procedure TfaParamsRptTemp.CloseDataset;
begin
  inherited;
  if QueryBinder.Field<>nil then
    QueryBinder.Field.Data.Clear;
end;

function TfaParamsRptTemp.InternalGetCanEdit: Boolean;
begin
  // ��������ά�����ͺ͵�ǰӪҵ������FCanEdit����
  // ��������������ظ÷������ṩ����Ŀ���
{  case FMaintainType of
    pmtCenter : Result := IsCenterDepartment;
    pmtDepartment : Result := (FDepartmentWVField<>nil) and (FLocalDepartment=FDepartmentWVField.Data.AsString);
  else
    Result := False;
  end;
  }
  Result:=True;
end;

procedure TfaParamsRptTemp.DataSourceStateChange(Sender: TObject);
begin
  CheckDataCanEdit;    
end;

procedure TfaParamsRptTemp.CheckDataCanEdit;
var
  DepartField : TField;
  SameDepart : Boolean;
begin
  if (DataSource.DataSet=nil) or (DataSource.DataSet.IsEmpty) or not DataSource.DataSet.Active then
  begin
    //�޲�ѯ������ݣ���ֹ�޸ġ�ɾ������������
    FCanDelete := False;
    FCanChange := False;
    FCanAdd := True;
    btnViewDetail.Enabled := False;
  end else
  begin
    //�в�ѯ���ݣ�
    if (FDepartmentFieldName<>'') and (FMaintainType=pmtDepartment) then
    begin
      // �����Ӫҵ��ά�����ݣ���ô��Ҫ���ݷ������ݼ��Ӫҵ����ֻ���޸ĺ�ɾ����Ӫҵ��������
      DepartField:= DataSource.DataSet.FindField(FDepartmentFieldName);
      SameDepart := (DepartField<>nil) and (DepartField.AsString=FLocalDepartment);
    end else
      // ������Ҫ���Ӫҵ��������༭
      SameDepart := True;
    FCanAdd := True;
    FCanDelete := SameDepart;
    FCanChange := SameDepart;
    btnViewDetail.Enabled := True;
  end;
  UpdateButton;
end;

procedure TfaParamsRptTemp.BeforeViewDetail{(IsFirst : Boolean=True)};
begin
  tsEdit.Caption := '����';//SViewDetail;
  // ���е�������Ŀ�������Ա༭
  EnableEditCtrls(False);
end;

procedure TfaParamsRptTemp.btnViewDetailClick(Sender: TObject);
begin
  // ���û�����ݼ��������ݼ�Ϊ�վͷ��� add by ����
  if (DataSource.DataSet<>nil) and (not DataSource.DataSet.IsEmpty) then
    Status := ssViewDetail
  else
    Exit;
  //
  if datasource.DataSet.RecNo = datasource.DataSet.RecordCount then
    datasource.DataSet.Last;
end;

procedure TfaParamsRptTemp.CheckEditFieldValid(WorkField: TWVField);
begin
  if not (status in [ssAdd, ssChange]) then
    WorkField.Valid := True;
end;

procedure TfaParamsRptTemp.DBNavigatorClick(Sender: TObject;
  Button: TNavigateBtn);
begin
  if datasource.DataSet.RecNo = datasource.DataSet.RecordCount then
  begin
    datasource.DataSet.Last;
  end;
  if datasource.DataSet.RecNo = 0 then
  begin
    datasource.DataSet.First;
  end;

end;

procedure TfaParamsRptTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaParamsRptTemp.StatusChanged;
begin
  if (Status in [ssChange,ssDelete,ssViewDetail]) then
    DisplayData
  else if (Status=ssAdd) and
    ckAutoSetNewParams.Checked and
    (WVDataSource.DataSource<>nil) and
    (WVDataSource.DataSource.Dataset<>nil) and
    not WVDataSource.DataSource.Dataset.IsEmpty
  then
    DisplayData;
end;

procedure TfaParamsRptTemp.DisplayData;
begin
  // �����ݴ�����Դͬ����������ͼ���ٵ����ֿؼ�����ע�⣺һЩ������Ҫ���ظ÷�������������ؼ�������ͬ����
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaParamsRptTemp.SaveModifiedData;
begin
  // ���޸ĵ�����ͬ����������ͼ�����ʹ������Ŀؼ���Ҫ���ش˷�����
  WorkView.SynchronizeCtrlsToFields;
end;


procedure TfaParamsRptTemp.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
var
  FRect:TRect;
begin
  with Grid do
  begin
    if ((State = [gdSelected]) or (State=[gdSelected,gdFocused])) then
    begin
      Canvas.Font.Color :=ClYellow;
      Canvas.Brush.Color :=ClNavy;
    end
    else
    begin
      if DataSource.DataSet.RecNo mod 2<>0 then {�жϵ�ǰ��������������ż����}
      Canvas.brush.Color :=clInfoBk {����������У�DBGrid�����԰�ɫ��ʾ}
    else
      Canvas.brush.Color :=$00EBDED0; {�����ż����$00EBDED0��DBGrid������ǳ��ɫ��ʾ}
    end;
    DefaultDrawColumnCell(Rect, DataCol, Column, State); {���кܹؼ��ģ�һ����Ҫ��©��}
  end;
  DBGridRecordSize(Column);
  if FDepartmentWVField=nil then Exit;
  if FDepartmentWVField.Data.AsString=CenterDepartNo then
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,'')
  else
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,FDepartmentFieldName);
end;

procedure TfaParamsRptTemp.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_F8) then
  begin
     DBGridAutoSize(Grid);
  end;
  {if (Key=VK_RETURN) and ([ssCtrl]=Shift) then
  begin
    Key := 0;
    if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
      Status := ssViewDetail;
  end;}

end;

procedure TfaParamsRptTemp.alDatasetActionsExecute(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  if Action.HandlesTarget(DataSource) then
    Action.ExecuteTarget(DataSource);
end;

procedure TfaParamsRptTemp.alDatasetActionsUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  Action.UpdateTarget(DataSource);
end;

function TfaParamsRptTemp.ConfirmEdit: Boolean;
begin
  Result := True;
end;



procedure TfaParamsRptTemp.GridTitleClick(Column: TColumn);
begin
  DoDBGrid1TitleClick(Column);
end;

procedure TfaParamsRptTemp.pcPagesPaintTabBackground(Sender: TObject;
  ACanvas: TCanvas; ATabIndex: Integer; const ARect: TRect;
  var Handled: Boolean);
var
  Rect : TRect;
begin
  if pcPages.Pages[ATabIndex].Enabled then
    ACanvas.Font.Color := clWindowText else
    ACanvas.Font.Color := clGrayText;
  Rect := ARect;
  Windows.DrawText(ACanvas.Handle,PChar(pcPages.Pages[ATabIndex].Caption),-1,
    Rect,DT_CENTER or DT_VCENTER or DT_SINGLELINE);
end;

procedure TfaParamsRptTemp.pcPagesChanging(Sender: TObject;
  NewIndex: Integer; var AllowChange: Boolean);
begin
  if ((pcPages.ActivePageIndex=0) and (Status=ssBrowse))
    or ((pcPages.ActivePageIndex=1) and (Status<>ssBrowse)) then
    AllowChange := False;
end;

procedure TfaParamsRptTemp.DataSetPriorExecute(Sender: TObject);
begin
  if DBNavigator.DataSource.DataSet.Eof then
  begin
    DBNavigator.Refresh;
  end;
end;

procedure TfaParamsRptTemp.GridDblClick(Sender: TObject);
begin
  btnViewDetailClick(Sender);
end;

procedure TfaParamsRptTemp.RedrawBorder(const Clip: HRGN);
var
  DC: HDC;
  R: TRect;
  BtnFaceBrush: HBRUSH;
begin
  DC := GetWindowDC(Handle);
  try
    GetWindowRect(Handle, R);
    OffsetRect(R, -R.Left, -R.Top);
    BtnFaceBrush := CreateSolidBrush(ColorToRGB($00FEDEC9));
    FrameRect(DC, R, BtnFaceBrush);
    InitializeFlatSB(Handle);
    //InflateRect(R, -1, -1);
  finally
    ReleaseDC(Handle, DC);
  end;
  DeleteObject(BtnFaceBrush);
end;

procedure TfaParamsRptTemp.GridMouseEnter(Sender: TObject);
begin
  RedrawBorder(3);
end;

procedure TfaParamsRptTemp.btn100Click(Sender: TObject);
begin
  rmprvwP.Zoom := 100;

end;

procedure TfaParamsRptTemp.btnPageWidthClick(Sender: TObject);
begin
  rmprvwP.PageWidth;
end;

procedure TfaParamsRptTemp.btnFirstClick(Sender: TObject);
begin
  rmprvwP.First;
end;

procedure TfaParamsRptTemp.btnpreviousClick(Sender: TObject);
begin
  rmprvwP.Prev;
end;

procedure TfaParamsRptTemp.btnNextClick(Sender: TObject);
begin
  rmprvwP.Next;
end;

procedure TfaParamsRptTemp.btnLastClick(Sender: TObject);
begin
  rmprvwP.Last;
end;

type
  THackExport = class(TRMExportFilter)
  end;
procedure TfaParamsRptTemp.btnExpXlsClick(Sender: TObject);
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

procedure TfaParamsRptTemp.btnPagePrintClick(Sender: TObject);
begin
  rmprvwP.Print;
end;

procedure TfaParamsRptTemp.btnSetupClick(Sender: TObject);
begin
  rmprvwP.DlgPageSetup;
end;

procedure TfaParamsRptTemp.btnDesignClick(Sender: TObject);
begin
  if Application.MessageBox('�Ա�����ƽ�Ӱ����ʾЧ�����������иò�����',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  rptQRpt.DesignReport;

end;

procedure TfaParamsRptTemp.btnOpenRptClick(Sender: TObject);
begin
  try
  if dlgOpenRpt.Execute then
    rmprvwP.LoadFromFile(dlgOpenRpt.FileName);
  except

  end;
end;

end.

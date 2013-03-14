unit USetParamsTemp;

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
  ActnList, RzDBGrid, RzTabs, RzDBNav, RzButton, RzRadChk,Dialogs, Buttons;
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

  TfaSetParamsTemp = class(TKSFrame)
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
    procedure btn1Click(Sender: TObject);
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
  faSetParamsTemp: TfaSetParamsTemp;

implementation

uses KSFrameWorkUtils, DataUsageUtils, LogFile, SmartCardCommon,TypInfo, DBAIntf,DataTypes;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

{ TfaSetParamsTemp }

constructor TfaSetParamsTemp.Create(AOwner: TComponent);
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


function  TfaSetParamsTemp.GetCurrentRecordCount:Integer;
begin
  if (FDataSource<>nil) and
    (FDataSource.Dataset<>nil) and
    (not FDataSource.Dataset.IsEmpty) and
    (FDataSource.DataSet.Active)
  then
    Result:=FDataSource.Dataset.RecordCount
  else Result:=0;
end;


Procedure TfaSetParamsTemp.OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
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



procedure TfaSetParamsTemp.btnAddClick(Sender: TObject);
begin
  Status := ssAdd;
end;

procedure TfaSetParamsTemp.Init;
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
  tsEdit.Caption := SSet;
  TWinControlAccess(tsQuery).SelectFirst;
  CheckDataCanEdit;
end;

procedure TfaSetParamsTemp.btnChangeClick(Sender: TObject);
begin
  Status := ssChange;
end;

procedure TfaSetParamsTemp.SetStatus(const Value: TSettingStatus);
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
      tsEdit.Caption := SSet;
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

procedure TfaSetParamsTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSetParamsTemp.BeforeAdd;
begin
  tsEdit.Caption := SAdd;
  // ���е�������Ŀ���Ա༭
  EnableEditCtrls(True);
  // ��ʼ������������Ŀ
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaSetParamsTemp.BeforeChange;
begin
  tsEdit.Caption := SChange;
  // ���е�������Ŀ���Ա༭
  // ���������ظ÷�������ֹ�������Ա༭
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSetParamsTemp.BeforeDelete;
begin
  tsEdit.Caption := SDelete;
  // ���е�������Ŀ�������Ա༭
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSetParamsTemp.btnDeleteClick(Sender: TObject);
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

function TfaSetParamsTemp.GetCurrentRecordInfo: string;
begin
  Result := '';
end;

procedure TfaSetParamsTemp.CancelEdit;
begin
  Status := ssBrowse;
end;

procedure TfaSetParamsTemp.DoAdd;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSetParamsTemp.DoChange;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSetParamsTemp.DoDelete;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(DeleteRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSetParamsTemp.DoQuery;
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

procedure TfaSetParamsTemp.SendQueryCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    QueryRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSetParamsTemp.btnOKClick(Sender: TObject);
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

procedure TfaSetParamsTemp.btnCancelClick(Sender: TObject);
begin
  CancelEdit;
end;

procedure TfaSetParamsTemp.SendEditCommand(Request : TWVRequest);
begin
  FEditSucceed := True;
  try
    ShowWaiting(SWaitingOperation);
    Request.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSetParamsTemp.EnableEdit(CanEdit: Boolean);
begin
  //FCanEdit := CanEdit;
  //UpdateButton;
end;

procedure TfaSetParamsTemp.CheckReturnData(Request: TWVRequest;
  Command: TWVCommand);
begin
  LabRecordCount.Caption:='��ѯ�� '+IntToStr(GetCurrentRecordCount)+' ����¼';
  CheckCommandReturnValue(Command);
end;

procedure TfaSetParamsTemp.pcPagesDrawTab(Control: TCustomTabControl;
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

procedure TfaSetParamsTemp.EnableEditCtrls(AEnabled: Boolean);
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

procedure TfaSetParamsTemp.DataSourceDataChange(Sender: TObject;
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

procedure TfaSetParamsTemp.SetCanAdd(const Value: Boolean);
begin
  FCanAdd := Value;
  UpdateButton;
end;

procedure TfaSetParamsTemp.SetCanChange(const Value: Boolean);
begin
  FCanChange := Value;
  UpdateButton;
end;

procedure TfaSetParamsTemp.SetCanDelete(const Value: Boolean);
begin
  FCanDelete := Value;
  UpdateButton;
end;

procedure TfaSetParamsTemp.UpdateButton;
begin
  FCanEdit := InternalGetCanEdit;
  btnAdd.Enabled := FCanEdit and CanAdd;
  btnDelete.Enabled := FCanEdit and CanDelete;
  btnChange.Enabled := FCanEdit and CanChange;
end;

procedure TfaSetParamsTemp.CloseDataset;
begin
  inherited;
  if QueryBinder.Field<>nil then
    QueryBinder.Field.Data.Clear;
end;

function TfaSetParamsTemp.InternalGetCanEdit: Boolean;
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

procedure TfaSetParamsTemp.DataSourceStateChange(Sender: TObject);
begin
  CheckDataCanEdit;    
end;

procedure TfaSetParamsTemp.CheckDataCanEdit;
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

procedure TfaSetParamsTemp.BeforeViewDetail{(IsFirst : Boolean=True)};
begin
  tsEdit.Caption := SViewDetail;
  // ���е�������Ŀ�������Ա༭
  EnableEditCtrls(False);
end;

procedure TfaSetParamsTemp.btnViewDetailClick(Sender: TObject);
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

procedure TfaSetParamsTemp.CheckEditFieldValid(WorkField: TWVField);
begin
  if not (status in [ssAdd, ssChange]) then
    WorkField.Valid := True;
end;

procedure TfaSetParamsTemp.DBNavigatorClick(Sender: TObject;
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

procedure TfaSetParamsTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSetParamsTemp.StatusChanged;
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

procedure TfaSetParamsTemp.DisplayData;
begin
  // �����ݴ�����Դͬ����������ͼ���ٵ����ֿؼ�����ע�⣺һЩ������Ҫ���ظ÷�������������ؼ�������ͬ����
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaSetParamsTemp.SaveModifiedData;
begin
  // ���޸ĵ�����ͬ����������ͼ�����ʹ������Ŀؼ���Ҫ���ش˷�����
  WorkView.SynchronizeCtrlsToFields;
end;


procedure TfaSetParamsTemp.GridDrawColumnCell(Sender: TObject;
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

procedure TfaSetParamsTemp.GridKeyDown(Sender: TObject; var Key: Word;
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

procedure TfaSetParamsTemp.alDatasetActionsExecute(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  if Action.HandlesTarget(DataSource) then
    Action.ExecuteTarget(DataSource);
end;

procedure TfaSetParamsTemp.alDatasetActionsUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  Action.UpdateTarget(DataSource);
end;

function TfaSetParamsTemp.ConfirmEdit: Boolean;
begin
  Result := True;
end;



procedure TfaSetParamsTemp.GridTitleClick(Column: TColumn);
begin
  DoDBGrid1TitleClick(Column);
end;

procedure TfaSetParamsTemp.pcPagesPaintTabBackground(Sender: TObject;
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

procedure TfaSetParamsTemp.pcPagesChanging(Sender: TObject;
  NewIndex: Integer; var AllowChange: Boolean);
begin
  if ((pcPages.ActivePageIndex=0) and (Status=ssBrowse))
    or ((pcPages.ActivePageIndex=1) and (Status<>ssBrowse)) then
    AllowChange := False;
end;

procedure TfaSetParamsTemp.DataSetPriorExecute(Sender: TObject);
begin
  if DBNavigator.DataSource.DataSet.Eof then
  begin
    DBNavigator.Refresh;
  end;
end;

procedure TfaSetParamsTemp.GridDblClick(Sender: TObject);
begin
  btnViewDetailClick(Sender);
end;

procedure TfaSetParamsTemp.RedrawBorder(const Clip: HRGN);
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

procedure TfaSetParamsTemp.GridMouseEnter(Sender: TObject);
begin
  RedrawBorder(3);
end;

procedure TfaSetParamsTemp.btn1Click(Sender: TObject);
var
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
  mmo:TMemo;
begin
  mmo:=nil;
  try
  mmo:=TMemo.Create(nil);
  mmo.Parent:=UIPanel1;
  mmo.Lines.Clear;
  mmo.Lines.Add('���ܺ�999'+',�����ֶ���'+',�ֶ���'+',��ʾ˳���'+',�����'+',�Ƿ���ʾ'+',�����뷽ʽ'+',�������'+',��������С'+',��ͷ����'+',��ͷ�����С'+',��ͷ���뷽ʽ'+',���������ɫ'+',��ͷ������ɫ');
  for i := 0 to Grid.Columns.Count-1 do
  begin
    ss:='';
    //�����ֶ���
    titcaption:= Grid.Columns[i].Title.Caption;
    //�ֶ���
    fieldname:=Grid.Columns[i].FieldName;
    //˳���
    id := IntToStr(i);
    //�ֶο��
    width:= inttostr(Grid.Columns[i].width);
    //�Ƿ���ʾ
    if Grid.Columns[i].Visible then
      visible:='1'
    else
      Visible:='0';
    //�����뷽ʽ
    if Grid.Columns[i].Alignment=Talignment(0) then
      align:='0'
    else if Grid.Columns[i].Alignment=Talignment(1) then
      align:='1'
    else if Grid.Columns[i].Alignment=Talignment(2) then
      align:='2';

    //�������
    font:=Grid.Columns[i].Font.Name;
    //���������ɫ
    fontcolor:=ColorToString(Grid.Columns[i].Font.Color);
    //��������С
    fontsize:=inttostr(Grid.Columns[i].Font.size);
    //��ͷ����
    titfont:= Grid.Columns[i].Title.Font.Name;
    //��ͷ������ɫ
    titfontcolor:=ColorToString(Grid.Columns[i].Title.Font.Color);
    //��ͷ�����С
    titfontsize:=inttostr(Grid.Columns[i].Title.Font.size);
    //��ͷ���ݶ��뷽ʽ
    if Grid.Columns[i].Title.Alignment=Talignment(0) then
      titalign:='0'
    else if Grid.Columns[i].Title.Alignment=Talignment(1) then
      titalign:='1'
    else if Grid.Columns[i].Title.Alignment=Talignment(2) then
      titalign:='2';
    mmo.Lines.Add('���ܺ�999'+','+titcaption+','+fieldname+','+id+','+width+','+visible+','+align+','+font+','+fontsize+','+titfont+','+titfontsize+','+titalign+','+fontcolor+','+titfontcolor);
  end;
  mmo.Lines.SaveToFile('c:/setparam.txt');
  finally
    mmo.Destroy;
  end;
end;

end.

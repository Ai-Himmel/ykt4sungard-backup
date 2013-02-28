unit USMSetParamsTemp;

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
  ComCtrls, Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVDBBinders, WVCmdReq, WorkViews, Db, WVCommands, DBCtrls, DBActns,
  ActnList, RzDBGrid, RzTabs, RzDBNav, RzButton, RzRadChk;
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

  TfaSMSetParamsTemp = class(TKSFrame)
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
    Grid: TRzDBGrid;
    tsEdit: TRzTabSheet;
    UIPanel2: TUIPanel;
    btnOK: TImageButton;
    btnCancel: TImageButton;
    DBNavigator: TRzDBNavigator;
    ImageButton1: TImageButton;
    ImageButton2: TImageButton;
    UIPanel1: TUIPanel;
    btnQuery: TImageButton;
    btnAdd: TImageButton;
    btnChange: TImageButton;
    btnDelete: TImageButton;
    btnViewDetail: TImageButton;
    ckAutoSetNewParams: TRzCheckBox;
    procedure   btnAddClick(Sender: TObject);
    procedure   btnChangeClick(Sender: TObject);
    procedure   pcPagesChanging(Sender: TObject; var AllowChange: Boolean);
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
    procedure   GridDblClick(Sender: TObject);
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
  private
    FStatus:    TSettingStatus;
    FAutoRefresh : Boolean;
    FCanEdit : Boolean;   //�������ӡ��޸ġ�ɾ��
    FCanDelete: Boolean;  // ����ɾ��
    FCanAdd: Boolean;     // ��������
    FCanChange: Boolean;  // �����޸�
    FLocalDepartment : string;  // ����Ӫҵ������
    procedure   SetStatus(const Value: TSettingStatus);
    procedure   SetCanAdd(const Value: Boolean);
    procedure   SetCanChange(const Value: Boolean);
    procedure   SetCanDelete(const Value: Boolean);
    procedure   CheckDataCanEdit;
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
  public
    constructor Create(AOwner : TComponent); override;
    procedure   CloseDataset; override;
    property    Status : TSettingStatus read FStatus write SetStatus;
    property    AutoRefresh : Boolean read FAutoRefresh write FAutoRefresh default True;
    property    CanAdd : Boolean read FCanAdd write SetCanAdd default True;
    property    CanChange : Boolean read FCanChange write SetCanChange default True;
    property    CanDelete : Boolean read FCanDelete write SetCanDelete default True;
    property    MaintainType : TParamMaintainType read FMaintainType;
  end;

var
  faSMSetParamsTemp: TfaSMSetParamsTemp;

implementation

uses KSFrameWorkUtils, DataUsageUtils, LogFile;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

{ TfaSetParamsTemp }

constructor TfaSMSetParamsTemp.Create(AOwner: TComponent);
begin
  inherited;
  DataGrid := Grid;
  FStatus := ssBrowse;
  FCanEdit := True;
  FCanDelete := True;
  FCanAdd := True;
  FCanChange := True;
  FAutoRefresh := True;
end;

procedure TfaSMSetParamsTemp.btnAddClick(Sender: TObject);
begin
  Status := ssAdd;
end;

procedure TfaSMSetParamsTemp.Init;
begin
  inherited;
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

procedure TfaSMSetParamsTemp.btnChangeClick(Sender: TObject);
begin
  Status := ssChange;
end;

procedure TfaSMSetParamsTemp.SetStatus(const Value: TSettingStatus);
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

procedure TfaSMSetParamsTemp.pcPagesChanging(Sender: TObject;
  var AllowChange: Boolean);
begin
  if ((pcPages.ActivePageIndex=0) and (Status=ssBrowse))
    or ((pcPages.ActivePageIndex=1) and (Status<>ssBrowse)) then
    AllowChange := False;
end;

procedure TfaSMSetParamsTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSMSetParamsTemp.BeforeAdd;
begin
  tsEdit.Caption := SAdd;
  // ���е�������Ŀ���Ա༭
  EnableEditCtrls(True);
  // ��ʼ������������Ŀ
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaSMSetParamsTemp.BeforeChange;
begin
  tsEdit.Caption := SChange;
  // ���е�������Ŀ���Ա༭
  // ���������ظ÷�������ֹ�������Ա༭
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetParamsTemp.BeforeDelete;
begin
  tsEdit.Caption := SDelete;
  // ���е�������Ŀ�������Ա༭
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetParamsTemp.btnDeleteClick(Sender: TObject);
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

function TfaSMSetParamsTemp.GetCurrentRecordInfo: string;
begin
  Result := '';
end;

procedure TfaSMSetParamsTemp.CancelEdit;
begin
  Status := ssBrowse;
end;

procedure TfaSMSetParamsTemp.DoAdd;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetParamsTemp.DoChange;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetParamsTemp.DoDelete;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(DeleteRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetParamsTemp.DoQuery;
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

procedure TfaSMSetParamsTemp.SendQueryCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    QueryRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSMSetParamsTemp.btnOKClick(Sender: TObject);
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
      ssChange :
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
      DoQuery;
  end;
end;

procedure TfaSMSetParamsTemp.btnCancelClick(Sender: TObject);
begin
  CancelEdit;
end;

procedure TfaSMSetParamsTemp.SendEditCommand(Request : TWVRequest);
begin
  FEditSucceed := True;
  try
    ShowWaiting(SWaitingOperation);
    Request.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSMSetParamsTemp.EnableEdit(CanEdit: Boolean);
begin
  //FCanEdit := CanEdit;
  //UpdateButton;
end;

procedure TfaSMSetParamsTemp.CheckReturnData(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TfaSMSetParamsTemp.pcPagesDrawTab(Control: TCustomTabControl;
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

procedure TfaSMSetParamsTemp.EnableEditCtrls(AEnabled: Boolean);
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

procedure TfaSMSetParamsTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  if Field=nil then
  begin
    CheckDataCanEdit;
    if Status=ssViewDetail then
      DisplayData;
  end;
end;

procedure TfaSMSetParamsTemp.SetCanAdd(const Value: Boolean);
begin
  FCanAdd := Value;
  UpdateButton;
end;

procedure TfaSMSetParamsTemp.SetCanChange(const Value: Boolean);
begin
  FCanChange := Value;
  UpdateButton;
end;

procedure TfaSMSetParamsTemp.SetCanDelete(const Value: Boolean);
begin
  FCanDelete := Value;
  UpdateButton;
end;

procedure TfaSMSetParamsTemp.UpdateButton;
begin
  FCanEdit := InternalGetCanEdit;
  btnAdd.Enabled := FCanEdit and CanAdd;
  btnDelete.Enabled := FCanEdit and CanDelete;
  btnChange.Enabled := FCanEdit and CanChange;
end;

procedure TfaSMSetParamsTemp.CloseDataset;
begin
  inherited;
  if QueryBinder.Field<>nil then
    QueryBinder.Field.Data.Clear;
end;

function TfaSMSetParamsTemp.InternalGetCanEdit: Boolean;
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

procedure TfaSMSetParamsTemp.DataSourceStateChange(Sender: TObject);
begin
  CheckDataCanEdit;
end;

procedure TfaSMSetParamsTemp.CheckDataCanEdit;
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

procedure TfaSMSetParamsTemp.BeforeViewDetail{(IsFirst : Boolean=True)};
begin
  tsEdit.Caption := SViewDetail;
  // ���е�������Ŀ�������Ա༭
  EnableEditCtrls(False);
end;

procedure TfaSMSetParamsTemp.btnViewDetailClick(Sender: TObject);
begin
  if (DataSource.DataSet<>nil) and (not DataSource.DataSet.IsEmpty) then
    Status := ssViewDetail;
end;

procedure TfaSMSetParamsTemp.GridDblClick(Sender: TObject);
begin
  if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
    Status := ssViewDetail;
end;

procedure TfaSMSetParamsTemp.CheckEditFieldValid(WorkField: TWVField);
begin
  if not (status in [ssAdd, ssChange]) then
    WorkField.Valid := True;
end;

procedure TfaSMSetParamsTemp.DBNavigatorClick(Sender: TObject;
  Button: TNavigateBtn);
begin
  //BeforeViewDetail(False);
  //DisplayData;
end;

procedure TfaSMSetParamsTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSMSetParamsTemp.StatusChanged;
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

procedure TfaSMSetParamsTemp.DisplayData;
begin
  // �����ݴ�����Դͬ����������ͼ���ٵ����ֿؼ�����ע�⣺һЩ������Ҫ���ظ÷�������������ؼ�������ͬ����
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetParamsTemp.SaveModifiedData;
begin
  // ���޸ĵ�����ͬ����������ͼ�����ʹ������Ŀؼ���Ҫ���ش˷�����
  WorkView.SynchronizeCtrlsToFields;
end;


procedure TfaSMSetParamsTemp.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  if FDepartmentWVField=nil then Exit;
  if FDepartmentWVField.Data.AsString=CenterDepartNo then
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,'')
  else
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,FDepartmentFieldName);
end;

procedure TfaSMSetParamsTemp.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_RETURN) and ([ssCtrl]=Shift) then
  begin
    Key := 0;
    if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
      Status := ssViewDetail;
  end;
end;

procedure TfaSMSetParamsTemp.alDatasetActionsExecute(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  if Action.HandlesTarget(DataSource) then
    Action.ExecuteTarget(DataSource);
end;

procedure TfaSMSetParamsTemp.alDatasetActionsUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  Action.UpdateTarget(DataSource);
end;

function TfaSMSetParamsTemp.ConfirmEdit: Boolean;
begin
  Result := True;
end;



end.

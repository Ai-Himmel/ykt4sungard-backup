unit USimpleQueryTemp;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USimpleQueryTemp
   <What>�򵥲�ѯ����ģ��
   <Written By> Huang YanLai (������)
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
    {wsn20041230 ��������������Ϣ}
    Procedure OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
    //20050316 wsn �ڿ���м���ȡ�õ�ǰ���ݼ���ѯ�������Ĺ���
    function  GetCurrentRecordCount:Integer;

  protected
    procedure   DoIt; virtual; // �̳и÷�������������
    procedure   SendCommand; virtual; // �̳и÷������������(����FHaveGotData=False����ֹ�л�page)
    function    CanDoAction(const ActionID : TCommonActionID) : Boolean; override;
    procedure   InitEx; override;
    procedure   Init; override; //��дworkview ������Ϊinteger,float��ֵ��hanjiwei add it 
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
  LabRecordCount.Caption:='��ѯ�� '+IntToStr(GetCurrentRecordCount)+' ����¼';
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
  LabRecordCount.Caption:='��ѯ�� '+IntToStr(GetCurrentRecordCount)+' ����¼';
end;


{-------------------------------------------------------------------------------
  ������:    TfaSimpleQueryTemp.GridDrawColumnCell��������ʾ
  ����:      ����ΰ
  ����:      2006.06.30
  ����:      Sender: TObject; const Rect: TRect; DataCol: Integer; Column: TColumn; State: TGridDrawState
  ����ֵ:    ��
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
      if DataSource.DataSet.RecNo mod 2<>0 then {�жϵ�ǰ��������������ż����}
      Canvas.brush.Color :=clInfoBk {����������У�DBGrid�����԰�ɫ��ʾ}
    else
      Canvas.brush.Color :=$00EBDED0; {�����ż����$00EBDED0��DBGrid������ǳ��ɫ��ʾ}
    end;
    DefaultDrawColumnCell(Rect, DataCol, Column, State); {���кܹؼ��ģ�һ����Ҫ��©��}
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
  //�Զ���ʼ��Integer��ֵ,hanjiwei add it 20080421
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

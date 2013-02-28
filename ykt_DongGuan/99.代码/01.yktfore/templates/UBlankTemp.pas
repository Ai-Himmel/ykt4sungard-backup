unit UBlankTemp;

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
  TfaBlankTemp = class(TKSFrame)
    UIPnlQueryCount: TUIPanel;
    UIPanel2: TUIPanel;
    LabRecordCount: TLabel;
    Image1: TImage;
    procedure  MainRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure  btnPrintClick(Sender: TObject);
    procedure DataSourceDataChange(Sender: TObject; Field: TField);
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
  faBlankTemp: TfaBlankTemp;

implementation

{$R *.DFM}

uses KSFrameWorkUtils, SmartCardCommon,TypInfo, DBAIntf,DataTypes;

{TfaSimpleQueryTemp}

constructor TfaBlankTemp.Create(AOwner: TComponent);
begin
  inherited;

  //Application.OnMessage:=OnMouseWheel;
end;

function  TfaBlankTemp.GetCurrentRecordCount:Integer;
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

Procedure TfaBlankTemp.OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
begin 
end;


procedure TfaBlankTemp.DoIt;
begin
end;

procedure TfaBlankTemp.SendCommand;
begin
end;

procedure TfaBlankTemp.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  LabRecordCount.Caption:='��ѯ�� '+IntToStr(GetCurrentRecordCount)+' ����¼';
  CheckCommandReturnValue(Command, False);
end;

procedure TfaBlankTemp.InitEx;
begin
  inherited;
end;

procedure TfaBlankTemp.btnPrintClick(Sender: TObject);
begin
  DoPrint;
end;

function TfaBlankTemp.CanDoAction(
  const ActionID: TCommonActionID): Boolean;
begin
end;

procedure TfaBlankTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
end;


{-------------------------------------------------------------------------------
  ������:    TfaSimpleQueryTemp.GridDrawColumnCell��������ʾ
  ����:      ����ΰ
  ����:      2006.06.30
  ����:      Sender: TObject; const Rect: TRect; DataCol: Integer; Column: TColumn; State: TGridDrawState
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaBlankTemp.Init;
begin
  inherited;
end;

end.

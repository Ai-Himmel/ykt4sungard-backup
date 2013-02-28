unit UBlankTemp;

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
  LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
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
  过程名:    TfaSimpleQueryTemp.GridDrawColumnCell表格隔行显示
  作者:      韩纪伟
  日期:      2006.06.30
  参数:      Sender: TObject; const Rect: TRect; DataCol: Integer; Column: TColumn; State: TGridDrawState
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfaBlankTemp.Init;
begin
  inherited;
end;

end.

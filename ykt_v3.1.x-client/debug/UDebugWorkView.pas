unit UDebugWorkView;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WorkViews, WVCtrls, Contnrs, StdCtrls;

const
  CaptionX = 10;
  TextX = 200;
  HMargin = 6;

type
  TfmDebugWorkView = class(TForm)
    ScrollBox1: TScrollBox;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
    FWorkView: TWorkView;
    FList : TObjectList;
    procedure SetWorkView(const Value: TWorkView);
    procedure CreateDetailLabels;
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
  public
    { Public declarations }
    procedure Execute(AWorkView : TWorkView; const ACaption:string='');
    property  WorkView : TWorkView read FWorkView write SetWorkView ;
  end;

var
  fmDebugWorkView: TfmDebugWorkView;

procedure DoDebugWorkView(WorkView : TWorkView; const ACaption:string='');

implementation

{$R *.DFM}

procedure DoDebugWorkView(WorkView : TWorkView; const ACaption:string='');
var
  DebugForm : TfmDebugWorkView;
begin
  DebugForm := TfmDebugWorkView.Create(Application);
  DebugForm.Execute(WorkView, ACaption);
end;

{ TfmDebugWorkView }

procedure TfmDebugWorkView.Execute(AWorkView: TWorkView; const ACaption:string='');
begin
  WorkView := AWorkView;
  Caption := Hint + ACaption;
  Show;
end;

procedure TfmDebugWorkView.SetWorkView(const Value: TWorkView);
begin
  if FWorkView <> Value then
  begin
    FWorkView := Value;
    ScrollBox1.HorzScrollBar.Position := 0;
    ScrollBox1.VertScrollBar.Position := 0;
    if FWorkView<>nil then
    begin
      FWorkView.FreeNotification(Self);
      CreateDetailLabels;
    end else
      Close;
  end;
end;

procedure TfmDebugWorkView.FormCreate(Sender: TObject);
begin
  FList := TObjectList.Create;
end;

procedure TfmDebugWorkView.FormDestroy(Sender: TObject);
begin
  FreeAndNil(FList);
end;

procedure TfmDebugWorkView.CreateDetailLabels;
var
  I : Integer;
  Field : TWVField;
  CaptionLabel : TLabel;
  TextLabel : TWVLabel;
  Y : Integer;
begin
  FList.Clear;
  if WorkView<>nil then
  begin
    Y := HMargin;
    for I:=0 to WorkView.FieldCount-1 do
    begin
      Field := WorkView.Fields[I];
      CaptionLabel := TLabel.Create(Self);
      CaptionLabel.Caption := Format('%d %s',[Field.GroupIndex,Field.Name]);
      CaptionLabel.SetBounds(CaptionX,Y,CaptionLabel.Width,CaptionLabel.Height);
      CaptionLabel.Parent := ScrollBox1;
      FList.Add(CaptionLabel);
      TextLabel:= TWVLabel.Create(Self);
      TextLabel.WorkView := WorkView;
      TextLabel.FieldName := Field.Name;
      TextLabel.SetBounds(TextX,Y,TextLabel.Width,TextLabel.Height);
      TextLabel.Parent := ScrollBox1;
      FList.Add(TextLabel);
      Inc(Y,CaptionLabel.Height+HMargin);
    end;
  end;
end;

procedure TfmDebugWorkView.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited;
  if (Operation=opRemove) and (AComponent=FWorkView) then
    WorkView:=nil;
end;

procedure TfmDebugWorkView.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  Action := caFree;
end;

end.

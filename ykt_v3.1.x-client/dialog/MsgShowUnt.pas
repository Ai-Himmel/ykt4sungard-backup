unit MsgShowUnt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  RzButton, StdCtrls, ExtCtrls, ImgList,RzCommon, RzEdit, jpeg;

  Const SB_OK=-2;
  Const SB_OKCANCEL=-3;
  Const SB_YESNO=-5;
  Const SB_OKOPTION=-7;
type
  TMsgShowFrm = class(TForm)
    Image2: TImage;
    ImgList: TImageList;
    ImgIcon: TImage;
    ImgClose: TImage;
    LabCap: TLabel;
    LabMsg: TLabel;
    Timer1: TTimer;
    FMeoOption: TRZMemo;
    procedure FormShow(Sender: TObject);
    procedure Image2MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ImgCloseClick(Sender: TObject);
    procedure ImgCloseMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ImgCloseMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Timer1Timer(Sender: TObject);
  private
    VaResult : integer;
    procedure CreateIcon(Index:Integer);
    procedure CreatefrmSize;
    procedure GetCreateButton(Mst:Integer;frm1:TMsgShowFrm);
    procedure OnClickBtn(Sender: TObject);
    procedure TimeClosefrm;
    { Private declarations }
  public
    SType:Integer;
    SIcon:Integer;
    STime:Integer;
    { Public declarations }
  end;

var
  MsgShowFrm: TMsgShowFrm;
  function ShowMsg(Text:String;Caption:String='软件名称';OptionText:string='详细的信息';ShowType:Integer=SB_OK;ShowIcon:integer=1;ShowTime:Integer=-1): Integer;
implementation


{$R *.DFM}

procedure TMsgShowFrm.FormShow(Sender: TObject);
begin
  CreatefrmSize;                     //调整窗体大小..
  GetCreateButton(SType,self);       //创建按钮..
  CreateIcon(SIcon);               //显示图标...
  self.Height := 128;
  Self.Refresh;
end;

procedure TMsgShowFrm.Image2MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if Button=mbLeft then
  begin
    ReleaseCapture;
    SendMessage(handle, WM_SYSCOMMAND, SC_MOVE or 2 , 0);
  end else inherited;
end;

procedure TMsgShowFrm.CreateIcon(Index:Integer);
begin
  ImgList.GetIcon(Index,ImgIcon.Picture.Icon);
end;

procedure TMsgShowFrm.ImgCloseClick(Sender: TObject);
begin
  close;
end;

procedure TMsgShowFrm.ImgCloseMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  ImgClose.Left :=ImgClose.Left +1;
  ImgClose.Top := ImgClose.Top +1;
end;

procedure TMsgShowFrm.ImgCloseMouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  ImgClose.Left :=ImgClose.Left -1;
  ImgClose.Top := ImgClose.Top -1;
end;

procedure TMsgShowFrm.CreatefrmSize;
begin
  self.Width := self.LabMsg.Width + 80;
  self.ImgClose.Left := Self.Width-18;
  self.FMeoOption.Width := self.Image2.Width;
end;

procedure TMsgShowFrm.GetCreateButton(Mst:Integer;frm1:TMsgShowFrm);
Var
  RzBtn : TRzButton;
begin
  if Mst = SB_OK then
  begin
    RzBtn :=  TRzButton.Create(self);
    RzBtn.parent := self;
    RzBtn.HotTrack := true;
    RzBtn.TextStyle := tsRecessed;
    RzBtn.Color := $00F0E8F0;
    RzBtn.Width := 75;
    RzBtn.Top := frm1.Height - 110;
    RzBtn.Left := Round((frm1.Width-RzBtn.Width)/2);
    RzBtn.Name := 'SB_OK';
    RzBtn.Caption := '确 定';
    RzBtn.OnClick := OnClickBtn;
  end;
  if Mst = SB_OKCANCEL then
  begin
    RzBtn :=  TRzButton.Create(self);
    RzBtn.parent := self;
    RzBtn.HotTrack := true;
    RzBtn.TextStyle := tsRecessed;
    RzBtn.Color := $00F0E8F0;
    RzBtn.Width := 70;
    RzBtn.Top := frm1.Height - 110;
    RzBtn.Left := Round((frm1.Width)/2-80);
    RzBtn.Name := 'SB_OK';
    RzBtn.Caption := '确 定';
    RzBtn.OnClick := OnClickBtn;
    RzBtn :=  TRzButton.Create(self);
    RzBtn.parent := self;
    RzBtn.HotTrack := true;
    RzBtn.TextStyle := tsRecessed;
    RzBtn.Color := $00F0E8F0;
    RzBtn.Width := 70;
    RzBtn.Top := frm1.Height - 110;
    RzBtn.Left := Round((frm1.Width)/2);
    RzBtn.Name := 'SB_CANCEL';
    RzBtn.Caption := '取 消';
    RzBtn.OnClick := OnClickBtn;
  end;
  if Mst = SB_YESNO then
  begin
    RzBtn :=  TRzButton.Create(self);
    RzBtn.parent := self;
    RzBtn.HotTrack := true;
    RzBtn.TextStyle := tsRecessed;
    RzBtn.Color := $00F0E8F0;
    RzBtn.Width := 70;
    RzBtn.Top := frm1.Height - 110;
    RzBtn.Left := Round((frm1.Width)/2-80);
    RzBtn.Name := 'SB_YES';
    RzBtn.Caption := '是';
    RzBtn.OnClick := OnClickBtn;
    RzBtn :=  TRzButton.Create(self);
    RzBtn.parent := self;
    RzBtn.HotTrack := true;
    RzBtn.TextStyle := tsRecessed;
    RzBtn.Color := $00F0E8F0;
    RzBtn.Width := 70;
    RzBtn.Top := frm1.Height - 110;
    RzBtn.Left := Round((frm1.Width)/2);
    RzBtn.Name := 'SB_NO';
    RzBtn.Caption := '否';
    RzBtn.OnClick := OnClickBtn;
  end;
  if Mst = SB_OKOPTION then
  begin
    RzBtn :=  TRzButton.Create(self);
    RzBtn.parent := self;
    RzBtn.HotTrack := true;
    RzBtn.TextStyle := tsRecessed;
    RzBtn.Color := $00F0E8F0;
    RzBtn.Width := 70;
    RzBtn.Top := frm1.Height - 110;
    RzBtn.Left := Round((frm1.Width)/2-80);
    RzBtn.Name := 'SB_OK';
    RzBtn.Caption := '确 定';
    RzBtn.OnClick := OnClickBtn;
    RzBtn :=  TRzButton.Create(self);
    RzBtn.parent := self;
    RzBtn.HotTrack := true;
    RzBtn.TextStyle := tsRecessed;
    RzBtn.Color := $00F0E8F0;
    RzBtn.Width := 70;
    RzBtn.Top := frm1.Height - 110;
    RzBtn.Left := Round((frm1.Width)/2);
    RzBtn.Name := 'SB_OPTION';
    RzBtn.Caption := '详细>>>';
    RzBtn.OnClick := OnClickBtn;
  end;
end;

function ShowMsg(Text:String;Caption:String='软件名称';OptionText:string='详细的信息';
  ShowType:Integer=SB_OK;ShowIcon:integer=1;ShowTime:Integer=-1): Integer;
Var
  frm:TMsgShowFrm;
begin
  frm := TMsgShowFrm.Create(nil);
  MsgShowFrm := frm;
  Try
    frm.LabMsg.Caption := Text;
    frm.LabCap.Caption := Caption;
    frm.FMeoOption.Lines.Text := OptionText;
    frm.SType:=ShowType;
    frm.SIcon:=ShowIcon;
    frm.STime:=ShowTime;
    if ShowTime<>-1 then
    begin
      frm.Timer1.Interval := ShowTime*1000;
      frm.Timer1.Enabled := True;
    end;
    frm.ShowModal;
  Finally
    ShowMsg := frm.VaResult;
    frm.free;
  End;
end;

procedure TMsgShowFrm.OnClickBtn(Sender: TObject);
begin
  Application.ProcessMessages;
  if TRzButton(Sender).name = 'SB_OK' then
  begin
    VaResult := IDOK;
    Close;
  end;
  if TRzButton(Sender).name = 'SB_CANCEL' then
  begin
    VaResult := IDCANCEL;
    Close;
  end;
  if TRzButton(Sender).name = 'SB_YES' then
  begin
    VaResult := IDYES;
    Close;
  end;
  if TRzButton(Sender).name = 'SB_NO' then
  begin
    VaResult := IDNO;
    Close;
  end;
  if TRzButton(Sender).name = 'SB_OPTION' then
  begin
    FMeoOption.Visible := not(FMeoOption.Visible);
    if FMeoOption.Visible then
      self.Height := 200
    else self.Height := 128;
  end;
end;

procedure TMsgShowFrm.TimeClosefrm;
begin
  Self.Hide;
  Application.ProcessMessages;
  if SType = SB_OK then
  begin
    VaResult := IDOK;
    Close;
  end;
  if SType = SB_OKCANCEL then
  begin
    VaResult := IDCANCEL;
    Close;
  end;
  if SType = SB_YESNO then
  begin
    VaResult := IDNO;
    Close;
  end;
  if SType = SB_OKOPTION then
  begin
    VaResult := IDOK;
    Close;
  end;
end;

procedure TMsgShowFrm.Timer1Timer(Sender: TObject);
begin
  Timer1.Enabled := false;
  TimeClosefrm;
end;

end.

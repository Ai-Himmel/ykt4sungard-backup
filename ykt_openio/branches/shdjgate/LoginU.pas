unit LoginU;

interface

uses
    Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
    Dialogs, StdCtrls, Buttons, ExtCtrls, SQLiteTable3, commu, ComCtrls;

type
    TLoginFrm = class(TForm)
        bbnOK: TBitBtn;
        bbnCancel: TBitBtn;
        mess: TPanel;
        StatusBar1: TStatusBar;
        Timer1: TTimer;
        procedure bbnCancelClick(Sender: TObject);
        procedure bbnOKClick(Sender: TObject);
        procedure FormClose(Sender: TObject; var Action: TCloseAction);
        procedure FormShow(Sender: TObject);
        procedure FormCreate(Sender: TObject);
        procedure FormKeyDown(Sender: TObject; var Key: Word;
            Shift: TShiftState);
        procedure FormKeyUp(Sender: TObject; var Key: Word;
            Shift: TShiftState);
        procedure FormKeyPress(Sender: TObject; var Key: Char);
        procedure StatusBar1DblClick(Sender: TObject);
        procedure Timer1Timer(Sender: TObject);
    private
        { Private declarations }
    public
        { Public declarations }
        beging: boolean;
        isTerminate: boolean;
    end;

var
    LoginFrm: TLoginFrm;
    isCtrl: boolean; //检测Shift键是否按下
    ss: string; //接收到键盘的字符串
    isStart: Boolean; //是否开始接收字符
implementation

{$R *.dfm}

procedure TLoginFrm.bbnCancelClick(Sender: TObject);
begin
    isTerminate := true;
    Close;
end;

procedure TLoginFrm.bbnOKClick(Sender: TObject);
begin
    isTerminate := false;
    beging := true;
    close;
end;

procedure TLoginFrm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
    if not beging then
        isTerminate := true;
end;

procedure TLoginFrm.FormShow(Sender: TObject);
begin
    beging := false;
end;

procedure TLoginFrm.FormCreate(Sender: TObject);
begin
    procGetIniInfo;
    ss := '';
    isCtrl := False;
    isStart := False;

    if debug = 'false' then begin
        timer1.Enabled := true;
        Application.Title := Application.Title + ' - Running mode';
        LoginFrm.Caption := LoginFrm.Caption + ' - Running mode';
    end
    else begin
        timer1.Enabled := false;
        Application.Title := Application.Title + ' - debug mode';
        LoginFrm.Caption := LoginFrm.Caption + ' - debug mode';
    end;
    mess.Caption :=    GetDelphiVer;

end;

procedure TLoginFrm.FormKeyDown(Sender: TObject; var Key: Word;
    Shift: TShiftState);
begin
    if Shift >= [ssCtrl] then begin
        isCtrl := True;
    end;
end;

procedure TLoginFrm.FormKeyUp(Sender: TObject; var Key: Word;
    Shift: TShiftState);
begin
    if not (ssCtrl in Shift) then begin
        ss := '';
        isCtrl := False;
        isStart := False;
    end;
end;

procedure TLoginFrm.FormKeyPress(Sender: TObject; var Key: Char);
begin
    if (isCtrl and (key = 'p')) then begin
        isCtrl := True;
    end;
    if isCtrl then begin
        ss := ss + key;
        if ss = 'phy' then begin
            ss := '';
            isCtrl := False;
            isStart := False;

        end;
    end;
end;

procedure TLoginFrm.StatusBar1DblClick(Sender: TObject);
begin
    if debug = 'true' then begin
        if encryConfigFile('phy.txt') then begin
            showmessage('恭喜您！加密成功');
            Application.Terminate;
            exit;
        end
        else begin
            showmessage('Sorry！加密失败');
        end

    end;
end;

procedure TLoginFrm.Timer1Timer(Sender: TObject);
begin
    bbnOKClick(Sender);
end;

end.


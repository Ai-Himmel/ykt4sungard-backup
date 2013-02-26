unit LoginU;

interface

uses
    Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
    Dialogs, StdCtrls, Buttons, ExtCtrls, commu, ComCtrls;

type
    TLoginFrm = class(TForm)
        bbnOK: TBitBtn;
        bbnCancel: TBitBtn;
        mess: TPanel;
        StatusBar1: TStatusBar;
        procedure bbnCancelClick(Sender: TObject);
        procedure bbnOKClick(Sender: TObject);
        procedure FormClose(Sender: TObject; var Action: TCloseAction);
        procedure FormShow(Sender: TObject);
        procedure StatusBar1DblClick(Sender: TObject);
    private
        { Private declarations }
    public
        { Public declarations }
        beging: boolean;
        isTerminate: boolean;
    end;

var
    LoginFrm: TLoginFrm;

implementation

{$R *.dfm}

procedure TLoginFrm.bbnCancelClick(Sender: TObject);
begin
    isTerminate := true;
    Close;
end;

procedure TLoginFrm.bbnOKClick(Sender: TObject);
var
    ret: integer;
    sSql: string;
begin
    procGetIniInfo;
    ret := SMT_ConnectMF280(posport, baud);
    if ret <> 0 then begin
        SMT_CloseMF280;
        showmessage('�򿪴���ʧ��ʧ�ܣ�');
        exit;
    end
    else begin
        ret := SMT_ControlBuzzer;
        if ret <> 0 then
            showmessage('�򿪴���ʧ��ʧ�ܣ�');
    end;

    if not funcConnectDB then begin
        showmessage('�������ݿ�ʧ�ܣ�');
        exit;
    end;

    isTerminate := false;
    beging := true;
    Close;
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

procedure TLoginFrm.StatusBar1DblClick(Sender: TObject);
begin
    procGetIniInfo;
    if debug = 'true' then begin
        if encryConfigFile('../conf/phy.txt') then begin
            showmessage('��ϲ�������ܳɹ�');
            Application.Terminate;
            exit;
        end
        else begin
            showmessage('Sorry������ʧ��');
        end

    end;
end;

end.

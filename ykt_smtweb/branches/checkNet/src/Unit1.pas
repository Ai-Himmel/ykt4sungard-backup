unit Unit1;

interface

uses
    Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
    ExtCtrls, WinInet, inifiles, ComCtrls, StdCtrls, Menus, RzTray;

type
    TForm1 = class(TForm)
        Timer1: TTimer;
        StatusBar1: TStatusBar;
        Button1: TButton;
        RzTrayIcon1: TRzTrayIcon;
        PopupMenu1: TPopupMenu;
        Exit1: TMenuItem;
        procedure Timer1Timer(Sender: TObject);
        procedure FormShow(Sender: TObject);
        procedure Button1Click(Sender: TObject);
        procedure Exit1Click(Sender: TObject);
    private
        { Private declarations }
    public
        { Public declarations }
    end;

var
    Form1: TForm1;
    timeSeparator: integer;
    urlString: String;
    errContent: String;
    _debug: String;
    _logged: boolean;

implementation

uses
    Unit2, Unit3;
{$R *.DFM}

function CheckUrl(url: string): boolean;
var
    hSession, hfile: hInternet;
    dwindex, dwcodelen: dword;
    dwcode: array [1 .. 20] of char;
    res: pchar;
begin
    // ���URL�Ƿ����http://����������������
    if pos('http://', lowercase(url)) = 0 then
        url := 'http://' + url;

    Result := false;

    hSession := InternetOpen('InetURL:/1.0', INTERNET_OPEN_TYPE_PRECONFIG, nil, nil, 0); // �����Ự���
    if assigned(hSession) then begin
        hfile := InternetOpenUrl(hSession, pchar(url), nil, 0, INTERNET_FLAG_RELOAD, 0); // ��URL��ָ��Դ

        dwindex := 0;
        dwcodelen := 10;
        HttpQueryInfo(hfile, HTTP_QUERY_STATUS_CODE, @dwcode, dwcodelen, dwindex); // ��ȡ���ص�HTTPͷ��Ϣ

        res := pchar(@dwcode);
        Result := (res = '200') or (res = '302');

        if assigned(hfile) then
            InternetCloseHandle(hfile); // �ر�URL��Դ���
        InternetCloseHandle(hSession); // �ر�Internet�Ự���
    end;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
    if (CheckUrl(urlString)) then begin
        if (_logged) then
            writeLog(FormatDateTime('yyyy-mm-dd hh:nn:ss', Now()) + '    ' + 'Server is ok.');
        StatusBar1.SimpleText := 'url is : ' + urlString + ', success...';
        form2.Panel1.Caption := '';
        form2.Hide;
    end
    else begin
        if (_logged) then
            writeLog(FormatDateTime('yyyy-mm-dd hh:nn:ss', Now()) + '    ' + 'Server is error.');
        StatusBar1.SimpleText := 'url is : ' + urlString + ', connect fail...';
        form2.WindowState := wsMaximized;
        form2.BorderStyle := bsNone;
        form2.Panel1.Caption := errContent;
        form2.FormStyle := fsStayOnTop;
        form2.Show;
    end;
end;

procedure TForm1.FormShow(Sender: TObject);
var
    iniFile: TIniFile;
begin
    iniFile := TIniFile.Create(ExtractFilePath(Application.EXEName) + '..\configs\config.ini');
    timeSeparator := iniFile.ReadInteger('CheckNet', 'timeSeparator', 60);
    urlString := iniFile.ReadString('CheckNet', 'urlString', 'http://www.google.com');
    errContent := iniFile.ReadString('CheckNet', 'errContent', '���������Ӳ���,���Ժ�����!');
    _debug := iniFile.ReadString('System', 'debug', 'true');

    if (UpperCase(iniFile.ReadString('System', 'logged', 'true')) = 'TRUE') then begin
        _logged := true;
    end
    else begin
        _logged := false;
    end;

    Timer1.Interval := timeSeparator * 1000;
    if (UpperCase(_debug) = 'TRUE') then begin
        ShowMessage('Time Separator is:' + IntToStr(timeSeparator));
        ShowMessage('Server URL String is:' + urlString);
        ShowMessage('Error String is:' + errContent);
        Timer1.Enabled := false;
    end
    else begin
        Timer1.Enabled := true;
    end;

    iniFile.Free;
    makeInitConfigFile();
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
    if (CheckUrl(urlString)) then begin
        if (_logged) then
            writeLog(FormatDateTime('yyyy-mm-dd hh:nn:ss', Now()) + '    ' + 'Server is ok.');
        StatusBar1.SimpleText := 'url is : ' + urlString + ', success...';
        form2.Panel1.Caption := '';
        form2.Hide;
        Application.Minimize;
    end
    else begin
        if (_logged) then
            writeLog(FormatDateTime('yyyy-mm-dd hh:nn:ss', Now()) + '    ' + 'Server is error.');
        RzTrayIcon1.RestoreApp;
        Application.BringToFront;
        StatusBar1.SimpleText := 'url is : ' + urlString + ', connect fail...';
        form2.WindowState := wsMaximized;
        form2.BorderStyle := bsNone;
        form2.Panel1.Caption := errContent;
        form2.FormStyle := fsStayOnTop;
        form2.Show;
    end;
end;

procedure TForm1.Exit1Click(Sender: TObject);
begin
    Application.Terminate;
end;

end.

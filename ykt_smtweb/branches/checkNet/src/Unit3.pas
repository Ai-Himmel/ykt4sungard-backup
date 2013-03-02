unit Unit3;

interface

procedure writeLog(content: String);
procedure makeDir(dirString: String);
procedure makeInitConfigFile();

implementation

uses
    SysUtils, Forms;

procedure writeLog(content: String);
var
    logFilename: String;
    F: Textfile;
begin
    //
    makeDir(ExtractFilePath(Application.EXEName) + '..\logs\');
    logFilename := ExtractFilePath(Application.EXEName) + '..\logs\' + FormatDateTime('yyyymmdd', Now()) + '.txt';
    if fileExists(logFilename) then begin
        AssignFile(F, logFilename);
        Append(F);
    end
    else begin
        AssignFile(F, logFilename);
        ReWrite(F);
    end;
    Writeln(F, content);
    Flush(F);
    Closefile(F);

end;

procedure makeDir(dirString: String);
begin
    if not DirectoryExists(dirString) then begin
        if not CreateDir(dirString) then
            raise Exception.Create('Cannot create ' + dirString);
    end;
end;

procedure makeInitConfigFile();
var
    configFilename: String;
    F: Textfile;
begin
    makeDir(ExtractFilePath(Application.EXEName) + '..\configs\');
    configFilename := ExtractFilePath(Application.EXEName) + '..\configs\config.ini';
    if not fileExists(configFilename) then begin
        AssignFile(F, configFilename);
        ReWrite(F);
        Writeln(F, '[System]');
        Writeln(F, 'debug=false');
        Writeln(F, 'logged=true');
        Writeln(F, '[CheckNet]');
        Writeln(F, 'timeSeparator=10');
        Writeln(F, 'urlString=http://www.sina1.com.cn');
        Writeln(F, 'errContent=服务器连接失败，请以后再尝试！');
        Flush(F);
        Closefile(F);
        raise Exception.Create(
            '../configs/config.ini is not found,now use default config and create a new config.ini. please define your params in "../configs/config.ini" ');
    end;

end;

end.

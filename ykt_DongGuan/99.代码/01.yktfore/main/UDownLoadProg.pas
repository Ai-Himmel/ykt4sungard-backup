unit UDownLoadProg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  IdAntiFreezeBase, IdAntiFreeze, IdBaseComponent, IdComponent,
  IdTCPConnection, IdTCPClient, IdHTTP, ComCtrls, StdCtrls,IniFiles;

type
  TFrmDownloadProg = class(TForm)
    idhtp1: TIdHTTP;
    dlgSave1: TSaveDialog;
    idntfrz1: TIdAntiFreeze;
    lbl1: TLabel;
    pbPosi: TProgressBar;
    btnDownLoad: TButton;
    procedure idhtp1WorkBegin(Sender: TObject; AWorkMode: TWorkMode;
      const AWorkCountMax: Integer);
    procedure idhtp1Work(Sender: TObject; AWorkMode: TWorkMode;
      const AWorkCount: Integer);
    procedure btnDownLoadClick(Sender: TObject);
  private
    { Private declarations }
    FDownLoadFileName:string;
  public
    { Public declarations }
  end;

var
  FrmDownloadProg: TFrmDownloadProg;
procedure DoDownLoad(DFileName:string);

implementation

{$R *.DFM}
procedure DoDownLoad(DFileName:string);
var
  Dialog: TFrmDownloadProg;
begin
  Dialog := TFrmDownloadProg.Create(Application);
  try
    Dialog.FDownLoadFileName := DFileName;
    Dialog.ShowModal;
  finally
    Dialog.Free;
  end;
end;
procedure TFrmDownloadProg.idhtp1WorkBegin(Sender: TObject;
  AWorkMode: TWorkMode; const AWorkCountMax: Integer);
begin
  pbPosi.Max:=AWorkCountMax;
  pbPosi.Min:=0;
  pbPosi.Position:=0;
end;

procedure TFrmDownloadProg.idhtp1Work(Sender: TObject;
  AWorkMode: TWorkMode; const AWorkCount: Integer);
begin
  pbPosi.Position:=pbPosi.Position+AWorkCount;
end;

procedure TFrmDownloadProg.btnDownLoadClick(Sender: TObject);
var
  MyStream:TMemoryStream;
  myfile:TIniFile;
  verHttpPath:string;
  saveFileName:string;
  useProxy,proxyPort:Integer;
  proxyServer,proxyUser,proxyPwd:string;
begin

  dlgSave1.FileName := 'c:\'+FDownLoadFileName+'.exe';
  if dlgSave1.Execute then
    saveFileName := dlgSave1.FileName;
    
  myfile := nil;
  idntfrz1.OnlyWhenIdle:=False;//设置使程序有反应.
  MyStream := nil;
  try
    try
      myfile := TIniFile.Create(ExtractFilePath(Application.ExeName)+'../configs/update.ini');
      verHttpPath := myfile.ReadString('progupdate','httppath','');
      useProxy := myfile.ReadInteger('progupdate','useproxy',0);
      proxyServer := myfile.ReadString('progupdate','proxyserver','');
      proxyPort := myfile.ReadInteger('progupdate','proxyport',0);
      proxyUser := myfile.ReadString('progupdate','proxyuser','');
      proxyPwd := myfile.ReadString('progupdate','proxypwd','');
    except
      on e:exception do
      begin
        Showmessage('配置文件读取错误,不能完成版本检测--'+e.Message);
        Exit;
      end;
    end;
    if useProxy=1 then
    begin
      idhtp1.ProxyParams.ProxyServer := proxyServer;
      idhtp1.ProxyParams.ProxyPort := proxyPort;
      idhtp1.ProxyParams.ProxyUsername := proxyUser;
      idhtp1.ProxyParams.ProxyPassword := proxyPwd;
    end
    else
    begin
      idhtp1.ProxyParams.ProxyServer := '';
      idhtp1.ProxyParams.ProxyPort := 0;
      idhtp1.ProxyParams.ProxyUsername := '';
      idhtp1.ProxyParams.ProxyPassword := '';
    end;
    
    MyStream:=TMemoryStream.Create;
    try
      idhtp1.Get(verHttpPath+FDownLoadFileName+'.exe',MyStream);//下载我站点的一个ZIP文件
    except
      on e:Exception do
      begin
        ShowMessage('下载文件失败--'+e.Message);
        Exit;
      end;
    end;

    MyStream.SaveToFile(saveFileName);

    ShowMessage('下载完成，请重新安装该程序！');
    Application.Terminate;
  finally
    MyStream.Free;
    myfile.Free;
  end;
end;

end.

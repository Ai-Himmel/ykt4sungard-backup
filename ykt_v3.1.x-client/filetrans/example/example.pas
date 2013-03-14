unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
    SaveDialog1: TSaveDialog;
    Edit2: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Edit3: TEdit;
    Button2: TButton;
    OpenDialog1: TOpenDialog;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses filetrans;

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
  KSG_init('10.49.118.250',4000,7100);
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  KSG_uninit;
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  ret :integer;
begin
  if SaveDialog1.Execute then
  begin
    edit2.Text := SaveDialog1.FileName;
    if length(edit1.Text) = 0 then
    begin
      ShowMessage('请输入下载文件名!');
      Exit;
    end;
    ret := KSG_Download_File(edit1.Text,edit2.Text);
    if ret = KSG_SUCCESS then
      ShowMessage('下载成功')
    else
      ShowMessage('下载失败');
  end;
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  ret :Integer;
begin
  if OpenDialog1.Execute then
  begin
    edit3.Text := OpenDialog1.FileName;
    ret := KSG_Upload_File(edit3.Text,ExtractFileName(edit3.Text));
    if ret = KSG_SUCCESS then
      ShowMessage('上传成功')
    else
    begin
      ShowMessage(KSG_get_errmsg);
      ShowMessage('上传失败')
    end;
  end;
end;

end.
 Format('IP=%s,Port=%d,DestNo=%d,FuncNo=%d,Datasets=%d,Pooled=%d',
          [GatewayIP,GatewayPort,DestNo,FuncNo,Count,PooledConnectionCount]);
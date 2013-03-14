unit UASetBusPosKey;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,  PublicFunc,
  EditExts, Buttons;

type
  TfaqhBusPosKey = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVComboBox1: TWVComboBox;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    Panel2: TPanel;
    grp1: TGroupBox;
    Label3: TLabel;
    edtPwdVer: TWVEdit;
    chuploadfile: TCheckBox;
    btnOK: TImageButton;
    btnCancle: TImageButton;
    procedure btnOKClick(Sender: TObject);
    procedure btnCancleClick(Sender: TObject);
  private
    function GetPosKey : String;
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBusPosKey: TfaqhBusPosKey;

implementation

uses KsFrameworks;

{$R *.DFM}

function TfaqhBusPosKey.GetPosKey: String;
var
   GetKey : TDataSet;
begin
  Result:='';
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger <> 0 then
  begin
    ConText.GetDialogSystem.ShowError(WorkView.FieldByName('返回信息').Data.AsString);
    exit;
  end;
  GetKey:=TDataSet(WorkView.FieldByName('返回数据集').Data.AsObject);
  result := GetKey.fieldbyname('scard0').Asstring;
end;

procedure TfaqhBusPosKey.Init;
begin
  {
  ImageButton1.Caption := '确定';
  ImageButton2.Caption := '取消';
  }
  edtPwdVer.Text := FormatDateTime('yyMMddhhnnss',now());
  ReadConfig;
end;

procedure TfaqhBusPosKey.btnOKClick(Sender: TObject);
var
  ErrMsg : String;
begin
 SaveToBinary(Trim(edtPwdVer.Text)+GetPosKey,UPLOADDIR+KEY,length(edtPwdVer.Text+GetPosKey) div 2);
 if chuploadfile.Checked then
    UploadFile(pchar(UPLOADDIR+KEY),pchar(KEY),PORT,BAUT,INDEX,0,ErrMsg);
    
 if Trim(ErrMsg)<>'' then ConText.GetDialogSystem.ShowError(ErrMsg);
end;

procedure TfaqhBusPosKey.btnCancleClick(Sender: TObject);
begin
 close;
end;

initialization
  TUIStdClassFactory.Create('密钥管理', TfaqhBusPosKey);

end.

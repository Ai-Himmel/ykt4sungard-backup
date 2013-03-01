unit phtImportData;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls, ADOdb, phtDBConnect, phtFieldLink,
  phtDefaultValue, phtComplete, phtImportForm;

type
  // 导入数据的步骤，如数据源连接，字段对接，默认值设置，完成导入等。
  TimpStep = (impDBConnect, impFieldLink, impDefaultValue, impComplete);

  TfrmImportData = class(TForm)
    GroupBox1: TGroupBox;
    btnCancel: TButton;
    btnBack: TButton;
    btnNext: TButton;
    btnFinish: TButton;
    pnlMainland: TPanel;
    OpenDialog: TOpenDialog;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnBackClick(Sender: TObject);
    procedure btnNextClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnFinishClick(Sender: TObject);
  private
    { Private declarations }
    FCurStep: TimpStep;
    FImportForms: array[TimpStep] of TfrmImportForm;
    FCurForm: TfrmImportForm;

    procedure ChangeCurForm;
  public
    { Public declarations }   
    function SelectDataSource: Boolean;
  end;
    
  procedure ImportData(Conn: TADOConnection);

implementation

uses
  phtImport;
  
procedure ImportData(Conn: TADOConnection);
var
  frmImportData: TfrmImportData;
begin
  G_phtImport.Connect2Photo(Conn);

  frmImportData := TfrmImportData.Create(Application);  
  if frmImportData.SelectDataSource then
    frmImportData.ShowModal;
   
  frmImportData.Free;
end;

{$R *.DFM}

procedure TfrmImportData.FormCreate(Sender: TObject);
begin
  // 创建每个步骤所对应的窗体 
  FImportForms[impDBConnect] := TfrmDBConnect.Create(nil);
  FImportForms[impFieldLink] := TfrmFieldLink.Create(nil);
  FImportForms[impDefaultValue] := TfrmDefaultValue.Create(nil);
  FImportForms[impComplete] := TfrmComplete.Create(nil);
end;

procedure TfrmImportData.FormDestroy(Sender: TObject);
var
  Step: TimpStep;
begin
  // 释放每一个步骤所对应的窗体
  for Step := Low(TimpStep) to High(TimpStep) do
    FImportForms[Step].Free;
end;
 
procedure TfrmImportData.FormShow(Sender: TObject);
begin
  // 第一个步骤是数据源连接 (DBConnect)
  FCurStep := impDBConnect;
  FCurForm := FImportForms[FCurStep];
  FCurForm.Parent := pnlMainland;
  FCurForm.Enter;
end;

procedure TfrmImportData.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  // 断开当前步骤对应的窗体与主窗体的绑定关系，并使其不可见 
  FCurForm.Visible := False;
  FCurForm.Parent := nil;
end;

procedure TfrmImportData.btnBackClick(Sender: TObject);
begin
  FCurStep := TimpStep(Ord(FCurStep) - 1);  // 后退一步
  btnNext.Enabled := True;
  if FCurStep = Low(TimpStep) then
    btnBack.Enabled := False;              // 第一步

  ChangeCurForm;
  FCurForm.Show;
end;

procedure TfrmImportData.btnNextClick(Sender: TObject);
begin
  if not FCurForm.Leave then
    Exit;

  FCurStep := TimpStep(Ord(FCurStep) + 1);  // 前进一步
  btnBack.Enabled := True;
  if FCurStep = High(TimpStep) then
    btnNext.Enabled := False;               // 最后一步

  ChangeCurForm;
  FCurForm.Enter;
end;

procedure TfrmImportData.ChangeCurForm;
begin
  // 步骤改变后更新对应的窗体，并显示   
  FCurForm.Visible := False;
  FCurForm.Parent := nil;
  FCurForm := FImportForms[FCurStep];
  FCurForm.Parent := pnlMainland;
end;

procedure TfrmImportData.btnFinishClick(Sender: TObject);
begin   
  // add 20050601
  if FCurStep = impDBConnect then
    btnNextClick(btnNext);  // 前进一步
  // end of add
  
  if not FCurForm.Leave then
    Exit;   // 有待于考量

  if not G_phtImport.IsReady then
  begin
    MessageDlg(G_phtImport.ErrorMsg, mtWarning, [mbOk], 0);
    Exit;
  end;
  if MessageDlg('确认要导入数据吗?', mtConfirmation, [mbYes, mbNo], 0)
    = mrNo then
  begin // 放弃导入数据
    Exit;
  end;
{
  // add 当进度条，临时用
  FCurStep := impDBConnect;  // 第一步
  btnBack.Enabled := False;
  btnNext.Enabled := True; 
  ChangeCurForm;   
  FCurForm.Show;
  // end of add
}  
  Screen.Cursor := crHourGlass;
  if G_phtImport.Import then
  begin
    MessageDlg('导入数据成功!', mtInformation, [mbOk], 0);
    Self.Close;
  end
  else
    MessageDlg(G_phtImport.ErrorMsg, mtInformation, [mbOk], 0);

  Screen.Cursor := crDefault;
end;

function TfrmImportData.SelectDataSource: Boolean;
{
  建立导入数据源的连接。
}
begin
  if OpenDialog.Execute then
  begin
    case OpenDialog.FilterIndex of
      // Microsoft Visual FoxPro
      1: G_phtImport.Connect2FoxPro(OpenDialog.FileName);
      // Microsoft Access
      2: G_phtImport.Connect2Access(OpenDialog.FileName);
    end;
    Result := True;
  end
  else
    Result := False;
end;

end.

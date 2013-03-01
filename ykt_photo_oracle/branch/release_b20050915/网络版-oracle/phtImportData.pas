unit phtImportData;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls, ADOdb, phtDBConnect, phtFieldLink,
  phtDefaultValue, phtComplete, phtImportForm;

type
  // �������ݵĲ��裬������Դ���ӣ��ֶζԽӣ�Ĭ��ֵ���ã���ɵ���ȡ�
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
  // ����ÿ����������Ӧ�Ĵ��� 
  FImportForms[impDBConnect] := TfrmDBConnect.Create(nil);
  FImportForms[impFieldLink] := TfrmFieldLink.Create(nil);
  FImportForms[impDefaultValue] := TfrmDefaultValue.Create(nil);
  FImportForms[impComplete] := TfrmComplete.Create(nil);
end;

procedure TfrmImportData.FormDestroy(Sender: TObject);
var
  Step: TimpStep;
begin
  // �ͷ�ÿһ����������Ӧ�Ĵ���
  for Step := Low(TimpStep) to High(TimpStep) do
    FImportForms[Step].Free;
end;
 
procedure TfrmImportData.FormShow(Sender: TObject);
begin
  // ��һ������������Դ���� (DBConnect)
  FCurStep := impDBConnect;
  FCurForm := FImportForms[FCurStep];
  FCurForm.Parent := pnlMainland;
  FCurForm.Enter;
end;

procedure TfrmImportData.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  // �Ͽ���ǰ�����Ӧ�Ĵ�����������İ󶨹�ϵ����ʹ�䲻�ɼ� 
  FCurForm.Visible := False;
  FCurForm.Parent := nil;
end;

procedure TfrmImportData.btnBackClick(Sender: TObject);
begin
  FCurStep := TimpStep(Ord(FCurStep) - 1);  // ����һ��
  btnNext.Enabled := True;
  if FCurStep = Low(TimpStep) then
    btnBack.Enabled := False;              // ��һ��

  ChangeCurForm;
  FCurForm.Show;
end;

procedure TfrmImportData.btnNextClick(Sender: TObject);
begin
  if not FCurForm.Leave then
    Exit;

  FCurStep := TimpStep(Ord(FCurStep) + 1);  // ǰ��һ��
  btnBack.Enabled := True;
  if FCurStep = High(TimpStep) then
    btnNext.Enabled := False;               // ���һ��

  ChangeCurForm;
  FCurForm.Enter;
end;

procedure TfrmImportData.ChangeCurForm;
begin
  // ����ı����¶�Ӧ�Ĵ��壬����ʾ   
  FCurForm.Visible := False;
  FCurForm.Parent := nil;
  FCurForm := FImportForms[FCurStep];
  FCurForm.Parent := pnlMainland;
end;

procedure TfrmImportData.btnFinishClick(Sender: TObject);
begin   
  // add 20050601
  if FCurStep = impDBConnect then
    btnNextClick(btnNext);  // ǰ��һ��
  // end of add
  
  if not FCurForm.Leave then
    Exit;   // �д��ڿ���

  if not G_phtImport.IsReady then
  begin
    MessageDlg(G_phtImport.ErrorMsg, mtWarning, [mbOk], 0);
    Exit;
  end;
  if MessageDlg('ȷ��Ҫ����������?', mtConfirmation, [mbYes, mbNo], 0)
    = mrNo then
  begin // ������������
    Exit;
  end;
{
  // add ������������ʱ��
  FCurStep := impDBConnect;  // ��һ��
  btnBack.Enabled := False;
  btnNext.Enabled := True; 
  ChangeCurForm;   
  FCurForm.Show;
  // end of add
}  
  Screen.Cursor := crHourGlass;
  if G_phtImport.Import then
  begin
    MessageDlg('�������ݳɹ�!', mtInformation, [mbOk], 0);
    Self.Close;
  end
  else
    MessageDlg(G_phtImport.ErrorMsg, mtInformation, [mbOk], 0);

  Screen.Cursor := crDefault;
end;

function TfrmImportData.SelectDataSource: Boolean;
{
  ������������Դ�����ӡ�
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

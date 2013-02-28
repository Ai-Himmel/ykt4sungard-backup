unit UASetBusiDev;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhSetBusiDev = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label10: TLabel;
    Label13: TLabel;
    Label14: TLabel;
	WVEdit3: TWVEdit;
	WVEdit4: TWVEdit;
    edtSSNo: TWVEdit;
    Label1: TLabel;
    cbbDevType: TWVComboBox;
    btnQBusi: TSpeedButton;
    Label2: TLabel;
    edtBusiName: TWVEdit;
    Label7: TLabel;
    WVEdit2: TWVEdit;
    pnlBusiQ: TPanel;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    WVDBBinder1: TWVDBBinder;
    DataSource1: TDataSource;
    Panel2: TPanel;
    Label9: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label25: TLabel;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    WVComboBox8: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Grid1: TRzDBGrid;
    pnl1: TPanel;
    btnSelect: TButton;
    btnCan: TButton;
    btnQ: TButton;
    WVComboBox3: TWVComboBox;
    WVComboBox4: TWVComboBox;
    edtBusiId: TWVEdit;
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnCanClick(Sender: TObject);
    procedure btnQBusiClick(Sender: TObject);
    procedure btnSelectClick(Sender: TObject);
    procedure btnQClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure Grid1DrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure Grid1DblClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetBusiDev: TfaqhSetBusiDev;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSetBusiDev.Init;
begin
  inherited;
  {
  WorkView.FieldByName('≤È—Ø.≤Ÿ◊˜±Í÷æ').DefaultValue := '';
  WorkView.FieldByName('≤È—Ø.…Ãªß∫≈').DefaultValue := 0;
  WorkView.FieldByName('≤È—Ø.…Ë±∏÷’∂À–Ú¡–∫≈').DefaultValue := '';
  WorkView.FieldByName('≤È—Ø. °…Ë±∏÷’∂À–Ú¡–∫≈').DefaultValue := '';
  WorkView.FieldByName('≤È—Ø.…Ë±∏¿‡–Õ').DefaultValue := '';
  WorkView.FieldByName('≤È—Ø.◊¥Ã¨').DefaultValue := '';
  WorkView.FieldByName('≤È—Ø.◊¢≤·»’∆⁄').DefaultValue := '';
  WorkView.FieldByName('≤È—Ø.∆Ù”√»’∆⁄').DefaultValue := '';
  WorkView.FieldByName('≤È—Ø.Õ£”√»’∆⁄').DefaultValue := '';
  WorkView.FieldByName('…Ãªß∫≈').DefaultValue := 0;
  WorkView.FieldByName('…Ãªß√˚≥∆').DefaultValue := '';
  WorkView.FieldByName('…Ë±∏÷’∂À–Ú¡–∫≈').DefaultValue := '';
  WorkView.FieldByName(' ').DefaultValue := ;
  WorkView.FieldByName('…Ë±∏¿‡–Õ').DefaultValue := '';
  WorkView.FieldByName('◊¥Ã¨').DefaultValue := '';
  WorkView.FieldByName('◊¢≤·»’∆⁄').DefaultValue := '';
  WorkView.FieldByName('∆Ù”√»’∆⁄').DefaultValue := '';
  WorkView.FieldByName('Õ£”√»’∆⁄').DefaultValue := '';
  WorkView.FieldByName('∞Û∂®…Ë±∏±‡∫≈').DefaultValue := 0;
  WorkView.FieldByName('±∏◊¢').DefaultValue := '';
  WorkView.FieldByName('◊Ó∫Û∏¸–¬ ±º‰').DefaultValue := '';
  WorkView.Reset;
  }
  pnlBusiQ.Visible := False;
  edtBusiId.ReadOnly := True;
end;

procedure TfaqhSetBusiDev.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('≤Ÿ◊˜±Í÷æ').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetBusiDev.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('≤Ÿ◊˜±Í÷æ').Data.SetString('A');
  edtBusiId.Text := '0';
  btnQBusi.Enabled := True;
end;

procedure TfaqhSetBusiDev.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('≤Ÿ◊˜±Í÷æ').Data.SetString('U');
  btnQBusi.Enabled := False;

end;

procedure TfaqhSetBusiDev.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('≤Ÿ◊˜±Í÷æ').Data.SetString('D');
  btnQBusi.Enabled := False;

end;

procedure TfaqhSetBusiDev.btnOKClick(Sender: TObject);
begin
  if edtBusiId.Text='0' then
  begin
    Context.GetDialogSystem.ShowMessage('«Î—°‘Ò“™…Ë÷√µƒ…Ãªß£°');
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhSetBusiDev.btnCanClick(Sender: TObject);
begin
  pnlBusiQ.Visible := False;

end;

procedure TfaqhSetBusiDev.btnQBusiClick(Sender: TObject);
begin
  pnlBusiQ.Visible := True;

end;

procedure TfaqhSetBusiDev.btnSelectClick(Sender: TObject);
begin
  try
  edtBusiId.Text := Grid1.DataSource.DataSet.fieldbyname('lvol0').AsString;
  edtBusiName.Text := Grid1.DataSource.DataSet.fieldbyname('snote').AsString;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('«Î—°‘Ò…Ãªß£°');
      Exit;
    end;
  end;
  pnlBusiQ.Visible := False;
end;

procedure TfaqhSetBusiDev.btnQClick(Sender: TObject);
begin
  WorkView1.FieldByName('≤Ÿ◊˜±Í÷æ').Data.SetString('R');
  WVRequest1.SendCommand;

end;

procedure TfaqhSetBusiDev.GridDblClick(Sender: TObject);
begin
  //inherited;

end;

procedure TfaqhSetBusiDev.Grid1DrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

procedure TfaqhSetBusiDev.Grid1DblClick(Sender: TObject);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('…Ãªß÷’∂Àπ‹¿Ì',TfaqhSetBusiDev);

end.
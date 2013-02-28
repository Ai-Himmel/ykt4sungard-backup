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
  WorkView.FieldByName('��ѯ.������־').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻���').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�豸�ն����к�').DefaultValue := '';
  WorkView.FieldByName('��ѯ.ʡ�豸�ն����к�').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�豸����').DefaultValue := '';
  WorkView.FieldByName('��ѯ.״̬').DefaultValue := '';
  WorkView.FieldByName('��ѯ.ע������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.ͣ������').DefaultValue := '';
  WorkView.FieldByName('�̻���').DefaultValue := 0;
  WorkView.FieldByName('�̻�����').DefaultValue := '';
  WorkView.FieldByName('�豸�ն����к�').DefaultValue := '';
  WorkView.FieldByName('�').DefaultValue := ;
  WorkView.FieldByName('�豸����').DefaultValue := '';
  WorkView.FieldByName('״̬').DefaultValue := '';
  WorkView.FieldByName('ע������').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('ͣ������').DefaultValue := '';
  WorkView.FieldByName('���豸���').DefaultValue := 0;
  WorkView.FieldByName('��ע').DefaultValue := '';
  WorkView.FieldByName('������ʱ��').DefaultValue := '';
  WorkView.Reset;
  }
  pnlBusiQ.Visible := False;
  edtBusiId.ReadOnly := True;
end;

procedure TfaqhSetBusiDev.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetBusiDev.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('A');
  edtBusiId.Text := '0';
  btnQBusi.Enabled := True;
end;

procedure TfaqhSetBusiDev.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('U');
  btnQBusi.Enabled := False;

end;

procedure TfaqhSetBusiDev.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('D');
  btnQBusi.Enabled := False;

end;

procedure TfaqhSetBusiDev.btnOKClick(Sender: TObject);
begin
  if edtBusiId.Text='0' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ���õ��̻���');
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
      Context.GetDialogSystem.ShowMessage('��ѡ���̻���');
      Exit;
    end;
  end;
  pnlBusiQ.Visible := False;
end;

procedure TfaqhSetBusiDev.btnQClick(Sender: TObject);
begin
  WorkView1.FieldByName('������־').Data.SetString('R');
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
  TUIStdClassFactory.Create('�̻��ն˹���',TfaqhSetBusiDev);

end.
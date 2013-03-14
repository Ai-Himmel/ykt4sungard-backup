unit UAChangeDev;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, ComCtrls, RzDBGrid, Buttons, EditExts, RzListVw,
  RzPanel, RzSplit;

type
  TfqhqChangeDev = class(TfaqhSimpleQueryTemp)
    RzSizePanel1: TRzSizePanel;
    pnl1: TPanel;
    Panel1: TPanel;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    WVEdit1: TWVEdit;
    WVEdit3: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVComboBox6: TWVComboBox;
    edtMachineNo: TWVEdit;
    Label2: TLabel;
    btnOldQuery: TBitBtn;
    Panel2: TPanel;
    Label6: TLabel;
    Label7: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    WVEdit2: TWVEdit;
    WVEdit4: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    WVEdit5: TWVEdit;
    btnNewQry: TBitBtn;
    rgOld: TRzDBGrid;
    rgNew: TRzDBGrid;
    WVDBBinder1: TWVDBBinder;
    DataSource1: TDataSource;
    WVChange: TWorkView;
    WVRchange: TWVRequest;
    lblOld: TLabel;
    lblNew: TLabel;
    WVNewQry: TWorkView;
    WVRNewQry: TWVRequest;
    procedure btnOldQueryClick(Sender: TObject);
    procedure btnNewQryClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure rgOldCellClick(Column: TColumn);
    procedure rgNewCellClick(Column: TColumn);
  private
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  fqhqChangeDev: TfqhqChangeDev;
  flag:integer;

implementation

uses KsFrameworks,KSDataDictionary;
     
{$R *.DFM}
procedure TfqhqChangeDev.Init;
begin
  inherited;
  lblOld.Caption := '';
  lblNew.Caption := '';
end;
procedure TfqhqChangeDev.btnOldQueryClick(Sender: TObject);
begin
  if Trim(edtMachineNo.Text)='' then
    edtMachineNo.Text := '0';
  MainRequest.SendCommand;
end;

procedure TfqhqChangeDev.btnNewQryClick(Sender: TObject);
begin
  if Trim(WVEdit5.Text)='' then
    WVEdit5.Text := '0';
  WVRNewQry.SendCommand;
end;

procedure TfqhqChangeDev.btnQueryClick(Sender: TObject);
var
  oldUes,newUes:string;
begin
  oldUes := rgOld.DataSource.DataSet.fieldbyname('damt5').AsString;
  newUes := rgNew.DataSource.DataSet.fieldbyname('damt5').AsString;
  if oldUes<>newUes then
  begin
    Context.GetDialogSystem.ShowMessage('��Ҫ�������豸��;��ͬ����ȷ�Ϻ��ٸ�����');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ����ѡ����豸��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVChange.FieldByName('���豸').Data.SetInteger(rgold.DataSource.DataSet.FieldByName('lvol0').AsInteger);
  WVChange.FieldByName('���豸').Data.SetInteger(rgNew.DataSource.DataSet.FieldByName('lvol0').AsInteger);
  WVRchange.SendCommand;
  if WVChange.FieldByName('������').Data.AsInteger=0 then
    Context.GetDialogSystem.ShowMessage('�����豸�ɹ���')
  else
    Context.GetDialogSystem.ShowMessage(WVChange.FieldByName('������Ϣ').Data.AsString);
end;

procedure TfqhqChangeDev.rgOldCellClick(Column: TColumn);
begin
  lblOld.Caption := '��ǰѡ���豸��'+rgold.DataSource.DataSet.FieldByName('scert_no').AsString;

end;

procedure TfqhqChangeDev.rgNewCellClick(Column: TColumn);
begin
  lblNew.Caption := '��ǰѡ���豸��'+rgnew.DataSource.DataSet.FieldByName('scert_no').AsString;

end;

initialization
  TUIStdClassFactory.Create('�����豸',TfqhqChangeDev);

end.
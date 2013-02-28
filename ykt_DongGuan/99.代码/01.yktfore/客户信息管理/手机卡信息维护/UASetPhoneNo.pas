unit UASetPhoneNo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons;

type
  TfaqhSetPhoneNo = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    edtCardNoQ: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    Label1: TLabel;
    edtTNo: TWVEdit;
    Label6: TLabel;
    edtPhone: TWVEdit;
    Label7: TLabel;
    edtCardNo: TWVEdit;
    btnEdit: TBitBtn;
    WVSet: TWorkView;
    WVRequest1: TWVRequest;
    procedure btnQueryClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnEditClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetPhoneNo: TfaqhSetPhoneNo;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhSetPhoneNo.Init;
begin
  inherited;
  {
  WorkView.FieldByName('操作标志').DefaultValue := '';
  WorkView.FieldByName('卡号').DefaultValue := 0;
  WorkView.FieldByName('手机通宝卡号').DefaultValue := '';
  WorkView.FieldByName('手机号').DefaultValue := '';
  WorkView.FieldByName('更新时间').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhSetPhoneNo.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCardNoQ.Text)='' then
    edtCardNoQ.Text := '0';
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetPhoneNo.GridCellClick(Column: TColumn);
begin
  try
    edtCardNo.Text := Grid.DataSource.DataSet.fieldbyname('lvol0').AsString;
    edtTNo.Text:= Grid.DataSource.DataSet.fieldbyname('sphone3').AsString;
    edtPhone.Text := Grid.DataSource.DataSet.fieldbyname('sphone').AsString;
  except

  end;
end;

procedure TfaqhSetPhoneNo.btnEditClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要修改手机卡信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVSet.FieldByName('操作标志').Data.SetString('U');
  WVSet.FieldByName('卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
  WVSet.FieldByName('手机通宝卡号').Data.SetString(edtTNo.Text);
  WVSet.FieldByName('手机号').Data.SetString(edtPhone.Text);
  try
    WVRequest1.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  Context.GetDialogSystem.ShowMessage('修改手机卡信息成功！');

end;

initialization
  TUIStdClassFactory.Create('手机卡信息维护',TfaqhSetPhoneNo);

end.
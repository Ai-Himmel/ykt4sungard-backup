unit UAQueryBusinessByOther;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons;

type
  TfaqhQueryBusinessByOther = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label9: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label14: TLabel;
    Label20: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit12: TWVEdit;
    WVEdit14: TWVEdit;
    WVEdit20: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox5: TWVComboBox;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    WVEdit6: TWVEdit;
    Label17: TLabel;
    Label18: TLabel;
    WVComboBox6: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
    procedure WVEdit8DblClick(Sender: TObject);
    procedure WVEdit3Change(Sender: TObject);
    procedure WVEdit2Change(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhQueryBusinessByOther: TfaqhQueryBusinessByOther;

implementation

uses KsFrameworks, 
     UWorkerNum;
     
{$R *.DFM}

procedure TfaqhQueryBusinessByOther.Init;
begin
  inherited;
  WVComboBox1.ItemIndex:=0;
  WVComboBox2.ItemIndex:=0;
  WVComboBox5.ItemIndex:=0;
  WVComboBox6.ItemIndex:=0;

end;

procedure TfaqhQueryBusinessByOther.btnQueryClick(Sender: TObject);
begin
  if  Trim(WVEdit2.Text)='' then
  begin
    WorkView.FieldByName('商户标识').Data.SetInteger(0);
  end;
  if  Trim(WVEdit3.Text)='' then
  begin
    WorkView.FieldByName('父商户标识').Data.SetInteger(0);
  end;
  inherited;
end;

procedure TfaqhQueryBusinessByOther.WVEdit8DblClick(Sender: TObject);
begin
  QueryWorkerNum:=TQueryWorkerNum.Create(nil);
  try
    QueryWorkerNum.ShowModal;
  finally
    QueryWorkerNum.Free;
  end;


end;

procedure TfaqhQueryBusinessByOther.WVEdit3Change(Sender: TObject);
begin
  try
    StrToInt(WVEdit3.Text);
  except
    WVEdit3.Text:='0';
  end;
end;

procedure TfaqhQueryBusinessByOther.WVEdit2Change(Sender: TObject);
begin
  try
    StrToInt(WVEdit2.Text);
  except
    WVEdit2.Text:='0';
  end;

end;

initialization
  TUIStdClassFactory.Create('商户信息查询',TfaqhQueryBusinessByOther);

end.
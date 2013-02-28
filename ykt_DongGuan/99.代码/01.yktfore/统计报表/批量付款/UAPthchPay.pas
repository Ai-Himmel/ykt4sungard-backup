unit UAPthchPay;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons,filetrans, ComCtrls,FileCtrl,
  RzListVw, UIncrementComboBox;

type
  TfaqhPatchPay = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    edtTipInfo: TEdit;
    lvData: TRzListView;
    pbStatues: TProgressBar;
    WVLabel1: TWVLabel;
    edtBusiId: TWVEdit;
    WVLabel2: TWVLabel;
    edtBusiname: TWVEdit;
    chkSelectAll: TCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure btnPrintClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
  private

    { Private declarations }
    //endGetPhotoSign:Boolean;
    //procedure getPhoto;
    procedure fillList(wv:TWorkView);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPatchPay: TfaqhPatchPay;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,data2Excel,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhPatchPay.Init;
begin
  inherited;
end;

procedure TfaqhPatchPay.btnPrintClick(Sender: TObject);
var
  i,num:Integer;
  busiId,busiStr1,busiStr2,busiStr3,busiStr0:string;

begin
  if Application.MessageBox('��ȷ��Ҫ��ѡ�����̻�����������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
    num := 0;
    for i := 0 to lvData.Items.Count-1 do
    begin

      if lvData.Items[i].Checked then
      begin
        inc(num);
        if num>80 then
        begin
          busiStr0 := '';
          busiStr1 := '';
          busiStr3 := '';
          busiStr2 := '';
          Context.GetDialogSystem.ShowMessage('ѡ���̻����������ܳ���80����');
          Exit;
        end;
        busiId := lvData.Items[i].Caption;
        if num<=20 then
        begin
          if num=20 then
            busiStr0 := busiStr0+busiId
          else
            busiStr0 := busiStr0+busiId+',';
        end
        else if num<=40 then
        begin
          if num=40 then
            busiStr1 := busiStr1+busiId
          else
            busiStr1 := busiStr1+busiId+',';
        end
        else if num<=60 then
        begin
          if num=60 then
            busiStr2 := busiStr2+busiId
          else
            busiStr2 := busiStr2+busiId+',';
        end
        else if num<=80 then
        begin
          if num=80 then
            busiStr3 := busiStr3+busiId
          else
            busiStr3 := busiStr3+busiId+',';
        end;
      end;
    end;
    WorkView1.FieldByName('����').Data.SetString(edtTipInfo.Text);
    WorkView1.FieldByName('�̻�0').Data.SetString(busiStr0);
    WorkView1.FieldByName('�̻�1').Data.SetString(busiStr1);
    WorkView1.FieldByName('�̻�2').Data.SetString(busiStr2);
    WorkView1.FieldByName('�̻�3').Data.SetString(busiStr3);
    try
      WVRequest1.SendCommand;
      Context.GetDialogSystem.ShowMessage('������ɣ�');
    except
      on e:Exception do
      Context.GetDialogSystem.ShowMessage('����ʧ��-'+e.Message);
    end;
end;

procedure TfaqhPatchPay.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvData.Items.Add;
    //�̻���
    tmpItem.Caption := tmpdataset.fieldbyname('lvol2').AsString;
    //�̻�����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);
    //�̻����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);
    //�������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt1').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '��ѯ��'+inttostr(lvData.Items.Count)+'����¼';
end;

procedure TfaqhPatchPay.btnQueryClick(Sender: TObject);
begin
  lvData.Items.Clear;
  if (edtbusiId.text='') then
    edtBusiId.text := '0';
  inherited;
  fillList(WorkView);

end;

procedure TfaqhPatchPay.chkSelectAllClick(Sender: TObject);
var
  i:Integer;
begin
  if chkSelectAll.Checked then
    for i := 0 to lvdata.Items.Count-1 do
      lvdata.Items[i].Checked := True
  else
    for i := 0 to lvdata.Items.Count-1 do
      lvdata.Items[i].Checked := False;
end;

initialization
  TUIStdClassFactory.Create('��������',TfaqhPatchPay);

end.
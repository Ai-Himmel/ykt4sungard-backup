unit UASetGateMagOpen;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, ComCtrls, RzDBGrid, Buttons, EditExts, RzPanel,
  RzSplit;

type
  TEquipParaTreeNode = class
  public
    CEquipID: Integer;       {�豸��ʶ} //�� �豸�̻��� �� �豸�������Ψһ�ֶΣ�
    CNodeID: String;        {�豸����ID}
    CNodeCaption: String;   {�豸����}
    CNodeKind: String;     {����ID}
    CParentNodeID: String;  {���豸����ID}
    CParentNodeCaption: String;  {���豸����}
    CNodeKindCaption:String; {��������}
    CEquipRegNo : String ;  {�����豸ע���}
 //   CEquipNo: Integer ; {����}
 //   CEquipState : Integer; {�豸״̬ID}
 //   CEquipShowId:Integer;{�豸�������͹���}
 //   CNodeImage : Integer;
end;

type
  TfaqhSetGateMgrOpen = class(TfaqhSimpleQueryTemp)
    spnl1: TRzSizePanel;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    pnlDevInfo: TPanel;
    pnl1: TPanel;
    Label6: TLabel;
    Label7: TLabel;
    WVLabel5: TWVLabel;
    WVLabel9: TWVLabel;
    WVLabel8: TWVLabel;
    WVEdit4: TWVEdit;
    WVEdit8: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVEdit5: TWVEdit;
    WVComboBox5: TWVComboBox;
    btnCardQuery: TBitBtn;
    pnlCardInfo: TPanel;
    pnlCardQuery: TPanel;
    Label4: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label5: TLabel;
    Label3: TLabel;
    WVComboBox18: TWVComboBox;
    WVEdit1: TWVEdit;
    WVComboBox17: TWVComboBox;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    btnDevQuery: TBitBtn;
    lvEqu: TListView;
    lvCard: TListView;
    WVLabel1: TWVLabel;
    cbbUse: TWVComboBox;
    WVLabel2: TWVLabel;
    cbbOperType: TWVComboBox;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    dlgSave1: TSaveDialog;
    chkCustAll: TCheckBox;
    chkDevall: TCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnDevQueryClick(Sender: TObject);
    procedure btnCardQueryClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure chkCustAllClick(Sender: TObject);
    procedure chkDevallClick(Sender: TObject);
  private
    { Private declarations }

    function selectAllotD(lv:TListView):Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetGateMgrOpen: TfaqhSetGateMgrOpen;
  flag:integer;

implementation

uses KsFrameworks,KSDataDictionary,SmartCardCommon;

{$R *.DFM}
procedure TfaqhSetGateMgrOpen.Init;
begin
  inherited;
end;

procedure TfaqhSetGateMgrOpen.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSetGateMgrOpen.btnDevQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdataset:TDataSet;
begin
  MainRequest.SendCommand;
  lvEqu.Items.Clear;
  inherited;
  tmpdataset := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if tmpdataset.fieldbyname('lvol0').AsInteger=1 then
    begin
      tmpdataset.Next;
      Continue;
    end;
    tmpItem := lvEqu.Items.Add;
    //tmpItem.Caption := tmpdataset.fieldbyname('lvol0').AsString;//
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);//�豸���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);//�豸������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString); //�豸����
    tmpItem.SubItems.Add(GetIdObjectName(-31,tmpdataset.fieldbyname('damt6').AsString));//�ϼ��豸
    tmpItem.SubItems.Add(GetIdObjectName(47,tmpdataset.fieldbyname('sbank_code').AsString));//�豸����
    tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdataset.fieldbyname('lserial0').AsString));//������ϵͳ
    tmpdataset.Next;
  end;
end;

procedure TfaqhSetGateMgrOpen.btnCardQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdataset:TDataSet;
begin
  WVRequest1.SendCommand;
  lvCard.Items.Clear;
  inherited;
  tmpdataset := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvCard.Items.Add;
    //tmpItem.Caption := tmpdataset.fieldbyname('lvol0').AsString;//
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);//�ͻ���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);//����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString); //ѧ����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);//�ͻ�����
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lsafe_level2').AsString));//�ͻ����
    tmpItem.SubItems.Add(GetIdObjectName(-56,tmpdataset.fieldbyname('lsafe_level').AsString));//�����
    tmpItem.SubItems.Add(GetIdObjectName(17,tmpdataset.fieldbyname('sserial0').AsString));//��״̬
    tmpdataset.Next;
  end;
end;

procedure TfaqhSetGateMgrOpen.btnQueryClick(Sender: TObject);
var
  i,j:Integer;
  cardUse,operType:Integer;
  cardNo,devNo:Integer;
  errList:TStrings;
begin
  if cbbUse.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ����;��');
    Exit;
  end;
  if cbbOperType.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��������');
    Exit;
  end;
  if selectAllotD(lvCard)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ����Ŀ���');
    Exit;
  end;
  if selectAllotD(lvEqu)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ������Ž��豸��');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ����ѡ��Ŀ����Ž��豸��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  cardUse := StrToInt(Copy(cbbUse.Text,1,Pos('-',cbbUse.Text)-1));
  operType := StrToInt(Copy(cbbOperType.Text,1,Pos('-',cbbOperType.Text)-1));
  errList := nil;
  try
    errList := TStringList.Create;
    for i:= 0 to lvCard.Items.Count-1 do
    begin
      if lvCard.Items[i].Checked then
      begin
        cardNo := StrToInt(lvCard.Items[i].SubItems[1]);
        //ShowMessage(IntToStr(cardNo));
        for j := 0 to lvEqu.Items.Count-1 do
        begin
          if lvEqu.Items[j].Checked then
          begin
            devNo := StrToInt(lvEqu.Items[j].SubItems[0]);
            //ShowMessage(IntToStr(devNo));
            WorkView2.FieldByName('����;').Data.SetInteger(cardUse);
            WorkView2.FieldByName('�������').Data.SetInteger(operType);

            WorkView2.FieldByName('����').Data.SetInteger(cardNo);
            WorkView2.FieldByName('�豸��').Data.SetInteger(devNo);
            WorkView2.FieldByName('������־').Data.SetString('U');
            try
              WVRequest2.SendCommand;
            except
              on e:Exception do
              begin
                errList.Add('���ţ�['+inttostr(cardNo)+'],�豸��:['+inttostr(devNo)+']����ʧ�ܣ�ԭ��:'+e.Message);
              end;
            end;
          end;
        end;
      end;
    end;
    if errList.Count>0 then
      if dlgSave1.Execute then
        errList.SaveToFile(dlgSave1.FileName+'.txt');
    Context.GetDialogSystem.ShowMessage('���ó���������ɣ�');
  finally
    errList.Destroy;
  end;
end;

function TfaqhSetGateMgrOpen.selectAllotD(lv: TListView): Integer;
var
  i:Integer;
begin
  for i:= 0 to lv.Items.Count-1 do
  begin
    if lv.Items[i].Checked then
    begin
      Result := 0;
      Exit;
    end;
  end;
  Result := -1;
end;

procedure TfaqhSetGateMgrOpen.chkCustAllClick(Sender: TObject);
var
  i:Integer;
begin
  if chkCustAll.Checked = True then
  begin
    for i := 0 to lvCard.Items.Count - 1 do
    begin
      lvCard.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvCard.Items.Count - 1 do
    begin
      lvCard.Items[i].Checked := False;
    end;
  end;
end;

procedure TfaqhSetGateMgrOpen.chkDevallClick(Sender: TObject);
var
  i:Integer;
begin
  if chkDevall.Checked = True then
  begin
    for i := 0 to lvEqu.Items.Count - 1 do
    begin
      lvEqu.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvEqu.Items.Count - 1 do
    begin
      lvEqu.Items[i].Checked := False;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('��������������',TfaqhSetGateMgrOpen);

end.
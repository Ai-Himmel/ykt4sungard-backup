unit UApubAuthCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzRadGrp, RzEdit,
  UIncrementComboBox, RzStatus, Buttons, UtCardDll;

type
  TfaqhpubAuthCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    rzchckgrp1: TRzCheckGroup;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp1: TGroupBox;
    WVComboBox3: TWVComboBox;
    edtLimitDate: TRzEdit;
    Label2: TLabel;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    btnPubAuth: TBitBtn;
    procedure btnPubAuthClick(Sender: TObject);
  private

    { Private declarations }
  OperatorNoName:string;
  function getAuthLimit: Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhpubAuthCard: TfaqhpubAuthCard;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhpubAuthCard.Init;
begin
  inherited;
  {
  WorkView.FieldByName('����Ա��').DefaultValue := '';
  WorkView.FieldByName('������').DefaultValue := '';
  WorkView.FieldByName('��Ȩ��Ȩ��').DefaultValue := 0;
  WorkView.FieldByName('���׿���').DefaultValue := 0;
  WorkView.FieldByName('ҵ�����Ա').DefaultValue := '';
  WorkView.FieldByName('��Ч��').DefaultValue := '';
  WorkView.Reset;
  }
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  btnQuery.Caption:='������Ȩ��';
  edtLimitDate.Text:=FormatDateTime('yyyymmdd',Date()+365);
end;

function TfaqhpubAuthCard.getAuthLimit: Integer;
var
  ss,i:Integer;
  chkValue:Integer;
begin
  ss:=0;
  for i := 0 to rzchckgrp1.Items.Count-1 do
  begin
    if rzchckgrp1.ItemChecked[i] then
    begin
      chkValue := 1 shl i;
      ss := ss or chkValue;
    end;
  end;
  Result := ss;
end;

procedure TfaqhpubAuthCard.btnPubAuthClick(Sender: TObject);
var
  CardManage: TCardManage;
  Pcardid:string;
  mainKey:string;
  cardLimit:Integer;
  limitDate:string;
  cardNo:Integer;
  operCode:string;
  operName:string;
  iIniAuthCard:Integer;
  iPubAuthCard:Integer;
  tempStr: PChar;
  tempArr: array[0..8] of char;
  tempErr: string;
  PCM: TPublishCardMes;
  sErrInfo:string;
begin
  CardManage:=nil;
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
    Exit;
  end;
  if getAuthLimit=0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ����Ȩ����ӵ�е�Ȩ��!');
    exit;
  end;
  try
    CardManage:=Tcardmanage.Create();
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      context.GetDialogSystem.ShowWarning('�������к�ʧ�ܣ�');
      exit;
    end;
    WorkView.FieldByName('��Ȩ��Ȩ��').Data.SetInteger(getAuthLimit);
    WorkView.FieldByName('ҵ�����Ա').Data.SetString(OperatorNoName);
    WorkView.FieldByName('������').Data.SetString(PCardID);
    WorkView.FieldByName('��Ч��').Data.SetString(Trim(edtLimitDate.Text));
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger=0 then
    begin
      mainKey:=WorkView.fieldbyname('������Կ').Data.AsString;
      cardLimit:=WorkView.fieldbyname('��Ȩ��Ȩ��').Data.AsInteger;
      cardNo:=WorkView.fieldbyname('���׿���').Data.AsInteger;
      limitDate:=WorkView.fieldbyname('��Ч��').Data.AsString;
      operCode:=WorkView.fieldbyname('����Ա��').Data.AsString;
      operName:=WorkView.fieldbyname('����Ա����').Data.AsString;
      tempErr := '';
      ZeroMemory(@tempArr, 8);
      tempStr := @tempArr;
      CardManage.ConvertHexStrToPChar(mainKey, 16, tempStr, tempErr);
      sErrInfo := '�뵽��Ȩ�������аѸ���Ȩ���޿����գ�Ȼ�����·��У�';
      if tempErr <> '' then
      begin
        Context.GetDialogSystem.ShowMessage('ת��ʧ��--'+tempErr+sErrInfo);
        Exit;
      end;
      iIniAuthCard := CardManage.InitNewAuthCard(tempStr,cardLimit);
      if iIniAuthCard<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('��ʼ����Ȩ��ʧ��--'+sErrInfo);
        Exit;
      end;
      strcopy(@PCM.CardNo, PChar(IntToStr(cardNo)));         //���׿���
      strcopy(@PCM.DeadLineDate, PChar(limitDate));          //��ֹ����
      strcopy(@PCM.ucLibraryNo, PChar(operCode));            //����Ա��
      strcopy(@PCM.ucName, PChar(operName));                 //����Ա����

      iPubAuthCard := CardManage.PublishAuthCard(pcm);
      if iPubAuthCard<>0 then
        Context.GetDialogSystem.ShowMessage('������Ȩ��ʧ��--'+sErrInfo)
      else
        Context.GetDialogSystem.ShowMessage('������Ȩ���ɹ���');
    end;
  finally
    CardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('������Ȩ��',TfaqhpubAuthCard);

end.
unit UACardDestory;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, UtCardDll;

type
  TfaqhCardDestory = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    btnRenewCard: TBitBtn;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVRCardDestory: TWVRequest;
    WVCardDestory: TWorkView;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    Label4: TLabel;
    edtCardNo: TWVEdit;
    btnReadCardNo: TBitBtn;
    WVEdit4: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnRenewCardClick(Sender: TObject);
    procedure btnReadCardNoClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
  private
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardDestory: TfaqhCardDestory;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardDestory.Init;
begin
  inherited;
end;

procedure TfaqhCardDestory.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardDestory.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('Ǯ����').Data.SetInteger(1);
  inherited;
end;

procedure TfaqhCardDestory.btnRenewCardClick(Sender: TObject);
var
  cardBalance: Integer; //Ԫ���֡��������ַ���
  CardID: integer;
  AccUseNum: integer; //�ͻ��� ����
  CardState: string;
  CardExID, CardPhyID: string;
  CardManage: TCardManage;
  TOF: boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  ResInt: SmallInt;
  ResInt2: longint;
  patchNo:Integer;//�������κ�

  tmpData:TDataSet;
  custName:string;
  money:Real;
  totMoney:Real;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('û�����ݣ��޷����д˲�����');
    Exit;
  end;
  if PrepareReadCardInfo=False then
    Exit;
  //�ж��Ƿ���������
  CardState := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    if Copy(CardState,1,4) = '1000' then             
    begin
      //��������
      if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
      begin
        Context.GetDialogSystem.ShowMessage('��ȡ�������ʧ��,�뽫�����ڶ�д���ϣ�');
        Exit;
      end
      else
        WVCardDestory.FieldByName('��������').Data.SetString(CardPhyID);

      ResInt := CardManage.ReadExCardID(CardExID);
      if ResInt <> 0 then
      begin
        Context.GetDialogSystem.ShowMessage('��ȡ���Ŵ��󣬴�����--'+inttostr(ResInt));
        Exit;
      end;

      //�ȽϿ����Ƿ����
      CardID := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
      if CardID <> StrToInt(CardExID) then
      begin
        Context.GetDialogSystem.ShowMessage('�ÿ��Ŀ��ź���ѡ���¼�Ŀ��Ų���������ܽ����˿�������');
        Exit;
      end;

      TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo); //��ȡ������Ϣ
      if TOF = False then
      begin
        Context.GetDialogSystem.ShowMessage('���û���������Ϣʧ�ܣ�');
        CardManage.Destroy;
        Exit;
      end
      else
      begin
        cardBalance := StrToInt(format('%d', [LPI.RemainMoney]));
        AccUseNum:=StrToInt(format('%d', [LPI.DealTimes]));
        patchNo := StrToInt(Format('%d',[LPI.DealTimes_CurDay]))
      end;
      WVCardDestory.FieldByName('�����').Data.SetInteger(cardBalance);
      WVCardDestory.FieldByName('����').Data.SetInteger(CardID);
      WVCardDestory.FieldByName('���״���').Data.SetInteger(AccUseNum);
      WVCardDestory.FieldByName('�������κ�').Data.SetInteger(patchNo);
      WVCardDestory.FieldByName('�Ƿ��п�').Data.SetInteger(1);
    end
    else
    begin
      CardID := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
      WVCardDestory.FieldByName('����').Data.SetInteger(CardID);
      WVCardDestory.FieldByName('�����').Data.SetInteger(0);
      WVCardDestory.FieldByName('��������').Data.SetString('');
      WVCardDestory.FieldByName('���״���').Data.SetInteger(0);
      WVCardDestory.FieldByName('�������κ�').Data.SetInteger(0);
      WVCardDestory.FieldByName('�Ƿ��п�').Data.SetInteger(0);
    end;

    //�����Ƿ��˿�Ѻ��Ϳ�����ж�
    {
    frmBackCardOper := TfrmBackCardOper.Create(nil);
    frmBackCardOper.ShowModal;
    if frmBackCardOper.iType=0 then
    begin
      frmBackCardOper.Close;
      frmBackCardOper.Free;
      Exit;
    end;
    iYJ := frmBackCardOper.rgyj.ItemIndex;
    iJD := StrToInt(Copy(frmBackCardOper.cbbType.Text,1,Pos('-',frmBackCardOper.cbbType.Text)-1));
    frmBackCardOper.Close;
    frmBackCardOper.Free;
    //----------------------------------------------------------------------------
    }
    if Copy(CardState,1,4) = '1000' then
    begin
      ResInt := CardManage.ReadExCardID(CardExID);
      if ResInt<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('�ڻ��չ������벻Ҫ�ѿ����ߣ�');
        Exit;
      end;
    end;
    WVCardDestory.FieldByName('����').Data.SetInteger(0);
    WVCardDestory.FieldByName('�Ƿ���Ѻ��').Data.SetInteger(0);

    //ShowWaiting(SWaitingOperation);
    WVRCardDestory.SendCommand;
    if WVCardDestory.FieldByName('������').Data.AsInteger = 0 then
    begin
      if (Copy(CardState,1,4) = '1000') then
      begin
        try
          ResInt2 := CardManage.ClearCard;
          if ResInt2=0 then
            CardManage.ControlBuzzer
          else
            Context.GetDialogSystem.ShowMessage('���˿�ʱû����տ���Ϣ��');
        except
          Context.GetDialogSystem.ShowMessage('���˿�ʱû����տ���Ϣ��');
        end;
      end
      else
        ConText.GetDialogSystem.ShowWarning('���˿�ʱû����տ���Ϣ��');

      if bjopen=1 then
        try
          tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
          custName := tmpData.fieldbyname('sall_name').AsString;
          money := tmpData.fieldbyname('damt5').AsFloat;
          bj(bjcomport,'&Sc$');
          bj(bjcomport,'&C11��  ����'+trim(custName)+'$');
          bj(bjcomport,'&C21�����:'+floattostr(money)+'Ԫ$');
          try
            totMoney := WVCardDestory.fieldbyname('�˿���').Data.AsFloat;
          except
            totMoney := money;
          end;
          bj(bjcomport,'&C31���˿�:'+floattostr(totMoney)+'Ԫ$');
        except
        end;

      ShowMessage(WVCardDestory.FieldByName('������Ϣ').Data.AsString);
      RzStatusPane1.caption:=WVCardDestory.FieldByName('������Ϣ').Data.AsString;
    end
    else
    begin
      getReturn('�ջؿ�ʧ��--',WVCardDestory);
      RzStatusPane1.caption:=WVCardDestory.FieldByName('������Ϣ').Data.AsString;
    end;
    //CloseWaiting;
    btnQueryClick(Sender);
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhCardDestory.btnReadCardNoClick(Sender: TObject);
begin
  edtCardNo.Text:=readCardNo;
  btnQuery.Click();
end;

procedure TfaqhCardDestory.GridCellClick(Column: TColumn);
var
  tmpData:TDataSet;
  custName:string;
  money:Real;
begin
  //inherited;
  if bjopen=1 then
    try
      tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
      custName := tmpData.fieldbyname('sall_name').AsString;
      money := tmpData.fieldbyname('damt5').AsFloat;
      bj(bjcomport,'W');
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'&C11��  ����'+trim(custName)+'$');
      bj(bjcomport,'&C21�����:'+floattostr(money)+'Ԫs$');
    except
    end;
end;

initialization
  TUIStdClassFactory.Create('һ��ͨ����', TfaqhCardDestory);

end.



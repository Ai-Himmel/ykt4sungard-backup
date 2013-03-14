unit UACPUCollTrade;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVDBBinders, Db, 
  RzDBGrid, ComCtrls, RzListVw, CardDll, Buttons;

type
  TfaqhCPUCollTrade = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnUpLoad: TBitBtn;
    lvSerial: TRzListView;
    pb1: TProgressBar;
    stat1: TStatusBar;
    btnClear: TBitBtn;
    chkSelectAll: TCheckBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
    procedure btnUpLoadClick(Sender: TObject);
  private

    { Private declarations }
    cpuCardNo:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCPUCollTrade: TfaqhCPUCollTrade;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhCPUCollTrade.Init;
begin
  inherited;
end;

procedure TfaqhCPUCollTrade.btnQueryClick(Sender: TObject);
var
  paydtl:TPAYDTL;
  st:Integer;
  phyId:string;
  cm:TCM;
  i:Integer;
  errList:TStringList;
  tmpItem: TListItem;
  cardNo:string;
begin
  if not preReadCard then
    Exit;
  cm := nil;
  errList := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    errList := TStringList.Create;
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('����ʧ�ܣ���ѿ����ú����ԣ�');
      Exit;
    end;
    cardNo := readCardOneInfo(CARD_NO);
    if cardNo='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����ʧ�ܣ��ÿ�Ϊ�տ������𻵣�');
      Exit;
    end
    else
      cpuCardNo := StrToInt(cardNo);
    lvSerial.Items.Clear;
    pb1.Max := 50;
    pb1.Position := 0;
    for i := 1 to 50 do
    begin
      //preReadPayDtl(paydtl);
      ZeroMemory(@paydtl,SizeOf(paydtl));
      st:= ks_readpaydtl(i,@paydtl);
      if st = 0 then
      begin
        if paydtl.exist>0 then
        begin
          tmpItem := lvSerial.Items.Add;
          //��Ӽ�¼���б���
          tmpItem.Caption := IntToStr(paydtl.recordno);             //���
          tmpItem.SubItems.Add(paydtl.transdate);                   //��������
          tmpItem.SubItems.Add(paydtl.transtime);                   //����ʱ��
          tmpItem.SubItems.Add(IntToStr(paydtl.paycnt));            //���״���
          tmpItem.SubItems.Add(IntToStr(paydtl.cardbefbal));        //����ǰ���
          tmpItem.SubItems.Add(IntToStr(paydtl.transamt));          //���׽��
          tmpItem.SubItems.Add(IntToStr(paydtl.otherfee));          //����
          tmpItem.SubItems.Add(IntToStr(paydtl.extamt));            //��д���
          tmpItem.SubItems.Add(IntToStr(paydtl.shopid));            //�̻���
          tmpItem.SubItems.Add((paydtl.termno));                    //�ն˱��
          tmpItem.SubItems.Add(IntToStr(paydtl.termsno));           //�������
        end;
      end
      else
      begin
        //����ʧ�ܼ�¼��
        errList.Add('��¼��Ϊ['+inttostr(i)+']������ˮ��ȡʧ��--'+inttostr(st));
      end;
      pb1.Position := pb1.Position + 1;
    end;
    Context.GetDialogSystem.ShowMessage('��ȡ������ˮ��ɣ�');


  finally
    cm.Destroy;
    errList.Destroy;
  end;
end;

procedure TfaqhCPUCollTrade.btnClearClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ��ղɼ���¼��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  lvSerial.Items.Clear;
end;

procedure TfaqhCPUCollTrade.chkSelectAllClick(Sender: TObject);
var
  i: integer;
begin
  if lvSerial.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelectAll.Checked = True then
  begin
    for i := 0 to lvSerial.Items.Count - 1 do
    begin
      lvSerial.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvSerial.Items.Count - 1 do
    begin
      lvSerial.Items[i].Checked := False;
    end;
  end;
end;

procedure TfaqhCPUCollTrade.btnUpLoadClick(Sender: TObject);
var
  i:Integer;
begin
  if lvSerial.Items.Count=0 then
    Exit;
  pb1.Max := lvSerial.Items.Count-1;
  pb1.Position := 0;
  for i := 0 to lvSerial.Items.Count-1 do
  begin
    pb1.Position := pb1.Position+1;
    if lvSerial.Items[i].Checked then
    begin
      WorkView.FieldByName('վ���').Data.SetInteger(StrToInt(scSiteNo));
      WorkView.FieldByName('����').Data.SetInteger(cpuCardNo);
      WorkView.FieldByName('���ױ�־').Data.SetInteger(2);
      WorkView.FieldByName('���Ѵ���').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[2])));
      WorkView.FieldByName('��������').Data.SetString(lvSerial.Items[i].SubItems[0]);
      WorkView.FieldByName('����ʱ��').Data.SetString(lvSerial.Items[i].SubItems[1]);
      WorkView.FieldByName('����ǰ���').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[3])));
      WorkView.FieldByName('���׽��').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[4])));
      WorkView.FieldByName('����').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[5])));
      WorkView.FieldByName('��д���').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[6])));
      WorkView.FieldByName('�̻���').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[7])));
      WorkView.FieldByName('�ն˱��').Data.SetString(lvSerial.Items[i].SubItems[8]);
      WorkView.FieldByName('�������').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[9])));
      MainRequest.SendCommand;
    end;
    pb1.Position := 100;
  end;
  Context.GetDialogSystem.ShowMessage('�ϴ�������ˮ��ɣ�');
end;

initialization
  TUIStdClassFactory.Create('����ˮ�ɼ�',TfaqhCPUCollTrade);

end.
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
      Context.GetDialogSystem.ShowMessage('读卡失败，请把卡放置好重试！');
      Exit;
    end;
    cardNo := readCardOneInfo(CARD_NO);
    if cardNo='' then
    begin
      Context.GetDialogSystem.ShowMessage('读取卡号失败，该卡为空卡或已损坏！');
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
          //添加记录到列表中
          tmpItem.Caption := IntToStr(paydtl.recordno);             //序号
          tmpItem.SubItems.Add(paydtl.transdate);                   //交易日期
          tmpItem.SubItems.Add(paydtl.transtime);                   //交易时间
          tmpItem.SubItems.Add(IntToStr(paydtl.paycnt));            //交易次数
          tmpItem.SubItems.Add(IntToStr(paydtl.cardbefbal));        //交易前金额
          tmpItem.SubItems.Add(IntToStr(paydtl.transamt));          //交易金额
          tmpItem.SubItems.Add(IntToStr(paydtl.otherfee));          //搭伙费
          tmpItem.SubItems.Add(IntToStr(paydtl.extamt));            //补写金额
          tmpItem.SubItems.Add(IntToStr(paydtl.shopid));            //商户号
          tmpItem.SubItems.Add((paydtl.termno));                    //终端编号
          tmpItem.SubItems.Add(IntToStr(paydtl.termsno));           //交易序号
        end;
      end
      else
      begin
        //读卡失败记录号
        errList.Add('记录号为['+inttostr(i)+']消费流水读取失败--'+inttostr(st));
      end;
      pb1.Position := pb1.Position + 1;
    end;
    Context.GetDialogSystem.ShowMessage('读取消费流水完成！');


  finally
    cm.Destroy;
    errList.Destroy;
  end;
end;

procedure TfaqhCPUCollTrade.btnClearClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要清空采集记录吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
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
      WorkView.FieldByName('站点号').Data.SetInteger(StrToInt(scSiteNo));
      WorkView.FieldByName('卡号').Data.SetInteger(cpuCardNo);
      WorkView.FieldByName('交易标志').Data.SetInteger(2);
      WorkView.FieldByName('消费次数').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[2])));
      WorkView.FieldByName('交易日期').Data.SetString(lvSerial.Items[i].SubItems[0]);
      WorkView.FieldByName('交易时间').Data.SetString(lvSerial.Items[i].SubItems[1]);
      WorkView.FieldByName('交易前余额').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[3])));
      WorkView.FieldByName('交易金额').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[4])));
      WorkView.FieldByName('搭伙费').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[5])));
      WorkView.FieldByName('补写金额').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[6])));
      WorkView.FieldByName('商户号').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[7])));
      WorkView.FieldByName('终端编号').Data.SetString(lvSerial.Items[i].SubItems[8]);
      WorkView.FieldByName('交易序号').Data.SetInteger(strtoint(strtozero(lvSerial.Items[i].SubItems[9])));
      MainRequest.SendCommand;
    end;
    pb1.Position := 100;
  end;
  Context.GetDialogSystem.ShowMessage('上传消费流水完成！');
end;

initialization
  TUIStdClassFactory.Create('卡流水采集',TfaqhCPUCollTrade);

end.
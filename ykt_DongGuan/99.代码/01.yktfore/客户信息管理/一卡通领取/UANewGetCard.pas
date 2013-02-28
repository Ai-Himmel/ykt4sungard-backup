unit UANewGetCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  jpeg, RM_Class, RM_Common;

type
  TfaqhGetCardNew = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtCustNo: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit11: TWVEdit;
    edtAppNo: TWVEdit;
    cbbDept: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    chkPrint: TCheckBox;
    btnReadCard: TBitBtn;
    btnGetCard: TBitBtn;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    imgPhoto: TImage;
    procedure btnQueryClick(Sender: TObject);
    procedure btnGetCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
    endGetPhotoSign:Boolean;
    procedure getPhoto;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhGetCardNew: TfaqhGetCardNew;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,filetrans,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhGetCardNew.Init;
var
  filePath:string;
begin
  inherited;
  {
  WorkView.FieldByName('客户号').DefaultValue := 0;
  WorkView.FieldByName('姓名').DefaultValue := '';
  WorkView.FieldByName('证件类型').DefaultValue := '';
  WorkView.FieldByName('证件号码').DefaultValue := '';
  WorkView.FieldByName('发卡部门').DefaultValue := '';
  WorkView.FieldByName('电话').DefaultValue := '';
  WorkView.FieldByName('手机').DefaultValue := '';
  WorkView.FieldByName('卡号').DefaultValue := '';
  WorkView.FieldByName('卡物理编号').DefaultValue := '';
  WorkView.FieldByName('卡类型').DefaultValue := 0;
  WorkView.FieldByName('制卡日期').DefaultValue := '';
  WorkView.FieldByName('发行批次号').DefaultValue := 0;
  WorkView.Reset;
  }
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    endGetPhotoSign := True;
    filePath := sAppPath+'nophoto.jpg';
    imgPhoto.Picture.LoadFromFile(filePath);
  except

  end;
end;

procedure TfaqhGetCardNew.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  btnGetCard.Enabled := False;
  WorkView.FieldByName('查询类别').Data.SetString('1');
  inherited;
  btnGetCard.Enabled := True;
end;

procedure TfaqhGetCardNew.btnGetCardClick(Sender: TObject);
var
  custId:Integer;
  cardNo:string;
  cm: TCM;
  st:integer;
  phyId,appSerialNo:string;
  loDate,loTime:string;
  payCnt,DptCnt,cardBal:Integer;
  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
begin
  if not preReadCard then
    Exit;
  if Application.MessageBox('你确定要进行领卡操作吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请先放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CF_APPSERIALNO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(DPT_CARD_CNT);

    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败-'+geterrmsg);
      Exit;
    end;
    appSerialNo := cm.getAppSerialNo;
    payCnt := StrToInt(cm.getPayCardCnt);
    DptCnt := StrToInt(cm.getDptCardCnt);
    cardBal := StrToInt(cm.getCardBalance);
  finally
    cm.Destroy;
  end;
  loDate := FormatDateTime('yyyymmdd',Date);
  loTime := FormatDateTime('hhmmss',Now);
  custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  cardNo := Grid.DataSource.DataSet.fieldbyname('scard0').AsString;
  custName := Grid.DataSource.DataSet.fieldbyname('snote').AsString;
  phoneNo := Grid.DataSource.DataSet.fieldbyname('sphone2').AsString;
  WorkView1.FieldByName('操作标志').Data.SetString('G');
  WorkView1.FieldByName('卡号').Data.SetString(cardNo);
  WorkView1.FieldByName('客户号').Data.SetInteger(custId);
  WorkView1.FieldByName('预交款').Data.SetFloat(0);
  WorkView1.FieldByName('卡序列号').Data.SetString(appSerialNo);
  WorkView1.FieldByName('psam卡号').Data.SetString(psamTermId);
  WorkView1.FieldByName('本机流水号').Data.SetString(loTime);
  WorkView1.FieldByName('本机日期').Data.SetString(loDate);
  WorkView1.FieldByName('本机时间').Data.SetString(loTime);
  WorkView1.FieldByName('卡物理编号').Data.SetString(phyId);
  WorkView1.FieldByName('网点号').Data.SetString(scSiteNo);
  WorkView1.FieldByName('充值次数').Data.SetInteger(DptCnt);
  WorkView1.FieldByName('消费次数').Data.SetInteger(payCnt);
  WorkView1.FieldByName('卡余额').Data.SetInteger(cardBal);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger<>0 then
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('返回信息').Data.AsString)
  else
  begin
    Context.GetDialogSystem.ShowMessage('领卡成功！');
    rptReport := nil;
    if chkPrint.Checked then
    begin
      try
        try
          serialNo := WorkView1.fieldbyname('交易流水').Data.AsString;
          cardType := WorkView1.fieldbyname('卡类型').Data.AsString;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
          rptReport.Dictionary.Variables.AsString['custName'] := custName;
          rptReport.Dictionary.Variables.AsString['titleType'] := '实名卡发卡';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
          rptReport.Dictionary.Variables.AsString['cardNo'] := cardNo;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '卡内余额：';
          rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [cardBal / 100.0])+'元';
          rptReport.Dictionary.Variables.AsString['param2'] := '发卡时间：';
          rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.Dictionary.Variables.AsString['param3'] := '';
          rptReport.Dictionary.Variables.AsString['pValue3'] := '';
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\getcard.rmp');
          if showrpt=1 then
            rptReport.ShowReport
          else
            rptReport.PrintReport;
        except
          Context.GetDialogSystem.ShowMessage('你没有安装打印机，不能打印！');
        end;
      finally
        rptReport.Free;
      end;
    end;
  end;
end;

procedure TfaqhGetCardNew.getPhoto;
var
  dFile:string;
  ret:Integer;
  custNo:string;
begin
  if showphoto=0 then
    Exit;
  //查询照片前先清空以前的照片信息
  imgPhoto.Picture := nil;

  if endGetPhotoSign=false then
    Exit;
  try
    //从后台取得照片的名称，照片名为客户号
    custNo := Grid.DataSource.DataSet.fieldbyname('lvol0').asstring;
  except
    Context.GetDialogSystem.ShowMessage('请先选择一条记录，然后再取照片！');
    Exit;
  end;
  dFile := 'photo999999.jpg';
  try
    try
      endGetPhotoSign:=false;
      ret := KSG_Downloadphoto_File(custNo,dFile);
      if ret = KSG_SUCCESS then
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+dFile);
      end
      else
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
        //Context.GetDialogSystem.ShowMessage('该客户没有照片信息-'+inttostr(ret));
        Exit;
      end;
    except
      on e:Exception do
      begin        
        Context.GetDialogSystem.ShowMessage('下载照片信息失败，该客户可能没有拍照-'+e.Message);
        Exit;
      end;
    end;
  finally
    endGetPhotoSign:=True;
  end;
  //加载照片完成后删除
  //在本地查找是否存在dFile的照片，存在则删除
  try
    if FileExists(sAppPath+dFile) then
      DeleteFile(sAppPath+dFile);
  except
    //WriteLog('删除 photo999999.jpg 失败，该文件不存在！');
  end;
end;

procedure TfaqhGetCardNew.GridCellClick(Column: TColumn);
begin
  inherited;
  getPhoto;
end;

procedure TfaqhGetCardNew.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppNo.Text:='';
  try
    cardNo := readCardOneInfo(CF_APPSERIALNO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，应用序列号为零或不存在!');
    Exit;
  end;
  edtAppNo.Text:=cardNo;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhGetCardNew.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\getcard.rmp');
end;

initialization
  TUIStdClassFactory.Create('一卡通领取',TfaqhGetCardNew);

end.
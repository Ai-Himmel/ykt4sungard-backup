unit UAIntegeralPay;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  RzStatus,RM_Class, RzPanel, RzRadGrp,CardDll,HTTPApp, IdBaseComponent,
  IdComponent, IdTCPConnection, IdTCPClient, IdHTTP,NativeXml, RzEdit,
  EditExts;

type
  TfaqIntegeralPay = class(TfaqhSimpleQueryTemp)
    rzstspnInfo: TRzStatusPane;
    rgType: TRzRadioGroup;
    RzGroupBox1: TRzGroupBox;
    btnPayFee: TBitBtn;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    lblOldSerial: TLabel;
    lblTradeSerial: TLabel;
    lblInfo: TLabel;
    idhtp1: TIdHTTP;
    RzGroupBox2: TRzGroupBox;
    lbl5: TLabel;
    lbl6: TLabel;
    edtMoney: TEdit;
    procedure btnPayFeeClick(Sender: TObject);
  private

    { Private declarations }
    FXmlDoc:TNativeXml;
  public
    procedure Init; override;
    //destructor Destroy; override;
    { Public declarations }
  end;

var
  faqIntegeralPay: TfaqIntegeralPay;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, UCommon, Contnrs,
     KSClientConsts,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqIntegeralPay.Init;
begin
  inherited;
  //lblPhone.Caption := '';
  lblOldSerial.Caption := '';
  lblTradeSerial.Caption := '';
  lblInfo.Caption := '';
end;

procedure TfaqIntegeralPay.btnPayFeeClick(Sender: TObject);
var
  cardNo:string;
  
  respsm:TStringStream;
  AList:TStrings;
  testList:TStringList;
  tmpStream:TStream;
  tmpStr:string;
  reCode,reInfo:string;
  reqSerType:string;
  payMoney:string;
begin
  //lblPhone.Caption := '';
  lblOldSerial.Caption := '';
  lblTradeSerial.Caption := '';
  lblInfo.Caption := '';
  if ifDebug=0 then
  begin
    if psamTermId='' then
    begin
      Context.GetDialogSystem.ShowMessage('请先打开串口，设置PSAM卡座！');
      Exit;
    end;
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
  end
  else
    cardNo := '11000000070157';

  try
    if StrToFloat(edtMoney.Text)<=0 then
    begin
      Context.GetDialogSystem.ShowMessage('请输入有效的支付金额！');
      edtMoney.SetFocus;
      Exit;
    end;
    if Round(StrToFloat(edtMoney.Text)*100)<>StrToFloat(edtMoney.Text)*100 then
    begin
      Context.GetDialogSystem.ShowMessage('支付金额只能精确到分！');
      edtmoney.SetFocus;
      Exit;
    end;
    payMoney := FloatToStr(StrToFloat(edtMoney.Text)*100);
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('支付金额输入不合法-'+e.Message);
      edtmoney.SetFocus;
      Exit;
    end;
  end;

  if Application.MessageBox('你确定要使用积分支付吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if rgType.ItemIndex=0 then
    reqSerType := yhjf
  else
  if rgType.ItemIndex=1 then
    reqSerType := gmjf
  else
  if rgType.ItemIndex=2 then
    reqSerType := ghwjf
  else
  if rgType.ItemIndex=3 then
    reqSerType := sjjf
  else
    reqSerType := '99';
  FXmlDoc:= TNativeXml.Create;
  AList:=TStringList.Create;
  testList := TStringList.Create;
  AList.Append(createDptXML(dpt_ID,reqSerType,payMoney,cardNo,'')); //cardNo
  //AList.SaveToFile('c:\test.xml');//-------------------------------测试
  respsm:=TStringStream.Create('');
  tmpStream := TStringStream.Create('');
  idhtp1.Request.ContentType:='application/x-www-form-urlencoded';

  try
    try
      idhtp1.Post(REQIP,AList,respsm);
      tmpStr := respsm.DataString;
      tmpStr := (HTTPDecode(tmpStr));
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(e.Message);
        Exit;
      end;
    end;
    testList.Add((Copy(tmpStr,9,Length(tmpStr)-1)));
    //testList.SaveToFile(appPath+'test.xml');
    try
      testList.SaveToStream(tmpStream);
      FXmlDoc.XmlFormat:=xfReadable;
      FXmlDoc.LoadFromStream(tmpStream);
      reCode := FXmlDoc.Root.findnode('/resp/respCode').ValueAsString;
      reInfo := sdUtf8ToAnsi(FXmlDoc.Root.findnode('/resp/respDesc').ValueAsString);
      if reCode<>normalCode then
      begin
        Context.GetDialogSystem.ShowMessage(reInfo);
        rzstspnInfo.Caption := reCode+'-'+reInfo;
        Exit;
      end;
      if reCode=normalCode then
      begin
        //开始写最后冲正流水号
        WriteLastSerial(reqSerType,FXmlDoc.Root.findnode('/resp/transId').ValueAsString);
      end;
      //lblPhone.Caption := FXmlDoc.Root.findnode('/resp/mobile').ValueAsString;
      lblOldSerial.Caption := FXmlDoc.Root.findnode('/resp/transId').ValueAsString;
      lblTradeSerial.Caption := FXmlDoc.Root.findnode('/resp/platSeq').ValueAsString;
      lblInfo.Caption := sdUtf8ToAnsi(FXmlDoc.Root.findnode('/resp/printDesc').ValueAsString);
    except
      on e:Exception do
        Context.GetDialogSystem.ShowMessage(e.Message);
    end;
  finally
    respsm.Free;
    AList.Free;
    testList.Free;
    tmpStream.Free;
    FXmlDoc.Free;
  end;

end;
{
destructor TfaqIntegeralPay.Destroy;
begin
  FXmlDoc.Free;
  inherited;

end;
}
initialization
  TUIStdClassFactory.Create('积分支付',TfaqIntegeralPay);

end.
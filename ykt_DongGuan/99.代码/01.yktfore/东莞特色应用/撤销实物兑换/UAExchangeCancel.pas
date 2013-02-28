unit UAExchangeCancel;

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
  TfaqExchangeCancel = class(TfaqhSimpleQueryTemp)
    rzstspnInfo: TRzStatusPane;
    rgExType: TRzRadioGroup;
    RzGroupBox1: TRzGroupBox;
    btnPayFee: TBitBtn;
    lbl1: TLabel;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    lblPhone: TLabel;
    lblOldSerial: TLabel;
    lblTradeSerial: TLabel;
    lblInfo: TLabel;
    idhtp1: TIdHTTP;
    Label1: TLabel;
    Label2: TLabel;
    edtMInfo: TEdit;
    procedure btnPayFeeClick(Sender: TObject);
    procedure rgExTypeClick(Sender: TObject);
  private

    { Private declarations }
    FXmlDoc:TNativeXml;
  public
    procedure Init; override;
    //destructor Destroy; override;
    { Public declarations }
  end;

var
  faqExchangeCancel: TfaqExchangeCancel;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, UCommon, Contnrs,
     KSClientConsts,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqExchangeCancel.Init;
begin
  inherited;
  lblPhone.Caption := '';
  lblOldSerial.Caption := '';
  lblTradeSerial.Caption := '';
  lblInfo.Caption := '';
  FXmlDoc:= TNativeXml.Create;
end;

procedure TfaqExchangeCancel.btnPayFeeClick(Sender: TObject);
var
  cardNo,uuId:string;

  respsm:TStringStream;
  AList:TStrings;
  testList:TStringList;
  tmpStream:TStream;
  tmpStr:string;
  reCode,reInfo:string;
  reqSerType:string;
  //payMoney:string;

  oriTransId:string;
begin
  lblPhone.Caption := '';
  lblOldSerial.Caption := '';
  lblTradeSerial.Caption := '';
  lblInfo.Caption := '';
  {
  if psamTermId='' then
  begin
    Context.GetDialogSystem.ShowMessage('请先打开串口，设置PSAM卡座！');
    Exit;
  end;
  }
  if rgExType.ItemIndex=0 then
  begin
    try
      cardNo := readCardOneInfo(CF_APPSERIALNO);
    except
      Exit;
    end;
    if (cardNo='') or (cardNo='0') then
    begin
      Context.GetDialogSystem.ShowMessage('读卡失败，应用序列号为零或不存在!');
      Exit;
    end;
    uuId := cardNo;
  end
  else
  begin
    uuId := Trim(edtMInfo.Text);
  end;

  if rgExType.ItemIndex = 0 then
    reqSerType := swdh_DC
  else
  if rgExType.ItemIndex =1 then
    reqSerType := swdh_DM
  else
    reqSerType := '99';
    
  if Application.MessageBox('你确定要撤销已经选中兑换的最后一笔交易吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  oriTransId := GetLastSerialNo(reqSerType);
  AList:=TStringList.Create;
  testList := TStringList.Create;
  AList.Append(createDptXML(exCancel_ID,reqSerType,'',uuId,oriTransId));
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
    testList.SaveToFile(appPath+'test.xml');
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
      {
      if reCode=normalCode then
      begin
        //撤销成功后，把当前流水号设置为空
        WriteLastSerial(reqSerType,FXmlDoc.Root.findnode('/resp/transId').ValueAsString);
      end;
      }
      lblPhone.Caption := FXmlDoc.Root.findnode('/resp/mobile').ValueAsString;
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
  end;

end;
{
destructor TfaqIntegeralPay.Destroy;
begin
  FXmlDoc.Free;
  inherited;

end;
}
procedure TfaqExchangeCancel.rgExTypeClick(Sender: TObject);
begin
  if rgExType.ItemIndex=0 then
  begin
    edtMInfo.Text := '';
    edtMInfo.ReadOnly := True;
  end
  else
    edtMInfo.ReadOnly := False;
end;

initialization
  TUIStdClassFactory.Create('撤销实物兑换',TfaqExchangeCancel);

end.
unit UAMemberIdentify;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  RzStatus,RM_Class, RzPanel, RzRadGrp,CardDll,HTTPApp, IdBaseComponent,
  IdComponent, IdTCPConnection, IdTCPClient, IdHTTP,NativeXml;

type
  TfaqMemberIdentify = class(TfaqhSimpleQueryTemp)
    rzstspnInfo: TRzStatusPane;
    RzGroupBox1: TRzGroupBox;
    btnQueryFee: TBitBtn;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    lblOldSerial: TLabel;
    lblTradeSerial: TLabel;
    lblInfo: TLabel;
    idhtp1: TIdHTTP;
    procedure btnQueryFeeClick(Sender: TObject);
  private

    { Private declarations }
    FXmlDoc:TNativeXml;
  public
    procedure Init; override;
    destructor Destroy; override;
    { Public declarations }
  end;

var
  faqMemberIdentify: TfaqMemberIdentify;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, UCommon, Contnrs,
     KSClientConsts,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqMemberIdentify.Init;
begin
  inherited;
  //lblPhone.Caption := '';
  lblOldSerial.Caption := '';
  lblTradeSerial.Caption := '';
  lblInfo.Caption := '';
end;


procedure TfaqMemberIdentify.btnQueryFeeClick(Sender: TObject);
var
  cardNo:string;
  
  respsm:TStringStream;
  AList:TStrings;
  testList:TStringList;
  tmpStream:TStream;
  tmpStr:string;
  reCode,reInfo:string;
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

  FXmlDoc:= TNativeXml.Create;
  AList:=TStringList.Create;
  testList := TStringList.Create;
  AList.Append(createDptXML(userQ_ID,hydj,'',cardNo,'')); //cardNo 11000000070157
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
      //lblPhone.Caption := FXmlDoc.Root.findnode('/resp/mobile').ValueAsString;
      lblOldSerial.Caption := FXmlDoc.Root.findnode('/resp/transId').ValueAsString;
      lblTradeSerial.Caption := FXmlDoc.Root.findnode('/resp/platSeq').ValueAsString;
      lblInfo.Caption := sdUtf8ToAnsi(FXmlDoc.Root.findnode('/resp/printDesc').ValueAsString);
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(e.Message);
      end;
    end;
  finally
    respsm.Free;
    AList.Free;
    testList.Free;
    tmpStream.Free;
    FXmlDoc.Free;
  end;

end;

destructor TfaqMemberIdentify.Destroy;
begin
  FXmlDoc.Free;
  inherited;

end;

initialization
  TUIStdClassFactory.Create('会员识别',TfaqMemberIdentify);

end.
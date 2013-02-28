unit UAExchangeGoods;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  RzStatus,RM_Class, RzPanel, RzRadGrp,CardDll,HTTPApp, IdBaseComponent,
  IdComponent, IdTCPConnection, IdTCPClient, IdHTTP,NativeXml, ComCtrls;

type
  TfaqExchangeGoods = class(TfaqhSimpleQueryTemp)
    rzstspnInfo: TRzStatusPane;
    rgExType: TRzRadioGroup;
    RzGroupBox1: TRzGroupBox;
    btnExchange: TBitBtn;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    lblOldSerial: TLabel;
    lblTradeSerial: TLabel;
    lblInfo: TLabel;
    idhtp1: TIdHTTP;
    btnInteQuery: TBitBtn;
    Label1: TLabel;
    edtMInfo: TEdit;
    RzGroupBox2: TRzGroupBox;
    lvGoods: TListView;
    Label2: TLabel;
    lblGoodsName: TLabel;
    procedure btnExchangeClick(Sender: TObject);
    procedure btnInteQueryClick(Sender: TObject);
    procedure rgExTypeClick(Sender: TObject);
    procedure lvGoodsClick(Sender: TObject);
  private

    { Private declarations }
    FXmlDoc:TNativeXml;
    selectItem:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqExchangeGoods: TfaqExchangeGoods;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, UCommon, Contnrs,
     KSClientConsts,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqExchangeGoods.Init;
begin
  inherited;
  //lblPhone.Caption := '';
  lblOldSerial.Caption := '';
  lblTradeSerial.Caption := '';
  lblInfo.Caption := '';
  lblGoodsName.Caption := '';
  selectItem := -1;
end;


procedure TfaqExchangeGoods.btnExchangeClick(Sender: TObject);
var
  cardNo,uuId:string;
  
  respsm:TStringStream;
  AList:TStrings;
  testList:TStringList;
  tmpStream:TStream;
  tmpStr:string;
  reCode,reInfo:string;
  //reqSerType:string;
  itemCode,itemName:string;
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
  end
  else
    uuId := '11000000070157';

  if lvGoods.Items.Count=0 then
  begin
    Context.GetDialogSystem.ShowMessage('没有要兑换的物品列表！');
    Exit;
  end;
  if selectItem<0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要兑换的物品！');
    Exit;
  end;
  if Application.MessageBox('你确定要兑换选中的物品吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  itemCode := lvGoods.Items.Item[selectItem].Caption;
  itemName := lvGoods.Items.Item[selectItem].SubItems[0];
  FXmlDoc:= TNativeXml.Create;
  AList:=TStringList.Create;
  testList := TStringList.Create;
  AList.Append(createItemXML(swdh,uuId,itemCode,itemName));
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
        selectItem := -1;
        //开始写最后冲正流水号
        //WriteLastSerial(reqSerType,FXmlDoc.Root.findnode('/resp/transId').ValueAsString);
      end;

      //lblPhone.Caption := FXmlDoc.Root.findnode('/resp/mobile').ValueAsString;
      lblOldSerial.Caption := FXmlDoc.Root.findnode('/resp/transId').ValueAsString;
      lblTradeSerial.Caption := FXmlDoc.Root.findnode('/resp/platSeq').ValueAsString;
      lblInfo.Caption := sdUtf8ToAnsi(FXmlDoc.Root.findnode('/resp/printDesc').ValueAsString);
      btnExchange.Enabled := False;
    except
      on e:Exception do
        ShowMessage(e.Message);
    end;
  finally
    respsm.Free;
    AList.Free;
    testList.Free;
    tmpStream.Free;
    FXmlDoc.Free;
  end;

end;

procedure TfaqExchangeGoods.btnInteQueryClick(Sender: TObject);
var
  uuId,cardNo:string;
  
  respsm:TStringStream;
  AList:TStrings;
  testList:TStringList;
  tmpStream:TStream;
  tmpStr:string;
  reCode,reInfo:string;
  //reqSerType:string;
  AXMLList: TXmlNodeList;
  i:Integer;
  tmpItem: TListItem;
begin
  //lblPhone.Caption := '';
  lblOldSerial.Caption := '';
  lblTradeSerial.Caption := '';
  lblInfo.Caption := '';
  lblGoodsName.Caption := '';
  selectItem := -1;

  if ifDebug=0 then
  begin
    if psamTermId='' then
    begin
      Context.GetDialogSystem.ShowMessage('请先打开串口，设置PSAM卡座！');
      Exit;
    end;

    if rgExType.ItemIndex=0 then
    begin
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
      uuId := cardNo;
    end
    else
    begin
      uuId := Trim(edtMInfo.Text);
    end;
  end
  else
    uuId := '11000000070157';
  FXmlDoc:= TNativeXml.Create;
  AList:=TStringList.Create;
  testList := TStringList.Create;
  AXMLList:=TXmlNodeList.Create;
  AList.Append(createItemXML(swdh,uuId,'',''));
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
      //把返回的实物添加到列表
      FXmlDoc.Root.FindNodes('item',AXMLList);
      if AXMLList.Count>0 then
        btnExchange.Enabled := True
      else
        btnExchange.Enabled := False;
      lvGoods.Items.Clear;
      for i:=0 to AXMLList.Count-1 do
      begin
        tmpItem := lvGoods.Items.Add;
        //实物编号
        tmpItem.Caption := sdUtf8ToAnsi(AXMLList.Items[i].ReadString('itemId'));
        //实物名称
        tmpItem.SubItems.Add(sdUtf8ToAnsi(AXMLList.Items[i].ReadString('itemProperties')));
      end;
    except
      on e:Exception do
        ShowMessage(e.Message);
    end;
  finally
    respsm.Free;
    AList.Free;
    testList.Free;
    tmpStream.Free;
    AXMLList.Free;
    FXmlDoc.Free;
  end;
end;

procedure TfaqExchangeGoods.rgExTypeClick(Sender: TObject);
begin
  if rgExType.ItemIndex=0 then
  begin
    edtMInfo.Text := '';
    edtMInfo.ReadOnly := True;
  end
  else
    edtMInfo.ReadOnly := False;
end;

procedure TfaqExchangeGoods.lvGoodsClick(Sender: TObject);
begin
  try
    selectItem:=lvGoods.Selected.Index;
    lblGoodsName.Caption := lvGoods.Items.Item[selectItem].SubItems[0];
  except
    selectItem := -1;
  end;
end;

initialization
  TUIStdClassFactory.Create('实物兑换',TfaqExchangeGoods);

end.
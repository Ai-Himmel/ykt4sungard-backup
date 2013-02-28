unit UADiscountGoods;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  RzStatus,RM_Class, RzPanel, RzRadGrp,CardDll,HTTPApp, IdBaseComponent,
  IdComponent, IdTCPConnection, IdTCPClient, IdHTTP,NativeXml, ComCtrls;

type
  TfaqDiscountGoods = class(TfaqhSimpleQueryTemp)
    rzstspnInfo: TRzStatusPane;
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
    RzGroupBox2: TRzGroupBox;
    lvGoods: TListView;
    Label2: TLabel;
    lblGoodsName: TLabel;
    procedure btnExchangeClick(Sender: TObject);
    procedure btnInteQueryClick(Sender: TObject);
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
  faqDiscountGoods: TfaqDiscountGoods;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, UCommon, Contnrs,
     KSClientConsts,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqDiscountGoods.Init;
begin
  inherited;
  //lblPhone.Caption := '';
  lblOldSerial.Caption := '';
  lblTradeSerial.Caption := '';
  lblInfo.Caption := '';
  lblGoodsName.Caption := '';
  selectItem := -1;
end;


procedure TfaqDiscountGoods.btnExchangeClick(Sender: TObject);
var
  //cardNo,uuId:string;
  
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

  if lvGoods.Items.Count=0 then
  begin
    Context.GetDialogSystem.ShowMessage('û��Ҫ�һ�����Ʒ�б�');
    Exit;
  end;
  if selectItem<0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ�һ�����Ʒ��');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ�һ�ѡ�е���Ʒ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  itemCode := lvGoods.Items.Item[selectItem].Caption;
  itemName := lvGoods.Items.Item[selectItem].SubItems[0];
  FXmlDoc:= TNativeXml.Create;
  AList:=TStringList.Create;
  testList := TStringList.Create;
  AList.Append(createItemXML(yhqdh,'',itemCode,itemName));
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
        //��ʼд��������ˮ��
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

procedure TfaqDiscountGoods.btnInteQueryClick(Sender: TObject);
var
  //uuId,cardNo:string;
  
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

  FXmlDoc:= TNativeXml.Create;
  AList:=TStringList.Create;
  testList := TStringList.Create;
  AXMLList:=TXmlNodeList.Create;
  AList.Append(createItemXML(yhqdh,'','',''));
  //AList.SaveToFile('c:\test.xml');//-------------------------------����
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
      //�ѷ��ص�ʵ����ӵ��б�
      FXmlDoc.Root.FindNodes('item',AXMLList);
      if AXMLList.Count>0 then
        btnExchange.Enabled := True
      else
        btnExchange.Enabled := False;
      lvGoods.Items.Clear;
      for i:=0 to AXMLList.Count-1 do
      begin
        tmpItem := lvGoods.Items.Add;
        //ʵ����
        tmpItem.Caption := sdUtf8ToAnsi(AXMLList.Items[i].ReadString('itemId'));
        //ʵ������
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

procedure TfaqDiscountGoods.lvGoodsClick(Sender: TObject);
begin
  try
    selectItem:=lvGoods.Selected.Index;
    lblGoodsName.Caption := lvGoods.Items.Item[selectItem].SubItems[0];
  except
    selectItem := -1;
  end;
end;

initialization
  TUIStdClassFactory.Create('�Ż�ȯ�һ�',TfaqDiscountGoods);

end.
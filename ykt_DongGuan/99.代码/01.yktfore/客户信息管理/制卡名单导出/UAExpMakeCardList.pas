unit UAExpMakeCardList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons,filetrans, ComCtrls,FileCtrl,
  RzListVw, UIncrementComboBox;

type
  TfaqhExpMakeCardList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    Label2: TLabel;
    edtFilePath: TEdit;
    lvData: TRzListView;
    pbStatues: TProgressBar;
    Label4: TLabel;
    cbbDept: TWVComboBox;
    Label10: TLabel;
    cbbIDType: TWVComboBox;
    procedure btnPrintClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    //endGetPhotoSign:Boolean;
    //procedure getPhoto;
    procedure fillList(wv:TWorkView);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhExpMakeCardList: TfaqhExpMakeCardList;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,data2Excel;
     
{$R *.DFM}

procedure TfaqhExpMakeCardList.Init;
begin
  inherited;
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    //endGetPhotoSign := True;
  except

  end;
end;

procedure TfaqhExpMakeCardList.btnPrintClick(Sender: TObject);
var
  //tmpDataset:TDataSet;
  custNo,custName,certNo:string;
  dFile:string;
  ret,i,lvCount:Integer;
  errList:TStringList;
begin
  if Application.MessageBox('你确定要导出制卡名单列表吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;

  if not DirectoryExists(edtFilePath.Text) then
    ForceDirectories(edtFilePath.Text);
  ListViewToXLS(lvData,edtFilePath.Text+'\制卡人员名单.xls');
  errList := nil;
  lvCount := lvData.Items.Count;
  pbStatues.Position := 0;
  pbStatues.Max := lvCount;
  try
    errList := TStringList.Create;
    for i := 0 to lvCount-1 do
    begin
      custNo := lvData.Items[i].SubItems[0];
      custName := lvData.Items[i].SubItems[6];
      certNo := lvData.Items[i].SubItems[8];
      dFile := custName+'_'+certNo+'.jpg';
      if custNo='0' then
      begin
        pbStatues.Position := pbStatues.Position+1;
        Continue;
      end;
      try
        ret := KSG_Downloadphoto_File(custNo,edtfilepath.text+'\'+dFile);
        if ret <> KSG_SUCCESS then
        begin
          errList.Add('客户号['+custNo+'],姓名['+custName+']下载照片失败，该客户可能没有照片');
          pbStatues.Position := pbStatues.Position+1;
          Continue;
        end;
      except
        on e:Exception do
        begin
          errList.Add('客户号['+custNo+'],姓名['+custName+']下载照片失败，该客户可能没有照片');
          pbStatues.Position := pbStatues.Position+1;
          Continue;
        end;
      end;
      pbStatues.Position := pbStatues.Position+1;
    end;
  finally
    if errList.Count>0 then
      errList.SaveToFile(edtFilePath.Text+'\导出照片失败名单.txt');
    errlist.Destroy;
  end;
  Context.GetDialogSystem.ShowMessage('导出制卡名单及照片完成！');
end;

procedure TfaqhExpMakeCardList.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvData.Items.Add;
    //批次号
    tmpItem.Caption := tmpdataset.fieldbyname('snote2').AsString;
    //客户号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    //卡号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scard0').AsString);
    //应用序列号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);
    //卡片管理号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);
    //有效期
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sdate0').AsString);
    //发卡部门
    tmpItem.SubItems.Add(GetIdObjectName(210,tmpdataset.fieldbyname('sroom_no2').AsString));
    //发卡类型
    tmpItem.SubItems.Add(GetIdObjectName(-1,tmpdataset.fieldbyname('lvol2').AsString));
    //姓名
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('snote').AsString);
    //证件类型
    tmpItem.SubItems.Add(GetIdObjectName(201,tmpdataset.fieldbyname('sroom_no').AsString));
    //证件号码
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '查询到'+inttostr(lvData.Items.Count)+'条记录';
end;

procedure TfaqhExpMakeCardList.btnQueryClick(Sender: TObject);
begin
  lvData.Items.Clear;
  inherited;
  fillList(WorkView);

end;

initialization
  TUIStdClassFactory.Create('制卡名单导出',TfaqhExpMakeCardList);

end.
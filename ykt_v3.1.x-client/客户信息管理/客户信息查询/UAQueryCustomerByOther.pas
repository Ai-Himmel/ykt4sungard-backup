unit UAQueryCustomerByOther;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, FilterCombos,KSChineseSpell;

type
  TfaqhQueryCustomerByOther = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    cbbDeptName: TWVComboBox;
    WVComboBox8: TWVComboBox;
    WVComboBox9: TWVComboBox;
    WVEdit10: TWVEdit;
    WVEdit11: TWVEdit;
    WVLabel2: TWVLabel;
    WVEdit2: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    Label13: TLabel;
    WVComboBox4: TWVComboBox;
    WVLabel3: TWVLabel;
    WVEdit3: TWVEdit;
    cbbSpec: TWVComboBox;
    Label7: TLabel;
    imgPhoto: TImage;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    btnPhoto: TBitBtn;
    cbb1: TKSFilterComboBox;
    cbb2: TKSFilterComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnPhotoClick(Sender: TObject);
    procedure cbb2Change(Sender: TObject);
    procedure cbb1FilterItems(Sender: TObject);
    procedure cbb2FilterItems(Sender: TObject);
  private

    { Private declarations }
    FSpells,FSpec : TStringList;
    FDisplayItems,FSpecItems : TStringList;

    endGetPhotoSign:Boolean;

    procedure getPhoto;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhQueryCustomerByOther: TfaqhQueryCustomerByOther;

implementation

uses KsFrameworks,
  SmartCardCommon,filetrans,KSClientConsts,LogFile,KSDataDictionary;

{$R *.DFM}

procedure TfaqhQueryCustomerByOther.Init;
var
  filePath:string;
begin
  inherited;
  WVComboBox1.ItemIndex := 0;
  WVComboBox2.ItemIndex := 0;
  WVComboBox3.ItemIndex := 0;
  WVComboBox4.ItemIndex := 0;
  WVComboBox9.ItemIndex := 0;
  fillData2FilterCbb(FSpells,FDisplayItems,cbbDeptName);
  fillData2FilterCbb(FSpec,FSpecItems,cbbSpec);
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    endGetPhotoSign := True;
    filePath := sAppPath+'nophoto.jpg';
    imgPhoto.Picture.LoadFromFile(filePath);
  except

  end;
end;

procedure TfaqhQueryCustomerByOther.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhQueryCustomerByOther.btnQueryClick(Sender: TObject);
var
  deptNo,specNo:string;
begin
  if trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  try
    deptNo := Trim(Copy(cbb1.Text,1,Pos('-',cbb1.Text)-1));
    specNo := Trim(Copy(cbb2.Text,1,Pos('-',cbb2.Text)-1));
  except

  end;
  
  WorkView.FieldByName('联系人单位号').Data.SetString(deptNo);
  WorkView.FieldByName('专业').Data.SetString(specNo);
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;
  {
  if Grid.DataSource.DataSet.RecordCount=1 then
    getPhoto;
    }
end;

procedure TfaqhQueryCustomerByOther.getPhoto;
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
    custNo := Grid.DataSource.DataSet.fieldbyname('lvol1').asstring;
  except
    Context.GetDialogSystem.ShowMessage('请先选择一条记录，然后再取照片！');
    Exit;
  end;
  //WorkView1.FieldByName('客户号').Data.SetInteger(custNo);
  //WVRequest1.SendCommand;
  //sFile := WorkView1.fieldbyname('文件名').Data.AsString;
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
        Context.GetDialogSystem.ShowMessage('该客户没有照片信息-'+inttostr(ret));
        Exit;
      end;
    except
      on e:Exception do
      begin        
        Context.GetDialogSystem.ShowMessage('下载照片信息失败，该客户可能没有拍照!');
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

procedure TfaqhQueryCustomerByOther.btnPhotoClick(Sender: TObject);
begin
  getPhoto;

end;

procedure TfaqhQueryCustomerByOther.cbb2Change(Sender: TObject);
begin
  //inherited;

end;

procedure TfaqhQueryCustomerByOther.cbb1FilterItems(Sender: TObject);
begin
  cbbFilterItem( FSpells,FDisplayItems,sender);
end;

procedure TfaqhQueryCustomerByOther.cbb2FilterItems(Sender: TObject);
begin
  cbbFilterItem( FSpec,FSpecItems,sender);

end;

initialization
  TUIStdClassFactory.Create('客户信息查询', TfaqhQueryCustomerByOther);

end.

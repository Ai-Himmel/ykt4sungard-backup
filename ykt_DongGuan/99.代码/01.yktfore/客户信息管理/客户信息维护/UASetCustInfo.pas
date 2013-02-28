unit UASetCustInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox, jpeg;

type
  TfaqhSetCustInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label4: TLabel;
    Label7: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label37: TLabel;
	WVEdit9: TWVEdit;
	WVEdit11: TWVEdit;
    edtBirthdayQ: TWVEdit;
	WVEdit15: TWVEdit;
	WVEdit16: TWVEdit;
	WVEdit17: TWVEdit;
    WVDigitalEdit37: TWVDigitalEdit;
    cbbIDTypeQ: TWVComboBox;
    cbbDept: TWVComboBox;
    cbb1: TWVComboBox;
    WVComboBox1: TWVComboBox;
    grpBaseInfo: TGroupBox;
    Label44: TLabel;
    WVEdit44: TWVEdit;
    Label49: TLabel;
    Label56: TLabel;
    Label47: TLabel;
    edtBirthday: TWVEdit;
    Label45: TLabel;
    Label46: TLabel;
    edtIdNo: TWVEdit;
    Label48: TLabel;
    edtHeight: TWVEdit;
    Label55: TLabel;
    Label60: TLabel;
    Label54: TLabel;
    Label59: TLabel;
    Label62: TLabel;
    Label63: TLabel;
    WVEdit63: TWVEdit;
    Label61: TLabel;
    WVEdit61: TWVEdit;
    Label67: TLabel;
    edtArriveDate: TWVEdit;
    Label50: TLabel;
    WVEdit50: TWVEdit;
    Label51: TLabel;
    WVEdit51: TWVEdit;
    grpAddr: TGroupBox;
    Label57: TLabel;
    Label66: TLabel;
    edtLiveDate: TWVEdit;
    Label64: TLabel;
    Label65: TLabel;
    WVEdit65: TWVEdit;
    Label53: TLabel;
    WVEdit53: TWVEdit;
    Label52: TLabel;
    WVEdit52: TWVEdit;
    grpCardInfo: TGroupBox;
    Label41: TLabel;
    edtAppDate: TWVEdit;
    Label39: TLabel;
    Label40: TLabel;
    WVDigitalEdit40: TWVDigitalEdit;
    Label38: TLabel;
    WVEdit38: TWVEdit;
    WVComboBox2: TWVComboBox;
    cbbSex: TWVComboBox;
    WVComboBox3: TWVComboBox;
    cbbIdType: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVComboBox6: TWVComboBox;
    WVComboBox7: TWVComboBox;
    WVComboBox8: TWVComboBox;
    WVComboBox9: TWVComboBox;
    WVComboBox10: TWVComboBox;
    WVComboBox11: TWVComboBox;
    grpPhoto: TGroupBox;
    imgPhoto: TImage;
    Label1: TLabel;
    cbbCardType: TWVComboBox;
    Label2: TLabel;
    WVEdit1: TWVEdit;
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure btnViewDetailClick(Sender: TObject);
  private

    { Private declarations }
    //endGetPhotoSign:Boolean;
    //procedure getPhoto;
    {
    procedure connCam;
    procedure getPhotoFromCam;
    procedure cutPhoto;
    procedure disconnectCam;

    procedure delPhotoInfo;
    }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetCustInfo: TfaqhSetCustInfo;
  
implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon,filetrans,USetParamsTemp;

{$R *.DFM}

procedure TfaqhSetCustInfo.Init;
begin
  inherited;
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    //endGetPhotoSign := True;
    //filePath := sAppPath+'nophoto.jpg';
    //imgPhoto.Picture.LoadFromFile(filePath);
  except

  end;
end;

procedure TfaqhSetCustInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetCustInfo.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBirthdayQ.Text)<>'' then
    if CheckInputDateFormat(edtBirthdayQ.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('出生日期输入不正确，格式：yyyymmdd');
      edtBirthdayQ.SetFocus;
      Exit;
    end;

  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetCustInfo.btnAddClick(Sender: TObject);
begin
  imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
  WorkView.FieldByName('证件类型').Data.SetString('10');
  WorkView.FieldByName('国籍').Data.SetString('CHN');
  WorkView.FieldByName('民族').Data.SetString('1');
  WorkView.FieldByName('户口所在地类型').Data.SetString('1');
  WorkView.FieldByName('经济来源').Data.SetString('1');
  WorkView.FieldByName('居住是由').Data.SetString('1');
end;

procedure TfaqhSetCustInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  //getPhoto;
  WorkView.FieldByName('操作标志').Data.SetString('E');
end;

procedure TfaqhSetCustInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  //getPhoto;
  WorkView.FieldByName('操作标志').Data.SetString('D');
end;

procedure TfaqhSetCustInfo.btnOKClick(Sender: TObject);
var
  idtype:string;
  errorMsg:string;
begin
  if ((Status = ssAdd) or (Status = ssChange)) then
  begin
    if (Trim(cbbIdType.Text)='') or (Trim(cbbIdType.Text)='-') then
    begin
      Context.GetDialogSystem.ShowMessage('请选择证件类型！');
      cbbIdType.SetFocus;
      Exit;
    end;
    if Trim(edtIdNo.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('请输入证件号码！');
      edtIdNo.SetFocus;
      Exit;
    end;
    if Trim(edtBirthday.Text)<>'' then
      if CheckInputDateFormat(edtBirthday.Text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('出生日期输入不正确，格式：yyyymmdd');
        edtBirthday.SetFocus;
        Exit;
      end;
    if Trim(edtArriveDate.Text)<>'' then
      if CheckInputDateFormat(edtArriveDate.Text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('首次到达本市日期输入不正确，格式：yyyymmdd');
        edtArriveDate.SetFocus;
        Exit;
      end;
    if Trim(edtLiveDate.Text)<>'' then
      if CheckInputDateFormat(edtLiveDate.Text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('居住日期输入不正确，格式：yyyymmdd');
        edtLiveDate.SetFocus;
        Exit;
      end;
    if Trim(edtAppDate.Text)<>'' then
      if CheckInputDateFormat(edtAppDate.Text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('申请日期输入不正确，格式：yyyymmdd');
        edtAppDate.SetFocus;
        Exit;
      end;
    try
      if Trim(edtHeight.Text)<>'' then
      begin
        if StrToInt(edtHeight.Text)<0 then
        begin
          Context.GetDialogSystem.ShowMessage('请输入有效的身高，只能是整数，单位cm');
          Exit;
        end;
      end
      else
        edtHeight.Text:='0';
    except
      Context.GetDialogSystem.ShowMessage('请输入有效的身高，只能是整数，单位cm');
      Exit;
    end;
    if Trim(cbbCardType.Text)='-' then
    begin
      Context.GetDialogSystem.ShowMessage('请选择要发卡的类别！');
      cbbCardType.SetFocus;
      Exit;
    end;
    idtype := Copy(cbbIdType.Text,1,Pos('-',cbbIdType.Text)-1);
    
    if idtype='10' then
    begin
      errorMsg := ValidatePID(trim(edtIdNo.Text));
      if errorMsg<>'' then
      begin
        if Application.MessageBox(PChar(errorMsg+',你是否要继续保存？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
          Exit;
      end;
    end;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhSetCustInfo.GridDblClick(Sender: TObject);
begin
  inherited;
  //getPhoto;
end;

procedure TfaqhSetCustInfo.btnViewDetailClick(Sender: TObject);
begin
  inherited;
  //getPhoto;
end;
{
procedure TfaqhSetCustInfo.getPhoto;
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
}
initialization
  TUIStdClassFactory.Create('客户信息维护',TfaqhSetCustInfo);

end.
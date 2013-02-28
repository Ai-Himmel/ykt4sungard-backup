unit UAGetCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox, jpeg,
  RM_Common, RM_Class;

type
  TfaqhGetCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label4: TLabel;
    Label12: TLabel;
    Label7: TLabel;
    cbb1: TWVComboBox;
    edtBirthdayQ: TWVEdit;
    cbbDept: TWVComboBox;
    WVEdit17: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVEdit9: TWVEdit;
    Label9: TLabel;
    Label14: TLabel;
    Label17: TLabel;
    Label15: TLabel;
    Label10: TLabel;
    cbbIDType: TWVComboBox;
    WVEdit15: TWVEdit;
    Label16: TLabel;
    Label11: TLabel;
    WVEdit11: TWVEdit;
    WVEdit16: TWVEdit;
    QueryRequest: TWVRequest;
    WorkView1: TWorkView;
    btnGetCard: TBitBtn;
    chkPrint: TCheckBox;
    imgPhoto: TImage;
    rpt1: TRMReport;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    btnReadCard: TBitBtn;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    procedure btnQueryClick(Sender: TObject);
    procedure btnGetCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
  private

    { Private declarations }
    endGetPhotoSign:Boolean;
    procedure getPhoto;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhGetCard: TfaqhGetCard;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,filetrans;
     
{$R *.DFM}

procedure TfaqhGetCard.Init;
var
  filePath:string;
begin
  inherited;
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    endGetPhotoSign := True;
    filePath := sAppPath+'nophoto.jpg';
    imgPhoto.Picture.LoadFromFile(filePath);
  except

  end;
end;

procedure TfaqhGetCard.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBirthdayQ.Text)<>'' then
    if CheckInputDateFormat(edtBirthdayQ.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('出生日期输入不正确，格式：yyyymmdd');
      edtBirthdayQ.SetFocus;
      Exit;
    end;

  WorkView1.FieldByName('操作标志').Data.SetString('R');
  QueryRequest.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsString<>'0' then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString);
    Exit;
  end;
  if WorkView1.FieldByName('查询结果集').Data.IsEmpty then
    btnGetCard.Enabled := False
  else
    btnGetCard.Enabled := True;
end;

procedure TfaqhGetCard.btnGetCardClick(Sender: TObject);
var
  custId:Integer;
  cardNo:string;
begin
  if Application.MessageBox('你确定要进行领卡操作吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  cardNo := Grid.DataSource.DataSet.fieldbyname('scard0').AsString;
  WorkView.FieldByName('操作标志').Data.SetString('G');
  WorkView.FieldByName('卡号').Data.SetString(cardNo);
  WorkView.FieldByName('客户号').Data.SetInteger(custId);
  WorkView.FieldByName('预交款').Data.SetFloat(0);
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
    Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('返回信息').Data.AsString)
  else
    Context.GetDialogSystem.ShowMessage('领卡成功！');
end;

procedure TfaqhGetCard.getPhoto;
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

procedure TfaqhGetCard.GridCellClick(Column: TColumn);
begin
  inherited;
  getPhoto;
end;

initialization
  TUIStdClassFactory.Create('一卡通领取',TfaqhGetCard);

end.
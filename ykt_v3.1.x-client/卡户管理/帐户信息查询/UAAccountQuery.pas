unit UAAccountQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, UtCardDll;

type
  TfaqhAccountQuery = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    edtDate: TWVEdit;
    Label5: TLabel;
    WVEdit4: TWVEdit;
    WVLabel3: TWVLabel;
    WVComboBox4: TWVComboBox;
    Label4: TLabel;
    WVEdit7: TWVEdit;
    edtCardNo: TWVEdit;
    Label8: TLabel;
    btnReadCard: TBitBtn;
    WVLabel4: TWVLabel;
    WVComboBox7: TWVComboBox;
    imgPhoto: TImage;
    btnPhoto: TBitBtn;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPhotoClick(Sender: TObject);
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
  faqhAccountQuery: TfaqhAccountQuery;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts,SmartCardCommon,filetrans;

{$R *.DFM}

procedure TfaqhAccountQuery.Init;

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
    on e:Exception do
      Context.GetDialogSystem.ShowMessage(e.Message);
  end;
end;

procedure TfaqhAccountQuery.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhAccountQuery.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  if Trim(edtDate.Text)<>'' then
    if CheckInputDateFormat(edtDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('���˽����������벻��ȷ����ʽ��yyyymmdd');
      edtDate.SetFocus;
      Exit;
    end;
  inherited;
end;


procedure TfaqhAccountQuery.btnReadCardClick(Sender: TObject);
begin
  edtCardNo.Text:=readCardNo;
  btnQuery.Click;
end;

procedure TfaqhAccountQuery.getPhoto;
var
  sFile,dFile:string;
  ret:Integer;
  custNo:string;
begin
  if showphoto=0 then
    Exit;
  //��ѯ��Ƭǰ�������ǰ����Ƭ��Ϣ
  imgPhoto.Picture := nil;

  if endGetPhotoSign=false then
    Exit;
  //�Ӻ�̨ȡ����Ƭ�����ƣ���Ƭ��Ϊ�ͻ���
  custNo := Grid.DataSource.DataSet.fieldbyname('lvol1').AsString;
  sFile := custNo;
  dFile := 'photo999999.jpg';
  try
    try
      endGetPhotoSign:=false;
      ret := KSG_Downloadphoto_File(sFile,dFile);
      if ret = KSG_SUCCESS then
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+dFile);
      end
      else
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
        Context.GetDialogSystem.ShowMessage('�ÿͻ�û����Ƭ��Ϣ��');
        Exit;
      end;
    except
      on e:Exception do
      begin        
        Context.GetDialogSystem.ShowMessage('������Ƭ��Ϣʧ�ܣ��ÿͻ�����û������!');
        Exit;
      end;
    end;
  finally
    endGetPhotoSign:=True;
  end;
  //������Ƭ��ɺ�ɾ��
  //�ڱ��ز����Ƿ����dFile����Ƭ��������ɾ��

  try
    if FileExists(sAppPath+dFile) then
      DeleteFile(sAppPath+dFile);
  except
    //WriteLog('ɾ�� photo999999.jpg ʧ�ܣ����ļ������ڣ�');
  end;
end;

procedure TfaqhAccountQuery.btnPhotoClick(Sender: TObject);
begin
  getPhoto;
end;

procedure TfaqhAccountQuery.btnPrintClick(Sender: TObject);
begin

  RTitle := 'ches1';
  LTitle := 'ches2';
  rptTitle := 'ches3';
  DateSpotTitle := 'ches4';

  //rptTitleex := 'dd';
  inherited;

end;

initialization
  TUIStdClassFactory.Create('�ֿ����ʻ���Ϣ��ѯ', TfaqhAccountQuery);

end.



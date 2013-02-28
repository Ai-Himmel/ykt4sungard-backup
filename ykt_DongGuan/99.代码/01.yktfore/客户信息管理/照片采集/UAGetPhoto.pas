unit UAGetPhoto;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzStatus, jpeg;

type
  TfaqhGetPhoto = class(TfaqhSimpleQueryTemp)
    pnlQuery: TPanel;
    Label4: TLabel;
    Label12: TLabel;
    edtBirthdayQ: TWVEdit;
    cbbDept: TWVComboBox;
    WVEdit9: TWVEdit;
    Label9: TLabel;
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
    btnFee: TBitBtn;
    btnGetCard: TBitBtn;
    rzstspn1: TRzStatusPane;
    pnl1: TPanel;
    dlgOpen1: TOpenDialog;
    pnlP: TPanel;
    pnlPhoto: TPanel;
    btnExtPhoto: TBitBtn;
    grpPhoto: TGroupBox;
    imgPhoto: TImage;
    btnConn: TBitBtn;
    btnPhoto: TBitBtn;
    lblCustInfo: TLabel;
    btnDisConnect: TBitBtn;
    procedure btnQueryClick(Sender: TObject);
    procedure btnFeeClick(Sender: TObject);
    procedure btnExtPhotoClick(Sender: TObject);
    procedure btnConnClick(Sender: TObject);
    procedure btnPhotoClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnDisConnectClick(Sender: TObject);
  private

    { Private declarations }
    hWndC: THandle;
    endGetPhotoSign:Boolean;
    openCamSign:Boolean;
    procedure getPhoto;

    procedure connCam;
    procedure getPhotoFromCam;
    procedure cutPhoto;
    procedure disconnectCam;

    procedure delPhotoInfo;
  public
    procedure Init; override;
    destructor Destroy; override;
    { Public declarations }
  end;

var
  faqhGetPhoto: TfaqhGetPhoto;

const
  WM_CAP_START = WM_USER;
  WM_CAP_DRIVER_CONNECT = WM_CAP_START + 10;
  WM_CAP_DRIVER_DISCONNECT = WM_CAP_START + 11;
  WM_CAP_SAVEDIB = WM_CAP_START + 25;
  WM_CAP_GRAB_FRAME = WM_CAP_START + 60;
  WM_CAP_SET_OVERLAY = WM_CAP_START + 51;
  WM_CAP_SET_PREVIEW = WM_CAP_START + 50;
  WM_CAP_SET_CALLBACK_VIDEOSTREAM = WM_CAP_START + 6;
  WM_CAP_SET_CALLBACK_ERROR = WM_CAP_START + 2;
  WM_CAP_SET_CALLBACK_STATUSA = WM_CAP_START + 3;
  WM_CAP_SET_CALLBACK_FRAME = WM_CAP_START + 5;
  WM_CAP_SET_SCALE = WM_CAP_START + 53;
  WM_CAP_SET_PREVIEWRATE = WM_CAP_START + 52;

function capCreateCaptureWindowA(lpszWindowName: PCHAR; dwStyle: longint; x: integer; y: integer; nWidth: integer; nHeight: integer; ParentWin: HWND; nId: integer): HWND; stdcall external 'avicap32.dll';

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,filetrans;
     
{$R *.DFM}

procedure TfaqhGetPhoto.Init;
begin
  inherited;
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    endGetPhotoSign := True;
    openCamSign := False;
    btnDisConnect.Enabled := False;
    //filePath := sAppPath+'nophoto.jpg';
    //imgPhoto.Picture.LoadFromFile(filePath);
  except
    on e:Exception do
      Context.GetDialogSystem.ShowMessage(e.Message);
  end;
end;

procedure TfaqhGetPhoto.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBirthdayQ.Text)<>'' then
    if CheckInputDateFormat(edtBirthdayQ.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtBirthdayQ.SetFocus;
      Exit;
    end;

  WorkView1.FieldByName('������־').Data.SetString('R');
  QueryRequest.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);
    Exit;
  end;
  if WorkView1.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    btnGetCard.Enabled := False;
    btnFee.Enabled := False;
  end
  else
  begin
    btnGetCard.Enabled := True;
    btnFee.Enabled := True;
  end;
  //inherited;

end;

procedure TfaqhGetPhoto.btnFeeClick(Sender: TObject);
var
  custId:Integer;
  //money:Double;
  ret :integer;
  photoName:string;
begin
  custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  if Application.MessageBox(PChar('��ȷ��Ҫ����ͻ���Ϊ['+inttostr(custId)+']����Ƭ��'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
    
  photoName := inttostr(custId)+'.jpg';
  imgPhoto.Picture.SaveToFile(photoName);
  //�ϴ���Ƭ
  ret := KSG_Upload_File(photoName,sAppPath+photoName);
  if ret <> KSG_SUCCESS then
  begin
    Context.GetDialogSystem.ShowMessage('�ϴ���Ƭ��Ϣʧ�ܣ�����������--'+KSG_get_errmsg+'<'+Inttostr(Ret)+'>');
    Exit;
  end;

  try
    if FileExists(sAppPath+photoName) then
      DeleteFile(sAppPath+photoName);
  except
    //WriteLog('ɾ�� photo999999.jpg ʧ�ܣ����ļ������ڣ�');
  end;
  
  WorkView.FieldByName('�ͻ���').Data.SetInteger(custId);
  WorkView.FieldByName('�ļ���').Data.SetString(photoName);
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsString<>'0' then
    Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString)
  else
    Context.GetDialogSystem.ShowMessage('�ͻ���['+inttostr(custId)+']��Ƭ����ɹ���');
end;

procedure TfaqhGetPhoto.btnExtPhotoClick(Sender: TObject);
begin
  if dlgOpen1.Execute then
  begin
    imgPhoto.Picture.LoadFromFile(dlgOpen1.FileName);
    imgPhoto.Picture.SaveToFile(sAppPath+'tmpPhoto.jpg');
  end;
end;

procedure TfaqhGetPhoto.connCam;
begin
  hWndC := capCreateCaptureWindowA('MyCapWindow', WS_CHILD or WS_VISIBLE, pnlPhoto.Left, pnlPhoto.Top, pnlPhoto.Width, pnlPhoto.Height, pnlPhoto.Handle, 0);
  if hWndC <> 0 then
  begin
    SendMessage(hWndC, WM_CAP_SET_CALLBACK_VIDEOSTREAM, 0, 0);
    SendMessage(hWndC, WM_CAP_SET_CALLBACK_ERROR, 0, 0);
    SendMessage(hWndC, WM_CAP_SET_CALLBACK_STATUSA, 0, 0);
    SendMessage(hWndC, WM_CAP_DRIVER_CONNECT, 0, 0);
    SendMessage(hWndC, WM_CAP_SET_SCALE, 1, 0);
    SendMessage(hWndC, WM_CAP_SET_PREVIEWRATE, 66, 0);
    SendMessage(hWndC, WM_CAP_SET_OVERLAY, 1, 0);
    SendMessage(hWndC, WM_CAP_SET_PREVIEW, 1, 0);
  end;
end;

procedure TfaqhGetPhoto.cutPhoto;
var
  SrcBmp, DestBmp,tmpBmp: TBitmap;
  width,height:Integer;
  tmpW,tmpH:Integer;
  Destjpeg: Tjpegimage;
begin
  width:=360;
  height := 480;
  tmpW := 640;
  tmpH := 480;  
  tmpBmp := nil;
  SrcBmp := nil;
  DestBmp := nil;
  Destjpeg := nil;
  try
    SrcBmp := TBitmap.Create;
    SrcBmp.LoadFromFile(sAppPath+'tmpPhoto.bmp');

    //���¶�����Ƭ�Ĵ�С
    tmpBmp := TBitmap.Create;
    tmpBmp.Width := tmpW;
    tmpBmp.Height := tmpH;
    tmpBmp.Canvas.StretchDraw(Rect(0, 0, tmpBmp.Width, tmpBmp.Height),SrcBmp);
    tmpBmp.SaveToFile(sAppPath+'tmpPhoto.bmp');
    SrcBmp.LoadFromFile(sAppPath+'tmpPhoto.bmp');

    DestBmp := TBitmap.Create;
    DestBmp.Width := width;
    DestBmp.Height := height;
    
    DestBmp.Canvas.CopyRect(Rect(0, 0, width, height), SrcBmp.Canvas, Rect(0, 0, width, height));
    Destjpeg := TJPEGImage.Create;
    Destjpeg.Assign(DestBmp);
    Destjpeg.SaveToFile(sAppPath+'tmpPhoto.jpg');
    imgPhoto.Picture.LoadFromFile(sAppPath+'tmpPhoto.jpg');
  finally
    tmpBmp.Free;
    SrcBmp.Free;
    DestBmp.Free;
    Destjpeg.Free;
  end;
end;

procedure TfaqhGetPhoto.delPhotoInfo;
begin
  try
    if FileExists(sAppPath+'tmpPhoto.jpg') then
      DeleteFile(sAppPath+'tmpPhoto.jpg');
    if FileExists(sAppPath+'tmpPhoto.bmp') then
      DeleteFile(sAppPath+'tmpPhoto.bmp');
  except
    //WriteLog('ɾ�� photo999999.jpg ʧ�ܣ����ļ������ڣ�');
  end;
end;

destructor TfaqhGetPhoto.Destroy;
begin
  disconnectCam;
  inherited;
end;

procedure TfaqhGetPhoto.disconnectCam;
begin
  if hWndC <> 0 then
  begin
    SendMessage(hWndC, WM_CAP_DRIVER_DISCONNECT, 0, 0);
    hWndC := 0;
  end;
  delPhotoInfo;
end;

procedure TfaqhGetPhoto.getPhoto;
var
  dFile:string;
  ret:Integer;
  custNo,custName:string;
begin
  if showphoto=0 then
    Exit;
  //��ѯ��Ƭǰ�������ǰ����Ƭ��Ϣ
  imgPhoto.Picture := nil;

  if endGetPhotoSign=false then
    Exit;
  try
    //�Ӻ�̨ȡ����Ƭ�����ƣ���Ƭ��Ϊ�ͻ���
    custNo := Grid.DataSource.DataSet.fieldbyname('lvol0').asstring;
    custName := Grid.DataSource.DataSet.fieldbyname('snote').asstring;
    lblCustInfo.Caption := '['+custNo+'-'+custname+']����Ƭ'
  except
    Context.GetDialogSystem.ShowMessage('����ѡ��һ����¼��Ȼ����ȡ��Ƭ��');
    Exit;
  end;
  dFile := 'photo999999.jpg';
  try
    try
      endGetPhotoSign:=false;
      ret := KSG_Downloadphoto_File(custNo,sAppPath+dFile);
      //ShowMessage(IntToStr(ret));
      if ret = KSG_SUCCESS then
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+dFile);
      end
      else
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
        //Context.GetDialogSystem.ShowMessage('�ÿͻ�û����Ƭ��Ϣ-'+inttostr(ret));
        Exit;
      end;
    except
      on e:Exception do
      begin        
        Context.GetDialogSystem.ShowMessage('������Ƭ��Ϣʧ�ܣ��ÿͻ�����û������-'+e.Message);
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

procedure TfaqhGetPhoto.getPhotoFromCam;
begin
  if hWndC <> 0 then
  begin
    SendMessage(hWndC, WM_CAP_SAVEDIB, 0, longint(PCHAR(sAppPath+'tmpPhoto.bmp')));
  end;
end;

procedure TfaqhGetPhoto.btnConnClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ���������豸��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if openCamSign = False then
  begin
    connCam;
    openCamSign := True;
    btnDisConnect.Enabled := True;
    btnPhoto.Enabled := True;
    btnConn.Enabled := False;
  end;
end;

procedure TfaqhGetPhoto.btnPhotoClick(Sender: TObject);
begin
  getPhotoFromCam;
  cutPhoto;
end;

procedure TfaqhGetPhoto.GridCellClick(Column: TColumn);
begin
  inherited;
  getPhoto;
end;

procedure TfaqhGetPhoto.btnDisConnectClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ�Ͽ������豸��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if openCamSign = True then
  begin
    disconnectCam;
    openCamSign := False;
    btnDisConnect.Enabled := False;
    btnPhoto.Enabled := False;
    btnConn.Enabled := True;
  end;
end;

initialization
  TUIStdClassFactory.Create('��Ƭ�ɼ�',TfaqhGetPhoto);

end.
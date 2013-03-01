unit mainUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, ExtCtrls, StdCtrls, Buttons, ComCtrls, SkinCaption,
  WinSkinData, jpeg, DB, ADODB, DBCtrls, imageenio, ieview, imageenview,
  hyieutils, ieopensavedlg, imageenproc, ievect, videocap,PSCAMLIB;

type
  TfrmMain = class(TForm)
    mm1: TMainMenu;
    N1: TMenuItem;
    N3: TMenuItem;
    N4: TMenuItem;
    N5: TMenuItem;
    N6: TMenuItem;
    N7: TMenuItem;
    N8: TMenuItem;
    N9: TMenuItem;
    N10: TMenuItem;
    N11: TMenuItem;
    N12: TMenuItem;
    N13: TMenuItem;
    N14: TMenuItem;
    N15: TMenuItem;
    qryPhoto: TADOQuery;
    N16: TMenuItem;
    N17: TMenuItem;
    ImageEnIO1: TImageEnIO;
    opnmgndlg: TOpenImageEnDialog;
    N2: TMenuItem;
    N18: TMenuItem;
    N19: TMenuItem;
    N20: TMenuItem;
    svmgndlg1: TSaveImageEnDialog;
    N21: TMenuItem;
    skndt1: TSkinData;
    skncptn1: TSkinCaption;
    N22: TMenuItem;
    pnlPhotoInfo: TPanel;
    pnlPhoto: TPanel;
    imgPhoto: TImage;
    pnlOperator: TPanel;
    grp1: TGroupBox;
    btnEditInfo: TButton;
    btnDelPhoto: TButton;
    grp2: TGroupBox;
    Label13: TLabel;
    lblCustNo: TLabel;
    lblStuEmpNo: TLabel;
    Label1: TLabel;
    lbl1: TLabel;
    lblName: TLabel;
    lblType: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    lblArea: TLabel;
    lblDept: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    lblSpec: TLabel;
    lblState: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    lblRegDate: TLabel;
    lblCardId: TLabel;
    Label8: TLabel;
    bvl1: TBevel;
    Bevel1: TBevel;
    Bevel2: TBevel;
    Bevel3: TBevel;
    Bevel4: TBevel;
    Bevel5: TBevel;
    Bevel6: TBevel;
    Bevel7: TBevel;
    Bevel8: TBevel;
    Bevel9: TBevel;
    pnlRight: TPanel;
    pnl3: TPanel;
    imgCanon: TImage;
    shpSelect: TShape;
    imgSrc: TImageEnVideoView;
    imgCam: TImageEnView;
    grpPhotoSet: TGroupBox;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    cbbImageSize: TComboBox;
    cbbISO: TComboBox;
    cbbFlash: TComboBox;
    cbbPhotoEffect: TComboBox;
    cbbWhiteBalance: TComboBox;
    trckbr1: TTrackBar;
    pb: TProgressBar;
    btnSetParam: TButton;
    grp4: TGroupBox;
    pnlLeft: TPanel;
    pnlPhotoMain: TPanel;
    imgShow: TImageEnVect;
    grp3: TGroupBox;
    Label10: TLabel;
    Label11: TLabel;
    edtStuempNo: TEdit;
    btnQuery: TBitBtn;
    btnCustQuery: TBitBtn;
    cbbArea: TComboBox;
    pnl1: TPanel;
    grpPhoto: TGroupBox;
    btnPhoto: TBitBtn;
    btnSavePhoto: TBitBtn;
    btnSaveAs: TBitBtn;
    btnOpenPictrue: TBitBtn;
    btnGetPhoto: TBitBtn;
    pnl2: TPanel;
    grpCam: TGroupBox;
    btnConnCam: TButton;
    btnCamFormat: TButton;
    btnSetCam: TButton;
    btnCamClose: TButton;
    grpCanon: TGroupBox;
    btnConnectCan: TButton;
    btnPhotoShow: TButton;
    btnPhotoClose: TButton;
    btnCloseCanon: TButton;
    N23: TMenuItem;
    ImageEnProc1: TImageEnProc;
    ImageEnProc2: TImageEnProc;
    cbbMenu: TComboBox;
    procedure N11Click(Sender: TObject);
    procedure N12Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure N8Click(Sender: TObject);
    procedure N9Click(Sender: TObject);
    procedure btnDelPhotoClick(Sender: TObject);
    procedure N16Click(Sender: TObject);
    procedure btnEditInfoClick(Sender: TObject);
    procedure N5Click(Sender: TObject);
    procedure N14Click(Sender: TObject);
    procedure N3Click(Sender: TObject);
    procedure btnSavePhotoClick(Sender: TObject);
    procedure N6Click(Sender: TObject);
    procedure btnOpenPictrueClick(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure btnConnCamClick(Sender: TObject);
    procedure btnPhotoClick(Sender: TObject);
    procedure btnCamCloseClick(Sender: TObject);
    procedure imgCamViewChange(Sender: TObject; Change: Integer);
    procedure btnSetCamClick(Sender: TObject);
    procedure btnCamFormatClick(Sender: TObject);
    procedure N18Click(Sender: TObject);
    procedure N19Click(Sender: TObject);
    procedure N20Click(Sender: TObject);
    procedure btnConnectCanClick(Sender: TObject);
    procedure btnPhotoShowClick(Sender: TObject);
    procedure btnPhotoCloseClick(Sender: TObject);
    procedure trckbr1Change(Sender: TObject);
    procedure btnSetParamClick(Sender: TObject);
    procedure btnCloseCanonClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure shpSelectMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure shpSelectMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure shpSelectMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure btnSaveAsClick(Sender: TObject);
    procedure N21Click(Sender: TObject);
    procedure N15Click(Sender: TObject);
    procedure N22Click(Sender: TObject);
    procedure btnGetPhotoClick(Sender: TObject);
    procedure N23Click(Sender: TObject);
    procedure edtStuempNoKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    //FCap : TCapture;
    camType:string;//������ͣ�canonΪ���������camΪ����ͷ
    shpSelectLeft : Integer;
    m_p1,setRemoteParam:psRemoteReleaseParameters;
    m_connect:boolean;
    procedure clearCaption();

    procedure fillCbb();

    procedure queryBaseInfo(sstuempNo:string;sareaId:string;scustId:string);

    procedure queryPhoto(scustId:string);

    procedure cutPhoto(savePhotoName:string);

    procedure VideoFrame(Sender: TObject; Bitmap: TIEDibBitmap);

    procedure drawShpSelect();

    procedure saveCononPhotoToDisk();

    procedure getPrintMenu(sender:TObject);

    procedure openPrintM(sender:TObject);


    //�����������
    function getImageSizeAndQuality(inData:Integer):Integer;
    procedure setImageSize(inData:Integer);
    procedure setImageQuality(inData:Integer);
    procedure setWhiteBalance(inData:Integer);
    procedure setISO(inData:Integer);
    procedure setFlash(inData:Integer);
    procedure setPhotoEffect(inData:Integer);

  public
    { Public declarations }
    iCustId:Integer;
    ifPhoto:Boolean;
  end;

var
  frmMain: TfrmMain;
  yPos:integer;
  xPos:integer;
  leftMouse:boolean;
procedure ViewfinerCallbackFunction(buf_adr : pointer; buf_size : integer ); cdecl;
procedure ProgressCallbackFunction(p:integer); cdecl;

implementation

uses uCommon, Udm, uImport, uExport, uAddCustInfo, uPhotoStat,
  uAbout, uLimit, Ulogin, uPhotoQuery, uModifyPwd, uCustImport,
  uGetPhotoSet, uCardPrintTemp;

{$R *.dfm}

{ TfrmMain }

procedure ViewfinerCallbackFunction(buf_adr : pointer; buf_size : integer ); cdecl;
var mem_stream  : TMemoryStream;
    Jpg: TJpegImage;
begin
  try
    try
      try
        mem_stream := TMemoryStream.Create;
        mem_stream.Write(buf_adr^, buf_size);
      except on e:Exception do
        ShowMessage(e.Message+'--�ô����������Ӳ����ͻ����ģ��������ͬ�ͺŵĵ������ԣ�');
      end;
      try
      Jpg := TJpegImage.Create;
      try
      mem_stream.Position := 0;
      Jpg.LoadFromStream(mem_stream);
      except on e1:Exception do
        ShowMessage(e1.Message+'--Ӳ����ͻ��������������ԣ�');
      end;
      frmMain.imgCanon.picture.Assign(Jpg);
      finally
        Jpg.Free;
      end;
    finally
      mem_stream.Free;
    end;
  except
    ShowMessage('�������������⣬�����´������������...');
  end;
end;

procedure ProgressCallbackFunction(p:integer); cdecl;
begin
  try
    frmMain.pb.Position:=p;
  except
    ShowMessage('ϵͳ���󣬲�Ӱ��ʹ�ã������...');
  end;
end;

procedure TfrmMain.N11Click(Sender: TObject);
begin
  {
  if judgelimit(loginLimit,Mdl_stuPrint)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmCardPrint := TfrmCardPrint.Create(nil);
  frmCardPrint.cardType := 'stu';
  frmCardPrint.ShowModal;
  frmCardPrint.Free;
  }
end;

procedure TfrmMain.N12Click(Sender: TObject);
begin
  {
  if judgelimit(loginLimit,Mdl_empPrint)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmCardPrint := TfrmCardPrint.Create(nil);
  frmCardPrint.cardType := 'emp';
  frmCardPrint.ShowModal;
  frmCardPrint.Free;
  }
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  apppath := ExtractFilePath(Application.ExeName);
  getphotoconfigs;
  //frmMain.BorderStyle := bsToolWindow;
  //frmMain.BorderStyle := bsSingle;

  if useRemoteSoft = True then
  begin
    pnlRight.Visible := False;
    btnGetPhoto.Visible := True;
    btnPhoto.Visible := False;
    frmMain.Width := 620;
    try
      delFileBat(photopath,'*.jpg');
    except
    end;
  end
  else if useRemoteSoft=false then
  begin
    frmMain.Width := 1024;
    pnlRight.Visible := True;
    btnGetPhoto.Visible := False;
    btnPhoto.Visible := True;
  end;
  //�������sdk
  try
    psTStartSDK;
  except
  end;
end;

procedure TfrmMain.clearCaption;
begin
  lblStuempNo.Caption:='';
  lblName.Caption:='';
  lblType.Caption:='';
  lblArea.Caption:='';
  lblCardId.Caption:='';
  lblDept.Caption:='';
  lblRegDate.Caption:='';
  lblSpec.Caption:='';
  lblState.Caption:='';
  lblCustNo.Caption:='';
end;

procedure TfrmMain.FormShow(Sender: TObject);
begin
  loginform:=TloginForm.Create(nil);
  loginform.ShowModal;
  loginform.Free;
  frmMain.Top := -1;
  frmMain.Left := -1;
  frmMain.Height := 730;
  {
  if useRemoteSoft = True then
  begin
    frmMain.Width := 620;
    pnlRight.Visible := False;
    btnGetPhoto.Visible := True;
    btnPhoto.Visible := False;
    delFileBat(photopath,'*.jpg');
  end
  else if useRemoteSoft=false then
  begin
    frmMain.Width := 1030;
    pnlRight.Visible := True;
    btnGetPhoto.Visible := False;
    btnPhoto.Visible := True;
  end;
  }
  frmMain.Caption := '����/�ƿ�����ϵͳ--'+loginName;
  clearCaption();
  fillCbb();
  btnDelPhoto.Enabled:=False;
  btnEditInfo.Enabled:=False;
  btnSavePhoto.Enabled := False;
  shpSelect.Visible := False;
  imgCanon.Visible := False;
  grpPhotoSet.Visible := False;
  getPrintMenu(Sender);
  //imgShow.Select(0,0,360,480);
end;

procedure TfrmMain.fillCbb;
var
  sqlStr:string;
begin
  sqlStr:='select '+ areaName + ',' + areaNo + ' from ' + tblArea;
  sqlStr:=sqlStr+' where '+areaFather+'=1 order by '+areaNo;

  AddData(cbbArea,sqlStr);
end;

procedure TfrmMain.queryBaseInfo(sstuempNo:string;sareaId:string;scustId:string);
var
  sqlStr:string;
  qryExecSQL:TADOQuery;
  Fjpg: TJpegImage;
begin
  sqlStr:=queryBaseInfoSql(sstuempNo,sareaId,scustId);
  qryExecSQL := nil;
  Fjpg:=nil;
  imgPhoto.Picture.Graphic:=nil;
  try
    Fjpg := TJpegImage.Create;
    qryExecSQL := TADOQuery.Create(nil);
    qryExecSQL.Connection := frmdm.conn;
    //qryExecSQL.LockType := ltUnspecified;
    qryExecSQL.Close;
    qryExecSQL.SQL.Clear;
    qryExecSQL.SQL.Add(sqlStr);
    qryExecSQL.Prepared;
    qryExecSQL.Open;
    if not qryExecSQL.IsEmpty then
    begin
      lblCustNo.Caption:=qryExecSQL.fieldbyname(custId).AsString;
      lblName.Caption:=qryExecSQL.fieldbyname(custName).AsString;
      lblStuEmpNo.Caption:=qryExecSQL.fieldbyname(stuempNo).AsString;

      
      lblType.Caption:=getTypeName(qryExecSQL.fieldbyname(custType).AsString);
      lblArea.Caption:=getAreaName(qryExecSQL.fieldbyname(custArea).AsString);
      lblDept.Caption:=getDeptName(qryExecSQL.fieldbyname(custDeptNo).AsString);
      lblSpec.Caption:=getSName(qryExecSQL.fieldbyname(custSpecNo).AsString);
      lblState.Caption:=getStatesName(qryExecSQL.fieldbyname(custState).AsString);

      lblRegDate.Caption:=qryExecSQL.fieldbyname(custRegTime).AsString;
      lblCardId.Caption:=qryExecSQL.fieldbyname(custCardId).AsString;
      //ִ����Ƭ������Ϣ�������
      insertPhotoData(Trim(lblCustNo.Caption),Trim(lblStuEmpNo.Caption));
      
      queryPhoto(qryExecSQL.fieldbyname(custId).AsString);

      Fjpg := getPhotoInfo(qryExecSQL.fieldbyname(custId).AsString);
      if Fjpg=nil then
        pnlphoto.Caption := 'û��ԭʼ��Ƭ'
      else
        imgPhoto.Picture.Graphic:=Fjpg;

      btnDelPhoto.Enabled:=True;
      btnEditInfo.Enabled:=True;
      if useRemoteSoft then
        btnGetPhoto.Enabled := True;
    end
    else
    begin
      clearCaption();
      ShowMessage('�ͻ���Ϣ���������Ϣ��������ָ����ѯ������');
    end;
  finally
    Fjpg.Free;
    qryExecSQL.Destroy;
  end;
end;

procedure TfrmMain.btnQueryClick(Sender: TObject);
begin
  if (Trim(edtStuempNo.Text)='')and(cbbArea.Text='') then
  begin
    ShowMessage('�������ѯ������Ȼ���ٲ�ѯ��');
    edtStuempNo.SetFocus;
    Exit;
  end;
  queryBaseInfo(Trim(edtStuempNo.Text),subString(cbbArea.Text,'-','l'),'');
end;

procedure TfrmMain.N8Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_import)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmImport:=TfrmImport.Create(nil);
  frmImport.ShowModal;
  frmImport.Free;
end;

procedure TfrmMain.N9Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_export)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmExport:=TfrmExport.Create(nil);
  frmExport.ShowModal;
  frmExport.Free;
end;

procedure TfrmMain.queryPhoto(scustId: string);
var
  sqlstr:string;
begin
  sqlstr:='select '+custId+','+stuempNo+','+pPhoto+','+pPhotoDate+','+pPhotoDTime;
  sqlstr:=sqlstr+','+pPhotoTime+' from '+tblPhoto+' where '+custId+'='+scustId;
  qryPhoto.Close;
  qryPhoto.SQL.Clear;
  qryPhoto.SQL.Add(sqlstr);
  qryPhoto.Open;
end;

procedure TfrmMain.btnDelPhotoClick(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_delphoto)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  if qryPhoto.IsEmpty then
  begin
    ShowMessage('û����Ҫ��ѯ����Ƭ��Ϣ���޷�ɾ����');
    Exit;
  end;
  if Application.MessageBox(PChar('��ȷ��Ҫɾ����Ƭ��Ϣ��'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  qryPhoto.First;
  qryPhoto.Edit;
  qryPhoto.FieldByName(pPhotoDate).Assign(nil);
  qryPhoto.FieldByName(pPhotoTime).Assign(nil);
  qryPhoto.FieldByName(pPhoto).Assign(nil);
  qryPhoto.Post;
  imgPhoto.Picture.Graphic:=nil;
end;

procedure TfrmMain.N16Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_addCust)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmAddCustInfo:=TfrmAddCustInfo.create(nil);
  frmAddCustInfo.operType:='add';
  frmAddCustInfo.ShowModal;
  frmAddCustInfo.Free;
end;

procedure TfrmMain.btnEditInfoClick(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_EditCust)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  if lblCustNo.Caption='' then
  begin
    ShowMessage('���Ȳ�ѯҪ�޸ĵ���Ա��Ϣ��Ȼ���޸ģ�');
    Exit;
  end;
  frmAddCustInfo:=TfrmAddCustInfo.Create(nil);
  frmAddCustInfo.operType:='edit';
  frmAddCustInfo.lblCustId.Caption:=Trim(lblCustNo.Caption);
  frmAddCustInfo.ShowModal;
  frmAddCustInfo.Free;
end;

procedure TfrmMain.N5Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_photoStat)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmPhotoStat:=TfrmPhotoStat.Create(nil);
  frmPhotoStat.ShowModal;
  frmPhotoStat.Free;
end;

procedure TfrmMain.N14Click(Sender: TObject);
begin
  frmAbout:=TfrmAbout.Create(nil);
  frmAbout.ShowModal;
  frmAbout.Free;
end;

procedure TfrmMain.N3Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_limit)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmLimit:=TfrmLimit.Create(nil);
  frmLimit.ShowModal;
  frmLimit.Free;
end;

procedure TfrmMain.btnSavePhotoClick(Sender: TObject);
var
  F: TmemoryStream;
  FJpeg: TJpegImage;
begin
  if judgelimit(loginLimit,mdl_savephoto)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  if qryPhoto.IsEmpty then
  begin
    ShowMessage('���Ȳ��Ҫ������Ƭ����Ա��Ϣ��Ȼ���ٱ�����Ƭ��');
    Exit;
  end;
  if imgShow.Bitmap=nil then
  begin
    ShowMessage('�������ջ��Ҫ�������Ƭ��Ȼ���ٱ��棡');
    Exit;
  end;
  F := nil;
  FJpeg := nil;
  qryPhoto.Edit;
  try
    FJpeg := TJpegImage.Create;
    FJpeg.Assign(imgShow.Bitmap);
    F := TmemoryStream.Create;
    FJpeg.SaveToStream(F);
    if F.Size>600000 then
    begin
      ShowMessage('������Ƭ�����������Ƭ�벻Ҫ����600K!');
      Exit;
    end;
    //���浽����
    if not DirectoryExists(diskpath) then
      if CreateDir(diskpath)=False then
        ShowMessage('���ܴ����ļ��У�'+diskPath+'�����Ƿ���ڸô��̣�');
    try
      f.SaveToFile(diskpath+'\'+lblstuempno.Caption+'.jpg');
    except
    end;
    TBlobField(qryPhoto.FieldByName(pPhoto)).loadfromStream(F);
    qryPhoto.FieldByName(pPhotoDate).asstring := formatdatetime('yyyymmdd', date);
    qryPhoto.FieldByName(pPhotoTime).asstring := formatdatetime('HHMMSS', now);
    //���뾫ȷʱ�䣬��ʽyyyymmddhhmmsszzz,����֧��oracle��db2-----------------------]]]]]]]]]]]]]
    qryPhoto.FieldByName(pPhotoDTime).asstring := getDbTime;
    qryPhoto.Post;
    imgShow.Assign(nil);
    pnlPhotoMain.Caption:='��Ƭ����ɹ�';
    btnSavePhoto.Enabled := False;
    btnSaveAs.Enabled:=False;
    queryBaseInfo('','',lblCustNo.Caption);
    if useRemoteSoft then
      delFileBat(photopath,'*.jpg');
  finally
    F.Destroy;
    FJpeg.Destroy;
  end;
end;

procedure TfrmMain.N6Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_photoQuery)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmPhotoQuery:=TfrmPhotoQuery.Create(nil);
  ifPhoto:=False;
  frmPhotoQuery.ShowModal;
  if ifPhoto then
    queryBaseInfo('','',IntToStr(iCustId));
  frmPhotoQuery.Free;
end;

procedure TfrmMain.btnOpenPictrueClick(Sender: TObject);
begin
  if opnmgndlg.Execute then
  begin
    imgShow.IO.LoadFromFile(opnmgndlg.FileName);
    if rotate=True then
    begin
      imgShow.Proc.Rotate(angle, True, ierFast,-1 );
      imgShow.Fit;
    end;
    btnSavePhoto.Enabled:=True;
    btnSaveAs.Enabled := True;
  end;
end;

procedure TfrmMain.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
  if Application.MessageBox('��ȷ��Ҫ�˳�����/�ƿ�����ϵͳ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    CanClose:=False;
end;

procedure TfrmMain.btnConnCamClick(Sender: TObject);
begin
  if m_connect then
  begin
    ShowMessage('���ȹر����������Ȼ���ٴ�����ͷ��');
    Exit;
  end;
  imgCam.Visible:=True;
  imgCam.Height := selectH;
  imgCanon.Height := 0;
  imgCanon.Visible:=False;
  shpSelect.Visible:=False;
  imgSrc.ShowVideo:= True;
  imgSrc.OnVideoFrame:=VideoFrame;
  btnSetCam.Enabled := true;
  btnCamFormat.Enabled := True;
  btnCamClose.Enabled := True;
  btnPhoto.Enabled := True;
  btnConnCam.Enabled := False;
  camType := 'cam';
end;

procedure TfrmMain.btnPhotoClick(Sender: TObject);
begin
  if lblCustNo.Caption = '' then
  begin
    ShowMessage('���Ȳ�ѯ��Ҫ���յ���Ա��Ȼ�������գ�');
    edtStuempNo.SetFocus;
    Exit;
  end;
  if camType='cam' then
  begin
    if not imgCam.IsEmpty then
    begin
      imgCam.Proc.SelCopyToClip;
      imgShow.Proc.PasteFromClipboard;
    end;
  end
  else if camType='canon' then
  begin
    saveCononPhotoToDisk;
  end
  else
  begin
    showmessage('û�к�����Ƭ�����豸�������豸�Ƿ�������ȷ��');
    Exit;
  end;
  btnSavePhoto.Enabled:=True;
  btnSaveAs.Enabled:=True;
end;

procedure TfrmMain.btnCamCloseClick(Sender: TObject);
begin
  imgSrc.ShowVideo:=False;
  imgSrc.OnVideoFrame:=nil;
  imgCam.Visible:=False;
  btnConnCam.Enabled := True;
  btnPhoto.Enabled := False;
  btnSetCam.Enabled := False;
  btnCamFormat.Enabled := False;
  btnCamClose.Enabled := False;
end;

procedure TfrmMain.cutPhoto(savePhotoName:string);
var
  ExtendName: string;
  Srcjpeg,Destjpeg: Tjpegimage;
  //newbmp: TBitmap;
  SrcBmp, DestBmp: TBitmap;
  width,height,left:Integer;
begin
  SrcBmp:=nil;
  DestBmp:=nil;
  Srcjpeg:=nil;
  Destjpeg:=nil;
  ExtendName := ExtractFileExt(savePhotoName);
  try
    SrcBmp := TBitmap.Create;
    Srcjpeg := Tjpegimage.Create;
    if ExtendName = '.jpg' then
    begin
      Srcjpeg.LoadFromFile(savePhotoName);
      SrcBmp.Assign(Srcjpeg);
    end
    else if ExtendName = '.bmp' then
    begin
      SrcBmp.LoadFromFile(savePhotoName);
    end;

    height := SrcBmp.Height;
    width := Round(height*3/4+0.5);
    left := Round(SrcBmp.Width*shpselectleft/imgW+0.5);
    DestBmp := TBitmap.Create;
    DestBmp.Width := width;
    DestBmp.Height := height;

    DestBmp.Canvas.CopyRect(Rect(0, 0, width, height), SrcBmp.Canvas, Rect(left, 0, width+left, height));

    Destjpeg := TJPEGImage.Create;
    Destjpeg.Assign(DestBmp);
    Destjpeg.SaveToFile(savePhotoName);
    //DestBmp.SaveToFile(savePhotoName);
  finally
    SrcBmp.Free;
    DestBmp.Free;
    Srcjpeg.Free;
    Destjpeg.Free;
  end;
end;

procedure TfrmMain.VideoFrame(Sender: TObject; Bitmap: TIEDibBitmap);
begin
  Bitmap.CopyToTBitmap( imgCam.Bitmap );
  imgCam.Update;
  imgCam.Fit;
end;

procedure TfrmMain.imgCamViewChange(Sender: TObject; Change: Integer);
begin
  if imgCam.Selected then
    Exit;
  imgCam.Select(0,0,selectW,selectH);

end;

procedure TfrmMain.btnSetCamClick(Sender: TObject);
begin
	if not imgSrc.DoConfigureSource then
		MessageDlg('���ܴ���������ͷ�Ի���',mtInformation,[mbOK],0);
end;

procedure TfrmMain.btnCamFormatClick(Sender: TObject);
begin
   if not imgSrc.DoConfigureFormat then
	   MessageDlg('���ܴ�����ͷ��ʽ�Ի���',mtInformation,[mbOK],0);
end;

procedure TfrmMain.N18Click(Sender: TObject);
begin
  try
    imgShow.Proc.DoPreviews(ppeColorAdjust);
  except
  end;
end;

procedure TfrmMain.N19Click(Sender: TObject);
begin
  try
    imgShow.Proc.DoPreviews(ppeEffects);
  except
  end;
end;

procedure TfrmMain.N20Click(Sender: TObject);
begin
  try
    imgShow.Proc.RemoveRedEyes;
  except
  end;
end;      

procedure TfrmMain.btnConnectCanClick(Sender: TObject);
var
  ss:psGetZoomPostionType;
begin
  if btnCamClose.Enabled then
    btnCamCloseClick(Sender);
  try
    m_connect:=psTConnect();
  except
    ShowMessage('���������ʧ�ܣ����´�...');
    Exit;
  end;
  if m_connect then
  begin
    imgCanon.Visible:=True;
    shpSelect.Visible:=True;
    imgCanon.Height := selectH;
    drawShpSelect;
    imgCam.Height := 0;
    imgCam.Visible:=False;
    grpPhotoSet.Visible:=True;
    btnPhotoShow.Enabled:=True;
    btnPhotoClose.Enabled:=False;
    btnPhoto.Enabled := False;
    btnCloseCanon.Enabled:=True;
    btnConnectCan.Enabled:=False;
    try
      psTReleaseStart(psRelModeOnlyToPC,psRelDataKingTakeBothThumbAndPic);
      psRegisterViewfinderCallbackFunction(@ViewfinerCallbackFunction);
      psRegisterProgressCallbackFunction(@ProgressCallbackFunction);
    except
      ShowMessage('��������ʧ�ܣ������´��������...');
    end;

    ss:=psTReleaseGetZoomPosition;
    trckbr1.Max := ss.MaxOpticalZoom;
    trckbr1.Position := ss.CurrentPos;
    camType := 'canon';
  end
  else
    ShowMessage('���������豸�������豸�����Ƿ���ȷ��');
end;

procedure TfrmMain.btnPhotoShowClick(Sender: TObject);
begin
  If m_connect then
  begin
    try
      psTReleaseStartViewFinder;
    except
      ShowMessage('��ʾͼ��ʧ�ܣ�������ʾ...');
      Exit;
    end;
    btnPhoto.Enabled := True;
    btnPhotoClose.Enabled:=True;
    btnPhotoShow.Enabled:=False;
  end;
end;

procedure TfrmMain.btnPhotoCloseClick(Sender: TObject);
begin
  try
    psTReleaseStopViewFinder;
  except
    ShowMessage('�ر�ͼ��ʧ�ܣ����¹ر�...');
    Exit;
  end;
  btnCloseCanon.Enabled:=True;
  btnPhotoShow.Enabled:=True;
  
  imgCanon.Picture.Assign(nil);
end;

//******************************************************************************
//��������������**************************************************************
{-------------------------------------------------------------------------------
  ������:    TFormViewfinder.getImageSizeAndQuality
  ����:      hanjiwei
  ����:      2007.03.05
  ����:      inData: Integer
  ����ֵ:    Integer  9:��8����1��7��2��6С   ��1һ�㣬2��ϸ��3����ϸ
-------------------------------------------------------------------------------}
function TfrmMain.getImageSizeAndQuality(inData: Integer): Integer;
begin
  case inData of
    0:Result:=93;
    1:Result:=92;
    2:Result:=91;
    3:Result:=83;
    4:Result:=82;
    5:Result:=81;
    6:Result:=73;
    7:Result:=72;
    8:Result:=71;
    9:Result:=63;
    10:Result:=62;
    11:Result:=61;
    else
      Result := 10;
  end;
end;

procedure TfrmMain.setFlash(inData: Integer);
begin
  case inData of
    0: setRemoteParam.StrobeSetting := psRemoteFormatFlashOff;
    1: setRemoteParam.StrobeSetting := psRemoteFormatFlashAuto;
    2: setRemoteParam.StrobeSetting := psRemoteFormatFlashOn;
    3: setRemoteParam.StrobeSetting := psRemoteFormatFlashAutoRedEye;
    4: setRemoteParam.StrobeSetting := psRemoteFormatFlashOnRedEye;
  else
    setRemoteParam.StrobeSetting := psRemoteFormatFlashNotUsed;
  end;
end;

procedure TfrmMain.setImageQuality(inData: Integer);
var
  ss:string;
begin
  ss:=Copy(IntToStr(inData),2,1);
  case StrToInt(ss) of
    3: setRemoteParam.CompQuality:= psRemoteFormatQualitySuperfine;
    2: setRemoteParam.CompQuality:= psRemoteFormatQualityFine;
    1: setRemoteParam.CompQuality := psRemoteFormatQualityNormal;
  else
    setRemoteParam.CompQuality := psRemoteFormatQualityNotUsed;
  end;
end;

procedure TfrmMain.setImageSize(inData: Integer);
var
  ss:string;
begin
  ss:=Copy(IntToStr(inData),0,1);
  case StrToInt(ss) of
    9: setRemoteParam.ImageSize:= psRemoteFormatSizeMedium;
    8: setRemoteParam.ImageSize:= psRemoteFormatSizeMedium1;
    7: setRemoteParam.ImageSize := psRemoteFormatSizeMedium2;
    6: setRemoteParam.ImageSize := psRemoteFormatSizeSmall;
  else
    setRemoteParam.ImageSize := psRemoteFormatSizeNotUsed;
  end;
end;

procedure TfrmMain.setISO(inData: Integer);
begin
  case inData of
    0: setRemoteParam.ISO := psRemoteFormatISO50;
    1: setRemoteParam.ISO := psRemoteFormatISO100;
    2: setRemoteParam.ISO := psRemoteFormatISO200;
    3: setRemoteParam.ISO := psRemoteFormatISO400;
    4: setRemoteParam.ISO := psRemoteFormatISOAuto;
  else
    setRemoteParam.ISO := psRemoteFormatISONotUsed;
  end;
end;

procedure TfrmMain.setPhotoEffect(inData: Integer);
begin
  case inData of
    0: setRemoteParam.PhotoEffect := psRemoteFormatPhotoEffectOff;
    1: setRemoteParam.PhotoEffect := psRemoteFormatPhotoEffectVivid;
    2: setRemoteParam.PhotoEffect := psRemoteFormatPhotoEffectNeutral;
    3: setRemoteParam.PhotoEffect := psRemoteFormatPhotoEffectLowSharpening;
    4: setRemoteParam.PhotoEffect := psRemoteFormatPhotoEffectSepia;
    5: setRemoteParam.PhotoEffect := psRemoteFormatPhotoEffectBW;
  else
    setRemoteParam.PhotoEffect := psRemoteFormatPhotoEffectNotUsed;
  end;
end;

procedure TfrmMain.setWhiteBalance(inData: Integer);
begin
  case inData of
    0: setRemoteParam.WhiteBalanceSetting := psRemoteFormatWBAuto;
    1: setRemoteParam.WhiteBalanceSetting := psRemoteFormatWBDaylight;
    2: setRemoteParam.WhiteBalanceSetting := psRemoteFormatWBCloudy;
    3: setRemoteParam.WhiteBalanceSetting := psRemoteFormatWBTungsten;
    4: setRemoteParam.WhiteBalanceSetting := psRemoteFormatWBFluorscent;
    5: setRemoteParam.WhiteBalanceSetting := psRemoteFormatWBFluorescentLight;
    6: setRemoteParam.WhiteBalanceSetting := psRemoteFormatWBCustom;
  else
    setRemoteParam.WhiteBalanceSetting := psRemoteFormatWBNotUsed;
  end;
end;

procedure TfrmMain.trckbr1Change(Sender: TObject);
begin
  if m_connect then
  begin
    psTReleaseSetZoomPosition(trckbr1.Position);
  end;
end;

//�������������أ�������******************************************************
//******************************************************************************
//******************************************************************************

procedure TfrmMain.btnSetParamClick(Sender: TObject);
begin
  if m_connect then
  begin
    setImageQuality(getImageSizeAndQuality(cbbImageSize.ItemIndex));
    setImageSize(getImageSizeAndQuality(cbbImageSize.ItemIndex));
    setWhiteBalance(cbbWhiteBalance.ItemIndex);
    setISO(cbbISO.ItemIndex);
    setFlash(cbbFlash.ItemIndex);
    setPhotoEffect(cbbPhotoEffect.ItemIndex);
    try
      psTReleaseSetParams(setRemoteParam);
    except
      ShowMessage('���������������ʧ�ܣ���������...');
    end;
  end;
end;

procedure TfrmMain.btnCloseCanonClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ�ر��������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if m_connect then
  begin
    psTReleaseEnd;
    psTDisconnect;
    m_connect := False;
  end;
  grpPhotoSet.Visible:=False;
  shpSelect.Visible := False;
  imgCanon.Visible := False;
  btnPhotoShow.Enabled:=False;
  btnPhotoClose.Enabled:=False;
  btnCloseCanon.Enabled:=False;
  btnConnectCan.Enabled:=True;
end;

procedure TfrmMain.FormDestroy(Sender: TObject);
begin
  try
    if m_connect then
    begin
      psTReleaseEnd;
      psTDisconnect;
    end;
    psTFinishSDK();
  except
    //ShowMessage('�ر��������ʧ�ܣ����¹ر�...');
  end;

end;

procedure TfrmMain.shpSelectMouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
var
  shpLeft:integer;
  shpTop:integer;
  shpRight:integer;
  //shpBtom:integer;
begin
  shpLeft:=shpSelect.Left+X-xPos;
  //shpTop:=shpSelect.Top+Y-yPos;
  shpRight:=shpSelect.Left+X-xPos+shpSelect.Width;
  //shpBtom:=shpSelect.Top+Y-yPos+shpSelect.Height;
  if shpRight>imgCanon.Width then
    shpLeft:=imgCanon.Width-shpSelect.width;
  //if shpBtom>imgCanon.Height then
    //shpTop:=imgCanon.Height-shpSelect.Height;
  if shpLeft<=0 then
    shpLeft:=0;
  //if shpTop<=0 then
  shpTop:=0;

  if (leftMouse)then
  begin
      shpSelect.Left:=shpLeft;
      shpSelectLeft := shpLeft;
      shpSelect.Top:=shpTop;
  end;
end;

procedure TfrmMain.shpSelectMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if button=mbleft then
  begin
    yPos:=y;
    xPos:=x;
    leftMouse:=true;
  end
  else
  begin
    leftMouse:=false;
  end;
end;

procedure TfrmMain.shpSelectMouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if button=mbleft then
    leftMouse:=false;
end;

procedure TfrmMain.drawShpSelect;
begin
  shpSelect.Height := selectH;
  shpSelect.Width := selectW;
end;

procedure TfrmMain.saveCononPhotoToDisk;
var
  filename,filename2:string;
  sa,sa2:array[0..280] of char;
begin
  filename:=apppath+lblCustNo.Caption+'.jpg';
  filename2:=apppath+lblCustNo.Caption+'.jpg';
  if m_connect then
  begin
    try
      m_p1:=psTReleaseGetParams();
      psTrelease(psTReleaseDoSupportRemote);
      strpcopy(sa,filename);
      strpcopy(sa2,filename2);
      psTReleaseGetThumbnail(sa2);
      psTReleaseGetPicture(sa);
    except
      ShowMessage('��Ƭ����ʧ�ܣ�����������...');
      Exit;
    end;
  end;
  //������Ƭ
  cutPhoto(filename);
  //���뵽Ԥ����
  imgShow.IO.LoadFromFile(filename);
  //ɾ����Ƭ
  DeleteFile(filename);
end;

procedure TfrmMain.btnSaveAsClick(Sender: TObject);
begin
  if svmgndlg1.Execute then
  begin
    imgShow.IO.SaveToFile(svmgndlg1.FileName);
  end;
end;

procedure TfrmMain.N21Click(Sender: TObject);
begin
  frmModifyPwd := TfrmModifyPwd.Create(nil);
  frmModifyPwd.ShowModal;
  frmModifyPwd.Free;
end;

procedure TfrmMain.N15Click(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ�˳�����/�ƿ�����ϵͳ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idyes then
    Application.Terminate;

end;

procedure TfrmMain.N22Click(Sender: TObject);
begin
  if judgelimit(loginLimit,mdl_custImport)=False then
  begin
    ShowMessage('��û�в��������Ȩ�ޣ�');
    Exit;
  end;
  frmCustImport := TfrmCustImport.Create(nil);
  frmCustImport.ShowModal;
  frmCustImport.Free;
end;

procedure TfrmMain.btnGetPhotoClick(Sender: TObject);
begin
  if lblCustNo.Caption = '' then
  begin
    ShowMessage('���Ȳ�ѯ��Ҫ���յ���Ա��Ȼ�������գ�');
    edtStuempNo.SetFocus;
    Exit;
  end;

  //��Ӳ����ȡ���Ѿ��������Ƭ
  if FileExists(photopath+'\'+photopre+'.jpg') then
  begin
    imgShow.IO.LoadFromFile(photopath+'\'+photopre+'.jpg');
    if rotate=True then
    begin
      imgShow.Proc.Rotate(angle, True, ierFast,-1 );
      imgShow.Fit;
    end;
    btnSavePhoto.Enabled:=True;
    btnSaveAs.Enabled:=True;
  end
  else
    ShowMessage('Ҫȡ����Ƭ��'+photopath+'\'+photopre+'.jpg �����ڣ�����·���Ƿ���ȷ��');
end;

procedure TfrmMain.N23Click(Sender: TObject);
begin
  frmGetPhotoSet := TfrmGetPhotoSet.Create(nil);
  frmGetPhotoSet.ShowModal;
  frmGetPhotoSet.Free;
end;

procedure TfrmMain.edtStuempNoKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
    btnQuery.Click;
end;

procedure TfrmMain.getPrintMenu(sender: TObject);
var
  i:Integer;
  custM:TMenuItem;
begin
  try
    cbbMenu.Items.Clear;
    cbbMenu.Items.LoadFromFile(apppath+'printset\printmenu.txt');
    for i := 0 to cbbMenu.Items.Count-1 do
    begin
      custM := TMenuItem.Create(Self);
      custM.Tag := i;
      custM.Caption := cbbMenu.Items.Strings[i];
      N10.Add(custM);
      custM.OnClick := openPrintM;
    end;
  except
    on e:Exception do
    begin
      ShowMessage('�����û��Զ���˵�ʧ��--'+e.Message);
    end;
  end;
end;

procedure TfrmMain.openPrintM(sender: TObject);
var
  Item: TMenuItem;
  printType:string;
begin
  Case TMenuItem(Sender).tag of
    0..1000 : printType := Item.Caption;//ShowMessage(Item.Caption);
    -9991 : ShowMessage(Item.Items[0].Caption);
  end;

  frmCardPrintTemp:=TfrmCardPrintTemp.create(nil);
  frmCardPrintTemp.cardType := Trim(printType);
  frmCardPrintTemp.ShowModal;
  frmCardPrintTemp.Free;

end;

end.

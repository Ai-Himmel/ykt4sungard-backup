unit mainUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, ExtCtrls, StdCtrls, Buttons, ComCtrls, SkinCaption,
  WinSkinData, jpeg, DB, ADODB, DBCtrls, imageenio, ieview, imageenview,
  hyieutils, ieopensavedlg, imageenproc, ievect, videocap,PSCAMLIB,ksPicHandler,IniFiles;

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
    bvlCustId: TBevel;
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
    shpL: TShape;
    shpT: TShape;
    shpR: TShape;
    shpB: TShape;
    shpA: TShape;
    btn1: TButton;
    cbbMenu: TComboBox;
    lbl2: TLabel;
    lblPhotoNum: TLabel;
    sbZI: TSpeedButton;
    sbRL: TSpeedButton;
    sbRR: TSpeedButton;
    sbZO: TSpeedButton;
    sbLeft: TSpeedButton;
    sbDown: TSpeedButton;
    sbUp: TSpeedButton;
    sbRight: TSpeedButton;
    imgShowPhoto: TImage;
    PicFrame: TShape;
    shpLeft: TShape;
    shpRight: TShape;
    shpTop: TShape;
    btnPhotoCopy: TButton;
    N24: TMenuItem;
    Excel1: TMenuItem;
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
    procedure btn1Click(Sender: TObject);
    procedure sbZIClick(Sender: TObject);
    procedure sbRLClick(Sender: TObject);
    procedure sbZOClick(Sender: TObject);
    procedure sbRRClick(Sender: TObject);
    procedure sbLeftClick(Sender: TObject);
    procedure sbUpClick(Sender: TObject);
    procedure sbDownClick(Sender: TObject);
    procedure sbRightClick(Sender: TObject);
    procedure btnPhotoCopyClick(Sender: TObject);
    procedure N24Click(Sender: TObject);
    procedure Excel1Click(Sender: TObject);
  private
    { Private declarations }
    //FCap : TCapture;
    camType:string;//相机类型，canon为数码相机，cam为摄像头
    shpSelectLeft : Integer;
    m_p1,setRemoteParam:psRemoteReleaseParameters;
    m_connect:boolean;
    FPicHandler: TksPicHandler;
    procedure clearCaption();

    procedure fillCbb();

    procedure queryBaseInfo(sstuempNo:string;sareaId:string;scustId:string);

    procedure queryPhoto(scustId:string);

    procedure cutPhoto(savePhotoName:string);

    procedure VideoFrame(Sender: TObject; Bitmap: TIEDibBitmap);

    procedure drawShpSelect();

    procedure setViewBoxPosi(leftP:Integer);

    procedure saveCononPhotoToDisk();

    procedure setViewBoxVisible(param:Boolean);

    procedure getPrintMenu(sender:TObject);

    procedure openPrintM(sender:TObject);

    //设置相机参数
    function getImageSizeAndQuality(inData:Integer):Integer;
    procedure setImageSize(inData:Integer);
    procedure setImageQuality(inData:Integer);
    procedure setWhiteBalance(inData:Integer);
    procedure setISO(inData:Integer);
    procedure setFlash(inData:Integer);
    procedure setPhotoEffect(inData:Integer);
    procedure readCamParam;
    procedure writeCamParam;
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
  uGetPhotoSet, uCardPrintTemp, phtImportData, UPhotoCopy, uPhotoPatchCopy,
  uPhotoPExp;

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
        ShowMessage(e.Message+'--该错误可能是由硬件冲突引起的，请使用相机自带的拍照软件！');
      end;
      try
      Jpg := TJpegImage.Create;
      try
        mem_stream.Position := 0;
        Jpg.LoadFromStream(mem_stream);
      except on e1:Exception do
        ShowMessage(e1.Message+'--硬件冲突，请使用相机自带的拍照软件！');
      end;
      frmMain.imgCanon.picture.Assign(Jpg);
      finally
        Jpg.Free;
      end;
    finally
      mem_stream.Free;
    end;
  except
    ShowMessage('可能是驱动问题，请重新打开数码相机试试...');
  end;
end;

procedure ProgressCallbackFunction(p:integer); cdecl;
begin
  try
    frmMain.pb.Position:=p;
  except
    ShowMessage('系统错误，不影响使用，请继续...');
  end;
end;

procedure TfrmMain.N11Click(Sender: TObject);
begin
  {
  if judgelimit(loginLimit,Mdl_stuPrint)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  frmCardPrint := TfrmCardPrint.Create(nil);
  frmCardPrint.cardType := 'stu';
  frmCardPrint.ShowModal;
  frmCardPrint.Free; }
  frmCardPrintTemp:=TfrmCardPrintTemp.create(Self);
  frmCardPrintTemp.cardType := '卡片打印';
  frmCardPrintTemp.ShowModal;
  frmCardPrintTemp.Free;
end;

procedure TfrmMain.N12Click(Sender: TObject);
begin
  {
  if judgelimit(loginLimit,Mdl_empPrint)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
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
  //连接相机sdk
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
var
  sqlstr:string;
  ARect: TRect;
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
  frmMain.Caption := '拍照/制卡管理系统--'+loginName;
  clearCaption();
  fillCbb();
  btnDelPhoto.Enabled:=False;
  btnEditInfo.Enabled:=False;
  btnSavePhoto.Enabled := False;
  shpSelect.Visible := False;
  imgCanon.Visible := False;
  grpPhotoSet.Visible := False;
  shpL.Visible := False;
  shpT.Visible := False;
  shpR.Visible := False;
  shpB.Visible := False;
  shpA.Visible := False;
  getPrintMenu(Sender);
  sqlstr := 'select count(*)num from '+tblPhoto+' where '+pPhotoDate+'>'+QuotedStr('15000101');
  lblPhotoNum.Caption := sqlExec(sqlstr,'num');

  //imgShow.IO.LoadFromFile('D:\20090319\30026.jpg');
  //imgShow.
  FPicHandler := TksPicHandler.Create(imgShowPhoto);
  ARect := Rect(PicFrame.Left, PicFrame.Top,
    PicFrame.Left + PicFrame.Width, PicFrame.Top + PicFrame.Height);
  FPicHandler.SetFrame(ARect);

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
      //执行照片库中信息插入操作
      insertPhotoData(Trim(lblCustNo.Caption),Trim(lblStuEmpNo.Caption));
      
      queryPhoto(qryExecSQL.fieldbyname(custId).AsString);

      Fjpg := getPhotoInfo(qryExecSQL.fieldbyname(custId).AsString);
      if Fjpg=nil then
        pnlphoto.Caption := '没有原始照片'
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
      ShowMessage('客户信息表无相关信息，请重新指定查询条件！');
    end;
  finally
    Fjpg.Free;
    qryExecSQL.Destroy;
  end;
end;

procedure TfrmMain.btnQueryClick(Sender: TObject);
var
  sqlstr:string;
begin
  if (Trim(edtStuempNo.Text)='')and(cbbArea.Text='') then
  begin
    ShowMessage('请输入查询条件，然后再查询！');
    edtStuempNo.SetFocus;
    Exit;
  end;
  queryBaseInfo(Trim(edtStuempNo.Text),subString(cbbArea.Text,'-','l'),'');
  sqlstr := 'select count(*)num from '+tblPhoto+' where '+pPhotoDate+'>'+QuotedStr('15000101');
  lblPhotoNum.Caption := sqlExec(sqlstr,'num');
end;

procedure TfrmMain.N8Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_import)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
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
    ShowMessage('你没有操作该项的权限！');
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
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  if qryPhoto.IsEmpty then
  begin
    ShowMessage('没有你要查询的照片信息，无法删除！');
    Exit;
  end;
  if Application.MessageBox(PChar('你确定要删除照片信息吗？'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
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
    ShowMessage('你没有操作该项的权限！');
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
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  if lblCustNo.Caption='' then
  begin
    ShowMessage('请先查询要修改的人员信息，然后修改！');
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
    ShowMessage('你没有操作该项的权限！');
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
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  frmLimit:=TfrmLimit.Create(nil);
  frmLimit.ShowModal;
  frmLimit.Free;
end;

procedure TfrmMain.btnSavePhotoClick(Sender: TObject);
var
  F: TmemoryStream;
  oldJpeg:TJPEGImage;
  FJpeg: TJpegImage;
  filename:string;
  {
  tmpBmp:TBitmap;
  OldGraphics : TBitmap;
  expJpg:TJPEGImage;
  FMin:TmemoryStream;
  }
begin
  if judgelimit(loginLimit,mdl_savephoto)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  if qryPhoto.IsEmpty then
  begin
    ShowMessage('请先查出要保存照片的人员信息，然后再保存照片！');
    Exit;
  end;
  if imgShow.Bitmap=nil then
  begin
    ShowMessage('请先拍照或打开要保存的照片，然后再保存！');
    Exit;
  end;
  oldJpeg := getPhotoInfo(lblCustNo.Caption);
  if oldJpeg<>nil then
    if Application.MessageBox(PChar('客户号为['+lblcustNo.Caption+']姓名为['+lblName.caption+']的照片已经存在，你要覆盖以前的照片吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;
  F := nil;
  FJpeg := nil;
  {
  OldGraphics := nil;
  tmpBmp := nil;
  expJpg:=nil;
  }
  qryPhoto.Edit;
  try
    filename:=apppath+lblCustNo.Caption+'.jpg';
    FPicHandler.SaveToFile(filename);
    FJpeg := TJpegImage.Create;
    FJpeg.LoadFromFile(filename);
    DeleteFile(filename);
    //FJpeg.Assign(imgShow.Bitmap);
    F := TmemoryStream.Create;
    FJpeg.SaveToStream(F);
    if F.Size>600000 then
    begin
      ShowMessage('该张照片过大，拍摄的照片请不要超过600K!');
      Exit;
    end;

    {
    //保存小照片
    OldGraphics := TBitmap.Create;
    //先把jpg格式的照片转换为bmp格式
    OldGraphics.Assign(FJpeg);
    //重新定义照片的大小
    tmpBmp := TBitmap.Create;
    tmpBmp.Width := minWidth;
    tmpBmp.Height := minHeight;
    tmpBmp.Canvas.StretchDraw(Rect(0, 0, tmpBmp.Width, tmpBmp.Height),OldGraphics);

    //重新把照片转换为jpg格式
    expJpg := TJPEGImage.Create;
    expJpg.Assign(tmpBmp);
    FMin := TmemoryStream.Create;
    expJpg.SaveToStream(FMin);
    }
    //保存到本地
    if not DirectoryExists(diskpath) then
      if CreateDir(diskpath)=False then
        ShowMessage('不能创建文件夹：'+diskPath+'请检查是否存在该磁盘！');
    try
      f.SaveToFile(diskpath+'\'+lblstuempno.Caption+'.jpg');
    except
    end;
    TBlobField(qryPhoto.FieldByName(pPhoto)).loadfromStream(F);
    //TBlobField(qryPhoto.FieldByName(PMinPhoto)).loadfromStream(FMin);
    qryPhoto.FieldByName(pPhotoDate).asstring := formatdatetime('yyyymmdd', date);
    qryPhoto.FieldByName(pPhotoTime).asstring := formatdatetime('HHMMSS', now);
    //加入精确时间，格式yyyymmddhhmmsszzz,现在支持oracle和db2-----------------------]]]]]]]]]]]]]
    qryPhoto.FieldByName(pPhotoDTime).asstring := getDbTime;


    qryPhoto.Post;
    imgShow.Assign(nil);
    imgShowPhoto.Picture.Graphic := nil;
    pnlPhotoMain.Caption:='照片保存成功';
    btnSavePhoto.Enabled := False;
    btnSaveAs.Enabled:=False;
    queryBaseInfo('','',lblCustNo.Caption);
    if useRemoteSoft then
      delFileBat(photopath,'*.jpg');
  finally
    F.Destroy;
    FJpeg.Destroy;
    {
    OldGraphics.Destroy;
    tmpBmp.Destroy;
    expJpg.Destroy;
    FMin.Destroy;
    }
  end;
end;

procedure TfrmMain.N6Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_photoQuery)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
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
    FPicHandler.LoadFromFile(opnmgndlg.FileName);
    //imgShowPhoto.Picture.LoadFromFile(opnmgndlg.FileName);
    //imgShowPhoto.Picture.Assign(imgShow.Bitmap);
    btnSavePhoto.Enabled:=True;
    btnSaveAs.Enabled := True;
  end;
end;

procedure TfrmMain.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
  if Application.MessageBox('你确定要退出拍照/制卡管理系统吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    CanClose:=False;
end;

procedure TfrmMain.btnConnCamClick(Sender: TObject);
begin
  if m_connect then
  begin
    ShowMessage('请先关闭数码相机，然后再打开摄像头！');
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
var
  filename:string;
begin
  if lblCustNo.Caption = '' then
  begin
    ShowMessage('请先查询出要拍照的人员，然后再拍照！');
    edtStuempNo.SetFocus;
    Exit;
  end;
  if camType='cam' then
  begin
    if not imgCam.IsEmpty then
    begin
      filename:=apppath+lblCustNo.Caption+'.jpg';
      imgCam.Proc.SelCopyToClip;
      imgShow.Proc.PasteFromClipboard;
      imgShow.IO.SaveToFile(filename);
      imgShowPhoto.Picture.LoadFromFile(filename);
      DeleteFile(filename);
    end;
  end
  else if camType='canon' then
  begin
    saveCononPhotoToDisk;
  end
  else
  begin
    showmessage('没有合适照片拍摄设备，请检查设备是否连接正确！');
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
		MessageDlg('不能打开设置摄像头对话框！',mtInformation,[mbOK],0);
end;

procedure TfrmMain.btnCamFormatClick(Sender: TObject);
begin
   if not imgSrc.DoConfigureFormat then
	   MessageDlg('不能打开摄像头格式对话框！',mtInformation,[mbOK],0);
end;

procedure TfrmMain.N18Click(Sender: TObject);
begin
  try
    imgShow.Proc.DoPreviews(ppeColorAdjust);
    //imgShowPhoto.Picture.Assign(imgShow.Bitmap);
  except
  end;
end;

procedure TfrmMain.N19Click(Sender: TObject);
begin
  try
    imgShow.Proc.DoPreviews(ppeEffects);
    //imgShowPhoto.Picture.Assign(imgShow.Bitmap);
  except
  end;
end;

procedure TfrmMain.N20Click(Sender: TObject);
begin
  try
    imgShow.Proc.RemoveRedEyes;
    //imgShowPhoto.Picture.Assign(imgShow.Bitmap);
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
    ShowMessage('打开数码相机失败，重新打开...');
    Exit;
  end;
  if m_connect then
  begin
    imgCanon.Visible:=True;
    shpSelect.Visible:=True;
    getViewBoxConf;
    setViewBoxVisible(ve_visible);
    imgCanon.Height := selectH;
    drawShpSelect;
    if ve_visible then
      setViewBoxPosi(0);
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
      ShowMessage('驱动调用失败，请重新打开数码相机...');
    end;

    ss:=psTReleaseGetZoomPosition;
    trckbr1.Max := ss.MaxOpticalZoom;
    trckbr1.Position := ss.CurrentPos;
    camType := 'canon';
  end
  else
    ShowMessage('不能连接设备，请检查设备设置是否正确！');
end;

procedure TfrmMain.btnPhotoShowClick(Sender: TObject);
begin
  If m_connect then
  begin
    try
      psTReleaseStartViewFinder;
      readCamParam;
    except
      ShowMessage('显示图像失败，重新显示...');
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
    ShowMessage('关闭图像失败，重新关闭...');
    Exit;
  end;
  btnCloseCanon.Enabled:=True;
  btnPhotoShow.Enabled:=True;
  
  imgCanon.Picture.Assign(nil);
end;

//******************************************************************************
//相机参数设置相关**************************************************************
{-------------------------------------------------------------------------------
  过程名:    TFormViewfinder.getImageSizeAndQuality
  作者:      hanjiwei
  日期:      2007.03.05
  参数:      inData: Integer
  返回值:    Integer  9:大，8：中1，7中2，6小   ：1一般，2精细，3极精细
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

//相机参数设置相关（结束）******************************************************
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
      writeCamParam;
      psTReleaseSetParams(setRemoteParam);
    except
      ShowMessage('设置数码相机参数失败，重新设置...');
    end;
  end;
end;

procedure TfrmMain.btnCloseCanonClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要关闭照相机吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
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
  setViewBoxVisible(False);
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
    //ShowMessage('关闭数码相机失败，重新关闭...');
  end;

end;

procedure TfrmMain.shpSelectMouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
var
  shpLeft:integer;
  shpTop:integer;
  shpRight:integer;
begin
  shpLeft:=shpSelect.Left+X-xPos;
  shpRight:=shpSelect.Left+X-xPos+shpSelect.Width;
  if shpRight>imgCanon.Width then
    shpLeft:=imgCanon.Width-shpSelect.width;
  if shpLeft<=0 then
    shpLeft:=0;
  shpTop:=0;

  if (leftMouse)then
  begin
      shpSelect.Left:=shpLeft;
      shpSelectLeft := shpLeft;
      shpSelect.Top:=shpTop;

      setViewBoxPosi(shpLeft);
      //shp1.Left := shpSelect.Left+20;
      //shp1.Top := shpSelect.Top + 30;
      //Shape1.Left := shpSelect.Left + 30;
      //Shape1.Top := shpSelect.top + 20
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
      ShowMessage('照片拍摄失败，请重新拍摄...');
      Exit;
    end;
  end;
  //剪切照片
  cutPhoto(filename);
  //载入到预览框
  imgShow.IO.LoadFromFile(filename);
  //imgShowPhoto.Picture.Assign(imgShow.Bitmap);
  //载入到照片修剪框
  FPicHandler.LoadFromFile(filename);
  //删除照片
  DeleteFile(filename);
end;

procedure TfrmMain.btnSaveAsClick(Sender: TObject);
begin
  if svmgndlg1.Execute then
  begin
    //imgShow.IO.SaveToFile(svmgndlg1.FileName);
    imgShowPhoto.Picture.SaveToFile(svmgndlg1.FileName);
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
  if Application.MessageBox('你确定要退出拍照/制卡管理系统吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idyes then
    Application.Terminate;

end;

procedure TfrmMain.N22Click(Sender: TObject);
begin
  if judgelimit(loginLimit,mdl_custImport)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  //ImportData(frmdm.conn);

  frmCustImport := TfrmCustImport.Create(nil);
  frmCustImport.ShowModal;
  frmCustImport.Free;
  
end;

procedure TfrmMain.btnGetPhotoClick(Sender: TObject);
begin
  if lblCustNo.Caption = '' then
  begin
    ShowMessage('请先查询出要拍照的人员，然后再拍照！');
    edtStuempNo.SetFocus;
    Exit;
  end;

  //从硬盘中取得已经拍摄的照片
  if FileExists(photopath+'\'+photopre+'.jpg') then
  begin
    imgShow.IO.LoadFromFile(photopath+'\'+photopre+'.jpg');
    if rotate=True then
    begin
      imgShow.Proc.Rotate(angle, True, ierFast,-1 );
      imgShow.Fit;
    end;
    FPicHandler.LoadFromFile(photopath+'\'+photopre+'.jpg');
    if rotate=True then
      FPicHandler.Rotate(-angle);

    //imgShowPhoto.Picture.Assign(imgShow.Bitmap);
    btnSavePhoto.Enabled:=True;
    btnSaveAs.Enabled:=True;
  end
  else
    ShowMessage('要取的照片：'+photopath+'\'+photopre+'.jpg 不存在，请检查路径是否正确！');
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

procedure TfrmMain.setViewBoxVisible(param: Boolean);
begin
  shpL.Visible := param;
  shpT.Visible := param;
  shpR.Visible := param;
  shpB.Visible := param;
  shpA.Visible := param;
end;

procedure TfrmMain.setViewBoxPosi(leftP:Integer);
begin
  shpL.Top := veL_top;
  shpL.Left := leftP+veL_left;
  shpL.Height := veL_height;

  shpR.Top := veR_top;
  shpR.Left := leftP+veR_left;
  shpR.Height := veR_height;

  shpT.Top := veT_top;
  shpT.Left := leftP+veT_left;
  shpT.Width := veT_width;

  shpB.Top := veB_top;
  shpB.Left := leftP+veB_left;
  shpB.Width := veB_width;

  shpA.Top := veA_top;
  shpA.Left := leftP+veA_left;
  shpA.Width := veA_width;
end;

procedure TfrmMain.btn1Click(Sender: TObject);
begin
    imgCanon.Visible:=True;
    shpSelect.Visible:=True;
    getViewBoxConf;
    setViewBoxVisible(ve_visible);
    imgCanon.Height := selectH;
    drawShpSelect;
    if ve_visible then
      setViewBoxPosi(0);
    imgCam.Height := 0;
    imgCam.Visible:=False;

end;

{-------------------------------------------------------------------------------
  过程名:    TfrmMain.getPrintMenu得到用户自定义菜单
  作者:      hanjiwei
  日期:      2009.02.03
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfrmMain.getPrintMenu(sender:TObject);
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
      ShowMessage('加载用户自定义菜单失败--'+e.Message);
    end;
  end;
end;

procedure TfrmMain.openPrintM(sender:TObject);
var
  Item: TMenuItem;
  printType:string;
begin
  //try

    Case TMenuItem(Sender).tag of
      0..1000 : printType := TMenuItem(Sender).Caption;//ShowMessage(Item.Caption);
      -9991 : ShowMessage(Item.Items[0].Caption);
    end;

    frmCardPrintTemp:=TfrmCardPrintTemp.create(Self);
    frmCardPrintTemp.cardType := Trim(printType);
    frmCardPrintTemp.ShowModal;
    frmCardPrintTemp.Free;
    {
  except
    on e:Exception do
      ShowMessage(printType+inttostr(TMenuItem(Sender).tag)+'-'+e.Message);
  end;
  }
end;

procedure TfrmMain.sbZIClick(Sender: TObject);
begin
  FPicHandler.Zoom(+3);
end;

procedure TfrmMain.sbRLClick(Sender: TObject);
begin
  FPicHandler.Rotate(-0.011);
end;

procedure TfrmMain.sbZOClick(Sender: TObject);
begin
  FPicHandler.Zoom(-3);
end;

procedure TfrmMain.sbRRClick(Sender: TObject);
begin
  FPicHandler.Rotate(0.011);
end;

procedure TfrmMain.sbLeftClick(Sender: TObject);
begin
  FPicHandler.Move(Point(-2, 0));
end;

procedure TfrmMain.sbUpClick(Sender: TObject);
begin
  FPicHandler.Move(Point(0, -2));
end;

procedure TfrmMain.sbDownClick(Sender: TObject);
begin
  FPicHandler.Move(Point(0, 2));
end;

procedure TfrmMain.sbRightClick(Sender: TObject);
begin
  FPicHandler.Move(Point(2, 0));
end;

procedure TfrmMain.readCamParam;
var
  photoinifile:TIniFile;
  imgsize:Integer;
  whitebalance:Integer;
  photoeffect:Integer;
  iso:Integer;
  focus:Integer;
begin
  photoinifile := nil;
  if FileExists(apppath+'photo.ini') = false then
  begin
    Application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
      '系统错误！', mb_ok + mb_iconerror);
    Application.Terminate;
  end;
  try
    photoinifile := TIniFile.Create(apppath+'photo.ini');
    imgsize :=  photoinifile.ReadInteger('camparam','imgsize',0);
    whitebalance := photoinifile.ReadInteger('camparam','whitebalance',0);
    photoeffect := photoinifile.ReadInteger('camparam','photoeffect',0);
    iso := photoinifile.ReadInteger('camparam','iso',0);
    focus := photoinifile.ReadInteger('camparam','focus',0);
    cbbImageSize.ItemIndex := imgsize;
    cbbWhiteBalance.ItemIndex := whitebalance;
    cbbPhotoEffect.ItemIndex := photoeffect;
    cbbISO.ItemIndex := iso;
    trckbr1.Position := focus;
    btnSetParam.Click;
    if m_connect then
    begin
      psTReleaseSetZoomPosition(trckbr1.Position);
    end;

  finally
    photoinifile.Destroy;
  end;

end;

procedure TfrmMain.writeCamParam;
var
  photoinifile:TIniFile;
  imgsize:Integer;
  whitebalance:Integer;
  photoeffect:Integer;
  iso:Integer;
  focus:Integer;
begin
  photoinifile := nil;
  if FileExists(apppath+'photo.ini') = false then
  begin
    Application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
      '系统错误！', mb_ok + mb_iconerror);
    Application.Terminate;
  end;
  try
    photoinifile := TIniFile.Create(apppath+'photo.ini');
    photoinifile.WriteInteger('camparam','imgsize',cbbImageSize.ItemIndex);
    photoinifile.WriteInteger('camparam','whitebalance',cbbWhiteBalance.ItemIndex);
    photoinifile.WriteInteger('camparam','photoeffect',cbbPhotoEffect.ItemIndex);
    photoinifile.WriteInteger('camparam','iso',cbbISO.ItemIndex);
    photoinifile.WriteInteger('camparam','focus',trckbr1.Position);
  finally
    photoinifile.Destroy;
  end;
end;

procedure TfrmMain.btnPhotoCopyClick(Sender: TObject);
begin
  if judgelimit(loginLimit,mdl_photocopy)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  if Trim(lblStuEmpNo.Caption) = '' then
  begin
    ShowMessage('请先查询出要照片复制的人员，然后在操作！');
    Exit;
  end;
  if imgPhoto=nil then
  begin
    ShowMessage('请先拍照，然后在执行照片复制！');
    Exit;
  end;
  try
    frmPhotoCopy := TfrmPhotoCopy.Create(nil);
    frmPhotoCopy.oldStuempNo := lblStuEmpNo.Caption;
    frmPhotoCopy.custId := lblCustNo.Caption;
    frmPhotoCopy.patchSign := 0;
    //imgPhoto.Picture.Graphic.Assign(frmPhotoCopy.img.Picture.Graphic);
    //frmPhotoCopy.img.Picture.Graphic.Assign(imgPhoto.Picture.Graphic);
    frmPhotoCopy.ShowModal;
  finally
    frmPhotoCopy.Free;
  end;
end;

procedure TfrmMain.N24Click(Sender: TObject);
begin
  if judgelimit(loginLimit,mdl_photocopy)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  frmPhotoPatchCopy := TfrmPhotoPatchCopy.Create(nil);
  frmPhotoPatchCopy.ShowModal;
  frmPhotoPatchCopy.Free;
end;

procedure TfrmMain.Excel1Click(Sender: TObject);
begin
  if judgelimit(loginLimit,Mdl_export)=False then
  begin
    ShowMessage('你没有操作该项的权限！');
    Exit;
  end;
  frmPhotoPExp:=TfrmPhotoPExp.Create(nil);
  frmPhotoPExp.ShowModal;
  frmPhotoPExp.Free;

end;

end.

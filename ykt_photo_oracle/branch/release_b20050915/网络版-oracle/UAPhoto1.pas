unit UAPhoto1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Db, ADODB, Mask, DBCtrls, ExtCtrls, FileCtrl, inifiles, Jpeg,
  ComCtrls, DBTables, Grids, DBGrids, Menus, ShellAPI, Buttons, ksPicHandler;

type
  TPhotoSystem = class(TForm) //查询出学工的真正记录，
    DataSource1: TDataSource; //用于连接数据库，
    Panel1: TPanel;
    Label1: TLabel;
    Panel2: TPanel;
    Label2: TLabel;
    Edit1: TEdit;
    Button1: TButton; //“查询”按钮，
    Panel3: TPanel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Panel4: TPanel; //“取照片”按钮，
    Label8: TLabel;
    Edit2: TEdit;
    Label9: TLabel;
    Edit3: TEdit;
    Label7: TLabel;
    Edit4: TEdit;
    Button5: TButton; //用于显示新拍照片，
    Button6: TButton;
    Button7: TButton;
    Label10: TLabel;
    Label11: TLabel;
    Panel6: TPanel;
    Image2: TImage; //“相机首选项”菜单，
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    DBEdit1: TDBEdit;
    DBEdit2: TDBEdit;
    Edit5: TEdit;
    DBEdit4: TDBEdit;
    Label16: TLabel;
    Label17: TLabel; //获取专业名称，
    ADOQuery4: TADOQuery; //统计已拍照片人数，
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    MainMenu1: TMainMenu;
    file1: TMenuItem;
    N2: TMenuItem;
    count1: TMenuItem;
    N1: TMenuItem;
    N3: TMenuItem;
    N4: TMenuItem;
    N5: TMenuItem;
    Button8: TButton;
    Edit7: TEdit;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    LPicture: TLabel;
    ADOQuery1: TADOQuery;
    BitBtn1: TBitBtn;
    ADOQuery2: TADOQuery;
    N6: TMenuItem;
    N7: TMenuItem;
    Edit6: TEdit;
    N8: TMenuItem;
    N9: TMenuItem;
    N10: TMenuItem;
    N11: TMenuItem;
    btnDelPic: TButton;
    pnlHandlePic: TPanel;
    sbZI: TSpeedButton;
    sbZO: TSpeedButton;
    sbRL: TSpeedButton;
    sbRR: TSpeedButton;
    sbUp: TSpeedButton;
    sbLeft: TSpeedButton;
    sbRight: TSpeedButton;
    sbDown: TSpeedButton;
    pnlPic: TPanel;
    imgPic: TImage;
    PicFrame: TShape;
    shpTop: TShape;
    shpLeft: TShape;
    shpRight: TShape;
    shpCenter: TShape;
    Shape1: TShape;
    Shape2: TShape;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    btnExit: TButton;
    N12: TMenuItem;
    {查询}
    procedure Button1Click(Sender: TObject);
    {取照片，}
    procedure Button2Click(Sender: TObject);
    {确认，}
    procedure Button3Click(Sender: TObject);
    {取消，}
    procedure Button4Click(Sender: TObject);
    {初始化时，读取配置文件，}
    procedure FormCreate(Sender: TObject);
    {修改相机顺序号，}
    procedure Button5Click(Sender: TObject);
    {确认修改，}
    procedure Button6Click(Sender: TObject);
    {取消修改，}
    procedure Button7Click(Sender: TObject);
    procedure Edit1KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormClick(Sender: TObject);
    {显示前，做一次统计，}
    procedure FormShow(Sender: TObject);
    {处理提交错误，}
    procedure ADOQuery1PostError(DataSet: TDataSet; E: EDatabaseError;
      var Action: TDataAction);
    procedure ADOQuery1EditError(DataSet: TDataSet; E: EDatabaseError;
      var Action: TDataAction);
    procedure N2Click(Sender: TObject);
    procedure N1Click(Sender: TObject);
    procedure N4Click(Sender: TObject);
    procedure N5Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Shape1DragOver(Sender, Source: TObject; X, Y: Integer;
      State: TDragState; var Accept: Boolean);
    procedure BitBtn1Click(Sender: TObject);
    procedure N6Click(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
    procedure N7Click(Sender: TObject);
    procedure N8Click(Sender: TObject);
    procedure N9Click(Sender: TObject);
    procedure N10Click(Sender: TObject);
    procedure N11Click(Sender: TObject);
    procedure btnDelPicClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure sbZIClick(Sender: TObject);
    procedure sbZOClick(Sender: TObject);
    procedure sbRLClick(Sender: TObject);
    procedure sbRRClick(Sender: TObject);
    procedure sbLeftClick(Sender: TObject);
    procedure sbRightClick(Sender: TObject);
    procedure sbUpClick(Sender: TObject);
    procedure sbDownClick(Sender: TObject);
    procedure N12Click(Sender: TObject);
  private
    fn: string;
    NewNumberString2: string;
    mask1: string; //相机顺序号，
    user1: string; //连接数据库的用户名，
    pwd1: string; //连接数据库的密码，
    database1: string; //数据库名，

    FPicHandler: TksPicHandler;

    {初始化界面信息}
    procedure InitPrefaceInfo;

    procedure DeleteJPG;
    {}

    { Private declarations }
  public
    { Public declarations }
  end;

var
  PhotoSystem: TPhotoSystem;


function Capture(hParent: HWND; filename: pchar; resolution: longint): longint; cdecl;
external 'CaptureDLL.dll' name 'Capture';

implementation

uses UASetCanon, UACount1, UDb, UtConfigs, UBatchImport, UnBatchExport,
  UEditInfo, UOperator, Ulogin, Uquery, phtImportData, phtMadeCard, phtBatchDelete,
  uCardPrint;

{$R *.DFM}


procedure TPhotoSystem.InitPrefaceInfo;
begin
  Label1.width := 300;
  Label8.Width := 100;
  Label10.width := 200;
  PhotoSystem.Height := 740;
  Button6.Visible := False;
  Button7.Visible := False;
  Label8.Visible := False;
  Label9.Visible := False;
  Edit2.Visible := False;
  Edit3.Visible := False;
  Button3.Visible := true;
  Button4.Visible := true;
  Edit5.Text := '';
  Edit6.Text := '';
  Edit4.Enabled := False;
  Button5.Enabled := False;
  Button2.Enabled := False;
  button3.Enabled := false;
  button4.Enabled := false;
  Label12.Caption := '';
  Label13.Caption := '';
  Label14.Caption := '';
  Label15.Caption := '';
  Label17.Caption := '';
  Label18.Caption := '';

  DBEdit1.DataField := StuempName;
  DBEdit2.DataField := StuempNo;
end;



{进行查询，}

procedure TPhotoSystem.Button1Click(Sender: TObject);
var
  StuEmpNumber: string;
  F3: TADOBlobStream;
  Fjpg: TJpegImage; //用Image 存放 Jpeg 的中间形式，
  sDeptCode: string; //部门代码
  KindCode: string;
  tmpquery: Tadoquery;
begin
  if (dm.login <> '') or (dm.loginout <> '') then
    if (formatdatetime('yyyymmddhhmmss', now()) < dm.login) or (formatdatetime('yyyymmddhhmmss', now()) > dm.loginout) then
    begin
      try
        tmpquery := Tadoquery.Create(nil);
        tmpquery.Connection := dm.ConnectPhoto;
        tmpquery.Close;
        tmpquery.sql.Clear;
        tmpquery.SQL.Add('update T_PIF_OPERATOR set status=0 where oper_code=' + #39 + dm.oper_code + #39);
        tmpquery.Prepared;
        tmpquery.ExecSQL;
      finally
        tmpquery.Free;
      end;
      showmessage('该登录帐号已经过期，请和管理人员联系！');
      exit;
    end;

  if Edit1.Text = '' then
  begin
    ShowMessage('您输入的学工号为空！');
    exit;
  end;
  imgPic.Picture.Assign(nil);
  StuEmpNumber := Trim(Edit1.text);
  ADOQuery2.Close;
  ADOQuery2.SQL.Clear;
  ADOQuery2.SQL.Add('SELECT '+BanchCode+','+StuempName+','+PhotoDate+','+CutType+','+DeptName+','+FileName +','+opername+
    ','+StuempNo+','+DeptCode+','+SCode+','+ID2+','+Photo+','+PhotoTime+' from '+PhotoTableName+'  where ' +
    StuempNo + '=' + QuotedStr(StuEmpNumber));
    //adoquery2.SQL.SaveToFile('123.txt');
  ADOQuery2.Open;
  if ADOQuery2.IsEmpty = true then
  begin
    ADOQuery2.Recordset.close;
    ADOQuery2.Close;
    ShowMessage('该学工号记录不存在！');
    Edit1.Text := '';
    exit;
  end;
  ADOQuery2.edit;
  sDeptCode := ADOQuery2.FieldByName(BanchCode).AsString;
  Label12.Caption := ADOQuery2.FieldByName(StuempName).AsString;
  Label13.Caption := ADOQuery2.FieldByName(StuempNo).AsString;
  Edit5.text := ADOQuery2.FieldByName(BanchCode).AsString;
  KindCode := ADOQuery2.FieldByName(DeptCode).AsString;
  Label17.Caption := ADOQuery2.FieldByName(SCode).AsString;
  Label15.Caption := ADOQuery2.FieldByName(CutType).AsString;
  Label14.Caption := ADOQuery2.FieldByName(DeptName).AsString;
  LPicture.caption := ADOQuery2.FieldByName(FileName).AsString;
  Label24.Caption := ADOQuery2.FieldByName(id2).AsString;
  Button5.Enabled := True;
  button2.Enabled := true; //取照片
  button3.Enabled := false; //确定
  button4.Enabled := false; //取消
  Label12.Width := 120;
  Label20.Caption := ADOQuery2.FieldByName(PhotoDate).AsString;

  image2.Picture.Graphic := nil;
  if AdoQuery2.FieldByName(FileName).AsString <> '' then    // todo
  begin
    F3 := TADOBlobStream.Create(TBlobField(ADOQuery2.fieldbyname(Photo)), bmread);
    try
        // TBlobField(AdoQuery2.FieldByName(Photo)).SaveToStream(F3);    delete 050601 fuck
        Fjpg := TJpegImage.Create;
        try
          F3.Position := 0;
          if F3.Size > 100 then
          begin
            FJpg.LoadFromStream(F3);
            image2.Picture.Graphic := FJpg;
          end
          else
          begin
            Panel6.Caption := '没有原始照片';
          end;
        finally
          Fjpg.Free;
        end;
    finally
      F3.Destroy;
    end;
  end
  else
    Panel6.Caption := '没有原始照片';
  //统计已拍照片人数
  ADOQuery4.Close;
  ADOQuery4.SQL.Clear;
  {
  ADOQuery4.SQL.Add('select Count(' + StuEmpNo + ') from ' + PhotoTableName +
    ' where ' + FileName + '<>' + QuotedStr(''));
    }
  ADOQuery4.SQL.Add('select Count(' + StuEmpNo + ') from ' + PhotoTableName +
    ' where ' + FileName + '<> '''' or ' + FileName + ' is not null ');
  ADOQuery4.Open;
  ADOQuery4.first;
  Label18.Caption := IntToStr(ADOQuery4.Fields[0].AsInteger);
  //if Application.MessageBox('你要删除临时文件中的照片吗？',pchar(application.Title),mb_yesno+mb_iconquestion)=idyes then
    //DeleteJPG;

  // add by zhf 050601
  Panel3.Enabled := True;
  pnlHandlePic.Enabled := True;
end;



procedure TPhotoSystem.Button2Click(Sender: TObject);
var
  currentNum1: string;
  NewNumber2: string;
  TmpChar: PChar;
begin
  if dm.judgelimit(dm.soper,Mdl_LoadPic)=false then
  begin
    showmessage('你没有取照片的权限，请找管理人员开通该权限！');
    exit;
  end;
  OldNumber2 := '';
  currentNum1 := Trim(Edit4.Text); //允许客户在界面上修改，而不必打开配置文件修改，
  NewNumberString2 := currentNum1;
  while FileExists(OldDirPath + '\' + Pre + NewNumberString2 + '.JPG') do
  begin
    if FileExists(OldDirPath + '\' + Pre + OldNumber2 + '.JPG') then
      DeleteFile(PChar(OldDirPath + '\' + Pre + OldNumber2 + '.JPG'));
    OldNumber2 := NewNumberString2;
    NewNumber2 := IntToStr(StrToInt(OldNumber2) + 1);
    NewNumber2 := '0000000000' + NewNumber2;
    NewNumberString2 := Copy(NewNumber2, (Length(NewNumber2) - NumberLen + 1), NumberLen);
  end;
  if FileExists(OldDirPath + '\' + Pre + OldNumber2 + '.JPG') then
  begin
    TmpChar := nil;
    ReallocMem(TmpChar, 90);
    TmpChar := PChar(OldDirPath + '\' + Pre + OldNumber2 + '.JPG');
    Edit7.Text := OldDirPath + '\' + Pre + OldNumber2 + '.JPG';

    // modify by zhf
    FPicHandler.LoadFromFile(OldDirPath + '\' + Pre + OldNumber2 + '.JPG');
    //imgPic.Picture.LoadFromFile(OldDirPath + '\' + Pre + OldNumber2 + '.JPG');

    imgPic.Stretch := false;
    imgPic.Stretch := true; //先判断文件是否存在，
    Edit2.Text := Pre + OldNumber2 + '.JPG';
    Edit3.Text := DBEdit2.Text + '.JPG';
    Button5.Visible := false;
    Label8.Visible := True;
    Label9.Visible := True;
    Edit2.Visible := True;
    Edit3.Visible := True;
    button2.Enabled := false; //取照片
    button3.Enabled := true; //确定
    button4.Enabled := true; //取消
  end
  else
  begin
    ShowMessage('该照片不存在！请检查并"修改相机顺序号",必要时请手动修改配置文件..\file.ini 的值！');
  end;
end;

{保存照片，}

procedure TPhotoSystem.Button3Click(Sender: TObject);
var
  F, s: TmemoryStream;
  F2: TFileStream;
  OldNumber: string;
  NewNumber: string;
  NewNumberString: string;
  fileNamePath: string;
  DirPath1: string;
  DirPath2: string;
  j: integer; //计算已拍照数目
  my: TIniFile;
  FJpeg: TJpegImage;
  FPersonNo: string;
begin
         //保存到数据库，
  try
    // up from buttom   
    //保存到本地，
    if not DirectoryExists(NewDirPath) then
      if not CreateDir(NewDirPath) then
        raise Exception.Create('不能创建文件夹：' + NewDirPath);

    FPersonNo := Label13.Caption;
    DirPath1 := NewDirPath + '\' + Label14.Caption;
    DirPath2 := DirPath1 + '\' + Label15.Caption;

    //保存到本地，
    if not DirectoryExists(DirPath1) then
      if not CreateDir(DirPath1) then
        raise Exception.Create('不能创建文件夹：' + DirPath1);

    //当采用专业目录，
    if not DirectoryExists(DirPath2) then
      if not CreateDir(DirPath2) then
        raise Exception.Create('不能创建文件夹：' + DirPath2);

    //modify 050601
    FPicHandler.SaveToFile(DirPath2 + '\' + FPersonNo + '.JPG');
    // F2 := TFileStream.Create(DirPath2 + '\' + FPersonNo + '.JPG', fmCreate);
    //F2 := TFileStream.Create(DirPath2 + '\' + FPersonNo + '.jpg', fmCreate);
    //TBlobField(AdoQuery2.FieldByName(Photo)).SaveToStream(F2);
    // end of up

    ADOQuery2.Edit;
    FJpeg := TJpegImage.Create;
    FJpeg.LoadFromFile(DirPath2 + '\' + FPersonNo + '.JPG');
    (*
    FJpeg := TJpegImage.Create;
    F := TmemoryStream.Create {(OldDirPath+'\'+Pre+OldNumber2+'.JPG',fmOpenRead)};

    FJpeg.Assign(imgPic.Picture.Graphic);
    imgPic.Picture.Graphic.SaveToStream(F);
    F.Position := 0;
    *)
    F := TmemoryStream.Create;
    FJpeg.SaveToStream(F);
    TBlobField(ADOQuery2.FieldByName(Photo)).loadfromStream(F);

    ADOQuery2.FieldByName(PhotoDate).asstring := formatdatetime('yyyy-mm-dd', date); //照相日期字段名称
    ADOQuery2.FieldByName(StuempNo).asstring := Label13.Caption; //人员编号字段名称
    ADOQuery2.FieldByName(StuempName).asstring := Label12.Caption; //人员名称
    ADOQuery2.FieldByName(BanchCode).asstring := Edit5.Text; //人员类型二代码字段名称
    ADOQuery2.FieldByName(DeptCode).asstring := Edit6.Text; //人员类型一代码字段名称
    ADOQuery2.FieldByName(PhotoTime).asstring := formatdatetime('HH:MM:SS', now);
    ADOQuery2.FieldByName(opername).asstring := dm.oper_code;
    //showmessage(oper_code);

    ADOQuery2.FieldByName(FileName).AsString := Label14.Caption + '\' +
      ADOQuery2.FieldByName(StuempNo).AsString + '.JPG';
    adoquery2.Post;
    lpicture.caption := DirPath1 + '\' + Label15.Caption;
       
    Button1Click(nil);
  finally
    ADOQuery1.Close;
    F.Free;
    FJpeg.Free;
    // F2.Free;
  end;
  DeleteFile(OldDirPath + '\' + Pre + OldNumber2 + '.jpg');
  Edit4.Text := OldNumber1;
  Edit2.Text := '';
  Edit3.Text := '';
  Label8.Visible := False;
  Label9.Visible := False;
  Edit2.Visible := False;
  Edit3.Visible := False;
  button1.Enabled := true; //查询
  button2.Enabled := false; //取照片
  button3.Enabled := false; //确定
  button4.Enabled := false; //取消

       //从界面上，清除上一条记录的过程，
  imgPic.Picture.Assign(nil);
  Button5.Enabled := False;
end;

{按下“取消”按钮时，}

procedure TPhotoSystem.Button4Click(Sender: TObject);
var
  content: string;
  F: file;
  my: TInifile;
begin
  try
    AssignFile(F, OldDirPath + '\' + Pre + OldNumber2 + '.jpg'); //从公共区间 删除照片文件，被删除照片的文件名？
    Reset(F);
    CloseFile(F);
    Erase(F);
  except
    ShowMessage('删除照片错误！');
  end;
  //ADOQuery1.Close;
  //ADOQuery1.SQL.Clear;
  Label8.Visible := False;
  Label9.Visible := False;
  Edit2.Visible := False;
  Edit3.Visible := False;
  Button3.Visible := true;
  Button4.Visible := true;

     //从界面上，清除上一条记录的过程，
  Label12.Caption := '';
  Label13.Caption := '';
  Label14.Caption := '';
  Label17.Caption := '';
  Label15.Caption := '';
  Edit5.Text := '';
  imgPic.Picture.Assign(nil);
  Button5.Enabled := False;
  button1.Enabled := true; //查询
  button2.Enabled := false; //取照片
  button3.Enabled := false; //确定
  button4.Enabled := false; //取消
  Edit4.Text := OldNumber1;
end;

procedure TPhotoSystem.FormCreate(Sender: TObject);
var
  ARect: TRect;
begin
  GetConfigs;
  //ConfigConnectDB;
  InitPrefaceInfo;
  Edit4.Text := OldNumber1;

  
  FPicHandler := TksPicHandler.Create(imgPic); 
  ARect := Rect(PicFrame.Left, PicFrame.Top,
    PicFrame.Left + PicFrame.Width, PicFrame.Top + PicFrame.Height);
  FPicHandler.SetFrame(ARect);
end;

procedure TPhotoSystem.Button5Click(Sender: TObject);
begin
  Button5.Visible := False;
  Edit4.Enabled := True;
  Button2.Enabled := False;
  Button6.Visible := True;
  Button7.Visible := True;
  mask1 := Edit4.Text;
end;

procedure TPhotoSystem.Button6Click(Sender: TObject);
begin
  Button2.Enabled := True;
  Button6.Visible := False;
  Button7.Visible := False;
  Button5.Visible := True;
  Edit4.Enabled := False;
end;

procedure TPhotoSystem.Button7Click(Sender: TObject);
begin
  Button2.Enabled := True;
  Button6.Visible := False;
  Button7.Visible := False;
  Button5.Visible := True;
  Edit4.Enabled := False;
  Edit4.Text := mask1;
end;


procedure TPhotoSystem.Edit1KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key = 13) and (Edit1.Text <> '') then
    Button1Click(nil);
end;

procedure TPhotoSystem.FormMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  PhotoSystem.Align := alNone;
end;

procedure TPhotoSystem.FormClick(Sender: TObject);
begin
  PhotoSystem.Align := alNone;
end;

procedure TPhotoSystem.FormShow(Sender: TObject);
var
  j: integer; //计算已拍照数目
begin
  loginform.ShowModal;

  if (dm.oper_code <> 'tjxxb1') then
    btnDelPic.Enabled := False;

  //统计已拍照片人数
  ADOQuery4.Close;
  ADOQuery4.SQL.Clear;
  {
  ADOQuery4.SQL.Add('select Count(' + StuempNo + ') from ' + PhotoTableName +
    ' where ' + FileName + '<>' + QuotedStr(''));
    }
  ADOQuery4.SQL.Add('select Count(' + StuEmpNo + ') from ' + PhotoTableName +
    ' where ' + FileName + '<> '''' or ' + FileName + ' is not null ');
  ADOQuery4.Open;
  ADOQuery4.first;
  j := 0;
  j := ADOQuery4.Fields[0].AsInteger;
  Label18.Caption := IntToStr(j);
end;


{统计报表}

procedure TPhotoSystem.ADOQuery1PostError(DataSet: TDataSet;
  E: EDatabaseError; var Action: TDataAction);
var iDBIError: Integer;
begin
  if (E is EDBEngineError) then
  begin
    iDBIError := (E as EDBEngineError).Errors[0].Errorcode;
    showmessage('post err' + inttostr(iDBIError));
  end;
end;

procedure TPhotoSystem.ADOQuery1EditError(DataSet: TDataSet;
  E: EDatabaseError; var Action: TDataAction);
begin
  ShowMessage(' 修改记录失败！ ');
end;

procedure TPhotoSystem.N2Click(Sender: TObject);
var
  i: integer;
  startNumber2: string;
  temp2: string;
  my: TInifile;
begin
  SetOption := TSetOption.Create(nil);
  SetOption.ShowModal;
  if SetOption.ModalResult = mrOk then
  begin
    if (SetOption.Edit8.Text = '') or (SetOption.Edit3.Text = '') or (SetOption.Edit4.Text = '') or (SetOption.Edit2.Text = '') or (SetOption.Edit5.Text = '') then
    begin
      ShowMessage('请填写完整');
      exit;
    end;
    my := TIniFile.Create(ChangeFileExt('file', '.ini'));
    try
      if SetOption.Edit8.Text <> '' then
        my.WriteString('FILEDIR', 'PRENAME', Trim(SetOption.Edit8.Text) + '_');
      if SetOption.Edit3.Text <> '' then
        my.WriteString('FILEDIR', 'NUMBER', Trim(SetOption.Edit3.Text));
      if SetOption.Edit4.Text <> '' then
        my.WriteString('FILEDIR', 'STARTNUM', Trim(SetOption.Edit4.Text));
      if SetOption.Edit2.Text <> '' then
        my.WriteString('FILEDIR', 'OLDDIR', Trim(SetOption.Edit2.Text));
      if SetOption.Edit5.Text <> '' then
        my.WriteString('FILEDIR', 'NEWDIR', Trim(SetOption.Edit5.Text));

      //配置文件修改了，要做相应的修改
      OldDirPath := my.ReadString('FILEDIR', 'OLDDIR', '');
      NewDirPath := my.ReadString('FILEDIR', 'NEWDIR', '');
      Pre := my.ReadString('FILEDIR', 'PRENAME', '');
      NumberLen := my.ReadInteger('FILEDIR', 'NUMBER', 0);
      StartNum := my.ReadString('FILEDIR', 'STARTNUM', '');
      temp2 := '0000000000' + StartNum;
      startNumber2 := Copy(temp2, (Length(temp2) - NumberLen + 1), NumberLen);
      my.WriteString('CANON', 'INITNUM', startNumber2);
      initNumber := my.ReadString('CANON', 'INITNUM', '');
      my.WriteString('CANON', 'CURRENTNUM', startNumber2);
      addLength := my.ReadInteger('CANON', 'LENGTH', 0);
      OldNumber1 := my.ReadString('CANON', 'INITNUM', '');
      Edit4.Text := my.ReadString('CANON', 'INITNUM', '');
    finally
      my.Free;
    end;
  end;
  SetOption.free;
end;

procedure TPhotoSystem.N1Click(Sender: TObject);
var
  departName1: string;
  departCode1: string;
  deptPeopleAll: integer;
  photoedCount: integer; //已拍过的人数，
  unPhoCount: integer; //未拍过的人数，
begin
  ReportCount1 := TReportCount1.Create(nil);
  try
    ReportCount1.ShowModal;
  finally
    ReportCount1.free;
  end;
end;

procedure TPhotoSystem.N4Click(Sender: TObject);
begin
  if dm.judgelimit(dm.soper,Mdl_ExpPic)=false then
  begin
    showmessage('你没有导出照片的权限，请找管理人员开通该权限！');
    exit;
  end;

  BatchExpot := TBatchExpot.Create(Application);
  try
    BatchExpot.ShowModal;
  finally
    BatchExpot.Free;
  end;
end;

procedure TPhotoSystem.N5Click(Sender: TObject);
begin
  // delete by zhf  | because move to submenu
end;

procedure TPhotoSystem.Button8Click(Sender: TObject);
begin
  Edit7.Text := OldDirPath + '\' + Pre + NewNumberString2 + '.jpg';
  winexec(PChar(ExtractFileDir(Application.ExeName) + '\' + 'DLLTest.exe'), SW_Normal);
end;

procedure TPhotoSystem.Shape1DragOver(Sender, Source: TObject; X,
  Y: Integer; State: TDragState; var Accept: Boolean);
begin
  Accept := Source is TPanel;
end;

procedure TPhotoSystem.BitBtn1Click(Sender: TObject);
begin
  if dm.judgelimit(dm.soper,Mdl_EditData)=false then
  begin
    showmessage('你没有修改基本信息的权限，请找管理人员开通该权限！');
    exit;
  end;
  FrmEditInfo := TFrmEditInfo.Create(nil);
  try
    FrmEditInfo.ShowModal;
    FrmEditInfo.CurrentEditEmpNo := Label13.Caption;
  finally
    FrmEditInfo.Free;
  end;

end;

procedure TPhotoSystem.N6Click(Sender: TObject);
begin
  if (dm.oper_code <> 'tjxxb1')then
  begin
    showmessage('你没有操作该项的权限！');
    exit;
  end;
  operatorform := Toperatorform.Create(nil);
  operatorform.ShowModal;
  operatorform.Free;
end;

procedure TPhotoSystem.btnExitClick(Sender: TObject);
begin
  Application.Terminate;
end;

procedure TPhotoSystem.DeleteJPG;
var
  s: string;
  SearchRec: TSearchRec;
begin
  FindFirst(OldDirPath + '\*.JPG', faAnyFile, SearchRec);
  repeat
    s := SearchRec.Name;
    if SearchRec.Attr <> faDirectory then
    begin
      FileSetAttr(SearchRec.Name, 0); //修改文件属性为普通属性值
      DeleteFile(OldDirPath + '\' + SearchRec.Name); //删除文件
    end;
  until (FindNext(SearchRec) <> 0);
  FindClose(SearchRec);
end;

procedure TPhotoSystem.N7Click(Sender: TObject);
begin
  if dm.judgelimit(dm.soper,Mdl_Query)=false then
  begin
    showmessage('你没有查询的权限，请找管理人员开通该权限！');
    exit;
  end;
  queryform:=Tqueryform.Create(nil);
  queryform.ShowModal;
end;

procedure TPhotoSystem.N8Click(Sender: TObject);
begin
  // 导入照片 
  if dm.judgelimit(dm.soper,Mdl_ImpPic)=false then
  begin
    showmessage('你没有导入照片的权限，请找管理人员开通该权限！');
    exit;
  end;
  BatchImport := TBatchImport.Create(Application);
  try
    BatchImport.ShowModal;
  finally
    BatchImport.Free;
  end;
end;

procedure TPhotoSystem.N9Click(Sender: TObject);
begin
  // 导入学工基本信息
  if dm.judgelimit(dm.soper,Mdl_ImpData)=false then
  begin
    showmessage('你没有导入基本信息的权限，请找管理人员开通该权限！');
    exit;
  end;
  ImportData(dm.ConnectPhoto);
end;

procedure TPhotoSystem.N10Click(Sender: TObject);
begin
  // 制卡管理
  if dm.judgelimit(dm.soper,Mdl_MakeCard)=false then
  begin
    showmessage('你没有制卡管理的权限，请找管理人员开通该权限！');
    exit;
  end;
  MadeCard(dm.ConnectPhoto);
end;

procedure TPhotoSystem.N11Click(Sender: TObject);
begin
  // 批量删除基本信息
  if dm.judgelimit(dm.soper,Mdl_ExpData)=false then
  begin
    showmessage('你没有删除基本信息的权限，请找管理人员开通该权限！');
    exit;
  end;
  BatchDelete(dm.ConnectPhoto);
end;

procedure TPhotoSystem.btnDelPicClick(Sender: TObject);
var
  M1: TMemoryStream;
begin
  // 删除照片
  if (dm.oper_code <> 'tjxxb1')  then
  begin
    showmessage('你没有操作该项的权限！');
    exit;
  end;

  AdoQuery2.Edit;
  ADOQuery2.FieldByName(Photo).AsString := '';
  AdoQuery2.FieldByName(FileName).AsString := '';
  AdoQuery2.FieldByName(PhotoDate).AsString := '';
  AdoQuery2.FieldByName(PhotoTime).AsString := '';
  AdoQuery2.Post;
  Image2.Picture.Graphic := nil;
end;

procedure TPhotoSystem.FormDestroy(Sender: TObject);
begin
  FPicHandler.Free;
end;

procedure TPhotoSystem.sbZIClick(Sender: TObject);
begin
  FPicHandler.Zoom(+3);
end;

procedure TPhotoSystem.sbZOClick(Sender: TObject);
begin
  FPicHandler.Zoom(-3);
end;

procedure TPhotoSystem.sbRLClick(Sender: TObject);
begin
  FPicHandler.Rotate(-0.011);
end;

procedure TPhotoSystem.sbRRClick(Sender: TObject);
begin
  FPicHandler.Rotate(0.011);
end;

procedure TPhotoSystem.sbLeftClick(Sender: TObject);
begin
  FPicHandler.Move(Point(-2, 0));
end;

procedure TPhotoSystem.sbRightClick(Sender: TObject);
begin
  FPicHandler.Move(Point(2, 0));
end;

procedure TPhotoSystem.sbUpClick(Sender: TObject);
begin
  FPicHandler.Move(Point(0, -2));
end;

procedure TPhotoSystem.sbDownClick(Sender: TObject);
begin
  FPicHandler.Move(Point(0, 2));
end;

procedure TPhotoSystem.N12Click(Sender: TObject);
begin
  // 制卡
  if dm.judgelimit(dm.soper,Mdl_card)=false then
  begin
    showmessage('你没有制卡的权限，请找管理人员开通该权限！');
    exit;
  end;
  CardPrint(dm.ConnectPhoto);

end;

end.


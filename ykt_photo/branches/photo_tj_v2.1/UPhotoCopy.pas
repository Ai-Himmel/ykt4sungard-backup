unit UPhotoCopy;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls,jpeg,ADODB;

type
  TfrmPhotoCopy = class(TForm)
    pnl1: TPanel;
    pnlStuempNo: TPanel;
    imgNewPhoto: TImage;
    lbl1: TLabel;
    lbl2: TLabel;
    lblOldStuempNo: TLabel;
    edtNewStuempNo: TEdit;
    btnOk: TButton;
    btnSkip: TButton;
    btnCancle: TButton;
    imgOldPhoto: TImage;
    lbl3: TLabel;
    lbl4: TLabel;
    procedure FormShow(Sender: TObject);
    procedure btnCancleClick(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
    procedure btnSkipClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    //是否批量，0单个处理，1批量处理
    patchSign:Integer;
    oldStuempNo,newStuempNo,custId:string;
    errMsg:string;
    //img:TImage;
  end;

var
  frmPhotoCopy: TfrmPhotoCopy;

implementation

uses uCommon, Udm;

{$R *.dfm}

procedure TfrmPhotoCopy.FormShow(Sender: TObject);
var
  Fjpg: TJpegImage;
begin
  lblOldStuempNo.Caption := oldStuempNo;
  edtNewStuempNo.Text := newStuempNo;
  if patchSign = 0 then
  begin
    edtNewStuempNo.Enabled := True;
    btnSkip.Visible := False;
    //img.Picture.Graphic.Assign(imgPhoto.Picture.Graphic);
  end
  else
  begin
    edtNewStuempNo.Enabled := False;
    btnSkip.Visible := True;
  end;
  Fjpg:=nil;
  imgOldPhoto.Picture.Graphic:=nil;
  try
    Fjpg := TJpegImage.Create;
    Fjpg := getPhotoInfo(custId);
    imgOldPhoto.Picture.Graphic:=Fjpg;
  finally
    Fjpg.Free;
  end;

end;

procedure TfrmPhotoCopy.btnCancleClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmPhotoCopy.btnOkClick(Sender: TObject);
var
  newCustId,oldCustId:string;
  scustName,stype,sArea,scertId,sDept,sSpec:string;
  sqlStr:string;
  qryExecSQL:TADOQuery;
  Fjpg: TJpegImage;
begin
  if Trim(edtNewStuempNo.Text)='' then
  begin
    ShowMessage('请输入新的学/工号');
    edtNewStuempNo.SetFocus;
    Exit;
  end;
  //根据新的学工号到客户表查是否存在，不存在则添加该记录，
  //添加后取客户号，
  //在照片表插入一条新记录，该记录
  oldCustId := IntToStr(haveStuEmpNo(Trim(lblOldStuempNo.Caption)));
  if oldCustId='0' then
  begin
    if patchSign=0 then
    begin
      ShowMessage('在人员信息表找不到记录，无法复制该人员信息！');
      Exit;
    end
    else
    begin
      errMsg := lblOldStuempNo.Caption+'--在人员信息表找不到记录，无法复制该人员信息';
      self.Close;
      Exit;
    end;
  end;
  newCustId := IntToStr(haveStuEmpNo(Trim(edtNewStuempNo.Text)));
  if newCustId='0' then
  begin
    //开始添加一条记录
    sqlStr:=queryBaseInfoSql(Trim(lblOldStuempNo.Caption),'','');
    qryExecSQL := nil;
    Fjpg:=nil;
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
        scustName:=qryExecSQL.fieldbyname(custName).AsString;
        stype:=qryExecSQL.fieldbyname(custType).AsString;
        sArea:=qryExecSQL.fieldbyname(custArea).AsString;
        sDept:=qryExecSQL.fieldbyname(custDeptNo).AsString;
        sSpec:=qryExecSQL.fieldbyname(custSpecNo).AsString;
        scertId:=qryExecSQL.fieldbyname(custCardId).AsString;
      end;
      if addCustInfo(Trim(edtNewStuempNo.Text),scustName,stype,sArea,scertId,sDept,sSpec,'0')=False then
      begin
        if patchSign=0 then
        begin
          ShowMessage('复制人员信息失败，请重新操作该步骤！');
          Exit;
        end
        else
        begin
          errMsg := lblOldStuempNo.Caption+'--复制人员信息失败';
          self.Close;
          Exit;
        end;
      end;
    finally
      Fjpg.Destroy;
      qryExecSQL.Destroy;
    end;
  end;
  //复制客户表成功后开始对照片表进行操作
  newCustId := photoHaveRecord(Trim(edtNewStuempNo.Text));
  //开始添加照片信息
  //先检查是否存在新学工号的照片信息，存在则退出，不存在查询新学工号的客户号
  if newCustId<>'' then
  begin
    Fjpg := getPhotoInfo(newCustId);
    imgNewPhoto.Picture.Graphic:=Fjpg;
    if Fjpg<>nil then
    begin
      if Application.MessageBox(PChar('该人员照片已经存在，你用旧照片替换新照片吗？'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
        Exit;
    end;
    //用旧照片更新新照片
    if updatePhoto(Trim(lblOldStuempNo.Caption),Trim(edtNewStuempNo.Text))<>0 then
    begin
      if patchSign=0 then
      begin
        ShowMessage('替换照片信息失败，请重新操作！');
        Exit;
      end
      else
      begin
        errMsg := lblOldStuempNo.Caption+'--替换照片信息失败';
        self.Close;
        Exit;
      end;
    end;
  end
  else
  begin
    newCustId := IntToStr(haveStuEmpNo(Trim(edtNewStuempNo.Text)));
    //插入照片数据
    if insertPhoto(newCustId,Trim(lblOldStuempNo.Caption),Trim(edtNewStuempNo.Text))<>0 then
    begin
      if patchSign=0 then
      begin
        ShowMessage('复制照片信息失败，请重新操作！');
        Exit;
      end
      else
      begin
        errMsg := lblOldStuempNo.Caption+'--复制照片信息失败';
        self.Close;
        Exit;
      end;
    end;
  end;
  if patchSign=0 then
    ShowMessage('复制照片信息成功！');
  self.Close;

end;

procedure TfrmPhotoCopy.btnSkipClick(Sender: TObject);
begin
  errMsg := lblOldStuempNo.Caption+'--跳过该人员照片复制';
  Close;
end;

end.

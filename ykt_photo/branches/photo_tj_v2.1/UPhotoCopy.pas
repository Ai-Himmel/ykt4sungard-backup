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
    //�Ƿ�������0��������1��������
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
    ShowMessage('�������µ�ѧ/����');
    edtNewStuempNo.SetFocus;
    Exit;
  end;
  //�����µ�ѧ���ŵ��ͻ�����Ƿ���ڣ�����������Ӹü�¼��
  //��Ӻ�ȡ�ͻ��ţ�
  //����Ƭ�����һ���¼�¼���ü�¼
  oldCustId := IntToStr(haveStuEmpNo(Trim(lblOldStuempNo.Caption)));
  if oldCustId='0' then
  begin
    if patchSign=0 then
    begin
      ShowMessage('����Ա��Ϣ���Ҳ�����¼���޷����Ƹ���Ա��Ϣ��');
      Exit;
    end
    else
    begin
      errMsg := lblOldStuempNo.Caption+'--����Ա��Ϣ���Ҳ�����¼���޷����Ƹ���Ա��Ϣ';
      self.Close;
      Exit;
    end;
  end;
  newCustId := IntToStr(haveStuEmpNo(Trim(edtNewStuempNo.Text)));
  if newCustId='0' then
  begin
    //��ʼ���һ����¼
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
          ShowMessage('������Ա��Ϣʧ�ܣ������²����ò��裡');
          Exit;
        end
        else
        begin
          errMsg := lblOldStuempNo.Caption+'--������Ա��Ϣʧ��';
          self.Close;
          Exit;
        end;
      end;
    finally
      Fjpg.Destroy;
      qryExecSQL.Destroy;
    end;
  end;
  //���ƿͻ���ɹ���ʼ����Ƭ����в���
  newCustId := photoHaveRecord(Trim(edtNewStuempNo.Text));
  //��ʼ�����Ƭ��Ϣ
  //�ȼ���Ƿ������ѧ���ŵ���Ƭ��Ϣ���������˳��������ڲ�ѯ��ѧ���ŵĿͻ���
  if newCustId<>'' then
  begin
    Fjpg := getPhotoInfo(newCustId);
    imgNewPhoto.Picture.Graphic:=Fjpg;
    if Fjpg<>nil then
    begin
      if Application.MessageBox(PChar('����Ա��Ƭ�Ѿ����ڣ����þ���Ƭ�滻����Ƭ��'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
        Exit;
    end;
    //�þ���Ƭ��������Ƭ
    if updatePhoto(Trim(lblOldStuempNo.Caption),Trim(edtNewStuempNo.Text))<>0 then
    begin
      if patchSign=0 then
      begin
        ShowMessage('�滻��Ƭ��Ϣʧ�ܣ������²�����');
        Exit;
      end
      else
      begin
        errMsg := lblOldStuempNo.Caption+'--�滻��Ƭ��Ϣʧ��';
        self.Close;
        Exit;
      end;
    end;
  end
  else
  begin
    newCustId := IntToStr(haveStuEmpNo(Trim(edtNewStuempNo.Text)));
    //������Ƭ����
    if insertPhoto(newCustId,Trim(lblOldStuempNo.Caption),Trim(edtNewStuempNo.Text))<>0 then
    begin
      if patchSign=0 then
      begin
        ShowMessage('������Ƭ��Ϣʧ�ܣ������²�����');
        Exit;
      end
      else
      begin
        errMsg := lblOldStuempNo.Caption+'--������Ƭ��Ϣʧ��';
        self.Close;
        Exit;
      end;
    end;
  end;
  if patchSign=0 then
    ShowMessage('������Ƭ��Ϣ�ɹ���');
  self.Close;

end;

procedure TfrmPhotoCopy.btnSkipClick(Sender: TObject);
begin
  errMsg := lblOldStuempNo.Caption+'--��������Ա��Ƭ����';
  Close;
end;

end.

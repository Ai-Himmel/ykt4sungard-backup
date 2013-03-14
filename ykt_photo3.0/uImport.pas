unit uImport;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, FileCtrl, ComCtrls, Buttons,jpeg,phtIfRepalce
  ,Db,ADODB;

type
  TfrmImport = class(TForm)
    pnlTop: TPanel;
    lbl1: TLabel;
    drvcbb1: TDriveComboBox;
    dirlstPhoto: TDirectoryListBox;
    fllstPhoto: TFileListBox;
    Label1: TLabel;
    dtpDate: TDateTimePicker;
    dtpTime: TDateTimePicker;
    pnl1: TPanel;
    lstError: TListBox;
    Label2: TLabel;
    pb1: TProgressBar;
    btnImport: TBitBtn;
    BitBtn1: TBitBtn;
    qryImprot: TADOQuery;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    { Private declarations }
    FPersonNo: string;

    FOldJPEG, FNewJPEG: TJPEGImage; 
    FReply: TphtReply;

    ErrorPersonNo: TStrings;
    ErrorPersonName: TStrings;
  public
    { Public declarations }
  end;

var
  frmImport: TfrmImport;

implementation

uses uCommon, Udm;

{$R *.dfm}

procedure TfrmImport.BitBtn1Click(Sender: TObject);
begin
  close();
end;

procedure TfrmImport.FormShow(Sender: TObject);
begin
  dtpdate.Date:=Date;
  dtptime.Time:=Now;
end;

procedure TfrmImport.btnImportClick(Sender: TObject);
var i: Integer;
  FCurrentSetDir: string;
  FFileName: string;
  F: TFileStream;
  BS: TADOBlobStream;
  M1: TMemoryStream;
  //F2: TFileStream;
  Buffer:Word;
  J: Integer;
  CurDir: string;
  FailDir: string;
  SkipDir: string;

  sqlImprot:string;
  sqlCustInfo:string;

  scustId,sStuempNo:string;

  photoQuery:TADOQuery;
begin
  if fllstPhoto.Items.Count = 0 then
  begin
    ShowMessage('û����Ƭ������������');
    Exit;
  end;
  pb1.Position := 0;
  pb1.Min := 0;

  FReply := rpNone;

  lstError.Items.Clear;
  CurDir := dirlstPhoto.Directory;
  FailDir := CurDir + '\����ʧ����Ƭ';
  SkipDir := CurDir + '\����������Ƭ';
  CreateDir(FailDir);
  CreateDir(SkipDir);

  pb1.Max := fllstPhoto.Items.Count;
  for i := 0 to fllstPhoto.Items.Count - 1 do
  begin
    pb1.Position := i + 1;

    FCurrentSetDir := dirlstPhoto.Directory;
    FFileName := Trim(fllstPhoto.Items.Strings[i]);
    FPersonNo:=getJpgNo(FFileName);
    //���ͻ����в�ѯ��ѧ�����Ƿ����,������д�������Ϣ
    //���ڵ���д��Ƭ��Ϣ������ѯ��Ƭ���Ƿ����ѧ������Ϣ
    photoQuery := nil;
    try
      sqlCustInfo:= 'select '+custId+','+stuempNo+' from '+tblCust+' where ';
      sqlCustInfo:=sqlCustInfo+stuempNo+'='+QuotedStr(FPersonNo);
      photoQuery:=TADOQuery.Create(nil);
      photoQuery.Connection:=frmdm.conn;
      photoQuery.Close;
      photoQuery.SQL.Clear;
      photoQuery.SQL.Add(sqlCustInfo);
      photoQuery.Open;
      if not photoQuery.IsEmpty then
      begin
        scustId := photoQuery.fieldbyname(custId).AsString;
        sStuempNo := photoQuery.fieldbyname(stuempNo).AsString;
        insertPhotoData(scustId,sStuempNo);
      end
      else
      begin
        ErrorPersonNo.Add(stuempNo);
        ErrorPersonName.Add('');
        lstError.Items.Add('ѧ/����Ϊ��' + QuotedStr(FPersonNo) + '����Ա������Ϣ������, ����ʧ��!');
        photoQuery.Close;
        CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false);
        Continue;
      end;
    finally
      photoQuery.Free;
    end;

    sqlImprot:='select '+custId+','+stuempNo+','+pPhoto+','+pphotoDate+','+pphototime+' from ' ;
    sqlImprot:=sqlImprot+tblPhoto+' where '+stuempNo+'='+QuotedStr(FPersonNo);
    qryImprot.Close;
    qryImprot.SQL.Clear;
    qryImprot.SQL.Add(sqlImprot);
    qryImprot.Open;
    {
    if qryImprot.IsEmpty then
    begin
      ErrorPersonNo.Add(stuempNo);
      ErrorPersonName.Add('');
      lstError.Items.Add('ѧ/����Ϊ��' + QuotedStr(FPersonNo) + '����Ա������Ϣ������, ����ʧ��!');
      qryImprot.Recordset.Close;
      qryImprot.Close;
      CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false); 
      Continue;
    end;
    }
    if (FReply <> rpAllReplace) and (not qryImprot.FieldByName(pPhoto).IsNull) then
    begin
      BS := TADOBlobStream.Create(TBlobField(qryImprot.FieldByName(pPhoto)),bmread);
      TBlobField(qryImprot.FieldByName(pPhoto)).SaveToStream(BS);
      BS.Position := 0;
      if BS.Size > 4 then
        FOldJPEG.LoadFromStream(BS);
      try
        FNewJPEG.LoadFromFile(FFileName);
      except
        lstError.Items.Add('ѧ/����Ϊ��' + FPersonNo + '��ͼƬ��ʽ����, ����ʧ��! ');
        CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false); 
        Continue;
      end;

      FReply := frmIfRepalce.GetReply(FPersonNo, FOldJPEG, FNewJPEG);

      case FReply of
        rpReplace: ;

        rpSkip:
        begin
          CopyFile(PChar(CurDir+'\'+FFileName), PChar(SkipDir+'\'+FFileName), false);
          Continue;
        end;
        rpCancel:
        begin
          for J := I to fllstPhoto.Items.Count - 1 do
          begin
            FFileName := Trim(fllstPhoto.Items.Strings[J]);
            CopyFile(PChar(CurDir+'\'+FFileName), PChar(SkipDir+'\'+FFileName), false);
          end;
          Break;
        end;
      end;
    end;
    qryImprot.Edit;
    F := TFileStream.Create(FCurrentSetDir + '\' + FFileName, fmOpenRead);
    F.Position := 0;
    F.ReadBuffer(Buffer,2); //��ȡ�ļ���ǰ�����ֽڣ��ŵ�Buffer����
    if Buffer<>$D8FF then
    begin
      ErrorPersonNo.Add(FPersonNo + '��ͼƬ��Ϣ����ʧ��,ͼƬ��ʽ����ȷ!');
      lstError.Items.Add(FPersonNo + '��ͼƬ��Ϣ����ʧ��,ͼƬ��ʽ����ȷ!');
      CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false);
      continue;
    end;
    try
      F.Position := 0;
      //M1 := TMemoryStream.Create;
      //TBlobField(qryImprot.FieldByName(pPhoto)).SaveToStream(M1);
      //�����Ƭ��С�������ݿ�Blob�ֶδ�С 600k,����ʧ�ܣ�
      if F.Size > 600000 then
      begin
        lstError.Items.Add('ѧ/����Ϊ��' + FPersonNo + '��ͼƬ��Ϣ����, ����ʧ��! ');
        CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false);
        Continue;
      end;
      TBlobField(qryImprot.FieldByName(pPhoto)).loadfromStream(F);

      qryImprot.FieldByName(pPhotoDate).Value := FormatDateTime('yyyymmdd',dtpdate.date);
      qryImprot.FieldByName(pPhotoTime).Value := FormatDateTime('hhmmss',dtpdate.time);
      try
        qryImprot.Post;
      except
        ErrorPersonNo.Add(FPersonNo + '��ͼƬ��Ϣ����ʧ��!');
        lstError.Items.Add(FPersonNo + '��ͼƬ��Ϣ����ʧ��!');
        CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false);
        continue;
      end;

    finally
      F.Free;
      //M1.Free;
    end;
  end;
  ShowMessage('������Ƭ��ɣ�');
  // if _Dir is empty, then remove
  RemoveDir(FailDir);
  RemoveDir(SkipDir);
end;

procedure TfrmImport.FormCreate(Sender: TObject);
begin
  ErrorPersonNo := TStringList.Create;
  ErrorPersonName := TStringList.Create;

  FOldJPEG := TJPEGImage.Create;
  FNewJPEG := TJPEGImage.Create;

end;

procedure TfrmImport.FormDestroy(Sender: TObject);
begin
  ErrorPersonNo.Free;
  ErrorPersonName.Free;

  FOldJPEG.Free;
  FNewJPEG.Free;

end;

end.

unit uCardPrint;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls, Db, ADODB,JPEG, QuickRpt, Qrctrls;

type
  TfrmCardPrint = class(TForm)
    pnl1: TPanel;
    pnl2: TPanel;
    lbl1: TLabel;
    edtNo: TEdit;
    btnQuery: TButton;
    btnPreview: TButton;
    btnExit: TButton;
    pnl3: TPanel;
    lbl2: TLabel;
    lblNo: TLabel;
    lblName: TLabel;
    qryQuery: TADOQuery;
    pnlPictrue: TPanel;
    imgPicture: TImage;
    QuickRep1: TQuickRep;
    DetailBand1: TQRBand;
    QRImage1: TQRImage;
    QRNo: TQRLabel;
    QRName: TQRLabel;
    lblCardStatus: TLabel;
    lblmaketime: TLabel;
    procedure btnExitClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnPreviewClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure edtNoKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    procedure setPrintStatus;
  public
    { Public declarations }
  end;

var
  frmCardPrint: TfrmCardPrint;

  procedure CardPrint(Conn: TADOConnection);
implementation

uses Udb, UtConfigs;

{$R *.DFM}
procedure CardPrint(Conn: TADOConnection);
var
  frmCardPrint: TfrmCardPrint;
begin
  frmCardPrint := TfrmCardPrint.Create(Application);
  frmCardPrint.qryQuery.Connection := Conn;
  frmCardPrint.ShowModal;
  frmCardPrint.Free;
end;

procedure TfrmCardPrint.btnExitClick(Sender: TObject);
begin
  close;
end;

procedure TfrmCardPrint.btnQueryClick(Sender: TObject);
var
  F3:TADOBlobStream;
  Fjpg: TJpegImage;  //��Image ��� Jpeg ���м���ʽ��
  StuEmpNumber:string;
  sqlStr:string;
  sNo:string;        //ѧ����
  sName:string;      //����
  sType:string;      //���
begin
  if Trim(edtNo.Text)='' then
  begin
    ShowMessage('������ѧ���Ų�ѯ��');
    edtNo.SetFocus;
    Exit;
  end;
  StuEmpNumber := Trim(edtNo.text);
  sqlStr:='SELECT '+StuempName+','+CutType+','+StuempNo+','+Photo+','+ifmakecard+','+makecardtime
    +' from '+PhotoTableName+' where ' +StuempNo + '=' + QuotedStr(StuEmpNumber);
  imgPicture.Picture.Assign(nil);
  qryQuery.Close;
  qryQuery.SQL.Clear;
  qryQuery.SQL.Add(sqlStr);
  qryQuery.Open;
  if qryQuery.IsEmpty=true then
  begin
    ShowMessage('��ѧ������Ϣ�����ڣ�');
    qryQuery.Recordset.Close;
    qryQuery.Close;
    Exit;
  end;
  qryquery.edit;
  btnPreview.Enabled:=True;
  lblCardStatus.Caption:='';
  lblmaketime.Caption:='';
  //�ж��Ƿ��ƿ�
  if qryQuery.FieldByName(ifMakeCard).AsInteger=1 then
  begin
    ShowMessage('�ÿ�Ƭ�Ѿ�������');
    lblCardStatus.Caption:='���ƿ�';
  end;
  lblmaketime.Caption:='�ƿ����ڣ�'+qryQuery.fieldbyname(makecardtime).AsString;
  sNo:=qryQuery.fieldbyname(StuempNo).AsString;
  sName:=qryQuery.fieldbyname(StuempName).AsString;
  sType:=qryQuery.fieldbyname(CutType).AsString;
  if (sType='��ְ��')OR(sType='������') then
    lblNo.Caption:='���ţ�'+sNo
  else
    lblNo.Caption:='ѧ�ţ�'+sNo;
  lblName.Caption:='������'+sName;
  //ȡ����Ƭ��Ϣ
  Try
    F3:=TADOBlobStream.Create(TBlobField(qryQuery.fieldbyname(Photo)),bmread);
    If TBlobField(qryQuery.FieldByName(Photo)).AsString<>null then
    TBlobField(qryQuery.FieldByName(Photo)).SaveToStream(F3);

    Fjpg :=TJpegImage.Create ;
    Try
      F3.Position:=0;
      imgPicture.Picture.Graphic := nil;
      If  F3.Size>100 then
      begin
        FJpg.LoadFromStream(F3);
        imgPicture.Picture.Graphic :=FJpg;
      end
      else
      begin
        pnlPictrue.Caption:='û����Ƭ';
      end;
    Finally
     Fjpg.Free;
    end;
  Finally
    F3.Destroy;
  end;

end;

procedure TfrmCardPrint.btnPreviewClick(Sender: TObject);
begin
  QRName.Caption:=lblName.Caption;
  QRNo.Caption:=lblNo.Caption;
  QRImage1.Picture.Assign(imgPicture.Picture);
  QuickRep1.Preview;
  setPrintStatus;
  btnPreview.Enabled:=False;
  //�ڴ˼����Ƿ��Ѿ���ӡ���ÿ�
end;

//��ӡ��ѿ�Ƭ״̬��Ϊ�Ѵ�ӡ״̬
procedure TfrmCardPrint.setPrintStatus;
var
  sqlstr:string;
begin
  sqlstr:='update '+PhotoTableName+' set '+ifMakeCard+'='+#39+'1'+#39+','+makecardtime+'='+#39+formatdatetime('yyyy-mm-dd',Date)+#39;
  sqlstr:=sqlstr+' where '+StuempNo + '=' + QuotedStr(Trim(edtNo.Text));
  try
    qryQuery.Close;
    qryQuery.SQL.Clear;
    qryQuery.SQL.Add(sqlstr);
    qryQuery.Prepared;
    qryquery.SQL.SaveToFile('000.txt');
    qryQuery.ExecSQL;
  finally
    qryQuery.Close;
  end;
end;

procedure TfrmCardPrint.FormShow(Sender: TObject);
begin
  lblNo.Caption:='';
  lblName.Caption:='';
  lblCardStatus.Caption:='';
  lblmaketime.Caption:='';
  btnPreview.Enabled:=False;
end;

procedure TfrmCardPrint.edtNoKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if key = vk_return then
    btnquery.Click();

end;

end.

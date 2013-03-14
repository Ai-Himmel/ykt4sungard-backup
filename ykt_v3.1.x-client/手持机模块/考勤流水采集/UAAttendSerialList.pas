unit UAAttendSerialList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, ComCtrls, RzListVw,CardDll,Buttons;

type
  TfaqhAttendSerialList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    lvSerial: TRzListView;
    ibnUpLoadSerial: TBitBtn;
    lbl1: TLabel;
    edtFileName: TEdit;
    btnUpload: TBitBtn;
    mmoList: TMemo;
    dlgSave1: TSaveDialog;
    pb1: TProgressBar;
    procedure ibnUpLoadSerialClick(Sender: TObject);
    procedure btnUploadClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhAttendSerialList: TfaqhAttendSerialList;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,LogFile;
     
{$R *.DFM}

procedure TfaqhAttendSerialList.Init;
begin
  inherited;
end;

procedure TfaqhAttendSerialList.ibnUpLoadSerialClick(Sender: TObject);
var
  rtn,i:Integer;
  fileName,str,phyId,tmpTime:string;
  tmpItem: TListItem;
begin
  mmoList.Lines.Clear;
  lvSerial.Items.Clear;
  fileName:=Trim(edtFileName.Text);
  if (fileName='')then
  begin
    Context.GetDialogSystem.ShowMessage('������Ҫ�������ݵ�·�����ļ�����');
    Exit;
  end;
  rtn:=info2text(fileName);
  if (rtn=0)then
  begin
    mmoList.Lines.LoadFromFile(fileName);
    for i:=0 to mmoList.Lines.Count-1 do
    begin
      str := mmoList.Lines[i];
      if str='' then
        Continue;
      phyId:=Copy(str,1,8);
      tmpTime:=Copy(str,9,14);
      tmpItem := lvSerial.Items.Add;
      //���
      tmpItem.Caption := IntToStr(i+1);
      //������
      tmpItem.SubItems.Add(phyId);
      //����ʱ��
      tmpItem.SubItems.Add(tmpTime);
    end;
    if FileExists(fileName) then
      DeleteFile(fileName);
  end
  else
  begin
    Context.GetDialogSystem.ShowMessage('�ɼ�������ˮʧ�ܣ������Ӻ��ֳֻ����²ɼ���');
  end;
end;

procedure TfaqhAttendSerialList.btnUploadClick(Sender: TObject);
var
  i:Integer;
  errList:TStringList;
  listCount:Integer;
begin
  listCount:=lvSerial.Items.Count;
  if listCount=0 then
  begin
    Context.GetDialogSystem.ShowMessage('���Ȳɼ���ˮ��Ȼ�����ϴ�!');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ�ϴ���ɼ��Ŀ�����ˮ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  errList:=nil;
  try
    errList:=TStringList.Create();
    pb1.Max:=listCount;
    for i:=0 to listCount-1 do
    begin
      WorkView.FieldByName('������').Data.SetString(lvSerial.Items[i].SubItems[0]);
      WorkView.FieldByName('����ʱ��').Data.SetString(lvSerial.Items[i].SubItems[1]);
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('������:'+lvSerial.Items[i].SubItems[0]+'������ˮ�ϴ�ʧ��-'+e.Message);
        end;
      end;
      pb1.Position:=pb1.Position+1;
    end;
    pb1.Position:=pb1.Max;
  finally
    if errList.Count>0 then
    begin
      if dlgSave1.Execute then
        errList.SaveToFile(dlgSave1.FileName+'-�ֳֻ�������ˮʧ�ܼ�¼.txt');
    end;
    errList.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('������ˮ�ɼ�',TfaqhAttendSerialList);

end.
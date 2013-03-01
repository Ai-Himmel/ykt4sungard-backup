program Photo1;

{%ToDo 'Photo1.todo'}

uses
  Forms,
  UAPhoto1 in 'UAPhoto1.pas' {PhotoSystem},
  UASetCanon in 'UASetCanon.pas' {SetOption},
  UACount1 in 'UACount1.pas' {ReportCount1},
  UtConfigs in 'UtConfigs.pas',
  UnBatchExport in 'UnBatchExport.pas' {BatchExpot},
  Udb in 'Udb.pas' {dm: TDataModule},
  UPictureMag in 'UPictureMag.pas' {PictureMag},
  UBatchImport in 'UBatchImport.pas' {BatchImport},
  UEditInfo in 'UEditInfo.pas' {FrmEditInfo},
  Sysutils,
  Dialogs,
  UOperator in 'UOperator.pas' {OperatorForm},
  Ulogin in 'Ulogin.pas' {loginForm},
  Uquery in 'Uquery.pas' {QueryForm},
  phtMadeCard in 'phtMadeCard.pas' {frmMadeCard},
  phtComplete in 'phtComplete.pas' {frmComplete},
  phtDBConnect in 'phtDBConnect.pas' {frmDBConnect},
  phtDefaultValue in 'phtDefaultValue.pas' {frmDefaultValue},
  phtFieldLink in 'phtFieldLink.pas' {frmFieldLink},
  phtImport in 'phtImport.pas',
  phtImportData in 'phtImportData.pas' {frmImportData},
  phtImportForm in 'phtImportForm.pas' {frmImportForm},
  phtIfRepalce in 'phtIfRepalce.pas' {frmIfRepalce},
  ksgProgress in 'ksgProgress.pas' {frmProgress},
  phtBatchDelete in 'phtBatchDelete.pas' {frmBatchDelete},
  ksPicHandler in 'ksPicHandler.pas',
  uCardPrint in 'uCardPrint.pas' {frmCardPrint};

{$R *.RES}

begin
  Application.Initialize;
 { if (Now-StrToDate('2005-3-17')<=(ExpirationDate-15)) and
     (Now-StrToDate('2005-3-17')<ExpirationDate) then
  begin
    if Now-StrToDate('2005-3-17')< ExpirationDate then
    begin
       ShowMessage('��ʹ�õĳ�����'+IntToStr(ExpirationDate-
           Trunc(StrToFloat(FloatToStr(Now-StrToDate('2005-1-18')))))+
          '�����Ч����'+#13+'�뾡�������������ȡ����ϵ����������');
    end
    else
    begin
      ShowMessage('��ʹ�õĳ����Ѿ�������Ч���ޣ�'+#13+'�������������ȡ����ϵ����������');
      Application.Terminate;
      Exit;
    end;
  end;  }
  Application.Title := '���ո���ϵͳ';
  Application.CreateForm(Tdm, dm);
  Application.CreateForm(TPhotoSystem, PhotoSystem);
  Application.CreateForm(TOperatorForm, OperatorForm);
  Application.CreateForm(TloginForm, loginForm);
  Application.CreateForm(TfrmIfRepalce, frmIfRepalce);
  Application.CreateForm(TfrmProgress, frmProgress);
  Application.CreateForm(TfrmCardPrint, frmCardPrint);
  Application.Run;
end.


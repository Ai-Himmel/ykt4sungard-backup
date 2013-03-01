program Photo1;

uses
  Forms,
  UAPhoto1 in 'UAPhoto1.pas' {PhotoSystem},
  UASetCanon in 'UASetCanon.pas' {SetOption},
  UACount1 in 'UACount1.pas' {ReportCount1},
  UtConfigs in 'UtConfigs.pas',
  UnBatchExport in 'UnBatchExport.pas' {BatchExpot},
  Udb in 'Udb.pas' {dm: TDataModule},
  UPictureMag in 'UPictureMag.pas' {PictureMag},
  UBatchImport in 'UBatchImport.pas' {BatchImport};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(Tdm, dm);
  Application.CreateForm(TPhotoSystem, PhotoSystem);
  Application.CreateForm(TBatchImport, BatchImport);
  Application.Run;
end.

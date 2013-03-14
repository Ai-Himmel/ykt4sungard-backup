unit UMenuMan;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Menus;

type
  TfmSysFileMan = class(TForm)
    MainMenu: TMainMenu;
    N1: TMenuItem;
    miMenuTextToBin: TMenuItem;
    miMenuBinToText: TMenuItem;
    OpenDialog: TOpenDialog;
    SaveDialog: TSaveDialog;
    miLoadMenu: TMenuItem;
    miSaveMenu: TMenuItem;
    mnConfigTextToBin: TMenuItem;
    mnConfigBinToBin: TMenuItem;
    N2: TMenuItem;
    procedure miMenuTextToBinClick(Sender: TObject);
    procedure miMenuBinToTextClick(Sender: TObject);
    procedure miLoadMenuClick(Sender: TObject);
    procedure miSaveMenuClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmSysFileMan: TfmSysFileMan;

resourcestring
  SOpen = '打开%s';
  SSave = '保存%s';
  SMenuTextFileDes = '文本菜单文件';
  SMenuTextFilePostfix = 'mnt';
  SMenuTextFileFilters = '文本菜单文件|*.mnt|所有文件|*.*';
  SMenuBinFileDes = '二进制菜单文件';
  SMenuBinFilePostfix = 'mn';
  SMenuBinFileFilters = '二进制菜单文件|*.mn|所有文件|*.*';
  SConfigTextFileDes = '文本配置文件';
  SConfigTextFilePostfix = 'ini';
  SConfigTextFileFilters = '文本配置文件|*.mnt|所有文件|*.*';
  SConfigBinFileDes = '二进制配置文件';
  SConfigBinFilePostfix = 'in';
  SConfigBinFileFilters = '二进制配置文件|*.mn|所有文件|*.*';

implementation

{$R *.DFM}

uses KSClientConsts, FilterStreams, KSMenuAdmin, KSMenuFiles;

procedure TfmSysFileMan.miMenuTextToBinClick(Sender: TObject);
var
  TextStream : TFileStream;
  FilterStream  : TFilterStream;
  FileStream    : TFileStream;
  Filter : IStreamFilter;
begin
  OpenDialog.DefaultExt := SMenuTextFilePostfix;
  OpenDialog.Filter := SMenuTextFileFilters;
  OpenDialog.Title := Format(SOpen,[SMenuTextFileDes]);
  SaveDialog.DefaultExt := SMenuBinFilePostfix;
  SaveDialog.Filter := SMenuTextBinFilters;
  SaveDialog.Title := Format(SSave,[SMenuBinFileDes]);
  if OpenDialog.Execute and SaveDialog.Execute then
  begin
    TextStream    := nil;
    FilterStream  := nil;
    FileStream    := nil;
    try
      Filter        := TXorFilter.Create(SApplicationTitle);
      TextStream    := TFileStream.Create(OpenDialog.FileName,fmOpenRead);
      FileStream    := TFileStream.Create(SaveDialog.FileName,fmCreate);
      FilterStream  := TFilterStream.Create(FileStream, Filter);

      FilterStream.CopyFrom(TextStream,0);
    finally
      TextStream.Free;
      FilterStream.Free;
      FileStream.Free;
    end;
  end;
end;

procedure TfmSysFileMan.miMenuBinToTextClick(Sender: TObject);
var
  TextStream : TFileStream;
  FilterStream  : TFilterStream;
  FileStream    : TFileStream;
  Filter : IStreamFilter;
begin
  OpenDialog.DefaultExt := SMenuBinFilePostfix;
  OpenDialog.Filter := SMenuTextBinFilters;
  OpenDialog.Title := Format(SOpen,[SMenuBinFileDes]);
  SaveDialog.DefaultExt := SMenuTextFilePostfix;
  SaveDialog.Filter := SMenuTextFileFilters;
  SaveDialog.Title := Format(SSave,[SMenuTextFileDes]);
  if OpenDialog.Execute and SaveDialog.Execute then
  begin
    TextStream    := nil;
    FilterStream  := nil;
    FileStream    := nil;
    try
      Filter        := TXorFilter.Create(SApplicationTitle);
      TextStream    := TFileStream.Create(SaveTextDialog.FileName,fmCreate);
      FileStream    := TFileStream.Create(OpenBinDialog.FileName,fmOpenRead);
      FilterStream  := TFilterStream.Create(FileStream, Filter);

      TextStream.CopyFrom(FilterStream,0);
    finally
      TextStream.Free;
      FilterStream.Free;
      FileStream.Free;
    end;
  end;
end;

procedure TfmSysFileMan.miLoadMenuClick(Sender: TObject);
begin
  if OpenTextDialog.Execute then
  begin
    ReadMenuAdminFromFile(MenuAdmin, OpenTextDialog.FileName);
  end;
end;

procedure TfmSysFileMan.miSaveMenuClick(Sender: TObject);
begin
  if SaveTextDialog.Execute then
  begin
    WriteMenuAdminToFile(MenuAdmin, SaveTextDialog.FileName);
  end;
end;

procedure TfmSysFileMan.FormCreate(Sender: TObject);
begin
  MenuAdmin := TMenuAdmin.Create;
end;

procedure TfmSysFileMan.FormDestroy(Sender: TObject);
begin
  MenuAdmin.Free;
end;

end.

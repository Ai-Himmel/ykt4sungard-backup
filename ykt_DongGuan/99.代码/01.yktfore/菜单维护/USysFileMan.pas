unit USysFileMan;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USysFileMan
   <What>ά�������ļ��Ͳ˵��ļ��ĸ������ߡ���Ҫ�����ļ��ļ��ܺͽ��ܡ�
   <Written By> Huang YanLai (������)
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Menus, StdCtrls, Buttons, SkinCaption, WinSkinData,IniFiles;

type
  TfmSysFileMan = class(TForm)
    OpenDialog: TOpenDialog;
    SaveDialog: TSaveDialog;
    btnMenuToBate: TBitBtn;
    btnMenuToTxt: TBitBtn;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    SkinData1: TSkinData;
    SkinCaption1: TSkinCaption;
    btnClose: TBitBtn;
    procedure miLoadMenuClick(Sender: TObject);
    procedure miSaveMenuClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure btnMenuToBateClick(Sender: TObject);
    procedure btnMenuToTxtClick(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmSysFileMan: TfmSysFileMan;

resourcestring
  SOpen = '��%s';
  SSave = '����%s';
  SMenuTextFileDes = '�ı��˵��ļ�';
  SMenuTextFilePostfix = 'mnt';
  SMenuTextFileFilters = '�ı��˵��ļ�|*.mnt|�����ļ�|*.*';
  SMenuBinFileDes = '�����Ʋ˵��ļ�';
  SMenuBinFilePostfix = 'mn';
  SMenuBinFileFilters = '�����Ʋ˵��ļ�|*.mn|�����ļ�|*.*';
  SConfigTextFileDes = '�ı������ļ�';
  SConfigTextFilePostfix = 'ini';
  SConfigTextFileFilters = '�ı������ļ�|*.ini|�����ļ�|*.*';
  SConfigBinFileDes = '�����������ļ�';
  SConfigBinFilePostfix = 'in';
  SConfigBinFileFilters = '�����������ļ�|*.in|�����ļ�|*.*';

implementation

{$R *.DFM}

uses KSClientConsts, FilterStreams, KSMenuAdmin, KSMenuFiles, KSFileSystem,
  UQhClientConsts;

procedure TfmSysFileMan.FormCreate(Sender: TObject);
var
  //IsCenter : Boolean;
  myfile:TIniFile;
  FExePath:string;
  skinTag:Integer;
  FSkinFile:string;
begin
  MenuAdmin := TMenuAdmin.Create;
  {$ifdef Center}
  //IsCenter := True;
  {$else}
  IsCenter := False;
  {$endif}
  //miMenuTextToBin.Visible := IsCenter;
  //miMenuBinToText.Visible := IsCenter;
  //miLoadMenu.Visible := IsCenter;
  //miSaveMenu.Visible := IsCenter;
  //?????????hanjiwei add it 20080331----------------------------------
  myfile := nil;
  try
    FExePath:= ExtractFilePath(Application.ExeName);
    myfile := TIniFile.Create(FExePath+'../configs/SetPara.ini');
    skinTag := myfile.ReadInteger('skins','skin',0);
    FSkinFile := FExePath + '../skins/'+inttostr(skinTag)+'.skn';
    SkinData1.SkinFile := FSkinFile;
    if not SkinData1.Active then
      SkinData1.Active := True;
  //----------------------------------------------------------------------------
  finally
    myfile.Destroy;
  end;
end;

procedure TfmSysFileMan.FormDestroy(Sender: TObject);
begin
  MenuAdmin.Free;
end;

procedure TfmSysFileMan.miLoadMenuClick(Sender: TObject);
begin
  OpenDialog.DefaultExt := SMenuTextFilePostfix;
  OpenDialog.Filter := SMenuTextFileFilters;
  OpenDialog.Title := Format(SOpen,[SMenuTextFileDes]);
  OpenDialog.FileName := '';
  if OpenDialog.Execute then
  begin
    ReadMenuAdminFromFile(MenuAdmin, OpenDialog.FileName);
  end;
end;

procedure TfmSysFileMan.miSaveMenuClick(Sender: TObject);
begin
  SaveDialog.DefaultExt := SMenuTextFilePostfix;
  SaveDialog.Filter := SMenuTextFileFilters;
  SaveDialog.Title := Format(SSave,[SMenuTextFileDes]);
  SaveDialog.FileName := '';
  if SaveDialog.Execute then
  begin
    WriteMenuAdminToFile(MenuAdmin, SaveDialog.FileName);
  end;
end;

procedure TfmSysFileMan.btnMenuToBateClick(Sender: TObject);
begin
  OpenDialog.DefaultExt := SMenuTextFilePostfix;
  OpenDialog.Filter := SMenuTextFileFilters;
  OpenDialog.Title := Format(SOpen,[SMenuTextFileDes]);
  OpenDialog.FileName := '';
  SaveDialog.DefaultExt := SMenuBinFilePostfix;
  SaveDialog.Filter := SMenuBinFileFilters;
  SaveDialog.Title := Format(SSave,[SMenuBinFileDes]);
  SaveDialog.FileName := '';
  if OpenDialog.Execute and SaveDialog.Execute then
  begin
    TextToBin(OpenDialog.FileName,SaveDialog.FileName,SKingStarFutureBinMnuKey);
  end;

end;

procedure TfmSysFileMan.btnMenuToTxtClick(Sender: TObject);
begin
  OpenDialog.DefaultExt := SMenuBinFilePostfix;
  OpenDialog.Filter := SMenuBinFileFilters;
  OpenDialog.Title := Format(SOpen,[SMenuBinFileDes]);
  OpenDialog.FileName := '';
  SaveDialog.DefaultExt := SMenuTextFilePostfix;
  SaveDialog.Filter := SMenuTextFileFilters;
  SaveDialog.Title := Format(SSave,[SMenuTextFileDes]);
  SaveDialog.FileName := '';
  if OpenDialog.Execute and SaveDialog.Execute then
  begin
    BinToText(OpenDialog.FileName,SaveDialog.FileName,SKingStarFutureBinMnuKey);
  end;

end;

procedure TfmSysFileMan.BitBtn1Click(Sender: TObject);
begin
  OpenDialog.DefaultExt := SConfigTextFilePostfix;
  OpenDialog.Filter := SConfigTextFileFilters;
  OpenDialog.Title := Format(SOpen,[SConfigTextFileDes]);
  OpenDialog.FileName := '';
  SaveDialog.DefaultExt := SConfigBinFilePostfix;
  SaveDialog.Filter := SConfigBinFileFilters;
  SaveDialog.Title := Format(SSave,[SConfigBinFileDes]);
  SaveDialog.FileName := '';
  if OpenDialog.Execute and SaveDialog.Execute then
  begin
    TextToBin(OpenDialog.FileName,SaveDialog.FileName,SKingStarFutureBinCfgKey);
  end;

end;

procedure TfmSysFileMan.BitBtn2Click(Sender: TObject);
begin
  OpenDialog.DefaultExt := SConfigBinFilePostfix;
  OpenDialog.Filter := SConfigBinFileFilters;
  OpenDialog.Title := Format(SOpen,[SConfigBinFileDes]);
  OpenDialog.FileName := '';
  SaveDialog.DefaultExt := SConfigTextFilePostfix;
  SaveDialog.Filter := SConfigTextFileFilters;
  SaveDialog.Title := Format(SSave,[SConfigTextFileDes]);
  SaveDialog.FileName := '';
  if OpenDialog.Execute and SaveDialog.Execute then
  begin
    BinToText(OpenDialog.FileName,SaveDialog.FileName,SKingStarFutureBinCfgKey);
  end;

end;

procedure TfmSysFileMan.btnCloseClick(Sender: TObject);
begin
  Application.Terminate;
end;

end.

object frmImportData: TfrmImportData
  Left = 449
  Top = 191
  Width = 510
  Height = 412
  BorderIcons = [biSystemMenu]
  Caption = '��������'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '����'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object GroupBox1: TGroupBox
    Left = 10
    Top = 320
    Width = 481
    Height = 7
    TabOrder = 0
  end
  object btnCancel: TButton
    Left = 128
    Top = 342
    Width = 75
    Height = 25
    Caption = 'ȡ��'
    ModalResult = 2
    TabOrder = 1
  end
  object btnBack: TButton
    Left = 232
    Top = 342
    Width = 75
    Height = 25
    Caption = '��һ��(&B)'
    Enabled = False
    TabOrder = 2
    OnClick = btnBackClick
  end
  object btnNext: TButton
    Left = 312
    Top = 342
    Width = 75
    Height = 25
    Caption = '��һ��(&N) '
    TabOrder = 3
    OnClick = btnNextClick
  end
  object btnFinish: TButton
    Left = 416
    Top = 342
    Width = 75
    Height = 25
    BiDiMode = bdRightToLeft
    Caption = '���'
    ParentBiDiMode = False
    TabOrder = 4
    OnClick = btnFinishClick
  end
  object pnlMainland: TPanel
    Left = 0
    Top = 0
    Width = 497
    Height = 321
    BevelOuter = bvNone
    TabOrder = 5
  end
  object OpenDialog: TOpenDialog
    Filter = 'Microsoft Visual FoxPro|*.dbf|Microsoft Access|*.mdb'
    Title = '��ѡ���������ļ�'
    Left = 16
    Top = 336
  end
end

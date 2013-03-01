object fMain: TfMain
  Left = 363
  Top = 55
  Width = 266
  Height = 528
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = '脱机拍照'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 14
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 258
    Height = 85
    Align = alTop
    Color = clInfoBk
    TabOrder = 0
    object lbl1: TLabel
      Left = 19
      Top = 25
      Width = 56
      Height = 14
      Caption = '学工号：'
    end
    object btnFetch: TButton
      Left = 165
      Top = 11
      Width = 75
      Height = 25
      Caption = '取照片 '
      TabOrder = 0
      OnClick = btnFetchClick
    end
    object btnSave: TButton
      Left = 165
      Top = 44
      Width = 75
      Height = 25
      Caption = '保存'
      TabOrder = 1
      OnClick = btnSaveClick
    end
    object edtPersonNo: TEdit
      Left = 19
      Top = 47
      Width = 128
      Height = 22
      TabOrder = 2
    end
  end
  object pnlPic: TPanel
    Left = 0
    Top = 85
    Width = 258
    Height = 365
    Align = alTop
    TabOrder = 1
    object imgPic: TImage
      Left = 1
      Top = 1
      Width = 256
      Height = 363
      Align = alClient
    end
  end
  object btnConfig: TButton
    Left = 68
    Top = 462
    Width = 75
    Height = 25
    Caption = '配置'
    TabOrder = 2
    OnClick = btnConfigClick
  end
  object btnExit: TButton
    Left = 170
    Top = 462
    Width = 75
    Height = 25
    Caption = '退出'
    ModalResult = 2
    TabOrder = 3
    OnClick = btnExitClick
  end
end

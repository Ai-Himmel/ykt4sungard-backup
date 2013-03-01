object frmProgress: TfrmProgress
  Left = 374
  Top = 201
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'frmProgress'
  ClientHeight = 115
  ClientWidth = 367
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShortCut = FormShortCut
  PixelsPerInch = 96
  TextHeight = 13
  object pnlBoard: TPanel
    Left = 0
    Top = 0
    Width = 367
    Height = 115
    Align = alClient
    BevelInner = bvLowered
    BorderWidth = 3
    TabOrder = 0
    object Label1: TLabel
      Left = 120
      Top = 88
      Width = 123
      Height = 13
      Caption = '按 <Esc> 取消本次操作 '
      Visible = False
    end
    object lblTitle: TLabel
      Left = 16
      Top = 16
      Width = 24
      Height = 13
      Caption = '导出'
    end
    object lblPosition: TLabel
      Left = 16
      Top = 40
      Width = 51
      Height = 13
      Caption = '第 条记录'
    end
    object ProgressBar: TProgressBar
      Left = 16
      Top = 64
      Width = 337
      Height = 17
      Min = 0
      Max = 100
      TabOrder = 0
    end
  end
end

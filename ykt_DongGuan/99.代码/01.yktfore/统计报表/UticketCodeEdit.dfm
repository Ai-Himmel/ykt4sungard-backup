object frmTicketCodeEdit: TfrmTicketCodeEdit
  Left = 308
  Top = 311
  BorderStyle = bsDialog
  Caption = '更新经费本、支票号码'
  ClientHeight = 144
  ClientWidth = 262
  Color = 15458000
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 32
    Width = 53
    Height = 15
    Caption = '旧号码:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 32
    Top = 64
    Width = 53
    Height = 15
    Caption = '新号码:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object edtOldCode: TEdit
    Left = 88
    Top = 29
    Width = 137
    Height = 21
    ReadOnly = True
    TabOrder = 0
  end
  object edtNewCode: TEdit
    Left = 88
    Top = 61
    Width = 137
    Height = 21
    TabOrder = 1
  end
  object RzButton1: TRzButton
    Left = 48
    Top = 96
    Width = 65
    Caption = '确 定'
    Color = 15791348
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    HighlightColor = 16026986
    HotTrack = True
    HotTrackColor = 3983359
    ParentFont = False
    TabOrder = 2
    OnClick = RzButton1Click
  end
  object RzButton2: TRzButton
    Left = 152
    Top = 96
    Width = 65
    Caption = '取 消'
    Color = 15791348
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    HighlightColor = 16026986
    HotTrack = True
    HotTrackColor = 3983359
    ParentFont = False
    TabOrder = 3
    OnClick = RzButton2Click
  end
end

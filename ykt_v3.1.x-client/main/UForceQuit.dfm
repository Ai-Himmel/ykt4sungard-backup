object fmForceQuit: TfmForceQuit
  Left = 327
  Top = 288
  BorderStyle = bsDialog
  Caption = 'fmForceQuit'
  ClientHeight = 133
  ClientWidth = 351
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lblShine: TLabel
    Left = 0
    Top = 0
    Width = 351
    Height = 13
    Align = alTop
    Alignment = taCenter
    Caption = 'ϵͳ�Ѿ��յ�ǿ��¼��ָ�����%d�����Զ��رգ�'
    Color = clYellow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object btnOK: TBitBtn
    Left = 129
    Top = 104
    Width = 91
    Height = 25
    Caption = '�������رգ�'
    Default = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = btnOKClick
  end
  object Memo: TMemo
    Left = 0
    Top = 13
    Width = 351
    Height = 80
    Align = alTop
    Enabled = False
    ImeName = ''
    ReadOnly = True
    TabOrder = 1
  end
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 312
    Top = 24
  end
end

object frmGetPhotoSet: TfrmGetPhotoSet
  Left = 319
  Top = 293
  BorderStyle = bsDialog
  Caption = #33719#21462#29031#29255#35774#32622
  ClientHeight = 235
  ClientWidth = 420
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 420
    Height = 235
    Align = alClient
    BevelOuter = bvNone
    Color = 16053492
    TabOrder = 0
    object lbl1: TLabel
      Left = 24
      Top = 16
      Width = 105
      Height = 15
      AutoSize = False
      Caption = #29031#29255#25152#22312#25991#20214#22841
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 24
      Top = 72
      Width = 105
      Height = 15
      AutoSize = False
      Caption = #29031#29255#21517#31216#21069#32512
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 24
      Top = 128
      Width = 105
      Height = 15
      AutoSize = False
      Caption = #20445#23384#26412#22320#36335#24452
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object edtPath: TEdit
      Left = 24
      Top = 40
      Width = 353
      Height = 21
      TabOrder = 0
    end
    object edtPre: TEdit
      Left = 24
      Top = 96
      Width = 353
      Height = 21
      TabOrder = 1
    end
    object edtNativePath: TEdit
      Left = 24
      Top = 152
      Width = 353
      Height = 21
      TabOrder = 2
    end
    object btnLogin: TButton
      Left = 224
      Top = 184
      Width = 65
      Height = 25
      Caption = #30830' '#23450
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = btnLoginClick
    end
    object btnExit: TButton
      Left = 304
      Top = 184
      Width = 65
      Height = 25
      Caption = #21462' '#28040
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = btnExitClick
    end
  end
end

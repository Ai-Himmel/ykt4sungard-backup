object frmModifyPwd: TfrmModifyPwd
  Left = 331
  Top = 242
  BorderStyle = bsDialog
  Caption = #20462#25913#23494#30721
  ClientHeight = 188
  ClientWidth = 321
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 64
    Top = 16
    Width = 60
    Height = 15
    AutoSize = False
    Caption = #30331#24405#21517#65306
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
  end
  object lblName: TLabel
    Left = 128
    Top = 16
    Width = 145
    Height = 15
    AutoSize = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
  end
  object Label1: TLabel
    Left = 64
    Top = 47
    Width = 60
    Height = 15
    AutoSize = False
    Caption = #21407#23494#30721#65306
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 64
    Top = 77
    Width = 60
    Height = 15
    AutoSize = False
    Caption = #26032#23494#30721#65306
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 34
    Top = 108
    Width = 90
    Height = 15
    AutoSize = False
    Caption = #26657#39564#26032#23494#30721#65306
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
  end
  object edtOld: TEdit
    Left = 128
    Top = 41
    Width = 129
    Height = 21
    PasswordChar = '*'
    TabOrder = 0
  end
  object edtNew: TEdit
    Left = 128
    Top = 73
    Width = 129
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
  end
  object edtVerify: TEdit
    Left = 128
    Top = 104
    Width = 129
    Height = 21
    PasswordChar = '*'
    TabOrder = 2
  end
  object btnOk: TBitBtn
    Left = 96
    Top = 144
    Width = 65
    Height = 25
    Caption = '&O'#30830' '#23450
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = btnOkClick
  end
  object btnCancle: TBitBtn
    Left = 192
    Top = 144
    Width = 65
    Height = 25
    Caption = '&C'#21462' '#28040
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = btnCancleClick
  end
end

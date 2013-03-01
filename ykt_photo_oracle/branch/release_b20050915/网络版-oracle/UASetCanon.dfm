object SetOption: TSetOption
  Left = 275
  Top = 39
  Width = 392
  Height = 338
  Caption = '相机首选项设置'
  Color = clInfoBk
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel6: TPanel
    Left = 0
    Top = 0
    Width = 384
    Height = 57
    Align = alTop
    Color = clInfoBk
    TabOrder = 0
    object Label9: TLabel
      Left = 16
      Top = 8
      Width = 73
      Height = 13
      AutoSize = False
      Caption = '文件前缀'
    end
    object Label12: TLabel
      Left = 136
      Top = 8
      Width = 137
      Height = 13
      AutoSize = False
      Caption = '（最长 16 个字符）'
    end
    object Edit8: TEdit
      Left = 16
      Top = 32
      Width = 177
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 0
      OnChange = Edit8Change
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 57
    Width = 384
    Height = 72
    Align = alTop
    Color = clInfoBk
    TabOrder = 1
    object Label8: TLabel
      Left = 248
      Top = 20
      Width = 41
      Height = 13
      AutoSize = False
      Caption = '开始'
    end
    object Label3: TLabel
      Left = 112
      Top = 20
      Width = 65
      Height = 13
      AutoSize = False
      Caption = '数字位数'
    end
    object Label10: TLabel
      Left = 8
      Top = 56
      Width = 24
      Height = 13
      Caption = '示例'
    end
    object Label2: TLabel
      Left = 16
      Top = 80
      Width = 32
      Height = 13
      Caption = 'Label2'
    end
    object Label4: TLabel
      Left = 16
      Top = 8
      Width = 97
      Height = 13
      AutoSize = False
      Caption = '分配序列号'
    end
    object Edit4: TEdit
      Left = 248
      Top = 44
      Width = 81
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 0
      Text = '1'
    end
    object Edit3: TEdit
      Left = 112
      Top = 44
      Width = 81
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 1
      Text = '5'
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 193
    Width = 384
    Height = 57
    Align = alClient
    Color = clInfoBk
    TabOrder = 2
    object Label5: TLabel
      Left = 16
      Top = 12
      Width = 121
      Height = 13
      AutoSize = False
      Caption = '本地保存文件夹'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Edit5: TEdit
      Left = 16
      Top = 36
      Width = 353
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 0
    end
  end
  object Panel5: TPanel
    Left = 0
    Top = 250
    Width = 384
    Height = 54
    Align = alBottom
    Color = clInfoBk
    TabOrder = 3
    object Button1: TButton
      Left = 48
      Top = 16
      Width = 73
      Height = 25
      Caption = '确 认'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ModalResult = 1
      ParentFont = False
      TabOrder = 0
    end
    object Button2: TButton
      Left = 200
      Top = 16
      Width = 73
      Height = 25
      Caption = '取 消'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button2Click
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 129
    Width = 384
    Height = 64
    Align = alTop
    Color = clInfoBk
    TabOrder = 4
    object Label6: TLabel
      Left = 16
      Top = 12
      Width = 153
      Height = 13
      AutoSize = False
      Caption = '下载图像的目标文件夹'
    end
    object Edit2: TEdit
      Left = 16
      Top = 36
      Width = 353
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 0
    end
  end
end

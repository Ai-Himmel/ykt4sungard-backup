object faCalendar: TfaCalendar
  Left = 0
  Top = 0
  Width = 429
  Height = 277
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
  Font.Style = []
  ParentColor = False
  ParentFont = False
  TabOrder = 0
  object Image: TImage
    Left = 10
    Top = 40
    Width = 409
    Height = 225
    OnClick = ImageClick
  end
  object lblDate: TLabel
    Left = 256
    Top = 12
    Width = 113
    Height = 16
    AutoSize = False
    Font.Charset = GB2312_CHARSET
    Font.Color = clBlue
    Font.Height = -16
    Font.Name = '黑体'
    Font.Style = []
    ParentFont = False
  end
  object cbMonth: TComboBox
    Left = 10
    Top = 10
    Width = 100
    Height = 20
    Style = csDropDownList
    ItemHeight = 12
    TabOrder = 0
    OnChange = DateTimeChange
    Items.Strings = (
      '一月'
      '二月'
      '三月'
      '四月'
      '五月'
      '六月'
      '七月'
      '八月'
      '九月'
      '十月'
      '十一月'
      '十二月')
  end
  object edYear: TEdit
    Left = 120
    Top = 10
    Width = 100
    Height = 20
    Enabled = False
    TabOrder = 1
    OnChange = DateTimeChange
  end
  object UpDown: TUpDown
    Left = 220
    Top = 10
    Width = 16
    Height = 20
    Min = 10
    Max = 10
    Position = 10
    TabOrder = 2
    Wrap = False
    OnClick = UpDownClick
  end
end

object faLiquidateList: TfaLiquidateList
  Left = 0
  Top = 0
  Width = 590
  Height = 354
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = '宋体'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object GroupBox: TGroupBox
    Left = 0
    Top = 0
    Width = 590
    Height = 354
    Align = alClient
    Caption = '过程信息'
    TabOrder = 0
    object ListBox: TListBox
      Left = 2
      Top = 15
      Width = 586
      Height = 337
      Align = alClient
      ItemHeight = 13
      PopupMenu = PopupMenu
      TabOrder = 0
      OnMouseDown = ListBoxMouseDown
    end
  end
  object PopupMenu: TPopupMenu
    Left = 232
    Top = 112
    object nClear: TMenuItem
      Caption = '清除'
      OnClick = nClearClick
    end
  end
end

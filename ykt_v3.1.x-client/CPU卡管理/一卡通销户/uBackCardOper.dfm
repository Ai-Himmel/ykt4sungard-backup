object frmBackCardOper: TfrmBackCardOper
  Left = 364
  Top = 299
  BorderStyle = bsDialog
  Caption = '退校园卡操作'
  ClientHeight = 129
  ClientWidth = 249
  Color = 15458000
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
  object WVLabel11: TWVLabel
    Left = 24
    Top = 69
    Width = 48
    Height = 12
    Caption = '金额精度'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object rgyj: TRzRadioGroup
    Left = 16
    Top = 6
    Width = 169
    Height = 45
    Anchors = [akLeft]
    BorderWidth = 1
    Caption = '是否退还押金'
    Color = 15458000
    Columns = 2
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    ItemFrameColor = 8409372
    ItemHotTrack = True
    ItemHighlightColor = 2203937
    ItemHotTrackColor = 3983359
    ItemHotTrackColorType = htctActual
    ItemIndex = 1
    Items.Strings = (
      '不退押金'
      '退还押金')
    ParentFont = False
    TabOrder = 0
    ThemeAware = False
  end
  object btnOk: TRzBitBtn
    Left = 16
    Top = 96
    Width = 65
    Caption = '确　定'
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
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancle: TRzBitBtn
    Left = 120
    Top = 96
    Width = 65
    Caption = '取　消'
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
    OnClick = btnCancleClick
  end
  object cbbType: TWVComboBox
    Left = 80
    Top = 65
    Width = 105
    Height = 21
    Style = csDropDownList
    Color = clWhite
    ItemHeight = 13
    TabOrder = 3
    FieldName = '充值类型'
    DataPresentType = 'IDOBJECTS'
    AutoDropDown = False
    ItemsDataEntry = '122'
  end
end

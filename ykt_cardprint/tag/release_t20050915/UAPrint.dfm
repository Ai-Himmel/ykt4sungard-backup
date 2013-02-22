object APrintForm: TAPrintForm
  Left = 253
  Top = 233
  BorderStyle = bsDialog
  Caption = '卡片补打'
  ClientHeight = 208
  ClientWidth = 437
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  Scaled = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 16
    Width = 24
    Height = 13
    Caption = '工号'
  end
  object Label2: TLabel
    Left = 128
    Top = 64
    Width = 42
    Height = 13
    AutoSize = False
    Caption = '姓名：'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 128
    Top = 96
    Width = 42
    Height = 13
    AutoSize = False
    Caption = '单位：'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 128
    Top = 128
    Width = 42
    Height = 13
    AutoSize = False
    Caption = '工号：'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LName: TLabel
    Left = 168
    Top = 64
    Width = 241
    Height = 13
    AutoSize = False
    Font.Charset = GB2312_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object LDep: TLabel
    Left = 168
    Top = 96
    Width = 241
    Height = 13
    AutoSize = False
    Font.Charset = GB2312_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object LNo: TLabel
    Left = 168
    Top = 128
    Width = 241
    Height = 13
    AutoSize = False
    Font.Charset = GB2312_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 129
    Top = 165
    Width = 42
    Height = 13
    AutoSize = False
    Caption = '类别：'
    Font.Charset = GB2312_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object QuickRep1: TQuickRep
    Left = 24
    Top = 263
    Width = 455
    Height = 286
    Frame.Color = clBlack
    Frame.DrawTop = False
    Frame.DrawBottom = False
    Frame.DrawLeft = False
    Frame.DrawRight = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    Functions.Strings = (
      'PAGENUMBER'
      'COLUMNNUMBER'
      'REPORTTITLE')
    Functions.DATA = (
      '0'
      '0'
      #39#39)
    Options = [FirstPageHeader, LastPageFooter]
    Page.Columns = 1
    Page.Orientation = poLandscape
    Page.PaperSize = Custom
    Page.Values = (
      0
      540
      0
      860
      0
      0
      0)
    PrinterSettings.Copies = 1
    PrinterSettings.Duplex = False
    PrinterSettings.FirstPage = 0
    PrinterSettings.LastPage = 0
    PrinterSettings.OutputBin = Auto
    PrintIfEmpty = True
    SnapToGrid = True
    Units = MM
    Zoom = 140
    object DetailBand1: TQRBand
      Left = 0
      Top = 0
      Width = 455
      Height = 285
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clWhite
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        538.616071428571
        859.895833333333)
      BandType = rbDetail
      object QRLabel4: TQRLabel
        Left = 171
        Top = 90
        Width = 278
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          43.4672619047619
          323.169642857143
          170.089285714286
          525.386904761905)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Caption = 'QRLabel4'
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '黑体'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 9
      end
    end
  end
  object edtNo: TEdit
    Left = 56
    Top = 12
    Width = 121
    Height = 21
    ImeName = '中文 (简体) - 微软拼音'
    TabOrder = 1
    OnKeyDown = edtNoKeyDown
  end
  object btnQuery: TButton
    Left = 192
    Top = 8
    Width = 65
    Height = 25
    Caption = '&Q查询'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = btnQueryClick
  end
  object btnPreview: TButton
    Left = 272
    Top = 8
    Width = 57
    Height = 25
    Caption = '&P补打'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = btnPreviewClick
  end
  object chkS: TCheckBox
    Left = 296
    Top = 163
    Width = 121
    Height = 17
    Caption = '姓名是否留空格'
    TabOrder = 4
  end
  object Button1: TButton
    Left = 344
    Top = 8
    Width = 57
    Height = 25
    Caption = '&E退出'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = Button1Click
  end
  object Panel1: TPanel
    Left = 24
    Top = 40
    Width = 85
    Height = 112
    BevelInner = bvLowered
    Caption = '照片显示'
    TabOrder = 6
    object Image1: TImage
      Left = 2
      Top = 2
      Width = 82
      Height = 107
      Center = True
      Stretch = True
    end
  end
  object cbType: TComboBox
    Left = 192
    Top = 160
    Width = 89
    Height = 21
    ImeName = '中文 (简体) - 拼音加加3.11'
    ItemHeight = 13
    TabOrder = 7
    Items.Strings = (
      '教授'
      '研究员')
  end
  object ADOQuery1: TADOQuery
    AutoCalcFields = False
    Connection = dm.ADOConnection1
    CursorType = ctUnspecified
    MarshalOptions = moMarshalModifiedOnly
    EnableBCD = False
    ParamCheck = False
    Parameters = <>
    Left = 48
    Top = 161
  end
  object ADOQuery2: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 88
    Top = 161
  end
end

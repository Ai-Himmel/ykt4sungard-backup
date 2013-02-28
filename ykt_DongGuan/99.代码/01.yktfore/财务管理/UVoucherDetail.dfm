object frmVoucherDetail: TfrmVoucherDetail
  Left = 247
  Top = 138
  BorderStyle = bsDialog
  Caption = '凭证浏览'
  ClientHeight = 466
  ClientWidth = 814
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
  object pnlTop: TPanel
    Left = 0
    Top = 0
    Width = 814
    Height = 57
    Align = alTop
    BevelOuter = bvNone
    Color = 15458000
    TabOrder = 0
    object lbl1: TLabel
      Left = 14
      Top = 37
      Width = 56
      Height = 14
      Caption = '凭证类型'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 342
      Top = 37
      Width = 56
      Height = 14
      Caption = '附件张数'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 190
      Top = 35
      Width = 56
      Height = 14
      Caption = '凭证日期'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object pnl1: TPanel
      Left = 0
      Top = 0
      Width = 814
      Height = 33
      Align = alTop
      BevelOuter = bvNone
      Caption = '记 账 凭 证'
      Color = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -20
      Font.Name = '宋体'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      TabOrder = 0
    end
    object cbbVType: TWVComboBox
      Left = 76
      Top = 33
      Width = 109
      Height = 21
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 13
      TabOrder = 1
      FieldName = '凭证类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '-61'
    end
    object edtDate: TWVEdit
      Left = 252
      Top = 33
      Width = 85
      Height = 21
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<凭证日期>'
      FieldName = '凭证日期'
    end
    object edtNum: TWVEdit
      Left = 401
      Top = 33
      Width = 46
      Height = 21
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<单据数>'
      FieldName = '单据数'
    end
  end
  object dbgrdh1: TDBGridEh
    Left = 0
    Top = 57
    Width = 814
    Height = 320
    Align = alClient
    EvenRowColor = clInactiveCaptionText
    FixedColor = clInactiveCaptionText
    Flat = True
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = '宋体'
    Font.Style = []
    FooterColor = clInactiveCaptionText
    FooterFont.Charset = GB2312_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -16
    FooterFont.Name = '宋体'
    FooterFont.Style = []
    FooterRowCount = 1
    OddRowColor = clInfoBk
    Options = [dgEditing, dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    OptionsEh = [dghHighlightFocus, dghClearSelection, dghEnterAsTab, dghDialogFind]
    ParentFont = False
    SumList.Active = True
    TabOrder = 1
    TitleFont.Charset = GB2312_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -14
    TitleFont.Name = '宋体'
    TitleFont.Style = []
    UseMultiTitle = True
    OnColEnter = dbgrdh1ColEnter
    OnDrawColumnCell = dbgrdh1DrawColumnCell
    OnKeyPress = dbgrdh1KeyPress
    Columns = <
      item
        EditButtons = <>
        FieldName = 'certificate'
        Footer.Alignment = taRightJustify
        Footer.FieldName = 'certificate'
        Footer.Value = '合计：'
        Footer.ValueType = fvtStaticText
        Footers = <>
        Title.Caption = '摘  要'
        Width = 160
      end
      item
        EditButtons = <>
        FieldName = 'subjno'
        Footers = <>
        Title.Caption = '科目号'
        Width = 80
      end
      item
        EditButtons = <>
        FieldName = 'subjname'
        Footers = <>
        ReadOnly = True
        Title.Caption = '科目名称'
        Width = 250
      end
      item
        EditButtons = <>
        FieldName = 'debit'
        Footer.FieldName = 'debit'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Caption = '金    额|借  方'
        Width = 145
      end
      item
        EditButtons = <>
        FieldName = 'credit'
        Footer.FieldName = 'credit'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Caption = '金    额|贷  方'
        Width = 145
      end>
  end
  object rzpnlTot: TRzPanel
    Left = 0
    Top = 377
    Width = 814
    Height = 22
    Align = alBottom
    BorderInner = fsFlat
    BorderOuter = fsFlat
    Color = clScrollBar
    TabOrder = 3
    object lblUPCASE: TLabel
      Left = 77
      Top = 5
      Width = 473
      Height = 14
      AutoSize = False
      Caption = '大写金额'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lbl4: TLabel
      Left = 8
      Top = 5
      Width = 60
      Height = 14
      AutoSize = False
      Caption = '大写金额：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
  end
  object pnl2: TPanel
    Left = 0
    Top = 399
    Width = 814
    Height = 26
    Align = alBottom
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 4
    object lbl2: TLabel
      Left = 200
      Top = 6
      Width = 41
      Height = 14
      AutoSize = False
      Caption = '制单：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblOperName: TLabel
      Left = 240
      Top = 6
      Width = 57
      Height = 14
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 344
      Top = 6
      Width = 65
      Height = 14
      AutoSize = False
      Caption = '结算方式：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label13: TLabel
      Left = 512
      Top = 6
      Width = 65
      Height = 14
      AutoSize = False
      Caption = '结算号码：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lbl3: TLabel
      Left = 8
      Top = 6
      Width = 41
      Height = 14
      AutoSize = False
      Caption = '记账：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblAccount: TLabel
      Left = 40
      Top = 6
      Width = 57
      Height = 14
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label15: TLabel
      Left = 96
      Top = 6
      Width = 41
      Height = 14
      AutoSize = False
      Caption = '审核：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblCheck: TLabel
      Left = 136
      Top = 6
      Width = 57
      Height = 14
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object cbbAccType: TWVComboBox
      Left = 412
      Top = 2
      Width = 93
      Height = 21
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 13
      TabOrder = 0
      FieldName = '结算方式'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*165'
    end
    object edtAccNo: TWVEdit
      Left = 580
      Top = 3
      Width = 85
      Height = 21
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<结算号码>'
      FieldName = '结算号码'
    end
  end
  object pnlBottom: TPanel
    Left = 0
    Top = 425
    Width = 814
    Height = 41
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 5
  end
  object edtMoney: TsncDBCurrencyEdit
    Left = 73
    Top = 240
    Width = 98
    Height = 18
    BorderStyle = bsNone
    Ctl3D = False
    CurrencySymbol = ' '
    DigitalNumber = 12
    FocusedColor = clWhite
    KilobitSeparatorColor = clBlue
    MoveOutAllowed = True
    NegativeFont.Charset = DEFAULT_CHARSET
    NegativeFont.Color = clWindowText
    NegativeFont.Height = -13
    NegativeFont.Name = 'MS Sans Serif'
    NegativeFont.Style = []
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 2
    TabStop = True
    Visible = False
    OnEnter = edtMoneyEnter
  end
  object ztblPZ: TZTable
    Connection = cmAccountMgrImp.conFB
    SortType = stDescending
    TableName = '"certificate"'
    Left = 136
    Top = 234
    object ztblPZcertificate: TStringField
      FieldName = 'certificate'
      Size = 300
    end
    object subjno: TStringField
      FieldName = 'subjno'
    end
    object ztblPZsubjname: TStringField
      FieldName = 'subjname'
      Size = 300
    end
    object ztblPZdebit: TFloatField
      FieldName = 'debit'
    end
    object ztblPZcredit: TFloatField
      FieldName = 'credit'
    end
  end
end

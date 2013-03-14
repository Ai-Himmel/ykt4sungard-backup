inherited faqhAccCertificate: TfaqhAccCertificate
  Width = 799
  Height = 527
  inherited UIPanel1: TUIPanel
    Top = 491
    Width = 799
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 624
      Top = 500
      Enabled = False
      TabOrder = 2
    end
    inherited btnPrint: TBitBtn
      Left = 709
      Top = 500
      TabOrder = 3
    end
    object btnAdd: TBitBtn
      Left = 628
      Top = 3
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '新建(&N)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnQueryClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF005A5A5A0052525200525252004A4A4A004A4A
        4A00181818001818180018181800181818001818180010101000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0094949400949494009494940084848400848484007373
        73007373730063636300636363005A5A5A005A5A5A0018181800FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00A59C9C00FFFFCE00FFFFCE00FFFFCE00FFFFCE00FFFF
        9400FFFF9400FFFF9400FFFF9400FF9400005A5A5A0018181800FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00ADADAD00FFFFCE00FFFFCE00FFFFCE00FFFFCE00FFFF
        CE00FFFF9400FFFF9400FFFF9400FFFF94006363630018181800FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00BDBDBD00FFFFCE000000000000000000FFFFCE000000
        0000000000000000000000000000FFFF94006363630018181800FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00BDBDBD00FFFFCE00FFFFCE00FFFFCE00FFFFCE00FFFF
        CE00FFFFCE00FFFFCE00FFFFCE00FFFF94007373730018181800FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00CECECE00FFFFCE000000000000000000000000000000
        0000FFFFCE000000000000000000FFFF94007373730018181800FFFFFF00FFFF
        FF00FFFFFF00002994000029940000299400FFFFCE00FFFFCE00FFFFCE00FFFF
        CE00FFFFCE00FFFFCE00FFFFCE00FFFFCE00848484004A4A4A00FFFFFF00FFFF
        FF00FFFFFF00002994000029CE0000299400000000000000000000000000FFFF
        CE00000000000000000000000000FFFFCE00848484004A4A4A00FFFFFF00FFFF
        FF00FFFFFF00002994000029CE0000299400FFFFCE00FFFFCE00FFFFCE00FFFF
        CE00FFFFCE00FFFFCE00FFFFCE00FFFFCE009494940052525200002994000029
        940000299400002994007B7BFF00002994000029940000299400002994000000
        00000000000000000000FFFFCE00FFFFCE009494940052525200002994000029
        CE000029CE007B7BFF007B7BFF007B7BFF000029CE000029CE0000299400FFFF
        CE00FFFFCE00FFFFCE005A5A5A005A5A5A005A5A5A005A5A5A00002994000029
        940000299400002994000029FF0000299400002994000029940000299400FFFF
        CE00FFFFCE00FFFFCE00BDBDBD00ADADAD00A59C9C00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00002994000029CE0000299400DEDEDE00D6D6D600D6D6D600CECE
        CE00CECECE00BDBDBD00BDBDBD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00002994000029CE0000299400FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00002994000029940000299400FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    object btnSave: TBitBtn
      Left = 716
      Top = 3
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '保存(&S)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnSaveClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00004A
        6B00004A6B00004A6B00004A6B00004A6B00004A6B00004A6B00004A6B00004A
        6B00004A6B00004A6B00004A6B00004A6B00DEDEDE00FFFFFF00006394002931
        2900007BB500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00D6DED600D6DE
        D600D6DED600EFF7EF00ADE7FF002931290000314A00FFFFFF000063940042B5
        FF00007BB500BDC6BD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00D6DE
        D600D6DED600D6DED600ADE7FF0042B5FF0000314A00FFFFFF000063940063C6
        FF00007BB500B5B5B500BDC6BD00BDC6BD00BDC6BD00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00D6DED600ADE7FF0042B5FF0000314A00FFFFFF000063940063C6
        FF00007BB500B5B5B500B5B5B500B5B5B500BDC6BD00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00BDC6BD00ADE7FF0042B5FF0000314A00FFFFFF000063940063C6
        FF00007BB5008C948C00A59C9C00B5B5B500B5B5B500BDC6BD00FFFFFF00BDC6
        BD00BDC6BD00B5B5B500ADE7FF0042B5FF0000314A00FFFFFF000063940063C6
        FF00007BB5008C948C008C948C00A59C9C00A59C9C00B5B5B500BDC6BD00BDC6
        BD00B5B5B500B5B5B500ADE7FF0042B5FF0000314A00FFFFFF00006394008CD6
        FF00007BB500007BB500007BB500007BB500007BB500007BB500007BB500007B
        B500007BB500007BB5008CD6FF0042B5FF0000314A00FFFFFF00006394008CD6
        FF008CD6FF008CD6FF008CD6FF008CD6FF008CD6FF008CD6FF008CD6FF008CD6
        FF008CD6FF008CD6FF00ADE7FF0042B5FF0000314A00FFFFFF00006394008CD6
        FF00007BB50000ADFF00007BB500007BB500007BB500007BB500007BB500007B
        B500007BB50042B5FF008CD6FF0042B5FF0000314A00FFFFFF000063940063C6
        FF00007BB500E7E7E70000639400DEDEDE00EFF7EF00EFF7EF00B5B5B500B5B5
        B500EFF7EF00007BB5008CD6FF0063C6FF0000314A00FFFFFF00006394008CD6
        FF00007BB500DEDEDE0000639400DEDEDE00D6DED600D6DED6007B7B7B007B7B
        7B00EFF7EF00006394008CD6FF0063C6FF0000314A00FFFFFF000063940042B5
        FF00007BB500DEDEDE0000639400DEDEDE00D6DED600D6DED6006B6B6B008C94
        8C00D6DED600006394008CD6FF0063C6FF0000314A00FFFFFF00006394008CD6
        FF00007BB500DEDEDE0000639400D6D6D600E7E7E700D6DED600293129002931
        2900EFF7EF00006394008CD6FF0063C6FF0000314A00FFFFFF0000639400ADE7
        FF00007BB500D6DED600007BB500E7E7E700D6D6D600D6D6D600D6D6D600DEDE
        DE00FFFFFF0000639400ADE7FF00004A6B00FFFFFF00FFFFFF00DEDEDE008484
        8400848484008484840084848400848484008484840084848400848484008484
        8400848484008484840084848400DEDEDE00DEDEDE00FFFFFF00}
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 799
    inherited Image1: TImage
      Width = 799
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 799
    Height = 473
    inherited Grid: TRzDBGrid
      Left = 528
      Top = 1000
      Width = 217
      Height = 92
      Align = alNone
      Anchors = [akLeft, akTop, akBottom]
      DataSource = nil
      Font.Height = -16
      Options = [dgEditing, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 4
      Columns = <
        item
          Expanded = False
          FieldName = 'certificate'
          PickList.Strings = ()
          Title.Caption = '摘要'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'subjno'
          PickList.Strings = ()
          Title.Caption = '科目号'
          Width = 71
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'subjname'
          PickList.Strings = ()
          Title.Caption = '科目名称'
          Width = 143
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'debit'
          PickList.Strings = ()
          Title.Caption = '借方金额'
          Width = 143
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'credit'
          PickList.Strings = ()
          Title.Caption = '贷方金额'
          Width = 143
          Visible = True
        end>
    end
    object dbgrdh1: TDBGridEh
      Left = 0
      Top = 57
      Width = 799
      Height = 394
      Align = alClient
      DataSource = DataSource
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
      OnColExit = dbgrdh1ColExit
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
          Width = 200
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
          Width = 200
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
    object edtMoney: TsncDBCurrencyEdit
      Left = 169
      Top = 208
      Width = 98
      Height = 18
      BorderStyle = bsNone
      Ctl3D = False
      CurrencySymbol = ' '
      DataSource = DataSource
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
      OnMoveOut = edtMoneyMoveOut
      OnEnter = edtMoneyEnter
      OnExit = edtMoneyExit
      OnKeyPress = edtMoneyKeyPress
    end
    object rzpnlTot: TRzPanel
      Left = 0
      Top = 451
      Width = 799
      Height = 22
      Align = alBottom
      BorderInner = fsFlat
      BorderOuter = fsGroove
      Color = clScrollBar
      TabOrder = 3
      object lblUPCASE: TLabel
        Left = 8
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
    end
    object pnlTop: TPanel
      Left = 0
      Top = 0
      Width = 799
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
      object Label1: TLabel
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
      object Label2: TLabel
        Left = 454
        Top = 37
        Width = 280
        Height = 14
        Caption = '提示：最大支持4笔分录，多于4笔则取前四笔'
        Font.Charset = GB2312_CHARSET
        Font.Color = clMaroon
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
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
        Width = 799
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
      object cbbVoucherType: TWVComboBox
        Left = 76
        Top = 33
        Width = 109
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '凭证类型'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-61'
      end
      object edtNum: TEdit
        Left = 400
        Top = 33
        Width = 41
        Height = 20
        TabOrder = 3
        Text = '0'
      end
      object edtDate: TWVEdit
        Left = 252
        Top = 33
        Width = 85
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<凭证日期>'
        WorkView = WorkView
        FieldName = '凭证日期'
      end
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '返回码'
        Caption = '返回码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '标志'
        Caption = '标志'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '分录总条数'
        Caption = '分录总条数'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '凭证类型'
        Caption = '凭证类型'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '凭证日期'
        Caption = '凭证日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '单据数'
        Caption = '单据数'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '行号1'
        Caption = '行号1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '摘要1'
        Caption = '摘要1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '科目代码1'
        Caption = '科目代码1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '借方金额1'
        Caption = '借方金额1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '贷方金额1'
        Caption = '贷方金额1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '行号2'
        Caption = '行号2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '摘要2'
        Caption = '摘要2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '科目代码2'
        Caption = '科目代码2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '借方金额2'
        Caption = '借方金额2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '贷方金额2'
        Caption = '贷方金额2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '行号3'
        Caption = '行号3'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '摘要3'
        Caption = '摘要3'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '科目代码3'
        Caption = '科目代码3'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '借方金额3'
        Caption = '借方金额3'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '贷方金额3'
        Caption = '贷方金额3'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '行号4'
        Caption = '行号4'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '摘要4'
        Caption = '摘要4'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '科目代码4'
        Caption = '科目代码4'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '借方金额4'
        Caption = '借方金额4'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '贷方金额4'
        Caption = '贷方金额4'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|专业名称|备注|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '凭证科目录入'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '分录总条数'
        FieldName = '分录总条数'
      end
      item
        ParamName = '凭证类型'
        FieldName = '凭证类型'
      end
      item
        ParamName = '凭证日期'
        FieldName = '凭证日期'
      end
      item
        ParamName = '单据数'
        FieldName = '单据数'
      end
      item
        ParamName = '行号1'
        FieldName = '行号1'
      end
      item
        ParamName = '摘要1'
        FieldName = '摘要1'
      end
      item
        ParamName = '科目代码1'
        FieldName = '科目代码1'
      end
      item
        ParamName = '借方金额1'
        FieldName = '借方金额1'
      end
      item
        ParamName = '贷方金额1'
        FieldName = '贷方金额1'
      end
      item
        ParamName = '行号2'
        FieldName = '行号2'
      end
      item
        ParamName = '摘要2'
        FieldName = '摘要2'
      end
      item
        ParamName = '科目代码2'
        FieldName = '科目代码2'
      end
      item
        ParamName = '借方金额2'
        FieldName = '借方金额2'
      end
      item
        ParamName = '贷方金额2'
        FieldName = '贷方金额2'
      end
      item
        ParamName = '行号3'
        FieldName = '行号3'
      end
      item
        ParamName = '摘要3'
        FieldName = '摘要3'
      end
      item
        ParamName = '科目代码3'
        FieldName = '科目代码3'
      end
      item
        ParamName = '借方金额3'
        FieldName = '借方金额3'
      end
      item
        ParamName = '贷方金额3'
        FieldName = '贷方金额3'
      end
      item
        ParamName = '行号4'
        FieldName = '行号4'
      end
      item
        ParamName = '摘要4'
        FieldName = '摘要4'
      end
      item
        ParamName = '科目代码4'
        FieldName = '科目代码4'
      end
      item
        ParamName = '借方金额4'
        FieldName = '借方金额4'
      end
      item
        ParamName = '贷方金额4'
        FieldName = '贷方金额4'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    DataSource = nil
    FieldName = '查询结果集'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    DataSet = ztblPZ
    Left = 264
    Top = 224
  end
  object ztblPZ: TZTable
    Connection = cmAccountMgrImp.conFB
    SortType = stDescending
    BeforeInsert = ztblPZBeforeInsert
    TableName = 'certificate'
    Left = 304
    Top = 226
    object ztblPZcertificate: TStringField
      FieldName = 'certificate'
      Size = 300
    end
    object ztblPZsubjno: TIntegerField
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
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '凭证科目查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '账号'
        FieldName = '账号'
      end
      item
        ParamName = '名称'
        FieldName = '名称'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 160
    Top = 256
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '账号'
        Caption = '账号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '名称'
        Caption = '名称'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '返回码'
        Caption = '返回码'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|借方账号|贷方账号|发生金额|工作站号|操作员号|错账操作员号|错账' +
          '操作员密码|'
      end>
    Left = 196
    Top = 255
  end
end

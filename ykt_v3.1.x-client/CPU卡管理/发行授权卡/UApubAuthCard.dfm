inherited faqhpubAuthCard: TfaqhpubAuthCard
  Width = 626
  Height = 416
  inherited UIPanel1: TUIPanel
    Top = 365
    Width = 626
    Height = 51
    inherited btnQuery: TBitBtn
      Left = 526
      Width = 94
      Hint = '发行授权卡'
      Caption = '发行授权卡'
      TabOrder = 1
      Visible = False
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 352
      TabOrder = 0
      Visible = False
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 30
      Width = 626
      Height = 21
      AutoStyle = False
      BorderColor = clWindow
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      Color = 16184303
      FlatColor = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 626
        Height = 21
        FrameStyle = fsStatus
        Align = alClient
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 626
    inherited Image1: TImage
      Width = 626
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 626
    Height = 347
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object rzchckgrp1: TRzCheckGroup
      Left = 184
      Top = 176
      Width = 401
      Height = 65
      Caption = '授权设备'
      Color = 16184303
      Columns = 3
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ItemFrameColor = 8409372
      ItemHighlightColor = 2203937
      ItemHotTrack = True
      ItemHotTrackColor = 3983359
      ItemHotTrackColorType = htctActual
      Items.Strings = (
        '收费终端    '
        '管理中心    '
        '充值终端    '
        '门禁系统'
        '认证终端'
        '区域控制')
      ParentFont = False
      TabOrder = 1
      CheckStates = (
        0
        0
        0
        0
        0
        0)
    end
    object grp1: TGroupBox
      Left = 184
      Top = 72
      Width = 401
      Height = 97
      Caption = '操作员信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label2: TLabel
        Left = 295
        Top = 64
        Width = 84
        Height = 14
        Caption = '格式yyyymmdd'
        Font.Charset = GB2312_CHARSET
        Font.Color = clMaroon
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object RzStatusPane2: TRzStatusPane
        Left = 13
        Top = 26
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '操 作 员'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 58
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '有效期限'
      end
      object WVComboBox3: TWVComboBox
        Left = 136
        Top = 28
        Width = 153
        Height = 22
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 14
        TabOrder = 0
        WorkView = WorkView
        FieldName = '操作员号'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-30'
      end
      object edtLimitDate: TRzEdit
        Left = 136
        Top = 59
        Width = 153
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        MaxLength = 8
        ParentFont = False
        TabOrder = 1
      end
    end
    object btnPubAuth: TBitBtn
      Left = 491
      Top = 251
      Width = 94
      Height = 25
      Hint = '发行授权卡'
      Caption = '发行授权卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnPubAuthClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 624
    Top = 416
    Width = 76
    Height = 22
    Align = alNone
    TabOrder = 3
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      DataSource = nil
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '交易卡号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Caption = '操作员号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Caption = '有效期'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '卡权限位'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Caption = '工作密钥'
          Visible = True
        end>
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
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '操作员号'
        Caption = '操作员号'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '物理卡号'
        Caption = '物理卡号'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '授权卡权限'
        Caption = '授权卡权限'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '业务操作员'
        Caption = '业务操作员'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '有效期'
        Caption = '有效期'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '交易卡号'
        Caption = '交易卡号'
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
        Name = '工作密钥'
        Caption = '工作密钥'
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
        Name = '操作员名称'
        Caption = '操作员名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|操作员号|物理卡号|授权卡权限|业务操作员|有效期|'
      end>
    Left = 52
    Top = 55
  end
  inherited MainRequest: TWVRequest
    ID = '发行授权卡'
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
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员号'
        FieldName = '操作员号'
      end
      item
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '授权卡权限'
        FieldName = '授权卡权限'
      end
      item
        ParamName = '业务操作员'
        FieldName = '业务操作员'
      end
      item
        ParamName = '有效期'
        FieldName = '有效期'
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '工作密钥'
        FieldName = '工作密钥'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员号'
        FieldName = '操作员号'
        Direction = bdParam2Field
      end
      item
        ParamName = '有效期'
        FieldName = '有效期'
        Direction = bdParam2Field
      end
      item
        ParamName = '授权卡权限'
        FieldName = '授权卡权限'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员名称'
        FieldName = '操作员名称'
        Direction = bdParam2Field
      end>
    Left = 88
    Top = 56
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 88
    Top = 96
  end
  inherited DataSource: TDataSource
    Left = 128
    Top = 96
  end
end

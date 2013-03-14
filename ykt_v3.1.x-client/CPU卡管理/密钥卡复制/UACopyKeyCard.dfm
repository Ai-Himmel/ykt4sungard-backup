inherited faqhCopyKeyCard: TfaqhCopyKeyCard
  Width = 626
  Height = 416
  inherited UIPanel1: TUIPanel
    Top = 365
    Width = 626
    Height = 51
    inherited btnQuery: TBitBtn
      Left = 438
      Top = 43
      Width = 94
      Hint = '发行授权卡'
      Caption = '发行授权卡'
      TabOrder = 2
      Visible = False
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 352
      Top = 43
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
      TabOrder = 0
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
    object grp1: TGroupBox
      Left = 184
      Top = 72
      Width = 401
      Height = 113
      Caption = '密码信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
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
        Caption = '保护密码'
      end
      object rzstspn1: TRzStatusPane
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
        Caption = '验证保护密码'
      end
      object edtKey: TRzEdit
        Left = 136
        Top = 27
        Width = 153
        Height = 22
        BiDiMode = bdLeftToRight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        MaxLength = 6
        ParentBiDiMode = False
        ParentFont = False
        PasswordChar = '*'
        TabOrder = 0
      end
      object edtRePwd: TRzEdit
        Left = 136
        Top = 59
        Width = 153
        Height = 22
        BiDiMode = bdLeftToRight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        MaxLength = 6
        ParentBiDiMode = False
        ParentFont = False
        PasswordChar = '*'
        TabOrder = 1
      end
    end
    object btnPubAuth: TBitBtn
      Left = 472
      Top = 203
      Width = 113
      Height = 25
      Hint = '密钥卡复制'
      Caption = '密钥卡复制(&C)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnPubAuthClick
    end
    object btnRead: TBitBtn
      Left = 336
      Top = 203
      Width = 117
      Height = 25
      Hint = '密钥卡复制'
      Caption = '原密钥卡密钥(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnReadClick
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|操作员号|物理卡号|授权卡权限|业务操作员|有效期|'
      end>
    Left = 52
    Top = 55
  end
  inherited MainRequest: TWVRequest
    ID = 'PASM卡发行'
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

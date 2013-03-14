inherited faqhNormalOpen: TfaqhNormalOpen
  Width = 700
  Height = 456
  inherited UIPanel1: TUIPanel
    Top = 420
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 96
      Top = 5
      Width = 90
      Caption = '读卡信息(&R)'
      TabOrder = 1
      Visible = False
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 10
      TabOrder = 0
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 2
    inherited Image1: TImage
      Width = 700
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 700
    Height = 402
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Caption = '后台流水号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Caption = '购水后台流水号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt0'
          PickList.Strings = ()
          Title.Caption = '大钱包出卡值'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt2'
          PickList.Strings = ()
          Title.Caption = '小钱包出卡值'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol9'
          PickList.Strings = ()
          Title.Caption = '大钱包次数'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = '小钱包次数'
          Visible = True
        end>
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 18
    Width = 700
    Height = 402
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 184
      Top = 72
      Width = 377
      Height = 265
      Caption = '卡信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 62
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
        Caption = '交易卡号'
      end
      object RzStatusPane1: TRzStatusPane
        Left = 13
        Top = 94
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
        Caption = '姓    名'
      end
      object RzStatusPane2: TRzStatusPane
        Left = 13
        Top = 126
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
        Caption = '学 /工号'
      end
      object RzStatusPane4: TRzStatusPane
        Left = 13
        Top = 158
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
        Caption = '主钱包余额'
      end
      object rzstspn1: TRzStatusPane
        Left = 13
        Top = 190
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
        Caption = '主钱包充值次数'
      end
      object RzStatusPane8: TRzStatusPane
        Left = 13
        Top = 30
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
        Caption = '物理卡号'
      end
      object rzstspn3: TRzStatusPane
        Left = 13
        Top = 223
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
        Caption = '是否常开卡'
      end
      object edtMoney: TWVEdit
        Left = 132
        Top = 159
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object edtNo: TWVEdit
        Left = 132
        Top = 127
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object edtName: TWVEdit
        Left = 132
        Top = 95
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 2
      end
      object edtCardNo: TWVEdit
        Left = 132
        Top = 63
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtBigNum: TWVEdit
        Left = 132
        Top = 191
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
      object edtPhyId: TWVEdit
        Left = 132
        Top = 31
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtOpenCard: TWVEdit
        Left = 132
        Top = 223
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
    end
    object btnReadCard: TButton
      Left = 270
      Top = 349
      Width = 90
      Height = 25
      Caption = '读卡信息(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnReadCardClick
    end
    object btnNorOpen: TButton
      Left = 370
      Top = 349
      Width = 90
      Height = 25
      Caption = '设置常开卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnNorOpenClick
    end
    object btnNormal: TButton
      Left = 470
      Top = 349
      Width = 90
      Height = 25
      Caption = '设置正常卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnNormalClick
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|交易卡号|充值金额|操作员代码|大钱包金额|大钱包次数|小钱包次数|' +
          '小钱包金额|'
      end>
    Left = 36
    Top = 231
  end
  inherited MainRequest: TWVRequest
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end>
    Left = 80
    Top = 232
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 80
    Top = 264
  end
  inherited DataSource: TDataSource
    Left = 80
    Top = 296
  end
end

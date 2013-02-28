inherited faqhSetSaveOper: TfaqhSetSaveOper
  Width = 681
  Height = 480
  inherited UIPanel1: TUIPanel
    Top = 439
    Width = 681
    Height = 41
    TabOrder = 2
    object lbl2: TLabel [0]
      Left = 168
      Top = 16
      Width = 84
      Height = 12
      Caption = '授权操作员密码'
    end
    inherited btnOK: TBitBtn
      Left = 584
      Top = 10
      Width = 81
      Caption = '授 权'
      Font.Style = []
      TabOrder = 2
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0084848400FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00007B00008484840084848400FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0000CE0000007B000084848400FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF0000CE000000CE0000007B00008484840084848400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF0000CE000000FF000000FF000000CE0000007B000084848400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF0000FF000000FF000000FF000000CE0000007B00008484840084848400FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000CE
        000000FF000000FF000000FF000000FF000000CE0000007B0000848484008484
        8400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000FF
        000063FF630000FF0000007B000000FF000000FF000000CE0000007B00008484
        840084848400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000FF
        000094FF940063FF6300007B0000FFFFFF0000FF000000FF000000CE0000007B
        0000848484008484840084848400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF0000FF000000FF0000FFFFFF00FFFFFF00FFFFFF0000FF000000FF000000CE
        0000007B0000007B000084848400848484008484840084848400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000FF
        000000FF000000CE0000007B0000007B0000007B000084848400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0000FF000000FF000000CE0000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    inherited btnCancel: TBitBtn
      Left = 492
      Top = 10
      Width = 82
      Caption = '查 询'
      Font.Style = []
    end
    object rgLimit: TRadioGroup
      Left = 16
      Top = 4
      Width = 137
      Height = 32
      Caption = '是否有充值权限'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        '是'
        '否')
      TabOrder = 0
    end
    object edtPwd: TEdit
      Left = 256
      Top = 12
      Width = 97
      Height = 20
      MaxLength = 6
      PasswordChar = '*'
      TabOrder = 3
    end
  end
  object Panel2: TPanel [1]
    Left = 0
    Top = 0
    Width = 681
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object lbl1: TLabel
      Left = 16
      Top = 8
      Width = 240
      Height = 12
      Caption = '说明：该功能只有指定的操作员才拥有此权限'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
  end
  object pnl1: TPanel [2]
    Left = 0
    Top = 25
    Width = 681
    Height = 414
    Align = alClient
    BevelOuter = bvNone
    Color = 16184303
    TabOrder = 1
    object lv1: TRzListView
      Left = 0
      Top = 0
      Width = 681
      Height = 414
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '操作员类型'
          Width = 100
        end
        item
          Caption = '操作员编号'
          Width = 100
        end
        item
          Caption = '操作员名称'
          Width = 200
        end
        item
          Caption = '是否有充值权限'
          Width = 260
        end>
      GridLines = True
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '返回码'
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
        Name = '操作员'
        Caption = '操作员'
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
        Name = '操作员权限'
        Caption = '操作员权限'
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
        Name = '密码'
        Caption = '密码'
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
    Left = 460
    Top = 23
  end
  inherited MainRequest: TWVRequest
    ID = '设置充值操作员'
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
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '操作员权限'
        FieldName = '操作员权限'
      end
      item
        ParamName = '密码'
        FieldName = '密码'
      end>
    Left = 496
    Top = 24
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '查询.操作员代码'
        Caption = '查询.操作员代码'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.状态'
        Caption = '查询.状态'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sstatus3'
      end
      item
        Name = '操作类别'
        Caption = '操作类别'
        FieldType = wftUndefined
        DataType = kdtString
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
        MonitorValueChangedFields = '|查询.操作员代码|'
      end
      item
        MonitorValueChangedFields = 
          '|操作员代码|操作员姓名|电话|手机|地址|邮编|电子邮件|是否限制访问' +
          '站点|操作员状态|功能权限|'
        GroupIndex = 1
      end>
    Left = 456
    Top = 56
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '操作员查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员代码'
        FieldName = '查询.操作员代码'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '状态'
        FieldName = '查询.状态'
      end>
    Left = 496
    Top = 56
  end
end

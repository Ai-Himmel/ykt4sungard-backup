inherited faqhSmartTermConn: TfaqhSmartTermConn
  Width = 700
  Height = 489
  object RzLabel6: TRzLabel [0]
    Left = 120
    Top = 114
    Width = 144
    Height = 12
    AutoSize = False
  end
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    TabOrder = 7
    inherited btnQuery: TBitBtn
      Left = 307
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 394
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 6
    inherited Image1: TImage
      Width = 700
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 664
    Top = 416
    Width = 36
    Height = 43
    Align = alNone
    TabOrder = 5
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Visible = False
    end
  end
  object grp1: TGroupBox [4]
    Left = 184
    Top = 72
    Width = 321
    Height = 105
    TabOrder = 0
    object lbl1: TLabel
      Left = 32
      Top = 24
      Width = 36
      Height = 12
      Alignment = taRightJustify
      Caption = '端口：'
      Transparent = True
    end
    object lbl2: TLabel
      Left = 20
      Top = 48
      Width = 48
      Height = 12
      Alignment = taRightJustify
      Caption = '波特率：'
      Transparent = True
    end
    object cbbComPort: TComboBox
      Left = 73
      Top = 21
      Width = 162
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 0
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6'
        'COM7'
        'COM8'
        'COM9'
        'COM10'
        'COM11'
        'COM12'
        'COM13'
        'COM14')
    end
    object cbbComBand: TComboBox
      Left = 73
      Top = 45
      Width = 162
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 1
      Items.Strings = (
        '9600'
        '19200'
        '38400')
    end
    object rgType: TRadioGroup
      Left = 16
      Top = 64
      Width = 219
      Height = 33
      Caption = '串口类型'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        '消费手持机'
        '认证手持机')
      TabOrder = 2
    end
  end
  object RzGroupBox1: TRzGroupBox [5]
    Left = 184
    Top = 192
    Width = 321
    Caption = '手持机信息'
    ParentColor = True
    TabOrder = 1
    object RzLabel1: TRzLabel
      Left = 39
      Top = 32
      Width = 72
      Height = 12
      Alignment = taRightJustify
      Caption = '设置物理ID：'
    end
    object RzLabel2: TRzLabel
      Left = 51
      Top = 53
      Width = 60
      Height = 12
      Alignment = taRightJustify
      Caption = '程序版本：'
    end
    object RzLabel3: TRzLabel
      Left = 51
      Top = 75
      Width = 60
      Height = 12
      Alignment = taRightJustify
      Caption = '设备机号：'
    end
    object RzLabel4: TRzLabel
      Left = 39
      Top = 115
      Width = 72
      Height = 12
      Alignment = taRightJustify
      Caption = '黑名单版本：'
      Visible = False
    end
    object RzLabel5: TRzLabel
      Left = 27
      Top = 136
      Width = 84
      Height = 12
      Alignment = taRightJustify
      Caption = '黑名单有效期：'
      Visible = False
    end
    object lblPhyId: TRzLabel
      Left = 121
      Top = 32
      Width = 120
      Height = 12
      AutoSize = False
      LightTextStyle = True
    end
    object lblProVer: TRzLabel
      Left = 121
      Top = 53
      Width = 144
      Height = 12
      AutoSize = False
      LightTextStyle = True
    end
    object lblNo: TRzLabel
      Left = 121
      Top = 74
      Width = 144
      Height = 12
      AutoSize = False
      LightTextStyle = True
    end
    object lblBlkVer: TRzLabel
      Left = 121
      Top = 114
      Width = 144
      Height = 12
      AutoSize = False
      Visible = False
      LightTextStyle = True
    end
    object lblBlkExpire: TRzLabel
      Left = 121
      Top = 135
      Width = 144
      Height = 12
      AutoSize = False
      Visible = False
      LightTextStyle = True
    end
  end
  object btnCtrlCOM: TBitBtn [6]
    Left = 216
    Top = 315
    Width = 90
    Height = 25
    Hint = '查询/刷新数据'
    Caption = '打开串口'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = btnCtrlCOMClick
  end
  object btnReadInfo: TBitBtn [7]
    Left = 311
    Top = 315
    Width = 90
    Height = 25
    Hint = '读取手持机信息'
    Caption = '手持机信息'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = btnReadInfoClick
  end
  object btnSetWorkKey: TBitBtn [8]
    Left = 405
    Top = 315
    Width = 100
    Height = 25
    Hint = '设置工作密钥'
    Caption = '设置工作密钥'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = btnSetWorkKeyClick
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
        DataField = '@Return'
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
        DataField = 'vsmess'
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
        DataField = '@Dataset'
      end
      item
        Name = '设备物理ID'
        Caption = '设备物理ID'
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
        MonitorValueChangedFields = 
          '|终端设备ＩＤ|交易流水号|交易卡号|钱包号|交易日期|交易时间|累计' +
          '使用次数|本次消费金额|入卡金额|出卡金额|交易标记|通信版本号|数据' +
          '通信启动原因||'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 20
    Top = 207
  end
  inherited MainRequest: TWVRequest
    ID = '手持机参数设置'
    Bindings = <
      item
        ParamName = '设备物理ID'
        FieldName = '设备物理ID'
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end>
    Left = 56
    Top = 208
  end
  inherited WVDBBinder: TWVDBBinder
    Left = 88
    Top = 208
  end
  inherited DataSource: TDataSource
    Left = 120
    Top = 208
  end
  object wvrGetSysParam: TWVRequest
    WorkView = wvGetSysParam
    ID = '读取工作密钥'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '参数标志'
        FieldName = '参数标识'
      end>
    AfterExec = MainRequestAfterExec
    Left = 56
    Top = 144
  end
  object wvGetSysParam: TWorkView
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
        Name = '参数标识'
        Caption = '参数标识'
        FieldType = wftUndefined
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
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 20
    Top = 143
  end
end

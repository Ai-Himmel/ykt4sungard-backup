inherited faqhfillOperEquBanding: TfaqhfillOperEquBanding
  Width = 681
  Height = 477
  Caption = '充值操作员设备绑定'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 503
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 255
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Width = 161
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 375
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '充值操作员'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'saddr'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备编号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备名称'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户名称'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备注册时间'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '注册操作员'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 34
          Top = 10
          Width = 48
          Height = 12
          Caption = '设备编号'
        end
        object Label2: TLabel
          Left = 218
          Top = 10
          Width = 60
          Height = 12
          Caption = '充值操作员'
        end
        object WVEdit1: TWVEdit
          Left = 87
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.设备编号>'
          WorkView = WorkView
          FieldName = '查询.设备编号'
        end
        object WVComboBox1: TWVComboBox
          Left = 282
          Top = 5
          Width = 169
          Height = 22
          Style = csDropDownList
          Color = clInfoBk
          DropDownCount = 20
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ImeName = '中文 (简体) - 拼音加加'
          ItemHeight = 14
          ParentFont = False
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.充值操作员号'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-51'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 1
        inherited btnOK: TBitBtn
          Left = 501
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 589
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object grp1: TGroupBox
        Left = 128
        Top = 72
        Width = 489
        Height = 329
        Caption = '充值操作员设备绑定'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Label3: TLabel
          Left = 26
          Top = 28
          Width = 70
          Height = 14
          Caption = '充值操作员'
        end
        object cbbFillOper: TWVComboBox
          Left = 104
          Top = 24
          Width = 169
          Height = 22
          Style = csDropDownList
          DropDownCount = 20
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ImeName = '中文 (简体) - 拼音加加'
          ItemHeight = 14
          ParentColor = True
          ParentFont = False
          TabOrder = 0
          WorkView = WorkView
          FieldName = '充值操作员号'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-51'
        end
        object lvEqu: TRzListView
          Left = 16
          Top = 56
          Width = 457
          Height = 257
          Checkboxes = True
          Columns = <
            item
              Caption = '设备编号'
              Width = 100
            end
            item
              Caption = '设备名称'
              Width = 200
            end
            item
              Caption = '设备状态'
              Width = 60
            end
            item
              Caption = '所在区域'
              Width = 77
            end>
          ColumnClick = False
          FlatScrollBars = True
          GridLines = True
          MultiSelect = True
          RowSelect = True
          TabOrder = 1
          ViewStyle = vsReport
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 452
    Top = 55
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
        Name = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '操作类别.增加'
        Caption = '操作类别.增加'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end
      item
        Name = '操作类别.删除'
        Caption = '操作类别.删除'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '操作类别.修改'
        Caption = '操作类别.修改'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '查询.设备编号'
        Caption = '查询.设备编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.充值操作员号'
        Caption = '查询.充值操作员号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '充值操作员号'
        Caption = '充值操作员号'
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
        GroupIndex = 1
        DataField = 'scust_auth'
      end
      item
        Name = '设备编号'
        Caption = '设备编号'
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
        GroupIndex = 1
        DataField = 'saddr'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.设备编号|查询.充值操作员号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|充值操作员号|设备编号|设备名称|商户号|商户名称|设备注册时间|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 392
    Top = 24
  end
  inherited QueryRequest: TWVRequest
    ID = '操作员设备查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备编号'
        FieldName = '查询.设备编号'
      end
      item
        ParamName = '充值操作员号'
        FieldName = '查询.充值操作员号'
      end>
    Left = 520
    Top = 24
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'scust_auth'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end>
    Left = 484
    Top = 55
  end
  inherited AddRequest: TWVRequest
    ID = '充值操作员设备绑定'
    Bindings = <
      item
        ParamName = '充值操作员号'
        FieldName = '充值操作员号'
      end
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end>
    Left = 424
    Top = 24
  end
  inherited DeleteRequest: TWVRequest
    ID = '充值操作员设备绑定删除'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '充值操作员号'
        FieldName = '充值操作员号'
      end
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end>
    Left = 456
    Top = 24
  end
  inherited ChangeRequest: TWVRequest
    ID = '充值操作员设备绑定'
    Bindings = <
      item
        ParamName = '充值操作员号'
        FieldName = '充值操作员号'
      end
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end>
    Left = 488
    Top = 24
  end
  inherited WVDataSource: TWVDataSource
    Left = 516
    Top = 55
  end
  inherited alDatasetActions: TActionList
    Left = 420
    Top = 52
  end
  object MainRequest: TWVRequest
    WorkView = WorkView1
    ID = '设备非关键字查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '三九设备注册号'
        FieldName = '三九设备注册号'
      end
      item
        ParamName = '设备物理ID'
        FieldName = '设备物理ID'
      end
      item
        ParamName = '机号'
        FieldName = '机号'
      end
      item
        ParamName = '机型代码'
        FieldName = '机型代码'
      end
      item
        ParamName = '上级设备物理ID'
        FieldName = '上级设备物理ID'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '设备所在区域'
        FieldName = '设备所在区域'
      end
      item
        ParamName = '负责人员工号'
        FieldName = '负责人员工号'
      end>
    Left = 336
    Top = 32
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
        Name = '设备名称'
        Caption = '设备名称'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '三九设备注册号'
        Caption = '三九设备注册号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd'
      end
      item
        Name = '设备物理ID'
        Caption = '设备物理ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sbank_pwd2'
      end
      item
        Name = '机号'
        Caption = '机号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '机型代码'
        Caption = '机型代码'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '上级设备物理ID'
        Caption = '上级设备物理ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '设备状态'
        Caption = '设备状态'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '设备物理型号'
        Caption = '设备物理型号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '所属子系统'
        Caption = '所属子系统'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '设备所在区域'
        Caption = '设备所在区域'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end
      item
        Name = '负责人员工号'
        Caption = '负责人员工号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sname2'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 292
    Top = 31
  end
end

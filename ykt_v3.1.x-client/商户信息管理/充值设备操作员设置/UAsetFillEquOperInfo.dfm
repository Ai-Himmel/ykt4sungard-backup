inherited faqhsetFillEquOperInfo: TfaqhsetFillEquOperInfo
  Width = 681
  Height = 477
  Caption = '充值设备操作员设置'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 416
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
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
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否启用'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus2'
            PickList.Strings = ()
            Title.Caption = '是否指定设备'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus3'
            PickList.Strings = ()
            Title.Caption = '是否充值商户操作员'
            Width = 110
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '启用日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '停用日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '每日最大充值金额'
            Width = 110
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '最后一次充值日期'
            Width = 110
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '当日累计充值金额'
            Width = 110
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '当日累计充值次数'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '累计充值金额'
            Visible = False
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
        object Label2: TLabel
          Left = 18
          Top = 10
          Width = 60
          Height = 12
          Caption = '充值操作员'
        end
        object Label4: TLabel
          Left = 258
          Top = 10
          Width = 48
          Height = 12
          Caption = '是否启用'
        end
        object WVComboBox2: TWVComboBox
          Left = 311
          Top = 5
          Width = 100
          Height = 22
          Style = csDropDownList
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ImeName = '中文 (简体) - 拼音加加'
          ItemHeight = 14
          ParentFont = False
          TabOrder = 1
          WorkView = WorkView
          FieldName = '查询.状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*2'
        end
        object WVComboBox5: TWVComboBox
          Left = 82
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
        Left = 160
        Top = 72
        Width = 353
        Height = 161
        Caption = '充值操作员信息设置'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Label7: TLabel
          Left = 70
          Top = 28
          Width = 70
          Height = 14
          Caption = '充值操作员'
        end
        object Label11: TLabel
          Left = 28
          Top = 52
          Width = 112
          Height = 14
          Caption = '每日最大充值金额'
        end
        object Label8: TLabel
          Left = 56
          Top = 100
          Width = 84
          Height = 14
          Caption = '是否指定设备'
        end
        object Label1: TLabel
          Left = 14
          Top = 124
          Width = 126
          Height = 14
          Caption = '是否充值商户操作员'
        end
        object Label3: TLabel
          Left = 84
          Top = 76
          Width = 56
          Height = 14
          Caption = '是否启用'
        end
        object edtMoney: TWVDigitalEdit
          Left = 152
          Top = 48
          Width = 100
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 2
          MaxIntLen = 10
          ParentColor = False
          TabOrder = 1
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '每日最大充值金额'
          SynchronizeByValue = True
        end
        object cbbFillOper: TWVComboBox
          Left = 152
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
          ItemsDataEntry = '-30'
        end
        object WVComboBox1: TWVComboBox
          Left = 152
          Top = 94
          Width = 100
          Height = 22
          Style = csDropDownList
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
          TabOrder = 3
          WorkView = WorkView
          FieldName = '是否指定设备'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*2'
        end
        object WVComboBox3: TWVComboBox
          Left = 152
          Top = 118
          Width = 100
          Height = 22
          Style = csDropDownList
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
          TabOrder = 4
          WorkView = WorkView
          FieldName = '是否充值商户操作员'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*2'
        end
        object WVComboBox4: TWVComboBox
          Left = 152
          Top = 70
          Width = 100
          Height = 22
          Style = csDropDownList
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
          TabOrder = 2
          WorkView = WorkView
          FieldName = '状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*2'
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 532
    Top = 55
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        Name = '查询.状态'
        Caption = '查询.状态'
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
        DataField = 'vsvarstr1'
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
        Name = '每日最大充值金额'
        Caption = '每日最大充值金额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'damt0'
      end
      item
        Name = '是否指定设备'
        Caption = '是否指定设备'
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
        DataField = 'sstatus2'
      end
      item
        Name = '是否充值商户操作员'
        Caption = '是否充值商户操作员'
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
        GroupIndex = 1
        DataField = 'sstatus3'
      end
      item
        Name = '状态'
        Caption = '状态'
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
        GroupIndex = 1
        DataField = 'sstatus1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.设备编号|查询.充值操作员号|查询.每日最大充值金额|查询.状态' +
          '|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|商户号|设备编号|充值操作员号|状态|启用日期|停用日期|每日最大充' +
          '值金额|最后一次充值日期|当日累计充值金额|累计充值次数|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 448
    Top = 24
  end
  inherited QueryRequest: TWVRequest
    ID = '设备操作员查询'
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
      end
      item
        ParamName = '状态'
        FieldName = '查询.状态'
      end>
    Left = 584
    Top = 24
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'saddr'
        DataPresentType = 'idobjects'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'scust_auth'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end>
    Left = 492
    Top = 55
  end
  inherited AddRequest: TWVRequest
    ID = '充值设备操作员设置添加'
    Bindings = <
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end
      item
        ParamName = '充值操作员号'
        FieldName = '充值操作员号'
      end
      item
        ParamName = '是否指定设备'
        FieldName = '是否指定设备'
      end
      item
        ParamName = '每日最大充值金额'
        FieldName = '每日最大充值金额'
      end
      item
        ParamName = '是否充值商户操作员'
        FieldName = '是否充值商户操作员'
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end>
    Left = 488
    Top = 24
  end
  inherited DeleteRequest: TWVRequest
    ID = '充值设备操作员设置删除'
    Bindings = <
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end
      item
        ParamName = '充值操作员号'
        FieldName = '充值操作员号'
      end
      item
        ParamName = '是否指定设备'
        FieldName = '是否指定设备'
      end
      item
        ParamName = '是否充值商户操作员'
        FieldName = '是否充值商户操作员'
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end>
    Left = 520
    Top = 24
  end
  inherited ChangeRequest: TWVRequest
    ID = '充值设备操作员设置修改'
    Bindings = <
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end
      item
        ParamName = '充值操作员号'
        FieldName = '充值操作员号'
      end
      item
        ParamName = '是否指定设备'
        FieldName = '是否指定设备'
      end
      item
        ParamName = '每日最大充值金额'
        FieldName = '每日最大充值金额'
      end
      item
        ParamName = '是否充值商户操作员'
        FieldName = '是否充值商户操作员'
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end>
    Left = 552
    Top = 24
  end
  inherited WVDataSource: TWVDataSource
    Left = 612
    Top = 23
  end
  inherited alDatasetActions: TActionList
    Left = 564
    Top = 52
  end
end

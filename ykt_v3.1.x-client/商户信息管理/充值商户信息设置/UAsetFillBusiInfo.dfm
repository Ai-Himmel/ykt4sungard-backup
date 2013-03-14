inherited faqhsetFillBusiInfo: TfaqhsetFillBusiInfo
  Width = 681
  Height = 477
  Caption = '充值商户信息设置'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 402
        Width = 677
        Height = 52
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 416
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
        end
        object StatusBar: TRzStatusBar
          Left = 0
          Top = 31
          Width = 677
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
          TabOrder = 6
          object RzStatusPane1: TRzStatusPane
            Left = 0
            Top = 0
            Width = 677
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
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 73
        Width = 677
        Height = 329
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户号'
            Width = 50
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
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '负责人名称'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '负责人证件类型'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '负责人证件号码'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '提成比率(%)'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Caption = '商户状态'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '开户日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '销户日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '帐户余额'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '累计存款次数'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '累计存款金额'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '累计提成金额'
            Width = 60
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 55
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 46
          Top = 10
          Width = 48
          Height = 12
          Caption = '商户名称'
        end
        object Label2: TLabel
          Left = 234
          Top = 10
          Width = 60
          Height = 12
          Caption = '负责人名称'
        end
        object Label3: TLabel
          Left = 410
          Top = 10
          Width = 84
          Height = 12
          Caption = '负责人证件类型'
        end
        object Label4: TLabel
          Left = 10
          Top = 34
          Width = 84
          Height = 12
          Caption = '负责人证件号码'
        end
        object Label5: TLabel
          Left = 210
          Top = 34
          Width = 84
          Height = 12
          Caption = '负责人提成比率'
        end
        object Label12: TLabel
          Left = 446
          Top = 34
          Width = 48
          Height = 12
          Caption = '商户状态'
        end
        object WVEdit1: TWVEdit
          Left = 100
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.商户名称>'
          WorkView = WorkView
          FieldName = '查询.商户名称'
        end
        object WVEdit2: TWVEdit
          Left = 300
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.商户负责人名称>'
          WorkView = WorkView
          FieldName = '查询.商户负责人名称'
        end
        object WVEdit4: TWVEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.商户证件号码>'
          WorkView = WorkView
          FieldName = '查询.商户证件号码'
        end
        object WVDigitalEdit5: TWVDigitalEdit
          Left = 300
          Top = 30
          Width = 100
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 2
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 3
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '查询.商户提成比率'
          SynchronizeByValue = True
        end
        object WVComboBox2: TWVComboBox
          Left = 499
          Top = 6
          Width = 105
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '紫光拼音输入法'
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '查询.商户证件类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*87'
        end
        object cbbStatus: TWVComboBox
          Left = 499
          Top = 30
          Width = 105
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '紫光拼音输入法'
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '查询.商户状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*15'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object lblBusiNo: TLabel [0]
        Left = 70
        Top = 44
        Width = 36
        Height = 12
        Caption = '商户号'
        Visible = False
      end
      object Label8: TLabel [1]
        Left = 58
        Top = 84
        Width = 48
        Height = 12
        Caption = '商户名称'
      end
      object Label9: TLabel [2]
        Left = 46
        Top = 124
        Width = 60
        Height = 12
        Caption = '负责人姓名'
      end
      object Label10: TLabel [3]
        Left = 22
        Top = 164
        Width = 84
        Height = 12
        Caption = '负责人证件类型'
      end
      object Label11: TLabel [4]
        Left = 22
        Top = 204
        Width = 84
        Height = 12
        Caption = '负责人证件号码'
      end
      object Label6: TLabel [5]
        Left = 35
        Top = 244
        Width = 72
        Height = 12
        Caption = '商户提成比率'
      end
      object Label7: TLabel [6]
        Left = 320
        Top = 244
        Width = 6
        Height = 12
        Caption = '%'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 501
        end
        inherited btnCancel: TBitBtn
          Left = 589
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtBusiNo: TWVDigitalEdit
        Left = 118
        Top = 40
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '商户号'
        SynchronizeByValue = True
      end
      object WVEdit8: TWVEdit
        Left = 118
        Top = 80
        Width = 213
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<商户名称>'
        WorkView = WorkView
        FieldName = '商户名称'
        SynchronizeWhenExit = True
      end
      object WVEdit9: TWVEdit
        Left = 118
        Top = 120
        Width = 213
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<商户负责人名称>'
        WorkView = WorkView
        FieldName = '商户负责人名称'
        SynchronizeWhenExit = True
      end
      object WVEdit11: TWVEdit
        Left = 118
        Top = 200
        Width = 213
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 3
        Text = '<商户证件号码>'
        WorkView = WorkView
        FieldName = '商户证件号码'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 118
        Top = 158
        Width = 213
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '紫光拼音输入法'
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '商户证件类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*87'
      end
      object WVDigitalEdit1: TWVDigitalEdit
        Left = 118
        Top = 240
        Width = 195
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 4
        ParentColor = False
        TabOrder = 6
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '商户提成比率'
        SynchronizeByValue = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 236
    Top = 199
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
        Name = '查询.商户号'
        Caption = '查询.商户号'
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
        Name = '查询.商户名称'
        Caption = '查询.商户名称'
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
        Name = '查询.商户负责人名称'
        Caption = '查询.商户负责人名称'
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
        Name = '查询.商户证件类型'
        Caption = '查询.商户证件类型'
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
        Name = '查询.商户证件号码'
        Caption = '查询.商户证件号码'
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
        Name = '查询.商户提成比率'
        Caption = '查询.商户提成比率'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        Name = '查询.商户状态'
        Caption = '查询.商户状态'
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
        Name = '商户号'
        Caption = '商户号'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '商户名称'
        Caption = '商户名称'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '商户负责人名称'
        Caption = '商户负责人名称'
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
        DataField = 'sall_name'
      end
      item
        Name = '商户证件类型'
        Caption = '商户证件类型'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '商户证件号码'
        Caption = '商户证件号码'
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
        DataField = 'snote'
      end
      item
        Name = '商户提成比率'
        Caption = '商户提成比率'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.商户名称|查询.商户负责人名称|查询.商户证件类型|查询.商户证' +
          '件号码|查询.商户提成比率|查询.操作员号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|商户号|商户名称|商户负责人名称|商户证件类型|商户证件号码|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 152
    Top = 160
  end
  inherited QueryRequest: TWVRequest
    ID = '充值商户查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户名称'
        FieldName = '查询.商户名称'
      end
      item
        ParamName = '商户负责人名称'
        FieldName = '查询.商户负责人名称'
      end
      item
        ParamName = '商户证件类型'
        FieldName = '查询.商户证件类型'
      end
      item
        ParamName = '商户证件号码'
        FieldName = '查询.商户证件号码'
      end
      item
        ParamName = '商户提成比率'
        FieldName = '查询.商户提成比率'
      end
      item
        ParamName = '商户号'
        FieldName = '查询.商户号'
      end
      item
        ParamName = '商户状态'
        FieldName = '查询.商户状态'
      end>
    Left = 312
    Top = 160
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol1'
        WVFieldName = '证件类型'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'sstatus1'
        WVFieldName = '商户状态'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end>
    Left = 196
    Top = 199
  end
  inherited AddRequest: TWVRequest
    ID = '充值商户信息设置'
    Bindings = <
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '商户负责人名称'
        FieldName = '商户负责人名称'
      end
      item
        ParamName = '商户证件类型'
        FieldName = '商户证件类型'
      end
      item
        ParamName = '商户证件号码'
        FieldName = '商户证件号码'
      end
      item
        ParamName = '商户提成比率'
        FieldName = '商户提成比率'
      end>
    Left = 192
    Top = 160
  end
  inherited DeleteRequest: TWVRequest
    ID = '充值商户信息设置删除'
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
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '商户负责人名称'
        FieldName = '商户负责人名称'
      end
      item
        ParamName = '商户证件类型'
        FieldName = '商户证件类型'
      end
      item
        ParamName = '商户证件号码'
        FieldName = '商户证件号码'
      end
      item
        ParamName = '商户提成比率'
        FieldName = '商户提成比率'
      end>
    Left = 232
    Top = 160
  end
  inherited ChangeRequest: TWVRequest
    ID = '充值商户信息设置修改'
    Bindings = <
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '商户负责人名称'
        FieldName = '商户负责人名称'
      end
      item
        ParamName = '商户证件类型'
        FieldName = '商户证件类型'
      end
      item
        ParamName = '商户证件号码'
        FieldName = '商户证件号码'
      end
      item
        ParamName = '商户提成比率'
        FieldName = '商户提成比率'
      end>
    Left = 272
    Top = 160
  end
  inherited WVDataSource: TWVDataSource
    Left = 316
    Top = 199
  end
  inherited alDatasetActions: TActionList
    Left = 276
    Top = 204
  end
end

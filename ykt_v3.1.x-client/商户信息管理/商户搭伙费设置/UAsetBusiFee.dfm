inherited faqhsetBusiFee: TfaqhsetBusiFee
  Width = 775
  Height = 512
  Caption = '浮动费率设置'
  inherited pcPages: TRzPageControl
    Width = 775
    Height = 512
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 459
        Width = 771
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 509
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 597
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 424
        end
        inherited btnDelete: TBitBtn
          Left = 682
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 182
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 771
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 771
        Height = 410
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'Lvol3'
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
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '收费类别'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'drate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户费率(%)'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'drate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '学校费率(%)'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '操作员'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '最后修改时间'
            Width = 120
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 771
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label2: TLabel
          Left = 26
          Top = 10
          Width = 48
          Height = 12
          Caption = '商户编号'
        end
        object Label4: TLabel
          Left = 234
          Top = 10
          Width = 48
          Height = 12
          Caption = '收费类别'
        end
        object edtQBid: TWVEdit
          Left = 80
          Top = 7
          Width = 115
          Height = 20
          BiDiMode = bdRightToLeft
          Color = clWhite
          MaxLength = 9
          ParentBiDiMode = False
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.编号>'
          WorkView = WorkView
          FieldName = '查询.编号'
          SynchronizeWhenExit = True
        end
        object WVComboBox1: TWVComboBox
          Left = 292
          Top = 6
          Width = 150
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '紫光拼音输入法'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.收费类别'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-43'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label7: TLabel [0]
        Left = 42
        Top = 84
        Width = 54
        Height = 12
        Caption = '商户编号*'
      end
      object Label8: TLabel [1]
        Left = 42
        Top = 148
        Width = 54
        Height = 12
        Caption = '收费类别*'
      end
      object Label9: TLabel [2]
        Left = 42
        Top = 180
        Width = 54
        Height = 12
        Caption = '商户费率*'
      end
      object Label1: TLabel [3]
        Left = 48
        Top = 116
        Width = 48
        Height = 12
        Caption = '商户名称'
      end
      object btnSelect: TSpeedButton [4]
        Left = 226
        Top = 78
        Width = 23
        Height = 22
        Caption = '>>>'
        Flat = True
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        OnClick = btnSelectClick
      end
      object lbl1: TLabel [5]
        Left = 40
        Top = 56
        Width = 222
        Height = 12
        Caption = '说明：如果商户编号为0则为通用费率设置'
      end
      object Label3: TLabel [6]
        Left = 242
        Top = 180
        Width = 15
        Height = 12
        AutoSize = False
        Caption = '%'
      end
      object Label5: TLabel [7]
        Left = 42
        Top = 212
        Width = 54
        Height = 12
        Caption = '学校费率*'
      end
      object Label6: TLabel [8]
        Left = 242
        Top = 212
        Width = 15
        Height = 12
        AutoSize = False
        Caption = '%'
      end
      inherited UIPanel2: TUIPanel
        Top = 453
        Width = 771
        TabOrder = 5
        inherited btnOK: TBitBtn
          Left = 595
        end
        inherited btnCancel: TBitBtn
          Left = 683
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtBusiRate: TWVDigitalEdit
        Left = 100
        Top = 176
        Width = 133
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 4
        ParentColor = False
        TabOrder = 4
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '费率'
        SynchronizeByValue = True
      end
      object edtBusiName: TWVEdit
        Left = 100
        Top = 112
        Width = 149
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 2
        Text = '<商户名称>'
        WorkView = WorkView
        FieldName = '商户名称'
        SynchronizeWhenExit = True
      end
      object pnl1: TPanel
        Left = 256
        Top = 80
        Width = 489
        Height = 369
        Color = 16119543
        TabOrder = 1
        object pnl2: TPanel
          Left = 1
          Top = 1
          Width = 487
          Height = 9
          Align = alTop
          Color = 16119543
          TabOrder = 0
        end
        object pnl3: TPanel
          Left = 1
          Top = 327
          Width = 487
          Height = 41
          Align = alBottom
          Color = 16119543
          TabOrder = 2
          object btnQry: TBitBtn
            Left = 228
            Top = 8
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '&Q 查询'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = btnQryClick
          end
          object btnSel: TBitBtn
            Left = 316
            Top = 8
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '&S 选择'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            OnClick = btnSelClick
          end
          object btnCommon: TBitBtn
            Left = 20
            Top = 8
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '通用商户'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = btnCommonClick
          end
          object btnCnl: TBitBtn
            Left = 404
            Top = 8
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '取 消'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            OnClick = btnCnlClick
          end
        end
        object RzDBGrid1: TRzDBGrid
          Left = 1
          Top = 10
          Width = 487
          Height = 317
          Align = alClient
          DataSource = DataSource1
          FixedColor = 15458000
          ImeName = '拼音加加集合版'
          TabOrder = 1
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -12
          TitleFont.Name = '宋体'
          TitleFont.Style = []
          OnDrawColumnCell = RzDBGrid1DrawColumnCell
          OnDblClick = RzDBGrid1DblClick
          OnKeyDown = GridKeyDown
          FrameColor = 12164479
          FrameStyle = fsGroove
          FrameVisible = True
          FixedLineColor = 12164479
          LineColor = clBackground
          Columns = <
            item
              Expanded = False
              FieldName = 'sbranch_code0'
              Title.Alignment = taCenter
              Title.Caption = '校区'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'lvol3'
              Title.Alignment = taCenter
              Title.Caption = '商户号'
              Width = 50
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sall_name'
              Title.Alignment = taCenter
              Title.Caption = '商户名称'
              Width = 110
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'lvol7'
              Title.Alignment = taCenter
              Title.Caption = '商户类别'
              Width = 50
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'smain_flag2'
              Title.Alignment = taCenter
              Title.Caption = '末级商户'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'smain_flag'
              Title.Alignment = taCenter
              Title.Caption = '独立核算'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'scust_type'
              Title.Alignment = taCenter
              Title.Caption = '收搭伙费'
              Width = 60
              Visible = True
            end>
        end
      end
      object edtBusiId: TWVEdit
        Left = 100
        Top = 80
        Width = 127
        Height = 20
        MaxLength = 22
        ParentColor = True
        ReadOnly = True
        TabOrder = 0
        Text = '<商户号>'
        WorkView = WorkView
        FieldName = '商户号'
        SynchronizeWhenExit = True
      end
      object cbbFeeType: TWVComboBox
        Left = 100
        Top = 143
        Width = 150
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '紫光拼音输入法'
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '收费类别'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
      object edtSRate: TWVDigitalEdit
        Left = 100
        Top = 208
        Width = 133
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
        FieldName = '学校费率'
        SynchronizeByValue = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 324
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
        Name = '查询.编号'
        Caption = '查询.编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.Min = -1
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.收费类别'
        Caption = '查询.收费类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '商户名称'
        Caption = '商户名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '商户号'
        Caption = '商户号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '费率'
        Caption = '费率'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 2
        Checker.Max = 100
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'drate0'
      end
      item
        Name = '学校费率'
        Caption = '学校费率'
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
        DataField = 'drate1'
      end
      item
        Name = '操作标志'
        Caption = '操作标志'
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
        MonitorValueChangedFields = '|查询.营业额|查询.折扣比例|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|标志|编号|营业额|折扣比例|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 232
    Top = 248
  end
  inherited QueryRequest: TWVRequest
    ID = '商户搭伙费查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '商户号'
        FieldName = '查询.编号'
      end
      item
        ParamName = '收费类别'
        FieldName = '查询.收费类别'
      end>
    Left = 408
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 284
  end
  inherited AddRequest: TWVRequest
    ID = '商户搭伙费设置'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '费率'
        FieldName = '费率'
      end
      item
        ParamName = '学校费率'
        FieldName = '学校费率'
      end>
    Left = 280
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '商户搭伙费设置'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '费率'
        FieldName = '费率'
      end
      item
        ParamName = '学校费率'
        FieldName = '学校费率'
      end>
    Left = 328
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '商户搭伙费设置'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '费率'
        FieldName = '费率'
      end
      item
        ParamName = '学校费率'
        FieldName = '学校费率'
      end>
    Left = 368
    Top = 248
  end
  inherited WVDataSource: TWVDataSource
    Left = 404
  end
  inherited alDatasetActions: TActionList
    Left = 364
    Top = 284
  end
  object WVDBBinder: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView1
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '14'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end>
    HideUnbindingFields = False
    Left = 544
    Top = 360
  end
  object DataSource1: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 576
    Top = 360
  end
  object MainRequest: TWVRequest
    WorkView = WorkView1
    ID = '商户信息非主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
      end
      item
        ParamName = '父商户标识'
        FieldName = '父商户标识'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '商户类别'
        FieldName = '商户类别'
      end
      item
        ParamName = '是否为独立核算'
        FieldName = '是否为独立核算'
      end
      item
        ParamName = '是否为叶节点'
        FieldName = '是否为叶节点'
      end
      item
        ParamName = '收搭伙费'
        FieldName = '收搭伙费'
      end>
    Left = 512
    Top = 360
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
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '商户标识'
        Caption = '商户标识'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '父商户标识'
        Caption = '父商户标识'
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
        Name = '商户名称'
        Caption = '商户名称'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scard1'
      end
      item
        Name = '商户类别'
        Caption = '商户类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol7'
      end
      item
        Name = '是否为独立核算'
        Caption = '是否为独立核算'
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
        Name = '是否为叶节点'
        Caption = '是否为叶节点'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '收搭伙费'
        Caption = '收搭伙费'
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
        MonitorValueChangedFields = 
          '|商户标识|客户号|父商户标识|商户名称|商户类别|是否为叶节点|商户' +
          '状态|负责人员工号|负责人姓名|负责人性别|负责人民族代码|负责人身' +
          '份证号|联系电话|联系地址|是否收取管理费|收取消费管理费比例|商户' +
          '管理费计算方式|商户税费计算方式|注册时间|备注|'
      end>
    Left = 476
    Top = 359
  end
end

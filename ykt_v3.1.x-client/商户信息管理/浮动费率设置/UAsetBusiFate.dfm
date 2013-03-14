inherited faqhsetBusiFate: TfaqhsetBusiFate
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
          Left = 597
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 293
          Enabled = False
          TabOrder = 0
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 512
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 682
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 382
          TabOrder = 1
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
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '营业额'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '折扣比例(%)'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '备注'
            Width = 350
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
        object Label3: TLabel
          Left = 206
          Top = 10
          Width = 36
          Height = 12
          Caption = '营业额'
        end
        object Label4: TLabel
          Left = 386
          Top = 10
          Width = 66
          Height = 12
          Caption = '折扣比例(%)'
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
          TabOrder = 2
          Text = '<查询.编号>'
          WorkView = WorkView
          FieldName = '查询.编号'
          SynchronizeWhenExit = True
        end
        object edtMoney: TWVEdit
          Left = 248
          Top = 6
          Width = 115
          Height = 20
          BiDiMode = bdRightToLeft
          Color = clWhite
          MaxLength = 9
          ParentBiDiMode = False
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.营业额>'
          WorkView = WorkView
          FieldName = '查询.营业额'
          SynchronizeWhenExit = True
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 460
          Top = 6
          Width = 107
          Height = 20
          AllowPoint = True
          UserSeprator = True
          Precision = 2
          MaxIntLen = 10
          ParentColor = False
          TabOrder = 1
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '查询.折扣比例'
          SynchronizeByValue = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object lblMemo: TLabel [0]
        Left = 66
        Top = 212
        Width = 24
        Height = 12
        Caption = '备注'
      end
      object Label7: TLabel [1]
        Left = 42
        Top = 84
        Width = 48
        Height = 12
        Caption = '商户编号'
      end
      object Label8: TLabel [2]
        Left = 54
        Top = 148
        Width = 36
        Height = 12
        Caption = '营业额'
      end
      object Label9: TLabel [3]
        Left = 42
        Top = 180
        Width = 48
        Height = 12
        Caption = '折扣比例'
      end
      object Label1: TLabel [4]
        Left = 42
        Top = 116
        Width = 48
        Height = 12
        Caption = '商户名称'
      end
      object btnSelect: TSpeedButton [5]
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
      object lbl1: TLabel [6]
        Left = 40
        Top = 56
        Width = 222
        Height = 12
        Caption = '说明：如果商户编号为0则为通用费率设置'
      end
      object Label10: TLabel [7]
        Left = 250
        Top = 180
        Width = 6
        Height = 12
        Caption = '%'
      end
      inherited UIPanel2: TUIPanel
        Top = 453
        Width = 771
        TabOrder = 6
        inherited btnOK: TBitBtn
          Left = 595
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 683
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtMemo: TWVEdit
        Left = 99
        Top = 208
        Width = 390
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 5
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit8: TWVDigitalEdit
        Left = 100
        Top = 144
        Width = 149
        Height = 20
        AllowPoint = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '营业额'
        SynchronizeByValue = True
      end
      object edtBusiRate: TWVDigitalEdit
        Left = 100
        Top = 176
        Width = 149
        Height = 20
        AllowPoint = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 4
        TabStop = True
        Text = '0'
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
        Text = '<编号>'
        WorkView = WorkView
        FieldName = '编号'
        SynchronizeWhenExit = True
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
        Name = '查询.营业额'
        Caption = '查询.营业额'
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
        Name = '查询.折扣比例'
        Caption = '查询.折扣比例'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '标志'
        Caption = '标志'
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
        DataField = 'Sstatus0'
      end
      item
        Name = '编号'
        Caption = '编号'
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
        DataField = 'lserial0'
      end
      item
        Name = '营业额'
        Caption = '营业额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '折扣比例'
        Caption = '折扣比例'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt1'
      end
      item
        Name = '备注'
        Caption = '备注'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'ssectypes'
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
    ID = '浮动费率查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '编号'
        FieldName = '查询.编号'
      end
      item
        ParamName = '营业额'
        FieldName = '查询.营业额'
      end
      item
        ParamName = '折扣比例'
        FieldName = '查询.折扣比例'
      end>
    Left = 408
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 284
  end
  inherited AddRequest: TWVRequest
    ID = '浮动费率设置'
    Bindings = <
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '编号'
        FieldName = '编号'
      end
      item
        ParamName = '营业额'
        FieldName = '营业额'
      end
      item
        ParamName = '折扣比例'
        FieldName = '折扣比例'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 280
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '浮动费率设置'
    Bindings = <
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '编号'
        FieldName = '编号'
      end
      item
        ParamName = '营业额'
        FieldName = '营业额'
      end
      item
        ParamName = '折扣比例'
        FieldName = '折扣比例'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 328
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '浮动费率设置'
    Bindings = <
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '编号'
        FieldName = '编号'
      end
      item
        ParamName = '营业额'
        FieldName = '营业额'
      end
      item
        ParamName = '折扣比例'
        FieldName = '折扣比例'
      end
      item
        ParamName = '备注'
        FieldName = '备注.修改'
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
        FieldName = 'smain_flag2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '91'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
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
        ParamName = '费率类型'
        FieldName = '佣金类型'
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
        Name = '佣金类型'
        Caption = '佣金类型'
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

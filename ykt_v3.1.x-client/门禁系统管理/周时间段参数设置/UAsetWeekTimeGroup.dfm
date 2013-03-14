inherited faqhsetWeekTimeGroup: TfaqhsetWeekTimeGroup
  Width = 754
  Height = 566
  Caption = '周时间段参数设置'
  inherited pcPages: TRzPageControl
    Width = 754
    Height = 566
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 507
        Width = 750
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 489
          Top = 6
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 575
          Top = 6
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 403
          Top = 6
        end
        inherited btnDelete: TBitBtn
          Left = 661
          Top = 6
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
          Top = 6
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 11
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 750
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 750
        Height = 474
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '周时间段组编号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Caption = '周时间段组名'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '周一'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Caption = '周二'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Caption = '周三'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Caption = '周四'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = '周五'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol6'
            PickList.Strings = ()
            Title.Caption = '周六'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol7'
            PickList.Strings = ()
            Title.Caption = '周日'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Caption = '更新时间'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol8'
            PickList.Strings = ()
            Title.Caption = '标志'
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 750
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 10
          Top = 10
          Width = 84
          Height = 12
          Caption = '周时间段组编号'
        end
        object Label2: TLabel
          Left = 210
          Top = 10
          Width = 84
          Height = 12
          Caption = '周时间段组名称'
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 92
          Top = 6
          Width = 100
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 0
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '时间段组编号'
          SynchronizeByValue = True
        end
        object WVEdit2: TWVEdit
          Left = 300
          Top = 6
          Width = 157
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.时间段组名称>'
          WorkView = WorkView
          FieldName = '查询.时间段组名称'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label11: TLabel [0]
        Left = 118
        Top = 52
        Width = 84
        Height = 12
        Caption = '周时间段组编号'
      end
      object Label12: TLabel [1]
        Left = 130
        Top = 84
        Width = 72
        Height = 12
        Caption = '周时间段组名'
      end
      object Label14: TLabel [2]
        Left = 142
        Top = 116
        Width = 60
        Height = 12
        Caption = '周一组编号'
      end
      object Label15: TLabel [3]
        Left = 142
        Top = 156
        Width = 60
        Height = 12
        Caption = '周二组编号'
      end
      object Label16: TLabel [4]
        Left = 142
        Top = 196
        Width = 60
        Height = 12
        Caption = '周三组编号'
      end
      object Label17: TLabel [5]
        Left = 142
        Top = 236
        Width = 60
        Height = 12
        Caption = '周四组编号'
      end
      object Label18: TLabel [6]
        Left = 142
        Top = 276
        Width = 60
        Height = 12
        Caption = '周五组编号'
      end
      object Label19: TLabel [7]
        Left = 142
        Top = 316
        Width = 60
        Height = 12
        Caption = '周六组编号'
      end
      object Label20: TLabel [8]
        Left = 142
        Top = 356
        Width = 60
        Height = 12
        Caption = '周日组编号'
      end
      object btn1: TSpeedButton [9]
        Tag = 1
        Left = 334
        Top = 111
        Width = 21
        Height = 21
        Caption = '>>>'
        Flat = True
        OnClick = btn1Click
      end
      object SpeedButton1: TSpeedButton [10]
        Tag = 2
        Left = 334
        Top = 151
        Width = 21
        Height = 21
        Caption = '>>>'
        Flat = True
        OnClick = SpeedButton1Click
      end
      object SpeedButton2: TSpeedButton [11]
        Tag = 3
        Left = 334
        Top = 191
        Width = 21
        Height = 21
        Caption = '>>>'
        Flat = True
        OnClick = SpeedButton2Click
      end
      object SpeedButton3: TSpeedButton [12]
        Tag = 4
        Left = 334
        Top = 231
        Width = 21
        Height = 21
        Caption = '>>>'
        Flat = True
        OnClick = SpeedButton3Click
      end
      object SpeedButton4: TSpeedButton [13]
        Tag = 5
        Left = 334
        Top = 271
        Width = 21
        Height = 21
        Caption = '>>>'
        Flat = True
        OnClick = SpeedButton4Click
      end
      object SpeedButton5: TSpeedButton [14]
        Tag = 6
        Left = 334
        Top = 311
        Width = 21
        Height = 21
        Caption = '>>>'
        Flat = True
        OnClick = SpeedButton5Click
      end
      object SpeedButton6: TSpeedButton [15]
        Tag = 7
        Left = 334
        Top = 351
        Width = 21
        Height = 21
        Caption = '>>>'
        Flat = True
        OnClick = SpeedButton6Click
      end
      object lbl1: TLabel [16]
        Tag = 1
        Left = 213
        Top = 136
        Width = 60
        Height = 12
        Caption = '周一组编号'
      end
      object lbl2: TLabel [17]
        Tag = 2
        Left = 213
        Top = 176
        Width = 60
        Height = 12
        Caption = '周一组编号'
      end
      object lbl3: TLabel [18]
        Tag = 3
        Left = 213
        Top = 216
        Width = 60
        Height = 12
        Caption = '周一组编号'
      end
      object lbl4: TLabel [19]
        Tag = 4
        Left = 213
        Top = 256
        Width = 60
        Height = 12
        Caption = '周一组编号'
      end
      object lbl5: TLabel [20]
        Tag = 5
        Left = 213
        Top = 296
        Width = 60
        Height = 12
        Caption = '周一组编号'
      end
      object lbl6: TLabel [21]
        Tag = 6
        Left = 213
        Top = 336
        Width = 60
        Height = 12
        Caption = '周一组编号'
      end
      object lbl7: TLabel [22]
        Tag = 7
        Left = 213
        Top = 376
        Width = 60
        Height = 12
        Caption = '周一组编号'
      end
      inherited UIPanel2: TUIPanel
        Top = 507
        Width = 750
        TabOrder = 10
        inherited btnOK: TBitBtn
          Left = 574
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 662
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVDigitalEdit11: TWVDigitalEdit
        Left = 212
        Top = 48
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        ReadOnly = True
        Precision = 0
        MaxIntLen = 10
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '时间段组编号'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 212
        Top = 80
        Width = 141
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<时间段组名>'
        WorkView = WorkView
        FieldName = '时间段组名'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Tag = 1
        Left = 212
        Top = 112
        Width = 121
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 3
        Text = '<周一组编号>'
        OnChange = WVEdit1Change
        WorkView = WorkView
        FieldName = '周一组编号'
        SynchronizeWhenExit = True
      end
      object WVEdit3: TWVEdit
        Tag = 2
        Left = 212
        Top = 152
        Width = 121
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 4
        Text = '<周二组编号>'
        OnChange = WVEdit3Change
        WorkView = WorkView
        FieldName = '周二组编号'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Tag = 3
        Left = 212
        Top = 192
        Width = 121
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 5
        Text = '<周三组编号>'
        OnChange = WVEdit4Change
        WorkView = WorkView
        FieldName = '周三组编号'
        SynchronizeWhenExit = True
      end
      object WVEdit5: TWVEdit
        Tag = 4
        Left = 212
        Top = 232
        Width = 121
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 6
        Text = '<周四组编号>'
        OnChange = WVEdit5Change
        WorkView = WorkView
        FieldName = '周四组编号'
        SynchronizeWhenExit = True
      end
      object WVEdit6: TWVEdit
        Tag = 5
        Left = 212
        Top = 272
        Width = 121
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 7
        Text = '<周五组编号>'
        OnChange = WVEdit6Change
        WorkView = WorkView
        FieldName = '周五组编号'
        SynchronizeWhenExit = True
      end
      object WVEdit7: TWVEdit
        Tag = 6
        Left = 212
        Top = 312
        Width = 121
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<周六组编号>'
        OnChange = WVEdit7Change
        WorkView = WorkView
        FieldName = '周六组编号'
        SynchronizeWhenExit = True
      end
      object WVEdit8: TWVEdit
        Tag = 7
        Left = 212
        Top = 352
        Width = 121
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 9
        Text = '<周日组编号>'
        OnChange = WVEdit8Change
        WorkView = WorkView
        FieldName = '周日组编号'
        SynchronizeWhenExit = True
      end
      object pnlQuery: TPanel
        Left = 356
        Top = 111
        Width = 381
        Height = 385
        Color = 15458000
        TabOrder = 2
        Visible = False
        object Label10: TLabel
          Left = 6
          Top = 18
          Width = 24
          Height = 12
          Caption = '标识'
        end
        object Label13: TLabel
          Left = 89
          Top = 18
          Width = 72
          Height = 12
          Caption = '时间段组名称'
        end
        object WVEdit9: TWVEdit
          Left = 36
          Top = 14
          Width = 45
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.标识>'
          WorkView = WorkView2
          FieldName = '查询.标识'
        end
        object WVEdit10: TWVEdit
          Left = 164
          Top = 14
          Width = 133
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.时间段名称>'
          WorkView = WorkView2
          FieldName = '查询.时间段名称'
        end
        object pnl1: TPanel
          Left = 1
          Top = 352
          Width = 379
          Height = 32
          Align = alBottom
          BevelOuter = bvNone
          Color = 15458000
          TabOrder = 3
          object btnTimeQuery: TBitBtn
            Left = 124
            Top = 4
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '查　询'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = btnTimeQueryClick
          end
          object btnSelect: TBitBtn
            Left = 212
            Top = 4
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '选　择'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            OnClick = btnSelectClick
          end
          object btnCancle: TBitBtn
            Left = 300
            Top = 4
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '取　消'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            OnClick = btnCancleClick
          end
          object btnSet0: TBitBtn
            Left = 8
            Top = 4
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '置  零'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = btnSet0Click
          end
        end
        object dbgrd1: TDBGrid
          Left = 1
          Top = 40
          Width = 379
          Height = 312
          Align = alBottom
          DataSource = DataSource1
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ReadOnly = True
          TabOrder = 2
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -12
          TitleFont.Name = '宋体'
          TitleFont.Style = []
          OnDblClick = dbgrd1DblClick
          Columns = <
            item
              Expanded = False
              FieldName = 'lcert_code'
              Title.Caption = '标识'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail'
              Title.Caption = '时间段组名称'
              Width = 200
              Visible = True
            end>
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 76
    Top = 327
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
        Name = '查询.时间段组编号'
        Caption = '查询.时间段组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.时间段组名称'
        Caption = '查询.时间段组名称'
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
        Name = '查询.周一组编号'
        Caption = '查询.周一组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.周二组编号'
        Caption = '查询.周二组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.周三组编号'
        Caption = '查询.周三组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.周四组编号'
        Caption = '查询.周四组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.周五组编号'
        Caption = '查询.周五组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.周六组编号'
        Caption = '查询.周六组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.周日组编号'
        Caption = '查询.周日组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '时间段组编号'
        Caption = '时间段组编号'
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
        Name = '时间段组名'
        Caption = '时间段组名'
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
        DataField = 'semail'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
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
        Name = '周一组编号'
        Caption = '周一组编号'
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
        Name = '周二组编号'
        Caption = '周二组编号'
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
        DataField = 'lvol2'
      end
      item
        Name = '周三组编号'
        Caption = '周三组编号'
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
        DataField = 'lvol3'
      end
      item
        Name = '周四组编号'
        Caption = '周四组编号'
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
        DataField = 'lvol4'
      end
      item
        Name = '周五组编号'
        Caption = '周五组编号'
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
        DataField = 'lvol5'
      end
      item
        Name = '周六组编号'
        Caption = '周六组编号'
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
        DataField = 'lvol6'
      end
      item
        Name = '周日组编号'
        Caption = '周日组编号'
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
        DataField = 'lvol7'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.时间段组编号|查询.时间段组名称|查询.周一组编号|查询.周二组' +
          '编号|查询.周三组编号|查询.周四组编号|查询.周五组编号|查询.周六组' +
          '编号|查询.周日组编号|查询.标志|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|时间段组编号|时间段组名|标志|周一组编号|周二组编号|周三组编号|' +
          '周四组编号|周五组编号|周六组编号|周日组编号|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 16
    Top = 296
  end
  inherited QueryRequest: TWVRequest
    ID = '周时间段查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '时间段组编号'
        FieldName = '查询.时间段组编号'
      end
      item
        ParamName = '时间段组名称'
        FieldName = '查询.时间段组名称'
      end
      item
        ParamName = '周一组编号'
        FieldName = '查询.周一组编号'
      end
      item
        ParamName = '周二组编号'
        FieldName = '查询.周二组编号'
      end
      item
        ParamName = '周三组编号'
        FieldName = '查询.周三组编号'
      end
      item
        ParamName = '周四组编号'
        FieldName = '查询.周四组编号'
      end
      item
        ParamName = '周五组编号'
        FieldName = '查询.周五组编号'
      end
      item
        ParamName = '周六组编号'
        FieldName = '查询.周六组编号'
      end
      item
        ParamName = '周日组编号'
        FieldName = '查询.周日组编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 152
    Top = 296
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-14'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-14'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'idobjects'
        DataPresentParam = '-14'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-14'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'idobjects'
        DataPresentParam = '-14'
      end
      item
        FieldName = 'lvol6'
        DataPresentType = 'idobjects'
        DataPresentParam = '-14'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '-14'
      end>
    Left = 44
    Top = 327
  end
  inherited AddRequest: TWVRequest
    ID = '周时间段参数设置'
    Bindings = <
      item
        ParamName = '时间段组编号'
        FieldName = '时间段组编号'
      end
      item
        ParamName = '时间段组名'
        FieldName = '时间段组名'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '周一组编号'
        FieldName = '周一组编号'
      end
      item
        ParamName = '周二组编号'
        FieldName = '周二组编号'
      end
      item
        ParamName = '周三组编号'
        FieldName = '周三组编号'
      end
      item
        ParamName = '周四组编号'
        FieldName = '周四组编号'
      end
      item
        ParamName = '周五组编号'
        FieldName = '周五组编号'
      end
      item
        ParamName = '周六组编号'
        FieldName = '周六组编号'
      end
      item
        ParamName = '周日组编号'
        FieldName = '周日组编号'
      end>
    Left = 48
    Top = 296
  end
  inherited DeleteRequest: TWVRequest
    ID = '周时间段参数设置'
    Bindings = <
      item
        ParamName = '时间段组编号'
        FieldName = '时间段组编号'
      end
      item
        ParamName = '时间段组名'
        FieldName = '时间段组名'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '周一组编号'
        FieldName = '周一组编号'
      end
      item
        ParamName = '周二组编号'
        FieldName = '周二组编号'
      end
      item
        ParamName = '周三组编号'
        FieldName = '周三组编号'
      end
      item
        ParamName = '周四组编号'
        FieldName = '周四组编号'
      end
      item
        ParamName = '周五组编号'
        FieldName = '周五组编号'
      end
      item
        ParamName = '周六组编号'
        FieldName = '周六组编号'
      end
      item
        ParamName = '周日组编号'
        FieldName = '周日组编号'
      end>
    Left = 88
    Top = 296
  end
  inherited ChangeRequest: TWVRequest
    ID = '周时间段参数设置'
    Bindings = <
      item
        ParamName = '时间段组编号'
        FieldName = '时间段组编号'
      end
      item
        ParamName = '时间段组名'
        FieldName = '时间段组名'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '周一组编号'
        FieldName = '周一组编号'
      end
      item
        ParamName = '周二组编号'
        FieldName = '周二组编号'
      end
      item
        ParamName = '周三组编号'
        FieldName = '周三组编号'
      end
      item
        ParamName = '周四组编号'
        FieldName = '周四组编号'
      end
      item
        ParamName = '周五组编号'
        FieldName = '周五组编号'
      end
      item
        ParamName = '周六组编号'
        FieldName = '周六组编号'
      end
      item
        ParamName = '周日组编号'
        FieldName = '周日组编号'
      end>
    Left = 120
    Top = 296
  end
  inherited WVDataSource: TWVDataSource
    Left = 148
    Top = 327
  end
  inherited alDatasetActions: TActionList
    Left = 108
    Top = 324
  end
  object WorkView2: TWorkView
    WorkFields = <
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
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
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
        Name = '操作类别.增加'
        Caption = '操作类别.增加'
        FieldType = wftUndefined
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
        Name = '查询.时间段名称'
        Caption = '查询.时间段名称'
        FieldType = wftUndefined
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
        Name = '查询.标识'
        Caption = '查询.标识'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '交易类型'
        Caption = '交易类型'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.时间段名称|查询.标识|查询.交易类型|'
      end
      item
        MonitorValueChangedFields = '|时间段名称|'
      end>
    Left = 376
    Top = 280
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView2
    FieldName = '查询结果集'
    Bindings = <>
    HideUnbindingFields = False
    Left = 412
    Top = 279
  end
  object DataSource1: TDataSource
    OnStateChange = DataSourceStateChange
    OnDataChange = DataSourceDataChange
    Left = 444
    Top = 279
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '时间段组查询'
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
        ParamName = '时间段名称'
        FieldName = '查询.时间段名称'
      end
      item
        ParamName = '标识'
        FieldName = '查询.标识'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    AfterExec = CheckReturnData
    Left = 480
    Top = 280
  end
end

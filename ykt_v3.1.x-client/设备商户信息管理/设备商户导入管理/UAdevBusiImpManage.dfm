inherited faqhdevBusiImpManage: TfaqhdevBusiImpManage
  Width = 681
  Height = 476
  Caption = '设备商户导入管理'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 476
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 409
        Width = 677
        Height = 44
        TabOrder = 3
        object Label33: TLabel [0]
          Left = 102
          Top = 9
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 585
          Caption = '审核(&C)'
          Enabled = False
          TabOrder = 5
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            18000000000000030000120B0000120B00000000000000000000FFFFFFFFFFFF
            FFFFFFCBD9CF509050408040306830305030203820202820B7C6B7FFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF70A08090E8B080E8A080E0A040
            905050B070509060304030B05040A04030A03020872C1DD3CDCBFFFFFFFFFFFF
            FFFFFF80B080C0E8D090F0B080B080C0D8C040905050A870406040FF9890C058
            50F05840E05030902810FFFFFFFFFFFFFFFFFFCBD5CF80B89070B070F0F0F0FF
            F8FF70A070407840D08870E09080F0B8B0C05850E05840A03820DBECF37AADBD
            598FA66080904068705050505050506060603B774AA66859C06860F0F8F0FFF8
            FFC05850B04830F0F0F06297B250B0D080D8F080B8C0000000B0B0B0B0B8B090
            98905058506F6F6F606060505850606060B04830CFBDB7FFFFFF5090B050D8FF
            90E8FF302830201820E0E0E0D0D0D0B0B0B0909890605860D0D0D0B0B0B09098
            90505850878787FFFFFF5090B050D0FF90E8F0404840403840C0C0C0E0E0E0D0
            D0D0B0B0B0706870E0E0E0D0D0D0B0B0B0909890605860FFFFFF5098B050D0FF
            90E8F0607070505850505050606060504850D0D0D0707070C0C0C0E0E0E0D0D0
            D0B0B0B0706870FFFFFF6098B050D0FF90E8F080B8C0606060807880A098A080
            8880404840404840505050606060504850D0D0D0777777FFFFFF6098B050D0FF
            90E0F0A0E0F060A0B0507880808080707880405060605860807880A098A08088
            80404840A4A4A4FFFFFF60A0C050D0FF90E0F0A0E8F070D8F020B8F000A8F000
            A0E0306890B7BAB77C847C808080778077ABAFABEFF0EFFFFFFF60A0C040D0F0
            90E0F0A0E8F070D8F020B8F000A8F000A0E0307090FFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFF904820FFFFFF70A8C050D8FFA0F0FFB0F0FFA0F0FF90E8FF70D8F040
            C0F0408090FFFFFFF6E3D8904820FFFFFFF9ECE5D06830FFFFFF80B0C0A0E0F0
            C0F8FFC0F8FFC0F8FFC0F8FFC0F8FFA0E0F06090A0FFFFFFA048209048209048
            20D06830F9ECE5FFFFFFD5EAED97C4D970A8C070A0B070A0B07098B070A0B081
            B3BAC0DCE3FFFFFFF6E3D8904820FFFFFFFFFFFFFFFFFFFFFFFF}
        end
        inherited btnChange: TBitBtn [2]
          Left = 328
          Enabled = False
          TabOrder = 2
        end
        inherited btnQuery: TBitBtn [3]
          Left = 242
        end
        inherited btnDelete: TBitBtn
          Left = 414
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 16
          Top = 24
          Width = 169
          TabOrder = 7
          Visible = False
        end
        object btnPatchDel: TBitBtn
          Left = 499
          Top = 3
          Width = 79
          Height = 25
          Hint = '删除当前选中的条目'
          Anchors = [akTop, akRight]
          Caption = '批量删除'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 143
          Top = 5
          Width = 98
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 6
          Text = '<批次号>'
          WorkView = WorkView1
          FieldName = '批次号'
        end
        object pbstat: TProgressBar
          Left = 0
          Top = 34
          Width = 677
          Height = 10
          Align = alBottom
          Min = 0
          Max = 100
          TabOrder = 8
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 81
        Width = 677
        Height = 328
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入批次号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '顺序号'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备物理编号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备名称'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户名称'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '开始时间'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '结束时间'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '启用日期'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '停用日期'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '错误信息'
            Width = 100
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 63
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label2: TLabel
          Left = 406
          Top = 42
          Width = 60
          Height = 12
          Caption = '导入批次号'
        end
        object Label5: TLabel
          Left = 26
          Top = 18
          Width = 48
          Height = 12
          Caption = '设备编号'
        end
        object Label6: TLabel
          Left = 202
          Top = 18
          Width = 72
          Height = 12
          Caption = '设备物理编号'
        end
        object Label7: TLabel
          Left = 418
          Top = 18
          Width = 48
          Height = 12
          Caption = '设备名称'
        end
        object Label8: TLabel
          Left = 26
          Top = 42
          Width = 48
          Height = 12
          Caption = '商户编号'
        end
        object Label9: TLabel
          Left = 226
          Top = 42
          Width = 48
          Height = 12
          Caption = '商户名称'
        end
        object WVEdit2: TWVEdit
          Left = 476
          Top = 38
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 5
          Text = '<查询.导入批次号>'
          WorkView = WorkView
          FieldName = '查询.导入批次号'
        end
        object WVEdit6: TWVEdit
          Left = 284
          Top = 14
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.设备物理编号>'
          WorkView = WorkView
          FieldName = '查询.设备物理编号'
        end
        object WVEdit7: TWVEdit
          Left = 476
          Top = 14
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.设备名称>'
          WorkView = WorkView
          FieldName = '查询.设备名称'
        end
        object WVEdit9: TWVEdit
          Left = 284
          Top = 38
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<查询.商户名称>'
          WorkView = WorkView
          FieldName = '查询.商户名称'
        end
        object edtDevNo: TWVEdit
          Left = 84
          Top = 14
          Width = 100
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.设备编号>'
          WorkView = WorkView
          FieldName = '查询.设备编号'
        end
        object edtBusiNo: TWVEdit
          Left = 84
          Top = 38
          Width = 100
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 3
          Text = '<查询.商户编号>'
          WorkView = WorkView
          FieldName = '查询.商户编号'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label15: TLabel [0]
        Left = 86
        Top = 68
        Width = 60
        Height = 12
        Caption = '导入批次号'
      end
      object Label16: TLabel [1]
        Left = 86
        Top = 104
        Width = 60
        Height = 12
        Caption = '导入顺序号'
      end
      object Label20: TLabel [2]
        Left = 98
        Top = 140
        Width = 48
        Height = 12
        Caption = '设备名称'
      end
      object Label22: TLabel [3]
        Left = 98
        Top = 176
        Width = 48
        Height = 12
        Caption = '商户名称'
      end
      object Label24: TLabel [4]
        Left = 98
        Top = 284
        Width = 48
        Height = 12
        Caption = '结束时间'
      end
      object Label25: TLabel [5]
        Left = 98
        Top = 212
        Width = 48
        Height = 12
        Caption = '启用日期'
      end
      object Label26: TLabel [6]
        Left = 98
        Top = 248
        Width = 48
        Height = 12
        Caption = '停用日期'
      end
      object Label1: TLabel [7]
        Left = 266
        Top = 212
        Width = 108
        Height = 12
        Caption = '日期格式：yyyymmdd'
      end
      object Label3: TLabel [8]
        Left = 266
        Top = 249
        Width = 108
        Height = 12
        Caption = '日期格式：yyyymmdd'
      end
      object Label4: TLabel [9]
        Left = 266
        Top = 284
        Width = 96
        Height = 12
        Caption = '时间格式：hhmmss'
      end
      inherited UIPanel2: TUIPanel
        Top = 417
        Width = 677
        TabOrder = 6
        inherited btnOK: TBitBtn
          Left = 505
        end
        inherited btnCancel: TBitBtn
          Left = 593
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtPatchNo: TWVEdit
        Left = 158
        Top = 64
        Width = 100
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 0
        Text = '<导入批次号>'
        WorkView = WorkView
        FieldName = '导入批次号'
        SynchronizeWhenExit = True
      end
      object edtDevName: TWVEdit
        Left = 158
        Top = 136
        Width = 219
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<设备名称>'
        WorkView = WorkView
        FieldName = '设备名称'
        SynchronizeWhenExit = True
      end
      object edtBusiName: TWVEdit
        Left = 158
        Top = 172
        Width = 219
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<商户名称>'
        WorkView = WorkView
        FieldName = '商户名称'
        SynchronizeWhenExit = True
      end
      object edtEndTime: TWVEdit
        Left = 158
        Top = 280
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 6
        ReadOnly = False
        TabOrder = 5
        Text = '<结束时间>'
        WorkView = WorkView
        FieldName = '结束时间'
        SynchronizeWhenExit = True
      end
      object edtStartDate: TWVEdit
        Left = 158
        Top = 208
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<启用日期>'
        WorkView = WorkView
        FieldName = '启用日期'
        SynchronizeWhenExit = True
      end
      object edtStopDate: TWVEdit
        Left = 158
        Top = 244
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<停用日期>'
        WorkView = WorkView
        FieldName = '停用日期'
        SynchronizeWhenExit = True
      end
      object edtNO: TWVEdit
        Left = 158
        Top = 96
        Width = 100
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 7
        Text = '<导入顺序号>'
        WorkView = WorkView
        FieldName = '导入顺序号'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 484
    Top = 183
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
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '查询.导入批次号'
        Caption = '查询.导入批次号'
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
        Name = '查询.设备编号'
        Caption = '查询.设备编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.设备物理编号'
        Caption = '查询.设备物理编号'
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
        Name = '查询.设备名称'
        Caption = '查询.设备名称'
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
        Name = '查询.商户编号'
        Caption = '查询.商户编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
        Name = '导入批次号'
        Caption = '导入批次号'
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
        DataField = 'scust_limit'
      end
      item
        Name = '导入顺序号'
        Caption = '导入顺序号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '设备名称'
        Caption = '设备名称'
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
        DataField = 'sbankname'
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
        DataField = 'sall_name'
      end
      item
        Name = '结束时间'
        Caption = '结束时间'
        FieldType = wftUndefined
        DomainName = '时间校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'stime2'
      end
      item
        Name = '启用日期'
        Caption = '启用日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        DataField = 'Sdate1'
      end
      item
        Name = '停用日期'
        Caption = '停用日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        DataField = 'Sdate2'
      end>
    FieldsMonitors = <
      item
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 416
    Top = 152
  end
  inherited QueryRequest: TWVRequest
    ID = '设备商户查询'
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
        ParamName = '导入批次号'
        FieldName = '查询.导入批次号'
      end
      item
        ParamName = '设备编号'
        FieldName = '查询.设备编号'
      end
      item
        ParamName = '设备物理编号'
        FieldName = '查询.设备物理编号'
      end
      item
        ParamName = '设备名称'
        FieldName = '查询.设备名称'
      end
      item
        ParamName = '商户编号'
        FieldName = '查询.商户编号'
      end
      item
        ParamName = '商户名称'
        FieldName = '查询.商户名称'
      end>
    Left = 544
    Top = 152
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 452
    Top = 183
  end
  inherited AddRequest: TWVRequest
    ID = '设备商户导入管理'
    Bindings = <
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '导入顺序号'
        FieldName = '导入顺序号'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '启用日期'
        FieldName = '启用日期'
      end
      item
        ParamName = '停用日期'
        FieldName = '停用日期'
      end>
    Left = 448
    Top = 152
  end
  inherited DeleteRequest: TWVRequest
    ID = '设备商户导入管理'
    Bindings = <
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '导入顺序号'
        FieldName = '导入顺序号'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '启用日期'
        FieldName = '启用日期'
      end
      item
        ParamName = '停用日期'
        FieldName = '停用日期'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 480
    Top = 152
  end
  inherited ChangeRequest: TWVRequest
    ID = '设备商户导入管理'
    Bindings = <
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '导入顺序号'
        FieldName = '导入顺序号'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '启用日期'
        FieldName = '启用日期'
      end
      item
        ParamName = '停用日期'
        FieldName = '停用日期'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 512
    Top = 152
  end
  inherited WVDataSource: TWVDataSource
    Left = 516
    Top = 183
  end
  inherited alDatasetActions: TActionList
    Left = 548
    Top = 180
  end
  object WVImpCheck: TWorkView
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
        Name = '导入批次号'
        Caption = '导入批次号'
        FieldType = wftUndefined
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
        DataField = 'scust_limit'
      end
      item
        Name = '导入顺序号'
        Caption = '导入顺序号'
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
        GroupIndex = 1
        DataField = 'Lvol1'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.操作标志|查询.导入批次号|查询.导入顺序号|查询.记录号|查询.' +
          '设备编号|查询.设备物理编号|查询.设备名称|查询.商户编号|查询.商户' +
          '名称|查询.开始时间|查询.结束时间|查询.启用日期|查询.停用日期|查' +
          '询.备注|'
      end
      item
        MonitorValueChangedFields = 
          '|导入批次号|导入顺序号|记录号|设备编号|设备物理编号|设备名称|商' +
          '户编号|商户名称|开始时间|结束时间|启用日期|停用日期|'
      end>
    Left = 416
    Top = 216
  end
  object WVRImpCheck: TWVRequest
    WorkView = WVImpCheck
    ID = '设备商户导入审核'
    Bindings = <
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '导入顺序号'
        FieldName = '导入顺序号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    AfterExec = CheckReturnData
    Left = 448
    Top = 216
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        GroupIndex = 1
      end
      item
        Name = '批次号'
        Caption = '批次号'
        FieldType = wftUndefined
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
        DataField = 'scust_limit'
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
        Name = '批量标志'
        Caption = '批量标志'
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
          '|查询.操作标志|查询.导入批次号|查询.导入顺序号|查询.记录号|查询.' +
          '设备编号|查询.设备物理编号|查询.设备名称|查询.商户编号|查询.商户' +
          '名称|查询.开始时间|查询.结束时间|查询.启用日期|查询.停用日期|查' +
          '询.备注|'
      end
      item
        MonitorValueChangedFields = 
          '|导入批次号|导入顺序号|记录号|设备编号|设备物理编号|设备名称|商' +
          '户编号|商户名称|开始时间|结束时间|启用日期|停用日期|'
      end>
    Left = 424
    Top = 264
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '商户设备批量删除'
    Bindings = <
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '批量标志'
        FieldName = '批量标志'
      end
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
    AfterExec = CheckReturnData
    Left = 456
    Top = 264
  end
end

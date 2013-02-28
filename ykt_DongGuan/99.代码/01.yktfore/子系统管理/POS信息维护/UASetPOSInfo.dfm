inherited faqhSetPOSInfo: TfaqhSetPOSInfo
  Width = 758
  Height = 477
  Caption = 'POS信息维护'
  inherited pcPages: TRzPageControl
    Width = 758
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 754
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 488
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 576
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 399
        end
        inherited btnDelete: TBitBtn
          Left = 665
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 754
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 105
        Width = 754
        Height = 319
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sstock_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '地区编码'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '所属商户号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备终端号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '产品编号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备型号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spost_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备类型'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备名称'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备用途'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备状态'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '启用日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '注册日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '删除日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '最后更新时间'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '备注'
            Width = 100
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 754
        Height = 87
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label2: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = '设备编号'
        end
        object Label3: TLabel
          Left = 236
          Top = 10
          Width = 60
          Height = 12
          Caption = '所属商户号'
        end
        object Label4: TLabel
          Left = 434
          Top = 10
          Width = 60
          Height = 12
          Caption = '设备终端号'
        end
        object Label5: TLabel
          Left = 42
          Top = 34
          Width = 48
          Height = 12
          Caption = '产品编号'
        end
        object Label6: TLabel
          Left = 248
          Top = 34
          Width = 48
          Height = 12
          Caption = '设备型号'
        end
        object Label7: TLabel
          Left = 446
          Top = 34
          Width = 48
          Height = 12
          Caption = '设备类型'
        end
        object Label8: TLabel
          Left = 42
          Top = 58
          Width = 48
          Height = 12
          Caption = '设备名称'
        end
        object Label9: TLabel
          Left = 446
          Top = 58
          Width = 48
          Height = 12
          Caption = '设备用途'
        end
        object Label10: TLabel
          Left = 248
          Top = 58
          Width = 48
          Height = 12
          Caption = '设备状态'
        end
        object WVEdit4: TWVEdit
          Left = 500
          Top = 6
          Width = 121
          Height = 20
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.设备终端号>'
          WorkView = WorkView
          FieldName = '查询.设备终端号'
        end
        object WVEdit5: TWVEdit
          Left = 100
          Top = 30
          Width = 115
          Height = 20
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.终端序列号>'
          WorkView = WorkView
          FieldName = '查询.终端序列号'
        end
        object WVEdit8: TWVEdit
          Left = 100
          Top = 54
          Width = 115
          Height = 20
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.设备名称>'
          WorkView = WorkView
          FieldName = '查询.设备名称'
        end
        object WVComboBox3: TWVComboBox
          Left = 300
          Top = 30
          Width = 121
          Height = 20
          Style = csDropDownList
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '查询.设备型号'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*223'
        end
        object WVComboBox1: TWVComboBox
          Left = 300
          Top = 54
          Width = 121
          Height = 20
          Style = csDropDownList
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '查询.设备状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*220'
        end
        object WVComboBox2: TWVComboBox
          Left = 500
          Top = 30
          Width = 121
          Height = 20
          Style = csDropDownList
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '查询.设备类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*221'
        end
        object WVComboBox4: TWVComboBox
          Left = 500
          Top = 54
          Width = 121
          Height = 20
          Style = csDropDownList
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '查询.用途'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*222'
        end
        object edtPosIdQ: TWVEdit
          Left = 100
          Top = 6
          Width = 115
          Height = 20
          ReadOnly = False
          TabOrder = 7
          Text = '<查询.设备编号>'
          WorkView = WorkView
          FieldName = '查询.设备编号'
        end
        object edtBusiIdQ: TWVEdit
          Left = 300
          Top = 6
          Width = 121
          Height = 20
          MaxLength = 22
          ReadOnly = False
          TabOrder = 8
          Text = '<查询.所属商户号>'
          WorkView = WorkView
          FieldName = '查询.所属商户号'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label17: TLabel [0]
        Left = 44
        Top = 28
        Width = 48
        Height = 12
        Caption = '设备编号'
      end
      object Label18: TLabel [1]
        Left = 238
        Top = 236
        Width = 60
        Height = 12
        Caption = '所属商户号'
        Visible = False
      end
      object Label19: TLabel [2]
        Left = 455
        Top = 68
        Width = 60
        Height = 12
        Caption = '设备终端号'
      end
      object Label20: TLabel [3]
        Left = 44
        Top = 108
        Width = 48
        Height = 12
        Caption = '产品编号'
      end
      object Label21: TLabel [4]
        Left = 258
        Top = 108
        Width = 48
        Height = 12
        Caption = '设备型号'
      end
      object Label22: TLabel [5]
        Left = 467
        Top = 108
        Width = 48
        Height = 12
        Caption = '设备类型'
      end
      object Label23: TLabel [6]
        Left = 258
        Top = 68
        Width = 48
        Height = 12
        Caption = '设备名称'
      end
      object Label24: TLabel [7]
        Left = 44
        Top = 148
        Width = 48
        Height = 12
        Caption = '设备用途'
      end
      object Label26: TLabel [8]
        Left = 258
        Top = 148
        Width = 48
        Height = 12
        Caption = '启用日期'
      end
      object Label1: TLabel [9]
        Left = 44
        Top = 68
        Width = 48
        Height = 12
        Caption = '地区编码'
      end
      object Label11: TLabel [10]
        Left = 491
        Top = 148
        Width = 24
        Height = 12
        Caption = '备注'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 754
        TabOrder = 10
        inherited btnOK: TBitBtn
          Left = 578
        end
        inherited btnCancel: TBitBtn
          Left = 666
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVEdit19: TWVEdit
        Left = 524
        Top = 64
        Width = 127
        Height = 20
        ReadOnly = False
        TabOrder = 3
        Text = '<设备终端号>'
        WorkView = WorkView
        FieldName = '设备终端号'
        SynchronizeWhenExit = True
      end
      object WVEdit20: TWVEdit
        Left = 100
        Top = 104
        Width = 123
        Height = 20
        ReadOnly = False
        TabOrder = 4
        Text = '<终端序列号>'
        WorkView = WorkView
        FieldName = '终端序列号'
        SynchronizeWhenExit = True
      end
      object edtPosName: TWVEdit
        Left = 312
        Top = 64
        Width = 128
        Height = 20
        ReadOnly = False
        TabOrder = 2
        Text = '<设备名称>'
        WorkView = WorkView
        FieldName = '设备名称'
        SynchronizeWhenExit = True
      end
      object edtDate: TWVEdit
        Left = 312
        Top = 144
        Width = 127
        Height = 20
        MaxLength = 8
        ReadOnly = False
        TabOrder = 8
        Text = '<启用日期>'
        WorkView = WorkView
        FieldName = '启用日期'
        SynchronizeWhenExit = True
      end
      object WVComboBox5: TWVComboBox
        Left = 524
        Top = 102
        Width = 127
        Height = 20
        Style = csDropDownList
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '设备类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*221'
      end
      object WVComboBox6: TWVComboBox
        Left = 100
        Top = 144
        Width = 123
        Height = 20
        Style = csDropDownList
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '用途'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*222'
      end
      object WVComboBox7: TWVComboBox
        Left = 312
        Top = 104
        Width = 128
        Height = 20
        Style = csDropDownList
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '设备型号'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*223'
      end
      object edtPosId: TWVEdit
        Left = 100
        Top = 24
        Width = 123
        Height = 20
        ReadOnly = False
        TabOrder = 0
        Text = '<设备机编号>'
        WorkView = WorkView
        FieldName = '设备机编号'
        SynchronizeWhenExit = True
      end
      object edtBusiId: TWVEdit
        Left = 304
        Top = 232
        Width = 128
        Height = 20
        MaxLength = 22
        ReadOnly = False
        TabOrder = 9
        Text = '<所属商户号>'
        Visible = False
        WorkView = WorkView
        FieldName = '所属商户号'
        SynchronizeWhenExit = True
      end
      object WVComboBox8: TWVComboBox
        Left = 100
        Top = 64
        Width = 123
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '地区编码'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*229'
      end
      object WVEdit1: TWVEdit
        Left = 524
        Top = 144
        Width = 127
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 11
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 148
    Top = 375
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
        Name = '查询.所属商户号'
        Caption = '查询.所属商户号'
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
      end
      item
        Name = '查询.设备终端号'
        Caption = '查询.设备终端号'
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
        Name = '查询.终端序列号'
        Caption = '查询.终端序列号'
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
        Name = '查询.设备型号'
        Caption = '查询.设备型号'
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
        Name = '查询.设备类型'
        Caption = '查询.设备类型'
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
        Name = '查询.用途'
        Caption = '查询.用途'
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
        Name = '查询.设备状态'
        Caption = '查询.设备状态'
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
        Name = '操作标志'
        Caption = '操作标志'
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
        DataField = 'sstat_type'
      end
      item
        Name = '设备机编号'
        Caption = '设备机编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
        DataField = 'scert_no'
      end
      item
        Name = '所属商户号'
        Caption = '所属商户号'
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
      end
      item
        Name = '设备终端号'
        Caption = '设备终端号'
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
        DataField = 'sname'
      end
      item
        Name = '终端序列号'
        Caption = '终端序列号'
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
        DataField = 'sname2'
      end
      item
        Name = '设备型号'
        Caption = '设备型号'
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
        Name = '设备类型'
        Caption = '设备类型'
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
        DataField = 'spost_code'
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
        Name = '用途'
        Caption = '用途'
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
        Name = '设备状态'
        Caption = '设备状态'
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
        DataField = 'sstatus0'
      end
      item
        Name = '启用日期'
        Caption = '启用日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sdate0'
      end
      item
        Name = '注册日期'
        Caption = '注册日期'
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
        DataField = 'sdate1'
      end
      item
        Name = '删除日期'
        Caption = '删除日期'
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
        DataField = 'sdate2'
      end
      item
        Name = '最后更新时间'
        Caption = '最后更新时间'
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
        DataField = 'scard0'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '地区编码'
        Caption = '地区编码'
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
        DataField = 'sstock_code'
      end>
    InvalidColor = clWindow
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = 'POS信息维护查询'
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
        ParamName = '设备编号'
        FieldName = '查询.设备编号'
      end
      item
        ParamName = '所属商户号'
        FieldName = '查询.所属商户号'
      end
      item
        ParamName = '设备终端号'
        FieldName = '查询.设备终端号'
      end
      item
        ParamName = '终端序列号'
        FieldName = '查询.终端序列号'
      end
      item
        ParamName = '设备型号'
        FieldName = '查询.设备型号'
      end
      item
        ParamName = '设备类型'
        FieldName = '查询.设备类型'
      end
      item
        ParamName = '设备名称'
        FieldName = '查询.设备名称'
      end
      item
        ParamName = '用途'
        FieldName = '查询.用途'
      end
      item
        ParamName = '设备状态'
        FieldName = '查询.设备状态'
      end>
    Left = 208
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '229'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '223'
      end
      item
        FieldName = 'spost_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '221'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'idobjects'
        DataPresentParam = '222'
      end
      item
        FieldName = 'sstatus0'
        DataPresentType = 'idobjects'
        DataPresentParam = '220'
      end>
    Left = 108
    Top = 375
  end
  inherited AddRequest: TWVRequest
    ID = 'POS信息维护'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '设备机编号'
        FieldName = '设备机编号'
      end
      item
        ParamName = '所属商户号'
        FieldName = '所属商户号'
      end
      item
        ParamName = '设备终端号'
        FieldName = '设备终端号'
      end
      item
        ParamName = '终端序列号'
        FieldName = '终端序列号'
      end
      item
        ParamName = '设备型号'
        FieldName = '设备型号'
      end
      item
        ParamName = '设备类型'
        FieldName = '设备类型'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '用途'
        FieldName = '用途'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end
      item
        ParamName = '启用日期'
        FieldName = '启用日期'
      end
      item
        ParamName = '注册日期'
        FieldName = '注册日期'
      end
      item
        ParamName = '删除日期'
        FieldName = '删除日期'
      end
      item
        ParamName = '最后更新时间'
        FieldName = '最后更新时间'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '地区编码'
        FieldName = '地区编码'
      end>
    Left = 112
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = 'POS信息维护'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '设备机编号'
        FieldName = '设备机编号'
      end
      item
        ParamName = '所属商户号'
        FieldName = '所属商户号'
      end
      item
        ParamName = '设备终端号'
        FieldName = '设备终端号'
      end
      item
        ParamName = '终端序列号'
        FieldName = '终端序列号'
      end
      item
        ParamName = '设备型号'
        FieldName = '设备型号'
      end
      item
        ParamName = '设备类型'
        FieldName = '设备类型'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '用途'
        FieldName = '用途'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end
      item
        ParamName = '启用日期'
        FieldName = '启用日期'
      end
      item
        ParamName = '注册日期'
        FieldName = '注册日期'
      end
      item
        ParamName = '删除日期'
        FieldName = '删除日期'
      end
      item
        ParamName = '最后更新时间'
        FieldName = '最后更新时间'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '地区编码'
        FieldName = '地区编码'
      end>
    Left = 144
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = 'POS信息维护'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '设备机编号'
        FieldName = '设备机编号'
      end
      item
        ParamName = '所属商户号'
        FieldName = '所属商户号'
      end
      item
        ParamName = '设备终端号'
        FieldName = '设备终端号'
      end
      item
        ParamName = '终端序列号'
        FieldName = '终端序列号'
      end
      item
        ParamName = '设备型号'
        FieldName = '设备型号'
      end
      item
        ParamName = '设备类型'
        FieldName = '设备类型'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '用途'
        FieldName = '用途'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end
      item
        ParamName = '启用日期'
        FieldName = '启用日期'
      end
      item
        ParamName = '注册日期'
        FieldName = '注册日期'
      end
      item
        ParamName = '删除日期'
        FieldName = '删除日期'
      end
      item
        ParamName = '最后更新时间'
        FieldName = '最后更新时间'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '地区编码'
        FieldName = '地区编码'
      end>
    Left = 176
    Top = 344
  end
  inherited WVDataSource: TWVDataSource
    Left = 228
    Top = 375
  end
  inherited alDatasetActions: TActionList
    Left = 188
    Top = 372
  end
end

inherited faqhimpNewStuCardOper: TfaqhimpNewStuCardOper
  Width = 873
  Height = 477
  Caption = '新生换卡导入管理'
  inherited pcPages: TRzPageControl
    Width = 873
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 869
        TabOrder = 3
        object Label10: TLabel [0]
          Left = 94
          Top = 9
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 312
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnChange: TBitBtn [2]
          Left = 614
          Enabled = False
        end
        inherited btnQuery: TBitBtn [3]
          Left = 527
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 701
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 0
          Width = 161
          TabOrder = 7
          Visible = False
        end
        object btnPatchDel: TBitBtn
          Left = 787
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
          TabOrder = 5
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 135
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
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 869
      end
      inherited Grid: TRzDBGrid
        Top = 51
        Width = 869
        Height = 373
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '批次号'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '学/工号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '姓名'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '新卡显示卡号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Scust_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '新卡物理编号'
            Width = 96
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡有效期'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '旧卡物理编号'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '状态'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '修改日期'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '部门全称'
            Width = 200
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 869
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label3: TLabel
          Left = 406
          Top = 10
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        object Label6: TLabel
          Left = 24
          Top = 10
          Width = 42
          Height = 12
          Caption = '学/工号'
        end
        object Label9: TLabel
          Left = 202
          Top = 10
          Width = 72
          Height = 12
          Caption = '新卡显示卡号'
        end
        object lbl1: TLabel
          Left = 594
          Top = 10
          Width = 24
          Height = 12
          Caption = '状态'
        end
        object WVEdit3: TWVEdit
          Left = 444
          Top = 6
          Width = 125
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.批次号>'
          WorkView = WorkView
          FieldName = '查询.批次号'
        end
        object WVEdit6: TWVEdit
          Left = 68
          Top = 6
          Width = 119
          Height = 20
          CharCase = ecUpperCase
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.学工号>'
          WorkView = WorkView
          FieldName = '查询.学工号'
        end
        object WVEdit9: TWVEdit
          Left = 276
          Top = 6
          Width = 118
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.新卡卡号>'
          WorkView = WorkView
          FieldName = '查询.新卡卡号'
        end
        object cbbstatus: TWVComboBox
          Left = 625
          Top = 7
          Width = 104
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '查询.状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*96'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label21: TLabel [0]
        Left = 82
        Top = 100
        Width = 42
        Height = 12
        Caption = '学/工号'
      end
      object Label32: TLabel [1]
        Left = 62
        Top = 421
        Width = 48
        Height = 12
        Caption = '客户号 *'
        Visible = False
      end
      object Label12: TLabel [2]
        Left = 54
        Top = 140
        Width = 72
        Height = 12
        Caption = '新卡显示卡号'
      end
      object Label1: TLabel [3]
        Left = 78
        Top = 180
        Width = 48
        Height = 12
        Caption = '卡有效期'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 869
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 697
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 785
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtStuempNo: TWVEdit
        Left = 137
        Top = 95
        Width = 159
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<学工号>'
        WorkView = WorkView
        FieldName = '学工号'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 137
        Top = 135
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<新卡卡号>'
        WorkView = WorkView
        FieldName = '新卡卡号'
        SynchronizeWhenExit = True
      end
      object edtDealDate: TWVEdit
        Left = 137
        Top = 175
        Width = 159
        Height = 20
        Color = clWhite
        MaxLength = 8
        ReadOnly = False
        TabOrder = 2
        Text = '<卡有效期>'
        WorkView = WorkView
        FieldName = '卡有效期'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 364
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        GroupIndex = 1
        DataField = '@Dataset'
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
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.批次号'
        Caption = '查询.批次号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.学工号'
        Caption = '查询.学工号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.新卡卡号'
        Caption = '查询.新卡卡号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '学工号'
        Caption = '学工号'
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
        DataField = 'spager'
      end
      item
        Name = '新卡卡号'
        Caption = '新卡卡号'
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
        DataField = 'sorder0'
      end
      item
        Name = '查询.状态'
        Caption = '查询.状态'
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
        Name = '卡有效期'
        Caption = '卡有效期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.操作标志|查询.导入日期|查询.批次号|查询.导入顺序号|查询.导' +
          '入操作员|查询.学工号|查询.客户类型|查询.收费类别|查询.客户姓名|' +
          '查询.区域代码|查询.部门代码|查询.专业代码|查询.班级|查询.证件类' +
          '型|查询.证件号码|查询.性别|查询.国籍|查询.民族|查询.电子邮箱|查' +
          '询.电话|查询.手机|查询.地址|查询.邮政编码|查询.入校日期|查询.预' +
          '计离校日期|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|导入日期|批次号|导入顺序号|导入操作员|学工号|客户类型|收费类别|' +
          '客户姓名|区域代码|部门代码|专业代码|班级|证件类型|证件号码|性别|' +
          '国籍|民族|电子邮箱|电话|手机|地址|邮政编码|入校日期|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 336
    Top = 248
  end
  inherited QueryRequest: TWVRequest
    ID = '新生换卡导入查询'
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
        ParamName = '新卡显示卡号'
        FieldName = '查询.新卡卡号'
      end
      item
        ParamName = '批次号'
        FieldName = '查询.批次号'
      end
      item
        ParamName = '学工号'
        FieldName = '查询.学工号'
      end
      item
        ParamName = '绑定状态'
        FieldName = '查询.状态'
      end>
    Left = 464
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '96'
      end>
    Left = 396
  end
  inherited AddRequest: TWVRequest
    ID = '新生换卡名单管理'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '新卡卡号'
        FieldName = '新卡卡号'
      end
      item
        ParamName = '卡有效期'
        FieldName = '卡有效期'
      end>
    Left = 368
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '新生换卡名单管理'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '新卡卡号'
        FieldName = '新卡卡号'
      end
      item
        ParamName = '卡有效期'
        FieldName = '卡有效期'
      end>
    Left = 400
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '新生换卡名单管理'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '新卡卡号'
        FieldName = '新卡卡号'
      end
      item
        ParamName = '卡有效期'
        FieldName = '卡有效期'
      end>
    Left = 432
    Top = 248
  end
  inherited WVDataSource: TWVDataSource
    Left = 468
  end
  inherited alDatasetActions: TActionList
    Left = 428
    Top = 284
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
    Left = 336
    Top = 328
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '新生换卡名单管理'
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
    Left = 368
    Top = 328
  end
end

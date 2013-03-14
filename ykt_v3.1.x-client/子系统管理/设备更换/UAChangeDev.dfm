inherited fqhqChangeDev: TfqhqChangeDev
  Width = 893
  Height = 489
  inherited UIPnlQueryCount: TUIPanel [0]
    Width = 893
    TabOrder = 0
    inherited Image1: TImage
      Width = 893
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
      Visible = False
    end
  end
  inherited UIPanel1: TUIPanel [1]
    Top = 459
    Width = 893
    TabOrder = 2
    inherited btnQuery: TBitBtn
      Left = 804
      Hint = '更换设备'
      Caption = '更换设备'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 803
      Top = 100
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 893
    Height = 441
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Left = 104
      Top = 72
      Width = 284
      Height = 170
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所在区域'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备标识'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备名称'
          Width = 87
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备物理ID'
          Width = 71
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '机号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '机型代码'
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '服务器端口总数'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '上级设备'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scurrency_type'
          PickList.Strings = ()
          Title.Caption = '卡片结构'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '服务器端口号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备状态'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '通讯端口号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备类型'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'IP地址'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所属子系统'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '备注'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt5'
          PickList.Strings = ()
          Title.Caption = '设备用途'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Caption = '是否支持科目收费'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = '通讯类别'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '导入批次号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '黑名单版本'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Caption = '备注'
          Width = 120
          Visible = True
        end>
    end
    object RzSizePanel1: TRzSizePanel
      Left = 0
      Top = 0
      Width = 454
      Height = 441
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 1
      UseGradients = True
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 446
        Height = 131
        Align = alTop
        BevelOuter = bvNone
        Color = 16119543
        TabOrder = 0
        object Label1: TLabel
          Left = 34
          Top = 27
          Width = 48
          Height = 12
          Caption = '设备名称'
        end
        object Label3: TLabel
          Left = 230
          Top = 80
          Width = 60
          Height = 12
          Caption = '设备物理ID'
        end
        object Label4: TLabel
          Left = 58
          Top = 53
          Width = 24
          Height = 12
          Caption = '机号'
        end
        object Label5: TLabel
          Left = 242
          Top = 29
          Width = 48
          Height = 12
          Caption = '设备机型'
        end
        object Label8: TLabel
          Left = 242
          Top = 53
          Width = 48
          Height = 12
          Caption = '设备类型'
        end
        object Label9: TLabel
          Left = 22
          Top = 80
          Width = 60
          Height = 12
          Caption = '所属子系统'
        end
        object Label2: TLabel
          Left = 34
          Top = 5
          Width = 75
          Height = 14
          Caption = '旧设备查询'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object lblOld: TLabel
          Left = 22
          Top = 108
          Width = 307
          Height = 12
          AutoSize = False
          Caption = '所属子系统'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVEdit1: TWVEdit
          Left = 84
          Top = 23
          Width = 135
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<设备名称>'
          WorkView = WorkView
          FieldName = '设备名称'
        end
        object WVEdit3: TWVEdit
          Left = 292
          Top = 76
          Width = 124
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<设备物理ID>'
          WorkView = WorkView
          FieldName = '设备物理ID'
        end
        object WVComboBox3: TWVComboBox
          Left = 84
          Top = 76
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '所属子系统'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVComboBox5: TWVComboBox
          Left = 292
          Top = 49
          Width = 124
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '设备物理型号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-35'
        end
        object WVComboBox6: TWVComboBox
          Left = 292
          Top = 23
          Width = 124
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '机型代码'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object edtMachineNo: TWVEdit
          Left = 84
          Top = 50
          Width = 135
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 2
          Text = '<机号>'
          WorkView = WorkView
          FieldName = '机号'
        end
        object btnOldQuery: TBitBtn
          Left = 340
          Top = 99
          Width = 75
          Height = 25
          Caption = '查 询'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
          OnClick = btnOldQueryClick
        end
      end
      object rgOld: TRzDBGrid
        Left = 0
        Top = 131
        Width = 446
        Height = 310
        Align = alClient
        Color = clWhite
        DataSource = DataSource
        FixedColor = 15458000
        TabOrder = 1
        TitleFont.Charset = GB2312_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = '宋体'
        TitleFont.Style = []
        OnCellClick = rgOldCellClick
        OnDrawColumnCell = GridDrawColumnCell
        OnKeyDown = GridKeyDown
        FrameColor = 12164479
        FrameStyle = fsGroove
        FrameVisible = True
        FixedLineColor = 12164479
        LineColor = clBackground
        Columns = <
          item
            Expanded = False
            FieldName = 'lserial1'
            Title.Alignment = taCenter
            Title.Caption = '所在区域'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            Title.Alignment = taCenter
            Title.Caption = '设备标识'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            Title.Alignment = taCenter
            Title.Caption = '设备名称'
            Width = 87
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            Title.Alignment = taCenter
            Title.Caption = '设备物理ID'
            Width = 71
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            Title.Alignment = taCenter
            Title.Caption = '机号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            Title.Alignment = taCenter
            Title.Caption = '机型代码'
            Width = 72
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            Title.Alignment = taCenter
            Title.Caption = '服务器端口总数'
            Width = 69
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt6'
            Title.Alignment = taCenter
            Title.Caption = '上级设备'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scurrency_type'
            Title.Caption = '卡片结构'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            Title.Alignment = taCenter
            Title.Caption = '服务器端口号'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            Title.Alignment = taCenter
            Title.Caption = '设备状态'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code2'
            Title.Alignment = taCenter
            Title.Caption = '通讯端口号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            Title.Alignment = taCenter
            Title.Caption = '设备类型'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstation0'
            Title.Alignment = taCenter
            Title.Caption = 'IP地址'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            Title.Alignment = taCenter
            Title.Caption = '所属子系统'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            Title.Alignment = taCenter
            Title.Caption = '备注'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'damt5'
            Title.Caption = '设备用途'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt4'
            Title.Caption = '是否支持科目收费'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            Title.Caption = '通讯类别'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            Title.Alignment = taCenter
            Title.Caption = '导入批次号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            Title.Alignment = taCenter
            Title.Caption = '黑名单版本'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            Title.Caption = '备注'
            Width = 120
            Visible = True
          end>
      end
    end
    object pnl1: TPanel
      Left = 454
      Top = 0
      Width = 439
      Height = 441
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 2
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 439
        Height = 131
        Align = alTop
        BevelOuter = bvNone
        Color = 16119543
        TabOrder = 0
        object Label6: TLabel
          Left = 34
          Top = 27
          Width = 48
          Height = 12
          Caption = '设备名称'
        end
        object Label7: TLabel
          Left = 230
          Top = 80
          Width = 60
          Height = 12
          Caption = '设备物理ID'
        end
        object Label10: TLabel
          Left = 58
          Top = 53
          Width = 24
          Height = 12
          Caption = '机号'
        end
        object Label11: TLabel
          Left = 242
          Top = 29
          Width = 48
          Height = 12
          Caption = '设备机型'
        end
        object Label12: TLabel
          Left = 242
          Top = 53
          Width = 48
          Height = 12
          Caption = '设备类型'
        end
        object Label13: TLabel
          Left = 22
          Top = 80
          Width = 60
          Height = 12
          Caption = '所属子系统'
        end
        object Label14: TLabel
          Left = 34
          Top = 5
          Width = 75
          Height = 14
          Caption = '新设备查询'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object lblNew: TLabel
          Left = 22
          Top = 108
          Width = 307
          Height = 12
          AutoSize = False
          Caption = '所属子系统'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVEdit2: TWVEdit
          Left = 84
          Top = 23
          Width = 135
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<设备名称>'
          WorkView = WVNewQry
          FieldName = '设备名称'
        end
        object WVEdit4: TWVEdit
          Left = 292
          Top = 76
          Width = 124
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<设备物理ID>'
          WorkView = WVNewQry
          FieldName = '设备物理ID'
        end
        object WVComboBox1: TWVComboBox
          Left = 84
          Top = 76
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 4
          WorkView = WVNewQry
          FieldName = '所属子系统'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVComboBox2: TWVComboBox
          Left = 292
          Top = 49
          Width = 124
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 3
          WorkView = WVNewQry
          FieldName = '设备物理型号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-35'
        end
        object WVComboBox4: TWVComboBox
          Left = 292
          Top = 23
          Width = 124
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WVNewQry
          FieldName = '机型代码'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object WVEdit5: TWVEdit
          Left = 84
          Top = 50
          Width = 135
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 2
          Text = '<机号>'
          WorkView = WVNewQry
          FieldName = '机号'
        end
        object btnNewQry: TBitBtn
          Left = 340
          Top = 99
          Width = 75
          Height = 25
          Caption = '查 询'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
          OnClick = btnNewQryClick
        end
      end
      object rgNew: TRzDBGrid
        Left = 0
        Top = 131
        Width = 439
        Height = 310
        Align = alClient
        Color = clWhite
        DataSource = DataSource1
        FixedColor = 15458000
        TabOrder = 1
        TitleFont.Charset = GB2312_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = '宋体'
        TitleFont.Style = []
        OnCellClick = rgNewCellClick
        OnDrawColumnCell = GridDrawColumnCell
        OnKeyDown = GridKeyDown
        FrameColor = 12164479
        FrameStyle = fsGroove
        FrameVisible = True
        FixedLineColor = 12164479
        LineColor = clBackground
        Columns = <
          item
            Expanded = False
            FieldName = 'lserial1'
            Title.Alignment = taCenter
            Title.Caption = '所在区域'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            Title.Alignment = taCenter
            Title.Caption = '设备标识'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            Title.Alignment = taCenter
            Title.Caption = '设备名称'
            Width = 87
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            Title.Alignment = taCenter
            Title.Caption = '设备物理ID'
            Width = 71
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            Title.Alignment = taCenter
            Title.Caption = '机号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            Title.Alignment = taCenter
            Title.Caption = '机型代码'
            Width = 72
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            Title.Alignment = taCenter
            Title.Caption = '服务器端口总数'
            Width = 69
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt6'
            Title.Alignment = taCenter
            Title.Caption = '上级设备'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scurrency_type'
            Title.Caption = '卡片结构'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            Title.Alignment = taCenter
            Title.Caption = '服务器端口号'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            Title.Alignment = taCenter
            Title.Caption = '设备状态'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code2'
            Title.Alignment = taCenter
            Title.Caption = '通讯端口号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            Title.Alignment = taCenter
            Title.Caption = '设备类型'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstation0'
            Title.Alignment = taCenter
            Title.Caption = 'IP地址'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            Title.Alignment = taCenter
            Title.Caption = '所属子系统'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            Title.Alignment = taCenter
            Title.Caption = '备注'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'damt5'
            Title.Caption = '设备用途'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt4'
            Title.Caption = '是否支持科目收费'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            Title.Caption = '通讯类别'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            Title.Alignment = taCenter
            Title.Caption = '导入批次号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            Title.Alignment = taCenter
            Title.Caption = '黑名单版本'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            Title.Caption = '备注'
            Width = 120
            Visible = True
          end>
      end
    end
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
      end
      item
        Name = '设备名称'
        Caption = '设备名称'
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
        DataField = 'scert_no'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '机型代码'
        Caption = '机型代码'
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
        DataField = 'sbank_code'
      end
      item
        Name = '设备物理型号'
        Caption = '设备物理型号'
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
        DataField = 'lbank_acc_type'
      end
      item
        Name = '所属子系统'
        Caption = '所属子系统'
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
        DataField = 'lserial0'
      end
      item
        Name = '设备状态'
        Caption = '设备状态'
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
        Name = '设备物理型号'
        Caption = '设备物理型号'
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
        Name = '所属子系统'
        Caption = '所属子系统'
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
        Name = '设备所在区域'
        Caption = '设备所在区域'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 100
    Top = 255
  end
  inherited MainRequest: TWVRequest
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
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end>
    Left = 136
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end
      item
        FieldName = 'damt6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '5'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'damt5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '81'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '50'
      end>
    Left = 176
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 216
    Top = 256
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WVNewQry
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end
      item
        FieldName = 'damt6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '5'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'damt5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '81'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '50'
      end>
    HideUnbindingFields = False
    Left = 160
    Top = 312
  end
  object DataSource1: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 192
    Top = 312
  end
  object WVChange: TWorkView
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
        Name = '老设备'
        Caption = '老设备'
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
        Name = '新设备'
        Caption = '新设备'
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
    Left = 92
    Top = 351
  end
  object WVRchange: TWVRequest
    WorkView = WVChange
    ID = '更换设备'
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
        ParamName = '老设备'
        FieldName = '老设备'
      end
      item
        ParamName = '新设备'
        FieldName = '新设备'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 352
  end
  object WVNewQry: TWorkView
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
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 92
    Top = 311
  end
  object WVRNewQry: TWVRequest
    WorkView = WVNewQry
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
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 312
  end
end

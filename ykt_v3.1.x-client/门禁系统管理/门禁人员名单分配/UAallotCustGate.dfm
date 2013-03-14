inherited faqhallotCustGate: TfaqhallotCustGate
  Width = 752
  Height = 543
  inherited UIPanel1: TUIPanel
    Top = 507
    Width = 752
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 87
      TabOrder = 1
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 6
      TabOrder = 0
      Visible = False
    end
    object btnPre: TBitBtn
      Left = 399
      Top = 5
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '上一步'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnPreClick
    end
    object btnNext: TBitBtn
      Left = 487
      Top = 5
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '下一步'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnNextClick
    end
    object btnFinish: TBitBtn
      Left = 575
      Top = 5
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '完 成'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnFinishClick
    end
    object btnInit: TBitBtn
      Left = 663
      Top = 5
      Width = 75
      Height = 25
      Hint = '返回到人员选择界面'
      Anchors = [akTop, akRight]
      Caption = '初始化'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnInitClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 752
    inherited Image1: TImage
      Width = 752
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 752
    Height = 489
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object rzpc1: TRzPageControl
      Left = 0
      Top = 0
      Width = 752
      Height = 489
      ActivePage = rztsCust
      Align = alClient
      Color = 16119543
      FlatColor = 10263441
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      ParentColor = False
      TabColors.HighlightBar = 3983359
      TabIndex = 0
      TabOrder = 0
      TabStyle = tsCutCorner
      FixedDimension = 19
      object rztsCust: TRzTabSheet
        Color = 16119543
        Caption = '人员选择'
        object pnl1: TPanel
          Left = 422
          Top = 0
          Width = 326
          Height = 466
          Align = alClient
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 1
          object lvCust: TRzListView
            Left = 0
            Top = 41
            Width = 326
            Height = 394
            Align = alClient
            Columns = <
              item
                Caption = '客户号'
                Width = 60
              end
              item
                Caption = '学工号'
                Width = 100
              end
              item
                Caption = '客户姓名'
                Width = 80
              end
              item
                Caption = '所在校区'
                Width = 65
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            MultiSelect = True
            RowSelect = True
            SmallImages = il1
            TabOrder = 1
            ViewStyle = vsReport
          end
          object pnl3: TPanel
            Left = 0
            Top = 0
            Width = 326
            Height = 41
            Align = alTop
            BevelOuter = bvNone
            Caption = '已选择的人员列表'
            Color = 16119543
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object Panel6: TPanel
            Left = 0
            Top = 435
            Width = 326
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object SpeedButton2: TSpeedButton
              Left = 2
              Top = 5
              Width = 60
              Height = 22
              Caption = '<-删除'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton2Click
            end
            object SpeedButton11: TSpeedButton
              Left = 70
              Top = 5
              Width = 68
              Height = 22
              Caption = '清空列表'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton11Click
            end
          end
        end
        object rzszpnl2: TRzSizePanel
          Left = 0
          Top = 0
          Width = 422
          Height = 466
          Color = 16119543
          HotSpotSizePercent = 100
          HotSpotVisible = True
          SizeBarWidth = 7
          TabOrder = 0
          UseGradients = True
          object lvCustUnAllot: TRzListView
            Left = 0
            Top = 95
            Width = 414
            Height = 315
            Align = alClient
            Checkboxes = True
            Columns = <
              item
                Caption = '客户号'
                Width = 60
              end
              item
                Caption = '学工号'
                Width = 100
              end
              item
                Caption = '客户姓名'
                Width = 80
              end
              item
                Caption = '所在校区'
                Width = 153
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            TabOrder = 1
            ViewStyle = vsReport
          end
          object pnl2: TPanel
            Left = 0
            Top = 0
            Width = 414
            Height = 95
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label6: TLabel
              Left = 212
              Top = 51
              Width = 48
              Height = 12
              Caption = '所在部门'
            end
            object Label3: TLabel
              Left = 12
              Top = 73
              Width = 48
              Height = 12
              Caption = '所属区域'
            end
            object Label10: TLabel
              Left = 212
              Top = 29
              Width = 48
              Height = 12
              Caption = '身份证号'
            end
            object Label5: TLabel
              Left = 24
              Top = 51
              Width = 36
              Height = 12
              Caption = '学工号'
            end
            object Label1: TLabel
              Left = 12
              Top = 29
              Width = 48
              Height = 12
              Caption = '客户类别'
            end
            object WVLabel2: TWVLabel
              Left = 24
              Top = 7
              Width = 36
              Height = 12
              Caption = '客户号'
            end
            object Label4: TLabel
              Left = 212
              Top = 7
              Width = 48
              Height = 12
              Caption = '客户姓名'
            end
            object WVComboBox6: TWVComboBox
              Tag = 1
              Left = 264
              Top = 46
              Width = 142
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 12
              TabOrder = 5
              WorkView = WorkView1
              FieldName = '联系人单位号'
              DataPresentType = 'IDOBJECTS'
              SeperatedStr = '-'
              AutoDropDown = False
              ItemsDataEntry = '*-22'
            end
            object WVComboBox3: TWVComboBox
              Tag = 1
              Left = 64
              Top = 68
              Width = 142
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 12
              TabOrder = 7
              WorkView = WorkView1
              FieldName = '客户所在区域'
              DataPresentType = 'IDOBJECTS'
              SeperatedStr = '-'
              AutoDropDown = False
              ItemsDataEntry = '*-27'
            end
            object WVEdit10: TWVEdit
              Tag = 1
              Left = 264
              Top = 24
              Width = 142
              Height = 20
              Color = clWhite
              ReadOnly = False
              TabOrder = 3
              Text = '<联系人身份证号>'
              WorkView = WorkView1
              FieldName = '联系人身份证号'
            end
            object WVEdit5: TWVEdit
              Tag = 1
              Left = 64
              Top = 46
              Width = 141
              Height = 20
              CharCase = ecUpperCase
              Color = clWhite
              ReadOnly = False
              TabOrder = 4
              Text = '<联系人学工号>'
              WorkView = WorkView1
              FieldName = '联系人学工号'
            end
            object WVComboBox1: TWVComboBox
              Tag = 1
              Left = 64
              Top = 24
              Width = 142
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 12
              TabOrder = 2
              WorkView = WorkView1
              FieldName = '客户类别'
              DataPresentType = 'IDOBJECTS'
              SeperatedStr = '-'
              AutoDropDown = False
              ItemsDataEntry = '*-34'
            end
            object edtCustNo: TWVEdit
              Left = 64
              Top = 2
              Width = 142
              Height = 20
              Color = clWhite
              MaxLength = 22
              ReadOnly = False
              TabOrder = 0
              Text = '<客户号>'
              WorkView = WorkView1
              FieldName = '客户号'
            end
            object WVEdit4: TWVEdit
              Tag = 1
              Left = 264
              Top = 2
              Width = 142
              Height = 20
              Color = clWhite
              ReadOnly = False
              TabOrder = 1
              Text = '<客户名称>'
              WorkView = WorkView1
              FieldName = '客户名称'
            end
            object btnCustQuery: TBitBtn
              Left = 330
              Top = 66
              Width = 75
              Height = 25
              Hint = '确认操作'
              Caption = '客户查询'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              TabOrder = 6
              OnClick = btnCustQueryClick
            end
          end
          object Panel3: TPanel
            Left = 0
            Top = 410
            Width = 414
            Height = 56
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 3
            object btnSelect: TSpeedButton
              Left = 353
              Top = 29
              Width = 60
              Height = 22
              Anchors = [akTop, akRight]
              Caption = '选择->'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = btnSelectClick
            end
            object SpeedButton8: TSpeedButton
              Left = 282
              Top = 29
              Width = 68
              Height = 22
              Anchors = [akTop, akRight]
              Caption = '清空列表'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton8Click
            end
            object SpeedButton9: TSpeedButton
              Left = 8
              Top = 29
              Width = 68
              Height = 22
              Caption = '选择文件'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton9Click
            end
            object btnImportQuery: TSpeedButton
              Left = 202
              Top = 29
              Width = 68
              Height = 22
              Caption = '导入查询'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = btnImportQueryClick
            end
            object lbl1: TLabel
              Left = 80
              Top = 34
              Width = 42
              Height = 14
              Caption = '表单：'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object SpeedButton1: TSpeedButton
              Left = 82
              Top = 4
              Width = 71
              Height = 22
              Anchors = [akTop, akRight]
              Caption = '失败信息'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton1Click
            end
            object edtSheet: TEdit
              Left = 117
              Top = 30
              Width = 81
              Height = 22
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
              Text = 'sheet1'
            end
            object chkCustUnAllot: TRzCheckBox
              Left = 13
              Top = 7
              Width = 57
              Height = 17
              Caption = '全选'
              FrameColor = 8409372
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              HighlightColor = 2203937
              HotTrack = True
              HotTrackColor = 3983359
              HotTrackColorType = htctActual
              ParentFont = False
              State = cbUnchecked
              TabOrder = 0
              OnClick = chkCustUnAllotClick
            end
          end
          object pnlImportError: TPanel
            Left = 146
            Top = 203
            Width = 271
            Height = 233
            Anchors = [akLeft, akBottom]
            Color = 16119543
            TabOrder = 2
            Visible = False
            object SpeedButton3: TSpeedButton
              Left = 202
              Top = 204
              Width = 64
              Height = 22
              Anchors = [akTop, akRight]
              Caption = '关 闭'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton3Click
            end
            object mmoImportError: TRzMemo
              Left = 1
              Top = 1
              Width = 269
              Height = 192
              Align = alTop
              ScrollBars = ssBoth
              TabOrder = 0
            end
          end
        end
      end
      object rztsGateGroup: TRzTabSheet
        Color = 16119543
        Caption = '门禁组选择'
        object pnl4: TPanel
          Left = 0
          Top = 0
          Width = 748
          Height = 466
          Align = alClient
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 0
          object Panel9: TPanel
            Left = 0
            Top = 0
            Width = 748
            Height = 65
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label8: TLabel
              Left = 6
              Top = 18
              Width = 60
              Height = 12
              Caption = '门禁组名称'
            end
            object Label22: TLabel
              Left = 6
              Top = 43
              Width = 364
              Height = 14
              Caption = '说明：如果此处不选择门禁组，则下一步一定要选择门禁机'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object WVEdit9: TWVEdit
              Left = 69
              Top = 14
              Width = 124
              Height = 20
              Color = clInfoBk
              MaxLength = 9
              ReadOnly = False
              TabOrder = 1
              Text = '<查询.门禁组名称>'
              WorkView = WorkView3
              FieldName = '查询.门禁组名称'
            end
            object btnGroupQuery: TBitBtn
              Left = 206
              Top = 11
              Width = 75
              Height = 25
              Hint = '确认操作'
              Caption = '组查询'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = btnGroupQueryClick
            end
          end
          object lvGateGroup: TRzListView
            Left = 0
            Top = 65
            Width = 748
            Height = 370
            Align = alClient
            Checkboxes = True
            Columns = <
              item
                Caption = '门禁组编号'
                Width = 80
              end
              item
                Caption = '门禁组名称'
                Width = 647
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            TabOrder = 1
            ViewStyle = vsReport
          end
          object Panel18: TPanel
            Left = 0
            Top = 435
            Width = 748
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object chkGateGroup: TRzCheckBox
              Left = 5
              Top = 7
              Width = 57
              Height = 17
              Caption = '全选'
              FrameColor = 8409372
              HighlightColor = 2203937
              HotTrack = True
              HotTrackColor = 3983359
              HotTrackColorType = htctActual
              State = cbUnchecked
              TabOrder = 0
              OnClick = chkGateGroupClick
            end
          end
        end
      end
      object rztsGate: TRzTabSheet
        Color = 16119543
        Caption = '门禁机选择'
        object Panel7: TPanel
          Left = 0
          Top = 0
          Width = 748
          Height = 466
          Align = alClient
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 0
          object Panel11: TPanel
            Left = 0
            Top = 0
            Width = 748
            Height = 81
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label7: TLabel
              Left = 74
              Top = 9
              Width = 48
              Height = 12
              Caption = '设备名称'
            end
            object Label11: TLabel
              Left = 74
              Top = 56
              Width = 48
              Height = 12
              Caption = '设备状态'
              Visible = False
            end
            object Label12: TLabel
              Left = 86
              Top = 34
              Width = 36
              Height = 12
              Caption = '子系统'
            end
            object Label14: TLabel
              Left = 458
              Top = 31
              Width = 72
              Height = 12
              Caption = '设备所在区域'
            end
            object Label15: TLabel
              Left = 242
              Top = 32
              Width = 72
              Height = 12
              Caption = '设备物理型号'
            end
            object Label16: TLabel
              Left = 482
              Top = 8
              Width = 48
              Height = 12
              Caption = '设备机型'
            end
            object Label18: TLabel
              Left = 254
              Top = 9
              Width = 60
              Height = 12
              Caption = '设备物理ID'
            end
            object Label21: TLabel
              Left = 246
              Top = 54
              Width = 308
              Height = 14
              Caption = '说明：如果已经选择了门禁组，门禁机可以不选择'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object WVEdit3: TWVEdit
              Left = 124
              Top = 5
              Width = 112
              Height = 20
              Color = clWhite
              ReadOnly = False
              TabOrder = 1
              Text = '<设备名称>'
              WorkView = WorkView2
              FieldName = '设备名称'
            end
            object WVComboBox5: TWVComboBox
              Left = 124
              Top = 52
              Width = 112
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 7
              Text = '<设备状态>'
              Visible = False
              WorkView = WorkView2
              FieldName = '设备状态'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*5'
            end
            object WVComboBox7: TWVComboBox
              Left = 124
              Top = 28
              Width = 112
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 4
              Text = '<所属子系统>'
              WorkView = WorkView2
              FieldName = '所属子系统'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*-32'
            end
            object cbbScode: TWVComboBox
              Left = 532
              Top = 4
              Width = 132
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 0
              Text = '<机型代码>'
              WorkView = WorkView2
              FieldName = '机型代码'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*47'
            end
            object WVComboBox8: TWVComboBox
              Left = 316
              Top = 28
              Width = 132
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 5
              Text = '<设备物理型号>'
              WorkView = WorkView2
              FieldName = '设备物理型号'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*-35'
            end
            object WVComboBox9: TWVComboBox
              Left = 532
              Top = 27
              Width = 132
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 3
              Text = '<设备所在区域>'
              WorkView = WorkView2
              FieldName = '设备所在区域'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*-28'
            end
            object WVEdit6: TWVEdit
              Left = 316
              Top = 5
              Width = 130
              Height = 20
              Color = clWhite
              ReadOnly = False
              TabOrder = 2
              Text = '<设备物理ID>'
              WorkView = WorkView2
              FieldName = '设备物理ID'
            end
            object btnEquQuery: TBitBtn
              Left = 588
              Top = 49
              Width = 75
              Height = 25
              Hint = '确认操作'
              Caption = '设备查询'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              TabOrder = 6
              OnClick = btnEquQueryClick
            end
          end
          object Panel12: TPanel
            Left = 0
            Top = 435
            Width = 748
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object chkGateUnAllot: TRzCheckBox
              Left = 5
              Top = 7
              Width = 57
              Height = 17
              Caption = '全选'
              FrameColor = 8409372
              HighlightColor = 2203937
              HotTrack = True
              HotTrackColor = 3983359
              HotTrackColorType = htctActual
              State = cbUnchecked
              TabOrder = 0
              OnClick = chkGateUnAllotClick
            end
          end
          object lvGate: TRzListView
            Left = 0
            Top = 81
            Width = 748
            Height = 354
            Align = alClient
            Checkboxes = True
            Columns = <
              item
                Caption = '门禁机编号'
                Width = 80
              end
              item
                Caption = '门禁机名称'
                Width = 647
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            TabOrder = 1
            ViewStyle = vsReport
          end
        end
      end
      object rztsHoliday: TRzTabSheet
        Color = 16119543
        Caption = '节假日/周选择'
        object rzszpnl1: TRzSizePanel
          Left = 0
          Top = 0
          Width = 354
          Height = 466
          Color = 16119543
          HotSpotSizePercent = 100
          HotSpotVisible = True
          SizeBarWidth = 7
          TabOrder = 0
          UseGradients = True
          object Panel14: TPanel
            Left = 0
            Top = 0
            Width = 346
            Height = 65
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label17: TLabel
              Left = 6
              Top = 18
              Width = 60
              Height = 12
              Caption = '节假日名称'
            end
            object Label9: TLabel
              Left = 6
              Top = 42
              Width = 252
              Height = 14
              Caption = '说明：节假日为可选，不选系统默认为空'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object WVEdit7: TWVEdit
              Left = 69
              Top = 14
              Width = 124
              Height = 20
              Color = clInfoBk
              MaxLength = 9
              ReadOnly = False
              TabOrder = 1
              Text = '<查询.节假日名>'
              WorkView = WorkView4
              FieldName = '查询.节假日名'
            end
            object btnHolidayQuery: TBitBtn
              Left = 216
              Top = 10
              Width = 90
              Height = 25
              Hint = '确认操作'
              Caption = '节假日查询'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = btnHolidayQueryClick
            end
          end
          object lvHoliday: TRzListView
            Left = 0
            Top = 65
            Width = 346
            Height = 370
            Align = alClient
            Columns = <
              item
                Caption = '节假日编号'
                Width = 80
              end
              item
                Caption = '节假日名称'
                Width = 245
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            SmallImages = il1
            TabOrder = 1
            ViewStyle = vsReport
            OnChange = lvHolidayChange
          end
          object Panel15: TPanel
            Left = 0
            Top = 435
            Width = 346
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object Label20: TLabel
              Left = 6
              Top = 10
              Width = 103
              Height = 14
              AutoSize = False
              Caption = '当前选择节假日：'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object lblHolidayID: TLabel
              Left = 110
              Top = 9
              Width = 35
              Height = 14
              AutoSize = False
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object lblHolidayName: TLabel
              Left = 150
              Top = 9
              Width = 7
              Height = 14
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object btnClearSele: TSpeedButton
              Left = 272
              Top = 5
              Width = 68
              Height = 22
              Caption = '清除选择'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              OnClick = btnClearSeleClick
            end
          end
        end
        object pnl5: TPanel
          Left = 354
          Top = 0
          Width = 394
          Height = 466
          Align = alClient
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 1
          object Panel16: TPanel
            Left = 0
            Top = 0
            Width = 394
            Height = 65
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label19: TLabel
              Left = 6
              Top = 18
              Width = 72
              Height = 12
              Caption = '周时间段名称'
            end
            object Label13: TLabel
              Left = 6
              Top = 42
              Width = 322
              Height = 14
              Caption = '说明：周时间段必须选择，不选则不能分配人员名单'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object WVEdit8: TWVEdit
              Left = 85
              Top = 14
              Width = 124
              Height = 20
              Color = clInfoBk
              MaxLength = 9
              ReadOnly = False
              TabOrder = 1
              Text = '<查询.时间段组名称>'
              WorkView = WorkView5
              FieldName = '查询.时间段组名称'
            end
            object btnWeekQuery: TBitBtn
              Left = 239
              Top = 11
              Width = 75
              Height = 25
              Hint = '确认操作'
              Caption = '周查询'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = btnWeekQueryClick
            end
          end
          object lvWeek: TRzListView
            Left = 0
            Top = 65
            Width = 394
            Height = 370
            Align = alClient
            Columns = <
              item
                Caption = '周时间段编号'
                Width = 100
              end
              item
                Caption = '周时间段名称'
                Width = 273
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            SmallImages = il1
            TabOrder = 1
            ViewStyle = vsReport
            OnChange = lvWeekChange
          end
          object Panel17: TPanel
            Left = 0
            Top = 435
            Width = 394
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object lblWeekName: TLabel
              Left = 150
              Top = 9
              Width = 7
              Height = 14
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object lblWeekId: TLabel
              Left = 112
              Top = 9
              Width = 31
              Height = 14
              AutoSize = False
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
            object Label23: TLabel
              Left = 6
              Top = 10
              Width = 103
              Height = 14
              AutoSize = False
              Caption = '当前选择周时间：'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '宋体'
              Font.Style = []
              ParentFont = False
            end
          end
        end
      end
      object rztsOk: TRzTabSheet
        Color = 16119543
        Caption = '分配信息'
        object pnl6: TPanel
          Left = 0
          Top = 427
          Width = 748
          Height = 39
          Align = alBottom
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 1
          object btnClear: TSpeedButton
            Left = 600
            Top = 8
            Width = 68
            Height = 22
            Anchors = [akTop, akRight]
            Caption = '清空信息'
            Flat = True
            Font.Charset = GB2312_CHARSET
            Font.Color = clNavy
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            OnClick = btnClearClick
          end
          object btnSaveAs: TSpeedButton
            Left = 672
            Top = 8
            Width = 68
            Height = 22
            Anchors = [akTop, akRight]
            Caption = '信息另存'
            Flat = True
            Font.Charset = GB2312_CHARSET
            Font.Color = clNavy
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            OnClick = btnSaveAsClick
          end
        end
        object mmoError: TRzMemo
          Left = 0
          Top = 0
          Width = 748
          Height = 427
          Align = alClient
          ReadOnly = True
          ScrollBars = ssBoth
          TabOrder = 0
          WordWrap = False
        end
      end
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 696
    Top = 480
    Width = 56
    Height = 27
    Align = alNone
    TabOrder = 2
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '时间段组编号'
          Visible = True
        end>
    end
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
        Name = '返回标志'
        Caption = '返回标志'
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
        Name = '周时间段'
        Caption = '周时间段'
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
        Name = '节假日'
        Caption = '节假日'
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
        Name = '门禁编号'
        Caption = '门禁编号'
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
        Name = '客户号'
        Caption = '客户号'
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
        Name = '标志'
        Caption = '标志'
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
        MonitorValueChangedFields = '|时间段组编号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 4
    Top = 415
  end
  inherited MainRequest: TWVRequest
    ID = '门禁人员名单分配'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回标志'
        FieldName = '返回标志'
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
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '节假日'
        FieldName = '节假日'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '门禁编号'
        FieldName = '门禁编号'
      end
      item
        ParamName = '周时间段'
        FieldName = '周时间段'
      end>
    Left = 40
    Top = 416
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 72
    Top = 416
  end
  inherited DataSource: TDataSource
    Left = 104
    Top = 416
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '设备查询门禁系统'
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
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end>
    Left = 40
    Top = 256
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
    Left = 4
    Top = 255
  end
  object WVRequest3: TWVRequest
    WorkView = WorkView3
    ID = '门禁组操作员查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '门禁组编号'
        FieldName = '查询.门禁组编号'
      end
      item
        ParamName = '门禁组名称'
        FieldName = '查询.门禁组名称'
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
    Left = 40
    Top = 296
  end
  object WorkView3: TWorkView
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
        Name = '查询.门禁组编号'
        Caption = '查询.门禁组编号'
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
        Name = '查询.门禁组名称'
        Caption = '查询.门禁组名称'
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
        MonitorValueChangedFields = '|查询.门禁组编号|查询.门禁组名称|查询.交易类型|'
      end
      item
        MonitorValueChangedFields = '|门禁组编号|'
      end>
    Left = 8
    Top = 296
  end
  object WVRequest4: TWVRequest
    WorkView = WorkView4
    ID = '节假日查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '节假日编号'
        FieldName = '查询.节假日编号'
      end
      item
        ParamName = '节假日名'
        FieldName = '查询.节假日名'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
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
    Left = 40
    Top = 336
  end
  object WorkView4: TWorkView
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
        Name = '查询.节假日编号'
        Caption = '查询.节假日编号'
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
        Name = '查询.节假日名'
        Caption = '查询.节假日名'
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
        Name = '节假日编号'
        Caption = '节假日编号'
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
        DataField = 'lvol0'
      end
      item
        Name = '节假日名'
        Caption = '节假日名'
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
        DataField = 'semail'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
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
        MonitorValueChangedFields = '|查询.节假日编号|查询.节假日名|查询.交易类型|'
      end
      item
        MonitorValueChangedFields = '|节假日编号|'
      end>
    Left = 8
    Top = 336
  end
  object WVRequest5: TWVRequest
    WorkView = WorkView5
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
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end>
    Left = 40
    Top = 368
  end
  object WorkView5: TWorkView
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
        Name = '查询.时间段组编号'
        Caption = '查询.时间段组编号'
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
        Name = '查询.时间段组名称'
        Caption = '查询.时间段组名称'
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
        Name = '查询.周一组编号'
        Caption = '查询.周一组编号'
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
        Name = '查询.周二组编号'
        Caption = '查询.周二组编号'
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
        Name = '查询.周三组编号'
        Caption = '查询.周三组编号'
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
        Name = '查询.周四组编号'
        Caption = '查询.周四组编号'
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
        Name = '查询.周五组编号'
        Caption = '查询.周五组编号'
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
        Name = '查询.周六组编号'
        Caption = '查询.周六组编号'
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
        Name = '查询.周日组编号'
        Caption = '查询.周日组编号'
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
        Name = '时间段组编号'
        Caption = '时间段组编号'
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
        DataField = 'lvol0'
      end
      item
        Name = '时间段组名'
        Caption = '时间段组名'
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
        DataField = 'semail'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
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
      end
      item
        Name = '周一组编号'
        Caption = '周一组编号'
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
        DataField = 'lvol1'
      end
      item
        Name = '周二组编号'
        Caption = '周二组编号'
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
        DataField = 'lvol2'
      end
      item
        Name = '周三组编号'
        Caption = '周三组编号'
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
        DataField = 'lvol3'
      end
      item
        Name = '周四组编号'
        Caption = '周四组编号'
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
        DataField = 'lvol4'
      end
      item
        Name = '周五组编号'
        Caption = '周五组编号'
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
        DataField = 'lvol5'
      end
      item
        Name = '周六组编号'
        Caption = '周六组编号'
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
        DataField = 'lvol6'
      end
      item
        Name = '周日组编号'
        Caption = '周日组编号'
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
        DataField = 'lvol7'
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
          '|查询.时间段组编号|查询.时间段组名称|查询.周一组编号|查询.周二组' +
          '编号|查询.周三组编号|查询.周四组编号|查询.周五组编号|查询.周六组' +
          '编号|查询.周日组编号|查询.标志|'
      end
      item
        MonitorValueChangedFields = 
          '|时间段组编号|时间段组名|标志|周一组编号|周二组编号|周三组编号|' +
          '周四组编号|周五组编号|周六组编号|周日组编号|'
      end>
    Left = 8
    Top = 368
  end
  object dlgOpen: TOpenDialog
    Left = 232
    Top = 416
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 192
    Top = 416
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\桌面\新建 Microsoft Office Access 应用程序.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 152
    Top = 416
  end
  object dlgSaveError: TSaveDialog
    Filter = '文本文件|*.txt'
    Left = 281
    Top = 415
  end
  object il1: TImageList
    Left = 129
    Top = 359
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '客户信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
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
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '客户名称'
        FieldName = '客户名称'
      end
      item
        ParamName = '客户状态'
        FieldName = '客户状态'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '客户所在区域'
      end
      item
        ParamName = '联系人学工号'
        FieldName = '联系人学工号'
      end
      item
        ParamName = '联系人单位号'
        FieldName = '联系人单位号'
      end
      item
        ParamName = '联系人性别'
        FieldName = '联系人性别'
      end
      item
        ParamName = '联系人民族'
        FieldName = '联系人民族'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = '联系人身份证号'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    AfterExec = MainRequestAfterExec
    Left = 40
    Top = 216
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = True
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
        DataField = '@Return'
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
        DataField = 'vsmess'
      end
      item
        Name = '客户号'
        Caption = '客户号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '客户名称'
        Caption = '客户名称'
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
        Name = '客户状态'
        Caption = '客户状态'
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
        Name = '客户类别'
        Caption = '客户类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '联系人单位号'
        Caption = '联系人单位号'
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
        Name = '联系人性别'
        Caption = '联系人性别'
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
        Name = '联系人学工号'
        Caption = '联系人学工号'
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
        Name = '联系人民族'
        Caption = '联系人民族'
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
        Name = '联系人身份证号'
        Caption = '联系人身份证号'
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
      end
      item
        Name = '客户所在区域'
        Caption = '客户所在区域'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '班级'
        Caption = '班级'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|客户类别|客户状态|地区|客户名称|联系人学号或员工号|联系人班级或' +
          '部门|联系人姓名|联系人性别|联系人民族代码|联系人身份证号|联系电' +
          '话|联系地址|注册时间|预计注销时间|'
      end>
    Left = 4
    Top = 215
  end
end

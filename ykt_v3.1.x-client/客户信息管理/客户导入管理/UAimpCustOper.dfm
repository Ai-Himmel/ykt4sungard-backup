inherited faqhimpCustOper: TfaqhimpCustOper
  Width = 773
  Height = 477
  Caption = '客户导入管理'
  inherited pcPages: TRzPageControl
    Width = 773
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 410
        Width = 769
        Height = 44
        TabOrder = 3
        object Label33: TLabel [0]
          Left = 262
          Top = 9
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 427
          Top = 1000
          Enabled = False
          TabOrder = 9
          Visible = False
        end
        inherited btnChange: TBitBtn [2]
          Left = 419
          Enabled = False
          TabOrder = 2
        end
        inherited btnQuery: TBitBtn [3]
          Left = 334
        end
        inherited btnDelete: TBitBtn
          Left = 504
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Width = 161
          TabOrder = 7
        end
        object btnCheck: TBitBtn
          Left = 677
          Top = 3
          Width = 79
          Height = 25
          Hint = '增加一个项目'
          Anchors = [akTop, akRight]
          Caption = '审核(&C)'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = btnCheckClick
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
        object pbStat: TProgressBar
          Left = 0
          Top = 34
          Width = 769
          Height = 10
          Align = alBottom
          Min = 0
          Max = 100
          TabOrder = 8
        end
        object btnPatchDel: TBitBtn
          Left = 591
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
          Left = 303
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
        Width = 769
      end
      inherited Grid: TRzDBGrid
        Top = 121
        Width = 769
        Height = 289
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'Sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '批次号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入顺序号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入操作员'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '学工号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户类别'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户类别名称'
            Width = 80
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
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户姓名'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '校区'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '所属部门'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '专业'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '班级'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '证件类型'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '证件号码'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '性别'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snation_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '国籍'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_type2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '民族'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '电子邮箱'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '电话'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '手机'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '地址'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spost_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '邮政编码'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '入校日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '预计离校日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Caption = '错误信息'
            Width = 150
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 769
        Height = 103
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label3: TLabel
          Left = 454
          Top = 10
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        object Label5: TLabel
          Left = 22
          Top = 34
          Width = 60
          Height = 12
          Caption = '导入操作员'
        end
        object Label6: TLabel
          Left = 46
          Top = 10
          Width = 36
          Height = 12
          Caption = '学工号'
        end
        object Label7: TLabel
          Left = 242
          Top = 34
          Width = 48
          Height = 12
          Caption = '客户类别'
        end
        object Label8: TLabel
          Left = 442
          Top = 34
          Width = 48
          Height = 12
          Caption = '收费类别'
        end
        object Label9: TLabel
          Left = 242
          Top = 10
          Width = 48
          Height = 12
          Caption = '客户姓名'
        end
        object Label10: TLabel
          Left = 58
          Top = 58
          Width = 24
          Height = 12
          Caption = '校区'
        end
        object Label11: TLabel
          Left = 242
          Top = 58
          Width = 48
          Height = 12
          Caption = '所属部门'
        end
        object Label12: TLabel
          Left = 442
          Top = 58
          Width = 48
          Height = 12
          Caption = '专业代码'
        end
        object Label13: TLabel
          Left = 58
          Top = 82
          Width = 24
          Height = 12
          Caption = '班级'
        end
        object Label14: TLabel
          Left = 242
          Top = 82
          Width = 48
          Height = 12
          Caption = '证件类型'
        end
        object Label15: TLabel
          Left = 442
          Top = 82
          Width = 48
          Height = 12
          Caption = '证件号码'
        end
        object WVEdit3: TWVEdit
          Left = 500
          Top = 6
          Width = 151
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.批次号>'
          WorkView = WorkView
          FieldName = '查询.批次号'
        end
        object WVEdit5: TWVEdit
          Left = 92
          Top = 31
          Width = 138
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 3
          Text = '<查询.导入操作员>'
          WorkView = WorkView
          FieldName = '查询.导入操作员'
        end
        object WVEdit6: TWVEdit
          Left = 92
          Top = 6
          Width = 138
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
          Left = 300
          Top = 6
          Width = 136
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.客户姓名>'
          WorkView = WorkView
          FieldName = '查询.客户姓名'
        end
        object WVEdit13: TWVEdit
          Left = 92
          Top = 78
          Width = 138
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 10
          Text = '<查询.班级>'
          WorkView = WorkView
          FieldName = '查询.班级'
        end
        object WVEdit15: TWVEdit
          Left = 500
          Top = 78
          Width = 151
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 11
          Text = '<查询.证件号码>'
          WorkView = WorkView
          FieldName = '查询.证件号码'
        end
        object cbbQFeeType: TWVComboBox
          Left = 500
          Top = 31
          Width = 151
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '查询.收费类别'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '-43'
        end
        object cbbQCustType: TWVComboBox
          Left = 300
          Top = 31
          Width = 136
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '查询.客户类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '-34'
        end
        object WVComboBox4: TWVComboBox
          Left = 92
          Top = 55
          Width = 138
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 7
          WorkView = WorkView
          FieldName = '查询.区域代码'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '-27'
        end
        object WVComboBox7: TWVComboBox
          Left = 300
          Top = 54
          Width = 136
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '查询.部门代码'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-22'
        end
        object WVComboBox6: TWVComboBox
          Left = 500
          Top = 55
          Width = 151
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '查询.专业代码'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-23'
        end
        object cbbQIdCardType: TWVComboBox
          Left = 300
          Top = 77
          Width = 136
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 9
          WorkView = WorkView
          FieldName = '查询.证件类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*87'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label1: TLabel [0]
        Left = 50
        Top = 44
        Width = 60
        Height = 12
        Caption = '客户姓名 *'
      end
      object Label4: TLabel [1]
        Left = 74
        Top = 84
        Width = 36
        Height = 12
        Caption = '校区 *'
      end
      object Label2: TLabel [2]
        Left = 294
        Top = 84
        Width = 48
        Height = 12
        Caption = '所属部门'
      end
      object Label17: TLabel [3]
        Left = 282
        Top = 44
        Width = 60
        Height = 12
        Caption = '收费类别 *'
      end
      object Label18: TLabel [4]
        Left = 570
        Top = 84
        Width = 24
        Height = 12
        Caption = '专业'
      end
      object Label16: TLabel [5]
        Left = 534
        Top = 44
        Width = 60
        Height = 12
        Caption = '客户类别 *'
      end
      object Label19: TLabel [6]
        Left = 570
        Top = 124
        Width = 24
        Height = 12
        Caption = '国籍'
      end
      object Label20: TLabel [7]
        Left = 318
        Top = 124
        Width = 24
        Height = 12
        Caption = '性别'
      end
      object Label21: TLabel [8]
        Left = 68
        Top = 124
        Width = 42
        Height = 12
        Caption = '学/工号'
      end
      object Label22: TLabel [9]
        Left = 86
        Top = 164
        Width = 24
        Height = 12
        Caption = '民族'
      end
      object Label23: TLabel [10]
        Left = 294
        Top = 164
        Width = 48
        Height = 12
        Caption = '证件类型'
      end
      object Label24: TLabel [11]
        Left = 546
        Top = 163
        Width = 48
        Height = 12
        Caption = '证件号码'
      end
      object Label25: TLabel [12]
        Left = 546
        Top = 203
        Width = 48
        Height = 12
        Caption = '电子邮箱'
      end
      object Label26: TLabel [13]
        Left = 294
        Top = 244
        Width = 48
        Height = 12
        Caption = '入校日期'
      end
      object Label27: TLabel [14]
        Left = 318
        Top = 204
        Width = 24
        Height = 12
        Caption = '手机'
      end
      object WVLabel2: TWVLabel [15]
        Left = 86
        Top = 244
        Width = 24
        Height = 12
        Caption = '班级'
      end
      object Label28: TLabel [16]
        Left = 86
        Top = 204
        Width = 24
        Height = 12
        Caption = '电话'
      end
      object Label29: TLabel [17]
        Left = 318
        Top = 285
        Width = 24
        Height = 12
        Caption = '地址'
      end
      object Label30: TLabel [18]
        Left = 522
        Top = 242
        Width = 72
        Height = 12
        Caption = '预计注销时间'
      end
      object Label31: TLabel [19]
        Left = 570
        Top = 282
        Width = 24
        Height = 12
        Caption = '邮编'
      end
      object Label32: TLabel [20]
        Left = 62
        Top = 421
        Width = 48
        Height = 12
        Caption = '客户号 *'
        Visible = False
      end
      object lbl1: TLabel [21]
        Left = 522
        Top = 18
        Width = 72
        Height = 12
        Caption = '客户类别名称'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 769
        TabOrder = 23
        inherited btnOK: TBitBtn
          Left = 597
        end
        inherited btnCancel: TBitBtn
          Left = 685
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtCustName: TWVEdit
        Left = 121
        Top = 40
        Width = 147
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<客户姓名>'
        WorkView = WorkView
        FieldName = '客户姓名'
        SynchronizeWhenExit = True
      end
      object cbbArea: TWVComboBox
        Left = 121
        Top = 80
        Width = 147
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '区域代码'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-27'
      end
      object cbbFeeType: TWVComboBox
        Left = 353
        Top = 40
        Width = 159
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '收费类别'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-43'
      end
      object WVComboBox3: TWVComboBox
        Left = 353
        Top = 79
        Width = 159
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '部门代码'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object WVComboBox5: TWVComboBox
        Left = 603
        Top = 78
        Width = 161
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '专业代码'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-23'
      end
      object cbbCustType: TWVComboBox
        Left = 603
        Top = 40
        Width = 161
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '客户类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-34'
      end
      object WVComboBox9: TWVComboBox
        Left = 603
        Top = 117
        Width = 161
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '国籍'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*89'
      end
      object WVComboBox10: TWVComboBox
        Left = 353
        Top = 118
        Width = 159
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '性别'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*39'
      end
      object WVEdit2: TWVEdit
        Left = 121
        Top = 119
        Width = 147
        Height = 20
        CharCase = ecUpperCase
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 9
        Text = '<学工号>'
        WorkView = WorkView
        FieldName = '学工号'
        SynchronizeWhenExit = True
      end
      object WVComboBox11: TWVComboBox
        Left = 121
        Top = 159
        Width = 147
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 12
        WorkView = WorkView
        FieldName = '民族'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2001'
      end
      object cbbIdCardType: TWVComboBox
        Left = 353
        Top = 158
        Width = 159
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 11
        WorkView = WorkView
        FieldName = '证件类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*87'
      end
      object WVEdit8: TWVEdit
        Left = 603
        Top = 197
        Width = 161
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 13
        Text = '<电子邮箱>'
        WorkView = WorkView
        FieldName = '电子邮箱'
        SynchronizeWhenExit = True
      end
      object WVEdit18: TWVEdit
        Left = 353
        Top = 199
        Width = 159
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 15
        Text = '<手机>'
        WorkView = WorkView
        FieldName = '手机'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Left = 353
        Top = 240
        Width = 159
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 18
        Text = '<入校日期>'
        WorkView = WorkView
        FieldName = '入校日期'
        SynchronizeWhenExit = True
      end
      object WVEdit12: TWVEdit
        Left = 121
        Top = 199
        Width = 147
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 14
        Text = '<电话>'
        WorkView = WorkView
        FieldName = '电话'
        SynchronizeWhenExit = True
      end
      object WVEdit7: TWVEdit
        Left = 121
        Top = 240
        Width = 147
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 17
        Text = '<班级>'
        WorkView = WorkView
        FieldName = '班级'
      end
      object WVEdit10: TWVEdit
        Left = 353
        Top = 280
        Width = 159
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 20
        Text = '<地址>'
        WorkView = WorkView
        FieldName = '地址'
        SynchronizeWhenExit = True
      end
      object WVEdit14: TWVEdit
        Left = 603
        Top = 278
        Width = 161
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 19
        Text = '<邮政编码>'
        WorkView = WorkView
        FieldName = '邮政编码'
        SynchronizeWhenExit = True
      end
      object edtDestoryDate: TWVEdit
        Left = 603
        Top = 238
        Width = 161
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 16
        Text = '<预计离校日期>'
        WorkView = WorkView
        FieldName = '预计离校日期'
        SynchronizeWhenExit = True
      end
      object WVEdit11: TWVEdit
        Left = 120
        Top = 344
        Width = 89
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 21
        Text = '<批次号>'
        Visible = False
        WorkView = WorkView
        FieldName = '批次号'
      end
      object edtIdCardNo: TWVEdit
        Left = 603
        Top = 157
        Width = 161
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 10
        Text = '<证件号码>'
        WorkView = WorkView
        FieldName = '证件号码'
        SynchronizeWhenExit = True
      end
      object WVEdit16: TWVEdit
        Left = 120
        Top = 384
        Width = 89
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 22
        Text = '<导入顺序号>'
        Visible = False
        WorkView = WorkView
        FieldName = '导入顺序号'
      end
      object WVEdit1: TWVEdit
        Left = 603
        Top = 17
        Width = 161
        Height = 15
        BorderStyle = bsNone
        ParentColor = True
        ReadOnly = True
        TabOrder = 0
        Text = '<客户类别名称>'
        WorkView = WorkView
        FieldName = '客户类别名称'
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
        Name = '查询.导入日期'
        Caption = '查询.导入日期'
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
        Name = '查询.导入顺序号'
        Caption = '查询.导入顺序号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.导入操作员'
        Caption = '查询.导入操作员'
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
        Name = '查询.客户类型'
        Caption = '查询.客户类型'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.收费类别'
        Caption = '查询.收费类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Name = '查询.客户姓名'
        Caption = '查询.客户姓名'
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
        Name = '查询.区域代码'
        Caption = '查询.区域代码'
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
        Name = '查询.部门代码'
        Caption = '查询.部门代码'
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
        Name = '查询.专业代码'
        Caption = '查询.专业代码'
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
        Name = '查询.班级'
        Caption = '查询.班级'
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
        Name = '查询.证件类型'
        Caption = '查询.证件类型'
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
        Name = '查询.证件号码'
        Caption = '查询.证件号码'
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
        Name = '查询.性别'
        Caption = '查询.性别'
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
        Name = '查询.国籍'
        Caption = '查询.国籍'
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
        Name = '查询.民族'
        Caption = '查询.民族'
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
        Name = '查询.电子邮箱'
        Caption = '查询.电子邮箱'
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
        Name = '查询.电话'
        Caption = '查询.电话'
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
        Name = '查询.手机'
        Caption = '查询.手机'
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
        Name = '查询.地址'
        Caption = '查询.地址'
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
        Name = '查询.邮政编码'
        Caption = '查询.邮政编码'
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
        Name = '查询.入校日期'
        Caption = '查询.入校日期'
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
        Name = '查询.预计离校日期'
        Caption = '查询.预计离校日期'
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
        Name = '导入日期'
        Caption = '导入日期'
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
        DataField = 'Sdate0'
      end
      item
        Name = '批次号'
        Caption = '批次号'
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
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Lvol4'
      end
      item
        Name = '导入操作员'
        Caption = '导入操作员'
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
        DataField = 'Semp_no'
      end
      item
        Name = '学工号'
        Caption = '学工号'
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
        DataField = 'spager'
      end
      item
        Name = '客户类型'
        Caption = '客户类型'
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
        DataField = 'lsafe_level2'
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
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
        Name = '客户姓名'
        Caption = '客户姓名'
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
        Name = '区域代码'
        Caption = '区域代码'
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
        DataField = 'sbranch_code0'
      end
      item
        Name = '部门代码'
        Caption = '部门代码'
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
        DataField = 'scert_no'
      end
      item
        Name = '专业代码'
        Caption = '专业代码'
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
        DataField = 'scert_no2'
      end
      item
        Name = '班级'
        Caption = '班级'
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
        DataField = 'scard1'
      end
      item
        Name = '证件类型'
        Caption = '证件类型'
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
        DataField = 'smarket_code2'
      end
      item
        Name = '证件号码'
        Caption = '证件号码'
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
        DataField = 'semail2'
      end
      item
        Name = '性别'
        Caption = '性别'
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
        DataField = 'smarket_code'
      end
      item
        Name = '国籍'
        Caption = '国籍'
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
        DataField = 'snation_code'
      end
      item
        Name = '民族'
        Caption = '民族'
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
        DataField = 'scust_type2'
      end
      item
        Name = '电子邮箱'
        Caption = '电子邮箱'
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
        Name = '电话'
        Caption = '电话'
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
        DataField = 'sphone'
      end
      item
        Name = '手机'
        Caption = '手机'
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
        DataField = 'sphone2'
      end
      item
        Name = '地址'
        Caption = '地址'
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
        DataField = 'scusttypes'
      end
      item
        Name = '邮政编码'
        Caption = '邮政编码'
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
        Name = '入校日期'
        Caption = '入校日期'
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
        DataField = 'Sdate1'
      end
      item
        Name = '预计离校日期'
        Caption = '预计离校日期'
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
        DataField = 'sdate2'
      end
      item
        Name = '客户类别名称'
        Caption = '客户类别名称'
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
        DataField = 'snote2'
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
    ID = '导入客户信息查询'
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
        ParamName = '导入日期'
        FieldName = '查询.导入日期'
      end
      item
        ParamName = '批次号'
        FieldName = '查询.批次号'
      end
      item
        ParamName = '导入顺序号'
        FieldName = '查询.导入顺序号'
      end
      item
        ParamName = '导入操作员'
        FieldName = '查询.导入操作员'
      end
      item
        ParamName = '学工号'
        FieldName = '查询.学工号'
      end
      item
        ParamName = '客户类型'
        FieldName = '查询.客户类型'
      end
      item
        ParamName = '收费类别'
        FieldName = '查询.收费类别'
      end
      item
        ParamName = '客户姓名'
        FieldName = '查询.客户姓名'
      end
      item
        ParamName = '区域代码'
        FieldName = '查询.区域代码'
      end
      item
        ParamName = '部门代码'
        FieldName = '查询.部门代码'
      end
      item
        ParamName = '专业代码'
        FieldName = '查询.专业代码'
      end
      item
        ParamName = '班级'
        FieldName = '查询.班级'
      end
      item
        ParamName = '证件类型'
        FieldName = '查询.证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '查询.证件号码'
      end
      item
        ParamName = '性别'
        FieldName = '查询.性别'
      end
      item
        ParamName = '国籍'
        FieldName = '查询.国籍'
      end
      item
        ParamName = '民族'
        FieldName = '查询.民族'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '查询.电子邮箱'
      end
      item
        ParamName = '电话'
        FieldName = '查询.电话'
      end
      item
        ParamName = '手机'
        FieldName = '查询.手机'
      end
      item
        ParamName = '地址'
        FieldName = '查询.地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '查询.邮政编码'
      end
      item
        ParamName = '入校日期'
        FieldName = '查询.入校日期'
      end
      item
        ParamName = '预计离校日期'
        FieldName = '查询.预计离校日期'
      end>
    Left = 464
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'scust_type2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'scert_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '89'
      end>
    Left = 396
  end
  inherited AddRequest: TWVRequest
    ID = '导入客户管理'
    Bindings = <
      item
        ParamName = '导入日期'
        FieldName = '导入日期'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '导入顺序号'
        FieldName = '导入顺序号'
      end
      item
        ParamName = '导入操作员'
        FieldName = '导入操作员'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '客户类型'
        FieldName = '客户类型'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
      end
      item
        ParamName = '区域代码'
        FieldName = '区域代码'
      end
      item
        ParamName = '部门代码'
        FieldName = '部门代码'
      end
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '性别'
        FieldName = '性别'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '民族'
        FieldName = '民族'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '入校日期'
        FieldName = '入校日期'
      end
      item
        ParamName = '预计离校日期'
        FieldName = '预计离校日期'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 368
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '导入客户管理'
    Bindings = <
      item
        ParamName = '导入日期'
        FieldName = '导入日期'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '导入顺序号'
        FieldName = '导入顺序号'
      end
      item
        ParamName = '导入操作员'
        FieldName = '导入操作员'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '客户类型'
        FieldName = '客户类型'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
      end
      item
        ParamName = '区域代码'
        FieldName = '区域代码'
      end
      item
        ParamName = '部门代码'
        FieldName = '部门代码'
      end
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '性别'
        FieldName = '性别'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '民族'
        FieldName = '民族'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '入校日期'
        FieldName = '入校日期'
      end
      item
        ParamName = '预计离校日期'
        FieldName = '预计离校日期'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 400
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '导入客户管理'
    Bindings = <
      item
        ParamName = '导入日期'
        FieldName = '导入日期'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '导入顺序号'
        FieldName = '导入顺序号'
      end
      item
        ParamName = '导入操作员'
        FieldName = '导入操作员'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '客户类型'
        FieldName = '客户类型'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
      end
      item
        ParamName = '区域代码'
        FieldName = '区域代码'
      end
      item
        ParamName = '部门代码'
        FieldName = '部门代码'
      end
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '性别'
        FieldName = '性别'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '民族'
        FieldName = '民族'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '入校日期'
        FieldName = '入校日期'
      end
      item
        ParamName = '预计离校日期'
        FieldName = '预计离校日期'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
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
  object WVRImpCheck: TWVRequest
    WorkView = WVImpCheck
    ID = '客户导入信息设置.审核'
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
    Left = 368
    Top = 208
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
    Left = 336
    Top = 208
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
    ID = '客户批量删除'
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

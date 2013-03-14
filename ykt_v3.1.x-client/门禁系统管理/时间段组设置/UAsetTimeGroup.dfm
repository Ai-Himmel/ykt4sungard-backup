inherited faqhsetTimeGroup: TfaqhsetTimeGroup
  Width = 748
  Height = 556
  Caption = '时间段组设置'
  inherited pcPages: TRzPageControl
    Width = 748
    Height = 556
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 497
        Width = 744
        Height = 36
        TabOrder = 4
        inherited btnAdd: TBitBtn [0]
          Left = 572
          Top = 6
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 658
          Top = 6
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 485
          Top = 6
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = -17
          Enabled = False
          TabOrder = 0
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 6
          TabOrder = 1
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 11
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 681
        Align = alNone
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 744
        Height = 464
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lcert_code'
            PickList.Strings = ()
            Title.Caption = '标识'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '时间段组名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '时间段一'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Caption = '时间段二'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Caption = '时间段三'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Caption = '时间段四'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = '时间段五'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol6'
            PickList.Strings = ()
            Title.Caption = '时间段六'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol7'
            PickList.Strings = ()
            Title.Caption = '时间段七'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol8'
            PickList.Strings = ()
            Title.Caption = '时间段八'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 744
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 30
          Top = 10
          Width = 60
          Height = 12
          Caption = '时间段名称'
        end
        object Label2: TLabel
          Left = 266
          Top = 10
          Width = 24
          Height = 12
          Caption = '标识'
        end
        object WVEdit1: TWVEdit
          Left = 100
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.时间段名称>'
          WorkView = WorkView
          FieldName = '查询.时间段名称'
        end
        object WVDigitalEdit2: TWVDigitalEdit
          Left = 300
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
          TabOrder = 1
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '查询.标识'
          SynchronizeByValue = True
        end
      end
      object pnl2: TPanel
        Left = 6
        Top = 239
        Width = 531
        Height = 267
        Anchors = [akLeft, akBottom]
        Color = 16119543
        TabOrder = 3
        Visible = False
        object RzDBGrid1: TRzDBGrid
          Left = 1
          Top = 1
          Width = 529
          Height = 232
          Align = alTop
          DataSource = DataSource2
          FixedColor = 15458000
          TabOrder = 0
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -12
          TitleFont.Name = '宋体'
          TitleFont.Style = []
          OnDrawColumnCell = RzDBGrid1DrawColumnCell
          OnKeyDown = GridKeyDown
          FrameColor = 12164479
          FrameStyle = fsGroove
          FrameVisible = True
          FixedLineColor = 12164479
          LineColor = clBackground
          Columns = <
            item
              Expanded = False
              FieldName = 'lvol0'
              Title.Caption = '时间段组编号'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'lvol2'
              Title.Caption = '时间段编号'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail'
              Title.Caption = '时间段组名'
              Width = 120
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail2'
              Title.Caption = '时间段名称'
              Width = 120
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate1'
              Title.Caption = '起始时间'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate2'
              Title.Caption = '结束时间'
              Width = 60
              Visible = True
            end>
        end
        object btnClose: TBitBtn
          Left = 446
          Top = 235
          Width = 75
          Height = 25
          Hint = '查询/刷新数据'
          Anchors = [akTop, akRight]
          Caption = '&C 关闭'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = btnCloseClick
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label6: TLabel [0]
        Left = 42
        Top = 5
        Width = 96
        Height = 16
        Caption = '时间段组设置'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel [1]
        Left = 138
        Top = 50
        Width = 28
        Height = 14
        Caption = '标识'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel [2]
        Left = 82
        Top = 79
        Width = 84
        Height = 14
        Caption = '时间段组名称'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 497
        Width = 744
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 572
          Caption = '保存设置'
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 660
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtName: TWVEdit
        Left = 172
        Top = 75
        Width = 181
        Height = 22
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
        Text = '<时间段名称>'
        WorkView = WorkView
        FieldName = '时间段名称'
        SynchronizeWhenExit = True
      end
      object edtNo: TWVDigitalEdit
        Left = 172
        Top = 46
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '标识'
        SynchronizeByValue = True
      end
      object rbTimeSet: TRzGroupBox
        Left = 88
        Top = 111
        Width = 337
        Height = 418
        Caption = '时间段设置'
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        object Label8: TLabel
          Left = 8
          Top = 27
          Width = 56
          Height = 14
          Caption = '时间段一'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object Label9: TLabel
          Left = 8
          Top = 76
          Width = 56
          Height = 14
          Caption = '时间段二'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object Label10: TLabel
          Left = 8
          Top = 125
          Width = 56
          Height = 14
          Caption = '时间段三'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object Label11: TLabel
          Left = 8
          Top = 174
          Width = 56
          Height = 14
          Caption = '时间段四'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object Label12: TLabel
          Left = 8
          Top = 222
          Width = 56
          Height = 14
          Caption = '时间段五'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object Label13: TLabel
          Left = 8
          Top = 271
          Width = 56
          Height = 14
          Caption = '时间段六'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object Label14: TLabel
          Left = 8
          Top = 320
          Width = 56
          Height = 14
          Caption = '时间段七'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object Label15: TLabel
          Left = 8
          Top = 369
          Width = 56
          Height = 14
          Caption = '时间段八'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblTime1: TLabel
          Tag = 1
          Left = 68
          Top = 48
          Width = 249
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblTime2: TLabel
          Tag = 2
          Left = 68
          Top = 97
          Width = 249
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblTime3: TLabel
          Tag = 3
          Left = 68
          Top = 145
          Width = 249
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblTime4: TLabel
          Tag = 4
          Left = 68
          Top = 194
          Width = 249
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblTime5: TLabel
          Tag = 5
          Left = 68
          Top = 243
          Width = 249
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblTime6: TLabel
          Tag = 6
          Left = 68
          Top = 292
          Width = 249
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblTime7: TLabel
          Tag = 7
          Left = 68
          Top = 340
          Width = 249
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object lblTime8: TLabel
          Tag = 8
          Left = 68
          Top = 389
          Width = 249
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object btn1: TSpeedButton
          Tag = 1
          Left = 248
          Top = 22
          Width = 21
          Height = 21
          Caption = '>>>'
          Flat = True
          OnClick = btn1Click
        end
        object btn2: TSpeedButton
          Tag = 2
          Left = 248
          Top = 71
          Width = 21
          Height = 21
          Caption = '>>>'
          Flat = True
          OnClick = btn2Click
        end
        object btn3: TSpeedButton
          Tag = 3
          Left = 248
          Top = 120
          Width = 21
          Height = 21
          Caption = '>>>'
          Flat = True
          OnClick = btn3Click
        end
        object btn4: TSpeedButton
          Tag = 4
          Left = 248
          Top = 169
          Width = 21
          Height = 21
          Caption = '>>>'
          Flat = True
          OnClick = btn4Click
        end
        object btn5: TSpeedButton
          Tag = 5
          Left = 248
          Top = 217
          Width = 21
          Height = 21
          Caption = '>>>'
          Flat = True
          OnClick = btn5Click
        end
        object btn6: TSpeedButton
          Tag = 6
          Left = 248
          Top = 266
          Width = 21
          Height = 21
          Caption = '>>>'
          Flat = True
          OnClick = btn6Click
        end
        object btn7: TSpeedButton
          Tag = 7
          Left = 248
          Top = 315
          Width = 21
          Height = 21
          Caption = '>>>'
          Flat = True
          OnClick = btn7Click
        end
        object btn8: TSpeedButton
          Tag = 8
          Left = 248
          Top = 364
          Width = 21
          Height = 21
          Caption = '>>>'
          Flat = True
          OnClick = btn8Click
        end
        object edtTime1: TWVEdit
          Tag = 1
          Left = 69
          Top = 22
          Width = 180
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<时间段一>'
          WorkView = WorkView
          FieldName = '时间段一'
        end
        object edtTime2: TWVEdit
          Tag = 2
          Left = 69
          Top = 71
          Width = 180
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 1
          Text = '<时间段二>'
          WorkView = WorkView
          FieldName = '时间段二'
        end
        object edtTime3: TWVEdit
          Tag = 3
          Left = 69
          Top = 120
          Width = 180
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 2
          Text = '<时间段三>'
          WorkView = WorkView
          FieldName = '时间段三'
        end
        object edtTime4: TWVEdit
          Tag = 4
          Left = 69
          Top = 169
          Width = 180
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 3
          Text = '<时间段四>'
          WorkView = WorkView
          FieldName = '时间段四'
        end
        object edtTime5: TWVEdit
          Tag = 5
          Left = 69
          Top = 217
          Width = 180
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 4
          Text = '<时间段五>'
          WorkView = WorkView
          FieldName = '时间段五'
        end
        object edtTime6: TWVEdit
          Tag = 6
          Left = 69
          Top = 266
          Width = 180
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 5
          Text = '<时间段六>'
          WorkView = WorkView
          FieldName = '时间段六'
        end
        object edtTime7: TWVEdit
          Tag = 7
          Left = 69
          Top = 315
          Width = 180
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 6
          Text = '<时间段七>'
          WorkView = WorkView
          FieldName = '时间段七'
        end
        object edtTime8: TWVEdit
          Tag = 8
          Left = 69
          Top = 364
          Width = 180
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 7
          Text = '<时间段八>'
          WorkView = WorkView
          FieldName = '时间段八'
        end
      end
      object pnlQuery: TPanel
        Left = 360
        Top = 133
        Width = 401
        Height = 385
        Color = 15458000
        TabOrder = 3
        Visible = False
        object Label16: TLabel
          Left = 182
          Top = 18
          Width = 60
          Height = 12
          Caption = '时间段名称'
        end
        object Label4: TLabel
          Left = 42
          Top = 18
          Width = 24
          Height = 12
          Caption = '标识'
        end
        object WVEdit2: TWVEdit
          Left = 244
          Top = 14
          Width = 93
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.时间段名称>'
          WorkView = WorkView1
          FieldName = '查询.时间段名称'
        end
        object pnl1: TPanel
          Left = 1
          Top = 352
          Width = 399
          Height = 32
          Align = alBottom
          BevelOuter = bvNone
          Color = 15458000
          TabOrder = 3
          object btnTimeQuery: TBitBtn
            Left = 144
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
            Left = 232
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
            Left = 320
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
          Width = 399
          Height = 312
          Align = alBottom
          DataSource = DataSource1
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
              FieldName = 'lvol0'
              Title.Caption = '标识'
              Width = 40
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail'
              Title.Caption = '时间段名称'
              Width = 200
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate0'
              Title.Caption = '开始日期'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate1'
              Title.Caption = '结束日期'
              Width = 60
              Visible = True
            end>
        end
        object WVEdit5: TWVEdit
          Left = 68
          Top = 14
          Width = 101
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.标识>'
          WorkView = WorkView1
          FieldName = '查询.标识'
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 548
    Top = 63
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
        Name = '查询.时间段名称'
        Caption = '查询.时间段名称'
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
        Name = '查询.标识'
        Caption = '查询.标识'
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
        Name = '交易类型'
        Caption = '交易类型'
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
        Name = '时间段名称'
        Caption = '时间段名称'
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
        Name = '时间段一'
        Caption = '时间段一'
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
        DataField = 'lvol1'
      end
      item
        Name = '时间段二'
        Caption = '时间段二'
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
        DataField = 'lvol2'
      end
      item
        Name = '时间段三'
        Caption = '时间段三'
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
        Name = '时间段四'
        Caption = '时间段四'
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
        DataField = 'lvol4'
      end
      item
        Name = '时间段五'
        Caption = '时间段五'
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
        Name = '时间段六'
        Caption = '时间段六'
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
        DataField = 'lvol6'
      end
      item
        Name = '时间段七'
        Caption = '时间段七'
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
        DataField = 'lvol7'
      end
      item
        Name = '时间段八'
        Caption = '时间段八'
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
        DataField = 'lvol8'
      end
      item
        Name = '标识'
        Caption = '标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lcert_code'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.时间段名称|查询.标识|查询.交易类型|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|时间段名称|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 464
    Top = 24
  end
  inherited QueryRequest: TWVRequest
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
    Left = 624
    Top = 24
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end
      item
        FieldName = 'lvol6'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end
      item
        FieldName = 'lvol8'
        DataPresentType = 'idobjects'
        DataPresentParam = '-51'
      end>
    Left = 516
    Top = 63
  end
  inherited AddRequest: TWVRequest
    ID = '时间段组设置'
    Bindings = <
      item
        ParamName = '时间段名称'
        FieldName = '时间段名称'
      end
      item
        ParamName = '标识'
        FieldName = '标识'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '时间段一'
        FieldName = '时间段一'
      end
      item
        ParamName = '时间段二'
        FieldName = '时间段二'
      end
      item
        ParamName = '时间段三'
        FieldName = '时间段三'
      end
      item
        ParamName = '时间段四'
        FieldName = '时间段四'
      end
      item
        ParamName = '时间段五'
        FieldName = '时间段五'
      end
      item
        ParamName = '时间段六'
        FieldName = '时间段六'
      end
      item
        ParamName = '时间段七'
        FieldName = '时间段七'
      end
      item
        ParamName = '时间段八'
        FieldName = '时间段八'
      end>
    Left = 504
    Top = 24
  end
  inherited DeleteRequest: TWVRequest
    ID = '时间段组设置'
    Bindings = <
      item
        ParamName = '时间段名称'
        FieldName = '时间段名称'
      end
      item
        ParamName = '标识'
        FieldName = '标识'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 544
    Top = 24
  end
  inherited ChangeRequest: TWVRequest
    ID = '时间段组设置'
    Bindings = <
      item
        ParamName = '时间段名称'
        FieldName = '时间段名称'
      end
      item
        ParamName = '标识'
        FieldName = '标识'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '时间段一'
        FieldName = '时间段一'
      end
      item
        ParamName = '时间段二'
        FieldName = '时间段二'
      end
      item
        ParamName = '时间段三'
        FieldName = '时间段三'
      end
      item
        ParamName = '时间段四'
        FieldName = '时间段四'
      end
      item
        ParamName = '时间段五'
        FieldName = '时间段五'
      end
      item
        ParamName = '时间段六'
        FieldName = '时间段六'
      end
      item
        ParamName = '时间段七'
        FieldName = '时间段七'
      end
      item
        ParamName = '时间段八'
        FieldName = '时间段八'
      end>
    Left = 584
    Top = 24
  end
  inherited WVDataSource: TWVDataSource
    Left = 628
    Top = 63
  end
  inherited alDatasetActions: TActionList
    Left = 588
    Top = 68
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '时间段参数查询'
    Bindings = <
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
        ParamName = '开始时间'
        FieldName = '查询.开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '查询.结束时间'
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
  object WorkView1: TWorkView
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
        Name = '查询.开始时间'
        Caption = '查询.开始时间'
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
        Name = '查询.结束时间'
        Caption = '查询.结束时间'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.时间段名称|查询.开始时间|查询.结束时间|查询.标识|查询.交易' +
          '类型|'
      end
      item
        MonitorValueChangedFields = '|时间段名称|开始时间|结束时间|'
      end>
    Left = 376
    Top = 280
  end
  object DataSource1: TDataSource
    OnStateChange = DataSourceStateChange
    OnDataChange = DataSourceDataChange
    Left = 444
    Top = 279
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView1
    FieldName = '查询结果集'
    Bindings = <>
    HideUnbindingFields = False
    Left = 412
    Top = 279
  end
  object WorkView2: TWorkView
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
      end
      item
        Name = '星期'
        Caption = '星期'
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
        MonitorValueChangedFields = '|时间段组编号|'
      end>
    Left = 148
    Top = 295
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '时间段组详细情况查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '时间段组编号'
        FieldName = '时间段组编号'
      end
      item
        ParamName = '星期'
        FieldName = '星期'
      end>
    Left = 184
    Top = 296
  end
  object DataSource2: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 248
    Top = 296
  end
  object WVDBBinder: TWVDBBinder
    DataSource = DataSource2
    WorkView = WorkView2
    FieldName = '查询结果集'
    Bindings = <>
    HideUnbindingFields = False
    Left = 216
    Top = 296
  end
end

inherited faqhsetTimeGroup: TfaqhsetTimeGroup
  Width = 748
  Height = 556
  Caption = 'ʱ���������'
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
            Title.Caption = '��ʶ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ʱ���������'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = 'ʱ���һ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Caption = 'ʱ��ζ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Caption = 'ʱ�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Caption = 'ʱ�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = 'ʱ�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol6'
            PickList.Strings = ()
            Title.Caption = 'ʱ�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol7'
            PickList.Strings = ()
            Title.Caption = 'ʱ�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol8'
            PickList.Strings = ()
            Title.Caption = 'ʱ��ΰ�'
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
          Caption = 'ʱ�������'
        end
        object Label2: TLabel
          Left = 266
          Top = 10
          Width = 24
          Height = 12
          Caption = '��ʶ'
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
          Text = '<��ѯ.ʱ�������>'
          WorkView = WorkView
          FieldName = '��ѯ.ʱ�������'
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
          FieldName = '��ѯ.��ʶ'
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
          TitleFont.Name = '����'
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
              Title.Caption = 'ʱ�������'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'lvol2'
              Title.Caption = 'ʱ��α��'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail'
              Title.Caption = 'ʱ�������'
              Width = 120
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail2'
              Title.Caption = 'ʱ�������'
              Width = 120
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate1'
              Title.Caption = '��ʼʱ��'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate2'
              Title.Caption = '����ʱ��'
              Width = 60
              Visible = True
            end>
        end
        object btnClose: TBitBtn
          Left = 446
          Top = 235
          Width = 75
          Height = 25
          Hint = '��ѯ/ˢ������'
          Anchors = [akTop, akRight]
          Caption = '&C �ر�'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
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
        Caption = 'ʱ���������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel [1]
        Left = 138
        Top = 50
        Width = 28
        Height = 14
        Caption = '��ʶ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel [2]
        Left = 82
        Top = 79
        Width = 84
        Height = 14
        Caption = 'ʱ���������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 497
        Width = 744
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 572
          Caption = '��������'
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
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
        Text = '<ʱ�������>'
        WorkView = WorkView
        FieldName = 'ʱ�������'
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
        Font.Name = '����'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '��ʶ'
        SynchronizeByValue = True
      end
      object rbTimeSet: TRzGroupBox
        Left = 88
        Top = 111
        Width = 337
        Height = 418
        Caption = 'ʱ�������'
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        object Label8: TLabel
          Left = 8
          Top = 27
          Width = 56
          Height = 14
          Caption = 'ʱ���һ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label9: TLabel
          Left = 8
          Top = 76
          Width = 56
          Height = 14
          Caption = 'ʱ��ζ�'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label10: TLabel
          Left = 8
          Top = 125
          Width = 56
          Height = 14
          Caption = 'ʱ�����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label11: TLabel
          Left = 8
          Top = 174
          Width = 56
          Height = 14
          Caption = 'ʱ�����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label12: TLabel
          Left = 8
          Top = 222
          Width = 56
          Height = 14
          Caption = 'ʱ�����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label13: TLabel
          Left = 8
          Top = 271
          Width = 56
          Height = 14
          Caption = 'ʱ�����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label14: TLabel
          Left = 8
          Top = 320
          Width = 56
          Height = 14
          Caption = 'ʱ�����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label15: TLabel
          Left = 8
          Top = 369
          Width = 56
          Height = 14
          Caption = 'ʱ��ΰ�'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
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
          Font.Name = '����'
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
          Font.Name = '����'
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
          Font.Name = '����'
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
          Font.Name = '����'
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
          Font.Name = '����'
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
          Font.Name = '����'
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
          Font.Name = '����'
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
          Font.Name = '����'
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
          Text = '<ʱ���һ>'
          WorkView = WorkView
          FieldName = 'ʱ���һ'
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
          Text = '<ʱ��ζ�>'
          WorkView = WorkView
          FieldName = 'ʱ��ζ�'
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
          Text = '<ʱ�����>'
          WorkView = WorkView
          FieldName = 'ʱ�����'
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
          Text = '<ʱ�����>'
          WorkView = WorkView
          FieldName = 'ʱ�����'
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
          Text = '<ʱ�����>'
          WorkView = WorkView
          FieldName = 'ʱ�����'
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
          Text = '<ʱ�����>'
          WorkView = WorkView
          FieldName = 'ʱ�����'
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
          Text = '<ʱ�����>'
          WorkView = WorkView
          FieldName = 'ʱ�����'
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
          Text = '<ʱ��ΰ�>'
          WorkView = WorkView
          FieldName = 'ʱ��ΰ�'
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
          Caption = 'ʱ�������'
        end
        object Label4: TLabel
          Left = 42
          Top = 18
          Width = 24
          Height = 12
          Caption = '��ʶ'
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
          Text = '<��ѯ.ʱ�������>'
          WorkView = WorkView1
          FieldName = '��ѯ.ʱ�������'
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
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = '�顡ѯ'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
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
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = 'ѡ����'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
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
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = 'ȡ����'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
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
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = '��  ��'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
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
          TitleFont.Name = '����'
          TitleFont.Style = []
          OnDblClick = dbgrd1DblClick
          Columns = <
            item
              Expanded = False
              FieldName = 'lvol0'
              Title.Caption = '��ʶ'
              Width = 40
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail'
              Title.Caption = 'ʱ�������'
              Width = 200
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate0'
              Title.Caption = '��ʼ����'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate1'
              Title.Caption = '��������'
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
          Text = '<��ѯ.��ʶ>'
          WorkView = WorkView1
          FieldName = '��ѯ.��ʶ'
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
        Name = '������'
        Caption = '������'
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
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        Name = '��ѯ�����'
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
        Name = '�������.����'
        Caption = '�������.����'
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
        Name = '�������.ɾ��'
        Caption = '�������.ɾ��'
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
        Name = '�������.�޸�'
        Caption = '�������.�޸�'
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
        Name = '��ѯ.ʱ�������'
        Caption = '��ѯ.ʱ�������'
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
        Name = '��ѯ.��ʶ'
        Caption = '��ѯ.��ʶ'
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
        Name = '��������'
        Caption = '��������'
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
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        Name = 'ʱ���һ'
        Caption = 'ʱ���һ'
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
        Name = 'ʱ��ζ�'
        Caption = 'ʱ��ζ�'
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
        Name = 'ʱ�����'
        Caption = 'ʱ�����'
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
        Name = 'ʱ�����'
        Caption = 'ʱ�����'
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
        Name = 'ʱ�����'
        Caption = 'ʱ�����'
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
        Name = 'ʱ�����'
        Caption = 'ʱ�����'
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
        Name = 'ʱ�����'
        Caption = 'ʱ�����'
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
        Name = 'ʱ��ΰ�'
        Caption = 'ʱ��ΰ�'
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
        Name = '��ʶ'
        Caption = '��ʶ'
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
        MonitorValueChangedFields = '|��ѯ.ʱ�������|��ѯ.��ʶ|��ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|ʱ�������|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 464
    Top = 24
  end
  inherited QueryRequest: TWVRequest
    ID = 'ʱ������ѯ'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʱ�������'
        FieldName = '��ѯ.ʱ�������'
      end
      item
        ParamName = '��ʶ'
        FieldName = '��ѯ.��ʶ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 624
    Top = 24
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
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
    ID = 'ʱ���������'
    Bindings = <
      item
        ParamName = 'ʱ�������'
        FieldName = 'ʱ�������'
      end
      item
        ParamName = '��ʶ'
        FieldName = '��ʶ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ʱ���һ'
        FieldName = 'ʱ���һ'
      end
      item
        ParamName = 'ʱ��ζ�'
        FieldName = 'ʱ��ζ�'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ��ΰ�'
        FieldName = 'ʱ��ΰ�'
      end>
    Left = 504
    Top = 24
  end
  inherited DeleteRequest: TWVRequest
    ID = 'ʱ���������'
    Bindings = <
      item
        ParamName = 'ʱ�������'
        FieldName = 'ʱ�������'
      end
      item
        ParamName = '��ʶ'
        FieldName = '��ʶ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 544
    Top = 24
  end
  inherited ChangeRequest: TWVRequest
    ID = 'ʱ���������'
    Bindings = <
      item
        ParamName = 'ʱ�������'
        FieldName = 'ʱ�������'
      end
      item
        ParamName = '��ʶ'
        FieldName = '��ʶ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ʱ���һ'
        FieldName = 'ʱ���һ'
      end
      item
        ParamName = 'ʱ��ζ�'
        FieldName = 'ʱ��ζ�'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'ʱ�����'
      end
      item
        ParamName = 'ʱ��ΰ�'
        FieldName = 'ʱ��ΰ�'
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
    ID = 'ʱ��β�����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʱ�������'
        FieldName = '��ѯ.ʱ�������'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = '��ѯ.��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '��ѯ.����ʱ��'
      end
      item
        ParamName = '��ʶ'
        FieldName = '��ѯ.��ʶ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    AfterExec = CheckReturnData
    Left = 480
    Top = 280
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
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
        Name = '�������.����'
        Caption = '�������.����'
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
        Name = '�������.ɾ��'
        Caption = '�������.ɾ��'
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
        Name = '�������.�޸�'
        Caption = '�������.�޸�'
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
        Name = '��ѯ.ʱ�������'
        Caption = '��ѯ.ʱ�������'
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
        Name = '��ѯ.��ʼʱ��'
        Caption = '��ѯ.��ʼʱ��'
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
        Name = '��ѯ.����ʱ��'
        Caption = '��ѯ.����ʱ��'
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
        Name = '��ѯ.��ʶ'
        Caption = '��ѯ.��ʶ'
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
        Name = '��������'
        Caption = '��������'
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
          '|��ѯ.ʱ�������|��ѯ.��ʼʱ��|��ѯ.����ʱ��|��ѯ.��ʶ|��ѯ.����' +
          '����|'
      end
      item
        MonitorValueChangedFields = '|ʱ�������|��ʼʱ��|����ʱ��|'
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
    FieldName = '��ѯ�����'
    Bindings = <>
    HideUnbindingFields = False
    Left = 412
    Top = 279
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
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
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        Name = '����'
        Caption = '����'
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
        MonitorValueChangedFields = '|ʱ�������|'
      end>
    Left = 148
    Top = 295
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = 'ʱ�������ϸ�����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'ʱ�������'
      end
      item
        ParamName = '����'
        FieldName = '����'
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
    FieldName = '��ѯ�����'
    Bindings = <>
    HideUnbindingFields = False
    Left = 216
    Top = 296
  end
end

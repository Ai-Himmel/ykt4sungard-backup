inherited faqhsetSmartTermList: TfaqhsetSmartTermList
  Width = 803
  Height = 623
  inherited UIPanel1: TUIPanel
    Top = 587
    Width = 803
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 704
      Top = 6
      Width = 89
      Caption = '�·�����'
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
    inherited btnPrint: TBitBtn
      Left = 185
      Top = 7
      Caption = '��������'
      Enabled = True
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 803
    inherited Image1: TImage
      Width = 803
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 803
    Height = 569
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object btnAdd: TSpeedButton
      Left = 384
      Top = 224
      Width = 57
      Height = 25
      Hint = '������Ա����'
      Caption = '>>>'
      Flat = True
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnAddClick
    end
    object btnDelete: TSpeedButton
      Left = 384
      Top = 280
      Width = 57
      Height = 25
      Hint = 'ɾ���ѷ������Ա����'
      Caption = '<<<'
      Flat = True
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnDeleteClick
    end
    object rb1: TRzGroupBox
      Left = 0
      Top = 16
      Width = 377
      Height = 521
      Caption = '��������Ա����'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object lvUnAllot: TRzListView
        Left = 1
        Top = 153
        Width = 375
        Height = 367
        Align = alClient
        Checkboxes = True
        Color = 16184303
        Columns = <
          item
            Caption = '����'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = '����'
            Width = 80
          end
          item
            Caption = 'ѧ����'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = '�����'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = '�ͻ����'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = '�շ����'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = 'Ժϵ'
            Width = 120
          end
          item
            Alignment = taCenter
            Caption = 'רҵ'
            Width = 183
          end>
        ColumnClick = False
        FlatScrollBars = True
        FrameColor = clInactiveCaption
        FrameHotTrack = True
        FrameVisible = True
        GridLines = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 1
        ViewStyle = vsReport
        OnCustomDrawItem = lvUnAllotCustomDrawItem
      end
      object pnl1: TPanel
        Left = 1
        Top = 15
        Width = 375
        Height = 138
        Align = alTop
        BevelOuter = bvNone
        Color = 16184303
        TabOrder = 0
        object Label11: TLabel
          Left = 34
          Top = 13
          Width = 28
          Height = 14
          Caption = 'Ժϵ'
        end
        object Label6: TLabel
          Left = 34
          Top = 37
          Width = 28
          Height = 14
          Caption = 'רҵ'
        end
        object Label1: TLabel
          Left = 6
          Top = 61
          Width = 56
          Height = 14
          Caption = '�ͻ����'
        end
        object Label10: TLabel
          Left = 20
          Top = 85
          Width = 42
          Height = 14
          Caption = '������'
        end
        object lbl2: TLabel
          Left = 6
          Top = 109
          Width = 56
          Height = 14
          Caption = '�豸���'
        end
        object Label9: TLabel
          Left = 242
          Top = 87
          Width = 28
          Height = 14
          Caption = '����'
        end
        object Label7: TLabel
          Left = 228
          Top = 63
          Width = 42
          Height = 14
          Caption = '�ͻ���'
        end
        object Label3: TLabel
          Left = 242
          Top = 39
          Width = 28
          Height = 14
          Caption = '����'
        end
        object Label5: TLabel
          Left = 221
          Top = 15
          Width = 49
          Height = 14
          Caption = 'ѧ/����'
        end
        object btnUnQuery: TSpeedButton
          Left = 306
          Top = 107
          Width = 63
          Height = 25
          Caption = '�� ѯ'
          Flat = True
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          OnClick = btnUnQueryClick
        end
        object cbbDept: TWVComboBox
          Left = 66
          Top = 9
          Width = 150
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 0
          WorkView = WorkView
          FieldName = 'Ժϵ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-22'
        end
        object cbbSpec: TWVComboBox
          Left = 66
          Top = 33
          Width = 150
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 2
          WorkView = WorkView
          FieldName = 'רҵ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-23'
        end
        object cbbCustType: TWVComboBox
          Left = 66
          Top = 57
          Width = 150
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 4
          WorkView = WorkView
          FieldName = '�ͻ����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-34'
        end
        object cbbCardType: TWVComboBox
          Left = 65
          Top = 81
          Width = 151
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 6
          WorkView = WorkView
          FieldName = '������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*18'
        end
        object cbbDeviceId: TWVComboBox
          Left = 66
          Top = 105
          Width = 150
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 8
          WorkView = WorkView
          FieldName = '�ֳֻ����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-49'
        end
        object edtCardNo: TWVEdit
          Left = 271
          Top = 82
          Width = 98
          Height = 22
          Color = clInfoBk
          MaxLength = 22
          ReadOnly = False
          TabOrder = 7
          Text = '<����>'
          WorkView = WorkView
          FieldName = '����'
        end
        object edtCustNo: TWVEdit
          Left = 271
          Top = 58
          Width = 98
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 5
          Text = '<�ͻ���>'
          WorkView = WorkView
          FieldName = '�ͻ���'
        end
        object edtName: TWVEdit
          Left = 271
          Top = 34
          Width = 98
          Height = 22
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<����>'
          WorkView = WorkView
          FieldName = '����'
        end
        object edtNo: TWVEdit
          Left = 271
          Top = 10
          Width = 98
          Height = 22
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<ѧ����>'
          WorkView = WorkView
          FieldName = 'ѧ����'
        end
      end
    end
    object rb2: TRzGroupBox
      Left = 448
      Top = 16
      Width = 353
      Height = 521
      Caption = '�ѷ�����Ա����'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object lvAllot: TRzListView
        Left = 1
        Top = 153
        Width = 351
        Height = 367
        Align = alClient
        Checkboxes = True
        Color = 16184303
        Columns = <
          item
            Caption = '����'
            Width = 100
          end
          item
            Alignment = taCenter
            Caption = '����'
            Width = 60
          end
          item
            Caption = 'ѧ����'
            Width = 80
          end
          item
            Caption = '��ɾ״̬'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = '�ͻ����'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = '�շ����'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = '����У��'
            Width = 120
          end
          item
            Alignment = taCenter
            Caption = 'Ժϵ'
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = 'רҵ'
            Width = 80
          end>
        ColumnClick = False
        FlatScrollBars = True
        FrameColor = clInactiveCaption
        FrameHotTrack = True
        FrameVisible = True
        GridLines = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 1
        ViewStyle = vsReport
      end
      object pnl2: TPanel
        Left = 1
        Top = 15
        Width = 351
        Height = 138
        Align = alTop
        BevelOuter = bvNone
        Color = 16184303
        TabOrder = 0
        object Label2: TLabel
          Left = 6
          Top = 15
          Width = 56
          Height = 14
          Caption = '����У��'
        end
        object Label8: TLabel
          Left = 7
          Top = 111
          Width = 56
          Height = 14
          Caption = '�豸���'
        end
        object Label12: TLabel
          Left = 6
          Top = 39
          Width = 56
          Height = 14
          Caption = '�ͻ����'
        end
        object Label13: TLabel
          Left = 6
          Top = 63
          Width = 56
          Height = 14
          Caption = '��ɾ״̬'
        end
        object Label14: TLabel
          Left = 6
          Top = 87
          Width = 56
          Height = 14
          Caption = '����״̬'
        end
        object Label15: TLabel
          Left = 226
          Top = 87
          Width = 28
          Height = 14
          Caption = '����'
        end
        object Label16: TLabel
          Left = 212
          Top = 63
          Width = 42
          Height = 14
          Caption = '�ͻ���'
        end
        object Label17: TLabel
          Left = 226
          Top = 39
          Width = 28
          Height = 14
          Caption = '����'
        end
        object Label18: TLabel
          Left = 205
          Top = 15
          Width = 49
          Height = 14
          Caption = 'ѧ/����'
        end
        object btnAllQuery: TSpeedButton
          Left = 280
          Top = 107
          Width = 65
          Height = 25
          Caption = '�� ѯ'
          Flat = True
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          OnClick = btnAllQueryClick
        end
        object cbbArea: TWVComboBox
          Left = 65
          Top = 9
          Width = 139
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 0
          WorkView = WorkView1
          FieldName = '����У��'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-27'
        end
        object cbbgroup: TWVComboBox
          Left = 65
          Top = 105
          Width = 139
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 8
          OnChange = cbbgroupChange
          WorkView = WorkView1
          FieldName = '�豸���'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '-49'
        end
        object cbbCust: TWVComboBox
          Left = 65
          Top = 33
          Width = 139
          Height = 22
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 14
          TabOrder = 2
          WorkView = WorkView1
          FieldName = '�ͻ����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-34'
        end
        object cbbStatus: TWVComboBox
          Left = 65
          Top = 57
          Width = 139
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 4
          WorkView = WorkView1
          FieldName = '״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*67'
        end
        object cbbStat: TWVComboBox
          Left = 65
          Top = 81
          Width = 139
          Height = 22
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 14
          TabOrder = 6
          WorkView = WorkView1
          FieldName = '����״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*68'
        end
        object WVEdit4: TWVEdit
          Left = 254
          Top = 81
          Width = 92
          Height = 22
          Color = clInfoBk
          MaxLength = 22
          ReadOnly = False
          TabOrder = 7
          Text = '<����>'
          WorkView = WorkView1
          FieldName = '����'
        end
        object WVEdit1: TWVEdit
          Left = 254
          Top = 57
          Width = 92
          Height = 22
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 5
          Text = '<�ͻ���>'
          WorkView = WorkView1
          FieldName = '�ͻ���'
        end
        object WVEdit2: TWVEdit
          Left = 254
          Top = 33
          Width = 92
          Height = 22
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<����>'
          WorkView = WorkView1
          FieldName = '����'
        end
        object WVEdit3: TWVEdit
          Left = 254
          Top = 9
          Width = 92
          Height = 22
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<ѧ����>'
          WorkView = WorkView1
          FieldName = 'ѧ����'
        end
      end
    end
    object chkSelectAll: TRzCheckBox
      Left = 5
      Top = 545
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 3
      OnClick = chkSelectAllClick
    end
    object chkDelSelectAll: TRzCheckBox
      Left = 452
      Top = 544
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 2
      OnClick = chkDelSelectAllClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 744
    Top = 544
    Width = 59
    Height = 43
    Align = alNone
    TabOrder = 2
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
    end
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
        DataField = '@Return'
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
        DataField = 'vsmess'
      end
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
      end
      item
        Name = '����'
        Caption = '����'
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
      end
      item
        Name = '����'
        Caption = '����'
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
      end
      item
        Name = '�ͻ����'
        Caption = '�ͻ����'
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
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
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
      end
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
        GroupIndex = 1
      end
      item
        Name = 'רҵ'
        Caption = 'רҵ'
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
      end
      item
        Name = 'Ժϵ'
        Caption = 'Ժϵ'
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
      end
      item
        Name = '�༶'
        Caption = '�༶'
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
      end
      item
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
      end
      item
        Name = '����У��'
        Caption = '����У��'
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
      end
      item
        Name = '�ֳֻ����'
        Caption = '�ֳֻ����'
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
        MonitorValueChangedFields = '|������|�豸���|����Ա��|'
      end>
    Left = 156
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�ֳֻ����������ѯ'
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
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = 'Ժϵ'
        FieldName = 'Ժϵ'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'רҵ'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
      end
      item
        ParamName = '����У��'
        FieldName = '����У��'
      end
      item
        ParamName = '�ֳֻ����'
        FieldName = '�ֳֻ����'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 224
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�ֳֻ������´�'
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
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 264
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
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
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        Name = '�豸���'
        Caption = '�豸���'
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
      end
      item
        Name = '����Ա��'
        Caption = '����Ա��'
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'semail'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValidChangedFields = '|Ԥ����|'
      end>
    Left = 152
    Top = 264
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
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
        DataField = '@Return'
      end
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        DataField = 'vsmess'
      end
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�ͻ����'
        Caption = '�ͻ����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
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
        Name = '�豸���'
        Caption = '�豸���'
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        Name = '����У��'
        Caption = '����У��'
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
        Name = '״̬'
        Caption = '״̬'
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
        Name = '����״̬'
        Caption = '����״̬'
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
        MonitorValueChangedFields = '|������|�豸���|����Ա��|'
      end>
    Left = 476
    Top = 239
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�·��ֳֻ�������ѯ'
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
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '����У��'
        FieldName = '����У��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end>
    AfterExec = MainRequestAfterExec
    Left = 512
    Top = 240
  end
  object WVRequest3: TWVRequest
    WorkView = WorkView3
    ID = '�ֳֻ�����ɾ��'
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
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end>
    AfterExec = MainRequestAfterExec
    Left = 520
    Top = 272
  end
  object WorkView3: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
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
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        Name = '�豸���'
        Caption = '�豸���'
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '����'
        Caption = '����'
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
      end
      item
        Name = '����Ա��'
        Caption = '����Ա��'
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
        MonitorValidChangedFields = '|Ԥ����|'
      end>
    Left = 480
    Top = 272
  end
  object WVRequest4: TWVRequest
    WorkView = WorkView4
    ID = '�ֳֻ������ɹ�'
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
        ParamName = '�豸��'
        FieldName = '�豸��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    AfterExec = MainRequestAfterExec
    Left = 520
    Top = 312
  end
  object WorkView4: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
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
        DataField = '@Return'
      end
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        DataField = 'vsmess'
      end
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
        Name = '�豸��'
        Caption = '�豸��'
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
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|������|�豸���|����Ա��|'
      end>
    Left = 484
    Top = 311
  end
end

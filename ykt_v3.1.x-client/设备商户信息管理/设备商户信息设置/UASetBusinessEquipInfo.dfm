inherited faqhSetBusinessEquipInfo: TfaqhSetBusinessEquipInfo
  Width = 882
  Height = 581
  Caption = '�豸�̻���Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 882
    Height = 581
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      OnEnter = tsQueryEnter
      inherited UIPanel1: TUIPanel
        Top = 520
        Width = 878
        Height = 38
        TabOrder = 5
        inherited btnAdd: TBitBtn [0]
          Left = 616
          Enabled = False
          TabOrder = 3
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 704
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 523
          Visible = False
        end
        inherited btnDelete: TBitBtn
          Left = 789
          Enabled = False
          TabOrder = 2
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Visible = False
        end
        inherited ckAutoSetNewParams: TCheckBox
          Visible = False
        end
        object btnAddEB1: TButton
          Left = 488
          Top = 8
          Width = 73
          Height = 28
          Caption = '�����豸'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          OnClick = btnAddEB1Click
        end
        object btnBefChaEB2: TButton
          Left = 576
          Top = 8
          Width = 73
          Height = 28
          Caption = '�޸��豸'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
          OnClick = btnBefChaEB2Click
        end
        object btnBefDelEB2: TButton
          Left = 664
          Top = 8
          Width = 73
          Height = 28
          Caption = 'ɾ���豸'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
          OnClick = btnBefDelEB2Click
        end
        object btnReTree1: TButton
          Left = 88
          Top = 8
          Width = 73
          Height = 28
          Caption = 'ˢ����ʾ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 9
          OnClick = btnReTree1Click
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 878
      end
      inherited Grid: TRzDBGrid
        Left = 568
        Top = 192
        Width = 378
        Height = 328
        Align = alNone
        Visible = False
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '���'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '�豸��ʶ'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Caption = '�̻���ʶ'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Caption = 'ʹ�ÿ�ʼ����'
            Width = 93
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sholder_ac_no'
            PickList.Strings = ()
            Title.Caption = 'ʹ�ÿ�ʼʱ��'
            Width = 88
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no2'
            PickList.Strings = ()
            Title.Caption = 'ʹ�ý�������'
            Width = 92
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sholder_ac_no2'
            PickList.Strings = ()
            Title.Caption = 'ʹ�ý���ʱ��'
            Width = 88
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '��ע'
            Width = 193
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 304
        Top = 224
        Width = 273
        Height = 169
        ParentColor = True
        TabOrder = 0
        Visible = False
        object Label9: TLabel
          Left = 42
          Top = 5
          Width = 128
          Height = 16
          Caption = '�豸�̻���Ϣ��ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label1: TLabel
          Left = 58
          Top = 41
          Width = 24
          Height = 12
          Caption = '���'
        end
        object Label13: TLabel
          Left = 258
          Top = 41
          Width = 72
          Height = 12
          Caption = 'ʹ�ÿ�ʼ����'
        end
        object Label14: TLabel
          Left = 538
          Top = 41
          Width = 72
          Height = 12
          Caption = 'ʹ�ý�������'
        end
        object WVEdit4: TWVEdit
          Left = 104
          Top = 37
          Width = 97
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.���>'
          WorkView = WorkView
          FieldName = '��ѯ.���'
        end
        object WVEdit5: TWVEdit
          Left = 356
          Top = 37
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.ʹ�ÿ�ʼ����>'
          WorkView = WorkView
          FieldName = '��ѯ.ʹ�ÿ�ʼ����'
        end
        object WVEdit8: TWVEdit
          Left = 644
          Top = 37
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.ʹ�ý�������>'
          WorkView = WorkView
          FieldName = '��ѯ.ʹ�ý�������'
        end
      end
      object UIPanel5: TUIPanel
        Left = 0
        Top = 73
        Width = 878
        Height = 447
        Align = alClient
        Color = 15458000
        TabOrder = 3
        object Splitter1: TSplitter
          Left = 401
          Top = 1
          Width = 4
          Height = 445
          Cursor = crHSplit
          Beveled = True
        end
        object treevEquAndBusi2: TTreeView
          Left = 1
          Top = 1
          Width = 400
          Height = 445
          Align = alLeft
          Images = ImageList1
          Indent = 19
          PopupMenu = PopupMenu1
          TabOrder = 0
          OnMouseDown = treevEquAndBusi2MouseDown
          OnMouseUp = treevEquAndBusi2MouseUp
        end
        object EquipTreVw1: TTreeView
          Left = 405
          Top = 1
          Width = 472
          Height = 445
          Align = alClient
          Images = ImageList1
          Indent = 19
          TabOrder = 1
          OnMouseDown = EquipTreVw1MouseDown
        end
      end
      object UIPanel7: TUIPanel
        Left = 0
        Top = 18
        Width = 878
        Height = 55
        Align = alTop
        Color = 15458000
        TabOrder = 4
        object Label15: TLabel
          Left = 344
          Top = 9
          Width = 160
          Height = 16
          Caption = 'Ϊѡ�е��̻������豸'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label18: TLabel
          Left = 384
          Top = 29
          Width = 108
          Height = 12
          Caption = '<-----------------'
          Font.Charset = GB2312_CHARSET
          Font.Color = clRed
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          Visible = False
        end
        object Label17: TLabel
          Left = 496
          Top = 29
          Width = 42
          Height = 12
          Caption = 'Label17'
        end
        object Label16: TLabel
          Left = 312
          Top = 29
          Width = 42
          Height = 12
          Caption = 'Label16'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 66
        Top = 44
        Width = 24
        Height = 12
        Caption = '���'
      end
      object Label3: TLabel [1]
        Left = 78
        Top = 80
        Width = 48
        Height = 12
        Caption = '�豸��ʶ'
        Visible = False
      end
      object Label4: TLabel [2]
        Left = 82
        Top = 120
        Width = 48
        Height = 12
        Caption = '�̻���ʶ'
        Visible = False
      end
      object Label5: TLabel [3]
        Left = 268
        Top = 44
        Width = 72
        Height = 12
        Caption = 'ʹ�ÿ�ʼ����'
      end
      object Label6: TLabel [4]
        Left = 268
        Top = 80
        Width = 72
        Height = 12
        Caption = 'ʹ�ÿ�ʼʱ��'
      end
      object Label7: TLabel [5]
        Left = 268
        Top = 120
        Width = 72
        Height = 12
        Caption = 'ʹ�ý���ʱ��'
      end
      object Label8: TLabel [6]
        Left = 468
        Top = 44
        Width = 72
        Height = 12
        Caption = 'ʹ�ý�������'
      end
      object Label10: TLabel [7]
        Left = 42
        Top = 5
        Width = 128
        Height = 16
        Caption = '�豸�̻���ϵ����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object WVLabel1: TWVLabel [8]
        Left = 74
        Top = 200
        Width = 24
        Height = 12
        Caption = '��ע'
      end
      object Label11: TLabel [9]
        Left = 464
        Top = 80
        Width = 126
        Height = 12
        Caption = '<-����6λ����(hhddss)'
      end
      object Label12: TLabel [10]
        Left = 464
        Top = 120
        Width = 126
        Height = 12
        Caption = '<-����6λ����(hhddss)'
      end
      object Label19: TLabel [11]
        Left = 54
        Top = 80
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label20: TLabel [12]
        Left = 54
        Top = 120
        Width = 48
        Height = 12
        Caption = '�̻�����'
      end
      object lbl1: TLabel [13]
        Left = 54
        Top = 160
        Width = 48
        Height = 12
        Caption = '�շѿ�Ŀ'
      end
      object lbl2: TLabel [14]
        Left = 206
        Top = 160
        Width = 264
        Height = 12
        Caption = '�շѿ�ĿֵΪ0��99֮�������ֵ��0Ϊ���շѿ�Ŀ'
      end
      inherited UIPanel2: TUIPanel
        Top = 522
        Width = 878
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 698
        end
        inherited btnCancel: TBitBtn
          Left = 794
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          Visible = False
        end
        object btnAdDlChOK3: TButton
          Left = 416
          Top = 8
          Width = 81
          Height = 25
          Caption = '&O ȷ��'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = btnAdDlChOK3Click
        end
        object btnAdDlChCcl3: TButton
          Left = 520
          Top = 8
          Width = 81
          Height = 25
          Caption = 'ȡ��'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = btnAdDlChCcl3Click
        end
      end
      object WVDigitalEdit2: TWVDigitalEdit
        Left = 151
        Top = 76
        Width = 98
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '�豸��ʶ'
        SynchronizeByValue = True
      end
      object WVEdit6: TWVEdit
        Left = 350
        Top = 76
        Width = 100
        Height = 20
        Color = clInfoBk
        MaxLength = 6
        ReadOnly = False
        TabOrder = 1
        Text = '<ʹ�ÿ�ʼʱ��>'
        WorkView = WorkView
        FieldName = 'ʹ�ÿ�ʼʱ��'
        SynchronizeWhenExit = True
      end
      object WVEdit7: TWVEdit
        Left = 350
        Top = 116
        Width = 100
        Height = 20
        Color = clInfoBk
        MaxLength = 6
        ReadOnly = False
        TabOrder = 2
        Text = '<ʹ�ý���ʱ��>'
        WorkView = WorkView
        FieldName = 'ʹ�ý���ʱ��'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 104
        Top = 200
        Width = 353
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<��ע>'
        WorkView = WorkView
        FieldName = '��ע'
      end
      object WVDigitalEdit1: TWVDigitalEdit
        Left = 104
        Top = 40
        Width = 97
        Height = 25
        ParentColor = False
        TabOrder = 5
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '���'
      end
      object WVDigitalEdit3: TWVDigitalEdit
        Left = 152
        Top = 114
        Width = 97
        Height = 25
        ParentColor = False
        TabOrder = 6
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '�̻���ʶ'
      end
      object WVEdit2: TWVEdit
        Left = 348
        Top = 37
        Width = 100
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 7
        Text = '<ʹ�ÿ�ʼ����>'
        WorkView = WorkView
        FieldName = 'ʹ�ÿ�ʼ����'
      end
      object WVEdit3: TWVEdit
        Left = 548
        Top = 37
        Width = 100
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 8
        Text = '<ʹ�ý�������>'
        WorkView = WorkView
        FieldName = 'ʹ�ý�������'
      end
      object UIPanel4: TUIPanel
        Left = 360
        Top = 168
        Width = 185
        Height = 241
        Color = 15458000
        TabOrder = 9
        Visible = False
      end
      object UIPanel3: TUIPanel
        Left = 600
        Top = 160
        Width = 177
        Height = 241
        Color = 15458000
        TabOrder = 10
        Visible = False
      end
      object Edit1: TEdit
        Left = 104
        Top = 76
        Width = 97
        Height = 20
        Enabled = False
        TabOrder = 11
      end
      object Edit2: TEdit
        Left = 104
        Top = 116
        Width = 97
        Height = 20
        Enabled = False
        TabOrder = 12
      end
      object WVDigitalEdit4: TWVDigitalEdit
        Left = 104
        Top = 154
        Width = 97
        Height = 23
        ParentColor = False
        TabOrder = 13
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�շѿ�Ŀ'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 468
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        Name = '��ѯ.���'
        Caption = '��ѯ.���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol1'
      end
      item
        Name = '���'
        Caption = '���'
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
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
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
        DataField = 'lvol0'
      end
      item
        Name = '��ѯ.�豸��ʶ'
        Caption = '��ѯ.�豸��ʶ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol0'
      end
      item
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'damt0'
      end
      item
        Name = '��ѯ.�̻���ʶ'
        Caption = '��ѯ.�̻���ʶ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'damt0'
      end
      item
        Name = 'ʹ�ÿ�ʼ����'
        Caption = 'ʹ�ÿ�ʼ����'
        FieldType = wftUndefined
        DomainName = '���ڸ�ʽ'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no'
      end
      item
        Name = 'ʹ�ÿ�ʼʱ��'
        Caption = 'ʹ�ÿ�ʼʱ��'
        FieldType = wftUndefined
        DomainName = 'ʱ���ʽ'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sholder_ac_no'
      end
      item
        Name = 'ʹ�ý�������'
        Caption = 'ʹ�ý�������'
        FieldType = wftUndefined
        DomainName = '���ڸ�ʽ'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no2'
      end
      item
        Name = 'ʹ�ý���ʱ��'
        Caption = 'ʹ�ý���ʱ��'
        FieldType = wftUndefined
        DomainName = 'ʱ���ʽ'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sholder_ac_no2'
      end
      item
        Name = '��ע'
        Caption = '��ע'
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
        DataField = 'scusttypes'
      end
      item
        Name = '��ѯ.��ע'
        Caption = '��ѯ.��ע'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scusttypes'
      end
      item
        Name = '��ѯ.ʹ�ÿ�ʼ����'
        Caption = '��ѯ.ʹ�ÿ�ʼ����'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scust_no2'
      end
      item
        Name = '��ѯ.ʹ�ÿ�ʼʱ��'
        Caption = '��ѯ.ʹ�ÿ�ʼʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sholder_ac_no'
      end
      item
        Name = '��ѯ.ʹ�ý�������'
        Caption = '��ѯ.ʹ�ý�������'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scust_no2'
      end
      item
        Name = '��ѯ.ʹ�ý���ʱ��'
        Caption = '��ѯ.ʹ�ý���ʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sholder_ac_no2'
      end
      item
        Name = '�շѿ�Ŀ'
        Caption = '�շѿ�Ŀ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 2
        Checker.Max = 99
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�豸�̻���ʶ|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|���|ǰ�˻���ʶ|�̻���ʶ|ʹ�ÿ�ʼ����|ʹ�ÿ�ʼʱ��|ʹ�ý���ʱ��' +
          '|ʹ�ý�������|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 416
    Top = 376
  end
  inherited QueryRequest: TWVRequest
    ID = '�豸�̻���Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���'
        FieldName = '���'
      end>
    Left = 552
    Top = 336
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol0'
        WVFieldName = '�豸��ʶ'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '1317'
      end
      item
        FieldName = 'damt0'
        WVFieldName = '�̻���ʶ'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '1317'
      end>
    Left = 468
    Top = 375
  end
  inherited AddRequest: TWVRequest
    ID = '�豸�̻���Ϣ����.����'
    Bindings = <
      item
        ParamName = 'ʹ�ÿ�ʼ����'
        FieldName = 'ʹ�ÿ�ʼ����'
      end
      item
        ParamName = 'ʹ�ÿ�ʼʱ��'
        FieldName = 'ʹ�ÿ�ʼʱ��'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = 'ʹ�ý�������'
        FieldName = 'ʹ�ý�������'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end
      item
        ParamName = '�շѿ�Ŀ'
        FieldName = '�շѿ�Ŀ'
      end>
    Left = 416
    Top = 336
  end
  inherited DeleteRequest: TWVRequest
    ID = '�豸�̻���Ϣ����.ɾ��'
    Bindings = <
      item
        ParamName = 'ʹ�ÿ�ʼ����'
        FieldName = 'ʹ�ÿ�ʼ����'
      end
      item
        ParamName = 'ʹ�ÿ�ʼʱ��'
        FieldName = 'ʹ�ÿ�ʼʱ��'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = 'ʹ�ý�������'
        FieldName = 'ʹ�ý�������'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end
      item
        ParamName = '�շѿ�Ŀ'
        FieldName = '�շѿ�Ŀ'
      end>
    Left = 464
    Top = 336
  end
  inherited ChangeRequest: TWVRequest
    ID = '�豸�̻���Ϣ����.�޸�'
    Bindings = <
      item
        ParamName = 'ʹ�ÿ�ʼ����'
        FieldName = 'ʹ�ÿ�ʼ����'
      end
      item
        ParamName = 'ʹ�ÿ�ʼʱ��'
        FieldName = 'ʹ�ÿ�ʼʱ��'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = 'ʹ�ý�������'
        FieldName = 'ʹ�ý�������'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end
      item
        ParamName = '�շѿ�Ŀ'
        FieldName = '�շѿ�Ŀ'
      end>
    Left = 512
    Top = 336
  end
  inherited WVDataSource: TWVDataSource
    Left = 556
    Top = 375
  end
  inherited alDatasetActions: TActionList
    Left = 508
    Top = 372
  end
  object QueryRequest3: TWVRequest
    WorkView = WorkView3
    ID = '�豸�ؼ��ֲ�ѯ3'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end>
    Left = 712
    Top = 368
  end
  object WorkView3: TWorkView
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
        DataField = '@Dataset'
      end
      item
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�豸��־|������Կ|'
      end>
    Left = 676
    Top = 367
  end
  object PopupMenu1: TPopupMenu
    Left = 276
    Top = 151
    object ChaDateTime1: TMenuItem
      Caption = '�޸��豸������ʱ��'
      OnClick = ChaDateTime1Click
    end
    object DelEquAndBus1: TMenuItem
      Caption = 'ɾ���豸'
      OnClick = DelEquAndBus1Click
    end
  end
  object QueryRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�̻���Ϣ��������ѯ2'
    Bindings = <
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = '���̻���ʶ'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�Ƿ�Ϊ��������'
        FieldName = '�Ƿ�Ϊ��������'
      end
      item
        ParamName = '�Ƿ�ΪҶ�ڵ�'
        FieldName = '�Ƿ�ΪҶ�ڵ�'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = '�̻�״̬'
      end
      item
        ParamName = '�Ƿ���ȡ�����'
        FieldName = '�Ƿ���ȡ�����'
      end
      item
        ParamName = '������Ա����'
        FieldName = '������Ա����'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '�������Ա�'
        FieldName = '�������Ա�'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '���������֤��'
        FieldName = '���������֤��'
      end
      item
        ParamName = '��ȡ���ѹ���ѱ���'
        FieldName = '��ȡ���ѹ���ѱ���'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = '��ϵ�绰'
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = '��ϵ��ַ'
      end
      item
        ParamName = 'ע��ʱ��'
        FieldName = 'ע��ʱ��'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end>
    Left = 160
    Top = 360
  end
  object WorkView1: TWorkView
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
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
        FieldType = wftUndefined
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '���̻���ʶ'
        Caption = '���̻���ʶ'
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
        Name = '�̻�����'
        Caption = '�̻�����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scard1'
      end
      item
        Name = '�̻����'
        Caption = '�̻����'
        FieldType = wftUndefined
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
        Name = '�Ƿ�Ϊ��������'
        Caption = '�Ƿ�Ϊ��������'
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
        Name = '�Ƿ�ΪҶ�ڵ�'
        Caption = '�Ƿ�ΪҶ�ڵ�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'smarket_code2'
      end
      item
        Name = '�̻�״̬'
        Caption = '�̻�״̬'
        FieldType = wftUndefined
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
        Name = '������Ա����'
        Caption = '������Ա����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_auth'
      end
      item
        Name = '����������'
        Caption = '����������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sname'
      end
      item
        Name = '�������Ա�'
        Caption = '�������Ա�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sstatus0'
      end
      item
        Name = '����������'
        Caption = '����������'
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
        Name = '���������֤��'
        Caption = '���������֤��'
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
      end
      item
        Name = '��ϵ�绰'
        Caption = '��ϵ�绰'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_auth2'
      end
      item
        Name = '��ϵ��ַ'
        Caption = '��ϵ��ַ'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scusttypes'
      end
      item
        Name = '�Ƿ���ȡ�����'
        Caption = '�Ƿ���ȡ�����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'smarket_code'
      end
      item
        Name = '��ȡ���ѹ���ѱ���'
        Caption = '��ȡ���ѹ���ѱ���'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'damt0'
      end
      item
        Name = 'ע��ʱ��'
        Caption = 'ע��ʱ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sphone3'
      end
      item
        Name = '��ע'
        Caption = '��ע'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'ssectypes'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�̻���ʶ|�ͻ���|���̻���ʶ|�̻�����|�̻����|�Ƿ�ΪҶ�ڵ�|�̻�' +
          '״̬|������Ա����|����������|�������Ա�|�������������|��������' +
          '��֤��|��ϵ�绰|��ϵ��ַ|�Ƿ���ȡ�����|��ȡ���ѹ���ѱ���|�̻�' +
          '����Ѽ��㷽ʽ|�̻�˰�Ѽ��㷽ʽ|ע��ʱ��|��ע|'
      end>
    Left = 124
    Top = 359
  end
  object ImageList1: TImageList
    Left = 253
    Top = 47
    Bitmap = {
      494C010103000400040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF0000000000000000000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF00000000000084840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007BADEF00639CE700528CDE00528CDE004A84CE00427BBD00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60000848400008484000084840000000000C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C6000000000000000000000000000000
      0000A5C6EF008CB5EF006BADF7005AA5FF00529CEF004A8CD600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FF000000FF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000ADC6E70084B5EF007BB5F70063ADFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B5CEE7008CB5EF008CB5EF00000000005AA5FF00528CDE00000000000000
      000000000000000000000000000000000000C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6000000FF000000FF00C6C6C600848484000000FF000000FF00C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000BDCEE7008CB5EF008CB5EF007BB5F7006BADF7004A84CE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C6C6C6008484840000000000000000000000000000000000000000000000
      0000BDCEEF008CB5EF008CB5EF008CB5EF0073ADF70063A5EF004A8CD600427B
      BD00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400C6C6C6008484840084848400000000000000000000000000000000000000
      0000B5CEEF008CB5EF008CB5EF008CB5EF007BB5EF006BADF7005294EF00528C
      DE00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6008484840084848400000000000000000000000000000000000000
      0000BDCEEF0094BDEF008CB5EF008CB5EF008CB5EF000000000052A5FF00528C
      DE000000000000000000000000000000000084848400C6C6C600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C6C6C6008484840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000084
      000000FF00008484840084848400000000000000000000000000000000000000
      0000BDD6EF009CBDEF008CB5EF008CB5EF008CB5EF00000000005AA5FF00528C
      DE000000000000000000000000000000000084848400C6C6C600848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400C6C6C6008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008484840084848400000000000000000000000000000000000000
      0000BDD6EF00A5C6EF0094BDEF008CBDEF008CB5EF008CB5EF007BADE700528C
      DE000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084848400000000000000000000000000000000000000
      0000B5C6DE00BDCEE700BDD6EF00BDD6EF00BDCEEF00ADC6EF009CBDEF0094BD
      EF000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000084
      000000FF00008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400848484008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400848484008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFFFFFF0000FC3FF03FF99F0000
      0100E01FFC3F00000000E01FFE7F0000FE7FE01F00000000FE7FE01F00000000
      8003E00FFE7F00003FF1E007FE7F00000000E007800300000000E0073FF10000
      0000E007000000007FF8E007000000008000E00700000000C001F00F7FF80000
      FFFFFFFF80000000FFFFFFFFC001000000000000000000000000000000000000
      000000000000}
  end
  object WorkView5: TWorkView
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
        Name = '���'
        Caption = '���'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�豸�̻���ʶ|'
      end>
    Left = 124
    Top = 215
  end
  object QueryRequest5: TWVRequest
    WorkView = WorkView5
    ID = '�豸�̻���Ϣ������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���'
        FieldName = '���'
      end>
    Left = 160
    Top = 216
  end
  object QueryRequest6: TWVRequest
    WorkView = WorkView
    ID = '�豸�̻���Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���'
        FieldName = '���'
      end>
    Left = 608
    Top = 334
  end
  object QueryRequest4: TWVRequest
    WorkView = WorkView4
    ID = '�豸�ǹؼ��ֲ�ѯ2'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�����豸ע���'
        FieldName = '�����豸ע���'
      end
      item
        ParamName = '�豸����ID'
        FieldName = '�豸����ID'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = '�ϼ��豸����ID'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '�豸״̬'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�豸��������'
        FieldName = '�豸��������'
      end
      item
        ParamName = '������Ա����'
        FieldName = '������Ա����'
      end>
    Left = 712
    Top = 328
  end
  object WorkView4: TWorkView
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
        Name = '�豸����'
        Caption = '�豸����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_auth'
      end
      item
        Name = '�����豸ע���'
        Caption = '�����豸ע���'
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
        Name = '�豸����ID'
        Caption = '�豸����ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd2'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
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
        Name = '�ϼ��豸����ID'
        Caption = '�ϼ��豸����ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '�豸״̬'
        Caption = '�豸״̬'
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
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
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
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
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
        Name = '�豸��������'
        Caption = '�豸��������'
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
        Name = '������Ա����'
        Caption = '������Ա����'
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
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 676
    Top = 327
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
      end
      item
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�̻���ʶ|'
      end>
    Left = 124
    Top = 319
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�̻���Ϣ������ѯ2'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end>
    Left = 160
    Top = 320
  end
end

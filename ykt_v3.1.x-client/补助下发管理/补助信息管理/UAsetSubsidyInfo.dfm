inherited faqhsetSubsidyInfo: TfaqhsetSubsidyInfo
  Width = 762
  Height = 484
  Caption = '������Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 762
    Height = 484
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 431
        Width = 758
        TabOrder = 3
        object Label33: TLabel [0]
          Left = 102
          Top = 9
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        object Label8: TLabel [1]
          Left = 250
          Top = 10
          Width = 24
          Height = 12
          Caption = '״̬'
        end
        inherited btnAdd: TBitBtn [2]
          Left = 128
          Top = 1000
          Enabled = False
          TabOrder = 8
          Visible = False
        end
        inherited btnChange: TBitBtn [3]
          Left = 504
          Enabled = False
          TabOrder = 2
        end
        inherited btnQuery: TBitBtn [4]
          Left = 419
        end
        inherited btnDelete: TBitBtn
          Left = 589
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
          Width = 57
          TabOrder = 7
          Visible = False
        end
        object btnPatchDel: TBitBtn
          Left = 673
          Top = 3
          Width = 79
          Height = 25
          Anchors = [akTop, akRight]
          Caption = '����ɾ��'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
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
          TabOrder = 5
          Text = '<���κ�>'
          WorkView = WorkView1
          FieldName = '���κ�'
        end
        object WVComboBox1: TWVComboBox
          Left = 285
          Top = 5
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView1
          FieldName = '״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*76'
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 758
      end
      inherited Grid: TRzDBGrid
        Top = 122
        Width = 758
        Height = 309
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������κ�'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '˳���'
            Width = 40
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ѧ/����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol10'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������κ�'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��¼״̬'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���״̬'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������Ϣ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����ʱ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�·�����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�·�ʱ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ȡ����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ȡʱ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ժҪ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol11'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����������'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���������֤��'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '֧����ʽ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ƾ֤����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������Ա'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smain_flag'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 758
        Height = 104
        Align = alTop
        BevelOuter = bvNone
        ParentColor = True
        TabOrder = 1
        object Label2: TLabel
          Left = 30
          Top = 10
          Width = 60
          Height = 12
          Caption = '�������κ�'
        end
        object Label3: TLabel
          Left = 466
          Top = 34
          Width = 24
          Height = 12
          Caption = '״̬'
        end
        object Label4: TLabel
          Left = 448
          Top = 10
          Width = 42
          Height = 12
          Caption = 'ѧ/����'
        end
        object Label5: TLabel
          Left = 254
          Top = 10
          Width = 36
          Height = 12
          Caption = '�ͻ���'
        end
        object Label6: TLabel
          Left = 230
          Top = 34
          Width = 60
          Height = 12
          Caption = '�������κ�'
        end
        object Label7: TLabel
          Left = 66
          Top = 34
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label13: TLabel
          Left = 18
          Top = 58
          Width = 72
          Height = 12
          Caption = '�·���ʼ����'
        end
        object Label14: TLabel
          Left = 218
          Top = 58
          Width = 72
          Height = 12
          Caption = '�·���������'
        end
        object lbl1: TLabel
          Left = 42
          Top = 80
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label16: TLabel
          Left = 442
          Top = 58
          Width = 48
          Height = 12
          Caption = '���״̬'
        end
        object WVEdit2: TWVEdit
          Left = 100
          Top = 5
          Width = 100
          Height = 20
          Color = clBtnHighlight
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.�������κ�>'
          WorkView = WorkView
          FieldName = '��ѯ.�������κ�'
        end
        object WVEdit4: TWVEdit
          Left = 500
          Top = 6
          Width = 100
          Height = 20
          Color = clBtnHighlight
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.ѧ����>'
          WorkView = WorkView
          FieldName = '��ѯ.ѧ����'
        end
        object cbbType: TWVComboBox
          Left = 501
          Top = 29
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clBtnHighlight
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '��ѯ.״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*76'
        end
        object edtQCustNo: TWVEdit
          Left = 300
          Top = 6
          Width = 100
          Height = 20
          Color = clBtnHighlight
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�ͻ���>'
          WorkView = WorkView
          FieldName = '��ѯ.�ͻ���'
        end
        object edtQPatchNo: TWVEdit
          Left = 300
          Top = 30
          Width = 100
          Height = 20
          Color = clBtnHighlight
          MaxLength = 9
          ReadOnly = False
          TabOrder = 5
          Text = '<��ѯ.�������κ�>'
          WorkView = WorkView
          FieldName = '��ѯ.�������κ�'
        end
        object edtQCardNo: TWVEdit
          Left = 100
          Top = 29
          Width = 100
          Height = 20
          Color = clBtnHighlight
          MaxLength = 9
          ReadOnly = False
          TabOrder = 3
          Text = '<��ѯ.����>'
          WorkView = WorkView
          FieldName = '��ѯ.����'
        end
        object edtBDate: TWVEdit
          Left = 100
          Top = 53
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 6
          Text = '<��ѯ.��ʼ����>'
          WorkView = WorkView
          FieldName = '��ѯ.��ʼ����'
        end
        object edtEDate: TWVEdit
          Left = 300
          Top = 53
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 7
          Text = '<��ѯ.��������>'
          WorkView = WorkView
          FieldName = '��ѯ.��������'
        end
        object cbbDept: TWVComboBox
          Left = 100
          Top = 77
          Width = 301
          Height = 20
          Style = csDropDownList
          Color = clWhite
          DropDownCount = 20
          ItemHeight = 12
          TabOrder = 9
          WorkView = WorkView
          FieldName = '����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-22'
        end
        object WVComboBox2: TWVComboBox
          Left = 501
          Top = 53
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '���״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*160'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label9: TLabel [0]
        Left = 54
        Top = 44
        Width = 36
        Height = 12
        Caption = '���κ�'
      end
      object Label10: TLabel [1]
        Left = 54
        Top = 84
        Width = 36
        Height = 12
        Caption = '˳���'
      end
      object Label11: TLabel [2]
        Left = 54
        Top = 308
        Width = 36
        Height = 12
        Caption = 'ѧ����'
        Visible = False
      end
      object Label12: TLabel [3]
        Left = 54
        Top = 124
        Width = 36
        Height = 12
        Caption = '�ͻ���'
      end
      object Label15: TLabel [4]
        Left = 66
        Top = 164
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label21: TLabel [5]
        Left = 54
        Top = 204
        Width = 36
        Height = 12
        Caption = '������'
      end
      object Label1: TLabel [6]
        Left = 46
        Top = 284
        Width = 48
        Height = 12
        Caption = '��¼״̬'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 425
        Width = 758
        TabOrder = 7
        inherited btnOK: TBitBtn
          Left = 586
        end
        inherited btnCancel: TBitBtn
          Left = 674
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtPatchNo: TWVEdit
        Left = 102
        Top = 40
        Width = 100
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 0
        Text = '<���κ�>'
        WorkView = WorkView
        FieldName = '���κ�'
        SynchronizeWhenExit = True
      end
      object edtNo: TWVDigitalEdit
        Left = 102
        Top = 80
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        Precision = 0
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 1
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '˳���'
        SynchronizeByValue = True
      end
      object WVEdit11: TWVEdit
        Left = 102
        Top = 304
        Width = 100
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 6
        Text = '<ѧ����>'
        Visible = False
        WorkView = WorkView
        FieldName = 'ѧ����'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit12: TWVDigitalEdit
        Left = 102
        Top = 120
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        Precision = 0
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 2
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�ͻ���'
        SynchronizeByValue = True
      end
      object WVDigitalEdit15: TWVDigitalEdit
        Left = 102
        Top = 160
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        Precision = 0
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '����'
        SynchronizeByValue = True
      end
      object WVDigitalEdit21: TWVDigitalEdit
        Left = 102
        Top = 200
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 4
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '������'
        SynchronizeByValue = True
      end
      object WVEdit6: TWVEdit
        Left = 102
        Top = 280
        Width = 100
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 5
        Text = '<��¼״̬>'
        Visible = False
        WorkView = WorkView
        FieldName = '��¼״̬'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 492
    Top = 255
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
        Name = '��ѯ.��ʼ����'
        Caption = '��ѯ.��ʼ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.�������κ�'
        Caption = '��ѯ.�������κ�'
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
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
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
        Name = '��ѯ.ѧ����'
        Caption = '��ѯ.ѧ����'
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
        Name = '��ѯ.�ͻ���'
        Caption = '��ѯ.�ͻ���'
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
        Name = '��ѯ.�������κ�'
        Caption = '��ѯ.�������κ�'
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
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
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
        Name = '���״̬'
        Caption = '���״̬'
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
        Name = '����'
        Caption = '����'
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
        Name = '���κ�'
        Caption = '���κ�'
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
        Name = '˳���'
        Caption = '˳���'
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
        DataField = 'lvol1'
      end
      item
        Name = '��¼״̬'
        Caption = '��¼״̬'
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
        DataField = 'sstatus1'
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
        DataField = 'scust_auth'
      end
      item
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        DataField = 'lvol0'
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
        DataField = 'lvol11'
      end
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.��������|��ѯ.�������κ�|��ѯ.״̬|��ѯ.ѧ����|��ѯ.�ͻ���' +
          '|��ѯ.�������κ�|��ѯ.����|��ѯ.������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|���κ�|˳���|ѧ����|�ͻ���|�������κ�|��������|����|ժҪ|����' +
          '������|���������֤��|֧����ʽ|ƾ֤����|������|��������|����ʱ��' +
          '|�·�����|�·�ʱ��|��ȡ����|��ȡʱ��|��¼״̬|������Ϣ|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    InvalidColor = clBtnHighlight
    Left = 408
    Top = 224
  end
  inherited QueryRequest: TWVRequest
    ID = '������Ϣ��ѯ'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�������κ�'
        FieldName = '��ѯ.�������κ�'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end
      item
        ParamName = 'ѧ����'
        FieldName = '��ѯ.ѧ����'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '��ѯ.�ͻ���'
      end
      item
        ParamName = '�������κ�'
        FieldName = '��ѯ.�������κ�'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ѯ.��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '���״̬'
        FieldName = '���״̬'
      end>
    Left = 568
    Top = 224
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '76'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '63'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '160'
      end>
    Left = 452
    Top = 255
  end
  inherited AddRequest: TWVRequest
    ID = '������Ϣ����'
    Bindings = <
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '˳���'
        FieldName = '˳���'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ժҪ'
        FieldName = 'ժҪ'
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
        ParamName = '֧����ʽ'
        FieldName = '֧����ʽ'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '�·�����'
        FieldName = '�·�����'
      end
      item
        ParamName = '�·�ʱ��'
        FieldName = '�·�ʱ��'
      end
      item
        ParamName = '��ȡ����'
        FieldName = '��ȡ����'
      end
      item
        ParamName = '��ȡʱ��'
        FieldName = '��ȡʱ��'
      end
      item
        ParamName = '��¼״̬'
        FieldName = '��¼״̬'
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
      end
      item
        ParamName = '�������Ա'
        FieldName = '�������Ա.����'
      end>
    Left = 448
    Top = 224
  end
  inherited DeleteRequest: TWVRequest
    ID = '������Ϣ����'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '˳���'
        FieldName = '˳���'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
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
        ParamName = '��¼״̬'
        FieldName = '��¼״̬'
      end>
    Left = 488
    Top = 224
  end
  inherited ChangeRequest: TWVRequest
    ID = '������Ϣ����'
    Bindings = <
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '˳���'
        FieldName = '˳���'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��¼״̬'
        FieldName = '��¼״̬'
      end>
    Left = 528
    Top = 224
  end
  inherited WVDataSource: TWVDataSource
    Left = 580
    Top = 255
  end
  inherited alDatasetActions: TActionList
    Left = 532
    Top = 260
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        GroupIndex = 1
      end
      item
        Name = '���κ�'
        Caption = '���κ�'
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
        Name = '������־'
        Caption = '������־'
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
        Name = '������־'
        Caption = '������־'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�������κ�|��ѯ.����˳���|��ѯ.��¼��|��ѯ.' +
          '�豸���|��ѯ.�豸������|��ѯ.�豸����|��ѯ.�̻����|��ѯ.�̻�' +
          '����|��ѯ.��ʼʱ��|��ѯ.����ʱ��|��ѯ.��������|��ѯ.ͣ������|��' +
          'ѯ.��ע|'
      end
      item
        MonitorValueChangedFields = 
          '|�������κ�|����˳���|��¼��|�豸���|�豸������|�豸����|��' +
          '�����|�̻�����|��ʼʱ��|����ʱ��|��������|ͣ������|'
      end>
    Left = 408
    Top = 304
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '��������ɾ��'
    Bindings = <
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
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
        ParamName = '״̬'
        FieldName = '״̬'
      end>
    AfterExec = CheckReturnData
    Left = 440
    Top = 304
  end
end

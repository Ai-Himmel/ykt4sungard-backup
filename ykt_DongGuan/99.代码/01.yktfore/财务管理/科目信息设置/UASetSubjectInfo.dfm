inherited faqhSetSubjectInfo: TfaqhSetSubjectInfo
  Width = 743
  Height = 511
  Caption = '�̻���֯�ṹ����'
  inherited pcPages: TRzPageControl
    Width = 743
    Height = 511
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      object Label30: TLabel [0]
        Left = 344
        Top = 64
        Width = 128
        Height = 16
        Caption = '�����ѡ���̻�'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Panel1: TPanel [1]
        Left = 0
        Top = 18
        Width = 739
        Height = 57
        Align = alTop
        ParentColor = True
        TabOrder = 2
        object Label1: TLabel
          Left = 14
          Top = 10
          Width = 48
          Height = 12
          Caption = '��Ŀ����'
        end
        object Label25: TLabel
          Left = 214
          Top = 10
          Width = 36
          Height = 12
          Caption = '������'
        end
        object Label26: TLabel
          Left = 388
          Top = 10
          Width = 48
          Height = 12
          Caption = '��Ŀ����'
        end
        object Label27: TLabel
          Left = 578
          Top = 9
          Width = 48
          Height = 12
          Caption = '��Ŀ���'
        end
        object Label9: TLabel
          Left = 14
          Top = 34
          Width = 48
          Height = 12
          Caption = '��Ŀ����'
        end
        object Label17: TLabel
          Left = 202
          Top = 33
          Width = 48
          Height = 12
          Caption = '����'
        end
        object WVEdit2: TWVEdit
          Left = 254
          Top = 6
          Width = 120
          Height = 20
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ReadOnly = False
          TabOrder = 1
          Text = '<������Q>'
          WorkView = WorkView
          FieldName = '������Q'
          SynchronizeWhenExit = True
        end
        object WVComboBox8: TWVComboBox
          Left = 440
          Top = 6
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '��Ŀ����Q'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*14'
        end
        object WVComboBox9: TWVComboBox
          Left = 628
          Top = 5
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '��Ŀ���Q'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*29'
        end
        object edtBusiId: TWVEdit
          Left = 68
          Top = 6
          Width = 120
          Height = 20
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ReadOnly = False
          TabOrder = 0
          Text = '<��Ŀ����Q>'
          WorkView = WorkView
          FieldName = '��Ŀ����Q'
          SynchronizeWhenExit = True
        end
        object WVComboBox1: TWVComboBox
          Left = 68
          Top = 30
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '��Ŀ����Q'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*31'
        end
        object WVComboBox2: TWVComboBox
          Left = 254
          Top = 29
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '����Q'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*30'
        end
      end
      inherited UIPanel1: TUIPanel
        Top = 458
        Width = 739
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 478
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 564
        end
        inherited btnQuery: TBitBtn [2]
          Left = 392
        end
        inherited btnDelete: TBitBtn
          Left = 650
          Hint = 'ע����ǰѡ�е���Ŀ'
          Caption = 'ע��(&D)'
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 98
          Width = 159
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 739
      end
      inherited Grid: TRzDBGrid
        Top = 75
        Width = 739
        Height = 383
        ImeName = ''
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        Columns = <
          item
            Expanded = False
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���к�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Caption = '�ϼ����к�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ŀ����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ŀ����'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ŀȫ��'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ŀ����'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ŀ���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ŀ����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ƿ�ĩ��'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol6'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ֽ����Ŀ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol7'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������Ŀ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol8'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'һ��ͨ��Ŀ'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'Lvol9'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ƿ�ɾ��'
            Width = 80
            Visible = True
          end>
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 166
        Top = 74
        Width = 48
        Height = 12
        Caption = '��Ŀ����'
      end
      object Label3: TLabel [1]
        Left = 166
        Top = 213
        Width = 48
        Height = 12
        Caption = '��Ŀ����'
      end
      object Label4: TLabel [2]
        Left = 178
        Top = 143
        Width = 36
        Height = 12
        Caption = '������'
      end
      object Label5: TLabel [3]
        Left = 166
        Top = 247
        Width = 48
        Height = 12
        Caption = '����'
      end
      object Label6: TLabel [4]
        Left = 166
        Top = 282
        Width = 48
        Height = 12
        Caption = '�Ƿ�ĩ��'
      end
      object Label7: TLabel [5]
        Left = 166
        Top = 178
        Width = 48
        Height = 12
        Caption = '��Ŀ���'
      end
      object Label8: TLabel [6]
        Left = 178
        Top = 40
        Width = 36
        Height = 12
        Caption = '���к�'
        Visible = False
      end
      object Label11: TLabel [7]
        Left = 166
        Top = 109
        Width = 48
        Height = 12
        Caption = '��Ŀ����'
      end
      object Label12: TLabel [8]
        Left = 142
        Top = 317
        Width = 72
        Height = 12
        Caption = '�Ƿ��ֽ��Ŀ'
      end
      object Label13: TLabel [9]
        Left = 142
        Top = 351
        Width = 72
        Height = 12
        Caption = '�Ƿ����п�Ŀ'
      end
      object Label14: TLabel [10]
        Left = 130
        Top = 386
        Width = 84
        Height = 12
        Caption = '�Ƿ�һ��ͨ��Ŀ'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 452
        Width = 739
        TabOrder = 11
        inherited btnOK: TBitBtn
          Left = 507
        end
        inherited btnCancel: TBitBtn
          Left = 603
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVComboBox3: TWVComboBox
        Left = 220
        Top = 209
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '��Ŀ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*31'
      end
      object edtSubjNo: TWVEdit
        Left = 220
        Top = 70
        Width = 120
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 1
        Text = '<��Ŀ����>'
        WorkView = WorkView
        FieldName = '��Ŀ����'
        SynchronizeWhenExit = True
      end
      object WVComboBox4: TWVComboBox
        Left = 220
        Top = 243
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*30'
      end
      object WVEdit3: TWVEdit
        Left = 220
        Top = 139
        Width = 120
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 3
        Text = '<������>'
        WorkView = WorkView
        FieldName = '������'
        SynchronizeWhenExit = True
      end
      object WVComboBox5: TWVComboBox
        Left = 220
        Top = 278
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '�Ƿ�ĩ��'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox6: TWVComboBox
        Left = 220
        Top = 174
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '��Ŀ���'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*29'
      end
      object edtId: TWVEdit
        Left = 220
        Top = 36
        Width = 120
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<���к�>'
        Visible = False
        WorkView = WorkView
        FieldName = '���к�'
        SynchronizeWhenExit = True
      end
      object edtSubjName: TWVEdit
        Left = 220
        Top = 105
        Width = 120
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 2
        Text = '<��Ŀ����>'
        WorkView = WorkView
        FieldName = '��Ŀ����'
        SynchronizeWhenExit = True
      end
      object WVComboBox7: TWVComboBox
        Left = 220
        Top = 313
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '�ֽ��Ŀ'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox10: TWVComboBox
        Left = 220
        Top = 347
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 9
        WorkView = WorkView
        FieldName = '���п�Ŀ'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox11: TWVComboBox
        Left = 220
        Top = 382
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 10
        Visible = False
        WorkView = WorkView
        FieldName = 'һ��ͨ��Ŀ'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 564
    Top = 327
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
        Name = '��־'
        Caption = '��־'
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
        Name = '��Ŀ����Q'
        Caption = '��Ŀ����Q'
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
        Name = '������Q'
        Caption = '������Q'
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
        Name = '��Ŀ����Q'
        Caption = '��Ŀ����Q'
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
        Name = '��Ŀ���Q'
        Caption = '��Ŀ���Q'
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
        Name = '��Ŀ����Q'
        Caption = '��Ŀ����Q'
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
        Name = '����Q'
        Caption = '����Q'
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
        Name = '��Ŀ����'
        Caption = '��Ŀ����'
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
        DataField = 'scust_auth'
      end
      item
        Name = '��Ŀ����'
        Caption = '��Ŀ����'
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
        DataField = 'sall_name'
      end
      item
        Name = '������'
        Caption = '������'
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
        DataField = 'sname'
      end
      item
        Name = '��Ŀ���'
        Caption = '��Ŀ���'
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
        Name = '��Ŀ����'
        Caption = '��Ŀ����'
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
        Name = '����'
        Caption = '����'
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
        Name = '�Ƿ�ĩ��'
        Caption = '�Ƿ�ĩ��'
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
        Name = '�ֽ��Ŀ'
        Caption = '�ֽ��Ŀ'
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
        Name = '���п�Ŀ'
        Caption = '���п�Ŀ'
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
        Name = 'һ��ͨ��Ŀ'
        Caption = 'һ��ͨ��Ŀ'
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
        Name = '�Ƿ�ɾ��'
        Caption = '�Ƿ�ɾ��'
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
        DataField = 'lvol9'
      end
      item
        Name = '���к�'
        Caption = '���к�'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�̻���ʶ|���̻���ʶ|�̻�����|�̻����|�Ƿ�Ϊ��������|�Ƿ�ΪҶ��' +
          '��|�̻�״̬|����������|�Ƿ���ȡ�����|У��|��ϵ�˰༶���ź�|��' +
          '������|'
      end>
    Left = 536
    Top = 296
  end
  inherited QueryRequest: TWVRequest
    ID = '��Ŀ��Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����Q'
      end
      item
        ParamName = '������'
        FieldName = '������Q'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����Q'
      end
      item
        ParamName = '��Ŀ���'
        FieldName = '��Ŀ���Q'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����Q'
      end
      item
        ParamName = '����'
        FieldName = '����Q'
      end>
    Left = 568
    Top = 296
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '29'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '31'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '30'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol8'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end>
    Left = 596
    Top = 327
  end
  inherited AddRequest: TWVRequest
    ID = '��Ŀ��Ϣ����'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��Ŀ���'
        FieldName = '��Ŀ���'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�Ƿ�ĩ��'
        FieldName = '�Ƿ�ĩ��'
      end
      item
        ParamName = '�ֽ��Ŀ'
        FieldName = '�ֽ��Ŀ'
      end
      item
        ParamName = '���п�Ŀ'
        FieldName = '���п�Ŀ'
      end
      item
        ParamName = 'һ��ͨ��Ŀ'
        FieldName = 'һ��ͨ��Ŀ'
      end>
    Left = 600
    Top = 296
  end
  inherited DeleteRequest: TWVRequest
    ID = '��Ŀ��Ϣ����'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '���к�'
        FieldName = '���к�'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��Ŀ���'
        FieldName = '��Ŀ���'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�Ƿ�ĩ��'
        FieldName = '�Ƿ�ĩ��'
      end
      item
        ParamName = '�ֽ��Ŀ'
        FieldName = '�ֽ��Ŀ'
      end
      item
        ParamName = '���п�Ŀ'
        FieldName = '���п�Ŀ'
      end
      item
        ParamName = 'һ��ͨ��Ŀ'
        FieldName = 'һ��ͨ��Ŀ'
      end>
    Left = 632
    Top = 296
  end
  inherited ChangeRequest: TWVRequest
    ID = '��Ŀ��Ϣ����'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '���к�'
        FieldName = '���к�'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��Ŀ���'
        FieldName = '��Ŀ���'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�Ƿ�ĩ��'
        FieldName = '�Ƿ�ĩ��'
      end
      item
        ParamName = '�ֽ��Ŀ'
        FieldName = '�ֽ��Ŀ'
      end
      item
        ParamName = '���п�Ŀ'
        FieldName = '���п�Ŀ'
      end
      item
        ParamName = 'һ��ͨ��Ŀ'
        FieldName = 'һ��ͨ��Ŀ'
      end>
    Left = 664
    Top = 296
  end
  inherited WVDataSource: TWVDataSource
    Left = 664
    Top = 328
  end
  inherited alDatasetActions: TActionList
    Left = 628
    Top = 328
  end
end

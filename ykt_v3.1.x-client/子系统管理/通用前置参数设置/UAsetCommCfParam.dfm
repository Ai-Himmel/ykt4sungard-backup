inherited faqhsetCommCfParam: TfaqhsetCommCfParam
  Width = 763
  Height = 517
  Caption = 'ͨ��ǰ�ò�������'
  inherited pcPages: TRzPageControl
    Width = 763
    Height = 517
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 464
        Width = 759
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 586
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 673
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 500
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 254
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Width = 177
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 759
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 759
        Height = 431
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lcert_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ǰ�ñ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Caption = 'ǰ�û���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '����ʱ����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '�����ӷ�ֵ'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Caption = '����Ӧ���ܺ�'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Caption = 'ָ����ȶ��к�'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol9'
            PickList.Strings = ()
            Title.Caption = 'ָ��Ӧ���ܺ�'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Caption = 'ָ��ִ�г�ʱʱ��'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol8'
            PickList.Strings = ()
            Title.Caption = 'ָ���ȡʱ����'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol6'
            PickList.Strings = ()
            Title.Caption = '�豸���������ܺ�'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Caption = '�豸����ģʽ'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = '��ˮ�ɼ�Ƶ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol7'
            PickList.Strings = ()
            Title.Caption = 'ָ���������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol10'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ͨѶƽ̨�ڵ��'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ͨѶƽ̨IP��ַ'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol12'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ͨѶƽ̨�˿�'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����ܺ�'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ѯ���ʱ��(����)'
            Width = 90
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 759
        Height = 15
        Align = alTop
        ParentColor = True
        TabOrder = 1
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label16: TLabel [0]
        Left = 42
        Top = 308
        Width = 48
        Height = 12
        Caption = 'ǰ�ñ��'
        Visible = False
      end
      object Label17: TLabel [1]
        Left = 42
        Top = 348
        Width = 48
        Height = 12
        Caption = 'ǰ�û���'
        Visible = False
      end
      object Label18: TLabel [2]
        Left = 22
        Top = 84
        Width = 72
        Height = 12
        Caption = '����ʱ����'
      end
      object Label19: TLabel [3]
        Left = 34
        Top = 124
        Width = 60
        Height = 12
        Caption = '�����ӷ�ֵ'
      end
      object Label20: TLabel [4]
        Left = 10
        Top = 164
        Width = 84
        Height = 12
        Caption = '����Ӧ���ܺ�'
      end
      object Label21: TLabel [5]
        Left = 264
        Top = 44
        Width = 84
        Height = 12
        Caption = 'ָ����ȶ��к�'
      end
      object Label22: TLabel [6]
        Left = 264
        Top = 84
        Width = 84
        Height = 12
        Caption = 'ָ��Ӧ���ܺ�'
      end
      object Label23: TLabel [7]
        Left = 252
        Top = 124
        Width = 96
        Height = 12
        Caption = 'ָ��ִ�г�ʱʱ��'
      end
      object Label24: TLabel [8]
        Left = 252
        Top = 164
        Width = 96
        Height = 12
        Caption = 'ָ���ȡʱ����'
      end
      object Label25: TLabel [9]
        Left = 244
        Top = 348
        Width = 72
        Height = 12
        Caption = '�豸�����־'
        Visible = False
      end
      object Label26: TLabel [10]
        Left = 466
        Top = 44
        Width = 108
        Height = 12
        Caption = '�豸���������ܺ�'
      end
      object Label27: TLabel [11]
        Left = 254
        Top = 380
        Width = 72
        Height = 12
        Caption = '�豸����ģʽ'
        Visible = False
      end
      object Label28: TLabel [12]
        Left = 502
        Top = 84
        Width = 72
        Height = 12
        Caption = '��ˮ�ɼ�Ƶ��'
      end
      object Label29: TLabel [13]
        Left = 502
        Top = 124
        Width = 72
        Height = 12
        Caption = 'ָ���������'
      end
      object Label2: TLabel [14]
        Left = 46
        Top = 44
        Width = 48
        Height = 12
        Caption = 'ǰ�ñ��'
      end
      object Label1: TLabel [15]
        Left = 10
        Top = 204
        Width = 84
        Height = 12
        Caption = 'ͨѶƽ̨�ڵ��'
      end
      object Label3: TLabel [16]
        Left = 264
        Top = 204
        Width = 84
        Height = 12
        Caption = 'ͨѶƽ̨IP��ַ'
      end
      object Label4: TLabel [17]
        Left = 502
        Top = 164
        Width = 72
        Height = 12
        Caption = 'ͨѶƽ̨�˿�'
      end
      object Label5: TLabel [18]
        Left = 46
        Top = 244
        Width = 48
        Height = 12
        Caption = '�����ܺ�'
      end
      object Label6: TLabel [19]
        Left = 240
        Top = 244
        Width = 108
        Height = 12
        Caption = '��ѯ���ʱ��(����)'
      end
      inherited UIPanel2: TUIPanel
        Top = 458
        Width = 759
        TabOrder = 20
        inherited btnOK: TBitBtn
          Left = 587
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 675
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVEdit16: TWVEdit
        Tag = 9
        Left = 100
        Top = 304
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 16
        Text = '<ǰ�ñ��>'
        Visible = False
        WorkView = WorkView
        FieldName = 'ǰ�ñ��'
        SynchronizeWhenExit = True
      end
      object WVEdit17: TWVEdit
        Left = 100
        Top = 344
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 17
        Text = '<ǰ�û���>'
        Visible = False
        WorkView = WorkView
        FieldName = 'ǰ�û���'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit18: TWVEdit
        Tag = 9
        Left = 100
        Top = 80
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 3
        Text = '<����ʱ����>'
        WorkView = WorkView
        FieldName = '����ʱ����'
      end
      object WVDigitalEdit19: TWVEdit
        Tag = 9
        Left = 100
        Top = 120
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 6
        Text = '<�����ӷ�ֵ>'
        WorkView = WorkView
        FieldName = '�����ӷ�ֵ'
      end
      object WVDigitalEdit20: TWVEdit
        Tag = 9
        Left = 100
        Top = 160
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 9
        Text = '<����Ӧ���ܺ�>'
        WorkView = WorkView
        FieldName = '����Ӧ���ܺ�'
      end
      object WVDigitalEdit21: TWVEdit
        Tag = 9
        Left = 352
        Top = 40
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<ָ����ȶ��к�>'
        WorkView = WorkView
        FieldName = 'ָ����ȶ��к�'
      end
      object WVDigitalEdit22: TWVEdit
        Tag = 9
        Left = 352
        Top = 80
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 4
        Text = '<ָ��Ӧ���ܺ�>'
        WorkView = WorkView
        FieldName = 'ָ��Ӧ���ܺ�'
      end
      object WVDigitalEdit23: TWVEdit
        Tag = 9
        Left = 352
        Top = 120
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 7
        Text = '<ָ��ִ�г�ʱʱ��>'
        WorkView = WorkView
        FieldName = 'ָ��ִ�г�ʱʱ��'
      end
      object WVDigitalEdit24: TWVEdit
        Tag = 9
        Left = 352
        Top = 160
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 10
        Text = '<ָ���ȡʱ����>'
        WorkView = WorkView
        FieldName = 'ָ���ȡʱ����'
      end
      object WVEdit25: TWVEdit
        Left = 326
        Top = 344
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 18
        Text = '<�豸�����־>'
        Visible = False
        WorkView = WorkView
        FieldName = '�豸�����־'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit26: TWVEdit
        Tag = 9
        Left = 580
        Top = 40
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<�豸���������ܺ�>'
        WorkView = WorkView
        FieldName = '�豸���������ܺ�'
      end
      object WVEdit27: TWVEdit
        Left = 332
        Top = 376
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 19
        Text = '<�豸����ģʽ>'
        Visible = False
        WorkView = WorkView
        FieldName = '�豸����ģʽ'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit28: TWVEdit
        Tag = 9
        Left = 580
        Top = 80
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 5
        Text = '<��ˮ�ɼ�Ƶ��>'
        WorkView = WorkView
        FieldName = '��ˮ�ɼ�Ƶ��'
      end
      object WVDigitalEdit29: TWVEdit
        Tag = 9
        Left = 580
        Top = 120
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<ָ���������>'
        WorkView = WorkView
        FieldName = 'ָ���������'
      end
      object WVComboBox1: TWVComboBox
        Left = 100
        Top = 40
        Width = 137
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 0
        WorkView = WorkView
        FieldName = 'ǰ�ñ��'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-32'
      end
      object WVEdit1: TWVEdit
        Tag = 9
        Left = 100
        Top = 200
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 12
        Text = '<�ڵ��>'
        WorkView = WorkView
        FieldName = '�ڵ��'
      end
      object edtIp: TWVEdit
        Left = 352
        Top = 200
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 13
        Text = '<ƽ̨IP>'
        WorkView = WorkView
        FieldName = 'ƽ̨IP'
      end
      object WVEdit3: TWVEdit
        Tag = 9
        Left = 580
        Top = 160
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 11
        Text = '<�˿�>'
        WorkView = WorkView
        FieldName = '�˿�'
      end
      object WVEdit4: TWVEdit
        Tag = 9
        Left = 100
        Top = 240
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 14
        Text = '<���ܺ�>'
        WorkView = WorkView
        FieldName = '���ܺ�'
      end
      object WVEdit5: TWVEdit
        Tag = 9
        Left = 352
        Top = 240
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 15
        Text = '<��ѯ���ʱ��>'
        WorkView = WorkView
        FieldName = '��ѯ���ʱ��'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 404
    Top = 303
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
        Name = '��־'
        Caption = '��־'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ǰ�ñ��'
        Caption = 'ǰ�ñ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lcert_code'
      end
      item
        Name = 'ǰ�û���'
        Caption = 'ǰ�û���'
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
        DataField = 'semail'
      end
      item
        Name = '����ʱ����'
        Caption = '����ʱ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '�����ӷ�ֵ'
        Caption = '�����ӷ�ֵ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '����Ӧ���ܺ�'
        Caption = '����Ӧ���ܺ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = 'ָ����ȶ��к�'
        Caption = 'ָ����ȶ��к�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = 'ָ��Ӧ���ܺ�'
        Caption = 'ָ��Ӧ���ܺ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol9'
      end
      item
        Name = 'ָ��ִ�г�ʱʱ��'
        Caption = 'ָ��ִ�г�ʱʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = 'ָ���ȡʱ����'
        Caption = 'ָ���ȡʱ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol8'
      end
      item
        Name = '�豸�����־'
        Caption = '�豸�����־'
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
        DataField = 'sdate0'
      end
      item
        Name = '�豸���������ܺ�'
        Caption = '�豸���������ܺ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol6'
      end
      item
        Name = '�豸����ģʽ'
        Caption = '�豸����ģʽ'
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
        DataField = 'sstatus1'
      end
      item
        Name = '��ˮ�ɼ�Ƶ��'
        Caption = '��ˮ�ɼ�Ƶ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = 'ָ���������'
        Caption = 'ָ���������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol7'
      end
      item
        Name = '������Կ'
        Caption = '������Կ'
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
        DataField = 'sname2'
      end
      item
        Name = '�ڵ��'
        Caption = '�ڵ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol10'
      end
      item
        Name = 'ƽ̨IP'
        Caption = 'ƽ̨IP'
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
        Name = '�˿�'
        Caption = '�˿�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol12'
      end
      item
        Name = '���ܺ�'
        Caption = '���ܺ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lsafe_level'
      end
      item
        Name = '��ѯ���ʱ��'
        Caption = '��ѯ���ʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lsafe_level2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.ǰ�û|��ѯ.����ʱ����|��ѯ.�����ӷ�ֵ|��ѯ.����Ӧ����' +
          '��|��ѯ.ָ����ȶ��к�|��ѯ.ָ��Ӧ���ܺ�|��ѯ.ָ��ִ�г�ʱʱ��' +
          '|��ѯ.ָ���ȡʱ����|��ѯ.�豸�����־|��ѯ.�豸���������ܺ�' +
          '|��ѯ.�豸����ģʽ|��ѯ.��ˮ�ɼ�Ƶ��|��ѯ.ָ���������|��ѯ.����' +
          '��Կ|��ѯ.��־|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|ǰ�û|ǰ�û���|����ʱ����|�����ӷ�ֵ|����Ӧ���ܺ�|ָ�����' +
          '���к�|ָ��Ӧ���ܺ�|ָ��ִ�г�ʱʱ��|ָ���ȡʱ����|�豸����' +
          '��־|�豸���������ܺ�|�豸����ģʽ|��ˮ�ɼ�Ƶ��|ָ���������|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 328
    Top = 304
  end
  inherited QueryRequest: TWVRequest
    ID = 'ͨ��ǰ�ò�����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end>
    Left = 448
    Top = 272
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 364
    Top = 303
  end
  inherited AddRequest: TWVRequest
    ID = 'ͨ��ǰ�ò�������'
    Bindings = <
      item
        ParamName = 'ǰ�ñ��'
        FieldName = 'ǰ�ñ��'
      end
      item
        ParamName = 'ǰ�û���'
        FieldName = 'ǰ�û���'
      end
      item
        ParamName = '����ʱ����'
        FieldName = '����ʱ����'
      end
      item
        ParamName = '�����ӷ�ֵ'
        FieldName = '�����ӷ�ֵ'
      end
      item
        ParamName = '����Ӧ���ܺ�'
        FieldName = '����Ӧ���ܺ�'
      end
      item
        ParamName = 'ָ����ȶ��к�'
        FieldName = 'ָ����ȶ��к�'
      end
      item
        ParamName = 'ָ��Ӧ���ܺ�'
        FieldName = 'ָ��Ӧ���ܺ�'
      end
      item
        ParamName = 'ָ��ִ�г�ʱʱ��'
        FieldName = 'ָ��ִ�г�ʱʱ��'
      end
      item
        ParamName = 'ָ���ȡʱ����'
        FieldName = 'ָ���ȡʱ����'
      end
      item
        ParamName = '�豸�����־'
        FieldName = '�豸�����־'
      end
      item
        ParamName = '�豸���������ܺ�'
        FieldName = '�豸���������ܺ�'
      end
      item
        ParamName = '�豸����ģʽ'
        FieldName = '�豸����ģʽ'
      end
      item
        ParamName = '��ˮ�ɼ�Ƶ��'
        FieldName = '��ˮ�ɼ�Ƶ��'
      end
      item
        ParamName = 'ָ���������'
        FieldName = 'ָ���������'
      end
      item
        ParamName = '������Կ'
        FieldName = '������Կ'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '�ڵ��'
        FieldName = '�ڵ��'
      end
      item
        ParamName = 'ƽ̨IP'
        FieldName = 'ƽ̨IP'
      end
      item
        ParamName = '�˿�'
        FieldName = '�˿�'
      end
      item
        ParamName = '���ܺ�'
        FieldName = '���ܺ�'
      end
      item
        ParamName = '��ѯ���ʱ��'
        FieldName = '��ѯ���ʱ��'
      end>
    Left = 328
    Top = 272
  end
  inherited DeleteRequest: TWVRequest
    ID = 'ͨ��ǰ�ò�������'
    Bindings = <
      item
        ParamName = 'ǰ�ñ��'
        FieldName = 'ǰ�ñ��'
      end
      item
        ParamName = 'ǰ�û���'
        FieldName = 'ǰ�û���'
      end
      item
        ParamName = '����ʱ����'
        FieldName = '����ʱ����'
      end
      item
        ParamName = '�����ӷ�ֵ'
        FieldName = '�����ӷ�ֵ'
      end
      item
        ParamName = '����Ӧ���ܺ�'
        FieldName = '����Ӧ���ܺ�'
      end
      item
        ParamName = 'ָ����ȶ��к�'
        FieldName = 'ָ����ȶ��к�'
      end
      item
        ParamName = 'ָ��Ӧ���ܺ�'
        FieldName = 'ָ��Ӧ���ܺ�'
      end
      item
        ParamName = 'ָ��ִ�г�ʱʱ��'
        FieldName = 'ָ��ִ�г�ʱʱ��'
      end
      item
        ParamName = 'ָ���ȡʱ����'
        FieldName = 'ָ���ȡʱ����'
      end
      item
        ParamName = '�豸�����־'
        FieldName = '�豸�����־'
      end
      item
        ParamName = '�豸���������ܺ�'
        FieldName = '�豸���������ܺ�'
      end
      item
        ParamName = '�豸����ģʽ'
        FieldName = '�豸����ģʽ'
      end
      item
        ParamName = '��ˮ�ɼ�Ƶ��'
        FieldName = '��ˮ�ɼ�Ƶ��'
      end
      item
        ParamName = 'ָ���������'
        FieldName = 'ָ���������'
      end
      item
        ParamName = '������Կ'
        FieldName = '������Կ'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '�ڵ��'
        FieldName = '�ڵ��'
      end
      item
        ParamName = 'ƽ̨IP'
        FieldName = 'ƽ̨IP'
      end
      item
        ParamName = '�˿�'
        FieldName = '�˿�'
      end
      item
        ParamName = '���ܺ�'
        FieldName = '���ܺ�'
      end
      item
        ParamName = '��ѯ���ʱ��'
        FieldName = '��ѯ���ʱ��־'
      end>
    Left = 368
    Top = 272
  end
  inherited ChangeRequest: TWVRequest
    ID = 'ͨ��ǰ�ò�������'
    Bindings = <
      item
        ParamName = 'ǰ�ñ��'
        FieldName = 'ǰ�ñ��'
      end
      item
        ParamName = 'ǰ�û���'
        FieldName = 'ǰ�û���'
      end
      item
        ParamName = '����ʱ����'
        FieldName = '����ʱ����'
      end
      item
        ParamName = '�����ӷ�ֵ'
        FieldName = '�����ӷ�ֵ'
      end
      item
        ParamName = '����Ӧ���ܺ�'
        FieldName = '����Ӧ���ܺ�'
      end
      item
        ParamName = 'ָ����ȶ��к�'
        FieldName = 'ָ����ȶ��к�'
      end
      item
        ParamName = 'ָ��Ӧ���ܺ�'
        FieldName = 'ָ��Ӧ���ܺ�'
      end
      item
        ParamName = 'ָ��ִ�г�ʱʱ��'
        FieldName = 'ָ��ִ�г�ʱʱ��'
      end
      item
        ParamName = 'ָ���ȡʱ����'
        FieldName = 'ָ���ȡʱ����'
      end
      item
        ParamName = '�豸�����־'
        FieldName = '�豸�����־'
      end
      item
        ParamName = '�豸���������ܺ�'
        FieldName = '�豸���������ܺ�'
      end
      item
        ParamName = '�豸����ģʽ'
        FieldName = '�豸����ģʽ'
      end
      item
        ParamName = '��ˮ�ɼ�Ƶ��'
        FieldName = '��ˮ�ɼ�Ƶ��'
      end
      item
        ParamName = 'ָ���������'
        FieldName = 'ָ���������'
      end
      item
        ParamName = '������Կ'
        FieldName = '������Կ'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '�ڵ��'
        FieldName = '�ڵ��'
      end
      item
        ParamName = 'ƽ̨IP'
        FieldName = 'ƽ̨IP'
      end
      item
        ParamName = '�˿�'
        FieldName = '�˿�'
      end
      item
        ParamName = '���ܺ�'
        FieldName = '���ܺ�'
      end
      item
        ParamName = '��ѯ���ʱ��'
        FieldName = '��ѯ���ʱ��'
      end>
    Left = 408
    Top = 272
  end
  inherited WVDataSource: TWVDataSource
    Left = 444
    Top = 303
  end
  inherited alDatasetActions: TActionList
    Left = 444
    Top = 340
  end
end

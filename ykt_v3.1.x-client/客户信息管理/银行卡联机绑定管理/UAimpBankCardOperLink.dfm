inherited faqhimpBankCardOperLink: TfaqhimpBankCardOperLink
  Width = 873
  Height = 477
  Caption = '�ͻ��������'
  inherited pcPages: TRzPageControl
    Width = 873
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 869
        TabOrder = 3
        object Label10: TLabel [0]
          Left = 94
          Top = 9
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 528
          Enabled = False
        end
        inherited btnChange: TBitBtn [2]
          Left = 614
          Enabled = False
        end
        inherited btnQuery: TBitBtn [3]
          Left = 442
        end
        inherited btnDelete: TBitBtn
          Left = 701
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 0
          Width = 161
          TabOrder = 7
          Visible = False
        end
        object btnPatchDel: TBitBtn
          Left = 787
          Top = 3
          Width = 79
          Height = 25
          Hint = 'ɾ����ǰѡ�е���Ŀ'
          Anchors = [akTop, akRight]
          Caption = '����ɾ��'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 135
          Top = 5
          Width = 98
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 6
          Text = '<���κ�>'
          WorkView = WorkView1
          FieldName = '���κ�'
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 869
      end
      inherited Grid: TRzDBGrid
        Top = 73
        Width = 869
        Height = 351
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'Sname2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��¼��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������κ�'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����Ա'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ѧ/����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Scard0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���п���'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ɾ��־'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����״̬'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ע'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'Sbank_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���д���'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 869
        Height = 55
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label3: TLabel
          Left = 414
          Top = 10
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        object Label6: TLabel
          Left = 40
          Top = 10
          Width = 42
          Height = 12
          Caption = 'ѧ/����'
        end
        object Label8: TLabel
          Left = 218
          Top = 34
          Width = 48
          Height = 12
          Caption = '����״̬'
        end
        object Label9: TLabel
          Left = 218
          Top = 10
          Width = 48
          Height = 12
          Caption = '�ͻ�����'
        end
        object Label11: TLabel
          Left = 578
          Top = 34
          Width = 48
          Height = 12
          Caption = '���д���'
          Visible = False
        end
        object Label13: TLabel
          Left = 34
          Top = 34
          Width = 48
          Height = 12
          Caption = '���п���'
        end
        object Label7: TLabel
          Left = 590
          Top = 10
          Width = 36
          Height = 12
          Caption = '�ͻ���'
        end
        object WVEdit3: TWVEdit
          Left = 460
          Top = 6
          Width = 125
          Height = 20
          Color = clBtnHighlight
          MaxLength = 50
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.���κ�>'
          WorkView = WorkView
          FieldName = '��ѯ.���κ�'
        end
        object WVEdit6: TWVEdit
          Left = 92
          Top = 6
          Width = 119
          Height = 20
          CharCase = ecUpperCase
          Color = clBtnHighlight
          MaxLength = 50
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.ѧ����>'
          WorkView = WorkView
          FieldName = '��ѯ.ѧ����'
        end
        object WVEdit9: TWVEdit
          Left = 276
          Top = 6
          Width = 118
          Height = 20
          Color = clBtnHighlight
          MaxLength = 50
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�ͻ�����>'
          WorkView = WorkView
          FieldName = '��ѯ.�ͻ�����'
        end
        object WVEdit13: TWVEdit
          Left = 92
          Top = 30
          Width = 119
          Height = 20
          Color = clBtnHighlight
          MaxLength = 50
          ReadOnly = False
          TabOrder = 4
          Text = '<��ѯ.���п���>'
          WorkView = WorkView
          FieldName = '��ѯ.���п���'
        end
        object cbbQFeeType: TWVComboBox
          Left = 276
          Top = 32
          Width = 118
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '��ѯ.��״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*10'
        end
        object WVComboBox7: TWVComboBox
          Left = 636
          Top = 31
          Width = 118
          Height = 18
          Style = csOwnerDrawFixed
          Color = clBtnHighlight
          ItemHeight = 12
          TabOrder = 5
          Visible = False
          WorkView = WorkView
          FieldName = '��ѯ.���д���'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*110'
        end
        object edtCustNo: TWVEdit
          Left = 636
          Top = 6
          Width = 123
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 3
          Text = '<��ѯ.�ͻ���>'
          WorkView = WorkView
          FieldName = '��ѯ.�ͻ���'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label1: TLabel [0]
        Left = 84
        Top = 68
        Width = 36
        Height = 12
        Caption = '��¼��'
      end
      object Label21: TLabel [1]
        Left = 78
        Top = 100
        Width = 42
        Height = 12
        Caption = 'ѧ/����'
      end
      object Label32: TLabel [2]
        Left = 62
        Top = 421
        Width = 48
        Height = 12
        Caption = '�ͻ��� *'
        Visible = False
      end
      object Label2: TLabel [3]
        Left = 72
        Top = 132
        Width = 48
        Height = 12
        Caption = '���п���'
      end
      object Label12: TLabel [4]
        Left = 84
        Top = 164
        Width = 36
        Height = 12
        Caption = '���κ�'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 869
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 697
        end
        inherited btnCancel: TBitBtn
          Left = 785
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtCustId: TWVEdit
        Left = 129
        Top = 64
        Width = 159
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 0
        Text = '<��¼��>'
        WorkView = WorkView
        FieldName = '��¼��'
        SynchronizeWhenExit = True
      end
      object edtStuempNo: TWVEdit
        Left = 129
        Top = 95
        Width = 159
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<ѧ����>'
        WorkView = WorkView
        FieldName = 'ѧ����'
        SynchronizeWhenExit = True
      end
      object edtOldBankCardNo: TWVEdit
        Left = 129
        Top = 127
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<���п���>'
        WorkView = WorkView
        FieldName = '���п���'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 129
        Top = 159
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<���κ�>'
        WorkView = WorkView
        FieldName = '���κ�'
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
        GroupIndex = 1
        DataField = '@Dataset'
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
        Name = '������־'
        Caption = '������־'
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
        Name = '��ѯ.���κ�'
        Caption = '��ѯ.���κ�'
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
        Name = '��ѯ.�ͻ���'
        Caption = '��ѯ.�ͻ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
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
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�ͻ�����'
        Caption = '��ѯ.�ͻ�����'
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
        Name = '��ѯ.���п���'
        Caption = '��ѯ.���п���'
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
        Name = '��ѯ.���д���'
        Caption = '��ѯ.���д���'
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
        Name = '��ѯ.��״̬'
        Caption = '��ѯ.��״̬'
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '��¼��'
        Caption = '��¼��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
        DataField = 'sname2'
      end
      item
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        DataField = 'spager'
      end
      item
        Name = '���п���'
        Caption = '���п���'
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
        DataField = 'Scard0'
      end
      item
        Name = '���κ�'
        Caption = '���κ�'
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
        DataField = 'scust_limit'
      end>
    InvalidColor = clBtnHighlight
    Left = 336
    Top = 248
  end
  inherited QueryRequest: TWVRequest
    ID = '���п��󶨲�ѯ����'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��״̬'
        FieldName = '��ѯ.��״̬'
      end
      item
        ParamName = '���κ�'
        FieldName = '��ѯ.���κ�'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '��ѯ.�ͻ�����'
      end
      item
        ParamName = 'ѧ����'
        FieldName = '��ѯ.ѧ����'
      end
      item
        ParamName = '���д���'
        FieldName = '��ѯ.���д���'
      end
      item
        ParamName = '���п���'
        FieldName = '��ѯ.���п���'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '��ѯ.�ͻ���'
      end>
    Left = 464
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '110'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '33'
      end
      item
        FieldName = 'Lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '44'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '10'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end>
    Left = 396
  end
  inherited AddRequest: TWVRequest
    ID = '�������п���������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��¼��'
        FieldName = '��¼��'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '���п���'
        FieldName = '���п���'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end>
    Left = 368
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '�������п���������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��¼��'
        FieldName = '��¼��'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '���п���'
        FieldName = '���п���'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end>
    Left = 400
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '�������п���������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��¼��'
        FieldName = '��¼��'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '���п���'
        FieldName = '���п���'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
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
    Left = 336
    Top = 328
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '���п�����ɾ������'
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
      end>
    AfterExec = CheckReturnData
    Left = 368
    Top = 328
  end
end

inherited faqhgateSerialDetailQuery: TfaqhgateSerialDetailQuery
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 523
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 2
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 127
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label1: TLabel
      Left = 54
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label2: TLabel
      Left = 242
      Top = 9
      Width = 48
      Height = 12
      Caption = '���׿���'
    end
    object Label3: TLabel
      Left = 442
      Top = 9
      Width = 48
      Height = 12
      Caption = '������'
    end
    object Label4: TLabel
      Left = 42
      Top = 33
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object Label5: TLabel
      Left = 242
      Top = 33
      Width = 48
      Height = 12
      Caption = '��ʼʱ��'
    end
    object Label6: TLabel
      Left = 442
      Top = 33
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label7: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '����ʱ��'
    end
    object Label8: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '�豸��ʶ'
    end
    object Label9: TLabel
      Left = 418
      Top = 57
      Width = 72
      Height = 12
      Caption = '�豸������'
    end
    object Label10: TLabel
      Left = 66
      Top = 81
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label11: TLabel
      Left = 254
      Top = 81
      Width = 36
      Height = 12
      Caption = 'ѧ����'
    end
    object lbl1: TLabel
      Left = 466
      Top = 81
      Width = 24
      Height = 12
      Caption = '�¼�'
    end
    object Label12: TLabel
      Left = 42
      Top = 104
      Width = 48
      Height = 12
      Caption = '�ͻ����'
    end
    object Label13: TLabel
      Left = 242
      Top = 102
      Width = 48
      Height = 12
      Caption = '���ڲ���'
    end
    object lblMachineType: TWVLabel
      Left = 442
      Top = 105
      Width = 48
      Height = 12
      Caption = '�豸����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 117
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object WVEdit2: TWVEdit
      Left = 300
      Top = 5
      Width = 117
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<���׿���>'
      WorkView = WorkView
      FieldName = '���׿���'
    end
    object WVEdit3: TWVEdit
      Left = 500
      Top = 5
      Width = 123
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<������>'
      WorkView = WorkView
      FieldName = '������'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 29
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object WVEdit5: TWVEdit
      Left = 300
      Top = 29
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<��ʼʱ��>'
      WorkView = WorkView
      FieldName = '��ʼʱ��'
    end
    object WVEdit6: TWVEdit
      Left = 500
      Top = 29
      Width = 123
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 5
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 53
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 6
      Text = '<����ʱ��>'
      WorkView = WorkView
      FieldName = '����ʱ��'
    end
    object WVEdit8: TWVEdit
      Left = 300
      Top = 53
      Width = 117
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 7
      Text = '<�豸��ʶ>'
      WorkView = WorkView
      FieldName = '�豸��ʶ'
    end
    object WVEdit9: TWVEdit
      Left = 500
      Top = 53
      Width = 123
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 8
      Text = '<�豸������>'
      WorkView = WorkView
      FieldName = '�豸������'
    end
    object WVEdit10: TWVEdit
      Left = 100
      Top = 77
      Width = 117
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit11: TWVEdit
      Left = 300
      Top = 77
      Width = 117
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 11
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
    end
    object WVComboBox7: TWVComboBox
      Left = 500
      Top = 76
      Width = 123
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '�¼�'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*86'
    end
    object WVComboBox1: TWVComboBox
      Tag = 1
      Left = 100
      Top = 99
      Width = 117
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 13
      WorkView = WorkView
      FieldName = '�ͻ����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVComboBox6: TWVComboBox
      Tag = 1
      Left = 301
      Top = 98
      Width = 117
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 12
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object cbbMachineType: TWVComboBox
      Left = 500
      Top = 103
      Width = 123
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 14
      WorkView = WorkView
      FieldName = '�豸����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '47'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 145
    Width = 700
    Height = 314
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 314
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '�ͻ���'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '���׿���'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Caption = '������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Caption = '��������'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Caption = '����ʱ��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '�豸��ʶ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Caption = '�豸����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Caption = '�¼�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '�ɼ�����'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Caption = '�ɼ�ʱ��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsmess'
          PickList.Strings = ()
          Title.Caption = '��ע'
          Width = 200
          Visible = True
        end>
    end
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
      end
      item
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '������'
        Caption = '������'
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
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
        Name = '��ʼʱ��'
        Caption = '��ʼʱ��'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
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
        Name = '�豸������'
        Caption = '�豸������'
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
      end
      item
        Name = '�¼�'
        Caption = '�¼�'
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
      end
      item
        Name = '�豸����'
        Caption = '�豸����'
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
        MonitorValueChangedFields = 
          '|�ͻ���|���׿���|������|��ʼ����|��ʼʱ��|��������|����ʱ��|��' +
          '����ʶ|�豸������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�Ž���ˮ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = '��ʼʱ��'
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
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
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
        ParamName = '�¼�'
        FieldName = '�¼�'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '86'
      end
      item
        FieldName = 'scust_auth2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-34'
      end>
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
end

inherited faqhaccountTradeQuery: TfaqhaccountTradeQuery
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 523
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 610
      TabOrder = 2
    end
    object btnReadCard: TBitBtn
      Left = 435
      Top = 3
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '������ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnReadCardClick
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
    Height = 151
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label1: TLabel
      Left = 18
      Top = 33
      Width = 72
      Height = 12
      Caption = '���˿�ʼ����'
    end
    object Label2: TLabel
      Left = 218
      Top = 33
      Width = 72
      Height = 12
      Caption = '���˽�������'
    end
    object Label3: TLabel
      Left = 18
      Top = 9
      Width = 72
      Height = 12
      Caption = '���׿�ʼ����'
    end
    object Label4: TLabel
      Left = 218
      Top = 9
      Width = 72
      Height = 12
      Caption = '���׽�������'
    end
    object Label5: TLabel
      Left = 454
      Top = 9
      Width = 36
      Height = 12
      Caption = '��Ŀ��'
    end
    object Label6: TLabel
      Left = 466
      Top = 33
      Width = 24
      Height = 12
      Caption = '�˺�'
    end
    object Label7: TLabel
      Left = 54
      Top = 57
      Width = 36
      Height = 12
      Caption = '�ʻ���'
    end
    object Label8: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '�ն˱��'
    end
    object Label9: TLabel
      Left = 430
      Top = 57
      Width = 60
      Height = 12
      Caption = '�ն���ˮ��'
    end
    object Label10: TLabel
      Left = 454
      Top = 81
      Width = 36
      Height = 12
      Caption = '������'
    end
    object Label11: TLabel
      Left = 242
      Top = 81
      Width = 48
      Height = 12
      Caption = 'ƾ֤����'
    end
    object Label12: TLabel
      Left = 54
      Top = 81
      Width = 36
      Height = 12
      Caption = '�̻���'
    end
    object Label13: TLabel
      Left = 42
      Top = 105
      Width = 48
      Height = 12
      Caption = '��ʾ����'
    end
    object Label14: TLabel
      Left = 266
      Top = 105
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label15: TLabel
      Left = 454
      Top = 105
      Width = 36
      Height = 12
      Caption = '����Ա'
    end
    object Label16: TLabel
      Left = 48
      Top = 129
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object edtJbDate: TWVEdit
      Left = 100
      Top = 29
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<���˿�ʼ����>'
      WorkView = WorkView
      FieldName = '���˿�ʼ����'
    end
    object edtJEDate: TWVEdit
      Left = 300
      Top = 29
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<���˽�ֹ����>'
      WorkView = WorkView
      FieldName = '���˽�ֹ����'
    end
    object edtTBDate: TWVEdit
      Left = 100
      Top = 5
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<���׿�ʼ����>'
      WorkView = WorkView
      FieldName = '���׿�ʼ����'
    end
    object edtTEdate: TWVEdit
      Left = 300
      Top = 5
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<���׽�ֹ����>'
      WorkView = WorkView
      FieldName = '���׽�ֹ����'
    end
    object WVEdit6: TWVEdit
      Left = 501
      Top = 29
      Width = 141
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<�˺�>'
      WorkView = WorkView
      FieldName = '�˺�'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 53
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 6
      Text = '<�ʻ���>'
      WorkView = WorkView
      FieldName = '�ʻ���'
    end
    object edtSeriId: TWVEdit
      Left = 501
      Top = 53
      Width = 141
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 8
      Text = '<�ն���ˮ��>'
      WorkView = WorkView
      FieldName = '�ն���ˮ��'
    end
    object WVEdit11: TWVEdit
      Left = 300
      Top = 77
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<ƾ֤����>'
      WorkView = WorkView
      FieldName = 'ƾ֤����'
    end
    object edtBusiId: TWVEdit
      Left = 100
      Top = 77
      Width = 112
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 9
      Text = '<�̻���>'
      WorkView = WorkView
      FieldName = '�̻���'
    end
    object WVEdit13: TWVEdit
      Left = 100
      Top = 101
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<��ʾ����>'
      WorkView = WorkView
      FieldName = '��ʾ����'
    end
    object edtCardNo: TWVEdit
      Left = 300
      Top = 101
      Width = 112
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 13
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVComboBox3: TWVComboBox
      Left = 501
      Top = 77
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-16'
    end
    object WVComboBox1: TWVComboBox
      Left = 501
      Top = 5
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '��Ŀ��'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-25'
    end
    object WVComboBox4: TWVComboBox
      Left = 501
      Top = 101
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 14
      WorkView = WorkView
      FieldName = '����Ա'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object edtStationNo: TWVEdit
      Left = 300
      Top = 53
      Width = 112
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 7
      Text = '<�ն˱��>'
      WorkView = WorkView
      FieldName = '�ն˱��'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 125
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 15
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 169
    Width = 700
    Height = 290
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 290
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lwithdraw_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ն˱��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ն���ˮ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ˮ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol9'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ƾ֤����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ƾ֤����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ժҪ'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ŀ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ʺ�'
          Width = 70
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
          FieldName = 'sbankname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ʻ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smain_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Է���Ŀ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Է��˺�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbankname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Է��ʻ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա����'
          Width = 60
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
        Name = '���˿�ʼ����'
        Caption = '���˿�ʼ����'
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
        GetPrevChar = '*'
      end
      item
        Name = '���˽�ֹ����'
        Caption = '���˽�ֹ����'
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
        GetPrevChar = '*'
      end
      item
        Name = '���׿�ʼ����'
        Caption = '���׿�ʼ����'
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
        GetPrevChar = '*'
      end
      item
        Name = '���׽�ֹ����'
        Caption = '���׽�ֹ����'
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
        GetPrevChar = '*'
      end
      item
        Name = '��Ŀ��'
        Caption = '��Ŀ��'
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
      end
      item
        Name = '�˺�'
        Caption = '�˺�'
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
      end
      item
        Name = '�ʻ���'
        Caption = '�ʻ���'
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
      end
      item
        Name = '�ն˱��'
        Caption = '�ն˱��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '�ն���ˮ��'
        Caption = '�ն���ˮ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        DefaultValue = 0
        GetPrevChar = '*'
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = 'ƾ֤����'
        Caption = 'ƾ֤����'
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
      end
      item
        Name = '�̻���'
        Caption = '�̻���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '��ʾ����'
        Caption = '��ʾ����'
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
      end
      item
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '����Ա'
        Caption = '����Ա'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|���˿�ʼ����|���˽�ֹ����|���׿�ʼ����|���׽�ֹ����|��Ŀ��|�˺�' +
          '|�ʻ���|�ն˱��|�ն���ˮ��|������|ƾ֤����|�̻���|��ʾ����|����' +
          '|Ǯ����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�ʻ�������ϸ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���˿�ʼ����'
        FieldName = '���˿�ʼ����'
      end
      item
        ParamName = '���˽�ֹ����'
        FieldName = '���˽�ֹ����'
      end
      item
        ParamName = '���׿�ʼ����'
        FieldName = '���׿�ʼ����'
      end
      item
        ParamName = '���׽�ֹ����'
        FieldName = '���׽�ֹ����'
      end
      item
        ParamName = '��Ŀ��'
        FieldName = '��Ŀ��'
      end
      item
        ParamName = '�˺�'
        FieldName = '�˺�'
      end
      item
        ParamName = '�ʻ���'
        FieldName = '�ʻ���'
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
      end
      item
        ParamName = '�ն���ˮ��'
        FieldName = '�ն���ˮ��'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '��ʾ����'
        FieldName = '��ʾ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'scust_auth'
        DataPresentType = 'idobjects'
        DataPresentParam = '-25'
      end
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-9'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-10'
      end
      item
        FieldName = 'lbank_acc_type2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-55'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '26'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'idobjects'
        DataPresentParam = '63'
      end
      item
        FieldName = 'scust_auth2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-25'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
end

inherited faqhPatchCheck: TfaqhPatchCheck
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 523
      TabOrder = 2
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Top = 1000
      TabOrder = 5
      Visible = False
    end
    object btnCheck: TBitBtn
      Left = 615
      Top = 3
      Width = 79
      Height = 25
      Hint = '����ƾ֤'
      Anchors = [akTop, akRight]
      Caption = 'ƾ֤���'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnCheckClick
    end
    object btnCancelCheck: TBitBtn
      Left = 146
      Top = 3
      Width = 79
      Height = 25
      Hint = '����ƾ֤ȡ��'
      Anchors = [akTop, akRight]
      Caption = 'ȡ�����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Visible = False
      OnClick = btnCancelCheckClick
    end
    object btnEnter: TBitBtn
      Left = 238
      Top = 3
      Width = 79
      Height = 25
      Hint = 'ƾ֤����'
      Anchors = [akTop, akRight]
      Caption = 'ƾ֤����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Visible = False
      OnClick = btnEnterClick
    end
    object chkSelect: TWVCheckBox
      Left = 14
      Top = 8
      Width = 43
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 4
      OnClick = chkSelectClick
      DefaultChecked = False
      PresentType = cdpEqual
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label2: TLabel
      Left = 18
      Top = 9
      Width = 72
      Height = 12
      Caption = '����ڼ�(��)'
    end
    object Label3: TLabel
      Left = 218
      Top = 9
      Width = 72
      Height = 12
      Caption = '����ڼ�(��)'
    end
    object Label4: TLabel
      Left = 442
      Top = 9
      Width = 48
      Height = 12
      Caption = 'ƾ֤����'
    end
    object Label5: TLabel
      Left = 42
      Top = 33
      Width = 48
      Height = 12
      Caption = 'ƾ֤����'
    end
    object Label6: TLabel
      Left = 254
      Top = 33
      Width = 36
      Height = 12
      Caption = 'ƾ֤��'
    end
    object Label9: TLabel
      Left = 430
      Top = 33
      Width = 60
      Height = 12
      Caption = '�Ƿ��ֹ���'
    end
    object edtYear: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<����ڼ�(��)>'
      WorkView = WorkView
      FieldName = '����ڼ�(��)'
    end
    object edtMonth: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<����ڼ�(��)>'
      WorkView = WorkView
      FieldName = '����ڼ�(��)'
    end
    object edtDate: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<ƾ֤����>'
      WorkView = WorkView
      FieldName = 'ƾ֤����'
    end
    object edtVoucherNo: TWVEdit
      Left = 300
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 4
      Text = '<ƾ֤��>'
      WorkView = WorkView
      FieldName = 'ƾ֤��'
    end
    object cbbVoucherType: TWVComboBox
      Left = 100
      Top = 29
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = 'ƾ֤����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-61'
    end
    object cbbManual: TWVComboBox
      Left = 500
      Top = 29
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '�Ƿ��ֹ���ƾ֤'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*162'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 700
    Height = 386
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 386
      TabOrder = 1
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol10'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol11'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��'
          Width = 30
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ƾ֤����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ƾ֤����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ƾ֤��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol9'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���㷽ʽ'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�к�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ժҪ'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ƾ֤״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֹ��ʱ�־'
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
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ŀ����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�跽������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ƶ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scheck_emp'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'schange_emp'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end>
    end
    object lvVoucher: TRzListView
      Left = 0
      Top = 0
      Width = 700
      Height = 386
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = 'ƾ֤����'
          Width = 100
        end
        item
          Caption = 'ID'
          Width = 1
        end
        item
          Alignment = taCenter
          Caption = 'ƾ֤��'
          Width = 100
        end
        item
          Caption = 'ժҪ'
          Width = 100
        end
        item
          Alignment = taRightJustify
          Caption = '�跽���ϼ�'
          Width = 90
        end
        item
          Alignment = taRightJustify
          Caption = '�������ϼ�'
          Width = 90
        end
        item
          Caption = '���״̬'
          Width = 70
        end
        item
          Caption = '����״̬'
          Width = 70
        end
        item
          Caption = '�ֹ��˱�־'
          Width = 80
        end
        item
          Caption = '�Ƶ�'
          Width = 70
        end
        item
          Caption = '����'
          Width = 70
        end
        item
          Caption = '���'
          Width = 70
        end
        item
          Caption = '����'
          Width = 70
        end>
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnClick = lvVoucherClick
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
        Name = '��־'
        Caption = '��־'
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
        Name = '����ڼ�(��)'
        Caption = '����ڼ�(��)'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '����ڼ�(��)'
        Caption = '����ڼ�(��)'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ƾ֤����'
        Caption = 'ƾ֤����'
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
        Name = 'ƾ֤��'
        Caption = 'ƾ֤��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��Ŀ����'
        Caption = '��Ŀ����'
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
        Name = '״̬'
        Caption = '״̬'
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
        Name = '�Ƿ��ֹ���ƾ֤'
        Caption = '�Ƿ��ֹ���ƾ֤'
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
        Name = '��ѯ����'
        Caption = '��ѯ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = 'ƾ֤����.��ѯ'
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
        ParamName = '����ڼ�(��)'
        FieldName = '����ڼ�(��)'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '����ڼ�(��)'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = 'ƾ֤��'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = '�Ƿ��ֹ���ƾ֤'
        FieldName = '�Ƿ��ֹ���ƾ֤'
      end
      item
        ParamName = '��ѯ����'
        FieldName = '��ѯ����'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'idobjects'
        DataPresentParam = '160'
      end
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'idobjects'
        DataPresentParam = '-61'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'scheck_emp'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'schange_emp'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'idobjects'
        DataPresentParam = '165'
      end
      item
        FieldName = 'lbank_acc_type2'
        DataPresentType = 'idobjects'
        DataPresentParam = '162'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '161'
      end>
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 224
  end
  object wvVOper: TWorkView
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
        Name = '��־'
        Caption = '��־'
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
        Name = '����ڼ�(��)'
        Caption = '����ڼ�(��)'
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
        Name = '����ڼ�(��)'
        Caption = '����ڼ�(��)'
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
        Name = 'ƾ֤����'
        Caption = 'ƾ֤����'
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
        Name = 'ƾ֤��'
        Caption = 'ƾ֤��'
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
        Name = 'ƾ֤ID'
        Caption = 'ƾ֤ID'
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
    FieldsMonitors = <>
    Left = 164
    Top = 263
  end
  object wvrVOper: TWVRequest
    WorkView = wvVOper
    ID = 'ƾ֤����'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '����ڼ�(��)'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '����ڼ�(��)'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = 'ƾ֤��'
      end
      item
        ParamName = 'ƾ֤ID'
        FieldName = 'ƾ֤ID'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 264
  end
  object wvVoucherQ: TWorkView
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
        Name = '��־'
        Caption = '��־'
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
        Name = '��ѯ.����ڼ�(��)'
        Caption = '��ѯ.����ڼ�(��)'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.����ڼ�(��)'
        Caption = '��ѯ.����ڼ�(��)'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.ƾ֤����'
        Caption = '��ѯ.ƾ֤����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.ƾ֤����'
        Caption = '��ѯ.ƾ֤����'
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
        Name = '��ѯ.ƾ֤��'
        Caption = '��ѯ.ƾ֤��'
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
        Name = '��ѯ.��Ŀ����'
        Caption = '��ѯ.��Ŀ����'
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
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
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
        Name = '��ѯ.ID'
        Caption = '��ѯ.ID'
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
        MonitorValueChangedFields = '|��ѯ.רҵ����|'
      end
      item
        MonitorValueChangedFields = '|רҵ����|רҵ����|'
      end>
    Left = 167
    Top = 304
  end
  object wvrVoucherQ: TWVRequest
    WorkView = wvVoucherQ
    ID = 'ƾ֤����.��ѯ'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '��ѯ.����ڼ�(��)'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '��ѯ.����ڼ�(��)'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = '��ѯ.ƾ֤����'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = '��ѯ.ƾ֤����'
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = '��ѯ.ƾ֤��'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��ѯ.��Ŀ����'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end
      item
        ParamName = 'ID'
        FieldName = '��ѯ.ID'
      end>
    Left = 200
    Top = 304
  end
end

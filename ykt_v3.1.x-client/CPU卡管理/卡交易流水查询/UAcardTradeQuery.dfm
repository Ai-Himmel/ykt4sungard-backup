inherited faqhcardTradeQuery: TfaqhcardTradeQuery
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
      Left = 424
      Top = 83
      Width = 48
      Height = 12
      Caption = '�ն˱��'
    end
    object Label4: TLabel
      Left = 30
      Top = 81
      Width = 60
      Height = 12
      Caption = '�ն���ˮ��'
    end
    object Label5: TLabel
      Left = 436
      Top = 35
      Width = 36
      Height = 12
      Caption = '������'
    end
    object Label6: TLabel
      Left = 242
      Top = 81
      Width = 48
      Height = 12
      Caption = 'ƾ֤����'
    end
    object Label7: TLabel
      Left = 54
      Top = 105
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label8: TLabel
      Left = 248
      Top = 105
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label9: TLabel
      Left = 424
      Top = 59
      Width = 48
      Height = 12
      Caption = '��ʾ����'
    end
    object Label10: TLabel
      Left = 66
      Top = 129
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label11: TLabel
      Left = 436
      Top = 11
      Width = 36
      Height = 12
      Caption = '����Ա'
    end
    object Label12: TLabel
      Left = 242
      Top = 129
      Width = 48
      Height = 12
      Caption = '��ˮ״̬'
    end
    object Label13: TLabel
      Left = 18
      Top = 9
      Width = 72
      Height = 12
      Caption = '���׿�ʼ����'
    end
    object Label14: TLabel
      Left = 218
      Top = 9
      Width = 72
      Height = 12
      Caption = '���׽�������'
    end
    object Label15: TLabel
      Left = 424
      Top = 106
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object Label16: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '��ʼʱ��'
    end
    object Label17: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '����ʱ��'
    end
    object lbl1: TLabel
      Left = 200
      Top = 300
      Width = 48
      Height = 12
      Caption = '���ױ�־'
      Visible = False
    end
    object Label18: TLabel
      Left = 426
      Top = 128
      Width = 48
      Height = 12
      Caption = '�ⲿ����'
    end
    object edtBDate: TWVEdit
      Left = 100
      Top = 29
      Width = 110
      Height = 20
      Color = clInfoBk
      MaxLength = 8
      ReadOnly = False
      TabOrder = 3
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEDate: TWVEdit
      Left = 298
      Top = 29
      Width = 110
      Height = 20
      Color = clInfoBk
      MaxLength = 8
      ReadOnly = False
      TabOrder = 4
      Text = '<��ֹ����>'
      WorkView = WorkView
      FieldName = '��ֹ����'
    end
    object edtSeriNo: TWVEdit
      Left = 100
      Top = 77
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 9
      Text = '<�ն���ˮ��>'
      WorkView = WorkView
      FieldName = '�ն���ˮ��'
    end
    object WVEdit6: TWVEdit
      Left = 298
      Top = 77
      Width = 110
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 10
      Text = '<ƾ֤����>'
      WorkView = WorkView
      FieldName = 'ƾ֤����'
    end
    object edtCustNo: TWVEdit
      Left = 100
      Top = 101
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 13
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object WVEdit8: TWVEdit
      Left = 298
      Top = 100
      Width = 110
      Height = 20
      CharCase = ecUpperCase
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 12
      Text = '<ѧ/����>'
      WorkView = WorkView
      FieldName = 'ѧ/����'
    end
    object WVEdit9: TWVEdit
      Left = 480
      Top = 55
      Width = 159
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 8
      Text = '<��ʾ����>'
      WorkView = WorkView
      FieldName = '��ʾ����'
    end
    object edtCardNo: TWVEdit
      Left = 100
      Top = 125
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 16
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVComboBox3: TWVComboBox
      Left = 480
      Top = 79
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '�ն˱��'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-9'
    end
    object WVComboBox1: TWVComboBox
      Left = 480
      Top = 30
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-15'
    end
    object WVComboBox2: TWVComboBox
      Left = 480
      Top = 5
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '����Ա'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox4: TWVComboBox
      Left = 298
      Top = 123
      Width = 110
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 15
      WorkView = WorkView
      FieldName = '��ˮ״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*3'
    end
    object edtTBDate: TWVEdit
      Left = 100
      Top = 5
      Width = 110
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<���׿�ʼ����>'
      WorkView = WorkView
      FieldName = '���׿�ʼ����'
    end
    object edtTEDate: TWVEdit
      Left = 298
      Top = 5
      Width = 110
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<���׽�������>'
      WorkView = WorkView
      FieldName = '���׽�������'
    end
    object cbbNetConn: TWVComboBox
      Left = 480
      Top = 102
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 14
      WorkView = WorkView
      FieldName = '����״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*139'
    end
    object edtBTime: TWVEdit
      Left = 100
      Top = 53
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 6
      Text = '<��ʼʱ��>'
      WorkView = WorkView
      FieldName = '��ʼʱ��'
    end
    object edtEtime: TWVEdit
      Left = 298
      Top = 53
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 7
      Text = '<����ʱ��>'
      WorkView = WorkView
      FieldName = '����ʱ��'
    end
    object cbb1: TWVComboBox
      Left = 256
      Top = 300
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 18
      Visible = False
      WorkView = WorkView
      FieldName = '���ױ�־'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*155'
    end
    object WVComboBox5: TWVComboBox
      Left = 480
      Top = 125
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 17
      WorkView = WorkView
      FieldName = '�ⲿ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-60'
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
          FieldName = 'lwithdraw_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ն˱��'
          Width = 80
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
          FieldName = 'sstatus3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������־'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp'
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
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ�����'
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
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ȫ��'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʾ����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ǯ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = '���ױ�־'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���״���'
          Width = 60
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
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ǰ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׺����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstat_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֧����ʽ'
          Width = 60
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
          FieldName = 'lcert_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵͳ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸��ˮ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level2'
          PickList.Strings = ()
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
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
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���д���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���п���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ⲿ����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Caption = '������������'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Caption = '���ײο���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ˮ״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote2'
          PickList.Strings = ()
          Title.Caption = '��ע'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ɼ�����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ɼ�ʱ��'
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ֹ����'
        Caption = '��ֹ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        Name = 'ѧ/����'
        Caption = 'ѧ/����'
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
        Name = '��ʾ����'
        Caption = '��ʾ����'
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
        Name = 'Ǯ����'
        Caption = 'Ǯ����'
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '��ˮ״̬'
        Caption = '��ˮ״̬'
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
        Name = '���׿�ʼ����'
        Caption = '���׿�ʼ����'
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
        Name = '���׽�������'
        Caption = '���׽�������'
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
      end
      item
        Name = '����״̬'
        Caption = '����״̬'
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
        Name = '��ʼʱ��'
        Caption = '��ʼʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '����ʱ��'
        Caption = '����ʱ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '���ױ�־'
        Caption = '���ױ�־'
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
        Name = '�ⲿ����'
        Caption = '�ⲿ����'
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
      end>
    FieldsMonitors = <
      item
      end>
    Left = 164
    Top = 303
  end
  inherited MainRequest: TWVRequest
    ID = '��������ˮ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��ֹ����'
        FieldName = '��ֹ����'
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
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = 'ѧ/����'
        FieldName = 'ѧ/����'
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
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = '��ˮ״̬'
      end
      item
        ParamName = '���׿�ʼ����'
        FieldName = '���׿�ʼ����'
      end
      item
        ParamName = '���׽�������'
        FieldName = '���׽�������'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '���ױ�־'
        FieldName = '���ױ�־'
      end
      item
        ParamName = '�ⲿ����'
        FieldName = '�ⲿ����'
        DefaultValue = 0
      end>
    Left = 200
    Top = 304
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstat_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '63'
      end
      item
        FieldName = 'lcert_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'idobjects'
        DataPresentParam = '116'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '3'
      end
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'idobjects'
        DataPresentParam = '-60'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-10'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-9'
      end
      item
        FieldName = 'semp'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstat_type2'
        DataPresentType = 'idobjects'
        DataPresentParam = '128'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'idobjects'
        DataPresentParam = '139'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '155'
      end>
    Left = 232
    Top = 304
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 304
  end
end

inherited faqhsendSublidyList: TfaqhsendSublidyList
  Width = 756
  Height = 455
  inherited UIPanel1: TUIPanel
    Top = 354
    Width = 756
    Height = 101
    TabOrder = 3
    object Label10: TLabel [0]
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object Label11: TLabel [1]
      Left = 66
      Top = 57
      Width = 24
      Height = 12
      Caption = 'ժҪ'
    end
    object Label12: TLabel [2]
      Left = 224
      Top = 9
      Width = 48
      Height = 12
      Caption = '���ʽ'
    end
    object Label13: TLabel [3]
      Left = 398
      Top = 9
      Width = 48
      Height = 12
      Caption = 'Ʊ�ݺ���'
    end
    object Label14: TLabel [4]
      Left = 30
      Top = 33
      Width = 60
      Height = 12
      Caption = '����������'
    end
    object Label15: TLabel [5]
      Left = 212
      Top = 33
      Width = 60
      Height = 12
      Caption = '�����ܽ��'
    end
    object Label16: TLabel [6]
      Left = 576
      Top = 9
      Width = 48
      Height = 12
      Caption = '������־'
      Visible = False
    end
    object RzStatusPane1: TRzStatusPane [7]
      Left = 0
      Top = 80
      Width = 756
      Height = 21
      FrameStyle = fsStatus
      Align = alBottom
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    object Label1: TLabel [8]
      Left = 388
      Top = 33
      Width = 60
      Height = 12
      Caption = '����Ա����'
    end
    inherited btnQuery: TBitBtn
      Left = 575
      Top = 52
      Enabled = False
      TabOrder = 7
    end
    inherited btnPrint: TBitBtn
      Left = 666
      Top = 52
      Hint = '�·�����'
      Caption = '�·�����'
      TabOrder = 8
      Glyph.Data = {00000000}
    end
    object edtPNo: TWVEdit
      Left = 92
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 0
      Text = '<�������κ�>'
      WorkView = WorkView1
      FieldName = '�������κ�'
    end
    object edtInfo: TWVEdit
      Left = 92
      Top = 53
      Width = 461
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 9
      Text = '<ժҪ>'
      WorkView = WorkView1
      FieldName = 'ժҪ'
    end
    object cbbFeeType: TWVComboBox
      Left = 277
      Top = 5
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clBtnHighlight
      ItemHeight = 12
      TabOrder = 1
      OnChange = cbbFeeTypeChange
      WorkView = WorkView1
      FieldName = '���ʽ'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*63'
    end
    object edtTicketNo: TWVEdit
      Left = 452
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 2
      Text = '<Ʊ�ݺ���>'
      WorkView = WorkView1
      FieldName = 'Ʊ�ݺ���'
    end
    object edtNum: TWVEdit
      Left = 92
      Top = 29
      Width = 100
      Height = 20
      Color = clBtnHighlight
      MaxLength = 22
      ReadOnly = False
      TabOrder = 4
      Text = '<����������>'
      WorkView = WorkView1
      FieldName = '����������'
    end
    object edtMoney: TWVEdit
      Left = 276
      Top = 29
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
    end
    object cbbFlag: TWVComboBox
      Left = 629
      Top = 5
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clBtnHighlight
      ItemHeight = 12
      TabOrder = 3
      Visible = False
      WorkView = WorkView1
      FieldName = '������־'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*77'
    end
    object edtPwd: TWVEdit
      Left = 452
      Top = 29
      Width = 100
      Height = 20
      Color = clBtnHighlight
      PasswordChar = '*'
      ReadOnly = False
      TabOrder = 6
      WorkView = WorkView1
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 756
    TabOrder = 2
    inherited Image1: TImage
      Width = 756
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 756
    Height = 79
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label4: TLabel
      Left = 448
      Top = 10
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label7: TLabel
      Left = 66
      Top = 34
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label2: TLabel
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object Label5: TLabel
      Left = 254
      Top = 10
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label3: TLabel
      Left = 466
      Top = 34
      Width = 24
      Height = 12
      Caption = '״̬'
    end
    object Label6: TLabel
      Left = 230
      Top = 34
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object lbl1: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label8: TLabel
      Left = 442
      Top = 58
      Width = 48
      Height = 12
      Caption = '���״̬'
    end
    object WVEdit4: TWVEdit
      Left = 500
      Top = 6
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<��ѯ.ѧ����>'
      WorkView = WorkView
      FieldName = '��ѯ.ѧ����'
    end
    object edtCardId: TWVEdit
      Left = 100
      Top = 29
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<��ѯ.����>'
      WorkView = WorkView
      FieldName = '��ѯ.����'
    end
    object WVEdit2: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<��ѯ.�������κ�>'
      WorkView = WorkView
      FieldName = '��ѯ.�������κ�'
    end
    object edtCustNo: TWVEdit
      Left = 300
      Top = 6
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<��ѯ.�ͻ���>'
      WorkView = WorkView
      FieldName = '��ѯ.�ͻ���'
    end
    object cbbType: TWVComboBox
      Left = 501
      Top = 29
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '��ѯ.״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*76'
    end
    object edtPatchNo: TWVEdit
      Left = 300
      Top = 30
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
      Text = '<��ѯ.�������κ�>'
      WorkView = WorkView
      FieldName = '��ѯ.�������κ�'
    end
    object cbbDept: TWVComboBox
      Left = 100
      Top = 53
      Width = 301
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVComboBox1: TWVComboBox
      Left = 501
      Top = 53
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '���״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*160'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 97
    Width = 756
    Height = 257
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 756
      Height = 257
      Columns = <
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
          Width = 70
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
          FieldName = 'smain_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '״̬'
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
          Width = 60
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
          Title.Caption = 'Ʊ������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ʊ�ݺ���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������Ա'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '��ѯ.�������κ�'
        Caption = '��ѯ.�������κ�'
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
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
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
        Name = '��ѯ.ѧ����'
        Caption = '��ѯ.ѧ����'
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
      end
      item
        Name = '��ѯ.�������κ�'
        Caption = '��ѯ.�������κ�'
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
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 108
    Top = 191
  end
  inherited MainRequest: TWVRequest
    ID = '������Ϣ��ѯ'
    Bindings = <
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
        ParamName = '�������κ�'
        FieldName = '��ѯ.�������κ�'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '��ѯ.�ͻ���'
      end
      item
        ParamName = 'ѧ����'
        FieldName = '��ѯ.ѧ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '���״̬'
        FieldName = '���״̬'
      end>
    Left = 152
    Top = 192
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '63'
      end
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '76'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '77'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'idobjects'
        DataPresentParam = '160'
      end>
    Left = 192
    Top = 192
  end
  inherited DataSource: TDataSource
    Left = 224
    Top = 192
  end
  object WorkView1: TWorkView
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        Name = 'ժҪ'
        Caption = 'ժҪ'
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
        Name = '���ʽ'
        Caption = '���ʽ'
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
        Name = 'Ʊ�ݺ���'
        Caption = 'Ʊ�ݺ���'
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
        Name = '����������'
        Caption = '����������'
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
        Name = '�����ܽ��'
        Caption = '�����ܽ��'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = -999999
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '���������֤��'
        Caption = '���������֤��'
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
        Name = '����������'
        Caption = '����������'
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
        Name = '������־'
        Caption = '������־'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end>
    InvalidColor = clBtnHighlight
    Left = 108
    Top = 239
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�·�'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
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
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = 'ժҪ'
        FieldName = 'ժҪ'
      end
      item
        ParamName = '���ʽ'
        FieldName = '���ʽ'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'Ʊ�ݺ���'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '�����ܽ��'
        FieldName = '�����ܽ��'
      end
      item
        ParamName = '���������֤��'
        FieldName = '���������֤��'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    AfterExec = MainRequestAfterExec
    Left = 152
    Top = 240
  end
end

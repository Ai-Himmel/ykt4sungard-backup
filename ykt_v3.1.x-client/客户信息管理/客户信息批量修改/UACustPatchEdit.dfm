inherited faqhCustPatchEdit: TfaqhCustPatchEdit
  Width = 752
  Height = 536
  inherited UIPanel1: TUIPanel
    Top = 379
    Width = 752
    Height = 157
    TabOrder = 4
    object Label11: TLabel [0]
      Left = 80
      Top = 103
      Width = 48
      Height = 12
      Caption = '������'
    end
    inherited btnQuery: TBitBtn
      Left = 577
      Top = 97
      Enabled = False
      TabOrder = 4
    end
    inherited btnPrint: TBitBtn
      Left = 14
      Top = 10000
      TabOrder = 9
      Visible = False
    end
    object edtSheetName: TEdit
      Left = 136
      Top = 99
      Width = 77
      Height = 20
      TabOrder = 6
      Text = 'sheet1'
    end
    object btnSelectFile: TBitBtn
      Left = 219
      Top = 97
      Width = 85
      Height = 25
      Hint = '����У԰��'
      Caption = 'ѡ���ļ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnSelectFileClick
    end
    object btnImportQuery: TBitBtn
      Left = 307
      Top = 97
      Width = 85
      Height = 25
      Hint = '�����ѯ'
      Caption = '�����ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnImportQueryClick
    end
    object btnClear: TBitBtn
      Left = 396
      Top = 97
      Width = 85
      Height = 25
      Hint = '�����ѯ'
      Caption = '����б�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnClearClick
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 136
      Width = 752
      Height = 21
      AutoStyle = False
      BorderColor = clWindow
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      Color = 16184303
      FlatColor = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 752
        Height = 21
        FrameStyle = fsStatus
        Align = alClient
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object chkSelect: TCheckBox
      Left = 8
      Top = 100
      Width = 45
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 7
      OnClick = chkSelectClick
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 752
      Height = 89
      Hint = '����Ҫ�޸ĵ����ݴ�'
      Align = alTop
      Caption = '�޸���Ϣ'
      TabOrder = 0
      object chkCustType: TCheckBox
        Left = 40
        Top = 16
        Width = 65
        Height = 17
        Alignment = taLeftJustify
        Caption = '�ͻ����'
        TabOrder = 3
      end
      object chkFeeType: TCheckBox
        Left = 40
        Top = 40
        Width = 65
        Height = 17
        Alignment = taLeftJustify
        Caption = '�շ����'
        TabOrder = 10
      end
      object chkArea: TCheckBox
        Left = 288
        Top = 16
        Width = 41
        Height = 17
        Alignment = taLeftJustify
        Caption = 'У��'
        TabOrder = 4
      end
      object chkDept: TCheckBox
        Left = 264
        Top = 40
        Width = 65
        Height = 17
        Alignment = taLeftJustify
        Caption = '��������'
        TabOrder = 11
      end
      object chkDestoryTime: TCheckBox
        Left = 40
        Top = 64
        Width = 65
        Height = 17
        Alignment = taLeftJustify
        Caption = '��Ч����'
        TabOrder = 14
      end
      object chkClass: TCheckBox
        Left = 520
        Top = 16
        Width = 41
        Height = 17
        Alignment = taLeftJustify
        Caption = '�༶'
        TabOrder = 5
      end
      object cbbCustType: TWVComboBox
        Left = 113
        Top = 14
        Width = 142
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 0
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-34'
      end
      object cbbFeeType: TWVComboBox
        Left = 113
        Top = 37
        Width = 142
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 6
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
      object cbbArea: TWVComboBox
        Left = 338
        Top = 14
        Width = 142
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 1
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-27'
      end
      object cbbDept: TWVComboBox
        Left = 322
        Top = 37
        Width = 142
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 7
        Visible = False
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object edtClass: TWVEdit
        Left = 568
        Top = 14
        Width = 145
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
      end
      object edtDestoryTime: TWVEdit
        Left = 113
        Top = 61
        Width = 142
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 13
      end
      object cbb2: TKSFilterComboBox
        Left = 338
        Top = 37
        Width = 142
        Height = 22
        ListFont.Charset = GB2312_CHARSET
        ListFont.Color = clWindowText
        ListFont.Height = -12
        ListFont.Name = '����'
        ListFont.Style = []
        OnFilterItems = cbb2FilterItems
        TabOrder = 8
      end
      object chkSpec: TCheckBox
        Left = 520
        Top = 40
        Width = 41
        Height = 17
        Alignment = taLeftJustify
        Caption = 'רҵ'
        TabOrder = 12
      end
      object cbbSpec: TWVComboBox
        Left = 568
        Top = 37
        Width = 145
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 9
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-23'
      end
    end
    object btnPatchEdit: TBitBtn
      Left = 660
      Top = 97
      Width = 85
      Height = 25
      Hint = '�����޸�'
      Anchors = [akTop, akRight]
      Caption = '�����޸�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnPatchEditClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 752
    inherited Image1: TImage
      Width = 752
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 752
    Height = 127
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object WVLabel2: TWVLabel
      Left = 64
      Top = 15
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label1: TLabel
      Left = 52
      Top = 39
      Width = 48
      Height = 12
      Caption = '�ͻ����'
    end
    object Label8: TLabel
      Left = 76
      Top = 63
      Width = 24
      Height = 12
      Caption = '�Ա�'
    end
    object Label10: TLabel
      Left = 52
      Top = 87
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object Label3: TLabel
      Left = 301
      Top = 87
      Width = 24
      Height = 12
      Caption = 'У��'
    end
    object WVLabel1: TWVLabel
      Left = 493
      Top = 63
      Width = 36
      Height = 12
      Caption = '���κ�'
    end
    object Label9: TLabel
      Left = 504
      Top = 39
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label5: TLabel
      Left = 283
      Top = 63
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label13: TLabel
      Left = 277
      Top = 39
      Width = 48
      Height = 12
      Caption = '�շ����'
    end
    object Label4: TLabel
      Left = 277
      Top = 15
      Width = 48
      Height = 12
      Caption = '�ͻ�����'
    end
    object Label6: TLabel
      Left = 480
      Top = 15
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object WVLabel3: TWVLabel
      Left = 504
      Top = 87
      Width = 24
      Height = 12
      Caption = '�༶'
    end
    object WVEdit2: TWVEdit
      Left = 112
      Top = 10
      Width = 120
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object WVComboBox1: TWVComboBox
      Left = 112
      Top = 34
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '�ͻ����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVComboBox8: TWVComboBox
      Left = 112
      Top = 58
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '��ϵ���Ա�'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*39'
    end
    object WVEdit10: TWVEdit
      Left = 112
      Top = 82
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<��ϵ�����֤��>'
      WorkView = WorkView
      FieldName = '��ϵ�����֤��'
    end
    object WVComboBox3: TWVComboBox
      Left = 339
      Top = 82
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '�ͻ���������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
    object WVEdit1: TWVEdit
      Left = 541
      Top = 58
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = '<���κ�>'
      WorkView = WorkView
      FieldName = '���κ�'
    end
    object WVComboBox9: TWVComboBox
      Left = 541
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '��ϵ������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*2001'
    end
    object WVEdit5: TWVEdit
      Left = 339
      Top = 58
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 8
      Text = '<��ϵ��ѧ����>'
      WorkView = WorkView
      FieldName = '��ϵ��ѧ����'
    end
    object WVComboBox4: TWVComboBox
      Left = 339
      Top = 34
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '�շ����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object WVEdit4: TWVEdit
      Left = 339
      Top = 10
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<�ͻ�����>'
      WorkView = WorkView
      FieldName = '�ͻ�����'
    end
    object cbbQDept: TWVComboBox
      Left = 541
      Top = 10
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      Visible = False
      WorkView = WorkView
      FieldName = '��ϵ�˵�λ��'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVEdit3: TWVEdit
      Left = 541
      Top = 82
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<�༶>'
      WorkView = WorkView
      FieldName = '�༶'
    end
    object chkFilter: TCheckBox
      Left = 112
      Top = 104
      Width = 169
      Height = 17
      Caption = '���˵��б����ظ��ļ�¼'
      TabOrder = 13
    end
    object cbb1: TKSFilterComboBox
      Left = 540
      Top = 9
      Width = 144
      Height = 22
      ListFont.Charset = GB2312_CHARSET
      ListFont.Color = clWindowText
      ListFont.Height = -12
      ListFont.Name = '����'
      ListFont.Style = []
      OnFilterItems = cbb1FilterItems
      TabOrder = 3
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 145
    Width = 752
    Height = 234
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 752
      Height = 234
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'У��'
          Width = 91
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ����'
          Width = 61
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�շ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 128
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'רҵ'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ�״̬'
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ע��ʱ��'
          Width = 103
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ڲ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Caption = '�༶'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵ��'
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���֤��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 71
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ԥ��ע��ʱ��'
          Width = 92
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ/����'
          Width = 76
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵ��ַ'
          Width = 229
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵ�绰'
          Width = 109
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Width = 270
          Visible = True
        end>
    end
  end
  object lv1: TListView [4]
    Left = 0
    Top = 145
    Width = 752
    Height = 234
    Align = alClient
    Checkboxes = True
    Columns = <
      item
        Caption = '�ͻ���'
        Width = 70
      end
      item
        Caption = 'ѧ/����'
        Width = 70
      end
      item
        Caption = 'У��'
        Width = 91
      end
      item
        Caption = '�ͻ�����'
        Width = 70
      end
      item
        Caption = '�Ա�'
        Width = 60
      end
      item
        Caption = '�ͻ����'
        Width = 100
      end
      item
        Caption = '�շ����'
        Width = 60
      end
      item
        Caption = '��������'
        Width = 130
      end
      item
        Caption = 'רҵ'
        Width = 70
      end
      item
        Caption = '�༶'
        Width = 60
      end
      item
        Caption = '֤������'
        Width = 70
      end
      item
        Caption = '֤������'
        Width = 120
      end
      item
        Caption = '����'
        Width = 71
      end
      item
        Caption = '��Ч����'
        Width = 90
      end
      item
        Caption = '��ϵ�绰'
        Width = 60
      end
      item
        Caption = '��ϵ��ַ'
        Width = 120
      end>
    ColumnClick = False
    FlatScrollBars = True
    GridLines = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = True
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
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
      end
      item
        Name = '�ͻ�״̬'
        Caption = '�ͻ�״̬'
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
        GroupIndex = 1
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
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
      end
      item
        Name = '��ϵ�˵�λ��'
        Caption = '��ϵ�˵�λ��'
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
      end
      item
        Name = '��ϵ���Ա�'
        Caption = '��ϵ���Ա�'
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
      end
      item
        Name = '��ϵ��ѧ����'
        Caption = '��ϵ��ѧ����'
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
      end
      item
        Name = '��ϵ������'
        Caption = '��ϵ������'
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
      end
      item
        Name = '��ϵ�����֤��'
        Caption = '��ϵ�����֤��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
      end
      item
        Name = '�ͻ���������'
        Caption = '�ͻ���������'
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
      end
      item
        Name = '�༶'
        Caption = '�༶'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�ͻ����|�ͻ�״̬|����|�ͻ�����|��ϵ��ѧ�Ż�Ա����|��ϵ�˰༶��' +
          '����|��ϵ������|��ϵ���Ա�|��ϵ���������|��ϵ�����֤��|��ϵ��' +
          '��|��ϵ��ַ|ע��ʱ��|Ԥ��ע��ʱ��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 319
  end
  inherited MainRequest: TWVRequest
    ID = '�ͻ���Ϣ��ѯ'
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
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�ͻ�״̬'
        FieldName = '�ͻ�״̬'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '��ϵ�˵�λ��'
        FieldName = '��ϵ�˵�λ��'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = '��ϵ���Ա�'
      end
      item
        ParamName = '��ϵ��ѧ����'
        FieldName = '��ϵ��ѧ����'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = '��ϵ�����֤��'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = '�ͻ���������'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 120
    Top = 320
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'scust_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end>
    Left = 192
    Top = 320
  end
  inherited DataSource: TDataSource
    Top = 320
  end
  object dlgOpen: TOpenDialog
    Left = 88
    Top = 352
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\����\�½� Microsoft Office Access Ӧ�ó���.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 144
    Top = 352
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 184
    Top = 352
  end
  object ChangeRequest: TWVRequest
    WorkView = WorkView1
    ID = '�ͻ���Ϣ����'
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
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = '�ͻ���������'
      end
      item
        ParamName = 'Ԥ��ע��ʱ��'
        FieldName = 'Ԥ��ע��ʱ��'
      end
      item
        ParamName = '��ϵ�˰༶���ź�'
        FieldName = '��ϵ�˰༶���ź�'
      end
      item
        ParamName = '��ϵ�˰༶��������'
        FieldName = '��ϵ�˰༶��������'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = '��ϵ���Ա�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'רҵ'
      end>
    Left = 128
    Top = 256
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
        Name = '�ͻ����'
        Caption = '�ͻ����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol3'
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol5'
      end
      item
        Name = '�ͻ���������'
        Caption = '�ͻ���������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = 'Ԥ��ע��ʱ��'
        Caption = 'Ԥ��ע��ʱ��'
        FieldType = wftUndefined
        DomainName = '����У��'
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
        GetPrevChar = '*'
        DataField = 'sphone3'
      end
      item
        Name = '��ϵ�˰༶���ź�'
        Caption = '��ϵ�˰༶���ź�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scert_no'
      end
      item
        Name = '��ϵ�˰༶��������'
        Caption = '��ϵ�˰༶��������'
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol1'
      end
      item
        Name = '��ϵ���Ա�'
        Caption = '��ϵ���Ա�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'smarket_code'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = 'רҵ'
        Caption = 'רҵ'
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
    FieldsMonitors = <>
    InvalidColor = clBtnHighlight
    Left = 88
    Top = 256
  end
end

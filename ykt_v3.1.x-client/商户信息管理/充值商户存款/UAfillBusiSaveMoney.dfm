inherited faqhfillBusiSaveMoney: TfaqhfillBusiSaveMoney
  Width = 667
  Height = 569
  inherited UIPanel1: TUIPanel
    Top = 517
    Width = 667
    Height = 52
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 90
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 177
      Visible = False
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 31
      Width = 667
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
      TabOrder = 2
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 667
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
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 667
    inherited Image1: TImage
      Width = 667
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 667
    Height = 499
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object grp1: TGroupBox
      Left = 168
      Top = 72
      Width = 393
      Height = 185
      Caption = '�̻������Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object lbl1: TRzLabel
        Left = 32
        Top = 31
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '�̻�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel1: TRzLabel
        Left = 32
        Top = 151
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel16: TRzLabel
        Left = 32
        Top = 55
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '��ɱ���'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object lblBl: TRzLabel
        Left = 128
        Top = 54
        Width = 224
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel18: TRzLabel
        Left = 32
        Top = 78
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '�ʻ����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object lblAccMoney: TRzLabel
        Left = 128
        Top = 77
        Width = 224
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object lbl2: TLabel
        Left = 360
        Top = 59
        Width = 7
        Height = 14
        Caption = '%'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 360
        Top = 83
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 360
        Top = 155
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object RzLabel4: TRzLabel
        Left = 32
        Top = 103
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '��ֵ����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel5: TRzLabel
        Left = 32
        Top = 127
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Ʊ�ݺ���'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object edtSveMoney: TWVDigitalEdit
        Left = 128
        Top = 151
        Width = 224
        Height = 22
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�����'
        SynchronizeByValue = True
      end
      object cbbBusiName: TWVComboBox
        Left = 128
        Top = 30
        Width = 225
        Height = 22
        Style = csDropDownList
        Color = clInfoBk
        DropDownCount = 20
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ImeName = '�Ϲ�ƴ�����뷨'
        ItemHeight = 14
        ParentFont = False
        TabOrder = 0
        OnChange = cbbBusiNameChange
        WorkView = WorkView
        FieldName = '�̻���'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-50'
      end
      object cbbType: TWVComboBox
        Left = 128
        Top = 102
        Width = 225
        Height = 22
        Style = csDropDownList
        Color = clWhite
        DropDownCount = 20
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ImeName = '�Ϲ�ƴ�����뷨'
        ItemHeight = 14
        ParentFont = False
        TabOrder = 1
        OnChange = cbbTypeChange
        WorkView = WorkView
        FieldName = '��ֵ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '63'
      end
      object edtTicketNo: TRzEdit
        Left = 127
        Top = 126
        Width = 224
        Height = 22
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        TabOrder = 2
      end
    end
    object grpSuccInfo: TGroupBox
      Left = 168
      Top = 264
      Width = 393
      Height = 201
      Caption = '���ɹ���Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object RzLabel2: TRzLabel
        Left = 32
        Top = 47
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '�̻���'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel3: TRzLabel
        Left = 32
        Top = 70
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '�̻�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel6: TRzLabel
        Left = 32
        Top = 22
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '��̨��ˮ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel8: TRzLabel
        Left = 32
        Top = 94
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '��������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel10: TRzLabel
        Left = 32
        Top = 142
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '��ɽ��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel12: TRzLabel
        Left = 32
        Top = 166
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '�ʻ����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel14: TRzLabel
        Left = 32
        Top = 118
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '�����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object Label3: TLabel
        Left = 360
        Top = 149
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 360
        Top = 173
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 360
        Top = 125
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtSeriId: TRzEdit
        Left = 129
        Top = 22
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtBusiId: TRzEdit
        Left = 129
        Top = 46
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtBusiName: TRzEdit
        Left = 129
        Top = 70
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edtDate: TRzEdit
        Left = 129
        Top = 94
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object edtTc: TRzEdit
        Left = 129
        Top = 142
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
      object edtAccMoney: TRzEdit
        Left = 129
        Top = 166
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
      object edtSaveMoney: TRzEdit
        Left = 129
        Top = 118
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
    end
    object btnSaveMoney: TImageButton
      Left = 466
      Top = 467
      Width = 95
      Height = 25
      Caption = '�̻����(&S)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnSaveMoneyClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 696
    Top = 432
    Width = 56
    Height = 33
    Align = alNone
    TabOrder = 2
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'semp_pwd'
          PickList.Strings = ()
          Title.Caption = '���˲���Ա����'
          Visible = True
        end>
    end
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
        Name = '�̻���'
        Caption = '�̻���'
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
        Name = '�����'
        Caption = '�����'
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
        Name = '����Ա��'
        Caption = '����Ա��'
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
        Name = '��̨��ˮ��'
        Caption = '��̨��ˮ��'
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
        Name = '�̻�����'
        Caption = '�̻�����'
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
        Name = '��ɽ��'
        Caption = '��ɽ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�ʻ����'
        Caption = '�ʻ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ֵ����'
        Caption = '��ֵ����'
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
        Name = 'Ʊ�ݺ���'
        Caption = 'Ʊ�ݺ���'
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
        MonitorValueChangedFields = '|�̻���|�����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 308
    Top = 31
  end
  inherited MainRequest: TWVRequest
    ID = '��ֵ�̻����'
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
        ParamName = '�̻���'
        FieldName = '�̻���'
        Direction = bdBiDirection
      end
      item
        ParamName = '�����'
        FieldName = '�����'
        Direction = bdBiDirection
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
        Direction = bdParam2Field
      end
      item
        ParamName = '��̨��ˮ��'
        FieldName = '��̨��ˮ��'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ɽ��'
        FieldName = '��ɽ��'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ʻ����'
        FieldName = '�ʻ����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'Ʊ�ݺ���'
      end
      item
        ParamName = '��ֵ����'
        FieldName = '��ֵ����'
      end>
    Left = 344
    Top = 32
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 392
    Top = 32
  end
  inherited DataSource: TDataSource
    Left = 432
    Top = 32
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
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
        Name = '��ѯ.�̻���'
        Caption = '��ѯ.�̻���'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.�̻�����|��ѯ.�̻�����������|��ѯ.�̻�֤������|��ѯ.�̻�֤' +
          '������|��ѯ.�̻���ɱ���|��ѯ.����Ա��|'
      end
      item
        MonitorValueChangedFields = '|�̻���|�̻�����|�̻�����������|�̻�֤������|�̻�֤������|'
      end>
    Left = 48
    Top = 40
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '�̻���Ϣ������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '��ѯ.�̻���'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 88
    Top = 40
  end
end

inherited faqhBusPosKey: TfaqhBusPosKey
  Width = 791
  Height = 563
  inherited UIPanel1: TUIPanel
    Top = 523
    Width = 791
    Height = 40
    TabOrder = 4
    inherited btnQuery: TBitBtn
      Left = 616
      Top = 5
      Hint = ''
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 701
      Top = 5
      Hint = ''
      Enabled = True
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 791
    Height = 16
    inherited Image1: TImage
      Width = 791
      Height = 16
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 16
    Width = 791
    Height = 0
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label2: TLabel
      Left = 531
      Top = 58
      Width = 72
      Height = 12
      Caption = '�Ƿ񽻴���'
      Visible = False
    end
    object WVLabel1: TWVLabel
      Left = 40
      Top = 58
      Width = 108
      Height = 12
      Caption = '��һ����ȡ���ɱ���'
      Visible = False
    end
    object WVLabel2: TWVLabel
      Left = 295
      Top = 58
      Width = 84
      Height = 12
      Caption = '�Ƿ��˿��ɱ���'
      Visible = False
    end
    object WVComboBox1: TWVComboBox
      Left = 615
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      Visible = False
      WorkView = WorkView
      FieldName = '�Ƿ񽻴���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox2: TWVComboBox
      Left = 159
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      Visible = False
      WorkView = WorkView
      FieldName = '��һ���Ƿ���ȡ���ɱ���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox3: TWVComboBox
      Left = 391
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      Visible = False
      WorkView = WorkView
      FieldName = '�Ƿ��˿��ɱ���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 16
    Width = 791
    Height = 507
    inherited Grid: TRzDBGrid
      Width = 791
      Height = 507
    end
  end
  object Panel2: TPanel [4]
    Left = 0
    Top = 16
    Width = 791
    Height = 507
    Align = alClient
    Color = 16184303
    TabOrder = 2
    object grp1: TGroupBox
      Left = 184
      Top = 72
      Width = 345
      Height = 121
      Caption = '��Կ����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label3: TLabel
        Left = 44
        Top = 43
        Width = 70
        Height = 14
        Caption = '��Կ�汾��'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object edtPwdVer: TWVEdit
        Left = 119
        Top = 38
        Width = 138
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object chuploadfile: TCheckBox
        Left = 120
        Top = 72
        Width = 137
        Height = 17
        Caption = '�ϴ��ļ����ֳֻ�'
        Checked = True
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        State = cbChecked
        TabOrder = 1
        Visible = False
      end
    end
    object btnOK: TImageButton
      Left = 360
      Top = 213
      Width = 75
      Height = 25
      Caption = 'ȷ ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnOKClick
    end
    object btnCancle: TImageButton
      Left = 453
      Top = 213
      Width = 75
      Height = 25
      Caption = 'ȡ ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnCancleClick
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
        Name = '�������ݼ�'
        Caption = '�������ݼ�'
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
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2006'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end>
    Left = 116
    Top = 503
  end
  inherited MainRequest: TWVRequest
    ID = 'ȡ�ù�����Կ'
    Bindings = <
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
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '�������ݼ�'
        Direction = bdParam2Field
      end>
    Left = 152
    Top = 504
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '�������ݼ�'
    Bindings = <
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end>
    Left = 200
    Top = 504
  end
  inherited DataSource: TDataSource
    Left = 328
    Top = 512
  end
end

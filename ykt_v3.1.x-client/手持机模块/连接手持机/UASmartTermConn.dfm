inherited faqhSmartTermConn: TfaqhSmartTermConn
  Width = 700
  Height = 489
  object RzLabel6: TRzLabel [0]
    Left = 120
    Top = 114
    Width = 144
    Height = 12
    AutoSize = False
  end
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    TabOrder = 7
    inherited btnQuery: TBitBtn
      Left = 307
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 394
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 6
    inherited Image1: TImage
      Width = 700
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 664
    Top = 416
    Width = 36
    Height = 43
    Align = alNone
    TabOrder = 5
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Visible = False
    end
  end
  object grp1: TGroupBox [4]
    Left = 184
    Top = 72
    Width = 321
    Height = 105
    TabOrder = 0
    object lbl1: TLabel
      Left = 32
      Top = 24
      Width = 36
      Height = 12
      Alignment = taRightJustify
      Caption = '�˿ڣ�'
      Transparent = True
    end
    object lbl2: TLabel
      Left = 20
      Top = 48
      Width = 48
      Height = 12
      Alignment = taRightJustify
      Caption = '�����ʣ�'
      Transparent = True
    end
    object cbbComPort: TComboBox
      Left = 73
      Top = 21
      Width = 162
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 0
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6'
        'COM7'
        'COM8'
        'COM9'
        'COM10'
        'COM11'
        'COM12'
        'COM13'
        'COM14')
    end
    object cbbComBand: TComboBox
      Left = 73
      Top = 45
      Width = 162
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 1
      Items.Strings = (
        '9600'
        '19200'
        '38400')
    end
    object rgType: TRadioGroup
      Left = 16
      Top = 64
      Width = 219
      Height = 33
      Caption = '��������'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        '�����ֳֻ�'
        '��֤�ֳֻ�')
      TabOrder = 2
    end
  end
  object RzGroupBox1: TRzGroupBox [5]
    Left = 184
    Top = 192
    Width = 321
    Caption = '�ֳֻ���Ϣ'
    ParentColor = True
    TabOrder = 1
    object RzLabel1: TRzLabel
      Left = 39
      Top = 32
      Width = 72
      Height = 12
      Alignment = taRightJustify
      Caption = '��������ID��'
    end
    object RzLabel2: TRzLabel
      Left = 51
      Top = 53
      Width = 60
      Height = 12
      Alignment = taRightJustify
      Caption = '����汾��'
    end
    object RzLabel3: TRzLabel
      Left = 51
      Top = 75
      Width = 60
      Height = 12
      Alignment = taRightJustify
      Caption = '�豸���ţ�'
    end
    object RzLabel4: TRzLabel
      Left = 39
      Top = 115
      Width = 72
      Height = 12
      Alignment = taRightJustify
      Caption = '�������汾��'
      Visible = False
    end
    object RzLabel5: TRzLabel
      Left = 27
      Top = 136
      Width = 84
      Height = 12
      Alignment = taRightJustify
      Caption = '��������Ч�ڣ�'
      Visible = False
    end
    object lblPhyId: TRzLabel
      Left = 121
      Top = 32
      Width = 120
      Height = 12
      AutoSize = False
      LightTextStyle = True
    end
    object lblProVer: TRzLabel
      Left = 121
      Top = 53
      Width = 144
      Height = 12
      AutoSize = False
      LightTextStyle = True
    end
    object lblNo: TRzLabel
      Left = 121
      Top = 74
      Width = 144
      Height = 12
      AutoSize = False
      LightTextStyle = True
    end
    object lblBlkVer: TRzLabel
      Left = 121
      Top = 114
      Width = 144
      Height = 12
      AutoSize = False
      Visible = False
      LightTextStyle = True
    end
    object lblBlkExpire: TRzLabel
      Left = 121
      Top = 135
      Width = 144
      Height = 12
      AutoSize = False
      Visible = False
      LightTextStyle = True
    end
  end
  object btnCtrlCOM: TBitBtn [6]
    Left = 216
    Top = 315
    Width = 90
    Height = 25
    Hint = '��ѯ/ˢ������'
    Caption = '�򿪴���'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '����'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = btnCtrlCOMClick
  end
  object btnReadInfo: TBitBtn [7]
    Left = 311
    Top = 315
    Width = 90
    Height = 25
    Hint = '��ȡ�ֳֻ���Ϣ'
    Caption = '�ֳֻ���Ϣ'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '����'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = btnReadInfoClick
  end
  object btnSetWorkKey: TBitBtn [8]
    Left = 405
    Top = 315
    Width = 100
    Height = 25
    Hint = '���ù�����Կ'
    Caption = '���ù�����Կ'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '����'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = btnSetWorkKeyClick
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
        DataField = '@Dataset'
      end
      item
        Name = '�豸����ID'
        Caption = '�豸����ID'
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
          '|�ն��豸�ɣ�|������ˮ��|���׿���|Ǯ����|��������|����ʱ��|�ۼ�' +
          'ʹ�ô���|�������ѽ��|�뿨���|�������|���ױ��|ͨ�Ű汾��|����' +
          'ͨ������ԭ��||'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 20
    Top = 207
  end
  inherited MainRequest: TWVRequest
    ID = '�ֳֻ���������'
    Bindings = <
      item
        ParamName = '�豸����ID'
        FieldName = '�豸����ID'
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    Left = 56
    Top = 208
  end
  inherited WVDBBinder: TWVDBBinder
    Left = 88
    Top = 208
  end
  inherited DataSource: TDataSource
    Left = 120
    Top = 208
  end
  object wvrGetSysParam: TWVRequest
    WorkView = wvGetSysParam
    ID = '��ȡ������Կ'
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
        ParamName = '������־'
        FieldName = '������ʶ'
      end>
    AfterExec = MainRequestAfterExec
    Left = 56
    Top = 144
  end
  object wvGetSysParam: TWorkView
    WorkFields = <
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
        Name = '������ʶ'
        Caption = '������ʶ'
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
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 20
    Top = 143
  end
end

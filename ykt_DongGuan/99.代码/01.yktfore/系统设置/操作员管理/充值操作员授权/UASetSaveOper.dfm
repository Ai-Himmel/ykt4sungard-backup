inherited faqhSetSaveOper: TfaqhSetSaveOper
  Width = 681
  Height = 480
  inherited UIPanel1: TUIPanel
    Top = 439
    Width = 681
    Height = 41
    TabOrder = 2
    object lbl2: TLabel [0]
      Left = 168
      Top = 16
      Width = 84
      Height = 12
      Caption = '��Ȩ����Ա����'
    end
    inherited btnOK: TBitBtn
      Left = 584
      Top = 10
      Width = 81
      Caption = '�� Ȩ'
      Font.Style = []
      TabOrder = 2
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0084848400FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00007B00008484840084848400FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0000CE0000007B000084848400FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF0000CE000000CE0000007B00008484840084848400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF0000CE000000FF000000FF000000CE0000007B000084848400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF0000FF000000FF000000FF000000CE0000007B00008484840084848400FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000CE
        000000FF000000FF000000FF000000FF000000CE0000007B0000848484008484
        8400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000FF
        000063FF630000FF0000007B000000FF000000FF000000CE0000007B00008484
        840084848400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000FF
        000094FF940063FF6300007B0000FFFFFF0000FF000000FF000000CE0000007B
        0000848484008484840084848400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF0000FF000000FF0000FFFFFF00FFFFFF00FFFFFF0000FF000000FF000000CE
        0000007B0000007B000084848400848484008484840084848400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000FF
        000000FF000000CE0000007B0000007B0000007B000084848400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0000FF000000FF000000CE0000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    inherited btnCancel: TBitBtn
      Left = 492
      Top = 10
      Width = 82
      Caption = '�� ѯ'
      Font.Style = []
    end
    object rgLimit: TRadioGroup
      Left = 16
      Top = 4
      Width = 137
      Height = 32
      Caption = '�Ƿ��г�ֵȨ��'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        '��'
        '��')
      TabOrder = 0
    end
    object edtPwd: TEdit
      Left = 256
      Top = 12
      Width = 97
      Height = 20
      MaxLength = 6
      PasswordChar = '*'
      TabOrder = 3
    end
  end
  object Panel2: TPanel [1]
    Left = 0
    Top = 0
    Width = 681
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object lbl1: TLabel
      Left = 16
      Top = 8
      Width = 240
      Height = 12
      Caption = '˵�����ù���ֻ��ָ���Ĳ���Ա��ӵ�д�Ȩ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
  end
  object pnl1: TPanel [2]
    Left = 0
    Top = 25
    Width = 681
    Height = 414
    Align = alClient
    BevelOuter = bvNone
    Color = 16184303
    TabOrder = 1
    object lv1: TRzListView
      Left = 0
      Top = 0
      Width = 681
      Height = 414
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '����Ա����'
          Width = 100
        end
        item
          Caption = '����Ա���'
          Width = 100
        end
        item
          Caption = '����Ա����'
          Width = 200
        end
        item
          Caption = '�Ƿ��г�ֵȨ��'
          Width = 260
        end>
      GridLines = True
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '������'
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
        Name = '����ԱȨ��'
        Caption = '����ԱȨ��'
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
      end>
    Left = 460
    Top = 23
  end
  inherited MainRequest: TWVRequest
    ID = '���ó�ֵ����Ա'
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
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '����ԱȨ��'
        FieldName = '����ԱȨ��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 496
    Top = 24
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
        Name = '��ѯ.����Ա����'
        Caption = '��ѯ.����Ա����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        Checker.Required = False
        GetPrevChar = '*'
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
        DataField = 'sstatus3'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        MonitorValueChangedFields = '|��ѯ.����Ա����|'
      end
      item
        MonitorValueChangedFields = 
          '|����Ա����|����Ա����|�绰|�ֻ�|��ַ|�ʱ�|�����ʼ�|�Ƿ����Ʒ���' +
          'վ��|����Ա״̬|����Ȩ��|'
        GroupIndex = 1
      end>
    Left = 456
    Top = 56
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '����Ա��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����Ա����'
        FieldName = '��ѯ.����Ա����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end>
    Left = 496
    Top = 56
  end
end

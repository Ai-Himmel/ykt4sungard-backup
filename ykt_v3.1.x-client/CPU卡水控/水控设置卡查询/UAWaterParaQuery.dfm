inherited faqhWaterParaQ: TfaqhWaterParaQ
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 521
      Top = 6
    end
    inherited btnPrint: TBitBtn
      Left = 612
      Top = 1000
      TabOrder = 2
    end
    object btnDelete: TBitBtn
      Left = 609
      Top = 6
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = 'ɾ��(&D)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnDeleteClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFF
        FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF000000FF0000FFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF000000FF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFF
        FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B000000
        FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B000000
        FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFF
        FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF000000FF0000FFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF007B7B7B000000FF007B7B7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
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
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label2: TLabel
      Left = 34
      Top = 11
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object WVLabel1: TWVLabel
      Left = 32
      Top = 48
      Width = 48
      Height = 12
      Caption = '��Чʱ��'
      Visible = False
    end
    object WVLabel2: TWVLabel
      Left = 232
      Top = 48
      Width = 144
      Height = 12
      Caption = '��ʽ����λ����λ����λ��'
      Visible = False
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 40
      Width = 101
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<��Чʱ��>'
      Visible = False
      WorkView = WorkView
      FieldName = '��Чʱ��'
    end
    object cbbFeeType: TWVComboBox
      Left = 84
      Top = 6
      Width = 157
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 10
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-63'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 700
    Height = 404
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 404
      Columns = <
        item
          Expanded = False
          FieldName = 'lcert_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ʱ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lwithdraw_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ǯ����'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ʒѵ�λ'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = -1
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol11'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�շ����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����1'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���1'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʱ��1'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����2'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���2'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʱ��2'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����3'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol8'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���3'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʱ��3'
          Width = 70
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'vsmess'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|������־|��������|����ֵ|��Чʱ��|����ʱ��|������λ|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 348
    Top = 143
  end
  inherited MainRequest: TWVRequest
    ID = '�������ÿ���ѯ'
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
        ParamName = '��������'
        FieldName = '����'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end>
    Left = 384
    Top = 144
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lserial0'
        DataPresentType = 'idobjects'
        DataPresentParam = '97'
      end
      item
        FieldName = 'lvol11'
        DataPresentType = 'idobjects'
        DataPresentParam = '-43'
      end>
    Left = 416
    Top = 144
  end
  inherited DataSource: TDataSource
    Left = 448
    Top = 144
  end
  object WorkView1: TWorkView
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'vsmess'
      end
      item
        Name = '����'
        Caption = '����'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|������־|��������|����ֵ|��Чʱ��|����ʱ��|������λ|'
      end>
    Left = 348
    Top = 183
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�������ÿ���ѯ'
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
        ParamName = '��������'
        FieldName = '����'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end>
    AfterExec = MainRequestAfterExec
    Left = 384
    Top = 184
  end
end

inherited faqhBusiPayInQuery: TfaqhBusiPayInQuery
  Width = 716
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 716
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 539
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 626
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 716
    inherited Image1: TImage
      Width = 716
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 716
    Height = 28
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object WVLabel1: TWVLabel
      Left = 322
      Top = 8
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object WVLabel2: TWVLabel
      Left = 464
      Top = 8
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object lblBusiname: TLabel
      Left = 8
      Top = 8
      Width = 297
      Height = 12
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object edtBeginDate: TWVEdit
      Left = 376
      Top = 4
      Width = 81
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 0
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 520
      Top = 4
      Width = 89
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 1
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 46
    Width = 716
    Height = 413
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 507
      Height = 413
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻���'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ʱ��'
          Width = 70
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������ʺ�'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Vsvarstr1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���������˻�����'
          Width = 100
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'Sbank_acc2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�տ�����ʺ�'
          Width = 100
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'Vsvarstr2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�տ������˻�����'
          Width = 100
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա'
          Width = 80
          Visible = True
        end>
    end
    inherited RzSizePanel1: TRzSizePanel
      Height = 413
      inherited tvTree: TRzTreeView
        Height = 413
        OnClick = tvCustClick
      end
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
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
      end
      item
        Name = '��������'
        Caption = '��������'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�����|����Ա��|������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 244
    Top = 135
  end
  inherited MainRequest: TWVRequest
    ID = '�̻�����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end>
    Left = 280
    Top = 136
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 312
    Top = 136
  end
  inherited DataSource: TDataSource
    Left = 344
    Top = 136
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�̻���Ϣ������ѯ2'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end>
    Left = 280
    Top = 216
  end
  object WorkView2: TWorkView
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
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�̻���ʶ|'
      end>
    Left = 244
    Top = 215
  end
end

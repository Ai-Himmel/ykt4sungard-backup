inherited faqhappDeal: TfaqhappDeal
  Width = 700
  Height = 434
  inherited UIPanel1: TUIPanel
    Top = 404
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Hint = 'ȡ������'
      Caption = '����ȡ��'
      Glyph.Data = {00000000}
    end
    object btnReadQ: TBitBtn
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
      TabOrder = 2
      OnClick = btnReadQClick
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
    Height = 79
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label2: TLabel
      Left = 42
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label3: TLabel
      Left = 242
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label4: TLabel
      Left = 442
      Top = 9
      Width = 48
      Height = 12
      Caption = '���뵥��'
    end
    object Label5: TLabel
      Left = 66
      Top = 33
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label6: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object Label7: TLabel
      Left = 30
      Top = 57
      Width = 60
      Height = 12
      Caption = 'Ӧ�����к�'
    end
    object Label8: TLabel
      Left = 242
      Top = 33
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label9: TLabel
      Left = 442
      Top = 33
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object edtAppDate: TWVEdit
      Left = 92
      Top = 5
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object edtDealDate: TWVEdit
      Left = 294
      Top = 5
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object edtOrderNo: TWVEdit
      Left = 494
      Top = 5
      Width = 142
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 2
      Text = '<���뵥��>'
      WorkView = WorkView
      FieldName = '���뵥��'
    end
    object edtCardNo: TWVEdit
      Left = 92
      Top = 29
      Width = 142
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit6: TWVEdit
      Left = 294
      Top = 53
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
      Text = '<֤������>'
      WorkView = WorkView
      FieldName = '֤������'
    end
    object edtAppSerialNo: TWVEdit
      Left = 92
      Top = 53
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 6
      Text = '<Ӧ�����к�>'
      WorkView = WorkView
      FieldName = 'Ӧ�����к�'
    end
    object cbbIDType: TWVComboBox
      Left = 294
      Top = 29
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*233'
    end
    object WVComboBox1: TWVComboBox
      Left = 494
      Top = 29
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '����״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*234'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 97
    Width = 700
    Height = 307
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 307
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���뵥��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ԭ��'
          Width = 120
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
        Name = '������־'
        Caption = '������־'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '���뵥��'
        Caption = '���뵥��'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '֤������'
        Caption = '֤������'
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
        Name = 'Ӧ�����к�'
        Caption = 'Ӧ�����к�'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '����״̬'
        Caption = '����״̬'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��������|��������|���뵥��|����|֤������|Ӧ�����к�|��������|��' +
          '��״̬|'
      end>
    InvalidColor = clWhite
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '���뵥����'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���뵥��'
        FieldName = '���뵥��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'Ӧ�����к�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '233'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '234'
      end>
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 256
  end
  object WVCancelApp: TWorkView
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
        Name = '���뵥��'
        Caption = '���뵥��'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|������־|��������|��������|���뵥��|����|֤������|Ӧ�����к�|��' +
          '������|����״̬|'
      end>
    Left = 92
    Top = 295
  end
  object WVRCancelApp: TWVRequest
    WorkView = WVCancelApp
    ID = '���뵥ȡ��'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '���뵥��'
        FieldName = '���뵥��'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 296
  end
end

inherited faqhPatchAccount: TfaqhPatchAccount
  Width = 794
  Height = 486
  inherited UIPanel1: TUIPanel
    Top = 429
    Width = 794
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 617
      Top = 6
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 704
      Top = 6
      Hint = 'ȷ��'
      TabOrder = 2
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 537
      Height = 36
      Align = alLeft
      TabOrder = 0
      object Label6: TLabel
        Left = 18
        Top = 16
        Width = 48
        Height = 12
        Caption = '�������'
      end
      object Label7: TLabel
        Left = 184
        Top = 16
        Width = 36
        Height = 12
        Caption = '����Ա'
      end
      object Label8: TLabel
        Left = 343
        Top = 16
        Width = 60
        Height = 12
        Caption = '����Ա����'
      end
      object edtMoney: TWVEdit
        Left = 76
        Top = 11
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<�������>'
        WorkView = WVPatchAccount
        FieldName = '�������'
      end
      object edtChk: TWVEdit
        Left = 228
        Top = 11
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<����Ա>'
        WorkView = WVPatchAccount
        FieldName = '����Ա'
      end
      object edtChkPwd: TWVEdit
        Left = 413
        Top = 11
        Width = 100
        Height = 20
        Color = clWhite
        PasswordChar = '*'
        ReadOnly = False
        TabOrder = 2
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 794
    inherited Image1: TImage
      Width = 794
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 794
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 18
      Top = 9
      Width = 48
      Height = 12
      Caption = '���׿���'
    end
    object Label2: TLabel
      Left = 186
      Top = 9
      Width = 48
      Height = 12
      Caption = '�����ʺ�'
    end
    object Label3: TLabel
      Left = 410
      Top = 9
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object Label4: TLabel
      Left = 578
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object edtCardNo: TWVEdit
      Left = 76
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<���׿���>'
      WorkView = WorkView
      FieldName = '���׿���'
    end
    object edtBankCardNo: TWVEdit
      Left = 244
      Top = 5
      Width = 157
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<�����˺�>'
      WorkView = WorkView
      FieldName = '�����˺�'
    end
    object edtBeginDate: TWVEdit
      Left = 468
      Top = 5
      Width = 101
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 636
      Top = 5
      Width = 101
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 48
    Width = 794
    Height = 381
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 794
      Height = 381
      Columns = <
        item
          Expanded = False
          FieldName = 'sbank_pwd'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_pwd2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ˮ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ˮ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ؽ��'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���н��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׿���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���п���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ƽ���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '״̬'
          Width = 60
          Visible = True
        end>
    end
  end
  object StatusBar: TRzStatusBar [4]
    Left = 0
    Top = 465
    Width = 794
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
    TabOrder = 4
    object RzStatusPane1: TRzStatusPane
      Left = 0
      Top = 0
      Width = 794
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
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
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|��ʼ����|'
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�����˺�'
        Caption = '�����˺�'
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
        Name = '״̬'
        Caption = '״̬'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|ѧ�Ż�Ա����|���׿���|����|��ʾ����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 60
    Top = 183
  end
  inherited MainRequest: TWVRequest
    ID = '���ʽ��ײ�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�����˺�'
        FieldName = '�����˺�'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end>
    Left = 104
    Top = 184
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '3'
      end>
    Left = 144
    Top = 184
  end
  inherited DataSource: TDataSource
    Left = 184
    Top = 184
  end
  object WVRBackState: TWVRequest
    WorkView = WVBackState
    ID = '�޸Ŀ�״̬'
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
        ParamName = '����ʶ'
        FieldName = '����ʶ'
      end
      item
        ParamName = '��̨������ˮ��'
        FieldName = '��̨������ˮ��'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end>
    Left = 104
    Top = 328
  end
  object WVBackState: TWorkView
    WorkFields = <
      item
        Name = '����ʶ'
        Caption = '����ʶ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '��̨������ˮ��'
        Caption = '��̨������ˮ��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
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
        GroupIndex = 1
        DataField = 'lvol2'
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'vsmess'
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 56
    Top = 328
  end
  object WVRPatchAccount: TWVRequest
    WorkView = WVPatchAccount
    ID = '���ʽ���'
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
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�뿨ֵ'
        FieldName = '�뿨ֵ'
      end
      item
        ParamName = '����վ��'
        FieldName = '����վ��'
      end
      item
        ParamName = '��ǰ�����״���'
        FieldName = '��ǰ�����״���'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '����'
        FieldName = '����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����ֵ'
        FieldName = '����ֵ'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ֵ���'
        FieldName = '��ֵ���'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ˮ��������'
        FieldName = '��ˮ��������'
      end
      item
        ParamName = 'ԭ��ˮ��'
        FieldName = 'ԭ��ˮ��'
      end>
    Left = 104
    Top = 232
  end
  object WVPatchAccount: TWorkView
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '������'
        Caption = '������'
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
        Name = '�뿨ֵ'
        Caption = '�뿨ֵ'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '����վ��'
        Caption = '����վ��'
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
        Name = '��ǰ�����״���'
        Caption = '��ǰ�����״���'
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
        Name = '����Ա'
        Caption = '����Ա'
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
        Name = '�������'
        Caption = '�������'
        FieldType = wftUndefined
        DataType = kdtFloat
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '����Ա����'
        Caption = '����Ա����'
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
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '����ֵ'
        Caption = '����ֵ'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ˮ��'
        Caption = '��ˮ��'
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
        Name = '��ֵ���'
        Caption = '��ֵ���'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ˮ��������'
        Caption = '��ˮ��������'
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
        Name = 'ԭ��ˮ��'
        Caption = 'ԭ��ˮ��'
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
    FieldsMonitors = <>
    Left = 56
    Top = 232
  end
end

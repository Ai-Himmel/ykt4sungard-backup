inherited faqhSmartTermSetParam: TfaqhSmartTermSetParam
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
  end
  inherited UIPanel2: TUIPanel
    Left = 664
    Top = 432
    Width = 36
    Height = 27
    Align = alNone
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Visible = False
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '�豸��ʶ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ID    sbank_pwd2'
          PickList.Strings = ()
          Title.Caption = '�豸���'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '����'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Caption = '���ʹ���'
          Visible = True
        end>
    end
  end
  object ibnSetWorkKey: TBitBtn [3]
    Left = 251
    Top = 203
    Width = 158
    Height = 25
    Hint = '�����豸������Կ'
    Anchors = [akTop, akRight]
    Caption = '�����豸������Կ'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = ibnSetWorkKeyClick
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
        Name = '�豸����'
        Caption = '�豸����'
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
        Name = '�����豸ע���'
        Caption = '�����豸ע���'
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
        Name = '�豸����ID'
        Caption = '�豸����ID'
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
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
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
        Name = '�ϼ��豸����ID'
        Caption = '�ϼ��豸����ID'
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
        Name = '�豸״̬'
        Caption = '�豸״̬'
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
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
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
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
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
        Name = '�豸��������'
        Caption = '�豸��������'
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
        Name = '������Ա����'
        Caption = '������Ա����'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 28
    Top = 47
  end
  inherited MainRequest: TWVRequest
    ID = '�ֳֻ���������'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�����豸ע���'
        FieldName = '�����豸ע���'
      end
      item
        ParamName = '�豸����ID'
        FieldName = '�豸����ID'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = '�ϼ��豸����ID'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '�豸״̬'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�豸��������'
        FieldName = '�豸��������'
      end
      item
        ParamName = '������Ա����'
        FieldName = '������Ա����'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    Left = 64
    Top = 48
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 96
    Top = 48
  end
  inherited DataSource: TDataSource
    Left = 136
    Top = 48
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
    Left = 28
    Top = 207
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
    Left = 72
    Top = 208
  end
end

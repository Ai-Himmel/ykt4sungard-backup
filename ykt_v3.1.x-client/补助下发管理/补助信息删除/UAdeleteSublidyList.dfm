inherited faqhdeleteSublidyList: TfaqhdeleteSublidyList
  Width = 761
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 432
    Width = 761
    Height = 57
    object Label10: TLabel [0]
      Left = 38
      Top = 13
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object RzStatusPane1: TRzStatusPane [1]
      Left = 0
      Top = 36
      Width = 761
      Height = 21
      FrameStyle = fsStatus
      Align = alBottom
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 501
      Top = 6
    end
    inherited btnPrint: TBitBtn
      Left = 588
      Top = 6
      Caption = '����ɾ��'
      Enabled = True
      Glyph.Data = {00000000}
    end
    object edtPNo: TWVEdit
      Left = 100
      Top = 8
      Width = 125
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 2
    end
    object btnPDelete: TBitBtn
      Left = 676
      Top = 5
      Width = 75
      Height = 25
      Hint = '��ӡ'
      Anchors = [akTop, akRight]
      Caption = '����ɾ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = btnPDeleteClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 761
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 761
    Height = 78
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 54
      Top = 9
      Width = 36
      Height = 12
      Caption = 'ѧ����'
    end
    object Label2: TLabel
      Left = 430
      Top = 9
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object Label3: TLabel
      Left = 430
      Top = 33
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object Label4: TLabel
      Left = 42
      Top = 33
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label5: TLabel
      Left = 242
      Top = 33
      Width = 48
      Height = 12
      Caption = '��ȡ����'
    end
    object Label6: TLabel
      Left = 206
      Top = 57
      Width = 84
      Height = 12
      Caption = '���������֤��'
    end
    object Label7: TLabel
      Left = 30
      Top = 57
      Width = 60
      Height = 12
      Caption = '����������'
    end
    object Label8: TLabel
      Left = 466
      Top = 57
      Width = 24
      Height = 12
      Caption = '״̬'
    end
    object Label11: TLabel
      Left = 254
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label9: TLabel
      Left = 622
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
    end
    object edtPatchNo: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<�������κ�>'
      WorkView = WorkView
      FieldName = '�������κ�'
    end
    object WVEdit3: TWVEdit
      Left = 500
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<�������κ�>'
      WorkView = WorkView
      FieldName = '�������κ�'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object WVEdit5: TWVEdit
      Left = 300
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<��ȡ����>'
      WorkView = WorkView
      FieldName = '��ȡ����'
    end
    object WVEdit6: TWVEdit
      Left = 300
      Top = 53
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 5
      Text = '<���������֤��>'
      WorkView = WorkView
      FieldName = '���������֤��'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 53
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 6
      Text = '<����������>'
      WorkView = WorkView
      FieldName = '����������'
    end
    object cbbType: TWVComboBox
      Left = 501
      Top = 53
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*76'
    end
    object edtCustNo: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 8
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object edtCardNo: TWVEdit
      Left = 652
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 9
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 96
    Width = 761
    Height = 336
    inherited Grid: TRzDBGrid
      Width = 761
      Height = 336
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '�ͻ���'
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol11'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol10'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ȡ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ȡʱ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smain_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������־'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ժҪ'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֹ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ʊ������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ʊ�ݺ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���������֤��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������Ա'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '˳���'
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        Name = '��ȡ����'
        Caption = '��ȡ����'
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
        Name = '���������֤��'
        Caption = '���������֤��'
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
        Name = '����������'
        Caption = '����������'
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
        Name = '״̬'
        Caption = '״̬'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
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
        Checker.LowerCase = False
        Checker.UpperCase = False
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end>
    Left = 84
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '������Ϣɾ��'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ȡ����'
        FieldName = '��ȡ����'
      end
      item
        ParamName = '���������֤��'
        FieldName = '���������֤��'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '63'
      end
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '76'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '77'
      end>
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 256
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
      end
      item
        Name = 'ɾ����־'
        Caption = 'ɾ����־'
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
        MonitorValueChangedFields = '|'
      end>
    Left = 84
    Top = 303
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'ɾ��'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
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
      end
      item
        ParamName = 'ɾ����־'
        FieldName = 'ɾ����־'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 304
  end
end

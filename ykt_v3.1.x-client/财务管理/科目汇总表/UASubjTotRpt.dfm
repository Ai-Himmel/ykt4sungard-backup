inherited faQueryAreaTable: TfaQueryAreaTable
  Width = 709
  Height = 453
  object WVLabel4: TWVLabel [0]
    Left = 160
    Top = 144
    Width = 48
    Height = 12
    Caption = 'WVLabel4'
  end
  inherited upnlBottom: TUIPanel
    Top = 416
    Width = 709
    inherited tlb1: TRzToolbar
      ToolbarControls = (
        btn100
        btnPageWidth
        rzspcr1
        btnFirst
        btnprevious
        btnNext
        btnLast
        rzspcr2
        btnExpXls
        btnPagePrint
        btnSetup
        rzspcr3
        btnDesign
        btnOpenRpt)
    end
    inherited btnQuery: TBitBtn
      Left = 608
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 709
    inherited Image1: TImage
      Width = 709
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 709
    Height = 398
    inherited Grid: TRzDBGrid
      Top = 128
      Width = 709
      Height = 270
      Align = alNone
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 2
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 74
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 79
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���򼶱�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϸ��ַ'
          Width = 124
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Width = 130
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Top = 41
      Width = 709
      Height = 357
      TabOrder = 1
    end
    object pnlRptQ: TPanel
      Left = 0
      Top = 0
      Width = 709
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      Color = 14999516
      TabOrder = 0
      object lbl2: TLabel
        Left = 210
        Top = 14
        Width = 12
        Height = 12
        Caption = '��'
      end
      object Label5: TLabel
        Left = 322
        Top = 13
        Width = 48
        Height = 12
        Caption = '���ܼ���'
      end
      object chkAcc: TCheckBox
        Left = 592
        Top = 11
        Width = 97
        Height = 17
        Caption = '��δ����ƾ֤'
        TabOrder = 5
        Visible = False
      end
      object rgQType: TRzRadioGroup
        Left = 8
        Top = 8
        Width = 101
        Height = 17
        Color = 14999516
        Columns = 2
        GroupStyle = gsTopLine
        ItemIndex = 1
        Items.Strings = (
          '�·�'
          '����')
        TabOrder = 0
        ThemeAware = False
        OnClick = rgQTypeClick
      end
      object edtBeginDate: TWVEdit
        Left = 115
        Top = 8
        Width = 90
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<��ʼ����>'
        WorkView = WorkView
        FieldName = '��ʼ����'
      end
      object edtEndDate: TWVEdit
        Left = 227
        Top = 8
        Width = 90
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
      end
      object chkShowSub: TCheckBox
        Left = 472
        Top = 11
        Width = 121
        Height = 17
        Caption = '��ʾδ���׵Ŀ�Ŀ'
        TabOrder = 4
      end
      object cbbLeval: TWVComboBox
        Left = 372
        Top = 9
        Width = 93
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '��Ŀ����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-70'
      end
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��Ŀ����'
        Caption = '��Ŀ����'
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
        Name = '����δ����'
        Caption = '����δ����'
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
        Name = '��ѯ��ʽ'
        Caption = '��ѯ��ʽ'
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
        Name = '��ʾδ����'
        Caption = '��ʾδ����'
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
    Top = 183
  end
  inherited MainRequest: TWVRequest
    ID = '��Ŀ���ܱ���'
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
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��Ŀ����'
      end
      item
        ParamName = '����δ����'
        FieldName = '����δ����'
      end
      item
        ParamName = '��ѯ��ʽ'
        FieldName = '��ѯ��ʽ'
      end
      item
        ParamName = '��ʾδ����'
        FieldName = '��ʾδ����'
      end>
    Left = 104
    Top = 184
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 144
    Top = 184
  end
  inherited DataSource: TDataSource
    Left = 184
    Top = 184
  end
  inherited rptReport: TRMReport
    ReportData = {}
  end
  inherited rmDS: TRMDBDataSet
    DataSet = zqry1
  end
  object zqry1: TZQuery
    Connection = cmAccountMgrImp.conFB
    SQL.Strings = (
      'select * from subjtot order by lineno')
    Params = <>
    Left = 259
    Top = 89
  end
end

inherited faqhwaterInfo_cqcsgl: TfaqhwaterInfo_cqcsgl
  Width = 700
  Height = 618
  inherited UIPanel1: TUIPanel
    Top = 582
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 96
      Top = 5
      Width = 90
      Caption = '������Ϣ(&R)'
      TabOrder = 1
      Visible = False
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 10
      TabOrder = 0
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 2
    inherited Image1: TImage
      Width = 700
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 700
    Height = 564
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Caption = '��̨��ˮ��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Caption = '��ˮ��̨��ˮ��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt0'
          PickList.Strings = ()
          Title.Caption = '��Ǯ������ֵ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt2'
          PickList.Strings = ()
          Title.Caption = 'СǮ������ֵ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol9'
          PickList.Strings = ()
          Title.Caption = '��Ǯ������'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = 'СǮ������'
          Visible = True
        end>
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 18
    Width = 700
    Height = 564
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 184
      Top = 72
      Width = 377
      Height = 193
      Caption = '����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 30
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���׿���'
      end
      object RzStatusPane1: TRzStatusPane
        Left = 13
        Top = 62
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��    ��'
      end
      object RzStatusPane2: TRzStatusPane
        Left = 13
        Top = 94
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ѧ /����'
      end
      object RzStatusPane4: TRzStatusPane
        Left = 13
        Top = 126
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��Ǯ�����'
      end
      object rzstspn1: TRzStatusPane
        Left = 13
        Top = 158
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��Ǯ����ֵ����'
      end
      object edtMoney: TWVEdit
        Left = 132
        Top = 127
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object edtNo: TWVEdit
        Left = 132
        Top = 95
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edtName: TWVEdit
        Left = 132
        Top = 63
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
      end
      object edtCardNo: TWVEdit
        Left = 132
        Top = 31
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtBigNum: TWVEdit
        Left = 132
        Top = 159
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
    end
    object btnReadCard: TButton
      Left = 470
      Top = 517
      Width = 90
      Height = 25
      Caption = '������Ϣ(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnReadCardClick
    end
    object grp1: TGroupBox
      Left = 184
      Top = 272
      Width = 377
      Height = 241
      Caption = 'СǮ����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object RzStatusPane5: TRzStatusPane
        Left = 13
        Top = 49
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'Ǯ�����'
      end
      object RzStatusPane6: TRzStatusPane
        Left = 13
        Top = 81
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�ܳ�ֵ���'
      end
      object rzstspn2: TRzStatusPane
        Left = 13
        Top = 17
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'Ǯ������'
      end
      object RzStatusPane7: TRzStatusPane
        Left = 13
        Top = 113
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'Ǯ����Ч��'
      end
      object RzStatusPane8: TRzStatusPane
        Left = 13
        Top = 145
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ˮ��1'
      end
      object RzStatusPane9: TRzStatusPane
        Left = 13
        Top = 177
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ˮ��2'
      end
      object RzStatusPane10: TRzStatusPane
        Left = 13
        Top = 209
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ˮ��3'
      end
      object edtsmlMoney1: TWVEdit
        Left = 132
        Top = 51
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtTotalMoney: TWVEdit
        Left = 132
        Top = 83
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edtExpireDate: TWVEdit
        Left = 132
        Top = 115
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object cbbSmlNo: TWVComboBox
        Left = 132
        Top = 18
        Width = 157
        Height = 22
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 14
        TabOrder = 0
        WorkView = WorkView
        FieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-26'
      end
      object edtP1: TWVEdit
        Left = 132
        Top = 147
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object edtP2: TWVEdit
        Left = 132
        Top = 179
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
      object edtP3: TWVEdit
        Left = 132
        Top = 211
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|���׿���|��ֵ���|����Ա����|��Ǯ�����|��Ǯ������|СǮ������|' +
          'СǮ�����|'
      end>
    Left = 36
    Top = 231
  end
  inherited MainRequest: TWVRequest
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end>
    Left = 80
    Top = 232
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 80
    Top = 264
  end
  inherited DataSource: TDataSource
    Left = 80
    Top = 296
  end
end

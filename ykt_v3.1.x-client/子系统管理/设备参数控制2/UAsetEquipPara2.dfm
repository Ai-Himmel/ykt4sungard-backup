inherited faqhsetEquipPara2: TfaqhsetEquipPara2
  Width = 859
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 859
    TabOrder = 5
    inherited btnQuery: TBitBtn
      Left = 682
      Width = 82
      Enabled = False
      TabOrder = 3
    end
    inherited btnPrint: TBitBtn
      Left = 769
      Width = 82
      Hint = 'ִ������'
      Caption = 'ִ������&E'
      TabOrder = 4
      Glyph.Data = {00000000}
    end
    object btnClear: TBitBtn
      Left = 594
      Top = 3
      Width = 82
      Height = 25
      Hint = '������'
      Anchors = [akTop, akRight]
      Caption = '������&C'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnClearClick
    end
    object btnselectall: TBitBtn
      Left = 378
      Top = 3
      Width = 82
      Height = 25
      Hint = '�豸ȫѡ'
      Anchors = [akTop, akRight]
      Caption = '�豸ȫѡ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnselectallClick
    end
    object btnselectno: TBitBtn
      Left = 466
      Top = 3
      Width = 82
      Height = 25
      Hint = '�豸���'
      Anchors = [akTop, akRight]
      Caption = '�豸���'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnselectnoClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 859
    inherited Image1: TImage
      Width = 859
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 859
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = -2
      Top = 34
      Width = 72
      Height = 12
      Caption = '�ϼ�������'
    end
    object Label2: TLabel
      Left = 221
      Top = 34
      Width = 72
      Height = 12
      Caption = '�豸������'
    end
    object Label3: TLabel
      Left = 454
      Top = 34
      Width = 48
      Height = 12
      Caption = '�豸����'
    end
    object Label4: TLabel
      Left = 22
      Top = 10
      Width = 48
      Height = 12
      Caption = '�豸����'
    end
    object Label5: TLabel
      Left = 233
      Top = 10
      Width = 60
      Height = 12
      Caption = '������ϵͳ'
    end
    object WVEdit1: TWVEdit
      Left = 76
      Top = 30
      Width = 133
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<�ϼ��豸>'
      WorkView = WorkView
      FieldName = '�ϼ��豸'
    end
    object WVEdit2: TWVEdit
      Left = 304
      Top = 30
      Width = 133
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<�豸������>'
      WorkView = WorkView
      FieldName = '�豸������'
    end
    object WVEdit3: TWVEdit
      Left = 508
      Top = 30
      Width = 141
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<�豸����>'
      WorkView = WorkView
      FieldName = '�豸����'
    end
    object WVComboBox18: TWVComboBox
      Left = 76
      Top = 6
      Width = 133
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '�豸����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*47'
    end
    object WVComboBox17: TWVComboBox
      Left = 304
      Top = 6
      Width = 133
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView
      FieldName = '��ϵͳ'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-32'
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 217
    Top = 73
    Width = 642
    Height = 386
    TabOrder = 4
    inherited Grid: TRzDBGrid
      Align = alNone
    end
  end
  object RzSizePanel1: TRzSizePanel [4]
    Left = 0
    Top = 73
    Width = 217
    Height = 386
    Color = 16184303
    GradientColorAdjustment = 50
    HotSpotVisible = True
    SizeBarWidth = 5
    TabOrder = 2
    UseGradients = True
    object pnl1: TRzPanel
      Left = 0
      Top = 0
      Width = 211
      Height = 386
      Align = alClient
      BorderOuter = fsGroove
      Color = 16184303
      TabOrder = 0
      object pnl3: TRzPanel
        Left = 2
        Top = 2
        Width = 207
        Height = 55
        Align = alTop
        BorderOuter = fsNone
        Color = 16184303
        TabOrder = 0
        object lbl1: TLabel
          Left = 8
          Top = 8
          Width = 73
          Height = 14
          AutoSize = False
          Caption = '��������'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object cbbName: TWVComboBox
          Left = 5
          Top = 28
          Width = 196
          Height = 20
          DropDownCount = 16
          ItemHeight = 12
          TabOrder = 0
          Text = '<>'
          OnChange = cbbNameChange
          Items.Strings = (
            '1-�´��豸ʱ��'
            '2-�ϴ��豸ʱ��'
            '3-�豸����������'
            '4-ǿ��ǰ�û�ǩ��'
            '5-�´����ѱ���'
            '6-���ô�������޶�'
            '7-�ɼ���ʷ������ˮ'
            '8-�ɼ���ʷ�ֽ��ֵ��ˮ'
            '9-���������ۼ��޶�'
            '10-�Ž���������'
            '11-�´�ˮ�ط���')
          AutoDropDown = False
        end
      end
      object PnlCard: TRzSizePanel
        Left = 2
        Top = 133
        Width = 207
        Height = 251
        Align = alClient
        Color = 16184303
        HotSpotVisible = True
        SizeBarWidth = 7
        TabOrder = 2
        UseGradients = True
        object dxInspector2: TdxInspector
          Left = 0
          Top = 25
          Width = 207
          Height = 226
          Align = alClient
          ParentColor = True
          TabOrder = 1
          DividerPos = 101
          GridColor = clSilver
          Flat = True
          PaintStyle = ipsSimple
          Data = {
            9C1800000001000008000000000000000B0000006478496E73436865636B3108
            000000000000000B0000006478496E73436865636B3208000000000000000B00
            00006478496E73436865636B3308000000000000000B0000006478496E734368
            65636B3408000000000000000B0000006478496E73436865636B350800000000
            0000000B0000006478496E73436865636B3608000000000000000B0000006478
            496E73436865636B3708000000000000000B0000006478496E73436865636B38
            08000000000000000B0000006478496E73436865636B3908000000000000000C
            0000006478496E73436865636B313008000000000000000C0000006478496E73
            436865636B313108000000000000000C0000006478496E73436865636B313208
            000000000000000C0000006478496E73436865636B313308000000000000000C
            0000006478496E73436865636B313408000000000000000C0000006478496E73
            436865636B313508000000000000000C0000006478496E73436865636B313608
            000000000000000C0000006478496E73436865636B313708000000000000000C
            0000006478496E73436865636B313808000000000000000C0000006478496E73
            436865636B313908000000000000000C0000006478496E73436865636B323008
            000000000000000C0000006478496E73436865636B323108000000000000000C
            0000006478496E73436865636B323208000000000000000C0000006478496E73
            436865636B323308000000000000000C0000006478496E73436865636B323408
            000000000000000C0000006478496E73436865636B323508000000000000000C
            0000006478496E73436865636B323608000000000000000C0000006478496E73
            436865636B323708000000000000000C0000006478496E73436865636B323808
            000000000000000C0000006478496E73436865636B323908000000000000000C
            0000006478496E73436865636B333008000000000000000C0000006478496E73
            436865636B333108000000000000000C0000006478496E73436865636B333208
            000000000000000C0000006478496E73436865636B333308000000000000000C
            0000006478496E73436865636B333408000000000000000C0000006478496E73
            436865636B333508000000000000000C0000006478496E73436865636B333608
            000000000000000C0000006478496E73436865636B333708000000000000000C
            0000006478496E73436865636B333808000000000000000C0000006478496E73
            436865636B333908000000000000000C0000006478496E73436865636B343008
            000000000000000C0000006478496E73436865636B343108000000000000000C
            0000006478496E73436865636B343208000000000000000C0000006478496E73
            436865636B343308000000000000000C0000006478496E73436865636B343408
            000000000000000C0000006478496E73436865636B343508000000000000000C
            0000006478496E73436865636B343608000000000000000C0000006478496E73
            436865636B343708000000000000000C0000006478496E73436865636B343808
            000000000000000C0000006478496E73436865636B343908000000000000000C
            0000006478496E73436865636B353008000000000000000C0000006478496E73
            436865636B353108000000000000000C0000006478496E73436865636B353208
            000000000000000C0000006478496E73436865636B353308000000000000000C
            0000006478496E73436865636B353408000000000000000C0000006478496E73
            436865636B353508000000000000000C0000006478496E73436865636B353608
            000000000000000C0000006478496E73436865636B353708000000000000000C
            0000006478496E73436865636B353808000000000000000C0000006478496E73
            436865636B353908000000000000000C0000006478496E73436865636B363008
            000000000000000C0000006478496E73436865636B363108000000000000000C
            0000006478496E73436865636B363208000000000000000C0000006478496E73
            436865636B363308000000000000000C0000006478496E73436865636B363408
            000000000000000C0000006478496E73436865636B363508000000000000000C
            0000006478496E73436865636B363608000000000000000C0000006478496E73
            436865636B363708000000000000000C0000006478496E73436865636B363808
            000000000000000C0000006478496E73436865636B363908000000000000000C
            0000006478496E73436865636B373008000000000000000C0000006478496E73
            436865636B373108000000000000000C0000006478496E73436865636B373208
            000000000000000C0000006478496E73436865636B373308000000000000000C
            0000006478496E73436865636B373408000000000000000C0000006478496E73
            436865636B373508000000000000000C0000006478496E73436865636B373608
            000000000000000C0000006478496E73436865636B373708000000000000000C
            0000006478496E73436865636B373808000000000000000C0000006478496E73
            436865636B373908000000000000000C0000006478496E73436865636B383008
            000000000000000C0000006478496E73436865636B383108000000000000000C
            0000006478496E73436865636B383208000000000000000C0000006478496E73
            436865636B383308000000000000000C0000006478496E73436865636B383408
            000000000000000C0000006478496E73436865636B383508000000000000000C
            0000006478496E73436865636B383608000000000000000C0000006478496E73
            436865636B383708000000000000000C0000006478496E73436865636B383808
            000000000000000C0000006478496E73436865636B383908000000000000000C
            0000006478496E73436865636B393008000000000000000C0000006478496E73
            436865636B393108000000000000000C0000006478496E73436865636B393208
            000000000000000C0000006478496E73436865636B393308000000000000000C
            0000006478496E73436865636B393408000000000000000C0000006478496E73
            436865636B393508000000000000000C0000006478496E73436865636B393608
            000000000000000C0000006478496E73436865636B393708000000000000000C
            0000006478496E73436865636B393808000000000000000C0000006478496E73
            436865636B393908000000000000000D0000006478496E73436865636B313030
            08000000000000000D0000006478496E73436865636B31303108000000000000
            000D0000006478496E73436865636B31303208000000000000000D0000006478
            496E73436865636B31303308000000000000000D0000006478496E7343686563
            6B31303408000000000000000D0000006478496E73436865636B313035080000
            00000000000D0000006478496E73436865636B31303608000000000000000D00
            00006478496E73436865636B31303708000000000000000D0000006478496E73
            436865636B31303808000000000000000D0000006478496E73436865636B3130
            3908000000000000000D0000006478496E73436865636B313130080000000000
            00000D0000006478496E73436865636B31313108000000000000000D00000064
            78496E73436865636B31313208000000000000000D0000006478496E73436865
            636B31313308000000000000000D0000006478496E73436865636B3131340800
            0000000000000D0000006478496E73436865636B31313508000000000000000D
            0000006478496E73436865636B31313608000000000000000D0000006478496E
            73436865636B31313708000000000000000D0000006478496E73436865636B31
            313808000000000000000D0000006478496E73436865636B3131390800000000
            0000000D0000006478496E73436865636B31323008000000000000000D000000
            6478496E73436865636B31323108000000000000000D0000006478496E734368
            65636B31323208000000000000000D0000006478496E73436865636B31323308
            000000000000000D0000006478496E73436865636B3132340800000000000000
            0D0000006478496E73436865636B31323508000000000000000D000000647849
            6E73436865636B31323608000000000000000D0000006478496E73436865636B
            31323708000000000000000D0000006478496E73436865636B31323808000000
            000000000D0000006478496E73436865636B31323908000000000000000D0000
            006478496E73436865636B31333008000000000000000D0000006478496E7343
            6865636B31333108000000000000000D0000006478496E73436865636B313332
            08000000000000000D0000006478496E73436865636B31333308000000000000
            000D0000006478496E73436865636B31333408000000000000000D0000006478
            496E73436865636B31333508000000000000000D0000006478496E7343686563
            6B31333608000000000000000D0000006478496E73436865636B313337080000
            00000000000D0000006478496E73436865636B31333808000000000000000D00
            00006478496E73436865636B31333908000000000000000D0000006478496E73
            436865636B31343008000000000000000D0000006478496E73436865636B3134
            3108000000000000000D0000006478496E73436865636B313432080000000000
            00000D0000006478496E73436865636B31343308000000000000000D00000064
            78496E73436865636B31343408000000000000000D0000006478496E73436865
            636B31343508000000000000000D0000006478496E73436865636B3134360800
            0000000000000D0000006478496E73436865636B31343708000000000000000D
            0000006478496E73436865636B31343808000000000000000D0000006478496E
            73436865636B31343908000000000000000D0000006478496E73436865636B31
            353008000000000000000D0000006478496E73436865636B3135310800000000
            0000000D0000006478496E73436865636B31353208000000000000000D000000
            6478496E73436865636B31353308000000000000000D0000006478496E734368
            65636B31353408000000000000000D0000006478496E73436865636B31353508
            000000000000000D0000006478496E73436865636B3135360800000000000000
            0D0000006478496E73436865636B31353708000000000000000D000000647849
            6E73436865636B31353808000000000000000D0000006478496E73436865636B
            31353908000000000000000D0000006478496E73436865636B31363008000000
            000000000D0000006478496E73436865636B31363108000000000000000D0000
            006478496E73436865636B31363208000000000000000D0000006478496E7343
            6865636B31363308000000000000000D0000006478496E73436865636B313634
            08000000000000000D0000006478496E73436865636B31363508000000000000
            000D0000006478496E73436865636B31363608000000000000000D0000006478
            496E73436865636B31363708000000000000000D0000006478496E7343686563
            6B31363808000000000000000D0000006478496E73436865636B313639080000
            00000000000D0000006478496E73436865636B31373008000000000000000D00
            00006478496E73436865636B31373108000000000000000D0000006478496E73
            436865636B31373208000000000000000D0000006478496E73436865636B3137
            3308000000000000000D0000006478496E73436865636B313734080000000000
            00000D0000006478496E73436865636B31373508000000000000000D00000064
            78496E73436865636B31373608000000000000000D0000006478496E73436865
            636B31373708000000000000000D0000006478496E73436865636B3137380800
            0000000000000D0000006478496E73436865636B31373908000000000000000D
            0000006478496E73436865636B31383008000000000000000D0000006478496E
            73436865636B31383108000000000000000D0000006478496E73436865636B31
            383208000000000000000D0000006478496E73436865636B3138330800000000
            0000000D0000006478496E73436865636B31383408000000000000000D000000
            6478496E73436865636B31383508000000000000000D0000006478496E734368
            65636B31383608000000000000000D0000006478496E73436865636B31383708
            000000000000000D0000006478496E73436865636B3138380800000000000000
            0D0000006478496E73436865636B31383908000000000000000D000000647849
            6E73436865636B31393008000000000000000D0000006478496E73436865636B
            31393108000000000000000D0000006478496E73436865636B31393208000000
            000000000D0000006478496E73436865636B31393308000000000000000D0000
            006478496E73436865636B31393408000000000000000D0000006478496E7343
            6865636B31393508000000000000000D0000006478496E73436865636B313936
            08000000000000000D0000006478496E73436865636B31393708000000000000
            000D0000006478496E73436865636B31393808000000000000000D0000006478
            496E73436865636B31393908000000000000000D0000006478496E7343686563
            6B32303008000000000000000D0000006478496E73436865636B323031080000
            00000000000D0000006478496E73436865636B32303208000000000000000D00
            00006478496E73436865636B32303308000000000000000D0000006478496E73
            436865636B32303408000000000000000D0000006478496E73436865636B3230
            3508000000000000000D0000006478496E73436865636B323036080000000000
            00000D0000006478496E73436865636B32303708000000000000000D00000064
            78496E73436865636B32303808000000000000000D0000006478496E73436865
            636B32303908000000000000000D0000006478496E73436865636B3231300800
            0000000000000D0000006478496E73436865636B32313108000000000000000D
            0000006478496E73436865636B32313208000000000000000D0000006478496E
            73436865636B32313308000000000000000D0000006478496E73436865636B32
            313408000000000000000D0000006478496E73436865636B3231350800000000
            0000000D0000006478496E73436865636B32313608000000000000000D000000
            6478496E73436865636B32313708000000000000000D0000006478496E734368
            65636B32313808000000000000000D0000006478496E73436865636B32313908
            000000000000000D0000006478496E73436865636B3232300800000000000000
            0D0000006478496E73436865636B32323108000000000000000D000000647849
            6E73436865636B32323208000000000000000D0000006478496E73436865636B
            32323308000000000000000D0000006478496E73436865636B32323408000000
            000000000D0000006478496E73436865636B32323508000000000000000D0000
            006478496E73436865636B32323608000000000000000D0000006478496E7343
            6865636B32323708000000000000000D0000006478496E73436865636B323238
            08000000000000000D0000006478496E73436865636B32323908000000000000
            000D0000006478496E73436865636B32333008000000000000000D0000006478
            496E73436865636B32333108000000000000000D0000006478496E7343686563
            6B32333208000000000000000D0000006478496E73436865636B323333080000
            00000000000D0000006478496E73436865636B32333408000000000000000D00
            00006478496E73436865636B32333508000000000000000D0000006478496E73
            436865636B32333608000000000000000D0000006478496E73436865636B3233
            3708000000000000000D0000006478496E73436865636B323338080000000000
            00000D0000006478496E73436865636B32333908000000000000000D00000064
            78496E73436865636B32343008000000000000000D0000006478496E73436865
            636B32343108000000000000000D0000006478496E73436865636B3234320800
            0000000000000D0000006478496E73436865636B32343308000000000000000D
            0000006478496E73436865636B32343408000000000000000D0000006478496E
            73436865636B32343508000000000000000D0000006478496E73436865636B32
            343608000000000000000D0000006478496E73436865636B3234370800000000
            0000000D0000006478496E73436865636B32343808000000000000000D000000
            6478496E73436865636B32343908000000000000000D0000006478496E734368
            65636B32353008000000000000000D0000006478496E73436865636B32353108
            000000000000000D0000006478496E73436865636B3235320800000000000000
            0D0000006478496E73436865636B32353308000000000000000D000000647849
            6E73436865636B32353408000000000000000D0000006478496E73436865636B
            32353508000000000000000D0000006478496E73436865636B32353600000000}
          object dxInsCheck1: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck2: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck3: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck4: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck5: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck6: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck7: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck8: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck9: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck10: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck11: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck12: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck13: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck14: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck15: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck16: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck17: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck18: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck19: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck20: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck21: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck22: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck23: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck24: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck25: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck26: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck27: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck28: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck29: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck30: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck31: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck32: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck33: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck34: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck35: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck36: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck37: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck38: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck39: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck40: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck41: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck42: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck43: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck44: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck45: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck46: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck47: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck48: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck49: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck50: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck51: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck52: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck53: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck54: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck55: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck56: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck57: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck58: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck59: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck60: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck61: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck62: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck63: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck64: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck65: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck66: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck67: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck68: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck69: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck70: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck71: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck72: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck73: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck74: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck75: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck76: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck77: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck78: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck79: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck80: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck81: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck82: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck83: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck84: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck85: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck86: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck87: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck88: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck89: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck90: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck91: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck92: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck93: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck94: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck95: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck96: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck97: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck98: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck99: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck100: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck101: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck102: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck103: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck104: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck105: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck106: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck107: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck108: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck109: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck110: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck111: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck112: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck113: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck114: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck115: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck116: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck117: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck118: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck119: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck120: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck121: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck122: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck123: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck124: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck125: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck126: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck127: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck128: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck129: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck130: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck131: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck132: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck133: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck134: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck135: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck136: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck137: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck138: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck139: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck140: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck141: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck142: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck143: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck144: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck145: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck146: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck147: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck148: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck149: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck150: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck151: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck152: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck153: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck154: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck155: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck156: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck157: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck158: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck159: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck160: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck161: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck162: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck163: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck164: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck165: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck166: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck167: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck168: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck169: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck170: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck171: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck172: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck173: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck174: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck175: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck176: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck177: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck178: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck179: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck180: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck181: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck182: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck183: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck184: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck185: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck186: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck187: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck188: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck189: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck190: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck191: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck192: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck193: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck194: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck195: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck196: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck197: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck198: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck199: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck200: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck201: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck202: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck203: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck204: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck205: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck206: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck207: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck208: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck209: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck210: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck211: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck212: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck213: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck214: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck215: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck216: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck217: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck218: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck219: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck220: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck221: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck222: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck223: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck224: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck225: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck226: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck227: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck228: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck229: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck230: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck231: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck232: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck233: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck234: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck235: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck236: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck237: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck238: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck239: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck240: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck241: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck242: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck243: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck244: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck245: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck246: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck247: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck248: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck249: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck250: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck251: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck252: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck253: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck254: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck255: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
          object dxInsCheck256: TdxInspectorTextCheckRow
            ValueChecked = 'True'
            ValueUnchecked = 'False'
          end
        end
        object pnl4: TRzPanel
          Left = 0
          Top = 0
          Width = 207
          Height = 25
          Align = alTop
          Alignment = taLeftJustify
          BorderOuter = fsFlat
          Caption = '�շ����'
          Color = 16184303
          Font.Charset = GB2312_CHARSET
          Font.Color = clNavy
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
      end
      object PnlTask: TRzSizePanel
        Left = 2
        Top = 57
        Width = 207
        Height = 76
        Align = alTop
        Color = 16184303
        HotSpotVisible = True
        SizeBarWidth = 5
        TabOrder = 1
        UseGradients = True
        object dxInspector1: TdxInspector
          Left = 0
          Top = 0
          Width = 207
          Height = 70
          Align = alClient
          ParentColor = True
          TabOrder = 0
          DividerPos = 140
          GridColor = clSilver
          Flat = True
          PaintStyle = ipsSimple
          Data = {
            840000000500000008000000000000000D0000006478496E73526F774D6F6E65
            7908000000000000000D0000006478496E73526F77426567696E080000000000
            00000B0000006478496E73526F77456E6408000000000000000C000000647849
            6E73526F774761746508000000000000000F0000006478496E73526F77466565
            5479706500000000}
          object dxInsRowMoney: TdxInspectorTextCurrencyRow
            MaxLength = 0
            DecimalPlaces = 0
            DisplayFormat = '��,0'
            MinValue = 1
            MaxValue = 999
          end
          object dxInsRowBegin: TdxInspectorTextCurrencyRow
            DecimalPlaces = 0
            DisplayFormat = '0'
          end
          object dxInsRowEnd: TdxInspectorTextCurrencyRow
            DecimalPlaces = 0
            DisplayFormat = '0'
          end
          object dxInsRowGate: TdxInspectorTextPickRow
            Items.Strings = (
              '0-����'
              '1-����'
              '2-��һ��'
              '4-ָ��ʱ�ο���')
          end
          object dxInsRowFeeType: TdxInspectorTextPickRow
          end
        end
      end
    end
  end
  object pnl2: TRzPanel [5]
    Left = 217
    Top = 73
    Width = 642
    Height = 386
    Align = alClient
    BorderOuter = fsGroove
    Color = 16184303
    TabOrder = 3
    object RzSizePanel2: TRzSizePanel
      Left = 2
      Top = 248
      Width = 638
      Height = 136
      Align = alBottom
      Color = 16184303
      GradientColorAdjustment = 40
      HotSpotVisible = True
      SizeBarWidth = 5
      TabOrder = 1
      UseGradients = True
      object lvResult: TListView
        Left = 0
        Top = 6
        Width = 638
        Height = 130
        Align = alClient
        Columns = <
          item
            Caption = '��������'
            Width = 150
          end
          item
            Caption = '����ʱ��'
            Width = 130
          end
          item
            Caption = '�豸����'
            Width = 150
          end
          item
            Caption = '���'
            Width = 150
          end>
        ColumnClick = False
        FlatScrollBars = True
        TabOrder = 0
        ViewStyle = vsReport
      end
    end
    object lvEqu: TListView
      Left = 2
      Top = 2
      Width = 638
      Height = 246
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = 'ѡ��'
          Width = 40
        end
        item
          Caption = '�豸���'
          Width = 60
        end
        item
          Caption = '�豸������'
          Width = 120
        end
        item
          Caption = '�豸����'
          Width = 200
        end
        item
          Caption = '�ϼ��豸'
          Width = 120
        end
        item
          Caption = '�豸����'
          Width = 80
        end
        item
          Caption = '������ϵͳ'
          Width = 80
        end>
      ColumnClick = False
      FlatScrollBars = True
      GridLines = True
      TabOrder = 0
      ViewStyle = vsReport
      OnClick = lvEquClick
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
        Name = '�ϼ��豸'
        Caption = '�ϼ��豸'
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
        Name = '�豸������'
        Caption = '�豸������'
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
        Name = '�豸����'
        Caption = '�豸����'
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
        Name = '�豸����'
        Caption = '�豸����'
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
        Name = '��ϵͳ'
        Caption = '��ϵͳ'
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
        MonitorValueChangedFields = '|��ϵͳ|���׿���|ѧ����|ģ������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 356
    Top = 111
  end
  inherited MainRequest: TWVRequest
    ID = '�豸��ѯ'
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
        ParamName = '�ϼ��豸'
        FieldName = '�ϼ��豸'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '��ϵͳ'
        FieldName = '��ϵͳ'
      end>
    Left = 280
    Top = 112
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 320
    Top = 112
  end
  inherited DataSource: TDataSource
    Left = 392
    Top = 112
  end
  object WVDownEquipClock: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate0'
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
      end
      item
        Name = '�´�ʱ��'
        Caption = '�´�ʱ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sserial0'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 284
    Top = 153
  end
  object WVRDownEquipClock: TWVRequest
    WorkView = WVDownEquipClock
    ID = '�´��豸ʱ��'
    Bindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '�´�ʱ��'
        FieldName = '�´�ʱ��'
        Direction = bdParam2Field
      end
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
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end>
    Left = 316
    Top = 153
  end
  object WVUpEquipClock: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate0'
      end
      item
        Name = '�ϴ�ʱ��'
        Caption = '�ϴ�ʱ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sserial0'
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
        DataField = 'vsvarstr0'
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
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 284
    Top = 185
  end
  object WVRUpEquipClock: TWVRequest
    WorkView = WVUpEquipClock
    ID = '�ϴ��豸ʱ��'
    Bindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '�ϴ�ʱ��'
        FieldName = '�ϴ�ʱ��'
        Direction = bdParam2Field
      end
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
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end>
    Left = 316
    Top = 185
  end
  object WVEquipCompellOut: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate0'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 368
    Top = 152
  end
  object WVREquipCompellOut: TWVRequest
    WorkView = WVEquipCompellOut
    ID = 'ǿ��ǰ�û����豸ǩ��'
    Bindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
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
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end>
    Left = 400
    Top = 152
  end
  object WVRDownShareMoney: TWVRequest
    WorkView = WVDownShareMoney
    ID = '�´����ѱ���'
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
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
      end>
    Left = 317
    Top = 223
  end
  object WVDownShareMoney: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lcert_code'
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
      end
      item
        Name = '�豸������'
        Caption = '�豸������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sdate0'
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 285
    Top = 223
  end
  object WVRDownMaxMoney: TWVRequest
    WorkView = WVDownMaxMoney
    ID = '�´���������޶�'
    Bindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '��������޶�'
        FieldName = '��������޶�'
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
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end>
    Left = 318
    Top = 257
  end
  object WVDownMaxMoney: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sdate0'
      end
      item
        Name = '��������޶�'
        Caption = '��������޶�'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol4'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
        MonitorValueChangedFields = '|�豸��־|������Կ|'
      end>
    Left = 284
    Top = 257
  end
  object WVRCollectConsumeSer: TWVRequest
    WorkView = WVCollectConsumeSer
    ID = '�ɼ���ʷ������ˮ'
    Bindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '������ʼ��ˮ��'
        FieldName = '������ʼ��ˮ��'
      end
      item
        ParamName = '����������ˮ��'
        FieldName = '����������ˮ��'
      end
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
        ParamName = '�豸���'
        FieldName = '�豸���'
      end>
    Left = 400
    Top = 184
  end
  object WVCollectConsumeSer: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate0'
      end
      item
        Name = '������ʼ��ˮ��'
        Caption = '������ʼ��ˮ��'
        FieldType = wftUndefined
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '����������ˮ��'
        Caption = '����������ˮ��'
        FieldType = wftUndefined
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
        GroupIndex = 1
        DataField = 'lvol6'
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
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 368
    Top = 184
  end
  object WVRCollectAddMoneySer: TWVRequest
    WorkView = WVCollectAddMoneySer
    ID = '�ɼ��ֽ��ֵ��ˮ'
    Bindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '������ʼ��ˮ��'
        FieldName = '������ʼ��ˮ��'
      end
      item
        ParamName = '����������ˮ��'
        FieldName = '����������ˮ��'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end>
    Left = 400
    Top = 216
  end
  object WVCollectAddMoneySer: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate0'
      end
      item
        Name = '������ʼ��ˮ��'
        Caption = '������ʼ��ˮ��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '����������ˮ��'
        Caption = '����������ˮ��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol6'
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
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 366
    Top = 216
  end
  object QueryRequestCustomerKindByKey: TWVRequest
    WorkView = WorkViewCustomerKindByKey
    ID = 'querycustomerkind'
    Bindings = <
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
      end
      item
        ParamName = 'lcert_code'
        FieldName = 'lcert_code'
      end>
    Left = 544
    Top = 112
  end
  object WorkViewCustomerKindByKey: TWorkView
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
        GroupIndex = 1
        DataField = 'vsmess'
      end
      item
        Name = 'lcert_code'
        Caption = 'lcert_code'
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
        MonitorValueChangedFields = '|��ѯ.�ͻ�������|'
      end
      item
        MonitorValueChangedFields = 
          '|�ͻ��������|�Ƿ񽻴���|���ѷ���|��ʽ����Ч��|Ѻ����|����' +
          '����|�������|��һ���Ƿ���ȡ���ɱ���|�Ƿ��˿��ɱ���|�˻�������' +
          '|'
      end>
    Left = 504
    Top = 112
  end
  object WorkViewEquGroup: TWorkView
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '����Ȩ��'
        Caption = '����Ȩ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'vsvarstr0'
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 364
    Top = 249
  end
  object WVRequestEquGroup: TWVRequest
    WorkView = WorkViewEquGroup
    ID = 'EquGroup'
    Bindings = <
      item
        ParamName = '����Ȩ��'
        FieldName = '����Ȩ��'
      end
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
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end>
    Left = 396
    Top = 249
  end
  object WorkViewQueryEquByKey: TWorkView
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
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�豸��־|������Կ|'
      end>
    Left = 508
    Top = 151
  end
  object WVRequestQueryEquByKey: TWVRequest
    WorkView = WorkViewQueryEquByKey
    ID = '�豸�ؼ��ֲ�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end>
    AfterExec = MainRequestAfterExec
    Left = 544
    Top = 152
  end
  object WVRSetHisSumMoney: TWVRequest
    WorkView = WVSetHisSumMoney
    ID = '���������ۼ��޶�'
    Bindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '�ۼ������޶�'
        FieldName = '�ۼ������޶�'
      end
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
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end>
    Left = 544
    Top = 192
  end
  object WVSetHisSumMoney: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate0'
      end
      item
        Name = '�ۼ������޶�'
        Caption = '�ۼ������޶�'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol4'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 512
    Top = 192
  end
  object WVGateOpen: TWorkView
    WorkFields = <
      item
        Name = '�ն��豸ID'
        Caption = '�ն��豸ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate0'
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
      end
      item
        Name = '��־'
        Caption = '��־'
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
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 516
    Top = 257
  end
  object WVRGateOpen: TWVRequest
    WorkView = WVGateOpen
    ID = '�Ž���������'
    Bindings = <
      item
        ParamName = '�ն��豸ID'
        FieldName = '�ն��豸ID'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end>
    Left = 548
    Top = 257
  end
  object wvSetFeeType: TWorkView
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
        Name = '��־'
        Caption = '��־'
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
        Name = '�豸���'
        Caption = '�豸���'
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
    Left = 516
    Top = 225
  end
  object wvrSetFeeType: TWVRequest
    WorkView = wvSetFeeType
    ID = '�´���������'
    Bindings = <
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end>
    Left = 548
    Top = 225
  end
  object wvrDictQ: TWVRequest
    WorkView = wvDictQ
    ID = '��ȡ�����ֵ�'
    Bindings = <
      item
        ParamName = '���ݼ�'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�����ֵ���Ŀ'
        FieldName = '�����ֵ���Ŀ'
      end>
    AfterExec = MainRequestAfterExec
    Left = 624
    Top = 112
  end
  object wvDictQ: TWorkView
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
        Name = '�����ֵ���Ŀ'
        Caption = '�����ֵ���Ŀ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�豸��־|������Կ|'
      end>
    Left = 588
    Top = 112
  end
end

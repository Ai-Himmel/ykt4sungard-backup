inherited faqhallotCustGate: TfaqhallotCustGate
  Width = 752
  Height = 543
  inherited UIPanel1: TUIPanel
    Top = 507
    Width = 752
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 87
      TabOrder = 1
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 6
      TabOrder = 0
      Visible = False
    end
    object btnPre: TBitBtn
      Left = 399
      Top = 5
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '��һ��'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnPreClick
    end
    object btnNext: TBitBtn
      Left = 487
      Top = 5
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '��һ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnNextClick
    end
    object btnFinish: TBitBtn
      Left = 575
      Top = 5
      Width = 75
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '�� ��'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnFinishClick
    end
    object btnInit: TBitBtn
      Left = 663
      Top = 5
      Width = 75
      Height = 25
      Hint = '���ص���Աѡ�����'
      Anchors = [akTop, akRight]
      Caption = '��ʼ��'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnInitClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 752
    inherited Image1: TImage
      Width = 752
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 752
    Height = 489
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object rzpc1: TRzPageControl
      Left = 0
      Top = 0
      Width = 752
      Height = 489
      ActivePage = rztsCust
      Align = alClient
      Color = 16119543
      FlatColor = 10263441
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      ParentColor = False
      TabColors.HighlightBar = 3983359
      TabIndex = 0
      TabOrder = 0
      TabStyle = tsCutCorner
      FixedDimension = 19
      object rztsCust: TRzTabSheet
        Color = 16119543
        Caption = '��Աѡ��'
        object pnl1: TPanel
          Left = 422
          Top = 0
          Width = 326
          Height = 466
          Align = alClient
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 1
          object lvCust: TRzListView
            Left = 0
            Top = 41
            Width = 326
            Height = 394
            Align = alClient
            Columns = <
              item
                Caption = '�ͻ���'
                Width = 60
              end
              item
                Caption = 'ѧ����'
                Width = 100
              end
              item
                Caption = '�ͻ�����'
                Width = 80
              end
              item
                Caption = '����У��'
                Width = 65
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            MultiSelect = True
            RowSelect = True
            SmallImages = il1
            TabOrder = 1
            ViewStyle = vsReport
          end
          object pnl3: TPanel
            Left = 0
            Top = 0
            Width = 326
            Height = 41
            Align = alTop
            BevelOuter = bvNone
            Caption = '��ѡ�����Ա�б�'
            Color = 16119543
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object Panel6: TPanel
            Left = 0
            Top = 435
            Width = 326
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object SpeedButton2: TSpeedButton
              Left = 2
              Top = 5
              Width = 60
              Height = 22
              Caption = '<-ɾ��'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton2Click
            end
            object SpeedButton11: TSpeedButton
              Left = 70
              Top = 5
              Width = 68
              Height = 22
              Caption = '����б�'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton11Click
            end
          end
        end
        object rzszpnl2: TRzSizePanel
          Left = 0
          Top = 0
          Width = 422
          Height = 466
          Color = 16119543
          HotSpotSizePercent = 100
          HotSpotVisible = True
          SizeBarWidth = 7
          TabOrder = 0
          UseGradients = True
          object lvCustUnAllot: TRzListView
            Left = 0
            Top = 95
            Width = 414
            Height = 315
            Align = alClient
            Checkboxes = True
            Columns = <
              item
                Caption = '�ͻ���'
                Width = 60
              end
              item
                Caption = 'ѧ����'
                Width = 100
              end
              item
                Caption = '�ͻ�����'
                Width = 80
              end
              item
                Caption = '����У��'
                Width = 153
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            TabOrder = 1
            ViewStyle = vsReport
          end
          object pnl2: TPanel
            Left = 0
            Top = 0
            Width = 414
            Height = 95
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label6: TLabel
              Left = 212
              Top = 51
              Width = 48
              Height = 12
              Caption = '���ڲ���'
            end
            object Label3: TLabel
              Left = 12
              Top = 73
              Width = 48
              Height = 12
              Caption = '��������'
            end
            object Label10: TLabel
              Left = 212
              Top = 29
              Width = 48
              Height = 12
              Caption = '���֤��'
            end
            object Label5: TLabel
              Left = 24
              Top = 51
              Width = 36
              Height = 12
              Caption = 'ѧ����'
            end
            object Label1: TLabel
              Left = 12
              Top = 29
              Width = 48
              Height = 12
              Caption = '�ͻ����'
            end
            object WVLabel2: TWVLabel
              Left = 24
              Top = 7
              Width = 36
              Height = 12
              Caption = '�ͻ���'
            end
            object Label4: TLabel
              Left = 212
              Top = 7
              Width = 48
              Height = 12
              Caption = '�ͻ�����'
            end
            object WVComboBox6: TWVComboBox
              Tag = 1
              Left = 264
              Top = 46
              Width = 142
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 12
              TabOrder = 5
              WorkView = WorkView1
              FieldName = '��ϵ�˵�λ��'
              DataPresentType = 'IDOBJECTS'
              SeperatedStr = '-'
              AutoDropDown = False
              ItemsDataEntry = '*-22'
            end
            object WVComboBox3: TWVComboBox
              Tag = 1
              Left = 64
              Top = 68
              Width = 142
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 12
              TabOrder = 7
              WorkView = WorkView1
              FieldName = '�ͻ���������'
              DataPresentType = 'IDOBJECTS'
              SeperatedStr = '-'
              AutoDropDown = False
              ItemsDataEntry = '*-27'
            end
            object WVEdit10: TWVEdit
              Tag = 1
              Left = 264
              Top = 24
              Width = 142
              Height = 20
              Color = clWhite
              ReadOnly = False
              TabOrder = 3
              Text = '<��ϵ�����֤��>'
              WorkView = WorkView1
              FieldName = '��ϵ�����֤��'
            end
            object WVEdit5: TWVEdit
              Tag = 1
              Left = 64
              Top = 46
              Width = 141
              Height = 20
              CharCase = ecUpperCase
              Color = clWhite
              ReadOnly = False
              TabOrder = 4
              Text = '<��ϵ��ѧ����>'
              WorkView = WorkView1
              FieldName = '��ϵ��ѧ����'
            end
            object WVComboBox1: TWVComboBox
              Tag = 1
              Left = 64
              Top = 24
              Width = 142
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 12
              TabOrder = 2
              WorkView = WorkView1
              FieldName = '�ͻ����'
              DataPresentType = 'IDOBJECTS'
              SeperatedStr = '-'
              AutoDropDown = False
              ItemsDataEntry = '*-34'
            end
            object edtCustNo: TWVEdit
              Left = 64
              Top = 2
              Width = 142
              Height = 20
              Color = clWhite
              MaxLength = 22
              ReadOnly = False
              TabOrder = 0
              Text = '<�ͻ���>'
              WorkView = WorkView1
              FieldName = '�ͻ���'
            end
            object WVEdit4: TWVEdit
              Tag = 1
              Left = 264
              Top = 2
              Width = 142
              Height = 20
              Color = clWhite
              ReadOnly = False
              TabOrder = 1
              Text = '<�ͻ�����>'
              WorkView = WorkView1
              FieldName = '�ͻ�����'
            end
            object btnCustQuery: TBitBtn
              Left = 330
              Top = 66
              Width = 75
              Height = 25
              Hint = 'ȷ�ϲ���'
              Caption = '�ͻ���ѯ'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              TabOrder = 6
              OnClick = btnCustQueryClick
            end
          end
          object Panel3: TPanel
            Left = 0
            Top = 410
            Width = 414
            Height = 56
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 3
            object btnSelect: TSpeedButton
              Left = 353
              Top = 29
              Width = 60
              Height = 22
              Anchors = [akTop, akRight]
              Caption = 'ѡ��->'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = btnSelectClick
            end
            object SpeedButton8: TSpeedButton
              Left = 282
              Top = 29
              Width = 68
              Height = 22
              Anchors = [akTop, akRight]
              Caption = '����б�'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton8Click
            end
            object SpeedButton9: TSpeedButton
              Left = 8
              Top = 29
              Width = 68
              Height = 22
              Caption = 'ѡ���ļ�'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton9Click
            end
            object btnImportQuery: TSpeedButton
              Left = 202
              Top = 29
              Width = 68
              Height = 22
              Caption = '�����ѯ'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = btnImportQueryClick
            end
            object lbl1: TLabel
              Left = 80
              Top = 34
              Width = 42
              Height = 14
              Caption = '����'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object SpeedButton1: TSpeedButton
              Left = 82
              Top = 4
              Width = 71
              Height = 22
              Anchors = [akTop, akRight]
              Caption = 'ʧ����Ϣ'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton1Click
            end
            object edtSheet: TEdit
              Left = 117
              Top = 30
              Width = 81
              Height = 22
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
              Text = 'sheet1'
            end
            object chkCustUnAllot: TRzCheckBox
              Left = 13
              Top = 7
              Width = 57
              Height = 17
              Caption = 'ȫѡ'
              FrameColor = 8409372
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              HighlightColor = 2203937
              HotTrack = True
              HotTrackColor = 3983359
              HotTrackColorType = htctActual
              ParentFont = False
              State = cbUnchecked
              TabOrder = 0
              OnClick = chkCustUnAllotClick
            end
          end
          object pnlImportError: TPanel
            Left = 146
            Top = 203
            Width = 271
            Height = 233
            Anchors = [akLeft, akBottom]
            Color = 16119543
            TabOrder = 2
            Visible = False
            object SpeedButton3: TSpeedButton
              Left = 202
              Top = 204
              Width = 64
              Height = 22
              Anchors = [akTop, akRight]
              Caption = '�� ��'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = SpeedButton3Click
            end
            object mmoImportError: TRzMemo
              Left = 1
              Top = 1
              Width = 269
              Height = 192
              Align = alTop
              ScrollBars = ssBoth
              TabOrder = 0
            end
          end
        end
      end
      object rztsGateGroup: TRzTabSheet
        Color = 16119543
        Caption = '�Ž���ѡ��'
        object pnl4: TPanel
          Left = 0
          Top = 0
          Width = 748
          Height = 466
          Align = alClient
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 0
          object Panel9: TPanel
            Left = 0
            Top = 0
            Width = 748
            Height = 65
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label8: TLabel
              Left = 6
              Top = 18
              Width = 60
              Height = 12
              Caption = '�Ž�������'
            end
            object Label22: TLabel
              Left = 6
              Top = 43
              Width = 364
              Height = 14
              Caption = '˵��������˴���ѡ���Ž��飬����һ��һ��Ҫѡ���Ž���'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object WVEdit9: TWVEdit
              Left = 69
              Top = 14
              Width = 124
              Height = 20
              Color = clInfoBk
              MaxLength = 9
              ReadOnly = False
              TabOrder = 1
              Text = '<��ѯ.�Ž�������>'
              WorkView = WorkView3
              FieldName = '��ѯ.�Ž�������'
            end
            object btnGroupQuery: TBitBtn
              Left = 206
              Top = 11
              Width = 75
              Height = 25
              Hint = 'ȷ�ϲ���'
              Caption = '���ѯ'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = btnGroupQueryClick
            end
          end
          object lvGateGroup: TRzListView
            Left = 0
            Top = 65
            Width = 748
            Height = 370
            Align = alClient
            Checkboxes = True
            Columns = <
              item
                Caption = '�Ž�����'
                Width = 80
              end
              item
                Caption = '�Ž�������'
                Width = 647
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            TabOrder = 1
            ViewStyle = vsReport
          end
          object Panel18: TPanel
            Left = 0
            Top = 435
            Width = 748
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object chkGateGroup: TRzCheckBox
              Left = 5
              Top = 7
              Width = 57
              Height = 17
              Caption = 'ȫѡ'
              FrameColor = 8409372
              HighlightColor = 2203937
              HotTrack = True
              HotTrackColor = 3983359
              HotTrackColorType = htctActual
              State = cbUnchecked
              TabOrder = 0
              OnClick = chkGateGroupClick
            end
          end
        end
      end
      object rztsGate: TRzTabSheet
        Color = 16119543
        Caption = '�Ž���ѡ��'
        object Panel7: TPanel
          Left = 0
          Top = 0
          Width = 748
          Height = 466
          Align = alClient
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 0
          object Panel11: TPanel
            Left = 0
            Top = 0
            Width = 748
            Height = 81
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label7: TLabel
              Left = 74
              Top = 9
              Width = 48
              Height = 12
              Caption = '�豸����'
            end
            object Label11: TLabel
              Left = 74
              Top = 56
              Width = 48
              Height = 12
              Caption = '�豸״̬'
              Visible = False
            end
            object Label12: TLabel
              Left = 86
              Top = 34
              Width = 36
              Height = 12
              Caption = '��ϵͳ'
            end
            object Label14: TLabel
              Left = 458
              Top = 31
              Width = 72
              Height = 12
              Caption = '�豸��������'
            end
            object Label15: TLabel
              Left = 242
              Top = 32
              Width = 72
              Height = 12
              Caption = '�豸�����ͺ�'
            end
            object Label16: TLabel
              Left = 482
              Top = 8
              Width = 48
              Height = 12
              Caption = '�豸����'
            end
            object Label18: TLabel
              Left = 254
              Top = 9
              Width = 60
              Height = 12
              Caption = '�豸����ID'
            end
            object Label21: TLabel
              Left = 246
              Top = 54
              Width = 308
              Height = 14
              Caption = '˵��������Ѿ�ѡ�����Ž��飬�Ž������Բ�ѡ��'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object WVEdit3: TWVEdit
              Left = 124
              Top = 5
              Width = 112
              Height = 20
              Color = clWhite
              ReadOnly = False
              TabOrder = 1
              Text = '<�豸����>'
              WorkView = WorkView2
              FieldName = '�豸����'
            end
            object WVComboBox5: TWVComboBox
              Left = 124
              Top = 52
              Width = 112
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 7
              Text = '<�豸״̬>'
              Visible = False
              WorkView = WorkView2
              FieldName = '�豸״̬'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*5'
            end
            object WVComboBox7: TWVComboBox
              Left = 124
              Top = 28
              Width = 112
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 4
              Text = '<������ϵͳ>'
              WorkView = WorkView2
              FieldName = '������ϵͳ'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*-32'
            end
            object cbbScode: TWVComboBox
              Left = 532
              Top = 4
              Width = 132
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 0
              Text = '<���ʹ���>'
              WorkView = WorkView2
              FieldName = '���ʹ���'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*47'
            end
            object WVComboBox8: TWVComboBox
              Left = 316
              Top = 28
              Width = 132
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 5
              Text = '<�豸�����ͺ�>'
              WorkView = WorkView2
              FieldName = '�豸�����ͺ�'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*-35'
            end
            object WVComboBox9: TWVComboBox
              Left = 532
              Top = 27
              Width = 132
              Height = 20
              Style = csDropDownList
              Color = clWhite
              ItemHeight = 0
              TabOrder = 3
              Text = '<�豸��������>'
              WorkView = WorkView2
              FieldName = '�豸��������'
              DataPresentType = 'IDOBJECTS'
              AutoDropDown = False
              ItemsDataEntry = '*-28'
            end
            object WVEdit6: TWVEdit
              Left = 316
              Top = 5
              Width = 130
              Height = 20
              Color = clWhite
              ReadOnly = False
              TabOrder = 2
              Text = '<�豸����ID>'
              WorkView = WorkView2
              FieldName = '�豸����ID'
            end
            object btnEquQuery: TBitBtn
              Left = 588
              Top = 49
              Width = 75
              Height = 25
              Hint = 'ȷ�ϲ���'
              Caption = '�豸��ѯ'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              TabOrder = 6
              OnClick = btnEquQueryClick
            end
          end
          object Panel12: TPanel
            Left = 0
            Top = 435
            Width = 748
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object chkGateUnAllot: TRzCheckBox
              Left = 5
              Top = 7
              Width = 57
              Height = 17
              Caption = 'ȫѡ'
              FrameColor = 8409372
              HighlightColor = 2203937
              HotTrack = True
              HotTrackColor = 3983359
              HotTrackColorType = htctActual
              State = cbUnchecked
              TabOrder = 0
              OnClick = chkGateUnAllotClick
            end
          end
          object lvGate: TRzListView
            Left = 0
            Top = 81
            Width = 748
            Height = 354
            Align = alClient
            Checkboxes = True
            Columns = <
              item
                Caption = '�Ž������'
                Width = 80
              end
              item
                Caption = '�Ž�������'
                Width = 647
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            TabOrder = 1
            ViewStyle = vsReport
          end
        end
      end
      object rztsHoliday: TRzTabSheet
        Color = 16119543
        Caption = '�ڼ���/��ѡ��'
        object rzszpnl1: TRzSizePanel
          Left = 0
          Top = 0
          Width = 354
          Height = 466
          Color = 16119543
          HotSpotSizePercent = 100
          HotSpotVisible = True
          SizeBarWidth = 7
          TabOrder = 0
          UseGradients = True
          object Panel14: TPanel
            Left = 0
            Top = 0
            Width = 346
            Height = 65
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label17: TLabel
              Left = 6
              Top = 18
              Width = 60
              Height = 12
              Caption = '�ڼ�������'
            end
            object Label9: TLabel
              Left = 6
              Top = 42
              Width = 252
              Height = 14
              Caption = '˵�����ڼ���Ϊ��ѡ����ѡϵͳĬ��Ϊ��'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object WVEdit7: TWVEdit
              Left = 69
              Top = 14
              Width = 124
              Height = 20
              Color = clInfoBk
              MaxLength = 9
              ReadOnly = False
              TabOrder = 1
              Text = '<��ѯ.�ڼ�����>'
              WorkView = WorkView4
              FieldName = '��ѯ.�ڼ�����'
            end
            object btnHolidayQuery: TBitBtn
              Left = 216
              Top = 10
              Width = 90
              Height = 25
              Hint = 'ȷ�ϲ���'
              Caption = '�ڼ��ղ�ѯ'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = btnHolidayQueryClick
            end
          end
          object lvHoliday: TRzListView
            Left = 0
            Top = 65
            Width = 346
            Height = 370
            Align = alClient
            Columns = <
              item
                Caption = '�ڼ��ձ��'
                Width = 80
              end
              item
                Caption = '�ڼ�������'
                Width = 245
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            SmallImages = il1
            TabOrder = 1
            ViewStyle = vsReport
            OnChange = lvHolidayChange
          end
          object Panel15: TPanel
            Left = 0
            Top = 435
            Width = 346
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object Label20: TLabel
              Left = 6
              Top = 10
              Width = 103
              Height = 14
              AutoSize = False
              Caption = '��ǰѡ��ڼ��գ�'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object lblHolidayID: TLabel
              Left = 110
              Top = 9
              Width = 35
              Height = 14
              AutoSize = False
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object lblHolidayName: TLabel
              Left = 150
              Top = 9
              Width = 7
              Height = 14
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object btnClearSele: TSpeedButton
              Left = 272
              Top = 5
              Width = 68
              Height = 22
              Caption = '���ѡ��'
              Flat = True
              Font.Charset = GB2312_CHARSET
              Font.Color = clNavy
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              OnClick = btnClearSeleClick
            end
          end
        end
        object pnl5: TPanel
          Left = 354
          Top = 0
          Width = 394
          Height = 466
          Align = alClient
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 1
          object Panel16: TPanel
            Left = 0
            Top = 0
            Width = 394
            Height = 65
            Align = alTop
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 0
            object Label19: TLabel
              Left = 6
              Top = 18
              Width = 72
              Height = 12
              Caption = '��ʱ�������'
            end
            object Label13: TLabel
              Left = 6
              Top = 42
              Width = 322
              Height = 14
              Caption = '˵������ʱ��α���ѡ�񣬲�ѡ���ܷ�����Ա����'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object WVEdit8: TWVEdit
              Left = 85
              Top = 14
              Width = 124
              Height = 20
              Color = clInfoBk
              MaxLength = 9
              ReadOnly = False
              TabOrder = 1
              Text = '<��ѯ.ʱ���������>'
              WorkView = WorkView5
              FieldName = '��ѯ.ʱ���������'
            end
            object btnWeekQuery: TBitBtn
              Left = 239
              Top = 11
              Width = 75
              Height = 25
              Hint = 'ȷ�ϲ���'
              Caption = '�ܲ�ѯ'
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = btnWeekQueryClick
            end
          end
          object lvWeek: TRzListView
            Left = 0
            Top = 65
            Width = 394
            Height = 370
            Align = alClient
            Columns = <
              item
                Caption = '��ʱ��α��'
                Width = 100
              end
              item
                Caption = '��ʱ�������'
                Width = 273
              end>
            ColumnClick = False
            FlatScrollBars = True
            GridLines = True
            RowSelect = True
            SmallImages = il1
            TabOrder = 1
            ViewStyle = vsReport
            OnChange = lvWeekChange
          end
          object Panel17: TPanel
            Left = 0
            Top = 435
            Width = 394
            Height = 31
            Align = alBottom
            BevelOuter = bvNone
            Color = 16119543
            TabOrder = 2
            object lblWeekName: TLabel
              Left = 150
              Top = 9
              Width = 7
              Height = 14
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object lblWeekId: TLabel
              Left = 112
              Top = 9
              Width = 31
              Height = 14
              AutoSize = False
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
            object Label23: TLabel
              Left = 6
              Top = 10
              Width = 103
              Height = 14
              AutoSize = False
              Caption = '��ǰѡ����ʱ�䣺'
              Font.Charset = GB2312_CHARSET
              Font.Color = clMaroon
              Font.Height = -14
              Font.Name = '����'
              Font.Style = []
              ParentFont = False
            end
          end
        end
      end
      object rztsOk: TRzTabSheet
        Color = 16119543
        Caption = '������Ϣ'
        object pnl6: TPanel
          Left = 0
          Top = 427
          Width = 748
          Height = 39
          Align = alBottom
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 1
          object btnClear: TSpeedButton
            Left = 600
            Top = 8
            Width = 68
            Height = 22
            Anchors = [akTop, akRight]
            Caption = '�����Ϣ'
            Flat = True
            Font.Charset = GB2312_CHARSET
            Font.Color = clNavy
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            OnClick = btnClearClick
          end
          object btnSaveAs: TSpeedButton
            Left = 672
            Top = 8
            Width = 68
            Height = 22
            Anchors = [akTop, akRight]
            Caption = '��Ϣ���'
            Flat = True
            Font.Charset = GB2312_CHARSET
            Font.Color = clNavy
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            OnClick = btnSaveAsClick
          end
        end
        object mmoError: TRzMemo
          Left = 0
          Top = 0
          Width = 748
          Height = 427
          Align = alClient
          ReadOnly = True
          ScrollBars = ssBoth
          TabOrder = 0
          WordWrap = False
        end
      end
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 696
    Top = 480
    Width = 56
    Height = 27
    Align = alNone
    TabOrder = 2
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = 'ʱ�������'
          Visible = True
        end>
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
      end
      item
        Name = '���ر�־'
        Caption = '���ر�־'
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
        Name = '��ʱ���'
        Caption = '��ʱ���'
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
        Name = '�ڼ���'
        Caption = '�ڼ���'
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
        Name = '�Ž����'
        Caption = '�Ž����'
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
        Name = '��־'
        Caption = '��־'
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
        MonitorValueChangedFields = '|ʱ�������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 4
    Top = 415
  end
  inherited MainRequest: TWVRequest
    ID = '�Ž���Ա��������'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '���ر�־'
        FieldName = '���ر�־'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '�ڼ���'
        FieldName = '�ڼ���'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�Ž����'
        FieldName = '�Ž����'
      end
      item
        ParamName = '��ʱ���'
        FieldName = '��ʱ���'
      end>
    Left = 40
    Top = 416
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 72
    Top = 416
  end
  inherited DataSource: TDataSource
    Left = 104
    Top = 416
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�豸��ѯ�Ž�ϵͳ'
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
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    Left = 40
    Top = 256
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
        Name = '�豸����'
        Caption = '�豸����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '�����豸ע���'
        Caption = '�����豸ע���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd'
      end
      item
        Name = '�豸����ID'
        Caption = '�豸����ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sbank_pwd2'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '�ϼ��豸����ID'
        Caption = '�ϼ��豸����ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '�豸״̬'
        Caption = '�豸״̬'
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
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '�豸��������'
        Caption = '�豸��������'
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
        Name = '������Ա����'
        Caption = '������Ա����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sname2'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 4
    Top = 255
  end
  object WVRequest3: TWVRequest
    WorkView = WorkView3
    ID = '�Ž������Ա��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�Ž�����'
        FieldName = '��ѯ.�Ž�����'
      end
      item
        ParamName = '�Ž�������'
        FieldName = '��ѯ.�Ž�������'
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
    Left = 40
    Top = 296
  end
  object WorkView3: TWorkView
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
        Name = '��ѯ.�Ž�����'
        Caption = '��ѯ.�Ž�����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�Ž�������'
        Caption = '��ѯ.�Ž�������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�Ž�����|��ѯ.�Ž�������|��ѯ.��������|'
      end
      item
        MonitorValueChangedFields = '|�Ž�����|'
      end>
    Left = 8
    Top = 296
  end
  object WVRequest4: TWVRequest
    WorkView = WorkView4
    ID = '�ڼ��ղ�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ڼ��ձ��'
        FieldName = '��ѯ.�ڼ��ձ��'
      end
      item
        ParamName = '�ڼ�����'
        FieldName = '��ѯ.�ڼ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
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
    Left = 40
    Top = 336
  end
  object WorkView4: TWorkView
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
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end
      item
        Name = '�������.ɾ��'
        Caption = '�������.ɾ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '�������.�޸�'
        Caption = '�������.�޸�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '��ѯ.�ڼ��ձ��'
        Caption = '��ѯ.�ڼ��ձ��'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�ڼ�����'
        Caption = '��ѯ.�ڼ�����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�ڼ��ձ��'
        Caption = '�ڼ��ձ��'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '�ڼ�����'
        Caption = '�ڼ�����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'semail'
      end
      item
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.�ڼ��ձ��|��ѯ.�ڼ�����|��ѯ.��������|'
      end
      item
        MonitorValueChangedFields = '|�ڼ��ձ��|'
      end>
    Left = 8
    Top = 336
  end
  object WVRequest5: TWVRequest
    WorkView = WorkView5
    ID = '��ʱ��β�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʱ�������'
        FieldName = '��ѯ.ʱ�������'
      end
      item
        ParamName = 'ʱ���������'
        FieldName = '��ѯ.ʱ���������'
      end
      item
        ParamName = '��һ����'
        FieldName = '��ѯ.��һ����'
      end
      item
        ParamName = '�ܶ�����'
        FieldName = '��ѯ.�ܶ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
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
      end>
    Left = 40
    Top = 368
  end
  object WorkView5: TWorkView
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
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end
      item
        Name = '�������.ɾ��'
        Caption = '�������.ɾ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '�������.�޸�'
        Caption = '�������.�޸�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '��ѯ.ʱ�������'
        Caption = '��ѯ.ʱ�������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.ʱ���������'
        Caption = '��ѯ.ʱ���������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��һ����'
        Caption = '��ѯ.��һ����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�ܶ�����'
        Caption = '��ѯ.�ܶ�����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        GroupIndex = 1
        DataField = 'semail'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        Name = '��һ����'
        Caption = '��һ����'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '�ܶ�����'
        Caption = '�ܶ�����'
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
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        GroupIndex = 1
        DataField = 'lvol6'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        GroupIndex = 1
        DataField = 'lvol7'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.ʱ�������|��ѯ.ʱ���������|��ѯ.��һ����|��ѯ.�ܶ���' +
          '���|��ѯ.��������|��ѯ.��������|��ѯ.��������|��ѯ.������' +
          '���|��ѯ.��������|��ѯ.��־|'
      end
      item
        MonitorValueChangedFields = 
          '|ʱ�������|ʱ�������|��־|��һ����|�ܶ�����|��������|' +
          '��������|��������|��������|��������|'
      end>
    Left = 8
    Top = 368
  end
  object dlgOpen: TOpenDialog
    Left = 232
    Top = 416
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 192
    Top = 416
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\����\�½� Microsoft Office Access Ӧ�ó���.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 152
    Top = 416
  end
  object dlgSaveError: TSaveDialog
    Filter = '�ı��ļ�|*.txt'
    Left = 281
    Top = 415
  end
  object il1: TImageList
    Left = 129
    Top = 359
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�ͻ���Ϣ��ѯ'
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
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�ͻ�״̬'
        FieldName = '�ͻ�״̬'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = '�ͻ���������'
      end
      item
        ParamName = '��ϵ��ѧ����'
        FieldName = '��ϵ��ѧ����'
      end
      item
        ParamName = '��ϵ�˵�λ��'
        FieldName = '��ϵ�˵�λ��'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = '��ϵ���Ա�'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = '��ϵ�����֤��'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    AfterExec = MainRequestAfterExec
    Left = 40
    Top = 216
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = True
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '�ͻ�״̬'
        Caption = '�ͻ�״̬'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '�ͻ����'
        Caption = '�ͻ����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ�˵�λ��'
        Caption = '��ϵ�˵�λ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ���Ա�'
        Caption = '��ϵ���Ա�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ��ѧ����'
        Caption = '��ϵ��ѧ����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ������'
        Caption = '��ϵ������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ�����֤��'
        Caption = '��ϵ�����֤��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
      end
      item
        Name = '�ͻ���������'
        Caption = '�ͻ���������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '���κ�'
        Caption = '���κ�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '�༶'
        Caption = '�༶'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�ͻ����|�ͻ�״̬|����|�ͻ�����|��ϵ��ѧ�Ż�Ա����|��ϵ�˰༶��' +
          '����|��ϵ������|��ϵ���Ա�|��ϵ���������|��ϵ�����֤��|��ϵ��' +
          '��|��ϵ��ַ|ע��ʱ��|Ԥ��ע��ʱ��|'
      end>
    Left = 4
    Top = 215
  end
end

inherited faqhSetEquipmentInfo: TfaqhSetEquipmentInfo
  Width = 745
  Height = 435
  Caption = '�豸��Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 745
    Height = 435
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 382
        Width = 741
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 488
        end
        inherited btnChange: TBitBtn [1]
          Left = 574
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 402
        end
        inherited btnDelete: TBitBtn
          Left = 660
          Caption = '&D ע��'
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 741
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 741
        Height = 285
        Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
        ReadOnly = True
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lserial1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 77
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸��ʶ'
            Width = 61
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 142
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����ID'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '�豸����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������˿�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt6'
            PickList.Strings = ()
            Title.Caption = '�ϼ��豸'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scurrency_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ƭ�ṹ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������˿ں�'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸״̬'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ͨѶ�˿ں�'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 98
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstation0'
            PickList.Strings = ()
            Title.Caption = 'IP��ַ'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������ϵͳ'
            Width = 81
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ע'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'damt5'
            PickList.Strings = ()
            Title.Caption = '�豸��;'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt4'
            PickList.Strings = ()
            Title.Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = 'ͨѶ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������κ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ע'
            Width = 120
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 741
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 58
          Top = 34
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label2: TLabel
          Left = 58
          Top = 10
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label3: TLabel
          Left = 538
          Top = 10
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label4: TLabel
          Left = 281
          Top = 10
          Width = 60
          Height = 12
          Caption = '������ϵͳ'
        end
        object WVLabel14: TWVLabel
          Left = 136
          Top = 74
          Width = 48
          Height = 12
          Caption = '�豸״̬'
          Visible = False
        end
        object Label5: TLabel
          Left = 346
          Top = 74
          Width = 48
          Height = 12
          Caption = '�շѷ�ʽ'
          Visible = False
        end
        object Label6: TLabel
          Left = 58
          Top = 58
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label7: TLabel
          Left = 281
          Top = 34
          Width = 60
          Height = 12
          Caption = '�豸����ID'
        end
        object Label8: TLabel
          Left = 257
          Top = 58
          Width = 84
          Height = 12
          Caption = '�ϼ��豸����ID'
        end
        object Label9: TLabel
          Left = 525
          Top = 34
          Width = 60
          Height = 12
          Caption = '�������κ�'
        end
        object Label10: TLabel
          Left = 536
          Top = 58
          Width = 48
          Height = 12
          Caption = '�豸��ʶ'
        end
        object WVComboBox18: TWVComboBox
          Left = 120
          Top = 6
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 0
          Text = '<��ѯ.���ʹ���>'
          WorkView = WorkView
          FieldName = '��ѯ.���ʹ���'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object WVComboBox1: TWVComboBox
          Left = 595
          Top = 6
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 2
          Text = '<��ѯ.�豸�����ͺ�>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸�����ͺ�'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-35'
        end
        object WVComboBox17: TWVComboBox
          Left = 351
          Top = 6
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 1
          Text = '<��ѯ.������ϵͳ>'
          WorkView = WorkView
          FieldName = '��ѯ.������ϵͳ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVComboBox20: TWVComboBox
          Left = 120
          Top = 30
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 3
          Text = '<��ѯ.��������>'
          WorkView = WorkView
          FieldName = '��ѯ.��������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-28'
        end
        object WVComboBox3: TWVComboBox
          Left = 200
          Top = 70
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 9
          Text = '<��ѯ.�豸״̬>'
          Visible = False
          WorkView = WorkView
          FieldName = '��ѯ.�豸״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*5'
        end
        object WVComboBox19: TWVComboBox
          Left = 404
          Top = 70
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 10
          Text = '<��ѯ.�豸�����ͺ�>'
          Visible = False
          WorkView = WorkView
          FieldName = '��ѯ.�豸�����ͺ�'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*53'
        end
        object WVEdit4: TWVEdit
          Left = 120
          Top = 54
          Width = 125
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 6
          Text = '<��ѯ.�豸����>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸����'
        end
        object WVEdit5: TWVEdit
          Left = 351
          Top = 30
          Width = 125
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 4
          Text = '<��ѯ.�豸����ID>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸����ID'
        end
        object WVEdit6: TWVEdit
          Left = 351
          Top = 54
          Width = 125
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 7
          Text = '<��ѯ.�ϼ��豸����ID>'
          WorkView = WorkView
          FieldName = '��ѯ.�ϼ��豸����ID'
        end
        object WVEdit2: TWVEdit
          Left = 595
          Top = 30
          Width = 125
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<��ѯ.�������κ�>'
          WorkView = WorkView
          FieldName = '��ѯ.�������κ�'
        end
        object WVEdit7: TWVEdit
          Left = 595
          Top = 54
          Width = 125
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 8
          Text = '<��ѯ.�豸��ʶ>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸��ʶ'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object WVLabel11: TWVLabel [0]
        Left = 572
        Top = 552
        Width = 36
        Height = 12
        Caption = '�����'
        Visible = False
      end
      object WVLabel29: TWVLabel [1]
        Left = 280
        Top = 544
        Width = 120
        Height = 12
        Caption = '�ն˻������û������'
        Visible = False
      end
      object WVLabel44: TWVLabel [2]
        Left = 112
        Top = 552
        Width = 48
        Height = 12
        Caption = '������Կ'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 376
        Width = 741
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 565
        end
        inherited btnCancel: TBitBtn
          Left = 653
          TabStop = True
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object RzPanel1: TRzPanel
        Left = 0
        Top = 33
        Width = 741
        Height = 343
        Align = alClient
        BorderOuter = fsNone
        Color = 16119543
        TabOrder = 1
        object WVLabel4: TWVLabel
          Left = 57
          Top = 36
          Width = 54
          Height = 12
          Caption = '�豸����*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel43: TWVLabel
          Left = 386
          Top = 110
          Width = 54
          Height = 12
          Caption = '��������*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblPhyNo: TWVLabel
          Left = 51
          Top = 110
          Width = 60
          Height = 12
          Caption = '�豸����ID'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblUEqu: TWVLabel
          Left = 57
          Top = 147
          Width = 54
          Height = 12
          Caption = '�ϼ��豸*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblSerPortNo: TWVLabel
          Left = 39
          Top = 182
          Width = 72
          Height = 12
          Caption = '�������˿ں�'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblSerPortNum: TWVLabel
          Left = 27
          Top = 256
          Width = 84
          Height = 12
          Caption = '�������˿�����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblMachineNo: TWVLabel
          Left = 391
          Top = 224
          Width = 48
          Height = 12
          Caption = '�豸����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel42: TWVLabel
          Left = 374
          Top = 147
          Width = 66
          Height = 12
          Caption = '������ϵͳ*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblMachineType: TWVLabel
          Left = 57
          Top = 73
          Width = 54
          Height = 12
          Caption = '�豸����*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lbl3: TWVLabel
          Left = 385
          Top = 73
          Width = 54
          Height = 12
          Caption = '�豸��;*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel40: TWVLabel
          Left = 385
          Top = 36
          Width = 54
          Height = 12
          Caption = '�豸����*'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel17: TWVLabel
          Left = 75
          Top = 218
          Width = 36
          Height = 12
          Caption = 'IP��ַ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel2: TWVLabel
          Left = 391
          Top = 261
          Width = 48
          Height = 12
          Caption = 'ͨѶ���'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblPort: TWVLabel
          Left = 51
          Top = 290
          Width = 60
          Height = 12
          Alignment = taRightJustify
          Caption = 'ͨѶ�˿ں�'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object btnOpen: TSpeedButton
          Left = 287
          Top = 145
          Width = 19
          Height = 19
          Flat = True
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            00009C310000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE6300009C310000FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300CE9C
            6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C63009C31
            0000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E7009C31
            0000CE630000CE630000CE630000CE6300009C310000FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE630000CE630000CE630000CE630000CE6300009C310000CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E7009C31
            0000CE630000CE630000CE630000CE6300009C310000FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E7009C31
            0000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009C31
            0000CE6300009C310000FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E7009C31
            00009C310000CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7E700E7E7
            E700FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300CE9C
            6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C
            6300CE9C6300CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
          OnClick = btnOpenClick
        end
        object btnClose: TSpeedButton
          Left = 288
          Top = 144
          Width = 19
          Height = 19
          Flat = True
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF009C3100009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF009C310000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF009C310000CE630000CE6300009C310000CE9C6300CE9C6300CE9C
            6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300FFFFFF00FFFF
            FF009C310000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF009C31
            0000CE630000CE630000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C63009C310000CE63
            0000CE630000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF009C31
            0000CE630000CE630000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
            FF009C310000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF009C310000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF009C310000CE6300009C310000FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C63009C3100009C310000E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00E7E7E700E7E7E700E7E7E700E7E7
            E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C
            6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300}
          Visible = False
          OnClick = btnCloseClick
        end
        object WVLabel3: TWVLabel
          Left = 391
          Top = 184
          Width = 48
          Height = 12
          Caption = '��Ƭ�ṹ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object WVLabel5: TWVLabel
          Left = 415
          Top = 290
          Width = 24
          Height = 12
          Alignment = taRightJustify
          Caption = '��ע'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object edtEquName: TWVEdit
          Left = 121
          Top = 33
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          ReadOnly = False
          TabOrder = 1
          Text = '<�豸����>'
          WorkView = WorkView
          FieldName = '�豸����'
        end
        object edtPhyNo: TWVEdit
          Left = 121
          Top = 106
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          MaxLength = 30
          ParentFont = False
          ReadOnly = False
          TabOrder = 4
          Text = '<�豸�����>'
          WorkView = WorkView
          FieldName = '�豸�����'
        end
        object edtSerPortNo: TWVEdit
          Left = 120
          Top = 177
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          MaxLength = 22
          ParentFont = False
          ReadOnly = False
          TabOrder = 10
          Text = '<�������˿ں�>'
          WorkView = WorkView
          FieldName = '�������˿ں�'
        end
        object edtSerPortNum: TWVEdit
          Left = 120
          Top = 252
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          MaxLength = 22
          ParentFont = False
          ReadOnly = False
          TabOrder = 14
          Text = '<�������˿�����>'
          WorkView = WorkView
          FieldName = '�������˿�����'
        end
        object edtMachineNo: TWVEdit
          Left = 449
          Top = 218
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          MaxLength = 22
          ParentFont = False
          ReadOnly = False
          TabOrder = 13
          Text = '<����>'
          WorkView = WorkView
          FieldName = '����'
        end
        object cbbChildSys: TWVComboBox
          Left = 448
          Top = 143
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 7
          WorkView = WorkView
          FieldName = '������ϵͳ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '-32'
        end
        object cbbMachineType: TWVComboBox
          Left = 121
          Top = 71
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 3
          WorkView = WorkView
          FieldName = '���ʹ���'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '47'
        end
        object cbbUseType: TWVComboBox
          Left = 448
          Top = 69
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 2
          WorkView = WorkView
          FieldName = '�豸��;'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '81'
        end
        object cbbEquPhyType: TWVComboBox
          Left = 448
          Top = 31
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 0
          WorkView = WorkView
          FieldName = '�豸�����ͺ�'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '-35'
        end
        object edtIP: TWVEdit
          Left = 121
          Top = 214
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          MaxLength = 15
          ParentFont = False
          ReadOnly = False
          TabOrder = 12
          Text = '<ͨ�ŵ�ַ>'
          WorkView = WorkView
          FieldName = 'ͨ�ŵ�ַ'
        end
        object cbbComm: TWVComboBox
          Left = 449
          Top = 257
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 15
          OnChange = cbbCommChange
          WorkView = WorkView
          FieldName = 'ͨѶ���'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*50'
        end
        object edtCommPortNo: TWVEdit
          Left = 120
          Top = 287
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          ReadOnly = False
          TabOrder = 16
          Text = '<ͨѶ�˿�>'
          WorkView = WorkView
          FieldName = 'ͨѶ�˿�'
        end
        object cbbArea: TWVComboBox
          Left = 448
          Top = 107
          Width = 188
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '�豸��������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '-28'
        end
        object edtUEqu: TWVEdit
          Left = 120
          Top = 144
          Width = 41
          Height = 20
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          MaxLength = 22
          ParentColor = True
          ParentFont = False
          ReadOnly = True
          TabOrder = 8
          Text = '<�ϼ��豸�����>'
          OnChange = edtUEquChange
          WorkView = WorkView
          FieldName = '�ϼ��豸�����'
        end
        object edtParName: TEdit
          Left = 160
          Top = 144
          Width = 129
          Height = 20
          Color = 16119543
          Enabled = False
          ReadOnly = True
          TabOrder = 9
        end
        object WVComboBox4: TWVComboBox
          Left = 449
          Top = 179
          Width = 188
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 11
          OnChange = cbbCommChange
          WorkView = WorkView
          FieldName = '��Ƭ�ṹ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*48'
        end
        object WVEdit3: TWVEdit
          Left = 448
          Top = 287
          Width = 188
          Height = 20
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          ReadOnly = False
          TabOrder = 17
          Text = '<��ע>'
          WorkView = WorkView
          FieldName = '��ע'
        end
        object TreeView1: TTreeView
          Left = 305
          Top = 142
          Width = 56
          Height = 123
          Indent = 19
          TabOrder = 6
          Visible = False
          OnDblClick = btnCloseClick
          OnExit = TreeView1Exit
        end
      end
      object pnl1: TRzPanel
        Left = 0
        Top = 0
        Width = 741
        Height = 33
        Align = alTop
        BorderInner = fsGroove
        BorderOuter = fsNone
        Color = 16119543
        TabOrder = 0
        object WVLabel1: TWVLabel
          Left = 53
          Top = 13
          Width = 48
          Height = 12
          Caption = '�豸��ʶ'
          Visible = False
        end
        object WVEdit1: TWVEdit
          Left = 120
          Top = 8
          Width = 125
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<�豸��ʶ>'
          Visible = False
          WorkView = WorkView
          FieldName = '�豸��ʶ'
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 419
    Top = 55
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Name = '��ѯ.�������κ�'
        Caption = '��ѯ.�������κ�'
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
        Name = '��ѯ.���ʹ���'
        Caption = '��ѯ.���ʹ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sbank_code'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lserial1'
      end
      item
        Name = '��ѯ.�豸�����ͺ�'
        Caption = '��ѯ.�豸�����ͺ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lbank_acc_type'
      end
      item
        Name = '��ѯ.������ϵͳ'
        Caption = '��ѯ.������ϵͳ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lserial0'
      end
      item
        Name = '��ѯ.�豸״̬'
        Caption = '��ѯ.�豸״̬'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '��ѯ.�շѷ�ʽ'
        Caption = '��ѯ.�շѷ�ʽ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'damt0'
      end
      item
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
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
        Name = '��ѯ.�豸����ID'
        Caption = '��ѯ.�豸����ID'
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
        Name = '��ѯ.�ϼ��豸����ID'
        Caption = '��ѯ.�ϼ��豸����ID'
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
        Name = '��ѯ.�豸��ʶ'
        Caption = '��ѯ.�豸��ʶ'
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
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol0'
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
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '�豸��;'
        Caption = '�豸��;'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'damt5'
      end
      item
        Name = '�ϼ��豸�����'
        Caption = '�ϼ��豸�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'damt6'
      end
      item
        Name = '�豸�����'
        Caption = '�豸�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 30
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sphone3'
      end
      item
        Name = '�豸��������'
        Caption = '�豸��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lserial1'
      end
      item
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = 'ͨ�ŵ�ַ'
        Caption = 'ͨ�ŵ�ַ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 15
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sstation0'
      end
      item
        Name = '�������˿ں�'
        Caption = '�������˿ں�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '�������˿�����'
        Caption = '�������˿�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol2'
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
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = 'ͨѶ���'
        Caption = 'ͨѶ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = 'ͨѶ�˿�'
        Caption = 'ͨѶ�˿�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code2'
      end
      item
        Name = '��Ƭ�ṹ'
        Caption = '��Ƭ�ṹ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scurrency_type'
      end
      item
        Name = '�Ƿ�֧�ֿ�Ŀ�շ�'
        Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
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
        Name = '��ע'
        Caption = '��ע'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'vsvarstr0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�豸����|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 355
    Top = 55
  end
  inherited QueryRequest: TWVRequest
    ID = '�ɱ༭�豸��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '��ѯ.���ʹ���'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '��ѯ.�豸�����ͺ�'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '��ѯ.������ϵͳ'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '��ѯ.�豸״̬'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = '��ѯ.�շѷ�ʽ'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '�豸����ID'
        FieldName = '��ѯ.�豸����ID'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = '��ѯ.�ϼ��豸����ID'
      end
      item
        ParamName = '�������κ�'
        FieldName = '��ѯ.�������κ�'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '��ѯ.�豸��ʶ'
      end>
    Left = 448
    Top = 24
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end
      item
        FieldName = 'damt6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '5'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'damt5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '81'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '50'
      end>
    Left = 391
    Top = 55
  end
  inherited AddRequest: TWVRequest
    ID = '�豸��Ϣ����.����'
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
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end
      item
        ParamName = '�豸��;'
        FieldName = '�豸��;'
      end
      item
        ParamName = '�ϼ��豸�����'
        FieldName = '�ϼ��豸�����'
      end
      item
        ParamName = '�豸�����'
        FieldName = '�豸�����'
      end
      item
        ParamName = '�豸��������'
        FieldName = '�豸��������'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = 'ͨ�ŵ�ַ'
        FieldName = 'ͨ�ŵ�ַ'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = '�Ƿ�֧�ֿ�Ŀ�շ�'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = '�������˿ں�'
      end
      item
        ParamName = '�������˿�����'
        FieldName = '�������˿�����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ͨѶ���'
        FieldName = 'ͨѶ���'
      end
      item
        ParamName = 'ͨѶ�˿�'
        FieldName = 'ͨѶ�˿�'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = '��Ƭ�ṹ'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 364
    Top = 24
  end
  inherited DeleteRequest: TWVRequest
    ID = '�豸��Ϣ����.ɾ��'
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
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end
      item
        ParamName = '�豸��;'
        FieldName = '�豸��;'
      end
      item
        ParamName = '�ϼ��豸�����'
        FieldName = '�ϼ��豸�����'
      end
      item
        ParamName = '�豸�����'
        FieldName = '�豸�����'
      end
      item
        ParamName = '�豸��������'
        FieldName = '�豸��������'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = 'ͨ�ŵ�ַ'
        FieldName = 'ͨ�ŵ�ַ'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = '�Ƿ�֧�ֿ�Ŀ�շ�'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = '�������˿ں�'
      end
      item
        ParamName = '�������˿�����'
        FieldName = '�������˿�����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ͨѶ���'
        FieldName = 'ͨѶ���'
      end
      item
        ParamName = 'ͨѶ�˿�'
        FieldName = 'ͨѶ�˿�'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = '��Ƭ�ṹ'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 392
    Top = 24
  end
  inherited ChangeRequest: TWVRequest
    ID = '�豸��Ϣ����.�޸�'
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
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end
      item
        ParamName = '�豸��;'
        FieldName = '�豸��;'
      end
      item
        ParamName = '�ϼ��豸�����'
        FieldName = '�ϼ��豸�����'
      end
      item
        ParamName = '�豸�����'
        FieldName = '�豸�����'
      end
      item
        ParamName = '�豸��������'
        FieldName = '�豸��������'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = 'ͨ�ŵ�ַ'
        FieldName = 'ͨ�ŵ�ַ'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = '�Ƿ�֧�ֿ�Ŀ�շ�'
      end
      item
        ParamName = '�������˿�����'
        FieldName = '�������˿�����'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = '�������˿ں�'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ͨѶ�˿�'
        FieldName = 'ͨѶ�˿�'
      end
      item
        ParamName = 'ͨѶ���'
        FieldName = 'ͨѶ���'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = '��Ƭ�ṹ'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 420
    Top = 24
  end
  inherited WVDataSource: TWVDataSource
    Left = 475
    Top = 55
  end
  inherited alDatasetActions: TActionList
    Left = 447
    Top = 55
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView
    ID = '�ɱ༭�豸��ѯ2'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '��ѯ.���ʹ���'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '��ѯ.�豸�����ͺ�'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '��ѯ.������ϵͳ'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '��ѯ.�豸״̬'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = '��ѯ.�շѷ�ʽ'
      end>
    AfterExec = CheckReturnData
    Left = 320
    Top = 56
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView1
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
    AfterExec = CheckReturnData
    Left = 256
    Top = 24
  end
  object WorkView1: TWorkView
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
        DefaultValue = '1'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end
      item
        MonitorValueChangedFields = '|�豸����|'
      end>
    Left = 299
    Top = 23
  end
end

inherited faqhdevImpManage: TfaqhdevImpManage
  Width = 807
  Height = 477
  Caption = '…Ë±∏µº»Îπ‹¿Ì'
  inherited pcPages: TRzPageControl
    Width = 807
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 409
        Width = 803
        Height = 45
        TabOrder = 3
        object Label10: TLabel [0]
          Left = 102
          Top = 9
          Width = 36
          Height = 12
          Caption = '≈˙¥Œ∫≈'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 718
          Caption = '…Û∫À(&C)'
          Enabled = False
          TabOrder = 5
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            18000000000000030000120B0000120B00000000000000000000FFFFFFFFFFFF
            FFFFFFCBD9CF509050408040306830305030203820202820B7C6B7FFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF70A08090E8B080E8A080E0A040
            905050B070509060304030B05040A04030A03020872C1DD3CDCBFFFFFFFFFFFF
            FFFFFF80B080C0E8D090F0B080B080C0D8C040905050A870406040FF9890C058
            50F05840E05030902810FFFFFFFFFFFFFFFFFFCBD5CF80B89070B070F0F0F0FF
            F8FF70A070407840D08870E09080F0B8B0C05850E05840A03820DBECF37AADBD
            598FA66080904068705050505050506060603B774AA66859C06860F0F8F0FFF8
            FFC05850B04830F0F0F06297B250B0D080D8F080B8C0000000B0B0B0B0B8B090
            98905058506F6F6F606060505850606060B04830CFBDB7FFFFFF5090B050D8FF
            90E8FF302830201820E0E0E0D0D0D0B0B0B0909890605860D0D0D0B0B0B09098
            90505850878787FFFFFF5090B050D0FF90E8F0404840403840C0C0C0E0E0E0D0
            D0D0B0B0B0706870E0E0E0D0D0D0B0B0B0909890605860FFFFFF5098B050D0FF
            90E8F0607070505850505050606060504850D0D0D0707070C0C0C0E0E0E0D0D0
            D0B0B0B0706870FFFFFF6098B050D0FF90E8F080B8C0606060807880A098A080
            8880404840404840505050606060504850D0D0D0777777FFFFFF6098B050D0FF
            90E0F0A0E0F060A0B0507880808080707880405060605860807880A098A08088
            80404840A4A4A4FFFFFF60A0C050D0FF90E0F0A0E8F070D8F020B8F000A8F000
            A0E0306890B7BAB77C847C808080778077ABAFABEFF0EFFFFFFF60A0C040D0F0
            90E0F0A0E8F070D8F020B8F000A8F000A0E0307090FFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFF904820FFFFFF70A8C050D8FFA0F0FFB0F0FFA0F0FF90E8FF70D8F040
            C0F0408090FFFFFFF6E3D8904820FFFFFFF9ECE5D06830FFFFFF80B0C0A0E0F0
            C0F8FFC0F8FFC0F8FFC0F8FFC0F8FFA0E0F06090A0FFFFFFA048209048209048
            20D06830F9ECE5FFFFFFD5EAED97C4D970A8C070A0B070A0B07098B070A0B081
            B3BAC0DCE3FFFFFFF6E3D8904820FFFFFFFFFFFFFFFFFFFFFFFF}
        end
        inherited btnChange: TBitBtn [2]
          Left = 462
          Enabled = False
          TabOrder = 2
        end
        inherited btnQuery: TBitBtn [3]
          Left = 376
        end
        inherited btnDelete: TBitBtn
          Left = 547
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Top = 32
          Width = 161
          TabOrder = 7
          Visible = False
        end
        object pbstat: TProgressBar
          Left = 0
          Top = 35
          Width = 803
          Height = 10
          Align = alBottom
          Min = 0
          Max = 100
          ParentShowHint = False
          Smooth = True
          ShowHint = False
          TabOrder = 8
        end
        object btnPatchDel: TBitBtn
          Left = 632
          Top = 3
          Width = 79
          Height = 25
          Hint = '…æ≥˝µ±«∞—°÷–µƒÃıƒø'
          Anchors = [akTop, akRight]
          Caption = '≈˙¡ø…æ≥˝'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = 'ÀŒÃÂ'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 143
          Top = 5
          Width = 98
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 6
          Text = '<≈˙¥Œ∫≈>'
          WorkView = WorkView1
          FieldName = '≈˙¥Œ∫≈'
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 803
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 803
        Height = 312
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '≈˙¥Œ∫≈'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'µº»ÎÀ≥–Ú∫≈'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ë±∏√˚≥∆'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ë±∏ŒÔ¿Ì±‡∫≈'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ë±∏¿‡–Õ'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ë±∏ª˙–Õ'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol7'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ë±∏”√Õæ'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'À˘ Ù◊”œµÕ≥'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…œº∂…Ë±∏±‡∫≈'
            Width = 65
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'À˘‘⁄«¯”Ú'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'saddr'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ø®∆¨Ω·ππ'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol8'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol6'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ë±∏ª˙∫≈'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstation0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'IPµÿ÷∑'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Õ®—∂∑Ω Ω'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Õ®—∂∂Àø⁄∫≈'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '¥ÌŒÛ–≈œ¢'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 803
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label3: TLabel
          Left = 38
          Top = 58
          Width = 36
          Height = 12
          Caption = '≈˙¥Œ∫≈'
        end
        object Label4: TLabel
          Left = 26
          Top = 10
          Width = 48
          Height = 12
          Caption = '…Ë±∏√˚≥∆'
        end
        object Label5: TLabel
          Left = 218
          Top = 10
          Width = 72
          Height = 12
          Caption = '…Ë±∏ŒÔ¿Ì±‡∫≈'
        end
        object Label6: TLabel
          Left = 474
          Top = 10
          Width = 48
          Height = 12
          Caption = '…Ë±∏¿‡–Õ'
        end
        object Label7: TLabel
          Left = 26
          Top = 34
          Width = 48
          Height = 12
          Caption = '…Ë±∏ª˙–Õ'
        end
        object Label8: TLabel
          Left = 242
          Top = 34
          Width = 48
          Height = 12
          Caption = '…Ë±∏”√Õæ'
        end
        object Label9: TLabel
          Left = 462
          Top = 34
          Width = 60
          Height = 12
          Caption = 'À˘ Ù◊”œµÕ≥'
        end
        object Label11: TLabel
          Left = 242
          Top = 58
          Width = 48
          Height = 12
          Caption = 'À˘‘⁄«¯”Ú'
        end
        object Label12: TLabel
          Left = 474
          Top = 58
          Width = 48
          Height = 12
          Caption = 'ø®∆¨Ω·ππ'
        end
        object Label17: TLabel
          Left = 290
          Top = 234
          Width = 6
          Height = 12
        end
        object WVEdit3: TWVEdit
          Left = 84
          Top = 54
          Width = 129
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 8
          Text = '<≤È—Ø.≈˙¥Œ∫≈>'
          WorkView = WorkView
          FieldName = '≤È—Ø.≈˙¥Œ∫≈'
        end
        object WVEdit4: TWVEdit
          Left = 84
          Top = 6
          Width = 129
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<≤È—Ø.…Ë±∏√˚≥∆>'
          WorkView = WorkView
          FieldName = '≤È—Ø.…Ë±∏√˚≥∆'
        end
        object WVEdit5: TWVEdit
          Left = 300
          Top = 6
          Width = 142
          Height = 20
          Color = clInfoBk
          MaxLength = 8
          ReadOnly = False
          TabOrder = 1
          Text = '<≤È—Ø.…Ë±∏ŒÔ¿Ì±‡∫≈>'
          WorkView = WorkView
          FieldName = '≤È—Ø.…Ë±∏ŒÔ¿Ì±‡∫≈'
        end
        object cbbQEquPhyType: TWVComboBox
          Left = 532
          Top = 7
          Width = 128
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'ÀŒÃÂ'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 2
          WorkView = WorkView
          FieldName = '≤È—Ø.…Ë±∏¿‡–Õ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-35'
        end
        object cbbQMachineType: TWVComboBox
          Left = 84
          Top = 31
          Width = 129
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'ÀŒÃÂ'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 3
          WorkView = WorkView
          FieldName = '≤È—Ø.…Ë±∏ª˙–Õ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object cbbQUseType: TWVComboBox
          Left = 300
          Top = 31
          Width = 143
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'ÀŒÃÂ'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 4
          WorkView = WorkView
          FieldName = '≤È—Ø.…Ë±∏”√Õæ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*81'
        end
        object cbbQChildSys: TWVComboBox
          Left = 532
          Top = 31
          Width = 128
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'ÀŒÃÂ'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 5
          WorkView = WorkView
          FieldName = '≤È—Ø.À˘ Ù◊”œµÕ≥'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVComboBox2: TWVComboBox
          Left = 300
          Top = 53
          Width = 143
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '≤È—Ø.À˘‘⁄«¯”Ú'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-28'
        end
        object WVComboBox4: TWVComboBox
          Left = 532
          Top = 53
          Width = 129
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'ÀŒÃÂ'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 7
          WorkView = WorkView
          FieldName = '≤È—Ø.ø®∆¨Ω·ππ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*48'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label20: TLabel [0]
        Left = 330
        Top = 44
        Width = 60
        Height = 12
        Caption = 'µº»ÎÀ≥–Ú∫≈'
      end
      object Label21: TLabel [1]
        Left = 51
        Top = 44
        Width = 60
        Height = 12
        Caption = 'µº»Î≈˙¥Œ∫≈'
      end
      object Label23: TLabel [2]
        Left = 57
        Top = 76
        Width = 54
        Height = 12
        Caption = '…Ë±∏√˚≥∆*'
      end
      object Label24: TLabel [3]
        Left = 39
        Top = 140
        Width = 72
        Height = 12
        Caption = '…Ë±∏ŒÔ¿Ì±‡∫≈'
      end
      object Label25: TLabel [4]
        Left = 336
        Top = 76
        Width = 54
        Height = 12
        Caption = '…Ë±∏¿‡–Õ*'
      end
      object Label26: TLabel [5]
        Left = 336
        Top = 108
        Width = 54
        Height = 12
        Caption = '…Ë±∏ª˙–Õ*'
      end
      object Label27: TLabel [6]
        Left = 57
        Top = 108
        Width = 54
        Height = 12
        Caption = '…Ë±∏”√Õæ*'
      end
      object Label28: TLabel [7]
        Left = 324
        Top = 172
        Width = 66
        Height = 12
        Caption = 'À˘ Ù◊”œµÕ≥*'
      end
      object Label29: TLabel [8]
        Left = 33
        Top = 172
        Width = 78
        Height = 12
        Caption = '…œº∂…Ë±∏±‡∫≈*'
      end
      object Label30: TLabel [9]
        Left = 336
        Top = 140
        Width = 54
        Height = 12
        Caption = 'À˘‘⁄«¯”Ú*'
      end
      object Label31: TLabel [10]
        Left = 342
        Top = 204
        Width = 48
        Height = 12
        Caption = 'ø®∆¨Ω·ππ'
      end
      object Label32: TLabel [11]
        Left = 39
        Top = 204
        Width = 72
        Height = 12
        Caption = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
      end
      object Label33: TLabel [12]
        Left = 27
        Top = 268
        Width = 84
        Height = 12
        Caption = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
      end
      object Label35: TLabel [13]
        Left = 342
        Top = 236
        Width = 48
        Height = 12
        Caption = '…Ë±∏ª˙∫≈'
      end
      object Label36: TLabel [14]
        Left = 540
        Top = 124
        Width = 6
        Height = 12
      end
      object Label37: TLabel [15]
        Left = 342
        Top = 268
        Width = 48
        Height = 12
        Caption = 'Õ®—∂∑Ω Ω'
      end
      object Label1: TLabel [16]
        Left = 75
        Top = 236
        Width = 36
        Height = 12
        Caption = 'IPµÿ÷∑'
      end
      object Label2: TLabel [17]
        Left = 51
        Top = 300
        Width = 60
        Height = 12
        Caption = 'Õ®—∂∂Àø⁄∫≈'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 803
        TabOrder = 17
        inherited btnOK: TBitBtn
          Left = 631
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 719
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtPatchNo: TWVEdit
        Left = 118
        Top = 40
        Width = 188
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 0
        Text = '<≈˙¥Œ∫≈>'
        WorkView = WorkView
        FieldName = '≈˙¥Œ∫≈'
        SynchronizeWhenExit = True
      end
      object edtEquName: TWVEdit
        Left = 118
        Top = 72
        Width = 188
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<…Ë±∏√˚≥∆>'
        WorkView = WorkView
        FieldName = '…Ë±∏√˚≥∆'
        SynchronizeWhenExit = True
      end
      object WVEdit24: TWVEdit
        Left = 118
        Top = 136
        Width = 188
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 6
        Text = '<…Ë±∏ŒÔ¿Ì±‡∫≈>'
        WorkView = WorkView
        FieldName = '…Ë±∏ŒÔ¿Ì±‡∫≈'
        SynchronizeWhenExit = True
      end
      object edtUEqu: TWVEdit
        Left = 118
        Top = 168
        Width = 188
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<…œº∂…Ë±∏±‡∫≈>'
        WorkView = WorkView
        FieldName = '…œº∂…Ë±∏±‡∫≈'
        SynchronizeWhenExit = True
      end
      object edtSerPortNo: TWVEdit
        Left = 118
        Top = 199
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 10
        Text = '<∑˛ŒÒ∆˜∂Àø⁄∫≈>'
        WorkView = WorkView
        FieldName = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
        SynchronizeWhenExit = True
      end
      object edtIP: TWVEdit
        Left = 118
        Top = 232
        Width = 188
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 13
        Text = '<IPµÿ÷∑>'
        WorkView = WorkView
        FieldName = 'IPµÿ÷∑'
        SynchronizeWhenExit = True
      end
      object cbbEquPhyType: TWVComboBox
        Left = 398
        Top = 73
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'ÀŒÃÂ'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 3
        Text = '<…Ë±∏¿‡–Õ>'
        WorkView = WorkView
        FieldName = '…Ë±∏¿‡–Õ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-35'
      end
      object cbbMachineType: TWVComboBox
        Left = 398
        Top = 104
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'ÀŒÃÂ'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 4
        Text = '<…Ë±∏ª˙–Õ>'
        WorkView = WorkView
        FieldName = '…Ë±∏ª˙–Õ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '47'
      end
      object cbbUseType: TWVComboBox
        Left = 118
        Top = 105
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'ÀŒÃÂ'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 5
        Text = '<…Ë±∏”√Õæ>'
        WorkView = WorkView
        FieldName = '…Ë±∏”√Õæ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '81'
      end
      object cbbArea: TWVComboBox
        Left = 398
        Top = 136
        Width = 188
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 0
        TabOrder = 7
        Text = '<À˘‘⁄«¯”Ú>'
        WorkView = WorkView
        FieldName = 'À˘‘⁄«¯”Ú'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-28'
      end
      object cbbChildSys: TWVComboBox
        Left = 398
        Top = 169
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'ÀŒÃÂ'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 9
        Text = '<À˘ Ù◊”œµÕ≥>'
        WorkView = WorkView
        FieldName = 'À˘ Ù◊”œµÕ≥'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-32'
      end
      object WVComboBox8: TWVComboBox
        Left = 398
        Top = 200
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'ÀŒÃÂ'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 11
        Text = '<ø®∆¨Ω·ππ>'
        WorkView = WorkView
        FieldName = 'ø®∆¨Ω·ππ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*48'
      end
      object cbbComm: TWVComboBox
        Left = 398
        Top = 265
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'ÀŒÃÂ'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 15
        Text = '<Õ®—∂∑Ω Ω>'
        WorkView = WorkView
        FieldName = 'Õ®—∂∑Ω Ω'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*50'
      end
      object edtMachineNo: TWVEdit
        Left = 398
        Top = 231
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 12
        Text = '<…Ë±∏ª˙∫≈>'
        WorkView = WorkView
        FieldName = '…Ë±∏ª˙∫≈'
        SynchronizeWhenExit = True
      end
      object edtSerPortNum: TWVEdit
        Left = 118
        Top = 263
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 14
        Text = '<∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝>'
        WorkView = WorkView
        FieldName = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
        SynchronizeWhenExit = True
      end
      object edtCommPortNo: TWVEdit
        Left = 118
        Top = 295
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 16
        Text = '<Õ®—∂∂Àø⁄∫≈>'
        WorkView = WorkView
        FieldName = 'Õ®—∂∂Àø⁄∫≈'
        SynchronizeWhenExit = True
      end
      object edtNo: TWVEdit
        Left = 398
        Top = 40
        Width = 188
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<µº»ÎÀ≥–Ú∫≈>'
        WorkView = WorkView
        FieldName = 'µº»ÎÀ≥–Ú∫≈'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 76
    Top = 407
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '≤È—ØΩ·π˚ºØ'
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
        Name = '≤Ÿ◊˜¿‡±.‘ˆº”'
        Caption = '≤Ÿ◊˜¿‡±.‘ˆº”'
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
        Name = '≤Ÿ◊˜¿‡±.…æ≥˝'
        Caption = '≤Ÿ◊˜¿‡±.…æ≥˝'
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
        Name = '≤Ÿ◊˜¿‡±.–ﬁ∏ƒ'
        Caption = '≤Ÿ◊˜¿‡±.–ﬁ∏ƒ'
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
        Name = '≤Ÿ◊˜±Í÷æ'
        Caption = '≤Ÿ◊˜±Í÷æ'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '≤È—Ø.…Ë±∏√˚≥∆'
        Caption = '≤È—Ø.…Ë±∏√˚≥∆'
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
        Name = '≤È—Ø.…Ë±∏ŒÔ¿Ì±‡∫≈'
        Caption = '≤È—Ø.…Ë±∏ŒÔ¿Ì±‡∫≈'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '≤È—Ø.…Ë±∏¿‡–Õ'
        Caption = '≤È—Ø.…Ë±∏¿‡–Õ'
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
        Name = '≤È—Ø.…Ë±∏ª˙–Õ'
        Caption = '≤È—Ø.…Ë±∏ª˙–Õ'
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
        Name = '≤È—Ø.…Ë±∏”√Õæ'
        Caption = '≤È—Ø.…Ë±∏”√Õæ'
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
        Name = '≤È—Ø.À˘ Ù◊”œµÕ≥'
        Caption = '≤È—Ø.À˘ Ù◊”œµÕ≥'
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
        Name = '≤È—Ø.À˘‘⁄«¯”Ú'
        Caption = '≤È—Ø.À˘‘⁄«¯”Ú'
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
        Name = '≤È—Ø.≈˙¥Œ∫≈'
        Caption = '≤È—Ø.≈˙¥Œ∫≈'
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
        Name = '≤È—Ø.ø®∆¨Ω·ππ'
        Caption = '≤È—Ø.ø®∆¨Ω·ππ'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = 'µº»ÎÀ≥–Ú∫≈'
        Caption = 'µº»ÎÀ≥–Ú∫≈'
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
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '≈˙¥Œ∫≈'
        Caption = '≈˙¥Œ∫≈'
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
        GroupIndex = 1
        DataField = 'scust_limit'
      end
      item
        Name = '…Ë±∏√˚≥∆'
        Caption = '…Ë±∏√˚≥∆'
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
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '…Ë±∏ŒÔ¿Ì±‡∫≈'
        Caption = '…Ë±∏ŒÔ¿Ì±‡∫≈'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = True
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sphone3'
      end
      item
        Name = '…Ë±∏¿‡–Õ'
        Caption = '…Ë±∏¿‡–Õ'
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
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '…Ë±∏ª˙–Õ'
        Caption = '…Ë±∏ª˙–Õ'
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
        GroupIndex = 1
        DataField = 'sserial1'
      end
      item
        Name = '…Ë±∏”√Õæ'
        Caption = '…Ë±∏”√Õæ'
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
        GroupIndex = 1
        DataField = 'Lvol7'
      end
      item
        Name = 'À˘ Ù◊”œµÕ≥'
        Caption = 'À˘ Ù◊”œµÕ≥'
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
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '…œº∂…Ë±∏±‡∫≈'
        Caption = '…œº∂…Ë±∏±‡∫≈'
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
        GroupIndex = 1
        DataField = 'Lvol0'
      end
      item
        Name = 'À˘‘⁄«¯”Ú'
        Caption = 'À˘‘⁄«¯”Ú'
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
        GroupIndex = 1
        DataField = 'sbranch_code0'
      end
      item
        Name = 'ø®∆¨Ω·ππ'
        Caption = 'ø®∆¨Ω·ππ'
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
        GroupIndex = 1
        DataField = 'saddr'
      end
      item
        Name = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
        Caption = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol8'
      end
      item
        Name = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
        Caption = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Lvol2'
      end
      item
        Name = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
        Caption = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Lvol6'
      end
      item
        Name = '…Ë±∏ª˙∫≈'
        Caption = '…Ë±∏ª˙∫≈'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = 'IPµÿ÷∑'
        Caption = 'IPµÿ÷∑'
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
        GroupIndex = 1
        DataField = 'sstation0'
      end
      item
        Name = 'Õ®—∂∑Ω Ω'
        Caption = 'Õ®—∂∑Ω Ω'
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = 'Õ®—∂∂Àø⁄∫≈'
        Caption = 'Õ®—∂∂Àø⁄∫≈'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol3'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|≤È—Ø.≤Ÿ◊˜±Í÷æ|≤È—Ø.µº»ÎÀ≥–Ú∫≈|≤È—Ø.≈˙¥Œ∫≈|≤È—Ø.…Ë±∏√˚≥∆|≤È—Ø.…Ë' +
          '±∏ŒÔ¿Ì±‡∫≈|≤È—Ø.…Ë±∏¿‡–Õ|≤È—Ø.…Ë±∏ª˙–Õ|≤È—Ø.…Ë±∏”√Õæ|≤È—Ø.À˘ Ù◊”' +
          'œµÕ≥|≤È—Ø.…œº∂…Ë±∏±‡∫≈|≤È—Ø.À˘‘⁄«¯”Ú|≤È—Ø.ø®∆¨Ω·ππ|≤È—Ø.∑˛ŒÒ∆˜∂À' +
          'ø⁄∫≈|≤È—Ø.∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝|≤È—Ø. «∑Ò÷ß≥÷ø∆ƒø ’∑—|≤È—Ø.…Ë±∏ª˙∫≈|≤È' +
          '—Ø.|≤È—Ø.Õ®—∂∑Ω Ω|≤È—Ø.Õ®—∂∂Àø⁄∫≈|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|µº»ÎÀ≥–Ú∫≈|≈˙¥Œ∫≈|À≥–Ú∫≈|…Ë±∏√˚≥∆|…Ë±∏ŒÔ¿|…Ë±∏¿‡–Õ|…Ë±∏ª˙–Õ|…Ë' +
          '±∏”√Õæ|À˘ Ù◊”œµÕ≥|…œº∂…Ë±|À˘‘⁄«¯”Ú|ø®∆¨Ω·ππ|∑˛ŒÒ∆˜∂Àø⁄∫≈|∑˛ŒÒ∆˜' +
          '∂Àø⁄◊‹ ˝| «∑Ò÷ß≥÷ø∆ƒø ’∑—|…Ë±∏ª˙∫≈||Õ®—∂∑Ω Ω|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 8
    Top = 376
  end
  inherited QueryRequest: TWVRequest
    ID = '…Ë±∏–≈œ¢≤È—Ø'
    Bindings = <
      item
        ParamName = '≤È—ØΩ·π˚ºØ'
        FieldName = '≤È—ØΩ·π˚ºØ'
        Direction = bdParam2Field
      end
      item
        ParamName = '≤Ÿ◊˜±Í÷æ'
        FieldName = '≤Ÿ◊˜±Í÷æ'
      end
      item
        ParamName = '≈˙¥Œ∫≈'
        FieldName = '≤È—Ø.≈˙¥Œ∫≈'
      end
      item
        ParamName = '…Ë±∏√˚≥∆'
        FieldName = '≤È—Ø.…Ë±∏√˚≥∆'
      end
      item
        ParamName = '…Ë±∏ŒÔ¿Ì±‡∫≈'
        FieldName = '≤È—Ø.…Ë±∏ŒÔ¿Ì±‡∫≈'
      end
      item
        ParamName = '…Ë±∏¿‡–Õ'
        FieldName = '≤È—Ø.…Ë±∏¿‡–Õ'
      end
      item
        ParamName = '…Ë±∏ª˙–Õ'
        FieldName = '≤È—Ø.…Ë±∏ª˙–Õ'
      end
      item
        ParamName = '…Ë±∏”√Õæ'
        FieldName = '≤È—Ø.…Ë±∏”√Õæ'
      end
      item
        ParamName = 'À˘ Ù◊”œµÕ≥'
        FieldName = '≤È—Ø.À˘ Ù◊”œµÕ≥'
      end
      item
        ParamName = 'À˘‘⁄«¯”Ú'
        FieldName = '≤È—Ø.À˘‘⁄«¯”Ú'
      end
      item
        ParamName = 'ø®∆¨Ω·ππ'
        FieldName = '≤È—Ø.ø®∆¨Ω·ππ'
      end>
    Left = 136
    Top = 376
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '≤È—ØΩ·π˚ºØ'
    Bindings = <
      item
        FieldName = 'Lvol7'
        DataPresentType = 'Idobjects'
        DataPresentParam = '81'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'Idobjects'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'Idobjects'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'Lvol6'
        DataPresentType = 'Idobjects'
        DataPresentParam = '64'
      end
      item
        FieldName = 'saddr'
        DataPresentType = 'Idobjects'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'Idobjects'
        DataPresentParam = '50'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'sserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end>
    Left = 44
    Top = 407
  end
  inherited AddRequest: TWVRequest
    ID = '…Ë±∏µº»Îπ‹¿Ì'
    Bindings = <
      item
        ParamName = 'µº»ÎÀ≥–Ú∫≈'
        FieldName = 'µº»ÎÀ≥–Ú∫≈'
      end
      item
        ParamName = '≈˙¥Œ∫≈'
        FieldName = '≈˙¥Œ∫≈'
      end
      item
        ParamName = 'À≥–Ú∫≈'
        FieldName = 'À≥–Ú∫≈'
      end
      item
        ParamName = '…Ë±∏√˚≥∆'
        FieldName = '…Ë±∏√˚≥∆'
      end
      item
        ParamName = '…Ë±∏ŒÔ¿'
        FieldName = '…Ë±∏ŒÔ¿'
      end
      item
        ParamName = '…Ë±∏¿‡–Õ'
        FieldName = '…Ë±∏¿‡–Õ'
      end
      item
        ParamName = '…Ë±∏ª˙–Õ'
        FieldName = '…Ë±∏ª˙–Õ'
      end
      item
        ParamName = '…Ë±∏”√Õæ'
        FieldName = '…Ë±∏”√Õæ'
      end
      item
        ParamName = 'À˘ Ù◊”œµÕ≥'
        FieldName = 'À˘ Ù◊”œµÕ≥'
      end
      item
        ParamName = '…œº∂…Ë±'
        FieldName = '…œº∂…Ë±'
      end
      item
        ParamName = 'À˘‘⁄«¯”Ú'
        FieldName = 'À˘‘⁄«¯”Ú'
      end
      item
        ParamName = 'ø®∆¨Ω·ππ'
        FieldName = 'ø®∆¨Ω·ππ'
      end
      item
        ParamName = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
        FieldName = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
      end
      item
        ParamName = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
        FieldName = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
      end
      item
        ParamName = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
        FieldName = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
      end
      item
        ParamName = '…Ë±∏ª˙∫≈'
        FieldName = '…Ë±∏ª˙∫≈'
      end
      item
        ParamName = 'Õ®—∂∑Ω Ω'
        FieldName = 'Õ®—∂∑Ω Ω'
      end
      item
        ParamName = 'Õ®—∂∂Àø⁄∫≈'
        FieldName = 'Õ®—∂∂Àø⁄∫≈.‘ˆº”'
      end>
    Left = 40
    Top = 376
  end
  inherited DeleteRequest: TWVRequest
    ID = '…Ë±∏µº»Îπ‹¿Ì'
    Bindings = <
      item
        ParamName = 'µº»ÎÀ≥–Ú∫≈'
        FieldName = 'µº»ÎÀ≥–Ú∫≈'
      end
      item
        ParamName = '≈˙¥Œ∫≈'
        FieldName = '≈˙¥Œ∫≈'
      end
      item
        ParamName = '…Ë±∏√˚≥∆'
        FieldName = '…Ë±∏√˚≥∆'
      end
      item
        ParamName = '…Ë±∏ŒÔ¿Ì±‡∫≈'
        FieldName = '…Ë±∏ŒÔ¿Ì±‡∫≈'
      end
      item
        ParamName = '…Ë±∏¿‡–Õ'
        FieldName = '…Ë±∏¿‡–Õ'
      end
      item
        ParamName = '…Ë±∏ª˙–Õ'
        FieldName = '…Ë±∏ª˙–Õ'
      end
      item
        ParamName = '…Ë±∏”√Õæ'
        FieldName = '…Ë±∏”√Õæ'
      end
      item
        ParamName = 'À˘ Ù◊”œµÕ≥'
        FieldName = 'À˘ Ù◊”œµÕ≥'
      end
      item
        ParamName = '…œº∂…Ë±∏±‡∫≈'
        FieldName = '…œº∂…Ë±∏±‡∫≈'
      end
      item
        ParamName = 'À˘‘⁄«¯”Ú'
        FieldName = 'À˘‘⁄«¯”Ú'
      end
      item
        ParamName = 'ø®∆¨Ω·ππ'
        FieldName = 'ø®∆¨Ω·ππ'
      end
      item
        ParamName = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
        FieldName = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
      end
      item
        ParamName = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
        FieldName = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
      end
      item
        ParamName = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
        FieldName = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
      end
      item
        ParamName = '…Ë±∏ª˙∫≈'
        FieldName = '…Ë±∏ª˙∫≈'
      end
      item
        ParamName = 'IPµÿ÷∑'
        FieldName = 'IPµÿ÷∑'
      end
      item
        ParamName = 'Õ®—∂∑Ω Ω'
        FieldName = 'Õ®—∂∑Ω Ω'
      end
      item
        ParamName = 'Õ®—∂∂Àø⁄∫≈'
        FieldName = 'Õ®—∂∂Àø⁄∫≈'
      end
      item
        ParamName = '≤Ÿ◊˜±Í÷æ'
        FieldName = '≤Ÿ◊˜±Í÷æ'
      end>
    Left = 72
    Top = 376
  end
  inherited ChangeRequest: TWVRequest
    ID = '…Ë±∏µº»Îπ‹¿Ì'
    Bindings = <
      item
        ParamName = 'µº»ÎÀ≥–Ú∫≈'
        FieldName = 'µº»ÎÀ≥–Ú∫≈'
      end
      item
        ParamName = '≈˙¥Œ∫≈'
        FieldName = '≈˙¥Œ∫≈'
      end
      item
        ParamName = '…Ë±∏√˚≥∆'
        FieldName = '…Ë±∏√˚≥∆'
      end
      item
        ParamName = '…Ë±∏ŒÔ¿Ì±‡∫≈'
        FieldName = '…Ë±∏ŒÔ¿Ì±‡∫≈'
      end
      item
        ParamName = '…Ë±∏¿‡–Õ'
        FieldName = '…Ë±∏¿‡–Õ'
      end
      item
        ParamName = '…Ë±∏ª˙–Õ'
        FieldName = '…Ë±∏ª˙–Õ'
      end
      item
        ParamName = '…Ë±∏”√Õæ'
        FieldName = '…Ë±∏”√Õæ'
      end
      item
        ParamName = 'À˘ Ù◊”œµÕ≥'
        FieldName = 'À˘ Ù◊”œµÕ≥'
      end
      item
        ParamName = '…œº∂…Ë±∏±‡∫≈'
        FieldName = '…œº∂…Ë±∏±‡∫≈'
      end
      item
        ParamName = 'À˘‘⁄«¯”Ú'
        FieldName = 'À˘‘⁄«¯”Ú'
      end
      item
        ParamName = 'ø®∆¨Ω·ππ'
        FieldName = 'ø®∆¨Ω·ππ'
      end
      item
        ParamName = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
        FieldName = '∑˛ŒÒ∆˜∂Àø⁄∫≈'
      end
      item
        ParamName = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
        FieldName = '∑˛ŒÒ∆˜∂Àø⁄◊‹ ˝'
      end
      item
        ParamName = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
        FieldName = ' «∑Ò÷ß≥÷ø∆ƒø ’∑—'
      end
      item
        ParamName = '…Ë±∏ª˙∫≈'
        FieldName = '…Ë±∏ª˙∫≈'
      end
      item
        ParamName = 'IPµÿ÷∑'
        FieldName = 'IPµÿ÷∑'
      end
      item
        ParamName = 'Õ®—∂∑Ω Ω'
        FieldName = 'Õ®—∂∑Ω Ω'
      end
      item
        ParamName = 'Õ®—∂∂Àø⁄∫≈'
        FieldName = 'Õ®—∂∂Àø⁄∫≈'
      end
      item
        ParamName = '≤Ÿ◊˜±Í÷æ'
        FieldName = '≤Ÿ◊˜±Í÷æ'
      end>
    Left = 104
    Top = 376
  end
  inherited WVDataSource: TWVDataSource
    Left = 140
    Top = 407
  end
  inherited alDatasetActions: TActionList
    Left = 108
    Top = 404
  end
  object WVImpCheck: TWorkView
    WorkFields = <
      item
        Name = '≤È—ØΩ·π˚ºØ'
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
        Name = 'µº»Î≈˙¥Œ∫≈'
        Caption = 'µº»Î≈˙¥Œ∫≈'
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
        DataField = 'scust_limit'
      end
      item
        Name = 'µº»ÎÀ≥–Ú∫≈'
        Caption = 'µº»ÎÀ≥–Ú∫≈'
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
        DataField = 'Lvol1'
      end
      item
        Name = '≤Ÿ◊˜±Í÷æ'
        Caption = '≤Ÿ◊˜±Í÷æ'
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
          '|≤È—Ø.≤Ÿ◊˜±Í÷æ|≤È—Ø.µº»Î≈˙¥Œ∫≈|≤È—Ø.µº»ÎÀ≥–Ú∫≈|≤È—Ø.º«¬º∫≈|≤È—Ø.' +
          '…Ë±∏±‡∫≈|≤È—Ø.…Ë±∏ŒÔ¿Ì±‡∫≈|≤È—Ø.…Ë±∏√˚≥∆|≤È—Ø.…Ãªß±‡∫≈|≤È—Ø.…Ãªß' +
          '√˚≥∆|≤È—Ø.ø™ º ±º‰|≤È—Ø.Ω· ¯ ±º‰|≤È—Ø.∆Ù”√»’∆⁄|≤È—Ø.Õ£”√»’∆⁄|≤È' +
          '—Ø.±∏◊¢|'
      end
      item
        MonitorValueChangedFields = 
          '|µº»Î≈˙¥Œ∫≈|µº»ÎÀ≥–Ú∫≈|º«¬º∫≈|…Ë±∏±‡∫≈|…Ë±∏ŒÔ¿Ì±‡∫≈|…Ë±∏√˚≥∆|…Ã' +
          'ªß±‡∫≈|…Ãªß√˚≥∆|ø™ º ±º‰|Ω· ¯ ±º‰|∆Ù”√»’∆⁄|Õ£”√»’∆⁄|'
      end>
    Left = 8
    Top = 336
  end
  object WVRImpCheck: TWVRequest
    WorkView = WVImpCheck
    ID = '…Ë±∏µº»Î…Û∫À'
    Bindings = <
      item
        ParamName = 'µº»Î≈˙¥Œ∫≈'
        FieldName = 'µº»Î≈˙¥Œ∫≈'
      end
      item
        ParamName = 'µº»ÎÀ≥–Ú∫≈'
        FieldName = 'µº»ÎÀ≥–Ú∫≈'
      end
      item
        ParamName = '≤Ÿ◊˜±Í÷æ'
        FieldName = '≤Ÿ◊˜±Í÷æ'
      end>
    AfterExec = CheckReturnData
    Left = 40
    Top = 336
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '∑µªÿ–≈œ¢'
        Caption = '∑µªÿ–≈œ¢'
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
        Name = '≈˙¥Œ∫≈'
        Caption = '≈˙¥Œ∫≈'
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
        DataField = 'scust_limit'
      end
      item
        Name = '≤Ÿ◊˜±Í÷æ'
        Caption = '≤Ÿ◊˜±Í÷æ'
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
        Name = '≈˙¡ø±Í÷æ'
        Caption = '≈˙¡ø±Í÷æ'
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
        Name = '∑µªÿ¬Î'
        Caption = '∑µªÿ¬Î'
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
          '|≤È—Ø.≤Ÿ◊˜±Í÷æ|≤È—Ø.µº»Î≈˙¥Œ∫≈|≤È—Ø.µº»ÎÀ≥–Ú∫≈|≤È—Ø.º«¬º∫≈|≤È—Ø.' +
          '…Ë±∏±‡∫≈|≤È—Ø.…Ë±∏ŒÔ¿Ì±‡∫≈|≤È—Ø.…Ë±∏√˚≥∆|≤È—Ø.…Ãªß±‡∫≈|≤È—Ø.…Ãªß' +
          '√˚≥∆|≤È—Ø.ø™ º ±º‰|≤È—Ø.Ω· ¯ ±º‰|≤È—Ø.∆Ù”√»’∆⁄|≤È—Ø.Õ£”√»’∆⁄|≤È' +
          '—Ø.±∏◊¢|'
      end
      item
        MonitorValueChangedFields = 
          '|µº»Î≈˙¥Œ∫≈|µº»ÎÀ≥–Ú∫≈|º«¬º∫≈|…Ë±∏±‡∫≈|…Ë±∏ŒÔ¿Ì±‡∫≈|…Ë±∏√˚≥∆|…Ã' +
          'ªß±‡∫≈|…Ãªß√˚≥∆|ø™ º ±º‰|Ω· ¯ ±º‰|∆Ù”√»’∆⁄|Õ£”√»’∆⁄|'
      end>
    Left = 144
    Top = 328
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '…Ë±∏≈˙¡ø…æ≥˝'
    Bindings = <
      item
        ParamName = '≈˙¥Œ∫≈'
        FieldName = '≈˙¥Œ∫≈'
      end
      item
        ParamName = '≤Ÿ◊˜±Í÷æ'
        FieldName = '≤Ÿ◊˜±Í÷æ'
      end
      item
        ParamName = '≈˙¡ø±Í÷æ'
        FieldName = '≈˙¡ø±Í÷æ'
      end
      item
        ParamName = '∑µªÿ¬Î'
        FieldName = '∑µªÿ¬Î'
        Direction = bdParam2Field
      end
      item
        ParamName = '∑µªÿ–≈œ¢'
        FieldName = '∑µªÿ–≈œ¢'
        Direction = bdParam2Field
      end>
    AfterExec = CheckReturnData
    Left = 176
    Top = 328
  end
end

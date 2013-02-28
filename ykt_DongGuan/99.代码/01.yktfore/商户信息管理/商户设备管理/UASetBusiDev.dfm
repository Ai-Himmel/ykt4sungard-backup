inherited faqhSetBusiDev: TfaqhSetBusiDev
  Width = 839
  Height = 477
  Caption = '…Ãªß…Ë±∏π‹¿Ì'
  inherited pcPages: TRzPageControl
    Width = 839
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 835
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 573
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 661
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 485
        end
        inherited btnDelete: TBitBtn
          Left = 746
          Enabled = False
          TabOrder = 2
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 835
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 73
        Width = 835
        Height = 351
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ãªß∫≈'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ãªß√˚≥∆'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ë±∏÷’∂À–Ú¡–∫≈'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstock_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '…Ë±∏¿‡–Õ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scurrency_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '◊¥Ã¨'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '◊¢≤·»’∆⁄'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '∆Ù”√»’∆⁄'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Õ£”√»’∆⁄'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '∞Û∂®…Ë±∏±‡∫≈'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '±∏◊¢'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '◊Ó∫Û∏¸–¬ ±º‰'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 835
        Height = 55
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label3: TLabel
          Left = 22
          Top = 10
          Width = 84
          Height = 12
          Caption = '…Ë±∏÷’∂À–Ú¡–∫≈'
        end
        object Label4: TLabel
          Left = 10
          Top = 34
          Width = 96
          Height = 12
          Caption = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
        end
        object Label5: TLabel
          Left = 282
          Top = 10
          Width = 48
          Height = 12
          Caption = '…Ë±∏¿‡–Õ'
        end
        object Label6: TLabel
          Left = 306
          Top = 34
          Width = 24
          Height = 12
          Caption = '◊¥Ã¨'
        end
        object WVEdit3: TWVEdit
          Left = 116
          Top = 6
          Width = 133
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<≤È—Ø.…Ë±∏÷’∂À–Ú¡–∫≈>'
          WorkView = WorkView
          FieldName = '≤È—Ø.…Ë±∏÷’∂À–Ú¡–∫≈'
        end
        object WVEdit4: TWVEdit
          Left = 116
          Top = 30
          Width = 133
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<≤È—Ø. °…Ë±∏÷’∂À–Ú¡–∫≈>'
          WorkView = WorkView
          FieldName = '≤È—Ø. °…Ë±∏÷’∂À–Ú¡–∫≈'
        end
        object WVComboBox3: TWVComboBox
          Left = 340
          Top = 3
          Width = 141
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '÷–Œƒ (ºÚÃÂ) - Œ¢»Ì∆¥“Ù'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '≤È—Ø.…Ë±∏¿‡–Õ'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*221'
        end
        object WVComboBox4: TWVComboBox
          Left = 340
          Top = 27
          Width = 141
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '÷–Œƒ (ºÚÃÂ) - Œ¢»Ì∆¥“Ù'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '≤È—Ø.◊¥Ã¨'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*239'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label10: TLabel [0]
        Left = 78
        Top = 60
        Width = 36
        Height = 12
        Caption = '…Ãªß∫≈'
      end
      object Label13: TLabel [1]
        Left = 84
        Top = 164
        Width = 6
        Height = 12
        Caption = ' '
      end
      object Label14: TLabel [2]
        Left = 66
        Top = 166
        Width = 48
        Height = 12
        Caption = '…Ë±∏¿‡–Õ'
      end
      object Label1: TLabel [3]
        Left = 18
        Top = 130
        Width = 96
        Height = 12
        Caption = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      object btnQBusi: TSpeedButton [4]
        Left = 243
        Top = 56
        Width = 23
        Height = 22
        Caption = '>>>'
        Flat = True
        OnClick = btnQBusiClick
      end
      object Label2: TLabel [5]
        Left = 66
        Top = 96
        Width = 48
        Height = 12
        Caption = '…Ãªß√˚≥∆'
      end
      object Label7: TLabel [6]
        Left = 90
        Top = 200
        Width = 24
        Height = 12
        Caption = '±∏◊¢'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 835
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 659
        end
        inherited btnCancel: TBitBtn
          Left = 747
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtSSNo: TWVEdit
        Left = 124
        Top = 126
        Width = 277
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '< °…Ë±∏÷’∂À–Ú¡–∫≈>'
        WorkView = WorkView
        FieldName = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
        SynchronizeWhenExit = True
      end
      object cbbDevType: TWVComboBox
        Left = 124
        Top = 161
        Width = 277
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '÷–Œƒ (ºÚÃÂ) - Œ¢»Ì∆¥“Ù'
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '…Ë±∏¿‡–Õ'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*221'
      end
      object edtBusiName: TWVEdit
        Left = 124
        Top = 92
        Width = 277
        Height = 20
        Enabled = False
        ParentColor = True
        ReadOnly = False
        TabOrder = 4
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 124
        Top = 196
        Width = 277
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 5
        Text = '<±∏◊¢>'
        WorkView = WorkView
        FieldName = '±∏◊¢'
        SynchronizeWhenExit = True
      end
      object pnlBusiQ: TPanel
        Left = 270
        Top = 56
        Width = 539
        Height = 353
        TabOrder = 6
        object Panel2: TPanel
          Left = 1
          Top = 1
          Width = 537
          Height = 79
          Align = alTop
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 0
          object Label9: TLabel
            Left = 230
            Top = 10
            Width = 60
            Height = 12
            Caption = '÷––ƒ…Ãªß∫≈'
          end
          object Label11: TLabel
            Left = 30
            Top = 34
            Width = 60
            Height = 12
            Caption = ' °…Ãªß±‡∫≈'
          end
          object Label12: TLabel
            Left = 42
            Top = 10
            Width = 48
            Height = 12
            Caption = '…Ãªß√˚≥∆'
          end
          object Label17: TLabel
            Left = 242
            Top = 58
            Width = 48
            Height = 12
            Caption = '…Ãªß¿‡–Õ'
          end
          object Label18: TLabel
            Left = 42
            Top = 58
            Width = 48
            Height = 12
            Caption = '––“µ¿‡–Õ'
          end
          object Label25: TLabel
            Left = 242
            Top = 34
            Width = 48
            Height = 12
            Caption = '…Ãªß◊¥Ã¨'
          end
          object WVEdit7: TWVEdit
            Left = 300
            Top = 6
            Width = 120
            Height = 20
            Color = clInfoBk
            ReadOnly = False
            TabOrder = 1
            Text = '<≤È—Ø.÷––ƒ…Ãªß∫≈>'
            WorkView = WorkView1
            FieldName = '≤È—Ø.÷––ƒ…Ãªß∫≈'
          end
          object WVEdit8: TWVEdit
            Left = 100
            Top = 30
            Width = 121
            Height = 20
            Color = clInfoBk
            ReadOnly = False
            TabOrder = 2
            Text = '<≤È—Ø. °…Ãªß±‡∫≈>'
            WorkView = WorkView1
            FieldName = '≤È—Ø. °…Ãªß±‡∫≈'
          end
          object WVEdit9: TWVEdit
            Left = 100
            Top = 6
            Width = 121
            Height = 20
            Color = clInfoBk
            ReadOnly = False
            TabOrder = 0
            Text = '<≤È—Ø.…Ãªß√˚>'
            WorkView = WorkView1
            FieldName = '≤È—Ø.…Ãªß√˚'
          end
          object WVComboBox8: TWVComboBox
            Left = 300
            Top = 30
            Width = 120
            Height = 20
            Style = csDropDownList
            Color = clInfoBk
            ImeName = '÷–Œƒ (ºÚÃÂ) - Œ¢»Ì∆¥“Ù'
            ItemHeight = 12
            TabOrder = 3
            WorkView = WorkView1
            FieldName = '≤È—Ø.…Ãªß◊¥Ã¨'
            DataPresentType = 'IDOBJECTS'
            SeperatedStr = '-'
            AutoDropDown = False
            ItemsDataEntry = '*224'
          end
          object WVComboBox1: TWVComboBox
            Left = 300
            Top = 54
            Width = 120
            Height = 20
            Style = csDropDownList
            Color = clInfoBk
            ImeName = '÷–Œƒ (ºÚÃÂ) - Œ¢»Ì∆¥“Ù'
            ItemHeight = 12
            TabOrder = 5
            WorkView = WorkView1
            FieldName = '≤È—Ø.…Ãªß¿‡–Õ'
            DataPresentType = 'IDOBJECTS'
            SeperatedStr = '-'
            AutoDropDown = False
            ItemsDataEntry = '*216'
          end
          object WVComboBox2: TWVComboBox
            Left = 100
            Top = 54
            Width = 121
            Height = 20
            Style = csDropDownList
            Color = clInfoBk
            ImeName = '÷–Œƒ (ºÚÃÂ) - Œ¢»Ì∆¥“Ù'
            ItemHeight = 12
            TabOrder = 4
            WorkView = WorkView1
            FieldName = '≤È—Ø.––“µ¿‡–Õ'
            DataPresentType = 'IDOBJECTS'
            SeperatedStr = '-'
            AutoDropDown = False
            ItemsDataEntry = '*217'
          end
          object btnQ: TButton
            Left = 436
            Top = 50
            Width = 65
            Height = 25
            Caption = '≤È —Ø'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = 'ÀŒÃÂ'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            OnClick = btnQClick
          end
        end
        object Grid1: TRzDBGrid
          Left = 1
          Top = 80
          Width = 537
          Height = 236
          Align = alClient
          Color = clWhite
          DataSource = DataSource1
          FixedColor = 15458000
          ImeName = '∆¥“Ùº”º”ºØ∫œ∞Ê'
          TabOrder = 1
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -12
          TitleFont.Name = 'ÀŒÃÂ'
          TitleFont.Style = []
          OnDrawColumnCell = Grid1DrawColumnCell
          OnDblClick = Grid1DblClick
          FrameColor = 12164479
          FrameStyle = fsGroove
          FrameVisible = True
          FixedLineColor = 12164479
          LineColor = clBackground
          Columns = <
            item
              Expanded = False
              FieldName = 'lvol0'
              Title.Alignment = taCenter
              Title.Caption = '…Ãªß±‡∫≈'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sname'
              Title.Alignment = taCenter
              Title.Caption = '÷––ƒ…Ãªß∫≈'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sname2'
              Title.Alignment = taCenter
              Title.Caption = ' °…Ãªß±‡∫≈'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'snote'
              Title.Alignment = taCenter
              Title.Caption = '…Ãªß√˚≥∆'
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'snote2'
              Title.Alignment = taCenter
              Title.Caption = '…Ãªß”¢Œƒ√˚≥∆'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail'
              Title.Alignment = taCenter
              Title.Caption = '…ÃªßºÚ≥∆'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sbranch_code0'
              Title.Alignment = taCenter
              Title.Caption = '…Ãªß¿‡–Õ'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sbranch_code1'
              Title.Alignment = taCenter
              Title.Caption = '––“µ¿‡–Õ'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sbankname'
              Title.Alignment = taCenter
              Title.Caption = '¡™œµ»À'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sphone'
              Title.Alignment = taCenter
              Title.Caption = 'µÁª∞'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sphone2'
              Title.Alignment = taCenter
              Title.Caption = ' ÷ª˙'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail2'
              Title.Alignment = taCenter
              Title.Caption = 'µÁ◊”–≈œ‰'
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sphone3'
              Title.Alignment = taCenter
              Title.Caption = '¥´’Ê'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'vsvarstr0'
              Title.Alignment = taCenter
              Title.Caption = '”™“µµÿ÷∑'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'spost_code'
              Title.Alignment = taCenter
              Title.Caption = '” ’˛±‡¬Î'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'damt0'
              Title.Alignment = taCenter
              Title.Caption = 'Ω·À„∑—¬ '
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'vsvarstr1'
              Title.Alignment = taCenter
              Title.Caption = 'ø™ªß“¯––'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'spager'
              Title.Alignment = taCenter
              Title.Caption = '“¯––’À∫≈'
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sbankname2'
              Title.Alignment = taCenter
              Title.Caption = '“¯––’ ªß√˚'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'scert_no'
              Title.Alignment = taCenter
              Title.Caption = '¡™––∫≈'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate0'
              Title.Alignment = taCenter
              Title.Caption = 'ø™ªß»’∆⁄'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate1'
              Title.Alignment = taCenter
              Title.Caption = 'œ˙ªß»’∆⁄'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sstatus1'
              Title.Alignment = taCenter
              Title.Caption = '…Ãªß◊¥Ã¨'
              Width = 70
              Visible = True
            end>
        end
        object pnl1: TPanel
          Left = 1
          Top = 316
          Width = 537
          Height = 36
          Align = alBottom
          TabOrder = 2
          object btnSelect: TButton
            Left = 392
            Top = 5
            Width = 65
            Height = 25
            Caption = '—°  ‘Ò'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = 'ÀŒÃÂ'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = btnSelectClick
          end
          object btnCan: TButton
            Left = 464
            Top = 5
            Width = 65
            Height = 25
            Caption = '»° œ˚'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = 'ÀŒÃÂ'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = btnCanClick
          end
        end
      end
      object edtBusiId: TWVEdit
        Left = 124
        Top = 57
        Width = 118
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<…Ãªß∫≈>'
        WorkView = WorkView
        FieldName = '…Ãªß∫≈'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 124
    Top = 295
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
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '≤È—Ø.…Ãªß∫≈'
        Caption = '≤È—Ø.…Ãªß∫≈'
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
        Name = '≤È—Ø.…Ë±∏÷’∂À–Ú¡–∫≈'
        Caption = '≤È—Ø.…Ë±∏÷’∂À–Ú¡–∫≈'
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
        Name = '≤È—Ø. °…Ë±∏÷’∂À–Ú¡–∫≈'
        Caption = '≤È—Ø. °…Ë±∏÷’∂À–Ú¡–∫≈'
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
        Name = '≤È—Ø.…Ë±∏¿‡–Õ'
        Caption = '≤È—Ø.…Ë±∏¿‡–Õ'
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
        Name = '≤È—Ø.◊¥Ã¨'
        Caption = '≤È—Ø.◊¥Ã¨'
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
        Name = '≤È—Ø.◊¢≤·»’∆⁄'
        Caption = '≤È—Ø.◊¢≤·»’∆⁄'
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
        Name = '≤È—Ø.∆Ù”√»’∆⁄'
        Caption = '≤È—Ø.∆Ù”√»’∆⁄'
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
        Name = '≤È—Ø.Õ£”√»’∆⁄'
        Caption = '≤È—Ø.Õ£”√»’∆⁄'
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
        Name = '…Ãªß∫≈'
        Caption = '…Ãªß∫≈'
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
        DataField = 'lvol0'
      end
      item
        Name = '…Ãªß√˚≥∆'
        Caption = '…Ãªß√˚≥∆'
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
        DataField = 'sall_name'
      end
      item
        Name = '…Ë±∏÷’∂À–Ú¡–∫≈'
        Caption = '…Ë±∏÷’∂À–Ú¡–∫≈'
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
        DataField = 'scust_auth'
      end
      item
        Name = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
        Caption = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
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
        DataField = 'scust_auth2'
      end
      item
        Name = '…Ë±∏¿‡–Õ'
        Caption = '…Ë±∏¿‡–Õ'
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
        DataField = 'sstock_code'
      end
      item
        Name = '◊¥Ã¨'
        Caption = '◊¥Ã¨'
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
        DataField = 'scurrency_type'
      end
      item
        Name = '◊¢≤·»’∆⁄'
        Caption = '◊¢≤·»’∆⁄'
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
        DataField = 'sdate0'
      end
      item
        Name = '∆Ù”√»’∆⁄'
        Caption = '∆Ù”√»’∆⁄'
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
        DataField = 'sdate1'
      end
      item
        Name = 'Õ£”√»’∆⁄'
        Caption = 'Õ£”√»’∆⁄'
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
        DataField = 'sdate2'
      end
      item
        Name = '∞Û∂®…Ë±∏±‡∫≈'
        Caption = '∞Û∂®…Ë±∏±‡∫≈'
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
        DataField = 'lvol1'
      end
      item
        Name = '±∏◊¢'
        Caption = '±∏◊¢'
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
        DataField = 'snote2'
      end
      item
        Name = '◊Ó∫Û∏¸–¬ ±º‰'
        Caption = '◊Ó∫Û∏¸–¬ ±º‰'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scust_limit2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|≤È—Ø.≤Ÿ◊˜±Í÷æ|≤È—Ø.…Ãªß∫≈|≤È—Ø.…Ë±∏÷’∂À–Ú¡–∫≈|≤È—Ø. °…Ë±∏÷’∂À–Ú' +
          '¡–∫≈|≤È—Ø.…Ë±∏¿‡–Õ|≤È—Ø.◊¥Ã¨|≤È—Ø.◊¢≤·»’∆⁄|≤È—Ø.∆Ù”√»’∆⁄|≤È—Ø.Õ£' +
          '”√»’∆⁄|'
      end
      item
        MonitorValueChangedFields = 
          '|…Ãªß∫≈|…Ãªß√˚≥∆|…Ë±∏÷’∂À–Ú¡–∫≈| |…Ë±∏¿‡–Õ|◊¥Ã¨|◊¢≤·»’∆⁄|∆Ù”√»’' +
          '∆⁄|Õ£”√»’∆⁄|∞Û∂®…Ë±∏±‡∫≈|±∏◊¢|'
      end>
    Left = 56
    Top = 264
  end
  inherited QueryRequest: TWVRequest
    ID = '…Ãªß…Ë±∏π‹¿Ì≤È—Ø'
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
        ParamName = '…Ãªß∫≈'
        FieldName = '≤È—Ø.…Ãªß∫≈'
        DefaultValue = 0
      end
      item
        ParamName = '…Ë±∏÷’∂À–Ú¡–∫≈'
        FieldName = '≤È—Ø.…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      item
        ParamName = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
        FieldName = '≤È—Ø. °…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      item
        ParamName = '…Ë±∏¿‡–Õ'
        FieldName = '≤È—Ø.…Ë±∏¿‡–Õ'
      end
      item
        ParamName = '◊¥Ã¨'
        FieldName = '≤È—Ø.◊¥Ã¨'
      end
      item
        ParamName = '◊¢≤·»’∆⁄'
        FieldName = '≤È—Ø.◊¢≤·»’∆⁄'
      end
      item
        ParamName = '∆Ù”√»’∆⁄'
        FieldName = '≤È—Ø.∆Ù”√»’∆⁄'
      end
      item
        ParamName = 'Õ£”√»’∆⁄'
        FieldName = '≤È—Ø.Õ£”√»’∆⁄'
      end>
    Left = 192
    Top = 264
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '≤È—ØΩ·π˚ºØ'
    Bindings = <
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '221'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '239'
      end>
    Left = 84
    Top = 295
  end
  inherited AddRequest: TWVRequest
    ID = '…Ãªß…Ë±∏π‹¿Ì'
    Bindings = <
      item
        ParamName = '…Ãªß∫≈'
        FieldName = '…Ãªß∫≈'
      end
      item
        ParamName = '…Ãªß√˚≥∆'
        FieldName = '…Ãªß√˚≥∆'
      end
      item
        ParamName = '…Ë±∏÷’∂À–Ú¡–∫≈'
        FieldName = '…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      item
        ParamName = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
        FieldName = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      item
        ParamName = '…Ë±∏¿‡–Õ'
        FieldName = '…Ë±∏¿‡–Õ'
      end
      item
        ParamName = '◊¥Ã¨'
        FieldName = '◊¥Ã¨'
      end
      item
        ParamName = '◊¢≤·»’∆⁄'
        FieldName = '◊¢≤·»’∆⁄'
      end
      item
        ParamName = '∆Ù”√»’∆⁄'
        FieldName = '∆Ù”√»’∆⁄'
      end
      item
        ParamName = 'Õ£”√»’∆⁄'
        FieldName = 'Õ£”√»’∆⁄'
      end
      item
        ParamName = '∞Û∂®…Ë±∏±‡∫≈'
        FieldName = '∞Û∂®…Ë±∏±‡∫≈'
      end
      item
        ParamName = '±∏◊¢'
        FieldName = '±∏◊¢'
      end
      item
        ParamName = '◊Ó∫Û∏¸–¬ ±º‰'
        FieldName = '◊Ó∫Û∏¸–¬ ±º‰'
      end
      item
        ParamName = '≤Ÿ◊˜±Í÷æ'
        FieldName = '≤Ÿ◊˜±Í÷æ'
      end>
    Left = 88
    Top = 264
  end
  inherited DeleteRequest: TWVRequest
    ID = '…Ãªß…Ë±∏π‹¿Ì'
    Bindings = <
      item
        ParamName = '…Ãªß∫≈'
        FieldName = '…Ãªß∫≈'
      end
      item
        ParamName = '…Ãªß√˚≥∆'
        FieldName = '…Ãªß√˚≥∆'
      end
      item
        ParamName = '…Ë±∏÷’∂À–Ú¡–∫≈'
        FieldName = '…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      item
        ParamName = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
        FieldName = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      item
        ParamName = '…Ë±∏¿‡–Õ'
        FieldName = '…Ë±∏¿‡–Õ'
      end
      item
        ParamName = '◊¥Ã¨'
        FieldName = '◊¥Ã¨'
      end
      item
        ParamName = '◊¢≤·»’∆⁄'
        FieldName = '◊¢≤·»’∆⁄'
      end
      item
        ParamName = '∆Ù”√»’∆⁄'
        FieldName = '∆Ù”√»’∆⁄'
      end
      item
        ParamName = 'Õ£”√»’∆⁄'
        FieldName = 'Õ£”√»’∆⁄'
      end
      item
        ParamName = '∞Û∂®…Ë±∏±‡∫≈'
        FieldName = '∞Û∂®…Ë±∏±‡∫≈'
      end
      item
        ParamName = '±∏◊¢'
        FieldName = '±∏◊¢'
      end
      item
        ParamName = '≤Ÿ◊˜±Í÷æ'
        FieldName = '≤Ÿ◊˜±Í÷æ'
      end>
    Left = 120
    Top = 264
  end
  inherited ChangeRequest: TWVRequest
    ID = '…Ãªß…Ë±∏π‹¿Ì'
    Bindings = <
      item
        ParamName = '…Ãªß∫≈'
        FieldName = '…Ãªß∫≈'
      end
      item
        ParamName = '…Ãªß√˚≥∆'
        FieldName = '…Ãªß√˚≥∆'
      end
      item
        ParamName = '…Ë±∏÷’∂À–Ú¡–∫≈'
        FieldName = '…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      item
        ParamName = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
        FieldName = ' °…Ë±∏÷’∂À–Ú¡–∫≈'
      end
      item
        ParamName = '…Ë±∏¿‡–Õ'
        FieldName = '…Ë±∏¿‡–Õ'
      end
      item
        ParamName = '◊¥Ã¨'
        FieldName = '◊¥Ã¨'
      end
      item
        ParamName = '◊¢≤·»’∆⁄'
        FieldName = '◊¢≤·»’∆⁄'
      end
      item
        ParamName = '∆Ù”√»’∆⁄'
        FieldName = '∆Ù”√»’∆⁄'
      end
      item
        ParamName = 'Õ£”√»’∆⁄'
        FieldName = 'Õ£”√»’∆⁄'
      end
      item
        ParamName = '∞Û∂®…Ë±∏±‡∫≈'
        FieldName = '∞Û∂®…Ë±∏±‡∫≈'
      end
      item
        ParamName = '±∏◊¢'
        FieldName = '±∏◊¢'
      end
      item
        ParamName = '◊Ó∫Û∏¸–¬ ±º‰'
        FieldName = '◊Ó∫Û∏¸–¬ ±º‰'
      end
      item
        ParamName = '≤Ÿ◊˜±Í÷æ'
        FieldName = '≤Ÿ◊˜±Í÷æ'
      end>
    Left = 152
    Top = 264
  end
  inherited WVDataSource: TWVDataSource
    Left = 156
    Top = 303
  end
  inherited alDatasetActions: TActionList
    Left = 196
    Top = 300
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '…Ãªß–≈œ¢Œ¨ª§≤È—Ø'
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
        ParamName = '…Ãªß±‡∫≈'
        FieldName = '≤È—Ø.…Ãªß±‡∫≈'
        DefaultValue = 0
      end
      item
        ParamName = '÷––ƒ…Ãªß∫≈'
        FieldName = '≤È—Ø.÷––ƒ…Ãªß∫≈'
      end
      item
        ParamName = '…Ãªß◊¥Ã¨'
        FieldName = '≤È—Ø.…Ãªß◊¥Ã¨'
      end
      item
        ParamName = ' °…Ãªß±‡∫≈'
        FieldName = '≤È—Ø. °…Ãªß±‡∫≈'
      end
      item
        ParamName = '…Ãªß√˚'
        FieldName = '≤È—Ø.…Ãªß√˚'
      end
      item
        ParamName = '…Ãªß”¢Œƒ√˚≥∆'
        FieldName = '≤È—Ø.…Ãªß”¢Œƒ√˚≥∆'
      end
      item
        ParamName = '…ÃªßºÚ≥∆'
        FieldName = '≤È—Ø.…ÃªßºÚ≥∆'
      end
      item
        ParamName = '…Ãªß¿‡–Õ'
        FieldName = '≤È—Ø.…Ãªß¿‡–Õ'
      end
      item
        ParamName = '––“µ¿‡–Õ'
        FieldName = '≤È—Ø.––“µ¿‡–Õ'
      end>
    AfterExec = CheckReturnData
    Left = 400
    Top = 8
  end
  object WorkView1: TWorkView
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
        Name = '≤Ÿ◊˜¿‡±.‘ˆº”'
        Caption = '≤Ÿ◊˜¿‡±.‘ˆº”'
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
        Name = '≤Ÿ◊˜¿‡±.…æ≥˝'
        Caption = '≤Ÿ◊˜¿‡±.…æ≥˝'
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
        Name = '≤Ÿ◊˜¿‡±.–ﬁ∏ƒ'
        Caption = '≤Ÿ◊˜¿‡±.–ﬁ∏ƒ'
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
        Name = '≤Ÿ◊˜±Í÷æ'
        Caption = '≤Ÿ◊˜±Í÷æ'
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
        Name = '≤È—Ø.…Ãªß±‡∫≈'
        Caption = '≤È—Ø.…Ãªß±‡∫≈'
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
        Name = '≤È—Ø.÷––ƒ…Ãªß∫≈'
        Caption = '≤È—Ø.÷––ƒ…Ãªß∫≈'
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
        Name = '≤È—Ø.…Ãªß◊¥Ã¨'
        Caption = '≤È—Ø.…Ãªß◊¥Ã¨'
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
        Name = '≤È—Ø. °…Ãªß±‡∫≈'
        Caption = '≤È—Ø. °…Ãªß±‡∫≈'
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
        Name = '≤È—Ø.…Ãªß√˚'
        Caption = '≤È—Ø.…Ãªß√˚'
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
        Name = '≤È—Ø.…Ãªß”¢Œƒ√˚≥∆'
        Caption = '≤È—Ø.…Ãªß”¢Œƒ√˚≥∆'
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
        Name = '≤È—Ø.…ÃªßºÚ≥∆'
        Caption = '≤È—Ø.…ÃªßºÚ≥∆'
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
        Name = '≤È—Ø.…Ãªß¿‡–Õ'
        Caption = '≤È—Ø.…Ãªß¿‡–Õ'
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
        Name = '≤È—Ø.––“µ¿‡–Õ'
        Caption = '≤È—Ø.––“µ¿‡–Õ'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|≤È—Ø.≤Ÿ◊˜±Í÷æ|≤È—Ø.…Ãªß±‡∫≈|≤È—Ø.÷––ƒ…Ãªß∫≈|≤È—Ø. °…Ãªß±‡∫≈|≤È' +
          '—Ø.…Ãªß√˚|≤È—Ø.…Ãªß”¢Œƒ√˚≥∆|≤È—Ø.…ÃªßºÚ≥∆|≤È—Ø.…Ãªß¿‡–Õ|≤È—Ø.––' +
          '“µ¿‡–Õ|≤È—Ø.¡™œµ»À|≤È—Ø.µÁª∞|≤È—Ø. ÷ª˙|≤È—Ø.µÁ◊”–≈œ‰|≤È—Ø.¥´’Ê|' +
          '≤È—Ø.”™“µµÿ÷∑|≤È—Ø.” ’˛±‡¬Î|≤È—Ø.Ω·À„∑—¬ |≤È—Ø.ø™ªß“¯––|≤È—Ø.“¯' +
          '––’À∫≈|≤È—Ø.“¯––’ ªß√˚|≤È—Ø.¡™––∫≈|≤È—Ø.ø™ªß»’∆⁄|≤È—Ø.œ˙ªß»’∆⁄|' +
          '≤È—Ø.œ˙ªß◊¥Ã¨|≤È—Ø.…Ãªß◊¥Ã¨|'
      end
      item
        MonitorValueChangedFields = 
          '|…Ãªß±‡∫≈|÷––ƒ…Ãªß∫≈| °…Ãªß±‡∫≈|…Ãªß√˚|…Ãªß”¢Œƒ√˚≥∆|…ÃªßºÚ≥∆|…Ã' +
          'ªß¿‡–Õ|––“µ¿‡–Õ|¡™œµ»À|µÁª∞| ÷ª˙|µÁ◊”–≈œ‰|¥´’Ê|”™“µµÿ÷∑|” ’˛±‡¬Î' +
          '|Ω·À„∑—¬ |ø™ªß“¯––|“¯––’À∫≈|“¯––’ ªß√˚|¡™––∫≈|ø™ªß»’∆⁄|œ˙ªß»’∆⁄|' +
          'œ˙ªß◊¥Ã¨|'
      end>
    Left = 368
    Top = 8
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView1
    FieldName = '≤È—ØΩ·π˚ºØ'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        WVFieldName = '…Ãªß¿‡–Õ'
        DataPresentType = 'idobjects'
        DataPresentParam = '216'
      end
      item
        FieldName = 'sbranch_code1'
        WVFieldName = '––“µ¿‡–Õ'
        DataPresentType = 'idobjects'
        DataPresentParam = '217'
      end
      item
        FieldName = 'sstatus1'
        WVFieldName = '…Ãªß◊¥Ã¨'
        DataPresentType = 'idobjects'
        DataPresentParam = '224'
      end>
    HideUnbindingFields = False
    Left = 436
    Top = 7
  end
  object DataSource1: TDataSource
    OnStateChange = DataSourceStateChange
    OnDataChange = DataSourceDataChange
    Left = 468
    Top = 7
  end
end

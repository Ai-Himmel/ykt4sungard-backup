object datreplistfrm: Tdatreplistfrm
  Left = 224
  Top = 141
  Width = 1000
  Height = 593
  Caption = #26085#25253#34920#26597#35810
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 992
    Height = 559
    Align = alClient
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 990
      Height = 32
      Align = alTop
      TabOrder = 0
      object Label1: TLabel
        Left = 398
        Top = 8
        Width = 66
        Height = 16
        Caption = #26085#25253#34920#26597#35810
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 33
      Width = 990
      Height = 439
      Align = alClient
      TabOrder = 1
      object DBGrid1: TDBGrid
        Left = 1
        Top = 1
        Width = 988
        Height = 437
        Align = alClient
        DataSource = DataSource1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
        ReadOnly = True
        TabOrder = 0
        TitleFont.Charset = GB2312_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -16
        TitleFont.Name = #23435#20307
        TitleFont.Style = []
        OnDblClick = DBGrid1DblClick
        Columns = <
          item
            Expanded = False
            FieldName = 'OPERCODE'
            Title.Caption = #21307#29983#20195#30721
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'OPERNAME'
            Title.Caption = #21307#29983#22995#21517
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'STUEMPNO'
            Title.Caption = #23398#24037#21495
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'CUSTNAME'
            Title.Caption = #22995#21517
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'CUSTTYPENAME'
            Title.Caption = #23458#25143#31867#22411' '
            Width = 84
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sexname'
            Title.Caption = #24615#21035
            Width = 40
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'TRANSAMT'
            ImeName = 'TRANSAMT'
            Title.Caption = #32564#36153#37329#39069
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'TRANSDATE'
            Title.Caption = #32564#36153#26085#26399
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'VOUCHERNO'
            Title.Caption = #22788#26041#32534#21495
            Visible = True
          end>
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 472
      Width = 990
      Height = 86
      Align = alBottom
      TabOrder = 2
      object Label14: TLabel
        Left = 14
        Top = 16
        Width = 80
        Height = 16
        Caption = #21307#29983#20195#30721#65306
      end
      object stuno: TLabel
        Left = 286
        Top = 14
        Width = 64
        Height = 16
        Caption = #23398#24037#21495#65306
      end
      object Label12: TLabel
        Left = 12
        Top = 55
        Width = 80
        Height = 16
        Caption = #24320#22987#26085#26399#65306
      end
      object Label13: TLabel
        Left = 274
        Top = 58
        Width = 80
        Height = 16
        Caption = #32467#26463#26085#26399#65306
      end
      object Button1: TButton
        Left = 606
        Top = 48
        Width = 59
        Height = 25
        Caption = #19978#19968#39029
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 674
        Top = 49
        Width = 61
        Height = 25
        Caption = #19979#19968#39029
        TabOrder = 1
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 828
        Top = 49
        Width = 75
        Height = 24
        Caption = #36820#22238
        TabOrder = 2
        OnClick = Button3Click
      end
      object doctor: TEdit
        Left = 84
        Top = 10
        Width = 157
        Height = 24
        TabOrder = 3
        Text = 'doctor'
      end
      object studentno: TEdit
        Left = 361
        Top = 9
        Width = 152
        Height = 24
        TabOrder = 4
        Text = 'studentno'
      end
      object oldbegdate: TDateTimePicker
        Left = 83
        Top = 50
        Width = 158
        Height = 24
        Date = 40100.000000000000000000
        Time = 40100.000000000000000000
        DateFormat = dfLong
        TabOrder = 5
      end
      object oldenddate: TDateTimePicker
        Left = 361
        Top = 50
        Width = 153
        Height = 24
        Date = 40100.000000000000000000
        Time = 40100.000000000000000000
        DateFormat = dfLong
        TabOrder = 6
      end
      object Button4: TButton
        Left = 527
        Top = 48
        Width = 66
        Height = 25
        Caption = #21382#21490#26597#35810
        TabOrder = 7
        OnClick = Button4Click
      end
      object outexcel: TButton
        Left = 744
        Top = 49
        Width = 73
        Height = 25
        Caption = #23548#20986'excel'
        TabOrder = 8
        OnClick = outexcelClick
      end
    end
  end
  object DataSource1: TDataSource
    Left = 169
    Top = 113
  end
  object SaveDialog1: TSaveDialog
    Filter = '.xls|excel '#25991#20214
    Left = 129
    Top = 113
  end
end

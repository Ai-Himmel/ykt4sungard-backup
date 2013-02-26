object inppatfrm: Tinppatfrm
  Left = 249
  Top = 120
  Width = 992
  Height = 644
  Caption = 'inppatfrm'
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #23435#20307
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 984
    Height = 610
    Align = alClient
    TabOrder = 0
    object title: TPanel
      Left = 1
      Top = 1
      Width = 982
      Height = 32
      Align = alTop
      TabOrder = 0
      object labletaitle: TLabel
        Left = 356
        Top = 5
        Width = 66
        Height = 16
        Caption = #25910#36153#30331#35760#34920
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object Panel2: TPanel
      Left = 1
      Top = 33
      Width = 982
      Height = 216
      Align = alTop
      TabOrder = 1
      object ucCardNoname: TLabel
        Left = 30
        Top = 35
        Width = 64
        Height = 16
        Caption = #23398#24037#21495#65306
      end
      object Label1: TLabel
        Left = 26
        Top = 10
        Width = 103
        Height = 13
        Caption = #24739#32773#22522#26412#20449#24687'      '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label2: TLabel
        Left = 44
        Top = 54
        Width = 48
        Height = 16
        Caption = #22995#21517#65306
      end
      object Label3: TLabel
        Left = 44
        Top = 73
        Width = 48
        Height = 16
        Caption = #24615#21035#65306
      end
      object Label4: TLabel
        Left = 16
        Top = 91
        Width = 80
        Height = 16
        Caption = #23458#25143#31867#21035#65306
      end
      object Label5: TLabel
        Left = 16
        Top = 112
        Width = 80
        Height = 16
        Caption = #25152#22312#37096#38376#65306
      end
      object Label6: TLabel
        Left = 30
        Top = 131
        Width = 64
        Height = 16
        Caption = #21345#29366#24577#65306
      end
      object Label7: TLabel
        Left = 30
        Top = 149
        Width = 64
        Height = 16
        Caption = #21345#20313#39069#65306
      end
      object Label8: TLabel
        Left = 16
        Top = 170
        Width = 80
        Height = 16
        Caption = #21345#26377#25928#26399#65306
      end
      object ucCardNo: TLabel
        Left = 96
        Top = 32
        Width = 64
        Height = 16
        Caption = 'ucCardNo'
      end
      object ucName: TLabel
        Left = 96
        Top = 51
        Width = 48
        Height = 16
        Caption = 'ucName'
      end
      object ucSexNo: TLabel
        Left = 96
        Top = 72
        Width = 56
        Height = 16
        Caption = 'ucSexNo'
      end
      object ucIdentifyNo: TLabel
        Left = 96
        Top = 90
        Width = 96
        Height = 16
        Caption = 'ucIdentifyNo'
      end
      object ucDepartmentNo: TLabel
        Left = 96
        Top = 108
        Width = 112
        Height = 16
        Caption = 'ucDepartmentNo'
      end
      object STATUS: TLabel
        Left = 96
        Top = 128
        Width = 48
        Height = 16
        Caption = 'STATUS'
      end
      object readMoney: TLabel
        Left = 96
        Top = 147
        Width = 72
        Height = 16
        Caption = 'readMoney'
      end
      object DeadLineDate: TLabel
        Left = 96
        Top = 169
        Width = 96
        Height = 16
        Caption = 'DeadLineDate'
      end
      object Panel5: TPanel
        Left = 599
        Top = 1
        Width = 382
        Height = 214
        Align = alRight
        TabOrder = 0
        object Panel6: TPanel
          Left = 1
          Top = 1
          Width = 184
          Height = 212
          Align = alLeft
          TabOrder = 0
          object Image1: TImage
            Left = 1
            Top = 1
            Width = 182
            Height = 210
            Align = alClient
            Stretch = True
          end
        end
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 249
      Width = 982
      Height = 143
      Align = alClient
      TabOrder = 2
      object Memo1: TMemo
        Left = 1
        Top = 25
        Width = 980
        Height = 117
        Align = alClient
        Lines.Strings = (
          'Memo1')
        TabOrder = 0
      end
      object Panel7: TPanel
        Left = 1
        Top = 1
        Width = 980
        Height = 24
        Align = alTop
        TabOrder = 1
        object Label9: TLabel
          Left = 25
          Top = 5
          Width = 95
          Height = 13
          Caption = #26412#27425#23601#21307#24773#20917'    '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object noname: TLabel
          Left = 398
          Top = 5
          Width = 64
          Height = 16
          Caption = #22788#26041#21495#65306
        end
        object noid: TLabel
          Left = 475
          Top = 5
          Width = 32
          Height = 16
          Caption = 'noid'
        end
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 392
      Width = 982
      Height = 217
      Align = alBottom
      TabOrder = 3
      object Label11: TLabel
        Left = 43
        Top = 189
        Width = 80
        Height = 16
        Caption = #32564#36153#37329#39069#65306
      end
      object Panel8: TPanel
        Left = 1
        Top = 1
        Width = 980
        Height = 24
        Align = alTop
        TabOrder = 0
        object Label10: TLabel
          Left = 26
          Top = 4
          Width = 69
          Height = 13
          Caption = #25152#24320#33647#21697'    '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object Panel9: TPanel
        Left = 1
        Top = 25
        Width = 980
        Height = 144
        Align = alTop
        TabOrder = 1
        object Memo2: TMemo
          Left = 1
          Top = 1
          Width = 978
          Height = 142
          Align = alClient
          Lines.Strings = (
            'Memo1')
          TabOrder = 0
        end
      end
      object changgemoney: TEdit
        Left = 130
        Top = 184
        Width = 169
        Height = 24
        TabOrder = 2
        Text = '100'
      end
      object cancel: TButton
        Left = 679
        Top = 181
        Width = 65
        Height = 25
        Caption = #36820#22238
        TabOrder = 3
        OnClick = cancelClick
      end
    end
  end
end

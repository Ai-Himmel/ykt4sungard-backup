object FrmPersonWrite: TFrmPersonWrite
  Left = 247
  Top = 130
  Width = 575
  Height = 251
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = '��Ա��Ϣ¼��'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 567
    Height = 217
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object grpMast: TGroupBox
      Left = 0
      Top = 16
      Width = 567
      Height = 81
      Caption = '����¼����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object lblNo: TLabel
        Left = 16
        Top = 24
        Width = 49
        Height = 13
        AutoSize = False
        Caption = 'ѧ���ţ�'
      end
      object lblName: TLabel
        Left = 196
        Top = 24
        Width = 49
        Height = 13
        AutoSize = False
        Caption = '��  ����'
      end
      object lbltype: TLabel
        Left = 16
        Top = 56
        Width = 49
        Height = 13
        AutoSize = False
        Caption = '��  ��'
      end
      object lblDep: TLabel
        Left = 184
        Top = 56
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'һ����λ��'
      end
      object lblsex: TLabel
        Left = 376
        Top = 24
        Width = 53
        Height = 13
        AutoSize = False
        Caption = '��  ��'
      end
      object edtNo: TEdit
        Left = 64
        Top = 20
        Width = 113
        Height = 21
        TabOrder = 0
      end
      object edtName: TEdit
        Left = 240
        Top = 20
        Width = 129
        Height = 21
        TabOrder = 1
      end
      object cbbType: TComboBox
        Left = 64
        Top = 50
        Width = 113
        Height = 21
        ItemHeight = 13
        TabOrder = 3
      end
      object cbbDep: TComboBox
        Left = 240
        Top = 50
        Width = 129
        Height = 21
        ItemHeight = 13
        TabOrder = 4
      end
      object cbbsex: TComboBox
        Left = 424
        Top = 18
        Width = 113
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        Items.Strings = (
          '-'
          '��'
          'Ů')
      end
    end
    object grpother: TGroupBox
      Left = 0
      Top = 97
      Width = 567
      Height = 64
      Caption = 'ѡ����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object lbldep2: TLabel
        Left = 5
        Top = 24
        Width = 65
        Height = 13
        AutoSize = False
        Caption = '������λ��'
      end
      object lblIDCard: TLabel
        Left = 185
        Top = 24
        Width = 61
        Height = 13
        AutoSize = False
        Caption = '���֤�ţ�'
      end
      object lblGrade: TLabel
        Left = 376
        Top = 24
        Width = 49
        Height = 13
        AutoSize = False
        Caption = '��  ����'
      end
      object cbbdep2: TComboBox
        Left = 64
        Top = 18
        Width = 113
        Height = 21
        ItemHeight = 13
        TabOrder = 0
      end
      object edtIDCard: TEdit
        Left = 240
        Top = 20
        Width = 129
        Height = 21
        TabOrder = 1
      end
      object cbbGrade: TComboBox
        Left = 424
        Top = 18
        Width = 113
        Height = 21
        ItemHeight = 13
        TabOrder = 2
      end
    end
    object btnSave: TButton
      Left = 368
      Top = 176
      Width = 75
      Height = 25
      Caption = '�� ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = btnSaveClick
    end
    object btnExit: TButton
      Left = 456
      Top = 176
      Width = 75
      Height = 25
      Caption = '�� ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = btnExitClick
    end
  end
  object qryExecSQL: TADOQuery
    Connection = dm.ConnectPhoto
    Parameters = <>
    Left = 48
    Top = 137
  end
end

object SetPix: TSetPix
  Left = 348
  Top = 273
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '����'
  ClientHeight = 164
  ClientWidth = 412
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 32
    Width = 60
    Height = 13
    Caption = '��Ƭ��С��'
  end
  object Label2: TLabel
    Left = 200
    Top = 32
    Width = 24
    Height = 13
    Caption = '���'
  end
  object Label3: TLabel
    Left = 24
    Top = 8
    Width = 65
    Height = 13
    AutoSize = False
    Caption = '��λ��MM'
  end
  object Label4: TLabel
    Left = 24
    Top = 64
    Width = 60
    Height = 13
    Caption = '��Ƭλ�ã�'
  end
  object Label5: TLabel
    Left = 189
    Top = 64
    Width = 36
    Height = 13
    Caption = '��߾�'
  end
  object Label6: TLabel
    Left = 88
    Top = 64
    Width = 36
    Height = 13
    Caption = '�ϱ߾�'
  end
  object Label7: TLabel
    Left = 99
    Top = 32
    Width = 24
    Height = 17
    AutoSize = False
    Caption = '�߶�'
  end
  object Edit1: TEdit
    Left = 128
    Top = 28
    Width = 49
    Height = 21
    ImeName = '���� (����) - ΢��ƴ��'
    TabOrder = 0
    OnExit = Edit1Exit
  end
  object Edit2: TEdit
    Left = 232
    Top = 28
    Width = 49
    Height = 21
    ImeName = '���� (����) - ΢��ƴ��'
    TabOrder = 1
    OnExit = Edit2Exit
  end
  object Button1: TButton
    Left = 80
    Top = 128
    Width = 75
    Height = 25
    Caption = 'ȷ��'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 168
    Top = 128
    Width = 75
    Height = 25
    Caption = 'Ӧ��'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 304
    Top = 128
    Width = 75
    Height = 25
    Caption = 'ȡ��'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = Button3Click
  end
  object Edit3: TEdit
    Left = 128
    Top = 59
    Width = 49
    Height = 21
    ImeName = '���� (����) - ΢��ƴ��'
    TabOrder = 5
  end
  object Edit4: TEdit
    Left = 232
    Top = 59
    Width = 49
    Height = 21
    ImeName = '���� (����) - ΢��ƴ��'
    TabOrder = 6
  end
  object CheckBox1: TCheckBox
    Left = 312
    Top = 32
    Width = 57
    Height = 17
    Caption = '������'
    Checked = True
    State = cbChecked
    TabOrder = 7
  end
  object CheckBox2: TCheckBox
    Left = 16
    Top = 91
    Width = 361
    Height = 22
    Caption = '����ӡ"������Ժϵ��רҵ����λ��ѧ����"����ʾ�ֶ�'
    TabOrder = 8
  end
end

object frmFieldLink: TfrmFieldLink
  Left = 384
  Top = 210
  BorderStyle = bsNone
  Caption = '�ֶζԽ�'
  ClientHeight = 327
  ClientWidth = 504
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '����'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  PixelsPerInch = 96
  TextHeight = 12
  object Label1: TLabel
    Left = 16
    Top = 14
    Width = 186
    Height = 12
    Caption = '��������ֶζԽ� --- ���ĸ�����'
  end
  object Shape1: TShape
    Left = 16
    Top = 30
    Width = 187
    Height = 1
    Brush.Style = bsClear
    Pen.Color = clTeal
    Pen.Style = psInsideFrame
  end
  object Shape2: TShape
    Left = 16
    Top = 33
    Width = 187
    Height = 1
    Brush.Style = bsClear
    Pen.Color = clTeal
    Pen.Style = psInsideFrame
  end
  object gbDataLink: TGroupBox
    Left = 32
    Top = 46
    Width = 433
    Height = 267
    Caption = ' �ֶζԽ� '
    TabOrder = 0
    object Label2: TLabel
      Left = 71
      Top = 24
      Width = 72
      Height = 12
      Caption = '���������ֶ�'
    end
    object Label3: TLabel
      Left = 239
      Top = 24
      Width = 72
      Height = 12
      Caption = 'ƥ�������ֶ�'
    end
    object sbDataLink: TScrollBox
      Left = 35
      Top = 44
      Width = 361
      Height = 171
      TabOrder = 0
      object lbFields: TListBox
        Left = 200
        Top = 9
        Width = 121
        Height = 147
        Enabled = False
        ItemHeight = 12
        TabOrder = 0
      end
      object clbFields: TCheckListBox
        Left = 32
        Top = 9
        Width = 121
        Height = 147
        OnClickCheck = clbFieldsClickCheck
        ItemHeight = 12
        TabOrder = 1
        OnClick = clbFieldsClick
      end
    end
    object edtField: TEdit
      Left = 35
      Top = 233
      Width = 89
      Height = 20
      Enabled = False
      TabOrder = 1
    end
    object cbField: TComboBox
      Left = 133
      Top = 233
      Width = 113
      Height = 20
      ItemHeight = 12
      TabOrder = 2
    end
    object btnMatch: TButton
      Left = 255
      Top = 228
      Width = 65
      Height = 25
      Caption = 'ƥ��'
      TabOrder = 3
      OnClick = btnMatchClick
    end
    object btnClear: TButton
      Left = 332
      Top = 228
      Width = 65
      Height = 25
      Caption = '���'
      TabOrder = 4
      OnClick = btnClearClick
    end
  end
end

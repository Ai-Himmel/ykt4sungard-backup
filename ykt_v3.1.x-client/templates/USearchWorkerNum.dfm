object QueryWorkerNum: TQueryWorkerNum
  Left = 279
  Top = 245
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Ա����Ϣ��ѯ'
  ClientHeight = 280
  ClientWidth = 591
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 41
    Height = 13
    AutoSize = False
    Caption = 'Ա����'
  end
  object Label2: TLabel
    Left = 168
    Top = 16
    Width = 33
    Height = 13
    AutoSize = False
    Caption = '����'
  end
  object Label3: TLabel
    Left = 304
    Top = 16
    Width = 57
    Height = 13
    AutoSize = False
    Caption = '���֤��'
  end
  object WorkerDBGrid: TDBGrid
    Left = 8
    Top = 40
    Width = 569
    Height = 225
    ImeName = ''
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnCellClick = WorkerDBGridCellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'sname2'
        Title.Alignment = taCenter
        Title.Caption = 'Ա����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        Title.Alignment = taCenter
        Title.Caption = '����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol0'
        Title.Alignment = taCenter
        Title.Caption = 'Ա��״̬'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_no'
        Title.Alignment = taCenter
        Title.Caption = '��λ����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth'
        Title.Alignment = taCenter
        Title.Caption = '���֤��'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        Title.Alignment = taCenter
        Title.Caption = 'ְ�ƴ���'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol3'
        Title.Alignment = taCenter
        Title.Caption = '������ò'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'smarket_code'
        Title.Alignment = taCenter
        Title.Caption = '�Ա�'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth2'
        Title.Alignment = taCenter
        Title.Caption = '��ϵ�绰'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol4'
        Title.Alignment = taCenter
        Title.Caption = 'Ա�����'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scusttypes'
        Title.Alignment = taCenter
        Title.Caption = '��ϵ��ַ'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ssectypes'
        Title.Alignment = taCenter
        Title.Caption = '��ע'
        Visible = True
      end>
  end
  object Button1: TButton
    Left = 504
    Top = 8
    Width = 75
    Height = 25
    Caption = '�� ��'
    TabOrder = 1
    OnClick = Button1Click
  end
  object WVEdit1: TWVEdit
    Left = 56
    Top = 8
    Width = 89
    Height = 21
    ImeName = ''
    ReadOnly = False
    TabOrder = 2
  end
  object WVEdit2: TWVEdit
    Left = 208
    Top = 8
    Width = 81
    Height = 21
    ImeName = ''
    ReadOnly = False
    TabOrder = 3
  end
  object WVEdit3: TWVEdit
    Left = 368
    Top = 8
    Width = 121
    Height = 21
    ImeName = ''
    ReadOnly = False
    TabOrder = 4
  end
end

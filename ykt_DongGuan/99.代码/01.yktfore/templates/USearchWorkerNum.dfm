object QueryWorkerNum: TQueryWorkerNum
  Left = 279
  Top = 245
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '员工信息查询'
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
    Caption = '员工号'
  end
  object Label2: TLabel
    Left = 168
    Top = 16
    Width = 33
    Height = 13
    AutoSize = False
    Caption = '姓名'
  end
  object Label3: TLabel
    Left = 304
    Top = 16
    Width = 57
    Height = 13
    AutoSize = False
    Caption = '身份证号'
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
        Title.Caption = '员工号'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        Title.Alignment = taCenter
        Title.Caption = '姓名'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol0'
        Title.Alignment = taCenter
        Title.Caption = '员工状态'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_no'
        Title.Alignment = taCenter
        Title.Caption = '单位代码'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth'
        Title.Alignment = taCenter
        Title.Caption = '身份证号'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        Title.Alignment = taCenter
        Title.Caption = '职称代码'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol3'
        Title.Alignment = taCenter
        Title.Caption = '政治面貌'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'smarket_code'
        Title.Alignment = taCenter
        Title.Caption = '性别'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth2'
        Title.Alignment = taCenter
        Title.Caption = '联系电话'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol4'
        Title.Alignment = taCenter
        Title.Caption = '员工类别'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scusttypes'
        Title.Alignment = taCenter
        Title.Caption = '联系地址'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ssectypes'
        Title.Alignment = taCenter
        Title.Caption = '备注'
        Visible = True
      end>
  end
  object Button1: TButton
    Left = 504
    Top = 8
    Width = 75
    Height = 25
    Caption = '检 索'
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

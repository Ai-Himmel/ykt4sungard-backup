object frmBatchDelete: TfrmBatchDelete
  Left = 294
  Top = 125
  Width = 686
  Height = 483
  BorderIcons = [biMaximize]
  Caption = '批量删除'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object lblTotlal: TLabel
    Left = 568
    Top = 136
    Width = 70
    Height = 14
    Caption = '共  条记录'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 649
    Height = 105
    Caption = '查询条件'
    TabOrder = 0
    object Label6: TLabel
      Left = 32
      Top = 19
      Width = 63
      Height = 14
      Caption = '学    号:'
    end
    object Label8: TLabel
      Left = 32
      Top = 47
      Width = 63
      Height = 14
      Caption = '一级单位:'
    end
    object Label9: TLabel
      Left = 232
      Top = 19
      Width = 63
      Height = 14
      Caption = '姓    名:'
    end
    object Label10: TLabel
      Left = 232
      Top = 47
      Width = 63
      Height = 14
      Caption = '二级单位:'
    end
    object Label11: TLabel
      Left = 432
      Top = 47
      Width = 63
      Height = 14
      Caption = '年    级:'
    end
    object Label12: TLabel
      Left = 432
      Top = 19
      Width = 63
      Height = 14
      Caption = '类    别:'
    end
    object Label1: TLabel
      Left = 256
      Top = 80
      Width = 14
      Height = 14
      Caption = '自'
    end
    object Label2: TLabel
      Left = 456
      Top = 80
      Width = 14
      Height = 14
      Caption = '至'
    end
    object edtNum: TEdit
      Left = 96
      Top = 19
      Width = 113
      Height = 22
      TabOrder = 0
    end
    object cbDept: TComboBox
      Left = 96
      Top = 47
      Width = 113
      Height = 20
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 1
    end
    object edtName: TEdit
      Left = 296
      Top = 19
      Width = 113
      Height = 22
      TabOrder = 2
    end
    object cbSubDept: TComboBox
      Left = 296
      Top = 47
      Width = 113
      Height = 22
      ItemHeight = 14
      TabOrder = 3
    end
    object cbGrade: TComboBox
      Left = 496
      Top = 47
      Width = 113
      Height = 22
      ItemHeight = 14
      TabOrder = 4
    end
    object cbType: TComboBox
      Left = 496
      Top = 19
      Width = 113
      Height = 22
      ItemHeight = 14
      TabOrder = 5
    end
    object dtpFromDate: TDateTimePicker
      Left = 296
      Top = 76
      Width = 113
      Height = 22
      CalAlignment = dtaLeft
      Date = 38455.7226207986
      Time = 38455.7226207986
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = '拼音加加集合版'
      Kind = dtkDate
      ParseInput = False
      TabOrder = 6
    end
    object dtpToDate: TDateTimePicker
      Left = 496
      Top = 76
      Width = 113
      Height = 22
      CalAlignment = dtaLeft
      Date = 38455.7231351273
      Time = 38455.7231351273
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = '拼音加加集合版'
      Kind = dtkDate
      ParseInput = False
      TabOrder = 7
    end
  end
  object btnQuery: TButton
    Left = 24
    Top = 128
    Width = 75
    Height = 25
    Caption = '查询'
    TabOrder = 1
    OnClick = btnQueryClick
  end
  object btnDelete: TButton
    Left = 16
    Top = 411
    Width = 75
    Height = 25
    Caption = '删除'
    TabOrder = 2
    OnClick = btnDeleteClick
  end
  object btnCancel: TButton
    Left = 590
    Top = 411
    Width = 75
    Height = 25
    Caption = '退出'
    TabOrder = 3
    OnClick = btnCancelClick
  end
  object DBGridEh1: TDBGridEh
    Left = 16
    Top = 160
    Width = 649
    Height = 241
    DataSource = DataSource
    FooterColor = clWindow
    FooterFont.Charset = ANSI_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -14
    FooterFont.Name = '宋体'
    FooterFont.Style = []
    TabOrder = 4
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -14
    TitleFont.Name = '宋体'
    TitleFont.Style = []
    Columns = <
      item
        EditButtons = <>
        FieldName = 'CUT_TYPE'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '类别'
        Width = 49
      end
      item
        EditButtons = <>
        FieldName = 'STUEMP_NO'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '学号/工号'
        Width = 73
      end
      item
        EditButtons = <>
        FieldName = 'STUEMP_NAME'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '姓名'
        Width = 54
      end
      item
        EditButtons = <>
        FieldName = 'SEX_NAME'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '性别'
        Width = 32
      end
      item
        EditButtons = <>
        FieldName = 'IN_DATE'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '年级'
        Width = 49
      end
      item
        EditButtons = <>
        FieldName = 'DEPT_NAME'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '一级单位'
        Width = 92
      end
      item
        EditButtons = <>
        FieldName = 'S_CODE'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '二级单位'
        Width = 84
      end
      item
        EditButtons = <>
        FieldName = 'ID2'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '身份证号码'
        Width = 85
      end
      item
        EditButtons = <>
        FieldName = 'PHOTO_DATE'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '拍照日期'
        Width = 61
      end>
  end
  object cbPhotoDate: TCheckBox
    Left = 152
    Top = 96
    Width = 73
    Height = 17
    Caption = '拍照日期'
    TabOrder = 5
  end
  object qryInit: TADOQuery
    Parameters = <>
    Left = 280
    Top = 128
  end
  object qrySelect: TADOQuery
    Parameters = <>
    SQL.Strings = (
      'select CUT_TYPE, STUEMP_NO, STUEMP_NAME, DEPT_NAME, S_CODE,'
      '    SEX_NAME, ID2, IN_DATE, PHOTO_DATE from PHOTO.T_CIF_PHOTO ')
    Left = 336
    Top = 128
    object qrySelectCUT_TYPE: TStringField
      FieldName = 'CUT_TYPE'
      Size = 50
    end
    object qrySelectSTUEMP_NO: TStringField
      FieldName = 'STUEMP_NO'
    end
    object qrySelectSTUEMP_NAME: TStringField
      FieldName = 'STUEMP_NAME'
      Size = 60
    end
    object qrySelectDEPT_NAME: TStringField
      FieldName = 'DEPT_NAME'
      Size = 150
    end
    object qrySelectS_CODE: TStringField
      FieldName = 'S_CODE'
      Size = 150
    end
    object qrySelectSEX_NAME: TStringField
      FieldName = 'SEX_NAME'
      Size = 30
    end
    object qrySelectID2: TStringField
      FieldName = 'ID2'
      Size = 30
    end
    object qrySelectIN_DATE: TStringField
      FieldName = 'IN_DATE'
      Size = 30
    end
    object qrySelectPHOTO_DATE: TStringField
      FieldName = 'PHOTO_DATE'
      Size = 10
    end
  end
  object DataSource: TDataSource
    DataSet = qrySelect
    Left = 448
    Top = 128
  end
  object SaveDialog: TSaveDialog
    Filter = 
      '文本文件|*.txt|网页格式|*.htm|Word格式|*.rtf|Excel格式|*.xls|csv' +
      '|*.csv'
    Left = 192
    Top = 129
  end
  object qryPhoto: TADOQuery
    Parameters = <>
    Left = 416
    Top = 128
  end
  object qryDelete: TADOQuery
    Parameters = <>
    Left = 384
    Top = 128
  end
end

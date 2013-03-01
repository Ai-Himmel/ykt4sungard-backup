object frmMadeCard: TfrmMadeCard
  Left = 27
  Top = 32
  Width = 696
  Height = 480
  BorderIcons = [biSystemMenu]
  Caption = '制卡管理'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object lblTotlal: TLabel
    Left = 584
    Top = 120
    Width = 60
    Height = 12
    Caption = '共  条记录'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 649
    Height = 89
    Caption = '查询条件'
    TabOrder = 0
    object Label6: TLabel
      Left = 32
      Top = 24
      Width = 54
      Height = 12
      Caption = '学    号:'
    end
    object Label8: TLabel
      Left = 32
      Top = 56
      Width = 54
      Height = 12
      Caption = '一级单位:'
    end
    object Label9: TLabel
      Left = 232
      Top = 24
      Width = 54
      Height = 12
      Caption = '姓    名:'
    end
    object Label10: TLabel
      Left = 232
      Top = 56
      Width = 54
      Height = 12
      Caption = '二级单位:'
    end
    object Label11: TLabel
      Left = 432
      Top = 56
      Width = 54
      Height = 12
      Caption = '年    级:'
    end
    object Label12: TLabel
      Left = 432
      Top = 24
      Width = 54
      Height = 12
      Caption = '类    别:'
    end
    object edtNum: TEdit
      Left = 96
      Top = 24
      Width = 113
      Height = 20
      TabOrder = 0
    end
    object cbDept: TComboBox
      Left = 96
      Top = 56
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
      Top = 24
      Width = 113
      Height = 20
      TabOrder = 2
    end
    object cbSubDept: TComboBox
      Left = 296
      Top = 56
      Width = 113
      Height = 20
      ItemHeight = 12
      TabOrder = 3
    end
    object cbGrade: TComboBox
      Left = 496
      Top = 56
      Width = 113
      Height = 20
      ItemHeight = 12
      TabOrder = 4
    end
    object cbType: TComboBox
      Left = 496
      Top = 24
      Width = 113
      Height = 20
      ItemHeight = 12
      TabOrder = 5
    end
  end
  object btnQuery: TButton
    Left = 16
    Top = 112
    Width = 75
    Height = 25
    Caption = '查询'
    TabOrder = 1
    OnClick = btnQueryClick
  end
  object tsDBGrid: TtsDBGrid
    Left = 16
    Top = 144
    Width = 649
    Height = 257
    CellSelectMode = cmNone
    CheckBoxStyle = stCheck
    Cols = 9
    DatasetType = dstStandard
    DataSource = DataSource
    DefaultRowHeight = 16
    ExactRowCount = True
    FieldState = fsCustomized
    HeadingFont.Charset = ANSI_CHARSET
    HeadingFont.Color = clWindowText
    HeadingFont.Height = -12
    HeadingFont.Name = '宋体'
    HeadingFont.Style = []
    ParentShowHint = False
    RowChangedIndicator = riAutoReset
    RowMoving = False
    ShowHint = True
    TabOrder = 2
    Version = '2.01'
    DataBound = True
    ColProperties = <
      item
        DataCol = 1
        FieldName = 'CUT_TYPE'
        Col.ControlType = ctText
        Col.FieldName = 'CUT_TYPE'
        Col.Heading = '类别'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 50
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 54
        Col.AssignedValues = #2
      end
      item
        DataCol = 2
        FieldName = 'STUEMP_NO'
        Col.ControlType = ctText
        Col.FieldName = 'STUEMP_NO'
        Col.Heading = '学工号'
        Col.HeadingButton = cbNone
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 20
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 54
        Col.AssignedValues = #2
      end
      item
        DataCol = 3
        FieldName = 'STUEMP_NAME'
        Col.ControlType = ctText
        Col.FieldName = 'STUEMP_NAME'
        Col.Heading = '姓名'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 60
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 47
        Col.AssignedValues = #2
      end
      item
        DataCol = 4
        FieldName = 'DEPT_NAME'
        Col.ControlType = ctText
        Col.FieldName = 'DEPT_NAME'
        Col.Heading = '一级单位'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 150
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 97
        Col.AssignedValues = #2
      end
      item
        DataCol = 5
        FieldName = 'S_CODE'
        Col.ControlType = ctText
        Col.FieldName = 'S_CODE'
        Col.Heading = '二级单位'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 150
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 92
        Col.AssignedValues = #2
      end
      item
        DataCol = 6
        FieldName = 'SEX_NAME'
        Col.ControlType = ctText
        Col.FieldName = 'SEX_NAME'
        Col.Heading = '性别'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 30
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 29
        Col.AssignedValues = #2
      end
      item
        DataCol = 7
        FieldName = 'ID2'
        Col.ControlType = ctText
        Col.FieldName = 'ID2'
        Col.Heading = '身份证号码'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 30
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 86
        Col.AssignedValues = #2
      end
      item
        DataCol = 8
        FieldName = 'IN_DATE'
        Col.ControlType = ctText
        Col.FieldName = 'IN_DATE'
        Col.Heading = '入学年份'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 30
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 52
        Col.AssignedValues = #2
      end
      item
        DataCol = 9
        FieldName = 'IF_MAKECARD'
        Col.ControlType = ctText
        Col.FieldName = 'IF_MAKECARD'
        Col.Heading = '是否制卡'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.MaxLength = 1
        Col.ReadOnly = True
        Col.HorzAlignment = htaLeft
        Col.Width = 56
        Col.AssignedValues = #2
      end>
  end
  object btnAllSelect: TButton
    Left = 16
    Top = 411
    Width = 75
    Height = 25
    Caption = '全选'
    TabOrder = 3
    OnClick = btnAllSelectClick
  end
  object btnAntSelect: TButton
    Left = 112
    Top = 411
    Width = 75
    Height = 25
    Caption = '反选'
    TabOrder = 4
    OnClick = btnAntSelectClick
  end
  object btnMadeCard: TButton
    Left = 208
    Top = 411
    Width = 75
    Height = 25
    Caption = '已制卡'
    TabOrder = 5
    OnClick = btnMadeCardClick
  end
  object btnCancel: TButton
    Left = 592
    Top = 411
    Width = 75
    Height = 25
    Caption = '退出'
    ModalResult = 2
    TabOrder = 6
  end
  object btnNotMade: TButton
    Left = 304
    Top = 411
    Width = 75
    Height = 25
    Caption = '未制卡'
    TabOrder = 7
    OnClick = btnNotMadeClick
  end
  object qryInit: TADOQuery
    Parameters = <>
    Left = 184
    Top = 112
  end
  object qrySelect: TADOQuery
    Parameters = <>
    SQL.Strings = (
      'select CUT_TYPE, STUEMP_NO, STUEMP_NAME, DEPT_NAME, S_CODE,'
      '    SEX_NAME, ID2, IN_DATE, IF_MAKECARD from PHOTO.T_CIF_PHOTO ')
    Left = 232
    Top = 112
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
    object qrySelectIF_MAKECARD: TStringField
      FieldName = 'IF_MAKECARD'
      FixedChar = True
      Size = 1
    end
  end
  object DataSource: TDataSource
    DataSet = qrySelect
    Left = 312
    Top = 112
  end
end

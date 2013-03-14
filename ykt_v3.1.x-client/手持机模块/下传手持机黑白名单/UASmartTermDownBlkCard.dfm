inherited faqhSmartTermDownBlkCard: TfaqhSmartTermDownBlkCard
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 428
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 611
      Top = 6
      Hint = '下传黑白名单'
      Caption = '下传(&D)'
      TabOrder = 2
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF000000FF00FFFFFF00FFFFFF00FFFFFF007B0000007B00
        00007B0000007B0000007B0000007B0000007B0000007B0000007B000000FFFF
        FF000000FF000000FF000000FF000000FF000000FF00FFFFFF007B000000FFFF
        FF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF000000
        FF000000FF000000FF000000FF000000FF000000FF000000FF007B000000FFFF
        FF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBD
        BD000000FF000000FF000000FF000000FF000000FF000000FF007B000000BDBD
        BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD007B00
        0000FFFFFF000000FF000000FF00FFFFFF000000FF000000FF007B000000FFFF
        FF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF007B00
        0000FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF000000FF007B000000FFFF
        FF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF007B00
        00007B0000007B000000FFFFFF00FFFFFF000000FF000000FF007B0000007B00
        00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
        0000FFFFFF00FFFFFF007B0000000000FF000000FF000000FF007B0000007B00
        00007B0000007B0000007B0000007B000000FFFF00007B000000FFFF00007B00
        0000FFFFFF00FFFFFF007B0000000000FF000000FF000000FF007B0000007B00
        00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
        0000BDBDBD00BDBDBD007B0000000000FF000000FF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B000000FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBD
        BD00FFFFFF00FFFFFF007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B000000FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBD
        BD00FFFFFF00FFFFFF007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B0000007B0000007B0000007B0000007B0000007B0000007B00
        00007B0000007B0000007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B0000007B0000007B0000007B0000007B0000007B000000FFFF
        00007B000000FFFF00007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B0000007B0000007B0000007B0000007B0000007B0000007B00
        00007B0000007B0000007B000000FFFFFF00FFFFFF00FFFFFF00}
    end
    inherited btnPrint: TBitBtn
      Left = 322
      TabOrder = 0
      Visible = False
    end
    object imgQueryBlack: TBitBtn
      Left = 522
      Top = 6
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '查询(&Q)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = imgQueryBlackClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF001818180018181800181818001818180018181800181818001818
        1800181818001818180018181800FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF001818180084848400ADADAD00D6D6D600D6D6D600D6D6D600D6D6D600D6D6
        D600D6D6D600CECECE00181818001818180018181800FFFFFF00FFFFFF001818
        1800DEDEDE0018181800ADADAD00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
        DE00DEDEDE005A5A5A000029CE002994FF000029940018181800181818008484
        8400181818005A5A5A00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
        DE005A5A5A000029CE0094CEFF009494FF000029CE001818180018181800D6D6
        D600DEDEDE00DEDEDE00DEDEDE00DEDEDE00D6D6D600A59C9C00A59C9C005A5A
        5A000029CE0094CEFF009494FF000029CE0018181800FFFFFF0018181800DEDE
        DE00DEDEDE00DEDEDE00BDBDBD00636363001818180018181800181818001818
        180094CEFF009494FF000029CE0018181800FFFFFF00FFFFFF0018181800DEDE
        DE00DEDEDE00BDBDBD0063636300FFCE6300FFCE6300FFCE6300FFCE2900FF94
        63002963FF000029CE0018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
        DE00BDBDBD0063636300A59C9C00EFC6A500FFFF9400FFFF9400FFCE6300FFCE
        2900FF9463001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
        DE00BDBDBD0063636300EFC6A500FFFFCE00FFFF9400FFFF9400FFFF9400FFCE
        6300FFCE29001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
        DE00BDBDBD0063636300EFC6A500FFFFCE00FFFF9400FFFF9400FFFF9400FFFF
        9400FFCE29001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
        DE00BDBDBD0063636300EFC6A500FFFFCE00FFFF9400FFFF9400FFFF9400FFFF
        9400FFCE29001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
        DE00D6D6D60063636300BDBDBD00EFC6A500FFFFCE00FFFF9400FFFF9400EFC6
        A500A59C9C001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
        DE00D6D6D600BDBDBD0063636300BDBDBD00EFC6A500EFC6A500EFC6A500A59C
        9C0018181800BDBDBD0018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
        DE00D6D6D600D6D6D600BDBDBD00636363006363630063636300636363006363
        6300BDBDBD00DEDEDE0018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
        DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00BDBDBD00BDBDBD00BDBDBD00BDBD
        BD00DEDEDE00DEDEDE0018181800FFFFFF00FFFFFF00FFFFFF00181818001818
        1800181818001818180018181800181818001818180018181800181818001818
        1800181818001818180018181800FFFFFF00FFFFFF00FFFFFF00}
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel2: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 15
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
  end
  inherited UIPanel2: TUIPanel
    Top = 33
    Width = 700
    Height = 395
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 395
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易卡号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '版本号'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '增加标志'
          Width = 70
          Visible = True
        end>
    end
  end
  object sbInfo: TStatusBar [4]
    Left = 0
    Top = 464
    Width = 700
    Height = 25
    Font.Charset = GB2312_CHARSET
    Font.Color = clGreen
    Font.Height = -15
    Font.Name = '宋体'
    Font.Style = []
    Panels = <
      item
        Width = 400
      end
      item
        Width = 50
      end>
    SimplePanel = False
    UseSystemFont = False
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '设备物理ID'
        Caption = '设备'
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
        Name = '返回码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|设备|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 244
    Top = 23
  end
  inherited MainRequest: TWVRequest
    ID = '下传手持机黑白名单'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备物理ID'
        FieldName = '设备物理ID'
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end>
    Left = 280
    Top = 24
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 312
    Top = 24
  end
  inherited DataSource: TDataSource
    Left = 352
    Top = 24
  end
  object wvUpdateVersion: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '设备物理ID'
        Caption = '设备'
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
        Name = '版本号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|设备|'
      end>
    Left = 244
    Top = 63
  end
  object wvrVersion: TWVRequest
    WorkView = wvUpdateVersion
    ID = '更新手持机名单版本'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备物理ID'
        FieldName = '设备物理ID'
      end
      item
        ParamName = '版本号'
        FieldName = '版本号'
      end>
    AfterExec = MainRequestAfterExec
    Left = 280
    Top = 64
  end
end

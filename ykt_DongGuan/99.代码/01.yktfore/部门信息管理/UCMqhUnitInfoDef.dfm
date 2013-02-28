inherited dmUnitInfoDef: TdmUnitInfoDef
  OldCreateOrder = True
  Left = 198
  Top = 139
  object cqQueryUnitInfoByKey: TWVCommandTypeInfo
    ID = '单位信息主键查询一'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '单位代码'
      end>
    Left = 48
    Top = 10
  end
  object cqQueryUnitInfoByOther: TWVCommandTypeInfo
    ID = '单位信息查询一'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end
      item
        ParamName = '查询结果集'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '单位代码'
      end
      item
        ParamName = '单位名称'
      end
      item
        ParamName = '英文名称'
      end
      item
        ParamName = '上级单位'
      end
      item
        ParamName = '所属区域'
      end
      item
        ParamName = '操作类别'
      end>
    Left = 48
    Top = 106
  end
  object cpSetUnitInfo: TWVCommandTypeInfo
    ID = '单位信息设置'
    Params = <
      item
        ParamName = '返回码'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '返回信息'
        ParamType = ptOutput
      end
      item
        ParamName = '单位代码'
      end
      item
        ParamName = '单位名称'
      end
      item
        ParamName = '英文名称'
      end
      item
        ParamName = '上级单位'
      end
      item
        ParamName = '所属区域'
      end
      item
        ParamName = '操作类别'
      end
      item
        ParamName = '旧部门代码'
      end>
    Left = 48
    Top = 58
  end
  object KCQueryUnitInfoByKey: TKCWVQuery
    ID = '单位信息主键查询一'
    InputBindings = <
      item
        ParamName = '单位代码'
        FieldName = 'scert_no'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 842001
    Left = 128
    Top = 26
  end
  object KCQueryUnitInfoByOther: TKCWVQuery
    ID = '单位信息查询一'
    InputBindings = <
      item
        ParamName = '单位代码'
        FieldName = 'scert_no'
      end
      item
        ParamName = '单位名称'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '英文名称'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '上级单位'
        FieldName = 'semail2'
      end
      item
        ParamName = '所属区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '查询结果集'
        FieldName = '@Dataset'
      end
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 842001
    Left = 128
    Top = 122
  end
  object KCSetUnitInfo: TKCWVProcessor
    ID = '单位信息设置'
    InputBindings = <
      item
        ParamName = '单位代码'
        FieldName = 'scert_no'
      end
      item
        ParamName = '单位名称'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '英文名称'
        FieldName = 'ssectypes'
      end
      item
        ParamName = '上级单位'
        FieldName = 'semail2'
      end
      item
        ParamName = '所属区域'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '操作类别'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '旧部门代码'
        FieldName = 'scert_no2'
      end>
    OutputBindings = <
      item
        ParamName = '返回码'
        FieldName = '@Return'
      end
      item
        ParamName = '返回信息'
        FieldName = 'vsmess'
      end>
    RequestType = 842001
    KCDataset = Dataset
    Left = 128
    Top = 74
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 392
    Top = 32
  end
end

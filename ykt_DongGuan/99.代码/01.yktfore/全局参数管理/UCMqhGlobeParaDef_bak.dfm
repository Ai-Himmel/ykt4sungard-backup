inherited dmGlobeParaDef: TdmGlobeParaDef     
  OldCreateOrder = True     
  Left = 285     
  object cpAddGlobeParaInfo: TWVCommandTypeInfo     
    ID = '全局参数设置.增加'     
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
        ParamName = '参数标识'     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '参数名称'     
      end     
      item     
        ParamName = '参数值'     
      end     
      item     
        ParamName = '生效时间'     
      end     
      item     
        ParamName = '参数单位'     
      end     
      item     
        ParamName = '备注'     
      end>     
    Left = 192     
    Top = 106     
  end     
  object cpChangeGlobeParaInfo: TWVCommandTypeInfo     
    ID = '全局参数设置.修改'     
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
        ParamName = '参数标识'     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '参数名称'     
      end     
      item     
        ParamName = '参数值'     
      end     
      item     
        ParamName = '生效时间'     
      end     
      item     
        ParamName = '参数单位'     
      end     
      item     
        ParamName = '备注'     
      end>     
    Left = 200     
    Top = 184     
  end     
  object cpDelGlobeParaInfo: TWVCommandTypeInfo     
    ID = '全局参数设置.删除'     
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
        ParamName = '参数标识'     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '参数名称'     
      end     
      item     
        ParamName = '参数值'     
      end     
      item     
        ParamName = '生效时间'     
      end     
      item     
        ParamName = '参数单位'     
      end     
      item     
        ParamName = '备注'     
      end>     
    Left = 192     
    Top = 256     
  end     
  object cqQueryGlobeParaByOther: TWVCommandTypeInfo     
    ID = '全局参数非关键字查询'     
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
        ParamName = '参数名称'     
      end     
      item     
        ParamName = '参数值'     
      end     
      item     
        ParamName = '参数单位'     
      end     
      item     
        ParamName = '生效时间'     
      end     
      item     
        ParamName = '设置时间'     
      end>     
    Left = 192     
    Top = 26     
  end     
  object cqQueryGlobeParaByKey: TWVCommandTypeInfo     
    ID = '全局参数关键字查询'     
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
        ParamName = '参数标志'     
        ParamDataType = kdtInteger     
      end>     
    Left = 48     
    Top = 34     
  object cqSetChargePara: TWVCommandTypeInfo 
    ID = '收费参数查询' 
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
        ParamName = '设备商户标识' 
      end> 
    Left = 40 
    Top =  10 
  end 
  object cpSetChargePara: TWVCommandTypeInfo
    ID = '收费参数设置'
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
        ParamName = '编号'
      end
      item
        ParamName = '前端机标识'
      end
      item
        ParamName = '商户标识'
      end>
    Left = 160
    Top =  10
  end
  end     
 


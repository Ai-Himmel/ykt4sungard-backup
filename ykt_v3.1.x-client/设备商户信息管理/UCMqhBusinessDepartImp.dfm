inherited dmBusinessDepartImp: TdmBusinessDepartImp   
  OldCreateOrder = True   
  Left = 285   
  Top = 161   
  Height = 479   
  Width = 741   
  object cqQueryBusinessDepartByOther: TKCWVQuery   
    ID = '设备商户信息非主键查询'   
    InputBindings = <   
      item   
        ParamName = '#营业部代码'   
        FieldName = 'sbranch_code0'   
      end   
      item   
        ParamName = '#职工代码'   
        FieldName = 'semp'   
      end   
      item   
        ParamName = '#网卡地址'   
        FieldName = 'sstation0'   
      end   
      item   
        ParamName = '前端机标识'   
        FieldName = 'lvol2'   
      end   
      item   
        ParamName = '商户标识'   
        FieldName = 'lvol4'   
      end   
      item   
        ParamName = '使用开始日期'   
        FieldName = 'scust_auth1'   
      end   
      item   
        ParamName = '使用开始时间'   
        FieldName = 'scust_auth'   
      end   
      item   
        ParamName = '使用结束时间'   
        FieldName = 'scust_limit'   
      end   
      item   
        ParamName = '使用结束日期'   
        FieldName = 'scust_limit2'   
      end   
      item   
        ParamName = '备注'   
        FieldName = 'usset2'   
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
    RequestType = 843372   
    Left = 40   
    Top = 34   
  end   
  object cqQueryBusinessDepartByKey: TKCWVQuery   
    ID = '设备商户信息主键查询'   
    InputBindings = <   
      item   
        ParamName = '#营业部代码'   
        FieldName = 'sbranch_code0'   
      end   
      item   
        ParamName = '#职工代码'   
        FieldName = 'semp'   
      end   
      item   
        ParamName = '#网卡地址'   
        FieldName = 'sstation0'   
      end   
      item   
        ParamName = '设备商户标识'   
        FieldName = 'lvol0'   
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
    RequestType = 843371   
    Left = 200   
    Top = 18   
  end   
  object KCDataset1: TKCDataset   
    MaxRows = 0   
    AggregateFields = <>   
    RequestType = 0   
    Params = <>   
    Left = 376   
    Top = 80   
  end   
  object cqSetBusinessDepartInfo: TKCWVQuery 
    ID = '设备商户信息查询' 
    InputBindings = < 
      item 
        ParamName = '#营业部代码' 
        FieldName = 'sbranch_code0' 
      end 
      item 
        ParamName = '#职工代码' 
        FieldName = 'semp' 
      end 
      item 
        ParamName = '#网卡地址' 
        FieldName = 'sstation0' 
      end 
      item 
        ParamName = '设备商户标识' 
        FieldName = 'lvol0' 
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
    RequestType = 843368 
    Left = 40 
    Top  = 10 
  end 
  object cpSetBusinessDepartInfo: TKCWVProcessor
    ID = '设备商户信息设置'
    InputBindings = <
      item
        ParamName = '#营业部代码'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#职工代码'
        FieldName = 'semp'
      end
      item
        ParamName = '#网卡地址'
        FieldName = 'sstation0'
      end
      item
        ParamName = '编号'
        FieldName = 'lvol3'
      end
      item
        ParamName = '前端机标识'
        FieldName = 'lvol2'
      end
      item
        ParamName = '商户标识'
        FieldName = 'sdate0'
      end
      item
        ParamName = '使用开始日期'
        FieldName = 'scust_auth1'
      end
      item
        ParamName = '使用开始时间'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '使用结束时间'
        FieldName = 'scust_limit1'
      end
      item
        ParamName = '使用结束日期'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '备注'
        FieldName = 'usset2'
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
    RequestType = 843369
    KCDataset = KCDataset
    Left = 160
    Top  = 10
  end
end   
  
 


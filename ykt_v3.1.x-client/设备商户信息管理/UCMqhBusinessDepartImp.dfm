inherited dmBusinessDepartImp: TdmBusinessDepartImp   
  OldCreateOrder = True   
  Left = 285   
  Top = 161   
  Height = 479   
  Width = 741   
  object cqQueryBusinessDepartByOther: TKCWVQuery   
    ID = '�豸�̻���Ϣ��������ѯ'   
    InputBindings = <   
      item   
        ParamName = '#Ӫҵ������'   
        FieldName = 'sbranch_code0'   
      end   
      item   
        ParamName = '#ְ������'   
        FieldName = 'semp'   
      end   
      item   
        ParamName = '#������ַ'   
        FieldName = 'sstation0'   
      end   
      item   
        ParamName = 'ǰ�˻���ʶ'   
        FieldName = 'lvol2'   
      end   
      item   
        ParamName = '�̻���ʶ'   
        FieldName = 'lvol4'   
      end   
      item   
        ParamName = 'ʹ�ÿ�ʼ����'   
        FieldName = 'scust_auth1'   
      end   
      item   
        ParamName = 'ʹ�ÿ�ʼʱ��'   
        FieldName = 'scust_auth'   
      end   
      item   
        ParamName = 'ʹ�ý���ʱ��'   
        FieldName = 'scust_limit'   
      end   
      item   
        ParamName = 'ʹ�ý�������'   
        FieldName = 'scust_limit2'   
      end   
      item   
        ParamName = '��ע'   
        FieldName = 'usset2'   
      end>   
    OutputBindings = <   
      item   
        ParamName = '��ѯ�����'   
        FieldName = '@Dataset'   
      end   
      item   
        ParamName = '������'   
        FieldName = '@Return'   
      end   
      item   
        ParamName = '������Ϣ'   
        FieldName = 'vsmess'   
      end>   
    RequestType = 843372   
    Left = 40   
    Top = 34   
  end   
  object cqQueryBusinessDepartByKey: TKCWVQuery   
    ID = '�豸�̻���Ϣ������ѯ'   
    InputBindings = <   
      item   
        ParamName = '#Ӫҵ������'   
        FieldName = 'sbranch_code0'   
      end   
      item   
        ParamName = '#ְ������'   
        FieldName = 'semp'   
      end   
      item   
        ParamName = '#������ַ'   
        FieldName = 'sstation0'   
      end   
      item   
        ParamName = '�豸�̻���ʶ'   
        FieldName = 'lvol0'   
      end>   
    OutputBindings = <   
      item   
        ParamName = '��ѯ�����'   
        FieldName = '@Dataset'   
      end   
      item   
        ParamName = '������'   
        FieldName = '@Return'   
      end   
      item   
        ParamName = '������Ϣ'   
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
    ID = '�豸�̻���Ϣ��ѯ' 
    InputBindings = < 
      item 
        ParamName = '#Ӫҵ������' 
        FieldName = 'sbranch_code0' 
      end 
      item 
        ParamName = '#ְ������' 
        FieldName = 'semp' 
      end 
      item 
        ParamName = '#������ַ' 
        FieldName = 'sstation0' 
      end 
      item 
        ParamName = '�豸�̻���ʶ' 
        FieldName = 'lvol0' 
      end> 
    OutputBindings = < 
      item 
        ParamName = '��ѯ�����' 
        FieldName = '@Dataset' 
      end 
      item 
        ParamName = '������' 
        FieldName = '@Return' 
      end 
      item 
        ParamName = '������Ϣ' 
        FieldName = 'vsmess' 
      end> 
    RequestType = 843368 
    Left = 40 
    Top  = 10 
  end 
  object cpSetBusinessDepartInfo: TKCWVProcessor
    ID = '�豸�̻���Ϣ����'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '���'
        FieldName = 'lvol3'
      end
      item
        ParamName = 'ǰ�˻���ʶ'
        FieldName = 'lvol2'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = 'sdate0'
      end
      item
        ParamName = 'ʹ�ÿ�ʼ����'
        FieldName = 'scust_auth1'
      end
      item
        ParamName = 'ʹ�ÿ�ʼʱ��'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'scust_limit1'
      end
      item
        ParamName = 'ʹ�ý�������'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '��ע'
        FieldName = 'usset2'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 843369
    KCDataset = KCDataset
    Left = 160
    Top  = 10
  end
end   
  
 


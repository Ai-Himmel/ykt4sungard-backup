inherited dmGlobeParaDef: TdmGlobeParaDef     
  OldCreateOrder = True     
  Left = 285     
  object cpAddGlobeParaInfo: TWVCommandTypeInfo     
    ID = 'ȫ�ֲ�������.����'     
    Params = <     
      item     
        ParamName = '������'     
        ParamType = ptOutput     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '������Ϣ'     
        ParamType = ptOutput     
      end     
      item     
        ParamName = '������ʶ'     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '��������'     
      end     
      item     
        ParamName = '����ֵ'     
      end     
      item     
        ParamName = '��Чʱ��'     
      end     
      item     
        ParamName = '������λ'     
      end     
      item     
        ParamName = '��ע'     
      end>     
    Left = 192     
    Top = 106     
  end     
  object cpChangeGlobeParaInfo: TWVCommandTypeInfo     
    ID = 'ȫ�ֲ�������.�޸�'     
    Params = <     
      item     
        ParamName = '������'     
        ParamType = ptOutput     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '������Ϣ'     
        ParamType = ptOutput     
      end     
      item     
        ParamName = '������ʶ'     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '��������'     
      end     
      item     
        ParamName = '����ֵ'     
      end     
      item     
        ParamName = '��Чʱ��'     
      end     
      item     
        ParamName = '������λ'     
      end     
      item     
        ParamName = '��ע'     
      end>     
    Left = 200     
    Top = 184     
  end     
  object cpDelGlobeParaInfo: TWVCommandTypeInfo     
    ID = 'ȫ�ֲ�������.ɾ��'     
    Params = <     
      item     
        ParamName = '������'     
        ParamType = ptOutput     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '������Ϣ'     
        ParamType = ptOutput     
      end     
      item     
        ParamName = '������ʶ'     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '��������'     
      end     
      item     
        ParamName = '����ֵ'     
      end     
      item     
        ParamName = '��Чʱ��'     
      end     
      item     
        ParamName = '������λ'     
      end     
      item     
        ParamName = '��ע'     
      end>     
    Left = 192     
    Top = 256     
  end     
  object cqQueryGlobeParaByOther: TWVCommandTypeInfo     
    ID = 'ȫ�ֲ����ǹؼ��ֲ�ѯ'     
    Params = <     
      item     
        ParamName = '������'     
        ParamType = ptOutput     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '������Ϣ'     
        ParamType = ptOutput     
      end     
      item     
        ParamName = '��ѯ�����'     
        ParamType = ptOutput     
        ParamDataType = kdtObject     
      end     
      item     
        ParamName = '��������'     
      end     
      item     
        ParamName = '����ֵ'     
      end     
      item     
        ParamName = '������λ'     
      end     
      item     
        ParamName = '��Чʱ��'     
      end     
      item     
        ParamName = '����ʱ��'     
      end>     
    Left = 192     
    Top = 26     
  end     
  object cqQueryGlobeParaByKey: TWVCommandTypeInfo     
    ID = 'ȫ�ֲ����ؼ��ֲ�ѯ'     
    Params = <     
      item     
        ParamName = '������'     
        ParamType = ptOutput     
        ParamDataType = kdtInteger     
      end     
      item     
        ParamName = '������Ϣ'     
        ParamType = ptOutput     
      end     
      item     
        ParamName = '��ѯ�����'     
        ParamType = ptOutput     
        ParamDataType = kdtObject     
      end     
      item     
        ParamName = '������־'     
        ParamDataType = kdtInteger     
      end>     
    Left = 48     
    Top = 34     
  object cqSetChargePara: TWVCommandTypeInfo 
    ID = '�շѲ�����ѯ' 
    Params = < 
      item 
        ParamName = '������' 
        ParamType = ptOutput 
        ParamDataType = kdtInteger 
      end 
      item 
        ParamName = '������Ϣ' 
        ParamType = ptOutput 
      end 
      item 
        ParamName = '��ѯ�����' 
        ParamType = ptOutput 
        ParamDataType = kdtObject 
      end 
      item 
        ParamName = '�豸�̻���ʶ' 
      end> 
    Left = 40 
    Top =  10 
  end 
  object cpSetChargePara: TWVCommandTypeInfo
    ID = '�շѲ�������'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '���'
      end
      item
        ParamName = 'ǰ�˻���ʶ'
      end
      item
        ParamName = '�̻���ʶ'
      end>
    Left = 160
    Top =  10
  end
  end     
 


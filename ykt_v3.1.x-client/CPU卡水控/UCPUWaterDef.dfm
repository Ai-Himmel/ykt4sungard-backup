inherited cmCPUWaterDef: TcmCPUWaterDef
  OldCreateOrder = True
  Left = 486
  Top = 165
  object ctRollBack: TWVCommandTypeInfo
    ID = 'ʧ����Ϣ_water'
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
        ParamName = '���ײο���'
      end
      item
        ParamName = '�����'
      end>
    Left = 16
    Top = 104
  end
  object cqwaterTrans: TWVCommandTypeInfo
    ID = 'ˮ��ת��_water'
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
        ParamName = '�ն˺�'
      end
      item
        ParamName = '���ײο���'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '���״���'
      end
      item
        ParamName = 'СǮ�����'
      end
      item
        ParamName = 'ת�˽��'
      end
      item
        ParamName = '֧������'
      end
      item
        ParamName = '�ն���ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '��������'
        ParamType = ptOutput
      end
      item
        ParamName = '����ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = '����ֵ'
        ParamType = ptOutput
      end
      item
        ParamName = '�ۿ���'
        ParamType = ptOutput
      end
      item
        ParamName = '��д���'
        ParamType = ptOutput
      end
      item
        ParamName = 'СǮ�����'
        ParamType = ptOutput
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 16
    Top = 58
  end
  object cqTradeCode: TWVCommandTypeInfo
    ID = '���ײο���_water'
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
        ParamName = '�ն˺�'
      end
      item
        ParamName = 'ʱ���'
      end
      item
        ParamName = '���ײο���'
        ParamType = ptOutput
      end
      item
        ParamName = '�����'
        ParamType = ptOutput
      end>
    Left = 16
    Top = 10
  end
  object WVQueryGlobeParaByKey: TWVCommandTypeInfo
    ID = 'ȫ�ֲ���������ѯ_water'
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
      end
      item
        ParamName = '��Կ'
        ParamType = ptOutput
      end>
    Left = 16
    Top = 154
  end
  object cqSaveFeeType: TWVCommandTypeInfo
    ID = '����������ÿ�'
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
        ParamName = '��־'
      end
      item
        ParamName = '���ʱ��'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�Ʒѵ�λ'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '���ʸ���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '����ʱ��1'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '���ʽ��1'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '���ʷ���1'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '����ʱ��2'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '���ʽ��2'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '���ʷ���2'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '����ʱ��3'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '���ʽ��3'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '���ʷ���3'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 16
    Top = 202
  end
  object cqFeeTypeQ: TWVCommandTypeInfo
    ID = '�������ÿ���ѯ'
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
        ParamName = '��־'
      end
      item
        ParamName = '��������'
      end>
    Left = 16
    Top = 250
  end
  object cqFeeTypeDel: TWVCommandTypeInfo
    ID = '�������ÿ�ɾ��'
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
        ParamName = '��־'
      end
      item
        ParamName = '��������'
      end>
    Left = 16
    Top = 298
  end
  object cqSmlTradeSerial: TWVCommandTypeInfo
    ID = 'СǮ����ˮ��ѯ'
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
        ParamName = '��ʼ����'
      end
      item
        ParamName = '��ֹ����'
      end
      item
        ParamName = '�ն˱��'
      end
      item
        ParamName = '�ն���ˮ��'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = 'ƾ֤����'
      end
      item
        ParamName = '�ͻ���'
      end
      item
        ParamName = 'ѧ/����'
      end
      item
        ParamName = '��ʾ����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = 'Ǯ����'
      end
      item
        ParamName = '��ˮ״̬'
      end
      item
        ParamName = '��ѯ����'
      end
      item
        ParamName = '���׿�ʼ����'
      end
      item
        ParamName = '���׽�������'
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '����״̬'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '��ʼʱ��'
      end
      item
        ParamName = '���ױ�־'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�ⲿ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 80
    Top = 26
  end
  object WVsmlSerialRcv: TWVCommandTypeInfo
    ID = 'СǮ����ˮ����'
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
        ParamName = '�ն˱��'
      end
      item
        ParamName = '�ն���ˮ��'
      end
      item
        ParamName = '�ͻ���'
      end
      item
        ParamName = '����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '���׽��'
      end
      item
        ParamName = 'СǮ�����'
        ParamType = ptOutput
      end>
    Left = 80
    Top = 74
  end
end

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
    Top = 82
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
    Left = 192
    Top = 128
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
    Top = 176
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
    Left = 288
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
    Left = 56
    Top = 106
  end
  object cpAddSetChargePara: TWVCommandTypeInfo
    ID = '�շѲ�������.����'
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
        ParamName = '��λ����'
      end
      item
        ParamName = '�ͻ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end>
    Left = 192
    Top = 234
  end
  object cpChargeSetChargePara: TWVCommandTypeInfo
    ID = '�շѲ�������.�޸�'
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
        ParamName = '��λ����'
      end
      item
        ParamName = '�ͻ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end>
    Left = 192
    Top = 290
  end
  object cpDelSetChargePara: TWVCommandTypeInfo
    ID = '�շѲ�������.ɾ��'
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
        ParamName = '��λ����'
      end
      item
        ParamName = '�ͻ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end>
    Left = 192
    Top = 346
  end
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
        ParamName = '��λ����'
      end>
    Left = 64
    Top = 234
  end
  object cqSetChargeType: TWVCommandTypeInfo
    ID = '�շ��������'
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
        ParamName = '�շ����'
      end
      item
        ParamName = '�Ƿ��մ���'
      end
      item
        ParamName = '��־'
      end
      item
        ParamName = '����־'
        ParamDataType = kdtInteger
      end>
    Left = 64
    Top = 290
  end
end

inherited dmEPurseReg: TdmEPurseReg
  OldCreateOrder = True
  Left = 285
  object cqEpurseReg: TWVCommandTypeInfo
    ID = '����Ǯ������'
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
        ParamName = '�ʻ�����'
      end
      item
        ParamName = '�ͻ���'
        ParamDataType = kdtInteger
      end>
    Left = 48
    Top = 10
  end
  object WVEPurseDestory: TWVCommandTypeInfo
    ID = '������ѯ'
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
        ParamName = '�ͻ���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ѧ����'
      end
      item
        ParamName = '�ͻ�����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '���ڲ���'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = 'ֹ��״̬'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�ʺ�'
      end>
    Left = 48
    Top = 58
  end
  object cqEPurseDestory: TWVCommandTypeInfo
    ID = '����Ǯ������'
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
        ParamName = '�ʻ�����'
      end
      item
        ParamName = '�ͻ���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ʺ�'
      end>
    Left = 48
    Top = 106
  end
  object WVEPurseIn: TWVCommandTypeInfo
    ID = '����Ǯ����ֵ'
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
        ParamName = '�ʺ�'
      end
      item
        ParamName = '��ֵ��ʽ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ƾ֤����'
      end
      item
        ParamName = '��ֵ���'
        ParamDataType = kdtFloat
      end>
    Left = 48
    Top = 154
  end
  object WVEPurseOut: TWVCommandTypeInfo
    ID = '����Ǯ��֧ȡ'
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
        ParamName = '�ʺ�'
      end
      item
        ParamName = '�ͻ���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ȡ������'
      end
      item
        ParamName = 'ȡ����'
        ParamDataType = kdtFloat
      end>
    Left = 48
    Top = 202
  end
  object WVFreeze: TWVCommandTypeInfo
    ID = 'Ǯ��ֹ���⸶'
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
        ParamName = '�ʺ�'
      end
      item
        ParamName = '�ͻ���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��־'
      end>
    Left = 48
    Top = 250
  end
  object WVEpurseTrans: TWVCommandTypeInfo
    ID = '����Ǯ��ת��'
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
        ParamName = '����'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�뿨���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '���״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ֵ���'
        ParamDataType = kdtFloat
      end
      item
        ParamName = 'ת�˷���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ʻ�����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ҵ������'
        ParamType = ptOutput
      end
      item
        ParamName = '�������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ն˱��'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end>
    Left = 48
    Top = 298
  end
  object WVchangepwd: TWVCommandTypeInfo
    ID = 'Ǯ�������޸�'
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
        ParamName = '�ʺ�'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '������'
      end>
    Left = 128
    Top = 26
  end
  object WVresetpwd: TWVCommandTypeInfo
    ID = 'Ǯ����������'
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
        ParamName = '�ʺ�'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '������'
      end>
    Left = 128
    Top = 74
  end
end

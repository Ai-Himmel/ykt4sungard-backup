inherited dmBusinessDepartDef: TdmBusinessDepartDef
  OldCreateOrder = True
  object cqQueryBusinessDepartByOther: TWVCommandTypeInfo
    ID = '�豸�̻���Ϣ��������ѯ'
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
        ParamName = 'ǰ�˻���ʶ'
      end
      item
        ParamName = '�̻���ʶ'
      end
      item
        ParamName = 'ʹ�ÿ�ʼ����'
      end
      item
        ParamName = 'ʹ�ÿ�ʼʱ��'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = 'ʹ�ý�������'
      end
      item
        ParamName = '��ע'
      end>
    Left = 240
    Top = 42
  end
  object cqQueryBusinessDepartByKey: TWVCommandTypeInfo
    ID = '�豸�̻���Ϣ������ѯ'
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
    Left = 88
    Top = 42
  end
  object cqSetBusinessDepartInfo: TWVCommandTypeInfo
    ID = '�豸�̻���Ϣ��ѯ'
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
    Left = 240
    Top = 154
  end
  object cpSetBusinessDepartInfo: TWVCommandTypeInfo
    ID = '�豸�̻���Ϣ����'
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
      end
      item
        ParamName = 'ʹ�ÿ�ʼ����'
      end
      item
        ParamName = 'ʹ�ÿ�ʼʱ��'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = 'ʹ�ý�������'
      end
      item
        ParamName = '��ע'
      end>
    Left = 80
    Top = 154
  end
end

inherited dmBusinessEquipDef: TdmBusinessEquipDef
  OldCreateOrder = True
  Left = 435
  Top = 180
  Height = 543
  Width = 628
  object cqQueryBusinessEquipByOther: TWVCommandTypeInfo
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
        ParamName = 'ʹ��״̬'
      end
      item
        ParamName = '�豸��ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�̻�����'
      end
      item
        ParamName = 'ʹ�ÿ�ʼ����'
      end
      item
        ParamName = 'ʹ�ý�������'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = '�̻����'
        ParamDataType = kdtInteger
      end>
    Left = 144
    Top = 74
  end
  object cpSetBusinessEquipInfo: TWVCommandTypeInfo
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
        ParamName = '������־'
      end
      item
        ParamName = '���'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�̻���ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�豸��ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = 'ͣ������'
      end>
    Left = 40
    Top = 202
  end
  object cqSetBusinessEquipInfo: TWVCommandTypeInfo
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
        ParamName = '���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�豸���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�̻����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'ʹ��״̬'
      end>
    Left = 40
    Top = 58
  end
  object cqQueryEquipmentByKey3: TWVCommandTypeInfo
    ID = '�豸�ؼ��ֲ�ѯ3'
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
        ParamName = '�豸��ʶ'
        ParamDataType = kdtInteger
      end>
    Left = 144
    Top = 124
  end
  object cqQueryBusinessByKey2: TWVCommandTypeInfo
    ID = '�̻���Ϣ������ѯ2'
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
        ParamName = '�̻���ʶ'
      end>
    Left = 40
    Top = 106
  end
  object cqQueryBusinessByOther2: TWVCommandTypeInfo
    ID = '�̻���Ϣ��������ѯ2'
    Params = <
      item
        ParamName = '��ѯ�����'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
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
        ParamName = '�̻���ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '���̻���ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�̻�����'
      end
      item
        ParamName = '�̻����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�Ƿ�Ϊ��������'
      end
      item
        ParamName = '�Ƿ�ΪҶ�ڵ�'
      end
      item
        ParamName = '����������'
      end
      item
        ParamName = '���������֤��'
      end>
    Left = 40
    Top = 154
  end
  object cqQueryEquipmentByOther2: TWVCommandTypeInfo
    ID = '�豸�ǹؼ��ֲ�ѯ2'
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
        ParamName = '�豸����'
      end
      item
        ParamName = '�����豸ע���'
      end
      item
        ParamName = '�豸����ID'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '���ʹ���'
      end
      item
        ParamName = '�ϼ��豸����ID'
      end
      item
        ParamName = '�豸״̬'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�豸�����ͺ�'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������ϵͳ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�豸��������'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ա����'
      end>
    Left = 144
    Top = 28
  end
  object cqsetMealOrder: TWVCommandTypeInfo
    ID = '�ʹ���Ϣ��ѯ'
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
        ParamName = '�ʹ�����'
      end
      item
        ParamName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '������־'
      end>
    Left = 232
    Top = 10
  end
  object cpsetMealOrder: TWVCommandTypeInfo
    ID = '�ʹ���Ϣ����'
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
        ParamName = '�ʹ�����'
      end
      item
        ParamName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '��ע'
      end>
    Left = 232
    Top = 58
  end
  object WVDevBusiImp: TWVCommandTypeInfo
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
        ParamName = '���κ�'
        ParamType = ptInputOutput
      end
      item
        ParamName = '���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�Ƿ������'
      end
      item
        ParamName = '�̻����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�豸���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ͣ��ʱ��'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = 'ͣ������'
      end
      item
        ParamName = '������־'
      end>
    Left = 40
    Top = 250
  end
  object cqdevBusiImpManage: TWVCommandTypeInfo
    ID = '�豸�̻���ѯ'
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
      end
      item
        ParamName = '�������κ�'
      end
      item
        ParamName = '�豸���'
      end
      item
        ParamName = '�豸������'
      end
      item
        ParamName = '�豸����'
      end
      item
        ParamName = '�̻����'
      end
      item
        ParamName = '�̻�����'
      end>
    Left = 144
    Top = 170
  end
  object cpdevBusiImpManage: TWVCommandTypeInfo
    ID = '�豸�̻��������'
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
        ParamName = '�������κ�'
      end
      item
        ParamName = '����˳���'
      end
      item
        ParamName = '�豸����'
      end
      item
        ParamName = '�̻�����'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = 'ͣ������'
      end
      item
        ParamName = '������־'
      end>
    Left = 144
    Top = 218
  end
  object WVdevBusiImpCheck: TWVCommandTypeInfo
    ID = '�豸�̻��������'
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
        ParamName = '�������κ�'
      end
      item
        ParamName = '����˳���'
      end
      item
        ParamName = '������־'
      end>
    Left = 144
    Top = 266
  end
  object cqPatchDel: TWVCommandTypeInfo
    ID = '�̻��豸����ɾ��'
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
        ParamName = '���κ�'
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '������־'
        ParamDataType = kdtInteger
      end>
    Left = 232
    Top = 206
  end
  object cqsetBusiCC: TWVCommandTypeInfo
    ID = '�̻��ʹ���Ϣ��ѯ'
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
        ParamName = '�̻����'
      end
      item
        ParamName = '�������'
      end>
    Left = 232
    Top = 306
  end
  object cpsetBusiCC: TWVCommandTypeInfo
    ID = '�̻��ʹ���Ϣ����'
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
        ParamName = '�̻����'
      end
      item
        ParamName = '��ͽ���ʱ��'
      end
      item
        ParamName = '��ͽ���ʱ��'
      end
      item
        ParamName = '��ͽ���ʱ��'
      end
      item
        ParamName = '�������'
      end>
    Left = 232
    Top = 258
  end
end

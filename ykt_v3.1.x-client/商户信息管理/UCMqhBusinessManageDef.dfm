inherited dmBusinessManageDef: TdmBusinessManageDef
  OldCreateOrder = True
  Left = 264
  Top = 149
  Height = 491
  Width = 711
  object cqQueryBusinessByOther: TWVCommandTypeInfo
    ID = '�̻���Ϣ��������ѯ'
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
        ParamName = '������־'
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
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�մ���'
      end>
    Left = 32
    Top = 58
  end
  object cqQueryBusinessByKey: TWVCommandTypeInfo
    ID = '�̻���Ϣ������ѯ'
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
      end
      item
        ParamName = '������־'
      end>
    Left = 32
    Top = 10
  end
  object cqsetBusiFate: TWVCommandTypeInfo
    ID = '�������ʲ�ѯ'
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
        ParamName = '���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'Ӫҵ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ۿ۱���'
        ParamDataType = kdtFloat
      end>
    Left = 128
    Top = 178
  end
  object cpsetBusiFate: TWVCommandTypeInfo
    ID = '������������'
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
        ParamName = '��־'
      end
      item
        ParamName = '���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'Ӫҵ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ۿ۱���'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '��ע'
      end>
    Left = 128
    Top = 226
  end
  object cqfillBusiSaveMoney: TWVCommandTypeInfo
    ID = '��ֵ�̻����'
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
        ParamName = '�̻���'
        ParamType = ptInputOutput
      end
      item
        ParamName = '�����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��������'
        ParamType = ptOutput
      end
      item
        ParamName = '����Ա��'
        ParamType = ptOutput
      end
      item
        ParamName = '��̨��ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '��ɽ��'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '�ʻ����'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '�̻�����'
        ParamType = ptOutput
      end
      item
        ParamName = '��ֵ����'
      end
      item
        ParamName = 'Ʊ�ݺ���'
      end>
    Left = 320
    Top = 122
  end
  object cqsetFillBusiEquInfo: TWVCommandTypeInfo
    ID = '��ֵ�̻��豸��ѯ'
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
        ParamName = '�̻���'
      end
      item
        ParamName = '�豸���'
      end>
    Left = 224
    Top = 2
  end
  object cpsetFillBusiEquInfo: TWVCommandTypeInfo
    ID = '��ֵ�̻��豸��Ϣ��������'
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
        ParamName = '�̻���'
      end
      item
        ParamName = '�豸���'
      end>
    Left = 224
    Top = 50
  end
  object cpsetFillBusiEquInfoDel: TWVCommandTypeInfo
    ID = '��ֵ�̻��豸��Ϣ����ɾ��'
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
        ParamName = '�̻���'
      end
      item
        ParamName = '�豸���'
      end>
    Left = 224
    Top = 98
  end
  object cqsetFillEquOperInfo: TWVCommandTypeInfo
    ID = '�豸����Ա��ѯ'
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
        ParamName = '�豸���'
      end
      item
        ParamName = '��ֵ����Ա��'
      end
      item
        ParamName = '״̬'
      end>
    Left = 224
    Top = 146
  end
  object cpsetFillEquOperInfo: TWVCommandTypeInfo
    ID = '��ֵ�豸����Ա�������'
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
        ParamName = '�豸���'
      end
      item
        ParamName = '��ֵ����Ա��'
      end
      item
        ParamName = 'ÿ������ֵ���'
      end
      item
        ParamName = '״̬'
      end
      item
        ParamName = '�Ƿ�ָ���豸'
      end
      item
        ParamName = '�Ƿ��ֵ�̻�����Ա'
      end>
    Left = 224
    Top = 194
  end
  object cpsetFillEquOperInfoEdit: TWVCommandTypeInfo
    ID = '��ֵ�豸����Ա�����޸�'
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
        ParamName = '�豸���'
      end
      item
        ParamName = '��ֵ����Ա��'
      end
      item
        ParamName = 'ÿ������ֵ���'
      end
      item
        ParamName = '״̬'
      end
      item
        ParamName = '�Ƿ�ָ���豸'
      end
      item
        ParamName = '�Ƿ��ֵ�̻�����Ա'
      end>
    Left = 224
    Top = 242
  end
  object cpsetFillEquOperInfoDel: TWVCommandTypeInfo
    ID = '��ֵ�豸����Ա����ɾ��'
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
        ParamName = '�豸���'
      end
      item
        ParamName = '��ֵ����Ա��'
      end
      item
        ParamName = '״̬'
      end
      item
        ParamName = '�Ƿ�ָ���豸'
      end
      item
        ParamName = '�Ƿ��ֵ�̻�����Ա'
      end>
    Left = 224
    Top = 290
  end
  object cqfillOperEquBanding: TWVCommandTypeInfo
    ID = '����Ա�豸��ѯ'
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
        ParamName = '�豸���'
      end
      item
        ParamName = '��ֵ����Ա��'
      end>
    Left = 128
    Top = 26
  end
  object cpfillOperEquBanding: TWVCommandTypeInfo
    ID = '��ֵ����Ա�豸��'
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
        ParamName = '��ֵ����Ա��'
      end
      item
        ParamName = '�豸���'
      end>
    Left = 128
    Top = 74
  end
  object cpfillOperEquBandingDel: TWVCommandTypeInfo
    ID = '��ֵ����Ա�豸��ɾ��'
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
        ParamName = '��ֵ����Ա��'
      end
      item
        ParamName = '�豸���'
      end>
    Left = 128
    Top = 122
  end
  object cpSetBusinessInfo: TWVCommandTypeInfo
    ID = '�̻���Ϣ����'
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
        ParamName = '����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '�̻�����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ϵ��'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '�绰'
      end
      item
        ParamName = '�ֻ�'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ַ'
      end
      item
        ParamName = '�ʱ�'
      end
      item
        ParamName = 'Ӷ������'
      end
      item
        ParamName = 'Ӷ�����'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '�����ɱ���'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '���д���'
      end
      item
        ParamName = '�����ʺ�'
      end
      item
        ParamName = '�����ʻ���'
      end
      item
        ParamName = 'ĩ���̻�'
      end
      item
        ParamName = '�Ƿ��մ���'
      end>
    Left = 32
    Top = 106
  end
  object cqSetBusiFee: TWVCommandTypeInfo
    ID = '�̻����Ѳ�ѯ'
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
        ParamName = '�̻���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end>
    Left = 320
    Top = 26
  end
  object cpSetBusiFee: TWVCommandTypeInfo
    ID = '�̻���������'
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
        ParamName = '�̻���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����'
        ParamDataType = kdtFloat
      end
      item
        ParamName = 'ѧУ����'
        ParamDataType = kdtFloat
      end>
    Left = 320
    Top = 74
  end
  object cqBusiSubjectLink: TWVCommandTypeInfo
    ID = '�̻���Ŀӳ���ѯ'
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
        ParamName = '�̻���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '��Ӧ��Ŀ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�����˺�'
      end>
    Left = 320
    Top = 170
  end
  object cpBusiSubjectLink: TWVCommandTypeInfo
    ID = '�̻���Ŀӳ��'
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
        ParamName = '�̻���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�̻�����'
      end
      item
        ParamName = '��Ӧ��Ŀ��'
      end
      item
        ParamName = '��Ӧ��Ŀ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�����˺�'
      end
      item
        ParamName = '��־'
      end>
    Left = 320
    Top = 218
  end
  object cqSetBusiStruct: TWVCommandTypeInfo
    ID = '�̻���֯�ṹ����'
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
        ParamName = '����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '�̻�����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ϵ��'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '�绰'
      end
      item
        ParamName = '�ֻ�'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ַ'
      end
      item
        ParamName = '�ʱ�'
      end
      item
        ParamName = 'Ӷ������'
      end
      item
        ParamName = 'Ӷ�����'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '�����ɱ���'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '���д���'
      end
      item
        ParamName = '�����ʺ�'
      end
      item
        ParamName = '�����ʻ���'
      end
      item
        ParamName = 'ĩ���̻�'
      end
      item
        ParamName = '�Ƿ��մ���'
      end>
    Left = 32
    Top = 154
  end
  object cqQBusiStruct: TWVCommandTypeInfo
    ID = '�̻���֯�ṹ��ѯ'
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
        ParamName = '������־'
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
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�մ���'
      end>
    Left = 32
    Top = 202
  end
end

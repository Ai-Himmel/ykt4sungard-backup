inherited dmCardDef: TdmCardDef
  OldCreateOrder = True
  Left = 410
  Top = 153
  Height = 495
  Width = 626
  object WVMoneyIn: TWVCommandTypeInfo
    ID = '����ֵ'
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
        DefaultValue = 0
      end
      item
        ParamName = '���Ѵ���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '��ֵ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'Ʊ�ݺ���'
      end
      item
        ParamName = '��ֵ���'
        ParamDataType = kdtFloat
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
      end
      item
        ParamName = 'ҵ��ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = 'psam����'
      end
      item
        ParamName = '������ˮ��'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end
      item
        ParamName = '����1'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 26
  end
  object WVMoneyOut: TWVCommandTypeInfo
    ID = '��֧ȡ'
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
        ParamName = '��ֵ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '���״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '֧ȡ���'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ҵ������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
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
      end
      item
        ParamName = 'ҵ��ʱ��'
        ParamType = ptOutput
      end>
    Left = 24
    Top = 74
  end
  object WVRefreshCard: TWVCommandTypeInfo
    ID = '���¿���Ϣ'
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
        ParamName = '��������'
      end
      item
        ParamName = '��ʾ����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ͻ����'
        ParamType = ptOutput
      end
      item
        ParamName = '�շ����'
        ParamType = ptOutput
      end
      item
        ParamName = 'ѧ����'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '���Ŵ���'
        ParamType = ptOutput
      end
      item
        ParamName = '֤������'
        ParamType = ptOutput
      end
      item
        ParamName = '�Ա�'
        ParamType = ptOutput
      end
      item
        ParamName = '����������'
        ParamType = ptInputOutput
      end
      item
        ParamName = '�����'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '���״���'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�������κ�'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '�����޶�'
        ParamType = ptOutput
      end
      item
        ParamName = '���޶�'
        ParamType = ptOutput
      end
      item
        ParamName = '�뵥���޶�'
      end
      item
        ParamName = '�����޶�'
      end
      item
        ParamName = '֤������'
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
        ParamName = '��ֵ����'
      end>
    Left = 24
    Top = 120
  end
  object cqSetMoney: TWVCommandTypeInfo
    ID = '���������'
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
        ParamName = '�������'
        ParamDataType = kdtFloat
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
        ParamName = 'ҵ��ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = '�������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ն˱��'
      end
      item
        ParamName = '��֤����Ա'
      end
      item
        ParamName = '��֤����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��ֵ����'
      end>
    Left = 24
    Top = 170
  end
  object cqAccountQ: TWVCommandTypeInfo
    ID = '�˻���Ϣ��ѯ'
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
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�绰'
      end
      item
        ParamName = '�ֻ�'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�ƿ�����'
      end
      item
        ParamName = '�����к�'
      end
      item
        ParamName = '��״̬'
      end
      item
        ParamName = '��ѯ���'
      end>
    Left = 88
    Top = 50
  end
  object cqCardSericalQ: TWVCommandTypeInfo
    ID = '������ˮ��ѯ'
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
        ParamName = '��������'
      end
      item
        ParamName = '�ͻ���'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�绰'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '����Ա'
      end>
    Left = 88
    Top = 98
  end
  object cqCardInfoQ: TWVCommandTypeInfo
    ID = '�ѷ�����Ϣ��ѯ'
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
        ParamName = '��������'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '���к�'
      end
      item
        ParamName = '����'
      end>
    Left = 88
    Top = 154
  end
  object WVLoss_UN: TWVCommandTypeInfo
    ID = '��ʧ���'
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
        ParamName = '�ͻ���'
      end
      item
        ParamName = '����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '�汾��'
        ParamType = ptOutput
      end
      item
        ParamName = 'psam����'
      end
      item
        ParamName = '������ˮ��'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '�����'
        ParamType = ptOutput
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end>
    Left = 88
    Top = 202
  end
  object cqReturnMoney: TWVCommandTypeInfo
    ID = '��ֵ��ѯ'
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
        ParamName = '��������'
      end
      item
        ParamName = '����Ա��'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '������'
      end>
    Left = 88
    Top = 250
  end
  object WVRtnMoney: TWVCommandTypeInfo
    ID = '��ֵ����'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
        ParamType = ptInputOutput
      end
      item
        ParamName = 'Ӧ�����к�'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ǰ��ֵ����'
      end
      item
        ParamName = '����ǰ���Ѵ���'
      end
      item
        ParamName = '�����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '�ϱ�sam�ն˺�'
      end
      item
        ParamName = '�ϱ�����'
      end
      item
        ParamName = '�ϱʽ��'
      end
      item
        ParamName = '�ϱ�����'
      end
      item
        ParamName = '�ϱ�ʱ��'
      end
      item
        ParamName = '����Ա���'
        ParamType = ptInputOutput
      end
      item
        ParamName = '����Ա��ˮ'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��������'
        ParamType = ptInputOutput
      end
      item
        ParamName = '����ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = '�����'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end
      item
        ParamName = '�ο���'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ע'
      end>
    Left = 88
    Top = 298
  end
  object WVChangeCardA: TWVCommandTypeInfo
    ID = '��������'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '����ԭ��'
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '���뵥��'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 34
  end
  object WVReNewApp: TWVCommandTypeInfo
    ID = '��������'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '����ԭ��'
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 82
  end
  object WVDestoryApp: TWVCommandTypeInfo
    ID = '��������'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '����ԭ��'
      end
      item
        ParamName = '��ֵ����'
      end
      item
        ParamName = '���Ѵ���'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '�ϱ�sam�ն�'
      end
      item
        ParamName = '�ϱ�����'
      end
      item
        ParamName = '�ϱʽ��'
      end
      item
        ParamName = '�ϱ�����'
      end
      item
        ParamName = '�ϱ�ʱ��'
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
        ParamName = '�ն˺�'
        ParamType = ptOutput
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 130
  end
  object WVReNewOper: TWVCommandTypeInfo
    ID = '�������'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��ֵ����'
      end
      item
        ParamName = '���Ѵ���'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '�ն˺�'
        ParamType = ptOutput
      end
      item
        ParamName = '����ֵ'
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
        ParamName = '��ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '�����'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 178
  end
  object WVChangeCardOper: TWVCommandTypeInfo
    ID = '��������'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��ֵ����'
      end
      item
        ParamName = '���Ѵ���'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '�ն˺�'
        ParamType = ptOutput
      end
      item
        ParamName = '����ֵ'
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
        ParamName = '��Ӧ�����к�'
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 226
  end
  object WVDestoryOper: TWVCommandTypeInfo
    ID = '��������'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end
      item
        ParamName = '�˿����'
        ParamType = ptOutput
      end>
    Left = 152
    Top = 274
  end
  object cqappDeal: TWVCommandTypeInfo
    ID = '���뵥����'
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
        ParamName = '��������'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '���뵥��'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����״̬'
      end>
    Left = 208
    Top = 18
  end
  object WVCancelApp: TWVCommandTypeInfo
    ID = '���뵥ȡ��'
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
        ParamName = '���뵥��'
      end>
    Left = 208
    Top = 66
  end
  object WVMakeAnonCNo: TWVCommandTypeInfo
    ID = '��������������'
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
        ParamName = '������λ'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '���κ�'
        ParamType = ptOutput
      end
      item
        ParamName = '��ʼ����'
        ParamType = ptOutput
      end
      item
        ParamName = '��������'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 114
  end
  object WVNonCardChange: TWVCommandTypeInfo
    ID = '�Ǽ�����������'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = '���뵥��'
      end
      item
        ParamName = 'ԭ����'
      end
      item
        ParamName = 'Ӧ�����к�'
        ParamType = ptInputOutput
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��ֵ����'
      end
      item
        ParamName = '���Ѵ���'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '�ն˺�'
        ParamType = ptOutput
      end
      item
        ParamName = '����ֵ'
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
        ParamName = '��ˮ��'
        ParamType = ptOutput
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 162
  end
  object WVTradeCancel: TWVCommandTypeInfo
    ID = '���׳���'
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
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '���ײο���'
      end
      item
        ParamName = '��������Ա'
      end
      item
        ParamName = '�������'
      end>
    Left = 208
    Top = 210
  end
  object cqSetPOSInfo: TWVCommandTypeInfo
    ID = '�豸��Ϣά����ѯ'
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
        ParamName = '�豸�ն˺�'
      end>
    Left = 24
    Top = 218
  end
  object WVMachineConsume: TWVCommandTypeInfo
    ID = '����������'
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
        ParamName = '���ױ�־'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = 'sam��ˮ��'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��ֵ����'
      end
      item
        ParamName = '���Ѵ���'
      end
      item
        ParamName = '���ѽ��'
      end
      item
        ParamName = '�����'
      end
      item
        ParamName = '��������'
        ParamType = ptOutput
      end
      item
        ParamName = '���ײο���'
        ParamType = ptOutput
      end
      item
        ParamName = '����ֵ'
        ParamType = ptOutput
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end
      item
        ParamName = '����ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 258
  end
  object WVConsumeOk: TWVCommandTypeInfo
    ID = '����������ȷ��'
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
        ParamName = '���ױ�־'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
      end
      item
        ParamName = 'sam��ˮ��'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '���ײο���'
      end
      item
        ParamName = '����ֵ'
        ParamType = ptOutput
      end
      item
        ParamName = 'TAC��'
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end
      item
        ParamName = '�ֻ�'
        ParamType = ptOutput
      end
      item
        ParamName = '����ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end>
    Left = 208
    Top = 306
  end
  object WVConsumeSerial: TWVCommandTypeInfo
    ID = '������ˮ��ѯ'
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
        ParamName = '��������'
      end
      item
        ParamName = '����Ա��'
      end
      item
        ParamName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�̻���'
      end>
    Left = 280
    Top = 34
  end
end

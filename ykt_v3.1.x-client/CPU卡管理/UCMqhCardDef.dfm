inherited dmCardDef: TdmCardDef
  OldCreateOrder = True
  Left = 319
  Top = 124
  Height = 577
  Width = 800
  object ctLossCard: TWVCommandTypeInfo
    ID = '��ʧ���'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '���汾��'
        ParamType = ptOutput
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end>
    Left = 40
    Top = 148
  end
  object ctChangeCardPwd: TWVCommandTypeInfo
    ID = '�޸Ŀ�����'
    Params = <
      item
        ParamName = '����ʶ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end>
    Left = 120
    Top = 24
  end
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
      end>
    Left = 40
    Top = 98
  end
  object ctTradeBusiInfo: TWVCommandTypeInfo
    ID = 'δ���˽����̻���ѯ'
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
        ParamName = '�ն˻��豸����ID'
      end>
    Left = 120
    Top = 124
  end
  object cqManualTradeQ: TWVCommandTypeInfo
    ID = 'δ������ˮ��ѯ'
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
        ParamName = '������ʼʱ��'
      end
      item
        ParamName = '������ֹʱ��'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ն˻�����ID'
      end
      item
        ParamName = '�ն˻���ˮ��'
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '״̬'
      end>
    Left = 192
    Top = 140
  end
  object cpManualTrade: TWVCommandTypeInfo
    ID = '������ˮ�ֹ�����'
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
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '�ն˻�����ID'
      end
      item
        ParamName = '�ն˻���ˮ��'
      end
      item
        ParamName = 'Ǯ����'
      end
      item
        ParamName = '�뿨���'
      end
      item
        ParamName = '�������'
      end
      item
        ParamName = '���׽��'
      end
      item
        ParamName = '��ǰ�������ۼƴ���'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '���ױ��'
      end
      item
        ParamName = 'ͨ�Ű汾��'
      end
      item
        ParamName = '����ԭ��'
      end
      item
        ParamName = '�̻�ID'
      end
      item
        ParamName = '�ն��豸��Ȩ��'
      end
      item
        ParamName = '���ϵͳ��ʶ'
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '״̬'
      end
      item
        ParamName = '�ɼ�ʱ���'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end>
    Left = 120
    Top = 76
  end
  object ctCardDestory: TWVCommandTypeInfo
    ID = 'һ��ͨ����'
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
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�Ƿ��п�'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '���״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�Ƿ���Ѻ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�˿���'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '�������κ�'
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
        ParamName = '��ֵ����'
      end>
    Left = 344
    Top = 98
  end
  object cqPatchAccount: TWVCommandTypeInfo
    ID = '���ʽ���'
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
        ParamName = '���׿���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�뿨ֵ'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '����վ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ǰ�����״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '�������'
        ParamDataType = kdtFloat
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '����Ա����'
      end
      item
        ParamName = '����'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '����ֵ'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '��ֵ���'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '��ˮ��������'
      end
      item
        ParamName = '��ˮ��'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ԭ��ˮ��'
        ParamDataType = kdtInteger
      end>
    Left = 40
    Top = 50
  end
  object cqPatchAccQuery: TWVCommandTypeInfo
    ID = '���ʽ��ײ�ѯ'
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
        ParamName = '���׿���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ʼ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�����˺�'
      end
      item
        ParamName = '״̬'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ѧ����'
      end>
    Left = 40
    Top = 2
  end
  object cqinAccountByMan: TWVCommandTypeInfo
    ID = '����ֹ�����'
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
        ParamName = '�跽�˺�'
      end
      item
        ParamName = '�����˺�'
      end
      item
        ParamName = '�������'
      end
      item
        ParamName = '����վ��'
      end
      item
        ParamName = '����Ա��'
      end
      item
        ParamName = '���˲���Ա��'
      end
      item
        ParamName = '���˲���Ա����'
      end>
    Left = 192
    Top = 2
  end
  object ctinAccountByMan: TWVCommandTypeInfo
    ID = '����ֹ����ʲ�ѯ'
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
        ParamName = '�˺�'
      end
      item
        ParamName = '����'
        ParamType = ptOutput
      end>
    Left = 192
    Top = 50
  end
  object cpPubAuthCard: TWVCommandTypeInfo
    ID = '������Ȩ��'
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
        ParamName = '����Ա��'
        ParamType = ptInputOutput
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��Ȩ��Ȩ��'
        ParamType = ptInputOutput
      end
      item
        ParamName = 'ҵ�����Ա'
      end
      item
        ParamName = '��Ч��'
        ParamType = ptInputOutput
      end
      item
        ParamName = '���׿���'
        ParamType = ptOutput
      end
      item
        ParamName = '������Կ'
        ParamType = ptOutput
      end
      item
        ParamName = '����Ա����'
        ParamType = ptOutput
      end>
    Left = 280
    Top = 26
  end
  object cpauthCardOper: TWVCommandTypeInfo
    ID = '��Ȩ������'
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
        ParamName = '���׿���'
      end
      item
        ParamName = '����Ա����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '״̬'
      end>
    Left = 280
    Top = 74
  end
  object cpmodifyAuthCard: TWVCommandTypeInfo
    ID = '�޸���Ȩ������'
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
        ParamName = '���׿���'
        ParamType = ptInputOutput
      end
      item
        ParamName = '������Ч��'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��Ȩ��'
        ParamType = ptInputOutput
      end
      item
        ParamName = 'ҵ�����Ա��'
      end>
    Left = 280
    Top = 122
  end
  object cpReturnAuthCard: TWVCommandTypeInfo
    ID = '��Ȩ������'
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
        ParamName = '���׿���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '�޿�����'
      end>
    Left = 280
    Top = 170
  end
  object cpLoseAuthCard: TWVCommandTypeInfo
    ID = '��Ȩ����ʧ'
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
        ParamName = '���׿���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա����'
      end
      item
        ParamName = 'ҵ�����Ա��'
      end>
    Left = 280
    Top = 218
  end
  object cpRLoseAuthCard: TWVCommandTypeInfo
    ID = '��Ȩ�����'
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
        ParamName = '���׿���'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա����'
      end
      item
        ParamName = 'ҵ�����Ա��'
      end
      item
        ParamName = '�������汾'
        ParamType = ptOutput
      end>
    Left = 280
    Top = 266
  end
  object WVCardCustInfoQuery: TWVCommandTypeInfo
    ID = '�����ͻ���Ϣ��ѯ'
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
        ParamName = '����'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '�ͻ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = 'רҵ'
      end
      item
        ParamName = '�������κ�'
      end
      item
        ParamName = 'ע������'
      end
      item
        ParamName = '�༶'
      end
      item
        ParamName = '�������'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 280
    Top = 312
  end
  object WVFeeQuery: TWVCommandTypeInfo
    ID = '�����շѲ�ѯ'
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
        ParamName = '���ܺ�'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ���Ϣ'
        ParamType = ptOutput
      end
      item
        ParamName = '�ܷ���'
        ParamType = ptOutput
        ParamDataType = kdtFloat
      end
      item
        ParamName = '�Ƿ񲻼�����'
      end
      item
        ParamName = '����Ч��'
        ParamType = ptOutput
      end
      item
        ParamName = '�ͻ���'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 280
    Top = 354
  end
  object WVRelCardOk: TWVCommandTypeInfo
    ID = '����ȷ��'
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
        ParamName = '�ն˱��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ҵ������'
      end
      item
        ParamName = '��������Ա'
      end>
    Left = 280
    Top = 400
  end
  object WVCardInfoQuery: TWVCommandTypeInfo
    ID = '�ѿ����ͻ���Ϣ��ѯ'
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
        ParamName = '����'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '�ͻ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ʾ����'
      end
      item
        ParamName = '�������κ�'
      end
      item
        ParamName = 'ע������'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��״̬'
      end
      item
        ParamName = '�����־'
      end
      item
        ParamName = '��ԭ��'
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 344
    Top = 48
  end
  object ctFreezeCard: TWVCommandTypeInfo
    ID = '����ⶳ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = '���汾��'
        ParamType = ptOutput
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
      end>
    Left = 40
    Top = 196
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
    Left = 120
    Top = 170
  end
  object WVcashOperCancel: TWVCommandTypeInfo
    ID = '��ֵ֧ȡ����'
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
        ParamName = '��ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ҵ������'
      end
      item
        ParamName = '�ն˱��'
        ParamDataType = kdtInteger
      end>
    Left = 344
    Top = 194
  end
  object WVAccountQuery: TWVCommandTypeInfo
    ID = '�ʻ���Ϣ��ѯ'
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
        ParamName = '����'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '֤������'
      end
      item
        ParamName = '�ͻ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�շ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ʾ����'
      end
      item
        ParamName = '�������κ�'
      end
      item
        ParamName = 'ע������'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '��״̬'
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 344
    Top = 240
  end
  object cqcardTradeQuery: TWVCommandTypeInfo
    ID = '��������ˮ��ѯ'
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
        DefaultValue = 0
      end>
    Left = 40
    Top = 242
  end
  object WVTradeReserse: TWVCommandTypeInfo
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
        ParamName = '�ն˱��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ҵ������'
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '����Ա����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '�Ƿ���Ȩ'
      end>
    Left = 40
    Top = 288
  end
  object WVReverseOpenCard: TWVCommandTypeInfo
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
        ParamName = '�ն˱��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ҵ������'
        ParamType = ptInputOutput
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '���״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��֤����Ա'
      end
      item
        ParamName = '����Ա����'
      end
      item
        ParamName = '�Ƿ���Ȩ'
      end
      item
        ParamName = 'ҵ��ʱ��'
        ParamType = ptOutput
      end>
    Left = 344
    Top = 288
  end
  object cqaccountTradeQuery: TWVCommandTypeInfo
    ID = '�ʻ�������ϸ��ѯ'
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
        ParamName = '���˿�ʼ����'
      end
      item
        ParamName = '���˽�ֹ����'
      end
      item
        ParamName = '���׿�ʼ����'
      end
      item
        ParamName = '���׽�ֹ����'
      end
      item
        ParamName = '��Ŀ��'
      end
      item
        ParamName = '�˺�'
      end
      item
        ParamName = '�ʻ���'
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
        ParamName = '�̻���'
      end
      item
        ParamName = '��ʾ����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = 'ѧ����'
      end>
    Left = 120
    Top = 218
  end
  object WVRevSaveMoney: TWVCommandTypeInfo
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
        ParamName = 'ҵ������'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ն˱��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '����Ա����'
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
        ParamName = '�����״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�뿨ֵ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����ֵ'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ҵ��ʱ��'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��ֵ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 344
    Top = 336
  end
  object WVRevConsume: TWVCommandTypeInfo
    ID = '���ѳ���'
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
        ParamName = 'ҵ������'
        ParamType = ptInputOutput
      end
      item
        ParamName = '��ˮ��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ն˱��'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����Ա'
      end
      item
        ParamName = '����Ա����'
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
        ParamName = '�����״���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�뿨ֵ'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '����ֵ'
        ParamType = ptOutput
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ҵ��ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = '��ֵ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 344
    Top = 384
  end
  object cpbadCardManage: TWVCommandTypeInfo
    ID = '�����Ǽ�'
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
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��ԭ��'
      end
      item
        ParamName = '������־'
      end>
    Left = 120
    Top = 266
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
    Left = 192
    Top = 96
  end
  object cqcardLibNotBalance: TWVCommandTypeInfo
    ID = '���ⲻƽ�����ѯ'
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
        ParamName = '����'
      end
      item
        ParamName = '�ͻ���'
      end
      item
        ParamName = '���ⲻƽ����'
      end
      item
        ParamName = '��ƽ��ֵ'
      end
      item
        ParamName = 'ͳ������'
      end
      item
        ParamName = 'ƽ������'
      end
      item
        ParamName = 'ƽ�˲���Ա'
      end
      item
        ParamName = 'ƽ��״̬'
      end
      item
        ParamName = '��������'
      end>
    Left = 120
    Top = 314
  end
  object cqcqcardLibNotBal: TWVCommandTypeInfo
    ID = '���ⲻƽ����'
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
      end
      item
        ParamName = 'ͳ������'
      end
      item
        ParamName = 'ƽ�˷�ʽ'
      end>
    Left = 120
    Top = 362
  end
  object cqPubPASMCard: TWVCommandTypeInfo
    ID = 'PASM������'
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
        ParamName = '��������'
      end
      item
        ParamName = '��Ч����'
      end
      item
        ParamName = '�豸ʹ�÷�'
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = 'pasm����'
        ParamType = ptOutput
      end
      item
        ParamName = '������'
        ParamType = ptInputOutput
      end
      item
        ParamName = '�ն˱��'
        ParamType = ptInputOutput
      end
      item
        ParamName = '������'
        ParamType = ptOutput
      end
      item
        ParamName = '���з���ʶ'
        ParamType = ptOutput
      end>
    Left = 416
    Top = 16
  end
  object cqPASMEdit: TWVCommandTypeInfo
    ID = 'PASM���޸�'
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
        ParamName = '���׿���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '������'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '��Կ������'
        ParamDataType = kdtInteger
      end
      item
        ParamName = 'ʹ�÷���ʶ'
      end
      item
        ParamName = '��Ч����'
      end
      item
        ParamName = '״̬'
      end
      item
        ParamName = '������־'
      end>
    Left = 416
    Top = 64
  end
  object cqPASMDel: TWVCommandTypeInfo
    ID = 'PASM������'
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
        ParamName = '���׿���'
        ParamDataType = kdtInteger
      end
      item
        ParamName = '�ն˱��'
      end
      item
        ParamName = '������־'
      end>
    Left = 416
    Top = 112
  end
  object cqPASMQuery: TWVCommandTypeInfo
    ID = 'PASM����ѯ'
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
        ParamName = '����'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = 'ʹ�÷�'
      end
      item
        ParamName = '��Ч��'
      end
      item
        ParamName = '��״̬'
      end>
    Left = 416
    Top = 160
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
        ParamType = ptOutput
        ParamDataType = kdtInteger
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
    Left = 40
    Top = 338
  end
  object cqCollSerial_CPU: TWVCommandTypeInfo
    ID = 'CPU����ˮ�ɼ�'
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
        ParamName = 'վ���'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '���ױ�־'
      end
      item
        ParamName = '���Ѵ���'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '����ǰ���'
      end
      item
        ParamName = '���׽��'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��д���'
      end
      item
        ParamName = '�̻���'
      end
      item
        ParamName = '�ն˱��'
      end
      item
        ParamName = '�������'
      end>
    Left = 416
    Top = 210
  end
  object cqsmlPacket: TWVCommandTypeInfo
    ID = 'СǮ������'
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
        ParamName = '�������ݼ�'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '������־'
      end
      item
        ParamName = 'СǮ����'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�ͻ���'
        ParamType = ptInputOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'ת������'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'ת�뿨��'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'СǮ�����'
        ParamType = ptInputOutput
        ParamDataType = kdtFloat
        DefaultValue = 0
      end>
    Left = 416
    Top = 264
  end
  object cqReturnSml: TWVCommandTypeInfo
    ID = '��СǮ������'
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
        ParamName = '�������ݼ�'
        ParamType = ptOutput
        ParamDataType = kdtObject
      end
      item
        ParamName = '�ն˺�'
      end
      item
        ParamName = '���޿���־'
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'Ǯ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'СǮ�����Ѵ���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'СǮ�����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '��Ǯ����ֵ����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '��Ǯ�����Ѵ���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '��Ǯ�����'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'r��Ǯ�����'
        ParamType = ptOutput
      end
      item
        ParamName = 'r��������'
        ParamType = ptOutput
      end
      item
        ParamName = 'r����ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = 'r����'
        ParamType = ptOutput
      end>
    Left = 416
    Top = 312
  end
  object cqFeeCardLock: TWVCommandTypeInfo
    ID = '�󸶷ѽ���'
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
        DefaultValue = 0
      end
      item
        ParamName = '������'
      end
      item
        ParamName = '���Ѵ���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�뿨���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�����豸'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '�������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = 'ҵ��ʱ��'
        ParamType = ptOutput
      end
      item
        ParamName = 'ҵ������'
        ParamType = ptOutput
      end
      item
        ParamName = '�ۿ���'
        ParamType = ptOutput
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 416
    Top = 354
  end
end

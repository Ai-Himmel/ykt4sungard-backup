inherited dmBusPosManage: TdmBusPosManage
  OldCreateOrder = True
  Left = 285
  object wvgetworkkey: TWVCommandTypeInfo
    ID = 'ȡ�ù�����Կ'
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
        ParamDataType = kdtObject
      end
      item
        ParamName = '������־'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end>
    Left = 32
    Top = 24
  end
  object kcworkkey: TKCWVQuery
    ID = 'ȡ�ù�����Կ'
    InputBindings = <
      item
        ParamName = '������־'
        FieldName = 'lvol0'
        DefaultValue = '0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 820404
    Left = 88
    Top = 40
  end
  object WVgetblacklist: TWVCommandTypeInfo
    ID = '��ȡ������'
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
      end>
    Left = 30
    Top = 120
  end
  object kcwgetblacklist: TKCWVQuery
    ID = '��ȡ������'
    InputBindings = <>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '�������ݼ�'
        FieldName = '@Dataset'
      end>
    RequestType = 950996
    Left = 89
    Top = 136
  end
  object getcardtypeinfo: TWVCommandTypeInfo
    ID = '��ȡ������'
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
        ParamDataType = kdtObject
      end
      item
        ParamName = '������־'
        DefaultValue = 'R'
      end>
    Left = 32
    Top = 72
  end
  object kcgetcardtypeinfo: TKCWVQuery
    ID = '��ȡ������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
        DefaultValue = 'R'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end>
    RequestType = 847198
    Left = 88
    Top = 88
  end
  object uploadwater: TWVCommandTypeInfo
    ID = '�ϴ���ˮ'
    Params = <
      item
        ParamName = '������'
        ParamType = ptOutput
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '������Ϣ'
        ParamType = ptOutput
        DefaultValue = '0'
      end
      item
        ParamName = '��ˮ��'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '����ID'
        DefaultValue = '0'
      end
      item
        ParamName = '���׿���'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '����վ��ʾ'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '�뿨���'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '�������'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '���ѽ��'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = 'Ǯ��'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '���Ѵ���'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = '���ױ�־'
        ParamDataType = kdtInteger
        DefaultValue = '0'
      end
      item
        ParamName = 'CRCУ����'
        DefaultValue = '0'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '����ʱ��'
      end
      item
        ParamName = '������2'
      end>
    Left = 32
    Top = 168
  end
  object kcupload: TKCWVQuery
    ID = '�ϴ���ˮ'
    InputBindings = <
      item
        ParamName = '��ˮ��'
        FieldName = 'lvol4'
        DefaultValue = '0'
      end
      item
        ParamName = '����ID'
        FieldName = 'sdate1'
        DefaultValue = '0'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol5'
        DefaultValue = '0'
      end
      item
        ParamName = '����վ��ʾ'
        FieldName = 'lcert_code'
        DefaultValue = '0'
      end
      item
        ParamName = '�뿨���'
        FieldName = 'lvol9'
        DefaultValue = '0'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol10'
        DefaultValue = '0'
      end
      item
        ParamName = '���ѽ��'
        FieldName = 'lvol8'
        DefaultValue = '0'
      end
      item
        ParamName = 'Ǯ��'
        FieldName = 'lvol6'
        DefaultValue = '0'
      end
      item
        ParamName = '���Ѵ���'
        FieldName = 'lvol7'
        DefaultValue = '0'
      end
      item
        ParamName = '���ױ�־'
        FieldName = 'lvol12'
        DefaultValue = '0'
      end
      item
        ParamName = 'CRCУ����'
        FieldName = 'sbank_code2'
        DefaultValue = '0'
      end
      item
        ParamName = '��������'
        FieldName = 'spost_code'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'spost_code2'
      end
      item
        ParamName = '������2'
        FieldName = 'sphone3'
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
    RequestType = 940031
    Left = 88
    Top = 184
  end
  object kcBusPosSerialQ: TKCWVQuery
    ID = '���ػ���ˮ��ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '�������ݼ�'
        FieldName = '@Dataset'
      end>
    RequestType = 846723
    Left = 88
    Top = 232
  end
  object cqBusPosSerialQ: TWVCommandTypeInfo
    ID = '���ػ���ˮ��ѯ'
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
        ParamName = 'ѧ����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��ʼ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
      end>
    Left = 32
    Top = 216
  end
  object cqBusPosSerStat: TWVCommandTypeInfo
    ID = '���ػ���ˮͳ��'
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
        ParamName = 'ѧ����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '����'
      end
      item
        ParamName = '��ʼ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end>
    Left = 32
    Top = 264
  end
  object kcBusPosSerStat: TKCWVQuery
    ID = '���ػ���ˮͳ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '����'
        FieldName = 'sall_name'
      end
      item
        ParamName = '����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '�������ݼ�'
        FieldName = '@Dataset'
      end>
    RequestType = 846724
    Left = 88
    Top = 280
  end
  object cq1BusPosserial: TWVCommandTypeInfo
    ID = '��Pos��ˮ��ѯ'
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
        ParamName = '�豸���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�豸����'
      end
      item
        ParamName = '��ʼ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
      end>
    Left = 32
    Top = 312
  end
  object kc1BusPosSerial: TKCWVQuery
    ID = '��Pos��ˮ��ѯ'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '�豸����'
        FieldName = 'snote'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '�������ݼ�'
        FieldName = '@Dataset'
      end>
    RequestType = 846725
    Left = 88
    Top = 328
  end
  object cq1BusPosStat: TWVCommandTypeInfo
    ID = '��Pos��ˮͳ��'
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
        ParamName = '�豸���'
        ParamDataType = kdtInteger
        DefaultValue = 0
      end
      item
        ParamName = '�豸����'
      end
      item
        ParamName = '��ʼ����'
      end
      item
        ParamName = '��������'
      end
      item
        ParamName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
      end>
    Left = 152
    Top = 16
  end
  object kcBusPosStat: TKCWVQuery
    ID = '��Pos��ˮͳ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '�豸����'
        FieldName = 'snote'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '�������ݼ�'
        FieldName = '@Dataset'
      end>
    RequestType = 846726
    Left = 208
    Top = 32
  end
end

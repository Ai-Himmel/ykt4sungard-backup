inherited dmGateBanImp: TdmGateBanImp
  OldCreateOrder = True
  Left = 348
  Top = 126
  Height = 565
  Width = 696
  object cqsetGateHoliday: TKCWVQuery
    ID = '�ڼ��ղ�ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ڼ��ձ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ڼ�����'
        FieldName = 'semail'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848255
    Left = 24
    Top = 66
  end
  object cpsetGateHoliday: TKCWVProcessor
    ID = '�ڼ�������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ڼ��ձ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ڼ�����'
        FieldName = 'semail'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
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
        ParamName = '�ڼ��ձ��'
        FieldName = 'lvol0'
      end>
    RequestType = 848255
    KCDataset = Dataset
    Left = 24
    Top = 114
  end
  object cqsetGateTime: TKCWVQuery
    ID = 'ʱ��β�����ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'semail'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848250
    Left = 24
    Top = 354
  end
  object cpsetGateTime: TKCWVProcessor
    ID = 'ʱ��β�������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'semail'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��ʶ'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
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
    RequestType = 848250
    KCDataset = Dataset
    Left = 24
    Top = 402
  end
  object cqsetDayTimeGroup: TKCWVQuery
    ID = 'ʱ�����ÿ������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'lcert_code'
      end
      item
        ParamName = 'ʱ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ʱ���һ'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ʱ��ζ�'
        FieldName = 'lvol2'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol3'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol4'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol6'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol7'
      end
      item
        ParamName = 'ʱ��ΰ�'
        FieldName = 'lvol8'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848252
    Left = 104
    Top = 338
  end
  object cqsetTimeGroup: TKCWVQuery
    ID = 'ʱ������ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'semail'
      end
      item
        ParamName = '��ʶ'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848252
    Left = 24
    Top = 258
  end
  object cpsetTimeGroup: TKCWVProcessor
    ID = 'ʱ���������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'semail'
      end
      item
        ParamName = '��ʶ'
        FieldName = 'lcert_code'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = 'ʱ���һ'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ʱ��ζ�'
        FieldName = 'lvol2'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol3'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol4'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol6'
      end
      item
        ParamName = 'ʱ�����'
        FieldName = 'lvol7'
      end
      item
        ParamName = 'ʱ��ΰ�'
        FieldName = 'lvol8'
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
        ParamName = '��ʶ'
        FieldName = 'lvol0'
      end>
    RequestType = 848252
    KCDataset = Dataset
    Left = 24
    Top = 306
  end
  object cqqueryTimeGroupDetail: TKCWVQuery
    ID = 'ʱ�������ϸ�����ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848254
    Left = 104
    Top = 386
  end
  object cqsetGateHolidayDetail: TKCWVQuery
    ID = '�ڼ�����ϸ����'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ڼ��ձ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ڼ�������'
        FieldName = 'sdate0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��־'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848256
    Left = 104
    Top = 434
  end
  object cqsetGateGroup: TKCWVQuery
    ID = '�Ž����ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�Ž�������'
        FieldName = 'semail'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848257
    Left = 24
    Top = 162
  end
  object cpsetGateGroup: TKCWVProcessor
    ID = '�Ž�������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�Ž�������'
        FieldName = 'semail'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
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
    RequestType = 848257
    KCDataset = Dataset
    Left = 24
    Top = 210
  end
  object cqsetGateGroupForGate: TKCWVQuery
    ID = '�Ž����Ž�����ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�Ž������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848258
    Left = 104
    Top = 146
  end
  object cpsetGateGroupForGate: TKCWVProcessor
    ID = '�Ž����Ž�������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�Ž������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
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
    RequestType = 848258
    KCDataset = Dataset
    Left = 104
    Top = 194
  end
  object cqsetGateOperLimit: TKCWVQuery
    ID = '�Ž�������ԱȨ�޲�ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848259
    Left = 104
    Top = 242
  end
  object cpsetGateOperLimit: TKCWVProcessor
    ID = '�Ž�������ԱȨ������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
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
    RequestType = 848259
    KCDataset = Dataset
    Left = 104
    Top = 290
  end
  object cqsetGateGroupOperLimit: TKCWVQuery
    ID = '�Ž������ԱȨ�޲�ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž�������'
        FieldName = 'semail'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848260
    Left = 104
    Top = 50
  end
  object cpsetGateGroupOperLimit: TKCWVProcessor
    ID = '�Ž������ԱȨ������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����Ա��'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
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
    RequestType = 848260
    KCDataset = Dataset
    Left = 104
    Top = 98
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 448
    Top = 64
  end
  object cqQueryEquipmentByOther: TKCWVQuery
    ID = '�豸��ѯ�Ž�ϵͳ'
    InputBindings = <
      item
        ParamName = '�豸����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�����豸ע���'
        FieldName = 'sbank_pwd'
      end
      item
        ParamName = '�豸����ID'
        FieldName = 'sbank_pwd2'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '���ʹ���'
        FieldName = 'sbank_code'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = 'sdate1'
      end
      item
        ParamName = '�豸״̬'
        FieldName = 'lvol4'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = 'lbank_acc_type'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = 'lserial0'
      end
      item
        ParamName = '�豸��������'
        FieldName = 'lserial1'
      end
      item
        ParamName = '������Ա����'
        FieldName = 'sname2'
      end
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848264
    Left = 192
    Top = 69
  end
  object KCHolidayQuery: TKCWVQuery
    ID = '�ڼ�����ϸ��ѯ'
    InputBindings = <
      item
        ParamName = '�ڼ��ձ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�ڼ�������'
        FieldName = 'semail'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848266
    Left = 192
    Top = 117
  end
  object cqsetWeekTimeGroup: TKCWVQuery
    ID = '��ʱ��β�ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ʱ���������'
        FieldName = 'semail'
      end
      item
        ParamName = '��һ����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ܶ�����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol3'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol4'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol6'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol7'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848251
    Left = 192
    Top = 162
  end
  object cpsetWeekTimeGroup: TKCWVProcessor
    ID = '��ʱ��β�������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ʱ�������'
        FieldName = 'semail'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��һ����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ܶ�����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol3'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol4'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol6'
      end
      item
        ParamName = '��������'
        FieldName = 'lvol7'
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
    RequestType = 848251
    KCDataset = Dataset
    Left = 192
    Top = 210
  end
  object KCallotCustGate: TKCWVProcessor
    ID = '�Ž���Ա��������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�Ž����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��ʱ���'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�ڼ���'
        FieldName = 'lvol4'
      end
      item
        ParamName = '��־'
        FieldName = 'lvol5'
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
        ParamName = '���ر�־'
        FieldName = 'lvol0'
      end>
    RequestType = 848267
    KCDataset = Dataset
    Left = 192
    Top = 258
  end
  object cqGateListQuery: TKCWVQuery
    ID = '�Ž���Ա������ѯ'
    InputBindings = <
      item
        ParamName = '�Ž�������'
        FieldName = 'semail2'
      end
      item
        ParamName = '�Ž��豸���'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '����'
        FieldName = 'semail'
      end
      item
        ParamName = 'Ժϵ����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol2'
        DefaultValue = Null
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '�շ�����'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '��������'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�༶'
        FieldName = 'sstation1'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '����Ա'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '��ɾ��־'
        FieldName = 'lvol8'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848269
    Left = 192
    Top = 306
  end
  object cqGateListDelete: TKCWVQuery
    ID = '�Ž���Ա����ɾ��'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�Ž����'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ʱ����'
        FieldName = 'lvol2'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848268
    Left = 192
    Top = 354
  end
  object KCGateGroupOper: TKCWVQuery
    ID = '�Ž������Ա��ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�Ž�������'
        FieldName = 'semail'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848265
    Left = 192
    Top = 402
  end
  object cqgateSerialDetailQuery: TKCWVQuery
    ID = '�Ž���ˮ��ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '���׿���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '������'
        FieldName = 'sname'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate0'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'stime0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = 'lvol2'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sall_name'
      end
      item
        ParamName = '����'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '�¼�'
        FieldName = 'lvol3'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = 'semail'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lvol5'
        DefaultValue = 0
      end
      item
        ParamName = '�豸����'
        FieldName = 'scust_limit'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848270
    Left = 280
    Top = 18
  end
  object cqattendDetailQuery: TKCWVQuery
    ID = '������ˮ��ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '����'
        FieldName = 'sname'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime2'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 847233
    Left = 280
    Top = 138
  end
  object cqattendDetailstat: TKCWVQuery
    ID = '������Ϣͳ��'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '����'
        FieldName = 'lvol1'
      end
      item
        ParamName = '����'
        FieldName = 'sname'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '��ʼʱ��'
        FieldName = 'stime1'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime2'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 847234
    Left = 280
    Top = 82
  end
  object cqQueryGateOpenAlong: TKCWVQuery
    ID = '����ʱ��β�ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž������'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848273
    Left = 280
    Top = 186
  end
  object cqSetGateOpenAlong: TKCWVProcessor
    ID = '����ʱ�������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�Ž������'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��������'
        FieldName = 'sstatus0'
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
    RequestType = 848273
    KCDataset = Dataset
    Left = 280
    Top = 234
  end
  object cqsetgatebaninfo: TKCWVProcessor
    ID = '�Ž��ԽӲ�������'
    InputBindings = <
      item
        ParamName = '������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = 'oper.��¥����'
        FieldName = 'scusttypes'
      end
      item
        ParamName = 'oper.��¥���'
        FieldName = 'scert_no'
      end
      item
        ParamName = 'oper.�Ž���'
        FieldName = 'lvol0'
        DefaultValue = '0'
      end
      item
        ParamName = 'oper.��ע'
        FieldName = 'vsvarstr0'
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
    RequestType = 888180
    KCDataset = Dataset
    Left = 280
    Top = 282
  end
  object cpSetGateTimeWeek: TKCWVProcessor
    ID = '�Ž�ʱ��������'
    InputBindings = <
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lvol2'
      end
      item
        ParamName = '���������'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'lvol3'
      end
      item
        ParamName = '���ʹ���'
        FieldName = 'spost_code'
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
    RequestType = 848021
    KCDataset = Dataset
    Left = 280
    Top = 330
  end
  object cqGateTimeWeekManager: TKCWVQuery
    ID = '�Ž�ʱ���ܹ���'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '���������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '����������'
        FieldName = 'sall_name'
      end
      item
        ParamName = '�豸������'
        FieldName = 'sholder_type'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sholder_type2'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '�豸����'
        FieldName = 'spost_code'
      end
      item
        ParamName = '��������'
        FieldName = 'smain_flag2'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'lserial1'
        DefaultValue = 0
      end
      item
        ParamName = 'ʱ��������'
        FieldName = 'saddr2'
      end
      item
        ParamName = '��ϵͳ'
        FieldName = 'lvol4'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848021
    Left = 280
    Top = 378
  end
  object kcGateTimeWeekDel: TKCWVQuery
    ID = '�Ž�ʱ����ɾ��'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�������'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '���������'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�豸���'
        FieldName = 'lvol2'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'lvol3'
        DefaultValue = 0
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848021
    Left = 280
    Top = 426
  end
  object cqQueryCustomerByOther: TKCWVQuery
    ID = '�Ž��ͻ���Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '��ϵ��ַ'
        FieldName = 'scusttypes'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ϵ�˵�λ����'
        FieldName = 'scard1'
      end
      item
        ParamName = '��ϵ�˵�λ��'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sname'
      end
      item
        ParamName = '�ͻ�״̬'
        FieldName = 'lvol2'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lvol3'
      end
      item
        ParamName = '��ϵ������'
        FieldName = 'sname2'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '��ϵ������'
        FieldName = 'lvol4'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '��ϵ��ѧ����'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = 'sphone'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�༶'
        FieldName = 'sorder0'
      end
      item
        ParamName = '����ѧ����'
        FieldName = 'sphone2'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 848022
    Left = 376
    Top = 34
  end
  object kcSetGateOpenMgr: TKCWVQuery
    ID = '��������������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�豸��'
        FieldName = 'lvol3'
      end
      item
        ParamName = '����;'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol2'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
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
    RequestType = 950106
    Left = 376
    Top = 82
  end
  object kcQgateMgrOpen: TKCWVQuery
    ID = '������������ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�豸��'
        FieldName = 'lvol3'
      end
      item
        ParamName = '����;'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol2'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
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
    RequestType = 950106
    Left = 376
    Top = 130
  end
end

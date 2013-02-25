unit def;

interface

const
  IP_LEN = 15;
  MAC_LEN = 18;
  CRC_LEN = 16;
  MODULE_NAME_LEN = 256;
  MAX_PATH_LEN = 1024;

  RET_OK = 1;
  RET_FAILD = 2;

type
  // ����������
  ksf_server_conf = record
    ip : array[0..IP_LEN] of char;
    mac : array[0..MAC_LEN] of char;
    port : Integer;
  end;
  Pksf_server_conf = ^ksf_server_conf;
  
  // �������ݰ�����  
  ksf_xml_data = packed record
    length : Longint;               // ���ݶγ���
    func_no : Integer;              // ���ܺ�
    count : Longint;                // ���ݶ��а����� CARD ��Ϣ����
    data : Char;// ���ݶΣ�����Ϊ���ܺ������,�� '\0' ��Ϊ��β��
  end;
  Pksf_xml_data = ^ksf_xml_data;

  // ���ؽ������
  ksf_ret_result = Integer;
  ksf_card_result = record
    ret : ksf_ret_result;         // ���ؽ��,������  RET_OK , RET_FAILD
    pack_index : Integer;         // ����İ��� index
  end;
  Pksf_card_result = ^ksf_card_result;

  // �ӿں�������
  lp_module_init = function:Integer; stdcall;
  lp_module_release = function:Integer; stdcall;
  lp_module_receive = function(svr : Pksf_server_conf;
                              data : Pksf_xml_data;
                              result : Pksf_card_result):Integer; stdcall;

  ksf_plugin_module = record
    module_name : array[0..MODULE_NAME_LEN] of char;     	// ģ������
    module_path : array[0..MAX_PATH_LEN] of char;         // ģ��·��
    date : array[0..8] of char;                           // ����
    author : array[0..255] of char;                       // ������
    major_ver : ShortInt;                                 // ���汾�š��ΰ汾��
    minor_ver : ShortInt;
    module_init : lp_module_init;                         // ģ���ʼ������ָ��
    module_release : lp_module_release;                   // ģ���ͷź���ָ��
    module_receive : lp_module_receive;                   // ģ�������ܺ��������뱣������
  end;
  Pksf_plugin_module = ^ksf_plugin_module;

implementation

end.

package com.kingstargroup.fdykt;

public interface KSConstant {
	
	/**
	 * ���ݿ����ÿ���
	 */
	static public final String DB_CONFIG = "oracle";
	
	static public boolean drtpinit = false;
	
	static public final String DRTP_IP = "10.49.188.243";
	
	static public final int DRTP_PORT = 4000;
	/**
	 * ϵͳ�����ļ�·��
	 */
	static public final String CONFIG_FILE = "com/kingstargroup/fdykt/ksconfig.properties";
	/**
	 * JNDI ��Դ��
	 */
	static public final String JNDI_RES_NAME = "jndires"; 
	/**
	 * ��ʽ��δ��ʧ,���ܰ���ʱ��
	 */
	static public final int MAINCARD_UNLOSSED = 100559;
	/**
	 * ��һ����ʱ��������ʹ��,�����ٰ���ʱ��
	 */
	static public final int TEMPCARD_EXISTS = 100560;
	
	static public final int CARDTYPE_MAIN = 1;
	
	static public final int DICT_MAINKEY = 2006;
	
	static public final String CARDSTAT_LOGOUT = "2000";
	static public final String CARDSTAT_NORMAL = "1000";
	static public final String CARDSTAT_WFAIL = "1001";
	static public final int CARDSTAT_TYPE_REG = 0;
	static public final int CARDSTAT_TYPE_LOST = 1;
	static public final int CARDSTAT_TYPE_FREEZE = 2;
	static public final int CARDSTAT_TYPE_WFAIL = 3;
	
	static public final char BOOLEAN_TRUE = '1';
	static public final char BOOLEAN_FALSE = '0';
	
	static public final String DICT_AREADEV = "DICT_AREADEVICE";
	static public final String DICT_DEPTNAME = "DICT_DEPTNAME";
	static public final String DICT_SERIALTYPE = "DICT_SERIALTYPE";
	static public final String DICT_FEETYPE = "DICT_FEETYPE";
	static public final String DICT_AREA = "DICT_AREA";
	static public final String DICT_SIDY_STATUS = "DICT_SIDY_STATUS";
	static public final String DICT_SIDY_TYPE = "DICT_SIDY_TYPE";
	static public final String DICT_ERR_CODE = "DICT_ERR_CODE";
}

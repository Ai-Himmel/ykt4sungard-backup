package org.king.web.util;

public class Constants {
	public static final String CURENTDEPT="currentDept";	 //��ǰ����  (DeptInfo)
	public static final String ACCOUNTID="account";		 //��ǰ��¼Id
	public static final String MANAGERDEPTS="managerDepts";//��ǰ������Ĳ��� (List)
	public static final String CURENTROLES="rolesByAccountIdAndDeptId";//��ǰ���ź͵�¼�����õĽ�ɫ
	public static final String LOGIN_NAME="userName";//��ǰ��¼��
	public static final String PERSON_NAME="personName";//��ǰ�û���
	
	public static final String DICTIONUSE="1"; // ʹ��
	public static final String DICTIONNOTUSE="0"; //����
		
    //���ر�ʶ����
	public final static String noName = "��";
	public final static String yesName = "��";
	
    //���ر�ʶ����
	public final static String noCode = "0";
	public final static String yesCode = "1";
	
    //�������ơ��������Ƶȵ�״ֵ̬
	public final static String notCheckName = "δ��";
	public final static String isUsingName = "ʹ��";
	public final static String notUsingName = "����";
    //�������ơ��������Ƶȵ�״̬����
	public final static String notCheckCode = "n";
	public final static String isUsingCode = "1";
	public final static String notUsingCode = "0";
		
	//�������ơ��������Ƶȵ�״̬����
	public final static String[][] mczt = new String[][]{
		{notCheckCode,notCheckName},{isUsingCode,isUsingName},{notUsingCode,notUsingName}
	};
	
    //���ر�ʶ����
	public final static String[][] onoff_flag = new String[][]{
		{noCode,noName},{yesCode,yesName}
	};
}

package org.king.check.config;

public class CommonConfig {

	/*�Կ�����Ϣ�Ĳ�ѯ����*/
	public static final String startDate="startDate" ;
	
	public static final String endDate="endDate";
	
	public static final String deptId="deptId";
	
	public static final String page="page";
	
	public static final String titleStr="titleStr";
	
	public static final String dutyStrs="dutyStrs";
	
	public static final String trueName="trueName";
	
	/*
	 * �������ֵ���Ӧһ��
	 */
	
	/*
	 * ����ϸ����Ϣ��־λ�����ֵ�
	 */
	public static final String late="1";//�ٵ�
	
	public static final String earlyQuit="2";//���� 
	
	public static final String earlycheckin="3";//����������ǰ��ʱ�� 
	
	public static final String latecheckout="4";//���������ͺ��ʱ��
	
	public static final String onDutyOk="5";//�ϰ����� 
	
	public static final String offDutyOk="6";//�°����� 
	
	/*
	 * ������Ϣ��־λ�����ֵ�
	 */
	
	public static final String workInfoException="2";//������Ϣ�쳣
	
	public static final String workInfoOk="5";//������Ϣ����
	
	public static final String absent="4";//����
	
	/*
	 * ��ٱ�־λ
	 */
	public static final String isGlobe="1";
	/*
	 * ��Ҫ�����ı���
	 */
	public static final String table_LEAVEINFO="YKT_CK.LEAVEINFO";
	public static final String table_EXTRAWORKINFO="YKT_CK.EXTRAWORKINFO";
	public static final String table_IRREGULARREST="YKT_CK.IRREGULARREST";
	/*
	 * ���ſ����ƶȱ�ʶ����
	 */
	public static final String restInWKD="1";//��ĩ��Ϣ��ʶ
	public static final String workInWKD="2";//��ĩ�ϰ��ʶ
}

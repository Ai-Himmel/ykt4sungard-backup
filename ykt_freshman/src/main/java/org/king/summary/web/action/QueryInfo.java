/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    QueryInfo.java
 * �������ڣ� 2007-7-6 13:18:52
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-7-6 13:18:52     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.summary.web.action;

public class QueryInfo {
	//ѧ�š��������Ա����塢����¼ȡԺϵ��ѡ�񣩡�¼ȡרҵ��ѡ�񣩡�ѧ�����ѡ��
	//У����8�����֣���¥�ţ�10�����֣���ѡ�񣩡���Ԫ�ţ�10�����֣�������ţ�6λ���֣�
	
	
	private String stuNo;
	private String stuName;
	private String sex;
	private String minZu;
	private String guoJi;
	
	
	private String yuanXi;
	private String zhuanYe;
	private String leiBie;

	private String location;
	private String area;
	private String louHao;
	private String unit;
	private String roomNumber;
	public String getArea() {
		return area;
	}
	public void setArea(String area) {
		this.area = area;
	}

	public String getGuoJi() {
		return guoJi;
	}
	public void setGuoJi(String guoJi) {
		this.guoJi = guoJi;
	}
	public String getLeiBie() {
		return leiBie;
	}
	public void setLeiBie(String leiBie) {
		this.leiBie = leiBie;
	}
	public String getUnit() {
		return unit;
	}
	public void setUnit(String unit) {
		this.unit = unit;
	}
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}
	public String getLouHao() {
		return louHao;
	}
	public void setLouHao(String louHao) {
		this.louHao = louHao;
	}
	
	public String getMinZu() {
		return minZu;
	}
	public void setMinZu(String minZu) {
		this.minZu = minZu;
	}
	public String getRoomNumber() {
		return roomNumber;
	}
	public void setRoomNumber(String roomNumber) {
		this.roomNumber = roomNumber;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	
	public String getStuName() {
		return stuName;
	}
	public void setStuName(String stuName) {
		this.stuName = stuName;
	}
	public String getStuNo() {
		return stuNo;
	}
	public void setStuNo(String stuNo) {
		this.stuNo = stuNo;
	}
	public String getYuanXi() {
		return yuanXi;
	}
	public void setYuanXi(String yuanXi) {
		this.yuanXi = yuanXi;
	}
	public String getZhuanYe() {
		return zhuanYe;
	}
	public void setZhuanYe(String zhuanYe) {
		this.zhuanYe = zhuanYe;
	}
	
}

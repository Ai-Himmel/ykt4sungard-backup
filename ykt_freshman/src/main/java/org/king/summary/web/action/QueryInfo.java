/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    QueryInfo.java
 * 创建日期： 2007-7-6 13:18:52
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-7-6 13:18:52     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.summary.web.action;

public class QueryInfo {
	//学号、姓名、性别、民族、国籍录取院系（选择）、录取专业（选择）、学生类别（选择）
	//校区（8个汉字）、楼号（10个汉字）（选择）、单元号（10个汉字）、宿舍号（6位数字）
	
	
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

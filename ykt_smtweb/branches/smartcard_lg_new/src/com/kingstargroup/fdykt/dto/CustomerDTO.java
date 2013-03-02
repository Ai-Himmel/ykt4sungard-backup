package com.kingstargroup.fdykt.dto;

public class CustomerDTO {
	private int Cut_id;

	private int Cut_type;

	private int Cut_state;

	private String Cut_name;

	private int Area;

	private String Stuemp_no;

	private String Classdept_no;

	private String Classdept_name;

	private String Man;

	private String Sex;

	private int Nation;

	private String Man_id;

	private String Tel;

	private String Address;

	private String Reg_time;

	private String Can_time;

	private String Comments;

	private String Password;

	public void setPassword(String Password) {
		this.Password = Password;
	}

	public String getPassword() {
		return Password;
	}

	public void setComments(String Comments) {
		this.Comments = Comments;
	}

	public String getComments() {
		return Comments;
	}

	public void setCan_time(String Can_time) {
		this.Can_time = Can_time;
	}

	public String getCan_time() {
		return Can_time;
	}

	public void setReg_time(String Reg_time) {
		this.Reg_time = Reg_time;
	}

	public String getReg_time() {
		return Reg_time;
	}

	public void setAddress(String Address) {
		this.Address = Address;
	}

	public String getAddress() {
		return Address;
	}

	public void setTel(String Tel) {
		this.Tel = Tel;
	}

	public String getTel() {
		return Tel;
	}

	public void setMan_id(String Man_id) {
		this.Man_id = Man_id;
	}

	public String getMan_id() {
		return Man_id;
	}

	public void setNation(int Nation) {
		this.Nation = Nation;
	}

	public int getNation() {
		return Nation;
	}

	public void setSex(String Sex) {
		this.Sex = Sex;
	}

	public String getSex() {
		return Sex;
	}

	public void setMan(String Man) {
		this.Man = Man;
	}

	public String getMan() {
		return Man;
	}

	public void setClassdept_name(String Classdept_name) {
		this.Classdept_name = Classdept_name;
	}

	public String getClassdept_name() {
		return Classdept_name;
	}

	public void setClassdept_no(String Classdept_no) {
		this.Classdept_no = Classdept_no;
	}

	public String getClassdept_no() {
		return Classdept_no;
	}

	public void setStuemp_no(String Stuemp_no) {
		this.Stuemp_no = Stuemp_no;
	}

	public String getStuemp_no() {
		return Stuemp_no;
	}

	public void setArea(int Area) {
		this.Area = Area;
	}

	public int getArea() {
		return Area;
	}

	public void setCut_name(String Cut_name) {
		this.Cut_name = Cut_name;
	}

	public String getCut_name() {
		return Cut_name;
	}

	public void setCut_state(int Cut_state) {
		this.Cut_state = Cut_state;
	}

	public int getCut_state() {
		return Cut_state;
	}

	public void setCut_type(int Cut_type) {
		this.Cut_type = Cut_type;
	}

	public int getCut_type() {
		return Cut_type;
	}

	public void setCut_id(int Cut_id) {
		this.Cut_id = Cut_id;
	}

	public int getCut_id() {
		return Cut_id;
	}

}

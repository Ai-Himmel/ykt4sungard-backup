package com.kingstargroup.fdykt.dto;

public class AccountDTO implements java.io.Serializable {
	private String Account_id;

	private long Act_type;

	private long Card_id;

	private long Card_type;

	private float Cur_Bala;

	private float Cur_FreeBala;

	private float Cur_FrozeBala;

	private long Customer_id;

	private int Con_Count;

	private String Open_Date;

	private String Close_Date;

	private String Cut_name;

	private long Cut_type;

	private String IsAutoTra;

	private String Password;

	private long Purse_id;

	private String StuEmp_no;

	private long current_state;

	private String subno;

	private String state_id;

	private String ClassDept_name;

	private String Type_name;

	public String getAccount_id() {
		return Account_id;
	}

	public void setAccount_id(String Account_id) {
		this.Account_id = Account_id;
	}

	public long getAct_type() {
		return Act_type;
	}

	public void setAct_type(long Act_type) {
		this.Act_type = Act_type;
	}

	public long getCard_id() {
		return Card_id;
	}

	public void setCard_id(long Card_id) {
		this.Card_id = Card_id;
	}

	public long getCard_type() {
		return Card_type;
	}

	public void setCard_type(long Card_type) {
		this.Card_type = Card_type;
	}

	public float getCur_Bala() {
		return Cur_Bala;
	}

	public void setCur_Bala(float Cur_Bala) {
		this.Cur_Bala = Cur_Bala;
	}

	public float getCur_FreeBala() {
		return Cur_FreeBala;
	}

	public void setCur_FreeBala(float Cur_FreeBala) {
		this.Cur_FreeBala = Cur_FreeBala;
	}

	public float getCur_FrozeBala() {
		return Cur_FrozeBala;
	}

	public void setCur_FrozeBala(float Cur_FrozeBala) {
		this.Cur_FrozeBala = Cur_FrozeBala;
	}

	public long getCustomer_id() {
		return Customer_id;
	}

	public void setCustomer_id(long Customer_id) {
		this.Customer_id = Customer_id;
	}

	public String getCut_name() {
		return Cut_name;
	}

	public void setCut_name(String Cut_name) {
		this.Cut_name = Cut_name;
	}

	public long getCut_type() {
		return Cut_type;
	}

	public void setCut_type(long Cut_type) {
		this.Cut_type = Cut_type;
	}

	public String getIsAutoTra() {
		return IsAutoTra;
	}

	public void setIsAutoTra(String IsAutoTra) {
		this.IsAutoTra = IsAutoTra;
	}

	public String getPassword() {
		return Password;
	}

	public void setPassword(String Password) {
		this.Password = Password;
	}

	public long getPurse_id() {
		return Purse_id;
	}

	public void setPurse_id(long Purse_id) {
		this.Purse_id = Purse_id;
	}

	public String getStuEmp_no() {
		return StuEmp_no;
	}

	public void setStuEmp_no(String StuEmp_no) {
		this.StuEmp_no = StuEmp_no;
	}

	public long getCurrent_state() {
		return current_state;
	}

	public void setCurrent_state(long current_state) {
		this.current_state = current_state;
	}

	public String getSubno() {
		return subno;
	}

	public String getState_id() {
		return state_id;
	}

	public String getClassDept_name() {
		return ClassDept_name;
	}

	public String getType_name() {
		return Type_name;
	}

	public String getClose_Date() {
		return Close_Date;
	}

	public String getOpen_Date() {
		return Open_Date;
	}

	public int getCon_Count() {
		return Con_Count;
	}

	public void setSubno(String subno) {
		this.subno = subno;
	}

	public void setState_id(String state_id) {
		this.state_id = state_id;
	}

	public void setClassDept_name(String ClassDept_name) {
		this.ClassDept_name = ClassDept_name;
	}

	public void setType_name(String Type_name) {
		this.Type_name = Type_name;
	}

	public void setClose_Date(String Close_Date) {
		this.Close_Date = Close_Date;
	}

	public void setOpen_Date(String Open_Date) {
		this.Open_Date = Open_Date;
	}

	public void setCon_Count(int Con_Count) {
		this.Con_Count = Con_Count;
	}
}

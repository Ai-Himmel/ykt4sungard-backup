package com.kingstargroup.advquery.register.dto;

public class AbstractRegisterPay {
	
	private String stuempNo ;
	private String cutName ;
	private Integer registerFlag;
	private String registerInfo;
	private String operateDate;
	private String operateTime;
	private Integer flag;
	private Integer reserverNo1;
	private String  reserverNo2;
	private Integer reserverNo3;
	
	public AbstractRegisterPay(){}
	
	public AbstractRegisterPay(String stuempNo){
		this.stuempNo = stuempNo;
	}
	
	
	public String getCutName() {
		return cutName;
	}
	public void setCutName(String cutName) {
		this.cutName = cutName;
	}
	public Integer getFlag() {
		return flag;
	}
	public void setFlag(Integer flag) {
		this.flag = flag;
	}
	public String getOperateDate() {
		return operateDate;
	}
	public void setOperateDate(String operateDate) {
		this.operateDate = operateDate;
	}
	public String getOperateTime() {
		return operateTime;
	}
	public void setOperateTime(String operateTime) {
		this.operateTime = operateTime;
	}

	public Integer getRegisterFlag() {
		return registerFlag;
	}

	public void setRegisterFlag(Integer registerFlag) {
		this.registerFlag = registerFlag;
	}

	public String getRegisterInfo() {
		return registerInfo;
	}
	public void setRegisterInfo(String registerInfo) {
		this.registerInfo = registerInfo;
	}

	public String getReserverNo2() {
		return reserverNo2;
	}

	public void setReserverNo2(String reserverNo2) {
		this.reserverNo2 = reserverNo2;
	}

	public Integer getReserverNo1() {
		return reserverNo1;
	}
	public void setReserverNo1(Integer reserverNo1) {
		this.reserverNo1 = reserverNo1;
	}
	public Integer getReserverNo3() {
		return reserverNo3;
	}
	public void setReserverNo3(Integer reserverNo3) {
		this.reserverNo3 = reserverNo3;
	}
	public String getStuempNo() {
		return stuempNo;
	}
	public void setStuempNo(String stuempNo) {
		this.stuempNo = stuempNo;
	}
	  
	

}

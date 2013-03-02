package com.kingstargroup.fdykt.dto;

public class CardDTO implements java.io.Serializable {
	private long cardno;
	private long custid;
	private String cardphyid;
	private String cardstatus;	
	private String cardpwd;
	public long getCardno() {
		return cardno;
	}
	public void setCardno(long cardno) {
		this.cardno = cardno;
	}
	public long getCustid() {
		return custid;
	}
	public void setCustid(long custid) {
		this.custid = custid;
	}
	public String getCardphyid() {
		return cardphyid;
	}
	public void setCardphyid(String cardphyid) {
		this.cardphyid = cardphyid;
	}
	public String getCardstatus() {
		return cardstatus;
	}
	public void setCardstatus(String cardstatus) {
		this.cardstatus = cardstatus;
	}
	public String getCardpwd() {
		return cardpwd;
	}
	public void setCardpwd(String cardpwd) {
		this.cardpwd = cardpwd;
	}

	
 
}

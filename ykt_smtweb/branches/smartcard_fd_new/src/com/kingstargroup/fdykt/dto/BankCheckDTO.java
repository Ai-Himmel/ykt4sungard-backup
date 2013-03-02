package com.kingstargroup.fdykt.dto;

public class BankCheckDTO implements java.io.Serializable {
	
	private String cardHead;
	private int  cardLength;
	private String bankName;
	private String banktype;
	public String getBankName() {
		return bankName;
	}
	public void setBankName(String bankName) {
		this.bankName = bankName;
	}
	public String getBanktype() {
		return banktype;
	}
	public void setBanktype(String banktype) {
		this.banktype = banktype;
	}
	public String getCardHead() {
		return cardHead;
	}
	public void setCardHead(String cardHead) {
		this.cardHead = cardHead;
	}
	public int getCardLength() {
		return cardLength;
	}
	public void setCardLength(int cardLength) {
		this.cardLength = cardLength;
	}
	

}

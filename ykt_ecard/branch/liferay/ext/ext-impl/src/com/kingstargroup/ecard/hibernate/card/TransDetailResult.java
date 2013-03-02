package com.kingstargroup.ecard.hibernate.card;

public class TransDetailResult {
	
	private String tradeName="";
	private String tradePlace="";
	private String tradeTime="";
	private double tradeAmount=0;
	private double balance=0;
	public String getTradeName() {
		return tradeName;
	}
	public void setTradeName(String tradeName) {
		this.tradeName = tradeName;
	}
	public String getTradePlace() {
		return tradePlace;
	}
	public void setTradePlace(String tradePlace) {
		this.tradePlace = tradePlace;
	}
	public String getTradeTime() {
		return tradeTime;
	}
	public void setTradeTime(String tradeTime) {
		this.tradeTime = tradeTime;
	}
	public double getTradeAmount() {
		return tradeAmount;
	}
	public void setTradeAmount(double tradeAmount) {
		this.tradeAmount = tradeAmount;
	}
	public double getBalance() {
		return balance;
	}
	public void setBalance(double balance) {
		this.balance = balance;
	}

	
	
	
}

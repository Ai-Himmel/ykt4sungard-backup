package org.king.monitor.domain;

public class RcvdtlCardResult {
	/** The value of the CARD_NO component of this composite id. */
    private long cardNo;
    
	 /** The value of the TX_DATE component of this composite id. */
    private java.lang.String txDate;   
    
    /** The value of the simple amount property. */
    private double amount;
    
	/**
	 * 
	 */
	public RcvdtlCardResult() {
	}

	/**
	 * @return
	 */
	public double getAmount() {
		return amount;
	}

	public void setAmount(double amount) {
		this.amount = amount;
	}

	public long getCardNo() {
		return cardNo;
	}

	public void setCardNo(long cardNo) {
		this.cardNo = cardNo;
	}

	public java.lang.String getTxDate() {
		return txDate;
	}

	public void setTxDate(java.lang.String txDate) {
		this.txDate = txDate;
	}

	/**
	 * @param amount
	 * @param no
	 * @param date
	 */
	public RcvdtlCardResult( long cardNo, String date, double amount) {
		// TODO Auto-generated constructor stub
		this.amount = amount;
		this.cardNo = cardNo;
		this.txDate = date;
	}


}

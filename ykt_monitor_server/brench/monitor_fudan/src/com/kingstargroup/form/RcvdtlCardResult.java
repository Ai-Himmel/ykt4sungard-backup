package com.kingstargroup.form;

public class RcvdtlCardResult {
	/** The value of the CARD_NO component of this composite id. */
    private java.lang.Integer cardNo;
    
	 /** The value of the TX_DATE component of this composite id. */
    private java.lang.String txDate;   
    
    /** The value of the simple amount property. */
    private java.lang.Integer amount;
    
	/**
	 * @return
	 */
	public java.lang.Integer getAmount() {
		return amount;
	}

	public void setAmount(java.lang.Integer amount) {
		this.amount = amount;
	}

	public java.lang.Integer getCardNo() {
		return cardNo;
	}

	public void setCardNo(java.lang.Integer cardNo) {
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
	public RcvdtlCardResult( Integer cardNo, String date, Integer amount) {
		// TODO Auto-generated constructor stub
		this.amount = amount;
		this.cardNo = cardNo;
		this.txDate = date;
	}


}

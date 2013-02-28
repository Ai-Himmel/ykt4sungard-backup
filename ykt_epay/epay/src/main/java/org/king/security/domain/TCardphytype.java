package org.king.security.domain;


/**
 * TCardphytype entity. @author MyEclipse Persistence Tools
 */

public class TCardphytype implements java.io.Serializable {

	// Fields

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Long cardphytype;
	private String cardphytypename;
	private Boolean useflag;
	private Long cardphytypecode;

	// Constructors

	/** default constructor */
	public TCardphytype() {
	}

	/** full constructor */
	public TCardphytype(Long cardphytype, String cardphytypename,
			Boolean useflag, Long cardphytypecode) {
		this.cardphytype = cardphytype;
		this.cardphytypename = cardphytypename;
		this.useflag = useflag;
		this.cardphytypecode = cardphytypecode;
	}

	// Property accessors

	public Long getCardphytype() {
		return this.cardphytype;
	}

	public void setCardphytype(Long cardphytype) {
		this.cardphytype = cardphytype;
	}

	public String getCardphytypename() {
		return this.cardphytypename;
	}

	public void setCardphytypename(String cardphytypename) {
		this.cardphytypename = cardphytypename;
	}

	public Boolean getUseflag() {
		return this.useflag;
	}

	public void setUseflag(Boolean useflag) {
		this.useflag = useflag;
	}

	public Long getCardphytypecode() {
		return this.cardphytypecode;
	}

	public void setCardphytypecode(Long cardphytypecode) {
		this.cardphytypecode = cardphytypecode;
	}

}
package com.kingstargroup.ecard.hibernate.losecard;
// default package

/**
 * AbstractTLosscardinfoId entity provides the base persistence definition of
 * the TLosscardinfoId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTLosscardinfoId implements java.io.Serializable {

	// Fields

	private long cardno;
	private String shopcode;
	private String regdate;

	// Constructors

	/** default constructor */
	public AbstractTLosscardinfoId() {
	}

	/** full constructor */
	public AbstractTLosscardinfoId(long cardno, String shopcode, String regdate) {
		this.cardno = cardno;
		this.shopcode = shopcode;
		this.regdate = regdate;
	}

	// Property accessors

	public long getCardno() {
		return this.cardno;
	}

	public void setCardno(long cardno) {
		this.cardno = cardno;
	}

	public String getShopcode() {
		return this.shopcode;
	}

	public void setShopcode(String shopcode) {
		this.shopcode = shopcode;
	}

	public String getRegdate() {
		return this.regdate;
	}

	public void setRegdate(String regdate) {
		this.regdate = regdate;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTLosscardinfoId))
			return false;
		AbstractTLosscardinfoId castOther = (AbstractTLosscardinfoId) other;

		return (this.getCardno() == castOther.getCardno())
				&& ((this.getShopcode() == castOther.getShopcode()) || (this
						.getShopcode() != null
						&& castOther.getShopcode() != null && this
						.getShopcode().equals(castOther.getShopcode())))
				&& ((this.getRegdate() == castOther.getRegdate()) || (this
						.getRegdate() != null
						&& castOther.getRegdate() != null && this.getRegdate()
						.equals(castOther.getRegdate())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result + (int) this.getCardno();
		result = 37 * result
				+ (getShopcode() == null ? 0 : this.getShopcode().hashCode());
		result = 37 * result
				+ (getRegdate() == null ? 0 : this.getRegdate().hashCode());
		return result;
	}

}
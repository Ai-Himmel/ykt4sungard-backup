package org.king.check.domain;



/**
 * AbstractTCheckrecord entity provides the base persistence definition of the
 * TCheckrecord entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCheckrecord  implements 	java.io.Serializable {

	// Fields

	private TCheckrecordId id;
	private Integer custid;
	private Integer cardno;
	private String cardphyid;
	private String punchtime;
	private String coldate;
	private Integer status;

	// Constructors

	/** default constructor */
	public AbstractTCheckrecord() {
	}

	/** minimal constructor */
	public AbstractTCheckrecord(TCheckrecordId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTCheckrecord(TCheckrecordId id, Integer custid,
			Integer cardno, String cardphyid, String punchtime,
			String coldate, Integer status) {
		this.id = id;
		this.custid = custid;
		this.cardno = cardno;
		this.cardphyid = cardphyid;
		this.punchtime = punchtime;
		this.coldate = coldate;
		this.status = status;
	}

	// Property accessors

	public TCheckrecordId getId() {
		return this.id;
	}

	public void setId(TCheckrecordId id) {
		this.id = id;
	}

	public Integer getCustid() {
		return this.custid;
	}

	public void setCustid(Integer custid) {
		this.custid = custid;
	}

	public Integer getCardno() {
		return this.cardno;
	}

	public void setCardno(Integer cardno) {
		this.cardno = cardno;
	}

	public String getCardphyid() {
		return this.cardphyid;
	}

	public void setCardphyid(String cardphyid) {
		this.cardphyid = cardphyid;
	}

	public String getPunchtime() {
		return this.punchtime;
	}

	public void setPunchtime(String punchtime) {
		this.punchtime = punchtime;
	}

	public String getColdate() {
		return this.coldate;
	}

	public void setColdate(String coldate) {
		this.coldate = coldate;
	}

	public Integer getStatus() {
		return this.status;
	}

	public void setStatus(Integer status) {
		this.status = status;
	}

}
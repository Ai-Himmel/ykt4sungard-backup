package com.kingstargroup.fdykt.form;

/**
 * AbstractTSyspara entity provides the base persistence definition of the
 * TSyspara entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTSyspara implements java.io.Serializable {

	// Fields

	private Long paraid;
	private String paraval;
	private String paraname;
	private String paraunit;
	private String displayflag;
	private String remark;

	// Constructors

	/** default constructor */
	public AbstractTSyspara() {
	}

	/** minimal constructor */
	public AbstractTSyspara(Long paraid, String paraval) {
		this.paraid = paraid;
		this.paraval = paraval;
	}

	/** full constructor */
	public AbstractTSyspara(Long paraid, String paraval, String paraname,
			String paraunit, String displayflag, String remark) {
		this.paraid = paraid;
		this.paraval = paraval;
		this.paraname = paraname;
		this.paraunit = paraunit;
		this.displayflag = displayflag;
		this.remark = remark;
	}

	// Property accessors

	public Long getParaid() {
		return this.paraid;
	}

	public void setParaid(Long paraid) {
		this.paraid = paraid;
	}

	public String getParaval() {
		return this.paraval;
	}

	public void setParaval(String paraval) {
		this.paraval = paraval;
	}

	public String getParaname() {
		return this.paraname;
	}

	public void setParaname(String paraname) {
		this.paraname = paraname;
	}

	public String getParaunit() {
		return this.paraunit;
	}

	public void setParaunit(String paraunit) {
		this.paraunit = paraunit;
	}

	public String getDisplayflag() {
		return this.displayflag;
	}

	public void setDisplayflag(String displayflag) {
		this.displayflag = displayflag;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

}
package com.kingstargroup.fdykt.newform;

/**
 * AbstractTFeetype entity provides the base persistence definition of the
 * TFeetype entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTFeetype implements java.io.Serializable {

	// Fields

	private Long feetype;
	private String feename;
	private String boardfeeflag;
	private String useflag;
	private String remark;

	// Constructors

	/** default constructor */
	public AbstractTFeetype() {
	}

	/** minimal constructor */
	public AbstractTFeetype(Long feetype) {
		this.feetype = feetype;
	}

	/** full constructor */
	public AbstractTFeetype(Long feetype, String feename, String boardfeeflag,
			String useflag, String remark) {
		this.feetype = feetype;
		this.feename = feename;
		this.boardfeeflag = boardfeeflag;
		this.useflag = useflag;
		this.remark = remark;
	}

	// Property accessors

	public Long getFeetype() {
		return this.feetype;
	}

	public void setFeetype(Long feetype) {
		this.feetype = feetype;
	}

	public String getFeename() {
		return this.feename;
	}

	public void setFeename(String feename) {
		this.feename = feename;
	}

	public String getBoardfeeflag() {
		return this.boardfeeflag;
	}

	public void setBoardfeeflag(String boardfeeflag) {
		this.boardfeeflag = boardfeeflag;
	}

	public String getUseflag() {
		return this.useflag;
	}

	public void setUseflag(String useflag) {
		this.useflag = useflag;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

}
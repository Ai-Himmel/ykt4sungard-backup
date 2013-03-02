package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTFuncList entity provides the base persistence definition of the
 * TFuncList entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTFuncList implements java.io.Serializable {

	// Fields

	private String funcCode;
	private String funcName;
	private String funcUrl;

	// Constructors

	/** default constructor */
	public AbstractTFuncList() {
	}

	/** minimal constructor */
	public AbstractTFuncList(String funcCode) {
		this.funcCode = funcCode;
	}

	/** full constructor */
	public AbstractTFuncList(String funcCode, String funcName, String funcUrl) {
		this.funcCode = funcCode;
		this.funcName = funcName;
		this.funcUrl = funcUrl;
	}

	// Property accessors

	public String getFuncCode() {
		return this.funcCode;
	}

	public void setFuncCode(String funcCode) {
		this.funcCode = funcCode;
	}

	public String getFuncName() {
		return this.funcName;
	}

	public void setFuncName(String funcName) {
		this.funcName = funcName;
	}

	public String getFuncUrl() {
		return this.funcUrl;
	}

	public void setFuncUrl(String funcUrl) {
		this.funcUrl = funcUrl;
	}

}
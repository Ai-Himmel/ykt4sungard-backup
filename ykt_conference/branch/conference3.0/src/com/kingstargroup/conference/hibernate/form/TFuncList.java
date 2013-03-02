package com.kingstargroup.conference.hibernate.form;

/**
 * TFuncList entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TFuncList extends AbstractTFuncList implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TFuncList() {
	}

	/** minimal constructor */
	public TFuncList(String funcCode) {
		super(funcCode);
	}

	/** full constructor */
	public TFuncList(String funcCode, String funcName, String funcUrl) {
		super(funcCode, funcName, funcUrl);
	}

}

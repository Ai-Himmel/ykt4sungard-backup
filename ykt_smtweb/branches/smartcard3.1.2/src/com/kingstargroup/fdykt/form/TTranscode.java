package com.kingstargroup.fdykt.form;

/**
 * TTranscode entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TTranscode extends AbstractTTranscode implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TTranscode() {
	}

	/** minimal constructor */
	public TTranscode(Long transcode) {
		super(transcode);
	}

	/** full constructor */
	public TTranscode(Long transcode, String transname, Long logflag,
			Long limitflag) {
		super(transcode, transname, logflag, limitflag);
	}

}

package com.kingstargroup.fdykt.newform;

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
			Long limitflag, Long feeflag, Long transflag, Long disableflag) {
		super(transcode, transname, logflag, limitflag, feeflag, transflag,
				disableflag);
	}

}

package org.king.monitor.domain;


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
	public TTranscode(long transcode) {
		super(transcode);
	}

	/** full constructor */
	public TTranscode(long transcode, String transname, long logflag,
			long limitflag) {
		super(transcode, transname, logflag, limitflag);
	}

}

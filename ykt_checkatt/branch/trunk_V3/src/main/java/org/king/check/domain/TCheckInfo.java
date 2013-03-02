package org.king.check.domain;


/**
 * TCheckInfo entity. @author MyEclipse Persistence Tools
 */
public class TCheckInfo extends AbstractTCheckInfo implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCheckInfo() {
	}

	/** minimal constructor */
	public TCheckInfo(String id, Integer custId, String checkDate) {
		super(id, custId, checkDate);
	}

	/** full constructor */
	public TCheckInfo(String id, Integer custId, String checkDate,
			String checkinTime, String checkoutTime, Integer checkDuration,
			String locationId, Integer checkNum, Integer delayNum,
			Integer earlyNum, String checkType) {
		super(id, custId, checkDate, checkinTime, checkoutTime, checkDuration,
				locationId, checkNum, delayNum, earlyNum, checkType);
	}

}

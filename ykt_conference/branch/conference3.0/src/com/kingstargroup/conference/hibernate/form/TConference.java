package com.kingstargroup.conference.hibernate.form;

/**
 * TConference entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TConference extends AbstractTConference implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TConference() {
	}

	/** full constructor */
	public TConference(String conName, String roomId, String typeName,
			String conBegindate, String conSigntime, String conBegintime,
			String conEnddate, String conEndtime, String organigerId,
			String compere, String conExplain, String ifSerecy, String status,
			String content, String comments, String preplan1, String preplan2,
			String preplan3) {
		super(conName, roomId, typeName, conBegindate, conSigntime,
				conBegintime, conEnddate, conEndtime, organigerId, compere,
				conExplain, ifSerecy, status, content, comments, preplan1,
				preplan2, preplan3);
	}

}

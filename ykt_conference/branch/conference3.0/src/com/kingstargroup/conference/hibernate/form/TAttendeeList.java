package com.kingstargroup.conference.hibernate.form;

/**
 * TAttendeeList entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TAttendeeList extends AbstractTAttendeeList implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TAttendeeList() {
	}

	/** minimal constructor */
	public TAttendeeList(TAttendeeListId id) {
		super(id);
	}

	/** full constructor */
	public TAttendeeList(TAttendeeListId id, long cardNo, String allotDate,
			String allotTime, String sendSign, String delSign,
			String attendeeType, String attendSign, String attendDate,
			String attendTime, String leaveReason, String replacerId,
			String replacerName, String replacerDept, String replacerDuty,
			String replacerComments, long delegray, String cutName,
			String deptName, String stuempNo, String sex) {
		super(id, cardNo, allotDate, allotTime, sendSign, delSign,
				attendeeType, attendSign, attendDate, attendTime, leaveReason,
				replacerId, replacerName, replacerDept, replacerDuty,
				replacerComments, delegray, cutName, deptName, stuempNo, sex);
	}

}

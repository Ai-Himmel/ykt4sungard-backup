package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTConference entity provides the base persistence definition of the
 * TConference entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTConference implements java.io.Serializable {

	// Fields

	private long conId;
	private String conName;
	private String roomId;
	private String typeName;
	private String conBegindate;
	private String conSigntime;
	private String conBegintime;
	private String conEnddate;
	private String conEndtime;
	private String organigerId;
	private String compere;
	private String conExplain;
	private String ifSerecy;
	private String status;
	private String content;
	private String comments;
	private String preplan1;
	private String preplan2;
	private String preplan3;

	// Constructors

	/** default constructor */
	public AbstractTConference() {
	}

	/** full constructor */
	public AbstractTConference(String conName, String roomId, String typeName,
			String conBegindate, String conSigntime, String conBegintime,
			String conEnddate, String conEndtime, String organigerId,
			String compere, String conExplain, String ifSerecy, String status,
			String content, String comments, String preplan1, String preplan2,
			String preplan3) {
		this.conName = conName;
		this.roomId = roomId;
		this.typeName = typeName;
		this.conBegindate = conBegindate;
		this.conSigntime = conSigntime;
		this.conBegintime = conBegintime;
		this.conEnddate = conEnddate;
		this.conEndtime = conEndtime;
		this.organigerId = organigerId;
		this.compere = compere;
		this.conExplain = conExplain;
		this.ifSerecy = ifSerecy;
		this.status = status;
		this.content = content;
		this.comments = comments;
		this.preplan1 = preplan1;
		this.preplan2 = preplan2;
		this.preplan3 = preplan3;
	}

	// Property accessors

	public long getConId() {
		return this.conId;
	}

	public void setConId(long conId) {
		this.conId = conId;
	}

	public String getConName() {
		return this.conName;
	}

	public void setConName(String conName) {
		this.conName = conName;
	}

	public String getRoomId() {
		return this.roomId;
	}

	public void setRoomId(String roomId) {
		this.roomId = roomId;
	}

	public String getTypeName() {
		return this.typeName;
	}

	public void setTypeName(String typeName) {
		this.typeName = typeName;
	}

	public String getConBegindate() {
		return this.conBegindate;
	}

	public void setConBegindate(String conBegindate) {
		this.conBegindate = conBegindate;
	}

	public String getConSigntime() {
		return this.conSigntime;
	}

	public void setConSigntime(String conSigntime) {
		this.conSigntime = conSigntime;
	}

	public String getConBegintime() {
		return this.conBegintime;
	}

	public void setConBegintime(String conBegintime) {
		this.conBegintime = conBegintime;
	}

	public String getConEnddate() {
		return this.conEnddate;
	}

	public void setConEnddate(String conEnddate) {
		this.conEnddate = conEnddate;
	}

	public String getConEndtime() {
		return this.conEndtime;
	}

	public void setConEndtime(String conEndtime) {
		this.conEndtime = conEndtime;
	}

	public String getOrganigerId() {
		return this.organigerId;
	}

	public void setOrganigerId(String organigerId) {
		this.organigerId = organigerId;
	}

	public String getCompere() {
		return this.compere;
	}

	public void setCompere(String compere) {
		this.compere = compere;
	}

	public String getConExplain() {
		return this.conExplain;
	}

	public void setConExplain(String conExplain) {
		this.conExplain = conExplain;
	}

	public String getIfSerecy() {
		return this.ifSerecy;
	}

	public void setIfSerecy(String ifSerecy) {
		this.ifSerecy = ifSerecy;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getContent() {
		return this.content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public String getComments() {
		return this.comments;
	}

	public void setComments(String comments) {
		this.comments = comments;
	}

	public String getPreplan1() {
		return this.preplan1;
	}

	public void setPreplan1(String preplan1) {
		this.preplan1 = preplan1;
	}

	public String getPreplan2() {
		return this.preplan2;
	}

	public void setPreplan2(String preplan2) {
		this.preplan2 = preplan2;
	}

	public String getPreplan3() {
		return this.preplan3;
	}

	public void setPreplan3(String preplan3) {
		this.preplan3 = preplan3;
	}

}
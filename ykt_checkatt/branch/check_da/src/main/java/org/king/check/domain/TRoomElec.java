package org.king.check.domain;

public class TRoomElec implements java.io.Serializable {
	
	private String serialno;
	private String updatedate;
	private String updatetime;
	private String personcode;
	private String personname;
	private TRoom  room;
	private String state;
    private Integer isdeal;
	private String transtime;
	
	public TRoomElec() {
		super();
	}
	public String getSerialno() {
		return serialno;
	}
	public void setSerialno(String serialno) {
		this.serialno = serialno;
	}
	public String getUpdatedate() {
		return updatedate;
	}
	public void setUpdatedate(String updatedate) {
		this.updatedate = updatedate;
	}
	public String getUpdatetime() {
		return updatetime;
	}
	public void setUpdatetime(String updatetime) {
		this.updatetime = updatetime;
	}
	public String getPersoncode() {
		return personcode;
	}
	public void setPersoncode(String personcode) {
		this.personcode = personcode;
	}
	public String getPersonname() {
		return personname;
	}
	public void setPersonname(String personname) {
		this.personname = personname;
	}
	
	public TRoom getRoom() {
		return room;
	}
	public void setRoom(TRoom room) {
		this.room = room;
	}

	public String getState() {
		return state;
	}
	public void setState(String state) {
		this.state = state;
	}

    public Integer getIsdeal() {
        return isdeal;
    }

    public void setIsdeal(Integer isdeal) {
        this.isdeal = isdeal;
    }

    public String getTranstime() {
        return transtime;
    }

    public void setTranstime(String transtime) {
        this.transtime = transtime;
    }

    public TRoomElec(String serialno, String updatedate, String updatetime,
			String personcode, String personname, TRoom room, String state,Integer isdeal,String transtime) {
		super();
		this.serialno = serialno;
		this.updatedate = updatedate;
		this.updatetime = updatetime;
		this.personcode = personcode;
		this.personname = personname;
		this.room = room;
		this.state = state;
        this.isdeal = isdeal;
        this.transtime = transtime;
	}

}

package org.king.check.domain;



/**
 * AbstractTArea entity provides the base persistence definition of the TArea entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTArea  implements java.io.Serializable {


    // Fields    

     private String areaCode;
     private String areaName;
     private String fareaCode;
     private Integer areaLevel;
     private String addr;
     private String remark;
     private String oldAreaCode;


    // Constructors

    /** default constructor */
    public AbstractTArea() {
    }

	/** minimal constructor */
    public AbstractTArea(String areaCode) {
        this.areaCode = areaCode;
    }
    
    /** full constructor */
    public AbstractTArea(String areaCode, String areaName, String fareaCode, Integer areaLevel, String addr, String remark, String oldAreaCode) {
        this.areaCode = areaCode;
        this.areaName = areaName;
        this.fareaCode = fareaCode;
        this.areaLevel = areaLevel;
        this.addr = addr;
        this.remark = remark;
        this.oldAreaCode = oldAreaCode;
    }

	public String getAreaCode() {
		return areaCode;
	}

	public void setAreaCode(String areaCode) {
		this.areaCode = areaCode;
	}

	public String getAreaName() {
		return areaName;
	}

	public void setAreaName(String areaName) {
		this.areaName = areaName;
	}

	public String getFareaCode() {
		return fareaCode;
	}

	public void setFareaCode(String fareaCode) {
		this.fareaCode = fareaCode;
	}

	public Integer getAreaLevel() {
		return areaLevel;
	}

	public void setAreaLevel(Integer areaLevel) {
		this.areaLevel = areaLevel;
	}

	public String getAddr() {
		return addr;
	}

	public void setAddr(String addr) {
		this.addr = addr;
	}

	public String getRemark() {
		return remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

	public String getOldAreaCode() {
		return oldAreaCode;
	}

	public void setOldAreaCode(String oldAreaCode) {
		this.oldAreaCode = oldAreaCode;
	}


}
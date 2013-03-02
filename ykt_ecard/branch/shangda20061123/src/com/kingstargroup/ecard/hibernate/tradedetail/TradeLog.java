/**
 * 
 */
package com.kingstargroup.ecard.hibernate.tradedetail;

import java.io.Serializable;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: TradeLog.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-29  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class TradeLog 
	implements Serializable
	{
	private Integer seriType;
	
	private String actId;
	
	private Integer feeType;
	 /** The value of the simple subno property. */
    private java.lang.String subno;

    /** The value of the simple otherActid property. */
    private java.lang.String otherActid;

    /** The value of the simple otherSubno property. */
    private java.lang.String otherSubno;

    /** The value of the simple outorin property. */
    private java.lang.Integer outorin;

    /** The value of the simple opFee property. */
    private java.lang.Double opFee;

    /** The value of the simple newFee property. */
    private java.lang.Double newFee;

    /** The value of the simple curFrozebala property. */
    private java.lang.Double curFrozebala;

    /** The value of the simple warrantType property. */
    private java.lang.Integer warrantType;

    /** The value of the simple warrantNo property. */
    private java.lang.String warrantNo;

    /** The value of the simple operateDate property. */
    private java.lang.String operateDate;

    /** The value of the simple operateTime property. */
    private java.lang.String operateTime;

    /** The value of the simple collectDate property. */
    private java.lang.String collectDate;

    /** The value of the simple collectTime property. */
    private java.lang.String collectTime;

    /** The value of the simple enteractDate property. */
    private java.lang.String enteractDate;

    /** The value of the simple enteractTime property. */
    private java.lang.String enteractTime;

    /** The value of the simple maindeviceId property. */
    private java.lang.Integer maindeviceId;

    /** The value of the simple deviceId property. */
    private java.lang.Integer deviceId;

    /** The value of the simple annex property. */
    private java.lang.Integer annex;

    /** The value of the simple recordOper property. */
    private java.lang.String recordOper;

    /** The value of the simple checkOper property. */
    private java.lang.String checkOper;

    /** The value of the simple writeOper property. */
    private java.lang.String writeOper;

    /** The value of the simple reserve1 property. */
    private java.lang.String reserve1;

    /** The value of the simple reserve2 property. */
    private java.lang.String reserve2;

    /** The value of the simple reserve3 property. */
    private java.lang.String reserve3;

    /** The value of the simple comments property. */
    private java.lang.String comments;
	/**
	 * 
	 */
	public TradeLog() {
		super();
		// TODO Auto-generated constructor stub
	}
	
	public TradeLog(Integer feeType, 
					String actId, 
					Integer seriType, 
					String subno, 
					String otherActid, 
					String otherSubno, 
					Integer outorin, 
					Double opFee, 
					Double newFee, 
					Double curFrozebala, 
					Integer warrantType, 
					String warrantNo, 
					String operateDate, 
					String operateTime, 
					String collectDate, 
					String collectTime, 
					String enteractDate, 
					String enteractTime, 
					Integer maindeviceId, 
					Integer deviceId, 
					Integer annex, 
					String recordOper, 
					String checkOper, 
					String writeOper, 
					String reserve1, 
					String reserve2, 
					String reserve3, 
					String comments
					) {
		setFeeType(feeType);
		setSeriType(seriType);
		setActId(actId);
		setSubno(subno);
		setAnnex(annex);
		setCheckOper(checkOper);
		setCollectDate(collectDate);
		setCollectTime(collectTime);
		setComments(comments);
		setCurFrozebala(curFrozebala);
		setDeviceId(deviceId);
		setEnteractDate(enteractDate);
		setEnteractTime(enteractTime);
		setMaindeviceId(maindeviceId);
		setNewFee(newFee);
		setOperateDate(operateDate);
		setOperateTime(operateTime);
		setOpFee(opFee);
		setOtherActid(otherActid);
		setOtherSubno(otherSubno);
		setOutorin(outorin);
		setRecordOper(recordOper);
		setReserve1(reserve1);
		setReserve2(reserve2);
		setReserve3(reserve3);
		setSubno(subno);
		setWarrantNo(warrantNo);
		setWriteOper(writeOper);
	}
    /**
     * Return the value of the SUBNO column.
     * @return java.lang.String
     */
    public java.lang.String getSubno()
    {
        return this.subno;
    }

    /**
     * Set the value of the SUBNO column.
     * @param subno
     */
    public void setSubno(java.lang.String subno)
    {
        this.subno = subno;
    }

    /**
     * Return the value of the OTHER_ACTID column.
     * @return java.lang.String
     */
    public java.lang.String getOtherActid()
    {
        return this.otherActid;
    }

    /**
     * Set the value of the OTHER_ACTID column.
     * @param otherActid
     */
    public void setOtherActid(java.lang.String otherActid)
    {
        this.otherActid = otherActid;
    }

    /**
     * Return the value of the OTHER_SUBNO column.
     * @return java.lang.String
     */
    public java.lang.String getOtherSubno()
    {
        return this.otherSubno;
    }

    /**
     * Set the value of the OTHER_SUBNO column.
     * @param otherSubno
     */
    public void setOtherSubno(java.lang.String otherSubno)
    {
        this.otherSubno = otherSubno;
    }

    /**
     * Return the value of the OUTORIN column.
     * @return java.lang.Integer
     */
    public java.lang.Integer getOutorin()
    {
        return this.outorin;
    }

    /**
     * Set the value of the OUTORIN column.
     * @param outorin
     */
    public void setOutorin(java.lang.Integer outorin)
    {
        this.outorin = outorin;
    }

    /**
     * Return the value of the OP_FEE column.
     * @return java.lang.Double
     */
    public java.lang.Double getOpFee()
    {
        return this.opFee;
    }

    /**
     * Set the value of the OP_FEE column.
     * @param opFee
     */
    public void setOpFee(java.lang.Double opFee)
    {
        this.opFee = opFee;
    }

    /**
     * Return the value of the NEW_FEE column.
     * @return java.lang.Double
     */
    public java.lang.Double getNewFee()
    {
        return this.newFee;
    }

    /**
     * Set the value of the NEW_FEE column.
     * @param newFee
     */
    public void setNewFee(java.lang.Double newFee)
    {
        this.newFee = newFee;
    }

    /**
     * Return the value of the CUR_FROZEBALA column.
     * @return java.lang.Double
     */
    public java.lang.Double getCurFrozebala()
    {
        return this.curFrozebala;
    }

    /**
     * Set the value of the CUR_FROZEBALA column.
     * @param curFrozebala
     */
    public void setCurFrozebala(java.lang.Double curFrozebala)
    {
        this.curFrozebala = curFrozebala;
    }

    /**
     * Return the value of the WARRANT_TYPE column.
     * @return java.lang.Integer
     */
    public java.lang.Integer getWarrantType()
    {
        return this.warrantType;
    }

    /**
     * Set the value of the WARRANT_TYPE column.
     * @param warrantType
     */
    public void setWarrantType(java.lang.Integer warrantType)
    {
        this.warrantType = warrantType;
    }

    /**
     * Return the value of the WARRANT_NO column.
     * @return java.lang.String
     */
    public java.lang.String getWarrantNo()
    {
        return this.warrantNo;
    }

    /**
     * Set the value of the WARRANT_NO column.
     * @param warrantNo
     */
    public void setWarrantNo(java.lang.String warrantNo)
    {
        this.warrantNo = warrantNo;
    }

    /**
     * Return the value of the OPERATE_DATE column.
     * @return java.lang.String
     */
    public java.lang.String getOperateDate()
    {
        return this.operateDate;
    }

    /**
     * Set the value of the OPERATE_DATE column.
     * @param operateDate
     */
    public void setOperateDate(java.lang.String operateDate)
    {
        this.operateDate = operateDate;
    }

    /**
     * Return the value of the OPERATE_TIME column.
     * @return java.lang.String
     */
    public java.lang.String getOperateTime()
    {
        return this.operateTime;
    }

    /**
     * Set the value of the OPERATE_TIME column.
     * @param operateTime
     */
    public void setOperateTime(java.lang.String operateTime)
    {
        this.operateTime = operateTime;
    }

    /**
     * Return the value of the COLLECT_DATE column.
     * @return java.lang.String
     */
    public java.lang.String getCollectDate()
    {
        return this.collectDate;
    }

    /**
     * Set the value of the COLLECT_DATE column.
     * @param collectDate
     */
    public void setCollectDate(java.lang.String collectDate)
    {
        this.collectDate = collectDate;
    }

    /**
     * Return the value of the COLLECT_TIME column.
     * @return java.lang.String
     */
    public java.lang.String getCollectTime()
    {
        return this.collectTime;
    }

    /**
     * Set the value of the COLLECT_TIME column.
     * @param collectTime
     */
    public void setCollectTime(java.lang.String collectTime)
    {
        this.collectTime = collectTime;
    }

    /**
     * Return the value of the ENTERACT_DATE column.
     * @return java.lang.String
     */
    public java.lang.String getEnteractDate()
    {
        return this.enteractDate;
    }

    /**
     * Set the value of the ENTERACT_DATE column.
     * @param enteractDate
     */
    public void setEnteractDate(java.lang.String enteractDate)
    {
        this.enteractDate = enteractDate;
    }

    /**
     * Return the value of the ENTERACT_TIME column.
     * @return java.lang.String
     */
    public java.lang.String getEnteractTime()
    {
        return this.enteractTime;
    }

    /**
     * Set the value of the ENTERACT_TIME column.
     * @param enteractTime
     */
    public void setEnteractTime(java.lang.String enteractTime)
    {
        this.enteractTime = enteractTime;
    }

    /**
     * Return the value of the MAINDEVICE_ID column.
     * @return java.lang.Integer
     */
    public java.lang.Integer getMaindeviceId()
    {
        return this.maindeviceId;
    }

    /**
     * Set the value of the MAINDEVICE_ID column.
     * @param maindeviceId
     */
    public void setMaindeviceId(java.lang.Integer maindeviceId)
    {
        this.maindeviceId = maindeviceId;
    }

    /**
     * Return the value of the DEVICE_ID column.
     * @return java.lang.Integer
     */
    public java.lang.Integer getDeviceId()
    {
        return this.deviceId;
    }

    /**
     * Set the value of the DEVICE_ID column.
     * @param deviceId
     */
    public void setDeviceId(java.lang.Integer deviceId)
    {
        this.deviceId = deviceId;
    }

    /**
     * Return the value of the ANNEX column.
     * @return java.lang.Integer
     */
    public java.lang.Integer getAnnex()
    {
        return this.annex;
    }

    /**
     * Set the value of the ANNEX column.
     * @param annex
     */
    public void setAnnex(java.lang.Integer annex)
    {
        this.annex = annex;
    }

    /**
     * Return the value of the RECORD_OPER column.
     * @return java.lang.String
     */
    public java.lang.String getRecordOper()
    {
        return this.recordOper;
    }

    /**
     * Set the value of the RECORD_OPER column.
     * @param recordOper
     */
    public void setRecordOper(java.lang.String recordOper)
    {
        this.recordOper = recordOper;
    }

    /**
     * Return the value of the CHECK_OPER column.
     * @return java.lang.String
     */
    public java.lang.String getCheckOper()
    {
        return this.checkOper;
    }

    /**
     * Set the value of the CHECK_OPER column.
     * @param checkOper
     */
    public void setCheckOper(java.lang.String checkOper)
    {
        this.checkOper = checkOper;
    }

    /**
     * Return the value of the WRITE_OPER column.
     * @return java.lang.String
     */
    public java.lang.String getWriteOper()
    {
        return this.writeOper;
    }

    /**
     * Set the value of the WRITE_OPER column.
     * @param writeOper
     */
    public void setWriteOper(java.lang.String writeOper)
    {
        this.writeOper = writeOper;
    }

    /**
     * Return the value of the RESERVE_1 column.
     * @return java.lang.String
     */
    public java.lang.String getReserve1()
    {
        return this.reserve1;
    }

    /**
     * Set the value of the RESERVE_1 column.
     * @param reserve1
     */
    public void setReserve1(java.lang.String reserve1)
    {
        this.reserve1 = reserve1;
    }

    /**
     * Return the value of the RESERVE_2 column.
     * @return java.lang.String
     */
    public java.lang.String getReserve2()
    {
        return this.reserve2;
    }

    /**
     * Set the value of the RESERVE_2 column.
     * @param reserve2
     */
    public void setReserve2(java.lang.String reserve2)
    {
        this.reserve2 = reserve2;
    }

    /**
     * Return the value of the RESERVE_3 column.
     * @return java.lang.String
     */
    public java.lang.String getReserve3()
    {
        return this.reserve3;
    }

    /**
     * Set the value of the RESERVE_3 column.
     * @param reserve3
     */
    public void setReserve3(java.lang.String reserve3)
    {
        this.reserve3 = reserve3;
    }

    /**
     * Return the value of the COMMENTS column.
     * @return java.lang.String
     */
    public java.lang.String getComments()
    {
        return this.comments;
    }

    /**
     * Set the value of the COMMENTS column.
     * @param comments
     */
    public void setComments(java.lang.String comments)
    {
        this.comments = comments;
    }

	/**
	 * @return Returns the actId.
	 */
	public String getActId() {
		return actId;
	}

	/**
	 * @param actId The actId to set.
	 */
	public void setActId(String actId) {
		this.actId = actId;
	}

	/**
	 * @return Returns the feeType.
	 */
	public Integer getFeeType() {
		return feeType;
	}

	/**
	 * @param feeType The feeType to set.
	 */
	public void setFeeType(Integer feeType) {
		this.feeType = feeType;
	}

	/**
	 * @return Returns the seriType.
	 */
	public Integer getSeriType() {
		return seriType;
	}

	/**
	 * @param seriType The seriType to set.
	 */
	public void setSeriType(Integer seriType) {
		this.seriType = seriType;
	}

}

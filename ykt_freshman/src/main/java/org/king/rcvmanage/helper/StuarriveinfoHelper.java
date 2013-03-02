/**
 * 
 */
package org.king.rcvmanage.helper;

import java.sql.Time;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;
import org.apache.commons.beanutils.BeanUtils;
import org.king.rcvmanage.domain.Stuarriveinfo;

/**
 * @author jackey
 *
 */
public class StuarriveinfoHelper {
	
	    // Fields    

	     private String id;
	     private String enrollNo;
	     private String stuName;
	     private String classNo;
	     private Date arriveDate;
	     private Time arriveTime;
	     private String arrivePlace;
	     private String trainNo;
	     private String trainRoomNo;
	     private Integer companyNum;
	     private String ifNeedHelp;
	     private String ifNeedBus;
	     private String memo;
	     private String ifDeleted;
	     private String creatorId;
	     private Timestamp createTime;
	     private String updatorId;
	     private Timestamp updateTime;


	    // Constructors

	    /** default constructor */
	    public StuarriveinfoHelper() {
	    }

		/** minimal constructor */
	    public StuarriveinfoHelper(String Id,String enrollNo, Date arriveDate, Time arriveTime, String arrivePlace, String trainNo, String trainRoomNo, Integer companyNum, String ifNeedHelp, String ifNeedBus, String ifDeleted, String creatorId, Timestamp createTime, String updatorId, Timestamp updateTime) {
	        this.id=Id;
	    	this.enrollNo = enrollNo;
	        this.arriveDate = arriveDate;
	        this.arriveTime = arriveTime;
	        this.arrivePlace = arrivePlace;
	        this.trainNo = trainNo;
	        this.trainRoomNo = trainRoomNo;
	        this.companyNum = companyNum;
	        this.ifNeedHelp = ifNeedHelp;
	        this.ifNeedBus = ifNeedBus;
	        this.ifDeleted = ifDeleted;
	        this.creatorId = creatorId;
	        this.createTime = createTime;
	        this.updatorId = updatorId;
	        this.updateTime = updateTime;
	    }
	    
	    /** full constructor */
	    public StuarriveinfoHelper(String Id,String enrollNo, Date arriveDate, Time arriveTime, String arrivePlace, String trainNo, String trainRoomNo, Integer companyNum, String ifNeedHelp, String ifNeedBus, String memo, String ifDeleted, String creatorId, Timestamp createTime, String updatorId, Timestamp updateTime) {
	        this.id=Id;
	    	this.enrollNo = enrollNo;
	        this.arriveDate = arriveDate;
	        this.arriveTime = arriveTime;
	        this.arrivePlace = arrivePlace;
	        this.trainNo = trainNo;
	        this.trainRoomNo = trainRoomNo;
	        this.companyNum = companyNum;
	        this.ifNeedHelp = ifNeedHelp;
	        this.ifNeedBus = ifNeedBus;
	        this.memo = memo;
	        this.ifDeleted = ifDeleted;
	        this.creatorId = creatorId;
	        this.createTime = createTime;
	        this.updatorId = updatorId;
	        this.updateTime = updateTime;
	    }
	    
	    public StuarriveinfoHelper(Stuarriveinfo stuarriveinfo){
	    	try{
	    		BeanUtils.copyProperties(this,stuarriveinfo);
	    	}catch(Exception e){
	    		e.printStackTrace();
	    	}
	    }

	   
	    // Property accessors

	    public String getId() {
	        return this.id;
	    }
	    
	    public void setId(String id) {
	        this.id = id;
	    }

	    public String getEnrollNo() {
	        return this.enrollNo;
	    }
	    
	    public void setEnrollNo(String enrollNo) {
	        this.enrollNo = enrollNo;
	    }
	    
	    public String getStuName() {
	        return this.stuName;
	    }
	    
	    public void setStuName(String stuName) {
	        this.stuName = stuName;
	    }
	    
	    public String getClassNo() {
	        return this.classNo;
	    }
	    
	    public void setClassNo(String classNo) {
	        this.classNo = classNo;
	    }

	    public String getArriveDate() {
	    	SimpleDateFormat formatter=new SimpleDateFormat("yyyy-MM-dd");
			String date=formatter.format(this.arriveDate);
		    return date;
	    }
	    
	    public void setArriveDate(Date arriveDate) {
	        this.arriveDate = arriveDate;
	    }

	    public String getArriveTime() {
	    	SimpleDateFormat formatter=new SimpleDateFormat("HH:mm:ss");
			String time=formatter.format(this.arriveTime);
		    return time;
	    }
	    
	    public void setArriveTime(Time arriveTime) {
	        this.arriveTime = arriveTime;
	    }

	    public String getArrivePlace() {
	        return this.arrivePlace;
	    }
	    
	    public void setArrivePlace(String arrivePlace) {
	        this.arrivePlace = arrivePlace;
	    }

	    public String getTrainNo() {
	        return this.trainNo;
	    }
	    
	    public void setTrainNo(String trainNo) {
	        this.trainNo = trainNo;
	    }

	    public String getTrainRoomNo() {
	        return this.trainRoomNo;
	    }
	    
	    public void setTrainRoomNo(String trainRoomNo) {
	        this.trainRoomNo = trainRoomNo;
	    }

	    public String getCompanyNum() {
	    	return String.valueOf(this.companyNum);
	    }
	    
	    public void setCompanyNum(Integer companyNum) {
	        this.companyNum = companyNum;
	    }

	    public String getIfNeedHelp() {
	        return this.ifNeedHelp;
	    }
	    
	    public void setIfNeedHelp(String ifNeedHelp) {
	        this.ifNeedHelp = ifNeedHelp;
	    }

	    public String getIfNeedBus() {
	        return this.ifNeedBus;
	    }
	    
	    public void setIfNeedBus(String ifNeedBus) {
	        this.ifNeedBus = ifNeedBus;
	    }

	    public String getMemo() {
	        return this.memo;
	    }
	    
	    public void setMemo(String memo) {
	        this.memo = memo;
	    }

	    public String getIfDeleted() {
	        return this.ifDeleted;
	    }
	    
	    public void setIfDeleted(String ifDeleted) {
	        this.ifDeleted = ifDeleted;
	    }

	    public String getCreatorId() {
	        return this.creatorId;
	    }
	    
	    public void setCreatorId(String creatorId) {
	        this.creatorId = creatorId;
	    }

	    public String getCreateTime() {
	    	SimpleDateFormat formatter=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String time=formatter.format(this.createTime);
		    return time;
	    }
	    
	    public void setCreateTime(Timestamp createTime) {
	        this.createTime = createTime;
	    }

	    public String getUpdatorId() {
	        return this.updatorId;
	    }
	    
	    public void setUpdatorId(String updatorId) {
	        this.updatorId = updatorId;
	    }

	    public String getUpdateTime() {
	    	SimpleDateFormat formatter=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String time=formatter.format(this.updateTime);
		    return time;
	    }
	    
	    public void setUpdateTime(Timestamp updateTime) {
	        this.updateTime = updateTime;
	    }

}

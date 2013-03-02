/**
 * 
 */
package org.king.rcvmanage.web.action;

import java.sql.Date;
import java.text.SimpleDateFormat;

import org.apache.struts.action.ActionForm;

/**
 * @author jackey
 *
 */
public class StuarriveinfoForm extends ActionForm{

	private String id=null;
	private String enrollNo=null;
	private Date arriveDate=null;
	private Date arriveTime=null;
	private String arrivePlace=null;
	private String trainNo=null;
	private String trainRoomNo=null;
	private int companyNum=0;
	private String ifNeedHelp="0";
	private String ifNeedBus="0";
	private String memo=null;
	private String ifDeleted="0";
	private String creatorId=null;
	private Date createTime=null;
	private String updatorId=null;
	private Date updateTime=null;
	
	public void setId(String id){
		this.id=id;
	}
	public String getId(){
		return this.id;
	}
	public void setEnrollNo(String enrollNo){
		this.enrollNo=enrollNo;
	}
	public String getEnrollNo(){
		return this.enrollNo;
	}
	public void setArriveDate(String arriveDate){
	    this.arriveDate=Date.valueOf(arriveDate);
	}
	public String getArriveDate(){
		SimpleDateFormat formatter=new SimpleDateFormat("yyyy-MM-dd");
		String date=formatter.format(this.arriveDate);
	    return date;
	}
	public void setArriveTime(String arriveTime){
	    this.arriveTime=Date.valueOf(arriveTime);
	}
	public String getArriveTime(){
		SimpleDateFormat formatter=new SimpleDateFormat("HH:mm:ss");
		String time=formatter.format(this.arriveTime);
	    return time;
	}
	public void setArrivePlace(String arrivePlace){
		this.arrivePlace=arrivePlace;
	}
	public String getArrivePlace(){
		return this.arrivePlace;
	}
	public void setTrainNo(String trainNo){
		this.trainNo=trainNo;
	}
	public String getTrainNo(){
		return this.trainNo;
	}
	public void setTrainRoomNo(String trainRoomNo){
		this.trainRoomNo=trainRoomNo;
	}
	public String getTrainRoomNo(){
		return this.trainRoomNo;
	}
	public void setCompanyNum(String companyNum){
		this.companyNum=Integer.parseInt(companyNum);
	}
	public String getCompanyNum(){
		return String.valueOf(this.companyNum);
	}
	public void setIfNeedHelp(String ifNeedHelp){
		this.ifNeedHelp=ifNeedHelp;
	}
	public String getIfNeedHelp(){
		return this.ifNeedHelp;
	}
	public void setIfNeedBus(String ifNeedBus){
		this.ifNeedBus=ifNeedBus;
	}
	public String getIfNeedBus(){
		return this.ifNeedBus;
	}
	public void setMemo(String memo){
		this.memo=memo;
	}
	public String getMemo(){
		return this.memo;
	}
	public void setIfDeleted(String ifDeleted){
		this.ifDeleted=ifDeleted;
	}
	public String getIfDeleted(){
		return this.ifDeleted;
	}
	public void setCreatorId(String creatorId){
		this.creatorId=creatorId;
	}
	public String getCreatorId(){
		return this.creatorId;
	}
	public void setCreateTime(String createTime){
		this.createTime=Date.valueOf(createTime);
	}
	public String getCreateTime(){
		SimpleDateFormat formatter=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String time=formatter.format(this.createTime);
	    return time;
	}
	public void setUpdatorId(String updatorId){
		this.updatorId=updatorId;
	}
	public String getUpdatorId(){
		return this.updatorId;
	}
	public void setUpdateTime(String updateTime){
		this.updateTime=Date.valueOf(updateTime);
	}
	public String getUpdateTime(){
		SimpleDateFormat formatter=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String time=formatter.format(this.updateTime);
	    return time;
	}
}

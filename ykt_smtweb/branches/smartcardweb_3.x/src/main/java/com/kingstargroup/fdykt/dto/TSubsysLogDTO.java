package com.kingstargroup.fdykt.dto;

public class TSubsysLogDTO {
	  // Fields    

    private int id;
    private int custId;
    private String loginName;
    private String logDate;
    private String logTime;
    private int flag;
    private int sussysId;
    private String comments;
/** basic constructor */
    public TSubsysLogDTO(){
   
    }

   
   /** full constructor */
   public TSubsysLogDTO(int custId, String loginName, String logDate, String logTime, int flag, int sussysId, String comments) {
       this.custId = custId;
       this.loginName = loginName;
       this.logDate = logDate;
       this.logTime = logTime;
       this.flag = flag;
       this.sussysId = sussysId;
       this.comments = comments;
   }

  
   // Property accessors

   public int getId() {
       return this.id;
   }
   
   public void setId(int id) {
       this.id = id;
   }

   public int getCustId() {
       return this.custId;
   }
   
   public void setCustId(int custId) {
       this.custId = custId;
   }

   public String getLoginName() {
       return this.loginName;
   }
   
   public void setLoginName(String loginName) {
       this.loginName = loginName;
   }

   public String getLogDate() {
       return this.logDate;
   }
   
   public void setLogDate(String logDate) {
       this.logDate = logDate;
   }

   public String getLogTime() {
       return this.logTime;
   }
   
   public void setLogTime(String logTime) {
       this.logTime = logTime;
   }

   public int getFlag() {
       return this.flag;
   }
   
   public void setFlag(int flag) {
       this.flag = flag;
   }

   public int getSussysId() {
       return this.sussysId;
   }
   
   public void setSussysId(int sussysId) {
       this.sussysId = sussysId;
   }

   public String getComments() {
       return this.comments;
   }
   
   public void setComments(String comments) {
       this.comments = comments;
   }
  

}

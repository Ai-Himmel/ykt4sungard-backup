package org.king.check.service.impl;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.config.ClerkConfig;
import org.king.check.config.CommonConfig;
import org.king.check.dao.CardInfoDAO;
import org.king.check.dao.ClerkDAO;
import org.king.check.dao.DepartmentDAO;
import org.king.check.dao.DutyTimeDAO;
import org.king.check.dao.WorkInfoDao;
import org.king.check.dao.WorkInfoDetailDAO;
import org.king.check.dao.WorkInfoDetailMapDAO;
import org.king.check.domain.CardInfo;
import org.king.check.domain.Clerk;
import org.king.check.domain.Department;
import org.king.check.domain.DutyTime;
import org.king.check.domain.Workinfo;
import org.king.check.domain.Workinfodetail;
import org.king.check.domain.Workinfodetailmap;
import org.king.check.domain.Worktimeconf;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.VacationService;
import org.king.check.service.WorkInfoService;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.springframework.jdbc.core.JdbcTemplate;

/**
 * @author liufei
 *
 */
public class WorkInfoServiceImpl extends BaseService implements WorkInfoService{
	 private static final Log log = LogFactory.getLog(WorkInfoServiceImpl.class);
	
	private WorkInfoDao workInfodao;
		
	private CardInfoDAO cardinfodao;
	
	private ClerkDAO clerkdao;
	
	private VacationService vacationService;
	
	private LeaveInfoService leaveInfoService;

	private DutyTimeDAO dutytimedao;
	
	private WorkInfoDetailDAO workInfoDetailDAO;
	
	private WorkInfoDetailMapDAO workInfoDetailMapDAO;
	
	private  JdbcTemplate jdbcTemplate;
	
	private DepartmentDAO departmentDAO;
	
	public void setCardinfodao(CardInfoDAO cardinfodao) {
		this.cardinfodao = cardinfodao;
	}

	  public void setWorkInfodao(WorkInfoDao workInfodao) {
		this.workInfodao = workInfodao;
	}
	  
	public void setClerkdao(ClerkDAO clerkdao) {
		this.clerkdao = clerkdao;
	}

	public void setVacationService(VacationService vacationService) {
		this.vacationService = vacationService;
	}

	
	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}
	
	public void setDutytimedao(DutyTimeDAO dutytimedao) {
		this.dutytimedao = dutytimedao;
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	public void setWorkInfoDetailDAO(WorkInfoDetailDAO workInfoDetailDAO) {
		this.workInfoDetailDAO = workInfoDetailDAO;
	}
	
	public void setWorkInfoDetailMapDAO(WorkInfoDetailMapDAO workInfoDetailMapDAO) {
		this.workInfoDetailMapDAO = workInfoDetailMapDAO;
	}

	public void setDepartmentDAO(DepartmentDAO departmentDAO) {
		this.departmentDAO = departmentDAO;
	}

	/*通过流水信息生成考勤信息*/
	  public void createAllClerkWorkInfo(Map filter)throws Exception
	  {
		  Date date=new Date();
		  String checkDate=(String)filter.get("checkDate");//格式为0000-00-00
		  Calendar cal=Calendar.getInstance();
		  
		  /*
		   * 如果考勤时间为空 则默认为生成当天的考勤信息
		   */
		  if(!StringUtils.isNotEmpty(checkDate))
		  {
			  cal.setTime(date);
		  }
		  else
		  {
			  checkDate=checkDate.replace('-','/');
			  checkDate=checkDate+" 00:00:00";
			  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
			  cal.setTime(sdf.parse(checkDate));
		  }
		  
		  
		  /*得出在考勤日加班的员工*/
		  String sql="select clerk.CLERKID as clerkId,clerk.DEPARTMENTID as departid " +
		  		" from YKT_CK.CLERK clerk ,YKT_CK.EXTRAWORKINFO extra ,YKT_CK.EXTRAWORKINFOMAP extramap " +
		  		" where extramap.CLERKID=clerk.CLERKID and extra.EXTRAINFOID=extramap.EXTRAINFOID " +
		  		" and extra.STARTDATE<='"+DateFormat.getDateInstance().format(cal.getTime())+" 23:59:59"+"' " +
		  		" and extra.ENDDATE>='"+DateFormat.getDateInstance().format(cal.getTime())+" 00:00:00"+"' " +
		  		" and clerk.ISSEAT='"+ClerkConfig.isSeat+"'";
		  log.debug("sql:"+sql);
		  List clerkListExtra=jdbcTemplate.queryForList(sql);
		  log.debug("get extra clerk List");
		  
		  /*
		   * 按照加班处理业务逻辑
		   */
		  
		  if(!clerkListExtra.isEmpty())
		  {
			  Iterator iteExt=clerkListExtra.iterator();
			  while(iteExt.hasNext())
			  {
				  Map map=(Map)iteExt.next();
				  map.put("checkDate",(String)filter.get("checkDate"));
				  createWorkInfoByClerkId(map);				 //生成考勤数据 
			  }
		  } 
		  log.debug("create extraclerk workInfo");
		  
		  /*找出考勤日特殊休息的员工*/
		  sql=" select clerk.CLERKID as clerkId " +
		  		" from YKT_CK.IRREGULARREST irrest ,YKT_CK.IRREGULARRESTMAP irrmap,YKT_CK.CLERK clerk" +
		  		" where irrmap.CLERKID=clerk.CLERKID and irrest.IRREGULARRESTID=irrmap.IRREGULARRESTID " +
		  		" and irrest.STARTDATE<='"+DateFormat.getDateInstance().format(cal.getTime())+" 23:59:59"+"'" +
		  		" and irrest.ENDDATE>='"+DateFormat.getDateInstance().format(cal.getTime())+" 00:00:00"+"'";
		  log.debug("sql:"+sql);
		  List clerkIrreList=jdbcTemplate.queryForList(sql);
		  log.debug("get irregular clerk list");
		  if(!clerkIrreList.isEmpty())
			  {
			  //按照特殊休息处理业务逻辑
			  }
		  
		  /*是否公休日，否则按照正常逻辑处理*/
		  
			  if(vacationService.isGlobeVacation(cal))
			  {
				  //考勤当天为休息日
			  }else
			  {
				  List departList=departmentDAO.getAll();
				  if(!departList.isEmpty())
				  {
					  Iterator departIte=departList.iterator();
					  while(departIte.hasNext())
					  {
						  Department department=(Department)departIte.next();
						  if(vacationService.isDepartVacation(department.getId(),cal))
						  {
							  continue;//该部门为公休日
						  }
						  sql="select clerk.CLERKID as clerkId " +
			  		      " from YKT_CK.CLERK clerk  " +
			  		      " where clerk.CLERKID not in  (" +
			  		      "select clerk.CLERKID as clerkId" +
			  		      " from YKT_CK.CLERK clerk ,YKT_CK.EXTRAWORKINFO extra ,YKT_CK.EXTRAWORKINFOMAP extramap " +
			  		      " where extramap.CLERKID=clerk.CLERKID and extra.EXTRAINFOID=extramap.EXTRAINFOID " +
			  		      " and extra.STARTDATE<='"+DateFormat.getDateInstance().format(cal.getTime())+" 23:59:59"+"' " +
			  		      " and extra.ENDDATE>='"+DateFormat.getDateInstance().format(cal.getTime())+" 00:00:00"+"' " +
			  		      " and clerk.ISSEAT='"+ClerkConfig.isSeat+"'"+
			  		      ") and clerk.CLERKID not in (" +
			  		      " select clerk.CLERKID as clerkid " +
			  		      " from YKT_CK.IRREGULARREST irrest ,YKT_CK.IRREGULARRESTMAP irrmap,YKT_CK.CLERK clerk" +
			  		      " where irrmap.CLERKID=clerk.CLERKID and irrest.IRREGULARRESTID=irrmap.IRREGULARRESTID " +
			  		      " and irrest.STARTDATE<='"+DateFormat.getDateInstance().format(cal.getTime())+" 23:59:59"+"'" +
			  		      " and irrest.ENDDATE>='"+DateFormat.getDateInstance().format(cal.getTime())+" 00:00:00"+"'"+
			  		      ")"+
			  		      " and clerk.ISSEAT='"+ClerkConfig.isSeat+"'" +
			  		      " and clerk.DEPARTMENTID='"+department.getId()+"'";//按部门找出余下需要考勤的人员
						  log.debug("sql:"+sql);
						  List clerkList=jdbcTemplate.queryForList(sql);
						  log.debug("get regular clerk list");
						  Iterator clerkIte=clerkList.iterator();
						  while(clerkIte.hasNext())
						  {
							  Map  paraMap=(Map)clerkIte.next();
							  paraMap.put("checkDate",(String)filter.get("checkDate"));
							  createWorkInfoByClerkId(paraMap);			//生成考勤数据 
						  }
						  log.debug("create regular clerk workInfo");
					  }//end while
				  }//end if
			  }  
			  log.debug("operation ok");
	  }
	public void saveWorkInfo(Workinfo workInfo)throws BusinessException
	  {
		  this.workInfodao.save(workInfo);
	  }

	  public void updateWorkInfo(Workinfo workInfo)throws BusinessException
	  {
		  this.workInfodao.update(workInfo);
	  }

	  public void getWorkInfoByWorkInfoId(String workInfoId)throws BusinessException
	  {
		  
	  }

	  public void getWorkInfoBySerialId(String serialId)throws BusinessException
	  {
		  
	  }

	  public List getWorkInfosByCardNumber(String cardNumber)throws BusinessException
	  {
		  return null;
	  }
	  public List getClerkWorkInfosDetailByDate(Date startDate, Date endDate, String userId)throws BusinessException
	  {
		  return null;
	  }

	  public List getDepartWorkInfosByDate(Date startDate, Date endDate, String departId)throws BusinessException
	  {
		  return null;
	  }
	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.WorkInfoService#dealWithNoSeatClerk()
	   * @处理不坐班员工信息
	   */
	  public void dealWithNoSeatClerk(Map filter)throws Exception//处理不坐班员工信息
	  {
		  Calendar cal=(Calendar)filter.get("cal");
		  
		  String year,mon,day,hour,min,sec;
		  year=Integer.toString(cal.get(Calendar.YEAR));
		  mon=Integer.toString(cal.get(Calendar.MONTH)+1);
		  if(Integer.parseInt(mon)<10)
			  mon="0"+mon;
		  day=Integer.toString(cal.get(Calendar.DAY_OF_MONTH));
		  if(Integer.parseInt(day)<10)
			  day="0"+day;
		  
		  
		  String checkDate=year+mon+day;
		  /*
		   * 得到非坐班人员卡号
		   */
		  String sql="select account.CARD_ID as card_id ,clerk.CLERKID as clerkid from " +
		  		" YKT_CK.CLERK  clerk,YKT_CUR.T_AIF_ACCOUNT account,YKT_CUR.T_PIF_CARD card " +
		  		" where account.CUSTOMER_ID=clerk.CLERKID and card.CARD_ID=account.CARD_ID and card.STATE_ID='1000'" +
		  		" and clerk.ISSEAT='"+ClerkConfig.isNoSeat+"'";
		  		  
		  List cardList=jdbcTemplate.queryForList(sql);
		  
		  if(!cardList.isEmpty())
		  {
			  Iterator cardIte=cardList.iterator();
			  while(cardIte.hasNext())
			  {
				  Map queryMap=(Map)cardIte.next();
				  /*
				   * 得到流水信息
				   */
				  sql="select txd.TX_DATE as date,txd.TX_TIME as time ,txd.CARD_NO as card_no" +
				  		" from YKT_CK.T_KQ_TXDTL txd " +
				  		" where txd.CARD_NO="+(Integer)queryMap.get("card_id")+" and txd.TX_DATE='"+checkDate+"'" +
				  				"order by txd.TX_TIME asc";
				  log.debug("sql:"+sql);
				  List timeList=jdbcTemplate.queryForList(sql);
				  if(!timeList.isEmpty())
				  {
					  Map temp=(Map)timeList.get(0);
					  String tDate=(String)temp.get("date");
					  String tTime=(String)temp.get("time");
					  Integer tCard_no=(Integer)temp.get("card_no");					  					  
					  
					  int iYear=Integer.parseInt(tDate.substring(0,4));
					  int iMon=Integer.parseInt(tDate.substring(4,6));
					  int iDay=Integer.parseInt(tDate.substring(6));
					  int ihour=Integer.parseInt(tTime.substring(0,2));
					  int iMin=Integer.parseInt(tTime.substring(2,4));
					  int iSec=Integer.parseInt(tTime.substring(4));
					  iMon--;
					  					  
					  cal.set(iYear,iMon,iDay,ihour,iMin,iSec);
					  Date onDutyDate=cal.getTime();

					  Clerk clerk=clerkdao.get((Integer)queryMap.get("clerkid"));
					  
					  DutyTime dutyTime=new DutyTime();
					  dutyTime.setClerk(clerk);
					  dutyTime.setOndutytime(onDutyDate);
					  if(timeList.size()>1)
					  {
						  temp=(Map)timeList.get(timeList.size()-1);
						  tDate=(String)temp.get("date");
						  tTime=(String)temp.get("time");
						  
						  iYear=Integer.parseInt(tDate.substring(0,4));
						  iMon=Integer.parseInt(tDate.substring(4,6));
						  iDay=Integer.parseInt(tDate.substring(6));
						  ihour=Integer.parseInt(tTime.substring(0,2));
						  iMin=Integer.parseInt(tTime.substring(2,4));
						  iSec=Integer.parseInt(tTime.substring(4));
						  iMon--;
						  
						  cal.set(iYear,iMon,iDay,ihour,iMin,iSec);
						  
						  Date offDutyDate=cal.getTime();
						  dutyTime.setOffdutytime(offDutyDate);
					  }
					  dutyTime.setDepartment(clerk.getDepartment());
					  
					  dutytimedao.save(dutyTime);
					  log.debug("save finish");
					  					  
				  }
			  }
		  }
	  

	  }
	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.WorkInfoService#searchClerkForReg(java.util.Map)
	   * @为手工打卡搜索考勤人员
	   */
	  public List searchClerkForReg(Map filter)throws Exception
	  {
		  String sql="select * from (" +
			  "select " +
		"dpart.DEPT_NAME AS departname ," +
		"dpart.DEPT_ID AS dept_id," +
		"cust.CUT_NAME AS clerkname ," +
		"cust.CUT_ID AS cut_id," +
		"cust.STUEMP_NO as stuno," +
		"dict.DICT_VALUE as dict_value ," +
		"(select card.CARD_ID from YKT_CUR.T_PIF_CARD card ,YKT_CUR.T_AIF_ACCOUNT account " +
  		"where card.CARD_ID=account.CARD_ID and account.CUSTOMER_ID=cust.CUT_ID and card.STATE_ID='1000') AS cardnumber ," +
		"dict.DICT_CAPTION as isseat,conf.CONFNAME as confname " +
		" from YKT_CK.DEPARTMENT dpart ,YKT_CK.CLERK clerk,YKT_CK.WORKCONF conf ,YKT_CUR.T_CIF_CUSTOMER cust," +
		" YKT_CK.COM_DICTIONARY dict  ,YKT_CK.WORKCONFMAP  map " +
		" where clerk.DEPARTMENTID=dpart.DEPT_ID  AND conf.WORKCONFID = " +
		"  map.WORKCONFID and  map.CLERKID=clerk.CLERKID " +
		" and  cust.CUT_ID=clerk.CLERKID " +
		" AND dict.DICT_NO=1002 AND dict.DICT_VALUE=clerk.ISSEAT  ) all where 1=1  " ;
	  
	  sql+=StringUtils.isNotEmpty((String)filter.get("trueName"))?" and all.clerkname like '%"+(String)filter.get("trueName")+"%' ":"";
	  sql+=StringUtils.isNotEmpty((String)filter.get("cardNumber"))?" and all.cardnumber  ="+(String)filter.get("cardNumber")+" ":"";
	  sql+=StringUtils.isNotEmpty((String)filter.get("stuNumber"))?" and all.stuno  ='"+(String)filter.get("stuNumber")+"' ":"";
	  sql+=StringUtils.isNotEmpty((String)filter.get("deptId"))?" and all.dept_id  ='"+(String)filter.get("deptId")+"' ":"";
	  sql+=StringUtils.isNotEmpty((String)filter.get("clerkType"))?" and all.dict_value='"+(String)filter.get("clerkType")+"' ":"";
	  
	  log.debug("sql:"+sql);
	  
	  List clerkList=jdbcTemplate.queryForList(sql);
	  
	  return clerkList;
	  }
	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.WorkInfoService#manualRegister(java.util.Map)
	   * @手工打卡
	   */
	  public void manualRegister(Map filter)throws Exception
	  {
		  Calendar cal=Calendar.getInstance();
		  String startDate=(String)filter.get("startDate");
		  String startHour=(String)filter.get("startHour");
		  if(Integer.parseInt(startHour)<10&&Integer.parseInt(startHour)!=0)
			  startHour="0"+startHour;
		  
		  String startMin=(String)filter.get("startMin");
		  if(Integer.parseInt(startMin)<10&&Integer.parseInt(startMin)!=0)
			  startMin="0"+startMin;
		  
		  startDate=startDate.replace('-','/');//日期格式化
		  startDate=startDate+" "+startHour+":"+startMin+":00";
		  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		  cal.setTime(sdf.parse(startDate));
		  
		  String checkDate=Integer.toString(cal.get(Calendar.YEAR))+
		  ((cal.get(Calendar.MONTH)+1)<10?"0"+Integer.toString(cal.get(Calendar.MONTH)+1):Integer.toString(cal.get(Calendar.MONTH)+1))+
		  (cal.get(Calendar.DAY_OF_MONTH)<10?"0"+Integer.toString(cal.get(Calendar.DAY_OF_MONTH)):Integer.toString(cal.get(Calendar.DAY_OF_MONTH)));
		  
		  
		  String checkTime=startHour+startMin+"00";
		  
		  String card_number[]=(String[])filter.get("card_number");
		  
		  String sql;
		  for(int i=0;i<card_number.length;i++)
			  {
			    sql=" insert into YKT_CK.T_KQ_TXDTL " +
			    		"(TX_DATE,TX_TIME,CARD_NO,DEVICE_ID,DEVPHY_ID,SERIAL_NO)" +
			    		"values" +
			    		"('"+checkDate+"','"+checkTime+"',"+card_number[i]+",0,'0',0)";
			    log.debug("sql:"+sql);
			    jdbcTemplate.execute(sql);
			  }
	  }
	  //判断考勤人员的卡号是否有效
	  public String[] judgeIsOwnValidCardByClerkId(String [] clerkIds)throws Exception
	  {
		  String sql="";
		  sql="select customer.CUT_NAME as cut_name, card.CARD_ID as card_id from " +
		  " YKT_CUR.T_PIF_CARD card ,YKT_CUR.T_CIF_CUSTOMER customer,YKT_CK.CLERK clerk ," +
		  " YKT_CUR.T_AIF_ACCOUNT account " +
		  "where customer.CUT_ID=clerk.CLERKID " +
		  "and account.CUSTOMER_ID=clerk.CLERKID and card.CARD_ID=account.CARD_ID and card.STATE_ID='1000'";
		  String card_number[]=new String[clerkIds.length];
		  
		  for(int i=0;i<clerkIds.length;i++)
		  {
			  String tempStr=" and clerk.CLERKID="+clerkIds[i];
			  log.debug("sql:"+sql+tempStr);
			  List tempList=jdbcTemplate.queryForList(sql+tempStr);
			  if(tempList.isEmpty())
			  {
				  return null;
			  }
			  else
			  {
				  Map map=(Map)tempList.get(0);
				  Integer temp=(Integer)map.get("card_id");
				  card_number[i]=temp.toString();
			  }
		  }
		  return card_number;
	  }
	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.WorkInfoService#createWorkInfoByClerkId(java.util.Map)
	   * @生成个人考勤数据
	   * @filter 包含参数为 checkdate，cleckid
	   */
	  public String createWorkInfoByClerkId(Map filter)throws Exception
	  {
		  String  sql;
		  String checkDate=(String)filter.get("checkDate");//格式为0000-00-00
		  Calendar cal=Calendar.getInstance();
		  Date date=new Date();		  
		  String recentTime="000000";
		  String timeConf;
		  Integer confTime;
		  String description="";
		  List tempList;
		  Integer card_id;
		  String errInfo=null;//生成过程中的异常信息
		  int result=0;
		  int lateNum=0,earlyNum=0,lateCheckOut=0,realyCheckIn=0;
		  boolean workInfoException=false;//有异常信息发生标识
		  String detailType="";
		  
		  /*
		   * 如果考勤时间为空 则默认为生成当天的考勤信息
		   */
		  if(!StringUtils.isNotEmpty(checkDate))
		  {
			  cal.setTime(date);
		  }
		  else
		  {
			  checkDate=checkDate.replace('-','/');
			  checkDate=checkDate+" 00:00:00";
			  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
			  cal.setTime(sdf.parse(checkDate));
		  }
		  checkDate=Integer.toString(cal.get(Calendar.YEAR))+
		  ((cal.get(Calendar.MONTH)+1)<10?"0"+Integer.toString(cal.get(Calendar.MONTH)+1):Integer.toString(cal.get(Calendar.MONTH)+1))+
		  (cal.get(Calendar.DAY_OF_MONTH)<10?"0"+Integer.toString(cal.get(Calendar.DAY_OF_MONTH)):Integer.toString(cal.get(Calendar.DAY_OF_MONTH)));
		  log.debug("checkDate:"+checkDate);
		  
		  
		  /*
		   * 得到员工工作时间制度
		   */
		  sql=" select timeconf.WORKTIMECONFID as id ," +
		  		" timeconf.CONFNAME as confname," +
		  		" timeconf.ONDUTYTIME1 as onduty1," +
		  		" timeconf.OFFDUTYTIME1 as offduty1," +
		  		" timeconf.ONDUTYTIME2 as onduty2," +
		  		" timeconf.OFFDUTYTIME2 as offduty2," +
		  		" timeconf.ONDUTYTIME3 as onduty3," +
		  		" timeconf.OFFDUTYTIME3 as offduty3," +
		  		" timeconf.ONDUTYTIME4 as onduty4," +
		  		" timeconf.OFFDUTYTIME4 as offduty4 " +
		  		" from " +
		  		" YKT_CK.CLERK clerk ,YKT_CK.WORKTIMECONF timeconf " +
		  		" where timeconf.WORKTIMECONFID=clerk.WORKTIMECONFID and clerk.CLERKID="+(Integer)filter.get("clerkId");
		  log.debug("sql:"+sql);
		  tempList=jdbcTemplate.queryForList(sql);
		  Map timeMap;
		  if(!tempList.isEmpty())
		  {
			  timeMap=(Map)tempList.get(0);
		  }else
		  {
			  errInfo="缺少员工工作时间制度";
			  return errInfo;
		  }
		  
		  log.debug("getTimeConf");

		  /*
		   * 得到员工考勤制度
		   */
		  sql="select workconf.PERMITLATETIME as latetime,workconf.PREEARLY as earlytime ," +
		  	  "workconf.ONDUTYADVANCEDTIME as ontime,workconf.OFFDUTYLASTTIME as offtime ," +
		  	  "workconf.WORKCONFID as workconfid " +
		  	  " from  YKT_CK.WORKCONFMAP map, YKT_CK.WORKCONF workconf " +
		  	  " where workconf.WORKCONFID=map.WORKCONFID and map.CLERKID="+(Integer)filter.get("clerkId");
		  log.debug("sql:"+sql);
		  Map confMap;
		  tempList=jdbcTemplate.queryForList(sql);
		  if(!tempList.isEmpty())
		  {
			  confMap=(Map)tempList.get(0);
		  }
		  else{
			  errInfo="缺少员工考勤制度";
			  return errInfo;
		  }
		  log.debug("getWorkConf");
		  
		  /*
		   * 得到员工考勤日的流水信息
		   */
		  sql=" select txdtl.TX_DATE as date,txdtl.TX_TIME as time" +
		  		" from YKT_CK.T_KQ_TXDTL txdtl , YKT_CUR.T_AIF_ACCOUNT account ,YKT_CUR.T_PIF_CARD card " +
		  		" where account.CUSTOMER_ID="+(Integer)filter.get("clerkId");
		  sql+=" and card.CARD_ID=account.CARD_ID and card.STATE_ID='1000' " +//建立与有效卡的关联
		  		" and txdtl.CARD_NO=card.CARD_ID and txdtl.TX_DATE='"+checkDate+"'";//得到考勤日期的数据
		  log.debug("sql:"+sql);
		  List dutyList=jdbcTemplate.queryForList(sql);
		  log.debug("getDutyList");
		  
		  /*
		   * 得到卡号
		   */
		  sql="select card.CARD_ID as card_id " +
		  	  " from " +
		  	  " YKT_CUR.T_AIF_ACCOUNT account ,YKT_CUR.T_PIF_CARD card " +
		  	  "where account.CUSTOMER_ID="+(Integer)filter.get("clerkId");
		  sql+=" and card.CARD_ID=account.CARD_ID and card.STATE_ID='1000' ";
		  tempList=jdbcTemplate.queryForList(sql);
		  if(!tempList.isEmpty())
		  {
			  Map tempMap=(Map)tempList.get(0);
			  card_id=(Integer)tempMap.get("card_id");
		  }
		  else
		  {
			  card_id=new Integer(0);
		  }
		  log.debug("getCard_id");
		  
		  /*
		   * 考勤数据初始化
		   */
		  Clerk clerk=clerkdao.get((Integer)filter.get("clerkId"));
		  Workinfo workinfo=new Workinfo();
		  workinfo.setClerkid((Integer)filter.get("clerkId"));
		  workinfo.setDeptid(clerk.getDepartment().getId());
		  workinfo.setIsseat(clerk.getIsseat());
		  workinfo.setRecordtime(new Date());
		  
		  workinfo.setCardnumber(card_id);
		  workinfo.setWorkconfid((String)confMap.get("workconfid"));
		  workinfo.setSerialid(0);//暂时设置为0
		  workinfo.setCheckdate(checkDate);
		  workInfodao.save(workinfo);
		  
		  /*
		   * 没有打卡流水信息，按照旷工处理,结束
		   */
		  if(dutyList.isEmpty())
		  {
			  workinfo.setWorkinfotype(CommonConfig.absent);
			  workinfo.setDescription("旷工缺席");
			  workInfodao.update(workinfo);
			  return errInfo;
		  }

		  
		  /*
		   * @开始分析数据
		   */
	  
		  
		  for(int i=1;i<5;i++)
		  {
			  if(StringUtils.isNotEmpty((String)timeMap.get("onduty"+i)))
				  {
				  /*
				   * 得到离考勤制度最近的时间
				   */
				  Map paraMap=getRecentTime(dutyList,(String)timeMap.get("onduty"+i),true);
				  recentTime=(String)paraMap.get("recentTime");
				  log.debug("on_closest:"+recentTime);
				  String formatTime=recentTime.substring(0,4);
				  timeConf=(String)timeMap.get("onduty"+i);
				  result=Integer.parseInt(timeConf)-Integer.parseInt(formatTime);//得到时间间隔
				  if(result<0)//迟到 只有上班考勤时间以前没有流水信息 才出现此情况
				  {
					  confTime=(Integer)confMap.get("latetime");
					  result=(getInterval(timeConf,recentTime)).intValue();
					  if(result>confTime.intValue())//超过允许迟到时间范围
					  {
						  lateNum++;
						  workInfoException=true;
						  detailType=CommonConfig.late;
						  log.debug("late");					  
					  }
					  else//按正常情况处理
					  {
						  /*
						   * 记录流水信息
						   */
						  Workinfodetail workinfodetail=new Workinfodetail();
						  workinfodetail.setCheckdate(checkDate);
						  workinfodetail.setDutycheckdate(recentTime);
						  workinfodetail.setExceptionmins(new Integer(result));
						  workinfodetail.setInfotype(CommonConfig.onDutyOk);
						  workInfoDetailDAO.save(workinfodetail);
						  
						  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
						  workinfodetailmap.setWorkinfo(workinfo);
						  workinfodetailmap.setWorkinfodetail(workinfodetail);
						  workInfoDetailMapDAO.save(workinfodetailmap);
					  }
				  }
				  else//上班考勤时间以前打卡
				  {
					  confTime=(Integer)confMap.get("ontime");
					  result=(getInterval(timeConf,recentTime)).intValue();
					  if(result>confTime.intValue())//超过允许提前打卡范围
					  {
						  if(StringUtils.isNotEmpty((String)paraMap.get("bakTime")))
						  {
							  int tempResult=(getInterval(timeConf,(String)paraMap.get("bakTime"))).intValue();
							  log.debug("adjustDate:"+(String)paraMap.get("bakTime"));
							  if(tempResult>((Integer)confMap.get("latetime")).intValue())//超过允许迟到范围
							  {
								  realyCheckIn++;
								  workInfoException=true;
								  detailType=CommonConfig.earlycheckin;
							  }
							  else{
								  //按正常情况处理
								  /*
								   * 记录流水信息
								   */
								  Workinfodetail workinfodetail=new Workinfodetail();
								  workinfodetail.setCheckdate(checkDate);
								  workinfodetail.setDutycheckdate((String)paraMap.get("bakTime"));
								  workinfodetail.setExceptionmins(new Integer(tempResult));
								  workinfodetail.setInfotype(CommonConfig.onDutyOk);
								  workInfoDetailDAO.save(workinfodetail);
								  
								  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
								  workinfodetailmap.setWorkinfo(workinfo);
								  workinfodetailmap.setWorkinfodetail(workinfodetail);
								  workInfoDetailMapDAO.save(workinfodetailmap);
							  }
						  }
						  else
						  {
							  realyCheckIn++;
							  workInfoException=true;
							  detailType=CommonConfig.earlycheckin;
						  }						  
					  }
					  else//按正常情况处理
					  {
						  /*
						   * 记录流水信息
						   */
						  Workinfodetail workinfodetail=new Workinfodetail();
						  workinfodetail.setCheckdate(checkDate);
						  workinfodetail.setDutycheckdate(recentTime);
						  workinfodetail.setExceptionmins(new Integer(result));
						  workinfodetail.setInfotype(CommonConfig.onDutyOk);
						  workInfoDetailDAO.save(workinfodetail);
						  
						  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
						  workinfodetailmap.setWorkinfo(workinfo);
						  workinfodetailmap.setWorkinfodetail(workinfodetail);
						  workInfoDetailMapDAO.save(workinfodetailmap);
					  }
				  }//end else 
				  }// end if 
			  /*
			   * 生成考勤细节
			   */
			  if(workInfoException)
			  {
				  Workinfodetail workinfodetail=new Workinfodetail();
				  workinfodetail.setCheckdate(checkDate);
				  workinfodetail.setDutycheckdate(recentTime);
				  workinfodetail.setExceptionmins(new Integer(result));
				  if(detailType.equals(CommonConfig.late))
				  {
					  workinfodetail.setInfotype(CommonConfig.late);
				  }
				  else if(detailType.equals(CommonConfig.earlycheckin))
				  {
					  workinfodetail.setInfotype(CommonConfig.earlycheckin);
				  }
				  workInfoDetailDAO.save(workinfodetail);
				  
				  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
				  workinfodetailmap.setWorkinfo(workinfo);
				  workinfodetailmap.setWorkinfodetail(workinfodetail);
				  workInfoDetailMapDAO.save(workinfodetailmap);
			  }
			  //标识还原
			  workInfoException=false;
			  detailType="";
			  
			  
			  if(StringUtils.isNotEmpty((String)timeMap.get("offduty"+i)))
			     {	
				  /*
				   * 得到离考勤制度最近的时间
				   */
				  Map paraMap=getRecentTime(dutyList,(String)timeMap.get("offduty"+i),false);
				  recentTime=(String)paraMap.get("recentTime");
				  log.debug("off_closest:"+recentTime);
				  String formatTime=recentTime.substring(0,4);
				  timeConf=(String)timeMap.get("offduty"+i);
				  result=Integer.parseInt(formatTime)-Integer.parseInt(timeConf);
				  if(result<0)//早退 只有在下班考勤时间以后没有流水信息才出现此情况
				  {
					  confTime=(Integer)confMap.get("earlytime");
					  result=(getInterval(timeConf,recentTime)).intValue();//得到时间间隔
					  if(result>confTime.intValue())//超过允许早退时间范围
					  {
						  earlyNum++;
						  workInfoException=true;
						  detailType=CommonConfig.earlyQuit;
						  log.debug("earlytime");
					  }
					  else//按正常情况处理
					  {
						  /*
						   * 记录流水信息
						   */
						  Workinfodetail workinfodetail=new Workinfodetail();
						  workinfodetail.setCheckdate(checkDate);
						  workinfodetail.setDutycheckdate(recentTime);
						  workinfodetail.setExceptionmins(new Integer(result));
						  workinfodetail.setInfotype(CommonConfig.offDutyOk);
						  workInfoDetailDAO.save(workinfodetail);
						  
						  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
						  workinfodetailmap.setWorkinfo(workinfo);
						  workinfodetailmap.setWorkinfodetail(workinfodetail);
						  workInfoDetailMapDAO.save(workinfodetailmap);
					  }
				  }
				  else//下班考勤时间以后打卡
				  {
					  result=(getInterval(timeConf,recentTime)).intValue();
					  confTime=(Integer)confMap.get("offtime");
					  if(confTime.intValue()<result)//超过下班允许滞后时间
					  {
						  if(StringUtils.isNotEmpty((String)paraMap.get("bakTime")))
						  {
							  int tempResult=(getInterval(timeConf,(String)paraMap.get("bakTime"))).intValue();
							  log.debug("adjustDate:"+(String)paraMap.get("bakTime"));
							  if(tempResult>((Integer)confMap.get("earlytime")).intValue())//超过早退规定时间打卡
							  {
								  lateCheckOut++;
								  workInfoException=true;
								  detailType=CommonConfig.latecheckout;
								  log.debug("beyendofftime");
							  }
							  else{
								  //按正常情况处理
								  /*
								   * 记录流水信息
								   */
								  Workinfodetail workinfodetail=new Workinfodetail();
								  workinfodetail.setCheckdate(checkDate);
								  workinfodetail.setDutycheckdate((String)paraMap.get("bakTime"));
								  workinfodetail.setExceptionmins(new Integer(tempResult));
								  workinfodetail.setInfotype(CommonConfig.offDutyOk);
								  workInfoDetailDAO.save(workinfodetail);
								  
								  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
								  workinfodetailmap.setWorkinfo(workinfo);
								  workinfodetailmap.setWorkinfodetail(workinfodetail);
								  workInfoDetailMapDAO.save(workinfodetailmap);
							  }
						  }
						  else
						  {
							  lateCheckOut++;
							  workInfoException=true;
							  detailType=CommonConfig.latecheckout;
							  log.debug("beyendofftime");
						  }
					  }
					  else//按正常情况处理
					  {
						  /*
						   * 记录流水信息
						   */
						  Workinfodetail workinfodetail=new Workinfodetail();
						  workinfodetail.setCheckdate(checkDate);
						  workinfodetail.setDutycheckdate(recentTime);
						  workinfodetail.setExceptionmins(new Integer(result));
						  workinfodetail.setInfotype(CommonConfig.offDutyOk);
						  workInfoDetailDAO.save(workinfodetail);
						  
						  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
						  workinfodetailmap.setWorkinfo(workinfo);
						  workinfodetailmap.setWorkinfodetail(workinfodetail);
						  workInfoDetailMapDAO.save(workinfodetailmap);
					  }
				  }//end else
			     }//end if 
			  /*
			   * 生成考勤细节
			   */
			  if(workInfoException)
			  {
				  Workinfodetail workinfodetail=new Workinfodetail();
				  workinfodetail.setCheckdate(checkDate);
				  workinfodetail.setDutycheckdate(recentTime);
				  workinfodetail.setExceptionmins(new Integer(result));
				  if(detailType.equals(CommonConfig.latecheckout))
				  {
					  workinfodetail.setInfotype(CommonConfig.latecheckout);
				  }
				  else if(detailType.equals(CommonConfig.earlyQuit))
				  {
					  workinfodetail.setInfotype(CommonConfig.earlyQuit);
				  }
				  workInfoDetailDAO.save(workinfodetail);
				  
				  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
				  workinfodetailmap.setWorkinfo(workinfo);
				  workinfodetailmap.setWorkinfodetail(workinfodetail);
				  workInfoDetailMapDAO.save(workinfodetailmap);
			  }
			  workInfoException=false;
			  detailType="";
		  }//end for
		  
		  /*
		   * 流水记录未出现异常信息，按正常情况处理
		   */
		  if(lateNum==0&&earlyNum==0&&lateCheckOut==0&&realyCheckIn==0)
		  {
			  workinfo.setWorkinfotype(CommonConfig.workInfoOk);
			  description="正常上下班";
			  workinfo.setDescription(description);
			  workInfodao.update(workinfo);
		  }
		  if(lateNum!=0||earlyNum!=0||lateCheckOut!=0||realyCheckIn!=0)
		  {
			  if(lateNum!=0)	  
		     {
				  description="迟到"+lateNum+"次 ";
		     }
		     if(earlyNum!=0)
		     {
		    	 description+="早退"+earlyNum+"次 ";
		     }
		     if(lateCheckOut!=0)
		     {
		    	 description+="下班滞后打卡"+lateCheckOut+"次 ";
		     }
		     if(realyCheckIn!=0)
		     {
		    	 description+="上班提前打卡"+realyCheckIn+"次 ";
		     }
		     workinfo.setWorkinfotype(CommonConfig.workInfoException);
		     workinfo.setDescription(description);
			 workInfodao.update(workinfo);
		  }
		  
		  return errInfo;
	  }
	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.WorkInfoService#getRecentOndutyTime(java.util.List, java.lang.String)
	   * @在打卡流水信息中,得到离工作上班设置时间最近的一个,以isOnduty为标识 isOnduty为true则为上班，为false则为下班
	   */
	  public Map getRecentTime(List dutyList,String ondutyTimeConf,boolean isOnduty)throws Exception
	  {
		  Iterator dutyIte=dutyList.iterator();
		  String recentyTime=null;
		  String overTime=null;
		  int plusMinValue=9999;//在考勤时间前面最小的差值
		  int minusValue=9999;//在考勤时间后面最小的差值
		  while(dutyIte.hasNext())
		  {
			  Map map=(Map)dutyIte.next();
			  String dutyTime=(String)map.get("time");
			  String fomatTime=dutyTime.substring(0,4);
			  log.debug("dutyTime:"+fomatTime+" ondutyTimeConf:"+ondutyTimeConf);
			  /*
			   * 得到离上班时间制度最近的一个考勤时间
			   */
			  if(Integer.parseInt(fomatTime)<Integer.parseInt(ondutyTimeConf))
			  {
				  if((Integer.parseInt(ondutyTimeConf)-Integer.parseInt(fomatTime))<plusMinValue)
				  {
					  plusMinValue=(Integer.parseInt(ondutyTimeConf)-Integer.parseInt(fomatTime));
					  recentyTime=dutyTime;
					  log.debug("earlyTime:"+recentyTime);
				  }
			  }
			  if(Integer.parseInt(fomatTime)>Integer.parseInt(ondutyTimeConf))
			  {
				  if((Integer.parseInt(fomatTime)-Integer.parseInt(ondutyTimeConf))<minusValue)
				  {
					  minusValue=(Integer.parseInt(fomatTime)-Integer.parseInt(ondutyTimeConf));
					  overTime=dutyTime;
					  log.debug("overTime:"+overTime);
				  }
			  }
		  }
		  Map paraMap=new HashMap();
		  if(isOnduty)
		  {
			  if(recentyTime==null)
			  {
				  paraMap.put("recentTime",overTime);
				  return paraMap;
			  }
			  else 
			  {
				  paraMap.put("recentTime",recentyTime);
				  paraMap.put("bakTime",overTime);
				  return paraMap;
			  }
		  }else
		  {
			  if(overTime==null)
				  {
				  paraMap.put("recentTime",recentyTime);
				  return paraMap;
				  }
			  paraMap.put("recentTime",overTime);
			  paraMap.put("bakTime",recentyTime);
			  return paraMap;

		  }
	  }
	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.WorkInfoService#getInterval(java.lang.String, java.lang.String)
	   * @得到打卡时间与考勤制度时间的差值 打卡时间参数格式为hhmmss 考勤制度时间参数格式为 hhmm
	   */
	  public Integer getInterval(String confTime,String dutyTime)throws Exception
	  {
		  int distance=24;
		  int confHour=Integer.parseInt(confTime.substring(0,2));
		  int confMin=Integer.parseInt(confTime.substring(2));
		  int dutyHour=Integer.parseInt(dutyTime.substring(0,2));
		  int dutyMin=Integer.parseInt(dutyTime.substring(2,4));
		  int result;
		  
		  
		  log.debug("confHour:"+confHour+" confMin:"+confMin+" dutyHour:"+dutyHour+" dutyMin:"+dutyMin);
		  /*
		   * 处理小时
		   */
		  result=confHour-dutyHour;
		  if(result!=0)
		  {
			  result=(Math.abs(result)-1)*60;
		  }
		  /*
		   * 处理分钟
		   */
		  if(confHour<dutyHour)
		  {
			  result+=dutyMin+60-confMin;
		  }
		  else if(confHour>dutyHour)
		  {
			  result+=confMin+60-dutyMin;
		  }
		  else
		  {
			  result+=Math.abs(confMin-dutyMin);
		  }
		  log.debug("interval:"+result);
		  return new Integer(result);
	  }

	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.WorkInfoService#createWorkInfoByDptConf(java.util.Map)
	   * 按照部门设置 来生成个人考勤数据 
	   */
	  public void createWorkInfoByDptConf(Map filter)throws Exception
	  {
		  String  sql;
		  String checkDate=(String)filter.get("checkDate");//格式为0000-00-00
		  Calendar cal=Calendar.getInstance();
		  Date date=new Date();		  
		  String recentTime="000000";
		  String timeConf;
		  Integer confTime;
		  String description="",leaveDes=checkDate+"请假:";//分别为考勤信息描述与请假信息描述
		  List tempList;
		  Integer card_id;
		  int result=0;
		  int lateNum=0,earlyNum=0,lateCheckOut=0,realyCheckIn=0;
		  boolean workInfoException=false,existLeave=false;//有异常信息发生标识
		  String detailType="";
		  
		  /*
		   * 判断请假信息
		   */
		  Map para=new HashMap();
		  para.put(CommonConfig.startDate,(String)filter.get("checkDate"));
		  para.put(CommonConfig.endDate,(String)filter.get("checkDate"));
		  para.put("clerkId",(Integer)filter.get("clerkId"));
		  List leaveList=leaveInfoService.isInLeave(para);
		  if(!leaveList.isEmpty())
		  {
			  Iterator leaveIte=leaveList.iterator();
			  existLeave=true;
			  while(leaveIte.hasNext())
			  {
				  Map temp=(Map)leaveIte.next();
				  Date startDate=(Date)temp.get("startDate");
				  Date endDate=(Date)temp.get("endDate");
				  
				  cal.setTime(startDate);
				  leaveDes+=cal.get(Calendar.HOUR)+":"+cal.get(Calendar.MINUTE);
				  
				  leaveDes+="--";
				  
				  cal.setTime(endDate);
				  leaveDes+=cal.get(Calendar.HOUR)+":"+cal.get(Calendar.MINUTE);
				  
				  leaveDes+=" ";
			  }
			  log.debug("leaveDes:"+leaveDes);
		  }
		  /*
		   * 如果考勤时间为空 则默认为生成当天的考勤信息
		   */
		  if(!StringUtils.isNotEmpty(checkDate))
		  {
			  cal.setTime(date);
		  }
		  else
		  {
			  checkDate=checkDate.replace('-','/');
			  checkDate=checkDate+" 00:00:00";
			  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
			  cal.setTime(sdf.parse(checkDate));
		  }
		  checkDate=Integer.toString(cal.get(Calendar.YEAR))+
		  ((cal.get(Calendar.MONTH)+1)<10?"0"+Integer.toString(cal.get(Calendar.MONTH)+1):Integer.toString(cal.get(Calendar.MONTH)+1))+
		  (cal.get(Calendar.DAY_OF_MONTH)<10?"0"+Integer.toString(cal.get(Calendar.DAY_OF_MONTH)):Integer.toString(cal.get(Calendar.DAY_OF_MONTH)));
		  log.debug("checkDate:"+checkDate);
		  
		  
		  /*
		   * 得到员工工作时间制度
		   */
		  Map timeMap=(Map)filter.get("timeMap");	  
		  
		  log.debug("getTimeConf");

		  /*
		   * 得到员工考勤制度
		   */
		  Map confMap=(Map)filter.get("confMap");

		  log.debug("getWorkConf");
		  
		  /*
		   * 得到员工考勤日的流水信息
		   */
		  sql=" select txdtl.TX_DATE as date,txdtl.TX_TIME as time" +
		  		" from YKT_CK.T_KQ_TXDTL txdtl , YKT_CUR.T_AIF_ACCOUNT account ,YKT_CUR.T_PIF_CARD card " +
		  		" where account.CUSTOMER_ID="+(Integer)filter.get("clerkId");
		  sql+=" and card.CARD_ID=account.CARD_ID and card.STATE_ID='1000' " +//建立与有效卡的关联
		  		" and txdtl.CARD_NO=card.CARD_ID and txdtl.TX_DATE='"+checkDate+"'";//得到考勤日期的数据
		  log.debug("sql:"+sql);
		  List dutyList=jdbcTemplate.queryForList(sql);
		  log.debug("getDutyList");
		  
		  /*
		   * 得到卡号
		   */
		  sql="select card.CARD_ID as card_id " +
		  	  " from " +
		  	  " YKT_CUR.T_AIF_ACCOUNT account ,YKT_CUR.T_PIF_CARD card " +
		  	  "where account.CUSTOMER_ID="+(Integer)filter.get("clerkId");
		  sql+=" and card.CARD_ID=account.CARD_ID and card.STATE_ID='1000' ";
		  tempList=jdbcTemplate.queryForList(sql);
		  if(!tempList.isEmpty())
		  {
			  Map tempMap=(Map)tempList.get(0);
			  card_id=(Integer)tempMap.get("card_id");
		  }
		  else
		  {
			  card_id=new Integer(0);
		  }
		  log.debug("getCard_id");
		  
		  /*
		   * 考勤数据初始化
		   */
		  Clerk clerk=clerkdao.get((Integer)filter.get("clerkId"));
		  Workinfo workinfo=new Workinfo();
		  workinfo.setClerkid((Integer)filter.get("clerkId"));
		  workinfo.setDeptid(clerk.getDepartment().getId());
		  workinfo.setIsseat(clerk.getIsseat());
		  workinfo.setRecordtime(new Date());
		  
		  workinfo.setCardnumber(card_id);
		  workinfo.setWorkconfid((String)confMap.get("workconfid"));
		  workinfo.setSerialid(0);//暂时设置为0
		  workinfo.setCheckdate(checkDate);
		  workInfodao.save(workinfo);
		  
		  /*
		   * 没有打卡流水信息，按照旷工处理,结束
		   */
		  if(dutyList.isEmpty())
		  {
			  workinfo.setWorkinfotype(CommonConfig.absent);
			  
			  if(existLeave)
			  workinfo.setDescription("旷工缺席"+leaveDes);
			  else
				  workinfo.setDescription("旷工缺席");
			  
			  workInfodao.update(workinfo);
			  return ;
		  }

		  
		  /*
		   * @开始分析数据
		   */
	  
		  
		  for(int i=1;i<5;i++)
		  {
			  if(StringUtils.isNotEmpty((String)timeMap.get("onduty"+i)))
				  {
				  /*
				   * 得到离考勤制度最近的时间
				   */
				  Map paraMap=getRecentTime(dutyList,(String)timeMap.get("onduty"+i),true);
				  recentTime=(String)paraMap.get("recentTime");
				  log.debug("on_closest:"+recentTime);
				  String formatTime=recentTime.substring(0,4);
				  timeConf=(String)timeMap.get("onduty"+i);
				  result=Integer.parseInt(timeConf)-Integer.parseInt(formatTime);//得到时间间隔
				  if(result<0)//迟到 只有上班考勤时间以前没有流水信息 才出现此情况
				  {
					  confTime=(Integer)confMap.get("latetime");
					  result=(getInterval(timeConf,recentTime)).intValue();
					  if(result>confTime.intValue())//超过允许迟到时间范围
					  {
						  lateNum++;
						  workInfoException=true;
						  detailType=CommonConfig.late;
						  log.debug("late");					  
					  }
					  else//按正常情况处理
					  {
						  /*
						   * 记录流水信息
						   */
						  Workinfodetail workinfodetail=new Workinfodetail();
						  workinfodetail.setCheckdate(checkDate);
						  workinfodetail.setDutycheckdate(recentTime);
						  workinfodetail.setExceptionmins(new Integer(result));
						  workinfodetail.setInfotype(CommonConfig.onDutyOk);
						  workInfoDetailDAO.save(workinfodetail);
						  
						  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
						  workinfodetailmap.setWorkinfo(workinfo);
						  workinfodetailmap.setWorkinfodetail(workinfodetail);
						  workInfoDetailMapDAO.save(workinfodetailmap);
					  }
				  }
				  else//上班考勤时间以前打卡
				  {
					  confTime=(Integer)confMap.get("ontime");
					  result=(getInterval(timeConf,recentTime)).intValue();
					  if(result>confTime.intValue())//超过允许提前打卡范围
					  {
						  if(StringUtils.isNotEmpty((String)paraMap.get("bakTime")))
						  {
							  int tempResult=(getInterval(timeConf,(String)paraMap.get("bakTime"))).intValue();
							  log.debug("adjustDate:"+(String)paraMap.get("bakTime"));
							  if(tempResult>((Integer)confMap.get("latetime")).intValue())//超过允许迟到范围
							  {
								  realyCheckIn++;
								  workInfoException=true;
								  detailType=CommonConfig.earlycheckin;
							  }
							  else{
								  //按正常情况处理
								  /*
								   * 记录流水信息
								   */
								  Workinfodetail workinfodetail=new Workinfodetail();
								  workinfodetail.setCheckdate(checkDate);
								  workinfodetail.setDutycheckdate((String)paraMap.get("bakTime"));
								  workinfodetail.setExceptionmins(new Integer(tempResult));
								  workinfodetail.setInfotype(CommonConfig.onDutyOk);
								  workInfoDetailDAO.save(workinfodetail);
								  
								  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
								  workinfodetailmap.setWorkinfo(workinfo);
								  workinfodetailmap.setWorkinfodetail(workinfodetail);
								  workInfoDetailMapDAO.save(workinfodetailmap);
							  }
						  }
						  else
						  {
							  realyCheckIn++;
							  workInfoException=true;
							  detailType=CommonConfig.earlycheckin;
						  }						  
					  }
					  else//按正常情况处理
					  {
						  /*
						   * 记录流水信息
						   */
						  Workinfodetail workinfodetail=new Workinfodetail();
						  workinfodetail.setCheckdate(checkDate);
						  workinfodetail.setDutycheckdate(recentTime);
						  workinfodetail.setExceptionmins(new Integer(result));
						  workinfodetail.setInfotype(CommonConfig.onDutyOk);
						  workInfoDetailDAO.save(workinfodetail);
						  
						  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
						  workinfodetailmap.setWorkinfo(workinfo);
						  workinfodetailmap.setWorkinfodetail(workinfodetail);
						  workInfoDetailMapDAO.save(workinfodetailmap);
					  }
				  }//end else 
				  }// end if 
			  /*
			   * 生成考勤细节
			   */
			  if(workInfoException)
			  {
				  Workinfodetail workinfodetail=new Workinfodetail();
				  workinfodetail.setCheckdate(checkDate);
				  workinfodetail.setDutycheckdate(recentTime);
				  workinfodetail.setExceptionmins(new Integer(result));
				  if(detailType.equals(CommonConfig.late))
				  {
					  workinfodetail.setInfotype(CommonConfig.late);
				  }
				  else if(detailType.equals(CommonConfig.earlycheckin))
				  {
					  workinfodetail.setInfotype(CommonConfig.earlycheckin);
				  }
				  workInfoDetailDAO.save(workinfodetail);
				  
				  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
				  workinfodetailmap.setWorkinfo(workinfo);
				  workinfodetailmap.setWorkinfodetail(workinfodetail);
				  workInfoDetailMapDAO.save(workinfodetailmap);
			  }
			  //标识还原
			  workInfoException=false;
			  detailType="";
			  
			  
			  if(StringUtils.isNotEmpty((String)timeMap.get("offduty"+i)))
			     {	
				  /*
				   * 得到离考勤制度最近的时间
				   */
				  Map paraMap=getRecentTime(dutyList,(String)timeMap.get("offduty"+i),false);
				  recentTime=(String)paraMap.get("recentTime");
				  log.debug("off_closest:"+recentTime);
				  String formatTime=recentTime.substring(0,4);
				  timeConf=(String)timeMap.get("offduty"+i);
				  result=Integer.parseInt(formatTime)-Integer.parseInt(timeConf);
				  if(result<0)//早退 只有在下班考勤时间以后没有流水信息才出现此情况
				  {
					  confTime=(Integer)confMap.get("earlytime");
					  result=(getInterval(timeConf,recentTime)).intValue();//得到时间间隔
					  if(result>confTime.intValue())//超过允许早退时间范围
					  {
						  earlyNum++;
						  workInfoException=true;
						  detailType=CommonConfig.earlyQuit;
						  log.debug("earlytime");
					  }
					  else//按正常情况处理
					  {
						  /*
						   * 记录流水信息
						   */
						  Workinfodetail workinfodetail=new Workinfodetail();
						  workinfodetail.setCheckdate(checkDate);
						  workinfodetail.setDutycheckdate(recentTime);
						  workinfodetail.setExceptionmins(new Integer(result));
						  workinfodetail.setInfotype(CommonConfig.offDutyOk);
						  workInfoDetailDAO.save(workinfodetail);
						  
						  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
						  workinfodetailmap.setWorkinfo(workinfo);
						  workinfodetailmap.setWorkinfodetail(workinfodetail);
						  workInfoDetailMapDAO.save(workinfodetailmap);
					  }
				  }
				  else//下班考勤时间以后打卡
				  {
					  result=(getInterval(timeConf,recentTime)).intValue();
					  confTime=(Integer)confMap.get("offtime");
					  if(confTime.intValue()<result)//超过下班允许滞后时间
					  {
						  if(StringUtils.isNotEmpty((String)paraMap.get("bakTime")))
						  {
							  int tempResult=(getInterval(timeConf,(String)paraMap.get("bakTime"))).intValue();
							  log.debug("adjustDate:"+(String)paraMap.get("bakTime"));
							  if(tempResult>((Integer)confMap.get("earlytime")).intValue())//超过早退规定时间打卡
							  {
								  lateCheckOut++;
								  workInfoException=true;
								  detailType=CommonConfig.latecheckout;
								  log.debug("beyendofftime");
							  }
							  else{
								  //按正常情况处理
								  /*
								   * 记录流水信息
								   */
								  Workinfodetail workinfodetail=new Workinfodetail();
								  workinfodetail.setCheckdate(checkDate);
								  workinfodetail.setDutycheckdate((String)paraMap.get("bakTime"));
								  workinfodetail.setExceptionmins(new Integer(tempResult));
								  workinfodetail.setInfotype(CommonConfig.offDutyOk);
								  workInfoDetailDAO.save(workinfodetail);
								  
								  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
								  workinfodetailmap.setWorkinfo(workinfo);
								  workinfodetailmap.setWorkinfodetail(workinfodetail);
								  workInfoDetailMapDAO.save(workinfodetailmap);
							  }
						  }
						  else
						  {
							  lateCheckOut++;
							  workInfoException=true;
							  detailType=CommonConfig.latecheckout;
							  log.debug("beyendofftime");
						  }
					  }
					  else//按正常情况处理
					  {
						  /*
						   * 记录流水信息
						   */
						  Workinfodetail workinfodetail=new Workinfodetail();
						  workinfodetail.setCheckdate(checkDate);
						  workinfodetail.setDutycheckdate(recentTime);
						  workinfodetail.setExceptionmins(new Integer(result));
						  workinfodetail.setInfotype(CommonConfig.offDutyOk);
						  workInfoDetailDAO.save(workinfodetail);
						  
						  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
						  workinfodetailmap.setWorkinfo(workinfo);
						  workinfodetailmap.setWorkinfodetail(workinfodetail);
						  workInfoDetailMapDAO.save(workinfodetailmap);
					  }
				  }//end else
			     }//end if 
			  /*
			   * 生成考勤细节
			   */
			  if(workInfoException)
			  {
				  Workinfodetail workinfodetail=new Workinfodetail();
				  workinfodetail.setCheckdate(checkDate);
				  workinfodetail.setDutycheckdate(recentTime);
				  workinfodetail.setExceptionmins(new Integer(result));
				  if(detailType.equals(CommonConfig.latecheckout))
				  {
					  workinfodetail.setInfotype(CommonConfig.latecheckout);
				  }
				  else if(detailType.equals(CommonConfig.earlyQuit))
				  {
					  workinfodetail.setInfotype(CommonConfig.earlyQuit);
				  }
				  workInfoDetailDAO.save(workinfodetail);
				  
				  Workinfodetailmap workinfodetailmap=new Workinfodetailmap();
				  workinfodetailmap.setWorkinfo(workinfo);
				  workinfodetailmap.setWorkinfodetail(workinfodetail);
				  workInfoDetailMapDAO.save(workinfodetailmap);
			  }
			  workInfoException=false;
			  detailType="";
		  }//end for
		  
		  /*
		   * 流水记录未出现异常信息，按正常情况处理
		   */
		  if(lateNum==0&&earlyNum==0&&lateCheckOut==0&&realyCheckIn==0)
		  {
			  workinfo.setWorkinfotype(CommonConfig.workInfoOk);
			  description="正常上下班";
			  workinfo.setDescription(description);
			  workInfodao.update(workinfo);
		  }
		  if(lateNum!=0||earlyNum!=0||lateCheckOut!=0||realyCheckIn!=0)
		  {
			  if(lateNum!=0)	  
		     {
				  description="迟到"+lateNum+"次 ";
		     }
		     if(earlyNum!=0)
		     {
		    	 description+="早退"+earlyNum+"次 ";
		     }
		     if(lateCheckOut!=0)
		     {
		    	 description+="下班滞后打卡"+lateCheckOut+"次 ";
		     }
		     if(realyCheckIn!=0)
		     {
		    	 description+="上班提前打卡"+realyCheckIn+"次 ";
		     }
		     workinfo.setWorkinfotype(CommonConfig.workInfoException);
		     if(existLeave)
		     workinfo.setDescription(description+leaveDes);
		     else
		    	 workinfo.setDescription(description);
			 workInfodao.update(workinfo);
		  }

	  }
	  /*
	   *  (non-Javadoc)
	   * @see org.king.check.service.WorkInfoService#createAllWorkInfoByDptConf(java.util.Map)
	   * 按照部门设置 生成全部个人考勤信息
	   */
	  public void createAllWorkInfoByDptConf(Map filter)throws Exception
	  {
		  Date date=new Date();
		  String checkDate=(String)filter.get("checkDate");//格式为00000000
		  Calendar cal=Calendar.getInstance();
		  String sql;
		  /*
		   * 如果考勤时间为空 则默认为生成当天的考勤信息
		   */
		  if(!StringUtils.isNotEmpty(checkDate))
		  {
			  cal.setTime(date);
		  }
		  else
		  {
			  checkDate=checkDate.replace('-','/');
			  checkDate=checkDate+" 00:00:00";
			  SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
			  cal.setTime(sdf.parse(checkDate));
		  }
		  /*
		   * 生成非坐班员工考勤信息
		   */
		  Map noSeatMap=new HashMap();
		  noSeatMap.put("cal",cal);
		  dealWithNoSeatClerk(noSeatMap);
		  log.debug("completely create no seat workinfo");
		  
		  /*
		   * 将日期格式化 与departconf表中字段一致
		   */
		  checkDate=Integer.toString(cal.get(Calendar.YEAR))+
		  ((cal.get(Calendar.MONTH)+1)<10?"0"+Integer.toString(cal.get(Calendar.MONTH)+1):Integer.toString(cal.get(Calendar.MONTH)+1))+
		  (cal.get(Calendar.DAY_OF_MONTH)<10?"0"+Integer.toString(cal.get(Calendar.DAY_OF_MONTH)):Integer.toString(cal.get(Calendar.DAY_OF_MONTH)));
		  log.debug("checkDate:"+checkDate);
		  
		  /*得出在考勤日加班的员工*/
          //....
		  
		  /*
		   * 按照加班处理业务逻辑
		   */
		 //...
		  
		  /*找出考勤日特殊休息的员工*/
          //..
		  ;
		  /*是否公休日，否则按照正常逻辑处理*/
		  boolean isVaction=vacationService.isGlobeVacation(cal);
		  
		  List departList=departmentDAO.getAll();
		  if(!departList.isEmpty())
		  {
			  Iterator departIte=departList.iterator();
			  while(departIte.hasNext())
			  {
				  Department department=(Department)departIte.next();
				  /*if(vacationService.isDepartVacation(department.getId(),cal))
				  {
					  continue;//该部门为公休日
				   }*/
				  
				  
				  if(isVaction)
				  {
					  //考勤当天为休息日
					  sql=" select timeconf.WORKTIMECONFID as id ," +
				  		" timeconf.CONFNAME as confname," +
				  		" timeconf.ONDUTYTIME1 as onduty1," +
				  		" timeconf.OFFDUTYTIME1 as offduty1," +
				  		" timeconf.ONDUTYTIME2 as onduty2," +
				  		" timeconf.OFFDUTYTIME2 as offduty2," +
				  		" timeconf.ONDUTYTIME3 as onduty3," +
				  		" timeconf.OFFDUTYTIME3 as offduty3," +
				  		" timeconf.ONDUTYTIME4 as onduty4," +
				  		" timeconf.OFFDUTYTIME4 as offduty4 " +
				  		" from " +
				  		" YKT_CK.WORKTIMECONF timeconf,YKT_CK.DEPARTCONF dptconf" +
				  		" where timeconf.WORKTIMECONFID=dptconf.WORKTIMECONFID " +
				  		" and dptconf.DEPARTMENTID='"+department.getId()+"'" +
				  		" and dptconf.STARTDATE<='"+checkDate+"'" +
				  		" and dptconf.ENDDATE>='"+checkDate+"'" +
				  		" and dptconf.RESTINWKD='"+CommonConfig.workInWKD+"'";
					  log.debug("now is weekend");
				  }
				  else 
				  /*
				  * 得到部门工作时间制度
				  */
				  sql=" select timeconf.WORKTIMECONFID as id ," +
						  		" timeconf.CONFNAME as confname," +
						  		" timeconf.ONDUTYTIME1 as onduty1," +
						  		" timeconf.OFFDUTYTIME1 as offduty1," +
						  		" timeconf.ONDUTYTIME2 as onduty2," +
						  		" timeconf.OFFDUTYTIME2 as offduty2," +
						  		" timeconf.ONDUTYTIME3 as onduty3," +
						  		" timeconf.OFFDUTYTIME3 as offduty3," +
						  		" timeconf.ONDUTYTIME4 as onduty4," +
						  		" timeconf.OFFDUTYTIME4 as offduty4 " +
						  		" from " +
						  		" YKT_CK.WORKTIMECONF timeconf,YKT_CK.DEPARTCONF dptconf" +
						  		" where timeconf.WORKTIMECONFID=dptconf.WORKTIMECONFID " +
						  		" and dptconf.DEPARTMENTID='"+department.getId()+"'" +
						  		" and dptconf.STARTDATE<='"+checkDate+"'" +
						  		" and dptconf.ENDDATE>='"+checkDate+"'";
				  log.debug("sql:"+sql);
				  List tempList=jdbcTemplate.queryForList(sql);
				  Map timeMap;
				  /*
				   * 如果为空则表示未设置 或者当日不考勤
				   */
				  if(!tempList.isEmpty())
				  {
					  timeMap=(Map)tempList.get(0);
					  log.debug("get timeMap");
				  }
				  else
				  {
					  continue;
				  }
				  /*
				   * 得到部门考勤制度
				   */
				  sql="select workconf.PERMITLATETIME as latetime,workconf.PREEARLY as earlytime ," +
						  	  "workconf.ONDUTYADVANCEDTIME as ontime,workconf.OFFDUTYLASTTIME as offtime ," +
						  	  "workconf.WORKCONFID as workconfid " +
						  	  " from  YKT_CK.DEPARTCONF dptconf, YKT_CK.WORKCONF workconf " +
						  	  " where workconf.WORKCONFID=dptconf.WORKCONFID " +
						  	  " and dptconf.DEPARTMENTID='"+department.getId()+"'" +
					  		  " and dptconf.STARTDATE<='"+checkDate+"'" +
					  		  " and dptconf.ENDDATE>='"+checkDate+"'";
				  log.debug("sql:"+sql);
				  Map confMap;
				  tempList=jdbcTemplate.queryForList(sql);
				  if(!tempList.isEmpty())
				  {
					  confMap=(Map)tempList.get(0);
					  log.debug("get confMap");
				  }
				  else{
					  continue;
				  }
				  /*
				   * 按部门找出需要考勤的人员
				   */
				  sql="select clerk.CLERKID as clerkId " +
			  		      " from YKT_CK.CLERK clerk  " +
			  		      " where  clerk.DEPARTMENTID='"+department.getId()+"'";
				  log.debug("sql:"+sql);
				  List clerkList=jdbcTemplate.queryForList(sql);
				  log.debug("get  clerk list");
				  Iterator clerkIte=clerkList.iterator();
				  while(clerkIte.hasNext())
				  {
					  Map  paraMap=(Map)clerkIte.next();
					  paraMap.put("checkDate",(String)filter.get("checkDate"));
					  paraMap.put("timeMap",timeMap);
					  paraMap.put("confMap",confMap);
					  createWorkInfoByDptConf(paraMap);			//生成考勤数据 
				   }
				   log.debug("create  clerk workInfo ok");
				}//end while
			}//end if
		  log.debug("operation ok");
	  }
}

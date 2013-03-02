package org.king.check.util;

import java.util.Calendar;
import java.util.Date;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.config.CommonConfig;

public class DutyTimeUtil {
	
	private static final int constrainDayNum=6;

	private static final Log log = LogFactory.getLog(DutyTimeUtil.class);
			
	public static String validate(Map filter)throws Exception
	{
		String msg=null;
		int dayNum=1;
		
		String startDate=(String)filter.get(CommonConfig.startDate);
    	String endDate=(String)filter.get(CommonConfig.endDate);
    	String checkDate=startDate;
    	
    	String sMon,eMon,sDay,eDay,sYear,eYear;
    	eMon=endDate.substring(5,7);
    	eDay=endDate.substring(8,10);
    	
    	sMon=startDate.substring(5,7);
    	sDay=startDate.substring(8,10);
    	
    	sYear=startDate.substring(0,4);
    	eYear=endDate.substring(0,4);
    	

    	while(true)
    	{
    		if(dayNum>constrainDayNum)
       		{
       			msg="请按照"+constrainDayNum+"天为一时间段查询"; 
       			log.debug("msg---------------->"+msg);
       			return msg;
       		}
    		dayNum++;
       		if(sYear.equals(eYear)&&(Integer.parseInt(sDay)==Integer.parseInt(eDay))&&(Integer.parseInt(sMon)==Integer.parseInt(eMon)))
       		{      			
       			break;
       		}
       		checkDate=getNextDate(checkDate);
       		sDay=checkDate.substring(8,10);
       		sMon=checkDate.substring(5,7);      		
       		
       		log.debug("sMon---------->"+sMon+"eMon-------------------->"+eMon);
       		log.debug("sDay---------->"+sDay+"eDay-------------------->"+eDay);
       }
    	 	
		return null;
	}
    public static String getNextDate(String curDate)throws Exception
    {
    	if(curDate==null)
    		throw new Exception("invalide date");
    	String curYear=curDate.substring(0,4);
    	String curMon=curDate.substring(5,7);
    	String curDay=curDate.substring(8,10);
    	int iCurDay=Integer.parseInt(curDay);
    	int iCurYear=Integer.parseInt(curYear);
    	int iCurMon=Integer.parseInt(curMon);
    	   	
    	log.debug("-------------------------------------->"+"curDate------------------>"+curDate+curMon);
    	
    	if(iCurDay==30)
    	{
    		if(iCurMon==4||iCurMon==6||iCurMon==9||iCurMon==11)//小月月末加一
    		{
    			iCurMon++;
    			iCurDay=1;
    			log.debug("mon--------->"+iCurMon+"day-------------->"+iCurDay);
    		}
    		else if(iCurMon==1||iCurMon==3||iCurMon==5||iCurMon==7||iCurMon==8||iCurMon==10||iCurMon==12)
    		{
    			iCurDay++;    			
    		}
    	}
    	else if(iCurDay==31)//大月判断
    	{
    		if(iCurMon==12)
    		{
    			iCurYear++;
    			iCurMon=1;  			
    		}
    		else
    		{
    			iCurMon++;
    		}
    		iCurDay=1;
    	}
    	else if(iCurMon==2)//闰年，月判断 
    	{
    		if(iCurDay==28)
    		{
    			if(iCurYear%4==0)//是闰年
    			{
    				iCurDay++;
    			}
    			else
    			{
    				iCurDay=1;
    				iCurMon++;
    			}
    		}
    		else if(iCurDay==29)
    		{
    			iCurDay=1;
    			iCurMon++;
    		}
    		else
    		{
    			iCurDay++;
    		}
    	}
    	else
    	{
    		iCurDay++;
    	}
    	
    	String theNext="0000-00-00";
    	if(iCurMon>=10&&iCurDay>=10)
    	{
    		theNext=Integer.toString(iCurYear)+"-"+Integer.toString(iCurMon)+"-"+Integer.toString(iCurDay);
    	}
    	else if(iCurMon>=10&&iCurDay<10)
    	{
    		theNext=Integer.toString(iCurYear)+"-"+Integer.toString(iCurMon)+"-0"+Integer.toString(iCurDay);
    	}
    	else if(iCurMon<10&&iCurDay<10)
    	{
    		theNext=Integer.toString(iCurYear)+"-0"+Integer.toString(iCurMon)+"-0"+Integer.toString(iCurDay);
    	}
    	else if(iCurMon<10&&iCurDay>=10)
    	{
    		theNext=Integer.toString(iCurYear)+"-0"+Integer.toString(iCurMon)+"-"+Integer.toString(iCurDay);
    	}
    	
    	log.debug("cur:=="+curDate+"next:==="+theNext);
    	
    	return theNext;
    }
    public static String getLastDate(Date curDate,int offSet)throws Exception
    {
    	if(curDate==null)
    		throw new Exception("invalide date");
    	
    	Calendar caCur=Calendar.getInstance();
    	caCur.setTime(curDate);
    	
    	
    	log.debug(curDate);
    	

    	int iCurDay=caCur.get(Calendar.DAY_OF_MONTH);
    	int iCurYear=caCur.get(Calendar.YEAR);
    	int iCurMon=caCur.get(Calendar.MONTH);
    	iCurMon++;
    	
    	log.debug(new Integer(iCurYear));
    	
    	for(int i=1;i<offSet;i++)
    	{
    	if(iCurDay==1)
    	{
    		if(iCurMon==2||iCurMon==4||iCurMon==6||iCurMon==9||iCurMon==11)//小月
    		{
    			iCurMon--;
    			iCurDay=31;
    		}
    		if(iCurMon==1)
    		{
    			iCurYear--;
    			iCurMon=12;
    			iCurDay=31;
    		}
    		if(iCurMon==5||iCurMon==7||iCurMon==8||iCurMon==10||iCurMon==12)
    		{
    			iCurMon--;
    			iCurDay=30;
    		}
    		if(iCurMon==3)
    		{
    			if(iCurYear%4==0)//是闰年
    			{
    				iCurDay=29;
    			}
    			else
    			{
    				iCurDay=28;
    			}
    			iCurMon--;
    		}
    	}
    	else
    	{
    		iCurDay--;
    	}
    	}
    	
    	String theLast="0000-00-00";
    	if(iCurMon>=10&&iCurDay>=10)
    	{
    		theLast=Integer.toString(iCurYear)+"-"+Integer.toString(iCurMon)+"-"+Integer.toString(iCurDay);
    	}
    	else if(iCurMon>=10&&iCurDay<10)
    	{
    		theLast=Integer.toString(iCurYear)+"-"+Integer.toString(iCurMon)+"-0"+Integer.toString(iCurDay);
    	}
    	else if(iCurMon<10&&iCurDay<10)
    	{
    		theLast=Integer.toString(iCurYear)+"-0"+Integer.toString(iCurMon)+"-0"+Integer.toString(iCurDay);
    	}
    	else if(iCurMon<10&&iCurDay>=10)
    	{
    		theLast=Integer.toString(iCurYear)+"-0"+Integer.toString(iCurMon)+"-"+Integer.toString(iCurDay);
    	}
    	
    	log.debug("cur:=="+curDate+"last:==="+theLast);
    	
    	return theLast;
    	
    }
}

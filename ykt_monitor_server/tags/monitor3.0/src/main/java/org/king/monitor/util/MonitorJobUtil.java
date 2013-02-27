package org.king.monitor.util;

import java.util.Iterator;
import java.util.Set;

import org.king.template.domain.MonitorTimePeriods;
import org.king.template.domain.MonitorTimeranger;
import org.king.utils.DateUtil;

public class MonitorJobUtil {
	
	public static boolean checkinWorktime(String nowtime,Set timeset){
		
		int dayofweek = DateUtil.getDayofWeek()-1;
		String daytime = nowtime.substring(0,8);
		String timeofday = nowtime.substring(8, 12);
		if(timeset==null){
			return true;
		}
		Iterator iter =  timeset.iterator();
		while(iter.hasNext()){
			MonitorTimeranger monitortimeranger = (MonitorTimeranger)iter.next();
			if(monitortimeranger.getTimeperiodDay()==dayofweek){
				
				if((DateUtil.checkSpecialTimeSequence(timeofday, monitortimeranger.getStartTime(), "HHmm")>=0)&&(DateUtil.checkSpecialTimeSequence(timeofday, monitortimeranger.getEndTime(), "HHmm")<=0)){
					return true;
				}else{
					return false;
				}
			}
		}
		
		return false;
		
	}

}

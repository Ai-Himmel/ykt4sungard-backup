/**
 * 
 */
package com.kingstargroup.advquery.common;

import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

/**
 * @author Administrator
 * 
 */
public class GetListResultStat {
	/**
	 * 取得列表值的合计值
	 * @param result
	 * @param columnTitle
	 * @return
	 */
	public int[] getListResultStat(List result, String columnTitle[]) {
		Iterator iter = result.iterator();
		int[] tot = new int[columnTitle.length];
		for (int j = 0; j < columnTitle.length; j++) {
			tot[j] = 0;
		}

		while (iter.hasNext()) {
			HashMap row = (HashMap) iter.next();
			for (int i = 0; i < columnTitle.length; i++) {
				tot[i] += Integer.parseInt(row.get(columnTitle[i]).toString());
			}
		}
		return tot;
	}
	
	public float[] getListResultStatFloat(List result, String columnTitle[]) {
		Iterator iter = result.iterator();
		float[] tot = new float[columnTitle.length];
		for (int j = 0; j < columnTitle.length; j++) {
			tot[j] = 0;
		}

		while (iter.hasNext()) {
			HashMap row = (HashMap) iter.next();
			for (int i = 0; i < columnTitle.length; i++) {
				tot[i] += Float.parseFloat(row.get(columnTitle[i]).toString());
			}
		}
		return tot;
	}
	
	public List getListByWeek(List result,String beginDate,String endDate){
		WeekSumCalc weekSum = new WeekSumCalc(new MapPopulate(){
			public String getDatePropertyName(){
				return "balance_date";
			}
		});
		Iterator iter = result.iterator();
		while (iter.hasNext()){
			HashMap row = (HashMap)iter.next();
			weekSum.populateMap(row,beginDate,endDate);
		}
		
		return weekSum.getCalcValue();
	}
	
	/**
	 * 根据返回值内容判断数据单位大小
	 * @param result返回值
	 * @param column计算列
	 * @param dataType要计算的数据类型
	 * @return数据单位提示信息
	 */
	public int getUnitValue(List result,String column,String dataType){
		Iterator iter = result.iterator();
		int dataUnit = 1;
		if ("float".equals(dataType)){
			float rowValue = 1;
			float maxValue = 1;
			float minValue = 100000;
			float avgValue = 0;
			while (iter.hasNext()){
				HashMap row = (HashMap)iter.next();
				if (null==row.get(column)){
					rowValue = 1;
				}else{
					rowValue = Float.parseFloat(row.get(column).toString());
				}
				if (rowValue>maxValue){
					maxValue = rowValue;
				}
				if (rowValue<minValue){
					minValue = rowValue;
				}
			}
			avgValue = (minValue+maxValue)/2;
			if ((avgValue/100000>10)&&(avgValue/100000<100)){
				dataUnit = 100000;
			}else if ((avgValue/10000>10)&&(avgValue/10000<100)){
				dataUnit = 10000;
			}else if ((avgValue/1000>10)&&(avgValue/1000<100)){
				dataUnit = 1000;
			}else if ((avgValue/100>10)&&(avgValue/100<100)){
				dataUnit = 100;
			}
			
		}else if ("integer".equals(dataType)){
			int rowValue = 1;
			int maxValue = 0;
			int minValue = 100000;
			int avgValue = 0;
			while (iter.hasNext()){
				HashMap row = (HashMap)iter.next();
				if (null==row.get(column)){
					rowValue = 1;
				}else{
					rowValue = Integer.parseInt(row.get(column).toString());
				}				
				if (rowValue>maxValue){
					maxValue = rowValue;
				}
				if (rowValue<minValue){
					minValue = rowValue;
				}
			}
			avgValue = (minValue+maxValue)/2;
			if ((avgValue/100000>10)&&(avgValue/100000<100)){
				dataUnit = 100000;
			}else if ((avgValue/10000>10)&&(avgValue/10000<100)){
				dataUnit = 10000;
			}else if ((avgValue/1000>10)&&(avgValue/1000<100)){
				dataUnit = 1000;
			}else if ((avgValue/100>10)&&(avgValue/100<100)){
				dataUnit = 100;
			}			
		}
		return dataUnit;	
	}
	/**
	 * Ｙ轴显示内容，根据计算出的金额显示（金额）
	 * @param result
	 * @param column
	 * @param dataType
	 * @return
	 */
	public String getYLabelMoney(List result,String column,String dataType){
		int dataUnit = getUnitValue(result,column,dataType);
		String yLabel = "";
		switch (dataUnit){
		case 100000:
			yLabel = "金额单位:十万元";
			break;		
		case 10000:
			yLabel = "金额单位:万元";
			break;
		case 1000:
			yLabel = "金额单位:千元";
			break;		
		case 100:
			yLabel = "金额单位:百元";
			break;
		default:
			yLabel = "金额单位:元";
		}
		return yLabel.toString();
	}
	/**
	 * Ｙ轴显示内容，根据计算出的笔数显示
	 * @param result
	 * @param column
	 * @param dataType
	 * @return
	 */
	public String getYLabelNum(List result,String column,String dataType){
		int dataUnit = getUnitValue(result,column,dataType);
		String yLabel = "";
		switch (dataUnit){
		case 100000:
			yLabel = "单位:十万笔";
			break;		
		case 10000:
			yLabel = "单位:万笔";
			break;
		case 1000:
			yLabel = "单位:千笔";
			break;		
		case 100:
			yLabel = "单位:百笔";
			break;
		default:
			yLabel = "单位:笔";
		}
		return yLabel.toString();
	}
	public String getYLabelCard(List result,String column,String dataType){
		int dataUnit = getUnitValue(result,column,dataType);
		String yLabel = "";
		switch (dataUnit){
		case 100000:
			yLabel = "单位:十万张";
			break;		
		case 10000:
			yLabel = "单位:万张";
			break;
		case 1000:
			yLabel = "单位:千张";
			break;		
		case 100:
			yLabel = "单位:百张";
			break;
		default:
			yLabel = "单位:张";
		}
		return yLabel.toString();
	}
	public String getYLabelRate(List result,String column,String dataType){
		int dataUnit = getUnitValue(result,column,dataType);
		String yLabel = "";
		switch (dataUnit){
		case 100000:
			yLabel = "百分比(%)";
			break;		
		case 10000:
			yLabel = "百分比(%)";
			break;
		case 1000:
			yLabel = "百分比(%)";
			break;		
		case 100:
			yLabel = "百分比(%)";
			break;
		default:
			yLabel = "百分比(%)";
		}
		return yLabel.toString();
	}
	public String getYLabelManNum(List result,String column,String dataType){
		int dataUnit = getUnitValue(result,column,dataType);
		String yLabel = "";
		switch (dataUnit){
		case 100000:
			yLabel = "单位：十万人";
			break;		
		case 10000:
			yLabel = "单位：万人";
			break;
		case 1000:
			yLabel = "单位：千人";
			break;		
		case 100:
			yLabel = "单位：百人";
			break;
		default:
			yLabel = "单位：人";
		}
		return yLabel.toString();
	}
	public String getYLabelVisitNum(List result,String column,String dataType){
		int dataUnit = getUnitValue(result,column,dataType);
		String yLabel = "";
		switch (dataUnit){
		case 100000:
			yLabel = "单位：十万次";
			break;		
		case 10000:
			yLabel = "单位：万次";
			break;
		case 1000:
			yLabel = "单位：千次";
			break;		
		case 100:
			yLabel = "单位：百次";
			break;
		default:
			yLabel = "单位：次";
		}
		return yLabel.toString();
	}
}
class UnsupportedValueTypeException extends Exception{
	public UnsupportedValueTypeException(String msg){
		super(msg);
	}
}
interface MapPopulate {
	public String getDatePropertyName();
}

class WeekSumCalc {
	public static final String YEAR_WEEK_KEY = "balance_date";
	public static final String WEEK = "yearweek";
	public static final String SYS_USED_WEEK = "sysusedweek";
	private static final String WEEK_PREFIX = "week_"; 
	private Map valueMap;
	private MapPopulate filter;
	public WeekSumCalc(MapPopulate filter){
		valueMap = new HashMap();
		this.filter = filter;
	}
	private String getWeekKey(String yearWeek){
		return WeekSumCalc.WEEK_PREFIX + yearWeek;
	}
	private Map getWeekMap(String yearWeek){
		String key = getWeekKey(yearWeek);
		if(valueMap.containsKey(key)){
			return (Map)valueMap.get(key);
		}
		Map result = new HashMap();
		valueMap.put(key,result);
		return result;
	}
	public void addNewValue(String date,String property,Object propertyValue,String beginDate,String endDate)
		throws UnsupportedValueTypeException{
		int year;
		int week;
		String weekBeginEndDate = "";
		
		if(null == date || date.length() != 8 || null == propertyValue ){
			return;
		}
		String yearWeek = DateUtilExtend.getWeek(date);
		year = Integer.parseInt(yearWeek.substring(0,4));
		week = Integer.parseInt(yearWeek.substring(4));

		weekBeginEndDate = new DateUtilExtend.WeekBeginEndDate().weekBeginEnd(year,week,beginDate,endDate);			
		Map vMap = getWeekMap(yearWeek);
		if(vMap.containsKey(property)){
			Object value = vMap.get(property);
			if(value.getClass() != propertyValue.getClass()){
				throw new UnsupportedValueTypeException("type not insistence");
			}
			if( value instanceof Float ){
				float t = ((Float)value).floatValue() + ((Float)propertyValue).floatValue();
				vMap.put(property,new Float(t));
			}else if( value instanceof Double ){
				double t = ((Double)value).doubleValue() + ((Double)propertyValue).doubleValue();
				vMap.put(property,new Double(t));
			}else if(value instanceof Integer){
				int t = ((Integer)value).intValue() + ((Integer)propertyValue).intValue();
				vMap.put(property,new Integer(t));
			}else if(value instanceof String){
				vMap.put(property,propertyValue);
			}else{
				throw new UnsupportedValueTypeException("error ");
			}
		}else{
			//
			vMap.put(property,propertyValue);
			vMap.put(WeekSumCalc.YEAR_WEEK_KEY,weekBeginEndDate+"("+yearWeek.substring(4)+")");
			vMap.put(property,propertyValue);
			vMap.put(WeekSumCalc.WEEK,yearWeek);
			vMap.put(WeekSumCalc.SYS_USED_WEEK,DateUtilExtend.getSysUsedWeek(yearWeek));
		}
	}
	public void populateMap(Map map,String beginDate,String endDate){
		String dateKey = filter.getDatePropertyName();
		if(!map.containsKey(dateKey)){
			return;
		}
		String dateValue = (String)map.get(dateKey);

		Iterator iter = map.keySet().iterator();
		while(iter.hasNext()){
			String currName = iter.next().toString();
			if(dateKey.equals(currName)){
				continue;
			}
			try {
				addNewValue(dateValue,currName,map.get(currName),beginDate,endDate);
			} catch (UnsupportedValueTypeException e) {
				
				e.printStackTrace();
			}
		}
	}
	public List getCalcValue(){
		List result = Collections.list(Collections.enumeration(valueMap.values()));

		return result;
	}
}

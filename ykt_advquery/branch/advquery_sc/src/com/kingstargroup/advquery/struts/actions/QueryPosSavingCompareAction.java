/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.Collections;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionServlet;

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.util.ReportOperUtil;

/**
 * ��У��Pos��ֵ����Աȣ���
 * @author Administrator
 *
 */
public class QueryPosSavingCompareAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
				ActionForm form, 
				HttpServletRequest request, 
				HttpServletResponse response) throws Exception {
		QueryAllConsumeCompareActionExecution exec = new QueryAllConsumeCompareActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryAllConsumeCompareActionExecution {
		private String beginDate;
		private String endDate;
		private String compareType;
		private StringBuffer dateRange = new StringBuffer(200);
		private String statTypeShow = "";
		//��λ
		private int dataUnitAmt = 1;
		private int dataUnitNum = 1;
		private int dateUnit = 1;
		//������ʾ��Ϣ
		private String yLabelAmt = "";
		private String yLabelNum = "";
		//���ز�ѯ���
		private List weekResult = null;
		private String showType;
		private String picType = "";
		private String statType;
		private String mapForward = "";
		
		//����ͼ���������
		private String accType[] = {"����У��","����У��","�Ž�У��"};
		private String xData = "";
		private String AmtcolumnTitle[] = {"hdamt","flamt","zjamt"};
		private String NumcolumnTitle[] = {"hdnum","flnum","zjnum"};
		
		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		private boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		private boolean showTextAxis =true;
		// ��ʾBarͼ���ϵ�����
		private boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		private boolean showBackgroundColor = true;
		// ��ʾ������
		private boolean showOutLine = true;
		//��ʾ������
		private boolean showGrid = true;
		ActionServlet servlet = QueryPosSavingCompareAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//��ʼ����
			beginDate = request.getParameter("begindate");
			//��������
			endDate = request.getParameter("enddate");
			//ѡ���ͼ����ʾ����
			showType = request.getParameter("showType");		
			//��ѯ���ͣ����ղ�ѯ���²�ѯ���ܲ�ѯ��
			statType = request.getParameter("statType");
			//�Ƚ����ͣ����Ǳ�����
			compareType = request.getParameter("moneyornum");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);
			//�ж��Ƿ�������ͼ��ʾ
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			
			String dataTypeAmt = "float";
			String dataTypeNum = "integer";
			String rAttributeAmt = "posSavingCompareAmt";
			String rAttributeNum = "posSavingCompareNum";
			List result = ReportOperUtil.posSavingCompareStat(beginDate,endDate,statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			dateUnit = result.size()/9;
			if ("money".equals(compareType)){
				//����pos��ֵ���ͼ��
				setTypeReturn(request,result,dataTypeAmt,rAttributeAmt);
				//����y����ʾ�����ݣ����������
				request.setAttribute("ylabelamt",yLabelAmt);
				mapForward = "possaving_queryresultmoney";
			}else if ("num".equals(compareType)){
				//����pos��ֵ����ͼ��
				setTypeReturn(request,result,dataTypeNum,rAttributeNum);
				request.setAttribute("ylabelnum",yLabelNum);
				mapForward = "possaving_queryresultnum";
			}
			//����Ҫ��ʾ��ͼ��������ͼ��
			showTypeResult();

			request.setAttribute("pictype",picType);

			request.setAttribute("stattypeshow",statTypeShow);
			
			request.setAttribute("daterange",dateRange.toString());
			drawPic(request);
			return mapping.findForward(mapForward);	
		}
		
		/**
		 * ��ʼ��
		 * @param request
		 */
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate48d",request.getParameter("begindate"));
				session.setAttribute("enddate48d",request.getParameter("enddate"));
				session.setAttribute("querytype48","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
	 			session.setAttribute("begindate48m",request.getParameter("begindate"));
				session.setAttribute("enddate48m",request.getParameter("enddate"));
				session.setAttribute("querytype48","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate48w",request.getParameter("begindate"));
				session.setAttribute("enddate48w",request.getParameter("enddate"));
				session.setAttribute("querytype48","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
		}
		
		/**
		 * ���ݽ������ͼ��
		 * @param request
		 * @param result
		 * @param dataType
		 */
		private void setTypeReturn(HttpServletRequest request,List result,String dataType,String rAttribute){
			if ("bydate".equals(statType)){
				if ("posSavingCompareAmt".equals(rAttribute)){
					dataUnitAmt = new GetListResultStat().getUnitValue(result, "hdamt",dataType);
					yLabelAmt = new GetListResultStat().getYLabelMoney(result, "hdamt",dataType);
				}else if ("posSavingCompareNum".equals(rAttribute)){
					yLabelNum = new GetListResultStat().getYLabelNum(result,"hdnum",dataType);
					dataUnitNum = new GetListResultStat().getUnitValue(result, "hdnum",dataType);
				}
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)){
					//���ƽ��ͼ�Σ�����ͼ��
					if ("posSavingCompareAmt".equals(rAttribute)){
						request.setAttribute(rAttribute,
								new DrawTimeSeries(result, AmtcolumnTitle, xData,
										dataType, accType, dataUnitAmt)
										.getTimeSeriesProducer());
					}else if ("posSavingCompareNum".equals(rAttribute)){
						//���Ʊ���ͼ�Σ�����ͼ�Ͷ�ջͼ��
						request.setAttribute(rAttribute,
								new DrawTimeSeries(result, NumcolumnTitle, xData,
										dataType, accType, dataUnitNum)
										.getTimeSeriesProducer());
					}
				}else{
					if ("posSavingCompareAmt".equals(rAttribute)){
						//���ƽ��ͼ�Σ�����ͼ��
						request.setAttribute(rAttribute,
								new DrawBarByTypeMap(result,accType,xData,dataType,AmtcolumnTitle,dataUnitAmt)
								.getDataProducer());
					}else if ("posSavingCompareNum".equals(rAttribute)){
						//���Ʊ���ͼ�Σ�����ͼ�Ͷ�ջͼ��
						request.setAttribute(rAttribute,
								new DrawBarByTypeMap(result,accType,xData,dataType,NumcolumnTitle,dataUnitNum)
								.getDataProducer());
					}
				}				
			}else if ("bymonth".equals(statType)){
				if ("posSavingCompareAmt".equals(rAttribute)){
					dataUnitAmt = new GetListResultStat().getUnitValue(result, "hdamt",dataType);
					yLabelAmt = new GetListResultStat().getYLabelMoney(result, "hdamt",dataType);
				}else if ("posSavingCompareNum".equals(rAttribute)){
					yLabelNum = new GetListResultStat().getYLabelNum(result,"hdnum",dataType);
					dataUnitNum = new GetListResultStat().getUnitValue(result, "hdnum",dataType);
				}
				request.setAttribute("result",result);
				xData = "balance_date";
				if ("posSavingCompareAmt".equals(rAttribute)){
					request.setAttribute(rAttribute,
							new DrawBarByTypeMap(result,accType,xData,dataType,AmtcolumnTitle,dataUnitAmt).getDataProducer());
				}else if ("posSavingCompareNum".equals(rAttribute)){
					request.setAttribute(rAttribute,
							new DrawBarByTypeMap(result,accType,xData,dataType,NumcolumnTitle,dataUnitNum).getDataProducer());
				}
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				if ("posSavingCompareAmt".equals(rAttribute)){
					yLabelAmt = new GetListResultStat().getYLabelMoney(result, "hdamt",dataType);
					dataUnitAmt = new GetListResultStat().getUnitValue(weekResult,"hdamt",dataType);
				}else if ("posSavingCompareNum".equals(rAttribute)){
					yLabelNum = new GetListResultStat().getYLabelNum(result,"hdnum",dataType);
					dataUnitNum = new GetListResultStat().getUnitValue(weekResult,"hdnum",dataType);
				}
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				if ("posSavingCompareAmt".equals(rAttribute)){
					request.setAttribute(rAttribute,
							new DrawBarByTypeMap(weekResult,accType,xData,dataType,AmtcolumnTitle,dataUnitAmt).getDataProducer());
				}else if ("posSavingCompareNum".equals(rAttribute)){
					request.setAttribute(rAttribute,
							new DrawBarByTypeMap(weekResult,accType,xData,dataType,NumcolumnTitle,dataUnitNum).getDataProducer());
				}
				showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			}

		}
		
		/**
		 * ͼ����ʾ��ʽ
		 *
		 */
		private void showTypeResult(){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					picType = GetProperty.getProperties("pic.timeseries",servlet.getServletContext());
				}else{
					picType = GetProperty.getProperties("pic.line",servlet.getServletContext());
				}
				showOutLine = false;
				showOutLine = false;
			}else if ("bar".equals(showType)){
				picType = GetProperty.getProperties("pic.bar",servlet.getServletContext());
				showOutLine = true;
			}else if ("stack".equals(showType)){
				picType = GetProperty.getProperties("pic.stack",servlet.getServletContext());
				showOutLine = true;
			}
		}
		private void drawPic(HttpServletRequest request){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					request.setAttribute("dataColor", new CustomerDrawChart(showBackgroundColor,showCustColor,dateUnit)
							.getTimeSeriesPostProcessor());
				}else{
					request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
							showTextAxis, showLabel, showBackgroundColor, showOutLine,
							showGrid).getChartPostProcessor());
				}
			}else if ("bar".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
						showTextAxis, showLabel, showBackgroundColor, showOutLine,
						showGrid).getChartPostProcessor());
			}else if ("stack".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
						showTextAxis, showLabel, showBackgroundColor, showOutLine,
						showGrid).getChartPostProcessor());
			}
		}
	}
}

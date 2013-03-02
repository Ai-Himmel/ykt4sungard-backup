/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.Collections;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.jfree.chart.JFreeChart;

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.util.ReportActiveUtil;
import com.kingstargroup.advquery.hibernate.util.ReportOperUtil;
import com.kingstargroup.advquery.hibernate.util.ReportShopBalanceUtil;
import com.kingstargroup.advquery.itext.ReportDataExport;
import com.kingstargroup.advquery.util.ParamUtil;
import com.lowagie.text.Document;
import com.lowagie.text.DocumentException;
import com.lowagie.text.Rectangle;
import com.lowagie.text.pdf.DefaultFontMapper;
import com.lowagie.text.pdf.PdfContentByte;
import com.lowagie.text.pdf.PdfTemplate;
import com.lowagie.text.pdf.PdfWriter;
/**
 * �����ܱ����±����ݣ�������
 * 
 * @author Administrator
 * 
 */
public class CreateDataAction extends Action {
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		QueryAllConsumeStatActionExecution exec = new QueryAllConsumeStatActionExecution();
		ActionForward returnActionForward = exec.execute(mapping, form,
				request, response);
		return returnActionForward;
	}

	private class QueryAllConsumeStatActionExecution {
		// �����ܱ����±�������
		private String createDate = "";

		// �������������ʼͳ������
		private String consume30DaysDate = "";

		// ��ǰ���ڵ�ǰһ����������
		private String endWeekDate = "";

		// ��ǰ���ڵ�ǰ30����һ������
		private String beginWeekDate = "";

		// ��ǰ���������·�
		private String beginMonthDate = "";

		// ��ǰ���ڵ�ǰ30�������·�
		private String endMonthDate = "";
		
		// Ȧ�濪ʼ����
		private String tranBeginDate = "";

		// ��ʾ�Զ�����ɫ
		private boolean showCustColor = true;

		// ��ʾ���������ֵ���ת����
		private boolean showTextAxis = true;

		// ��ʾBarͼ���ϵ�����
		private boolean showLabel = false;

		// ��ʾ�Զ���ͼ������ɫ
		private boolean showBackgroundColor = true;

		// ��ʾ������
		private boolean showOutLine = true;

		// ��ʾ������
		private boolean showGrid = true;

		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			String cmd = ParamUtil.getString(request,"cmd");
			String nowDate = DateUtilExtend.getNowDate2();
			setInit(request);
			if ((DateUtilExtend.diffDate(nowDate, createDate) > 0)
					|| (DateUtilExtend.diffDate(createDate, "20050418")) > 0) {
				request.setAttribute("errorcont", "��ѡ����ȷ��ͳ�����ڣ�");
				return mapping.findForward("errortest");
			}
			HttpSession session = request.getSession();
			session.setAttribute("begindate99", ParamUtil.getString(request,
					"begindate"));
			if ("query".equals(cmd)){
				// ��������ͼʱ��������ʾ����
				request.setAttribute("bardataColor", new CustomerDrawChart(
						showCustColor, showTextAxis, showLabel,
						showBackgroundColor, showOutLine, showGrid)
						.getChartPostProcessor());
				request.setAttribute("weekbardataColor", new CustomerDrawChart(
						showCustColor, false, showLabel, showBackgroundColor,
						showOutLine, showGrid).getChartPostProcessor());

				// ��30����������Աȣ������ͽ�
				Consume30Days(request);
				// ��У����30����������Աȣ������ͽ�
				AreaConsume30Days(request);
				// ���30�ܵ��������
				Consume30Weeks(request);
				// ���30���µ��������
				Consume30Months(request);
				// ���30������ֵ����Ա�
				savingCompare30Days(request);
				// ���30�쾭�ѱ���֧Ʊ��ֵ����Ա�
				billSavingCompare30Days(request);
				// ��У��Pos��ֵ����Աȣ�30�죩
				posSavingCompare30Days(request);
				// �����ֵ����Աȣ�30�ܣ�
				savingCompare30Weeks(request);
				// ���ѱ���֧Ʊ��ֵ����Աȣ�30�ܣ�
				billSavingCompare30Weeks(request);
				// �����ֵ����Աȣ�30���£�
				savingCompare30Months(request);
				// ���ѱ���֧Ʊ��ֵ����Աȣ�30���£�
				billSavingCompare30Months(request);
				// Ȧ��ɹ��ʺ����ʱ���
				transferSuccessRate(request);	
				return mapping.findForward("createdata_queryresult");
			}else if("export".equals(cmd)){
				drawPDFCellAndGraph(request);
				return mapping.findForward("reportdata");
			}
			return null;
		}

		/**
		 * ��ʼ��ͳ�����ڣ��ܣ��µ�ʱ����� 2006-6-2 hjw
		 * 
		 * @param
		 * @return
		 */
		private void setInit(HttpServletRequest request) {
			createDate = DateUtil.reFormatTime(ParamUtil.getString(request,
					"begindate"));
			consume30DaysDate = DateUtilExtend.decDate(createDate, 30);

			endWeekDate = DateUtilExtend.getPreWeekByDate(createDate);
			beginWeekDate = DateUtilExtend.decDate(endWeekDate, 210);

			beginMonthDate = DateUtilExtend.desMonth(createDate, 30);
			endMonthDate = createDate.substring(0, 6);
			
			tranBeginDate = "20050418";
		}

		/**
		 * �������30�죨�ܣ������ѱ����ͽ�����ݺ�����ͼ 2006-6-1 hjw
		 * 
		 * @param
		 * @return
		 */
		private void Consume30Days(HttpServletRequest request) {
			String accTypeMoney[] = { "���ѽ��" };
			String accTypeNum[] = { "���ѱ���" };
			String xData = "balance_date";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "tradeamt" };
			String columnTitleNum[] = { "tradenum" };
			String consume30DaysYMoney = "";
			String consume30DaysYNum = "";
			int dataUnitMoney = 1;
			int dataUnitNum = 1;

			List consume30DaysResult = ReportShopBalanceUtil.getAllConsumeStat(
					consume30DaysDate, createDate, "bydate");

			// --------------------------------------------------------------------------------
			// ����ǰ30�챨������
			// ����ͼ������
			request.setAttribute("consume30DaysResult", consume30DaysResult);
			// ���ɽ��ͼ������
			consume30DaysYMoney = new GetListResultStat().getYLabelMoney(
					consume30DaysResult, "tradeamt", dataTypeMoney);
			dataUnitMoney = new GetListResultStat().getUnitValue(
					consume30DaysResult, "tradeamt", dataTypeMoney);
			request.setAttribute("consume30DaysYLableMoney",
					consume30DaysYMoney);
			request.setAttribute("consume30DaysChartMoney",
					new DrawBarByTypeMap(consume30DaysResult, accTypeMoney,
							xData, dataTypeMoney, columnTitleMoney,
							dataUnitMoney).getDataProducer());
			// ���ɱ���ͼ������
			consume30DaysYNum = new GetListResultStat().getYLabelNum(
					consume30DaysResult, "tradenum", dataTypeNum);
			dataUnitNum = new GetListResultStat().getUnitValue(
					consume30DaysResult, "tradenum", dataTypeNum);
			request.setAttribute("consume30DaysYLableNum", consume30DaysYNum);
			request.setAttribute("consume30DaysChartNum", new DrawBarByTypeMap(
					consume30DaysResult, accTypeNum, xData, dataTypeNum,
					columnTitleNum, dataUnitNum).getDataProducer());

			// ----------------------------------------------------------------------------------
		}

		/**
		 * ��У�����ѽ��ͱ����Ա� 2006-6-2 hjw
		 * 
		 * @param
		 * @return
		 */
		private void AreaConsume30Days(HttpServletRequest request) {
			String accType[] = { "����У��", "����У��", "�Ž�У��" };
			String xData = "balance_date";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "hdamt", "flamt", "zjamt" };
			String columnTitleNum[] = { "hdnum", "flnum", "zjnum" };
			String areaConsume30DaysYMoney = "";
			String areaCconsume30DaysYNum = "";
			int dataUnitMoney = 1;
			int dataUnitNum = 1;
			List areaConsume30DaysResult = ReportShopBalanceUtil
					.getAreaSalesCompare(consume30DaysDate, createDate,
							"bydate");

			// ����ͼ������
			request.setAttribute("areaConsume30DaysResult",
					areaConsume30DaysResult);
			// ���ɽ��ͼ������
			areaConsume30DaysYMoney = new GetListResultStat().getYLabelMoney(
					areaConsume30DaysResult, "hdamt", dataTypeMoney);
			dataUnitMoney = new GetListResultStat().getUnitValue(
					areaConsume30DaysResult, "hdamt", dataTypeMoney);
			request.setAttribute("areaConsume30DaysYLableMoney",
					areaConsume30DaysYMoney);
			request.setAttribute("areaConsume30DaysChartMoney",
					new DrawBarByTypeMap(areaConsume30DaysResult, accType,
							xData, dataTypeMoney, columnTitleMoney,
							dataUnitMoney).getDataProducer());
			// ���ɱ���ͼ������
			areaCconsume30DaysYNum = new GetListResultStat().getYLabelNum(
					areaConsume30DaysResult, "flnum", dataTypeNum);
			dataUnitNum = new GetListResultStat().getUnitValue(
					areaConsume30DaysResult, "flnum", dataTypeNum);
			
			request.setAttribute("areaConsume30DaysYLableNum",
					areaCconsume30DaysYNum);
			request.setAttribute("areaConsume30DaysChartNum",
					new DrawBarByTypeMap(areaConsume30DaysResult, accType,
							xData, dataTypeNum, columnTitleNum, dataUnitNum)
							.getDataProducer());
		}

		/**
		 * ���30�����ѱ����ͽ��ͳ�� 2006-6-2 hjw
		 * 
		 * @param
		 * @return
		 */
		private void Consume30Weeks(HttpServletRequest request) {
			String accTypeMoney[] = { "���ѽ��" };
			String accTypeNum[] = { "���ѱ���" };
			String xweekData = "sysusedweek";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "tradeamt" };
			String columnTitleNum[] = { "tradenum" };
			String consume30WeeksYMoney = "";
			String consume30WeeksYNum = "";
			int WeekDataUnitMoney = 1;
			int WeekDataUnitNum = 1;
			// -------------------------
			List consume30DaysResult = ReportShopBalanceUtil.getAllConsumeStat(
					beginWeekDate, endWeekDate, "byweek");

			// ����ǰ30��ͳ������,�����ǰ���ڲ������գ����㵱ǰ��
			List consume30WeeksResult = new GetListResultStat().getListByWeek(
					consume30DaysResult, beginWeekDate, endWeekDate);
			Collections.sort(consume30WeeksResult, new SortListByResult(
					"balance_date"));
			request.setAttribute("consume30WeeksResult", consume30WeeksResult);
			// ���ɽ��ͼ������
			consume30WeeksYMoney = new GetListResultStat().getYLabelMoney(
					consume30WeeksResult, "tradeamt", dataTypeMoney);
			WeekDataUnitMoney = new GetListResultStat().getUnitValue(
					consume30WeeksResult, "tradeamt", dataTypeMoney);
			request.setAttribute("consume30WeeksYLableMoney",
					consume30WeeksYMoney);
			request.setAttribute("consume30WeeksChartMoney",
					new DrawBarByTypeMap(consume30WeeksResult, accTypeMoney,
							xweekData, dataTypeMoney, columnTitleMoney,
							WeekDataUnitMoney).getDataProducer());
			// ���ɱ���ͼ������
			consume30WeeksYNum = new GetListResultStat().getYLabelNum(
					consume30WeeksResult, "tradenum", dataTypeNum);
			WeekDataUnitNum = new GetListResultStat().getUnitValue(
					consume30WeeksResult, "tradenum", dataTypeNum);
			request.setAttribute("consume30WeeksYLableNum", consume30WeeksYNum);
			request.setAttribute("consume30WeeksChartNum",
					new DrawBarByTypeMap(consume30WeeksResult, accTypeNum,
							xweekData, dataTypeNum, columnTitleNum,
							WeekDataUnitNum).getDataProducer());
			// ------------------------------------------------------------------------------------
		}

		/**
		 * �������ͳ�ƣ��±����ݣ� 2006-6-2 hjw
		 * 
		 * @param
		 * @return
		 */
		private void Consume30Months(HttpServletRequest request) {
			String accTypeMoney[] = { "���ѽ��" };
			String accTypeNum[] = { "���ѱ���" };
			String xData = "balance_date";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "tradeamt" };
			String columnTitleNum[] = { "tradenum" };
			String consume30WeeksYMoney = "";
			String consume30WeeksYNum = "";
			int MonthDataUnitMoney = 1;
			int MonthDataUnitNum = 1;
			List consume30MonthsResult = ReportShopBalanceUtil
					.getAllConsumeStat(beginMonthDate, endMonthDate, "bymonth");

			request
					.setAttribute("consume30MonthsResult",
							consume30MonthsResult);
			// ���ɽ��ͼ������
			consume30WeeksYMoney = new GetListResultStat().getYLabelMoney(
					consume30MonthsResult, "tradeamt", dataTypeMoney);
			MonthDataUnitMoney = new GetListResultStat().getUnitValue(
					consume30MonthsResult, "tradeamt", dataTypeMoney);
			request.setAttribute("consume30MonthsYLableMoney",
					consume30WeeksYMoney);
			request.setAttribute("consume30MonthsChartMoney",
					new DrawBarByTypeMap(consume30MonthsResult, accTypeMoney,
							xData, dataTypeMoney, columnTitleMoney,
							MonthDataUnitMoney).getDataProducer());
			// ���ɱ���ͼ������
			consume30WeeksYNum = new GetListResultStat().getYLabelNum(
					consume30MonthsResult, "tradenum", dataTypeNum);
			MonthDataUnitNum = new GetListResultStat().getUnitValue(
					consume30MonthsResult, "tradenum", dataTypeNum);
			request
					.setAttribute("consume30MonthsYLableNum",
							consume30WeeksYNum);
			request.setAttribute("consume30MonthsChartNum",
					new DrawBarByTypeMap(consume30MonthsResult, accTypeNum,
							xData, dataTypeNum, columnTitleNum,
							MonthDataUnitNum).getDataProducer());
			// ------------------------------------------------------------------------------------
		}

		/**
		 * ���ֳ�ֵ��ʽ��ֵ����Աȣ�30�죩 2006-6-2 hjw
		 * 
		 * @param
		 * @return
		 */
		private void savingCompare30Days(HttpServletRequest request) {
			String accType[] = { "POS��ֵ", "Ȧ��ת��" };
			String xData = "balance_date";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "posamt", "transferamt" };
			String columnTitleNum[] = { "posnum", "transfernum" };
			String saving30DaysYMoney = "";
			String saving30DaysYNum = "";
			int DayDataUnitMoney = 1;
			int DayDataUnitNum = 1;
			List saving30DaysResult = ReportActiveUtil.getTotleSavingStat(
					consume30DaysDate, createDate, "bydate");

			request.setAttribute("saving30DaysResult", saving30DaysResult);
			// ���ɽ��ͼ������
			saving30DaysYMoney = new GetListResultStat().getYLabelMoney(
					saving30DaysResult, "posamt", dataTypeMoney);
			DayDataUnitMoney = new GetListResultStat().getUnitValue(
					saving30DaysResult, "posamt", dataTypeMoney);
			request.setAttribute("saving30DaysYLableMoney", saving30DaysYMoney);
			request.setAttribute("saving30DaysChartMoney",
					new DrawBarByTypeMap(saving30DaysResult, accType, xData,
							dataTypeMoney, columnTitleMoney, DayDataUnitMoney)
							.getDataProducer());
			// ���ɱ���ͼ������
			saving30DaysYNum = new GetListResultStat().getYLabelNum(
					saving30DaysResult, "transfernum", dataTypeNum);
			DayDataUnitNum = new GetListResultStat().getUnitValue(
					saving30DaysResult, "transfernum", dataTypeNum);
			request.setAttribute("saving30DaysYLableNum", saving30DaysYNum);
			request.setAttribute("saving30DaysChartNum", new DrawBarByTypeMap(
					saving30DaysResult, accType, xData, dataTypeNum,
					columnTitleNum, DayDataUnitNum).getDataProducer());
			// ------------------------------------------------------------------------------------
		}

		/**
		 * ���ѱ���֧Ʊ��ֵ�Ա� 2006-6-5 hjw
		 * 
		 * @param
		 * @return
		 */
		private void billSavingCompare30Days(HttpServletRequest request) {
			String accType[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
			String xData = "balance_date";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "outlaymoney", "ticketmoney" };
			String columnTitleNum[] = { "outlaynum", "ticketnum" };
			String billSaving30DaysYMoney = "";
			String billSaving30DaysYNum = "";
			int DayDataUnitMoney = 1;
			int DayDataUnitNum = 1;
			List billSaving30DaysResult = ReportActiveUtil
					.getBillTotleSavingStat(consume30DaysDate, createDate,
							"bydate");

			request.setAttribute("billSaving30DaysResult",
					billSaving30DaysResult);
			// ���ɽ��ͼ������
			billSaving30DaysYMoney = new GetListResultStat().getYLabelMoney(
					billSaving30DaysResult, "outlaymoney", dataTypeMoney);
			DayDataUnitMoney = new GetListResultStat().getUnitValue(
					billSaving30DaysResult, "outlaymoney", dataTypeMoney);
			request.setAttribute("billSaving30DaysYLableMoney",
					billSaving30DaysYMoney);
			request.setAttribute("billSaving30DaysChartMoney",
					new DrawBarByTypeMap(billSaving30DaysResult, accType,
							xData, dataTypeMoney, columnTitleMoney,
							DayDataUnitMoney).getDataProducer());
			// ���ɱ���ͼ������
			billSaving30DaysYNum = new GetListResultStat().getYLabelNum(
					billSaving30DaysResult, "outlaynum", dataTypeNum);
			DayDataUnitNum = new GetListResultStat().getUnitValue(
					billSaving30DaysResult, "outlaynum", dataTypeNum);
			request.setAttribute("billSaving30DaysYLableNum",
					billSaving30DaysYNum);
			request.setAttribute("billSaving30DaysChartNum",
					new DrawBarByTypeMap(billSaving30DaysResult, accType,
							xData, dataTypeNum, columnTitleNum, DayDataUnitNum)
							.getDataProducer());
			// ------------------------------------------------------------------------------------
		}

		/**
		 * ��У��POS��ֵ�����ͽ��Ա� 2006-6-5 hjw
		 * 
		 * @param
		 * @return
		 */
		private void posSavingCompare30Days(HttpServletRequest request) {
			String accType[] = { "����У��", "����У��", "�Ž�У��" };
			String xData = "balance_date";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "hdamt", "flamt", "zjamt" };
			String columnTitleNum[] = { "hdnum", "flnum", "zjnum" };
			String posSaving30DaysYMoney = "";
			String posSaving30DaysYNum = "";
			int DayDataUnitMoney = 1;
			int DayDataUnitNum = 1;
			List posSaving30DaysResult = ReportOperUtil.posSavingCompareStat(
					consume30DaysDate, createDate, "bydate");

			request
					.setAttribute("posSaving30DaysResult",
							posSaving30DaysResult);
			// ���ɽ��ͼ������
			posSaving30DaysYMoney = new GetListResultStat().getYLabelMoney(
					posSaving30DaysResult, "hdamt", dataTypeMoney);
			DayDataUnitMoney = new GetListResultStat().getUnitValue(
					posSaving30DaysResult, "hdamt", dataTypeMoney);
			request.setAttribute("posSaving30DaysYLableMoney",
					posSaving30DaysYMoney);
			request.setAttribute("posSaving30DaysChartMoney",
					new DrawBarByTypeMap(posSaving30DaysResult, accType, xData,
							dataTypeMoney, columnTitleMoney, DayDataUnitMoney)
							.getDataProducer());
			// ���ɱ���ͼ������
			posSaving30DaysYNum = new GetListResultStat().getYLabelNum(
					posSaving30DaysResult, "flnum", dataTypeNum);
			DayDataUnitNum = new GetListResultStat().getUnitValue(
					posSaving30DaysResult, "flnum", dataTypeNum);
			request.setAttribute("posSaving30DaysYLableNum",
					posSaving30DaysYNum);
			request.setAttribute("posSaving30DaysChartNum",
					new DrawBarByTypeMap(posSaving30DaysResult, accType, xData,
							dataTypeNum, columnTitleNum, DayDataUnitNum)
							.getDataProducer());
			// ------------------------------------------------------------------------------------
		}

		/**
		 * ���ֳ�ֵ��ʽ�ԱȰ��ܺϼƣ����30�ܣ� 2006-6-5 hjw
		 * 
		 * @param
		 * @return
		 */
		private void savingCompare30Weeks(HttpServletRequest request) {
			String accType[] = { "POS��ֵ", "Ȧ��ת��" };
			String xweekData = "sysusedweek";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "posamt", "transferamt" };
			String columnTitleNum[] = { "posnum", "transfernum" };
			String savingCompare30WeeksYMoney = "";
			String savingCompare30WeeksYNum = "";
			int WeekDataUnitMoney = 1;
			int WeekDataUnitNum = 1;
			// -------------------------
			List savingCompare30DaysResult = ReportActiveUtil
					.getTotleSavingStat(beginWeekDate, endWeekDate, "byweek");

			// ����ǰ30��ͳ������,�����ǰ���ڲ������գ����㵱ǰ��
			List savingCompare30WeeksResult = new GetListResultStat()
					.getListByWeek(savingCompare30DaysResult, beginWeekDate,
							endWeekDate);
			Collections.sort(savingCompare30WeeksResult, new SortListByResult(
					"balance_date"));
			request.setAttribute("savingCompare30WeeksResult",
					savingCompare30WeeksResult);
			// ���ɽ��ͼ������
			savingCompare30WeeksYMoney = new GetListResultStat()
					.getYLabelMoney(savingCompare30WeeksResult, "posamt",
							dataTypeMoney);
			WeekDataUnitMoney = new GetListResultStat().getUnitValue(
					savingCompare30WeeksResult, "posamt", dataTypeMoney);
			request.setAttribute("savingCompare30WeeksYLableMoney",
					savingCompare30WeeksYMoney);
			request.setAttribute("savingCompare30WeeksChartMoney",
					new DrawBarByTypeMap(savingCompare30WeeksResult, accType,
							xweekData, dataTypeMoney, columnTitleMoney,
							WeekDataUnitMoney).getDataProducer());
			// ���ɱ���ͼ������
			savingCompare30WeeksYNum = new GetListResultStat().getYLabelNum(
					savingCompare30WeeksResult, "transfernum", dataTypeNum);
			WeekDataUnitNum = new GetListResultStat().getUnitValue(
					savingCompare30WeeksResult, "transfernum", dataTypeNum);
			request.setAttribute("savingCompare30WeeksYLableNum",
					savingCompare30WeeksYNum);
			request.setAttribute("savingCompare30WeeksChartNum",
					new DrawBarByTypeMap(savingCompare30WeeksResult, accType,
							xweekData, dataTypeNum, columnTitleNum,
							WeekDataUnitNum).getDataProducer());
			// ------------------------------------------------------------------------------------
		}

		/**
		 * ���ѱ���֧Ʊ��ֵ����Աȣ��ܣ� 2006-6-5 hjw
		 * 
		 * @param
		 * @return
		 */
		private void billSavingCompare30Weeks(HttpServletRequest request) {
			String accType[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
			String xweekData = "sysusedweek";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "outlaymoney", "ticketmoney" };
			String columnTitleNum[] = { "outlaynum", "ticketnum" };
			String billSavingCompare30WeeksYMoney = "";
			String billSavingCompare30WeeksYNum = "";
			int WeekDataUnitMoney = 1;
			int WeekDataUnitNum = 1;
			// -------------------------
			List billSavingCompare30DaysResult = ReportActiveUtil
					.getBillTotleSavingStat(beginWeekDate, endWeekDate,
							"byweek");

			// ����ǰ30��ͳ������,�����ǰ���ڲ������գ����㵱ǰ��
			List billSavingCompare30WeeksResult = new GetListResultStat()
					.getListByWeek(billSavingCompare30DaysResult,
							beginWeekDate, endWeekDate);
			Collections.sort(billSavingCompare30WeeksResult,
					new SortListByResult("balance_date"));
			request.setAttribute("billSavingCompare30WeeksResult",
					billSavingCompare30WeeksResult);
			// ���ɽ��ͼ������
			billSavingCompare30WeeksYMoney = new GetListResultStat()
					.getYLabelMoney(billSavingCompare30WeeksResult,
							"outlaymoney", dataTypeMoney);
			WeekDataUnitMoney = new GetListResultStat().getUnitValue(
					billSavingCompare30WeeksResult, "outlaymoney",
					dataTypeMoney);
			request.setAttribute("billSavingCompare30WeeksYLableMoney",
					billSavingCompare30WeeksYMoney);
			request.setAttribute("billSavingCompare30WeeksChartMoney",
					new DrawBarByTypeMap(billSavingCompare30WeeksResult,
							accType, xweekData, dataTypeMoney,
							columnTitleMoney, WeekDataUnitMoney)
							.getDataProducer());
			// ���ɱ���ͼ������
			billSavingCompare30WeeksYNum = new GetListResultStat()
					.getYLabelNum(billSavingCompare30WeeksResult, "outlaynum",
							dataTypeNum);
			WeekDataUnitNum = new GetListResultStat().getUnitValue(
					billSavingCompare30WeeksResult, "outlaynum", dataTypeNum);
			request.setAttribute("billSavingCompare30WeeksYLableNum",
					billSavingCompare30WeeksYNum);
			request.setAttribute("billSavingCompare30WeeksChartNum",
					new DrawBarByTypeMap(billSavingCompare30WeeksResult,
							accType, xweekData, dataTypeNum, columnTitleNum,
							WeekDataUnitNum).getDataProducer());
			// ------------------------------------------------------------------------------------
		}

		/**
		 * pos��ֵ��Ȧ��ת�ʶԱȣ�30���£� 2006-6-6 hjw
		 * 
		 * @param
		 * @return
		 */
		private void savingCompare30Months(HttpServletRequest request) {
			String accType[] = { "POS��ֵ", "Ȧ��ת��" };
			String xData = "balance_date";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "posamt", "transferamt" };
			String columnTitleNum[] = { "posnum", "transfernum" };
			String savingCompare30WeeksYMoney = "";
			String savingCompare30WeeksYNum = "";
			int MonthDataUnitMoney = 1;
			int MonthDataUnitNum = 1;
			List savingCompare30MonthsResult = ReportActiveUtil
					.getTotleSavingStat(beginMonthDate, endMonthDate, "bymonth");

			request.setAttribute("savingCompare30MonthsResult",
					savingCompare30MonthsResult);
			// ���ɽ��ͼ������
			savingCompare30WeeksYMoney = new GetListResultStat()
					.getYLabelMoney(savingCompare30MonthsResult, "posamt",
							dataTypeMoney);
			MonthDataUnitMoney = new GetListResultStat().getUnitValue(
					savingCompare30MonthsResult, "posamt", dataTypeMoney);
			request.setAttribute("savingCompare30MonthsYLableMoney",
					savingCompare30WeeksYMoney);
			request.setAttribute("savingCompare30MonthsChartMoney",
					new DrawBarByTypeMap(savingCompare30MonthsResult, accType,
							xData, dataTypeMoney, columnTitleMoney,
							MonthDataUnitMoney).getDataProducer());
			// ���ɱ���ͼ������
			savingCompare30WeeksYNum = new GetListResultStat().getYLabelNum(
					savingCompare30MonthsResult, "transfernum", dataTypeNum);
			MonthDataUnitNum = new GetListResultStat().getUnitValue(
					savingCompare30MonthsResult, "transfernum", dataTypeNum);
			request.setAttribute("savingCompare30MonthsYLableNum",
					savingCompare30WeeksYNum);
			request.setAttribute("savingCompare30MonthsChartNum",
					new DrawBarByTypeMap(savingCompare30MonthsResult, accType,
							xData, dataTypeNum, columnTitleNum,
							MonthDataUnitNum).getDataProducer());
			// ------------------------------------------------------------------------------------
		}

		/**
		 * ���ѱ���֧Ʊ��ֵ����Աȣ�30���£� 2006-6-6 hjw
		 * 
		 * @param
		 * @return
		 */
		private void billSavingCompare30Months(HttpServletRequest request) {
			String accType[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
			String xData = "balance_date";
			String dataTypeMoney = "float";
			String dataTypeNum = "integer";
			String columnTitleMoney[] = { "outlaymoney", "ticketmoney" };
			String columnTitleNum[] = { "outlaynum", "ticketnum" };
			String billSavingCompare30WeeksYMoney = "";
			String billSavingCompare30WeeksYNum = "";
			int MonthDataUnitMoney = 1;
			int MonthDataUnitNum = 1;
			List billSavingCompare30MonthsResult = ReportActiveUtil
					.getBillTotleSavingStat(beginMonthDate, endMonthDate,
							"bymonth");

			request.setAttribute("billSavingCompare30MonthsResult",
					billSavingCompare30MonthsResult);
			// ���ɽ��ͼ������
			billSavingCompare30WeeksYMoney = new GetListResultStat()
					.getYLabelMoney(billSavingCompare30MonthsResult,
							"outlaymoney", dataTypeMoney);
			MonthDataUnitMoney = new GetListResultStat().getUnitValue(
					billSavingCompare30MonthsResult, "outlaymoney",
					dataTypeMoney);
			request.setAttribute("billSavingCompare30MonthsYLableMoney",
					billSavingCompare30WeeksYMoney);
			request.setAttribute("billSavingCompare30MonthsChartMoney",
					new DrawBarByTypeMap(billSavingCompare30MonthsResult,
							accType, xData, dataTypeMoney, columnTitleMoney,
							MonthDataUnitMoney).getDataProducer());
			// ���ɱ���ͼ������
			billSavingCompare30WeeksYNum = new GetListResultStat()
					.getYLabelNum(billSavingCompare30MonthsResult, "outlaynum",
							dataTypeNum);
			MonthDataUnitNum = new GetListResultStat().getUnitValue(
					billSavingCompare30MonthsResult, "outlaynum", dataTypeNum);
			request.setAttribute("billSavingCompare30MonthsYLableNum",
					billSavingCompare30WeeksYNum);
			request.setAttribute("billSavingCompare30MonthsChartNum",
					new DrawBarByTypeMap(billSavingCompare30MonthsResult,
							accType, xData, dataTypeNum, columnTitleNum,
							MonthDataUnitNum).getDataProducer());
			// ------------------------------------------------------------------------------------
		}
		
		/**
		 * Ȧ��ɹ���ͳ��
		 * 2006-6-6
		 * hjw
		 * @param
		 * @return
		 */
		private void transferSuccessRate(HttpServletRequest request){
			String xData = "balance_date";
			String yLabelRate = "";
			String yLabelAccount = "";
			String dataType = "float";
			String dataTypeAccount = "integer";
			String rateAccType[] = { "Ȧ��ɹ���" };
			String rateColumnTitle[] = {"rate"};
			String inaccountType[] = {"���ʱ���"};
			String inaccountColumnTitle[] = {"inaccount"};
			int dataUnitRate = 1;
			int dataUnitAccount = 1;
			int dateUnit = 1;
			List transferSuccResult = ReportActiveUtil.getTransferSuccessRate(
					tranBeginDate, createDate, "bydate");
			dateUnit = transferSuccResult.size()/9;
			request.setAttribute("transferSuccResult",
					transferSuccResult);
			yLabelRate = new GetListResultStat().getYLabelRate(transferSuccResult, "rate",dataType);
			yLabelAccount = new GetListResultStat().getYLabelNum(transferSuccResult, "inaccount",dataTypeAccount);
			dataUnitRate = new GetListResultStat().getUnitValue(transferSuccResult, "rate",dataType);
			dataUnitAccount = new GetListResultStat().getUnitValue(transferSuccResult, "inaccount",dataTypeAccount);
			request.setAttribute("transferSuccessRateYLabel",yLabelRate);
			request.setAttribute("transferSuccessAccountYLabel",yLabelAccount);
			request.setAttribute("transferRateChart",
					new DrawTimeSeries(transferSuccResult, rateColumnTitle, xData,
							dataType, rateAccType, dataUnitRate)
							.getTimeSeriesProducer());
			request.setAttribute("transferAccountChart",
					new DrawTimeSeries(transferSuccResult, inaccountColumnTitle, xData,
							dataTypeAccount, inaccountType, dataUnitAccount)
							.getTimeSeriesProducer());
			request.setAttribute("linedataColor", new CustomerDrawChart(true,showCustColor,dateUnit)
					.getTimeSeriesPostProcessor());

		}
	    public void convertToPdf(JFreeChart chart, int width, int height, String filename) {
	    	// step 1
	    	Document document = new Document(new Rectangle(width, height));
	    	try {
	    		// step 2
	    		PdfWriter writer;
				writer = PdfWriter.getInstance(document, new FileOutputStream(filename));
				// step 3
	    		document.open();
	    		// step 4
	    		PdfContentByte cb = writer.getDirectContent();
	    		PdfTemplate tp = cb.createTemplate(width, height);
	    		Graphics2D g2d = tp.createGraphics(width, height, new DefaultFontMapper());
	    		Rectangle2D r2d = new Rectangle2D.Double(0, 0, width, height);
	    		chart.draw(g2d, r2d);
	    		g2d.dispose();
	    		cb.addTemplate(tp, 0, 0);
	    	}
	    	catch(DocumentException de) {
	    		de.printStackTrace();
	    	}
	    	catch (FileNotFoundException e) {
	    		e.printStackTrace();
	    	}
	    	// step 5
	    	document.close();
	    }
	  
	    
    	/**
    	 * �����ɵ�ͼ��ת��ΪPDF��ʽ
    	 * 2006-6-14
    	 * hjw
    	 * @param
    	 * @return
    	 */
	    private void drawPDFCellAndGraph(HttpServletRequest request){
			String pdfSavePath = request.getRealPath("/")+"/yktrun/createdata/reportdata.doc";
			System.out.println(pdfSavePath);
			//String path = request.getContextPath()+"/servlet/DisplayChart?filename=jfreechart-809.png";
			//System.out.println(path);

			HttpSession session = request.getSession();
			new ReportDataExport(pdfSavePath,endWeekDate,createDate,session);
			// step 1: creation of a document-object
			
	    }
	}
	}

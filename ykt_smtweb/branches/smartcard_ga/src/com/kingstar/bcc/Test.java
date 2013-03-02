package com.kingstar.bcc;

import java.math.BigDecimal;

public class Test {

	/**
	 * Method name: main<br>
	 * Description: <br>
	 * Return: void<br>
	 * Args: @param args
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      何林青    Mar 13, 2008  <br>
	 * @author   何林青
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
//		BigDecimal b = new BigDecimal("240.4253225213213");
//		BigDecimal c = new BigDecimal("100");
//		String cout_card_amount = String.valueOf(b.multiply(c).doubleValue());
		double b = 12.4319212412312;
		BigDecimal s = new BigDecimal(Double.toString(b));
		BigDecimal c = new BigDecimal("100");
		BigDecimal d = new BigDecimal("1");
		BigDecimal f = s.divide(d, 2, BigDecimal.ROUND_HALF_UP);
		String cout_card_amount = String.valueOf(f.multiply(c).intValue());
		
		System.out.println(cout_card_amount);
		

	}

}

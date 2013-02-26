package com.sungard.ticketsys.component;

import java.awt.Rectangle;
import javax.swing.JLabel;
import javax.swing.JPanel;



public class InputComponet {
	
	/**
	 * 输入框
	 * @param right
	 * @param inputText
	 * @param TextName
	 * @param validateType
	 * @param notNull
	 * @param x
	 * @param y
	 * @return
	 */
	public static InputTextField textField(JPanel right,InputTextField inputText,String textName,String validateType,boolean notNull,int x,int y) {
		if (inputText == null) {
			inputText = new InputTextField();
		}
		inputText.setValidateType(validateType);
		inputText.setNotNull(notNull);
		inputText.setName(textName);
		inputText.setBounds(new Rectangle(x, y, 250, 26));
		right.add(inputText, null);
		
		return inputText;
	}
	
	/**
	 * 时间框
	 * @param right
	 * @param inputTimeField
	 * @param textName
	 * @param lb_error
	 * @param notNull
	 * @param x
	 * @param y
	 * @return
	 */
	public static TimeField timeField(JPanel right,TimeField inputTimeField,String textName,JLabel lb_error,boolean notNull,int x,int y){
		if(inputTimeField == null){
			inputTimeField = new TimeField(right, lb_error, x, y);
		}
		inputTimeField.setNotNull(notNull);
		inputTimeField.setName(textName);
		right.add(inputTimeField, null);
		return inputTimeField;
	}
	
	
	public static InputTextField moneyField(JPanel right,InputTextField moneyText,String textName,boolean notNull,int x,int y) {
		if (moneyText == null) {
			moneyText = new InputTextField();
		}
		moneyText.setValidateType(ValidateType.MONEY);
		moneyText.setNotNull(notNull);
		moneyText.setName(textName);
		moneyText.setBounds(new Rectangle(x, y, 250, 26));
		
		JLabel lb_priceyuan = new JLabel();
		lb_priceyuan.setBounds(new Rectangle(x+250, y, 20, 26));
		lb_priceyuan.setText("元");
		right.add(lb_priceyuan, null);
		right.add(moneyText, null);
		
		return moneyText;

	}
	
	
}

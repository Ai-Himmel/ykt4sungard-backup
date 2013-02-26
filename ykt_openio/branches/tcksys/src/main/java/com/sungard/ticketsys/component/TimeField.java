package com.sungard.ticketsys.component;

import java.awt.Rectangle;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;


public class TimeField extends JTextField{
	
	private static final long serialVersionUID = 1L;
	private JTextField tf_departhour;
	private JPanel right;
	private JLabel lb_error;
	
	private int height = 26;
	private int tfwidth = 63;
	private int lbwidth = 30;
	
	private JLabel lb_departhour = null;
	private JTextField tf_departminute = null;
	private JLabel lb_departminute = null;
	private JTextField tf_departsecond = null;
	private JLabel lb_departsecond = null;
	
	//�Ƿ�����Ϊ�յı�־
	private boolean notNull = false;
	
	private String departTime;
	
	private String name;
	
	public TimeField(JPanel right,JLabel lb_error,int x,int y){
		this.right = right;
		this.lb_error = lb_error;
		timeField(x,y);
	}
	



	/**
	 * This method initializes tf_startaddr
	 * 
	 * @return javax.swing.JTextField
	 */
	private void timeField( int x, int y) {
		
			tf_departhour = new JTextField();
			tf_departhour.setBounds(new Rectangle(x, y, 63, 26));
			lb_departhour = new JLabel();
			lb_departhour.setBounds(new Rectangle(x+tfwidth, y, 30, 26));
			lb_departhour.setText("ʱ");

			tf_departminute = new JTextField();
			tf_departminute.setBounds(new Rectangle(x+tfwidth+lbwidth, y, 63, 26));
			lb_departminute = new JLabel();
			lb_departminute.setBounds(new Rectangle(x+2*tfwidth+lbwidth, y, 30, 26));
			lb_departminute.setText("��");

			tf_departsecond = new JTextField();
			tf_departsecond.setBounds(new Rectangle(x+2*tfwidth+2*lbwidth, y, 63, 26));
			lb_departsecond = new JLabel();
			lb_departsecond.setBounds(new Rectangle(x+3*tfwidth+2*lbwidth, y, 30, 26));
			lb_departsecond.setText("��");

			right.add(tf_departhour, null);
			right.add(lb_departhour, null);
			right.add(tf_departminute, null);
			right.add(lb_departminute, null);
			right.add(tf_departsecond, null);
			right.add(lb_departsecond, null);
	}
	
	public void clearTimeField(){
		tf_departhour.setText("");
		departTime = null;
		tf_departminute.setText("");
		tf_departsecond.setText("");
	}
	
	/**
	 * ��֤����ʱ�䲢��ȡ����ʱ��
	 * 
	 * @param flag
	 * @param jp
	 * @return
	 */
	public boolean checkTime() {
		String departH = tf_departhour.getText().trim();
		String departM = tf_departminute.getText().trim();
		String departS = tf_departsecond.getText().trim();
		if (departH.equals("") || departM.equals("") || departS.equals("")) {
			if(notNull){
				lb_error.setText("�ύʧ�ܣ�["+name+"]����Ϊ�գ�������!");
				return false;
			}
			
		} else {
			int departHi;
			try {
				departHi = Integer.parseInt(departH);
				if (departHi < 0 || departHi > 23) {
					lb_error.setText("�ύʧ�ܣ��������["+name+"]��ʱ����ʽ����ȷ��������!");
					return false;
				} else {
					if (departHi < 10) {
						departH = departHi + "0";
					}
				}
			} catch (Exception e2) {
				lb_error.setText("�ύʧ�ܣ��������["+name+"]��ʱ����ʽ����ȷ��������!");
				return false;
			}

			int departMI;
			try {
				departMI = Integer.parseInt(departM);
				if (departMI < 0 || departMI > 59) {
					lb_error.setText("�ύʧ�ܣ��������["+name+"]���֣���ʽ����ȷ��������!");
					return false;
				} else {
					if (departMI < 10) {
						departM = departMI + "0";
					}
				}
			} catch (Exception e2) {
				lb_error.setText("�ύʧ�ܣ��������["+name+"]���֣���ʽ����ȷ��������!");
				return false;
			}
			int departSI;
			try {
				departSI = Integer.parseInt(departS);
				if (departSI < 0 || departSI > 59) {
					lb_error.setText("�ύʧ�ܣ��������["+name+"]���룩��ʽ����ȷ��������!");
					return false;
				} else {
					if (departSI < 10) {
						departS = departSI + "0";
					}
				}
			} catch (Exception e2) {
				lb_error.setText("�ύʧ�ܣ��������["+name+"]���룩��ʽ����ȷ��������!");
				return false;
			}

		}

		departTime = departH + departM + departS;

		return true;
	}


	public String getDepartTime() {
		return departTime;
	}

	public void setDepartTime(String departTime) {
		this.departTime = departTime;
	}


	public JLabel getLb_error() {
		return lb_error;
	}

	public void setLb_error(JLabel lbError) {
		lb_error = lbError;
	}


	public boolean isNotNull() {
		return notNull;
	}


	public void setNotNull(boolean notNull) {
		this.notNull = notNull;
	}


	public String getName() {
		return name;
	}


	public void setName(String name) {
		this.name = name;
	}

	public void setHourValue(String hour) {
		tf_departhour.setText(hour);
	}

	public void setMinuteValue(String minute) {
		tf_departminute.setText(minute);
	}

	public void setSecondValue(String second) {
		tf_departsecond.setText(second);
	}
}

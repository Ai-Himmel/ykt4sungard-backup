package com.sungard.ticketsys.component;

import java.awt.Component;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.sungard.ticketsys.common.MyFormat;
import com.sungard.ticketsys.service.LineManager;

public class Validate {
	
	/**
	 * ��֤����������Ƿ�Ϸ�
	 * 
	 * @return
	 */
	public static  boolean checkInputData(JPanel right,JLabel lb_error) {
		 Component components[] = right.getComponents();
		 
		 //��֤JTextField������ֵ
		 for (int i = 0; i < components.length; i++) {
			 //�������֤
			if(components[i].getClass().toString().endsWith("InputTextField")){
				InputTextField  texttField =(InputTextField)components[i];
				String value = texttField.getText().trim();
				boolean isEmpty = (texttField.getText().trim()==null)||("".equals(texttField.getText().trim()));
				String validateType = texttField.getValidateType();
				boolean notNull = texttField.isNotNull();
				
				if(notNull && isEmpty){
					lb_error.setText("�ύʧ�ܣ�["+texttField.getName()+"]����Ϊ�գ�������!");
					return false;
				}
				
				//�ַ�����ʽ��֤
				if(validateType.equals(ValidateType.STRING)){
					if (!isEmpty && value.length() > 12) {
						lb_error.setText("�ύʧ�ܣ��������["+texttField.getName()+"]̫�����벻Ҫ����12λ!");
					    return false;
					    }
					}
				
				//��Ǯ��ʽ��֤
				if(validateType.equals(ValidateType.MONEY)){
					if(!isEmpty && !MyFormat.checkMoneySdf(value)){
						lb_error.setText("�ύʧ�ܣ�["+texttField.getName()+"]��ʽ����ȷ��������С��λ��λ��������");
						return false;
					}
				}
				
				//�������������㣩
				if(!isEmpty && validateType.equals(ValidateType.INT)){
					try {
						int valuei = Integer.parseInt(value); 
						if(valuei<1){
							lb_error.setText("�ύʧ�ܣ�["+texttField.getName()+"]��ʽ����ȷ����������������������");
							return false;
							}
						} catch (Exception e2) {
							lb_error.setText("�ύʧ�ܣ�["+texttField.getName()+"]��ʽ����ȷ����������������������");
							return false;
						}	
					}
			}
			
			//ѡ�����֤
			if(components[i].getClass().toString().endsWith("InputComboBox")){
				InputComboBox inputComboBox = (InputComboBox)components[i];
				String value = inputComboBox.getSelectedItem().toString();
				if (inputComboBox.isNotNull()&&inputComboBox.getSelectedIndex() == 0) {
					lb_error.setText("�ύʧ�ܣ�û��ѡ��["+inputComboBox.getName()+"]����ѡ��!");
					return false;
				}
				if (value.equals("")) {
					lb_error.setText("�ύʧ�ܣ�û��ѡ��["+inputComboBox.getName()+"]����ѡ��!");
					return false;
				}
				
			}
			
			//ʱ�����֤
			if(components[i].getClass().toString().endsWith("TimeField")){
				TimeField  texttField =(TimeField)components[i];
				if(!texttField.checkTime()){
					return false;
				}
				
			}
			
		}
		 
		return true;
	}


}

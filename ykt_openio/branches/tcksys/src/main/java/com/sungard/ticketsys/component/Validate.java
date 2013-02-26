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
	 * 验证输入的数据是否合法
	 * 
	 * @return
	 */
	public static  boolean checkInputData(JPanel right,JLabel lb_error) {
		 Component components[] = right.getComponents();
		 
		 //验证JTextField的输入值
		 for (int i = 0; i < components.length; i++) {
			 //输入框验证
			if(components[i].getClass().toString().endsWith("InputTextField")){
				InputTextField  texttField =(InputTextField)components[i];
				String value = texttField.getText().trim();
				boolean isEmpty = (texttField.getText().trim()==null)||("".equals(texttField.getText().trim()));
				String validateType = texttField.getValidateType();
				boolean notNull = texttField.isNotNull();
				
				if(notNull && isEmpty){
					lb_error.setText("提交失败：["+texttField.getName()+"]不能为空，请输入!");
					return false;
				}
				
				//字符串格式验证
				if(validateType.equals(ValidateType.STRING)){
					if (!isEmpty && value.length() > 12) {
						lb_error.setText("提交失败：您输入的["+texttField.getName()+"]太长，请不要超过12位!");
					    return false;
					    }
					}
				
				//金钱格式验证
				if(validateType.equals(ValidateType.MONEY)){
					if(!isEmpty && !MyFormat.checkMoneySdf(value)){
						lb_error.setText("提交失败：["+texttField.getName()+"]格式不正确，请输入小数位两位的正数！");
						return false;
					}
				}
				
				//正整数（大于零）
				if(!isEmpty && validateType.equals(ValidateType.INT)){
					try {
						int valuei = Integer.parseInt(value); 
						if(valuei<1){
							lb_error.setText("提交失败：["+texttField.getName()+"]格式不正确，请输入大于零的正整数！");
							return false;
							}
						} catch (Exception e2) {
							lb_error.setText("提交失败：["+texttField.getName()+"]格式不正确，请输入大于零的正整数！");
							return false;
						}	
					}
			}
			
			//选择框验证
			if(components[i].getClass().toString().endsWith("InputComboBox")){
				InputComboBox inputComboBox = (InputComboBox)components[i];
				String value = inputComboBox.getSelectedItem().toString();
				if (inputComboBox.isNotNull()&&inputComboBox.getSelectedIndex() == 0) {
					lb_error.setText("提交失败：没有选择["+inputComboBox.getName()+"]，请选择!");
					return false;
				}
				if (value.equals("")) {
					lb_error.setText("提交失败：没有选择["+inputComboBox.getName()+"]，请选择!");
					return false;
				}
				
			}
			
			//时间框验证
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

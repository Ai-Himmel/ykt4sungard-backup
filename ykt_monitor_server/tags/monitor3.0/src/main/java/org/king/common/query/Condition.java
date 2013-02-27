package org.king.common.query;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-6
 */
public class Condition {

    //����
    private String propertyName;

    //������
    private String operator;

    //between�ĵ�һ��ֵ
    private Object firstValue;

    //between�ĵڶ���ֵ
    private Object secondValue;

    //���ͣ�date,string��������
    private String type;

    //ʵ����
    //todo condition �е�entity��ʱû���õ���Ŀǰ�������ѯ�ķ�ʽΪ��condition��property������ָ������entity.name
    private String entity;

    //����
    private String andOr;

    //����
    private String bracket;

    public String getPropertyName() {
        return propertyName;
    }

    public void setPropertyName(String propertyName) {
        this.propertyName = propertyName;
    }

    public String getOperator() {
        return operator;
    }

    public void setOperator(String operator) {
        this.operator = operator;
    }

    public Object getFirstValue() {
        return firstValue;
    }

    public void setFirstValue(Object firstValue) {
        this.firstValue = firstValue;
    }

    public Object getSecondValue() {
        return secondValue;
    }

    public void setSecondValue(Object secondValue) {
        this.secondValue = secondValue;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getEntity() {
        return entity;
    }

    public void setEntity(String entity) {
        this.entity = entity;
    }

    public String getAndOr() {
        return andOr;
    }

    public void setAndOr(String andOr) {
        this.andOr = andOr;
    }

    public String getBracket() {
        return bracket;
    }

    public void setBracket(String bracket) {
        this.bracket = bracket;
    }
}
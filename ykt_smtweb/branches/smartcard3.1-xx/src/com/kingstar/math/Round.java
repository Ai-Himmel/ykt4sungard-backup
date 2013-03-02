package com.kingstar.math;

import java.math.BigDecimal;

/**
 * ��Round.java��ʵ���������ṩ��ȷ��С��λ�������봦�� 
 */
public class Round
{
    /**
     * �ṩ��ȷ��С��λ�������봦��
     * @param v ��Ҫ�������������
     * @param scale С���������λ
     * @return ���������Ľ��
     */
    private double round(double v, int scale)
    {
        if (scale < 0)
        {
            throw new IllegalArgumentException(
                    "The scale must be a positive integer or zero");
        }

        BigDecimal b = new BigDecimal(Double.toString(v));
        BigDecimal one = new BigDecimal("1");
        return b.divide(one, scale, BigDecimal.ROUND_HALF_UP).doubleValue();
    }

    /**
     * 
     * ����������ȡ������
     * @param v
     * @return
     */
    public int roundDown(double v)
    {
        BigDecimal b = new BigDecimal(Double.toString(v));
        BigDecimal one = new BigDecimal("1");
        return b.divide(one, 0, BigDecimal.ROUND_DOWN).intValue();
    }

    /**
     * 
     * ��������ȡ������
     * @param v
     * @return
     */
    public int roundUp(double v)
    {
        BigDecimal b = new BigDecimal(Double.toString(v));
        BigDecimal one = new BigDecimal("1");
        return b.divide(one, 0, BigDecimal.ROUND_UP).intValue();
    }

    public static void main(String[] args)
    {
        Round round = new Round();
        
        System.out.println(round.round(00.45656, 4));
        
        System.out.println(round.roundDown(18.567));
        
        System.out.println(round.roundUp(18.567));
        
        double doubleValue = 18.567;
        
        int intValue = (int)doubleValue;
        
        System.out.println(intValue);
              System.out.println(Integer.MAX_VALUE);
              System.out.println(Long.MAX_VALUE);

    }
}

/**
 * 
 */
package com.kingstargroup.advquery.card;

/**
 * @author Administrator
 *
 */
public class CardUseBy extends AbstractResult{
	private String dictCaption;
	private Integer cardNum ;
	
	public CardUseBy(String dictCaption,Integer cardNum){
		this.dictCaption = dictCaption;
		this.cardNum = cardNum;
	}
	
	public String getDictCaption(){
		return dictCaption;
	}

	public void setDictCaption(){
		this.dictCaption = dictCaption;
	}
	
	public Integer getCardNum(){
		return cardNum;
	}
	
	public void setCardNum(){
		this.cardNum = cardNum;
	}
}

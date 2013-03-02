package com.kingstargroup.ecard.hibernate.web;
       
import java.io.Serializable;

public class WebDictionaryKey 
	 implements Serializable
	 {
	     /** The cached hash code value for this instance.  Settting to 0 triggers re-calculation. */
	     private volatile int hashValue = 0;

	     /** The value of the DICT_NO component of this composite id. */
	     private java.lang.String dicNo;

	     /** The value of the DICT_VALUE component of this composite id. */
	     private java.lang.String dicValue;

	     /**
	      * Simple constructor of TPifDictionaryKey instances.
	      */
	     public WebDictionaryKey()
	     {
	     }
	     public WebDictionaryKey(String dicNo,String dicValue){
	       this.dicNo=dicNo;
	       this.dicValue=dicValue;
	     }

	     public java.lang.String getDicNo() {
			return dicNo;
		}

		public void setDicNo(java.lang.String dicNo) {
			this.dicNo = dicNo;
		}



		public java.lang.String getDicValue() {
			return dicValue;
		}



		public void setDicValue(java.lang.String dicValue) {
			this.dicValue = dicValue;
		}



		public int getHashValue() {
			return hashValue;
		}



		public void setHashValue(int hashValue) {
			this.hashValue = hashValue;
		}
	}



	   


package com.kingstargroup.ecard.hibernate.equipment;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

public class AbstractMaintain  extends com.kingstargroup.ecard.common.BasicPersistence
    implements Serializable {
	
	private Integer  id;
	private String  applyTitle;
	private String  applyInfo;
	private String  applyPeople;
	private String  applyTime;
	private String  status;
	private String  answerInfo;
	private String  answerPeople;
	private String  answerTime;
	private String  schoolArea;
	private String  contactMethod;
	private String  accidentDate; 
	private String  accidentTime;
	private String  operator;
	private String  accidentExplain;
	private String  operatorDepend;
	private String  operatorStep;
	private String  applyPeopleAnswer;
	private String  inputPeople;
	private String  applyEmail;
	
	private Set     maintainType  = new HashSet(); 
	
	public void setMaintainType(Set maintainType) {
		this.maintainType = maintainType;
	}
	public AbstractMaintain(){
		
	}
	public AbstractMaintain(Integer id){
		
	}
	
	public String getAnswerInfo() {
		return answerInfo;
	}
	public void setAnswerInfo(String answerInfo) {
		this.answerInfo = answerInfo;
	}
	public String getAnswerPeople() {
		return answerPeople;
	}
	public void setAnswerPeople(String answerPeople) {
		this.answerPeople = answerPeople;
	}
	public String getAnswerTime() {
		return answerTime;
	}
	public void setAnswerTime(String answerTime) {
		this.answerTime = answerTime;
	}
	public String getApplyInfo() {
		return applyInfo;
	}
	public void setApplyInfo(String applyInfo) {
		this.applyInfo = applyInfo;
	}
	public String getApplyPeople() {
		return applyPeople;
	}
	public void setApplyPeople(String applyPeople) {
		this.applyPeople = applyPeople;
	}
	public String getApplyTime() {
		return applyTime;
	}
	public void setApplyTime(String applyTime) {
		this.applyTime = applyTime;
	}
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	
	public String getApplyTitle() {
		return applyTitle;
	}
	public void setApplyTitle(String applyTitle) {
		this.applyTitle = applyTitle;
	}
	public Set getMaintainType() {
		return maintainType;
	}
	public String getStatus() {
		return status;
	}
	public void setStatus(String status) {
		this.status = status;
	}
	public String getAccidentDate() {
		return accidentDate;
	}
	public void setAccidentDate(String accidentDate) {
		this.accidentDate = accidentDate;
	}
	public String getAccidentExplain() {
		return accidentExplain;
	}
	public void setAccidentExplain(String accidentExplain) {
		this.accidentExplain = accidentExplain;
	}
	public String getAccidentTime() {
		return accidentTime;
	}
	public void setAccidentTime(String accidentTime) {
		this.accidentTime = accidentTime;
	}
	public String getContactMethod() {
		return contactMethod;
	}
	public void setContactMethod(String contactMethod) {
		this.contactMethod = contactMethod;
	}
	public String getOperator() {
		return operator;
	}
	public void setOperator(String operator) {
		this.operator = operator;
	}
	public String getOperatorDepend() {
		return operatorDepend;
	}
	public void setOperatorDepend(String operatorDepend) {
		this.operatorDepend = operatorDepend;
	}
	public String getOperatorStep() {
		return operatorStep;
	}
	public void setOperatorStep(String operatorStep) {
		this.operatorStep = operatorStep;
	}
	public String getSchoolArea() {
		return schoolArea;
	}
	public void setSchoolArea(String schoolArea) {
		this.schoolArea = schoolArea;
	}
	public String getApplyPeopleAnswer() {
		return applyPeopleAnswer;
	}
	public void setApplyPeopleAnswer(String applyPeopleAnswer) {
		this.applyPeopleAnswer = applyPeopleAnswer;
	}

	public String getInputPeople() {
		return inputPeople;
	}
	public void setInputPeople(String inputPeople) {
		this.inputPeople = inputPeople;
	}
	public String getApplyEmail() {
		return applyEmail;
	}
	public void setApplyEmail(String applyEmail) {
		this.applyEmail = applyEmail;
	}
}

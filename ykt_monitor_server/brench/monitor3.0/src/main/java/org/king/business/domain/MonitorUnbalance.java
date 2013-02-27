package org.king.business.domain;


/**
 * MonitorUnbalance entity. @author MyEclipse Persistence Tools
 */
public class MonitorUnbalance extends AbstractMonitorUnbalance implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorUnbalance() {
	}

	/** full constructor */
	public MonitorUnbalance(Integer stm100acc, Double stm100amt,
			Integer stm100accchange, Double stm100amtchange,
			Integer stm50acc, Double stm50amt, Integer stm50accchange,
			Double stm50amtchange, Integer stm10acc, Double stm10amt,
			Integer stm10accchange, Double stm10amtchange,
			Integer stm1acc, Double stm1amt, Integer stm1accchange,
			Double stm1amtchange, Integer stm0acc, Double stm0amt,
			Integer stm0accchange, Double stm0amtchange, Integer st1acc,
			Double st1amt, Integer st1accchange, Double st1amtchange,
			Integer st10acc, Double st10amt, Integer st10accchange,
			Double st10amtchange, Integer st50acc, Double st50amt,
			Integer st50accchange, Double st50amtchange,
			Integer st100acc, Double st100amt, Integer st100accchange,
			Double st100amtchange, Integer lt100acc, Double lt100amt,
			Integer lt100accchange, Double lt100amtchange,
			Integer totalacc, Double totalamt, Double totalabsamt) {
		super(stm100acc, stm100amt, stm100accchange, stm100amtchange, stm50acc,
				stm50amt, stm50accchange, stm50amtchange, stm10acc, stm10amt,
				stm10accchange, stm10amtchange, stm1acc, stm1amt,
				stm1accchange, stm1amtchange, stm0acc, stm0amt, stm0accchange,
				stm0amtchange, st1acc, st1amt, st1accchange, st1amtchange,
				st10acc, st10amt, st10accchange, st10amtchange, st50acc,
				st50amt, st50accchange, st50amtchange, st100acc, st100amt,
				st100accchange, st100amtchange, lt100acc, lt100amt,
				lt100accchange, lt100amtchange, totalacc, totalamt, totalabsamt);
	}

}

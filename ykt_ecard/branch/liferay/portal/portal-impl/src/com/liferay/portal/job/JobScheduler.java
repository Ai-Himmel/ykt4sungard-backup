/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.job;

import com.liferay.util.Time;

import java.util.Date;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.quartz.JobDetail;
import org.quartz.Scheduler;
import org.quartz.SchedulerException;
import org.quartz.SimpleTrigger;
import org.quartz.Trigger;
import org.quartz.impl.StdSchedulerFactory;

/**
 * <a href="JobScheduler.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JobScheduler {

	public static void schedule(IntervalJob intervalJob)
		throws SchedulerException {

		Date startTime = new Date(System.currentTimeMillis() + Time.MINUTE * 3);
		Date endTime = null;

		JobDetail jobDetail = new JobDetail(
			intervalJob.getClass().getName(), Scheduler.DEFAULT_GROUP,
			intervalJob.getClass());

		Trigger trigger = new SimpleTrigger(
			intervalJob.getClass().getName() + "_TRIGGER",
			Scheduler.DEFAULT_GROUP, startTime, endTime,
			SimpleTrigger.REPEAT_INDEFINITELY,
			intervalJob.getInterval());

		scheduleJob(jobDetail, trigger);
	}

	public static void scheduleJob(JobDetail jobDetail, Trigger trigger)
		throws SchedulerException {

		_getScheduler().scheduleJob(jobDetail, trigger);
	}

	public static void scheduleJob(Trigger trigger) throws SchedulerException {
		_getScheduler().scheduleJob(trigger);
	}

	public static void shutdown() {
		_instance._shutdown();
	}

	public static void triggerJob(String jobName, String groupName)
		throws SchedulerException {

		_getScheduler().triggerJob(jobName, groupName);
	}

	public static void unscheduleJob(String className)
		throws SchedulerException {

		unscheduleJob(className + "_TRIGGER", Scheduler.DEFAULT_GROUP);
	}

	public static void unscheduleJob(String triggerName, String groupName)
		throws SchedulerException {

		_getScheduler().unscheduleJob(triggerName, groupName);
	}

	private static Scheduler _getScheduler() {
		return _instance._scheduler;
	}

	private JobScheduler() {
		_start();
	}

	private void _start() {
		StdSchedulerFactory sf = new StdSchedulerFactory();

		try {
			_scheduler = sf.getScheduler();

			_scheduler.start();
		}
		catch (SchedulerException se) {
			_log.error(se);
		}
	}

	private void _shutdown() {
		try {
			if (!_scheduler.isShutdown()) {
				_scheduler.shutdown();
			}
		}
		catch (SchedulerException se) {
			_log.error(se);
		}
	}

	private static Log _log = LogFactory.getLog(JobScheduler.class);

	private static JobScheduler _instance = new JobScheduler();

	private Scheduler _scheduler;

}
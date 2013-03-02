package com.kingstargroup.conference.mail;

import lotus.domino.NotesException;
import lotus.domino.Session;
import lotus.domino.NotesFactory;
import lotus.domino.Database;
import lotus.domino.EmbeddedObject;
import lotus.domino.RichTextItem;
import lotus.domino.Document;
import lotus.domino.View;

import java.util.*;

/**
 * 发送lotus邮件，客户是domino5.11版本，发送邮件需要参考5.11的designer的JAVA库对LOTUS数据库的操作。
 * 添加的附件必须放在DOMINO服务器上，不能放在客户端添加附件，不要问为什么，这是事实。 例如：放在AS400
 * 的em_01/test/test.tar,在程序使用相对路径，"test/test.tar"相对于邮件的根目录em_01.
 * 
 * 在操作完后，要对DOMINO上的使用的资源释放掉，一般只须释放掉database和session.
 * 语法：database.recycle(),session.recycle();
 * 
 * 
 * 
 * 
 * @author songlb
 * 
 */
public class SendMailLotus {
	private RichTextItem rti = null;

	private Document memo = null;

	private Session sNotes = null;

	private Database dbMail = null;

	public boolean attachFlag = false;

	/** 日志文件 */
	static org.apache.log4j.Logger log = org.apache.log4j.Logger
			.getLogger(SendMailLotus.class);

	public SendMailLotus() {
	}

	public void startSend(long userID, String[] to, String from,
			String smtpServer, String popServer, String subject, int interval,
			int priorityLevel, Date dateSent, String probeHost, String user,
			String password, String returnState, String cawtoArgument,
			int attachedSize, String sqlServer) throws NotesException {

		try {

			// sNotes = (Session) NotesFactory.createSession(smtpServer, user,
			// password);
			String strIOR = NotesFactory.getIOR(smtpServer);
			sNotes = NotesFactory.createSessionWithIOR(strIOR, user, password);

			dbMail = (Database) sNotes.getDatabase(sNotes.getServerName(),
					"mail\\" + user + ".nsf", false);

			{
				if (dbMail == null) {
					log.error("无法打开用户数据库文件" + user + ".nsf");
				} else {

					memo = (Document) dbMail.createDocument();

					memo.appendItemValue("Form", "Memo");

					subject = "good mail!";
					memo.appendItemValue("Subject", subject);

					rti = (RichTextItem) memo.createRichTextItem("Body");

					rti.addNewLine(2);
					rti.appendText("test mail!");

					String attachFilePath = "附件在DOMINO服务器上的位置";

					java.util.Vector v = new java.util.Vector();
					v.addElement(to[0]); // 收件人

					memo.setEncryptOnSend(true);
					memo.setSaveMessageOnSend(true);
					memo.setSignOnSend(true);
					memo.sign();

					if (attachFlag && (!attachFilePath.trim().equals(""))) {
						rti.embedObject(EmbeddedObject.EMBED_ATTACHMENT, null,
								attachFilePath, attachFilePath); // 添加附件
					}

					memo.setSaveMessageOnSend(true);
					memo.send(true, v);

				}
			}

			StringBuffer tmp = new StringBuffer();
			for (int j = 0; j < to.length; j++) {
				tmp.append(" ");
				tmp.append(to[j]);
			}
			java.util.Date endDate = new Date();
			log.info("发送邮件成功！");
			/**
			MailDatabase.insertMailSent(userID, sqlServer, from,
					tmp.toString(), smtpServer, popServer, subject, interval,
					priorityLevel, dateSent, endDate, probeHost, attachedSize,
					returnState, null, null);
			**/

		} catch (NotesException e) {
			log.error("发送LOTUS邮件失败：" + ((lotus.domino.NotesException) e).text);

		} catch (Exception ex) {

			log.error("发送LOTUS邮件失败：" + ex);

		} finally {
			try {
				if (sNotes != null) {
					if (dbMail != null) {
						dbMail.recycle();
					}

					sNotes.recycle(); // 一定要关闭，否则会使SERVER崩溃
					dbMail = null;
					sNotes = null;
					// log.info("===========lotus version:"+
					// sNotes.getNotesVersion());
				}
			} catch (NotesException ex1) {
				log.error("关闭SESSION出错！");
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

    public boolean sendMail(String user, String pass, String receivers, String title,
            String content)
    {
        boolean ret = false;
        try
        {
            String host = "10.108.0.99";
            Session s = NotesFactory.createSession(host, user, pass);
            String DB_NAMES = "names.nsf";
            Database dbCache = s.getDatabase(s.getServerName(), DB_NAMES, false);
            View view = dbCache.getView("($Users)");
            Document docKey = view.getDocumentByKey("test");
            //if (docKey != null)
            //{
                String strMailFile = docKey.getItemValueString("MailFile");
                dbMail = s.getDatabase(s.getServerName(), strMailFile + ".nsf", false);
                if (dbMail != null)
                {
                    Document doc = dbMail.createDocument();
                    doc.replaceItemValue("Subject", title);
                    doc.replaceItemValue("Body", content);
                    doc.replaceItemValue("From", user);
                    doc.send(receivers);
                    ret = true;
                }
                else
                {
                    ret = false;
                }
            //}
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        return ret;
    }
}

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
 * ����lotus�ʼ����ͻ���domino5.11�汾�������ʼ���Ҫ�ο�5.11��designer��JAVA���LOTUS���ݿ�Ĳ�����
 * ��ӵĸ����������DOMINO�������ϣ����ܷ��ڿͻ�����Ӹ�������Ҫ��Ϊʲô��������ʵ�� ���磺����AS400
 * ��em_01/test/test.tar,�ڳ���ʹ�����·����"test/test.tar"������ʼ��ĸ�Ŀ¼em_01.
 * 
 * �ڲ������Ҫ��DOMINO�ϵ�ʹ�õ���Դ�ͷŵ���һ��ֻ���ͷŵ�database��session.
 * �﷨��database.recycle(),session.recycle();
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

	/** ��־�ļ� */
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
					log.error("�޷����û����ݿ��ļ�" + user + ".nsf");
				} else {

					memo = (Document) dbMail.createDocument();

					memo.appendItemValue("Form", "Memo");

					subject = "good mail!";
					memo.appendItemValue("Subject", subject);

					rti = (RichTextItem) memo.createRichTextItem("Body");

					rti.addNewLine(2);
					rti.appendText("test mail!");

					String attachFilePath = "������DOMINO�������ϵ�λ��";

					java.util.Vector v = new java.util.Vector();
					v.addElement(to[0]); // �ռ���

					memo.setEncryptOnSend(true);
					memo.setSaveMessageOnSend(true);
					memo.setSignOnSend(true);
					memo.sign();

					if (attachFlag && (!attachFilePath.trim().equals(""))) {
						rti.embedObject(EmbeddedObject.EMBED_ATTACHMENT, null,
								attachFilePath, attachFilePath); // ��Ӹ���
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
			log.info("�����ʼ��ɹ���");
			/**
			MailDatabase.insertMailSent(userID, sqlServer, from,
					tmp.toString(), smtpServer, popServer, subject, interval,
					priorityLevel, dateSent, endDate, probeHost, attachedSize,
					returnState, null, null);
			**/

		} catch (NotesException e) {
			log.error("����LOTUS�ʼ�ʧ�ܣ�" + ((lotus.domino.NotesException) e).text);

		} catch (Exception ex) {

			log.error("����LOTUS�ʼ�ʧ�ܣ�" + ex);

		} finally {
			try {
				if (sNotes != null) {
					if (dbMail != null) {
						dbMail.recycle();
					}

					sNotes.recycle(); // һ��Ҫ�رգ������ʹSERVER����
					dbMail = null;
					sNotes = null;
					// log.info("===========lotus version:"+
					// sNotes.getNotesVersion());
				}
			} catch (NotesException ex1) {
				log.error("�ر�SESSION����");
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

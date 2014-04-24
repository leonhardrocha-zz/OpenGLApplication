#include <QObject>
#include <SingleFace.h>

class Worker : public QObject {
    Q_OBJECT
	
public:
    Worker();
    ~Worker();
	void SetMessage(void* message) { m_message = message; }
 
public slots:
    void process();
 
signals:
    void finished();
    void error(QString err);
 
private:
    // add your variables here
	void * m_message;
	MyTracker tracker;
};
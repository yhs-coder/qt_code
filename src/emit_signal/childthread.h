#ifndef CHILDTHREAD_H
#define CHILDTHREAD_H

#include <QThread>
#include <string>

using namespace std;

struct Score
{
    string name;
    int    id;
    int    age;
};

class ChildThread : public QThread
{
    Q_OBJECT
public:
    explicit ChildThread(QObject* parent = nullptr);

protected:
    void run() override;

signals:
    void sig_sendToUI(Score score);
    void sig2(string name, int id, int age);
};

#endif  // CHILDTHREAD_H
